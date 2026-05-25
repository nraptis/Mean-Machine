#include "TwistExpander_EdChan_0006.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix64.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmConstants.hpp"

#include <cstring>

TwistExpander_EdChan_0006::TwistExpander_EdChan_0006()
: TwistExpander() {
    mDomainBundleInbuilt.mPhaseASalts = kPhaseASalts;
    mDomainBundleInbuilt.mPhaseAConstants = kPhaseAConstants;
    mDomainBundleInbuilt.mPhaseBSalts = kPhaseBSalts;
    mDomainBundleInbuilt.mPhaseBConstants = kPhaseBConstants;
    mDomainBundleInbuilt.mPhaseCSalts = kPhaseCSalts;
    mDomainBundleInbuilt.mPhaseCConstants = kPhaseCConstants;
    mDomainBundleInbuilt.mPhaseASBoxes = kPhaseASBoxes;
    mDomainBundleInbuilt.mPhaseBSBoxes = kPhaseBSBoxes;
    mDomainBundleInbuilt.mPhaseCSBoxes = kPhaseCSBoxes;
    SyncLegacyFromDomainBundleInbuilt();
    std::memcpy(&mDomainBundleEphemeral, &mDomainBundleInbuilt, sizeof(mDomainBundleEphemeral));
}

void TwistExpander_EdChan_0006::KDF(std::uint64_t pNonce,
                                TwistDomainConstants *pConstants,
                                TwistDomainSaltSet *pDomainSaltSet,
                                TwistDomainSBoxSet *pDomainSBoxSet) {
    KDF_A(pNonce, pConstants, pDomainSaltSet, pDomainSBoxSet);
}

void TwistExpander_EdChan_0006::KDF_A(std::uint64_t pNonce,
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
            aIngress = aIngress ^ (RotL64(aNonceByteA, 35U) ^ RotL64(aNonceByteB, 52U));
            aIngress = aIngress ^ (RotL64(aSource[((aIndex + 15733U)) & S_BLOCK1], 23U) ^ RotL64(aSource[((aIndex + 16349U)) & S_BLOCK1], 13U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 21U) ^ RotL64(aNonceByteD, 29U)) ^ RotL64(aNonceByteE, 51U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 13320U)) & S_BLOCK1], 11U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 2915U)) & S_BLOCK1], 40U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 21U) ^ RotL64(aPrevious, 53U)) + (RotL64(aCross, 4U) + RotL64(aIngress, 41U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = ((aWandererC + RotL64(aIngress, 37U)) + RotL64(aCarry, 23U)) + 3339283916456813609U;
            aOrbiterC = (aWandererD + RotL64(aPrevious, 60U)) + 11339086426180649584U;
            aOrbiterD = ((aWandererE + RotL64(aCross, 47U)) + 16819191669329316585U) + aOrbiterAssignSaltA[((aIndex + 3619U)) & S_SALT1];
            aOrbiterB = ((((aWandererA + RotL64(aScatter, 53U)) + RotL64(aCarry, 51U)) + 8361916937762630725U) + aOrbiterAssignSaltB[((aIndex + 2547U)) & S_SALT1]) + RotL64(aNonceByteC, 37U);
            aOrbiterE = (aWandererI + RotL64(aIngress, 21U)) + 18031328374429899857U;
            aOrbiterG = ((aWandererJ + RotL64(aScatter, 41U)) + 18261756894092897276U) + RotL64(aNonceByteB, 24U);
            aOrbiterF = (aWandererH + RotL64(aPrevious, 39U)) + 4250319792907645666U;
            aOrbiterI = (aWandererB + RotL64(aCross, 3U)) + 1492411503643460886U;
            aOrbiterH = (aWandererG + RotL64(aPrevious, 13U)) + 17369549067879344180U;
            aOrbiterJ = ((aWandererF + RotL64(aCross, 27U)) + RotL64(aCarry, 19U)) + 7301713524358676722U;
            aOrbiterK = (aWandererK + RotL64(aIngress, 50U)) + 2985193736033012535U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 14086975808140927408U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 10390516547834639800U;
            aOrbiterD = RotL64((aOrbiterD * 11441293212275890819U), 51U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 18205555540941493267U) + RotL64(aNonceByteG, 49U);
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 16967799565443938873U;
            aOrbiterG = RotL64((aOrbiterG * 3009081009044782443U), 21U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 9209505304067579944U) + aOrbiterUpdateSaltC[((aIndex + 1368U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 3522631966146762306U;
            aOrbiterA = RotL64((aOrbiterA * 3441982898533162599U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 8811497120829041188U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 14707301680850257294U;
            aOrbiterB = RotL64((aOrbiterB * 11383709499376464085U), 27U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 10080595991787801029U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 6822892187784299166U;
            aOrbiterF = RotL64((aOrbiterF * 7417016898027778287U), 43U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 1981637172055758689U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 16463077485583119324U;
            aOrbiterH = RotL64((aOrbiterH * 2876782050665869121U), 37U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 8383837717361569465U;
            aOrbiterK = (aOrbiterK ^ aOrbiterE) ^ 2788511294985017326U;
            aOrbiterK = RotL64((aOrbiterK * 2809163242875130677U), 41U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 3529607472855930041U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterI) ^ 8850940802020173766U) ^ aOrbiterUpdateSaltA[((aIndex + 1755U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 7821450253655655943U), 53U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterF) + 7469160295100147267U) + RotL64(aNonceByteD, 23U);
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 16973986572163482061U;
            aOrbiterE = RotL64((aOrbiterE * 15660743778376905023U), 3U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 12371372942863279718U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterD) ^ 12098525148034303633U) ^ aOrbiterUpdateSaltD[((aIndex + 6157U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 11234127652230231751U), 29U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterK) + 5138683482859889480U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 196U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 3339283916456813609U;
            aOrbiterJ = RotL64((aOrbiterJ * 10975353228235695455U), 5U);
            //
            aIngress = RotL64(aOrbiterJ, 54U) ^ aOrbiterE;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterD, 35U));
            aIngress = aIngress + (RotL64(aOrbiterG, 23U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterI, 41U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterK, 51U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterC, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aIngress, 5U) + RotL64(aOrbiterH, 50U)) + aOrbiterB);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 37U) + RotL64(aOrbiterG, 11U)) + aOrbiterE);
            aWandererC = aWandererC + (((RotL64(aCross, 41U) + RotL64(aOrbiterH, 5U)) + aOrbiterC) + RotL64(aCarry, 57U));
            aWandererD = aWandererD ^ (((RotL64(aScatter, 56U) + RotL64(aOrbiterH, 35U)) + aOrbiterA) + RotL64(aNonceByteH, 21U));
            aWandererE = aWandererE + ((RotL64(aIngress, 19U) + RotL64(aOrbiterD, 39U)) + aOrbiterH);
            aWandererF = aWandererF ^ (((RotL64(aCross, 23U) + aOrbiterC) + RotL64(aOrbiterJ, 23U)) + aWandererUpdateSaltA[(((31U - aIndex) + 5744U)) & S_SALT1]);
            aWandererG = aWandererG + ((RotL64(aScatter, 11U) + RotL64(aOrbiterK, 21U)) + aOrbiterG);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 39U) + aOrbiterK) + RotL64(aOrbiterD, 57U));
            aWandererI = aWandererI + (((RotL64(aScatter, 43U) + aOrbiterA) + RotL64(aOrbiterK, 14U)) + RotL64(aNonceByteF, 55U));
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 30U) + aOrbiterF) + RotL64(aOrbiterI, 27U)) + aWandererUpdateSaltB[((aIndex + 1946U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aPrevious, 13U) + aOrbiterD) + RotL64(aOrbiterI, 41U)) + RotL64(aCarry, 35U));
            //
            aCarry = aCarry + (RotL64(aWandererG, 37U) ^ aWandererB);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererK, 21U));
            aCarry = aCarry + (RotL64(aWandererJ, 4U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererF, 19U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererD, 53U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererI, 11U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 56U) ^ RotL64(aNonceByteB, 13U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 2942U)) & S_BLOCK1], 29U) ^ RotL64(aSource[((aIndex + 11203U)) & S_BLOCK1], 39U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 43U) ^ RotL64(aNonceByteD, 60U)) ^ RotL64(aNonceByteE, 51U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 12832U)) & S_BLOCK1], 19U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 2252U)) & S_BLOCK1], 29U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 40U) ^ RotL64(aCarry, 57U)) + (RotL64(aIngress, 11U) ^ RotL64(aCross, 27U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = (aWandererH + RotL64(aScatter, 39U)) + 12775735908960052604U;
            aOrbiterE = ((aWandererC + RotL64(aPrevious, 57U)) + 11791373812080296887U) + RotL64(aNonceByteD, 11U);
            aOrbiterA = (aWandererE + RotL64(aIngress, 35U)) + 5537362877706057303U;
            aOrbiterI = (aWandererB + RotL64(aCross, 60U)) + 2023912048504189380U;
            aOrbiterK = (aWandererA + RotL64(aPrevious, 3U)) + 17668828109963766893U;
            aOrbiterH = (aWandererJ + RotL64(aCross, 37U)) + 558908629933941224U;
            aOrbiterF = ((aWandererF + RotL64(aScatter, 29U)) + 1479633119685446888U) + aOrbiterAssignSaltB[((aIndex + 3158U)) & S_SALT1];
            aOrbiterC = (aWandererK + RotL64(aIngress, 5U)) + 15460320397843364063U;
            aOrbiterJ = (((aWandererD + RotL64(aPrevious, 51U)) + RotL64(aCarry, 13U)) + 10059749397555469054U) + RotL64(aNonceByteF, 3U);
            aOrbiterB = ((aWandererI + RotL64(aScatter, 11U)) + RotL64(aCarry, 39U)) + 9987633811929693924U;
            aOrbiterD = (((aWandererG + RotL64(aCross, 54U)) + RotL64(aCarry, 57U)) + 10087337844580228269U) + aOrbiterAssignSaltA[((aIndex + 1198U)) & S_SALT1];
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 4446204415503364254U) + RotL64(aNonceByteA, 53U);
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 15106063243302192717U;
            aOrbiterA = RotL64((aOrbiterA * 13273756657334709803U), 57U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterK) + 9430197906134676162U) + aOrbiterUpdateSaltC[((aIndex + 5319U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 1226048679997253363U;
            aOrbiterE = RotL64((aOrbiterE * 14247538885252664127U), 41U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 10611580584157624739U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 3137391249289641509U;
            aOrbiterK = RotL64((aOrbiterK * 5462682413239873181U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 9327201928815412810U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 7890659377013147073U;
            aOrbiterF = RotL64((aOrbiterF * 13827717178378062047U), 51U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 10675114832750356941U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 8804440385852327267U;
            aOrbiterJ = RotL64((aOrbiterJ * 8520671775587260601U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 12871947817782057116U;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 11015991745792051390U;
            aOrbiterG = RotL64((aOrbiterG * 17152451500505815031U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 6320437975845673731U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 702457937087191287U;
            aOrbiterI = RotL64((aOrbiterI * 17491257114676739589U), 43U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 16629064896250312921U) + RotL64(aNonceByteE, 58U);
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 6054107387816339103U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 4657U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 6983767878966747219U), 3U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 13274874838094190290U;
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 12211422735294360321U;
            aOrbiterC = RotL64((aOrbiterC * 5113738196151089817U), 53U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 15338616110718583619U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 1475787183754511373U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 1466U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 10904607643785840003U), 37U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 15486810401396777742U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 12775735908960052604U) ^ aOrbiterUpdateSaltD[((aIndex + 1321U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 7478156942468930207U), 47U);
            //
            aIngress = RotL64(aOrbiterJ, 34U) ^ aOrbiterC;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterF, 41U));
            aIngress = aIngress + (RotL64(aOrbiterE, 29U) ^ aOrbiterI);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterK, 53U));
            aIngress = aIngress + (RotL64(aOrbiterH, 26U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterD, 57U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aScatter, 18U) + RotL64(aOrbiterD, 39U)) + aOrbiterH) + RotL64(aNonceByteG, 7U));
            aWandererB = aWandererB + ((((RotL64(aCross, 47U) + aOrbiterI) + RotL64(aOrbiterE, 18U)) + RotL64(aCarry, 43U)) + aWandererUpdateSaltB[(((31U - aIndex) + 3087U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aIngress, 13U) + RotL64(aOrbiterJ, 13U)) + aOrbiterA);
            aWandererD = aWandererD + ((((RotL64(aPrevious, 21U) + aOrbiterF) + RotL64(aOrbiterJ, 53U)) + RotL64(aCarry, 29U)) + aWandererUpdateSaltA[((aIndex + 1149U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aScatter, 29U) + RotL64(aOrbiterI, 11U)) + aOrbiterK);
            aWandererF = aWandererF + ((RotL64(aIngress, 27U) + RotL64(aOrbiterB, 23U)) + aOrbiterE);
            aWandererG = aWandererG ^ ((RotL64(aCross, 41U) + aOrbiterJ) + RotL64(aOrbiterC, 5U));
            aWandererH = aWandererH + ((RotL64(aPrevious, 43U) + aOrbiterG) + RotL64(aOrbiterJ, 60U));
            aWandererI = aWandererI ^ ((RotL64(aIngress, 53U) + RotL64(aOrbiterC, 57U)) + aOrbiterG);
            aWandererJ = aWandererJ + ((RotL64(aCross, 4U) + RotL64(aOrbiterE, 37U)) + aOrbiterK);
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 57U) + aOrbiterH) + RotL64(aOrbiterE, 43U)) + RotL64(aNonceByteH, 37U));
            //
            aCarry = aCarry + (RotL64(aWandererF, 43U) ^ aWandererD);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererK, 21U));
            aCarry = aCarry + (RotL64(aWandererC, 14U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererE, 27U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererI, 35U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererH, 19U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 57U) ^ RotL64(aNonceByteB, 35U)) ^ RotL64(aNonceByteC, 24U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 3371U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 15542U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 29U) ^ RotL64(aNonceByteE, 43U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 14736U)) & S_BLOCK1], 58U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 14604U)) & S_BLOCK1], 5U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 19U) + RotL64(aCarry, 39U)) ^ (RotL64(aCross, 5U) ^ RotL64(aIngress, 52U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterJ = (aWandererB + RotL64(aScatter, 50U)) + 5697928251815176134U;
            aOrbiterH = (((aWandererJ + RotL64(aPrevious, 57U)) + RotL64(aCarry, 41U)) + 337587740689259575U) + aOrbiterAssignSaltA[((aIndex + 3204U)) & S_SALT1];
            aOrbiterG = (aWandererE + RotL64(aCross, 41U)) + 4927686903263973950U;
            aOrbiterE = (aWandererA + RotL64(aIngress, 43U)) + 3742409032569801033U;
            aOrbiterC = (aWandererG + RotL64(aPrevious, 29U)) + 1608092659172197650U;
            aOrbiterB = (((aWandererK + RotL64(aScatter, 21U)) + RotL64(aCarry, 35U)) + 15848744267145717509U) + RotL64(aNonceByteG, 45U);
            aOrbiterK = (aWandererH + RotL64(aIngress, 53U)) + 15300174177963339253U;
            aOrbiterI = ((aWandererD + RotL64(aCross, 46U)) + RotL64(aCarry, 19U)) + 14162868453323648628U;
            aOrbiterF = (aWandererI + RotL64(aScatter, 19U)) + 12020167069983729869U;
            aOrbiterD = (((aWandererC + RotL64(aCross, 11U)) + 16259538291658723956U) + aOrbiterAssignSaltB[(((31U - aIndex) + 7575U)) & S_SALT1]) + RotL64(aNonceByteH, 7U);
            aOrbiterA = (aWandererF + RotL64(aIngress, 39U)) + 8516686212464112245U;
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 3722184575520553132U) + RotL64(aNonceByteC, 43U);
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 5663609293306386784U;
            aOrbiterG = RotL64((aOrbiterG * 14364218128780764749U), 3U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 15265344442454471986U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 3050323350098829515U;
            aOrbiterB = RotL64((aOrbiterB * 5890624677162388135U), 53U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 1093356813820599238U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterK) ^ 15167726103772238440U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 1391U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 5719466863561311069U), 11U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 15170797965325981472U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 17826286701992981628U;
            aOrbiterC = RotL64((aOrbiterC * 11186808881726573677U), 19U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterJ) + 14710892030473425181U) + aOrbiterUpdateSaltB[((aIndex + 6341U)) & S_SALT1]) + RotL64(pNonce, 41U);
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 397194787697553904U;
            aOrbiterI = RotL64((aOrbiterI * 14368930300818752833U), 37U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 1273724124862533034U;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 13018397560392545616U;
            aOrbiterD = RotL64((aOrbiterD * 4644812473262395329U), 21U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterK) + 9638716186445643730U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 4251U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 7255587739807843785U;
            aOrbiterJ = RotL64((aOrbiterJ * 6055682981584011189U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 9272350563697399628U;
            aOrbiterE = (aOrbiterE ^ aOrbiterH) ^ 1040729335295009339U;
            aOrbiterE = RotL64((aOrbiterE * 17825687660830291443U), 29U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 12128124729613601747U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 2285238815562202219U;
            aOrbiterK = RotL64((aOrbiterK * 15398840993074390573U), 41U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 6339113298619163493U) + aOrbiterUpdateSaltD[((aIndex + 7558U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 5911895708485037040U;
            aOrbiterF = RotL64((aOrbiterF * 3271006139923200439U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 7601399508218901328U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 5697928251815176134U;
            aOrbiterA = RotL64((aOrbiterA * 8184257916861355735U), 23U);
            //
            aIngress = RotL64(aOrbiterD, 51U) ^ aOrbiterB;
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterJ, 41U));
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterH, 36U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterC, 11U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterE, 57U));
            aIngress = aIngress + RotL64(aOrbiterF, 47U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((((RotL64(aIngress, 37U) + aOrbiterC) + RotL64(aOrbiterI, 21U)) + RotL64(aCarry, 19U)) + aWandererUpdateSaltB[((aIndex + 5107U)) & S_SALT1]);
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 60U) + RotL64(aOrbiterJ, 18U)) + aOrbiterF) + RotL64(aNonceByteB, 29U));
            aWandererC = aWandererC + ((RotL64(aScatter, 57U) + aOrbiterH) + RotL64(aOrbiterJ, 47U));
            aWandererD = aWandererD ^ ((RotL64(aCross, 29U) + RotL64(aOrbiterB, 13U)) + aOrbiterK);
            aWandererE = aWandererE + ((RotL64(aIngress, 43U) + aOrbiterI) + RotL64(aOrbiterK, 57U));
            aWandererF = aWandererF ^ ((RotL64(aScatter, 27U) + aOrbiterE) + RotL64(aOrbiterA, 53U));
            aWandererG = aWandererG + (((RotL64(aPrevious, 35U) + RotL64(aOrbiterC, 3U)) + aOrbiterH) + RotL64(aCarry, 5U));
            aWandererH = aWandererH ^ ((RotL64(aCross, 40U) + RotL64(aOrbiterD, 23U)) + aOrbiterJ);
            aWandererI = aWandererI + ((RotL64(aPrevious, 47U) + aOrbiterK) + RotL64(aOrbiterG, 51U));
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 21U) + RotL64(aOrbiterG, 27U)) + aOrbiterJ) + RotL64(aNonceByteF, 20U));
            aWandererK = aWandererK + (((RotL64(aScatter, 13U) + RotL64(aOrbiterF, 44U)) + aOrbiterA) + aWandererUpdateSaltA[((aIndex + 585U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererK, 44U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererI, 21U));
            aCarry = aCarry + (RotL64(aWandererJ, 27U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererA, 13U) ^ aWandererG);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererD, 51U));
            aCarry = aCarry + RotL64(aWandererE, 48U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 21U) ^ RotL64(aNonceByteB, 48U)) ^ RotL64(aNonceByteC, 29U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 11932U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 1554U)) & S_BLOCK1], 5U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 27U) ^ RotL64(aNonceByteE, 50U)) ^ RotL64(aNonceByteF, 19U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 13980U)) & S_BLOCK1], 41U) ^ RotL64(aSource[((aIndex + 1092U)) & S_BLOCK1], 3U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 54U) ^ RotL64(aPrevious, 37U)) + (RotL64(aIngress, 3U) + RotL64(aCross, 21U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = (aWandererA + RotL64(aPrevious, 13U)) + 17264605017518259932U;
            aOrbiterK = (aWandererF + RotL64(aIngress, 43U)) + 15209184354580778643U;
            aOrbiterJ = ((aWandererE + RotL64(aCross, 37U)) + RotL64(aCarry, 39U)) + 3299527965014731384U;
            aOrbiterE = (aWandererD + RotL64(aScatter, 18U)) + 16293096431816127821U;
            aOrbiterD = (((aWandererK + RotL64(aCross, 39U)) + 11031983436878828337U) + aOrbiterAssignSaltB[(((31U - aIndex) + 5829U)) & S_SALT1]) + RotL64(aNonceByteA, 13U);
            aOrbiterI = ((aWandererI + RotL64(aIngress, 47U)) + 9188018632448236358U) + aOrbiterAssignSaltA[((aIndex + 491U)) & S_SALT1];
            aOrbiterC = ((aWandererH + RotL64(aScatter, 3U)) + RotL64(aCarry, 13U)) + 13420816400363406556U;
            aOrbiterH = (aWandererC + RotL64(aPrevious, 57U)) + 2485063384097917101U;
            aOrbiterB = (aWandererJ + RotL64(aCross, 52U)) + 3089135816938128264U;
            aOrbiterG = ((aWandererB + RotL64(aIngress, 11U)) + 10730544971770435788U) + RotL64(aNonceByteG, 61U);
            aOrbiterA = ((aWandererG + RotL64(aPrevious, 23U)) + RotL64(aCarry, 23U)) + 10431767565618874806U;
            //
            aOrbiterF = ((aOrbiterF + aOrbiterK) + 14883796491656899074U) + aOrbiterUpdateSaltB[((aIndex + 2704U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 13465877783538483706U;
            aOrbiterJ = RotL64((aOrbiterJ * 14311686051108108503U), 47U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 13322163435314643713U;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 3307316600284371955U;
            aOrbiterD = RotL64((aOrbiterD * 12337846092069506365U), 43U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 4950101626975919939U) + aOrbiterUpdateSaltA[((aIndex + 6265U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 2596253994220103666U;
            aOrbiterI = RotL64((aOrbiterI * 7181706961838582889U), 3U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 17961706029559914243U;
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 10321902557977495175U;
            aOrbiterC = RotL64((aOrbiterC * 16189559888625084711U), 53U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 18146616411403012772U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 8414050129421955787U;
            aOrbiterH = RotL64((aOrbiterH * 14879448948196182863U), 35U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 11739172334166341121U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 7936637782633487291U;
            aOrbiterB = RotL64((aOrbiterB * 14940929920543800413U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 3160044627483874242U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterC) ^ 16816384076887379704U) ^ RotL64(aNonceByteD, 25U);
            aOrbiterG = RotL64((aOrbiterG * 5052772186568301951U), 57U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 8101560104988710226U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 8851416379738817624U) ^ RotL64(aNonceByteC, 15U);
            aOrbiterA = RotL64((aOrbiterA * 16767420038937389027U), 11U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterG) + 9941784290055185679U) + aOrbiterUpdateSaltC[((aIndex + 7530U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterB) ^ 14495651885701938495U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 7911U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 1540692851998143607U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 10599676325220702167U;
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 16092000942942971187U;
            aOrbiterK = RotL64((aOrbiterK * 2457268192247656817U), 37U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 16168470945107928109U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 17264605017518259932U;
            aOrbiterE = RotL64((aOrbiterE * 15038386057529909273U), 39U);
            //
            aIngress = RotL64(aOrbiterG, 19U) ^ aOrbiterF;
            aIngress = aIngress + (RotL64(aOrbiterI, 35U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterB, 22U));
            aIngress = aIngress + (RotL64(aOrbiterK, 27U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterE, 51U));
            aIngress = aIngress + RotL64(aOrbiterH, 13U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 53U) + RotL64(aOrbiterB, 14U)) + aOrbiterI);
            aWandererB = aWandererB + (((RotL64(aScatter, 23U) + aOrbiterD) + RotL64(aOrbiterA, 37U)) + RotL64(aCarry, 53U));
            aWandererC = aWandererC ^ (((RotL64(aCross, 35U) + RotL64(aOrbiterB, 3U)) + aOrbiterF) + RotL64(aNonceByteH, 51U));
            aWandererD = aWandererD + ((RotL64(aIngress, 10U) + RotL64(aOrbiterC, 51U)) + aOrbiterE);
            aWandererE = aWandererE ^ ((RotL64(aCross, 13U) + RotL64(aOrbiterF, 24U)) + aOrbiterI);
            aWandererF = aWandererF + (((RotL64(aPrevious, 51U) + RotL64(aOrbiterJ, 35U)) + aOrbiterE) + RotL64(aCarry, 57U));
            aWandererG = aWandererG ^ (((RotL64(aScatter, 19U) + RotL64(aOrbiterC, 29U)) + aOrbiterA) + aWandererUpdateSaltA[(((31U - aIndex) + 3415U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aIngress, 56U) + aOrbiterE) + RotL64(aOrbiterH, 53U));
            aWandererI = aWandererI ^ ((RotL64(aCross, 29U) + RotL64(aOrbiterK, 27U)) + aOrbiterC);
            aWandererJ = aWandererJ + ((((RotL64(aScatter, 5U) + RotL64(aOrbiterE, 57U)) + aOrbiterK) + RotL64(aNonceByteB, 18U)) + aWandererUpdateSaltB[(((31U - aIndex) + 1454U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 27U) + aOrbiterG) + RotL64(aOrbiterK, 47U));
            //
            aCarry = aCarry + (RotL64(aWandererD, 14U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererH, 41U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererG, 35U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererA, 51U) ^ aWandererK);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererE, 10U));
            aCarry = aCarry + RotL64(aWandererB, 39U);
            aCarry = aCarry + RotL64(aIngress, 21U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 43U) ^ RotL64(aNonceByteB, 19U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 12099U)) & S_BLOCK1], 54U) ^ RotL64(aExpandLaneC[((aIndex + 6970U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 29U) ^ RotL64(aNonceByteD, 51U)) ^ RotL64(aNonceByteE, 19U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 8595U)) & S_BLOCK1], 10U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 15251U)) & S_BLOCK1], 37U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 5U) + RotL64(aIngress, 19U)) ^ (RotL64(aPrevious, 57U) ^ RotL64(aCross, 44U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterD = ((aWandererC + RotL64(aPrevious, 54U)) + 11274974230580265396U) + RotL64(aNonceByteG, 29U);
            aOrbiterA = (aWandererJ + RotL64(aScatter, 47U)) + 16658438747342741547U;
            aOrbiterB = (((aWandererE + RotL64(aCross, 21U)) + RotL64(aCarry, 29U)) + 16612986966106053844U) + RotL64(aNonceByteA, 39U);
            aOrbiterJ = (aWandererI + RotL64(aIngress, 27U)) + 9329502236843231290U;
            aOrbiterG = ((aWandererH + RotL64(aCross, 13U)) + 14088261356708344656U) + aOrbiterAssignSaltB[((aIndex + 4115U)) & S_SALT1];
            aOrbiterH = (aWandererK + RotL64(aPrevious, 5U)) + 13692608802007789581U;
            aOrbiterE = ((aWandererF + RotL64(aScatter, 57U)) + RotL64(aCarry, 39U)) + 6824473946645682398U;
            aOrbiterC = (aWandererB + RotL64(aIngress, 37U)) + 2072915876348570040U;
            aOrbiterK = (((aWandererD + RotL64(aPrevious, 18U)) + RotL64(aCarry, 11U)) + 7420507753044460759U) + aOrbiterAssignSaltA[(((31U - aIndex) + 1679U)) & S_SALT1];
            aOrbiterI = (aWandererA + RotL64(aScatter, 23U)) + 4677557318688502593U;
            aOrbiterF = (aWandererG + RotL64(aCross, 3U)) + 15081678577055628459U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterA) + 7026792817486507482U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 7285U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 14871665922943969918U;
            aOrbiterB = RotL64((aOrbiterB * 694073180313083145U), 43U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 6807734532159292872U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 17882797335141303280U;
            aOrbiterH = RotL64((aOrbiterH * 15439872930381050291U), 53U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 9233542707022629190U) + aOrbiterUpdateSaltA[((aIndex + 7112U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 1205501586581350876U;
            aOrbiterC = RotL64((aOrbiterC * 2596053290311090589U), 23U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterH) + 10878718669747466677U) + RotL64(aNonceByteH, 5U);
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 8066049063548639241U;
            aOrbiterI = RotL64((aOrbiterI * 3031382633089381605U), 41U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterC) + 861295180226875235U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 4613U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 9134969787937288583U;
            aOrbiterD = RotL64((aOrbiterD * 7565008208670843555U), 39U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 6726642007159809594U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 8061661744643240470U;
            aOrbiterJ = RotL64((aOrbiterJ * 6703498926835391813U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 13541412083111962884U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 8617442758729315637U;
            aOrbiterE = RotL64((aOrbiterE * 15471862889276160953U), 21U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterJ) + 16884403561131293362U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 9490680911678221233U;
            aOrbiterK = RotL64((aOrbiterK * 15988763830018001033U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 10486145044311386738U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 10200001044821063684U;
            aOrbiterF = RotL64((aOrbiterF * 16149790736141571017U), 5U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterK) + 6997073594007878034U) + aOrbiterUpdateSaltC[((aIndex + 7876U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 13585783612009989767U;
            aOrbiterA = RotL64((aOrbiterA * 11425303157774550449U), 51U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 3847846040256340653U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterI) ^ 11274974230580265396U) ^ RotL64(aNonceByteF, 8U);
            aOrbiterG = RotL64((aOrbiterG * 13970270689108369205U), 37U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterA, 30U);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterG, 23U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterK, 5U));
            aIngress = aIngress + (RotL64(aOrbiterD, 3U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterH, 21U));
            aIngress = aIngress + RotL64(aOrbiterC, 41U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 51U) + RotL64(aOrbiterE, 41U)) + aOrbiterA);
            aWandererB = aWandererB + (((RotL64(aScatter, 44U) + RotL64(aOrbiterG, 29U)) + aOrbiterE) + RotL64(aCarry, 23U));
            aWandererC = aWandererC ^ ((RotL64(aIngress, 37U) + RotL64(aOrbiterB, 13U)) + aOrbiterG);
            aWandererD = aWandererD + ((RotL64(aCross, 21U) + aOrbiterC) + RotL64(aOrbiterE, 51U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 47U) + RotL64(aOrbiterH, 60U)) + aOrbiterK);
            aWandererF = aWandererF + (((RotL64(aCross, 29U) + aOrbiterA) + RotL64(aOrbiterD, 35U)) + RotL64(aNonceByteD, 23U));
            aWandererG = aWandererG ^ ((RotL64(aScatter, 35U) + aOrbiterJ) + RotL64(aOrbiterA, 5U));
            aWandererH = aWandererH + ((((RotL64(aPrevious, 57U) + RotL64(aOrbiterI, 3U)) + aOrbiterB) + RotL64(aCarry, 51U)) + aWandererUpdateSaltA[((aIndex + 5516U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aIngress, 3U) + aOrbiterF) + RotL64(aOrbiterI, 47U));
            aWandererJ = aWandererJ + (((RotL64(aCross, 5U) + RotL64(aOrbiterH, 37U)) + aOrbiterD) + RotL64(aNonceByteE, 21U));
            aWandererK = aWandererK ^ (((RotL64(aScatter, 24U) + RotL64(aOrbiterA, 22U)) + aOrbiterC) + aWandererUpdateSaltB[(((31U - aIndex) + 695U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererK, 52U));
            aCarry = aCarry + (RotL64(aWandererA, 5U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererG, 23U) ^ aWandererD);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererJ, 41U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 30U));
            aCarry = aCarry + RotL64(aWandererE, 13U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneE[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 29U) ^ RotL64(aNonceByteB, 11U));
            aIngress = aIngress ^ (RotL64(aExpandLaneE[((aIndex + 6067U)) & S_BLOCK1], 19U) ^ RotL64(aExpandLaneD[((aIndex + 10815U)) & S_BLOCK1], 40U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 3U) ^ RotL64(aNonceByteD, 41U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 6747U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneB[((aIndex + 946U)) & S_BLOCK1], 24U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 60U) + RotL64(aCarry, 27U)) ^ (RotL64(aPrevious, 13U) ^ RotL64(aCross, 47U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = ((aWandererJ + RotL64(aCross, 39U)) + RotL64(aCarry, 43U)) + 10336802574069791273U;
            aOrbiterC = (((aWandererA + RotL64(aPrevious, 27U)) + 169025388197058936U) + aOrbiterAssignSaltB[((aIndex + 3720U)) & S_SALT1]) + RotL64(aNonceByteE, 13U);
            aOrbiterD = (aWandererF + RotL64(aScatter, 13U)) + 6541354188379168846U;
            aOrbiterI = (((aWandererD + RotL64(aIngress, 34U)) + RotL64(aCarry, 5U)) + 16223920526599306104U) + aOrbiterAssignSaltA[((aIndex + 533U)) & S_SALT1];
            aOrbiterJ = (aWandererE + RotL64(aPrevious, 5U)) + 12756613707692514808U;
            aOrbiterE = (aWandererB + RotL64(aCross, 51U)) + 5082475548176484035U;
            aOrbiterK = (aWandererK + RotL64(aIngress, 47U)) + 4907435526952698526U;
            aOrbiterF = ((aWandererC + RotL64(aScatter, 19U)) + RotL64(aCarry, 29U)) + 14236627073831834337U;
            aOrbiterA = ((aWandererH + RotL64(aCross, 36U)) + 11502511046130497584U) + RotL64(aNonceByteA, 55U);
            aOrbiterG = (aWandererI + RotL64(aScatter, 43U)) + 3679044835550219497U;
            aOrbiterB = (aWandererG + RotL64(aIngress, 53U)) + 11254838916686736746U;
            //
            aOrbiterH = ((aOrbiterH + aOrbiterC) + 10582608424233200966U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 5507U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 10449735026385340313U;
            aOrbiterD = RotL64((aOrbiterD * 7363770199734997411U), 43U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 4628253464169957835U;
            aOrbiterJ = (((aOrbiterJ ^ aOrbiterC) ^ 17664454668473204465U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 7812U)) & S_SALT1]) ^ RotL64(aNonceByteB, 37U);
            aOrbiterJ = RotL64((aOrbiterJ * 4234720298731378527U), 53U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 3798386391743884889U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 1379331161819246587U;
            aOrbiterE = RotL64((aOrbiterE * 13086160171095077295U), 3U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 9816600392407327227U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 16781971616348376878U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 7431U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 12503867584828289879U), 5U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 4807797577690520554U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterJ) ^ 2492057261148595922U) ^ aOrbiterUpdateSaltD[((aIndex + 6828U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 9453302540675483005U), 39U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 7909676419643119585U;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 256053568910383007U;
            aOrbiterA = RotL64((aOrbiterA * 11965085163352053161U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 16179914439220412472U;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 3968867762761955845U;
            aOrbiterG = RotL64((aOrbiterG * 7473632378251893139U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 7474832923901283742U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 4736994731050735779U;
            aOrbiterB = RotL64((aOrbiterB * 9839654409121414047U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 596484364660389193U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 13822222274464306169U;
            aOrbiterH = RotL64((aOrbiterH * 1723502278319885511U), 47U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterB) + 16307920280681985443U) + RotL64(aNonceByteF, 40U);
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 3505106171801702915U;
            aOrbiterC = RotL64((aOrbiterC * 8479675421552861243U), 27U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 4987142580981135150U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 10336802574069791273U;
            aOrbiterI = RotL64((aOrbiterI * 2670706512498539705U), 37U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterD, 39U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 58U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterI, 43U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterH, 35U));
            aIngress = aIngress + (RotL64(aOrbiterE, 13U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterK, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aIngress, 19U) + aOrbiterB) + RotL64(aOrbiterF, 24U));
            aWandererB = aWandererB + ((RotL64(aScatter, 35U) + RotL64(aOrbiterG, 51U)) + aOrbiterD);
            aWandererC = aWandererC ^ ((RotL64(aCross, 13U) + RotL64(aOrbiterH, 11U)) + aOrbiterE);
            aWandererD = aWandererD + ((((RotL64(aPrevious, 21U) + RotL64(aOrbiterF, 47U)) + aOrbiterC) + RotL64(aCarry, 29U)) + aWandererUpdateSaltA[((aIndex + 2797U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 40U) + RotL64(aOrbiterH, 5U)) + aOrbiterA);
            aWandererF = aWandererF + ((((RotL64(aScatter, 57U) + RotL64(aOrbiterK, 3U)) + aOrbiterF) + RotL64(aCarry, 43U)) + aWandererUpdateSaltB[((aIndex + 4395U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 23U) + RotL64(aOrbiterI, 35U)) + aOrbiterD);
            aWandererH = aWandererH + (((RotL64(aPrevious, 37U) + aOrbiterG) + RotL64(aOrbiterE, 56U)) + RotL64(aNonceByteH, 61U));
            aWandererI = aWandererI ^ ((RotL64(aIngress, 51U) + RotL64(aOrbiterC, 19U)) + aOrbiterK);
            aWandererJ = aWandererJ + ((RotL64(aPrevious, 60U) + aOrbiterB) + RotL64(aOrbiterJ, 29U));
            aWandererK = aWandererK ^ (((RotL64(aScatter, 43U) + aOrbiterD) + RotL64(aOrbiterH, 37U)) + RotL64(aNonceByteG, 15U));
            //
            aCarry = aCarry + (RotL64(aWandererH, 53U) ^ aWandererA);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererJ, 27U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererE, 30U));
            aCarry = aCarry + (RotL64(aWandererK, 11U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererD, 19U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererG, 39U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneF[S_BLOCK1 - aIndex] = aIngress;
        }
    }
}

void TwistExpander_EdChan_0006::KDF_B(std::uint64_t pNonce,
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
            aIngress = aIngress ^ (RotL64(aNonceByteA, 5U) ^ RotL64(aNonceByteB, 22U));
            aIngress = aIngress ^ (RotL64(aSource[((aIndex + 338U)) & S_BLOCK1], 35U) ^ RotL64(aSource[((aIndex + 14534U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 3U) ^ RotL64(aNonceByteD, 21U)) ^ RotL64(aNonceByteE, 35U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 5538U)) & S_BLOCK1], 52U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 5113U)) & S_BLOCK1], 43U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 35U) + RotL64(aIngress, 19U)) + (RotL64(aCross, 6U) ^ RotL64(aPrevious, 47U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = ((aWandererA + RotL64(aCross, 11U)) + RotL64(aCarry, 57U)) + 3339283916456813609U;
            aOrbiterC = (aWandererH + RotL64(aPrevious, 20U)) + 11339086426180649584U;
            aOrbiterD = ((aWandererG + RotL64(aScatter, 37U)) + 16819191669329316585U) + aOrbiterAssignSaltA[(((31U - aIndex) + 3029U)) & S_SALT1];
            aOrbiterB = (aWandererB + RotL64(aIngress, 29U)) + 8361916937762630725U;
            aOrbiterE = (aWandererF + RotL64(aPrevious, 41U)) + 18031328374429899857U;
            aOrbiterG = ((aWandererC + RotL64(aCross, 43U)) + 18261756894092897276U) + RotL64(aNonceByteH, 13U);
            aOrbiterF = ((aWandererJ + RotL64(aScatter, 57U)) + 4250319792907645666U) + aOrbiterAssignSaltB[((aIndex + 6106U)) & S_SALT1];
            aOrbiterI = ((aWandererE + RotL64(aIngress, 39U)) + RotL64(aCarry, 13U)) + 1492411503643460886U;
            aOrbiterH = (aWandererK + RotL64(aCross, 60U)) + 17369549067879344180U;
            aOrbiterJ = ((aWandererD + RotL64(aPrevious, 5U)) + 7301713524358676722U) + RotL64(aNonceByteG, 17U);
            aOrbiterK = ((aWandererI + RotL64(aScatter, 27U)) + RotL64(aCarry, 21U)) + 2985193736033012535U;
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 14086975808140927408U) + aOrbiterUpdateSaltB[((aIndex + 2019U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 10390516547834639800U) ^ aOrbiterUpdateSaltD[((aIndex + 1107U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 11441293212275890819U), 43U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 18205555540941493267U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 16967799565443938873U) ^ aOrbiterUpdateSaltA[((aIndex + 6982U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 3009081009044782443U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 9209505304067579944U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 3522631966146762306U) ^ RotL64(aNonceByteA, 31U);
            aOrbiterA = RotL64((aOrbiterA * 3441982898533162599U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 8811497120829041188U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 14707301680850257294U;
            aOrbiterB = RotL64((aOrbiterB * 11383709499376464085U), 21U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 10080595991787801029U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 6822892187784299166U;
            aOrbiterF = RotL64((aOrbiterF * 7417016898027778287U), 47U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 1981637172055758689U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 16463077485583119324U;
            aOrbiterH = RotL64((aOrbiterH * 2876782050665869121U), 29U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 8383837717361569465U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterE) ^ 2788511294985017326U) ^ RotL64(aNonceByteE, 29U);
            aOrbiterK = RotL64((aOrbiterK * 2809163242875130677U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 3529607472855930041U;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 8850940802020173766U;
            aOrbiterC = RotL64((aOrbiterC * 7821450253655655943U), 19U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterF) + 7469160295100147267U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 7671U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 16973986572163482061U;
            aOrbiterE = RotL64((aOrbiterE * 15660743778376905023U), 37U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 12371372942863279718U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 12098525148034303633U;
            aOrbiterI = RotL64((aOrbiterI * 11234127652230231751U), 11U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 5138683482859889480U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 3339283916456813609U;
            aOrbiterJ = RotL64((aOrbiterJ * 10975353228235695455U), 5U);
            //
            aIngress = RotL64(aOrbiterK, 47U) ^ aOrbiterE;
            aIngress = aIngress + (RotL64(aOrbiterA, 10U) ^ aOrbiterD);
            aIngress = aIngress + (RotL64(aOrbiterH, 41U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterF, 51U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterI, 53U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterB, 19U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aScatter, 35U) + aOrbiterC) + RotL64(aOrbiterA, 57U));
            aWandererB = aWandererB + ((((RotL64(aPrevious, 39U) + aOrbiterJ) + RotL64(aOrbiterC, 28U)) + RotL64(aNonceByteF, 47U)) + aWandererUpdateSaltA[(((31U - aIndex) + 1394U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aCross, 29U) + RotL64(aOrbiterB, 35U)) + aOrbiterD);
            aWandererD = aWandererD + ((((RotL64(aIngress, 54U) + aOrbiterG) + RotL64(aOrbiterB, 3U)) + RotL64(aCarry, 23U)) + RotL64(aNonceByteB, 12U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 47U) + aOrbiterE) + RotL64(aOrbiterA, 41U));
            aWandererF = aWandererF + ((RotL64(aCross, 37U) + RotL64(aOrbiterD, 23U)) + aOrbiterF);
            aWandererG = aWandererG ^ ((RotL64(aIngress, 11U) + RotL64(aOrbiterJ, 5U)) + aOrbiterH);
            aWandererH = aWandererH + ((((RotL64(aScatter, 22U) + RotL64(aOrbiterG, 11U)) + aOrbiterA) + RotL64(aCarry, 35U)) + aWandererUpdateSaltB[(((31U - aIndex) + 2532U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aCross, 19U) + aOrbiterE) + RotL64(aOrbiterG, 21U));
            aWandererJ = aWandererJ + ((RotL64(aScatter, 57U) + aOrbiterE) + RotL64(aOrbiterI, 19U));
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 13U) + RotL64(aOrbiterE, 38U)) + aOrbiterK);
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererH, 53U));
            aCarry = aCarry + (RotL64(aWandererK, 39U) ^ aWandererF);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererI, 18U));
            aCarry = aCarry + (RotL64(aWandererG, 11U) ^ aWandererE);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererB, 43U));
            aCarry = aCarry + RotL64(aWandererJ, 13U);
            aCarry = aCarry + RotL64(aIngress, 22U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 11U) ^ RotL64(aNonceByteB, 43U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 3212U)) & S_BLOCK1], 24U) ^ RotL64(aSource[((aIndex + 16374U)) & S_BLOCK1], 51U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 53U) ^ RotL64(aNonceByteD, 3U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 14813U)) & S_BLOCK1], 28U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 13821U)) & S_BLOCK1], 37U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 39U) ^ RotL64(aCross, 23U)) + (RotL64(aIngress, 4U) ^ RotL64(aCarry, 51U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = (aWandererB + RotL64(aCross, 3U)) + 10336802574069791273U;
            aOrbiterE = ((aWandererJ + RotL64(aIngress, 47U)) + RotL64(aCarry, 29U)) + 169025388197058936U;
            aOrbiterA = ((aWandererF + RotL64(aScatter, 41U)) + 6541354188379168846U) + RotL64(aNonceByteC, 15U);
            aOrbiterI = (aWandererD + RotL64(aPrevious, 5U)) + 16223920526599306104U;
            aOrbiterK = (((aWandererG + RotL64(aCross, 58U)) + RotL64(aCarry, 39U)) + 12756613707692514808U) + RotL64(aNonceByteH, 19U);
            aOrbiterH = (aWandererH + RotL64(aIngress, 35U)) + 5082475548176484035U;
            aOrbiterF = (aWandererK + RotL64(aPrevious, 21U)) + 4907435526952698526U;
            aOrbiterC = (((aWandererA + RotL64(aScatter, 37U)) + RotL64(aCarry, 43U)) + 14236627073831834337U) + aOrbiterAssignSaltB[((aIndex + 314U)) & S_SALT1];
            aOrbiterJ = (aWandererE + RotL64(aCross, 51U)) + 11502511046130497584U;
            aOrbiterB = (aWandererC + RotL64(aIngress, 54U)) + 3679044835550219497U;
            aOrbiterD = ((aWandererI + RotL64(aPrevious, 19U)) + 11254838916686736746U) + aOrbiterAssignSaltA[((aIndex + 4465U)) & S_SALT1];
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 10582608424233200966U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterG) ^ 10449735026385340313U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 6009U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 7363770199734997411U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 4628253464169957835U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 17664454668473204465U) ^ aOrbiterUpdateSaltB[((aIndex + 3736U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 4234720298731378527U), 39U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 3798386391743884889U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 1379331161819246587U;
            aOrbiterK = RotL64((aOrbiterK * 13086160171095077295U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 9816600392407327227U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 16781971616348376878U;
            aOrbiterF = RotL64((aOrbiterF * 12503867584828289879U), 57U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 4807797577690520554U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 2492057261148595922U;
            aOrbiterJ = RotL64((aOrbiterJ * 9453302540675483005U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 7909676419643119585U;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 256053568910383007U;
            aOrbiterG = RotL64((aOrbiterG * 11965085163352053161U), 21U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 16179914439220412472U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterA) ^ 3968867762761955845U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 5071U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 7473632378251893139U), 41U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 7474832923901283742U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 502U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 4736994731050735779U;
            aOrbiterH = RotL64((aOrbiterH * 9839654409121414047U), 37U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 596484364660389193U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 13822222274464306169U) ^ RotL64(aNonceByteE, 25U);
            aOrbiterC = RotL64((aOrbiterC * 1723502278319885511U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 16307920280681985443U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 3505106171801702915U) ^ RotL64(aNonceByteF, 55U);
            aOrbiterB = RotL64((aOrbiterB * 8479675421552861243U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 4987142580981135150U;
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 10336802574069791273U;
            aOrbiterD = RotL64((aOrbiterD * 2670706512498539705U), 23U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterH, 21U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 27U) ^ aOrbiterD);
            aIngress = aIngress + (RotL64(aOrbiterE, 57U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterA, 39U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterG, 47U));
            aIngress = aIngress + RotL64(aOrbiterC, 12U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aPrevious, 29U) + RotL64(aOrbiterB, 27U)) + aOrbiterD) + RotL64(aCarry, 27U));
            aWandererB = aWandererB ^ ((RotL64(aIngress, 47U) + aOrbiterC) + RotL64(aOrbiterF, 41U));
            aWandererC = aWandererC + (((((RotL64(aCross, 41U) + aOrbiterF) + RotL64(aOrbiterD, 21U)) + RotL64(aCarry, 13U)) + RotL64(aNonceByteA, 22U)) + aWandererUpdateSaltB[((aIndex + 571U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aScatter, 35U) + aOrbiterE) + RotL64(aOrbiterH, 19U));
            aWandererE = aWandererE + ((RotL64(aIngress, 11U) + aOrbiterA) + RotL64(aOrbiterE, 43U));
            aWandererF = aWandererF ^ ((RotL64(aCross, 60U) + RotL64(aOrbiterJ, 56U)) + aOrbiterB);
            aWandererG = aWandererG + ((RotL64(aScatter, 13U) + RotL64(aOrbiterE, 51U)) + aOrbiterK);
            aWandererH = aWandererH ^ ((((RotL64(aPrevious, 3U) + aOrbiterH) + RotL64(aOrbiterD, 29U)) + RotL64(aNonceByteG, 39U)) + aWandererUpdateSaltA[((aIndex + 6U)) & S_SALT1]);
            aWandererI = aWandererI + ((RotL64(aCross, 21U) + aOrbiterG) + RotL64(aOrbiterA, 53U));
            aWandererJ = aWandererJ ^ ((RotL64(aIngress, 39U) + aOrbiterJ) + RotL64(aOrbiterG, 5U));
            aWandererK = aWandererK + ((RotL64(aPrevious, 44U) + RotL64(aOrbiterD, 38U)) + aOrbiterI);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererD, 56U));
            aCarry = aCarry + (RotL64(aWandererA, 19U) ^ aWandererB);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererF, 39U));
            aCarry = aCarry + (RotL64(aWandererE, 13U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererJ, 21U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererI, 47U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 51U) ^ RotL64(aNonceByteB, 37U)) ^ RotL64(aNonceByteC, 29U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 1799U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 2234U)) & S_BLOCK1], 20U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 35U) ^ RotL64(aNonceByteE, 18U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 1845U)) & S_BLOCK1], 27U) ^ RotL64(aExpandLaneB[((aIndex + 9940U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 5U) + RotL64(aIngress, 57U)) ^ (RotL64(aPrevious, 43U) ^ RotL64(aCross, 18U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterJ = ((aWandererB + RotL64(aIngress, 41U)) + 12775735908960052604U) + RotL64(aNonceByteG, 51U);
            aOrbiterH = (aWandererC + RotL64(aPrevious, 5U)) + 11791373812080296887U;
            aOrbiterG = (aWandererF + RotL64(aScatter, 43U)) + 5537362877706057303U;
            aOrbiterE = (aWandererK + RotL64(aCross, 13U)) + 2023912048504189380U;
            aOrbiterC = (aWandererI + RotL64(aIngress, 19U)) + 17668828109963766893U;
            aOrbiterB = ((aWandererA + RotL64(aCross, 46U)) + 558908629933941224U) + aOrbiterAssignSaltA[((aIndex + 1245U)) & S_SALT1];
            aOrbiterK = (((aWandererG + RotL64(aScatter, 37U)) + RotL64(aCarry, 23U)) + 1479633119685446888U) + aOrbiterAssignSaltB[((aIndex + 7619U)) & S_SALT1];
            aOrbiterI = (aWandererH + RotL64(aPrevious, 27U)) + 15460320397843364063U;
            aOrbiterF = ((aWandererD + RotL64(aIngress, 39U)) + RotL64(aCarry, 13U)) + 10059749397555469054U;
            aOrbiterD = (aWandererJ + RotL64(aCross, 57U)) + 9987633811929693924U;
            aOrbiterA = (((aWandererE + RotL64(aPrevious, 52U)) + RotL64(aCarry, 51U)) + 10087337844580228269U) + RotL64(aNonceByteB, 15U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 4446204415503364254U) + aOrbiterUpdateSaltB[((aIndex + 5083U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 15106063243302192717U;
            aOrbiterG = RotL64((aOrbiterG * 13273756657334709803U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 9430197906134676162U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 1226048679997253363U;
            aOrbiterB = RotL64((aOrbiterB * 14247538885252664127U), 23U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterI) + 10611580584157624739U) + aOrbiterUpdateSaltA[((aIndex + 1783U)) & S_SALT1];
            aOrbiterH = ((aOrbiterH ^ aOrbiterK) ^ 3137391249289641509U) ^ RotL64(aNonceByteH, 20U);
            aOrbiterH = RotL64((aOrbiterH * 5462682413239873181U), 37U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 9327201928815412810U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 7890659377013147073U;
            aOrbiterC = RotL64((aOrbiterC * 13827717178378062047U), 41U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 10675114832750356941U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 8804440385852327267U;
            aOrbiterI = RotL64((aOrbiterI * 8520671775587260601U), 19U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 12871947817782057116U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 2153U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 11015991745792051390U) ^ aOrbiterUpdateSaltC[((aIndex + 5785U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 17152451500505815031U), 39U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 6320437975845673731U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 702457937087191287U;
            aOrbiterJ = RotL64((aOrbiterJ * 17491257114676739589U), 3U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 16629064896250312921U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 6054107387816339103U) ^ RotL64(aNonceByteF, 41U);
            aOrbiterE = RotL64((aOrbiterE * 6983767878966747219U), 27U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 13274874838094190290U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 12211422735294360321U;
            aOrbiterK = RotL64((aOrbiterK * 5113738196151089817U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 15338616110718583619U;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 1475787183754511373U;
            aOrbiterF = RotL64((aOrbiterF * 10904607643785840003U), 51U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 15486810401396777742U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 12775735908960052604U;
            aOrbiterA = RotL64((aOrbiterA * 7478156942468930207U), 57U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterB, 3U);
            aIngress = aIngress + (RotL64(aOrbiterK, 19U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterJ, 27U) ^ aOrbiterA);
            aIngress = aIngress + (RotL64(aOrbiterD, 6U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterF, 53U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterG, 57U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((((RotL64(aCross, 53U) + RotL64(aOrbiterK, 21U)) + aOrbiterD) + RotL64(aCarry, 37U)) + aWandererUpdateSaltA[((aIndex + 732U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 30U) + RotL64(aOrbiterF, 3U)) + aOrbiterB);
            aWandererC = aWandererC + ((RotL64(aPrevious, 41U) + aOrbiterH) + RotL64(aOrbiterE, 54U));
            aWandererD = aWandererD ^ ((RotL64(aIngress, 11U) + RotL64(aOrbiterF, 27U)) + aOrbiterK);
            aWandererE = aWandererE + ((RotL64(aCross, 21U) + RotL64(aOrbiterJ, 51U)) + aOrbiterA);
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 19U) + aOrbiterC) + RotL64(aOrbiterG, 13U));
            aWandererG = aWandererG + ((((RotL64(aScatter, 43U) + aOrbiterJ) + RotL64(aOrbiterF, 35U)) + RotL64(aCarry, 11U)) + RotL64(aNonceByteA, 19U));
            aWandererH = aWandererH ^ ((RotL64(aIngress, 36U) + RotL64(aOrbiterE, 57U)) + aOrbiterG);
            aWandererI = aWandererI + (((RotL64(aCross, 39U) + aOrbiterG) + RotL64(aOrbiterB, 43U)) + aWandererUpdateSaltB[(((31U - aIndex) + 3117U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aPrevious, 23U) + RotL64(aOrbiterA, 47U)) + aOrbiterD) + RotL64(pNonce, 7U));
            aWandererK = aWandererK + ((RotL64(aScatter, 3U) + aOrbiterA) + RotL64(aOrbiterI, 24U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 37U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererK, 39U) ^ aWandererC);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererJ, 4U));
            aCarry = aCarry + (RotL64(aWandererA, 47U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererI, 11U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererD, 27U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 5U) ^ RotL64(aNonceByteB, 28U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 11529U)) & S_BLOCK1], 53U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 11213U)) & S_BLOCK1], 37U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 57U) ^ RotL64(aNonceByteD, 23U)) ^ RotL64(aNonceByteE, 38U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 9479U)) & S_BLOCK1], 11U) ^ RotL64(aSource[((aIndex + 6500U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 18U) + RotL64(aCross, 3U)) ^ (RotL64(aCarry, 53U) ^ RotL64(aPrevious, 37U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = ((aWandererB + RotL64(aPrevious, 24U)) + RotL64(aCarry, 57U)) + 17264605017518259932U;
            aOrbiterK = ((aWandererE + RotL64(aCross, 35U)) + 15209184354580778643U) + aOrbiterAssignSaltB[((aIndex + 4966U)) & S_SALT1];
            aOrbiterJ = ((aWandererH + RotL64(aScatter, 13U)) + 3299527965014731384U) + RotL64(aNonceByteC, 25U);
            aOrbiterE = ((aWandererK + RotL64(aIngress, 41U)) + RotL64(aCarry, 27U)) + 16293096431816127821U;
            aOrbiterD = (aWandererI + RotL64(aScatter, 50U)) + 11031983436878828337U;
            aOrbiterI = ((aWandererD + RotL64(aCross, 43U)) + RotL64(aCarry, 11U)) + 9188018632448236358U;
            aOrbiterC = ((aWandererJ + RotL64(aPrevious, 39U)) + 13420816400363406556U) + RotL64(aNonceByteF, 5U);
            aOrbiterH = (aWandererG + RotL64(aIngress, 21U)) + 2485063384097917101U;
            aOrbiterB = (aWandererC + RotL64(aPrevious, 47U)) + 3089135816938128264U;
            aOrbiterG = (aWandererA + RotL64(aIngress, 5U)) + 10730544971770435788U;
            aOrbiterA = ((aWandererF + RotL64(aScatter, 57U)) + 10431767565618874806U) + aOrbiterAssignSaltA[((aIndex + 3865U)) & S_SALT1];
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 14883796491656899074U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterF) ^ 13465877783538483706U) ^ RotL64(aNonceByteB, 31U);
            aOrbiterJ = RotL64((aOrbiterJ * 14311686051108108503U), 3U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 13322163435314643713U) + aOrbiterUpdateSaltA[((aIndex + 3172U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterK) ^ 3307316600284371955U) ^ aOrbiterUpdateSaltC[((aIndex + 4329U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 12337846092069506365U), 53U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 4950101626975919939U;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 2596253994220103666U;
            aOrbiterI = RotL64((aOrbiterI * 7181706961838582889U), 13U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 17961706029559914243U;
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 10321902557977495175U;
            aOrbiterC = RotL64((aOrbiterC * 16189559888625084711U), 27U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 18146616411403012772U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterD) ^ 8414050129421955787U) ^ aOrbiterUpdateSaltD[((aIndex + 1838U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 14879448948196182863U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 11739172334166341121U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 7936637782633487291U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 6035U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 14940929920543800413U), 29U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 3160044627483874242U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 16816384076887379704U;
            aOrbiterG = RotL64((aOrbiterG * 5052772186568301951U), 5U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 8101560104988710226U;
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 8851416379738817624U;
            aOrbiterA = RotL64((aOrbiterA * 16767420038937389027U), 47U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 9941784290055185679U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterB) ^ 14495651885701938495U) ^ RotL64(aNonceByteE, 35U);
            aOrbiterF = RotL64((aOrbiterF * 1540692851998143607U), 21U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 10599676325220702167U;
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 16092000942942971187U;
            aOrbiterK = RotL64((aOrbiterK * 2457268192247656817U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 16168470945107928109U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 17264605017518259932U;
            aOrbiterE = RotL64((aOrbiterE * 15038386057529909273U), 35U);
            //
            aIngress = RotL64(aOrbiterK, 27U) ^ aOrbiterH;
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterC, 58U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterE, 53U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterF, 11U));
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterA, 29U));
            aIngress = aIngress + RotL64(aOrbiterG, 19U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aCross, 41U) + aOrbiterD) + RotL64(aOrbiterJ, 27U));
            aWandererB = aWandererB + ((RotL64(aIngress, 37U) + RotL64(aOrbiterB, 29U)) + aOrbiterK);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 50U) + RotL64(aOrbiterI, 43U)) + aOrbiterA);
            aWandererD = aWandererD + (((RotL64(aScatter, 21U) + RotL64(aOrbiterD, 50U)) + aOrbiterA) + RotL64(aCarry, 51U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 35U) + aOrbiterF) + RotL64(aOrbiterK, 21U));
            aWandererF = aWandererF + ((RotL64(aScatter, 43U) + aOrbiterJ) + RotL64(aOrbiterA, 23U));
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 3U) + RotL64(aOrbiterB, 57U)) + aOrbiterG) + RotL64(aNonceByteG, 47U));
            aWandererH = aWandererH + ((((RotL64(aCross, 57U) + aOrbiterC) + RotL64(aOrbiterE, 5U)) + RotL64(aCarry, 29U)) + aWandererUpdateSaltB[(((31U - aIndex) + 5933U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aScatter, 47U) + aOrbiterG) + RotL64(aOrbiterK, 41U)) + aWandererUpdateSaltA[((aIndex + 4771U)) & S_SALT1]);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 39U) + aOrbiterE) + RotL64(aOrbiterI, 10U)) + RotL64(aNonceByteH, 20U));
            aWandererK = aWandererK ^ ((RotL64(aCross, 10U) + aOrbiterF) + RotL64(aOrbiterH, 3U));
            //
            aCarry = aCarry + (RotL64(aWandererG, 27U) ^ aWandererB);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererD, 38U));
            aCarry = aCarry + (RotL64(aWandererA, 19U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererE, 23U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererI, 53U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererJ, 56U);
            aCarry = aCarry + RotL64(aIngress, 41U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 29U) ^ RotL64(aNonceByteB, 21U)) ^ RotL64(aNonceByteC, 41U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 12967U)) & S_BLOCK1], 60U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 818U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 35U) ^ RotL64(aNonceByteE, 51U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 8391U)) & S_BLOCK1], 22U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 15199U)) & S_BLOCK1], 13U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 56U) ^ RotL64(aCross, 5U)) + (RotL64(aCarry, 19U) ^ RotL64(aIngress, 43U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterD = ((aWandererI + RotL64(aIngress, 27U)) + RotL64(aCarry, 41U)) + 11274974230580265396U;
            aOrbiterA = ((aWandererJ + RotL64(aScatter, 38U)) + RotL64(aCarry, 3U)) + 16658438747342741547U;
            aOrbiterB = ((aWandererF + RotL64(aCross, 19U)) + 16612986966106053844U) + aOrbiterAssignSaltB[(((31U - aIndex) + 2126U)) & S_SALT1];
            aOrbiterJ = ((aWandererE + RotL64(aPrevious, 53U)) + RotL64(aCarry, 23U)) + 9329502236843231290U;
            aOrbiterG = (aWandererK + RotL64(aCross, 11U)) + 14088261356708344656U;
            aOrbiterH = ((aWandererD + RotL64(aPrevious, 5U)) + 13692608802007789581U) + RotL64(aNonceByteG, 38U);
            aOrbiterE = ((aWandererA + RotL64(aScatter, 3U)) + 6824473946645682398U) + RotL64(aNonceByteH, 39U);
            aOrbiterC = (aWandererC + RotL64(aIngress, 29U)) + 2072915876348570040U;
            aOrbiterK = (aWandererH + RotL64(aPrevious, 21U)) + 7420507753044460759U;
            aOrbiterI = (aWandererB + RotL64(aCross, 41U)) + 4677557318688502593U;
            aOrbiterF = ((aWandererG + RotL64(aIngress, 50U)) + 15081678577055628459U) + aOrbiterAssignSaltA[(((31U - aIndex) + 1147U)) & S_SALT1];
            //
            aOrbiterD = ((aOrbiterD + aOrbiterA) + 7026792817486507482U) + RotL64(aNonceByteF, 61U);
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 14871665922943969918U) ^ aOrbiterUpdateSaltC[((aIndex + 4749U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 694073180313083145U), 41U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 6807734532159292872U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterJ) ^ 17882797335141303280U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 5172U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 15439872930381050291U), 13U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 9233542707022629190U) + RotL64(aNonceByteD, 17U);
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 1205501586581350876U;
            aOrbiterC = RotL64((aOrbiterC * 2596053290311090589U), 37U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 10878718669747466677U;
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 8066049063548639241U;
            aOrbiterI = RotL64((aOrbiterI * 3031382633089381605U), 11U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 861295180226875235U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 9134969787937288583U;
            aOrbiterD = RotL64((aOrbiterD * 7565008208670843555U), 53U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 6726642007159809594U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 8061661744643240470U;
            aOrbiterJ = RotL64((aOrbiterJ * 6703498926835391813U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 13541412083111962884U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 8617442758729315637U;
            aOrbiterE = RotL64((aOrbiterE * 15471862889276160953U), 27U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterJ) + 16884403561131293362U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 2695U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterB) ^ 9490680911678221233U) ^ aOrbiterUpdateSaltA[((aIndex + 1621U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 15988763830018001033U), 43U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 10486145044311386738U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 10200001044821063684U;
            aOrbiterF = RotL64((aOrbiterF * 16149790736141571017U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 6997073594007878034U;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 13585783612009989767U;
            aOrbiterA = RotL64((aOrbiterA * 11425303157774550449U), 5U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 3847846040256340653U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 11274974230580265396U;
            aOrbiterG = RotL64((aOrbiterG * 13970270689108369205U), 57U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterF, 27U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterJ, 41U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterH, 13U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterD, 29U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterC, 53U));
            aIngress = aIngress + RotL64(aOrbiterG, 50U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aIngress, 13U) + aOrbiterG) + RotL64(aOrbiterK, 52U));
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 60U) + RotL64(aOrbiterA, 5U)) + aOrbiterH) + RotL64(aNonceByteA, 9U));
            aWandererC = aWandererC + ((RotL64(aCross, 23U) + aOrbiterE) + RotL64(aOrbiterA, 39U));
            aWandererD = aWandererD ^ ((RotL64(aScatter, 29U) + aOrbiterA) + RotL64(aOrbiterJ, 23U));
            aWandererE = aWandererE + ((RotL64(aIngress, 43U) + RotL64(aOrbiterB, 13U)) + aOrbiterJ);
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 39U) + RotL64(aOrbiterK, 19U)) + aOrbiterD);
            aWandererG = aWandererG + ((((RotL64(aCross, 58U) + RotL64(aOrbiterE, 3U)) + aOrbiterC) + RotL64(aCarry, 3U)) + aWandererUpdateSaltB[((aIndex + 5238U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aScatter, 11U) + aOrbiterD) + RotL64(aOrbiterI, 41U));
            aWandererI = aWandererI + (((((RotL64(aIngress, 27U) + aOrbiterD) + RotL64(aOrbiterF, 43U)) + RotL64(aCarry, 57U)) + RotL64(aNonceByteC, 29U)) + aWandererUpdateSaltA[(((31U - aIndex) + 1542U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 37U) + aOrbiterA) + RotL64(aOrbiterG, 50U));
            aWandererK = aWandererK + ((RotL64(aCross, 3U) + aOrbiterK) + RotL64(aOrbiterC, 57U));
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererJ, 35U));
            aCarry = aCarry + (RotL64(aWandererB, 57U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererD, 60U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererK, 27U) ^ aWandererF);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererG, 3U));
            aCarry = aCarry + RotL64(aWandererE, 41U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneE[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 13U) ^ RotL64(aNonceByteB, 57U));
            aIngress = aIngress ^ (RotL64(aExpandLaneE[((aIndex + 15659U)) & S_BLOCK1], 24U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 15203U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 19U) ^ RotL64(aNonceByteD, 36U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 10267U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneB[((aIndex + 8127U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 5U) + RotL64(aPrevious, 38U)) + (RotL64(aCarry, 57U) ^ RotL64(aIngress, 19U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = (((aWandererB + RotL64(aPrevious, 27U)) + RotL64(aCarry, 29U)) + 5697928251815176134U) + aOrbiterAssignSaltA[(((31U - aIndex) + 3416U)) & S_SALT1];
            aOrbiterC = (aWandererK + RotL64(aIngress, 44U)) + 337587740689259575U;
            aOrbiterD = (aWandererC + RotL64(aScatter, 3U)) + 4927686903263973950U;
            aOrbiterI = (((aWandererG + RotL64(aCross, 13U)) + RotL64(aCarry, 43U)) + 3742409032569801033U) + RotL64(aNonceByteG, 9U);
            aOrbiterJ = ((aWandererJ + RotL64(aScatter, 47U)) + 1608092659172197650U) + RotL64(aNonceByteH, 44U);
            aOrbiterE = ((aWandererE + RotL64(aCross, 41U)) + 15848744267145717509U) + aOrbiterAssignSaltB[((aIndex + 4186U)) & S_SALT1];
            aOrbiterK = (aWandererF + RotL64(aIngress, 56U)) + 15300174177963339253U;
            aOrbiterF = (aWandererH + RotL64(aPrevious, 53U)) + 14162868453323648628U;
            aOrbiterA = (aWandererA + RotL64(aCross, 29U)) + 12020167069983729869U;
            aOrbiterG = ((aWandererD + RotL64(aIngress, 35U)) + RotL64(aCarry, 13U)) + 16259538291658723956U;
            aOrbiterB = (aWandererI + RotL64(aPrevious, 19U)) + 8516686212464112245U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 3722184575520553132U;
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 5663609293306386784U;
            aOrbiterD = RotL64((aOrbiterD * 14364218128780764749U), 47U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 15265344442454471986U) + aOrbiterUpdateSaltC[((aIndex + 6637U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterC) ^ 3050323350098829515U) ^ aOrbiterUpdateSaltB[((aIndex + 1383U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 5890624677162388135U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 1093356813820599238U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 15167726103772238440U;
            aOrbiterE = RotL64((aOrbiterE * 5719466863561311069U), 41U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterJ) + 15170797965325981472U) + RotL64(aNonceByteD, 29U);
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 17826286701992981628U;
            aOrbiterK = RotL64((aOrbiterK * 11186808881726573677U), 27U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 14710892030473425181U;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 397194787697553904U;
            aOrbiterF = RotL64((aOrbiterF * 14368930300818752833U), 43U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 1273724124862533034U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 6358U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 13018397560392545616U) ^ RotL64(aNonceByteB, 47U);
            aOrbiterA = RotL64((aOrbiterA * 4644812473262395329U), 53U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 9638716186445643730U;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 7255587739807843785U;
            aOrbiterG = RotL64((aOrbiterG * 6055682981584011189U), 19U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 9272350563697399628U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 1040729335295009339U;
            aOrbiterB = RotL64((aOrbiterB * 17825687660830291443U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 12128124729613601747U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 2285238815562202219U;
            aOrbiterH = RotL64((aOrbiterH * 15398840993074390573U), 23U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 6339113298619163493U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 5911895708485037040U;
            aOrbiterC = RotL64((aOrbiterC * 3271006139923200439U), 37U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 7601399508218901328U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterB) ^ 5697928251815176134U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 2617U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 8184257916861355735U), 39U);
            //
            aIngress = RotL64(aOrbiterB, 34U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterK, 13U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterA, 47U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterF, 27U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterE, 43U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterD, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((((RotL64(aCross, 52U) + RotL64(aOrbiterH, 60U)) + aOrbiterA) + RotL64(aCarry, 11U)) + RotL64(aNonceByteE, 37U));
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 11U) + aOrbiterF) + RotL64(aOrbiterB, 43U));
            aWandererC = aWandererC + ((RotL64(aIngress, 39U) + RotL64(aOrbiterJ, 5U)) + aOrbiterE);
            aWandererD = aWandererD ^ ((RotL64(aScatter, 29U) + RotL64(aOrbiterD, 29U)) + aOrbiterF);
            aWandererE = aWandererE + (((RotL64(aIngress, 23U) + aOrbiterC) + RotL64(aOrbiterF, 34U)) + aWandererUpdateSaltB[(((31U - aIndex) + 6569U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 35U) + aOrbiterC) + RotL64(aOrbiterG, 41U));
            aWandererG = aWandererG + (((RotL64(aScatter, 27U) + RotL64(aOrbiterI, 53U)) + aOrbiterK) + RotL64(aCarry, 39U));
            aWandererH = aWandererH ^ (((RotL64(aCross, 6U) + RotL64(aOrbiterE, 19U)) + aOrbiterA) + RotL64(aNonceByteF, 3U));
            aWandererI = aWandererI + (((RotL64(aIngress, 21U) + aOrbiterE) + RotL64(aOrbiterC, 27U)) + aWandererUpdateSaltA[(((31U - aIndex) + 1627U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 47U) + RotL64(aOrbiterK, 47U)) + aOrbiterG);
            aWandererK = aWandererK + ((RotL64(aPrevious, 37U) + aOrbiterG) + RotL64(aOrbiterB, 37U));
            //
            aCarry = aCarry + (RotL64(aWandererK, 24U) ^ aWandererE);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererF, 35U));
            aCarry = aCarry + (RotL64(aWandererA, 27U) ^ aWandererJ);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 29U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererD, 57U));
            aCarry = aCarry + RotL64(aWandererC, 12U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneF[S_BLOCK1 - aIndex] = aIngress;
        }
    }
}

void TwistExpander_EdChan_0006::Seed(TwistWorkSpace *pWorkspace,
                                 TwistFarmSBox *pFarmSBox,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint64_t pNonce,
                                 std::uint8_t *pSourceInput,
                                 std::uint8_t *pPassword,
                                 unsigned int pPasswordByteLength) {
    TwistExpander::Seed(pWorkspace, pFarmSBox, pFarmSalt, pNonce, pSourceInput, pPassword, pPasswordByteLength);
    if ((pWorkspace == nullptr) || (pFarmSBox == nullptr) ||
        (pFarmSalt == nullptr) || (pSourceInput == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aSource = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(0));
    [[maybe_unused]] std::uint8_t *aDestination = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(1));
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

    // [seed]
    mSource = aSource;
    mDest = aMaskLaneA;
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), &(mDomainBundleInbuilt.mPhaseASBoxes));

}

void TwistExpander_EdChan_0006::TwistBlock(TwistWorkSpace *pWorkspace,
                                       std::uint64_t pNonce,
                                       std::uint8_t *pSourceInput,
                                       std::uint8_t *pDestinationOutput) {
    TwistExpander::TwistBlock(pWorkspace, pNonce, pSourceInput, pDestinationOutput);
    if ((pWorkspace == nullptr) || (pDestinationOutput == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aSource = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(0));
    [[maybe_unused]] std::uint8_t *aDestination = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(1));
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

    // [twister]

    std::memcpy(pDestinationOutput, pWorkspace->mWorkLaneD, S_BLOCK);
}

const TwistDomainSaltSet TwistExpander_EdChan_0006::kPhaseASalts = {
    {
        {
            0xA4AC5129F671FE44ULL, 0x000002AA6DA7674FULL, 0x2D79B41B0D47CD9CULL, 0xBC840AF5555C9FD4ULL, 
            0x50666AE51E4DE569ULL, 0x2D95BA75E069C572ULL, 0x1CD1B318B2EDC784ULL, 0x53008D8FDCD0E24AULL, 
            0xD4A44FE337BD0467ULL, 0x1EDCD94C341576D2ULL, 0xDB488687DD2C10E0ULL, 0xF3761A1D0D1CF7D4ULL, 
            0xC6528D81C30EED7FULL, 0x006A46DFEE213836ULL, 0x9C8E3850EE5E0FCBULL, 0x98888BE5A791FE64ULL, 
            0xFD9C925152D86712ULL, 0xC1516656E333067DULL, 0xB552D0D3CD1D7FAFULL, 0x6345D10938F1DD28ULL, 
            0x12398D2455D661D6ULL, 0xB9761ED0FF0BDAD4ULL, 0x03463A8A9293FA0BULL, 0x3E918584BAAC4838ULL, 
            0xB7B399A93293E778ULL, 0x74A00856B06B9C79ULL, 0x1E17F18549119BB4ULL, 0xE4B33BF3A0F3B622ULL, 
            0x1191E47BB7AD28CBULL, 0xE4937A29D87DDDE7ULL, 0x6DBE04EF92110CA4ULL, 0x2838C5AADF203F80ULL
        },
        {
            0x5C4E55B6ECF164CDULL, 0xFD9B576A0E002682ULL, 0x3F55699DE0DD5C5CULL, 0x274AAA183E3284D7ULL, 
            0x2343DD54F19D3452ULL, 0x69CC42D8A669DB98ULL, 0x659D2E0B51344EB0ULL, 0xDB4617C7466AFB2DULL, 
            0xD2EB1894824A346FULL, 0x40BFE92397105DD3ULL, 0xEC01B8A89EB2ED75ULL, 0xA59B965140F1B423ULL, 
            0x0783F39ABEB083BEULL, 0x1BEFE77822CC884DULL, 0x8B77A288E7B15276ULL, 0x103800CE995E8711ULL, 
            0x9ADFA3106632B895ULL, 0xFC41D65D5482CF58ULL, 0x479B185581A5787DULL, 0x775B919F56750BDCULL, 
            0x976EE5EB27951D47ULL, 0x2B16139311EB17E8ULL, 0x9FCD30A3A95A547DULL, 0xCE2B9681642720B3ULL, 
            0x6C279036E12ED05BULL, 0x31C553EB21C7AF85ULL, 0x945747FFEA0083B8ULL, 0xD4419C06849387F0ULL, 
            0xDFEB49AE35D5ADDCULL, 0x9A2AAE4371DCAEDCULL, 0x6D917ED6C0BA4805ULL, 0x58C711146788E1A8ULL
        },
        {
            0x0DA9E971E1BAFCA0ULL, 0x2DDBCCD8BCE002B0ULL, 0x52665311AAED0B6DULL, 0x2FCCD6BAAD3E8BB5ULL, 
            0x1435677B23166FA5ULL, 0xC55044BC9F7AF99AULL, 0x35CE3A0FA00DF634ULL, 0x84C6204BF7B40EACULL, 
            0x08D7CF515BFAE9B8ULL, 0x4F74A255DF29DA71ULL, 0x58B90B73D7AE9E9BULL, 0x0DB27781902D8FCFULL, 
            0x8C8141C9A6708826ULL, 0x74F7697BA67BD75AULL, 0x19CD006C008F4EF6ULL, 0x840DBE187431D65FULL, 
            0xF25B155227D7A8DCULL, 0x260E5C4B80D361ACULL, 0x798171CDC5AF0696ULL, 0x94221E16E9910866ULL, 
            0x7E73CE3AB7024494ULL, 0x8AE929E01E7593B9ULL, 0x9F0CCC16D259C0D6ULL, 0xEE2D22D523C1FB58ULL, 
            0xEFE10CA155E73320ULL, 0xABEE389D8EE31107ULL, 0x7CBB226C26DA0D4FULL, 0xCDD9CE0223B482DBULL, 
            0xAC426B3649D2CCB0ULL, 0x4030269BDD9B3A96ULL, 0x367205399262624DULL, 0x7FFDEAE18ECECFD8ULL
        },
        {
            0x9E1619DB6DB8C3FBULL, 0x572034B217D25F87ULL, 0x62A9338B75374C0BULL, 0x2A35B154807070E6ULL, 
            0xFA4A240815EBD67FULL, 0x7E1AC731CF27D357ULL, 0x4CA9206F047F2BC6ULL, 0x2D064BDF4BF63371ULL, 
            0x497970F633B3FD53ULL, 0x52E863F443007BA4ULL, 0x9F070CB27372741FULL, 0xB354D83AD2E91246ULL, 
            0x4AE1906E84FF5543ULL, 0x768C9FF2F1440F6CULL, 0x2F825157A2714D66ULL, 0xA8F259354AAC78C8ULL, 
            0xA937C536EB14F695ULL, 0x94C5CE9240D82F9FULL, 0x080D796B3A529E3AULL, 0xF38B1B72431D1909ULL, 
            0x06E6FC04F4DB391AULL, 0x86C092FE75275C6EULL, 0xD21D486D412EFF55ULL, 0xE050EB47C8059F57ULL, 
            0x23937644DA4BE679ULL, 0x0B3AB72480BA2B4DULL, 0xA48BBE3D1560F30FULL, 0x31A6A99EEDA0BD15ULL, 
            0x9F1B6DF08B919A48ULL, 0x7980F8345E612945ULL, 0xDA07263AB0303AF2ULL, 0x91597DFA1A2DE438ULL
        },
        {
            0xFB5DDAC71DE2BBE5ULL, 0x1D61F5B954020E58ULL, 0x57FD7D7BC1580B28ULL, 0x6992503DAC3A1B1FULL, 
            0x0427451A5231A915ULL, 0x4840926FCB6EF315ULL, 0x0949E7AF4C1301A5ULL, 0xC05C0C1633199D1CULL, 
            0x59C0025713D1C705ULL, 0x6DC2A0F4C3AFB9EAULL, 0x2427788531B70714ULL, 0x4B85F5AF8422C358ULL, 
            0x9E5AB0B3675B8704ULL, 0x76226B61BDA0A1A1ULL, 0x4452095EDA719FE7ULL, 0x6CDCEC0441145D7DULL, 
            0xF14597773999D616ULL, 0x5E80BC16597A0C90ULL, 0xD6EDF62213018FBAULL, 0x4FBADBA31E8DE518ULL, 
            0x70CCB48CA2A0D0C4ULL, 0x18102F0618DDD61BULL, 0x4738A6C242F7E225ULL, 0x603127A2FE986311ULL, 
            0x64604AE843CE046AULL, 0x72056C372A4FB6D8ULL, 0x9051AAEA114C9627ULL, 0x2F76871283E30721ULL, 
            0xAA376FA08A53A990ULL, 0x4E620A64288742A0ULL, 0x53BA83190CE3FA8BULL, 0x864E8263879BD9E4ULL
        },
        {
            0x4C7663B753FCBB23ULL, 0xC96E8EB2992C7318ULL, 0x9830384598777FDAULL, 0x972EC396ABC8C848ULL, 
            0x31801F320F35A2B9ULL, 0xE58C55B0100A1756ULL, 0x44209CCE8B5C69C4ULL, 0x943E48E4DE0122E7ULL, 
            0x970B6D0B98575108ULL, 0xB39FBD8243AE9862ULL, 0xAE9555F82B7D70BFULL, 0x9DFF3A91CFBDF2BBULL, 
            0x37E4CF100247CFA6ULL, 0x71A783C3B6878907ULL, 0xA62FE0695863EB2FULL, 0xDDD40EE17A8C935DULL, 
            0xDA93664861DD0F80ULL, 0x5B630FD3834FDA1BULL, 0xC27EAE7E0F57330DULL, 0x67C65F9219C1C8D9ULL, 
            0x5AFB6BC96B6CC99BULL, 0x2B7E746476E801CDULL, 0x67DAEF0055E7E784ULL, 0x8FF2E0412F9150B8ULL, 
            0x29A96FFB81ABDB46ULL, 0xFF99D5F65AC4F4D9ULL, 0x732EB6296A958FB2ULL, 0xB0B32F37D1FF06EBULL, 
            0x493A52B714FE397AULL, 0xA2591201A1FD52F4ULL, 0x586FA0C50A862169ULL, 0xDD87D681336CEE17ULL
        }
    },
    {
        {
            0x77239BF5526BAF6EULL, 0x8A8C83B2A2354AC6ULL, 0xC9D9965F51ED2205ULL, 0xDD3C73C924E657CAULL, 
            0x078F7F9A83BA743FULL, 0x5904CD85B1DC000BULL, 0xA1D93F04147D1937ULL, 0xA50F7F0F765882E5ULL, 
            0xE25557ADBA13A9E0ULL, 0xDC8F3999308A5ACBULL, 0xA847D93EE6017569ULL, 0xB6564F05B9C19841ULL, 
            0x98342A9DCAF3AF6EULL, 0x269981AFA800DCD4ULL, 0xD113A9B902DBEADEULL, 0xACD0BF9C184D4A7BULL, 
            0xE066350F8C34DEE2ULL, 0xBD14EE0660B767C1ULL, 0x1FDA5254B8AAE7A5ULL, 0xB1E841AD89E06CD4ULL, 
            0xEED809BD1576C488ULL, 0xDC7998D934DE9157ULL, 0x1A5F1D4CBB52D378ULL, 0xC29BE4F672A43F14ULL, 
            0x3DFEF407B3398E7CULL, 0xE4D2B40341D81FD1ULL, 0xB79A3E663A975652ULL, 0x948E96829C04DB9BULL, 
            0x3CA70AD54C242583ULL, 0x7252027EFCA49251ULL, 0x364930250696F9F1ULL, 0x0F28FDC54741E484ULL
        },
        {
            0x9D2CDC7524BF0E61ULL, 0x60B61093058E0293ULL, 0x2050B38E5C01E154ULL, 0xF8D6269173172AC4ULL, 
            0x566FC24A9203DE88ULL, 0xE91DB69C5DDB7CA3ULL, 0x8159751CB79227BDULL, 0xF8EA63E55241D4B2ULL, 
            0x200D58633E4E35EBULL, 0x534B72B78CC99886ULL, 0x5F002159D6B0A1BAULL, 0xF23A56209D00ED63ULL, 
            0x7B66D948B11E7044ULL, 0x7F25C3FDEE7DDEBDULL, 0x85C26C4B77125FE5ULL, 0x1B6E6C7DF6A98BFEULL, 
            0xC76FE68D7D0F7D41ULL, 0x346E8D9AE3B214F3ULL, 0xA0D037DF6337070FULL, 0xA4E7319A7E78E995ULL, 
            0x2D0D2754827398B0ULL, 0x6E58166001BA6C73ULL, 0xAF6D476C040F52BBULL, 0x7B184AA332639BF2ULL, 
            0x45AFA535B4A84AB4ULL, 0x8F25B7FDFE3E08F2ULL, 0xAD27AEDFC0598B42ULL, 0x88F6F4AA1FA4E0FBULL, 
            0x3595C9C987103CB9ULL, 0x517EBE625B79AE1FULL, 0xDF134A00C5840730ULL, 0x78CFC8B743B8D9E3ULL
        },
        {
            0xB38BF84AACF5C82EULL, 0x9488B8D206B29F21ULL, 0xC418A869E142E6C1ULL, 0x9A6D5594F9D4628BULL, 
            0xE98C43DD9A1DC048ULL, 0x95574F7FBF9D5A9DULL, 0x7B301470F58598C5ULL, 0x2591A76316C62841ULL, 
            0x83123AEFE81E79A5ULL, 0x0D10B37EDBAA71F1ULL, 0x8C84187189FCAA3BULL, 0x39D9D52B5A8E25BFULL, 
            0x226A851CC5449236ULL, 0xD6C9A3F004E8BC81ULL, 0xDAA4C475F52F49F9ULL, 0x72709E1FA7AF002BULL, 
            0x99FC226321A878FAULL, 0x7CD9A71A95ACAA5AULL, 0x1794E503C08E7AAFULL, 0x2E310DC83626ADA7ULL, 
            0x4F5766DF3BA093F1ULL, 0x6A9BD66BF4CDF734ULL, 0x1B9BE6F4D32FA53FULL, 0xF087232DE7B77D89ULL, 
            0xD616D232B40146A7ULL, 0x06BC71A6207605F2ULL, 0x574D2AACCDD3059BULL, 0x175420EA25F8E607ULL, 
            0x50AFC91136DC7718ULL, 0x91C4999C2481491DULL, 0x23C9723EE79D3AE1ULL, 0x41634EC42360C286ULL
        },
        {
            0xAF70307A47CADD95ULL, 0xBD0F270CDE94604FULL, 0xA00B12CD21E5A589ULL, 0x6E7E2DAADB944575ULL, 
            0x2BD797995A9DB041ULL, 0x30CFAEF65A9899AFULL, 0x1D6543DD8FF71A70ULL, 0x2A2C94C91787625CULL, 
            0x1EFCE0CDD001AB59ULL, 0xB2078B72D58E727FULL, 0x282B075E59966806ULL, 0x0CB523736D3A7DC5ULL, 
            0xB5D59BE51705C12BULL, 0xF9DF6C6D2806A439ULL, 0xF8A9D9BEA5756773ULL, 0x0CC1C11B33F0B795ULL, 
            0x658EB0CE29004FFAULL, 0x82F1E9C9CC29AEC7ULL, 0x6AFB9B56B076F198ULL, 0xE5386DCFA965B252ULL, 
            0xA752E9275DF3F5F3ULL, 0xC07595462DA21150ULL, 0x097DC7EB257DFCECULL, 0x0E647012A1185B36ULL, 
            0x692F1E13CE86E5ECULL, 0xFBFBB3EE3D796733ULL, 0x194DDA00159F6810ULL, 0x47E7471C8507E36BULL, 
            0xD21E5ECE7976A9A4ULL, 0xD73B0BF6D1089F4FULL, 0xE652E7B0722D36C5ULL, 0xB9F08BAA5C214FF6ULL
        },
        {
            0x99D079CCA6C649C2ULL, 0xC4053DE4ADC6113CULL, 0x314CB366BA2C7065ULL, 0xB22400949737262EULL, 
            0xA0DD2E6AAEDBEBC3ULL, 0xE1D0F229A52D41A8ULL, 0x12AFA46FC4DBD56DULL, 0xEA42E2281D7CE85CULL, 
            0x54B5FA1B656C3A78ULL, 0x543307FFB721A0AFULL, 0x6A42BF889CAE1733ULL, 0x28C0D647CF2E0B90ULL, 
            0xA03F555E539C9767ULL, 0x61F6CE7C75453A0CULL, 0xC9E2AB9D554CADEDULL, 0x87FB556536426E06ULL, 
            0x0BA989E6BBC02773ULL, 0x8E0C9E0530197FEEULL, 0x6C16AD8781AD1F03ULL, 0x637124B6BEDF83E0ULL, 
            0x3A9EB00EB99DCE77ULL, 0x5FE940F84EF070CEULL, 0xBF37F3EE58171034ULL, 0x869D64A8CBB152EAULL, 
            0xF69B19F537D20055ULL, 0x8F6A6B884BA386B8ULL, 0x3482A49BC1D361F7ULL, 0x201621BEB64CF37AULL, 
            0x772B506E440D8F6BULL, 0x79B707ED5BAA3506ULL, 0x64569A72C6322B3CULL, 0x92EA72AA2806D341ULL
        },
        {
            0xE747B8DA9C1F5FF0ULL, 0x99F2A3C0D5F9C9C4ULL, 0xF2CE57F615EF7F1DULL, 0xD3E5942607FFB635ULL, 
            0x26AE11A26F062132ULL, 0x411C0B38B0A8CE44ULL, 0xB2192D9CD1549D9FULL, 0x223A19098D653248ULL, 
            0xFE5640ED798EACF0ULL, 0x607CB5BD7800E4B1ULL, 0x16B9EF8B5BD6F36BULL, 0x7642A546F5C2D6F8ULL, 
            0x3082217FD75F9102ULL, 0x222E8FCDEAC49E5FULL, 0xCE932CFCCB8C9EE6ULL, 0x8F0DE1748A2BA9F6ULL, 
            0x32EA5D9B489B7CB2ULL, 0xB6BC2F65E2B44FCBULL, 0x95DB6F6A193B5490ULL, 0x4707935150BAE1BBULL, 
            0xEFEC1B86695E74F4ULL, 0xCCEE9510582E8D68ULL, 0x31805E57CF797FB1ULL, 0xE14FDE9CE833BAA3ULL, 
            0x512DA9C8E0EE194CULL, 0x8EC496908DCA80F9ULL, 0xF285D0B9F2A64920ULL, 0xE68816A906899E62ULL, 
            0x3EDD677E5E295D71ULL, 0xAA7037B2F946534CULL, 0x0799BBF60D46089EULL, 0xB38EEC5E9818AD06ULL
        }
    },
    {
        {
            0x6A69F08386F7752DULL, 0x4E0FB526EB154CF2ULL, 0x76E5805EF9A234AFULL, 0x158A2D7D058430ECULL, 
            0x9DB0A868491E88DAULL, 0x6AFDB6700485D316ULL, 0x8A4FD6C7DD87AAE8ULL, 0x2B005C71AF5C711DULL, 
            0x190A39B91D507458ULL, 0x5A32FF538D728910ULL, 0xE5607769BA867A5BULL, 0x7A60679396352C01ULL, 
            0xE460EE11F0C8B072ULL, 0x465F06A7FF83C6D3ULL, 0xF2E3EC200463EF6FULL, 0xCF96DACBEC6DE36FULL, 
            0x2610CC7479857EA0ULL, 0x4F83A68B8ED5B505ULL, 0xF4778A875224AB6DULL, 0x3E5A89DD7EE9E6BBULL, 
            0x92AD1B4AFD9A5EBDULL, 0x66D2BD628C1C1858ULL, 0xBD5724823B49F51DULL, 0xEA9C781D90116A12ULL, 
            0x56D12F1A2C615326ULL, 0xE562EF3FBF62A36BULL, 0x8064DA58713D37B6ULL, 0xAEAA869A1BAD4DB8ULL, 
            0x5D96FF66FFC23AAFULL, 0x66B5B987105F6325ULL, 0xC8337AB34D930427ULL, 0xB131044DC455D6C4ULL
        },
        {
            0xCC7FBCB5B260136BULL, 0xA9DF9191BA04752FULL, 0xD046BD958D908A31ULL, 0x169AE80F543DF6C5ULL, 
            0xA0C055E228D42D0FULL, 0x536AF583CF841772ULL, 0x44B21F632ECBD22EULL, 0x8E40CD89AD6771E3ULL, 
            0xCFA1A670AF17256EULL, 0x84823982F2366C0EULL, 0x5A905460D6A3B045ULL, 0xE05C42274A5FBABDULL, 
            0xC68D4C248AC5B3F3ULL, 0x7C2159C0F1802212ULL, 0x3E06DFD505757EACULL, 0xC6840E492F88E5BBULL, 
            0xD557494883F2D9F9ULL, 0xAB9B994E066B3923ULL, 0x87AE7F03463CAE18ULL, 0x132066799DC325B8ULL, 
            0x7CFCDC11658551E8ULL, 0x711F86C5BF1BCD99ULL, 0x95C9D8171579BA6BULL, 0x1113B5AFF98BB176ULL, 
            0x99BDC0473B0C0FCAULL, 0x003C32A80B8D31B1ULL, 0x7BBA914F9578DE07ULL, 0x3202AB288BE98512ULL, 
            0x075D126395B0C2F5ULL, 0x5A628B8DEBB16165ULL, 0x67193FE74744BE2BULL, 0x0A9A0AF4481E4363ULL
        },
        {
            0xF986ED43AD570FD9ULL, 0x01A1EC3523954A2EULL, 0xA78BC0FE81E19209ULL, 0x5C6C1C0AD3BF0D81ULL, 
            0x008D952638872021ULL, 0xC83C09A0ACA86226ULL, 0x53C41131E73553F5ULL, 0xAB9AF652B4E7BBD6ULL, 
            0x0AAEC437F7271BF0ULL, 0x4044AFBE1AF78DFDULL, 0xA26F39156691AF61ULL, 0x7EAC49BEC275F9A9ULL, 
            0x763D482EB1FE0D7CULL, 0x759E23431CA72FE2ULL, 0x09A96DF4B170BA8AULL, 0xC2CA59A93D835D57ULL, 
            0x6B762E22E65AE289ULL, 0x15140BAF79718564ULL, 0xB133A930B14DB7BAULL, 0x3BAABB3811FAE5FCULL, 
            0x2353CC89522F8823ULL, 0xAE53A5BB339D1C91ULL, 0x171DF3E93FC87261ULL, 0x9A05312B45FD2099ULL, 
            0x16366C1516DC13FBULL, 0x36E424F2CBE0BC91ULL, 0x4B14709B846A2B83ULL, 0x080EF51A08AE8FEFULL, 
            0x6E58A69DBE3D1696ULL, 0x18553DDFC923B4E9ULL, 0x778B01587D814714ULL, 0x7CA59250E6F888F1ULL
        },
        {
            0xBBD7059F2ED9E849ULL, 0x371FE6590979C518ULL, 0x59383E4AFA268129ULL, 0xFE2CBCBE20275596ULL, 
            0xAF0B016E7B40BA02ULL, 0x39707D8300B0A467ULL, 0xDCE185757497D6F0ULL, 0xBBEA280286A32E72ULL, 
            0x616A5284600B1CE7ULL, 0x05E8C1E3CD864701ULL, 0x1010E7300BD5FCAFULL, 0x3DB7A4AF6DB7977EULL, 
            0x67D98CF29D33B94FULL, 0xD90C9CC5419CF970ULL, 0x87128616E4A10EABULL, 0xA74A4C1E60649C6CULL, 
            0x53C05FD86DA14741ULL, 0x429EDF6C9A38FD51ULL, 0x3FD43F085426EDEAULL, 0x294C389707678AE5ULL, 
            0x05B77C6771FB2A1CULL, 0x6375BFAF8B71ACAAULL, 0x88BEF9980B9ACABDULL, 0x988259B5AC0F2870ULL, 
            0x4C066B303223DC98ULL, 0x5C6F800E56D3778CULL, 0x276A5FFBB10F4E0EULL, 0xEA397E06C5AE90FEULL, 
            0x0E674E4E16AB3E46ULL, 0x86AA8192A47970F5ULL, 0xAD79171EAF55AF55ULL, 0x3208E9F1DF3CE57FULL
        },
        {
            0x6A348DCC5D10BA9DULL, 0x68E71BDFC1032B18ULL, 0xE00CE5934B1DD738ULL, 0xFE019DD8DBA9B6BFULL, 
            0xF4E3D4F265C74D62ULL, 0xD7E1152F0DCB9503ULL, 0xA44DF6EBF005337BULL, 0x6EC15A959AE1DA59ULL, 
            0x64F9F6AF62B0C32FULL, 0x6AE020D631B24FCFULL, 0xF0D094DBD3702B56ULL, 0xB1C7336D44F8E18EULL, 
            0xB1FE1444AEB3A646ULL, 0x2FBC250D7B17F19DULL, 0xD40B74F825E3D548ULL, 0xE8654435D463D06AULL, 
            0xA423F3C13810BFABULL, 0xC44FD6CB9B171FCCULL, 0x6306D233912E19BBULL, 0xC5943AE4A2E2AEA7ULL, 
            0x2AD31A012DB64F87ULL, 0x620CFA0AEC771260ULL, 0xF4E6DB6268EF139CULL, 0x8530DC2CE47CFD4CULL, 
            0x95BCEFE01CCB7256ULL, 0xCEAB4FE15F8D8EA2ULL, 0xF5CDEC4A6F09ACDCULL, 0x6610B7D14FC71B83ULL, 
            0x4B94BB0CBA6CA7D7ULL, 0xCAF221BE6268CF14ULL, 0xAFABF0D52725E164ULL, 0xFBFE0EE39F02052DULL
        },
        {
            0xA83D146E13B92A85ULL, 0xD56D29DCAF1F749CULL, 0xCD8ED8B31A19FD71ULL, 0xD848EF9BAA8A1FA1ULL, 
            0xA453D798F026293FULL, 0x27D22E482EDAF769ULL, 0x8C5E0E23425263D7ULL, 0x60A00780AFE44158ULL, 
            0xF8DCDEB707F8E776ULL, 0x8CD3CF074E84FE19ULL, 0x843037371AADB638ULL, 0x074AEE948C557AB7ULL, 
            0x31B699AF71E4DDB4ULL, 0x6D62948E4EC9A11FULL, 0x074E92CB225243DEULL, 0x394F28DABCF3C776ULL, 
            0x9083E6F61A0D5BCBULL, 0xE3C44DE793B0ED75ULL, 0x8E175F2BA42191FCULL, 0x54A60583A2BAE3BCULL, 
            0x6F22ECF306D10326ULL, 0xF78B74961447CEE5ULL, 0x57E585565381C53EULL, 0x3D8F52AD6B62B677ULL, 
            0x2814C3A318DD68BAULL, 0xF0A3DF27E1084F8EULL, 0x86FBBD56787272C6ULL, 0x2A16D6369F2521DDULL, 
            0xCF075EF83DB0EDC5ULL, 0xEC2FF1CC7082F8E5ULL, 0xB9D09718B4A79E9EULL, 0x7754D1C5306B8CC5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_EdChan_0006::kPhaseAConstants = {
    0x65604B1CB17EA400ULL,
    0xB7A9D9F1DDBF49C4ULL,
    0x417C4F5CA9670FDDULL,
    0x65604B1CB17EA400ULL,
    0xB7A9D9F1DDBF49C4ULL,
    0x417C4F5CA9670FDDULL,
    0x0B331EF58C386D5EULL,
    0x09AA7A0F02CE022BULL,
    0xA7,
    0x90,
    0xFA,
    0x8A,
    0xF7,
    0x42,
    0xFF,
    0x2D,
    0x9F,
    0xFB
};

const TwistDomainSaltSet TwistExpander_EdChan_0006::kPhaseBSalts = {
    {
        {
            0x0FF9B063B0ACC93AULL, 0x3BE39DBA1E8409BEULL, 0x12A1FF5764181E58ULL, 0x5E3993BF9B694B4AULL, 
            0x316CFCB3F91D3839ULL, 0xA6FF13A625C1DB05ULL, 0xBB4DA02CE6F99D45ULL, 0x7DE25B99517881BAULL, 
            0x8F20879F3CD7BAFFULL, 0x8DC5F0FF58ECCB0CULL, 0x80CF2FAC24575585ULL, 0x798409048E83588FULL, 
            0x9655BF72038EC9D5ULL, 0xAA47A909EFA59477ULL, 0xD91D01AC3D2C67EEULL, 0x91DAB6F3038A03F7ULL, 
            0xE97E544325B7E72BULL, 0x5F33F45D0247F693ULL, 0x84BC141790DA2A27ULL, 0xE2EE82CE33AE75CDULL, 
            0xF108688D69E25CA9ULL, 0x0DE097A1400FBFC0ULL, 0xFC81F1D528722EB1ULL, 0xA9BF37DDB31B8EF9ULL, 
            0xDDFEB91EB00A58AAULL, 0xC30F8DCEE18F8383ULL, 0xD838CB5BE8AB72B2ULL, 0xD271C6EEFF3E0B64ULL, 
            0x43EDA76D7F1143E5ULL, 0xF78F0FDB2ADADA91ULL, 0xE71588DD5195BBDAULL, 0x4D1EEC8833D8CE47ULL
        },
        {
            0x8BF97B8BEB1B271CULL, 0xB35F1B8CE5FE6321ULL, 0xD464F72CCE2A980FULL, 0x0F6B8F76524AEC1AULL, 
            0xEBDE3DCB2E90BAF3ULL, 0x58A3A0885D711827ULL, 0xEBFD283A69AE39A5ULL, 0x57143D2577F5F52EULL, 
            0x758C49535B7C669DULL, 0x4F7B414AD586E7E1ULL, 0x379FD1FABAB789ABULL, 0x37046B7C9E90FA74ULL, 
            0x1D459A55B98F47B7ULL, 0x6A02A50783702239ULL, 0x5CA92ABFF49DBA0EULL, 0x8615944CA9224A5BULL, 
            0xF245569F77C64445ULL, 0xC7E5B21D7A751109ULL, 0x113DE0555784904BULL, 0x4302B793F3E9AAFFULL, 
            0xED6E863E493D4B66ULL, 0xF1079D472510E9D7ULL, 0x61FB0CE9AE0F42C5ULL, 0x3C7053BECD123E6EULL, 
            0xAC045D131C5682BCULL, 0x51EBC7BFA2C2E1E2ULL, 0x481C4C88568E4D1DULL, 0xDC14AEB38E1420DFULL, 
            0x43B24693A24D9E6AULL, 0x5873479CF6ED11B6ULL, 0x6476B73AF811567BULL, 0x0F09C022D2BD6561ULL
        },
        {
            0xC82CEE4ED763B334ULL, 0xAD891F33B1B581D9ULL, 0xC9FC2BBFA331CB8DULL, 0xCEF338652484B509ULL, 
            0xE85B300A14BD40F4ULL, 0x33D4819E8195C7AAULL, 0x5C2F8F4445FA8B6BULL, 0x96103B35B5EFBE3AULL, 
            0x8957445D5E574CBBULL, 0x9A0AEF8580047346ULL, 0x5BD0FFEE4A09536DULL, 0xBDADAB1D0A1B8920ULL, 
            0x38A2FAA91EC1FBA0ULL, 0xED36AF91CC6B2B1FULL, 0x3FD3457E847C9277ULL, 0x039DA7156BE213F9ULL, 
            0x39EE7D0BDA015153ULL, 0xC6283ECA97D8194FULL, 0xF9440452F226A5DCULL, 0x16F5E087866CEF8DULL, 
            0xE3103B38367D89BDULL, 0x32D7094B5C744495ULL, 0xFB55824031196942ULL, 0x586618BF25B45F09ULL, 
            0x3B39925EE74D1CF5ULL, 0x259B55BAE984D514ULL, 0x950925318FB1DF06ULL, 0x1D644518A61A071EULL, 
            0xF2DCB4A19F184698ULL, 0x02FC80635FD8BA83ULL, 0x8C1EB16DA00D8D05ULL, 0xBEB8133025EDCD9AULL
        },
        {
            0xF4B7B8DE979AF05DULL, 0x294937DC787B0910ULL, 0x72BDCF2F97040F68ULL, 0x2CAD3FBFE34F884CULL, 
            0xCDA939824B445EBDULL, 0x0888D75FAC185964ULL, 0x06FE3398416F6D94ULL, 0x93BD5D1C9B3F1825ULL, 
            0x6175618EA42898A4ULL, 0x51712FB355D7190BULL, 0x55AF677F1E13C463ULL, 0x55BAD621152E904EULL, 
            0x54EF7F672266D7F1ULL, 0x3104D65F1EBAA9AAULL, 0x56263C628AAFEE0FULL, 0xEE6B4537BBC6D0EDULL, 
            0x83174001B2872764ULL, 0xBC5CC665C30B563BULL, 0x30DBC20E0AB36334ULL, 0x80D14DA39F84DBAAULL, 
            0x25B692AEC330ED3DULL, 0xAE69ABB8116C5797ULL, 0x8C14F50DFA3B0662ULL, 0x51A8B74D7C82159CULL, 
            0xC95BCFEF8104D460ULL, 0x43BBF3AF73D99187ULL, 0xE38B21BDE07355B8ULL, 0xF8D6136E308FB8CEULL, 
            0x26B4E3233134C763ULL, 0xAB4D8174B1289120ULL, 0xD7070C2BCE98E7A5ULL, 0x6DF62D0515C35B3FULL
        },
        {
            0xB8AFE869CD3EA0D0ULL, 0xBB501EE75157CC3AULL, 0xB3D57B0501EFEED6ULL, 0x3CB188D8C1AFCBBBULL, 
            0xDCEB8DF5FF622423ULL, 0x3F1EBED30304D89FULL, 0xB4A6A55563538C81ULL, 0x41917B66F87F1788ULL, 
            0xC7B1266655BEB7A0ULL, 0xFBEDE3913CD8F948ULL, 0x3AFC1C7151879AB5ULL, 0x28F31B3CDB3CC3CFULL, 
            0x964231279680ED11ULL, 0x2C90AB44EF7B02B3ULL, 0xD0E3D4034D812FF3ULL, 0x0065D2B8DD941EA8ULL, 
            0xB273C4D4B7F559F0ULL, 0x36C5C5BCA0FC7647ULL, 0x8435E665DD09F2EAULL, 0x8D31E784EC808391ULL, 
            0x58F94917D6580397ULL, 0x10495836FDC2F620ULL, 0x3C4B668764255E2CULL, 0xA7C5E2A8D17A142AULL, 
            0x45D9B3BA932CBE23ULL, 0xB9B37A7285F969E8ULL, 0x8CAD602F7F4B133EULL, 0xA845797E63C0AA53ULL, 
            0x1BF6D9892E1016DAULL, 0x794181CDE9F1E324ULL, 0x2B10E4540695D649ULL, 0xBF9CE43704B7F41FULL
        },
        {
            0xBAC7F7D19D9CD974ULL, 0x4E9C170BDF81FAD7ULL, 0x0306C9F3EBC3E5EDULL, 0xA2299B3286B57789ULL, 
            0xA4BF5599177CC6EAULL, 0xE59DACF5E482609EULL, 0x57B362521F106DA2ULL, 0x57C0972D839C45B8ULL, 
            0xB554F0E5CAB5854BULL, 0x77214F805DFB3F8FULL, 0x1A7AC6FDE00EB2DFULL, 0xE6BEC2423E15947DULL, 
            0x2A92054F03E027DCULL, 0x935F35377B8432E3ULL, 0x8E64104C7CB7B891ULL, 0x42C37B04A08C0293ULL, 
            0xEC108AF2CE60399DULL, 0xBF12E22487521F4BULL, 0xACDE60DA5DC781CDULL, 0x09B671396F24FA72ULL, 
            0x55E3AB7B22285BB9ULL, 0xAE283D08280509C3ULL, 0x494EB9B24A1884ACULL, 0x096A41C5DD8265E1ULL, 
            0x7CC341704609B4A4ULL, 0xA5372C17ED993632ULL, 0xA4A676596DE8906EULL, 0x75F160298F93462FULL, 
            0x46EDEF72D727F880ULL, 0x913CB680D690788FULL, 0x321D540933BD17B0ULL, 0x1403CBC40F5E77DEULL
        }
    },
    {
        {
            0xE8B21567F7F91CF0ULL, 0x7DF0CFA792F6B051ULL, 0x719FA77E1E60895CULL, 0x25589AA79507FED9ULL, 
            0x2CB8AF52F698D77EULL, 0x06486845A01B422BULL, 0xED0EED38821191BFULL, 0xF162167290B16821ULL, 
            0xB869E63F95B06EF8ULL, 0xAD1576864AAACFEFULL, 0xB700264765D5A2CCULL, 0x6EF0E254E462C3CEULL, 
            0x6023E337FF35CFCAULL, 0xE2BC0C978455D7CCULL, 0xE1818C7A28D9642DULL, 0x4BCB8CDC65DBC3C7ULL, 
            0xC74C3CAB22360C64ULL, 0x79E5384C839EA1B1ULL, 0xE4570480602F0055ULL, 0xEF0456286718924DULL, 
            0xC55AB30BA305AF92ULL, 0xB8186ACF1D0ECCEDULL, 0xDC651D384F37C18AULL, 0xCBF2F1A9C0D24BAEULL, 
            0xBCDC76A0A6CA28E3ULL, 0xE888FF33568C6276ULL, 0x2962FE4CE16D0C9FULL, 0x6428AB30F2C4892CULL, 
            0x196179D503079A6DULL, 0x6FB61658BF3B1752ULL, 0x8DE1EA535DD923A8ULL, 0x4D365029D2BCC1D4ULL
        },
        {
            0x2FA4CFF80842D434ULL, 0x8492B2904A43453EULL, 0x96CA7650F058E36FULL, 0xD3BE0ADDA088E3CFULL, 
            0x89B2D7A41A3EBEA4ULL, 0x7810B0453942683FULL, 0xB518697628D8F021ULL, 0x25E4E71663D69652ULL, 
            0xE079D1A8E76EDBB3ULL, 0xCB9DBFCF5E075C08ULL, 0xC70DA884CF8C9436ULL, 0x60E5B4A9C4C630BFULL, 
            0x608086F5E8BC7493ULL, 0xF2F28906785AF7C2ULL, 0x46CDEF49711AD9AEULL, 0x05EB8BD3CAFA3A13ULL, 
            0x8E5038B9F0750022ULL, 0x1417C3BCE0824523ULL, 0x2457891F13398845ULL, 0xFFF5C2B0F85E1AF8ULL, 
            0x84FF89A6A8D74F41ULL, 0xBB57CD03269D385CULL, 0x2631923BA2122C2CULL, 0x4B489B04BB29121CULL, 
            0xF2345A9BF43EB28FULL, 0xCDDD9B2503AB4963ULL, 0xED76AC7AF11BAB7AULL, 0xBBA1CFAE91399F7DULL, 
            0x964C84EA8A89AB1CULL, 0x82AA25786811AA16ULL, 0x5853608A79FF49CAULL, 0x2F1F27B54492782DULL
        },
        {
            0xA15E7B02B979DDC9ULL, 0x089650950B81B456ULL, 0x3631D4F1F16C829AULL, 0x7AC62BCC988E6A1FULL, 
            0x07B67EF9B35DB996ULL, 0xEDA487496E8C1187ULL, 0xEDCA9E47C49C48A7ULL, 0xA9AD0E7F4F297B20ULL, 
            0x5AB948BC7BBF85B4ULL, 0x0CD16AE68CE580BEULL, 0x431993D35175D72AULL, 0xA654C39FE15D13B0ULL, 
            0x70D60D35F345406CULL, 0x8E42443DD51A7FF5ULL, 0x00147E38D1C16B7EULL, 0xF21BBDD39FB4D120ULL, 
            0xDFE138C66561B6DDULL, 0x7C34875C32512ED9ULL, 0x6923D686EF003F88ULL, 0x9E59BC7E6D7C9ED1ULL, 
            0x905816CF34C8C9B7ULL, 0x6DE7DA3D9F10C9B3ULL, 0xBCEDEDA97C2CAD9AULL, 0xC70878F8C4D064E4ULL, 
            0x622A46495A6C52FAULL, 0x7D1E1D5C6B82E960ULL, 0x193390B15EF195C7ULL, 0x98D60008B4D74923ULL, 
            0x60003F04DFBEC76AULL, 0xEF15BBA69F2CB812ULL, 0xE08A4AFDA57111A7ULL, 0x312B0EAC944836A5ULL
        },
        {
            0xFA118BBC8E88E512ULL, 0x2478B4F5A2030F61ULL, 0xAD70442A5BCA4EB2ULL, 0xE516AC111240DAFFULL, 
            0xE8EFBEEB58B9CC5FULL, 0x6BAB8C1355AAE8ADULL, 0x6D855EDC69FEC362ULL, 0x651AEA9B6788D9D4ULL, 
            0xFA588A341A9DEE6AULL, 0x73A3B11E8C162CFAULL, 0x28F8E9172CE0CD35ULL, 0x79D23B753B84A40BULL, 
            0xF307E29DD3C0CA33ULL, 0xD4A6DA0B2994EE8BULL, 0x3F9A835EA3DCACD0ULL, 0x2555F651ECFA4C6FULL, 
            0x8F5507DAC3BCB850ULL, 0x9ECBD9F5651A8D85ULL, 0xA184E038E495CA2DULL, 0x932ED26B78BF41CBULL, 
            0x367BC4226C55BD50ULL, 0x7D533468F955FEF9ULL, 0xB0A7073EC76D85FCULL, 0xF44101AF36D812A7ULL, 
            0x4F2B9B147ECA91C8ULL, 0x1DDB10D38EBD7D86ULL, 0x089828AED3BC43B5ULL, 0x95561A1E3D086B42ULL, 
            0xDDC5CB974189E522ULL, 0x3DB76E511CB07A1FULL, 0x6C56F79F5869083BULL, 0x38A7E61352D53736ULL
        },
        {
            0x2BFBF1430AADE996ULL, 0x47099A7AD984ADAFULL, 0x6F78A3562135476FULL, 0xD637186705D6CC29ULL, 
            0xC04FD04DEE5651E0ULL, 0xC2070A41FDF03F50ULL, 0x61D83FDC22BD1003ULL, 0xF7EEF3A66774CEFCULL, 
            0xCF0B477BFACA104BULL, 0x6B61AC94525F853EULL, 0xAF0E78BE82567159ULL, 0xD1D666FED596BF00ULL, 
            0x5CAA5C883460F0D6ULL, 0x1827D56C7C432422ULL, 0x841823F9090740FAULL, 0xACD8AB6C85938201ULL, 
            0x73CD23DBCDC21EF8ULL, 0x5939AD2C52A3A4C6ULL, 0x47818CD5CC11EA1BULL, 0xC8D38CBFFED5788DULL, 
            0xE2C82C244D748D3CULL, 0xEEA489E1621D4008ULL, 0x09EEE332A5E660E4ULL, 0x50E0E23CFB27B49BULL, 
            0x0A6A4CC11A2CE6EAULL, 0xA603C5B867BC2285ULL, 0x5C0EB08BAF7FF5C8ULL, 0x6325BFEC97AD024AULL, 
            0xA34C15931086B52AULL, 0x47CBF5E97577D568ULL, 0x0DF55241641DB490ULL, 0x04E1170E63805D2CULL
        },
        {
            0x8F2B933615D4D6A9ULL, 0x8A4F9AC8F3E6AA7DULL, 0xBC5FABCCF2BB5ACFULL, 0x29191431E6D88A8EULL, 
            0x026820AD193942A7ULL, 0x181748C138131F66ULL, 0xE923462C1FA0D954ULL, 0xA73F1130733074D9ULL, 
            0x3DB3960051B15E6DULL, 0xCA2C2D5317939EF7ULL, 0x593A06D4DABE7141ULL, 0x9368157BA68927D3ULL, 
            0xC4638DC5238EB8CEULL, 0x26BAD554AB8D2B0FULL, 0xB8E24C0192247CBEULL, 0xA6C916D22A148F0AULL, 
            0xD82CD14FB37469FCULL, 0x26B51F42F2FC372DULL, 0x4FD52B939C4AF38CULL, 0x920896289FFAEB2CULL, 
            0xBF854BF0F9F22A9FULL, 0xF64D053B09B3F762ULL, 0xB3B018DBE698EF99ULL, 0x308C6979BAEFE9FCULL, 
            0xC8EA6BA64D790239ULL, 0xAA9FE0EC074E7A12ULL, 0x24F8B1C316EDD9C7ULL, 0x6A116D76722809E5ULL, 
            0xC5EAC7C3BF154BD3ULL, 0x9DD9ADE25CB8E249ULL, 0xAA28AD8BDE48B2FFULL, 0xC27B6644EC6F2722ULL
        }
    },
    {
        {
            0xB6C6FC3443A9E8EDULL, 0xDD6CE582C455795CULL, 0x405E11D64B6DCAE7ULL, 0xEC2E42FAF5737E3DULL, 
            0x9DC299430CAD102BULL, 0x4D3384013A6D3875ULL, 0x0713F4EE9C5A833EULL, 0x592E90FE7483910CULL, 
            0x5B0490A61792A108ULL, 0xD7EBAF5F493CB23CULL, 0x2267FC81DC13A27BULL, 0x095AE3EED7E8C5D4ULL, 
            0xD265DE003E699C57ULL, 0x26DAE2F840916A7AULL, 0x50B65E56619C0B5AULL, 0xED0062B04DA102D1ULL, 
            0x85FF37FC99D258CEULL, 0xF3FC37ECF4419609ULL, 0x69B02005AD99B34EULL, 0xC309D56DB5B62313ULL, 
            0x9D6EBE1304FEFC29ULL, 0xE53411C712475504ULL, 0x1868C32ED0AB000FULL, 0x92519E241099460DULL, 
            0xC1F0FDE0D9D436F4ULL, 0xA23B5AF438D4EFB4ULL, 0xAE93F64D130E297EULL, 0xE4C927369024979CULL, 
            0xE46B79F65CF7619FULL, 0xF01442E8F5315500ULL, 0xA1F1566E2B83B495ULL, 0x6D81F510336A500EULL
        },
        {
            0x15B2EEA03623AB64ULL, 0x2E998C00CBA802C4ULL, 0x7A74FD86FF014A53ULL, 0xFFCD2ABA4D52E073ULL, 
            0xB5C2BBF3C381393BULL, 0xCE297D0095A1DAD9ULL, 0x119A3E29DF7B3BB4ULL, 0x37E4A8FFB4276B2AULL, 
            0xE08CC575297D4302ULL, 0xACFA2FF3ACD5EE11ULL, 0xFB4C3A03B1B8553BULL, 0x2B342828E3B7B9B4ULL, 
            0xEA8AFB624E41C94FULL, 0x32AFD108FFF99109ULL, 0x546B2697134B23ACULL, 0x0052C78C563B3B85ULL, 
            0xC2C7D3BC5AC7194BULL, 0xA2A8F9B7D33C741EULL, 0x2465793FC768B68DULL, 0x1E7A8878B0F54498ULL, 
            0x674E1C56A3A3648FULL, 0x4C59C6BB811E619FULL, 0x58DC579755B9F3A7ULL, 0x79DA3CD1A1F6CE40ULL, 
            0xD8A58902A46BBAAEULL, 0x2F28D602F618D11CULL, 0x8303572FDF033702ULL, 0x073BDC002B94EDD9ULL, 
            0x1F76BCC30985B6BEULL, 0x4CD1F2040A25D3E2ULL, 0x1E1B2114F1FE933CULL, 0x82D776EAD5250DBFULL
        },
        {
            0x124728E6156EFD52ULL, 0xDCE1D5A1BF7C1E47ULL, 0xF9992DFB7B68C50CULL, 0xD027F557F851F4A5ULL, 
            0x7210C968F282CB64ULL, 0x0312B21883F1625EULL, 0x9E0C4303DF58474AULL, 0xDEEB9798598F3B47ULL, 
            0xAEDB0748B51BE5C3ULL, 0x609B0073E792AB63ULL, 0xBE41D475A39086C6ULL, 0x4E6B57F65630D94EULL, 
            0xD8FCBB1640B3AE03ULL, 0x4791EF271A30F4B7ULL, 0x38037B54D33F3054ULL, 0x5A47557CAC987828ULL, 
            0x9808A4C870265C87ULL, 0xC40405872A29C544ULL, 0x8D514F50611F5A09ULL, 0x962929A388A4599EULL, 
            0x825916CD26035F8BULL, 0xA375F76F0DDE7B24ULL, 0x67FAB57C5B691C94ULL, 0x2FEF403D795A5BD4ULL, 
            0x0DCF8D3903C42DBAULL, 0xB7A3CFAE4B43F2DBULL, 0x036B4E73C2494B0FULL, 0x8CC944086A5C6AB6ULL, 
            0x6F9D53AC1DC5B45EULL, 0x3864E50C555C4E8DULL, 0x074CCE558F2C3B3CULL, 0x3CE26D74D972968CULL
        },
        {
            0xAFAAB0DC6E322A03ULL, 0xE4E67AB6855A4468ULL, 0x2FCD52FB3B00742FULL, 0x42B7700A3433C4C8ULL, 
            0xF5ED0C3A9B564F19ULL, 0xE868BC7EE506D38BULL, 0x803B2A23348CCC2DULL, 0xA505BE7F90D2A598ULL, 
            0x9D47A0261B70C6B3ULL, 0xEB694CE1F0845E55ULL, 0x4EB71C78D40C8A9AULL, 0x2D53071E6CF3982FULL, 
            0x36E923A5DC3473C9ULL, 0x2355F5741DD6FEBCULL, 0xC90B4437B832DC1CULL, 0x6D40D49A813B7224ULL, 
            0x2F5DD96547F8F0CFULL, 0x19A0B562AFD93B94ULL, 0xFF1526A172D0F2E1ULL, 0x5DEA9E391AB1EE32ULL, 
            0xF808EF27E9AB47F9ULL, 0xC12A2B6A1CC20AB1ULL, 0x585925825FDD8B67ULL, 0x340EEE0CB56BB99FULL, 
            0x1917476F9ABA1842ULL, 0x43841266A0131F51ULL, 0xF1F702174849B986ULL, 0xEA54BCE0B0D1D9DDULL, 
            0xBBF1F5711BE9CEB1ULL, 0xC3EA857E051C9F43ULL, 0xA852815FD02C9114ULL, 0xD1784CA5A394FF0FULL
        },
        {
            0xA2472297403EB040ULL, 0xBAB3096DC6037EF2ULL, 0x47DE26C15B548643ULL, 0x2183E84D6C563AB6ULL, 
            0x25B2B944152150E5ULL, 0x8680A0EF80EB4C2AULL, 0xEE522FCA6EC6B941ULL, 0xA45D7BBED51B779AULL, 
            0x2BB4DCCA5EA4F85BULL, 0x15C86FD1362D7E83ULL, 0x275F6C97FCB69CE0ULL, 0x6D1AA0050EEF975AULL, 
            0xBEE8C5B45951CB6CULL, 0x4B89D49C72D6F082ULL, 0x0EC1FA595F1AF8C4ULL, 0x8ACE9BA3A9EF9DE3ULL, 
            0x6D17D40D7866FCB7ULL, 0xCE77C8568FD9206DULL, 0xBC0596B7EF0B3D8EULL, 0x6036789B5A989ADDULL, 
            0x55EE4F3084C5030AULL, 0x51792315F05C6980ULL, 0x03134665FC985489ULL, 0x96140C63858ADBF1ULL, 
            0x619FD6E915629177ULL, 0x06A93A836E4BA126ULL, 0xD3F362CFB26CD16AULL, 0x0FEAA99F188FC417ULL, 
            0xCDACC004553EB1D9ULL, 0xFFABDB31292967C5ULL, 0xF9393F018FBFDA51ULL, 0x736F0B44FA2C9232ULL
        },
        {
            0x802574CD80522239ULL, 0xF50E1987036C6104ULL, 0xAD62F47E1302D0F8ULL, 0x04EECAEB587BD66FULL, 
            0x7729E890C6D2E7CCULL, 0x69A189AB4E603BDFULL, 0xDBFAB6C3610DCD34ULL, 0x263390BEC795ADF3ULL, 
            0x4C52B1990414DD90ULL, 0x3090800913F26FC0ULL, 0x7F1E834E55C761A8ULL, 0x983A33F63C1C42B5ULL, 
            0x1CB6C0B900DBDA63ULL, 0xA10498EAA4015538ULL, 0x447A62F78585570BULL, 0x1CFFBD23F69613F2ULL, 
            0x8DC81D59C9436616ULL, 0x04B4A21902BA8E0DULL, 0xFFEE1CEDAF0D3706ULL, 0x5CE0924042086A36ULL, 
            0xC6D5ABFCCBEE1B95ULL, 0x1E85F8F4099A4430ULL, 0x4B71BE53811EF546ULL, 0x0A6DBA31C65DE5C1ULL, 
            0x266E9E1F66AD9A19ULL, 0xA5CA9DB7C6C76D09ULL, 0x0A5203067869B699ULL, 0x7D4F18DDE1E4F260ULL, 
            0x68642DB2488F92B6ULL, 0x38ADAA67CEFD672FULL, 0xB6D9606B3FFC17C6ULL, 0x9936EFBB62B930D4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_EdChan_0006::kPhaseBConstants = {
    0x687FD41F30181FD8ULL,
    0x42967C6803C6F1D0ULL,
    0xC37EE8D98C9EFCF4ULL,
    0x687FD41F30181FD8ULL,
    0x42967C6803C6F1D0ULL,
    0xC37EE8D98C9EFCF4ULL,
    0xA5A0F79DDBA964F0ULL,
    0x0496161D6B148914ULL,
    0xC2,
    0x5A,
    0x54,
    0x68,
    0x18,
    0x9D,
    0x98,
    0x75,
    0x1F,
    0xED
};

const TwistDomainSaltSet TwistExpander_EdChan_0006::kPhaseCSalts = {
    {
        {
            0x7206E6FD5950BD79ULL, 0xD5EFACBB9344E0D3ULL, 0x8B950A3BA2B75D86ULL, 0x085EAC47FD52C2E3ULL, 
            0x023AC327EAF7AEDEULL, 0x9E10F877149EF674ULL, 0x7DAEA345E3D45E4EULL, 0xEE56797FCE933F1CULL, 
            0x4B3B7D5739BE4786ULL, 0xDE79E8AEC4BD677EULL, 0xDFB1B3278EA58BA5ULL, 0xEB0071DB4AAD4929ULL, 
            0xE4FC8FC19C97AA4DULL, 0xF62D85122BE589F2ULL, 0x7D100DEB0A30DBBBULL, 0xD5309E7F385D6F1FULL, 
            0x285FE45C0848AA94ULL, 0xCD19209297FC2672ULL, 0x3C8B0651F2AB191EULL, 0x3E6FD62224E56928ULL, 
            0xB7A5CB2D3F6892C2ULL, 0x063F6EBC7FA82D47ULL, 0xFA3F957111384CD3ULL, 0xDEDF23E9AB293ACCULL, 
            0x87B6F2B686396DE6ULL, 0x893AE7B1EC761A29ULL, 0x67982F54DE257103ULL, 0x27BCD21D11C003B0ULL, 
            0xD6C1A5B02635A98EULL, 0x4ACDA0842F795E88ULL, 0x5A5CA33E3F7ED674ULL, 0x859266B19545B578ULL
        },
        {
            0x5FF728815B176394ULL, 0x7C7814CD9AA67033ULL, 0x3E675A4631F92228ULL, 0x4C6BDF53F41E47C4ULL, 
            0x9580CEEDE0659FB6ULL, 0x95485397AFCD44B1ULL, 0x3572CC07F4D38ECEULL, 0xCC5ABD4F8F61C58CULL, 
            0x8DEA939BBA98E5CCULL, 0xC51E1CE9AFA32B5CULL, 0x720593A7DC7ED8FAULL, 0xA65D6FA6461C2675ULL, 
            0xF71637ABD1825978ULL, 0x2F0DB464244949E0ULL, 0x10F3547700FD9C9DULL, 0x2A5F3099F7E77AF9ULL, 
            0x9001864C7296A810ULL, 0x77F2630C6CE0575CULL, 0x4D030A3BCE65313CULL, 0xE38FCACCB14203CCULL, 
            0xAEED2D20A64B71F9ULL, 0x585AB95D7D5D63A1ULL, 0x18DD8C30A706FD75ULL, 0x40A33BE9E0C81C06ULL, 
            0x07817296645D0229ULL, 0x244CF0CEEA4F7671ULL, 0xDBA18E05D1D7C887ULL, 0x0FCC972E43F807D4ULL, 
            0x0554CBF6D79AD413ULL, 0xB58D35645EAC10A5ULL, 0x99D1FA40F046BC37ULL, 0x2F686296BAF0B787ULL
        },
        {
            0xA2B8FEBD398E789AULL, 0xF681754E4D50586CULL, 0xB2B139F44DD2F747ULL, 0x054EC2446B5210BEULL, 
            0x81E6A20A64AE0E2FULL, 0x4D28224408356CA1ULL, 0x5BD68BCC53474C6DULL, 0x5CFED059A8991A03ULL, 
            0x0D28F3F89568BAA3ULL, 0x7FA4EE52560DEE47ULL, 0x4893C1B95391F224ULL, 0xDBB5C946A67CA7D5ULL, 
            0x91B75F7DEAFF762EULL, 0x5C36548F97F5F6DAULL, 0x76E80BA832CF2091ULL, 0x83EE102104C57CC7ULL, 
            0xF0B4FE08349D9C3CULL, 0xDCF05ED56A295EE6ULL, 0x3AB610A262B8009FULL, 0xF0A8D1392ED61EE4ULL, 
            0x1AEC09CD7C727339ULL, 0x7DD3E89DAD8D11E3ULL, 0xC2868977B9486862ULL, 0x5D87354562E1A967ULL, 
            0x8F26058C77BA4ABAULL, 0x208B12BDC528481FULL, 0x93E174930A2A8386ULL, 0x229693EA8530FE42ULL, 
            0xFD8F5BDFF2CA894BULL, 0xA031EDE398C5027FULL, 0xF84DD9C9D66B5111ULL, 0xF85DF5C9E5689F8DULL
        },
        {
            0x865991D384847BE0ULL, 0xAA08466F07601EDEULL, 0x86CC2EDDBD3DCC47ULL, 0x97B231FE6FCDA01FULL, 
            0x58DAD8038D4DD7DEULL, 0x71DD884B161B07F7ULL, 0x197A5E9FD13D9795ULL, 0x8C4AE10A4A53E02EULL, 
            0x02C711C533ABEC55ULL, 0x364916DC6415749EULL, 0x89A833CB2322A04AULL, 0x35284413A7589EC8ULL, 
            0xF02BE9CEF7D77CE1ULL, 0xF7A6D07761A4A562ULL, 0xAEB12A66044BAEE9ULL, 0xD27CB80356827C98ULL, 
            0xE81C9BA3AD5287C5ULL, 0x0DAA8E3D8A73BB44ULL, 0x319C6E4805628812ULL, 0xBCC2C531ADD9224BULL, 
            0xD159725928C49AF5ULL, 0xFD1FF66DE40DAC01ULL, 0xB005DA303CAB4766ULL, 0x135EA6C423ADF75AULL, 
            0x203EAE24893AC981ULL, 0x869B2D7FAA911CD7ULL, 0x0D7C9FA7CDC7874BULL, 0xAC00B60F04E980E0ULL, 
            0xC382A11533DB5990ULL, 0xA7332FD759DCF2CCULL, 0xB72EBC1AC94B0E04ULL, 0xB698ACF954F85232ULL
        },
        {
            0x8DFB7BF112EB007BULL, 0x849DF7683E21549AULL, 0xB6DE3107C4859E28ULL, 0x82241E7A636EAE66ULL, 
            0x7B8901557EAEEAA8ULL, 0x25F8409121145BE4ULL, 0xA891922C0A4D69D7ULL, 0x289C4D9BB6FB9A2FULL, 
            0x876EC05055F3E888ULL, 0x2667E8FD6108B462ULL, 0x13AE7F8A80B8637EULL, 0x9E10EC6B1A517580ULL, 
            0xF28B2DEBE48D0747ULL, 0xE1E48F850DF4B8F7ULL, 0x12830A19744F7B72ULL, 0x85620444886C04C1ULL, 
            0x704FAD841DBD5B3FULL, 0x2518CFEF139D5D21ULL, 0x3F3259567E812EB0ULL, 0xADDE7491F73FCC25ULL, 
            0x6DC19BF95C2D2EEFULL, 0x74C5523395943011ULL, 0xBA12DB0056365788ULL, 0x03CD735CA9E13ACBULL, 
            0xA65236593EC607ADULL, 0xA3019C863442DFD2ULL, 0x7DE0CE4BEED320B1ULL, 0x9E587B65A733FD89ULL, 
            0x199320C81B1B52FCULL, 0x0B8FEAD8BD483452ULL, 0x3BADA1ECC27DAA6AULL, 0x4C7DB043FB37E49CULL
        },
        {
            0xFC6D074870A7627FULL, 0xD343B3D1FFEAEEF6ULL, 0x81E99D0274D460BFULL, 0x9B60685D3CAA4DF7ULL, 
            0xB614E716DBAFC122ULL, 0x3667A16FF040811FULL, 0x5CAEF1F38BCFA2D3ULL, 0xBC102DE20AFC9D3CULL, 
            0xD91F3B86D3C93840ULL, 0x38C8F7BBA6756AE2ULL, 0xE2053FD2F1FB6514ULL, 0x1AFACAFAF82B7B8DULL, 
            0xF95250F911A7B927ULL, 0x5EBCB1736440B11EULL, 0xA7F643C17C6242B8ULL, 0xEDE96189EA0D0E3DULL, 
            0x82E33D1681E770F2ULL, 0xDA428ACDAD3A53C8ULL, 0x6566B77DFED1C89FULL, 0x71BCBDCE6A835954ULL, 
            0xCCF315408F47D230ULL, 0xDD99E74005670B17ULL, 0xF3E1100C62194E52ULL, 0x4B3ABC23103CAAF6ULL, 
            0x4B8F58D06D7EA819ULL, 0x4B5D7A3F2CD4F9F8ULL, 0x8511F13746406023ULL, 0x06DE7918379E90DBULL, 
            0x4242299BAE95979CULL, 0x5E55A1EEF525E512ULL, 0x1ADCE21EC2BE6049ULL, 0x76FA75A944F5F133ULL
        }
    },
    {
        {
            0x9A425CF8415C68FDULL, 0x843B68D58FE5C706ULL, 0xB12C526DC52C58D1ULL, 0x4573004ACB5626CBULL, 
            0x24216ABC9DE242D5ULL, 0x0504DE8D3847C7F2ULL, 0xC519B41CA6D3E7C2ULL, 0xC42E73140FA6DC8DULL, 
            0x6DD0AEA6AFE2E513ULL, 0x23B83A98BF497579ULL, 0xAF9DBA8C175A3EADULL, 0x23B52A9ED31A42BDULL, 
            0x98EC04E52CA4B113ULL, 0x3D2F15D4F909D1CEULL, 0x929063E77EB3B14BULL, 0x3A550AB7B34C9E00ULL, 
            0x7BED7F994202657AULL, 0xDC23E81BF8A89384ULL, 0xC2FD2FB1A39FCD07ULL, 0xA0A79629D11E67BBULL, 
            0x321D7C74D54AB650ULL, 0xE14E8D684274B288ULL, 0x679453300BA4EC15ULL, 0x48B2C1595F20FE28ULL, 
            0x19C8A517C11F1D63ULL, 0x8A409547565E5E84ULL, 0xEC2DCD8FC614D6E4ULL, 0xAFF61937475C3B96ULL, 
            0x51F6E104AF1C2960ULL, 0x20AFB0B631CBFD12ULL, 0x66FF2E791A6F9E3EULL, 0xC7A264A8F8000AC2ULL
        },
        {
            0xA587AD6740E77BD2ULL, 0x23414232E394DA37ULL, 0xEF7AFADC7DBB4953ULL, 0xA6526103667B1862ULL, 
            0x251219FE9D31AC41ULL, 0xDBE7E3C1026DAF1DULL, 0x1DD801DA0A7B8558ULL, 0x86EBE0E328607B43ULL, 
            0x4881708C550E1C34ULL, 0xC85A6D5999D9375AULL, 0x2FC95C3443AF8644ULL, 0xAAC388E10EF8AF6EULL, 
            0x2E03FAA5AE633E41ULL, 0x74E2CDB6A0C136E9ULL, 0x9BC5A18F3C34E973ULL, 0xA6BCF510553EDFE6ULL, 
            0x3EE4C19E9D4B7005ULL, 0xE5704487494AAEFDULL, 0x0135C49A52F09B30ULL, 0x4BE0F32707C3C20FULL, 
            0x373FAA052B3FD558ULL, 0x2242EF5C3DC5730AULL, 0x670A0EE98208284DULL, 0xC7A69CCAF4B6ED5DULL, 
            0xEADD28E015F87F60ULL, 0xA0D917DAD17F9639ULL, 0xE6D1C78469FEAD03ULL, 0xA11B2A972B4ED039ULL, 
            0xABFFD6DE729B9A76ULL, 0x82D86837A3E95719ULL, 0x04DA5D794302DF9BULL, 0xE5F1DFDDA801754CULL
        },
        {
            0x50EA8F5E4A986AF4ULL, 0x09115B43AE2A97A6ULL, 0x575B5166C0EAAC2FULL, 0xA108DC22B01EAD25ULL, 
            0x530E06687A4074D0ULL, 0x4A825DF4BB98E18CULL, 0xC78FD53A215637CEULL, 0xAD33ADD8EE8FEB74ULL, 
            0x97C4A58D2519FF3FULL, 0x5B5246E67FD4DF74ULL, 0xE3F929A7162FDAD7ULL, 0x3FF1855FA37C2D79ULL, 
            0xBD65B2F578176FDFULL, 0x7BEDF8E23BD81D27ULL, 0xFA172BEFC7FD9A08ULL, 0xD8A3916CF89B2CFAULL, 
            0xDE7695E8F3DAD8DEULL, 0x88494D60EE200ADDULL, 0x9BF8955764AD6E0BULL, 0x0A81E308267D9A00ULL, 
            0xC380E623A14EF4B3ULL, 0x4BD9A0D086D44962ULL, 0x645496D43881FC0FULL, 0x82F14DDA85642AB8ULL, 
            0x97310F8EB3A5320CULL, 0x4D79F39A8BECA9A2ULL, 0xE7764BDDF5F27B85ULL, 0x79A8C2E921270E69ULL, 
            0xACC192606D18AEDAULL, 0x061E42C6CE81B0ACULL, 0xD17DB61939B4E11DULL, 0x7A90993BBBD2F626ULL
        },
        {
            0x199C2B4AE5C2F507ULL, 0x916B1E99D195501DULL, 0x1377807C21D8FAC2ULL, 0x636737C753CEBC9FULL, 
            0x297270F9BBC5F438ULL, 0xC586B4FD32B449F1ULL, 0xE7D2E5DD6D09B522ULL, 0x8FDDA744FB098263ULL, 
            0xF2BE5CD51C7D7245ULL, 0x48DEA3B806887EBFULL, 0x966678A028B1B1D0ULL, 0xCBC846A7F3ED1858ULL, 
            0xF454CBE6D8E268C4ULL, 0xC61FAE84EB38374BULL, 0x79BC1072A07ECC1BULL, 0x0EF3A6480E2BCCA0ULL, 
            0x1A57AEC26A300199ULL, 0x04A7CF1BF4CE4102ULL, 0xD204429C487D0A0AULL, 0xAB85364822D5F4A6ULL, 
            0x00EE8F8A25914647ULL, 0x0123BEE72E2FEDD3ULL, 0x7947BE59530FC9E3ULL, 0x7DB4613C398F47F4ULL, 
            0xC065A817D80956A6ULL, 0x613E6B22F4E4D289ULL, 0xCC4393E867F32131ULL, 0x8E04E3DCB962F6F4ULL, 
            0x9CA66B1F115753B6ULL, 0xC9B4D56B6ADD1D83ULL, 0xC6B101BCF50195C9ULL, 0x19F09C218D29E90DULL
        },
        {
            0xD71805A21CF9EB95ULL, 0xE983C0EBAC442492ULL, 0xF920147B058B9C82ULL, 0x0280C4A9D764D4C3ULL, 
            0x4CD0E4CE469A4191ULL, 0x251D32D2A6547DBAULL, 0xAC7CD662F4C14832ULL, 0xD85CA856BAFA95E3ULL, 
            0x84D737AE78D34EFEULL, 0x8435B95CCB2ED58CULL, 0x262CC59761975F25ULL, 0x6EB801F347271BF6ULL, 
            0x143A86AA0E0C6EF9ULL, 0x99530D577B9EE640ULL, 0xF0CA7CC05B539750ULL, 0xC1FC716E0CAA01DAULL, 
            0x16E494A957B27A7BULL, 0x8A741C578536D37DULL, 0xC3122F5A90E8919AULL, 0x149DEA657EA91551ULL, 
            0x56489A5C7CD31EE5ULL, 0xC0EEF199CFC3B7DBULL, 0x2E09F93C136A26FCULL, 0x92EFE8ACC1D11CB4ULL, 
            0xAF20B5E38D55D62BULL, 0x1F52C54971FA6E7AULL, 0xF1656B493D0CBFD9ULL, 0xC2DA8FB9FA3D83C5ULL, 
            0x7077CF7F4BA39B6BULL, 0xB4CFF40AD39ACD0BULL, 0xCCF7593D90F72DDDULL, 0x3197AC0D9D4FE6D0ULL
        },
        {
            0xBE7DA5F3158FCF8BULL, 0x1C29ACB590A26851ULL, 0xCB6FA2B02B79B077ULL, 0xFAD8023872A92BD9ULL, 
            0x6E17006759410FD5ULL, 0x4E3FCB29ABBD08AFULL, 0xBE4E177F0674FC4CULL, 0x30E1CD3A23732B89ULL, 
            0x61470C79ED4190BDULL, 0x6E5F065D01B840EDULL, 0x2825F679F88CAE40ULL, 0xCF43F1403D3C8833ULL, 
            0x210AE901E5C3E5C3ULL, 0xB0C86A40487DD1BEULL, 0x85A97B9AA2ED5D48ULL, 0x3F1C1683D10433A0ULL, 
            0xAE8AC7EBA7CBE955ULL, 0xB875C21706DB6A50ULL, 0xE9514E3E4BEEAEECULL, 0xF625FC60F2C4E6A5ULL, 
            0x01D30A30F2DE27B0ULL, 0xFA66428C6D07621EULL, 0x7A78D09D0D27FC23ULL, 0x6C5168B4873E8402ULL, 
            0x07015B94194B57C9ULL, 0x270E870A72867C7BULL, 0xCF975037B85AA766ULL, 0xF1B10BD0201538D5ULL, 
            0x79AC1E4F7ECEDA0CULL, 0x5F8E1088E1E3E489ULL, 0xF0BBEC57BE0431E4ULL, 0x6260257AC3310537ULL
        }
    },
    {
        {
            0xBF209EBBC5350C0DULL, 0x30D54652472238B5ULL, 0xFB821436C6DD9DA8ULL, 0x3002716A68A13EDCULL, 
            0x128F27593DFE63D1ULL, 0x7C5CD7741DFAF72EULL, 0xEED9E04B034B368CULL, 0xD1D52E7D7D1044EEULL, 
            0x468BB7287A37F488ULL, 0x6815AE689062BDF6ULL, 0xD998E037291942BBULL, 0xF99B4EFFF995DF2CULL, 
            0x0281B28BD8E72376ULL, 0xABC08D1FDE93A82CULL, 0x694D106946BEBA79ULL, 0xAE12431DFA1204C1ULL, 
            0x2BEB4242702A0BF5ULL, 0xC320DE789992A82FULL, 0xC9CDA401C2D8A3F0ULL, 0xA82BEEA297BB1612ULL, 
            0x088AEAA61F15925EULL, 0x2B10133C71CE10A4ULL, 0x02B7BD673D5EADD2ULL, 0x57F1F42A28958307ULL, 
            0x306F557170B7FF29ULL, 0x6B80B6E12F29CC2FULL, 0xF11D7A224159679CULL, 0x315F06E781402EDAULL, 
            0x1956BAEBCD92FCD3ULL, 0x9AE08D40D3C7E1E9ULL, 0xE6F1A4813FBB0DBCULL, 0x9EC4496106A20975ULL
        },
        {
            0xEA7551613FB80F28ULL, 0xBE01AF3836A8BA0EULL, 0x66BC5BF95C66A27DULL, 0xB37A7BAF94A6E886ULL, 
            0xB4534B11C54627A1ULL, 0xA6BC7E1188678963ULL, 0x4B7A00D46FEA31C9ULL, 0x41E3FEF456846433ULL, 
            0x5FAB04D824E35B35ULL, 0x34A35D286EE0FC4AULL, 0x4FB9BC1DA815E530ULL, 0xB976C19F1FE8BB51ULL, 
            0x0543CA0D2D492FE4ULL, 0x9E7B1AA415AF9194ULL, 0xB48AB8EF406EE5F4ULL, 0x612FDAB23C0DE6A9ULL, 
            0xF0742B7FB6BB3E92ULL, 0x616A6827AA115B01ULL, 0x35F9BF2AD76BE9C7ULL, 0xCC07F30A8722F4D8ULL, 
            0x2DCF57A159A2EE31ULL, 0x2B6AE4B086DF1B9AULL, 0x0CB6A51F8072D075ULL, 0x61417BB3FA4DDCEAULL, 
            0x661CDB9A23D3B3F1ULL, 0x72E2039CBD09F17AULL, 0x3B1256F9C2045A5DULL, 0xDC9B9606A674B641ULL, 
            0x21C41DBE5D2FC3B0ULL, 0x8437E2B8459DF9B4ULL, 0x449DE283112BF415ULL, 0x1B466E39C52685FCULL
        },
        {
            0x976C64C4FE4D7DD2ULL, 0xED8377DA7EA8BFE2ULL, 0x81175697CCC66748ULL, 0xE0D2BC494C79D22AULL, 
            0xE2B4327FC0A3EC9BULL, 0x6656F88FD69B5CADULL, 0x3F33852719018519ULL, 0x468E5B8E0B70B60FULL, 
            0xB2430C9512BA6110ULL, 0x2C162B233EBF0CC5ULL, 0x8C328BD22D96DCC5ULL, 0xB7475C32C4EA3D57ULL, 
            0x624D30F5CD2E236EULL, 0x4A58BDC985AF617FULL, 0xA84FE3ECA4037A3CULL, 0x75C408857A6EE310ULL, 
            0xED945E07DD0E3998ULL, 0x581838BCAEF792FBULL, 0x3F2287A827386027ULL, 0xB93709A7B26CDF59ULL, 
            0x4238A281B4B3D59CULL, 0x4307F6EFBEE4C085ULL, 0x1608913C4361FD11ULL, 0x9B5D915784086E9BULL, 
            0x8A48A4C35E06310EULL, 0x8588E5BA22613BA0ULL, 0x6AB2B42292118EDCULL, 0x001D3A8C85F57CE5ULL, 
            0x2878860A9B5F2135ULL, 0x1ABA6E250BF46397ULL, 0xD76BFF4D91616EB2ULL, 0xCE32CCE8D3C31C56ULL
        },
        {
            0xE50FE12D02E63FBFULL, 0x5E224D44BB3BF1AAULL, 0xF4C834C208A57239ULL, 0x3C30457585C4698CULL, 
            0xFF9BB24A3550BC10ULL, 0xC48C255A06A2D126ULL, 0xBB1924EC7D128CF5ULL, 0xEFFEBBB64B3D2902ULL, 
            0xA1717EE8D7E51C3AULL, 0x70F7739BAEC14EF2ULL, 0xDE85F3CC3DD307D5ULL, 0x1AEA5557C338D4E1ULL, 
            0x94055FD9BE996BC2ULL, 0x3E308F7FDBE4628EULL, 0x9249F9277E553694ULL, 0x77CE703F84805D23ULL, 
            0xADA4D0DAD4B8D0F4ULL, 0x6D9E4B262254B58EULL, 0xE46BDF7739264C7DULL, 0x6654DD1CE9C130D3ULL, 
            0x7C7C152775939A19ULL, 0x66FA97F2CB4A1F3EULL, 0xA0F9B0B00DEC40A7ULL, 0xA67E7122EAECA219ULL, 
            0xB9EBC1DD3544EC39ULL, 0x10C52074063644A9ULL, 0x8C55F50C44200222ULL, 0xB87D77A73666C57EULL, 
            0x745C8479669EEF98ULL, 0x88463B5467E23011ULL, 0xBC1A02204A59078AULL, 0x562EFE4B34ADCFDEULL
        },
        {
            0xF8E048A8CDFCC906ULL, 0x1FA4BD8B1BB4DB61ULL, 0x276EF96A83EE8281ULL, 0x2C11061F35876B43ULL, 
            0x0012DD3353CCAA25ULL, 0x21F7CC2FBAFE5A9AULL, 0xBBE4749979C900E6ULL, 0xE9A3701354789943ULL, 
            0x89CFDC3DC3D92728ULL, 0xE4CBD0E3C4D98D3FULL, 0xC061A519CB69CE44ULL, 0xDDDE064A9C74643DULL, 
            0x61E58C85F504ACF1ULL, 0x1AA27BA64AF89227ULL, 0xC660F1E54CB7403CULL, 0xD974386F2B8B702EULL, 
            0x89E6583936BFBE5AULL, 0x3CBA4AC4AEE72D74ULL, 0xB322494B24CD5AF8ULL, 0x56DB399EBDC3872CULL, 
            0xD6FBD18602B2B865ULL, 0xC8EDD9525682EBA0ULL, 0xA5173D1B16E0C856ULL, 0x3497D4016FA6C3FAULL, 
            0x7341D7DA4CECE8B1ULL, 0x9B8803BD100076E2ULL, 0x8A90BEC7AB70CA4FULL, 0xC426A0BEBE08C9D4ULL, 
            0xFEF1A5873106EC2FULL, 0x0F6ABAE8536A82D1ULL, 0x980C9A05D8F9761FULL, 0x03D23583D9A566C1ULL
        },
        {
            0x50EF354CF089ECF0ULL, 0xC53D707FA0D568E0ULL, 0xC460488FD85DDDAAULL, 0x0A2E2066172C8C55ULL, 
            0x8484FCF28767B01BULL, 0x1626D0B31CD62419ULL, 0x93C7E8A522515D4CULL, 0x5FC1FBD7436F7DA1ULL, 
            0x014D9D074CDA9049ULL, 0x3F41F69A041B8531ULL, 0x6C4443239BF956FFULL, 0x760FF14CF3D93323ULL, 
            0xAFBFB9B58FC24232ULL, 0xAF52416CAAF8A2F0ULL, 0x14FAFD111393D9D4ULL, 0xE3E0710D5462C5C6ULL, 
            0x4C67116172B0B3E7ULL, 0x4541FE190B5D2438ULL, 0xAF7EE6B2003BF8C5ULL, 0xFA56B48A298D2A63ULL, 
            0x4D510BA162D77006ULL, 0x27A564C2E501A97FULL, 0x1C18A620DA2262EDULL, 0x153A05F55E8EACD3ULL, 
            0x3637551407EDA8E1ULL, 0xDEB998084515575DULL, 0x53FFF540E1B4585FULL, 0x2A55361C896FE2CBULL, 
            0xA0A0E475E3B59AA3ULL, 0xD3C9DF8A31BAF569ULL, 0xFF9411884C11173EULL, 0x6E7655D59AB01723ULL
        }
    }
};

const TwistDomainConstants TwistExpander_EdChan_0006::kPhaseCConstants = {
    0x39AAF99695AA2FD5ULL,
    0x81554648A7AE2D57ULL,
    0x165CADBCD2622281ULL,
    0x39AAF99695AA2FD5ULL,
    0x81554648A7AE2D57ULL,
    0x165CADBCD2622281ULL,
    0x77CCDF5E09603B08ULL,
    0x47EDACBE1946D619ULL,
    0x43,
    0x93,
    0x85,
    0xF4,
    0x99,
    0x16,
    0xCF,
    0x6E,
    0x7D,
    0x6C
};

const TwistDomainSBoxSet TwistExpander_EdChan_0006::kPhaseASBoxes = {
    {
        0xF9, 0x64, 0xC7, 0x59, 0xB5, 0x70, 0x67, 0x7E, 0xAE, 0xFF, 0xEE, 0x24, 0x2B, 0xDA, 0xE6, 0x60, 
        0xCA, 0x17, 0xE0, 0xC3, 0x3C, 0x0B, 0x31, 0x38, 0x7C, 0xF0, 0xC8, 0xF1, 0x2D, 0x52, 0x77, 0xCE, 
        0x51, 0x01, 0x99, 0x1D, 0x34, 0x1A, 0x05, 0x50, 0xB9, 0xF5, 0xA1, 0x9F, 0x5D, 0x6E, 0x09, 0xC1, 
        0x4F, 0xF3, 0xAD, 0xE4, 0xF8, 0x29, 0xE8, 0xB7, 0x65, 0xFC, 0x9A, 0x9C, 0xB2, 0xBA, 0xE1, 0x4A, 
        0x76, 0xB0, 0x19, 0x75, 0xD2, 0xC0, 0x21, 0x45, 0xA8, 0x0D, 0x7D, 0x46, 0xA9, 0x3B, 0x33, 0x8D, 
        0x0F, 0x40, 0x58, 0x28, 0x87, 0xA6, 0xCB, 0x86, 0xD7, 0x6D, 0x7F, 0x80, 0x08, 0x92, 0xAC, 0x7A, 
        0xE7, 0xA5, 0x41, 0x9B, 0x26, 0x35, 0x84, 0x2A, 0xBC, 0x16, 0xD5, 0x4E, 0x25, 0x30, 0x07, 0xCC, 
        0x82, 0x6F, 0x0C, 0x2E, 0x3E, 0x8A, 0x27, 0x88, 0xF2, 0xF6, 0xE3, 0x20, 0x71, 0x8C, 0x12, 0x6A, 
        0xF7, 0xC6, 0x5B, 0x8F, 0x91, 0x8E, 0x1B, 0x4C, 0xD9, 0x78, 0xE9, 0x97, 0xC4, 0x1C, 0x5F, 0xD0, 
        0xD3, 0x3D, 0xB8, 0x79, 0x0A, 0x83, 0xB3, 0x13, 0x96, 0x02, 0xE5, 0x66, 0xF4, 0x36, 0xFB, 0x44, 
        0x11, 0x23, 0xAA, 0x5C, 0x22, 0xC2, 0x90, 0xBB, 0x43, 0xCD, 0xDB, 0x5E, 0x14, 0x03, 0x06, 0xD4, 
        0x2C, 0x47, 0x93, 0xEA, 0xA3, 0x57, 0x1F, 0x6B, 0x4D, 0xBF, 0x2F, 0x15, 0x63, 0xFE, 0x56, 0xD1, 
        0x68, 0x73, 0x37, 0x94, 0xEF, 0xDF, 0x7B, 0x54, 0x98, 0xDE, 0xED, 0xC5, 0xAF, 0x55, 0x39, 0x9E, 
        0xFA, 0xBD, 0xDC, 0x49, 0x85, 0x72, 0xA2, 0x4B, 0x74, 0x1E, 0x18, 0x42, 0x00, 0x69, 0x48, 0xA0, 
        0xB6, 0xB1, 0x3A, 0xD6, 0xFD, 0xC9, 0x89, 0xA4, 0x10, 0x62, 0xA7, 0x3F, 0xDD, 0x95, 0x0E, 0x53, 
        0x04, 0xE2, 0xB4, 0x61, 0xD8, 0x8B, 0x81, 0x5A, 0xAB, 0x9D, 0xBE, 0xEC, 0x6C, 0x32, 0xCF, 0xEB
    },
    {
        0x53, 0x9C, 0xA3, 0xD7, 0x3E, 0xC0, 0x27, 0x04, 0x94, 0x37, 0xB4, 0xBC, 0x4A, 0x6D, 0x14, 0x71, 
        0xDC, 0x33, 0x70, 0x4E, 0xAD, 0xCF, 0xD2, 0x40, 0x8D, 0xC1, 0x55, 0xF3, 0x2E, 0xCC, 0x96, 0x31, 
        0x77, 0xE6, 0xF6, 0x1A, 0x0D, 0x4C, 0x0B, 0x45, 0x73, 0x1E, 0x62, 0x92, 0x3A, 0xB5, 0x46, 0xC7, 
        0x02, 0x7A, 0x2F, 0x9D, 0x61, 0xC3, 0xD0, 0xB7, 0xAE, 0x8C, 0x4D, 0x29, 0x68, 0xC8, 0x42, 0xDD, 
        0xA4, 0xE1, 0xF7, 0x1F, 0xCD, 0xF5, 0x63, 0x2B, 0xF0, 0xAB, 0xBF, 0x90, 0xC2, 0xFB, 0x5B, 0xAA, 
        0x22, 0xF4, 0xE5, 0xF1, 0x83, 0x34, 0xEE, 0xB1, 0x12, 0x0E, 0x36, 0xD5, 0x74, 0xED, 0x1D, 0xE9, 
        0x26, 0x8F, 0xC6, 0x7F, 0x35, 0x3F, 0x38, 0x78, 0xAC, 0x01, 0x9B, 0x30, 0x8E, 0xE0, 0x82, 0xB8, 
        0x5C, 0x87, 0x99, 0x95, 0x24, 0xFC, 0x07, 0x75, 0x48, 0xA5, 0xCB, 0x51, 0xF2, 0x98, 0xEC, 0x58, 
        0x97, 0x91, 0x5E, 0x23, 0x56, 0x11, 0x7E, 0xB9, 0xD6, 0x60, 0xE2, 0x32, 0x18, 0x28, 0xB3, 0x44, 
        0xFF, 0x9F, 0x41, 0x52, 0xFD, 0x6E, 0x5A, 0xDE, 0x00, 0x5D, 0xAF, 0x15, 0x2C, 0x84, 0xDA, 0x19, 
        0x57, 0xEA, 0x79, 0x08, 0xD8, 0x7C, 0x64, 0xFA, 0x4F, 0x8A, 0x5F, 0x81, 0x88, 0x6F, 0xB0, 0xA9, 
        0x1C, 0xA2, 0xDF, 0x59, 0xEB, 0x13, 0x93, 0x6A, 0x8B, 0x17, 0xA7, 0xBA, 0xCA, 0x05, 0x21, 0x76, 
        0xD1, 0x7B, 0xB6, 0x89, 0x86, 0xB2, 0xDB, 0xA8, 0xC4, 0x80, 0x0F, 0x2A, 0xA6, 0x9A, 0x72, 0xA0, 
        0xE8, 0x9E, 0x09, 0x66, 0x0A, 0x49, 0xD9, 0xEF, 0x2D, 0xA1, 0xC5, 0x7D, 0xD4, 0xE3, 0x54, 0x50, 
        0x85, 0xD3, 0xC9, 0x20, 0xBE, 0x67, 0x47, 0xBD, 0x65, 0xF8, 0x06, 0x16, 0x3B, 0xBB, 0x10, 0xFE, 
        0x39, 0xF9, 0x0C, 0x43, 0xE4, 0xCE, 0xE7, 0x6C, 0x4B, 0x1B, 0x25, 0x3D, 0x3C, 0x69, 0x03, 0x6B
    },
    {
        0xE7, 0x2E, 0x51, 0x8C, 0x29, 0x32, 0x3A, 0xFD, 0xAE, 0x39, 0xEF, 0x6F, 0xF4, 0x08, 0xFE, 0xB0, 
        0x8A, 0x02, 0x20, 0xCF, 0xFC, 0x0F, 0x27, 0x62, 0xBD, 0xA2, 0xCA, 0xF6, 0x2A, 0x89, 0xB8, 0x14, 
        0x9D, 0x5E, 0x5D, 0x53, 0xED, 0xD9, 0xC0, 0xC9, 0xA6, 0x68, 0x35, 0x83, 0x12, 0x7F, 0x4F, 0x8F, 
        0xD0, 0xB6, 0xBA, 0xBE, 0xB3, 0xB4, 0x31, 0x69, 0x7A, 0x2D, 0x49, 0x97, 0xA3, 0xB2, 0x74, 0x1A, 
        0xEC, 0xE3, 0xCD, 0xF8, 0x19, 0xDB, 0xA5, 0x81, 0x70, 0xD1, 0xE9, 0x95, 0x24, 0x76, 0x67, 0x41, 
        0x91, 0x4B, 0xD8, 0xE0, 0x10, 0xBF, 0xDE, 0x44, 0xD3, 0x6B, 0xA9, 0x9A, 0x1B, 0x58, 0xEE, 0x63, 
        0xAA, 0xAB, 0x1F, 0x1D, 0x2F, 0xB9, 0x04, 0xA0, 0x6C, 0x56, 0x93, 0x84, 0x3B, 0x73, 0x80, 0x54, 
        0xDA, 0x2B, 0x85, 0x3E, 0xBC, 0xCB, 0x7B, 0x8B, 0xE2, 0x7C, 0x34, 0xF1, 0x66, 0x15, 0xC8, 0xE1, 
        0x28, 0x05, 0xCC, 0x01, 0x4C, 0x55, 0x8D, 0xC4, 0x1C, 0x23, 0x65, 0x92, 0x45, 0x07, 0x52, 0x59, 
        0x4D, 0xA8, 0xF2, 0x77, 0x5B, 0x8E, 0xF7, 0x9C, 0xC6, 0x4A, 0xEA, 0x6E, 0x3C, 0xAD, 0xA7, 0xD5, 
        0xDC, 0xE5, 0x30, 0x46, 0xB1, 0x9B, 0x18, 0xE6, 0x5F, 0x00, 0x5C, 0x06, 0x16, 0x1E, 0xD4, 0xC7, 
        0x7E, 0xC1, 0x0C, 0x71, 0x75, 0x43, 0x13, 0xB5, 0x90, 0x78, 0x6A, 0x42, 0xA4, 0x6D, 0x17, 0x0D, 
        0xA1, 0x26, 0xF9, 0x86, 0xBB, 0xC2, 0x37, 0x57, 0x09, 0x96, 0xFB, 0x11, 0xFA, 0x03, 0x36, 0xD7, 
        0xF3, 0x38, 0xD6, 0x0E, 0x50, 0x72, 0x21, 0x4E, 0xAC, 0x47, 0x99, 0x0B, 0x0A, 0xF5, 0x5A, 0x61, 
        0x3D, 0xB7, 0x22, 0x87, 0x79, 0x9E, 0xDF, 0xFF, 0x88, 0xF0, 0xEB, 0xE8, 0x82, 0xD2, 0xC5, 0xDD, 
        0x94, 0x60, 0x7D, 0xE4, 0x48, 0x9F, 0xCE, 0x98, 0x64, 0xC3, 0x2C, 0xAF, 0x3F, 0x33, 0x40, 0x25
    },
    {
        0x67, 0x9B, 0x1B, 0x62, 0x12, 0x34, 0x1E, 0x09, 0x15, 0xA9, 0x4D, 0xC3, 0x6B, 0xD2, 0xBE, 0x45, 
        0xA3, 0x07, 0x70, 0xC5, 0x41, 0x5B, 0xF9, 0x9F, 0x19, 0x01, 0xB3, 0x94, 0xA5, 0x14, 0x6F, 0x7D, 
        0x91, 0xB8, 0x0F, 0xE4, 0xB2, 0xBF, 0x66, 0x04, 0x3F, 0x4A, 0xBD, 0xC1, 0xBC, 0x78, 0x4B, 0xD5, 
        0xDD, 0x84, 0x90, 0xAE, 0xF2, 0x7B, 0x83, 0x02, 0x0E, 0x2C, 0x8A, 0x44, 0x49, 0xBA, 0xE5, 0x96, 
        0xFA, 0x59, 0x3A, 0x7F, 0x21, 0x40, 0x88, 0x3E, 0xDB, 0x95, 0x8C, 0xBB, 0x4E, 0x1A, 0xE9, 0xA0, 
        0x85, 0x75, 0xF7, 0xEE, 0x43, 0xE6, 0x36, 0xD6, 0x6A, 0xFD, 0x9C, 0x18, 0xDE, 0x79, 0x05, 0xD7, 
        0x2B, 0x63, 0xE0, 0x1F, 0xD3, 0x27, 0xC6, 0xFE, 0x74, 0x92, 0x7A, 0x48, 0x56, 0x6C, 0x76, 0x6D, 
        0x08, 0xED, 0x00, 0x20, 0x51, 0xFB, 0x46, 0xEB, 0x11, 0xCF, 0xF5, 0x1D, 0xA1, 0x35, 0x4C, 0xA6, 
        0x5A, 0x8E, 0x72, 0xB0, 0xFC, 0x25, 0x2A, 0x58, 0x57, 0xC7, 0x16, 0x32, 0x9E, 0x71, 0xAC, 0x31, 
        0xB4, 0xD4, 0xAA, 0x52, 0xCE, 0x9D, 0xDC, 0xD9, 0xA7, 0x3D, 0x3B, 0x8B, 0xDF, 0xA2, 0x77, 0xAB, 
        0xC9, 0x98, 0xCB, 0x29, 0x0D, 0x50, 0x69, 0x2F, 0xF0, 0xF8, 0x47, 0x39, 0x82, 0xA8, 0xE3, 0xEF, 
        0x30, 0x2E, 0xEC, 0x93, 0xAD, 0x5F, 0xF4, 0x33, 0xCD, 0xF1, 0xB5, 0x17, 0xC0, 0x3C, 0xCA, 0xA4, 
        0xB6, 0xB1, 0x37, 0xB7, 0xD8, 0x99, 0x42, 0xDA, 0x9A, 0x0C, 0xC8, 0x0B, 0x80, 0x4F, 0x0A, 0x54, 
        0xE2, 0xE1, 0x1C, 0x13, 0x53, 0x24, 0x38, 0x03, 0xEA, 0x61, 0xAF, 0x65, 0x2D, 0x23, 0x86, 0x28, 
        0x97, 0xCC, 0x8F, 0xFF, 0xB9, 0x26, 0x7E, 0xF6, 0x5C, 0x55, 0x73, 0xC4, 0x89, 0x22, 0x10, 0x81, 
        0xF3, 0x60, 0x87, 0xD0, 0xC2, 0x6E, 0x8D, 0xE7, 0x5E, 0xD1, 0x64, 0x5D, 0x68, 0x7C, 0xE8, 0x06
    },
    {
        0x4C, 0x91, 0x65, 0xCE, 0x59, 0x2A, 0xE7, 0x3D, 0xB7, 0xC8, 0x81, 0xA7, 0xF2, 0x0F, 0x12, 0x21, 
        0x04, 0xEF, 0x96, 0xD5, 0x3F, 0xC7, 0x5E, 0x8F, 0x09, 0x9D, 0x30, 0xDF, 0x76, 0x2B, 0xEC, 0xB4, 
        0x5D, 0x60, 0x4F, 0x48, 0xAC, 0x8E, 0xD0, 0x1F, 0x7A, 0x6F, 0xE2, 0xCB, 0x7E, 0x36, 0xF3, 0xE1, 
        0x41, 0xEB, 0xC1, 0x26, 0x0E, 0xC6, 0x05, 0x6D, 0xD3, 0xBE, 0x39, 0xBD, 0x9F, 0x0C, 0xD4, 0xB3, 
        0xAE, 0xAB, 0xF8, 0xD8, 0x9C, 0xA3, 0x55, 0xE6, 0x33, 0x43, 0x4B, 0x90, 0x71, 0xF9, 0x6A, 0xF4, 
        0x77, 0x14, 0x8C, 0x84, 0x53, 0x24, 0x46, 0x11, 0x6E, 0x40, 0x7F, 0x95, 0xB1, 0xAA, 0x83, 0x8D, 
        0x50, 0x52, 0x56, 0x7B, 0x93, 0xEE, 0x25, 0xB0, 0x88, 0xAD, 0x5A, 0x03, 0xE5, 0x1C, 0xE4, 0x80, 
        0xA1, 0x74, 0x01, 0x00, 0x0B, 0x32, 0xD1, 0x06, 0xA9, 0x19, 0xE0, 0x17, 0x68, 0xB6, 0x1D, 0x86, 
        0x5B, 0x27, 0xFA, 0xC0, 0xDC, 0x82, 0xCC, 0x37, 0x79, 0xB9, 0x47, 0x58, 0x13, 0x0A, 0x4A, 0xA8, 
        0xDE, 0x7D, 0x38, 0xFB, 0x85, 0xE3, 0xDD, 0x5F, 0x1A, 0x16, 0x64, 0xA5, 0x2D, 0x98, 0x78, 0xA4, 
        0x6B, 0x61, 0x07, 0x3C, 0x23, 0x97, 0x9E, 0x4E, 0x62, 0xC2, 0x4D, 0x08, 0x99, 0x54, 0xA6, 0x18, 
        0x34, 0xD2, 0xE8, 0x31, 0xD6, 0xD9, 0x7C, 0xC4, 0x75, 0xFE, 0x42, 0xDB, 0x57, 0x8A, 0x9B, 0xEA, 
        0xB2, 0x5C, 0xDA, 0x2E, 0xC3, 0xFD, 0xCF, 0xAF, 0x0D, 0xBF, 0xF7, 0x51, 0xF5, 0xED, 0xCD, 0x89, 
        0x3A, 0xCA, 0x8B, 0xC5, 0x67, 0x1E, 0x94, 0xF1, 0x9A, 0x3E, 0xBA, 0x20, 0x22, 0xF0, 0x87, 0xA0, 
        0x2F, 0xE9, 0xBB, 0x2C, 0xFC, 0x72, 0x44, 0x10, 0x29, 0x15, 0x66, 0x49, 0xC9, 0x6C, 0x35, 0x69, 
        0x92, 0xA2, 0x1B, 0x63, 0x3B, 0x70, 0xD7, 0xB8, 0x45, 0xFF, 0xBC, 0xB5, 0x02, 0x28, 0xF6, 0x73
    },
    {
        0x50, 0xE7, 0xF3, 0xC0, 0x6B, 0x47, 0x63, 0xED, 0xA5, 0xD3, 0x74, 0x36, 0x58, 0xBE, 0x5D, 0x24, 
        0xDD, 0xBB, 0xDE, 0x30, 0x7C, 0x32, 0x52, 0xBF, 0xAD, 0xBD, 0x9D, 0x79, 0xDB, 0x6D, 0x00, 0x1E, 
        0xE9, 0x5B, 0xEB, 0xD2, 0x55, 0x95, 0x98, 0x2D, 0x81, 0xBA, 0xCB, 0x68, 0x03, 0x8E, 0x72, 0x70, 
        0x20, 0x39, 0x21, 0x1D, 0x94, 0x18, 0xF7, 0x2B, 0x23, 0x57, 0x6F, 0xEC, 0x2C, 0x05, 0x1A, 0x27, 
        0xC4, 0x6C, 0x11, 0x40, 0x97, 0xB4, 0x31, 0x49, 0x26, 0xB1, 0x69, 0xCD, 0xE2, 0x3B, 0x12, 0x4B, 
        0xF1, 0x4E, 0x04, 0xDC, 0x22, 0x8C, 0x19, 0xE6, 0x90, 0x0A, 0x29, 0x65, 0xB6, 0x46, 0xE5, 0x2E, 
        0x99, 0x08, 0x8A, 0xAB, 0x76, 0x91, 0xA6, 0x9C, 0x86, 0x7F, 0xD0, 0xE4, 0xF2, 0x96, 0xD8, 0x5E, 
        0x25, 0x4A, 0x75, 0x5F, 0x3C, 0x0C, 0xB2, 0x4C, 0xFD, 0x3E, 0x5A, 0xF5, 0x83, 0x8F, 0xBC, 0x4D, 
        0xFA, 0x37, 0x80, 0x0B, 0xC2, 0xCF, 0x51, 0xA4, 0x3A, 0x6E, 0x33, 0x41, 0x77, 0x16, 0x43, 0xD7, 
        0x53, 0xB8, 0x45, 0xAA, 0xF6, 0xE1, 0xE8, 0x78, 0x85, 0xDF, 0xD9, 0xA7, 0x7E, 0x15, 0x10, 0x8D, 
        0x38, 0x71, 0x66, 0xC7, 0xB5, 0xF4, 0x06, 0xC1, 0xCA, 0x9A, 0x7A, 0x87, 0x3F, 0x1B, 0x1C, 0x14, 
        0x1F, 0x09, 0x82, 0xB7, 0x8B, 0x6A, 0x92, 0x89, 0x60, 0x02, 0x9B, 0xFB, 0xA0, 0x17, 0xAE, 0x13, 
        0x0D, 0xC3, 0xD1, 0xC5, 0xB0, 0xB9, 0xEA, 0xEE, 0x2F, 0x7D, 0xF0, 0xB3, 0x61, 0x2A, 0x7B, 0xAC, 
        0xD4, 0x42, 0x3D, 0xA3, 0x62, 0x07, 0x4F, 0xE3, 0x84, 0x56, 0xD5, 0x0E, 0x9F, 0xC9, 0x67, 0x0F, 
        0xEF, 0xA8, 0xFF, 0x54, 0x93, 0x59, 0x88, 0xCC, 0xFC, 0x64, 0x48, 0xF8, 0xF9, 0x01, 0x35, 0xA9, 
        0x5C, 0x9E, 0xAF, 0xE0, 0xFE, 0xC8, 0xA1, 0x44, 0xA2, 0x28, 0xC6, 0x34, 0xCE, 0xD6, 0xDA, 0x73
    },
    {
        0xAC, 0x7B, 0x92, 0x13, 0x74, 0xE2, 0x2D, 0x34, 0x67, 0x39, 0x63, 0x7F, 0xF5, 0x14, 0x20, 0xE4, 
        0x12, 0xC1, 0xB5, 0x0D, 0x3A, 0x1B, 0xBA, 0xA5, 0x3E, 0xB3, 0x18, 0xEF, 0x60, 0x06, 0x2B, 0x8D, 
        0x50, 0x52, 0x46, 0x88, 0x79, 0x41, 0xCD, 0x0C, 0xA8, 0x70, 0xED, 0xD3, 0x8C, 0x32, 0x11, 0x07, 
        0x80, 0xE5, 0x31, 0x2A, 0xF0, 0xFF, 0xF6, 0x7E, 0x27, 0x6F, 0x10, 0x85, 0xBD, 0xFE, 0xE9, 0x43, 
        0x77, 0xB7, 0x17, 0x21, 0x57, 0x5B, 0xBC, 0xC9, 0xF2, 0x8E, 0x62, 0x9F, 0xAE, 0xF3, 0xB0, 0xDF, 
        0x84, 0x0A, 0x4F, 0xA3, 0x96, 0x24, 0x4E, 0xCA, 0x94, 0x64, 0x68, 0x5F, 0x4D, 0x53, 0x6D, 0xAB, 
        0x7C, 0x72, 0x56, 0x4C, 0x75, 0x25, 0xC0, 0xA9, 0x6B, 0x9D, 0x9E, 0xDC, 0x23, 0xE6, 0xC7, 0x87, 
        0x55, 0x6E, 0xD2, 0x36, 0x30, 0x16, 0x29, 0x1C, 0xB9, 0x26, 0xE3, 0xE0, 0xBE, 0x83, 0x02, 0xAD, 
        0x7A, 0xCE, 0x19, 0xD5, 0x05, 0x89, 0x1D, 0xD6, 0x42, 0xA1, 0xAA, 0x90, 0xC4, 0xD4, 0x86, 0x5D, 
        0x0B, 0x66, 0xF4, 0xFD, 0x47, 0x09, 0xE1, 0x5E, 0xCC, 0x04, 0x76, 0x71, 0x2C, 0x73, 0xA6, 0x95, 
        0x54, 0xB6, 0xF8, 0xD0, 0xEA, 0x51, 0x59, 0xA2, 0x5C, 0xDB, 0x48, 0xDA, 0x97, 0x58, 0x9B, 0xC2, 
        0x3C, 0xC3, 0x0F, 0xFC, 0xE7, 0xC5, 0x82, 0xF1, 0x8A, 0x3D, 0x6A, 0xCB, 0xB2, 0x65, 0x99, 0x01, 
        0xA7, 0xB4, 0x2F, 0xC6, 0x3F, 0xD7, 0xF7, 0x93, 0x1A, 0x8B, 0x35, 0x98, 0x3B, 0xCF, 0xF9, 0x8F, 
        0xFA, 0x37, 0x81, 0x15, 0x9C, 0xE8, 0xBB, 0x1F, 0x7D, 0xDE, 0x4B, 0x00, 0x0E, 0xFB, 0x49, 0xB1, 
        0x22, 0xEB, 0xAF, 0xC8, 0x33, 0x44, 0x40, 0x2E, 0x08, 0xEE, 0x78, 0x6C, 0xDD, 0x9A, 0xD8, 0x5A, 
        0x91, 0xBF, 0x28, 0xB8, 0x1E, 0x4A, 0x03, 0x45, 0xA4, 0xD9, 0x61, 0x69, 0x38, 0xEC, 0xD1, 0xA0
    },
    {
        0x08, 0xE5, 0xDF, 0x28, 0x3F, 0x15, 0xFF, 0x36, 0x7A, 0xBC, 0xE2, 0x7D, 0xC8, 0x2E, 0x75, 0xDD, 
        0xE6, 0x93, 0xC1, 0xE7, 0x22, 0xF4, 0x1B, 0x1A, 0xBA, 0x09, 0x6A, 0x9F, 0x7C, 0xA5, 0x37, 0xDE, 
        0xBF, 0xEF, 0xAC, 0x88, 0xB5, 0xAA, 0xD7, 0x29, 0x90, 0xA7, 0xCF, 0x18, 0x10, 0xFE, 0x78, 0x6B, 
        0x54, 0x13, 0x60, 0xF9, 0x9E, 0x44, 0x56, 0xB3, 0x73, 0xA6, 0xB6, 0x02, 0x1D, 0x8A, 0x57, 0xFA, 
        0xA1, 0x91, 0xB0, 0xBB, 0xB9, 0xFD, 0xD3, 0x4F, 0xCE, 0x40, 0x2C, 0x55, 0x58, 0x00, 0x97, 0x5C, 
        0xCC, 0xE1, 0xBE, 0xD2, 0x47, 0xED, 0x70, 0xD1, 0x17, 0xE4, 0xA0, 0x65, 0xEE, 0x21, 0xF6, 0x0E, 
        0xE3, 0xF7, 0x77, 0x20, 0xF1, 0x23, 0x5D, 0x5E, 0x3E, 0x05, 0x9B, 0xC2, 0xEB, 0x8D, 0x5B, 0x52, 
        0xE9, 0x68, 0xD6, 0x66, 0xAE, 0x7E, 0x67, 0xF2, 0x85, 0xBD, 0xDB, 0x45, 0x83, 0xCA, 0x3D, 0xC6, 
        0x2B, 0x49, 0xA4, 0xD0, 0x3B, 0x46, 0x3C, 0x4E, 0x34, 0x82, 0xC0, 0x8F, 0xC5, 0x1E, 0x9C, 0x35, 
        0x2F, 0xB4, 0x06, 0x14, 0x62, 0x7F, 0x8B, 0xAB, 0x19, 0xF5, 0x6F, 0x69, 0x31, 0x39, 0x84, 0xD9, 
        0x27, 0x5F, 0x42, 0x86, 0xC9, 0x71, 0xAD, 0x1C, 0xFB, 0xC4, 0xB8, 0x0A, 0x89, 0x63, 0xCD, 0x0D, 
        0xEA, 0xC3, 0xB7, 0xDA, 0x43, 0x0B, 0x04, 0x50, 0xD8, 0x24, 0xF0, 0x1F, 0xC7, 0x2A, 0x9D, 0xA3, 
        0x4A, 0x0F, 0xAF, 0x95, 0x74, 0x80, 0x98, 0x11, 0x3A, 0x16, 0xF8, 0x53, 0xEC, 0x87, 0x8C, 0x8E, 
        0x12, 0xA8, 0x9A, 0xE0, 0xCB, 0x99, 0xD5, 0x6C, 0x2D, 0x92, 0x26, 0x6D, 0x79, 0xDC, 0x76, 0x59, 
        0x25, 0x07, 0x96, 0x81, 0x30, 0xFC, 0x64, 0x61, 0xB1, 0x51, 0x7B, 0x38, 0x0C, 0x03, 0x5A, 0x33, 
        0x41, 0x4D, 0xA9, 0x4B, 0xA2, 0xE8, 0xF3, 0x32, 0xD4, 0x94, 0xB2, 0x6E, 0x72, 0x01, 0x48, 0x4C
    }
};

const TwistDomainSBoxSet TwistExpander_EdChan_0006::kPhaseBSBoxes = {
    {
        0xF9, 0x64, 0xC7, 0x59, 0xB5, 0x70, 0x67, 0x7E, 0xAE, 0xFF, 0xEE, 0x24, 0x2B, 0xDA, 0xE6, 0x60, 
        0xCA, 0x17, 0xE0, 0xC3, 0x3C, 0x0B, 0x31, 0x38, 0x7C, 0xF0, 0xC8, 0xF1, 0x2D, 0x52, 0x77, 0xCE, 
        0x51, 0x01, 0x99, 0x1D, 0x34, 0x1A, 0x05, 0x50, 0xB9, 0xF5, 0xA1, 0x9F, 0x5D, 0x6E, 0x09, 0xC1, 
        0x4F, 0xF3, 0xAD, 0xE4, 0xF8, 0x29, 0xE8, 0xB7, 0x65, 0xFC, 0x9A, 0x9C, 0xB2, 0xBA, 0xE1, 0x4A, 
        0x76, 0xB0, 0x19, 0x75, 0xD2, 0xC0, 0x21, 0x45, 0xA8, 0x0D, 0x7D, 0x46, 0xA9, 0x3B, 0x33, 0x8D, 
        0x0F, 0x40, 0x58, 0x28, 0x87, 0xA6, 0xCB, 0x86, 0xD7, 0x6D, 0x7F, 0x80, 0x08, 0x92, 0xAC, 0x7A, 
        0xE7, 0xA5, 0x41, 0x9B, 0x26, 0x35, 0x84, 0x2A, 0xBC, 0x16, 0xD5, 0x4E, 0x25, 0x30, 0x07, 0xCC, 
        0x82, 0x6F, 0x0C, 0x2E, 0x3E, 0x8A, 0x27, 0x88, 0xF2, 0xF6, 0xE3, 0x20, 0x71, 0x8C, 0x12, 0x6A, 
        0xF7, 0xC6, 0x5B, 0x8F, 0x91, 0x8E, 0x1B, 0x4C, 0xD9, 0x78, 0xE9, 0x97, 0xC4, 0x1C, 0x5F, 0xD0, 
        0xD3, 0x3D, 0xB8, 0x79, 0x0A, 0x83, 0xB3, 0x13, 0x96, 0x02, 0xE5, 0x66, 0xF4, 0x36, 0xFB, 0x44, 
        0x11, 0x23, 0xAA, 0x5C, 0x22, 0xC2, 0x90, 0xBB, 0x43, 0xCD, 0xDB, 0x5E, 0x14, 0x03, 0x06, 0xD4, 
        0x2C, 0x47, 0x93, 0xEA, 0xA3, 0x57, 0x1F, 0x6B, 0x4D, 0xBF, 0x2F, 0x15, 0x63, 0xFE, 0x56, 0xD1, 
        0x68, 0x73, 0x37, 0x94, 0xEF, 0xDF, 0x7B, 0x54, 0x98, 0xDE, 0xED, 0xC5, 0xAF, 0x55, 0x39, 0x9E, 
        0xFA, 0xBD, 0xDC, 0x49, 0x85, 0x72, 0xA2, 0x4B, 0x74, 0x1E, 0x18, 0x42, 0x00, 0x69, 0x48, 0xA0, 
        0xB6, 0xB1, 0x3A, 0xD6, 0xFD, 0xC9, 0x89, 0xA4, 0x10, 0x62, 0xA7, 0x3F, 0xDD, 0x95, 0x0E, 0x53, 
        0x04, 0xE2, 0xB4, 0x61, 0xD8, 0x8B, 0x81, 0x5A, 0xAB, 0x9D, 0xBE, 0xEC, 0x6C, 0x32, 0xCF, 0xEB
    },
    {
        0x53, 0x9C, 0xA3, 0xD7, 0x3E, 0xC0, 0x27, 0x04, 0x94, 0x37, 0xB4, 0xBC, 0x4A, 0x6D, 0x14, 0x71, 
        0xDC, 0x33, 0x70, 0x4E, 0xAD, 0xCF, 0xD2, 0x40, 0x8D, 0xC1, 0x55, 0xF3, 0x2E, 0xCC, 0x96, 0x31, 
        0x77, 0xE6, 0xF6, 0x1A, 0x0D, 0x4C, 0x0B, 0x45, 0x73, 0x1E, 0x62, 0x92, 0x3A, 0xB5, 0x46, 0xC7, 
        0x02, 0x7A, 0x2F, 0x9D, 0x61, 0xC3, 0xD0, 0xB7, 0xAE, 0x8C, 0x4D, 0x29, 0x68, 0xC8, 0x42, 0xDD, 
        0xA4, 0xE1, 0xF7, 0x1F, 0xCD, 0xF5, 0x63, 0x2B, 0xF0, 0xAB, 0xBF, 0x90, 0xC2, 0xFB, 0x5B, 0xAA, 
        0x22, 0xF4, 0xE5, 0xF1, 0x83, 0x34, 0xEE, 0xB1, 0x12, 0x0E, 0x36, 0xD5, 0x74, 0xED, 0x1D, 0xE9, 
        0x26, 0x8F, 0xC6, 0x7F, 0x35, 0x3F, 0x38, 0x78, 0xAC, 0x01, 0x9B, 0x30, 0x8E, 0xE0, 0x82, 0xB8, 
        0x5C, 0x87, 0x99, 0x95, 0x24, 0xFC, 0x07, 0x75, 0x48, 0xA5, 0xCB, 0x51, 0xF2, 0x98, 0xEC, 0x58, 
        0x97, 0x91, 0x5E, 0x23, 0x56, 0x11, 0x7E, 0xB9, 0xD6, 0x60, 0xE2, 0x32, 0x18, 0x28, 0xB3, 0x44, 
        0xFF, 0x9F, 0x41, 0x52, 0xFD, 0x6E, 0x5A, 0xDE, 0x00, 0x5D, 0xAF, 0x15, 0x2C, 0x84, 0xDA, 0x19, 
        0x57, 0xEA, 0x79, 0x08, 0xD8, 0x7C, 0x64, 0xFA, 0x4F, 0x8A, 0x5F, 0x81, 0x88, 0x6F, 0xB0, 0xA9, 
        0x1C, 0xA2, 0xDF, 0x59, 0xEB, 0x13, 0x93, 0x6A, 0x8B, 0x17, 0xA7, 0xBA, 0xCA, 0x05, 0x21, 0x76, 
        0xD1, 0x7B, 0xB6, 0x89, 0x86, 0xB2, 0xDB, 0xA8, 0xC4, 0x80, 0x0F, 0x2A, 0xA6, 0x9A, 0x72, 0xA0, 
        0xE8, 0x9E, 0x09, 0x66, 0x0A, 0x49, 0xD9, 0xEF, 0x2D, 0xA1, 0xC5, 0x7D, 0xD4, 0xE3, 0x54, 0x50, 
        0x85, 0xD3, 0xC9, 0x20, 0xBE, 0x67, 0x47, 0xBD, 0x65, 0xF8, 0x06, 0x16, 0x3B, 0xBB, 0x10, 0xFE, 
        0x39, 0xF9, 0x0C, 0x43, 0xE4, 0xCE, 0xE7, 0x6C, 0x4B, 0x1B, 0x25, 0x3D, 0x3C, 0x69, 0x03, 0x6B
    },
    {
        0xE7, 0x2E, 0x51, 0x8C, 0x29, 0x32, 0x3A, 0xFD, 0xAE, 0x39, 0xEF, 0x6F, 0xF4, 0x08, 0xFE, 0xB0, 
        0x8A, 0x02, 0x20, 0xCF, 0xFC, 0x0F, 0x27, 0x62, 0xBD, 0xA2, 0xCA, 0xF6, 0x2A, 0x89, 0xB8, 0x14, 
        0x9D, 0x5E, 0x5D, 0x53, 0xED, 0xD9, 0xC0, 0xC9, 0xA6, 0x68, 0x35, 0x83, 0x12, 0x7F, 0x4F, 0x8F, 
        0xD0, 0xB6, 0xBA, 0xBE, 0xB3, 0xB4, 0x31, 0x69, 0x7A, 0x2D, 0x49, 0x97, 0xA3, 0xB2, 0x74, 0x1A, 
        0xEC, 0xE3, 0xCD, 0xF8, 0x19, 0xDB, 0xA5, 0x81, 0x70, 0xD1, 0xE9, 0x95, 0x24, 0x76, 0x67, 0x41, 
        0x91, 0x4B, 0xD8, 0xE0, 0x10, 0xBF, 0xDE, 0x44, 0xD3, 0x6B, 0xA9, 0x9A, 0x1B, 0x58, 0xEE, 0x63, 
        0xAA, 0xAB, 0x1F, 0x1D, 0x2F, 0xB9, 0x04, 0xA0, 0x6C, 0x56, 0x93, 0x84, 0x3B, 0x73, 0x80, 0x54, 
        0xDA, 0x2B, 0x85, 0x3E, 0xBC, 0xCB, 0x7B, 0x8B, 0xE2, 0x7C, 0x34, 0xF1, 0x66, 0x15, 0xC8, 0xE1, 
        0x28, 0x05, 0xCC, 0x01, 0x4C, 0x55, 0x8D, 0xC4, 0x1C, 0x23, 0x65, 0x92, 0x45, 0x07, 0x52, 0x59, 
        0x4D, 0xA8, 0xF2, 0x77, 0x5B, 0x8E, 0xF7, 0x9C, 0xC6, 0x4A, 0xEA, 0x6E, 0x3C, 0xAD, 0xA7, 0xD5, 
        0xDC, 0xE5, 0x30, 0x46, 0xB1, 0x9B, 0x18, 0xE6, 0x5F, 0x00, 0x5C, 0x06, 0x16, 0x1E, 0xD4, 0xC7, 
        0x7E, 0xC1, 0x0C, 0x71, 0x75, 0x43, 0x13, 0xB5, 0x90, 0x78, 0x6A, 0x42, 0xA4, 0x6D, 0x17, 0x0D, 
        0xA1, 0x26, 0xF9, 0x86, 0xBB, 0xC2, 0x37, 0x57, 0x09, 0x96, 0xFB, 0x11, 0xFA, 0x03, 0x36, 0xD7, 
        0xF3, 0x38, 0xD6, 0x0E, 0x50, 0x72, 0x21, 0x4E, 0xAC, 0x47, 0x99, 0x0B, 0x0A, 0xF5, 0x5A, 0x61, 
        0x3D, 0xB7, 0x22, 0x87, 0x79, 0x9E, 0xDF, 0xFF, 0x88, 0xF0, 0xEB, 0xE8, 0x82, 0xD2, 0xC5, 0xDD, 
        0x94, 0x60, 0x7D, 0xE4, 0x48, 0x9F, 0xCE, 0x98, 0x64, 0xC3, 0x2C, 0xAF, 0x3F, 0x33, 0x40, 0x25
    },
    {
        0x67, 0x9B, 0x1B, 0x62, 0x12, 0x34, 0x1E, 0x09, 0x15, 0xA9, 0x4D, 0xC3, 0x6B, 0xD2, 0xBE, 0x45, 
        0xA3, 0x07, 0x70, 0xC5, 0x41, 0x5B, 0xF9, 0x9F, 0x19, 0x01, 0xB3, 0x94, 0xA5, 0x14, 0x6F, 0x7D, 
        0x91, 0xB8, 0x0F, 0xE4, 0xB2, 0xBF, 0x66, 0x04, 0x3F, 0x4A, 0xBD, 0xC1, 0xBC, 0x78, 0x4B, 0xD5, 
        0xDD, 0x84, 0x90, 0xAE, 0xF2, 0x7B, 0x83, 0x02, 0x0E, 0x2C, 0x8A, 0x44, 0x49, 0xBA, 0xE5, 0x96, 
        0xFA, 0x59, 0x3A, 0x7F, 0x21, 0x40, 0x88, 0x3E, 0xDB, 0x95, 0x8C, 0xBB, 0x4E, 0x1A, 0xE9, 0xA0, 
        0x85, 0x75, 0xF7, 0xEE, 0x43, 0xE6, 0x36, 0xD6, 0x6A, 0xFD, 0x9C, 0x18, 0xDE, 0x79, 0x05, 0xD7, 
        0x2B, 0x63, 0xE0, 0x1F, 0xD3, 0x27, 0xC6, 0xFE, 0x74, 0x92, 0x7A, 0x48, 0x56, 0x6C, 0x76, 0x6D, 
        0x08, 0xED, 0x00, 0x20, 0x51, 0xFB, 0x46, 0xEB, 0x11, 0xCF, 0xF5, 0x1D, 0xA1, 0x35, 0x4C, 0xA6, 
        0x5A, 0x8E, 0x72, 0xB0, 0xFC, 0x25, 0x2A, 0x58, 0x57, 0xC7, 0x16, 0x32, 0x9E, 0x71, 0xAC, 0x31, 
        0xB4, 0xD4, 0xAA, 0x52, 0xCE, 0x9D, 0xDC, 0xD9, 0xA7, 0x3D, 0x3B, 0x8B, 0xDF, 0xA2, 0x77, 0xAB, 
        0xC9, 0x98, 0xCB, 0x29, 0x0D, 0x50, 0x69, 0x2F, 0xF0, 0xF8, 0x47, 0x39, 0x82, 0xA8, 0xE3, 0xEF, 
        0x30, 0x2E, 0xEC, 0x93, 0xAD, 0x5F, 0xF4, 0x33, 0xCD, 0xF1, 0xB5, 0x17, 0xC0, 0x3C, 0xCA, 0xA4, 
        0xB6, 0xB1, 0x37, 0xB7, 0xD8, 0x99, 0x42, 0xDA, 0x9A, 0x0C, 0xC8, 0x0B, 0x80, 0x4F, 0x0A, 0x54, 
        0xE2, 0xE1, 0x1C, 0x13, 0x53, 0x24, 0x38, 0x03, 0xEA, 0x61, 0xAF, 0x65, 0x2D, 0x23, 0x86, 0x28, 
        0x97, 0xCC, 0x8F, 0xFF, 0xB9, 0x26, 0x7E, 0xF6, 0x5C, 0x55, 0x73, 0xC4, 0x89, 0x22, 0x10, 0x81, 
        0xF3, 0x60, 0x87, 0xD0, 0xC2, 0x6E, 0x8D, 0xE7, 0x5E, 0xD1, 0x64, 0x5D, 0x68, 0x7C, 0xE8, 0x06
    },
    {
        0x4C, 0x91, 0x65, 0xCE, 0x59, 0x2A, 0xE7, 0x3D, 0xB7, 0xC8, 0x81, 0xA7, 0xF2, 0x0F, 0x12, 0x21, 
        0x04, 0xEF, 0x96, 0xD5, 0x3F, 0xC7, 0x5E, 0x8F, 0x09, 0x9D, 0x30, 0xDF, 0x76, 0x2B, 0xEC, 0xB4, 
        0x5D, 0x60, 0x4F, 0x48, 0xAC, 0x8E, 0xD0, 0x1F, 0x7A, 0x6F, 0xE2, 0xCB, 0x7E, 0x36, 0xF3, 0xE1, 
        0x41, 0xEB, 0xC1, 0x26, 0x0E, 0xC6, 0x05, 0x6D, 0xD3, 0xBE, 0x39, 0xBD, 0x9F, 0x0C, 0xD4, 0xB3, 
        0xAE, 0xAB, 0xF8, 0xD8, 0x9C, 0xA3, 0x55, 0xE6, 0x33, 0x43, 0x4B, 0x90, 0x71, 0xF9, 0x6A, 0xF4, 
        0x77, 0x14, 0x8C, 0x84, 0x53, 0x24, 0x46, 0x11, 0x6E, 0x40, 0x7F, 0x95, 0xB1, 0xAA, 0x83, 0x8D, 
        0x50, 0x52, 0x56, 0x7B, 0x93, 0xEE, 0x25, 0xB0, 0x88, 0xAD, 0x5A, 0x03, 0xE5, 0x1C, 0xE4, 0x80, 
        0xA1, 0x74, 0x01, 0x00, 0x0B, 0x32, 0xD1, 0x06, 0xA9, 0x19, 0xE0, 0x17, 0x68, 0xB6, 0x1D, 0x86, 
        0x5B, 0x27, 0xFA, 0xC0, 0xDC, 0x82, 0xCC, 0x37, 0x79, 0xB9, 0x47, 0x58, 0x13, 0x0A, 0x4A, 0xA8, 
        0xDE, 0x7D, 0x38, 0xFB, 0x85, 0xE3, 0xDD, 0x5F, 0x1A, 0x16, 0x64, 0xA5, 0x2D, 0x98, 0x78, 0xA4, 
        0x6B, 0x61, 0x07, 0x3C, 0x23, 0x97, 0x9E, 0x4E, 0x62, 0xC2, 0x4D, 0x08, 0x99, 0x54, 0xA6, 0x18, 
        0x34, 0xD2, 0xE8, 0x31, 0xD6, 0xD9, 0x7C, 0xC4, 0x75, 0xFE, 0x42, 0xDB, 0x57, 0x8A, 0x9B, 0xEA, 
        0xB2, 0x5C, 0xDA, 0x2E, 0xC3, 0xFD, 0xCF, 0xAF, 0x0D, 0xBF, 0xF7, 0x51, 0xF5, 0xED, 0xCD, 0x89, 
        0x3A, 0xCA, 0x8B, 0xC5, 0x67, 0x1E, 0x94, 0xF1, 0x9A, 0x3E, 0xBA, 0x20, 0x22, 0xF0, 0x87, 0xA0, 
        0x2F, 0xE9, 0xBB, 0x2C, 0xFC, 0x72, 0x44, 0x10, 0x29, 0x15, 0x66, 0x49, 0xC9, 0x6C, 0x35, 0x69, 
        0x92, 0xA2, 0x1B, 0x63, 0x3B, 0x70, 0xD7, 0xB8, 0x45, 0xFF, 0xBC, 0xB5, 0x02, 0x28, 0xF6, 0x73
    },
    {
        0x50, 0xE7, 0xF3, 0xC0, 0x6B, 0x47, 0x63, 0xED, 0xA5, 0xD3, 0x74, 0x36, 0x58, 0xBE, 0x5D, 0x24, 
        0xDD, 0xBB, 0xDE, 0x30, 0x7C, 0x32, 0x52, 0xBF, 0xAD, 0xBD, 0x9D, 0x79, 0xDB, 0x6D, 0x00, 0x1E, 
        0xE9, 0x5B, 0xEB, 0xD2, 0x55, 0x95, 0x98, 0x2D, 0x81, 0xBA, 0xCB, 0x68, 0x03, 0x8E, 0x72, 0x70, 
        0x20, 0x39, 0x21, 0x1D, 0x94, 0x18, 0xF7, 0x2B, 0x23, 0x57, 0x6F, 0xEC, 0x2C, 0x05, 0x1A, 0x27, 
        0xC4, 0x6C, 0x11, 0x40, 0x97, 0xB4, 0x31, 0x49, 0x26, 0xB1, 0x69, 0xCD, 0xE2, 0x3B, 0x12, 0x4B, 
        0xF1, 0x4E, 0x04, 0xDC, 0x22, 0x8C, 0x19, 0xE6, 0x90, 0x0A, 0x29, 0x65, 0xB6, 0x46, 0xE5, 0x2E, 
        0x99, 0x08, 0x8A, 0xAB, 0x76, 0x91, 0xA6, 0x9C, 0x86, 0x7F, 0xD0, 0xE4, 0xF2, 0x96, 0xD8, 0x5E, 
        0x25, 0x4A, 0x75, 0x5F, 0x3C, 0x0C, 0xB2, 0x4C, 0xFD, 0x3E, 0x5A, 0xF5, 0x83, 0x8F, 0xBC, 0x4D, 
        0xFA, 0x37, 0x80, 0x0B, 0xC2, 0xCF, 0x51, 0xA4, 0x3A, 0x6E, 0x33, 0x41, 0x77, 0x16, 0x43, 0xD7, 
        0x53, 0xB8, 0x45, 0xAA, 0xF6, 0xE1, 0xE8, 0x78, 0x85, 0xDF, 0xD9, 0xA7, 0x7E, 0x15, 0x10, 0x8D, 
        0x38, 0x71, 0x66, 0xC7, 0xB5, 0xF4, 0x06, 0xC1, 0xCA, 0x9A, 0x7A, 0x87, 0x3F, 0x1B, 0x1C, 0x14, 
        0x1F, 0x09, 0x82, 0xB7, 0x8B, 0x6A, 0x92, 0x89, 0x60, 0x02, 0x9B, 0xFB, 0xA0, 0x17, 0xAE, 0x13, 
        0x0D, 0xC3, 0xD1, 0xC5, 0xB0, 0xB9, 0xEA, 0xEE, 0x2F, 0x7D, 0xF0, 0xB3, 0x61, 0x2A, 0x7B, 0xAC, 
        0xD4, 0x42, 0x3D, 0xA3, 0x62, 0x07, 0x4F, 0xE3, 0x84, 0x56, 0xD5, 0x0E, 0x9F, 0xC9, 0x67, 0x0F, 
        0xEF, 0xA8, 0xFF, 0x54, 0x93, 0x59, 0x88, 0xCC, 0xFC, 0x64, 0x48, 0xF8, 0xF9, 0x01, 0x35, 0xA9, 
        0x5C, 0x9E, 0xAF, 0xE0, 0xFE, 0xC8, 0xA1, 0x44, 0xA2, 0x28, 0xC6, 0x34, 0xCE, 0xD6, 0xDA, 0x73
    },
    {
        0xAC, 0x7B, 0x92, 0x13, 0x74, 0xE2, 0x2D, 0x34, 0x67, 0x39, 0x63, 0x7F, 0xF5, 0x14, 0x20, 0xE4, 
        0x12, 0xC1, 0xB5, 0x0D, 0x3A, 0x1B, 0xBA, 0xA5, 0x3E, 0xB3, 0x18, 0xEF, 0x60, 0x06, 0x2B, 0x8D, 
        0x50, 0x52, 0x46, 0x88, 0x79, 0x41, 0xCD, 0x0C, 0xA8, 0x70, 0xED, 0xD3, 0x8C, 0x32, 0x11, 0x07, 
        0x80, 0xE5, 0x31, 0x2A, 0xF0, 0xFF, 0xF6, 0x7E, 0x27, 0x6F, 0x10, 0x85, 0xBD, 0xFE, 0xE9, 0x43, 
        0x77, 0xB7, 0x17, 0x21, 0x57, 0x5B, 0xBC, 0xC9, 0xF2, 0x8E, 0x62, 0x9F, 0xAE, 0xF3, 0xB0, 0xDF, 
        0x84, 0x0A, 0x4F, 0xA3, 0x96, 0x24, 0x4E, 0xCA, 0x94, 0x64, 0x68, 0x5F, 0x4D, 0x53, 0x6D, 0xAB, 
        0x7C, 0x72, 0x56, 0x4C, 0x75, 0x25, 0xC0, 0xA9, 0x6B, 0x9D, 0x9E, 0xDC, 0x23, 0xE6, 0xC7, 0x87, 
        0x55, 0x6E, 0xD2, 0x36, 0x30, 0x16, 0x29, 0x1C, 0xB9, 0x26, 0xE3, 0xE0, 0xBE, 0x83, 0x02, 0xAD, 
        0x7A, 0xCE, 0x19, 0xD5, 0x05, 0x89, 0x1D, 0xD6, 0x42, 0xA1, 0xAA, 0x90, 0xC4, 0xD4, 0x86, 0x5D, 
        0x0B, 0x66, 0xF4, 0xFD, 0x47, 0x09, 0xE1, 0x5E, 0xCC, 0x04, 0x76, 0x71, 0x2C, 0x73, 0xA6, 0x95, 
        0x54, 0xB6, 0xF8, 0xD0, 0xEA, 0x51, 0x59, 0xA2, 0x5C, 0xDB, 0x48, 0xDA, 0x97, 0x58, 0x9B, 0xC2, 
        0x3C, 0xC3, 0x0F, 0xFC, 0xE7, 0xC5, 0x82, 0xF1, 0x8A, 0x3D, 0x6A, 0xCB, 0xB2, 0x65, 0x99, 0x01, 
        0xA7, 0xB4, 0x2F, 0xC6, 0x3F, 0xD7, 0xF7, 0x93, 0x1A, 0x8B, 0x35, 0x98, 0x3B, 0xCF, 0xF9, 0x8F, 
        0xFA, 0x37, 0x81, 0x15, 0x9C, 0xE8, 0xBB, 0x1F, 0x7D, 0xDE, 0x4B, 0x00, 0x0E, 0xFB, 0x49, 0xB1, 
        0x22, 0xEB, 0xAF, 0xC8, 0x33, 0x44, 0x40, 0x2E, 0x08, 0xEE, 0x78, 0x6C, 0xDD, 0x9A, 0xD8, 0x5A, 
        0x91, 0xBF, 0x28, 0xB8, 0x1E, 0x4A, 0x03, 0x45, 0xA4, 0xD9, 0x61, 0x69, 0x38, 0xEC, 0xD1, 0xA0
    },
    {
        0x08, 0xE5, 0xDF, 0x28, 0x3F, 0x15, 0xFF, 0x36, 0x7A, 0xBC, 0xE2, 0x7D, 0xC8, 0x2E, 0x75, 0xDD, 
        0xE6, 0x93, 0xC1, 0xE7, 0x22, 0xF4, 0x1B, 0x1A, 0xBA, 0x09, 0x6A, 0x9F, 0x7C, 0xA5, 0x37, 0xDE, 
        0xBF, 0xEF, 0xAC, 0x88, 0xB5, 0xAA, 0xD7, 0x29, 0x90, 0xA7, 0xCF, 0x18, 0x10, 0xFE, 0x78, 0x6B, 
        0x54, 0x13, 0x60, 0xF9, 0x9E, 0x44, 0x56, 0xB3, 0x73, 0xA6, 0xB6, 0x02, 0x1D, 0x8A, 0x57, 0xFA, 
        0xA1, 0x91, 0xB0, 0xBB, 0xB9, 0xFD, 0xD3, 0x4F, 0xCE, 0x40, 0x2C, 0x55, 0x58, 0x00, 0x97, 0x5C, 
        0xCC, 0xE1, 0xBE, 0xD2, 0x47, 0xED, 0x70, 0xD1, 0x17, 0xE4, 0xA0, 0x65, 0xEE, 0x21, 0xF6, 0x0E, 
        0xE3, 0xF7, 0x77, 0x20, 0xF1, 0x23, 0x5D, 0x5E, 0x3E, 0x05, 0x9B, 0xC2, 0xEB, 0x8D, 0x5B, 0x52, 
        0xE9, 0x68, 0xD6, 0x66, 0xAE, 0x7E, 0x67, 0xF2, 0x85, 0xBD, 0xDB, 0x45, 0x83, 0xCA, 0x3D, 0xC6, 
        0x2B, 0x49, 0xA4, 0xD0, 0x3B, 0x46, 0x3C, 0x4E, 0x34, 0x82, 0xC0, 0x8F, 0xC5, 0x1E, 0x9C, 0x35, 
        0x2F, 0xB4, 0x06, 0x14, 0x62, 0x7F, 0x8B, 0xAB, 0x19, 0xF5, 0x6F, 0x69, 0x31, 0x39, 0x84, 0xD9, 
        0x27, 0x5F, 0x42, 0x86, 0xC9, 0x71, 0xAD, 0x1C, 0xFB, 0xC4, 0xB8, 0x0A, 0x89, 0x63, 0xCD, 0x0D, 
        0xEA, 0xC3, 0xB7, 0xDA, 0x43, 0x0B, 0x04, 0x50, 0xD8, 0x24, 0xF0, 0x1F, 0xC7, 0x2A, 0x9D, 0xA3, 
        0x4A, 0x0F, 0xAF, 0x95, 0x74, 0x80, 0x98, 0x11, 0x3A, 0x16, 0xF8, 0x53, 0xEC, 0x87, 0x8C, 0x8E, 
        0x12, 0xA8, 0x9A, 0xE0, 0xCB, 0x99, 0xD5, 0x6C, 0x2D, 0x92, 0x26, 0x6D, 0x79, 0xDC, 0x76, 0x59, 
        0x25, 0x07, 0x96, 0x81, 0x30, 0xFC, 0x64, 0x61, 0xB1, 0x51, 0x7B, 0x38, 0x0C, 0x03, 0x5A, 0x33, 
        0x41, 0x4D, 0xA9, 0x4B, 0xA2, 0xE8, 0xF3, 0x32, 0xD4, 0x94, 0xB2, 0x6E, 0x72, 0x01, 0x48, 0x4C
    }
};

const TwistDomainSBoxSet TwistExpander_EdChan_0006::kPhaseCSBoxes = {
    {
        0xF9, 0x64, 0xC7, 0x59, 0xB5, 0x70, 0x67, 0x7E, 0xAE, 0xFF, 0xEE, 0x24, 0x2B, 0xDA, 0xE6, 0x60, 
        0xCA, 0x17, 0xE0, 0xC3, 0x3C, 0x0B, 0x31, 0x38, 0x7C, 0xF0, 0xC8, 0xF1, 0x2D, 0x52, 0x77, 0xCE, 
        0x51, 0x01, 0x99, 0x1D, 0x34, 0x1A, 0x05, 0x50, 0xB9, 0xF5, 0xA1, 0x9F, 0x5D, 0x6E, 0x09, 0xC1, 
        0x4F, 0xF3, 0xAD, 0xE4, 0xF8, 0x29, 0xE8, 0xB7, 0x65, 0xFC, 0x9A, 0x9C, 0xB2, 0xBA, 0xE1, 0x4A, 
        0x76, 0xB0, 0x19, 0x75, 0xD2, 0xC0, 0x21, 0x45, 0xA8, 0x0D, 0x7D, 0x46, 0xA9, 0x3B, 0x33, 0x8D, 
        0x0F, 0x40, 0x58, 0x28, 0x87, 0xA6, 0xCB, 0x86, 0xD7, 0x6D, 0x7F, 0x80, 0x08, 0x92, 0xAC, 0x7A, 
        0xE7, 0xA5, 0x41, 0x9B, 0x26, 0x35, 0x84, 0x2A, 0xBC, 0x16, 0xD5, 0x4E, 0x25, 0x30, 0x07, 0xCC, 
        0x82, 0x6F, 0x0C, 0x2E, 0x3E, 0x8A, 0x27, 0x88, 0xF2, 0xF6, 0xE3, 0x20, 0x71, 0x8C, 0x12, 0x6A, 
        0xF7, 0xC6, 0x5B, 0x8F, 0x91, 0x8E, 0x1B, 0x4C, 0xD9, 0x78, 0xE9, 0x97, 0xC4, 0x1C, 0x5F, 0xD0, 
        0xD3, 0x3D, 0xB8, 0x79, 0x0A, 0x83, 0xB3, 0x13, 0x96, 0x02, 0xE5, 0x66, 0xF4, 0x36, 0xFB, 0x44, 
        0x11, 0x23, 0xAA, 0x5C, 0x22, 0xC2, 0x90, 0xBB, 0x43, 0xCD, 0xDB, 0x5E, 0x14, 0x03, 0x06, 0xD4, 
        0x2C, 0x47, 0x93, 0xEA, 0xA3, 0x57, 0x1F, 0x6B, 0x4D, 0xBF, 0x2F, 0x15, 0x63, 0xFE, 0x56, 0xD1, 
        0x68, 0x73, 0x37, 0x94, 0xEF, 0xDF, 0x7B, 0x54, 0x98, 0xDE, 0xED, 0xC5, 0xAF, 0x55, 0x39, 0x9E, 
        0xFA, 0xBD, 0xDC, 0x49, 0x85, 0x72, 0xA2, 0x4B, 0x74, 0x1E, 0x18, 0x42, 0x00, 0x69, 0x48, 0xA0, 
        0xB6, 0xB1, 0x3A, 0xD6, 0xFD, 0xC9, 0x89, 0xA4, 0x10, 0x62, 0xA7, 0x3F, 0xDD, 0x95, 0x0E, 0x53, 
        0x04, 0xE2, 0xB4, 0x61, 0xD8, 0x8B, 0x81, 0x5A, 0xAB, 0x9D, 0xBE, 0xEC, 0x6C, 0x32, 0xCF, 0xEB
    },
    {
        0x53, 0x9C, 0xA3, 0xD7, 0x3E, 0xC0, 0x27, 0x04, 0x94, 0x37, 0xB4, 0xBC, 0x4A, 0x6D, 0x14, 0x71, 
        0xDC, 0x33, 0x70, 0x4E, 0xAD, 0xCF, 0xD2, 0x40, 0x8D, 0xC1, 0x55, 0xF3, 0x2E, 0xCC, 0x96, 0x31, 
        0x77, 0xE6, 0xF6, 0x1A, 0x0D, 0x4C, 0x0B, 0x45, 0x73, 0x1E, 0x62, 0x92, 0x3A, 0xB5, 0x46, 0xC7, 
        0x02, 0x7A, 0x2F, 0x9D, 0x61, 0xC3, 0xD0, 0xB7, 0xAE, 0x8C, 0x4D, 0x29, 0x68, 0xC8, 0x42, 0xDD, 
        0xA4, 0xE1, 0xF7, 0x1F, 0xCD, 0xF5, 0x63, 0x2B, 0xF0, 0xAB, 0xBF, 0x90, 0xC2, 0xFB, 0x5B, 0xAA, 
        0x22, 0xF4, 0xE5, 0xF1, 0x83, 0x34, 0xEE, 0xB1, 0x12, 0x0E, 0x36, 0xD5, 0x74, 0xED, 0x1D, 0xE9, 
        0x26, 0x8F, 0xC6, 0x7F, 0x35, 0x3F, 0x38, 0x78, 0xAC, 0x01, 0x9B, 0x30, 0x8E, 0xE0, 0x82, 0xB8, 
        0x5C, 0x87, 0x99, 0x95, 0x24, 0xFC, 0x07, 0x75, 0x48, 0xA5, 0xCB, 0x51, 0xF2, 0x98, 0xEC, 0x58, 
        0x97, 0x91, 0x5E, 0x23, 0x56, 0x11, 0x7E, 0xB9, 0xD6, 0x60, 0xE2, 0x32, 0x18, 0x28, 0xB3, 0x44, 
        0xFF, 0x9F, 0x41, 0x52, 0xFD, 0x6E, 0x5A, 0xDE, 0x00, 0x5D, 0xAF, 0x15, 0x2C, 0x84, 0xDA, 0x19, 
        0x57, 0xEA, 0x79, 0x08, 0xD8, 0x7C, 0x64, 0xFA, 0x4F, 0x8A, 0x5F, 0x81, 0x88, 0x6F, 0xB0, 0xA9, 
        0x1C, 0xA2, 0xDF, 0x59, 0xEB, 0x13, 0x93, 0x6A, 0x8B, 0x17, 0xA7, 0xBA, 0xCA, 0x05, 0x21, 0x76, 
        0xD1, 0x7B, 0xB6, 0x89, 0x86, 0xB2, 0xDB, 0xA8, 0xC4, 0x80, 0x0F, 0x2A, 0xA6, 0x9A, 0x72, 0xA0, 
        0xE8, 0x9E, 0x09, 0x66, 0x0A, 0x49, 0xD9, 0xEF, 0x2D, 0xA1, 0xC5, 0x7D, 0xD4, 0xE3, 0x54, 0x50, 
        0x85, 0xD3, 0xC9, 0x20, 0xBE, 0x67, 0x47, 0xBD, 0x65, 0xF8, 0x06, 0x16, 0x3B, 0xBB, 0x10, 0xFE, 
        0x39, 0xF9, 0x0C, 0x43, 0xE4, 0xCE, 0xE7, 0x6C, 0x4B, 0x1B, 0x25, 0x3D, 0x3C, 0x69, 0x03, 0x6B
    },
    {
        0xE7, 0x2E, 0x51, 0x8C, 0x29, 0x32, 0x3A, 0xFD, 0xAE, 0x39, 0xEF, 0x6F, 0xF4, 0x08, 0xFE, 0xB0, 
        0x8A, 0x02, 0x20, 0xCF, 0xFC, 0x0F, 0x27, 0x62, 0xBD, 0xA2, 0xCA, 0xF6, 0x2A, 0x89, 0xB8, 0x14, 
        0x9D, 0x5E, 0x5D, 0x53, 0xED, 0xD9, 0xC0, 0xC9, 0xA6, 0x68, 0x35, 0x83, 0x12, 0x7F, 0x4F, 0x8F, 
        0xD0, 0xB6, 0xBA, 0xBE, 0xB3, 0xB4, 0x31, 0x69, 0x7A, 0x2D, 0x49, 0x97, 0xA3, 0xB2, 0x74, 0x1A, 
        0xEC, 0xE3, 0xCD, 0xF8, 0x19, 0xDB, 0xA5, 0x81, 0x70, 0xD1, 0xE9, 0x95, 0x24, 0x76, 0x67, 0x41, 
        0x91, 0x4B, 0xD8, 0xE0, 0x10, 0xBF, 0xDE, 0x44, 0xD3, 0x6B, 0xA9, 0x9A, 0x1B, 0x58, 0xEE, 0x63, 
        0xAA, 0xAB, 0x1F, 0x1D, 0x2F, 0xB9, 0x04, 0xA0, 0x6C, 0x56, 0x93, 0x84, 0x3B, 0x73, 0x80, 0x54, 
        0xDA, 0x2B, 0x85, 0x3E, 0xBC, 0xCB, 0x7B, 0x8B, 0xE2, 0x7C, 0x34, 0xF1, 0x66, 0x15, 0xC8, 0xE1, 
        0x28, 0x05, 0xCC, 0x01, 0x4C, 0x55, 0x8D, 0xC4, 0x1C, 0x23, 0x65, 0x92, 0x45, 0x07, 0x52, 0x59, 
        0x4D, 0xA8, 0xF2, 0x77, 0x5B, 0x8E, 0xF7, 0x9C, 0xC6, 0x4A, 0xEA, 0x6E, 0x3C, 0xAD, 0xA7, 0xD5, 
        0xDC, 0xE5, 0x30, 0x46, 0xB1, 0x9B, 0x18, 0xE6, 0x5F, 0x00, 0x5C, 0x06, 0x16, 0x1E, 0xD4, 0xC7, 
        0x7E, 0xC1, 0x0C, 0x71, 0x75, 0x43, 0x13, 0xB5, 0x90, 0x78, 0x6A, 0x42, 0xA4, 0x6D, 0x17, 0x0D, 
        0xA1, 0x26, 0xF9, 0x86, 0xBB, 0xC2, 0x37, 0x57, 0x09, 0x96, 0xFB, 0x11, 0xFA, 0x03, 0x36, 0xD7, 
        0xF3, 0x38, 0xD6, 0x0E, 0x50, 0x72, 0x21, 0x4E, 0xAC, 0x47, 0x99, 0x0B, 0x0A, 0xF5, 0x5A, 0x61, 
        0x3D, 0xB7, 0x22, 0x87, 0x79, 0x9E, 0xDF, 0xFF, 0x88, 0xF0, 0xEB, 0xE8, 0x82, 0xD2, 0xC5, 0xDD, 
        0x94, 0x60, 0x7D, 0xE4, 0x48, 0x9F, 0xCE, 0x98, 0x64, 0xC3, 0x2C, 0xAF, 0x3F, 0x33, 0x40, 0x25
    },
    {
        0x67, 0x9B, 0x1B, 0x62, 0x12, 0x34, 0x1E, 0x09, 0x15, 0xA9, 0x4D, 0xC3, 0x6B, 0xD2, 0xBE, 0x45, 
        0xA3, 0x07, 0x70, 0xC5, 0x41, 0x5B, 0xF9, 0x9F, 0x19, 0x01, 0xB3, 0x94, 0xA5, 0x14, 0x6F, 0x7D, 
        0x91, 0xB8, 0x0F, 0xE4, 0xB2, 0xBF, 0x66, 0x04, 0x3F, 0x4A, 0xBD, 0xC1, 0xBC, 0x78, 0x4B, 0xD5, 
        0xDD, 0x84, 0x90, 0xAE, 0xF2, 0x7B, 0x83, 0x02, 0x0E, 0x2C, 0x8A, 0x44, 0x49, 0xBA, 0xE5, 0x96, 
        0xFA, 0x59, 0x3A, 0x7F, 0x21, 0x40, 0x88, 0x3E, 0xDB, 0x95, 0x8C, 0xBB, 0x4E, 0x1A, 0xE9, 0xA0, 
        0x85, 0x75, 0xF7, 0xEE, 0x43, 0xE6, 0x36, 0xD6, 0x6A, 0xFD, 0x9C, 0x18, 0xDE, 0x79, 0x05, 0xD7, 
        0x2B, 0x63, 0xE0, 0x1F, 0xD3, 0x27, 0xC6, 0xFE, 0x74, 0x92, 0x7A, 0x48, 0x56, 0x6C, 0x76, 0x6D, 
        0x08, 0xED, 0x00, 0x20, 0x51, 0xFB, 0x46, 0xEB, 0x11, 0xCF, 0xF5, 0x1D, 0xA1, 0x35, 0x4C, 0xA6, 
        0x5A, 0x8E, 0x72, 0xB0, 0xFC, 0x25, 0x2A, 0x58, 0x57, 0xC7, 0x16, 0x32, 0x9E, 0x71, 0xAC, 0x31, 
        0xB4, 0xD4, 0xAA, 0x52, 0xCE, 0x9D, 0xDC, 0xD9, 0xA7, 0x3D, 0x3B, 0x8B, 0xDF, 0xA2, 0x77, 0xAB, 
        0xC9, 0x98, 0xCB, 0x29, 0x0D, 0x50, 0x69, 0x2F, 0xF0, 0xF8, 0x47, 0x39, 0x82, 0xA8, 0xE3, 0xEF, 
        0x30, 0x2E, 0xEC, 0x93, 0xAD, 0x5F, 0xF4, 0x33, 0xCD, 0xF1, 0xB5, 0x17, 0xC0, 0x3C, 0xCA, 0xA4, 
        0xB6, 0xB1, 0x37, 0xB7, 0xD8, 0x99, 0x42, 0xDA, 0x9A, 0x0C, 0xC8, 0x0B, 0x80, 0x4F, 0x0A, 0x54, 
        0xE2, 0xE1, 0x1C, 0x13, 0x53, 0x24, 0x38, 0x03, 0xEA, 0x61, 0xAF, 0x65, 0x2D, 0x23, 0x86, 0x28, 
        0x97, 0xCC, 0x8F, 0xFF, 0xB9, 0x26, 0x7E, 0xF6, 0x5C, 0x55, 0x73, 0xC4, 0x89, 0x22, 0x10, 0x81, 
        0xF3, 0x60, 0x87, 0xD0, 0xC2, 0x6E, 0x8D, 0xE7, 0x5E, 0xD1, 0x64, 0x5D, 0x68, 0x7C, 0xE8, 0x06
    },
    {
        0x4C, 0x91, 0x65, 0xCE, 0x59, 0x2A, 0xE7, 0x3D, 0xB7, 0xC8, 0x81, 0xA7, 0xF2, 0x0F, 0x12, 0x21, 
        0x04, 0xEF, 0x96, 0xD5, 0x3F, 0xC7, 0x5E, 0x8F, 0x09, 0x9D, 0x30, 0xDF, 0x76, 0x2B, 0xEC, 0xB4, 
        0x5D, 0x60, 0x4F, 0x48, 0xAC, 0x8E, 0xD0, 0x1F, 0x7A, 0x6F, 0xE2, 0xCB, 0x7E, 0x36, 0xF3, 0xE1, 
        0x41, 0xEB, 0xC1, 0x26, 0x0E, 0xC6, 0x05, 0x6D, 0xD3, 0xBE, 0x39, 0xBD, 0x9F, 0x0C, 0xD4, 0xB3, 
        0xAE, 0xAB, 0xF8, 0xD8, 0x9C, 0xA3, 0x55, 0xE6, 0x33, 0x43, 0x4B, 0x90, 0x71, 0xF9, 0x6A, 0xF4, 
        0x77, 0x14, 0x8C, 0x84, 0x53, 0x24, 0x46, 0x11, 0x6E, 0x40, 0x7F, 0x95, 0xB1, 0xAA, 0x83, 0x8D, 
        0x50, 0x52, 0x56, 0x7B, 0x93, 0xEE, 0x25, 0xB0, 0x88, 0xAD, 0x5A, 0x03, 0xE5, 0x1C, 0xE4, 0x80, 
        0xA1, 0x74, 0x01, 0x00, 0x0B, 0x32, 0xD1, 0x06, 0xA9, 0x19, 0xE0, 0x17, 0x68, 0xB6, 0x1D, 0x86, 
        0x5B, 0x27, 0xFA, 0xC0, 0xDC, 0x82, 0xCC, 0x37, 0x79, 0xB9, 0x47, 0x58, 0x13, 0x0A, 0x4A, 0xA8, 
        0xDE, 0x7D, 0x38, 0xFB, 0x85, 0xE3, 0xDD, 0x5F, 0x1A, 0x16, 0x64, 0xA5, 0x2D, 0x98, 0x78, 0xA4, 
        0x6B, 0x61, 0x07, 0x3C, 0x23, 0x97, 0x9E, 0x4E, 0x62, 0xC2, 0x4D, 0x08, 0x99, 0x54, 0xA6, 0x18, 
        0x34, 0xD2, 0xE8, 0x31, 0xD6, 0xD9, 0x7C, 0xC4, 0x75, 0xFE, 0x42, 0xDB, 0x57, 0x8A, 0x9B, 0xEA, 
        0xB2, 0x5C, 0xDA, 0x2E, 0xC3, 0xFD, 0xCF, 0xAF, 0x0D, 0xBF, 0xF7, 0x51, 0xF5, 0xED, 0xCD, 0x89, 
        0x3A, 0xCA, 0x8B, 0xC5, 0x67, 0x1E, 0x94, 0xF1, 0x9A, 0x3E, 0xBA, 0x20, 0x22, 0xF0, 0x87, 0xA0, 
        0x2F, 0xE9, 0xBB, 0x2C, 0xFC, 0x72, 0x44, 0x10, 0x29, 0x15, 0x66, 0x49, 0xC9, 0x6C, 0x35, 0x69, 
        0x92, 0xA2, 0x1B, 0x63, 0x3B, 0x70, 0xD7, 0xB8, 0x45, 0xFF, 0xBC, 0xB5, 0x02, 0x28, 0xF6, 0x73
    },
    {
        0x50, 0xE7, 0xF3, 0xC0, 0x6B, 0x47, 0x63, 0xED, 0xA5, 0xD3, 0x74, 0x36, 0x58, 0xBE, 0x5D, 0x24, 
        0xDD, 0xBB, 0xDE, 0x30, 0x7C, 0x32, 0x52, 0xBF, 0xAD, 0xBD, 0x9D, 0x79, 0xDB, 0x6D, 0x00, 0x1E, 
        0xE9, 0x5B, 0xEB, 0xD2, 0x55, 0x95, 0x98, 0x2D, 0x81, 0xBA, 0xCB, 0x68, 0x03, 0x8E, 0x72, 0x70, 
        0x20, 0x39, 0x21, 0x1D, 0x94, 0x18, 0xF7, 0x2B, 0x23, 0x57, 0x6F, 0xEC, 0x2C, 0x05, 0x1A, 0x27, 
        0xC4, 0x6C, 0x11, 0x40, 0x97, 0xB4, 0x31, 0x49, 0x26, 0xB1, 0x69, 0xCD, 0xE2, 0x3B, 0x12, 0x4B, 
        0xF1, 0x4E, 0x04, 0xDC, 0x22, 0x8C, 0x19, 0xE6, 0x90, 0x0A, 0x29, 0x65, 0xB6, 0x46, 0xE5, 0x2E, 
        0x99, 0x08, 0x8A, 0xAB, 0x76, 0x91, 0xA6, 0x9C, 0x86, 0x7F, 0xD0, 0xE4, 0xF2, 0x96, 0xD8, 0x5E, 
        0x25, 0x4A, 0x75, 0x5F, 0x3C, 0x0C, 0xB2, 0x4C, 0xFD, 0x3E, 0x5A, 0xF5, 0x83, 0x8F, 0xBC, 0x4D, 
        0xFA, 0x37, 0x80, 0x0B, 0xC2, 0xCF, 0x51, 0xA4, 0x3A, 0x6E, 0x33, 0x41, 0x77, 0x16, 0x43, 0xD7, 
        0x53, 0xB8, 0x45, 0xAA, 0xF6, 0xE1, 0xE8, 0x78, 0x85, 0xDF, 0xD9, 0xA7, 0x7E, 0x15, 0x10, 0x8D, 
        0x38, 0x71, 0x66, 0xC7, 0xB5, 0xF4, 0x06, 0xC1, 0xCA, 0x9A, 0x7A, 0x87, 0x3F, 0x1B, 0x1C, 0x14, 
        0x1F, 0x09, 0x82, 0xB7, 0x8B, 0x6A, 0x92, 0x89, 0x60, 0x02, 0x9B, 0xFB, 0xA0, 0x17, 0xAE, 0x13, 
        0x0D, 0xC3, 0xD1, 0xC5, 0xB0, 0xB9, 0xEA, 0xEE, 0x2F, 0x7D, 0xF0, 0xB3, 0x61, 0x2A, 0x7B, 0xAC, 
        0xD4, 0x42, 0x3D, 0xA3, 0x62, 0x07, 0x4F, 0xE3, 0x84, 0x56, 0xD5, 0x0E, 0x9F, 0xC9, 0x67, 0x0F, 
        0xEF, 0xA8, 0xFF, 0x54, 0x93, 0x59, 0x88, 0xCC, 0xFC, 0x64, 0x48, 0xF8, 0xF9, 0x01, 0x35, 0xA9, 
        0x5C, 0x9E, 0xAF, 0xE0, 0xFE, 0xC8, 0xA1, 0x44, 0xA2, 0x28, 0xC6, 0x34, 0xCE, 0xD6, 0xDA, 0x73
    },
    {
        0xAC, 0x7B, 0x92, 0x13, 0x74, 0xE2, 0x2D, 0x34, 0x67, 0x39, 0x63, 0x7F, 0xF5, 0x14, 0x20, 0xE4, 
        0x12, 0xC1, 0xB5, 0x0D, 0x3A, 0x1B, 0xBA, 0xA5, 0x3E, 0xB3, 0x18, 0xEF, 0x60, 0x06, 0x2B, 0x8D, 
        0x50, 0x52, 0x46, 0x88, 0x79, 0x41, 0xCD, 0x0C, 0xA8, 0x70, 0xED, 0xD3, 0x8C, 0x32, 0x11, 0x07, 
        0x80, 0xE5, 0x31, 0x2A, 0xF0, 0xFF, 0xF6, 0x7E, 0x27, 0x6F, 0x10, 0x85, 0xBD, 0xFE, 0xE9, 0x43, 
        0x77, 0xB7, 0x17, 0x21, 0x57, 0x5B, 0xBC, 0xC9, 0xF2, 0x8E, 0x62, 0x9F, 0xAE, 0xF3, 0xB0, 0xDF, 
        0x84, 0x0A, 0x4F, 0xA3, 0x96, 0x24, 0x4E, 0xCA, 0x94, 0x64, 0x68, 0x5F, 0x4D, 0x53, 0x6D, 0xAB, 
        0x7C, 0x72, 0x56, 0x4C, 0x75, 0x25, 0xC0, 0xA9, 0x6B, 0x9D, 0x9E, 0xDC, 0x23, 0xE6, 0xC7, 0x87, 
        0x55, 0x6E, 0xD2, 0x36, 0x30, 0x16, 0x29, 0x1C, 0xB9, 0x26, 0xE3, 0xE0, 0xBE, 0x83, 0x02, 0xAD, 
        0x7A, 0xCE, 0x19, 0xD5, 0x05, 0x89, 0x1D, 0xD6, 0x42, 0xA1, 0xAA, 0x90, 0xC4, 0xD4, 0x86, 0x5D, 
        0x0B, 0x66, 0xF4, 0xFD, 0x47, 0x09, 0xE1, 0x5E, 0xCC, 0x04, 0x76, 0x71, 0x2C, 0x73, 0xA6, 0x95, 
        0x54, 0xB6, 0xF8, 0xD0, 0xEA, 0x51, 0x59, 0xA2, 0x5C, 0xDB, 0x48, 0xDA, 0x97, 0x58, 0x9B, 0xC2, 
        0x3C, 0xC3, 0x0F, 0xFC, 0xE7, 0xC5, 0x82, 0xF1, 0x8A, 0x3D, 0x6A, 0xCB, 0xB2, 0x65, 0x99, 0x01, 
        0xA7, 0xB4, 0x2F, 0xC6, 0x3F, 0xD7, 0xF7, 0x93, 0x1A, 0x8B, 0x35, 0x98, 0x3B, 0xCF, 0xF9, 0x8F, 
        0xFA, 0x37, 0x81, 0x15, 0x9C, 0xE8, 0xBB, 0x1F, 0x7D, 0xDE, 0x4B, 0x00, 0x0E, 0xFB, 0x49, 0xB1, 
        0x22, 0xEB, 0xAF, 0xC8, 0x33, 0x44, 0x40, 0x2E, 0x08, 0xEE, 0x78, 0x6C, 0xDD, 0x9A, 0xD8, 0x5A, 
        0x91, 0xBF, 0x28, 0xB8, 0x1E, 0x4A, 0x03, 0x45, 0xA4, 0xD9, 0x61, 0x69, 0x38, 0xEC, 0xD1, 0xA0
    },
    {
        0x08, 0xE5, 0xDF, 0x28, 0x3F, 0x15, 0xFF, 0x36, 0x7A, 0xBC, 0xE2, 0x7D, 0xC8, 0x2E, 0x75, 0xDD, 
        0xE6, 0x93, 0xC1, 0xE7, 0x22, 0xF4, 0x1B, 0x1A, 0xBA, 0x09, 0x6A, 0x9F, 0x7C, 0xA5, 0x37, 0xDE, 
        0xBF, 0xEF, 0xAC, 0x88, 0xB5, 0xAA, 0xD7, 0x29, 0x90, 0xA7, 0xCF, 0x18, 0x10, 0xFE, 0x78, 0x6B, 
        0x54, 0x13, 0x60, 0xF9, 0x9E, 0x44, 0x56, 0xB3, 0x73, 0xA6, 0xB6, 0x02, 0x1D, 0x8A, 0x57, 0xFA, 
        0xA1, 0x91, 0xB0, 0xBB, 0xB9, 0xFD, 0xD3, 0x4F, 0xCE, 0x40, 0x2C, 0x55, 0x58, 0x00, 0x97, 0x5C, 
        0xCC, 0xE1, 0xBE, 0xD2, 0x47, 0xED, 0x70, 0xD1, 0x17, 0xE4, 0xA0, 0x65, 0xEE, 0x21, 0xF6, 0x0E, 
        0xE3, 0xF7, 0x77, 0x20, 0xF1, 0x23, 0x5D, 0x5E, 0x3E, 0x05, 0x9B, 0xC2, 0xEB, 0x8D, 0x5B, 0x52, 
        0xE9, 0x68, 0xD6, 0x66, 0xAE, 0x7E, 0x67, 0xF2, 0x85, 0xBD, 0xDB, 0x45, 0x83, 0xCA, 0x3D, 0xC6, 
        0x2B, 0x49, 0xA4, 0xD0, 0x3B, 0x46, 0x3C, 0x4E, 0x34, 0x82, 0xC0, 0x8F, 0xC5, 0x1E, 0x9C, 0x35, 
        0x2F, 0xB4, 0x06, 0x14, 0x62, 0x7F, 0x8B, 0xAB, 0x19, 0xF5, 0x6F, 0x69, 0x31, 0x39, 0x84, 0xD9, 
        0x27, 0x5F, 0x42, 0x86, 0xC9, 0x71, 0xAD, 0x1C, 0xFB, 0xC4, 0xB8, 0x0A, 0x89, 0x63, 0xCD, 0x0D, 
        0xEA, 0xC3, 0xB7, 0xDA, 0x43, 0x0B, 0x04, 0x50, 0xD8, 0x24, 0xF0, 0x1F, 0xC7, 0x2A, 0x9D, 0xA3, 
        0x4A, 0x0F, 0xAF, 0x95, 0x74, 0x80, 0x98, 0x11, 0x3A, 0x16, 0xF8, 0x53, 0xEC, 0x87, 0x8C, 0x8E, 
        0x12, 0xA8, 0x9A, 0xE0, 0xCB, 0x99, 0xD5, 0x6C, 0x2D, 0x92, 0x26, 0x6D, 0x79, 0xDC, 0x76, 0x59, 
        0x25, 0x07, 0x96, 0x81, 0x30, 0xFC, 0x64, 0x61, 0xB1, 0x51, 0x7B, 0x38, 0x0C, 0x03, 0x5A, 0x33, 
        0x41, 0x4D, 0xA9, 0x4B, 0xA2, 0xE8, 0xF3, 0x32, 0xD4, 0x94, 0xB2, 0x6E, 0x72, 0x01, 0x48, 0x4C
    }
};

