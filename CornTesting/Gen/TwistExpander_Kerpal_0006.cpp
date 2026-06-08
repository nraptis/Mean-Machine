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

#include <cstring>

TwistExpander_Kerpal_0006::TwistExpander_Kerpal_0006()
: TwistExpander() {
    mDomainBundleInbuilt.mPhaseASalts = kPhaseASalts;
    mDomainBundleInbuilt.mPhaseAConstants = kPhaseAConstants;
    mDomainBundleInbuilt.mPhaseBSalts = kPhaseBSalts;
    mDomainBundleInbuilt.mPhaseBConstants = kPhaseBConstants;
    mDomainBundleInbuilt.mPhaseCSalts = kPhaseCSalts;
    mDomainBundleInbuilt.mPhaseCConstants = kPhaseCConstants;
    mDomainBundleInbuilt.mPhaseDSalts = kPhaseDSalts;
    mDomainBundleInbuilt.mPhaseDConstants = kPhaseDConstants;
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

    std::uint64_t aMatrixWriteIndex = 0; std::uint64_t aMatrixSlotA = 0; std::uint64_t aMatrixSlotB = 0; std::uint64_t aMatrixLoadIndexA = 0;
    std::uint64_t aMatrixLoadIndexB = 0; std::uint64_t aM88OperationIndex = 0; std::uint64_t aM88SourceIndex = 0; std::uint64_t aM88DestinationIndex = 0;
    std::uint64_t aM88UnrollDomainWord = 0; std::uint64_t aM88ArgADomainWord = 0; std::uint64_t aM88ArgBDomainWord = 0; std::uint64_t aM88ArgCDomainWord = 0;
    std::uint64_t aM88ArgDDomainWord = 0;

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
        aPrevious = 9372575038315840217U;
        aCarry = 12506796463528335919U;
        aWandererA = 13917397068999024099U;
        aWandererB = 14672984858452395245U;
        aWandererC = 16424676979066791081U;
        aWandererD = 10548582234627702811U;
        aWandererE = 18073086942917714561U;
        aWandererF = 12181728369307218404U;
        aWandererG = 12957068327883664606U;
        aWandererH = 18096217198176768615U;
        aWandererI = 12156433239496057671U;
        aWandererJ = 10910611036851333207U;
        aWandererK = 15711187159069657770U;
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteC, 57U) ^ RotL64(aNonceByteH, 19U)) ^ RotL64(aNonceByteB, 11U));
            aIngress = aIngress ^ (RotL64(aSource[((aIndex + 24553U)) & S_BLOCK1], 3U) ^ RotL64(mSnow[((aIndex + 32167U)) & S_BLOCK1], 38U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteE, 27U) ^ RotL64(aNonceByteF, 11U));
            aCross = aCross ^ (RotL64(mSnow[((S_BLOCK1 - aIndex + 30131U)) & S_BLOCK1], 41U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 12916U)) & S_BLOCK1], 60U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 11U) ^ RotL64(aPrevious, 35U)) ^ (RotL64(aIngress, 52U) + RotL64(aCross, 23U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = (aWandererC + RotL64(aIngress, 35U)) + 5697928251815176134U;
            aOrbiterC = (((aWandererI + RotL64(aCross, 51U)) + RotL64(aCarry, 35U)) + 337587740689259575U) + RotL64(aNonceByteC, 47U);
            aOrbiterB = ((((aWandererK + RotL64(aPrevious, 60U)) + RotL64(aCarry, 23U)) + 4927686903263973950U) + aOrbiterAssignSaltB[((aIndex + 6990U)) & S_SALT1]) + RotL64(aNonceByteF, 5U);
            aOrbiterI = ((aWandererE + RotL64(aScatter, 21U)) + RotL64(aCarry, 47U)) + 3742409032569801033U;
            aOrbiterE = ((aWandererD + RotL64(aCross, 5U)) + 1608092659172197650U) + aOrbiterAssignSaltF[((aIndex + 7437U)) & S_SALT1];
            //
            aOrbiterF = ((aOrbiterF + aOrbiterC) + 15848744267145717509U) + RotL64(aNonceByteA, 21U);
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 15300174177963339253U;
            aOrbiterB = RotL64((aOrbiterB * 5771922862677667319U), 41U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterE) + 14162868453323648628U) + RotL64(aNonceByteD, 41U);
            aOrbiterF = ((aOrbiterF ^ aOrbiterI) ^ 12020167069983729869U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 1606U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 2071080217680099017U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 16259538291658723956U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterC) ^ 8516686212464112245U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 4757U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 4731296903548893627U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterF) + 3722184575520553132U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 5663609293306386784U;
            aOrbiterC = RotL64((aOrbiterC * 14364218128780764749U), 53U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterI) + 15265344442454471986U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 2268U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 3050323350098829515U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 3828U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 5890624677162388135U), 13U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterE, 23U);
            aIngress = aIngress + (RotL64(aOrbiterB, 48U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterF, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 20U) + aOrbiterC) + RotL64(aOrbiterI, 29U)) + RotL64(pNonce, 40U));
            aWandererE = aWandererE + ((((RotL64(aIngress, 3U) + RotL64(aOrbiterB, 3U)) + aOrbiterF) + RotL64(aCarry, 47U)) + aWandererUpdateSaltD[((aIndex + 567U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aScatter, 39U) + RotL64(aOrbiterF, 14U)) + aOrbiterE);
            aWandererC = aWandererC + ((((RotL64(aCross, 57U) + aOrbiterB) + RotL64(aOrbiterE, 57U)) + RotL64(aCarry, 29U)) + aWandererUpdateSaltA[((aIndex + 1083U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 11U) + aOrbiterC) + RotL64(aOrbiterE, 43U)) + RotL64(aNonceByteG, 43U));
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererI, 57U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererE, 47U));
            aCarry = aCarry + RotL64(aWandererC, 13U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteF, 48U) ^ RotL64(aNonceByteG, 27U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 20123U)) & S_BLOCK1], 35U) ^ RotL64(aSource[((aIndex + 21860U)) & S_BLOCK1], 13U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteA, 19U) ^ RotL64(aNonceByteB, 30U));
            aCross = aCross ^ (RotL64(mSnow[((S_BLOCK1 - aIndex + 20803U)) & S_BLOCK1], 11U) ^ RotL64(aSource[((aIndex + 32570U)) & S_BLOCK1], 43U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 21U) + RotL64(aCross, 38U)) ^ (RotL64(aCarry, 53U) ^ RotL64(aPrevious, 5U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterC = ((aWandererG + RotL64(aPrevious, 11U)) + RotL64(aCarry, 51U)) + 12775735908960052604U;
            aOrbiterJ = ((((aWandererA + RotL64(aScatter, 21U)) + RotL64(aCarry, 35U)) + 11791373812080296887U) + aOrbiterAssignSaltD[((aIndex + 6363U)) & S_SALT1]) + RotL64(aNonceByteC, 54U);
            aOrbiterD = (((aWandererJ + RotL64(aCross, 35U)) + RotL64(aCarry, 13U)) + 5537362877706057303U) + RotL64(aNonceByteE, 41U);
            aOrbiterG = (aWandererF + RotL64(aIngress, 52U)) + 2023912048504189380U;
            aOrbiterH = ((aWandererE + RotL64(aScatter, 3U)) + 17668828109963766893U) + aOrbiterAssignSaltC[((aIndex + 4252U)) & S_SALT1];
            //
            aOrbiterC = ((aOrbiterC + aOrbiterJ) + 558908629933941224U) + aOrbiterUpdateSaltB[((aIndex + 2691U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterC) ^ 1479633119685446888U) ^ RotL64(aNonceByteH, 27U);
            aOrbiterD = RotL64((aOrbiterD * 4447153373540811385U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 15460320397843364063U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterJ) ^ 10059749397555469054U) ^ RotL64(aNonceByteB, 47U);
            aOrbiterH = RotL64((aOrbiterH * 8671817118586065469U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 9987633811929693924U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterG) ^ 10087337844580228269U) ^ aOrbiterUpdateSaltA[((aIndex + 4730U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 13817142288940843815U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 4446204415503364254U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterD) ^ 15106063243302192717U) ^ aOrbiterUpdateSaltD[((aIndex + 3463U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 13273756657334709803U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 9430197906134676162U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 1226048679997253363U) ^ aOrbiterUpdateSaltF[((aIndex + 3225U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 14247538885252664127U), 13U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterJ, 43U);
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterD, 53U));
            aIngress = aIngress + RotL64(aOrbiterH, 30U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererJ = aWandererJ ^ ((((RotL64(aCross, 51U) + aOrbiterJ) + RotL64(aOrbiterC, 3U)) + RotL64(aNonceByteD, 53U)) + aWandererUpdateSaltC[(((31U - aIndex) + 253U)) & S_SALT1]);
            aWandererA = aWandererA + ((((RotL64(aScatter, 24U) + RotL64(aOrbiterD, 43U)) + aOrbiterH) + RotL64(aCarry, 41U)) + RotL64(aNonceByteA, 25U));
            aWandererF = aWandererF ^ (((RotL64(aIngress, 39U) + RotL64(aOrbiterH, 24U)) + aOrbiterC) + aWandererUpdateSaltB[(((31U - aIndex) + 4683U)) & S_SALT1]);
            aWandererE = aWandererE + (((RotL64(aPrevious, 13U) + aOrbiterC) + RotL64(aOrbiterG, 13U)) + RotL64(aCarry, 29U));
            aWandererG = aWandererG ^ ((RotL64(aScatter, 5U) + RotL64(aOrbiterG, 57U)) + aOrbiterD);
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererF, 43U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererA, 21U));
            aCarry = aCarry + RotL64(aWandererG, 13U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 5U) ^ RotL64(aNonceByteG, 53U)) ^ RotL64(aNonceByteF, 13U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 15072U)) & S_BLOCK1], 24U) ^ RotL64(aExpandLaneA[((aIndex + 8276U)) & S_BLOCK1], 37U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteH, 50U) ^ RotL64(aNonceByteB, 37U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 29612U)) & S_BLOCK1], 27U) ^ RotL64(mSnow[((S_BLOCK1 - aIndex + 22368U)) & S_BLOCK1], 19U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 51U) ^ RotL64(aCarry, 38U)) + (RotL64(aCross, 23U) ^ RotL64(aIngress, 5U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterC = ((aWandererH + RotL64(aScatter, 56U)) + RotL64(aCarry, 19U)) + 11274974230580265396U;
            aOrbiterG = (((aWandererE + RotL64(aPrevious, 47U)) + RotL64(aCarry, 35U)) + 16658438747342741547U) + RotL64(aNonceByteD, 61U);
            aOrbiterK = (((aWandererJ + RotL64(aCross, 11U)) + RotL64(aCarry, 57U)) + 16612986966106053844U) + aOrbiterAssignSaltA[((aIndex + 2986U)) & S_SALT1];
            aOrbiterH = (aWandererD + RotL64(aIngress, 29U)) + 9329502236843231290U;
            aOrbiterB = (((aWandererA + RotL64(aCross, 37U)) + 14088261356708344656U) + aOrbiterAssignSaltE[(((31U - aIndex) + 4187U)) & S_SALT1]) + RotL64(aNonceByteE, 17U);
            //
            aOrbiterC = (((aOrbiterC + aOrbiterG) + 13692608802007789581U) + aOrbiterUpdateSaltA[((aIndex + 2383U)) & S_SALT1]) + RotL64(aNonceByteA, 9U);
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 6824473946645682398U;
            aOrbiterK = RotL64((aOrbiterK * 13619437545775237601U), 29U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 2072915876348570040U;
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 7420507753044460759U;
            aOrbiterG = RotL64((aOrbiterG * 13239288539564571257U), 3U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterH) + 4677557318688502593U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 209U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterB) ^ 15081678577055628459U) ^ aOrbiterUpdateSaltF[((aIndex + 3699U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 16659305295251177155U), 41U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterB) + 7026792817486507482U) + aOrbiterUpdateSaltD[((aIndex + 1786U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 14871665922943969918U;
            aOrbiterH = RotL64((aOrbiterH * 694073180313083145U), 21U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 6807734532159292872U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterG) ^ 17882797335141303280U) ^ RotL64(aNonceByteB, 23U);
            aOrbiterB = RotL64((aOrbiterB * 15439872930381050291U), 53U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterK, 47U);
            aIngress = aIngress + (RotL64(aOrbiterG, 19U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterC, 5U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererE = aWandererE ^ (((RotL64(aPrevious, 21U) + aOrbiterG) + RotL64(aOrbiterK, 47U)) + RotL64(aNonceByteC, 39U));
            aWandererA = aWandererA + (((RotL64(aIngress, 11U) + aOrbiterH) + RotL64(aOrbiterB, 3U)) + RotL64(aCarry, 37U));
            aWandererD = aWandererD ^ ((RotL64(aScatter, 39U) + RotL64(aOrbiterC, 22U)) + aOrbiterG);
            aWandererJ = aWandererJ + ((((RotL64(aCross, 48U) + RotL64(aOrbiterH, 11U)) + aOrbiterC) + RotL64(aCarry, 23U)) + aWandererUpdateSaltE[((aIndex + 6853U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((((RotL64(aPrevious, 3U) + aOrbiterH) + RotL64(aOrbiterK, 57U)) + RotL64(aNonceByteF, 44U)) + aWandererUpdateSaltF[(((31U - aIndex) + 2066U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererJ, 46U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererA, 21U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererD, 37U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteD, 23U) ^ RotL64(aNonceByteH, 11U)) ^ RotL64(aNonceByteA, 50U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 10575U)) & S_BLOCK1], 39U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 241U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteF, 29U) ^ RotL64(aNonceByteB, 13U)) ^ RotL64(aNonceByteG, 5U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 4578U)) & S_BLOCK1], 52U) ^ RotL64(aSource[((aIndex + 5692U)) & S_BLOCK1], 43U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 19U) ^ RotL64(aCross, 3U)) + (RotL64(aIngress, 41U) ^ RotL64(aCarry, 54U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = ((aWandererG + RotL64(aScatter, 27U)) + RotL64(aCarry, 5U)) + 17264605017518259932U;
            aOrbiterG = (((aWandererF + RotL64(aCross, 42U)) + RotL64(aCarry, 47U)) + 15209184354580778643U) + RotL64(aNonceByteA, 7U);
            aOrbiterB = (aWandererE + RotL64(aIngress, 5U)) + 3299527965014731384U;
            aOrbiterC = ((((aWandererH + RotL64(aPrevious, 51U)) + RotL64(aCarry, 23U)) + 16293096431816127821U) + aOrbiterAssignSaltB[((aIndex + 4043U)) & S_SALT1]) + RotL64(aNonceByteG, 39U);
            aOrbiterF = ((aWandererK + RotL64(aCross, 19U)) + 11031983436878828337U) + aOrbiterAssignSaltF[(((31U - aIndex) + 3509U)) & S_SALT1];
            //
            aOrbiterH = (aOrbiterH + aOrbiterG) + 9188018632448236358U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 13420816400363406556U;
            aOrbiterB = RotL64((aOrbiterB * 10958221259662190519U), 23U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 2485063384097917101U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterC) ^ 3089135816938128264U) ^ aOrbiterUpdateSaltC[((aIndex + 7945U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 8813152992957361153U), 43U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterB) + 10730544971770435788U) + aOrbiterUpdateSaltA[((aIndex + 3192U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterG) ^ 10431767565618874806U) ^ aOrbiterUpdateSaltD[((aIndex + 5556U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 4723078464590561545U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 14883796491656899074U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 13465877783538483706U;
            aOrbiterG = RotL64((aOrbiterG * 14311686051108108503U), 5U);
            //
            aOrbiterB = (((aOrbiterB + aOrbiterC) + 13322163435314643713U) + aOrbiterUpdateSaltE[((aIndex + 5872U)) & S_SALT1]) + RotL64(aNonceByteB, 51U);
            aOrbiterF = ((aOrbiterF ^ aOrbiterB) ^ 3307316600284371955U) ^ RotL64(aNonceByteF, 25U);
            aOrbiterF = RotL64((aOrbiterF * 12337846092069506365U), 53U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterH, 57U);
            aIngress = aIngress + (RotL64(aOrbiterC, 35U) ^ aOrbiterF);
            aIngress = aIngress + RotL64(aOrbiterG, 47U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ (((RotL64(aCross, 29U) + RotL64(aOrbiterH, 19U)) + aOrbiterG) + aWandererUpdateSaltD[((aIndex + 5805U)) & S_SALT1]);
            aWandererF = aWandererF + ((((RotL64(aIngress, 37U) + RotL64(aOrbiterF, 57U)) + aOrbiterH) + RotL64(aCarry, 23U)) + RotL64(aNonceByteC, 13U));
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 11U) + RotL64(aOrbiterF, 6U)) + aOrbiterC);
            aWandererE = aWandererE + (((RotL64(aScatter, 57U) + aOrbiterC) + RotL64(aOrbiterH, 41U)) + RotL64(aCarry, 53U));
            aWandererH = aWandererH ^ ((((RotL64(aCross, 48U) + RotL64(aOrbiterC, 29U)) + aOrbiterB) + RotL64(aNonceByteE, 20U)) + aWandererUpdateSaltA[((aIndex + 1418U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererF, 21U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererG, 3U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererE, 51U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteG, 42U) ^ RotL64(aNonceByteB, 13U)) ^ RotL64(aNonceByteF, 5U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 11880U)) & S_BLOCK1], 23U) ^ RotL64(aExpandLaneC[((aIndex + 23963U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteA, 35U) ^ RotL64(aNonceByteD, 21U)) ^ RotL64(aNonceByteH, 3U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 23970U)) & S_BLOCK1], 43U) ^ RotL64(aExpandLaneA[((aIndex + 18077U)) & S_BLOCK1], 54U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 50U) ^ RotL64(aCross, 3U)) + (RotL64(aCarry, 35U) ^ RotL64(aPrevious, 21U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterB = ((((aWandererC + RotL64(aCross, 23U)) + RotL64(aCarry, 13U)) + 10336802574069791273U) + aOrbiterAssignSaltF[((aIndex + 4829U)) & S_SALT1]) + RotL64(aNonceByteD, 3U);
            aOrbiterG = ((aWandererG + RotL64(aScatter, 14U)) + RotL64(aCarry, 53U)) + 169025388197058936U;
            aOrbiterA = (aWandererF + RotL64(aIngress, 35U)) + 6541354188379168846U;
            aOrbiterK = (((aWandererH + RotL64(aPrevious, 57U)) + RotL64(aCarry, 37U)) + 16223920526599306104U) + aOrbiterAssignSaltA[((aIndex + 7182U)) & S_SALT1];
            aOrbiterE = ((aWandererJ + RotL64(aCross, 3U)) + 12756613707692514808U) + RotL64(aNonceByteG, 29U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterG) + 5082475548176484035U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 8043U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterB) ^ 4907435526952698526U;
            aOrbiterA = RotL64((aOrbiterA * 1379692095754989215U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 14236627073831834337U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterK) ^ 11502511046130497584U) ^ RotL64(aNonceByteE, 50U);
            aOrbiterB = RotL64((aOrbiterB * 3460330807286625917U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 3679044835550219497U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterG) ^ 11254838916686736746U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 5242U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 8631695922983532915U), 23U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 10582608424233200966U) + aOrbiterUpdateSaltD[((aIndex + 7335U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 10449735026385340313U;
            aOrbiterG = RotL64((aOrbiterG * 7363770199734997411U), 11U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterK) + 4628253464169957835U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 7003U)) & S_SALT1]) + RotL64(aNonceByteB, 53U);
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 17664454668473204465U;
            aOrbiterE = RotL64((aOrbiterE * 4234720298731378527U), 43U);
            //
            aIngress = RotL64(aOrbiterG, 51U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterA, 29U));
            aIngress = aIngress + RotL64(aOrbiterB, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG ^ (((RotL64(aIngress, 27U) + RotL64(aOrbiterA, 21U)) + aOrbiterE) + RotL64(pNonce, 15U));
            aWandererF = aWandererF + (((RotL64(aPrevious, 5U) + aOrbiterG) + RotL64(aOrbiterK, 51U)) + RotL64(aCarry, 21U));
            aWandererJ = aWandererJ ^ ((((RotL64(aCross, 56U) + RotL64(aOrbiterB, 11U)) + aOrbiterE) + RotL64(aNonceByteC, 51U)) + aWandererUpdateSaltF[(((31U - aIndex) + 4082U)) & S_SALT1]);
            aWandererC = aWandererC + ((((RotL64(aScatter, 13U) + aOrbiterG) + RotL64(aOrbiterE, 39U)) + RotL64(aCarry, 37U)) + aWandererUpdateSaltD[((aIndex + 7225U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aIngress, 43U) + aOrbiterE) + RotL64(aOrbiterK, 30U));
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererC, 38U));
            aCarry = aCarry + (RotL64(aWandererG, 21U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererJ, 5U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 19U) ^ RotL64(aNonceByteH, 29U));
            aIngress = aIngress ^ (RotL64(aOperationLaneA[((aIndex + 21392U)) & S_BLOCK1], 37U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 21042U)) & S_BLOCK1], 52U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 11U) ^ RotL64(aNonceByteC, 44U)) ^ RotL64(aNonceByteB, 21U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 30809U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 28842U)) & S_BLOCK1], 29U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 35U) + RotL64(aIngress, 3U)) ^ (RotL64(aPrevious, 21U) ^ RotL64(aCross, 48U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterB = ((aWandererF + RotL64(aPrevious, 13U)) + RotL64(aCarry, 37U)) + 17264605017518259932U;
            aOrbiterJ = ((aWandererA + RotL64(aCross, 43U)) + 15209184354580778643U) + aOrbiterAssignSaltC[(((31U - aIndex) + 571U)) & S_SALT1];
            aOrbiterC = ((((aWandererI + RotL64(aScatter, 23U)) + RotL64(aCarry, 53U)) + 3299527965014731384U) + aOrbiterAssignSaltE[((aIndex + 2745U)) & S_SALT1]) + RotL64(aNonceByteF, 61U);
            aOrbiterD = (aWandererD + RotL64(aIngress, 58U)) + 16293096431816127821U;
            aOrbiterK = (((aWandererG + RotL64(aCross, 5U)) + RotL64(aCarry, 23U)) + 11031983436878828337U) + RotL64(aNonceByteA, 23U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterJ) + 9188018632448236358U) + aOrbiterUpdateSaltF[((aIndex + 7085U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 13420816400363406556U;
            aOrbiterC = RotL64((aOrbiterC * 10958221259662190519U), 3U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 2485063384097917101U;
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 3089135816938128264U;
            aOrbiterK = RotL64((aOrbiterK * 8813152992957361153U), 35U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterC) + 10730544971770435788U) + RotL64(aNonceByteH, 47U);
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 10431767565618874806U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 5737U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 4723078464590561545U), 57U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterK) + 14883796491656899074U) + RotL64(aNonceByteB, 45U);
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 13465877783538483706U;
            aOrbiterJ = RotL64((aOrbiterJ * 14311686051108108503U), 13U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterB) + 13322163435314643713U) + aOrbiterUpdateSaltB[((aIndex + 6053U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterK) ^ 3307316600284371955U) ^ aOrbiterUpdateSaltA[((aIndex + 3315U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 12337846092069506365U), 27U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterJ, 41U);
            aIngress = aIngress + (RotL64(aOrbiterD, 53U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterC, 3U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aIngress, 53U) + aOrbiterK) + RotL64(aOrbiterC, 51U)) + RotL64(aCarry, 3U));
            aWandererD = aWandererD ^ (((RotL64(aCross, 5U) + aOrbiterJ) + RotL64(aOrbiterD, 60U)) + aWandererUpdateSaltB[(((31U - aIndex) + 2642U)) & S_SALT1]);
            aWandererA = aWandererA + ((((RotL64(aPrevious, 43U) + aOrbiterD) + RotL64(aOrbiterC, 35U)) + RotL64(aCarry, 51U)) + RotL64(aNonceByteE, 60U));
            aWandererI = aWandererI ^ ((((RotL64(aScatter, 19U) + aOrbiterB) + RotL64(aOrbiterD, 19U)) + RotL64(aNonceByteG, 13U)) + aWandererUpdateSaltE[((aIndex + 4548U)) & S_SALT1]);
            aWandererF = aWandererF + ((RotL64(aPrevious, 34U) + aOrbiterD) + RotL64(aOrbiterK, 11U));
            //
            aCarry = aCarry + (RotL64(aWandererG, 11U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererI, 3U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererD, 21U);
            aCarry = aCarry + RotL64(aIngress, 41U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteE, 42U) ^ RotL64(aNonceByteF, 13U)) ^ RotL64(aNonceByteG, 21U));
            aIngress = aIngress ^ (RotL64(aOperationLaneB[((aIndex + 30588U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 23930U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteB, 48U) ^ RotL64(aNonceByteD, 37U)) ^ RotL64(aNonceByteH, 23U));
            aCross = aCross ^ (RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 19951U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneC[((aIndex + 11537U)) & S_BLOCK1], 57U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 37U) + RotL64(aCross, 23U)) ^ (RotL64(aCarry, 50U) ^ RotL64(aPrevious, 5U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = ((aWandererK + RotL64(aPrevious, 19U)) + 11274974230580265396U) + aOrbiterAssignSaltD[((aIndex + 5683U)) & S_SALT1];
            aOrbiterI = (((aWandererD + RotL64(aIngress, 52U)) + RotL64(aCarry, 47U)) + 16658438747342741547U) + aOrbiterAssignSaltB[((aIndex + 4451U)) & S_SALT1];
            aOrbiterD = ((aWandererH + RotL64(aScatter, 3U)) + RotL64(aCarry, 19U)) + 16612986966106053844U;
            aOrbiterK = (((aWandererC + RotL64(aCross, 11U)) + RotL64(aCarry, 5U)) + 9329502236843231290U) + RotL64(aNonceByteA, 21U);
            aOrbiterA = ((aWandererJ + RotL64(aPrevious, 37U)) + 14088261356708344656U) + RotL64(aNonceByteD, 19U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterI) + 13692608802007789581U) + RotL64(aNonceByteH, 50U);
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 6824473946645682398U;
            aOrbiterD = RotL64((aOrbiterD * 13619437545775237601U), 23U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterH) + 2072915876348570040U) + aOrbiterUpdateSaltB[((aIndex + 2685U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 7420507753044460759U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 2089U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 13239288539564571257U), 3U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterK) + 4677557318688502593U) + RotL64(aNonceByteE, 13U);
            aOrbiterH = ((aOrbiterH ^ aOrbiterA) ^ 15081678577055628459U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 5031U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 16659305295251177155U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 7026792817486507482U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 14871665922943969918U;
            aOrbiterK = RotL64((aOrbiterK * 694073180313083145U), 47U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 6807734532159292872U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterI) ^ 17882797335141303280U) ^ aOrbiterUpdateSaltF[((aIndex + 154U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 15439872930381050291U), 57U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterI, 3U);
            aIngress = aIngress + (RotL64(aOrbiterD, 13U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterH, 23U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ (((RotL64(aIngress, 50U) + aOrbiterD) + RotL64(aOrbiterI, 41U)) + RotL64(aNonceByteC, 37U));
            aWandererD = aWandererD + (((RotL64(aScatter, 29U) + aOrbiterK) + RotL64(aOrbiterA, 56U)) + RotL64(aCarry, 57U));
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 19U) + aOrbiterH) + RotL64(aOrbiterK, 13U));
            aWandererH = aWandererH + ((((RotL64(aCross, 37U) + RotL64(aOrbiterK, 3U)) + aOrbiterD) + RotL64(aCarry, 29U)) + aWandererUpdateSaltC[(((31U - aIndex) + 402U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((((RotL64(aIngress, 5U) + RotL64(aOrbiterH, 27U)) + aOrbiterI) + RotL64(aNonceByteF, 15U)) + aWandererUpdateSaltA[(((31U - aIndex) + 923U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererH, 43U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererJ, 5U));
            aCarry = aCarry + RotL64(aWandererC, 60U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteG, 21U) ^ RotL64(aNonceByteA, 37U)) ^ RotL64(aNonceByteD, 5U));
            aIngress = aIngress ^ (RotL64(aOperationLaneC[((aIndex + 9631U)) & S_BLOCK1], 47U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 4837U)) & S_BLOCK1], 56U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 37U) ^ RotL64(aNonceByteF, 19U)) ^ RotL64(aNonceByteH, 3U));
            aCross = aCross ^ (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 8861U)) & S_BLOCK1], 48U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 8396U)) & S_BLOCK1], 11U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 18U) + RotL64(aPrevious, 3U)) ^ (RotL64(aIngress, 51U) ^ RotL64(aCross, 35U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterE = ((aWandererI + RotL64(aPrevious, 47U)) + RotL64(aCarry, 5U)) + 12775735908960052604U;
            aOrbiterC = (aWandererD + RotL64(aScatter, 10U)) + 11791373812080296887U;
            aOrbiterB = ((((aWandererK + RotL64(aCross, 57U)) + RotL64(aCarry, 37U)) + 5537362877706057303U) + aOrbiterAssignSaltA[(((31U - aIndex) + 2323U)) & S_SALT1]) + RotL64(aNonceByteB, 53U);
            aOrbiterD = ((((aWandererC + RotL64(aIngress, 21U)) + RotL64(aCarry, 57U)) + 2023912048504189380U) + aOrbiterAssignSaltF[((aIndex + 6737U)) & S_SALT1]) + RotL64(aNonceByteC, 61U);
            aOrbiterK = (aWandererH + RotL64(aCross, 29U)) + 17668828109963766893U;
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 558908629933941224U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 1479633119685446888U;
            aOrbiterB = RotL64((aOrbiterB * 4447153373540811385U), 47U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterK) + 15460320397843364063U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 1710U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterD) ^ 10059749397555469054U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 5403U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 8671817118586065469U), 35U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterB) + 9987633811929693924U) + aOrbiterUpdateSaltE[((aIndex + 5300U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 10087337844580228269U;
            aOrbiterD = RotL64((aOrbiterD * 13817142288940843815U), 11U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 4446204415503364254U) + aOrbiterUpdateSaltF[((aIndex + 880U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 15106063243302192717U) ^ RotL64(aNonceByteF, 47U);
            aOrbiterC = RotL64((aOrbiterC * 13273756657334709803U), 3U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 9430197906134676162U) + RotL64(aNonceByteA, 5U);
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 1226048679997253363U;
            aOrbiterK = RotL64((aOrbiterK * 14247538885252664127U), 27U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterD, 3U);
            aIngress = aIngress + (RotL64(aOrbiterB, 44U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterK, 57U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ ((RotL64(aCross, 53U) + RotL64(aOrbiterK, 3U)) + aOrbiterE);
            aWandererI = aWandererI + (((RotL64(aScatter, 43U) + aOrbiterK) + RotL64(aOrbiterD, 51U)) + RotL64(aCarry, 21U));
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 3U) + RotL64(aOrbiterC, 21U)) + aOrbiterB) + RotL64(aNonceByteE, 17U));
            aWandererH = aWandererH + ((((RotL64(aIngress, 30U) + aOrbiterC) + RotL64(aOrbiterE, 40U)) + RotL64(aCarry, 35U)) + aWandererUpdateSaltF[((aIndex + 3719U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((((RotL64(aScatter, 13U) + RotL64(aOrbiterB, 13U)) + aOrbiterK) + RotL64(aNonceByteD, 4U)) + aWandererUpdateSaltD[(((31U - aIndex) + 5803U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererC, 13U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererK, 3U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererI, 35U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteG, 11U) ^ RotL64(aNonceByteD, 58U)) ^ RotL64(aNonceByteH, 19U));
            aIngress = aIngress ^ (RotL64(aOperationLaneD[((aIndex + 8026U)) & S_BLOCK1], 35U) ^ RotL64(aOperationLaneC[((aIndex + 15134U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 50U) ^ RotL64(aNonceByteE, 5U));
            aCross = aCross ^ (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 14995U)) & S_BLOCK1], 13U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 30055U)) & S_BLOCK1], 23U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 57U) + RotL64(aCarry, 10U)) ^ (RotL64(aIngress, 23U) ^ RotL64(aCross, 35U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = (((aWandererI + RotL64(aPrevious, 35U)) + RotL64(aCarry, 51U)) + 3339283916456813609U) + RotL64(aNonceByteC, 41U);
            aOrbiterJ = ((aWandererK + RotL64(aScatter, 21U)) + 11339086426180649584U) + RotL64(aNonceByteB, 19U);
            aOrbiterA = (((aWandererB + RotL64(aIngress, 44U)) + RotL64(aCarry, 27U)) + 16819191669329316585U) + aOrbiterAssignSaltD[(((31U - aIndex) + 3333U)) & S_SALT1];
            aOrbiterH = ((aWandererJ + RotL64(aCross, 57U)) + RotL64(aCarry, 39U)) + 8361916937762630725U;
            aOrbiterD = ((aWandererH + RotL64(aScatter, 5U)) + 18031328374429899857U) + aOrbiterAssignSaltC[((aIndex + 47U)) & S_SALT1];
            //
            aOrbiterF = (aOrbiterF + aOrbiterJ) + 18261756894092897276U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 4250319792907645666U;
            aOrbiterA = RotL64((aOrbiterA * 7053489184750217963U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 1492411503643460886U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 17369549067879344180U;
            aOrbiterF = RotL64((aOrbiterF * 2947354306696216579U), 21U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterA) + 7301713524358676722U) + aOrbiterUpdateSaltA[((aIndex + 4533U)) & S_SALT1];
            aOrbiterH = ((aOrbiterH ^ aOrbiterJ) ^ 2985193736033012535U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 7369U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 7473297294949338265U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 14086975808140927408U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterD) ^ 10390516547834639800U) ^ aOrbiterUpdateSaltD[((aIndex + 3412U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 11441293212275890819U), 13U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterH) + 18205555540941493267U) + RotL64(aNonceByteD, 46U);
            aOrbiterD = (((aOrbiterD ^ aOrbiterA) ^ 16967799565443938873U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 5466U)) & S_SALT1]) ^ RotL64(aNonceByteG, 35U);
            aOrbiterD = RotL64((aOrbiterD * 3009081009044782443U), 57U);
            //
            aIngress = RotL64(aOrbiterJ, 22U) ^ aOrbiterA;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterH, 47U));
            aIngress = aIngress + RotL64(aOrbiterD, 57U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererH = aWandererH + ((((RotL64(aScatter, 27U) + aOrbiterA) + RotL64(aOrbiterD, 38U)) + RotL64(aCarry, 11U)) + aWandererUpdateSaltF[((aIndex + 377U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aIngress, 57U) + aOrbiterH) + RotL64(aOrbiterJ, 47U));
            aWandererJ = aWandererJ + (((RotL64(aCross, 43U) + RotL64(aOrbiterD, 27U)) + aOrbiterJ) + RotL64(aCarry, 43U));
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 6U) + aOrbiterD) + RotL64(aOrbiterF, 11U)) + RotL64(aNonceByteA, 25U));
            aWandererI = aWandererI + ((((RotL64(aIngress, 35U) + aOrbiterF) + RotL64(aOrbiterH, 57U)) + RotL64(aNonceByteF, 17U)) + aWandererUpdateSaltE[(((31U - aIndex) + 1095U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererJ, 3U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererI, 38U));
            aCarry = aCarry + RotL64(aWandererK, 27U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteG, 30U) ^ RotL64(aNonceByteF, 51U)) ^ RotL64(aNonceByteE, 5U));
            aIngress = aIngress ^ (RotL64(aWorkLaneA[((aIndex + 12642U)) & S_BLOCK1], 41U) ^ RotL64(aOperationLaneD[((aIndex + 27889U)) & S_BLOCK1], 21U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 28U) ^ RotL64(aNonceByteH, 3U));
            aCross = aCross ^ (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 20597U)) & S_BLOCK1], 37U) ^ RotL64(aOperationLaneB[((aIndex + 25058U)) & S_BLOCK1], 19U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 39U) + RotL64(aIngress, 23U)) ^ (RotL64(aCarry, 10U) + RotL64(aPrevious, 51U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterJ = (((aWandererG + RotL64(aScatter, 21U)) + RotL64(aCarry, 39U)) + 5697928251815176134U) + RotL64(aNonceByteD, 41U);
            aOrbiterC = ((aWandererD + RotL64(aCross, 11U)) + RotL64(aCarry, 5U)) + 337587740689259575U;
            aOrbiterA = ((aWandererK + RotL64(aIngress, 37U)) + 4927686903263973950U) + aOrbiterAssignSaltF[(((31U - aIndex) + 721U)) & S_SALT1];
            aOrbiterK = ((((aWandererI + RotL64(aPrevious, 3U)) + RotL64(aCarry, 21U)) + 3742409032569801033U) + aOrbiterAssignSaltB[((aIndex + 5048U)) & S_SALT1]) + RotL64(aNonceByteF, 11U);
            aOrbiterI = (aWandererE + RotL64(aIngress, 48U)) + 1608092659172197650U;
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterC) + 15848744267145717509U) + aOrbiterUpdateSaltF[((aIndex + 4467U)) & S_SALT1]) + RotL64(aNonceByteB, 37U);
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 15300174177963339253U;
            aOrbiterA = RotL64((aOrbiterA * 5771922862677667319U), 57U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 14162868453323648628U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterC) ^ 12020167069983729869U) ^ aOrbiterUpdateSaltB[((aIndex + 7690U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 2071080217680099017U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterA) + 16259538291658723956U) + aOrbiterUpdateSaltE[((aIndex + 1507U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 8516686212464112245U;
            aOrbiterJ = RotL64((aOrbiterJ * 4731296903548893627U), 47U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 3722184575520553132U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterA) ^ 5663609293306386784U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 5751U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 14364218128780764749U), 35U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterJ) + 15265344442454471986U) + RotL64(aNonceByteA, 17U);
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 3050323350098829515U;
            aOrbiterK = RotL64((aOrbiterK * 5890624677162388135U), 19U);
            //
            aIngress = RotL64(aOrbiterC, 14U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterI, 57U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterK, 3U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererI = aWandererI + ((((RotL64(aIngress, 51U) + aOrbiterC) + RotL64(aOrbiterJ, 3U)) + RotL64(aCarry, 57U)) + aWandererUpdateSaltD[(((31U - aIndex) + 5797U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aCross, 60U) + RotL64(aOrbiterK, 27U)) + aOrbiterC) + RotL64(aNonceByteG, 56U));
            aWandererK = aWandererK + ((RotL64(aScatter, 11U) + RotL64(aOrbiterJ, 57U)) + aOrbiterK);
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 23U) + aOrbiterI) + RotL64(aOrbiterA, 11U)) + RotL64(pNonce, 39U));
            aWandererE = aWandererE + ((((RotL64(aCross, 43U) + aOrbiterA) + RotL64(aOrbiterK, 38U)) + RotL64(aCarry, 27U)) + aWandererUpdateSaltC[((aIndex + 6482U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererI, 14U));
            aCarry = aCarry + (RotL64(aWandererK, 23U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererE, 5U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteD, 3U) ^ RotL64(aNonceByteG, 19U));
            aIngress = aIngress ^ (RotL64(aWorkLaneB[((aIndex + 7648U)) & S_BLOCK1], 48U) ^ RotL64(aWorkLaneA[((aIndex + 28951U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteH, 57U) ^ RotL64(aNonceByteF, 29U));
            aCross = aCross ^ (RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 7304U)) & S_BLOCK1], 3U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 31515U)) & S_BLOCK1], 46U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 3U) + RotL64(aCross, 41U)) ^ (RotL64(aPrevious, 28U) + RotL64(aCarry, 53U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterC = (((aWandererC + RotL64(aPrevious, 21U)) + RotL64(aCarry, 57U)) + 17264605017518259932U) + RotL64(aNonceByteA, 29U);
            aOrbiterE = (aWandererJ + RotL64(aIngress, 11U)) + 15209184354580778643U;
            aOrbiterB = ((aWandererG + RotL64(aScatter, 34U)) + RotL64(aCarry, 11U)) + 3299527965014731384U;
            aOrbiterI = (((aWandererK + RotL64(aCross, 3U)) + RotL64(aCarry, 35U)) + 16293096431816127821U) + aOrbiterAssignSaltE[((aIndex + 2704U)) & S_SALT1];
            aOrbiterD = (((aWandererI + RotL64(aScatter, 47U)) + 11031983436878828337U) + aOrbiterAssignSaltA[(((31U - aIndex) + 7096U)) & S_SALT1]) + RotL64(aNonceByteE, 61U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterE) + 9188018632448236358U) + RotL64(aNonceByteF, 52U);
            aOrbiterB = ((aOrbiterB ^ aOrbiterC) ^ 13420816400363406556U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 4874U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 10958221259662190519U), 43U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 2485063384097917101U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 3089135816938128264U;
            aOrbiterE = RotL64((aOrbiterE * 8813152992957361153U), 29U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 10730544971770435788U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 10431767565618874806U;
            aOrbiterC = RotL64((aOrbiterC * 4723078464590561545U), 21U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 14883796491656899074U) + aOrbiterUpdateSaltD[((aIndex + 6551U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterB) ^ 13465877783538483706U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 1110U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 14311686051108108503U), 51U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 13322163435314643713U) + RotL64(aNonceByteC, 59U);
            aOrbiterD = ((aOrbiterD ^ aOrbiterE) ^ 3307316600284371955U) ^ aOrbiterUpdateSaltE[((aIndex + 2069U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 12337846092069506365U), 11U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterC, 47U);
            aIngress = aIngress + (RotL64(aOrbiterI, 60U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterD, 37U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK + ((((RotL64(aIngress, 13U) + RotL64(aOrbiterE, 57U)) + aOrbiterC) + RotL64(aCarry, 29U)) + RotL64(aNonceByteG, 47U));
            aWandererI = aWandererI ^ ((((RotL64(aScatter, 36U) + aOrbiterE) + RotL64(aOrbiterB, 6U)) + RotL64(aNonceByteB, 31U)) + aWandererUpdateSaltB[(((31U - aIndex) + 2451U)) & S_SALT1]);
            aWandererJ = aWandererJ + (((RotL64(aCross, 5U) + aOrbiterB) + RotL64(aOrbiterI, 39U)) + RotL64(aCarry, 41U));
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 57U) + aOrbiterD) + RotL64(aOrbiterB, 19U));
            aWandererC = aWandererC + (((RotL64(aIngress, 47U) + aOrbiterI) + RotL64(aOrbiterC, 47U)) + aWandererUpdateSaltA[(((31U - aIndex) + 3151U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererJ, 21U));
            aCarry = aCarry + (RotL64(aWandererI, 29U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererK, 13U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteC, 46U) ^ RotL64(aNonceByteE, 3U)) ^ RotL64(aNonceByteA, 21U));
            aIngress = aIngress ^ (RotL64(aWorkLaneC[((aIndex + 233U)) & S_BLOCK1], 11U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 18377U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteF, 41U) ^ RotL64(aNonceByteG, 4U));
            aCross = aCross ^ (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 24190U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 10934U)) & S_BLOCK1], 23U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 57U) + RotL64(aPrevious, 41U)) + (RotL64(aCross, 5U) ^ RotL64(aIngress, 20U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = (((aWandererA + RotL64(aScatter, 47U)) + RotL64(aCarry, 11U)) + 10336802574069791273U) + RotL64(aNonceByteG, 43U);
            aOrbiterJ = (((aWandererH + RotL64(aCross, 3U)) + RotL64(aCarry, 37U)) + 169025388197058936U) + aOrbiterAssignSaltD[((aIndex + 89U)) & S_SALT1];
            aOrbiterI = (((aWandererE + RotL64(aPrevious, 57U)) + RotL64(aCarry, 51U)) + 6541354188379168846U) + aOrbiterAssignSaltC[((aIndex + 1455U)) & S_SALT1];
            aOrbiterD = ((aWandererI + RotL64(aIngress, 38U)) + 16223920526599306104U) + RotL64(aNonceByteB, 47U);
            aOrbiterE = (aWandererC + RotL64(aCross, 27U)) + 12756613707692514808U;
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 5082475548176484035U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterG) ^ 4907435526952698526U) ^ aOrbiterUpdateSaltA[((aIndex + 842U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 1379692095754989215U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 14236627073831834337U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterD) ^ 11502511046130497584U) ^ aOrbiterUpdateSaltE[((aIndex + 6947U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 3460330807286625917U), 19U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 3679044835550219497U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 11254838916686736746U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 5523U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 8631695922983532915U), 53U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 10582608424233200966U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterE) ^ 10449735026385340313U) ^ RotL64(aNonceByteE, 19U);
            aOrbiterJ = RotL64((aOrbiterJ * 7363770199734997411U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 4628253464169957835U;
            aOrbiterE = (((aOrbiterE ^ aOrbiterI) ^ 17664454668473204465U) ^ aOrbiterUpdateSaltD[((aIndex + 5193U)) & S_SALT1]) ^ RotL64(aNonceByteF, 12U);
            aOrbiterE = RotL64((aOrbiterE * 4234720298731378527U), 43U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterI, 14U);
            aIngress = aIngress + (RotL64(aOrbiterE, 27U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterJ, 41U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ (((RotL64(aPrevious, 13U) + aOrbiterD) + RotL64(aOrbiterG, 41U)) + aWandererUpdateSaltE[((aIndex + 7349U)) & S_SALT1]);
            aWandererE = aWandererE + (((RotL64(aScatter, 5U) + RotL64(aOrbiterI, 3U)) + aOrbiterD) + RotL64(aCarry, 13U));
            aWandererH = aWandererH ^ ((((RotL64(aCross, 35U) + RotL64(aOrbiterD, 27U)) + aOrbiterE) + RotL64(aNonceByteD, 55U)) + aWandererUpdateSaltF[(((31U - aIndex) + 1242U)) & S_SALT1]);
            aWandererA = aWandererA + ((((RotL64(aIngress, 24U) + aOrbiterG) + RotL64(aOrbiterJ, 19U)) + RotL64(aCarry, 47U)) + RotL64(aNonceByteH, 25U));
            aWandererI = aWandererI ^ ((RotL64(aScatter, 43U) + RotL64(aOrbiterE, 54U)) + aOrbiterG);
            //
            aCarry = aCarry + (RotL64(aWandererA, 21U) ^ aWandererC);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererE, 5U));
            aCarry = aCarry + RotL64(aWandererI, 29U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
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
        aMatrixWriteIndex = 0U;
    
        for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
            aMatrixSlotA = aIndexList256A[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixSlotB = aIndexList256B[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixLoadIndexA = aMatrixSlotA * 128U;
            aMatrixLoadIndexB = (aMatrixSlotB * 128U) + 64U;
            aM88OperationIndex = aMatrixWriteIndex;
            aM88SourceIndex = aMatrixLoadIndexA;
            aM88DestinationIndex = aMatrixWriteIndex;
            aM88UnrollDomainWord = aDomainWordMatrixUnrollA;
            aM88ArgADomainWord = aDomainWordMatrixArgA;
            aM88ArgBDomainWord = aDomainWordMatrixArgB;
            aM88ArgCDomainWord = aDomainWordMatrixArgC;
            aM88ArgDDomainWord = aDomainWordMatrixArgD;
            mMatrix.Dispatch(aOperationLaneC, aM88OperationIndex, aWorkLaneA, aM88SourceIndex, aExpandLaneA, aM88DestinationIndex, static_cast<std::uint8_t>(aM88UnrollDomainWord), static_cast<std::uint8_t>(aM88ArgADomainWord), static_cast<std::uint8_t>(aM88ArgBDomainWord), static_cast<std::uint8_t>(aM88ArgCDomainWord), static_cast<std::uint8_t>(aM88ArgDDomainWord));
            aM88OperationIndex = aMatrixWriteIndex + 64U;
            aM88SourceIndex = aMatrixLoadIndexB;
            aM88DestinationIndex = aMatrixWriteIndex + 64U;
            aM88UnrollDomainWord = aDomainWordMatrixUnrollA;
            aM88ArgADomainWord = aDomainWordMatrixArgA;
            aM88ArgBDomainWord = aDomainWordMatrixArgB;
            aM88ArgCDomainWord = aDomainWordMatrixArgC;
            aM88ArgDDomainWord = aDomainWordMatrixArgD;
            mMatrix.Dispatch(aOperationLaneC, aM88OperationIndex, aWorkLaneB, aM88SourceIndex, aExpandLaneA, aM88DestinationIndex, static_cast<std::uint8_t>(aM88UnrollDomainWord), static_cast<std::uint8_t>(aM88ArgADomainWord), static_cast<std::uint8_t>(aM88ArgBDomainWord), static_cast<std::uint8_t>(aM88ArgCDomainWord), static_cast<std::uint8_t>(aM88ArgDDomainWord));
            aMatrixWriteIndex = aMatrixWriteIndex + 128U;
        }
    
        aMatrixWriteIndex = 0U;
    
        for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
            aMatrixSlotA = aIndexList256C[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixSlotB = aIndexList256D[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixLoadIndexA = (aMatrixSlotA * 128U) + 64U;
            aMatrixLoadIndexB = aMatrixSlotB * 128U;
            aM88OperationIndex = aMatrixWriteIndex + 64U;
            aM88SourceIndex = aMatrixLoadIndexA;
            aM88DestinationIndex = aMatrixWriteIndex + 64U;
            aM88UnrollDomainWord = aDomainWordMatrixUnrollB;
            aM88ArgADomainWord = aDomainWordMatrixArgA;
            aM88ArgBDomainWord = aDomainWordMatrixArgB;
            aM88ArgCDomainWord = aDomainWordMatrixArgC;
            aM88ArgDDomainWord = aDomainWordMatrixArgD;
            mMatrix.Dispatch(aOperationLaneD, aM88OperationIndex, aWorkLaneA, aM88SourceIndex, aExpandLaneB, aM88DestinationIndex, static_cast<std::uint8_t>(aM88UnrollDomainWord), static_cast<std::uint8_t>(aM88ArgADomainWord), static_cast<std::uint8_t>(aM88ArgBDomainWord), static_cast<std::uint8_t>(aM88ArgCDomainWord), static_cast<std::uint8_t>(aM88ArgDDomainWord));
            aM88OperationIndex = aMatrixWriteIndex;
            aM88SourceIndex = aMatrixLoadIndexB;
            aM88DestinationIndex = aMatrixWriteIndex;
            aM88UnrollDomainWord = aDomainWordMatrixUnrollB;
            aM88ArgADomainWord = aDomainWordMatrixArgA;
            aM88ArgBDomainWord = aDomainWordMatrixArgB;
            aM88ArgCDomainWord = aDomainWordMatrixArgC;
            aM88ArgDDomainWord = aDomainWordMatrixArgD;
            mMatrix.Dispatch(aOperationLaneD, aM88OperationIndex, aWorkLaneB, aM88SourceIndex, aExpandLaneB, aM88DestinationIndex, static_cast<std::uint8_t>(aM88UnrollDomainWord), static_cast<std::uint8_t>(aM88ArgADomainWord), static_cast<std::uint8_t>(aM88ArgBDomainWord), static_cast<std::uint8_t>(aM88ArgCDomainWord), static_cast<std::uint8_t>(aM88ArgDDomainWord));
            aMatrixWriteIndex = aMatrixWriteIndex + 128U;
        }
    }
    {
        // kdf-a-matrix-diffusion: yeah
    
        TwistIndexShuffle::ExecuteA(aIndexList256A, aOperationLaneC);
        TwistIndexShuffle::ExecuteA(aIndexList256B, aOperationLaneD);
        TwistIndexShuffle::ExecuteB(aIndexList256C, aOperationLaneC);
        TwistIndexShuffle::ExecuteB(aIndexList256D, aOperationLaneD);
        aMatrixWriteIndex = 0U;
    
        for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
            aMatrixSlotA = aIndexList256A[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixSlotB = aIndexList256B[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixLoadIndexA = aMatrixSlotA * 128U;
            aMatrixLoadIndexB = (aMatrixSlotB * 128U) + 64U;
            aM88OperationIndex = aMatrixWriteIndex;
            aM88SourceIndex = aMatrixLoadIndexA;
            aM88DestinationIndex = aMatrixWriteIndex;
            aM88UnrollDomainWord = aDomainWordMatrixUnrollA;
            aM88ArgADomainWord = aDomainWordMatrixArgA;
            aM88ArgBDomainWord = aDomainWordMatrixArgB;
            aM88ArgCDomainWord = aDomainWordMatrixArgC;
            aM88ArgDDomainWord = aDomainWordMatrixArgD;
            mMatrix.Dispatch(aOperationLaneA, aM88OperationIndex, aWorkLaneC, aM88SourceIndex, aExpandLaneC, aM88DestinationIndex, static_cast<std::uint8_t>(aM88UnrollDomainWord), static_cast<std::uint8_t>(aM88ArgADomainWord), static_cast<std::uint8_t>(aM88ArgBDomainWord), static_cast<std::uint8_t>(aM88ArgCDomainWord), static_cast<std::uint8_t>(aM88ArgDDomainWord));
            aM88OperationIndex = aMatrixWriteIndex + 64U;
            aM88SourceIndex = aMatrixLoadIndexB;
            aM88DestinationIndex = aMatrixWriteIndex + 64U;
            aM88UnrollDomainWord = aDomainWordMatrixUnrollA;
            aM88ArgADomainWord = aDomainWordMatrixArgA;
            aM88ArgBDomainWord = aDomainWordMatrixArgB;
            aM88ArgCDomainWord = aDomainWordMatrixArgC;
            aM88ArgDDomainWord = aDomainWordMatrixArgD;
            mMatrix.Dispatch(aOperationLaneA, aM88OperationIndex, aWorkLaneD, aM88SourceIndex, aExpandLaneC, aM88DestinationIndex, static_cast<std::uint8_t>(aM88UnrollDomainWord), static_cast<std::uint8_t>(aM88ArgADomainWord), static_cast<std::uint8_t>(aM88ArgBDomainWord), static_cast<std::uint8_t>(aM88ArgCDomainWord), static_cast<std::uint8_t>(aM88ArgDDomainWord));
            aMatrixWriteIndex = aMatrixWriteIndex + 128U;
        }
    
        aMatrixWriteIndex = 0U;
    
        for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
            aMatrixSlotA = aIndexList256C[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixSlotB = aIndexList256D[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixLoadIndexA = (aMatrixSlotA * 128U) + 64U;
            aMatrixLoadIndexB = aMatrixSlotB * 128U;
            aM88OperationIndex = aMatrixWriteIndex + 64U;
            aM88SourceIndex = aMatrixLoadIndexA;
            aM88DestinationIndex = aMatrixWriteIndex + 64U;
            aM88UnrollDomainWord = aDomainWordMatrixUnrollB;
            aM88ArgADomainWord = aDomainWordMatrixArgA;
            aM88ArgBDomainWord = aDomainWordMatrixArgB;
            aM88ArgCDomainWord = aDomainWordMatrixArgC;
            aM88ArgDDomainWord = aDomainWordMatrixArgD;
            mMatrix.Dispatch(aOperationLaneB, aM88OperationIndex, aWorkLaneC, aM88SourceIndex, aExpandLaneD, aM88DestinationIndex, static_cast<std::uint8_t>(aM88UnrollDomainWord), static_cast<std::uint8_t>(aM88ArgADomainWord), static_cast<std::uint8_t>(aM88ArgBDomainWord), static_cast<std::uint8_t>(aM88ArgCDomainWord), static_cast<std::uint8_t>(aM88ArgDDomainWord));
            aM88OperationIndex = aMatrixWriteIndex;
            aM88SourceIndex = aMatrixLoadIndexB;
            aM88DestinationIndex = aMatrixWriteIndex;
            aM88UnrollDomainWord = aDomainWordMatrixUnrollB;
            aM88ArgADomainWord = aDomainWordMatrixArgA;
            aM88ArgBDomainWord = aDomainWordMatrixArgB;
            aM88ArgCDomainWord = aDomainWordMatrixArgC;
            aM88ArgDDomainWord = aDomainWordMatrixArgD;
            mMatrix.Dispatch(aOperationLaneB, aM88OperationIndex, aWorkLaneD, aM88SourceIndex, aExpandLaneD, aM88DestinationIndex, static_cast<std::uint8_t>(aM88UnrollDomainWord), static_cast<std::uint8_t>(aM88ArgADomainWord), static_cast<std::uint8_t>(aM88ArgBDomainWord), static_cast<std::uint8_t>(aM88ArgCDomainWord), static_cast<std::uint8_t>(aM88ArgDDomainWord));
            aMatrixWriteIndex = aMatrixWriteIndex + 128U;
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
        aPrevious = 14865025809119351572U;
        aCarry = 11158548548640758608U;
        aWandererA = 10385098904369782641U;
        aWandererB = 15327694943411208467U;
        aWandererC = 14217921676383984484U;
        aWandererD = 14021468141095905224U;
        aWandererE = 11751029781684748998U;
        aWandererF = 17937515337285897925U;
        aWandererG = 9855037686832007245U;
        aWandererH = 14023503713078542016U;
        aWandererI = 12589490664951024134U;
        aWandererJ = 13682281613260393247U;
        aWandererK = 10372941121241627130U;
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteH, 22U) ^ RotL64(aNonceByteF, 57U)) ^ RotL64(aNonceByteE, 35U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 674U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneC[((aIndex + 9727U)) & S_BLOCK1], 47U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteB, 43U) ^ RotL64(aNonceByteG, 5U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 6311U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 23872U)) & S_BLOCK1], 52U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 5U) + RotL64(aCarry, 37U)) ^ (RotL64(aCross, 20U) + RotL64(aPrevious, 53U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = (((aWandererE + RotL64(aPrevious, 57U)) + RotL64(aCarry, 23U)) + 17264605017518259932U) + aOrbiterAssignSaltA[((aIndex + 2357U)) & S_SALT1];
            aOrbiterA = ((aWandererH + RotL64(aIngress, 19U)) + RotL64(aCarry, 5U)) + 15209184354580778643U;
            aOrbiterH = ((aWandererA + RotL64(aCross, 35U)) + 3299527965014731384U) + RotL64(aNonceByteE, 49U);
            aOrbiterC = (((aWandererK + RotL64(aScatter, 4U)) + RotL64(aCarry, 53U)) + 16293096431816127821U) + aOrbiterAssignSaltC[(((31U - aIndex) + 3364U)) & S_SALT1];
            aOrbiterJ = ((aWandererG + RotL64(aIngress, 47U)) + 11031983436878828337U) + RotL64(aNonceByteG, 27U);
            //
            aOrbiterF = (((aOrbiterF + aOrbiterA) + 9188018632448236358U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 5585U)) & S_SALT1]) + RotL64(aNonceByteA, 17U);
            aOrbiterH = (((aOrbiterH ^ aOrbiterF) ^ 13420816400363406556U) ^ aOrbiterUpdateSaltD[((aIndex + 3131U)) & S_SALT1]) ^ RotL64(aNonceByteC, 8U);
            aOrbiterH = RotL64((aOrbiterH * 10958221259662190519U), 43U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterJ) + 2485063384097917101U) + aOrbiterUpdateSaltC[((aIndex + 1867U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 3089135816938128264U;
            aOrbiterF = RotL64((aOrbiterF * 8813152992957361153U), 27U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 10730544971770435788U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 10431767565618874806U;
            aOrbiterC = RotL64((aOrbiterC * 4723078464590561545U), 51U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 14883796491656899074U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 13465877783538483706U;
            aOrbiterA = RotL64((aOrbiterA * 14311686051108108503U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 13322163435314643713U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterH) ^ 3307316600284371955U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 3692U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 12337846092069506365U), 3U);
            //
            aIngress = RotL64(aOrbiterH, 13U) ^ aOrbiterF;
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterA, 37U));
            aIngress = aIngress + RotL64(aOrbiterJ, 24U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((((RotL64(aIngress, 5U) + aOrbiterJ) + RotL64(aOrbiterH, 58U)) + RotL64(aCarry, 47U)) + RotL64(aNonceByteH, 13U));
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 58U) + aOrbiterF) + RotL64(aOrbiterH, 35U)) + RotL64(aNonceByteD, 55U));
            aWandererK = aWandererK + ((RotL64(aScatter, 29U) + aOrbiterA) + RotL64(aOrbiterC, 27U));
            aWandererG = aWandererG ^ (((RotL64(aCross, 13U) + aOrbiterH) + RotL64(aOrbiterA, 43U)) + aWandererUpdateSaltB[(((31U - aIndex) + 3400U)) & S_SALT1]);
            aWandererH = aWandererH + ((((RotL64(aPrevious, 43U) + RotL64(aOrbiterJ, 5U)) + aOrbiterA) + RotL64(aCarry, 23U)) + aWandererUpdateSaltE[(((31U - aIndex) + 6803U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererG, 11U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererE, 46U));
            aCarry = aCarry + RotL64(aWandererK, 19U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteG, 41U) ^ RotL64(aNonceByteH, 21U));
            aIngress = aIngress ^ (RotL64(aWorkLaneA[((aIndex + 8779U)) & S_BLOCK1], 56U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 18379U)) & S_BLOCK1], 13U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 28U) ^ RotL64(aNonceByteB, 53U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 10388U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneB[((aIndex + 9458U)) & S_BLOCK1], 41U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 5U) + RotL64(aCross, 54U)) ^ (RotL64(aCarry, 35U) + RotL64(aIngress, 19U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = ((aWandererC + RotL64(aIngress, 29U)) + 11274974230580265396U) + aOrbiterAssignSaltD[(((31U - aIndex) + 2310U)) & S_SALT1];
            aOrbiterJ = ((aWandererD + RotL64(aPrevious, 6U)) + RotL64(aCarry, 11U)) + 16658438747342741547U;
            aOrbiterA = ((aWandererA + RotL64(aScatter, 57U)) + 16612986966106053844U) + RotL64(aNonceByteD, 9U);
            aOrbiterD = (((aWandererJ + RotL64(aCross, 19U)) + RotL64(aCarry, 57U)) + 9329502236843231290U) + aOrbiterAssignSaltE[((aIndex + 3341U)) & S_SALT1];
            aOrbiterK = (((aWandererE + RotL64(aIngress, 37U)) + RotL64(aCarry, 29U)) + 14088261356708344656U) + RotL64(aNonceByteB, 53U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterJ) + 13692608802007789581U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 507U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 6824473946645682398U) ^ aOrbiterUpdateSaltD[((aIndex + 6615U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 13619437545775237601U), 51U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterD) + 2072915876348570040U) + RotL64(aNonceByteA, 3U);
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 7420507753044460759U;
            aOrbiterK = RotL64((aOrbiterK * 13239288539564571257U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 4677557318688502593U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 15081678577055628459U;
            aOrbiterH = RotL64((aOrbiterH * 16659305295251177155U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 7026792817486507482U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 14871665922943969918U;
            aOrbiterJ = RotL64((aOrbiterJ * 694073180313083145U), 5U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterH) + 6807734532159292872U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 3133U)) & S_SALT1];
            aOrbiterD = (((aOrbiterD ^ aOrbiterK) ^ 17882797335141303280U) ^ aOrbiterUpdateSaltE[((aIndex + 4779U)) & S_SALT1]) ^ RotL64(aNonceByteG, 18U);
            aOrbiterD = RotL64((aOrbiterD * 15439872930381050291U), 21U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterA, 3U);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterJ, 13U));
            aIngress = aIngress + RotL64(aOrbiterH, 28U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aScatter, 35U) + aOrbiterD) + RotL64(aOrbiterJ, 5U));
            aWandererC = aWandererC ^ ((((RotL64(aCross, 13U) + aOrbiterA) + RotL64(aOrbiterK, 57U)) + RotL64(aNonceByteE, 37U)) + aWandererUpdateSaltA[(((31U - aIndex) + 7760U)) & S_SALT1]);
            aWandererD = aWandererD + ((((RotL64(aIngress, 44U) + aOrbiterD) + RotL64(aOrbiterH, 37U)) + RotL64(aCarry, 43U)) + RotL64(aNonceByteF, 15U));
            aWandererE = aWandererE ^ (((RotL64(aPrevious, 3U) + RotL64(aOrbiterH, 13U)) + aOrbiterK) + aWandererUpdateSaltF[(((31U - aIndex) + 2986U)) & S_SALT1]);
            aWandererJ = aWandererJ + (((RotL64(aCross, 23U) + RotL64(aOrbiterA, 24U)) + aOrbiterD) + RotL64(aCarry, 19U));
            //
            aCarry = aCarry + (RotL64(aWandererA, 60U) ^ aWandererE);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererC, 47U));
            aCarry = aCarry + RotL64(aWandererJ, 5U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteE, 51U) ^ RotL64(aNonceByteA, 27U));
            aIngress = aIngress ^ (RotL64(aWorkLaneB[((aIndex + 18295U)) & S_BLOCK1], 4U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 23838U)) & S_BLOCK1], 37U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 37U) ^ RotL64(aNonceByteH, 11U));
            aCross = aCross ^ (RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 24114U)) & S_BLOCK1], 58U) ^ RotL64(aExpandLaneC[((aIndex + 11942U)) & S_BLOCK1], 21U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 20U) ^ RotL64(aCarry, 3U)) ^ (RotL64(aPrevious, 35U) + RotL64(aCross, 53U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = (((aWandererC + RotL64(aScatter, 46U)) + 10336802574069791273U) + aOrbiterAssignSaltB[((aIndex + 1581U)) & S_SALT1]) + RotL64(pNonce, 47U);
            aOrbiterC = ((aWandererK + RotL64(aIngress, 23U)) + RotL64(aCarry, 27U)) + 169025388197058936U;
            aOrbiterE = (((aWandererD + RotL64(aCross, 57U)) + RotL64(aCarry, 51U)) + 6541354188379168846U) + RotL64(aNonceByteF, 54U);
            aOrbiterB = ((aWandererG + RotL64(aPrevious, 3U)) + 16223920526599306104U) + aOrbiterAssignSaltF[(((31U - aIndex) + 6201U)) & S_SALT1];
            aOrbiterD = ((aWandererE + RotL64(aScatter, 13U)) + RotL64(aCarry, 13U)) + 12756613707692514808U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 5082475548176484035U;
            aOrbiterE = (aOrbiterE ^ aOrbiterF) ^ 4907435526952698526U;
            aOrbiterE = RotL64((aOrbiterE * 1379692095754989215U), 13U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterF) + 14236627073831834337U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 5307U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterB) ^ 11502511046130497584U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 2965U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 3460330807286625917U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 3679044835550219497U) + RotL64(aNonceByteG, 61U);
            aOrbiterF = ((aOrbiterF ^ aOrbiterD) ^ 11254838916686736746U) ^ RotL64(aNonceByteH, 41U);
            aOrbiterF = RotL64((aOrbiterF * 8631695922983532915U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 10582608424233200966U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 10449735026385340313U;
            aOrbiterB = RotL64((aOrbiterB * 7363770199734997411U), 35U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterE) + 4628253464169957835U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 4325U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterC) ^ 17664454668473204465U) ^ aOrbiterUpdateSaltA[((aIndex + 73U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 4234720298731378527U), 27U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterF, 19U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterB, 53U));
            aIngress = aIngress + RotL64(aOrbiterD, 6U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ ((RotL64(aCross, 13U) + aOrbiterC) + RotL64(aOrbiterF, 5U));
            aWandererC = aWandererC + ((((RotL64(aPrevious, 3U) + aOrbiterD) + RotL64(aOrbiterE, 27U)) + RotL64(aCarry, 39U)) + aWandererUpdateSaltC[((aIndex + 712U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((((RotL64(aScatter, 21U) + aOrbiterF) + RotL64(aOrbiterB, 18U)) + RotL64(aNonceByteC, 9U)) + aWandererUpdateSaltD[((aIndex + 3479U)) & S_SALT1]);
            aWandererD = aWandererD + ((((RotL64(aIngress, 52U) + RotL64(aOrbiterE, 37U)) + aOrbiterC) + RotL64(aCarry, 11U)) + RotL64(aNonceByteB, 45U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 39U) + RotL64(aOrbiterE, 53U)) + aOrbiterB);
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererG, 5U));
            aCarry = aCarry + (RotL64(aWandererE, 37U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererC, 27U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 57U) ^ RotL64(aNonceByteH, 11U)) ^ RotL64(aNonceByteC, 19U));
            aIngress = aIngress ^ (RotL64(aWorkLaneC[((aIndex + 20120U)) & S_BLOCK1], 29U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 7184U)) & S_BLOCK1], 38U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 27U) ^ RotL64(aNonceByteE, 38U)) ^ RotL64(aNonceByteF, 53U));
            aCross = aCross ^ (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 17964U)) & S_BLOCK1], 19U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 14778U)) & S_BLOCK1], 5U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 35U) + RotL64(aCarry, 20U)) + (RotL64(aPrevious, 5U) ^ RotL64(aCross, 53U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = ((aWandererH + RotL64(aCross, 43U)) + RotL64(aCarry, 21U)) + 5697928251815176134U;
            aOrbiterK = ((aWandererI + RotL64(aIngress, 3U)) + 337587740689259575U) + RotL64(aNonceByteB, 23U);
            aOrbiterF = ((((aWandererJ + RotL64(aScatter, 13U)) + RotL64(aCarry, 3U)) + 4927686903263973950U) + aOrbiterAssignSaltC[(((31U - aIndex) + 5525U)) & S_SALT1]) + RotL64(aNonceByteC, 45U);
            aOrbiterE = (((aWandererC + RotL64(aPrevious, 23U)) + RotL64(aCarry, 35U)) + 3742409032569801033U) + aOrbiterAssignSaltA[(((31U - aIndex) + 3215U)) & S_SALT1];
            aOrbiterI = (aWandererG + RotL64(aCross, 34U)) + 1608092659172197650U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 15848744267145717509U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterA) ^ 15300174177963339253U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 7611U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 5771922862677667319U), 5U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterI) + 14162868453323648628U) + aOrbiterUpdateSaltD[((aIndex + 4152U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 12020167069983729869U;
            aOrbiterA = RotL64((aOrbiterA * 2071080217680099017U), 13U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 16259538291658723956U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterK) ^ 8516686212464112245U) ^ RotL64(aNonceByteG, 13U);
            aOrbiterE = RotL64((aOrbiterE * 4731296903548893627U), 39U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterA) + 3722184575520553132U) + aOrbiterUpdateSaltE[((aIndex + 1508U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterI) ^ 5663609293306386784U) ^ RotL64(aNonceByteA, 61U);
            aOrbiterK = RotL64((aOrbiterK * 14364218128780764749U), 21U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterE) + 15265344442454471986U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 3493U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 3050323350098829515U;
            aOrbiterI = RotL64((aOrbiterI * 5890624677162388135U), 53U);
            //
            aIngress = RotL64(aOrbiterI, 3U) ^ aOrbiterE;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterA, 57U));
            aIngress = aIngress + RotL64(aOrbiterK, 14U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ (((RotL64(aIngress, 29U) + aOrbiterK) + RotL64(aOrbiterA, 46U)) + RotL64(aNonceByteH, 14U));
            aWandererC = aWandererC + ((((RotL64(aScatter, 43U) + RotL64(aOrbiterF, 21U)) + aOrbiterE) + RotL64(aCarry, 19U)) + RotL64(aNonceByteD, 43U));
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 19U) + RotL64(aOrbiterA, 57U)) + aOrbiterE) + aWandererUpdateSaltB[((aIndex + 7281U)) & S_SALT1]);
            aWandererJ = aWandererJ + ((((RotL64(aCross, 54U) + aOrbiterA) + RotL64(aOrbiterI, 3U)) + RotL64(aCarry, 3U)) + aWandererUpdateSaltE[((aIndex + 1782U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 5U) + RotL64(aOrbiterE, 29U)) + aOrbiterI);
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererJ, 3U));
            aCarry = aCarry + (RotL64(aWandererC, 53U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererH, 30U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteC, 38U) ^ RotL64(aNonceByteD, 53U));
            aIngress = aIngress ^ (RotL64(aWorkLaneD[((aIndex + 100U)) & S_BLOCK1], 11U) ^ RotL64(aWorkLaneC[((aIndex + 9245U)) & S_BLOCK1], 19U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteA, 3U) ^ RotL64(aNonceByteG, 21U)) ^ RotL64(aNonceByteF, 13U));
            aCross = aCross ^ (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 12464U)) & S_BLOCK1], 54U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 20460U)) & S_BLOCK1], 43U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 20U) ^ RotL64(aPrevious, 3U)) + (RotL64(aIngress, 53U) ^ RotL64(aCross, 41U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = (aWandererI + RotL64(aScatter, 56U)) + 12775735908960052604U;
            aOrbiterD = (((aWandererB + RotL64(aPrevious, 47U)) + RotL64(aCarry, 29U)) + 11791373812080296887U) + aOrbiterAssignSaltC[((aIndex + 403U)) & S_SALT1];
            aOrbiterK = ((((aWandererC + RotL64(aIngress, 39U)) + RotL64(aCarry, 11U)) + 5537362877706057303U) + aOrbiterAssignSaltE[(((31U - aIndex) + 6310U)) & S_SALT1]) + RotL64(aNonceByteF, 35U);
            aOrbiterF = ((aWandererJ + RotL64(aCross, 23U)) + RotL64(aCarry, 51U)) + 2023912048504189380U;
            aOrbiterH = ((aWandererA + RotL64(aPrevious, 5U)) + 17668828109963766893U) + RotL64(aNonceByteE, 34U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterD) + 558908629933941224U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 1571U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 1479633119685446888U;
            aOrbiterK = RotL64((aOrbiterK * 4447153373540811385U), 5U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 15460320397843364063U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 10059749397555469054U;
            aOrbiterA = RotL64((aOrbiterA * 8671817118586065469U), 29U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterK) + 9987633811929693924U) + aOrbiterUpdateSaltD[((aIndex + 3503U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 10087337844580228269U;
            aOrbiterF = RotL64((aOrbiterF * 13817142288940843815U), 19U);
            //
            aOrbiterH = (((aOrbiterH + aOrbiterA) + 4446204415503364254U) + aOrbiterUpdateSaltE[((aIndex + 6744U)) & S_SALT1]) + RotL64(aNonceByteG, 21U);
            aOrbiterD = ((aOrbiterD ^ aOrbiterH) ^ 15106063243302192717U) ^ RotL64(aNonceByteB, 39U);
            aOrbiterD = RotL64((aOrbiterD * 13273756657334709803U), 57U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 9430197906134676162U) + aOrbiterUpdateSaltF[((aIndex + 6405U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 1226048679997253363U;
            aOrbiterH = RotL64((aOrbiterH * 14247538885252664127U), 41U);
            //
            aIngress = RotL64(aOrbiterF, 3U) ^ aOrbiterD;
            aIngress = aIngress + (RotL64(aOrbiterK, 27U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterH, 54U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aCross, 58U) + aOrbiterK) + RotL64(aOrbiterA, 20U)) + RotL64(aCarry, 39U));
            aWandererC = aWandererC ^ ((RotL64(aIngress, 21U) + RotL64(aOrbiterD, 3U)) + aOrbiterH);
            aWandererJ = aWandererJ + (((((RotL64(aPrevious, 3U) + RotL64(aOrbiterF, 51U)) + aOrbiterD) + RotL64(aCarry, 57U)) + RotL64(aNonceByteH, 29U)) + aWandererUpdateSaltA[(((31U - aIndex) + 238U)) & S_SALT1]);
            aWandererB = aWandererB ^ (((RotL64(aScatter, 41U) + RotL64(aOrbiterK, 11U)) + aOrbiterH) + aWandererUpdateSaltD[((aIndex + 8157U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aPrevious, 29U) + RotL64(aOrbiterH, 35U)) + aOrbiterA) + RotL64(aNonceByteC, 51U));
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererI, 43U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererA, 51U));
            aCarry = aCarry + RotL64(aWandererB, 28U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteB, 27U) ^ RotL64(aNonceByteC, 56U)) ^ RotL64(aNonceByteG, 11U));
            aIngress = aIngress ^ (RotL64(aOperationLaneA[((aIndex + 26232U)) & S_BLOCK1], 35U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 13949U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteF, 3U) ^ RotL64(aNonceByteH, 43U)) ^ RotL64(aNonceByteE, 11U));
            aCross = aCross ^ (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 19562U)) & S_BLOCK1], 20U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 31179U)) & S_BLOCK1], 51U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 41U) + RotL64(aIngress, 11U)) ^ (RotL64(aCross, 58U) ^ RotL64(aPrevious, 23U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = ((aWandererB + RotL64(aScatter, 24U)) + RotL64(aCarry, 21U)) + 5697928251815176134U;
            aOrbiterJ = ((((aWandererK + RotL64(aCross, 13U)) + RotL64(aCarry, 37U)) + 337587740689259575U) + aOrbiterAssignSaltB[(((31U - aIndex) + 747U)) & S_SALT1]) + RotL64(aNonceByteA, 7U);
            aOrbiterH = (aWandererH + RotL64(aIngress, 35U)) + 4927686903263973950U;
            aOrbiterE = ((aWandererF + RotL64(aPrevious, 51U)) + 3742409032569801033U) + RotL64(pNonce, 46U);
            aOrbiterI = (((aWandererD + RotL64(aIngress, 5U)) + RotL64(aCarry, 53U)) + 1608092659172197650U) + aOrbiterAssignSaltD[(((31U - aIndex) + 596U)) & S_SALT1];
            //
            aOrbiterG = ((aOrbiterG + aOrbiterJ) + 15848744267145717509U) + aOrbiterUpdateSaltA[((aIndex + 3697U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 15300174177963339253U;
            aOrbiterH = RotL64((aOrbiterH * 5771922862677667319U), 41U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 14162868453323648628U) + RotL64(aNonceByteD, 11U);
            aOrbiterI = ((aOrbiterI ^ aOrbiterJ) ^ 12020167069983729869U) ^ aOrbiterUpdateSaltF[((aIndex + 838U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 2071080217680099017U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 16259538291658723956U;
            aOrbiterG = (((aOrbiterG ^ aOrbiterE) ^ 8516686212464112245U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 5883U)) & S_SALT1]) ^ RotL64(aNonceByteG, 45U);
            aOrbiterG = RotL64((aOrbiterG * 4731296903548893627U), 13U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 3722184575520553132U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterH) ^ 5663609293306386784U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 6739U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 14364218128780764749U), 51U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 15265344442454471986U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 3050323350098829515U;
            aOrbiterE = RotL64((aOrbiterE * 5890624677162388135U), 29U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterJ, 13U);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterE, 3U));
            aIngress = aIngress + RotL64(aOrbiterH, 57U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((((RotL64(aCross, 37U) + RotL64(aOrbiterI, 23U)) + aOrbiterH) + RotL64(aCarry, 19U)) + RotL64(aNonceByteH, 59U));
            aWandererK = aWandererK ^ (((RotL64(aScatter, 5U) + aOrbiterG) + RotL64(aOrbiterI, 13U)) + aWandererUpdateSaltF[((aIndex + 4277U)) & S_SALT1]);
            aWandererH = aWandererH + (((((RotL64(aIngress, 18U) + RotL64(aOrbiterJ, 56U)) + aOrbiterG) + RotL64(aCarry, 57U)) + RotL64(aNonceByteC, 17U)) + aWandererUpdateSaltB[(((31U - aIndex) + 4719U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aPrevious, 47U) + aOrbiterE) + RotL64(aOrbiterH, 37U));
            aWandererF = aWandererF + ((RotL64(aIngress, 29U) + aOrbiterJ) + RotL64(aOrbiterE, 5U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 54U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererH, 41U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererF, 21U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteC, 35U) ^ RotL64(aNonceByteA, 53U)) ^ RotL64(aNonceByteE, 21U));
            aIngress = aIngress ^ (RotL64(aOperationLaneB[((aIndex + 2488U)) & S_BLOCK1], 44U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 24045U)) & S_BLOCK1], 5U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 48U) ^ RotL64(aNonceByteH, 3U)) ^ RotL64(aNonceByteG, 57U));
            aCross = aCross ^ (RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 22854U)) & S_BLOCK1], 11U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 27018U)) & S_BLOCK1], 29U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 19U) + RotL64(aCross, 3U)) + (RotL64(aCarry, 51U) ^ RotL64(aPrevious, 36U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = (((aWandererD + RotL64(aPrevious, 18U)) + RotL64(aCarry, 29U)) + 3339283916456813609U) + RotL64(aNonceByteD, 51U);
            aOrbiterI = (((aWandererG + RotL64(aCross, 27U)) + RotL64(aCarry, 13U)) + 11339086426180649584U) + aOrbiterAssignSaltF[(((31U - aIndex) + 3048U)) & S_SALT1];
            aOrbiterF = ((aWandererI + RotL64(aIngress, 39U)) + 16819191669329316585U) + RotL64(aNonceByteE, 21U);
            aOrbiterC = (((aWandererH + RotL64(aScatter, 5U)) + RotL64(aCarry, 51U)) + 8361916937762630725U) + aOrbiterAssignSaltA[(((31U - aIndex) + 7318U)) & S_SALT1];
            aOrbiterJ = (aWandererF + RotL64(aIngress, 51U)) + 18031328374429899857U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 18261756894092897276U;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 4250319792907645666U;
            aOrbiterF = RotL64((aOrbiterF * 7053489184750217963U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 1492411503643460886U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterC) ^ 17369549067879344180U) ^ aOrbiterUpdateSaltD[((aIndex + 2956U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 2947354306696216579U), 29U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterC) + 7301713524358676722U) + aOrbiterUpdateSaltB[((aIndex + 4933U)) & S_SALT1]) + RotL64(aNonceByteG, 42U);
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 2985193736033012535U;
            aOrbiterA = RotL64((aOrbiterA * 7473297294949338265U), 13U);
            //
            aOrbiterF = (((aOrbiterF + aOrbiterJ) + 14086975808140927408U) + aOrbiterUpdateSaltA[((aIndex + 3031U)) & S_SALT1]) + RotL64(aNonceByteA, 23U);
            aOrbiterC = ((aOrbiterC ^ aOrbiterF) ^ 10390516547834639800U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 5661U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 11441293212275890819U), 39U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 18205555540941493267U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 16967799565443938873U;
            aOrbiterJ = RotL64((aOrbiterJ * 3009081009044782443U), 57U);
            //
            aIngress = RotL64(aOrbiterA, 29U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterF, 13U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterC, 3U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 43U) + aOrbiterI) + RotL64(aOrbiterA, 47U)) + RotL64(aNonceByteF, 11U));
            aWandererH = aWandererH + ((((RotL64(aScatter, 51U) + aOrbiterC) + RotL64(aOrbiterJ, 3U)) + RotL64(aCarry, 57U)) + aWandererUpdateSaltC[(((31U - aIndex) + 7635U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aCross, 34U) + aOrbiterC) + RotL64(aOrbiterF, 39U)) + RotL64(aNonceByteB, 27U));
            aWandererF = aWandererF + ((((RotL64(aIngress, 21U) + aOrbiterI) + RotL64(aOrbiterF, 28U)) + RotL64(aCarry, 29U)) + aWandererUpdateSaltE[((aIndex + 5129U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterA, 19U)) + aOrbiterC);
            //
            aCarry = aCarry + (RotL64(aWandererI, 60U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererF, 51U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererG, 5U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteB, 29U) ^ RotL64(aNonceByteC, 37U)) ^ RotL64(aNonceByteE, 10U));
            aIngress = aIngress ^ (RotL64(aOperationLaneC[((aIndex + 28597U)) & S_BLOCK1], 19U) ^ RotL64(aOperationLaneB[((aIndex + 11374U)) & S_BLOCK1], 53U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 13U) ^ RotL64(aNonceByteF, 56U)) ^ RotL64(aNonceByteH, 29U));
            aCross = aCross ^ (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 16563U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 17658U)) & S_BLOCK1], 41U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 11U) ^ RotL64(aCross, 57U)) ^ (RotL64(aCarry, 39U) + RotL64(aPrevious, 26U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = ((aWandererF + RotL64(aPrevious, 43U)) + RotL64(aCarry, 57U)) + 17264605017518259932U;
            aOrbiterF = (((aWandererC + RotL64(aIngress, 10U)) + 15209184354580778643U) + aOrbiterAssignSaltC[((aIndex + 4491U)) & S_SALT1]) + RotL64(aNonceByteA, 37U);
            aOrbiterI = (aWandererD + RotL64(aCross, 21U)) + 3299527965014731384U;
            aOrbiterK = (((aWandererB + RotL64(aScatter, 51U)) + RotL64(aCarry, 23U)) + 16293096431816127821U) + RotL64(aNonceByteF, 3U);
            aOrbiterD = (((aWandererI + RotL64(aIngress, 35U)) + RotL64(aCarry, 39U)) + 11031983436878828337U) + aOrbiterAssignSaltE[(((31U - aIndex) + 437U)) & S_SALT1];
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 9188018632448236358U) + RotL64(aNonceByteH, 16U);
            aOrbiterI = ((aOrbiterI ^ aOrbiterH) ^ 13420816400363406556U) ^ aOrbiterUpdateSaltC[((aIndex + 6471U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 10958221259662190519U), 29U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 2485063384097917101U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterK) ^ 3089135816938128264U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 2905U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 8813152992957361153U), 5U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 10730544971770435788U) + aOrbiterUpdateSaltE[((aIndex + 6353U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 10431767565618874806U;
            aOrbiterK = RotL64((aOrbiterK * 4723078464590561545U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterH) + 14883796491656899074U) + RotL64(aNonceByteG, 39U);
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 13465877783538483706U;
            aOrbiterF = RotL64((aOrbiterF * 14311686051108108503U), 21U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterK) + 13322163435314643713U) + aOrbiterUpdateSaltD[((aIndex + 6263U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 3307316600284371955U;
            aOrbiterD = RotL64((aOrbiterD * 12337846092069506365U), 41U);
            //
            aIngress = RotL64(aOrbiterH, 29U) ^ aOrbiterI;
            aIngress = aIngress + (RotL64(aOrbiterF, 54U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterK, 3U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererF = aWandererF ^ (((RotL64(aIngress, 43U) + RotL64(aOrbiterH, 57U)) + aOrbiterF) + RotL64(aNonceByteB, 19U));
            aWandererI = aWandererI + (((((RotL64(aPrevious, 27U) + aOrbiterD) + RotL64(aOrbiterH, 24U)) + RotL64(aCarry, 3U)) + RotL64(aNonceByteC, 51U)) + aWandererUpdateSaltD[(((31U - aIndex) + 3375U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 4U) + aOrbiterK) + RotL64(aOrbiterD, 43U));
            aWandererD = aWandererD + ((((RotL64(aCross, 35U) + RotL64(aOrbiterK, 5U)) + aOrbiterI) + RotL64(aCarry, 37U)) + aWandererUpdateSaltA[(((31U - aIndex) + 6296U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 51U) + aOrbiterK) + RotL64(aOrbiterH, 13U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 58U) ^ aWandererI);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererF, 47U));
            aCarry = aCarry + RotL64(aWandererC, 19U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteD, 39U) ^ RotL64(aNonceByteA, 21U));
            aIngress = aIngress ^ (RotL64(aOperationLaneD[((aIndex + 20387U)) & S_BLOCK1], 11U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 31267U)) & S_BLOCK1], 60U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteH, 39U) ^ RotL64(aNonceByteF, 6U));
            aCross = aCross ^ (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 30874U)) & S_BLOCK1], 29U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 13146U)) & S_BLOCK1], 53U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 13U) ^ RotL64(aCarry, 43U)) + (RotL64(aPrevious, 29U) ^ RotL64(aCross, 58U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterE = ((aWandererC + RotL64(aIngress, 11U)) + RotL64(aCarry, 57U)) + 10336802574069791273U;
            aOrbiterK = (((aWandererF + RotL64(aScatter, 51U)) + RotL64(aCarry, 5U)) + 169025388197058936U) + RotL64(aNonceByteF, 59U);
            aOrbiterF = (((aWandererJ + RotL64(aPrevious, 41U)) + 6541354188379168846U) + aOrbiterAssignSaltD[((aIndex + 5914U)) & S_SALT1]) + RotL64(aNonceByteC, 22U);
            aOrbiterH = ((aWandererI + RotL64(aCross, 3U)) + RotL64(aCarry, 19U)) + 16223920526599306104U;
            aOrbiterD = ((aWandererG + RotL64(aScatter, 28U)) + 12756613707692514808U) + aOrbiterAssignSaltF[(((31U - aIndex) + 1265U)) & S_SALT1];
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 5082475548176484035U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterE) ^ 4907435526952698526U) ^ aOrbiterUpdateSaltE[((aIndex + 5711U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 1379692095754989215U), 41U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 14236627073831834337U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 11502511046130497584U) ^ RotL64(aNonceByteG, 47U);
            aOrbiterE = RotL64((aOrbiterE * 3460330807286625917U), 51U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 3679044835550219497U) + RotL64(aNonceByteH, 3U);
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 11254838916686736746U;
            aOrbiterH = RotL64((aOrbiterH * 8631695922983532915U), 13U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterE) + 10582608424233200966U) + aOrbiterUpdateSaltB[((aIndex + 5228U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 10449735026385340313U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 2990U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 7363770199734997411U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 4628253464169957835U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 17664454668473204465U) ^ aOrbiterUpdateSaltD[((aIndex + 360U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 4234720298731378527U), 23U);
            //
            aIngress = RotL64(aOrbiterK, 47U) ^ aOrbiterD;
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterH, 57U));
            aIngress = aIngress + RotL64(aOrbiterF, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ ((RotL64(aIngress, 3U) + aOrbiterD) + RotL64(aOrbiterE, 37U));
            aWandererG = aWandererG + ((((RotL64(aCross, 24U) + aOrbiterE) + RotL64(aOrbiterH, 23U)) + RotL64(aCarry, 21U)) + aWandererUpdateSaltA[(((31U - aIndex) + 7890U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((((RotL64(aScatter, 43U) + RotL64(aOrbiterD, 3U)) + aOrbiterF) + RotL64(aNonceByteB, 39U)) + aWandererUpdateSaltC[(((31U - aIndex) + 6493U)) & S_SALT1]);
            aWandererF = aWandererF + ((((RotL64(aPrevious, 51U) + aOrbiterH) + RotL64(aOrbiterK, 11U)) + RotL64(aCarry, 5U)) + RotL64(aNonceByteE, 29U));
            aWandererI = aWandererI ^ ((RotL64(aIngress, 11U) + aOrbiterF) + RotL64(aOrbiterE, 48U));
            //
            aCarry = aCarry + (RotL64(aWandererF, 37U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererJ, 57U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererG, 46U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteG, 3U) ^ RotL64(aNonceByteD, 35U)) ^ RotL64(aNonceByteE, 21U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 21514U)) & S_BLOCK1], 51U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 12825U)) & S_BLOCK1], 12U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteA, 37U) ^ RotL64(aNonceByteH, 12U));
            aCross = aCross ^ (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 7106U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 9108U)) & S_BLOCK1], 21U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 23U) + RotL64(aIngress, 37U)) + (RotL64(aCarry, 5U) ^ RotL64(aPrevious, 54U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterI = ((((aWandererD + RotL64(aCross, 13U)) + RotL64(aCarry, 19U)) + 3339283916456813609U) + aOrbiterAssignSaltA[(((31U - aIndex) + 6684U)) & S_SALT1]) + RotL64(aNonceByteC, 27U);
            aOrbiterC = (aWandererH + RotL64(aPrevious, 5U)) + 11339086426180649584U;
            aOrbiterG = ((aWandererK + RotL64(aIngress, 37U)) + RotL64(aCarry, 35U)) + 16819191669329316585U;
            aOrbiterE = ((aWandererA + RotL64(aScatter, 58U)) + RotL64(aCarry, 5U)) + 8361916937762630725U;
            aOrbiterH = (((aWandererC + RotL64(aCross, 29U)) + 18031328374429899857U) + aOrbiterAssignSaltB[(((31U - aIndex) + 3543U)) & S_SALT1]) + RotL64(pNonce, 43U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterC) + 18261756894092897276U) + RotL64(aNonceByteE, 4U);
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 4250319792907645666U;
            aOrbiterG = RotL64((aOrbiterG * 7053489184750217963U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 1492411503643460886U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 17369549067879344180U;
            aOrbiterH = RotL64((aOrbiterH * 2947354306696216579U), 57U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterG) + 7301713524358676722U) + aOrbiterUpdateSaltB[((aIndex + 1737U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 2985193736033012535U;
            aOrbiterI = RotL64((aOrbiterI * 7473297294949338265U), 47U);
            //
            aOrbiterG = (((aOrbiterG + aOrbiterH) + 14086975808140927408U) + aOrbiterUpdateSaltA[((aIndex + 4699U)) & S_SALT1]) + RotL64(aNonceByteB, 19U);
            aOrbiterC = ((aOrbiterC ^ aOrbiterG) ^ 10390516547834639800U) ^ aOrbiterUpdateSaltF[((aIndex + 7033U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 11441293212275890819U), 27U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterI) + 18205555540941493267U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 139U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterH) ^ 16967799565443938873U;
            aOrbiterE = RotL64((aOrbiterE * 3009081009044782443U), 11U);
            //
            aIngress = RotL64(aOrbiterG, 35U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterH, 57U));
            aIngress = aIngress + RotL64(aOrbiterC, 46U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ (((RotL64(aCross, 29U) + RotL64(aOrbiterC, 56U)) + aOrbiterE) + aWandererUpdateSaltE[((aIndex + 4942U)) & S_SALT1]);
            aWandererH = aWandererH + ((((RotL64(aScatter, 37U) + aOrbiterH) + RotL64(aOrbiterG, 47U)) + RotL64(aCarry, 35U)) + RotL64(aNonceByteH, 13U));
            aWandererC = aWandererC ^ (((RotL64(aIngress, 47U) + aOrbiterI) + RotL64(aOrbiterE, 3U)) + aWandererUpdateSaltF[(((31U - aIndex) + 7226U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aPrevious, 3U) + aOrbiterH) + RotL64(aOrbiterI, 11U)) + RotL64(aCarry, 51U));
            aWandererA = aWandererA ^ (((RotL64(aIngress, 14U) + aOrbiterH) + RotL64(aOrbiterE, 19U)) + RotL64(aNonceByteF, 7U));
            //
            aCarry = aCarry + (RotL64(aWandererA, 3U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererD, 21U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererC, 47U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteB, 57U) ^ RotL64(aNonceByteF, 4U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 19479U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 29347U)) & S_BLOCK1], 23U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteA, 41U) ^ RotL64(aNonceByteD, 3U)) ^ RotL64(aNonceByteH, 51U));
            aCross = aCross ^ (RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 31038U)) & S_BLOCK1], 13U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 8961U)) & S_BLOCK1], 30U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 5U) + RotL64(aIngress, 19U)) + (RotL64(aPrevious, 52U) ^ RotL64(aCarry, 37U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = (((aWandererD + RotL64(aScatter, 13U)) + RotL64(aCarry, 19U)) + 12775735908960052604U) + RotL64(aNonceByteC, 3U);
            aOrbiterC = ((aWandererC + RotL64(aCross, 5U)) + 11791373812080296887U) + aOrbiterAssignSaltC[(((31U - aIndex) + 2643U)) & S_SALT1];
            aOrbiterI = ((aWandererJ + RotL64(aIngress, 21U)) + RotL64(aCarry, 51U)) + 5537362877706057303U;
            aOrbiterA = (((aWandererF + RotL64(aPrevious, 50U)) + RotL64(aCarry, 35U)) + 2023912048504189380U) + RotL64(aNonceByteG, 37U);
            aOrbiterK = ((aWandererG + RotL64(aScatter, 35U)) + 17668828109963766893U) + aOrbiterAssignSaltE[(((31U - aIndex) + 7110U)) & S_SALT1];
            //
            aOrbiterH = (((aOrbiterH + aOrbiterC) + 558908629933941224U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 5768U)) & S_SALT1]) + RotL64(aNonceByteD, 35U);
            aOrbiterI = ((aOrbiterI ^ aOrbiterH) ^ 1479633119685446888U) ^ aOrbiterUpdateSaltF[((aIndex + 2826U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 4447153373540811385U), 11U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 15460320397843364063U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 10059749397555469054U;
            aOrbiterC = RotL64((aOrbiterC * 8671817118586065469U), 3U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterA) + 9987633811929693924U) + aOrbiterUpdateSaltB[((aIndex + 1143U)) & S_SALT1];
            aOrbiterH = ((aOrbiterH ^ aOrbiterK) ^ 10087337844580228269U) ^ aOrbiterUpdateSaltE[((aIndex + 3544U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 13817142288940843815U), 21U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 4446204415503364254U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterI) ^ 15106063243302192717U) ^ RotL64(aNonceByteE, 22U);
            aOrbiterA = RotL64((aOrbiterA * 13273756657334709803U), 29U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 9430197906134676162U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 1226048679997253363U;
            aOrbiterK = RotL64((aOrbiterK * 14247538885252664127U), 41U);
            //
            aIngress = RotL64(aOrbiterI, 23U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterC, 11U));
            aIngress = aIngress + RotL64(aOrbiterH, 34U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ ((RotL64(aCross, 51U) + RotL64(aOrbiterC, 18U)) + aOrbiterI);
            aWandererG = aWandererG + (((((RotL64(aPrevious, 11U) + aOrbiterA) + RotL64(aOrbiterK, 57U)) + RotL64(aCarry, 3U)) + RotL64(aNonceByteF, 5U)) + aWandererUpdateSaltB[(((31U - aIndex) + 1486U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 37U) + aOrbiterA) + RotL64(aOrbiterI, 27U));
            aWandererC = aWandererC + ((((RotL64(aIngress, 60U) + RotL64(aOrbiterC, 3U)) + aOrbiterH) + RotL64(aCarry, 23U)) + aWandererUpdateSaltD[(((31U - aIndex) + 5489U)) & S_SALT1]);
            aWandererF = aWandererF ^ (((RotL64(aScatter, 23U) + RotL64(aOrbiterA, 35U)) + aOrbiterH) + RotL64(aNonceByteB, 61U));
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererD, 47U));
            aCarry = aCarry + (RotL64(aWandererJ, 37U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererC, 56U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteD, 56U) ^ RotL64(aNonceByteC, 13U)) ^ RotL64(aNonceByteA, 47U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 1350U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneB[((aIndex + 3986U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteB, 27U) ^ RotL64(aNonceByteG, 38U)) ^ RotL64(aNonceByteF, 53U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 29889U)) & S_BLOCK1], 11U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 4838U)) & S_BLOCK1], 19U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 36U) ^ RotL64(aPrevious, 21U)) + (RotL64(aCross, 53U) ^ RotL64(aIngress, 3U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = ((aWandererH + RotL64(aScatter, 56U)) + RotL64(aCarry, 27U)) + 11274974230580265396U;
            aOrbiterI = (((aWandererE + RotL64(aIngress, 13U)) + 16658438747342741547U) + aOrbiterAssignSaltD[((aIndex + 5955U)) & S_SALT1]) + RotL64(aNonceByteG, 29U);
            aOrbiterB = ((aWandererD + RotL64(aPrevious, 35U)) + 16612986966106053844U) + aOrbiterAssignSaltF[(((31U - aIndex) + 260U)) & S_SALT1];
            aOrbiterA = (((aWandererK + RotL64(aCross, 43U)) + RotL64(aCarry, 47U)) + 9329502236843231290U) + RotL64(aNonceByteB, 7U);
            aOrbiterH = ((aWandererB + RotL64(aPrevious, 3U)) + RotL64(aCarry, 5U)) + 14088261356708344656U;
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 13692608802007789581U) + aOrbiterUpdateSaltF[((aIndex + 7498U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 6824473946645682398U;
            aOrbiterB = RotL64((aOrbiterB * 13619437545775237601U), 53U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterH) + 2072915876348570040U) + aOrbiterUpdateSaltB[((aIndex + 5960U)) & S_SALT1]) + RotL64(aNonceByteC, 35U);
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 7420507753044460759U;
            aOrbiterF = RotL64((aOrbiterF * 13239288539564571257U), 41U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterB) + 4677557318688502593U) + aOrbiterUpdateSaltE[((aIndex + 2508U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 15081678577055628459U;
            aOrbiterA = RotL64((aOrbiterA * 16659305295251177155U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 7026792817486507482U;
            aOrbiterI = (((aOrbiterI ^ aOrbiterH) ^ 14871665922943969918U) ^ aOrbiterUpdateSaltD[((aIndex + 973U)) & S_SALT1]) ^ RotL64(aNonceByteD, 26U);
            aOrbiterI = RotL64((aOrbiterI * 694073180313083145U), 23U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 6807734532159292872U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 17882797335141303280U;
            aOrbiterH = RotL64((aOrbiterH * 15439872930381050291U), 3U);
            //
            aIngress = RotL64(aOrbiterH, 54U) ^ aOrbiterI;
            aIngress = aIngress + (RotL64(aOrbiterF, 3U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterA, 43U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH + ((RotL64(aScatter, 3U) + RotL64(aOrbiterH, 48U)) + aOrbiterA);
            aWandererD = aWandererD ^ ((((RotL64(aCross, 47U) + aOrbiterA) + RotL64(aOrbiterB, 3U)) + RotL64(aNonceByteH, 61U)) + aWandererUpdateSaltA[(((31U - aIndex) + 1031U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aPrevious, 39U) + RotL64(aOrbiterF, 21U)) + aOrbiterH) + RotL64(aCarry, 41U));
            aWandererB = aWandererB ^ (((RotL64(aIngress, 24U) + RotL64(aOrbiterF, 13U)) + aOrbiterI) + aWandererUpdateSaltC[(((31U - aIndex) + 6639U)) & S_SALT1]);
            aWandererE = aWandererE + ((((RotL64(aCross, 13U) + aOrbiterB) + RotL64(aOrbiterI, 39U)) + RotL64(aCarry, 19U)) + RotL64(aNonceByteE, 15U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 47U) ^ aWandererK);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererD, 11U));
            aCarry = aCarry + RotL64(aWandererE, 58U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
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
        // Making snow counter: sha 256
    
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
    
        // Making snow counter: aria 256
    
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
    
        // Making snow counter: aes 256
    
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
    
        // Making snow counter: cha cha 20
    
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
    }
    mSnow = aSnowLaneC;
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts));
    TwistInvest::InvestBlockMaskBoxA(aExpandLaneC, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxB(aExpandLaneA, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxB(aExpandLaneD, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxA(aExpandLaneB, pWorkSpace);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltA, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltC, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltE, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltA, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltC, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltE, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltA, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltC, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltE, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(mDomainBundleEphemeral.mPhaseAConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseAConstants), &(mDomainBundleEphemeral.mPhaseASalts));
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltC, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltE, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(pWorkSpace->mDomainBundle.mPhaseAConstants));
    mSnow = aSnowLaneD;
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts));
    TwistInvest::InvestBlockMaskBoxA(aExpandLaneC, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxB(aExpandLaneA, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxB(aExpandLaneD, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxA(aExpandLaneB, pWorkSpace);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltA, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltC, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltE, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltA, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltC, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltE, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltA, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltC, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltE, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(mDomainBundleEphemeral.mPhaseBConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseBConstants), &(mDomainBundleEphemeral.mPhaseBSalts));
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltE, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseBConstants));
    mSnow = aSnowLaneA;
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts));
    TwistInvest::InvestBlockMaskBoxA(aExpandLaneC, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxB(aExpandLaneA, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxB(aExpandLaneD, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxA(aExpandLaneB, pWorkSpace);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltA, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltC, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltE, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltA, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltC, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltE, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltA, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltC, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltE, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(mDomainBundleEphemeral.mPhaseCConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseCConstants), &(mDomainBundleEphemeral.mPhaseCSalts));
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltA, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltC, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltE, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(pWorkSpace->mDomainBundle.mPhaseCConstants));
    mSnow = aSnowLaneB;
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts));
    TwistInvest::InvestBlockMaskBoxA(aExpandLaneC, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxB(aExpandLaneA, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxB(aExpandLaneD, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxA(aExpandLaneB, pWorkSpace);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltA, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltC, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltE, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltA, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltC, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltE, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltA, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltC, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltE, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(mDomainBundleEphemeral.mPhaseDConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseDConstants), &(mDomainBundleEphemeral.mPhaseDSalts));
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltA, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltC, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltE, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseDConstants));
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
            0xD29099A3C844483CULL, 0xD2C227F02B945E01ULL, 0x1FED5801236A2023ULL, 0x17F4792E2D0A3FA5ULL, 
            0xFFB2CE123E64FC6DULL, 0x94E894AD74D0B725ULL, 0xAF8606DFE4E4FEF3ULL, 0xA4D14B9A6A8555ACULL, 
            0x04607CB331ECD300ULL, 0x9DE08ED55459AAF7ULL, 0xE6816BAE87A57603ULL, 0x3EDBC4108E70FBEEULL, 
            0x07D1975D96D576CCULL, 0x9C8E0D3ED2703813ULL, 0xC9B980AD7C970A42ULL, 0x2C7B296775AC0CB2ULL, 
            0xED9B46D6B663C49FULL, 0xEECEAA87954F4AE2ULL, 0x23FFE223B98A28EAULL, 0x2136A9406B933806ULL, 
            0xFE73D7B410CC9DA6ULL, 0x936930E8072ABEF8ULL, 0x927DC0B7F13E2E65ULL, 0xF37F20219F11056BULL, 
            0x7F409EF600CB59BCULL, 0x5447ADF971A23029ULL, 0x1CBB17FC7CE947B7ULL, 0x188B8700A5FD9F10ULL, 
            0x754EE906ACD2133AULL, 0x2454D8A0F7D88559ULL, 0xC5C243AFEF26CBFBULL, 0x458DE2D109DC9645ULL
        },
        {
            0x992BF41D64111075ULL, 0xD513E67CF33BB668ULL, 0xB5B864C930E580C2ULL, 0xDB612C41445A9A1FULL, 
            0xF309D9EE0BE726C2ULL, 0x6206615F99D3C798ULL, 0x5CBD4A0BF112AE7CULL, 0xC5B0DFF349F61C7AULL, 
            0x7EC0A3C92E3A71C1ULL, 0xD5DF9150674796DCULL, 0x607B488A26AE1302ULL, 0x99AF87463E4399D7ULL, 
            0x204CECA24B0FBB08ULL, 0xDD0DAF796453A1E6ULL, 0x79C22406DD643919ULL, 0x83A695DE9EEF0810ULL, 
            0x5EF972E455F9DEBBULL, 0xC9D07B5EC6B61C59ULL, 0xCDBD736B5D539914ULL, 0x50285A5BBCE05E54ULL, 
            0xB388BD72AD4F11DEULL, 0x47E9E489C38CE728ULL, 0xB40C9C8F0912EDFFULL, 0xE3013D0CE4791B9BULL, 
            0x44EC54619F92B978ULL, 0x6B56851D55931F9FULL, 0x0D77F3F9EC1B7A51ULL, 0x40CF9F126FACEF5AULL, 
            0x6C61D98CCE00A1B9ULL, 0xF037FFB89E8BEBD1ULL, 0x9DFC325D24601DDCULL, 0x31E6298BF4F342C9ULL
        },
        {
            0xE0B1D8B71AFDB8BDULL, 0xA65E29E8C73534C8ULL, 0xE71DACAE87B8A3DEULL, 0xC3DB064B7072D466ULL, 
            0x9696F9AA09C18BD7ULL, 0xB6989819D481102EULL, 0xFA8D4AE4D99EB23DULL, 0x8D20982C2D6F4F98ULL, 
            0xCC2C0ABE27689B57ULL, 0xF7B87C01632DEF75ULL, 0x9CB1911F5A558619ULL, 0xAEBB0EE96F9BCC41ULL, 
            0x963B1FD1A719F250ULL, 0x2CCB9701845E8974ULL, 0xFC1666AB949EB70EULL, 0x8112F3889BFE6EE2ULL, 
            0xBC66416594A78A71ULL, 0x39E24622496A6A28ULL, 0x1CCD9D96D8F532E2ULL, 0x2B9B8AB0BF7EEEAAULL, 
            0x071AD990DFE2E976ULL, 0x2D2A1731514C9ABEULL, 0x371582DC4ACA9EE4ULL, 0xE771178EE4D3A686ULL, 
            0x30E9B164ABC1D1BDULL, 0xC8DDBB713BE20D5BULL, 0x67B62BD58575C610ULL, 0x0C62976DFEE1FE8BULL, 
            0xA4B3BD63EC3312FCULL, 0x11AA5C2CAFDE4E97ULL, 0x074BC95DBE5903DCULL, 0xFC31F96B9270830DULL
        },
        {
            0xE7B1B7DF34C14302ULL, 0x904941DD7AE141B6ULL, 0xCA23EA98513BD495ULL, 0x66C0BFF0EE310859ULL, 
            0x1D1FE93443D48DC7ULL, 0x76784EC0F2D68502ULL, 0x08010DDB61CBE20DULL, 0x5BD6454FCD6164CCULL, 
            0xBB1E280C64A1C57CULL, 0x97FABBB4857B3660ULL, 0x8EA8BA184D769150ULL, 0x64EC2CA27295E94BULL, 
            0xC9B34AA655605819ULL, 0x9B012BBDEA73F158ULL, 0x7037B05EA2B63B53ULL, 0x3619D613F7043532ULL, 
            0x58723A60B51F3630ULL, 0xED0996E1FF59A4EEULL, 0x6393044AE7E02FC1ULL, 0x0E22DFBCDF42DAD3ULL, 
            0x1A91018BF90BDDE3ULL, 0xEFF1359130305BAEULL, 0x7B8DCF5E3B5BE2DFULL, 0x63C2C583055DB236ULL, 
            0xB36B04439220F6B2ULL, 0x6C5528DD80B5B7F5ULL, 0xB0516BEE13FB1340ULL, 0xE59C25FEE6FAB2B6ULL, 
            0x69EADAC7AA6AC707ULL, 0x1B9AA4F8F89342BDULL, 0xD813D3E35D2C2034ULL, 0x28B16DA5896FBB60ULL
        },
        {
            0x7A495C4F7B2749B1ULL, 0x0E0514E1EEC1CDF5ULL, 0x26984CEA2B149890ULL, 0x5C06A449DBCF5C78ULL, 
            0x9886DBF85F6EF8B6ULL, 0x45DD1368D3D88B2BULL, 0x440D71D5C73020C5ULL, 0x67640B638ABDBB26ULL, 
            0x03A543469DC6D8A9ULL, 0x7CDCA0E4061D1239ULL, 0x9BB9AB5DF7053A55ULL, 0xE959C2715A653723ULL, 
            0xC0B82ACB31651039ULL, 0xB581AB3ADC5B6551ULL, 0xA3415A331A14431BULL, 0x272F6D506CFBB2C2ULL, 
            0xCD231062D3CB83D7ULL, 0xCCEEDC6B7AEF79FBULL, 0xD53353E0231AE8CCULL, 0x9D93DE9CE53107C5ULL, 
            0x8617ED2FF1120EC5ULL, 0xA78333E28F92285FULL, 0x61793765D7D144E0ULL, 0xA29FD3D25A4A70E3ULL, 
            0xC6E2F3CE90AACC0FULL, 0xC1B1D0808E01937CULL, 0xDB8DE3F18260F2F5ULL, 0x4FF0866D1C725E88ULL, 
            0xF939195D77CBA184ULL, 0xF04921F8DE2475DCULL, 0x5CED5761B5D944EFULL, 0x1885E2BDB1F2FB6DULL
        },
        {
            0xD0FD4B92194D0992ULL, 0x3EF8232657FB2AC5ULL, 0x73AFF7D136F37E8CULL, 0x0AA44978EFDBB25BULL, 
            0xA3F46EA5C3021DAEULL, 0xD078532294638055ULL, 0xB77C481116952605ULL, 0x16A4AC7F751B988BULL, 
            0x1CF747D57536CA18ULL, 0x443C4010680147EDULL, 0x50FDE96ECC2CCCEBULL, 0xC53DB623069A6D47ULL, 
            0x180911548030C999ULL, 0x4923A68A04224569ULL, 0xD5F02147F65A7AF8ULL, 0x840935E0ECC10619ULL, 
            0x59AAF0E89DCD3621ULL, 0x501C437F76EF4AB4ULL, 0x8D668F10746A337DULL, 0x0113847161A68774ULL, 
            0x41A313740421695CULL, 0xEADBBE4E665E20AAULL, 0x323CC73DA8587A49ULL, 0x219AF365197214B1ULL, 
            0x441EDF93648CB632ULL, 0x5980F186434E03F5ULL, 0x1D02AF4EF3932D32ULL, 0xD774FE8FF3FC3074ULL, 
            0x5D588A697EF1B961ULL, 0xBBFDC2F20021A7D2ULL, 0x303BFABC7D1D88D3ULL, 0x86232FE87C7195A9ULL
        }
    },
    {
        {
            0xC534C5FBD7E16A6CULL, 0x4FE5BB2BF1FD527CULL, 0xC801F0A5038E47E1ULL, 0x1E87FE1D607A2152ULL, 
            0x4E93183121E2027EULL, 0xBF8C465B74ADF003ULL, 0xF35B4CE292D7154AULL, 0x81E92CA2E07F5319ULL, 
            0xE3DC1990E21B5116ULL, 0xED9787AA3517DE6AULL, 0xD608D04596C43CD9ULL, 0x6089EF22AA40CE22ULL, 
            0xEA2ED44BAE7C2934ULL, 0x6F6620AE717002F6ULL, 0x392FD8B994AE0767ULL, 0x947CBE7BD11C97CFULL, 
            0xE7D586608D136FDAULL, 0xAF2CEE3D61125AF5ULL, 0x7E806E05B6B547CEULL, 0xCC3F817B66114C91ULL, 
            0x1CD18179E7AA2915ULL, 0xB590D30B031F6E71ULL, 0x86427B1635ED553CULL, 0xD75F4C25F85B9AC7ULL, 
            0xD508E858B8547434ULL, 0x6265734CB7BFA955ULL, 0x347D7161DFB212E2ULL, 0x9E25F3BC9FAE5739ULL, 
            0x306F326ED5F7DFDFULL, 0xB55551191FD257A2ULL, 0x192AEC797F3FA155ULL, 0xBC34D3E994945AABULL
        },
        {
            0x3060CBE1178B1BA6ULL, 0x90EEF1DD57E6A9C2ULL, 0xEDB03E915A58A6A9ULL, 0x99E275A6F4DF01D5ULL, 
            0xD67C03A5D58F3BF9ULL, 0x9D046DA36A393FDEULL, 0x8580F4DD264B9B8EULL, 0xF10310AA82321471ULL, 
            0x7F9B9808378EBE20ULL, 0x1DC5994267326EF4ULL, 0x63DFD991D7161979ULL, 0x06B281D3EB7791CCULL, 
            0x0D9F951F0CBFCBEEULL, 0x61E15DCFC55CA5CEULL, 0xDDE4941EF0CB06A3ULL, 0x00D51D11A70AFA74ULL, 
            0x19940D37AFC6A521ULL, 0x451EAF3EB93AA829ULL, 0x231CD264CF56B2BDULL, 0x10CA2074174E83A0ULL, 
            0x18C5E79345209163ULL, 0x70DBD1318982C86DULL, 0xB416CB1BEE5FF59EULL, 0xCBA40FA4BB084F3FULL, 
            0x5A013CC79F07BE0AULL, 0x28034441141D7BE9ULL, 0xF599527C244AA493ULL, 0x60F2344F8E8208F7ULL, 
            0x4890EF8EF51C3420ULL, 0x63F3FF4EFD968033ULL, 0x3357687010AE22FBULL, 0x2B09B94577291293ULL
        },
        {
            0x5C07163ABBDBD0E0ULL, 0x38CFE6B584DF3927ULL, 0xBEFDA93DD0BB34E5ULL, 0x70FC177D0A26EDE8ULL, 
            0x25FF104A7679667AULL, 0x4574655C6574C678ULL, 0xA26F2D72A329FF7FULL, 0x5B69E4D2CB75020CULL, 
            0xFC1816F8F9558A00ULL, 0x6E369E90C83FCB7CULL, 0xCC12D51EE582D980ULL, 0xBDC0E52B6ABB6981ULL, 
            0x4C384FFD999BF42DULL, 0xED131E5C7076A1A2ULL, 0xE987C7D3FEAF519DULL, 0x08513CB2667F0E02ULL, 
            0x4E287449D19897B6ULL, 0x7F58F757E837398EULL, 0xAA51B8369A4469C3ULL, 0xDBBEDC95CE8758A0ULL, 
            0x5F0D6CE8B44E3FDCULL, 0x21CEC965E777E9D2ULL, 0xAA4BDD7AAE07526EULL, 0x3CF90484DF017E72ULL, 
            0x25354CB2C31C2CADULL, 0x5CD922357597D38DULL, 0x6AFAC7B09B562407ULL, 0xA72D448ED725CB72ULL, 
            0xEE0E3D7AD069A019ULL, 0x27384BC584917F94ULL, 0x3736684581391DE0ULL, 0x751E73B29E82CB7AULL
        },
        {
            0x7871F54F9A342092ULL, 0xCEA3B58C4A39D26BULL, 0xD35130B59F85BEE7ULL, 0xE9EDBF955CCAA984ULL, 
            0xC35010D001BF4E6CULL, 0xA04052E516C0FFBFULL, 0xA8DAE4DD03FACF59ULL, 0x1310DE3CC5794BF0ULL, 
            0xFD7C8497F1C95545ULL, 0x3A9206CBD9BAA7A9ULL, 0xE7847DA7AF9371C4ULL, 0x1C9F3BD1763F19B4ULL, 
            0x73EC6BA38197304AULL, 0xF10124B3EB4B0C8EULL, 0x8F073DBE05F444E5ULL, 0x009826E03A477FC5ULL, 
            0x76B65741FF4985F5ULL, 0x898951EF1FA24BBDULL, 0xC4569B1685258081ULL, 0xA3FA860E963B92BDULL, 
            0x4FB8454DDCA4F017ULL, 0x56B8E8D691BDDA6AULL, 0xC546982F120EC8D0ULL, 0x95E9C8B0F453E1E3ULL, 
            0x23A4777E2BCF1F4EULL, 0xA22D7F03CA8D378EULL, 0x0280058D88A0227AULL, 0xC75C17716151E0CAULL, 
            0x38D2A6B910153423ULL, 0xC5D6B92BE36263A8ULL, 0x2769E2E3BBD49123ULL, 0x0D84C2BD0B80A951ULL
        },
        {
            0xEC116ADA2FE0C2B5ULL, 0xCC64D8B603B78D9BULL, 0x8613BE9D5DF84B5AULL, 0x30CD3966C113DF1BULL, 
            0xB0CEB1DD5157755EULL, 0xEB4F0B231736177BULL, 0xC2681ED2FEB72D4BULL, 0xC45EAAD51613CEF6ULL, 
            0x7F7B8DC1ABC63E21ULL, 0xE4F17E0A98DA7CDBULL, 0xF7CBD34EAB3E982AULL, 0x40DAD344CCCADADDULL, 
            0x7631B0291142DE3CULL, 0xC9868EFDE1EFE2A3ULL, 0x0D312B0D88D03CDFULL, 0xE56B8F776878B209ULL, 
            0x1D257793D25A42AEULL, 0xCE4758EF69D1CF7AULL, 0x1DEED0D355EBEB25ULL, 0xD4C9847AEB69C94AULL, 
            0xCF3268D86208BB99ULL, 0x9BB89232D127FBB7ULL, 0x2859B64858DA324BULL, 0x99704F54215B4BCAULL, 
            0xC16F63CB9CAFB410ULL, 0x199881865B1302DCULL, 0x5530AEA7604E5CF1ULL, 0x550A71F1DFEE0794ULL, 
            0x4DF6117DC9728253ULL, 0xE7D51CEBCF9E7F51ULL, 0x19C2C63B56113D26ULL, 0x3B940685AAFE74C2ULL
        },
        {
            0xF222416D5F515DE3ULL, 0x46C61F25F52506D5ULL, 0x19F4B3760B237D01ULL, 0x7235D46565827D6AULL, 
            0xC67E0A43B7238A68ULL, 0x297DE44BEE44C0FAULL, 0xFC292419ACD25B20ULL, 0x73719C2117A2548AULL, 
            0x634CB42C204FD5B6ULL, 0x853494F4C5AC4469ULL, 0x98AB466D34554A70ULL, 0x7FCE317DE9E1E368ULL, 
            0x3CEE326122AA19BFULL, 0x57F022B75A337371ULL, 0xE7E023EA31E00BB8ULL, 0xB46D09A8914C8E5FULL, 
            0x34281ED5E63BF960ULL, 0xA0EA7E26C4A9BC86ULL, 0x3C8062AD53AD31B2ULL, 0x6BBC5BDFAE4335E1ULL, 
            0x6D8CA2099FD2E661ULL, 0xC6B95EF883320DB0ULL, 0x3FB6BBC6ED860ABDULL, 0x00809ECA8690D152ULL, 
            0x014F4BB285237E98ULL, 0x7D50F1031FB2B381ULL, 0xF0C0703355FFA8A9ULL, 0x1D8FADB2EB7F69F3ULL, 
            0x6F3D541840640466ULL, 0x7841DA06D1911618ULL, 0xF4884B5E01AF5BD5ULL, 0xFE2CC5B5863E8042ULL
        }
    },
    {
        {
            0x1A31C2933A509D96ULL, 0xCED8D7B384D02199ULL, 0x302B211C3342CBF0ULL, 0x78FC046E04778D7AULL, 
            0xC96F257495DE127EULL, 0xEECFD9B645F31E55ULL, 0x411572FE59F8D1BFULL, 0xDA1D784F49C356C2ULL, 
            0xD544E5AF5B7EE03CULL, 0x15423E8258C5AA63ULL, 0xC607E0C715570C24ULL, 0x159B301BEADE8CCAULL, 
            0xD3AF82FA56559785ULL, 0x44E1C47B791EBF15ULL, 0x5DADA24C206209F1ULL, 0x6ED8E6D5007BE4D6ULL, 
            0x415134EB22DE5E02ULL, 0xE6BC31E0C685C662ULL, 0x6851DE61783E2399ULL, 0xE3974C774DD7DD09ULL, 
            0xAAEF0AC63E9C256FULL, 0xD4DB5ADA0A6BAC14ULL, 0xF16878A6FFB5A6B1ULL, 0x7B68C0B9C3B609BDULL, 
            0xD2B6DC2460A6CD45ULL, 0xB9725E9A3BF8F283ULL, 0x09BA51783E11A55FULL, 0xBFF37C6FC374D7F9ULL, 
            0x685B47CE7ABA336BULL, 0x929121DD896D1C51ULL, 0x8CA169DB981160FEULL, 0x1A722BF06C951D88ULL
        },
        {
            0x8FB9407D31012BF9ULL, 0x9962C42C09F92EBDULL, 0x23BE290A105FE8D2ULL, 0x317A0D1BD413DC34ULL, 
            0x9DBA22378B264576ULL, 0x14DD256C641B40F7ULL, 0xC3A40DF4D95627CAULL, 0xE7B40A857CF96BA0ULL, 
            0x5221C4108CE0A0C0ULL, 0x0E8EE700285FFA78ULL, 0x9F8C167615FC1313ULL, 0x44EBD7496516B7FEULL, 
            0xFFD0327669D98500ULL, 0xD84AC35AE1320928ULL, 0x5CEC7873B61EA295ULL, 0xFC323A600A8C4A80ULL, 
            0x804105F04467179BULL, 0x92B6021DF9535E97ULL, 0xDEB8D42B0D2E9122ULL, 0xC5910FAB0B6813A3ULL, 
            0x4D156311BE2B5773ULL, 0xF50EEA89186C9161ULL, 0x3DA5827B5B10768CULL, 0xC1C2DE6FDE48CC31ULL, 
            0x79F3963DFB088164ULL, 0x2B7FAB6CA212770AULL, 0x0DD4616E422AA49FULL, 0xC4971347F411C10CULL, 
            0x335B6AEAA51702BCULL, 0x6974F7B40FBCB78FULL, 0x5765EABA1941CAD6ULL, 0x4CBFAC861F39D759ULL
        },
        {
            0xF4511480FA4B0B28ULL, 0x6BFEE5B02FE192C4ULL, 0x598B2139481D5C19ULL, 0xE82C66E8818A08F8ULL, 
            0x568BA74221B391DFULL, 0xFBF635831ECA9A89ULL, 0x054C4C105C0E8D73ULL, 0xA6F3324A677E2AE6ULL, 
            0xAB74EC4408CEE96CULL, 0x0764B490E9E81B5AULL, 0x8D8DB6BC343079B3ULL, 0xA1E714867DD07AB1ULL, 
            0x63B5CFE41606BDE5ULL, 0x1B6158013BEC1722ULL, 0x7FA9374ADE242AEBULL, 0x0E8E3A36A38BAB56ULL, 
            0x0432D226F8B41F0BULL, 0x38F409E6F90C5278ULL, 0x9E607C0D332BDAE9ULL, 0x231A39BC0D04FE78ULL, 
            0x9A98978BBFCF4488ULL, 0xCF059F1F547FC2A5ULL, 0x98A18B52DE168C98ULL, 0x5B166C7241F6B220ULL, 
            0x75333526FE4C00E0ULL, 0xFD7C2C936D3330CFULL, 0x35C5AA3B7664F518ULL, 0x7F1BBF03B9190A7FULL, 
            0x809CCEA2999DCD55ULL, 0x7E49E5E7EF5033B9ULL, 0xDC0C5B02D72370D4ULL, 0x08786289CE41A220ULL
        },
        {
            0x655864B12A4E90A1ULL, 0xFC4F4974C76096D2ULL, 0xEEF1BE330C74819EULL, 0x7A887868520D8880ULL, 
            0xA386FE4FC735D3E6ULL, 0x631F9D1B60DE0462ULL, 0x0F3BEE25B9A72F1DULL, 0x6C5C09F6F7348C32ULL, 
            0xE1EC5DCDA6F35E11ULL, 0x1134263AF147FC16ULL, 0x20DFF5E6B20C488EULL, 0xFDDBF7A939A7DBC6ULL, 
            0x593D3EF2854C1941ULL, 0x55EB60E3ABA95B8BULL, 0x72E089DF623CB2B5ULL, 0xE6847A5DBBA5E3C6ULL, 
            0x03E7E4DA44E968D3ULL, 0x1AC8F4A1AC65E59AULL, 0x32CA8C122EE4FBE9ULL, 0x2966F68179CB2FE5ULL, 
            0x2BD77E0143084895ULL, 0x3E5A30C5CFE69E6FULL, 0x7EA02ADB105EAA60ULL, 0x9905F916FA81C6A5ULL, 
            0x44985E74BE2F2ED4ULL, 0x8E3CF346FBA2E834ULL, 0x875129E668BBD3A9ULL, 0x8D4352B2CA3EF289ULL, 
            0x57C8DD71FC20CC00ULL, 0x25EB704DD7092F5DULL, 0xE69AD72EA97B103DULL, 0x9BCF3DE844B956EBULL
        },
        {
            0xA706309926C27732ULL, 0x6CB235D0CBD53B1AULL, 0xC3BC9073BF04F79BULL, 0xD91BDCC20361DF49ULL, 
            0x80FCF84A5A8D36CFULL, 0xD6BB0F106F32DCE1ULL, 0x88C56AA335DEB57CULL, 0x96C2CD840696A226ULL, 
            0x14F7BEA68C75B204ULL, 0xCFFA356A62B0B4EBULL, 0xD648001856F8B7CFULL, 0x1CEA8F1065CDCBE0ULL, 
            0x56C67B3CAB208AAAULL, 0x9727008AEFB1B2EDULL, 0xB1A5E63AB8A6A8C4ULL, 0x264FF747DCAAF08CULL, 
            0xAEB6479499AADC3FULL, 0xF4235DC482E9F789ULL, 0x09B14C4271913377ULL, 0xEAE854C935F03D19ULL, 
            0x416C299508684D46ULL, 0x27FBDA38EFCBD025ULL, 0xE1AB99C5310D69AAULL, 0x022531ECF1752A31ULL, 
            0x7AEE1C3D658AC07CULL, 0x582E25A4F7BD6CE9ULL, 0x50C01AE702FACA3AULL, 0xD061DA9AE660646AULL, 
            0xA9899F6469595B89ULL, 0x1A0400810254C5D1ULL, 0xE5BE264EB86DFC6AULL, 0x677B371EBDDAE5BEULL
        },
        {
            0xC298C0FCDB9E10C0ULL, 0xDE8F5133656D2D83ULL, 0x435191BC23E40F65ULL, 0x8C50E6F0A8D0D3D9ULL, 
            0xD1093395D34FFEC8ULL, 0xAB8CF3A538760244ULL, 0x65144238A3B1C4A8ULL, 0x5CBD0348CA254BEBULL, 
            0x005912ABB076F772ULL, 0x579D61792A216015ULL, 0xF6123365CBBE8578ULL, 0xFF158DF7F32FC4A0ULL, 
            0x51E3892D84D12DEFULL, 0x84A4C184AF45F10BULL, 0x07FE9759AFB43AE8ULL, 0x88525FBBB0607870ULL, 
            0xAD30F1CEE8BCB727ULL, 0xB711BD27E1CEC724ULL, 0x837D863B60A6E9C4ULL, 0x67F8EE9B929920B1ULL, 
            0x011E3952547B475AULL, 0x52CA8E491295F24AULL, 0x1CAAC9810FAEEE9BULL, 0xA9E2A4E5AB62EC5BULL, 
            0x38C177E085A775E7ULL, 0x5119870B0A3D73F5ULL, 0xB2DD6AC970ED78C1ULL, 0x23EBEB7C8185AFBAULL, 
            0x993600B4DBEDCFF3ULL, 0xD3C4A08EBCFE2DA8ULL, 0x6644ECB9A37FDB51ULL, 0x53E3300761326C15ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Kerpal_0006::kPhaseAConstants = {
    0xC68E1B26EF832874ULL,
    0x025DB9A06625EDB7ULL,
    0xE227F9383A24E93BULL,
    0xC68E1B26EF832874ULL,
    0x025DB9A06625EDB7ULL,
    0xE227F9383A24E93BULL,
    0x95C17D724D5CE720ULL,
    0xFC685F7482F60486ULL,
    0x34,
    0xD2,
    0x47,
    0x52,
    0x2F,
    0xE6,
    0xFF,
    0x4A
};

const TwistDomainSaltSet TwistExpander_Kerpal_0006::kPhaseBSalts = {
    {
        {
            0x8DA3F2CD11212279ULL, 0xDA909E170FC2221BULL, 0xCB45F39CC90BFB76ULL, 0x62CDE29F3F175B31ULL, 
            0xA9B25629A8FAABC5ULL, 0xAB4C8B740D9F3BC5ULL, 0x8F4E1FCEB8F90CB4ULL, 0xC1AB6A470425D048ULL, 
            0x5E0A5BC593C076A2ULL, 0x58C433611C049760ULL, 0x8B05D4CAB6E9D2EDULL, 0xFFC7BD841D831624ULL, 
            0x9B86C89AEBAEB734ULL, 0x8F0906611936F95BULL, 0x359745FDA82D948DULL, 0xDB116FB1EC76225CULL, 
            0x21E43E99E26FCB22ULL, 0x665684A955E09292ULL, 0x26A29D5778912F11ULL, 0x11221BF2EDD959BDULL, 
            0x69529B98EB70F67EULL, 0x60398BCC701595C7ULL, 0x303A6ED5EFCCADF0ULL, 0xD7B1C61F635B69BAULL, 
            0xDA612949277022D2ULL, 0xD5131D484A4E765BULL, 0x390B008E832E9BBDULL, 0xF7354F7AC0AEB4E7ULL, 
            0xAB994FE4F215CEF0ULL, 0x1071F4AA44792EABULL, 0xF6E5AD16FAC862ADULL, 0xF84AEAD3402CFAB0ULL
        },
        {
            0x569A9AF9B5FD85C5ULL, 0xEFC69338BB52AF12ULL, 0xDA9F9E9BCAE272B2ULL, 0x45F15D502ED291C6ULL, 
            0xAF23DD1F5A20A2A6ULL, 0x4D32D16DD9029BB6ULL, 0xDDDD3815500F44FFULL, 0x6F343E94256A0F9FULL, 
            0x5B00753AFC82B893ULL, 0xC0149B9BCAD56C5AULL, 0x693D116259AB246EULL, 0xE84C7D26F9969100ULL, 
            0x94F9DAC904D1E67BULL, 0xBED070673217CC33ULL, 0xBF68F8810CA1BED3ULL, 0x26F5B1BC7EE8A62CULL, 
            0x2216F611F06A2657ULL, 0x09317B02B1751F70ULL, 0x36B64E2D6A7CEFA7ULL, 0xE091DC5F76418A23ULL, 
            0x896EF0CC93FE64E3ULL, 0x4930805F6926F96BULL, 0x5FB7793132D96461ULL, 0x1B17785A2DFCA8C2ULL, 
            0x6674F75B79688AD0ULL, 0x7C3ED6C6044DFE8BULL, 0x5AD86F78A640C50AULL, 0x960B9974A19CBCE6ULL, 
            0x4CA22EACE6CB7296ULL, 0x3280155CD2444FC6ULL, 0x133790668EA3D0D0ULL, 0xF503E952479B3A19ULL
        },
        {
            0x9297DDE623E2DC74ULL, 0x37C619F611FF5281ULL, 0x5F6C02CE4A63B6FBULL, 0x5D2D143FBD5AAEACULL, 
            0xD4945DC6C4A52797ULL, 0xB35260E722AC43C8ULL, 0xB1036583F4F4458BULL, 0x428E50297C159F1FULL, 
            0x8DC0C1C3719538D4ULL, 0x5F1AFF7E41A097ABULL, 0x5D9DBCE5E6E66E8BULL, 0x5508CB4E3733FF2BULL, 
            0xC9C5950C5B4A30B6ULL, 0xFC0F1B6611A0A733ULL, 0x83294582D1419076ULL, 0xDA1F6B0B21420131ULL, 
            0x2F1127DD0766D515ULL, 0x23F5C59EED1F58F2ULL, 0x5D07C4463D4A2E69ULL, 0x621495463D4CE68EULL, 
            0x644D0848A982607AULL, 0x9A517420C8F5790FULL, 0x8F72464CF1156D2FULL, 0xE710975C241BC2F4ULL, 
            0xEE453394768058E9ULL, 0x1675346CE7ADF6F0ULL, 0xBA8D569295132D73ULL, 0x2A5FFDCD50D77844ULL, 
            0x7A5474650E87AAFFULL, 0xE865737A36B420F0ULL, 0x96AA2D95449C7337ULL, 0xBFE97010AF07073CULL
        },
        {
            0xDA3041B9394B2CA2ULL, 0xB30ADEABC2507585ULL, 0x1155F2690DCFFDBEULL, 0xF3EAC14109B85980ULL, 
            0xAD97089B0DD33F47ULL, 0x892B8C691ED322FEULL, 0xE55C3F7F085973C5ULL, 0x028EBF58C2B4FC07ULL, 
            0xBEFB9402AF30859EULL, 0x88F2322FB6B04276ULL, 0x0A61E9E0AADFA424ULL, 0x7DF52CFF433A3663ULL, 
            0x2B4B2D996667D6FCULL, 0x43C9BEA336EACA6CULL, 0x004F87F4A9A52B84ULL, 0x9537F01736815EECULL, 
            0xF5689B338B135583ULL, 0x332CD09A7828CD55ULL, 0xB5E6A9C6D3606BCAULL, 0xF0D2006287F6543DULL, 
            0x06CAA4860B294BA7ULL, 0x86A307574727DBC3ULL, 0xF190A321010CABF5ULL, 0xB53DD421D4661AB0ULL, 
            0x3D007522C8E3F900ULL, 0x2F8B2E55AE5DC5EBULL, 0x5AD7EB572B7A7752ULL, 0x19EF30C00C46F5D3ULL, 
            0xBF75308CD27F0851ULL, 0xC2F82E29362E32A5ULL, 0xDEC12FB500E7823FULL, 0x2381609A0067FCCAULL
        },
        {
            0x8EF2BBCA12E52965ULL, 0xCBD74F344091D3C7ULL, 0x47F55211D73DDB37ULL, 0xDDF7CA81ED2E3409ULL, 
            0xB33BD65A7AD3748EULL, 0xF7B4A90FC00FD8E2ULL, 0xC921F7C7388A9680ULL, 0xA8599CD255A71C83ULL, 
            0x87611A95AC8D1B86ULL, 0x37101D831D834DBFULL, 0xE8E8E174ACB07251ULL, 0x6A6A28373BD23FDAULL, 
            0xB744740EA9BCC102ULL, 0x2F999D0F26342BDEULL, 0x0D200DA4E371A59CULL, 0xA6FB8A2E358A438AULL, 
            0xDB57C5C96EC68BAFULL, 0xDE60F8342195F901ULL, 0x65D5AAA8EE43374BULL, 0x8CB143E81EA8C8A6ULL, 
            0xA0B5B6232F7D03CBULL, 0x1C9AB1693121E9A7ULL, 0x5D1F6D0B6B64F8FDULL, 0xAFAAE2FF7F968EF9ULL, 
            0x7F3E7430477BFFD6ULL, 0x7642CC5B57B89896ULL, 0xD0DCD39A0CBAB9E8ULL, 0x807A05F4AE4CA7EDULL, 
            0x9B26DC33A5255DE4ULL, 0x938345474AA4B325ULL, 0x832B8116BAD0CC41ULL, 0xC7499173BB831CB7ULL
        },
        {
            0x129760A3D9C94DE2ULL, 0xB102560C2882947AULL, 0xEB068087E27DFF4EULL, 0x587A0F3F4D163D06ULL, 
            0xF85F9B14DE357C07ULL, 0xE630F65AFC44DA0BULL, 0xFA609F487245F8ABULL, 0x20BE483CBD9204D3ULL, 
            0x1B381ADE838D06E9ULL, 0x308E26D37F7B9A57ULL, 0x7D188AAF715F37C8ULL, 0x3611134B2EDE2C53ULL, 
            0xC2A2B525EBA45096ULL, 0xE1ECE06B8B283F86ULL, 0xEFBE5E983312843DULL, 0xD4E0B6F2B99F3593ULL, 
            0x355C680A786C2FC5ULL, 0x6B5873D85E36021AULL, 0xB20900D55F6E4E43ULL, 0x85E790F73C126B61ULL, 
            0xD7F51E106C106820ULL, 0x0FA50E0C55541C8BULL, 0xF4DCA67EAB528D5BULL, 0xBDCBDA60B5E51D4FULL, 
            0xB853EAE916BCB3B8ULL, 0x85C0BDD65121A1FAULL, 0x9FCDBD80B230645EULL, 0xAC6AB41D12D996AAULL, 
            0xEE3440AED599808DULL, 0x83B3D69BBF347999ULL, 0x031104F692766602ULL, 0x895994EDE8E8645EULL
        }
    },
    {
        {
            0xE048D25B078A273EULL, 0x4AD6312D4EDD6782ULL, 0x4FD15C490E877551ULL, 0x9C8CAD104C6EF7DFULL, 
            0xE39D0D586A74F590ULL, 0xFE4A53AA3C719566ULL, 0x6667BBFA5E02A156ULL, 0x50053052CB7E54E2ULL, 
            0x1D172CFB6E9A7C51ULL, 0x36E8073735A7FFEAULL, 0x9A98DCD96B5C2DAAULL, 0x2B28FFF37851200EULL, 
            0xC246ED90CFE0ADE0ULL, 0x5A6E72C440110624ULL, 0x7061D5289DAF448AULL, 0xF310AC0030EEFAC2ULL, 
            0x2BF14FB482F3970EULL, 0xBBB14F922EC37CDCULL, 0xCD59CCB350F62924ULL, 0xEF6971A1546F882CULL, 
            0xFC2480B9AC60BB23ULL, 0x97E27868E3B43DE8ULL, 0x9024768661A08328ULL, 0xEAF05AA2E09A8980ULL, 
            0xB9B1FE19CAF1D196ULL, 0xA993ED3E7476154BULL, 0x6ECE3F058228C91EULL, 0x4E4C17240C8FC313ULL, 
            0x6165D6F2EF627545ULL, 0xB6C32B202B7542FDULL, 0xC1E6EBC3424B430AULL, 0x07A9E3A5206B7640ULL
        },
        {
            0x3AEBF08B7A2C6A96ULL, 0x82E17D556F053B30ULL, 0xB31A3787FF9CD01DULL, 0x60C91AFA9680F9ADULL, 
            0x348AD6D313015528ULL, 0x65AA11BF9DD87AF4ULL, 0x7B2FE21F91F3AA2CULL, 0x9AF4059A2C8290AAULL, 
            0xB4FD55A22B6ABDA9ULL, 0x026F0A486E135781ULL, 0x32F42ADA9047961DULL, 0x442703B59C62313DULL, 
            0xE7E4FAFD1D65DB19ULL, 0x63C0BA1AF8484056ULL, 0x529448B8AE09C193ULL, 0x64AB381407DD4F3CULL, 
            0xC504B558C7DAFEB2ULL, 0xC7B398A7B5C6729EULL, 0x5B4463C0854FD2C8ULL, 0x57921DD8D6A624D2ULL, 
            0xCBAF04731A411E8FULL, 0xB28E23D58EEB2B80ULL, 0x2D7861D94776D403ULL, 0x50EB2E3F16E46E16ULL, 
            0xA780DA227537557FULL, 0x872DC30D676225B6ULL, 0x4E9C935AC3F59CE3ULL, 0xEE1D1D417C941B94ULL, 
            0x5F228C4247499DE6ULL, 0xA5C5836F94F1E89AULL, 0x9683A439A0498F8FULL, 0x56CCDABA2122070DULL
        },
        {
            0xF2FEE734B73A1675ULL, 0x901257803345C9A4ULL, 0x2505A03BCFBCDB14ULL, 0x71852EFDAF4C1C5EULL, 
            0x5C57FFAF65F2BA59ULL, 0x2962D8E838610B76ULL, 0xA6F3620988608897ULL, 0x877070F285F94A9BULL, 
            0xBC9C659130DC14BDULL, 0xDA1E5A136DE97D3FULL, 0x3A24984FD6025463ULL, 0x6FD9DFBA57CE7C31ULL, 
            0x54F6C8003088E624ULL, 0xE00AC18525103D8EULL, 0xF4986518CDA6BE29ULL, 0x3FC4DCC49B691BFDULL, 
            0xA20EBFA46B945E2FULL, 0x699E70D074A71B62ULL, 0x78CB0AF6BB2511C5ULL, 0x81119C679DA0588CULL, 
            0xA6B1D7F281B802CEULL, 0x926CBF004863FEFCULL, 0xED263452606FCAD3ULL, 0xE870AC7170ED7069ULL, 
            0xCDA4EC91A072739CULL, 0x61E39A14094884E1ULL, 0xAE2A665C229EE6B7ULL, 0x846F841CE08A10CFULL, 
            0x2AA4A2A9F3F7B220ULL, 0x3A8A70CBB95C3717ULL, 0xDFC36F77EDFC26E3ULL, 0x82BDD33C5CF7B7B5ULL
        },
        {
            0xCD9FF37A52FBB71AULL, 0xB31931FB5AED5EB5ULL, 0xED9C6B22EDFA364DULL, 0x04C90DCD05076D95ULL, 
            0x042F8F2131FD1836ULL, 0x86471167AC3AA5EEULL, 0x29ACE2D72CFFBAC6ULL, 0x1F9B768C85B80320ULL, 
            0x0EA20BC362F32920ULL, 0xA21AF5F78CAC9ACCULL, 0x26321E74CDE8918EULL, 0x6C3207CD999933D2ULL, 
            0xB7A7AA67F0159D0EULL, 0x2B208EE4332F15E3ULL, 0xA7B3DEE46D6809CBULL, 0x5581D9E762826F20ULL, 
            0xA2FC2B63623D262BULL, 0x1745396F8DC667FFULL, 0xC1B937D87E475138ULL, 0x52EE8ACCA43AA180ULL, 
            0xCFBF3165B02270A8ULL, 0x1193024A79A52AECULL, 0x89A96FB9A922DF8AULL, 0xFDB96B30909B9E88ULL, 
            0x1233AC6F30AF663AULL, 0x8BDBC789EC535456ULL, 0x70D42AFA2EEF61CDULL, 0xD419641453DC454FULL, 
            0x534FB866F0DBE71BULL, 0x382E802C8F881B6AULL, 0xCB70A8D9BE48177BULL, 0x07C0EA762299D92CULL
        },
        {
            0x77FE926DE2880307ULL, 0x406484B5C54EFAF8ULL, 0xC5B4275CB3B5F843ULL, 0x7B6C45E851A0D427ULL, 
            0x69D9B2B216A7F8D5ULL, 0xA0F4805B33A715A7ULL, 0x710FDEE29D5067A7ULL, 0x502C7963A4648BA3ULL, 
            0xCCA03D2BB4DD38ECULL, 0x72F2CAEC87476081ULL, 0x3E9FEFD3BA92275AULL, 0xAB4E4283C4490FAFULL, 
            0xD70A81EB2BAB709EULL, 0x3DB23C4F49659495ULL, 0x7AF605D8A6DCA29EULL, 0x4174A595470C14DAULL, 
            0xD125A09D4A8FD3B8ULL, 0x279C5ACC27F13DA8ULL, 0x5D697E46B157D218ULL, 0xEFE0242E06CD389AULL, 
            0xCAD4CF89A8C5E6F7ULL, 0x169CE72573666344ULL, 0xC4DCB6B4DC383BA4ULL, 0xEB82037ABC7C4420ULL, 
            0x406BC9D4C8F6346FULL, 0x211A774399EF29BBULL, 0x803F1F7B4A2DF0C2ULL, 0xBE856027A438AC10ULL, 
            0x48A0053F7050F9B9ULL, 0xB6EE878D5AD13865ULL, 0xC1D77AF50AA4E457ULL, 0x49533F5CE895FB88ULL
        },
        {
            0x279B3F5D7949557BULL, 0xA6D6FF37A09E5F89ULL, 0x9F5182D322D2CB2CULL, 0x778B382D38314FE4ULL, 
            0xA4FEAB9E418E08FDULL, 0x2FCA346C04B75501ULL, 0x40B01AB2771814E8ULL, 0xDEDB49BC33855AD9ULL, 
            0x8EAA4060C1304984ULL, 0xF9116ADD57AD28FFULL, 0x8FB0B4652E3CDD23ULL, 0x83D88A9AED56791BULL, 
            0x2C9727B84733C4AAULL, 0xF9BC41C6D1432456ULL, 0x8DA68E37322B8DE6ULL, 0xD21F5E64F55B01ABULL, 
            0x3EC98DC8D6742E46ULL, 0xE6889C69ECB1B036ULL, 0xDFA6351BC24441EEULL, 0x3543C6425B2B73F7ULL, 
            0x7D70E9E2C5C53312ULL, 0x097798AF70FF788BULL, 0x39399B94D92F093DULL, 0xC465D7ECC813E522ULL, 
            0x0F93817281DF5439ULL, 0xC2FAEEAFCA9E8868ULL, 0xB7992C53F402316FULL, 0xCA66A71E3E0674E7ULL, 
            0xFBDB8708F8703EC3ULL, 0x21A7E4196C095C6FULL, 0xE2FD975B9AD8206DULL, 0x9D3C49112B967547ULL
        }
    },
    {
        {
            0x3528A6A55F7C7B98ULL, 0x0679A17E5DBA7FFEULL, 0xADCEB7C8E3FB7E06ULL, 0x01EFF9036BC2BADAULL, 
            0x261382D3E71FED26ULL, 0x0C097F6A5EEC030EULL, 0x2BAA1A3C0BCB9301ULL, 0xB90C4832AEFBA7E2ULL, 
            0x8F8DEA2A624C2E37ULL, 0x72A7F1964E5556D9ULL, 0x5A6740E115230DE2ULL, 0xE7371D38DFB6674CULL, 
            0xEA6F444B9001E24AULL, 0xC7243C7ECBD8C335ULL, 0xF0896F8AEE72156BULL, 0xF0968728DB7AB224ULL, 
            0x4BED4833EBFE6936ULL, 0xB7FAAE7E51625170ULL, 0xE650515A7F51FBFEULL, 0xEA1F02CEB6BCFD42ULL, 
            0x399F489A091EE4FEULL, 0xE5A236A5844A5982ULL, 0x747C084C45DCE3D0ULL, 0xAA20A1C07E11F723ULL, 
            0xA3675F78C95D285CULL, 0x047258ADB53C1761ULL, 0x83E9282328E30602ULL, 0x07E77A9F12E2B840ULL, 
            0xB6787DEA4637EA79ULL, 0x75BC34B58FB07A13ULL, 0x8EE8B7FB355A46A5ULL, 0x8A110F4372DDD03CULL
        },
        {
            0xF8C2C701CA61E653ULL, 0x3DFC9237EDA684DFULL, 0x9309501E51A33977ULL, 0xC7B495956D260A09ULL, 
            0x6D9E3B4566F77406ULL, 0x4501DE2DA7490359ULL, 0x4EE4578A9338D316ULL, 0xDB49B4B0BC1F9F68ULL, 
            0xABF9FE99C1C77C84ULL, 0x40C2B4993505038FULL, 0x160F8F5E25300FAAULL, 0x5046B95D984E4346ULL, 
            0x49B82A0471AC8DA5ULL, 0x91BCAE4E6ABB3874ULL, 0x38618C26ADC50A44ULL, 0x60D1396168FC48D4ULL, 
            0x9FD4BE4869582B44ULL, 0xBFA0F3F4B3251CDDULL, 0x68BAA931B897C4E4ULL, 0x58CAF40795C4AF04ULL, 
            0x512298EC3E59026BULL, 0x6F53D1D1A59226AFULL, 0xE9E09B02D151DC4EULL, 0x8C77EFB464FEDEABULL, 
            0xA7C75BBE5BB11D25ULL, 0xE00D12A4E8D2E77AULL, 0x5FB685F29D3946BFULL, 0x04AB30075C876756ULL, 
            0x53867BCDE8C4D537ULL, 0x08ABC08335064E75ULL, 0x44B5E225FA8DFD16ULL, 0xC89391CB83DC5E82ULL
        },
        {
            0x060C52086ED009E2ULL, 0x4BA84C6952306C83ULL, 0x613C61C21B0EA9E6ULL, 0xEDE99A67E8C8F68EULL, 
            0x363EFAF12F57300EULL, 0x6BD4EA57F805488CULL, 0x844CAD56234DE81DULL, 0x27FDA0B0DF6BB808ULL, 
            0xF4A2D95E3884B634ULL, 0x08F6C471982B2D39ULL, 0x29A8EF192821BED6ULL, 0x96E6120DCE6CE17AULL, 
            0xD10608BF26902254ULL, 0x8EFCC461321785A9ULL, 0xA6CE80FC2BBB0326ULL, 0x4D4C9DDB8D240DF4ULL, 
            0xEE519B0D1F5DC2A9ULL, 0xCEABE59136C46810ULL, 0x4D3006422D65B259ULL, 0xF6D9C2189202FC4BULL, 
            0x8BE4F6E1301FE24DULL, 0x77FD1E7E2BFCCF1FULL, 0x83B8464F29EDA50EULL, 0xC14AED2EF023FB7BULL, 
            0x20907D2C1DCD60C0ULL, 0x5B8779A6FA30A904ULL, 0x9C6E91AFAF77D85AULL, 0x69E2A9D360F7F97BULL, 
            0x2F923FB5A34D9270ULL, 0x3FAA5BEA19EB045DULL, 0x49BBB0979E415A81ULL, 0xF91AB3F9E576454CULL
        },
        {
            0x4EB3705A2E491297ULL, 0x16517C358571149CULL, 0x8BBD281992B9D5F0ULL, 0x1754C546FB6F2F9BULL, 
            0xD7E94AFA317C18CAULL, 0x3E6678A3FE9897CBULL, 0x288231B190C8F49AULL, 0x9B59E4514E98C3FAULL, 
            0xAFC9AF8D3231D7C2ULL, 0x83C6E046B2083642ULL, 0x7A9167035F4F9A35ULL, 0x1847C4B122EC1ADBULL, 
            0x66D67C482267AB03ULL, 0x182EDE4B5654A175ULL, 0xBF05CBC0AFBA7036ULL, 0x1D5AB1F4349A5BDAULL, 
            0x7C0D4117E6EC3369ULL, 0xDCEC8EE2A5A0056FULL, 0x0370572830B3ABD7ULL, 0xE6A0626545B71FF0ULL, 
            0xDDC58D21E274720DULL, 0xF61CA2650E480BD3ULL, 0x11E80C1CB854AE37ULL, 0xC9E9AA0934F62C83ULL, 
            0x92052C92D0D22BC3ULL, 0xBEC1864869CF1CA2ULL, 0x3578B6EA35F90BFAULL, 0x2BCE82AD86EB151AULL, 
            0x399A8D0057235C27ULL, 0xEFCE273B5F8941F5ULL, 0xE306ECECA2F4A041ULL, 0xC1AB5CE2DDAC78AAULL
        },
        {
            0xAA7419641A3F4020ULL, 0x594A7C4432AF262DULL, 0xD92162270A2B834CULL, 0x867ADD34BFED8B87ULL, 
            0x78D3D07A4A35D4F8ULL, 0x7D3BF6A886476000ULL, 0xCB1ECD91EF9E7C0FULL, 0x3FCF6A68907720E8ULL, 
            0xD1F27D27DF13BFADULL, 0xFBC8D3345B9D1FEAULL, 0xC8D7C04D69E7162DULL, 0x6FE203B3E665F4FFULL, 
            0x9BF758E8626BF3D1ULL, 0x4E5C232E1E4E5672ULL, 0x35A5D87AE48F5A3BULL, 0xFA2422F307D053B3ULL, 
            0xC5AF903303393691ULL, 0x19ADE243F041600CULL, 0x4B79527B660727C7ULL, 0x17E9C83815442191ULL, 
            0xC8209DA2ABD342B1ULL, 0xAE412F350CC0E819ULL, 0xF79A15D38392540FULL, 0xE56BECD87EE28644ULL, 
            0xE0D986C54074B23BULL, 0xF9A01B6780291CB8ULL, 0x390770503DA03C8BULL, 0xC6546BEA88FD4EAAULL, 
            0x9E9C583CB120E22AULL, 0x3DFF95CE190344E1ULL, 0x213745C04086FC58ULL, 0xE4208C0E3E93DB4FULL
        },
        {
            0xC802576A8B186DDBULL, 0xCCCABFBB8F159955ULL, 0x667EBD8434E3A3DBULL, 0xFA90AC7C71FB41F5ULL, 
            0xEB6BB09F807F6FBEULL, 0xB9093C90BE526156ULL, 0x647275969DBB9D07ULL, 0x3B63B0CA424DE44DULL, 
            0x25001B9F16455CACULL, 0x9BD8B6F5772389D1ULL, 0x9DB7352D9E751B74ULL, 0x9A84FBF5EC5122DAULL, 
            0x63C45104BC0471B4ULL, 0x895859AAB01CE73DULL, 0xD4AE80E12815B853ULL, 0xA03538803B6E38F3ULL, 
            0x3571E69B3AD870B8ULL, 0x4CEFABD089B1C76BULL, 0xD5AF05661A1681F1ULL, 0x70B6FC65E38C4F07ULL, 
            0x75F0DDBCD678C428ULL, 0x7FCE3D77D6400594ULL, 0x18418967BF3FF445ULL, 0x923FC857CA1D040DULL, 
            0xBE7305B15EA30FF0ULL, 0xAD711D0BDC586D14ULL, 0x382B423E5E2DCF78ULL, 0xE2CFBF5445203193ULL, 
            0xB5A9776564268AEAULL, 0x5BC66A56889FAE32ULL, 0xE5D8D313BD4A3BD8ULL, 0x61F51AA3C5AB26A1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Kerpal_0006::kPhaseBConstants = {
    0x80D6299E5646E871ULL,
    0x3C169F59D60982B7ULL,
    0x2E1C69BD7D479619ULL,
    0x80D6299E5646E871ULL,
    0x3C169F59D60982B7ULL,
    0x2E1C69BD7D479619ULL,
    0xFBEE068364624BADULL,
    0x9C1DAA7EE4002BB3ULL,
    0x40,
    0x8C,
    0xF9,
    0xAE,
    0x39,
    0x57,
    0xAF,
    0x50
};

const TwistDomainSaltSet TwistExpander_Kerpal_0006::kPhaseCSalts = {
    {
        {
            0x112803B4B7EBBCF5ULL, 0xCB926375F9BB1727ULL, 0x558389340C0EE429ULL, 0xA6E10CDDD7C1EA40ULL, 
            0x8EB5882E4980D897ULL, 0x3A9E566FC21EB587ULL, 0x10BE7FD449820FEAULL, 0x0AD7D58E2DD5C780ULL, 
            0x998E8DA1A1FCCD1AULL, 0xF2E505C17FFB0909ULL, 0x6A1507760F1AC9DCULL, 0x29096EFC9F8152D6ULL, 
            0x93473FFA17C65449ULL, 0x6DB259C76D57AB51ULL, 0x233A667D080BFB95ULL, 0xF547F207C3B97D07ULL, 
            0x5976399C1959C6A5ULL, 0x087DD4946D810907ULL, 0x0284F8919AB13F98ULL, 0x7C8861B53D1B00CBULL, 
            0xC0EA9D8B9501E122ULL, 0x06D6B62571D64C00ULL, 0x9E35AE0FC84CF087ULL, 0x84769D72985A0E92ULL, 
            0x35D73BDF653D6370ULL, 0xEFA480ACC4C55FA4ULL, 0x3BBCD040E1770D56ULL, 0x3BAF9F34F8013729ULL, 
            0xB293091EF46F8D25ULL, 0xC7A8CE399CC7E5E8ULL, 0xFC8D496183DFEF29ULL, 0x76389EE8DD29F027ULL
        },
        {
            0xACC308F6BA88B5F2ULL, 0x71F619DF2ABDCFC8ULL, 0x3D0716B808DD9752ULL, 0xE287B5D2DE0000C8ULL, 
            0x3816490FF82256E0ULL, 0x4A20253D6B2D9150ULL, 0xF83C994E7FE25ED8ULL, 0xC49A42BF5BC23ED8ULL, 
            0xEFD79C9C1CEA1FD0ULL, 0xE18E8D1DCE19B090ULL, 0xE3AC66C356C52A61ULL, 0x571F34A204164D3BULL, 
            0x6C23ABE801A20152ULL, 0x9D510CFFF0F095AEULL, 0x453C19250AB1FB97ULL, 0x4FD998EEBD419BAAULL, 
            0x07A1E15E3FA40B61ULL, 0xE7005C3ACFB6994DULL, 0xA4334FA86839EEA8ULL, 0xFF49ADF05104FF67ULL, 
            0xCA274C278BA7367FULL, 0xA830769FB102B06AULL, 0x44B0E14C1C74B2DFULL, 0x7F0ADD5C545B1FE8ULL, 
            0xB19774E67553A7BFULL, 0x4F0A05BC7E0D2579ULL, 0x1C2596C7ED092D19ULL, 0x1B20A3A8CB99D754ULL, 
            0xFB95A5AFC7E127A1ULL, 0x41DB7AED91FB5DADULL, 0x9509D10243D55A6CULL, 0xB93D68966710B625ULL
        },
        {
            0x58A3E6981D77DD31ULL, 0xBCCA6C5D31A1956EULL, 0x8E4A28A5A609B300ULL, 0xEC1E4B6DB2D81F4DULL, 
            0xF2A3C6267767F3E6ULL, 0x447A90A9C6700CDFULL, 0x68EF4082E5B49852ULL, 0xC54F674AAFD4EC7BULL, 
            0xD11BDC9945E5A57BULL, 0x2F168D98DDC1A8F4ULL, 0xE6522A079582FCF3ULL, 0xEAD89BCA334BB8CEULL, 
            0x031849583D5A1188ULL, 0x10D7DD11409DD6A6ULL, 0x92D885019C891A40ULL, 0xE8EA0B95B0AE5F15ULL, 
            0x8AC95649C1D8D6DAULL, 0x11EE564F76830A1BULL, 0x4BD68DDAB8D3731FULL, 0x40DA30A0A6B3CB64ULL, 
            0x36999CAAE6D1B854ULL, 0x545FD3C429AD0274ULL, 0xCD21062DE04E9EC1ULL, 0x60F22D219EBC86C0ULL, 
            0xAEDD5225A4C87DDFULL, 0xF23DBEF4DBAC66FFULL, 0x44EC82A64B6D62BCULL, 0x502CBBEEE818C2EDULL, 
            0x08C210300C11C8C3ULL, 0xA207397DA48C84EEULL, 0x966DA3D4D957D32BULL, 0x696EDB738CA065F8ULL
        },
        {
            0xCFBE6DC72D5DD407ULL, 0xA8EB7E0390DACA74ULL, 0x9E383EE56E304E7DULL, 0x62BE97C7998D4D1DULL, 
            0xFFF480FFED29D463ULL, 0xD40AFDC386575375ULL, 0xC9C5C3B320812893ULL, 0x1D5D45677F33F152ULL, 
            0x7DF009873DC0E4D0ULL, 0x796E1E6848428722ULL, 0x854CF096B20CE19CULL, 0x1019E617A9F126F4ULL, 
            0x2C829FE27A7FFAA6ULL, 0x086EFBCF27B32AE2ULL, 0xD56B7CEAFCDD43A8ULL, 0x2C896B99FED55ED8ULL, 
            0x009363A5B6D31180ULL, 0xB3EBBF1FD3C8781EULL, 0xCF94D1260F6D5F77ULL, 0x4A0166518BE732A2ULL, 
            0xF787315A80CBAF0BULL, 0xA3439EE6A3474DDDULL, 0x12B4E84F91EE720BULL, 0xF825EDB81CF4D570ULL, 
            0x314FF5FAA38B6A60ULL, 0xCC7054F26FD263FFULL, 0xE3818FD1C641291DULL, 0x3D23513234EC7E57ULL, 
            0x43CC79F762FFED80ULL, 0x64B61BA71AB1B94EULL, 0x7962927BBDF99430ULL, 0x00E97DC5822D751EULL
        },
        {
            0x63868549B1F3C337ULL, 0xEC315C129D7D0260ULL, 0x03878A73C1956F83ULL, 0x1DD96F9941416404ULL, 
            0xC2C205963110906FULL, 0x8EA1378D5CA87799ULL, 0xB3D2EEE63EC25599ULL, 0x757186A9EF4EF553ULL, 
            0xA11F057AF032DD8AULL, 0x72C7424783725AE6ULL, 0xF0C2CA86EAE0EEECULL, 0x839B1E4C9CD5E5B9ULL, 
            0xDF23EA3E35F9A666ULL, 0xEFF722A2E56BA7A6ULL, 0x76C8BB7341112A7CULL, 0x8B34FB591C4F9673ULL, 
            0x5DF06A0DEDED6325ULL, 0x1028BD35B9E03EA5ULL, 0x976D0132A1DC09E3ULL, 0x53D48CC25D6239D1ULL, 
            0xF5D1F2AF7657F967ULL, 0x08E28EB95D8827C3ULL, 0x9499DD087EB96E17ULL, 0x576412635AE50E92ULL, 
            0x26B2793CE245A2C6ULL, 0x56D68B49A9E8917EULL, 0xEB94AA929D7A2CFEULL, 0x6513497B8C4EBC50ULL, 
            0xEDCFE7670E797AA7ULL, 0xF087BE6308ADD616ULL, 0xC9E49BC804931281ULL, 0xD2542DA6A8DF762AULL
        },
        {
            0x2BDCF77FC6788AFFULL, 0xE32F7BFCD77D278EULL, 0x99F49D9CF3D3C3FAULL, 0xA4AB3D588CDD1AE4ULL, 
            0x376E5F74B28E1429ULL, 0xBC7F52316E73E145ULL, 0xEF44EB770FEE113DULL, 0xF8128B7F798DE72AULL, 
            0x9038B91E224744A2ULL, 0x93504F1917FACD86ULL, 0xE4D78D2DFE447D94ULL, 0x67640FC0483451B3ULL, 
            0x837CAFB75CEBA2C4ULL, 0x521171A4FBC8AB73ULL, 0x389DFAAC8FFDF3FCULL, 0x31E2E334F1235F91ULL, 
            0x6430F457F99BD3CFULL, 0xF469A2094CDED59DULL, 0x3BD23442FC5E7215ULL, 0x5D5D31D3A386CF68ULL, 
            0xA79AF3512EA4F720ULL, 0x1ED728E89947BFB9ULL, 0x539F6AF2DA0937C9ULL, 0x41CA2B6395476897ULL, 
            0x664B54F4E45802FFULL, 0x82CE06EA28EC0AE4ULL, 0x1C5E6FF2DB0AE3DAULL, 0xDEB5E9A1FC6EB09AULL, 
            0x688A571AF972784CULL, 0x6B77B6CE3F6BECA0ULL, 0x36FA778FA9D2659AULL, 0xFE59726D90C6E838ULL
        }
    },
    {
        {
            0x29CBB5DF7311995DULL, 0x3C985BAAF3A9C391ULL, 0xDF36999DE3F9B13DULL, 0xAC44F674B18DDDE2ULL, 
            0x0950378812D058EEULL, 0x49947BD913B86E57ULL, 0x00068A9471320180ULL, 0x9A8E46864175C8F2ULL, 
            0x101DB736D3EBE67EULL, 0x4B26CF5E6BEB82DCULL, 0x1F450DF225702104ULL, 0xB7237DE334C49B17ULL, 
            0x694E0488A1CC0795ULL, 0x1F24DB81F3C7176DULL, 0x4C3745A905138D41ULL, 0x5E99F81DADC696C7ULL, 
            0xB98295D857C8F4D9ULL, 0x7DED5FC7E9F64813ULL, 0xF09A078205B10438ULL, 0x195B4AA9C6EC90D6ULL, 
            0xD8E372A229402CA2ULL, 0xFF3CF5DA5C04EB31ULL, 0x5C3F857D1F81970FULL, 0xE2A25F4D900BBC65ULL, 
            0xFA0A625B7CDFABACULL, 0xB694FE6357DA8319ULL, 0x77C5056D479CE953ULL, 0xB672996CD76CA049ULL, 
            0x8B758EE242DBBE09ULL, 0x27AA8A9487ECBE9CULL, 0x90C9764617D51520ULL, 0x091B2499482FC61CULL
        },
        {
            0x2B1F26A7EA282605ULL, 0xBC8F8CA5B416D5D2ULL, 0x74C8B2F3D041E8ECULL, 0x9F5644FD41EE48FAULL, 
            0x12DA30F172A5AC5CULL, 0x263A918400C80D1EULL, 0x6096BB6E94F03EB3ULL, 0x1A1A6E0CCE994BC3ULL, 
            0x6BC9E03229173BDAULL, 0xFDC4B94FD2D0EACEULL, 0x1ADD370B0544AECEULL, 0x20A464743BF3FC3AULL, 
            0xCA9D1AE731961199ULL, 0x200578299EC5D959ULL, 0x085EF0499518D081ULL, 0x696D035409494753ULL, 
            0xA5B2C687D97C9DFFULL, 0x19A2E84B4ED97651ULL, 0x63008C24C43B7B9DULL, 0xAF8AC3500647E2D9ULL, 
            0xEAECCE2C9A803E6AULL, 0x585753C164331009ULL, 0xAB801FCC0DF8DB83ULL, 0xD76C176B0BDE91C1ULL, 
            0x7B958009A1F61748ULL, 0x39E8D9BAE235BB12ULL, 0xC21C0F66882894DFULL, 0x0769F2EC81747F70ULL, 
            0x602C9F0D83D202D7ULL, 0xCE25C12767B91EEDULL, 0xCE0C68160C49E9B5ULL, 0x6430A126B52489ACULL
        },
        {
            0xA39729676FF0B0AEULL, 0x68BE10F100047E0AULL, 0x905B9F1DCD1E3DB6ULL, 0xD4FF5E393A82C1B1ULL, 
            0x438FD458A19B7A4BULL, 0x4D0317B94F15169EULL, 0xC297277687FD78D8ULL, 0x6BDD1C84060F66D1ULL, 
            0x956119D44B5B0BEEULL, 0x1DEC616F2B262D94ULL, 0xC56DAA35B5E224E8ULL, 0x091C26873ED90714ULL, 
            0xD7F097DFD75E3655ULL, 0x8BAA68D02E9B7AF4ULL, 0x3BD6C8B6A9D5ABECULL, 0x432DE58502B63FF1ULL, 
            0x494E6F9A8295B01AULL, 0x36BA9B508DF3AECAULL, 0x34164B6E1FFA1406ULL, 0xDA14427B9C9986FFULL, 
            0x856C1EC6B5F1CE44ULL, 0x410C41C5A9D10559ULL, 0x89B219F99CEC7BBAULL, 0x863E4C5095A4430FULL, 
            0x92D45FA08A66A182ULL, 0x3A836AF49F4FD330ULL, 0x8FF98C82D6D486BCULL, 0x4E0E984E1E1CFD5CULL, 
            0x7CB1B6529408EDECULL, 0xCB9DD341B902A87BULL, 0x068C54B601A51727ULL, 0x8B228A5BDA9EEF56ULL
        },
        {
            0xD4F28164054E50A2ULL, 0xB3A12ABC4419F8D4ULL, 0xEC575EB9666EAF48ULL, 0x982EC7464705FCAFULL, 
            0xABE2E12F5BF56785ULL, 0x14A90CFF12A3C4CCULL, 0xC55401B35EDE7EB4ULL, 0x47E2EC01E6844059ULL, 
            0x347CDEAD761A1470ULL, 0x17EA091CD67E309DULL, 0x3D1ECB91AB1C2028ULL, 0x35619F1CF490FF2DULL, 
            0x8ED7ECD1FA1CCCCAULL, 0xE3771B74B1761DE4ULL, 0xE1E58E85928C414EULL, 0x99EF3D0538CC6793ULL, 
            0xCB5C43E1F24DB5A4ULL, 0xB31164617952139FULL, 0x50E18DDF83EC1738ULL, 0xF8480E63EA4FA4B7ULL, 
            0x1FCD3DB457C25926ULL, 0x4287A274E81FF020ULL, 0x03775B44ED342080ULL, 0xE335460C02EAB31CULL, 
            0x7A4CDACE1B79B896ULL, 0x62C660DB507EEF5CULL, 0x9EB0405A85047522ULL, 0xBA3EAE31048DE737ULL, 
            0x72F3FA39AE54673AULL, 0x3857F7D0514D182EULL, 0xD9C7CAE687E20B36ULL, 0x6CD160C8C44BD617ULL
        },
        {
            0x9343C58C4419ADA6ULL, 0x20944150A35ADDDDULL, 0xE5ECF939171D48A6ULL, 0x10DE383D5E54DA81ULL, 
            0x19F88CEAC5C29ACAULL, 0xE766315BA98AF60AULL, 0x41E99F839C3F88C5ULL, 0x017B4607CA294A72ULL, 
            0x2944792293EA61E1ULL, 0xEAB0B8A65D685199ULL, 0x64BB333E2F8E0252ULL, 0xA490B181A2AB1DE5ULL, 
            0x26996DFD64AB63A5ULL, 0x1144856B789FE7C8ULL, 0xED2EB69DA3C2CF40ULL, 0xDB5C98894226BB13ULL, 
            0x115221A500327805ULL, 0x411AA9772F7B45FAULL, 0x3EBC67DC30C90E36ULL, 0x8E4444B97180F921ULL, 
            0x9DE9352383B559F8ULL, 0xEFB0D25E657916B4ULL, 0xA973621DC9B5F6F4ULL, 0xC4AA7B420AE76EA6ULL, 
            0x2DAB6A4A06285810ULL, 0xA46DCFA2E193AA7DULL, 0x76EC53186FE0B1C4ULL, 0x8C343A1BD3BF0720ULL, 
            0x18808FA8D732A9F8ULL, 0xB2B5C37EA86E66BCULL, 0xB2D27467B194E08AULL, 0x63130F27133A34A2ULL
        },
        {
            0xCF66486B2E26E20FULL, 0x57562EE65A4636D6ULL, 0xFED1A60012379FFEULL, 0x2855DD7AFCFAA098ULL, 
            0xD407249BE7E680A6ULL, 0xC54C1461729A0F00ULL, 0x3380E8CB305B24C7ULL, 0xEC7247D7C2A157FFULL, 
            0x957BA1C86198A093ULL, 0x74F6BA90FDCB6DE7ULL, 0xED0FC8A11F5BA17BULL, 0x2072FC7C2D419113ULL, 
            0xF866293AD99BA9AFULL, 0x6D049FFAC195EC09ULL, 0x45333D225CE09B4DULL, 0x10404F85D1CAF1D5ULL, 
            0x265BEFCA1C278A1CULL, 0x0AC7C87A06EDDCC0ULL, 0x6DB37A290D5F9D0BULL, 0x86FD1C581F92D094ULL, 
            0x44F55ADFF4D83F5FULL, 0x25482F9C5E99AE1CULL, 0x2FD4FE6F87335028ULL, 0x05C50C5A7ABA1122ULL, 
            0x3321E066C46C0169ULL, 0x531695180106ADB7ULL, 0x4562D68747C11A0DULL, 0xC1454B4860415A74ULL, 
            0x70C5056ADA11ABF0ULL, 0xC8E0CC47AED87473ULL, 0x1399FAC308E7EB74ULL, 0xA10A042BA49A975EULL
        }
    },
    {
        {
            0x7B9F33637466AF25ULL, 0x17A7058DF6B6AC19ULL, 0x8289992AB581E1D1ULL, 0xAA0856ADCE004465ULL, 
            0x82CA4DF8CCD6D9ADULL, 0xF8DBDCBA7085644EULL, 0x8F86AF7771A8D996ULL, 0x779F9B676AF24461ULL, 
            0x42162214E1D715CAULL, 0x2D3366118E4569FAULL, 0x64E8A4D9CD1007A6ULL, 0xD4D96BD4EC5D306BULL, 
            0x2BE5B295B52E9161ULL, 0x6F63AB9B85F377C9ULL, 0x4FC8FE8F07549C7AULL, 0x38A445331360C04CULL, 
            0x9969A601F0EFB01BULL, 0x2420A59E5C77D95BULL, 0xF28D6889C13CDEFEULL, 0x5ABE8C44908928E6ULL, 
            0x55660892CA5DC553ULL, 0x63AC72FEB14BCC39ULL, 0x05406A8D10EEF7E3ULL, 0x40B3AE2406355D71ULL, 
            0xDFE6076E5C8725F0ULL, 0x88C474E23C8D7302ULL, 0x9F6F61B3D90ED966ULL, 0x78269168D8DB66D6ULL, 
            0x313F15BFEBF1E078ULL, 0x898B6A84933D1405ULL, 0xE8005F81B72B2CEDULL, 0xCFBC0008B90E5121ULL
        },
        {
            0x726AF0285E1BE4D9ULL, 0x3FA313AFBBC49933ULL, 0xA5242BCFE546B1D2ULL, 0x8581634C9460C5E5ULL, 
            0xAB30794EC3659D76ULL, 0x432316653AB1F986ULL, 0xE56F7119D37D4FD1ULL, 0x4DD9F4503792A2DCULL, 
            0x70F8FD67DF4F3845ULL, 0x5ABD91D37DA1BD87ULL, 0x69D85CED5198DD62ULL, 0x94C73DBD7F2C8582ULL, 
            0x5CFE6F3B89953B88ULL, 0xF86FD71D0360EF81ULL, 0x8DC50112953B4FC3ULL, 0xE166823D106BF838ULL, 
            0xDA20C00C0521E376ULL, 0x330616283C679AF4ULL, 0x6776AD9A48742FBFULL, 0x84A9977F02FA79D0ULL, 
            0x7FBC7BBF27FEACB8ULL, 0x006DCEFC0F3B8E0BULL, 0xF0147BCAEE652162ULL, 0x8C060AC029D185F9ULL, 
            0x602A2C0CF77247E1ULL, 0x21314D67AC1C0A6CULL, 0x5C615B41CD1B32F5ULL, 0x21DAEFFE5D358CD7ULL, 
            0xBE9A7C647E57D7F7ULL, 0x93E7E60AA44A6FB3ULL, 0x015E3A9F0C5B39BFULL, 0x84711B9B7405616FULL
        },
        {
            0xF0E5DC1413CB8F79ULL, 0x9FBA44960B5A7C29ULL, 0x9EE1E2968EE1236CULL, 0x9C2368CD5FC31B34ULL, 
            0xD16B77D83F838657ULL, 0xFF3E6CC89FAD707AULL, 0xBEEECA284CE074C4ULL, 0xAAA54A55D251F356ULL, 
            0x20CFC589CF0837CCULL, 0xCD344E8011FB0277ULL, 0x09AF2E6276B9D125ULL, 0xB95720CCDE265101ULL, 
            0x9D7180658428FA6AULL, 0x25948D806D8EF719ULL, 0xFA4E6B3B827E5198ULL, 0x7E294665E4423DBEULL, 
            0x638AE60BBF08531BULL, 0xE5A16677DE16FB79ULL, 0x651EE3B9BEEC98EBULL, 0x9DD9704A7FBEC7D4ULL, 
            0x572E089FEA9C0519ULL, 0x852AD0C5F516D4D3ULL, 0x422D259BA58027FAULL, 0x06F2BE8E7A624409ULL, 
            0xA4BCE5D9AB6B1EEEULL, 0x7C8D1507A4E43E02ULL, 0x543E20968639C71DULL, 0x16B3F83537D5DEB8ULL, 
            0x2FD8FB1D42A43A00ULL, 0xB11EF85FBB00E4AFULL, 0xC7EDE01E01CB5163ULL, 0x9D83C7FB93EE4B8AULL
        },
        {
            0xD50D8A0CB8B13B20ULL, 0x2FF37371038485C9ULL, 0xF85A6A02AEF7ABEBULL, 0xAD5FA8B88B6EFC73ULL, 
            0xBC7F2EA6BEF2AA57ULL, 0x64673781C8A57F44ULL, 0x769334FA612A70F8ULL, 0xAB8BEC13D3CB8AABULL, 
            0x5E996681C38AD430ULL, 0xDC8FF5CB43FC2D7EULL, 0xDD8DFD5150DF8DABULL, 0x8CCF31645DC3FB40ULL, 
            0xAD49C95ECF783A22ULL, 0x66244833E137E2AEULL, 0x5F4971AA72389231ULL, 0xF8B84B959FA361CBULL, 
            0x1BF6FC5389132A19ULL, 0x413B24BEB7326871ULL, 0xFDB63051AB81AB8CULL, 0xAF9702F504DE25EEULL, 
            0xD8C59E36F6330677ULL, 0xF0F97C658093BA49ULL, 0xCC27D03512A1D37CULL, 0x47C64A7775369EFEULL, 
            0xD8E7C99916D60708ULL, 0x7F7D28201F1BE96EULL, 0x6626381B8CCFF012ULL, 0xF7DA47AEC2808932ULL, 
            0x6BBD892AD0AF8762ULL, 0x23F71888B6CB18C3ULL, 0xA90D5123ED00284CULL, 0x869FB3EE6F42B13CULL
        },
        {
            0xB5F70EE8CC054482ULL, 0x334AC33E863B55D2ULL, 0x2F7D2E0F960D5470ULL, 0x2693BE0CBB02EE0BULL, 
            0x056A4B691B34D7E4ULL, 0xBEBFE4238EE44A11ULL, 0x0CC3BDFA34B846BEULL, 0x588A6927CFCF2DA7ULL, 
            0x5099A6032DF780DEULL, 0xF57209EF0B1CA2C7ULL, 0xF96F08DB234396B6ULL, 0x25DAE1DBFE2188ABULL, 
            0xD153FA8AFB3D3309ULL, 0x88540101068480DBULL, 0x2D30E124228CA292ULL, 0x344AA6FDB62B1C5AULL, 
            0x583CE64E9C48ACB1ULL, 0x678499EA8F102664ULL, 0x80713B77FFEB7025ULL, 0x81BBAF4C5F765B14ULL, 
            0xACF6FFD12636EA84ULL, 0xFE9ABBBCA48F0D9EULL, 0xA4DEB41B0D83DCBFULL, 0x8C7A825C534289F4ULL, 
            0x8F9FD7B4660851FFULL, 0x7773C8F78B996292ULL, 0x4FFFF8B3190A519FULL, 0xD40ADE95BC775F6CULL, 
            0x7240EE6714199440ULL, 0x916C3FB1C39A0609ULL, 0x591DE8070F656F71ULL, 0x302105FC9B26E9AEULL
        },
        {
            0xD67856C298BDFF30ULL, 0x8B207774A8151B98ULL, 0xE2003A6CEC8DE8E1ULL, 0xCF98FD2637A6E10EULL, 
            0x1210E36404C127EBULL, 0xC2B8751850568EB0ULL, 0xEE3551B8A6081E8AULL, 0x1C7433A47F6B488EULL, 
            0x2089F4ED462391E8ULL, 0x280C2D6473CF6874ULL, 0x591BDD4EEA933C7FULL, 0xAE47618A73507E1FULL, 
            0x03467B8DE7B7335BULL, 0x8B672DDDFE6EFB42ULL, 0xD4D0F9D8C5FDAE76ULL, 0x98E93687394C960DULL, 
            0x39F634298535CBDCULL, 0x08EC18293CFAC633ULL, 0x4651CF91EC1D8406ULL, 0x5B69C8EC24D07747ULL, 
            0x8AE441AED2F7DD68ULL, 0x647749CCE4607DD4ULL, 0x1F2FA4DC12984F40ULL, 0x16AE495D228630E7ULL, 
            0x6C24EBF38E5C7C95ULL, 0x811126D1D88D7125ULL, 0x722C5DB03814E1F2ULL, 0x93785518BB1AB518ULL, 
            0x58239CC55A3BDE21ULL, 0xF22F7C4DE57FB76AULL, 0x73D3C3F146CE4CFAULL, 0xE1592AE83A8AD6BFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Kerpal_0006::kPhaseCConstants = {
    0x9E037CB1432BD6AAULL,
    0xB7B348DAE3F67AFAULL,
    0x9AFA64EA1A1DCB85ULL,
    0x9E037CB1432BD6AAULL,
    0xB7B348DAE3F67AFAULL,
    0x9AFA64EA1A1DCB85ULL,
    0x3C40ED228C483660ULL,
    0x539F2BE94045614EULL,
    0xDE,
    0xCA,
    0x12,
    0xE6,
    0x1E,
    0x51,
    0x27,
    0xE4
};

const TwistDomainSaltSet TwistExpander_Kerpal_0006::kPhaseDSalts = {
    {
        {
            0x13295A9D27DAE341ULL, 0x69A9F95171308B7DULL, 0x667CD50BD19C8714ULL, 0x174A2608930DD4DAULL, 
            0x3598E7CA5DA31877ULL, 0x7D87F6EFEBEE415CULL, 0x87A49A9615ABDF83ULL, 0xD4B5509FDC928A4CULL, 
            0xDCAA560B8EBB079AULL, 0xB08C83E8FA554090ULL, 0xE5FFDD893E7ECB44ULL, 0x618EA835F69CE4B2ULL, 
            0xD189276BD32EAC3AULL, 0x63F44C0299FCBFCFULL, 0x56D6EFBB31F8FD3DULL, 0x745C4DB48AB9ECC1ULL, 
            0xE18EB3E0A952D747ULL, 0x3DD58310A9A5654DULL, 0x8B4AE4F498A2A3A2ULL, 0x4A7EA1A42FCCE8AEULL, 
            0x4AA9954589BB9C5EULL, 0x01618559D9F5CBDFULL, 0x62029D42D0136FC5ULL, 0x22010736C9EA6A36ULL, 
            0x09B9641662921E9BULL, 0x769F7B8BD647D7CBULL, 0x3F1D2EAC01819B8AULL, 0xF829595B496B8643ULL, 
            0xD70F783B082B24F3ULL, 0x2AF9F2C160AECA01ULL, 0x03FBA688FD6CA1E2ULL, 0xFBA478A4B5921A46ULL
        },
        {
            0xE878BE982BAB1B9EULL, 0x6ACAF7CA8F5A7795ULL, 0x0615E1E4E1430963ULL, 0x7589EEA9BA4BDE5DULL, 
            0xEF1E590386F87023ULL, 0x40D11D37B69A3E8DULL, 0xA3E501EC97B8E5D7ULL, 0xD16BE5F5B76118D1ULL, 
            0x11FEFF4B159E411AULL, 0x35BF516B9BAB3F42ULL, 0xDF874ACC622415F2ULL, 0x14D20ECBCF6B4211ULL, 
            0x08C235F0B97E37E2ULL, 0x8EA75740284F4ACFULL, 0x3F8DD319A3974E17ULL, 0x2215882AE4E64D50ULL, 
            0xE330CF829C5E309EULL, 0x70F75FBDE35B068EULL, 0x6F63190D1F371710ULL, 0x64B1CF23882C1ED3ULL, 
            0x230FA732A59BA3BEULL, 0x9466D4FB966ADBADULL, 0x16397007C7525FDBULL, 0x7DB889C35B7E3413ULL, 
            0xB8B1EE4D8DD67E5CULL, 0xA3E38A500A95921EULL, 0x137C10B9328E0BB6ULL, 0x5CFEEC2C9353C71BULL, 
            0xC0C7FD699E95BC42ULL, 0xB2307B269D742AB1ULL, 0x19379148EE231EA8ULL, 0xDCE6EEF6D16F8DBFULL
        },
        {
            0x2A5CE4131D02DA9BULL, 0xCA005F6764D8F8BEULL, 0xB9ABA51D5878AF3DULL, 0x28B00D7BF145A489ULL, 
            0xC060531C08A180BDULL, 0xBCCE289596EA21BEULL, 0x0565024F4A2ABE81ULL, 0x0C7F1EC209227710ULL, 
            0x61B39CFEC07FBF69ULL, 0xECCA726A93BBB23AULL, 0x0B0108B031250CA9ULL, 0xBBB9664EE64E180AULL, 
            0x67057FF53069F902ULL, 0x5DF0422CA43E35DEULL, 0xA95A05F3F2CD3AC4ULL, 0xDC7B936F3986C981ULL, 
            0x8BD0F962165A0ADCULL, 0xA45CB407E565B86EULL, 0xC31488C8204AB427ULL, 0x3C515919E27E2E41ULL, 
            0x0073D8715CEB0285ULL, 0x484B1DCD22E0CF41ULL, 0x6643A3B26B59577CULL, 0xFF1EE0FA57590580ULL, 
            0x06B4BB5E2BA883ACULL, 0x2F16E0A9227BA7BEULL, 0x5672ECA592FE7DA6ULL, 0x96D45CCFCB2E4C8EULL, 
            0xAE403934F0353D0DULL, 0x7C6D471A3BC4CD00ULL, 0x1F1D7F0FD1253B06ULL, 0x8A351FAD047492B8ULL
        },
        {
            0x9A9405D11FF44EB6ULL, 0x1FF0870160EFFB0CULL, 0xD87A84EB745D4AF2ULL, 0x7D6A20157BDFF8CBULL, 
            0xD2E5D1C56B082405ULL, 0x94715D43ECDCD521ULL, 0x4975549BA070D770ULL, 0x017458B17CD693D5ULL, 
            0x774319F58E0DF422ULL, 0x1CFDF326DBFB2BBBULL, 0xC27EA6457097A094ULL, 0x19C51B18EC2CC988ULL, 
            0x8F450F1793748F72ULL, 0x4C1850E71E468606ULL, 0x86F94085E238DD3AULL, 0x95DFDA4F4B9F2EE5ULL, 
            0x2EE983C882904E04ULL, 0x5A113FDE03DFCD91ULL, 0x7DE122D7AE4D9ACEULL, 0x0BA4F1E59FE25843ULL, 
            0xF133AF1AEB4BB070ULL, 0xD0AD8256737905F3ULL, 0x39BFCFB60FD19CF4ULL, 0x0AD06ECA7C944A33ULL, 
            0xC25DBA1A88495BBBULL, 0x0D75CFCDE21B76C9ULL, 0xF510B8D3E813AE59ULL, 0x6894E3A0EDBE6583ULL, 
            0x76909692ED982F29ULL, 0x97B3F70998526B39ULL, 0xB7486A6471E85D72ULL, 0x7AF1FEFECBF49526ULL
        },
        {
            0xBC0E69F27A00661CULL, 0x6DA4DA5556E814F6ULL, 0xED8D32BE212D9665ULL, 0x3EECEB0CDF5F36FFULL, 
            0xCA6859D1FF6EABC9ULL, 0xEE4D3731B866D110ULL, 0x53F828ACBC940EE8ULL, 0xE5283E48C5C9AB59ULL, 
            0x0093C5855450F9A6ULL, 0xA3C4EC8A1689DC18ULL, 0x9C18DAACD441776DULL, 0x2EC172660496F708ULL, 
            0x67A6C3F2FC69233BULL, 0x6E0FB7FC0A9FEF41ULL, 0xB9EA7F78CF6AB010ULL, 0xA2F01531255E9124ULL, 
            0xE2F48854E1402E73ULL, 0x6722DD879FB40F75ULL, 0x01EC16120E7A342BULL, 0x1C0BB93859194474ULL, 
            0xD7A3CA687583911AULL, 0x8BE4C84058CD2A55ULL, 0xBCE5E59A2AABB000ULL, 0x7E635E154B1C32FAULL, 
            0x4C6E6863F76274F3ULL, 0x66D35CE92A8CA0F9ULL, 0x9DE10522989EC09BULL, 0xE91F23F838A36F7EULL, 
            0x8F500C9DD2717742ULL, 0xB9C9E10E1B20CC67ULL, 0xD3B68A53F0E8074EULL, 0x3817C7ACA4A4B6CAULL
        },
        {
            0x2B1622F9B487E5A6ULL, 0x43F67C63EC0A250BULL, 0xE0B015BB821A8DC8ULL, 0x808AABC9E5A0D9EDULL, 
            0x02D2D681BB34441AULL, 0x4AFBC23C6E1AE73AULL, 0x447C59C1190C7C54ULL, 0x9EC91415AAD180C7ULL, 
            0xABFCB3B34DB5A88BULL, 0x7CE83F15E432C90EULL, 0x746526A502A7CD32ULL, 0x5BD34F35142DFFD2ULL, 
            0x352DA0E9BC589E9DULL, 0x15909A79923F8207ULL, 0xD3EB403510F32F52ULL, 0x8ECFE33F36BBC967ULL, 
            0x54CBE90E714B7913ULL, 0x74C01C811D0A4837ULL, 0xD229DCF7ED524F55ULL, 0xE86CB4968D42F9E5ULL, 
            0x19AC5E36AEF2F04DULL, 0xC447E9BD7F6C2598ULL, 0x13F21F0B38C48AACULL, 0xF7FEDAFA7073ED7BULL, 
            0x74263479DD0FEE38ULL, 0x256731813256D327ULL, 0x9137DA224EE1FBB4ULL, 0x4A57110829231F05ULL, 
            0x942C0F3FB5BA0522ULL, 0x1501D76BF59E6520ULL, 0x62523B1F837E5AD0ULL, 0x9847352FD6604CEBULL
        }
    },
    {
        {
            0xAF68E9FF9DE5B9E5ULL, 0x7A46DB59F3F45CB6ULL, 0xD99559AFF74F20FDULL, 0x6E2CA568CADD1ABDULL, 
            0x2440458236C4F34EULL, 0xAC80EA57D0B11DE1ULL, 0x9C129AC7A0568A40ULL, 0x85FE4681BBD4520FULL, 
            0x41A2194C46408393ULL, 0xD5D3460120F90300ULL, 0x850EF33039DCB9E0ULL, 0x3F352410D309A9F2ULL, 
            0x6E6073AB1738AE12ULL, 0x8A48731C461772EBULL, 0xD1E3E4939C5B53B2ULL, 0xE816C71D333AED84ULL, 
            0xDE3C539FE3DF43E1ULL, 0x3793B9BC11E48D30ULL, 0xB8499EBD060B13ABULL, 0x5F78AB0DD9A9FC73ULL, 
            0xC9192B0034E56266ULL, 0x9A1B398259AF7B71ULL, 0xCDC4675A654059E6ULL, 0xC4DEC0BA84BF29E9ULL, 
            0x831AAFAB0AFED1ECULL, 0xA06F72384CCC96ECULL, 0x8D5FC0775C682A23ULL, 0xE6D2DB95E0722B71ULL, 
            0x63A60DC276630DBDULL, 0xFBB8EA0C9B7ED7CFULL, 0xF781C23B5CEC4892ULL, 0xA323536F9874F657ULL
        },
        {
            0x2BE88C4EB83FD2D2ULL, 0xB6652510161FB979ULL, 0x249AEE9C257886E8ULL, 0x6ED67E3A4A656AF3ULL, 
            0xD227D1EAA0E03639ULL, 0x42DFC1984230E64CULL, 0x86FDC17A3623D522ULL, 0xB01CC4F8B712C40EULL, 
            0xC391FF8151DFBBE5ULL, 0x46B21888355C54A9ULL, 0x61FD7DBD034353F2ULL, 0xB708EC8588DB976EULL, 
            0xF1D3628F401D46A5ULL, 0xF8C5C079DC2F0E37ULL, 0xCBE78AFB3345A3EDULL, 0xCDAB481FE98EEE4DULL, 
            0x98A75A66E2258885ULL, 0x16EB05AD8E034056ULL, 0xC9AC3A96345B577CULL, 0x03DE656B88A29F9BULL, 
            0x4824B49843CF0D7CULL, 0xE7D5CBBC9BA48583ULL, 0x2B38ECA0C2E3B506ULL, 0xF5E3751A48329861ULL, 
            0x77049DF177D7CE3AULL, 0x7B8F18CF7F591D3FULL, 0x0337BB3155CCC0E8ULL, 0xE78E47A98DB66EC7ULL, 
            0xBB6E987AE61C729BULL, 0x9D04CADCC42ECC95ULL, 0xB05800F7F10DA486ULL, 0xA1567B0F7FFC7D81ULL
        },
        {
            0x442CB57C47358DE5ULL, 0x4C975E52648F7B5DULL, 0xAC1848EEA7D39405ULL, 0x3A4B2B9F5C78FCBDULL, 
            0x0AB8C080AB1A59FAULL, 0xFB603987B743FB6FULL, 0x19BAA80164FADD90ULL, 0x577FB1EF48E5BEDCULL, 
            0x8EF5E114436DF9B2ULL, 0x8224B1AB253227CAULL, 0x3C02B8A62039B9ECULL, 0xEF2F45A04801DF8FULL, 
            0xC32420F1146D99EEULL, 0xFBC306A2BDB4173DULL, 0x4E06C6B682A925F4ULL, 0xE7943198F2C4133BULL, 
            0xBF3A5D1807122C64ULL, 0x84C2A5753E106A0FULL, 0xD43FBF87DB318CCCULL, 0xFCABF4B272C09854ULL, 
            0x65026D9459BB4085ULL, 0xF6D9A0C8FC6FB525ULL, 0xC49D59857FE7F922ULL, 0xB3919C21A5D76385ULL, 
            0x96C9D657D0D8C399ULL, 0x17DCDEF71A7C5EEAULL, 0x1F5D0237A5293F8AULL, 0x09878824FBABFD2FULL, 
            0x511563EF8EED18D5ULL, 0xC345D9AF5361C664ULL, 0xE3966EAE85490308ULL, 0x93A76DB181B8FE96ULL
        },
        {
            0xA5ED000D90F35004ULL, 0x7452E246CDEFE69FULL, 0xA0A7B167809FD59EULL, 0xF305383AE099D0F3ULL, 
            0x8B5A5D007B6D5A31ULL, 0x5890663A066ABE2FULL, 0xE8069CC8FB23A6FAULL, 0x62FCE26AF8C75505ULL, 
            0x5AE8243E93AB4A78ULL, 0xACB3CF64EF7F2DF6ULL, 0xC70E1DF33AC6B0A1ULL, 0x11DB8CA4B77BE2E1ULL, 
            0x0F8C20C7DA313EBDULL, 0xC33D933741E43598ULL, 0x1BD2030181100A47ULL, 0xF4122F800ABDB62FULL, 
            0xE11BDCBD07F5FE6BULL, 0xF77DB3E85B948C70ULL, 0xA9B97DAFD8660784ULL, 0x9918BD1CC8223BB7ULL, 
            0x76F6BEC0E0D7A6DDULL, 0xBD7325C6B70CDA0DULL, 0xD2BA0804279A171EULL, 0x7C0121E5F91A97A0ULL, 
            0xFEB1A8689832FD8EULL, 0x0B407B45E80EA239ULL, 0x994F93BFC2EC7BD3ULL, 0xAF0C2ECC0A81CE9DULL, 
            0xC395F34C798AD2BDULL, 0xE0606E1E177824AAULL, 0xDFAA2E36390F50F7ULL, 0x21F7A565F74D0447ULL
        },
        {
            0x3EDC4A80A61CAD7CULL, 0x732671A211BEDB98ULL, 0x2AD2168B59025D98ULL, 0xE731F32C0B4B70E0ULL, 
            0x73B340CD21185965ULL, 0xA7D4256684EA5E2FULL, 0xC31D42D47F91CDD9ULL, 0xBFA830610949A4C1ULL, 
            0x38B4D2D2B0A6CD4AULL, 0xA342647AE8CBA7F5ULL, 0x5ADB34E1EAE5D3F9ULL, 0x4BFB5247B8AD3306ULL, 
            0x48571B25A53A2FCAULL, 0xDB6F39C44C75CA9FULL, 0xBCA3E7447E5340F4ULL, 0x1E8918109862B4D8ULL, 
            0xCF49418A390D0DF3ULL, 0xDD95DAE25BF06D06ULL, 0xC65F178FC4CC2B2FULL, 0x072374F762780C59ULL, 
            0x203D590B96C1C017ULL, 0xD500393114F540F3ULL, 0xE9B15CF242CD253BULL, 0x1798E7E9B07DD2D8ULL, 
            0xDDFB577F8512BF57ULL, 0x876B4BFE938BAD93ULL, 0xF53E3F51185111DAULL, 0xCA6F85748DE27096ULL, 
            0x3F81E60EFFA71220ULL, 0x6D89F4FA43825D81ULL, 0x67791F8B23731073ULL, 0xE8C20120AEEA6847ULL
        },
        {
            0x853D46667BEF5FEEULL, 0x38EFDF3E0F7A89A6ULL, 0xF09E900661381FA6ULL, 0x39473DB2CFA4CE8CULL, 
            0xFF4E156AFD1E1EA2ULL, 0x7EE54B9D7FB3F54CULL, 0xAF4D1A72A101955EULL, 0x0D963EBCED05E561ULL, 
            0x240A6DAACAE3B51DULL, 0xBA1718910F5BEEE9ULL, 0x35CE0951709320D8ULL, 0xE496C9EEA549CA11ULL, 
            0xF51AAD0082CEF412ULL, 0xA79A81363C2B5003ULL, 0x979554068827D28CULL, 0x3ED4C6B46B9DD7E2ULL, 
            0x7B9EE1F74D15D10EULL, 0xDA4A398C95B51C6BULL, 0xB5D581E006DC381CULL, 0xA684971E97A2E6A3ULL, 
            0xA987DC696B153D80ULL, 0xC8D2FA1F8FBF4B90ULL, 0x8422B411D0652553ULL, 0x3B3FD6696F11035EULL, 
            0x624F8F9BBD731C45ULL, 0x2BBC650B561E5A7DULL, 0x4CC0A30167CAAF28ULL, 0x4D7B1DDB5D463064ULL, 
            0xEF66CA0A8E3DB14CULL, 0xE30C04D118F802E2ULL, 0xF57904C442A345A2ULL, 0x47DA676B2B7EDB38ULL
        }
    },
    {
        {
            0x35B7C4831759CCCFULL, 0x71D066CB8D671083ULL, 0x83A3957852749E58ULL, 0x5976616DB6266056ULL, 
            0x828A29740E46F099ULL, 0x6FFAF29187CD1F9CULL, 0x399ADEB391195D97ULL, 0x0641C08DF9143445ULL, 
            0x971C8298C3712DD3ULL, 0x2D41550485F871EFULL, 0x333A6602E4391B34ULL, 0xF6D44B227CF63611ULL, 
            0xAFE95189922DEFAEULL, 0x8888669780179D25ULL, 0x5D24637651441196ULL, 0x1A171A5B28C47672ULL, 
            0xB1C643609580538FULL, 0x2450A323AF569DA4ULL, 0x00C62BCA89558C2AULL, 0x0201586D11E862ACULL, 
            0xF0C54E1A1410777EULL, 0x4BE8724F873D0B93ULL, 0x45223D4BBCAD9C29ULL, 0x54DF8B4C00582F76ULL, 
            0x1CF3F1B4E875BF87ULL, 0xBC052E83F8079318ULL, 0x4074D296863E374BULL, 0xE11FB9E0EFAB74FDULL, 
            0xC21E77CC0A2F1912ULL, 0x064E818CDE3589DBULL, 0xBCD3E825B02A6194ULL, 0x221A33C248EF4541ULL
        },
        {
            0xA188BE9C4E0BDD06ULL, 0x919D6509B3115C08ULL, 0x1DDCCD27BBE12210ULL, 0x1031E46A0549A469ULL, 
            0xFD50A663BBACBC13ULL, 0x73A8554BB7C777DEULL, 0x15FFE0B07EF59037ULL, 0xE0947DBE91C364C9ULL, 
            0xFB098BD0D966DEDDULL, 0x5DDCCC890E61DE20ULL, 0xBC85381EDA3CA2ABULL, 0x2BAD9387137D9C66ULL, 
            0x505E3B39449B9100ULL, 0x0A6B69FBC2F9F9A4ULL, 0x9C4670B579A64997ULL, 0xE703485B585B215CULL, 
            0x99C9073802C0DD73ULL, 0x3CE296A3AA2EC943ULL, 0x9612BDAFB0D7822BULL, 0x11F1D763A9163D03ULL, 
            0xDD4EEB02BDFEDEDDULL, 0x342936F73FCC7BFDULL, 0x379FAE33AB1EBFCAULL, 0xB58C353422936A49ULL, 
            0x54F13D15AA4CD908ULL, 0x4C631AF027D7F95EULL, 0xBA4B335E2A233576ULL, 0xB3C3D0EB0DDEFD0CULL, 
            0xA78A378B779EDDADULL, 0x0B8745B9A9C6FD53ULL, 0xCEDD483C028EBC25ULL, 0x801AC67B8F54D20FULL
        },
        {
            0x911D4C95C0EE7A99ULL, 0x8F415F8EA51CC445ULL, 0x7077529DEA1D5FB4ULL, 0xD7987D8B33010B94ULL, 
            0xD73C17C67C3C4565ULL, 0xE37CCB92F91C5C6FULL, 0xB6C95517936A8C8DULL, 0x21F2053D9979999FULL, 
            0xC84375750F90386FULL, 0x8447DA735565FFB4ULL, 0x26FE794841AAB784ULL, 0xBC3C6208A3C140B0ULL, 
            0x3ACB78A22243969EULL, 0x7376AAEFC7353825ULL, 0x77CEF3C9EE77711CULL, 0x1826E9E6A1F736ADULL, 
            0xE6C4B38CDCE388E2ULL, 0x50052C9955149E22ULL, 0xB33520019F537CE3ULL, 0x35E73376C65D6F06ULL, 
            0x02DDAFF8C1CF3FB9ULL, 0x427285DB7FD7397FULL, 0x06B9C654CA11EB5CULL, 0x54403BEDFA38BE0AULL, 
            0x6A5A8C001F3E3AB3ULL, 0x8659F709AE5EE4AEULL, 0xBAE787572E0FFA89ULL, 0x475BB24D8EF8E236ULL, 
            0xEA2EE7D48D57DF5DULL, 0x0900960DF6B9394FULL, 0xAA78FD42E32A2D5DULL, 0x9B789CD2FE1B9D08ULL
        },
        {
            0xAC95E119EA170C2CULL, 0xE84589350294D9B1ULL, 0xB89FDFE3B8D12E6DULL, 0x57CF011AD5C8A03BULL, 
            0x2F33CC035F06D92EULL, 0x46230EF178F5E557ULL, 0x3960549D2018C0CBULL, 0x9631B9D56C7F18CCULL, 
            0x094345F9AD58D399ULL, 0x3B49D9F28E60F044ULL, 0x8AF905FEA88048B3ULL, 0x2C9A63CA363556DAULL, 
            0x2E4839CA8915D2D1ULL, 0xF5FF3E184CE0BC31ULL, 0xA0B0DFB56C71FF5EULL, 0x76E805F1D9CA8538ULL, 
            0x2860684F3F09D140ULL, 0xAF41D5DA53F3F1FEULL, 0xBCAE79A4D0EDED05ULL, 0xE515181229484C8CULL, 
            0x54898782B1F9A03EULL, 0x72494D52575D5AE1ULL, 0xB73820B4C1B15FE5ULL, 0x508A5E5FAC38DEE3ULL, 
            0xDB8D75AD31D9C907ULL, 0xB736AC425419951AULL, 0x9F9A2E838A606752ULL, 0x2FBE7177273BB79DULL, 
            0xCE246849ECAD3648ULL, 0x290241C26BD9ACDFULL, 0x93606EAB5EBA8633ULL, 0xBBDD1E68517120B0ULL
        },
        {
            0x72811B319BA4D939ULL, 0x4375BA857D20F70DULL, 0x24CE73B36B1A5BA7ULL, 0xECAB9D99C7DE06C0ULL, 
            0x0F0230C7D71D22B6ULL, 0xD3427731045B7624ULL, 0x120389B423E5F257ULL, 0x7B79A4BC0178285FULL, 
            0x0210EABE2E901E17ULL, 0xD48628327E3035AFULL, 0x16BFA8BBCB96F218ULL, 0x0A800EB166A9B5CDULL, 
            0xB9D5B81D19E77B22ULL, 0x18D1E2B4272F47A4ULL, 0xEA00469F9CA39807ULL, 0xB1FBF61EA4AD8B15ULL, 
            0x37C82051981AA6A9ULL, 0x7717C745E70DA673ULL, 0x92947ED58E730E3CULL, 0x6332CE5FCF29ED14ULL, 
            0xE47E66A4583B5ECEULL, 0x70D2A7C71112A5A2ULL, 0xCB7ACF5CDF142AE1ULL, 0x82785C11C57C08F2ULL, 
            0xB51076D8AB33E929ULL, 0xC5979A08F249842CULL, 0x82B377CECFEF3478ULL, 0xB005DE5A45845215ULL, 
            0xCC23491B05F6967FULL, 0xF63BAB938FF3588EULL, 0x21276B30BA2504BEULL, 0xC3C34691925F481AULL
        },
        {
            0xD6579548AABF1A8CULL, 0xD2E12973460F3605ULL, 0x29EA49FCF5772C48ULL, 0x46D97137FFC68A41ULL, 
            0x201C1E60EEFA3D0AULL, 0x18613B7AD9CA1B5AULL, 0x531B480F7D6B4F99ULL, 0x3DBC4C9C22879051ULL, 
            0x0D9E7D34D06E9AA2ULL, 0x74B15B33E01222B3ULL, 0x63709F323589FE99ULL, 0xEF7C68E2F7CD4D30ULL, 
            0xA7DCA6CB1CF5BEC4ULL, 0xA80CB5154F6DAE7DULL, 0x265A7F9C9D781A87ULL, 0xD24C5CC5AE826F58ULL, 
            0x6F26D9D0BCADEFA5ULL, 0x12A7557CD414FACFULL, 0x5B250FEF710F6F12ULL, 0x3E87A599757A94A3ULL, 
            0xED21E0B5A0CB4578ULL, 0x273015C78B3E2187ULL, 0x7F372A39FA6990B0ULL, 0xD5400EED9A29D4C0ULL, 
            0xC5971131D6C8DBE9ULL, 0x0071E170BF82C7E2ULL, 0x65E19FC764AD97D8ULL, 0x00D765346F2FFAFFULL, 
            0x9D02DDB1E200438AULL, 0x1540A5408744594AULL, 0x2540FEEFFB823520ULL, 0xAAB563E37EC75CA9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Kerpal_0006::kPhaseDConstants = {
    0xD74D166341BA77DCULL,
    0x67098E7B4D668F77ULL,
    0x848D70B97368AE81ULL,
    0xD74D166341BA77DCULL,
    0x67098E7B4D668F77ULL,
    0x848D70B97368AE81ULL,
    0x0A193973840A7F6FULL,
    0x4D1288EA5DE2B36EULL,
    0x63,
    0xF5,
    0xBA,
    0x33,
    0xE5,
    0x39,
    0xFA,
    0x1B
};

