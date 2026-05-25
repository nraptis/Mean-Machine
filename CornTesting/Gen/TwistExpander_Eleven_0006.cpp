#include "TwistExpander_Eleven_0006.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix64.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmConstants.hpp"

#include <cstring>

TwistExpander_Eleven_0006::TwistExpander_Eleven_0006()
: TwistExpander() {

}

void TwistExpander_Eleven_0006::KDF(std::uint64_t pNonce,
                                TwistDomainConstants *pConstants,
                                TwistDomainSaltSet *pDomainSaltSet,
                                TwistDomainSBoxSet *pDomainSBoxSet) {
    KDF_A(pNonce, pConstants, pDomainSaltSet, pDomainSBoxSet);
}

void TwistExpander_Eleven_0006::KDF_A(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  TwistDomainSBoxSet *pDomainSBoxSet) {
    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pDomainSBoxSet);
    TwistWorkSpace *pWorkspace = mWorkspace;
    if ((pWorkspace == nullptr) || (mSource == nullptr) || (mDest == nullptr) ||
        (pConstants == nullptr) || (pDomainSaltSet == nullptr) || (pDomainSBoxSet == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aSource = mSource;
    [[maybe_unused]] std::uint8_t *aDestination = mDest;
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
    [[maybe_unused]] std::uint8_t *mSBoxA = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(30));
    [[maybe_unused]] std::uint8_t *mSBoxB = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(31));
    [[maybe_unused]] std::uint8_t *mSBoxC = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(32));
    [[maybe_unused]] std::uint8_t *mSBoxD = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(33));
    [[maybe_unused]] std::uint8_t *mSBoxE = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(34));
    [[maybe_unused]] std::uint8_t *mSBoxF = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(35));
    [[maybe_unused]] std::uint8_t *mSBoxG = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(36));
    [[maybe_unused]] std::uint8_t *mSBoxH = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(37));
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkspace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkspace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkspace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkspace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aExpandLaneE = pWorkspace->mExpansionLaneE;
    [[maybe_unused]] std::uint8_t *aExpandLaneF = pWorkspace->mExpansionLaneF;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneE = pWorkspace->mWorkLaneE;
    [[maybe_unused]] std::uint8_t *aWorkLaneF = pWorkspace->mWorkLaneF;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkspace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkspace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkspace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkspace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneE = pWorkspace->mOperationLaneE;
    [[maybe_unused]] std::uint8_t *aOperationLaneF = pWorkspace->mOperationLaneF;
    [[maybe_unused]] std::uint8_t *aMaskLaneA = pWorkspace->mMaskLaneA;
    [[maybe_unused]] std::uint8_t *aMaskLaneB = pWorkspace->mMaskLaneB;
    [[maybe_unused]] std::size_t *aIndexList256A = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(190)));
    [[maybe_unused]] std::size_t *aIndexList256B = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(191)));
    [[maybe_unused]] std::size_t *aIndexList256C = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(192)));
    [[maybe_unused]] std::size_t *aIndexList256D = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(193)));
    [[maybe_unused]] std::size_t *aIndexList256E = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(194)));
    [[maybe_unused]] std::size_t *aIndexList256F = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(195)));
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledB = &(pWorkspace->mMaskBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadA = &(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadB = &(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteB = &(pWorkspace->mMaskBoxB[0][0]);
    std::uint64_t aPrevious = 0; std::uint64_t aIngress = 0; std::uint64_t aCross = 0; std::uint64_t aScatter = 0;
    std::uint64_t aCarry = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    std::uint64_t aWandererA = 0; std::uint64_t aWandererB = 0; std::uint64_t aWandererC = 0; std::uint64_t aWandererD = 0;
    std::uint64_t aWandererE = 0; std::uint64_t aWandererF = 0; std::uint64_t aWandererG = 0; std::uint64_t aWandererH = 0;
    std::uint64_t aWandererI = 0; std::uint64_t aWandererJ = 0; std::uint64_t aWandererK = 0;

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
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixSchemeA = pConstants->mMatrixSchemeA;
    std::uint8_t aDomainWordMatrixSchemeB = pConstants->mMatrixSchemeB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;

    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 46U) ^ RotL64(aNonceByteB, 23U)) ^ RotL64(aNonceByteC, 13U));
            aIngress = aIngress ^ (RotL64(aSource[((aIndex + 6503U)) & S_BLOCK1], 57U) ^ RotL64(aSource[((aIndex + 9223U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 53U) ^ RotL64(aNonceByteE, 12U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 14961U)) & S_BLOCK1], 41U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 11129U)) & S_BLOCK1], 3U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 35U) + RotL64(aCross, 20U)) ^ (RotL64(aCarry, 51U) ^ RotL64(aIngress, 3U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = (((aWandererB + RotL64(aCross, 13U)) + RotL64(aCarry, 51U)) + 5697928251815176134U) + RotL64(aNonceByteD, 31U);
            aOrbiterC = ((aWandererK + RotL64(aIngress, 51U)) + RotL64(aCarry, 5U)) + 337587740689259575U;
            aOrbiterD = (((aWandererG + RotL64(aScatter, 58U)) + RotL64(aCarry, 29U)) + 4927686903263973950U) + aOrbiterAssignSaltB[((aIndex + 2246U)) & S_SALT1];
            aOrbiterB = (aWandererF + RotL64(aPrevious, 3U)) + 3742409032569801033U;
            aOrbiterE = (aWandererJ + RotL64(aCross, 39U)) + 1608092659172197650U;
            aOrbiterG = (aWandererH + RotL64(aScatter, 53U)) + 15848744267145717509U;
            aOrbiterF = (aWandererI + RotL64(aPrevious, 23U)) + 15300174177963339253U;
            aOrbiterI = (aWandererA + RotL64(aIngress, 35U)) + 14162868453323648628U;
            aOrbiterH = (aWandererE + RotL64(aCross, 19U)) + 12020167069983729869U;
            aOrbiterJ = (aWandererC + RotL64(aIngress, 60U)) + 16259538291658723956U;
            aOrbiterK = (((aWandererD + RotL64(aScatter, 47U)) + 8516686212464112245U) + aOrbiterAssignSaltA[((aIndex + 1327U)) & S_SALT1]) + RotL64(aNonceByteG, 37U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 3722184575520553132U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 5663609293306386784U;
            aOrbiterD = RotL64((aOrbiterD * 14364218128780764749U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 15265344442454471986U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 3050323350098829515U;
            aOrbiterG = RotL64((aOrbiterG * 5890624677162388135U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 1093356813820599238U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 15167726103772238440U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 5323U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 5719466863561311069U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 15170797965325981472U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterH) ^ 17826286701992981628U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 2269U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 11186808881726573677U), 5U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterD) + 14710892030473425181U) + RotL64(aNonceByteC, 8U);
            aOrbiterF = ((aOrbiterF ^ aOrbiterK) ^ 397194787697553904U) ^ RotL64(aNonceByteF, 13U);
            aOrbiterF = RotL64((aOrbiterF * 14368930300818752833U), 23U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 1273724124862533034U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 13018397560392545616U;
            aOrbiterH = RotL64((aOrbiterH * 4644812473262395329U), 53U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 9638716186445643730U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterE) ^ 7255587739807843785U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 1609U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 6055682981584011189U), 43U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 9272350563697399628U;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 1040729335295009339U;
            aOrbiterC = RotL64((aOrbiterC * 17825687660830291443U), 51U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 12128124729613601747U;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 2285238815562202219U;
            aOrbiterE = RotL64((aOrbiterE * 15398840993074390573U), 39U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 6339113298619163493U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 5911895708485037040U;
            aOrbiterI = RotL64((aOrbiterI * 3271006139923200439U), 37U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 7601399508218901328U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterG) ^ 5697928251815176134U) ^ aOrbiterUpdateSaltA[((aIndex + 7117U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 8184257916861355735U), 29U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterC, 3U);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterJ, 56U));
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterH, 37U));
            aIngress = aIngress + (RotL64(aOrbiterK, 13U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterD, 47U));
            aIngress = aIngress + RotL64(aOrbiterI, 11U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((((RotL64(aScatter, 14U) + RotL64(aOrbiterB, 51U)) + aOrbiterG) + RotL64(aNonceByteH, 21U)) + aWandererUpdateSaltB[((aIndex + 7886U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 23U) + aOrbiterA) + RotL64(aOrbiterI, 60U));
            aWandererC = aWandererC + ((RotL64(aIngress, 47U) + RotL64(aOrbiterE, 41U)) + aOrbiterJ);
            aWandererD = aWandererD ^ (((RotL64(aCross, 53U) + aOrbiterH) + RotL64(aOrbiterB, 5U)) + RotL64(aNonceByteB, 19U));
            aWandererE = aWandererE + ((RotL64(aPrevious, 35U) + RotL64(aOrbiterK, 35U)) + aOrbiterA);
            aWandererF = aWandererF ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterC, 23U)) + aOrbiterE);
            aWandererG = aWandererG + ((RotL64(aScatter, 29U) + RotL64(aOrbiterJ, 11U)) + aOrbiterG);
            aWandererH = aWandererH ^ ((RotL64(aIngress, 37U) + aOrbiterI) + RotL64(aOrbiterF, 29U));
            aWandererI = aWandererI + ((((RotL64(aCross, 27U) + RotL64(aOrbiterG, 46U)) + aOrbiterI) + RotL64(aCarry, 51U)) + aWandererUpdateSaltA[((aIndex + 7445U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 56U) + RotL64(aOrbiterF, 57U)) + aOrbiterJ);
            aWandererK = aWandererK + (((RotL64(aPrevious, 41U) + aOrbiterH) + RotL64(aOrbiterD, 39U)) + RotL64(aCarry, 57U));
            //
            aCarry = aCarry + (RotL64(aWandererC, 48U) ^ aWandererF);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererJ, 13U));
            aCarry = aCarry + (RotL64(aWandererI, 43U) ^ aWandererH);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererD, 39U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererE, 26U));
            aCarry = aCarry + RotL64(aWandererB, 53U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 41U) ^ RotL64(aNonceByteB, 13U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 724U)) & S_BLOCK1], 5U) ^ RotL64(aSource[((aIndex + 5U)) & S_BLOCK1], 58U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 27U) ^ RotL64(aNonceByteD, 57U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 13294U)) & S_BLOCK1], 41U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 10184U)) & S_BLOCK1], 14U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 10U) ^ RotL64(aIngress, 41U)) + (RotL64(aCross, 57U) + RotL64(aPrevious, 23U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = ((aWandererB + RotL64(aCross, 27U)) + 10336802574069791273U) + RotL64(aNonceByteE, 34U);
            aOrbiterE = (aWandererF + RotL64(aIngress, 41U)) + 169025388197058936U;
            aOrbiterA = (aWandererK + RotL64(aScatter, 37U)) + 6541354188379168846U;
            aOrbiterI = ((aWandererJ + RotL64(aPrevious, 46U)) + RotL64(aCarry, 37U)) + 16223920526599306104U;
            aOrbiterK = (((aWandererD + RotL64(aScatter, 23U)) + RotL64(aCarry, 29U)) + 12756613707692514808U) + aOrbiterAssignSaltA[(((31U - aIndex) + 6875U)) & S_SALT1];
            aOrbiterH = ((aWandererG + RotL64(aPrevious, 39U)) + 5082475548176484035U) + aOrbiterAssignSaltB[(((31U - aIndex) + 3880U)) & S_SALT1];
            aOrbiterF = (aWandererI + RotL64(aCross, 53U)) + 4907435526952698526U;
            aOrbiterC = (((aWandererE + RotL64(aIngress, 51U)) + RotL64(aCarry, 19U)) + 14236627073831834337U) + RotL64(aNonceByteH, 53U);
            aOrbiterJ = (aWandererA + RotL64(aPrevious, 19U)) + 11502511046130497584U;
            aOrbiterB = (aWandererH + RotL64(aCross, 56U)) + 3679044835550219497U;
            aOrbiterD = (aWandererC + RotL64(aIngress, 21U)) + 11254838916686736746U;
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 10582608424233200966U) + RotL64(aNonceByteF, 27U);
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 10449735026385340313U;
            aOrbiterA = RotL64((aOrbiterA * 7363770199734997411U), 13U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 4628253464169957835U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 17664454668473204465U;
            aOrbiterE = RotL64((aOrbiterE * 4234720298731378527U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 3798386391743884889U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 1379331161819246587U;
            aOrbiterK = RotL64((aOrbiterK * 13086160171095077295U), 39U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 9816600392407327227U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 16781971616348376878U;
            aOrbiterF = RotL64((aOrbiterF * 12503867584828289879U), 11U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterG) + 4807797577690520554U) + aOrbiterUpdateSaltB[((aIndex + 5494U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterB) ^ 2492057261148595922U) ^ aOrbiterUpdateSaltC[((aIndex + 7404U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 9453302540675483005U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 7909676419643119585U;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 256053568910383007U;
            aOrbiterG = RotL64((aOrbiterG * 11965085163352053161U), 5U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 16179914439220412472U;
            aOrbiterI = (((aOrbiterI ^ aOrbiterA) ^ 3968867762761955845U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 6311U)) & S_SALT1]) ^ RotL64(aNonceByteG, 49U);
            aOrbiterI = RotL64((aOrbiterI * 7473632378251893139U), 3U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 7474832923901283742U;
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 4736994731050735779U;
            aOrbiterH = RotL64((aOrbiterH * 9839654409121414047U), 19U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 596484364660389193U;
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 13822222274464306169U;
            aOrbiterC = RotL64((aOrbiterC * 1723502278319885511U), 37U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 16307920280681985443U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 3505106171801702915U;
            aOrbiterB = RotL64((aOrbiterB * 8479675421552861243U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 4987142580981135150U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 10336802574069791273U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 271U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 2670706512498539705U), 21U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterG, 51U);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterK, 34U));
            aIngress = aIngress + (RotL64(aOrbiterJ, 11U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterH, 47U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterF, 39U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterB, 53U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aCross, 11U) + RotL64(aOrbiterG, 51U)) + aOrbiterA);
            aWandererB = aWandererB + ((((RotL64(aIngress, 28U) + aOrbiterD) + RotL64(aOrbiterF, 3U)) + RotL64(aNonceByteC, 31U)) + aWandererUpdateSaltA[((aIndex + 3635U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 3U) + RotL64(aOrbiterF, 47U)) + aOrbiterH);
            aWandererD = aWandererD + (((RotL64(aPrevious, 35U) + aOrbiterG) + RotL64(aOrbiterI, 21U)) + RotL64(aCarry, 39U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 21U) + aOrbiterJ) + RotL64(aOrbiterA, 57U));
            aWandererF = aWandererF + ((RotL64(aScatter, 43U) + aOrbiterH) + RotL64(aOrbiterE, 44U));
            aWandererG = aWandererG ^ ((((RotL64(aPrevious, 19U) + aOrbiterI) + RotL64(aOrbiterD, 23U)) + RotL64(aNonceByteB, 43U)) + aWandererUpdateSaltB[(((31U - aIndex) + 7086U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aCross, 47U) + RotL64(aOrbiterC, 53U)) + aOrbiterF);
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 41U) + RotL64(aOrbiterD, 29U)) + aOrbiterK);
            aWandererJ = aWandererJ + (((RotL64(aCross, 6U) + RotL64(aOrbiterB, 14U)) + aOrbiterD) + RotL64(aCarry, 21U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 23U) + RotL64(aOrbiterJ, 37U)) + aOrbiterG);
            //
            aCarry = aCarry + (RotL64(aWandererA, 6U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererK, 19U) ^ aWandererI);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererD, 53U));
            aCarry = aCarry + (RotL64(aWandererC, 41U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererH, 50U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererF, 39U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 13U) ^ RotL64(aNonceByteB, 43U)) ^ RotL64(aNonceByteC, 3U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 11939U)) & S_BLOCK1], 26U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 6364U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 5U) ^ RotL64(aNonceByteE, 35U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 8901U)) & S_BLOCK1], 18U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 12093U)) & S_BLOCK1], 57U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 51U) + RotL64(aPrevious, 35U)) + (RotL64(aCarry, 23U) ^ RotL64(aIngress, 4U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterJ = (aWandererF + RotL64(aPrevious, 51U)) + 11274974230580265396U;
            aOrbiterH = (aWandererH + RotL64(aIngress, 13U)) + 16658438747342741547U;
            aOrbiterG = ((aWandererC + RotL64(aScatter, 30U)) + 16612986966106053844U) + aOrbiterAssignSaltB[((aIndex + 2390U)) & S_SALT1];
            aOrbiterE = (aWandererK + RotL64(aCross, 21U)) + 9329502236843231290U;
            aOrbiterC = (aWandererD + RotL64(aIngress, 11U)) + 14088261356708344656U;
            aOrbiterB = (((aWandererB + RotL64(aScatter, 39U)) + RotL64(aCarry, 57U)) + 13692608802007789581U) + RotL64(aNonceByteF, 31U);
            aOrbiterK = ((aWandererE + RotL64(aPrevious, 37U)) + RotL64(aCarry, 27U)) + 6824473946645682398U;
            aOrbiterI = ((aWandererG + RotL64(aCross, 18U)) + 2072915876348570040U) + RotL64(aNonceByteC, 8U);
            aOrbiterF = ((aWandererA + RotL64(aIngress, 27U)) + 7420507753044460759U) + aOrbiterAssignSaltA[((aIndex + 6841U)) & S_SALT1];
            aOrbiterD = ((aWandererJ + RotL64(aCross, 5U)) + RotL64(aCarry, 39U)) + 4677557318688502593U;
            aOrbiterA = (aWandererI + RotL64(aScatter, 23U)) + 15081678577055628459U;
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 7026792817486507482U) + aOrbiterUpdateSaltD[((aIndex + 8123U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 14871665922943969918U;
            aOrbiterG = RotL64((aOrbiterG * 694073180313083145U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 6807734532159292872U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 17882797335141303280U;
            aOrbiterB = RotL64((aOrbiterB * 15439872930381050291U), 21U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterI) + 9233542707022629190U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 1000U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 1205501586581350876U;
            aOrbiterH = RotL64((aOrbiterH * 2596053290311090589U), 11U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 10878718669747466677U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterF) ^ 8066049063548639241U) ^ aOrbiterUpdateSaltC[((aIndex + 8048U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 3031382633089381605U), 39U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 861295180226875235U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 9134969787937288583U;
            aOrbiterI = RotL64((aOrbiterI * 7565008208670843555U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 6726642007159809594U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 8061661744643240470U) ^ RotL64(aNonceByteB, 27U);
            aOrbiterD = RotL64((aOrbiterD * 6703498926835391813U), 3U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 13541412083111962884U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 8617442758729315637U;
            aOrbiterJ = RotL64((aOrbiterJ * 15471862889276160953U), 41U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 16884403561131293362U) + RotL64(aNonceByteH, 11U);
            aOrbiterE = (aOrbiterE ^ aOrbiterH) ^ 9490680911678221233U;
            aOrbiterE = RotL64((aOrbiterE * 15988763830018001033U), 51U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 10486145044311386738U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 10200001044821063684U;
            aOrbiterK = RotL64((aOrbiterK * 16149790736141571017U), 19U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 6997073594007878034U;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 13585783612009989767U;
            aOrbiterF = RotL64((aOrbiterF * 11425303157774550449U), 27U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 3847846040256340653U) + aOrbiterUpdateSaltB[((aIndex + 797U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 11274974230580265396U;
            aOrbiterA = RotL64((aOrbiterA * 13970270689108369205U), 13U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterF, 57U);
            aIngress = aIngress + (RotL64(aOrbiterB, 13U) ^ aOrbiterJ);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterG, 51U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterA, 60U));
            aIngress = aIngress + (RotL64(aOrbiterD, 21U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterH, 27U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aCross, 44U) + aOrbiterE) + RotL64(aOrbiterC, 53U)) + RotL64(aNonceByteD, 35U));
            aWandererB = aWandererB ^ ((RotL64(aIngress, 47U) + aOrbiterD) + RotL64(aOrbiterH, 34U));
            aWandererC = aWandererC + ((RotL64(aScatter, 37U) + RotL64(aOrbiterH, 13U)) + aOrbiterJ);
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 29U) + RotL64(aOrbiterB, 27U)) + aOrbiterG) + RotL64(aNonceByteG, 3U));
            aWandererE = aWandererE + ((RotL64(aIngress, 40U) + aOrbiterI) + RotL64(aOrbiterK, 47U));
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 23U) + RotL64(aOrbiterF, 3U)) + aOrbiterA);
            aWandererG = aWandererG + ((RotL64(aCross, 19U) + aOrbiterK) + RotL64(aOrbiterB, 43U));
            aWandererH = aWandererH ^ ((RotL64(aScatter, 57U) + RotL64(aOrbiterC, 23U)) + aOrbiterF);
            aWandererI = aWandererI + (((RotL64(aPrevious, 5U) + RotL64(aOrbiterC, 19U)) + aOrbiterH) + RotL64(aCarry, 27U));
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 21U) + aOrbiterK) + RotL64(aOrbiterF, 21U)) + aWandererUpdateSaltA[(((31U - aIndex) + 5560U)) & S_SALT1]);
            aWandererK = aWandererK + ((((RotL64(aIngress, 3U) + aOrbiterC) + RotL64(aOrbiterI, 58U)) + RotL64(aCarry, 41U)) + aWandererUpdateSaltB[(((31U - aIndex) + 6443U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererJ, 57U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererI, 28U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererD, 13U) ^ aWandererB);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererE, 11U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererC, 39U));
            aCarry = aCarry + RotL64(aWandererH, 42U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 53U) ^ RotL64(aNonceByteB, 21U)) ^ RotL64(aNonceByteC, 29U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 12520U)) & S_BLOCK1], 39U) ^ RotL64(aExpandLaneB[((aIndex + 11259U)) & S_BLOCK1], 6U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 5U) ^ RotL64(aNonceByteE, 58U)) ^ RotL64(aNonceByteF, 27U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 14904U)) & S_BLOCK1], 47U) ^ RotL64(aSource[((aIndex + 10056U)) & S_BLOCK1], 39U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 39U) + RotL64(aPrevious, 57U)) + (RotL64(aIngress, 27U) ^ RotL64(aCross, 14U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = ((aWandererD + RotL64(aPrevious, 50U)) + 12775735908960052604U) + aOrbiterAssignSaltA[(((31U - aIndex) + 4309U)) & S_SALT1];
            aOrbiterK = ((aWandererE + RotL64(aIngress, 5U)) + 11791373812080296887U) + RotL64(aNonceByteE, 48U);
            aOrbiterJ = (((aWandererI + RotL64(aScatter, 39U)) + RotL64(aCarry, 19U)) + 5537362877706057303U) + aOrbiterAssignSaltB[((aIndex + 2333U)) & S_SALT1];
            aOrbiterE = ((aWandererA + RotL64(aCross, 37U)) + 2023912048504189380U) + RotL64(aNonceByteA, 53U);
            aOrbiterD = (aWandererC + RotL64(aIngress, 54U)) + 17668828109963766893U;
            aOrbiterI = (aWandererG + RotL64(aPrevious, 35U)) + 558908629933941224U;
            aOrbiterC = (aWandererF + RotL64(aScatter, 11U)) + 1479633119685446888U;
            aOrbiterH = (aWandererB + RotL64(aCross, 43U)) + 15460320397843364063U;
            aOrbiterB = ((aWandererH + RotL64(aIngress, 47U)) + RotL64(aCarry, 3U)) + 10059749397555469054U;
            aOrbiterG = (aWandererK + RotL64(aPrevious, 57U)) + 9987633811929693924U;
            aOrbiterA = ((aWandererJ + RotL64(aCross, 3U)) + RotL64(aCarry, 13U)) + 10087337844580228269U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 4446204415503364254U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 15106063243302192717U;
            aOrbiterJ = RotL64((aOrbiterJ * 13273756657334709803U), 41U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 9430197906134676162U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterK) ^ 1226048679997253363U) ^ aOrbiterUpdateSaltC[((aIndex + 5657U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 14247538885252664127U), 13U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 10611580584157624739U;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 3137391249289641509U;
            aOrbiterI = RotL64((aOrbiterI * 5462682413239873181U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 9327201928815412810U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 7890659377013147073U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 627U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 13827717178378062047U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 10675114832750356941U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterD) ^ 8804440385852327267U) ^ aOrbiterUpdateSaltB[((aIndex + 4881U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 8520671775587260601U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 12871947817782057116U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 11015991745792051390U) ^ RotL64(pNonce, 61U);
            aOrbiterB = RotL64((aOrbiterB * 17152451500505815031U), 39U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 6320437975845673731U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 702457937087191287U;
            aOrbiterG = RotL64((aOrbiterG * 17491257114676739589U), 51U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterB) + 16629064896250312921U) + RotL64(aNonceByteF, 51U);
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 6054107387816339103U;
            aOrbiterA = RotL64((aOrbiterA * 6983767878966747219U), 37U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 13274874838094190290U;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 12211422735294360321U;
            aOrbiterF = RotL64((aOrbiterF * 5113738196151089817U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 15338616110718583619U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterG) ^ 1475787183754511373U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 3014U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 10904607643785840003U), 43U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 15486810401396777742U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 12775735908960052604U;
            aOrbiterE = RotL64((aOrbiterE * 7478156942468930207U), 5U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterF, 18U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterD, 39U));
            aIngress = aIngress + (RotL64(aOrbiterE, 5U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterH, 47U) ^ aOrbiterA);
            aIngress = aIngress + (RotL64(aOrbiterK, 29U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterI, 10U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aScatter, 3U) + RotL64(aOrbiterD, 50U)) + aOrbiterG);
            aWandererB = aWandererB + ((((RotL64(aIngress, 51U) + RotL64(aOrbiterE, 47U)) + aOrbiterG) + RotL64(aCarry, 37U)) + aWandererUpdateSaltA[((aIndex + 5660U)) & S_SALT1]);
            aWandererC = aWandererC ^ (((RotL64(aCross, 57U) + aOrbiterI) + RotL64(aOrbiterC, 35U)) + RotL64(aNonceByteH, 57U));
            aWandererD = aWandererD + ((((RotL64(aPrevious, 13U) + RotL64(aOrbiterF, 11U)) + aOrbiterC) + RotL64(aCarry, 23U)) + RotL64(aNonceByteG, 55U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 28U) + RotL64(aOrbiterB, 27U)) + aOrbiterF);
            aWandererF = aWandererF + ((RotL64(aPrevious, 23U) + RotL64(aOrbiterJ, 23U)) + aOrbiterH);
            aWandererG = aWandererG ^ ((RotL64(aScatter, 41U) + aOrbiterG) + RotL64(aOrbiterA, 30U));
            aWandererH = aWandererH + (((RotL64(aIngress, 19U) + aOrbiterA) + RotL64(aOrbiterI, 3U)) + aWandererUpdateSaltB[(((31U - aIndex) + 1746U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 47U) + RotL64(aOrbiterK, 53U)) + aOrbiterI);
            aWandererJ = aWandererJ + ((RotL64(aIngress, 44U) + aOrbiterD) + RotL64(aOrbiterJ, 39U));
            aWandererK = aWandererK ^ ((RotL64(aCross, 5U) + aOrbiterK) + RotL64(aOrbiterE, 37U));
            //
            aCarry = aCarry + (RotL64(aWandererD, 56U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererE, 41U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererA, 43U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererF, 11U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererG, 13U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererC, 20U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 39U) ^ RotL64(aNonceByteB, 58U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 8721U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 7073U)) & S_BLOCK1], 23U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 52U) ^ RotL64(aNonceByteD, 39U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 1583U)) & S_BLOCK1], 27U) ^ RotL64(aExpandLaneA[((aIndex + 9063U)) & S_BLOCK1], 3U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 39U) + RotL64(aCarry, 4U)) ^ (RotL64(aPrevious, 51U) ^ RotL64(aCross, 27U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterD = ((aWandererJ + RotL64(aScatter, 41U)) + 17264605017518259932U) + RotL64(aNonceByteF, 52U);
            aOrbiterA = ((aWandererD + RotL64(aPrevious, 11U)) + RotL64(aCarry, 41U)) + 15209184354580778643U;
            aOrbiterB = ((aWandererE + RotL64(aIngress, 5U)) + RotL64(aCarry, 57U)) + 3299527965014731384U;
            aOrbiterJ = ((((aWandererF + RotL64(aCross, 47U)) + RotL64(aCarry, 51U)) + 16293096431816127821U) + aOrbiterAssignSaltB[((aIndex + 3189U)) & S_SALT1]) + RotL64(aNonceByteD, 25U);
            aOrbiterG = (aWandererK + RotL64(aIngress, 27U)) + 11031983436878828337U;
            aOrbiterH = (aWandererA + RotL64(aPrevious, 38U)) + 9188018632448236358U;
            aOrbiterE = (aWandererB + RotL64(aScatter, 29U)) + 13420816400363406556U;
            aOrbiterC = ((aWandererH + RotL64(aCross, 43U)) + 2485063384097917101U) + aOrbiterAssignSaltA[(((31U - aIndex) + 7514U)) & S_SALT1];
            aOrbiterK = (aWandererI + RotL64(aIngress, 19U)) + 3089135816938128264U;
            aOrbiterI = (aWandererC + RotL64(aPrevious, 52U)) + 10730544971770435788U;
            aOrbiterF = (aWandererG + RotL64(aCross, 21U)) + 10431767565618874806U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterA) + 14883796491656899074U) + aOrbiterUpdateSaltA[((aIndex + 1105U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 13465877783538483706U;
            aOrbiterB = RotL64((aOrbiterB * 14311686051108108503U), 13U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 13322163435314643713U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 3307316600284371955U;
            aOrbiterH = RotL64((aOrbiterH * 12337846092069506365U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 4950101626975919939U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterE) ^ 2596253994220103666U) ^ aOrbiterUpdateSaltC[((aIndex + 2508U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 7181706961838582889U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 17961706029559914243U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 10321902557977495175U) ^ aOrbiterUpdateSaltD[((aIndex + 453U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 16189559888625084711U), 41U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 18146616411403012772U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 8414050129421955787U) ^ RotL64(aNonceByteG, 23U);
            aOrbiterD = RotL64((aOrbiterD * 14879448948196182863U), 5U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 11739172334166341121U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 7936637782633487291U;
            aOrbiterJ = RotL64((aOrbiterJ * 14940929920543800413U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 3160044627483874242U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 16816384076887379704U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 6803U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 5052772186568301951U), 27U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterJ) + 8101560104988710226U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 8851416379738817624U;
            aOrbiterK = RotL64((aOrbiterK * 16767420038937389027U), 39U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 9941784290055185679U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 14495651885701938495U;
            aOrbiterF = RotL64((aOrbiterF * 1540692851998143607U), 29U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 10599676325220702167U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 16092000942942971187U) ^ RotL64(aNonceByteE, 17U);
            aOrbiterA = RotL64((aOrbiterA * 2457268192247656817U), 43U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 16168470945107928109U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 17264605017518259932U;
            aOrbiterG = RotL64((aOrbiterG * 15038386057529909273U), 37U);
            //
            aIngress = RotL64(aOrbiterC, 19U) ^ aOrbiterA;
            aIngress = aIngress + (RotL64(aOrbiterF, 27U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterG, 6U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterD, 57U) ^ aOrbiterH);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterI, 37U));
            aIngress = aIngress + RotL64(aOrbiterB, 51U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 47U) + aOrbiterH) + RotL64(aOrbiterJ, 11U));
            aWandererB = aWandererB + ((RotL64(aCross, 13U) + aOrbiterC) + RotL64(aOrbiterJ, 44U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 24U) + aOrbiterK) + RotL64(aOrbiterD, 19U));
            aWandererD = aWandererD + (((RotL64(aIngress, 29U) + RotL64(aOrbiterD, 35U)) + aOrbiterJ) + aWandererUpdateSaltB[((aIndex + 6475U)) & S_SALT1]);
            aWandererE = aWandererE ^ (((RotL64(aPrevious, 3U) + RotL64(aOrbiterE, 3U)) + aOrbiterH) + RotL64(aNonceByteC, 39U));
            aWandererF = aWandererF + (((RotL64(aCross, 43U) + RotL64(aOrbiterG, 60U)) + aOrbiterC) + RotL64(aCarry, 39U));
            aWandererG = aWandererG ^ ((RotL64(aIngress, 35U) + RotL64(aOrbiterA, 37U)) + aOrbiterC);
            aWandererH = aWandererH + (((RotL64(aScatter, 57U) + aOrbiterF) + RotL64(aOrbiterB, 53U)) + aWandererUpdateSaltA[(((31U - aIndex) + 3355U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aCross, 26U) + aOrbiterB) + RotL64(aOrbiterD, 47U));
            aWandererJ = aWandererJ + (((RotL64(aScatter, 37U) + aOrbiterI) + RotL64(aOrbiterK, 29U)) + RotL64(aCarry, 3U));
            aWandererK = aWandererK ^ (((RotL64(aIngress, 41U) + RotL64(aOrbiterJ, 27U)) + aOrbiterF) + RotL64(aNonceByteH, 49U));
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererI, 21U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererC, 60U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererJ, 5U));
            aCarry = aCarry + (RotL64(aWandererH, 43U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererA, 53U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererD, 13U);
            aCarry = aCarry + RotL64(aIngress, 48U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneE[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 57U) ^ RotL64(aNonceByteB, 3U)) ^ RotL64(aNonceByteC, 37U));
            aIngress = aIngress ^ (RotL64(aExpandLaneE[((aIndex + 6429U)) & S_BLOCK1], 47U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 8866U)) & S_BLOCK1], 28U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 3U) ^ RotL64(aNonceByteE, 35U)) ^ RotL64(aNonceByteF, 11U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 6475U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneB[((aIndex + 10798U)) & S_BLOCK1], 48U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 41U) ^ RotL64(aPrevious, 23U)) + (RotL64(aIngress, 11U) ^ RotL64(aCarry, 54U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = (aWandererC + RotL64(aScatter, 11U)) + 3339283916456813609U;
            aOrbiterC = (aWandererB + RotL64(aIngress, 54U)) + 11339086426180649584U;
            aOrbiterD = (aWandererE + RotL64(aPrevious, 43U)) + 16819191669329316585U;
            aOrbiterI = (aWandererI + RotL64(aCross, 19U)) + 8361916937762630725U;
            aOrbiterJ = (((aWandererF + RotL64(aScatter, 5U)) + RotL64(aCarry, 21U)) + 18031328374429899857U) + RotL64(aNonceByteE, 27U);
            aOrbiterE = (aWandererG + RotL64(aCross, 3U)) + 18261756894092897276U;
            aOrbiterK = ((aWandererK + RotL64(aIngress, 51U)) + 4250319792907645666U) + aOrbiterAssignSaltA[(((31U - aIndex) + 7049U)) & S_SALT1];
            aOrbiterF = ((aWandererD + RotL64(aPrevious, 41U)) + RotL64(aCarry, 35U)) + 1492411503643460886U;
            aOrbiterA = ((aWandererJ + RotL64(aIngress, 37U)) + 17369549067879344180U) + RotL64(aNonceByteB, 23U);
            aOrbiterG = (((aWandererH + RotL64(aCross, 47U)) + RotL64(aCarry, 3U)) + 7301713524358676722U) + aOrbiterAssignSaltB[(((31U - aIndex) + 2661U)) & S_SALT1];
            aOrbiterB = (aWandererA + RotL64(aPrevious, 26U)) + 2985193736033012535U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 14086975808140927408U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterH) ^ 10390516547834639800U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 5012U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 11441293212275890819U), 51U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 18205555540941493267U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 16967799565443938873U;
            aOrbiterJ = RotL64((aOrbiterJ * 3009081009044782443U), 37U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 9209505304067579944U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 3522631966146762306U;
            aOrbiterE = RotL64((aOrbiterE * 3441982898533162599U), 39U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 8811497120829041188U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 14707301680850257294U) ^ aOrbiterUpdateSaltB[((aIndex + 4301U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 11383709499376464085U), 5U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 10080595991787801029U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 7631U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 6822892187784299166U;
            aOrbiterF = RotL64((aOrbiterF * 7417016898027778287U), 21U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 1981637172055758689U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 16463077485583119324U) ^ RotL64(aNonceByteC, 37U);
            aOrbiterA = RotL64((aOrbiterA * 2876782050665869121U), 41U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 8383837717361569465U;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 2788511294985017326U;
            aOrbiterG = RotL64((aOrbiterG * 2809163242875130677U), 57U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 3529607472855930041U) + aOrbiterUpdateSaltD[((aIndex + 3513U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 8850940802020173766U) ^ RotL64(aNonceByteH, 53U);
            aOrbiterB = RotL64((aOrbiterB * 7821450253655655943U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 7469160295100147267U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 16973986572163482061U;
            aOrbiterH = RotL64((aOrbiterH * 15660743778376905023U), 13U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 12371372942863279718U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 12098525148034303633U;
            aOrbiterC = RotL64((aOrbiterC * 11234127652230231751U), 3U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 5138683482859889480U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 3339283916456813609U;
            aOrbiterI = RotL64((aOrbiterI * 10975353228235695455U), 53U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterI, 29U);
            aIngress = aIngress + (RotL64(aOrbiterE, 35U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterH, 26U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterB, 53U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterD, 37U));
            aIngress = aIngress + RotL64(aOrbiterC, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aScatter, 47U) + RotL64(aOrbiterG, 29U)) + aOrbiterB) + aWandererUpdateSaltA[(((31U - aIndex) + 4316U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aCross, 21U) + RotL64(aOrbiterG, 43U)) + aOrbiterC);
            aWandererC = aWandererC + ((RotL64(aPrevious, 39U) + RotL64(aOrbiterF, 19U)) + aOrbiterI);
            aWandererD = aWandererD ^ ((RotL64(aIngress, 41U) + aOrbiterH) + RotL64(aOrbiterD, 54U));
            aWandererE = aWandererE + (((RotL64(aPrevious, 23U) + RotL64(aOrbiterK, 35U)) + aOrbiterG) + RotL64(aCarry, 27U));
            aWandererF = aWandererF ^ ((RotL64(aScatter, 34U) + aOrbiterB) + RotL64(aOrbiterD, 3U));
            aWandererG = aWandererG + ((RotL64(aCross, 13U) + aOrbiterA) + RotL64(aOrbiterK, 37U));
            aWandererH = aWandererH ^ (((RotL64(aIngress, 19U) + RotL64(aOrbiterC, 57U)) + aOrbiterE) + RotL64(aNonceByteF, 20U));
            aWandererI = aWandererI + (((RotL64(aCross, 57U) + aOrbiterI) + RotL64(aOrbiterD, 11U)) + RotL64(aCarry, 11U));
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 60U) + aOrbiterA) + RotL64(aOrbiterG, 60U)) + RotL64(aNonceByteG, 17U));
            aWandererK = aWandererK + (((RotL64(aPrevious, 5U) + aOrbiterJ) + RotL64(aOrbiterF, 13U)) + aWandererUpdateSaltB[((aIndex + 1550U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererF, 28U) ^ aWandererH);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererB, 51U));
            aCarry = aCarry + (RotL64(aWandererI, 39U) ^ aWandererC);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererA, 57U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererD, 23U));
            aCarry = aCarry + RotL64(aWandererJ, 60U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneF[S_BLOCK1 - aIndex] = aIngress;
        }
    }
}

void TwistExpander_Eleven_0006::KDF_B(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  TwistDomainSBoxSet *pDomainSBoxSet) {
    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet, pDomainSBoxSet);
    TwistWorkSpace *pWorkspace = mWorkspace;
    if ((pWorkspace == nullptr) || (mSource == nullptr) || (mDest == nullptr) ||
        (pConstants == nullptr) || (pDomainSaltSet == nullptr) || (pDomainSBoxSet == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aSource = mSource;
    [[maybe_unused]] std::uint8_t *aDestination = mDest;
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
    [[maybe_unused]] std::uint8_t *mSBoxA = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(30));
    [[maybe_unused]] std::uint8_t *mSBoxB = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(31));
    [[maybe_unused]] std::uint8_t *mSBoxC = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(32));
    [[maybe_unused]] std::uint8_t *mSBoxD = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(33));
    [[maybe_unused]] std::uint8_t *mSBoxE = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(34));
    [[maybe_unused]] std::uint8_t *mSBoxF = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(35));
    [[maybe_unused]] std::uint8_t *mSBoxG = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(36));
    [[maybe_unused]] std::uint8_t *mSBoxH = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(37));
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkspace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkspace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkspace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkspace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aExpandLaneE = pWorkspace->mExpansionLaneE;
    [[maybe_unused]] std::uint8_t *aExpandLaneF = pWorkspace->mExpansionLaneF;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneE = pWorkspace->mWorkLaneE;
    [[maybe_unused]] std::uint8_t *aWorkLaneF = pWorkspace->mWorkLaneF;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkspace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkspace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkspace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkspace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneE = pWorkspace->mOperationLaneE;
    [[maybe_unused]] std::uint8_t *aOperationLaneF = pWorkspace->mOperationLaneF;
    [[maybe_unused]] std::uint8_t *aMaskLaneA = pWorkspace->mMaskLaneA;
    [[maybe_unused]] std::uint8_t *aMaskLaneB = pWorkspace->mMaskLaneB;
    [[maybe_unused]] std::size_t *aIndexList256A = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(190)));
    [[maybe_unused]] std::size_t *aIndexList256B = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(191)));
    [[maybe_unused]] std::size_t *aIndexList256C = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(192)));
    [[maybe_unused]] std::size_t *aIndexList256D = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(193)));
    [[maybe_unused]] std::size_t *aIndexList256E = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(194)));
    [[maybe_unused]] std::size_t *aIndexList256F = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(195)));
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledB = &(pWorkspace->mMaskBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadA = &(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadB = &(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteB = &(pWorkspace->mMaskBoxB[0][0]);
    std::uint64_t aPrevious = 0; std::uint64_t aIngress = 0; std::uint64_t aCross = 0; std::uint64_t aScatter = 0;
    std::uint64_t aCarry = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    std::uint64_t aWandererA = 0; std::uint64_t aWandererB = 0; std::uint64_t aWandererC = 0; std::uint64_t aWandererD = 0;
    std::uint64_t aWandererE = 0; std::uint64_t aWandererF = 0; std::uint64_t aWandererG = 0; std::uint64_t aWandererH = 0;
    std::uint64_t aWandererI = 0; std::uint64_t aWandererJ = 0; std::uint64_t aWandererK = 0;

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
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixSchemeA = pConstants->mMatrixSchemeA;
    std::uint8_t aDomainWordMatrixSchemeB = pConstants->mMatrixSchemeB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;

    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 47U) ^ RotL64(aNonceByteB, 36U)) ^ RotL64(aNonceByteC, 3U));
            aIngress = aIngress ^ (RotL64(aSource[((aIndex + 4941U)) & S_BLOCK1], 19U) ^ RotL64(aSource[((aIndex + 6265U)) & S_BLOCK1], 27U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 23U) ^ RotL64(aNonceByteE, 3U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 13021U)) & S_BLOCK1], 34U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 10096U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 51U) + RotL64(aPrevious, 5U)) + (RotL64(aIngress, 22U) ^ RotL64(aCross, 35U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = ((aWandererK + RotL64(aIngress, 50U)) + 5697928251815176134U) + RotL64(pNonce, 60U);
            aOrbiterC = (aWandererH + RotL64(aPrevious, 29U)) + 337587740689259575U;
            aOrbiterD = ((aWandererD + RotL64(aScatter, 5U)) + RotL64(aCarry, 21U)) + 4927686903263973950U;
            aOrbiterB = (aWandererF + RotL64(aCross, 57U)) + 3742409032569801033U;
            aOrbiterE = (aWandererI + RotL64(aScatter, 21U)) + 1608092659172197650U;
            aOrbiterG = ((aWandererC + RotL64(aCross, 37U)) + 15848744267145717509U) + aOrbiterAssignSaltA[(((31U - aIndex) + 963U)) & S_SALT1];
            aOrbiterF = ((aWandererB + RotL64(aPrevious, 18U)) + 15300174177963339253U) + RotL64(aNonceByteF, 47U);
            aOrbiterI = ((aWandererE + RotL64(aIngress, 43U)) + 14162868453323648628U) + aOrbiterAssignSaltB[(((31U - aIndex) + 6919U)) & S_SALT1];
            aOrbiterH = ((aWandererG + RotL64(aCross, 35U)) + RotL64(aCarry, 5U)) + 12020167069983729869U;
            aOrbiterJ = (aWandererA + RotL64(aIngress, 23U)) + 16259538291658723956U;
            aOrbiterK = ((aWandererJ + RotL64(aPrevious, 53U)) + RotL64(aCarry, 57U)) + 8516686212464112245U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 3722184575520553132U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 5663609293306386784U;
            aOrbiterD = RotL64((aOrbiterD * 14364218128780764749U), 13U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 15265344442454471986U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 5658U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 3050323350098829515U;
            aOrbiterG = RotL64((aOrbiterG * 5890624677162388135U), 53U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 1093356813820599238U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 15167726103772238440U;
            aOrbiterA = RotL64((aOrbiterA * 5719466863561311069U), 47U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 15170797965325981472U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 17826286701992981628U;
            aOrbiterB = RotL64((aOrbiterB * 11186808881726573677U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 14710892030473425181U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 397194787697553904U;
            aOrbiterF = RotL64((aOrbiterF * 14368930300818752833U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 1273724124862533034U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 13018397560392545616U;
            aOrbiterH = RotL64((aOrbiterH * 4644812473262395329U), 27U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterA) + 9638716186445643730U) + aOrbiterUpdateSaltA[((aIndex + 3819U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterE) ^ 7255587739807843785U;
            aOrbiterK = RotL64((aOrbiterK * 6055682981584011189U), 23U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterB) + 9272350563697399628U) + RotL64(aNonceByteH, 21U);
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 1040729335295009339U;
            aOrbiterC = RotL64((aOrbiterC * 17825687660830291443U), 39U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 12128124729613601747U;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 2285238815562202219U;
            aOrbiterE = RotL64((aOrbiterE * 15398840993074390573U), 29U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 6339113298619163493U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterD) ^ 5911895708485037040U) ^ aOrbiterUpdateSaltD[((aIndex + 3142U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 3271006139923200439U), 41U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 7601399508218901328U;
            aOrbiterJ = (((aOrbiterJ ^ aOrbiterG) ^ 5697928251815176134U) ^ aOrbiterUpdateSaltB[((aIndex + 8187U)) & S_SALT1]) ^ RotL64(aNonceByteG, 25U);
            aOrbiterJ = RotL64((aOrbiterJ * 8184257916861355735U), 5U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterG, 18U);
            aIngress = aIngress + (RotL64(aOrbiterH, 29U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterB, 57U) ^ aOrbiterD);
            aIngress = aIngress + (RotL64(aOrbiterC, 13U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterA, 11U));
            aIngress = aIngress + RotL64(aOrbiterE, 5U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 50U) + aOrbiterI) + RotL64(aOrbiterF, 57U)) + RotL64(aNonceByteA, 55U));
            aWandererB = aWandererB + (((RotL64(aIngress, 41U) + aOrbiterE) + RotL64(aOrbiterC, 47U)) + aWandererUpdateSaltA[(((31U - aIndex) + 2405U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aCross, 27U) + RotL64(aOrbiterG, 21U)) + aOrbiterC);
            aWandererD = aWandererD + ((RotL64(aScatter, 23U) + aOrbiterK) + RotL64(aOrbiterF, 29U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 29U) + RotL64(aOrbiterH, 41U)) + aOrbiterJ);
            aWandererF = aWandererF + (((RotL64(aIngress, 5U) + aOrbiterC) + RotL64(aOrbiterA, 50U)) + RotL64(aCarry, 5U));
            aWandererG = aWandererG ^ (((RotL64(aCross, 3U) + RotL64(aOrbiterB, 53U)) + aOrbiterI) + aWandererUpdateSaltB[(((31U - aIndex) + 7281U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aScatter, 39U) + RotL64(aOrbiterB, 5U)) + aOrbiterK) + RotL64(aNonceByteC, 51U));
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 18U) + aOrbiterC) + RotL64(aOrbiterJ, 43U));
            aWandererJ = aWandererJ + (((RotL64(aCross, 35U) + aOrbiterD) + RotL64(aOrbiterH, 36U)) + RotL64(aCarry, 47U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 11U) + aOrbiterB) + RotL64(aOrbiterJ, 11U));
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererI, 51U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 43U));
            aCarry = aCarry + (RotL64(aWandererA, 56U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererC, 37U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererE, 29U) ^ aWandererB);
            aCarry = aCarry + RotL64(aWandererJ, 23U);
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
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 3U) ^ RotL64(aNonceByteB, 39U)) ^ RotL64(aNonceByteC, 48U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 13947U)) & S_BLOCK1], 11U) ^ RotL64(aSource[((aIndex + 14428U)) & S_BLOCK1], 19U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 39U) ^ RotL64(aNonceByteE, 29U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 15588U)) & S_BLOCK1], 47U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 8772U)) & S_BLOCK1], 56U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 23U) + RotL64(aPrevious, 10U)) ^ (RotL64(aIngress, 43U) + RotL64(aCross, 57U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = (aWandererI + RotL64(aIngress, 29U)) + 11274974230580265396U;
            aOrbiterE = (aWandererF + RotL64(aPrevious, 14U)) + 16658438747342741547U;
            aOrbiterA = (aWandererD + RotL64(aCross, 23U)) + 16612986966106053844U;
            aOrbiterI = (((aWandererH + RotL64(aScatter, 3U)) + RotL64(aCarry, 13U)) + 9329502236843231290U) + RotL64(aNonceByteH, 23U);
            aOrbiterK = (aWandererG + RotL64(aPrevious, 53U)) + 14088261356708344656U;
            aOrbiterH = (aWandererJ + RotL64(aCross, 27U)) + 13692608802007789581U;
            aOrbiterF = ((aWandererK + RotL64(aIngress, 35U)) + RotL64(aCarry, 27U)) + 6824473946645682398U;
            aOrbiterC = ((aWandererB + RotL64(aScatter, 43U)) + 2072915876348570040U) + aOrbiterAssignSaltB[((aIndex + 7786U)) & S_SALT1];
            aOrbiterJ = (aWandererC + RotL64(aPrevious, 39U)) + 7420507753044460759U;
            aOrbiterB = (((aWandererA + RotL64(aIngress, 58U)) + 4677557318688502593U) + aOrbiterAssignSaltA[((aIndex + 4972U)) & S_SALT1]) + RotL64(aNonceByteG, 17U);
            aOrbiterD = ((aWandererE + RotL64(aCross, 5U)) + RotL64(aCarry, 39U)) + 15081678577055628459U;
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 7026792817486507482U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 2729U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 14871665922943969918U;
            aOrbiterA = RotL64((aOrbiterA * 694073180313083145U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 6807734532159292872U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 17882797335141303280U;
            aOrbiterE = RotL64((aOrbiterE * 15439872930381050291U), 53U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 9233542707022629190U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 1205501586581350876U;
            aOrbiterK = RotL64((aOrbiterK * 2596053290311090589U), 3U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 10878718669747466677U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 8066049063548639241U;
            aOrbiterF = RotL64((aOrbiterF * 3031382633089381605U), 41U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 861295180226875235U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterB) ^ 9134969787937288583U) ^ aOrbiterUpdateSaltC[((aIndex + 2149U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 7565008208670843555U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 6726642007159809594U;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 8061661744643240470U;
            aOrbiterG = RotL64((aOrbiterG * 6703498926835391813U), 19U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterH) + 13541412083111962884U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 835U)) & S_SALT1]) + RotL64(aNonceByteF, 47U);
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 8617442758729315637U;
            aOrbiterI = RotL64((aOrbiterI * 15471862889276160953U), 27U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 16884403561131293362U;
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 9490680911678221233U;
            aOrbiterH = RotL64((aOrbiterH * 15988763830018001033U), 21U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 10486145044311386738U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 10200001044821063684U) ^ RotL64(aNonceByteE, 4U);
            aOrbiterC = RotL64((aOrbiterC * 16149790736141571017U), 37U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 6997073594007878034U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 13585783612009989767U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 8107U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 11425303157774550449U), 5U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 3847846040256340653U;
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 11274974230580265396U;
            aOrbiterD = RotL64((aOrbiterD * 13970270689108369205U), 29U);
            //
            aIngress = RotL64(aOrbiterD, 34U) ^ aOrbiterC;
            aIngress = aIngress + (RotL64(aOrbiterF, 5U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterI, 19U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterJ, 53U) ^ aOrbiterK);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterH, 51U));
            aIngress = aIngress + RotL64(aOrbiterB, 27U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aCross, 41U) + aOrbiterK) + RotL64(aOrbiterI, 3U)) + aWandererUpdateSaltB[(((31U - aIndex) + 269U)) & S_SALT1]);
            aWandererB = aWandererB + ((RotL64(aPrevious, 46U) + aOrbiterG) + RotL64(aOrbiterJ, 51U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 29U) + aOrbiterF) + RotL64(aOrbiterK, 53U));
            aWandererD = aWandererD + (((RotL64(aIngress, 13U) + RotL64(aOrbiterG, 41U)) + aOrbiterA) + RotL64(aNonceByteA, 53U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 35U) + RotL64(aOrbiterH, 34U)) + aOrbiterJ);
            aWandererF = aWandererF + (((RotL64(aIngress, 18U) + RotL64(aOrbiterC, 43U)) + aOrbiterG) + RotL64(aCarry, 29U));
            aWandererG = aWandererG ^ ((RotL64(aScatter, 11U) + aOrbiterA) + RotL64(aOrbiterE, 39U));
            aWandererH = aWandererH + (((RotL64(aPrevious, 57U) + aOrbiterA) + RotL64(aOrbiterD, 57U)) + RotL64(aCarry, 43U));
            aWandererI = aWandererI ^ ((RotL64(aScatter, 3U) + RotL64(aOrbiterE, 29U)) + aOrbiterI);
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 53U) + aOrbiterD) + RotL64(aOrbiterJ, 37U)) + RotL64(aNonceByteC, 21U));
            aWandererK = aWandererK ^ (((RotL64(aIngress, 51U) + RotL64(aOrbiterI, 20U)) + aOrbiterB) + aWandererUpdateSaltA[(((31U - aIndex) + 6328U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererH, 19U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererE, 60U) ^ aWandererF);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererD, 47U));
            aCarry = aCarry + (RotL64(aWandererB, 39U) ^ aWandererI);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererG, 53U));
            aCarry = aCarry + RotL64(aWandererC, 58U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 11U) ^ RotL64(aNonceByteB, 58U)) ^ RotL64(aNonceByteC, 39U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 10857U)) & S_BLOCK1], 21U) ^ RotL64(aExpandLaneA[((aIndex + 11996U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 11U) ^ RotL64(aNonceByteE, 24U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 4347U)) & S_BLOCK1], 35U) ^ RotL64(aExpandLaneB[((aIndex + 8464U)) & S_BLOCK1], 51U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 23U) + RotL64(aIngress, 38U)) + (RotL64(aPrevious, 5U) ^ RotL64(aCarry, 53U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterJ = (aWandererI + RotL64(aPrevious, 35U)) + 12775735908960052604U;
            aOrbiterH = ((aWandererJ + RotL64(aCross, 12U)) + RotL64(aCarry, 21U)) + 11791373812080296887U;
            aOrbiterG = (aWandererB + RotL64(aIngress, 47U)) + 5537362877706057303U;
            aOrbiterE = ((aWandererE + RotL64(aScatter, 27U)) + RotL64(aCarry, 47U)) + 2023912048504189380U;
            aOrbiterC = (aWandererC + RotL64(aCross, 41U)) + 17668828109963766893U;
            aOrbiterB = (((aWandererD + RotL64(aIngress, 19U)) + RotL64(aCarry, 57U)) + 558908629933941224U) + aOrbiterAssignSaltB[(((31U - aIndex) + 7204U)) & S_SALT1];
            aOrbiterK = (aWandererH + RotL64(aPrevious, 29U)) + 1479633119685446888U;
            aOrbiterI = (aWandererG + RotL64(aScatter, 22U)) + 15460320397843364063U;
            aOrbiterF = (((aWandererK + RotL64(aCross, 39U)) + 10059749397555469054U) + aOrbiterAssignSaltA[(((31U - aIndex) + 1910U)) & S_SALT1]) + RotL64(aNonceByteC, 11U);
            aOrbiterD = (aWandererA + RotL64(aIngress, 51U)) + 9987633811929693924U;
            aOrbiterA = ((aWandererF + RotL64(aPrevious, 3U)) + 10087337844580228269U) + RotL64(aNonceByteG, 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 4446204415503364254U;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 15106063243302192717U;
            aOrbiterG = RotL64((aOrbiterG * 13273756657334709803U), 37U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 9430197906134676162U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterE) ^ 1226048679997253363U) ^ aOrbiterUpdateSaltD[((aIndex + 1105U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 14247538885252664127U), 23U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 10611580584157624739U;
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 3137391249289641509U;
            aOrbiterH = RotL64((aOrbiterH * 5462682413239873181U), 41U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 9327201928815412810U) + RotL64(aNonceByteF, 15U);
            aOrbiterC = ((aOrbiterC ^ aOrbiterF) ^ 7890659377013147073U) ^ aOrbiterUpdateSaltB[((aIndex + 5835U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 13827717178378062047U), 47U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 10675114832750356941U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterA) ^ 8804440385852327267U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 2968U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 8520671775587260601U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 12871947817782057116U;
            aOrbiterD = (((aOrbiterD ^ aOrbiterG) ^ 11015991745792051390U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 2505U)) & S_SALT1]) ^ RotL64(aNonceByteD, 40U);
            aOrbiterD = RotL64((aOrbiterD * 17152451500505815031U), 19U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 6320437975845673731U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 702457937087191287U;
            aOrbiterJ = RotL64((aOrbiterJ * 17491257114676739589U), 39U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 16629064896250312921U;
            aOrbiterE = (aOrbiterE ^ aOrbiterH) ^ 6054107387816339103U;
            aOrbiterE = RotL64((aOrbiterE * 6983767878966747219U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 13274874838094190290U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 12211422735294360321U;
            aOrbiterK = RotL64((aOrbiterK * 5113738196151089817U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 15338616110718583619U;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 1475787183754511373U;
            aOrbiterF = RotL64((aOrbiterF * 10904607643785840003U), 35U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 15486810401396777742U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 12775735908960052604U;
            aOrbiterA = RotL64((aOrbiterA * 7478156942468930207U), 3U);
            //
            aIngress = RotL64(aOrbiterE, 23U) ^ aOrbiterH;
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterI, 51U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterJ, 44U));
            aIngress = aIngress + (RotL64(aOrbiterC, 27U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterB, 57U));
            aIngress = aIngress + RotL64(aOrbiterD, 19U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aScatter, 23U) + aOrbiterH) + RotL64(aOrbiterB, 11U));
            aWandererB = aWandererB + (((RotL64(aCross, 30U) + RotL64(aOrbiterA, 47U)) + aOrbiterK) + RotL64(aCarry, 47U));
            aWandererC = aWandererC ^ (((RotL64(aIngress, 57U) + aOrbiterI) + RotL64(aOrbiterA, 43U)) + aWandererUpdateSaltA[((aIndex + 1511U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aPrevious, 41U) + RotL64(aOrbiterI, 57U)) + aOrbiterD) + RotL64(aNonceByteB, 17U));
            aWandererE = aWandererE ^ ((((RotL64(aScatter, 53U) + aOrbiterF) + RotL64(aOrbiterJ, 51U)) + RotL64(aNonceByteH, 37U)) + aWandererUpdateSaltB[(((31U - aIndex) + 6197U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aIngress, 27U) + aOrbiterE) + RotL64(aOrbiterA, 36U)) + RotL64(aCarry, 27U));
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 35U) + RotL64(aOrbiterG, 39U)) + aOrbiterJ);
            aWandererH = aWandererH + ((RotL64(aCross, 43U) + RotL64(aOrbiterB, 13U)) + aOrbiterG);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 13U) + RotL64(aOrbiterG, 29U)) + aOrbiterE);
            aWandererJ = aWandererJ + ((RotL64(aCross, 4U) + RotL64(aOrbiterJ, 26U)) + aOrbiterH);
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 51U) + RotL64(aOrbiterC, 21U)) + aOrbiterA);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererK, 60U));
            aCarry = aCarry + (RotL64(aWandererI, 21U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererB, 13U) ^ aWandererH);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererG, 39U));
            aCarry = aCarry + (RotL64(aWandererF, 54U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererD, 27U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 43U) ^ RotL64(aNonceByteB, 34U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 3194U)) & S_BLOCK1], 53U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 5231U)) & S_BLOCK1], 21U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 3U) ^ RotL64(aNonceByteD, 19U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 15579U)) & S_BLOCK1], 43U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 1246U)) & S_BLOCK1], 56U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 11U) + RotL64(aCross, 53U)) + (RotL64(aCarry, 26U) ^ RotL64(aPrevious, 39U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = (((aWandererE + RotL64(aCross, 51U)) + RotL64(aCarry, 47U)) + 10336802574069791273U) + aOrbiterAssignSaltB[(((31U - aIndex) + 3098U)) & S_SALT1];
            aOrbiterK = ((aWandererG + RotL64(aScatter, 44U)) + 169025388197058936U) + RotL64(aNonceByteD, 59U);
            aOrbiterJ = (aWandererA + RotL64(aIngress, 5U)) + 6541354188379168846U;
            aOrbiterE = ((aWandererI + RotL64(aPrevious, 21U)) + RotL64(aCarry, 5U)) + 16223920526599306104U;
            aOrbiterD = (aWandererF + RotL64(aIngress, 53U)) + 12756613707692514808U;
            aOrbiterI = (aWandererB + RotL64(aPrevious, 37U)) + 5082475548176484035U;
            aOrbiterC = ((aWandererK + RotL64(aCross, 41U)) + 4907435526952698526U) + RotL64(aNonceByteH, 39U);
            aOrbiterH = (((aWandererD + RotL64(aScatter, 18U)) + RotL64(aCarry, 19U)) + 14236627073831834337U) + aOrbiterAssignSaltA[(((31U - aIndex) + 1573U)) & S_SALT1];
            aOrbiterB = (aWandererH + RotL64(aCross, 57U)) + 11502511046130497584U;
            aOrbiterG = (aWandererC + RotL64(aScatter, 27U)) + 3679044835550219497U;
            aOrbiterA = (aWandererJ + RotL64(aPrevious, 35U)) + 11254838916686736746U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 10582608424233200966U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 10449735026385340313U;
            aOrbiterJ = RotL64((aOrbiterJ * 7363770199734997411U), 21U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 4628253464169957835U;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 17664454668473204465U;
            aOrbiterD = RotL64((aOrbiterD * 4234720298731378527U), 57U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 3798386391743884889U) + RotL64(aNonceByteF, 8U);
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 1379331161819246587U;
            aOrbiterI = RotL64((aOrbiterI * 13086160171095077295U), 19U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterD) + 9816600392407327227U) + RotL64(aNonceByteE, 45U);
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 16781971616348376878U) ^ aOrbiterUpdateSaltB[((aIndex + 3697U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 12503867584828289879U), 5U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterI) + 4807797577690520554U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 4778U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 2492057261148595922U;
            aOrbiterH = RotL64((aOrbiterH * 9453302540675483005U), 13U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 7909676419643119585U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 256053568910383007U;
            aOrbiterB = RotL64((aOrbiterB * 11965085163352053161U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 16179914439220412472U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 3968867762761955845U;
            aOrbiterG = RotL64((aOrbiterG * 7473632378251893139U), 53U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 7474832923901283742U;
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 4736994731050735779U;
            aOrbiterA = RotL64((aOrbiterA * 9839654409121414047U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 596484364660389193U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterB) ^ 13822222274464306169U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 7880U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 1723502278319885511U), 43U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterA) + 16307920280681985443U) + aOrbiterUpdateSaltA[((aIndex + 6023U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 3505106171801702915U;
            aOrbiterK = RotL64((aOrbiterK * 8479675421552861243U), 39U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 4987142580981135150U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 10336802574069791273U;
            aOrbiterE = RotL64((aOrbiterE * 2670706512498539705U), 47U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterK, 38U);
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterD, 53U));
            aIngress = aIngress + (RotL64(aOrbiterI, 57U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterH, 27U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterE, 29U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterF, 5U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aScatter, 27U) + RotL64(aOrbiterK, 43U)) + aOrbiterI);
            aWandererB = aWandererB + ((((RotL64(aIngress, 37U) + aOrbiterC) + RotL64(aOrbiterA, 60U)) + RotL64(aCarry, 3U)) + RotL64(aNonceByteB, 11U));
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 13U) + aOrbiterK) + RotL64(aOrbiterF, 47U));
            aWandererD = aWandererD + (((RotL64(aCross, 44U) + aOrbiterC) + RotL64(aOrbiterE, 37U)) + aWandererUpdateSaltB[((aIndex + 957U)) & S_SALT1]);
            aWandererE = aWandererE ^ (((RotL64(aIngress, 47U) + aOrbiterG) + RotL64(aOrbiterK, 23U)) + aWandererUpdateSaltA[((aIndex + 2231U)) & S_SALT1]);
            aWandererF = aWandererF + ((RotL64(aPrevious, 51U) + aOrbiterD) + RotL64(aOrbiterK, 54U));
            aWandererG = aWandererG ^ ((RotL64(aCross, 35U) + aOrbiterF) + RotL64(aOrbiterB, 13U));
            aWandererH = aWandererH + (((RotL64(aScatter, 3U) + aOrbiterC) + RotL64(aOrbiterH, 29U)) + RotL64(aCarry, 19U));
            aWandererI = aWandererI ^ (((RotL64(aCross, 22U) + aOrbiterH) + RotL64(aOrbiterD, 11U)) + RotL64(aNonceByteG, 27U));
            aWandererJ = aWandererJ + ((RotL64(aScatter, 5U) + RotL64(aOrbiterG, 19U)) + aOrbiterJ);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 11U) + RotL64(aOrbiterG, 41U)) + aOrbiterA);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererB, 57U));
            aCarry = aCarry + (RotL64(aWandererG, 39U) ^ aWandererK);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererF, 48U));
            aCarry = aCarry + (RotL64(aWandererH, 37U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererJ, 23U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererE, 51U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 29U) ^ RotL64(aNonceByteB, 47U)) ^ RotL64(aNonceByteC, 3U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 13680U)) & S_BLOCK1], 21U) ^ RotL64(aExpandLaneC[((aIndex + 8270U)) & S_BLOCK1], 38U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 57U) ^ RotL64(aNonceByteE, 48U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 10447U)) & S_BLOCK1], 39U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 16018U)) & S_BLOCK1], 3U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 6U) ^ RotL64(aPrevious, 35U)) + (RotL64(aCarry, 47U) ^ RotL64(aIngress, 21U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterD = ((aWandererB + RotL64(aScatter, 23U)) + RotL64(aCarry, 5U)) + 17264605017518259932U;
            aOrbiterA = (((aWandererI + RotL64(aPrevious, 27U)) + RotL64(aCarry, 21U)) + 15209184354580778643U) + aOrbiterAssignSaltB[(((31U - aIndex) + 8090U)) & S_SALT1];
            aOrbiterB = (aWandererG + RotL64(aCross, 35U)) + 3299527965014731384U;
            aOrbiterJ = ((aWandererA + RotL64(aIngress, 3U)) + 16293096431816127821U) + RotL64(aNonceByteH, 45U);
            aOrbiterG = ((aWandererJ + RotL64(aPrevious, 51U)) + 11031983436878828337U) + aOrbiterAssignSaltA[((aIndex + 1519U)) & S_SALT1];
            aOrbiterH = ((aWandererF + RotL64(aIngress, 30U)) + RotL64(aCarry, 35U)) + 9188018632448236358U;
            aOrbiterE = (aWandererE + RotL64(aCross, 41U)) + 13420816400363406556U;
            aOrbiterC = (aWandererC + RotL64(aScatter, 21U)) + 2485063384097917101U;
            aOrbiterK = ((aWandererH + RotL64(aCross, 5U)) + 3089135816938128264U) + RotL64(aNonceByteF, 29U);
            aOrbiterI = (aWandererK + RotL64(aPrevious, 43U)) + 10730544971770435788U;
            aOrbiterF = (aWandererD + RotL64(aIngress, 56U)) + 10431767565618874806U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 14883796491656899074U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 13465877783538483706U) ^ RotL64(aNonceByteB, 55U);
            aOrbiterB = RotL64((aOrbiterB * 14311686051108108503U), 3U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 13322163435314643713U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 3307316600284371955U;
            aOrbiterH = RotL64((aOrbiterH * 12337846092069506365U), 43U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 4950101626975919939U) + aOrbiterUpdateSaltA[((aIndex + 6713U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterE) ^ 2596253994220103666U) ^ aOrbiterUpdateSaltD[((aIndex + 6211U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 7181706961838582889U), 39U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 17961706029559914243U;
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 10321902557977495175U;
            aOrbiterI = RotL64((aOrbiterI * 16189559888625084711U), 37U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 18146616411403012772U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 8414050129421955787U;
            aOrbiterD = RotL64((aOrbiterD * 14879448948196182863U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 11739172334166341121U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 7936637782633487291U;
            aOrbiterJ = RotL64((aOrbiterJ * 14940929920543800413U), 47U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 3160044627483874242U) + RotL64(aNonceByteA, 6U);
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 16816384076887379704U;
            aOrbiterE = RotL64((aOrbiterE * 5052772186568301951U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterJ) + 8101560104988710226U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 8851416379738817624U;
            aOrbiterK = RotL64((aOrbiterK * 16767420038937389027U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 9941784290055185679U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 14495651885701938495U;
            aOrbiterF = RotL64((aOrbiterF * 1540692851998143607U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 10599676325220702167U;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 16092000942942971187U;
            aOrbiterA = RotL64((aOrbiterA * 2457268192247656817U), 5U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 16168470945107928109U) + aOrbiterUpdateSaltC[((aIndex + 844U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterI) ^ 17264605017518259932U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 1735U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 15038386057529909273U), 53U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterH, 5U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 11U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterK, 41U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterE, 27U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterA, 35U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterB, 48U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 51U) + aOrbiterC) + RotL64(aOrbiterI, 3U));
            aWandererB = aWandererB + (((RotL64(aScatter, 58U) + aOrbiterK) + RotL64(aOrbiterG, 27U)) + aWandererUpdateSaltA[(((31U - aIndex) + 1262U)) & S_SALT1]);
            aWandererC = aWandererC ^ (((RotL64(aCross, 35U) + aOrbiterJ) + RotL64(aOrbiterF, 47U)) + RotL64(aNonceByteD, 25U));
            aWandererD = aWandererD + ((RotL64(aIngress, 39U) + RotL64(aOrbiterJ, 37U)) + aOrbiterA);
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 21U) + RotL64(aOrbiterC, 39U)) + aOrbiterH);
            aWandererF = aWandererF + (((RotL64(aIngress, 37U) + aOrbiterA) + RotL64(aOrbiterG, 30U)) + RotL64(aCarry, 13U));
            aWandererG = aWandererG ^ ((RotL64(aScatter, 6U) + aOrbiterF) + RotL64(aOrbiterD, 11U));
            aWandererH = aWandererH + ((((RotL64(aCross, 13U) + RotL64(aOrbiterE, 21U)) + aOrbiterI) + RotL64(aCarry, 19U)) + aWandererUpdateSaltB[(((31U - aIndex) + 4745U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aIngress, 11U) + aOrbiterD) + RotL64(aOrbiterK, 13U));
            aWandererJ = aWandererJ + (((RotL64(aScatter, 43U) + RotL64(aOrbiterE, 35U)) + aOrbiterC) + RotL64(aNonceByteG, 15U));
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 19U) + RotL64(aOrbiterG, 54U)) + aOrbiterB);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererB, 37U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 39U));
            aCarry = aCarry + (RotL64(aWandererI, 60U) ^ aWandererE);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererC, 51U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererK, 13U));
            aCarry = aCarry + RotL64(aWandererG, 53U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneE[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 47U) ^ RotL64(aNonceByteB, 5U)) ^ RotL64(aNonceByteC, 37U));
            aIngress = aIngress ^ (RotL64(aExpandLaneE[((aIndex + 1233U)) & S_BLOCK1], 14U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 11097U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 5U) ^ RotL64(aNonceByteE, 19U)) ^ RotL64(aNonceByteF, 54U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 2908U)) & S_BLOCK1], 29U) ^ RotL64(aExpandLaneB[((aIndex + 13978U)) & S_BLOCK1], 41U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 37U) + RotL64(aIngress, 54U)) + (RotL64(aPrevious, 3U) ^ RotL64(aCarry, 19U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = (((aWandererK + RotL64(aPrevious, 23U)) + RotL64(aCarry, 19U)) + 3339283916456813609U) + aOrbiterAssignSaltA[((aIndex + 6217U)) & S_SALT1];
            aOrbiterC = (aWandererJ + RotL64(aCross, 3U)) + 11339086426180649584U;
            aOrbiterD = (aWandererE + RotL64(aIngress, 56U)) + 16819191669329316585U;
            aOrbiterI = (aWandererF + RotL64(aScatter, 39U)) + 8361916937762630725U;
            aOrbiterJ = ((aWandererD + RotL64(aCross, 21U)) + RotL64(aCarry, 47U)) + 18031328374429899857U;
            aOrbiterE = ((aWandererI + RotL64(aPrevious, 51U)) + 18261756894092897276U) + RotL64(aNonceByteC, 23U);
            aOrbiterK = (aWandererB + RotL64(aIngress, 34U)) + 4250319792907645666U;
            aOrbiterF = (((aWandererG + RotL64(aScatter, 5U)) + 1492411503643460886U) + aOrbiterAssignSaltB[(((31U - aIndex) + 4603U)) & S_SALT1]) + RotL64(aNonceByteG, 11U);
            aOrbiterA = ((aWandererC + RotL64(aIngress, 29U)) + RotL64(aCarry, 57U)) + 17369549067879344180U;
            aOrbiterG = (aWandererH + RotL64(aCross, 19U)) + 7301713524358676722U;
            aOrbiterB = (aWandererA + RotL64(aScatter, 37U)) + 2985193736033012535U;
            //
            aOrbiterH = ((aOrbiterH + aOrbiterC) + 14086975808140927408U) + RotL64(aNonceByteE, 39U);
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 10390516547834639800U;
            aOrbiterD = RotL64((aOrbiterD * 11441293212275890819U), 43U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 18205555540941493267U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 16967799565443938873U;
            aOrbiterJ = RotL64((aOrbiterJ * 3009081009044782443U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 9209505304067579944U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 3522631966146762306U;
            aOrbiterE = RotL64((aOrbiterE * 3441982898533162599U), 21U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 8811497120829041188U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 14707301680850257294U;
            aOrbiterK = RotL64((aOrbiterK * 11383709499376464085U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 10080595991787801029U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterJ) ^ 6822892187784299166U) ^ aOrbiterUpdateSaltC[((aIndex + 5396U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 7417016898027778287U), 47U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 1981637172055758689U;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 16463077485583119324U;
            aOrbiterA = RotL64((aOrbiterA * 2876782050665869121U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 8383837717361569465U) + aOrbiterUpdateSaltA[((aIndex + 1100U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 2788511294985017326U) ^ RotL64(aNonceByteA, 8U);
            aOrbiterG = RotL64((aOrbiterG * 2809163242875130677U), 51U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 3529607472855930041U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 8850940802020173766U;
            aOrbiterB = RotL64((aOrbiterB * 7821450253655655943U), 13U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 7469160295100147267U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 3338U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 16973986572163482061U;
            aOrbiterH = RotL64((aOrbiterH * 15660743778376905023U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 12371372942863279718U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterG) ^ 12098525148034303633U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 3685U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 11234127652230231751U), 23U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 5138683482859889480U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 3339283916456813609U;
            aOrbiterI = RotL64((aOrbiterI * 10975353228235695455U), 37U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterJ, 19U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterA, 53U));
            aIngress = aIngress + (RotL64(aOrbiterE, 51U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterI, 37U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterK, 28U));
            aIngress = aIngress + RotL64(aOrbiterG, 21U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aPrevious, 43U) + RotL64(aOrbiterE, 43U)) + aOrbiterB);
            aWandererB = aWandererB ^ ((RotL64(aIngress, 34U) + aOrbiterJ) + RotL64(aOrbiterC, 51U));
            aWandererC = aWandererC + (((RotL64(aScatter, 23U) + aOrbiterE) + RotL64(aOrbiterI, 57U)) + RotL64(aCarry, 41U));
            aWandererD = aWandererD ^ (((RotL64(aCross, 39U) + aOrbiterF) + RotL64(aOrbiterH, 11U)) + RotL64(aNonceByteD, 9U));
            aWandererE = aWandererE + ((((RotL64(aPrevious, 5U) + aOrbiterI) + RotL64(aOrbiterF, 23U)) + RotL64(aCarry, 13U)) + RotL64(aNonceByteH, 53U));
            aWandererF = aWandererF ^ (((RotL64(aScatter, 19U) + RotL64(aOrbiterG, 5U)) + aOrbiterD) + aWandererUpdateSaltA[(((31U - aIndex) + 7619U)) & S_SALT1]);
            aWandererG = aWandererG + ((RotL64(aIngress, 41U) + RotL64(aOrbiterK, 36U)) + aOrbiterD);
            aWandererH = aWandererH ^ (((RotL64(aCross, 3U) + RotL64(aOrbiterK, 53U)) + aOrbiterI) + aWandererUpdateSaltB[((aIndex + 3443U)) & S_SALT1]);
            aWandererI = aWandererI + ((RotL64(aPrevious, 53U) + aOrbiterA) + RotL64(aOrbiterI, 21U));
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 10U) + RotL64(aOrbiterF, 27U)) + aOrbiterD);
            aWandererK = aWandererK + ((RotL64(aIngress, 13U) + RotL64(aOrbiterJ, 60U)) + aOrbiterA);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererK, 51U));
            aCarry = aCarry + (RotL64(aWandererJ, 42U) ^ aWandererI);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 37U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererG, 39U));
            aCarry = aCarry + (RotL64(aWandererD, 35U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererA, 13U);
            aCarry = aCarry + RotL64(aIngress, 44U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneF[S_BLOCK1 - aIndex] = aIngress;
        }
    }
};

