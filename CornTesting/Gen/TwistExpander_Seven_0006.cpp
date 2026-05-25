#include "TwistExpander_Seven_0006.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix64.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmConstants.hpp"

#include <cstring>

TwistExpander_Seven_0006::TwistExpander_Seven_0006()
: TwistExpander() {

}

void TwistExpander_Seven_0006::KDF(std::uint64_t pNonce,
                                TwistDomainConstants *pConstants,
                                TwistDomainSaltSet *pDomainSaltSet,
                                TwistDomainSBoxSet *pDomainSBoxSet) {
    KDF_A(pNonce, pConstants, pDomainSaltSet, pDomainSBoxSet);
}

void TwistExpander_Seven_0006::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0;

    std::uint64_t aWandererA = 0; std::uint64_t aWandererB = 0; std::uint64_t aWandererC = 0; std::uint64_t aWandererD = 0;
    std::uint64_t aWandererE = 0; std::uint64_t aWandererF = 0; std::uint64_t aWandererG = 0;

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
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 5U) ^ RotL64(aNonceByteB, 19U)) ^ RotL64(aNonceByteC, 58U));
            aIngress = aIngress ^ (RotL64(aSource[((aIndex + 1320U)) & S_BLOCK1], 27U) ^ RotL64(aSource[((aIndex + 14781U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 35U) ^ RotL64(aNonceByteE, 47U)) ^ RotL64(aNonceByteF, 5U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 555U)) & S_BLOCK1], 60U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 246U)) & S_BLOCK1], 13U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 13U) ^ RotL64(aIngress, 47U)) ^ (RotL64(aCross, 60U) + RotL64(aPrevious, 35U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = ((aWandererD + RotL64(aScatter, 51U)) + 12775735908960052604U) + aOrbiterAssignSaltA[(((31U - aIndex) + 1293U)) & S_SALT1];
            aOrbiterC = (aWandererF + RotL64(aCross, 19U)) + 11791373812080296887U;
            aOrbiterD = ((aWandererE + RotL64(aPrevious, 5U)) + 5537362877706057303U) + RotL64(aNonceByteG, 43U);
            aOrbiterB = ((aWandererB + RotL64(aIngress, 41U)) + RotL64(aCarry, 19U)) + 2023912048504189380U;
            aOrbiterE = (((aWandererC + RotL64(aPrevious, 35U)) + RotL64(aCarry, 57U)) + 17668828109963766893U) + aOrbiterAssignSaltB[(((31U - aIndex) + 1459U)) & S_SALT1];
            aOrbiterF = (aWandererG + RotL64(aCross, 58U)) + 558908629933941224U;
            aOrbiterG = (((aWandererA + RotL64(aScatter, 27U)) + RotL64(aCarry, 41U)) + 1479633119685446888U) + RotL64(aNonceByteC, 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 15460320397843364063U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 10059749397555469054U) ^ RotL64(aNonceByteD, 38U);
            aOrbiterD = RotL64((aOrbiterD * 8671817118586065469U), 57U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 9987633811929693924U;
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 10087337844580228269U;
            aOrbiterE = RotL64((aOrbiterE * 13817142288940843815U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 4446204415503364254U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterC) ^ 15106063243302192717U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 3613U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 13273756657334709803U), 29U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 9430197906134676162U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 2487U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 1226048679997253363U;
            aOrbiterG = RotL64((aOrbiterG * 14247538885252664127U), 41U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterG) + 10611580584157624739U) + RotL64(aNonceByteH, 29U);
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 3137391249289641509U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 148U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 5462682413239873181U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 9327201928815412810U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 7890659377013147073U;
            aOrbiterB = RotL64((aOrbiterB * 13827717178378062047U), 51U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterB) + 10675114832750356941U) + aOrbiterUpdateSaltA[((aIndex + 2361U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 8804440385852327267U;
            aOrbiterC = RotL64((aOrbiterC * 8520671775587260601U), 19U);
            //
            aIngress = RotL64(aOrbiterA, 11U) ^ aOrbiterB;
            aIngress = aIngress + (RotL64(aOrbiterC, 50U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterD, 3U) ^ aOrbiterF);
            aIngress = aIngress + RotL64(aOrbiterE, 23U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aCross, 41U) + aOrbiterF) + RotL64(aOrbiterC, 3U)) + RotL64(aNonceByteA, 47U));
            aWandererB = aWandererB + ((RotL64(aIngress, 3U) + aOrbiterA) + RotL64(aOrbiterC, 27U));
            aWandererC = aWandererC ^ (((RotL64(aPrevious, 13U) + aOrbiterB) + RotL64(aOrbiterE, 54U)) + aWandererUpdateSaltA[(((31U - aIndex) + 1206U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aScatter, 29U) + aOrbiterA) + RotL64(aOrbiterD, 35U)) + RotL64(aCarry, 5U));
            aWandererE = aWandererE ^ (((RotL64(aCross, 19U) + aOrbiterE) + RotL64(aOrbiterA, 13U)) + aWandererUpdateSaltB[((aIndex + 2094U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aIngress, 60U) + aOrbiterG) + RotL64(aOrbiterC, 41U)) + RotL64(aCarry, 21U));
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 51U) + aOrbiterB) + RotL64(aOrbiterD, 19U)) + RotL64(aNonceByteB, 57U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 51U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererF, 5U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererA, 43U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererD, 12U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 21U) ^ RotL64(aNonceByteB, 13U)) ^ RotL64(aNonceByteC, 52U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 7252U)) & S_BLOCK1], 37U) ^ RotL64(aSource[((aIndex + 13842U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 53U) ^ RotL64(aNonceByteE, 44U)) ^ RotL64(aNonceByteF, 35U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 12963U)) & S_BLOCK1], 19U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 13612U)) & S_BLOCK1], 27U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 23U) ^ RotL64(aIngress, 10U)) + (RotL64(aPrevious, 53U) ^ RotL64(aCarry, 35U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = (((aWandererA + RotL64(aPrevious, 53U)) + RotL64(aCarry, 35U)) + 17264605017518259932U) + RotL64(aNonceByteB, 23U);
            aOrbiterD = (aWandererG + RotL64(aIngress, 29U)) + 15209184354580778643U;
            aOrbiterC = ((aWandererB + RotL64(aCross, 46U)) + 3299527965014731384U) + aOrbiterAssignSaltA[(((31U - aIndex) + 7797U)) & S_SALT1];
            aOrbiterF = ((aWandererF + RotL64(aScatter, 5U)) + 16293096431816127821U) + aOrbiterAssignSaltB[((aIndex + 4328U)) & S_SALT1];
            aOrbiterB = (aWandererC + RotL64(aCross, 13U)) + 11031983436878828337U;
            aOrbiterG = (((aWandererE + RotL64(aScatter, 39U)) + RotL64(aCarry, 53U)) + 9188018632448236358U) + RotL64(aNonceByteD, 9U);
            aOrbiterE = ((aWandererD + RotL64(aIngress, 23U)) + RotL64(aCarry, 23U)) + 13420816400363406556U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 2485063384097917101U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 3089135816938128264U;
            aOrbiterC = RotL64((aOrbiterC * 8813152992957361153U), 19U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 10730544971770435788U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 10431767565618874806U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 4077U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 4723078464590561545U), 37U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 14883796491656899074U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterD) ^ 13465877783538483706U) ^ aOrbiterUpdateSaltA[((aIndex + 4827U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 14311686051108108503U), 27U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 13322163435314643713U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 1274U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 3307316600284371955U) ^ RotL64(aNonceByteE, 19U);
            aOrbiterD = RotL64((aOrbiterD * 12337846092069506365U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 4950101626975919939U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterG) ^ 2596253994220103666U) ^ RotL64(aNonceByteC, 35U);
            aOrbiterB = RotL64((aOrbiterB * 7181706961838582889U), 51U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 17961706029559914243U;
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 10321902557977495175U;
            aOrbiterG = RotL64((aOrbiterG * 16189559888625084711U), 13U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterF) + 18146616411403012772U) + aOrbiterUpdateSaltC[((aIndex + 2899U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 8414050129421955787U;
            aOrbiterE = RotL64((aOrbiterE * 14879448948196182863U), 57U);
            //
            aIngress = RotL64(aOrbiterD, 43U) ^ aOrbiterC;
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterB, 5U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterG, 21U));
            aIngress = aIngress + RotL64(aOrbiterA, 27U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((((RotL64(aPrevious, 43U) + RotL64(aOrbiterA, 4U)) + aOrbiterG) + RotL64(aCarry, 13U)) + aWandererUpdateSaltA[((aIndex + 1507U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 19U) + aOrbiterB) + RotL64(aOrbiterG, 29U));
            aWandererC = aWandererC + ((RotL64(aCross, 51U) + aOrbiterE) + RotL64(aOrbiterC, 13U));
            aWandererD = aWandererD ^ ((RotL64(aIngress, 37U) + aOrbiterG) + RotL64(aOrbiterC, 43U));
            aWandererE = aWandererE + ((((RotL64(aScatter, 27U) + RotL64(aOrbiterF, 35U)) + aOrbiterC) + RotL64(aCarry, 29U)) + aWandererUpdateSaltB[((aIndex + 5743U)) & S_SALT1]);
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 13U) + aOrbiterE) + RotL64(aOrbiterB, 57U)) + RotL64(aNonceByteG, 18U));
            aWandererG = aWandererG + (((RotL64(aCross, 58U) + aOrbiterD) + RotL64(aOrbiterB, 51U)) + RotL64(aNonceByteH, 45U));
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererC, 12U));
            aCarry = aCarry + (RotL64(aWandererE, 41U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererB, 53U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererD, 57U);
            aCarry = aCarry + RotL64(aIngress, 6U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 43U) ^ RotL64(aNonceByteB, 13U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 6956U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 8852U)) & S_BLOCK1], 28U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 27U) ^ RotL64(aNonceByteD, 19U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 9745U)) & S_BLOCK1], 4U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 9794U)) & S_BLOCK1], 41U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 21U) ^ RotL64(aCross, 35U)) ^ (RotL64(aPrevious, 5U) + RotL64(aCarry, 56U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterC = (aWandererF + RotL64(aCross, 43U)) + 11274974230580265396U;
            aOrbiterE = ((aWandererE + RotL64(aIngress, 19U)) + 16658438747342741547U) + RotL64(aNonceByteC, 48U);
            aOrbiterG = ((aWandererD + RotL64(aPrevious, 12U)) + 16612986966106053844U) + aOrbiterAssignSaltB[((aIndex + 5911U)) & S_SALT1];
            aOrbiterA = ((aWandererA + RotL64(aScatter, 51U)) + RotL64(aCarry, 41U)) + 9329502236843231290U;
            aOrbiterF = (((aWandererB + RotL64(aIngress, 37U)) + 14088261356708344656U) + aOrbiterAssignSaltA[((aIndex + 2300U)) & S_SALT1]) + RotL64(pNonce, 29U);
            aOrbiterD = ((aWandererC + RotL64(aPrevious, 5U)) + RotL64(aCarry, 53U)) + 13692608802007789581U;
            aOrbiterB = ((aWandererG + RotL64(aCross, 29U)) + RotL64(aCarry, 27U)) + 6824473946645682398U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 2072915876348570040U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 7420507753044460759U;
            aOrbiterG = RotL64((aOrbiterG * 13239288539564571257U), 5U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 4677557318688502593U) + RotL64(aNonceByteH, 35U);
            aOrbiterE = ((aOrbiterE ^ aOrbiterA) ^ 15081678577055628459U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 1165U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 16659305295251177155U), 35U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 7026792817486507482U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterF) ^ 14871665922943969918U) ^ aOrbiterUpdateSaltA[((aIndex + 6211U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 694073180313083145U), 21U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 6807734532159292872U) + aOrbiterUpdateSaltD[((aIndex + 1138U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 17882797335141303280U;
            aOrbiterA = RotL64((aOrbiterA * 15439872930381050291U), 13U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 9233542707022629190U) + aOrbiterUpdateSaltB[((aIndex + 4591U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 1205501586581350876U;
            aOrbiterF = RotL64((aOrbiterF * 2596053290311090589U), 27U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 10878718669747466677U;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 8066049063548639241U;
            aOrbiterD = RotL64((aOrbiterD * 3031382633089381605U), 41U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterG) + 861295180226875235U) + RotL64(aNonceByteG, 9U);
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 9134969787937288583U;
            aOrbiterB = RotL64((aOrbiterB * 7565008208670843555U), 57U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterE, 3U);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterB, 43U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterG, 11U));
            aIngress = aIngress + RotL64(aOrbiterF, 29U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 54U) + aOrbiterF) + RotL64(aOrbiterC, 47U));
            aWandererB = aWandererB + (((RotL64(aIngress, 3U) + RotL64(aOrbiterD, 11U)) + aOrbiterA) + RotL64(aCarry, 43U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 47U) + RotL64(aOrbiterF, 57U)) + aOrbiterD);
            aWandererD = aWandererD + (((RotL64(aCross, 39U) + RotL64(aOrbiterB, 35U)) + aOrbiterE) + RotL64(aCarry, 5U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 13U) + aOrbiterD) + RotL64(aOrbiterG, 26U));
            aWandererF = aWandererF + ((((RotL64(aScatter, 29U) + aOrbiterE) + RotL64(aOrbiterA, 5U)) + RotL64(aNonceByteF, 17U)) + aWandererUpdateSaltA[(((31U - aIndex) + 637U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((((RotL64(aCross, 19U) + aOrbiterB) + RotL64(aOrbiterD, 41U)) + RotL64(aNonceByteE, 59U)) + aWandererUpdateSaltB[(((31U - aIndex) + 2363U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererD, 10U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererG, 41U));
            aCarry = aCarry + (RotL64(aWandererE, 47U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererC, 37U);
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
            aIngress = aIngress ^ (RotL64(aNonceByteA, 57U) ^ RotL64(aNonceByteB, 12U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 2496U)) & S_BLOCK1], 23U) ^ RotL64(aExpandLaneB[((aIndex + 7908U)) & S_BLOCK1], 37U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 51U) ^ RotL64(aNonceByteD, 60U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 1371U)) & S_BLOCK1], 5U) ^ RotL64(aSource[((aIndex + 15347U)) & S_BLOCK1], 19U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 51U) ^ RotL64(aPrevious, 39U)) ^ (RotL64(aIngress, 3U) + RotL64(aCross, 18U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterB = (aWandererF + RotL64(aIngress, 60U)) + 3339283916456813609U;
            aOrbiterG = ((((aWandererA + RotL64(aCross, 43U)) + RotL64(aCarry, 57U)) + 11339086426180649584U) + aOrbiterAssignSaltA[((aIndex + 7255U)) & S_SALT1]) + RotL64(aNonceByteA, 60U);
            aOrbiterE = (aWandererE + RotL64(aScatter, 53U)) + 16819191669329316585U;
            aOrbiterC = (((aWandererB + RotL64(aPrevious, 27U)) + RotL64(aCarry, 21U)) + 8361916937762630725U) + RotL64(aNonceByteH, 53U);
            aOrbiterA = ((aWandererD + RotL64(aScatter, 35U)) + RotL64(aCarry, 37U)) + 18031328374429899857U;
            aOrbiterF = ((aWandererG + RotL64(aIngress, 3U)) + 18261756894092897276U) + aOrbiterAssignSaltB[((aIndex + 871U)) & S_SALT1];
            aOrbiterD = (aWandererC + RotL64(aCross, 19U)) + 4250319792907645666U;
            //
            aOrbiterB = ((aOrbiterB + aOrbiterG) + 1492411503643460886U) + aOrbiterUpdateSaltD[((aIndex + 405U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 17369549067879344180U;
            aOrbiterE = RotL64((aOrbiterE * 2947354306696216579U), 57U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 7301713524358676722U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 7835U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 2985193736033012535U;
            aOrbiterF = RotL64((aOrbiterF * 7473297294949338265U), 29U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 14086975808140927408U;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 10390516547834639800U;
            aOrbiterG = RotL64((aOrbiterG * 11441293212275890819U), 21U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 18205555540941493267U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 16967799565443938873U) ^ aOrbiterUpdateSaltB[((aIndex + 7972U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 3009081009044782443U), 11U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 9209505304067579944U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 3522631966146762306U;
            aOrbiterB = RotL64((aOrbiterB * 3441982898533162599U), 43U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 8811497120829041188U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 14707301680850257294U;
            aOrbiterC = RotL64((aOrbiterC * 11383709499376464085U), 3U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterF) + 10080595991787801029U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 5480U)) & S_SALT1]) + RotL64(aNonceByteE, 13U);
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 6822892187784299166U) ^ RotL64(aNonceByteD, 39U);
            aOrbiterD = RotL64((aOrbiterD * 7417016898027778287U), 37U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterG, 43U);
            aIngress = aIngress + (RotL64(aOrbiterC, 26U) ^ aOrbiterD);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterA, 19U));
            aIngress = aIngress + RotL64(aOrbiterB, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aIngress, 35U) + aOrbiterC) + RotL64(aOrbiterA, 3U));
            aWandererB = aWandererB + ((((RotL64(aScatter, 3U) + aOrbiterC) + RotL64(aOrbiterE, 35U)) + RotL64(aCarry, 53U)) + aWandererUpdateSaltB[((aIndex + 5684U)) & S_SALT1]);
            aWandererC = aWandererC ^ (((RotL64(aCross, 51U) + aOrbiterB) + RotL64(aOrbiterD, 11U)) + RotL64(aNonceByteF, 43U));
            aWandererD = aWandererD + ((((RotL64(aPrevious, 29U) + RotL64(aOrbiterG, 48U)) + aOrbiterE) + RotL64(aCarry, 13U)) + aWandererUpdateSaltA[(((31U - aIndex) + 4273U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aScatter, 43U) + aOrbiterD) + RotL64(aOrbiterF, 41U));
            aWandererF = aWandererF + ((RotL64(aPrevious, 18U) + RotL64(aOrbiterE, 27U)) + aOrbiterB);
            aWandererG = aWandererG ^ (((RotL64(aIngress, 57U) + RotL64(aOrbiterD, 19U)) + aOrbiterG) + RotL64(aNonceByteG, 21U));
            //
            aCarry = aCarry + (RotL64(aWandererC, 52U) ^ aWandererG);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererF, 29U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererB, 3U));
            aCarry = aCarry + RotL64(aWandererA, 35U);
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
            aIngress = aIngress ^ (RotL64(aNonceByteA, 11U) ^ RotL64(aNonceByteB, 27U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 15845U)) & S_BLOCK1], 56U) ^ RotL64(aExpandLaneC[((aIndex + 1042U)) & S_BLOCK1], 39U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 5U) ^ RotL64(aNonceByteD, 37U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 8719U)) & S_BLOCK1], 54U) ^ RotL64(aExpandLaneA[((aIndex + 9960U)) & S_BLOCK1], 23U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 5U) + RotL64(aPrevious, 57U)) ^ (RotL64(aIngress, 36U) ^ RotL64(aCross, 23U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterD = ((aWandererD + RotL64(aScatter, 47U)) + RotL64(aCarry, 51U)) + 5697928251815176134U;
            aOrbiterG = (((aWandererG + RotL64(aCross, 35U)) + RotL64(aCarry, 29U)) + 337587740689259575U) + RotL64(aNonceByteB, 9U);
            aOrbiterF = (aWandererF + RotL64(aIngress, 53U)) + 4927686903263973950U;
            aOrbiterB = ((aWandererB + RotL64(aPrevious, 29U)) + RotL64(aCarry, 11U)) + 3742409032569801033U;
            aOrbiterE = ((aWandererA + RotL64(aScatter, 18U)) + 1608092659172197650U) + aOrbiterAssignSaltB[(((31U - aIndex) + 6315U)) & S_SALT1];
            aOrbiterC = ((aWandererE + RotL64(aIngress, 11U)) + 15848744267145717509U) + aOrbiterAssignSaltA[((aIndex + 5937U)) & S_SALT1];
            aOrbiterA = ((aWandererC + RotL64(aCross, 3U)) + 15300174177963339253U) + RotL64(aNonceByteE, 41U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 14162868453323648628U;
            aOrbiterF = (((aOrbiterF ^ aOrbiterD) ^ 12020167069983729869U) ^ aOrbiterUpdateSaltC[((aIndex + 120U)) & S_SALT1]) ^ RotL64(aNonceByteF, 12U);
            aOrbiterF = RotL64((aOrbiterF * 2071080217680099017U), 29U);
            //
            aOrbiterB = (((aOrbiterB + aOrbiterE) + 16259538291658723956U) + aOrbiterUpdateSaltB[((aIndex + 5509U)) & S_SALT1]) + RotL64(aNonceByteH, 55U);
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 8516686212464112245U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 6585U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 4731296903548893627U), 23U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 3722184575520553132U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 5663609293306386784U;
            aOrbiterB = RotL64((aOrbiterB * 14364218128780764749U), 41U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterA) + 15265344442454471986U) + aOrbiterUpdateSaltD[((aIndex + 231U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 3050323350098829515U;
            aOrbiterG = RotL64((aOrbiterG * 5890624677162388135U), 57U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 1093356813820599238U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 15167726103772238440U;
            aOrbiterE = RotL64((aOrbiterE * 5719466863561311069U), 3U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 15170797965325981472U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 17826286701992981628U;
            aOrbiterC = RotL64((aOrbiterC * 11186808881726573677U), 35U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 14710892030473425181U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 397194787697553904U;
            aOrbiterA = RotL64((aOrbiterA * 14368930300818752833U), 47U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterD, 51U);
            aIngress = aIngress + (RotL64(aOrbiterB, 26U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterE, 5U));
            aIngress = aIngress + RotL64(aOrbiterA, 11U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aIngress, 13U) + RotL64(aOrbiterC, 37U)) + aOrbiterE) + aWandererUpdateSaltB[(((31U - aIndex) + 3517U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 3U) + aOrbiterA) + RotL64(aOrbiterC, 57U));
            aWandererC = aWandererC + (((RotL64(aScatter, 19U) + aOrbiterG) + RotL64(aOrbiterD, 23U)) + RotL64(aCarry, 19U));
            aWandererD = aWandererD ^ (((RotL64(aCross, 35U) + aOrbiterA) + RotL64(aOrbiterD, 13U)) + RotL64(aNonceByteD, 51U));
            aWandererE = aWandererE + (((RotL64(aPrevious, 26U) + aOrbiterB) + RotL64(aOrbiterD, 3U)) + RotL64(aCarry, 51U));
            aWandererF = aWandererF ^ ((RotL64(aIngress, 43U) + RotL64(aOrbiterF, 48U)) + aOrbiterD);
            aWandererG = aWandererG + ((((RotL64(aCross, 53U) + aOrbiterC) + RotL64(aOrbiterF, 29U)) + RotL64(aNonceByteG, 57U)) + aWandererUpdateSaltA[((aIndex + 2954U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererB, 29U));
            aCarry = aCarry + (RotL64(aWandererG, 20U) ^ aWandererC);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererA, 53U));
            aCarry = aCarry + RotL64(aWandererF, 3U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneE[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 53U) ^ RotL64(aNonceByteB, 38U));
            aIngress = aIngress ^ (RotL64(aExpandLaneE[((aIndex + 12239U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 1975U)) & S_BLOCK1], 29U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 37U) ^ RotL64(aNonceByteD, 54U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 3116U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneB[((aIndex + 105U)) & S_BLOCK1], 5U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 51U) ^ RotL64(aPrevious, 5U)) + (RotL64(aCarry, 21U) + RotL64(aIngress, 36U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterC = (((aWandererF + RotL64(aScatter, 60U)) + 10336802574069791273U) + aOrbiterAssignSaltA[(((31U - aIndex) + 2961U)) & S_SALT1]) + RotL64(aNonceByteA, 36U);
            aOrbiterE = (aWandererB + RotL64(aIngress, 13U)) + 169025388197058936U;
            aOrbiterF = (aWandererG + RotL64(aCross, 47U)) + 6541354188379168846U;
            aOrbiterD = (((aWandererC + RotL64(aPrevious, 27U)) + RotL64(aCarry, 53U)) + 16223920526599306104U) + aOrbiterAssignSaltB[((aIndex + 1019U)) & S_SALT1];
            aOrbiterG = ((aWandererD + RotL64(aIngress, 3U)) + RotL64(aCarry, 3U)) + 12756613707692514808U;
            aOrbiterA = ((aWandererE + RotL64(aScatter, 35U)) + 5082475548176484035U) + RotL64(aNonceByteF, 15U);
            aOrbiterB = ((aWandererA + RotL64(aCross, 19U)) + RotL64(aCarry, 27U)) + 4907435526952698526U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 14236627073831834337U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 11502511046130497584U;
            aOrbiterF = RotL64((aOrbiterF * 3460330807286625917U), 43U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 3679044835550219497U) + aOrbiterUpdateSaltA[((aIndex + 7495U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterD) ^ 11254838916686736746U) ^ aOrbiterUpdateSaltC[((aIndex + 7417U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 8631695922983532915U), 51U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 10582608424233200966U;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 10449735026385340313U;
            aOrbiterA = RotL64((aOrbiterA * 7363770199734997411U), 57U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 4628253464169957835U) + aOrbiterUpdateSaltB[((aIndex + 4378U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 17664454668473204465U;
            aOrbiterB = RotL64((aOrbiterB * 4234720298731378527U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 3798386391743884889U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 1379331161819246587U;
            aOrbiterC = RotL64((aOrbiterC * 13086160171095077295U), 37U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterC) + 9816600392407327227U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 5835U)) & S_SALT1]) + RotL64(aNonceByteH, 37U);
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 16781971616348376878U;
            aOrbiterD = RotL64((aOrbiterD * 12503867584828289879U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 4807797577690520554U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 2492057261148595922U) ^ RotL64(aNonceByteB, 41U);
            aOrbiterE = RotL64((aOrbiterE * 9453302540675483005U), 29U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterE, 3U);
            aIngress = aIngress + (RotL64(aOrbiterD, 27U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterA, 11U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterF, 57U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aPrevious, 11U) + RotL64(aOrbiterC, 51U)) + aOrbiterG);
            aWandererB = aWandererB ^ (((RotL64(aScatter, 48U) + RotL64(aOrbiterB, 57U)) + aOrbiterF) + RotL64(aNonceByteG, 39U));
            aWandererC = aWandererC + ((((RotL64(aIngress, 3U) + aOrbiterG) + RotL64(aOrbiterA, 23U)) + RotL64(aCarry, 5U)) + aWandererUpdateSaltB[((aIndex + 3410U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aCross, 37U) + aOrbiterC) + RotL64(aOrbiterF, 38U)) + RotL64(aNonceByteE, 7U));
            aWandererE = aWandererE + ((RotL64(aPrevious, 57U) + aOrbiterD) + RotL64(aOrbiterA, 11U));
            aWandererF = aWandererF ^ (((RotL64(aScatter, 27U) + RotL64(aOrbiterE, 3U)) + aOrbiterA) + aWandererUpdateSaltA[(((31U - aIndex) + 1366U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aCross, 19U) + RotL64(aOrbiterF, 29U)) + aOrbiterA) + RotL64(aCarry, 43U));
            //
            aCarry = aCarry + (RotL64(aWandererF, 3U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererC, 30U) ^ aWandererA);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererB, 57U));
            aCarry = aCarry + RotL64(aWandererG, 53U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneF[S_BLOCK1 - aIndex] = aIngress;
        }
    }
};

