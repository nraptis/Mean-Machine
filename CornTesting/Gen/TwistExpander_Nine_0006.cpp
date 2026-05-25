#include "TwistExpander_Nine_0006.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix64.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmConstants.hpp"

#include <cstring>

TwistExpander_Nine_0006::TwistExpander_Nine_0006()
: TwistExpander() {

}

void TwistExpander_Nine_0006::KDF(std::uint64_t pNonce,
                                TwistDomainConstants *pConstants,
                                TwistDomainSaltSet *pDomainSaltSet,
                                TwistDomainSBoxSet *pDomainSBoxSet) {
    KDF_A(pNonce, pConstants, pDomainSaltSet, pDomainSBoxSet);
}

void TwistExpander_Nine_0006::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aOrbiterI = 0;

    std::uint64_t aWandererA = 0; std::uint64_t aWandererB = 0; std::uint64_t aWandererC = 0; std::uint64_t aWandererD = 0;
    std::uint64_t aWandererE = 0; std::uint64_t aWandererF = 0; std::uint64_t aWandererG = 0; std::uint64_t aWandererH = 0;
    std::uint64_t aWandererI = 0;

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
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 21U) ^ RotL64(aNonceByteB, 41U)) ^ RotL64(aNonceByteC, 12U));
            aIngress = aIngress ^ (RotL64(aSource[((aIndex + 15002U)) & S_BLOCK1], 3U) ^ RotL64(aSource[((aIndex + 8832U)) & S_BLOCK1], 29U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 27U) ^ RotL64(aNonceByteE, 19U)) ^ RotL64(aNonceByteF, 57U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 2307U)) & S_BLOCK1], 39U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 15087U)) & S_BLOCK1], 48U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 57U) ^ RotL64(aCarry, 23U)) + (RotL64(aIngress, 10U) ^ RotL64(aCross, 43U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = ((aWandererC + RotL64(aIngress, 28U)) + 17264605017518259932U) + aOrbiterAssignSaltA[(((31U - aIndex) + 2246U)) & S_SALT1];
            aOrbiterC = (aWandererD + RotL64(aCross, 51U)) + 15209184354580778643U;
            aOrbiterD = ((aWandererE + RotL64(aScatter, 43U)) + RotL64(aCarry, 21U)) + 3299527965014731384U;
            aOrbiterB = (aWandererI + RotL64(aPrevious, 57U)) + 16293096431816127821U;
            aOrbiterH = ((aWandererG + RotL64(aIngress, 19U)) + 11031983436878828337U) + RotL64(aNonceByteF, 39U);
            aOrbiterG = (((aWandererF + RotL64(aPrevious, 4U)) + RotL64(aCarry, 5U)) + 9188018632448236358U) + aOrbiterAssignSaltB[((aIndex + 498U)) & S_SALT1];
            aOrbiterI = (((aWandererH + RotL64(aCross, 35U)) + RotL64(aCarry, 43U)) + 13420816400363406556U) + RotL64(aNonceByteG, 31U);
            aOrbiterE = (aWandererA + RotL64(aScatter, 39U)) + 2485063384097917101U;
            aOrbiterF = (aWandererB + RotL64(aCross, 13U)) + 3089135816938128264U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 10730544971770435788U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 10431767565618874806U;
            aOrbiterD = RotL64((aOrbiterD * 4723078464590561545U), 39U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 14883796491656899074U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 13465877783538483706U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 7510U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 14311686051108108503U), 11U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterD) + 13322163435314643713U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 1101U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 3307316600284371955U;
            aOrbiterE = RotL64((aOrbiterE * 12337846092069506365U), 19U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterG) + 4950101626975919939U) + RotL64(aNonceByteH, 41U);
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 2596253994220103666U;
            aOrbiterF = RotL64((aOrbiterF * 7181706961838582889U), 43U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 17961706029559914243U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 10321902557977495175U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 6021U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 16189559888625084711U), 53U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 18146616411403012772U;
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 8414050129421955787U;
            aOrbiterB = RotL64((aOrbiterB * 14879448948196182863U), 29U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterA) + 11739172334166341121U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 8053U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 7936637782633487291U;
            aOrbiterI = RotL64((aOrbiterI * 14940929920543800413U), 47U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 3160044627483874242U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 16816384076887379704U;
            aOrbiterC = RotL64((aOrbiterC * 5052772186568301951U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 8101560104988710226U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterF) ^ 8851416379738817624U) ^ RotL64(aNonceByteB, 11U);
            aOrbiterH = RotL64((aOrbiterH * 16767420038937389027U), 57U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterI, 51U);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterB, 3U));
            aIngress = aIngress + (RotL64(aOrbiterG, 11U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterD, 27U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterH, 48U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aScatter, 34U) + RotL64(aOrbiterG, 41U)) + aOrbiterB);
            aWandererB = aWandererB + (((RotL64(aCross, 23U) + aOrbiterF) + RotL64(aOrbiterD, 48U)) + aWandererUpdateSaltB[((aIndex + 3219U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aIngress, 19U) + aOrbiterE) + RotL64(aOrbiterA, 19U));
            aWandererD = aWandererD + ((RotL64(aPrevious, 53U) + RotL64(aOrbiterA, 37U)) + aOrbiterC);
            aWandererE = aWandererE ^ ((RotL64(aCross, 58U) + RotL64(aOrbiterE, 27U)) + aOrbiterI);
            aWandererF = aWandererF + (((((RotL64(aScatter, 47U) + RotL64(aOrbiterC, 3U)) + aOrbiterH) + RotL64(aCarry, 13U)) + RotL64(aNonceByteC, 59U)) + aWandererUpdateSaltA[((aIndex + 3946U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 29U) + aOrbiterF) + RotL64(aOrbiterI, 13U));
            aWandererH = aWandererH + ((((RotL64(aIngress, 5U) + RotL64(aOrbiterC, 52U)) + aOrbiterG) + RotL64(aCarry, 21U)) + RotL64(aNonceByteE, 24U));
            aWandererI = aWandererI ^ ((RotL64(aCross, 11U) + RotL64(aOrbiterB, 23U)) + aOrbiterD);
            //
            aCarry = aCarry + (RotL64(aWandererD, 19U) ^ aWandererC);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererH, 6U));
            aCarry = aCarry + (RotL64(aWandererG, 27U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererI, 23U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererF, 53U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 21U) ^ RotL64(aNonceByteB, 57U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 11534U)) & S_BLOCK1], 34U) ^ RotL64(aSource[((aIndex + 5438U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 35U) ^ RotL64(aNonceByteD, 43U)) ^ RotL64(aNonceByteE, 51U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 9902U)) & S_BLOCK1], 6U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 7761U)) & S_BLOCK1], 21U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 5U) + RotL64(aCross, 56U)) ^ (RotL64(aPrevious, 41U) + RotL64(aCarry, 19U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterC = ((aWandererG + RotL64(aIngress, 56U)) + RotL64(aCarry, 29U)) + 11274974230580265396U;
            aOrbiterF = (aWandererE + RotL64(aPrevious, 51U)) + 16658438747342741547U;
            aOrbiterG = ((aWandererA + RotL64(aCross, 19U)) + 16612986966106053844U) + aOrbiterAssignSaltA[(((31U - aIndex) + 6800U)) & S_SALT1];
            aOrbiterD = (aWandererC + RotL64(aScatter, 23U)) + 9329502236843231290U;
            aOrbiterH = ((aWandererI + RotL64(aCross, 47U)) + RotL64(aCarry, 3U)) + 14088261356708344656U;
            aOrbiterE = (aWandererH + RotL64(aPrevious, 29U)) + 13692608802007789581U;
            aOrbiterI = (aWandererD + RotL64(aIngress, 40U)) + 6824473946645682398U;
            aOrbiterA = (((aWandererF + RotL64(aScatter, 35U)) + RotL64(aCarry, 39U)) + 2072915876348570040U) + RotL64(aNonceByteA, 49U);
            aOrbiterB = (((aWandererB + RotL64(aPrevious, 5U)) + 7420507753044460759U) + aOrbiterAssignSaltB[((aIndex + 5937U)) & S_SALT1]) + RotL64(aNonceByteC, 29U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterF) + 4677557318688502593U) + RotL64(aNonceByteG, 9U);
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 15081678577055628459U;
            aOrbiterG = RotL64((aOrbiterG * 16659305295251177155U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 7026792817486507482U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 14871665922943969918U;
            aOrbiterH = RotL64((aOrbiterH * 694073180313083145U), 19U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterH) + 6807734532159292872U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 4050U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 17882797335141303280U;
            aOrbiterI = RotL64((aOrbiterI * 15439872930381050291U), 29U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 9233542707022629190U) + aOrbiterUpdateSaltA[((aIndex + 1019U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 1205501586581350876U;
            aOrbiterA = RotL64((aOrbiterA * 2596053290311090589U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 10878718669747466677U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 8066049063548639241U;
            aOrbiterB = RotL64((aOrbiterB * 3031382633089381605U), 43U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 861295180226875235U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 9134969787937288583U;
            aOrbiterC = RotL64((aOrbiterC * 7565008208670843555U), 47U);
            //
            aOrbiterI = (((aOrbiterI + aOrbiterC) + 6726642007159809594U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 1370U)) & S_SALT1]) + RotL64(aNonceByteH, 31U);
            aOrbiterD = ((aOrbiterD ^ aOrbiterI) ^ 8061661744643240470U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 1300U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 6703498926835391813U), 11U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 13541412083111962884U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 8617442758729315637U;
            aOrbiterE = RotL64((aOrbiterE * 15471862889276160953U), 37U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 16884403561131293362U;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 9490680911678221233U;
            aOrbiterF = RotL64((aOrbiterF * 15988763830018001033U), 5U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterI, 27U);
            aIngress = aIngress + (RotL64(aOrbiterD, 3U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterG, 35U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterH, 51U));
            aIngress = aIngress + RotL64(aOrbiterA, 14U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aScatter, 30U) + RotL64(aOrbiterB, 23U)) + aOrbiterF) + RotL64(aNonceByteF, 11U));
            aWandererB = aWandererB + (((RotL64(aIngress, 5U) + aOrbiterE) + RotL64(aOrbiterA, 28U)) + aWandererUpdateSaltB[((aIndex + 2887U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aCross, 37U) + aOrbiterC) + RotL64(aOrbiterI, 5U));
            aWandererD = aWandererD + ((RotL64(aPrevious, 47U) + RotL64(aOrbiterF, 11U)) + aOrbiterI);
            aWandererE = aWandererE ^ ((RotL64(aCross, 51U) + aOrbiterC) + RotL64(aOrbiterF, 51U));
            aWandererF = aWandererF + (((RotL64(aIngress, 43U) + RotL64(aOrbiterD, 57U)) + aOrbiterH) + RotL64(aCarry, 23U));
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 12U) + aOrbiterA) + RotL64(aOrbiterG, 35U));
            aWandererH = aWandererH + (((((RotL64(aScatter, 21U) + aOrbiterD) + RotL64(aOrbiterF, 18U)) + RotL64(aCarry, 13U)) + RotL64(aNonceByteB, 4U)) + aWandererUpdateSaltA[((aIndex + 5989U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterE, 39U)) + aOrbiterH);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererF, 39U));
            aCarry = aCarry + (RotL64(aWandererD, 26U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererG, 29U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererH, 19U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererE, 23U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 41U) ^ RotL64(aNonceByteB, 51U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 12270U)) & S_BLOCK1], 18U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 2968U)) & S_BLOCK1], 5U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 21U) ^ RotL64(aNonceByteD, 30U)) ^ RotL64(aNonceByteE, 3U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 2701U)) & S_BLOCK1], 43U) ^ RotL64(aExpandLaneB[((aIndex + 1059U)) & S_BLOCK1], 11U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 36U) + RotL64(aPrevious, 51U)) ^ (RotL64(aIngress, 11U) ^ RotL64(aCarry, 23U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = ((aWandererD + RotL64(aCross, 46U)) + RotL64(aCarry, 53U)) + 12775735908960052604U;
            aOrbiterB = (((aWandererH + RotL64(aIngress, 57U)) + RotL64(aCarry, 13U)) + 11791373812080296887U) + RotL64(aNonceByteC, 31U);
            aOrbiterE = ((aWandererB + RotL64(aScatter, 11U)) + 5537362877706057303U) + aOrbiterAssignSaltB[(((31U - aIndex) + 1725U)) & S_SALT1];
            aOrbiterI = (aWandererE + RotL64(aPrevious, 19U)) + 2023912048504189380U;
            aOrbiterD = ((aWandererI + RotL64(aCross, 53U)) + 17668828109963766893U) + RotL64(aNonceByteG, 7U);
            aOrbiterF = (aWandererG + RotL64(aIngress, 35U)) + 558908629933941224U;
            aOrbiterH = ((aWandererC + RotL64(aScatter, 5U)) + RotL64(aCarry, 37U)) + 1479633119685446888U;
            aOrbiterA = ((aWandererA + RotL64(aPrevious, 40U)) + 15460320397843364063U) + aOrbiterAssignSaltA[((aIndex + 7095U)) & S_SALT1];
            aOrbiterC = (aWandererF + RotL64(aScatter, 29U)) + 10059749397555469054U;
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 9987633811929693924U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 10087337844580228269U;
            aOrbiterE = RotL64((aOrbiterE * 13817142288940843815U), 43U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 4446204415503364254U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterI) ^ 15106063243302192717U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 1980U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 13273756657334709803U), 19U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 9430197906134676162U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 1226048679997253363U;
            aOrbiterI = RotL64((aOrbiterI * 14247538885252664127U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterH) + 10611580584157624739U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 4781U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 3137391249289641509U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 2663U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 5462682413239873181U), 27U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 9327201928815412810U) + aOrbiterUpdateSaltB[((aIndex + 5201U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 7890659377013147073U;
            aOrbiterD = RotL64((aOrbiterD * 13827717178378062047U), 5U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 10675114832750356941U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 8804440385852327267U) ^ RotL64(aNonceByteH, 29U);
            aOrbiterF = RotL64((aOrbiterF * 8520671775587260601U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 12871947817782057116U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 11015991745792051390U;
            aOrbiterH = RotL64((aOrbiterH * 17152451500505815031U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 6320437975845673731U;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 702457937087191287U;
            aOrbiterA = RotL64((aOrbiterA * 17491257114676739589U), 47U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 16629064896250312921U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterE) ^ 6054107387816339103U) ^ RotL64(aNonceByteA, 41U);
            aOrbiterC = RotL64((aOrbiterC * 6983767878966747219U), 39U);
            //
            aIngress = RotL64(aOrbiterD, 37U) ^ aOrbiterF;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterH, 13U));
            aIngress = aIngress + (RotL64(aOrbiterB, 58U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterI, 5U));
            aIngress = aIngress + RotL64(aOrbiterE, 51U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aCross, 57U) + RotL64(aOrbiterF, 60U)) + aOrbiterH) + RotL64(aCarry, 53U));
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 43U) + RotL64(aOrbiterC, 51U)) + aOrbiterI) + aWandererUpdateSaltB[(((31U - aIndex) + 4899U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aIngress, 22U) + RotL64(aOrbiterA, 11U)) + aOrbiterH) + aWandererUpdateSaltA[(((31U - aIndex) + 2344U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aScatter, 13U) + RotL64(aOrbiterI, 5U)) + aOrbiterG);
            aWandererE = aWandererE + ((RotL64(aIngress, 47U) + aOrbiterE) + RotL64(aOrbiterA, 35U));
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 27U) + RotL64(aOrbiterI, 43U)) + aOrbiterD) + RotL64(aNonceByteF, 43U));
            aWandererG = aWandererG + ((RotL64(aScatter, 36U) + aOrbiterH) + RotL64(aOrbiterB, 27U));
            aWandererH = aWandererH ^ ((RotL64(aCross, 3U) + aOrbiterC) + RotL64(aOrbiterA, 20U));
            aWandererI = aWandererI + ((((RotL64(aIngress, 53U) + aOrbiterC) + RotL64(aOrbiterH, 47U)) + RotL64(aCarry, 13U)) + RotL64(aNonceByteB, 4U));
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererB, 19U));
            aCarry = aCarry + (RotL64(aWandererD, 57U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererA, 50U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererG, 23U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererH, 35U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 51U) ^ RotL64(aNonceByteB, 60U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 8660U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 11587U)) & S_BLOCK1], 21U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 30U) ^ RotL64(aNonceByteD, 53U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 7819U)) & S_BLOCK1], 21U) ^ RotL64(aSource[((aIndex + 1320U)) & S_BLOCK1], 39U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 23U) + RotL64(aCarry, 3U)) ^ (RotL64(aIngress, 37U) + RotL64(aCross, 54U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterI = (aWandererG + RotL64(aIngress, 51U)) + 5697928251815176134U;
            aOrbiterG = ((aWandererH + RotL64(aScatter, 56U)) + 337587740689259575U) + RotL64(aNonceByteF, 31U);
            aOrbiterC = (aWandererA + RotL64(aPrevious, 13U)) + 4927686903263973950U;
            aOrbiterE = ((aWandererD + RotL64(aCross, 3U)) + 3742409032569801033U) + RotL64(aNonceByteH, 57U);
            aOrbiterH = ((aWandererI + RotL64(aPrevious, 19U)) + RotL64(aCarry, 47U)) + 1608092659172197650U;
            aOrbiterA = ((aWandererF + RotL64(aIngress, 27U)) + RotL64(aCarry, 35U)) + 15848744267145717509U;
            aOrbiterD = ((aWandererC + RotL64(aScatter, 60U)) + 15300174177963339253U) + aOrbiterAssignSaltA[((aIndex + 5641U)) & S_SALT1];
            aOrbiterF = (((aWandererB + RotL64(aCross, 39U)) + RotL64(aCarry, 13U)) + 14162868453323648628U) + aOrbiterAssignSaltB[(((31U - aIndex) + 1238U)) & S_SALT1];
            aOrbiterB = (aWandererE + RotL64(aScatter, 23U)) + 12020167069983729869U;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 16259538291658723956U) + aOrbiterUpdateSaltD[((aIndex + 8072U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 8516686212464112245U;
            aOrbiterC = RotL64((aOrbiterC * 4731296903548893627U), 53U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 3722184575520553132U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 5663609293306386784U) ^ RotL64(aNonceByteA, 54U);
            aOrbiterH = RotL64((aOrbiterH * 14364218128780764749U), 11U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 15265344442454471986U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 3050323350098829515U;
            aOrbiterD = RotL64((aOrbiterD * 5890624677162388135U), 19U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 1093356813820599238U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterF) ^ 15167726103772238440U) ^ RotL64(aNonceByteG, 25U);
            aOrbiterI = RotL64((aOrbiterI * 5719466863561311069U), 37U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterI) + 15170797965325981472U;
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 17826286701992981628U;
            aOrbiterE = RotL64((aOrbiterE * 11186808881726573677U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 14710892030473425181U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 397194787697553904U;
            aOrbiterA = RotL64((aOrbiterA * 14368930300818752833U), 23U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 1273724124862533034U) + aOrbiterUpdateSaltC[((aIndex + 1639U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 13018397560392545616U;
            aOrbiterF = RotL64((aOrbiterF * 4644812473262395329U), 57U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 9638716186445643730U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 5842U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 7255587739807843785U;
            aOrbiterB = RotL64((aOrbiterB * 6055682981584011189U), 27U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 9272350563697399628U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterD) ^ 1040729335295009339U) ^ aOrbiterUpdateSaltA[((aIndex + 7925U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 17825687660830291443U), 41U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterF, 18U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterE, 21U));
            aIngress = aIngress + (RotL64(aOrbiterA, 41U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterI, 35U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterD, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 43U) + RotL64(aOrbiterD, 34U)) + aOrbiterG) + aWandererUpdateSaltA[(((31U - aIndex) + 166U)) & S_SALT1]);
            aWandererB = aWandererB + ((RotL64(aCross, 29U) + RotL64(aOrbiterI, 3U)) + aOrbiterE);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 34U) + RotL64(aOrbiterI, 47U)) + aOrbiterF);
            aWandererD = aWandererD + ((((RotL64(aIngress, 13U) + aOrbiterA) + RotL64(aOrbiterH, 43U)) + RotL64(aCarry, 21U)) + RotL64(pNonce, 15U));
            aWandererE = aWandererE ^ ((RotL64(aScatter, 47U) + aOrbiterB) + RotL64(aOrbiterF, 19U));
            aWandererF = aWandererF + ((RotL64(aPrevious, 19U) + RotL64(aOrbiterH, 57U)) + aOrbiterD);
            aWandererG = aWandererG ^ (((RotL64(aIngress, 52U) + aOrbiterE) + RotL64(aOrbiterB, 27U)) + aWandererUpdateSaltB[((aIndex + 7819U)) & S_SALT1]);
            aWandererH = aWandererH + ((((RotL64(aCross, 23U) + aOrbiterC) + RotL64(aOrbiterH, 23U)) + RotL64(aCarry, 29U)) + RotL64(aNonceByteE, 7U));
            aWandererI = aWandererI ^ ((RotL64(aIngress, 57U) + RotL64(aOrbiterC, 14U)) + aOrbiterG);
            //
            aCarry = aCarry + (RotL64(aWandererC, 43U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererB, 10U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererG, 5U) ^ aWandererD);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererE, 51U));
            aCarry = aCarry + RotL64(aWandererA, 37U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 12U) ^ RotL64(aNonceByteB, 37U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 14334U)) & S_BLOCK1], 29U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 13498U)) & S_BLOCK1], 51U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 57U) ^ RotL64(aNonceByteD, 11U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 14526U)) & S_BLOCK1], 28U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 1680U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 29U) ^ RotL64(aIngress, 57U)) ^ (RotL64(aCross, 14U) + RotL64(aPrevious, 41U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = (aWandererA + RotL64(aScatter, 22U)) + 10336802574069791273U;
            aOrbiterI = ((aWandererB + RotL64(aCross, 11U)) + RotL64(aCarry, 53U)) + 169025388197058936U;
            aOrbiterA = ((aWandererF + RotL64(aPrevious, 47U)) + 6541354188379168846U) + aOrbiterAssignSaltB[(((31U - aIndex) + 6825U)) & S_SALT1];
            aOrbiterH = (aWandererD + RotL64(aIngress, 43U)) + 16223920526599306104U;
            aOrbiterD = (((aWandererE + RotL64(aPrevious, 51U)) + RotL64(aCarry, 29U)) + 12756613707692514808U) + RotL64(aNonceByteH, 23U);
            aOrbiterC = (((aWandererI + RotL64(aScatter, 5U)) + RotL64(aCarry, 19U)) + 5082475548176484035U) + RotL64(aNonceByteB, 57U);
            aOrbiterE = ((aWandererH + RotL64(aCross, 39U)) + 4907435526952698526U) + aOrbiterAssignSaltA[((aIndex + 6769U)) & S_SALT1];
            aOrbiterB = (aWandererC + RotL64(aIngress, 35U)) + 14236627073831834337U;
            aOrbiterG = (aWandererG + RotL64(aScatter, 60U)) + 11502511046130497584U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 3679044835550219497U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 11254838916686736746U;
            aOrbiterA = RotL64((aOrbiterA * 8631695922983532915U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 10582608424233200966U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterH) ^ 10449735026385340313U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 4731U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 7363770199734997411U), 47U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterA) + 4628253464169957835U) + RotL64(aNonceByteA, 53U);
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 17664454668473204465U;
            aOrbiterB = RotL64((aOrbiterB * 4234720298731378527U), 39U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 3798386391743884889U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterI) ^ 1379331161819246587U) ^ RotL64(aNonceByteF, 3U);
            aOrbiterG = RotL64((aOrbiterG * 13086160171095077295U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 9816600392407327227U;
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 16781971616348376878U;
            aOrbiterF = RotL64((aOrbiterF * 12503867584828289879U), 29U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 4807797577690520554U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 2613U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 2492057261148595922U;
            aOrbiterH = RotL64((aOrbiterH * 9453302540675483005U), 3U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 7909676419643119585U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 256053568910383007U;
            aOrbiterE = RotL64((aOrbiterE * 11965085163352053161U), 19U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 16179914439220412472U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 3968867762761955845U;
            aOrbiterI = RotL64((aOrbiterI * 7473632378251893139U), 53U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 7474832923901283742U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 1031U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 4736994731050735779U) ^ aOrbiterUpdateSaltD[((aIndex + 6852U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 9839654409121414047U), 11U);
            //
            aIngress = RotL64(aOrbiterF, 12U) ^ aOrbiterG;
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterB, 57U));
            aIngress = aIngress + (RotL64(aOrbiterD, 23U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterA, 53U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterC, 3U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aIngress, 5U) + aOrbiterD) + RotL64(aOrbiterH, 44U));
            aWandererB = aWandererB ^ ((RotL64(aScatter, 35U) + RotL64(aOrbiterC, 11U)) + aOrbiterA);
            aWandererC = aWandererC + (((RotL64(aPrevious, 23U) + aOrbiterI) + RotL64(aOrbiterA, 5U)) + RotL64(aCarry, 21U));
            aWandererD = aWandererD ^ ((RotL64(aCross, 39U) + aOrbiterB) + RotL64(aOrbiterH, 35U));
            aWandererE = aWandererE + ((((RotL64(aScatter, 52U) + RotL64(aOrbiterG, 27U)) + aOrbiterI) + RotL64(aNonceByteG, 17U)) + aWandererUpdateSaltB[((aIndex + 4366U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aIngress, 11U) + RotL64(aOrbiterG, 19U)) + aOrbiterB);
            aWandererG = aWandererG + ((RotL64(aCross, 47U) + aOrbiterA) + RotL64(aOrbiterE, 50U));
            aWandererH = aWandererH ^ (((RotL64(aPrevious, 29U) + RotL64(aOrbiterC, 39U)) + aOrbiterF) + RotL64(aNonceByteE, 10U));
            aWandererI = aWandererI + ((((RotL64(aScatter, 60U) + aOrbiterA) + RotL64(aOrbiterH, 23U)) + RotL64(aCarry, 47U)) + aWandererUpdateSaltA[(((31U - aIndex) + 6323U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererE, 29U) ^ aWandererB);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererF, 50U));
            aCarry = aCarry + (RotL64(aWandererI, 43U) ^ aWandererA);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererC, 3U));
            aCarry = aCarry + RotL64(aWandererG, 21U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneE[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 53U) ^ RotL64(aNonceByteB, 35U));
            aIngress = aIngress ^ (RotL64(aExpandLaneE[((aIndex + 5482U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 8733U)) & S_BLOCK1], 26U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 58U) ^ RotL64(aNonceByteD, 23U)) ^ RotL64(aNonceByteE, 13U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 15174U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 15830U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 44U) + RotL64(aIngress, 5U)) ^ (RotL64(aCarry, 57U) + RotL64(aPrevious, 23U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = (aWandererB + RotL64(aPrevious, 6U)) + 3339283916456813609U;
            aOrbiterB = (aWandererA + RotL64(aScatter, 11U)) + 11339086426180649584U;
            aOrbiterE = (((aWandererI + RotL64(aIngress, 29U)) + RotL64(aCarry, 35U)) + 16819191669329316585U) + aOrbiterAssignSaltA[(((31U - aIndex) + 5617U)) & S_SALT1];
            aOrbiterA = ((aWandererE + RotL64(aCross, 53U)) + 8361916937762630725U) + RotL64(aNonceByteG, 9U);
            aOrbiterC = ((aWandererD + RotL64(aScatter, 47U)) + RotL64(aCarry, 13U)) + 18031328374429899857U;
            aOrbiterF = (aWandererG + RotL64(aIngress, 22U)) + 18261756894092897276U;
            aOrbiterD = (((aWandererH + RotL64(aCross, 35U)) + RotL64(aCarry, 23U)) + 4250319792907645666U) + aOrbiterAssignSaltB[((aIndex + 178U)) & S_SALT1];
            aOrbiterH = (aWandererC + RotL64(aPrevious, 39U)) + 1492411503643460886U;
            aOrbiterI = ((aWandererF + RotL64(aCross, 43U)) + 17369549067879344180U) + RotL64(aNonceByteD, 19U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 7301713524358676722U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 2985193736033012535U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 775U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 7473297294949338265U), 37U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 14086975808140927408U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 10390516547834639800U;
            aOrbiterC = RotL64((aOrbiterC * 11441293212275890819U), 23U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 18205555540941493267U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 16967799565443938873U;
            aOrbiterD = RotL64((aOrbiterD * 3009081009044782443U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 9209505304067579944U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterB) ^ 3522631966146762306U) ^ aOrbiterUpdateSaltA[((aIndex + 2714U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 3441982898533162599U), 43U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterH) + 8811497120829041188U) + RotL64(aNonceByteH, 27U);
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 14707301680850257294U;
            aOrbiterI = RotL64((aOrbiterI * 11383709499376464085U), 19U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 10080595991787801029U) + RotL64(aNonceByteC, 7U);
            aOrbiterG = ((aOrbiterG ^ aOrbiterC) ^ 6822892187784299166U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 6307U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 7417016898027778287U), 51U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 1981637172055758689U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterD) ^ 16463077485583119324U) ^ aOrbiterUpdateSaltB[((aIndex + 4635U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 2876782050665869121U), 3U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 8383837717361569465U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 2788511294985017326U;
            aOrbiterF = RotL64((aOrbiterF * 2809163242875130677U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 3529607472855930041U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 8850940802020173766U;
            aOrbiterB = RotL64((aOrbiterB * 7821450253655655943U), 47U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterA, 47U);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterD, 21U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterH, 24U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterG, 37U));
            aIngress = aIngress + RotL64(aOrbiterI, 43U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aScatter, 23U) + RotL64(aOrbiterI, 57U)) + aOrbiterF);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 27U) + RotL64(aOrbiterA, 19U)) + aOrbiterI);
            aWandererC = aWandererC + ((((RotL64(aIngress, 60U) + aOrbiterC) + RotL64(aOrbiterE, 14U)) + RotL64(aCarry, 23U)) + RotL64(aNonceByteA, 11U));
            aWandererD = aWandererD ^ ((RotL64(aCross, 3U) + RotL64(aOrbiterC, 23U)) + aOrbiterG);
            aWandererE = aWandererE + (((RotL64(aScatter, 39U) + aOrbiterI) + RotL64(aOrbiterE, 39U)) + RotL64(aCarry, 41U));
            aWandererF = aWandererF ^ (((RotL64(aCross, 51U) + RotL64(aOrbiterI, 47U)) + aOrbiterB) + aWandererUpdateSaltA[((aIndex + 2704U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aPrevious, 12U) + RotL64(aOrbiterI, 35U)) + aOrbiterD) + aWandererUpdateSaltB[(((31U - aIndex) + 1252U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aIngress, 19U) + aOrbiterG) + RotL64(aOrbiterD, 27U));
            aWandererI = aWandererI + (((RotL64(aScatter, 47U) + aOrbiterB) + RotL64(aOrbiterH, 4U)) + RotL64(aNonceByteF, 56U));
            //
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererB, 14U));
            aCarry = aCarry + (RotL64(aWandererA, 57U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererC, 41U) ^ aWandererF);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 35U));
            aCarry = aCarry + RotL64(aWandererD, 23U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneF[S_BLOCK1 - aIndex] = aIngress;
        }
    }
}

void TwistExpander_Nine_0006::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aOrbiterI = 0;

    std::uint64_t aWandererA = 0; std::uint64_t aWandererB = 0; std::uint64_t aWandererC = 0; std::uint64_t aWandererD = 0;
    std::uint64_t aWandererE = 0; std::uint64_t aWandererF = 0; std::uint64_t aWandererG = 0; std::uint64_t aWandererH = 0;
    std::uint64_t aWandererI = 0;

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
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 57U) ^ RotL64(aNonceByteB, 27U)) ^ RotL64(aNonceByteC, 13U));
            aIngress = aIngress ^ (RotL64(aSource[((aIndex + 14348U)) & S_BLOCK1], 46U) ^ RotL64(aSource[((aIndex + 6011U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 6U) ^ RotL64(aNonceByteE, 35U)) ^ RotL64(aNonceByteF, 19U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 7902U)) & S_BLOCK1], 51U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 14627U)) & S_BLOCK1], 27U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 22U) ^ RotL64(aCross, 43U)) + (RotL64(aIngress, 57U) + RotL64(aCarry, 5U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = ((aWandererF + RotL64(aCross, 47U)) + RotL64(aCarry, 23U)) + 17264605017518259932U;
            aOrbiterC = (aWandererB + RotL64(aScatter, 56U)) + 15209184354580778643U;
            aOrbiterD = ((aWandererA + RotL64(aPrevious, 51U)) + 3299527965014731384U) + aOrbiterAssignSaltB[(((31U - aIndex) + 4325U)) & S_SALT1];
            aOrbiterB = (aWandererC + RotL64(aIngress, 37U)) + 16293096431816127821U;
            aOrbiterH = ((aWandererI + RotL64(aCross, 11U)) + 11031983436878828337U) + RotL64(aNonceByteC, 11U);
            aOrbiterG = ((aWandererG + RotL64(aPrevious, 27U)) + RotL64(aCarry, 3U)) + 9188018632448236358U;
            aOrbiterI = ((aWandererE + RotL64(aIngress, 23U)) + RotL64(aCarry, 53U)) + 13420816400363406556U;
            aOrbiterE = ((aWandererH + RotL64(aScatter, 41U)) + 2485063384097917101U) + RotL64(aNonceByteG, 19U);
            aOrbiterF = ((aWandererD + RotL64(aIngress, 6U)) + 3089135816938128264U) + aOrbiterAssignSaltA[(((31U - aIndex) + 4890U)) & S_SALT1];
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 10730544971770435788U) + RotL64(aNonceByteH, 18U);
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 10431767565618874806U;
            aOrbiterD = RotL64((aOrbiterD * 4723078464590561545U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 14883796491656899074U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 13465877783538483706U;
            aOrbiterG = RotL64((aOrbiterG * 14311686051108108503U), 19U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 13322163435314643713U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 3307316600284371955U) ^ aOrbiterUpdateSaltC[((aIndex + 4777U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 12337846092069506365U), 57U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterG) + 4950101626975919939U) + aOrbiterUpdateSaltB[((aIndex + 5045U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 2596253994220103666U;
            aOrbiterF = RotL64((aOrbiterF * 7181706961838582889U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 17961706029559914243U;
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 10321902557977495175U;
            aOrbiterA = RotL64((aOrbiterA * 16189559888625084711U), 27U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 18146616411403012772U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 8414050129421955787U) ^ RotL64(aNonceByteA, 39U);
            aOrbiterB = RotL64((aOrbiterB * 14879448948196182863U), 23U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 11739172334166341121U;
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 7936637782633487291U;
            aOrbiterI = RotL64((aOrbiterI * 14940929920543800413U), 43U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 3160044627483874242U) + aOrbiterUpdateSaltD[((aIndex + 4174U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 16816384076887379704U;
            aOrbiterC = RotL64((aOrbiterC * 5052772186568301951U), 5U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 8101560104988710226U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 6311U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 8851416379738817624U;
            aOrbiterH = RotL64((aOrbiterH * 16767420038937389027U), 37U);
            //
            aIngress = RotL64(aOrbiterB, 56U) ^ aOrbiterE;
            aIngress = aIngress + (RotL64(aOrbiterD, 27U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterF, 51U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterH, 23U));
            aIngress = aIngress + RotL64(aOrbiterG, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aPrevious, 51U) + RotL64(aOrbiterI, 57U)) + aOrbiterC) + RotL64(aNonceByteF, 51U));
            aWandererB = aWandererB ^ (((RotL64(aScatter, 12U) + aOrbiterF) + RotL64(aOrbiterH, 51U)) + aWandererUpdateSaltA[(((31U - aIndex) + 6041U)) & S_SALT1]);
            aWandererC = aWandererC + ((RotL64(aCross, 29U) + aOrbiterE) + RotL64(aOrbiterG, 12U));
            aWandererD = aWandererD ^ ((RotL64(aIngress, 39U) + aOrbiterE) + RotL64(aOrbiterH, 23U));
            aWandererE = aWandererE + (((RotL64(aScatter, 35U) + aOrbiterF) + RotL64(aOrbiterA, 29U)) + RotL64(aCarry, 29U));
            aWandererF = aWandererF ^ ((RotL64(aIngress, 57U) + RotL64(aOrbiterD, 5U)) + aOrbiterF);
            aWandererG = aWandererG + ((((RotL64(aPrevious, 22U) + aOrbiterH) + RotL64(aOrbiterB, 19U)) + RotL64(aCarry, 51U)) + RotL64(aNonceByteE, 59U));
            aWandererH = aWandererH ^ ((RotL64(aCross, 43U) + RotL64(aOrbiterB, 36U)) + aOrbiterI);
            aWandererI = aWandererI + (((RotL64(aPrevious, 47U) + RotL64(aOrbiterB, 43U)) + aOrbiterD) + aWandererUpdateSaltB[((aIndex + 6519U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererA, 3U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererE, 39U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererG, 23U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererD, 51U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererH, 6U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 11U) ^ RotL64(aNonceByteB, 28U)) ^ RotL64(aNonceByteC, 19U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 5833U)) & S_BLOCK1], 57U) ^ RotL64(aSource[((aIndex + 15132U)) & S_BLOCK1], 37U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 43U) ^ RotL64(aNonceByteE, 57U)) ^ RotL64(aNonceByteF, 3U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 4034U)) & S_BLOCK1], 14U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 10633U)) & S_BLOCK1], 23U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 54U) + RotL64(aCarry, 27U)) ^ (RotL64(aCross, 39U) + RotL64(aIngress, 5U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterC = (((aWandererE + RotL64(aPrevious, 48U)) + RotL64(aCarry, 57U)) + 5697928251815176134U) + RotL64(aNonceByteH, 61U);
            aOrbiterF = (aWandererF + RotL64(aScatter, 27U)) + 337587740689259575U;
            aOrbiterG = (aWandererI + RotL64(aCross, 57U)) + 4927686903263973950U;
            aOrbiterD = (aWandererG + RotL64(aIngress, 13U)) + 3742409032569801033U;
            aOrbiterH = ((aWandererB + RotL64(aScatter, 43U)) + RotL64(aCarry, 37U)) + 1608092659172197650U;
            aOrbiterE = (((aWandererH + RotL64(aPrevious, 53U)) + 15848744267145717509U) + aOrbiterAssignSaltB[(((31U - aIndex) + 56U)) & S_SALT1]) + RotL64(aNonceByteC, 59U);
            aOrbiterI = (aWandererD + RotL64(aIngress, 37U)) + 15300174177963339253U;
            aOrbiterA = (((aWandererC + RotL64(aCross, 19U)) + RotL64(aCarry, 47U)) + 14162868453323648628U) + aOrbiterAssignSaltA[(((31U - aIndex) + 2933U)) & S_SALT1];
            aOrbiterB = (aWandererA + RotL64(aPrevious, 6U)) + 12020167069983729869U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 16259538291658723956U;
            aOrbiterG = (((aOrbiterG ^ aOrbiterC) ^ 8516686212464112245U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 4125U)) & S_SALT1]) ^ RotL64(aNonceByteF, 41U);
            aOrbiterG = RotL64((aOrbiterG * 4731296903548893627U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 3722184575520553132U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 5663609293306386784U;
            aOrbiterH = RotL64((aOrbiterH * 14364218128780764749U), 43U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 15265344442454471986U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterE) ^ 3050323350098829515U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 6355U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 5890624677162388135U), 5U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 1093356813820599238U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 2352U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 15167726103772238440U;
            aOrbiterA = RotL64((aOrbiterA * 5719466863561311069U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 15170797965325981472U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 17826286701992981628U;
            aOrbiterB = RotL64((aOrbiterB * 11186808881726573677U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 14710892030473425181U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 397194787697553904U;
            aOrbiterC = RotL64((aOrbiterC * 14368930300818752833U), 35U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 1273724124862533034U;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 13018397560392545616U;
            aOrbiterD = RotL64((aOrbiterD * 4644812473262395329U), 27U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterD) + 9638716186445643730U) + RotL64(aNonceByteD, 19U);
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 7255587739807843785U;
            aOrbiterE = RotL64((aOrbiterE * 6055682981584011189U), 39U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 9272350563697399628U) + aOrbiterUpdateSaltB[((aIndex + 5768U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 1040729335295009339U;
            aOrbiterF = RotL64((aOrbiterF * 17825687660830291443U), 23U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterE, 18U);
            aIngress = aIngress + (RotL64(aOrbiterB, 23U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterA, 51U) ^ aOrbiterD);
            aIngress = aIngress + (RotL64(aOrbiterH, 35U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterC, 57U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aPrevious, 29U) + aOrbiterG) + RotL64(aOrbiterI, 24U));
            aWandererB = aWandererB ^ (((RotL64(aIngress, 13U) + aOrbiterD) + RotL64(aOrbiterH, 47U)) + RotL64(aNonceByteG, 6U));
            aWandererC = aWandererC + ((((RotL64(aScatter, 5U) + aOrbiterA) + RotL64(aOrbiterF, 29U)) + RotL64(aCarry, 41U)) + aWandererUpdateSaltA[(((31U - aIndex) + 5677U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aCross, 58U) + aOrbiterG) + RotL64(aOrbiterE, 57U)) + aWandererUpdateSaltB[((aIndex + 6809U)) & S_SALT1]);
            aWandererE = aWandererE + ((RotL64(aScatter, 19U) + RotL64(aOrbiterG, 34U)) + aOrbiterC);
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 37U) + RotL64(aOrbiterG, 11U)) + aOrbiterA) + RotL64(aNonceByteA, 49U));
            aWandererG = aWandererG + (((RotL64(aCross, 47U) + aOrbiterF) + RotL64(aOrbiterC, 51U)) + RotL64(aCarry, 21U));
            aWandererH = aWandererH ^ ((RotL64(aIngress, 42U) + aOrbiterI) + RotL64(aOrbiterB, 3U));
            aWandererI = aWandererI + ((RotL64(aPrevious, 51U) + RotL64(aOrbiterA, 43U)) + aOrbiterD);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererC, 3U));
            aCarry = aCarry + (RotL64(aWandererB, 35U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererH, 18U) ^ aWandererE);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererI, 51U));
            aCarry = aCarry + RotL64(aWandererD, 13U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 57U) ^ RotL64(aNonceByteB, 3U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 14914U)) & S_BLOCK1], 26U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 5732U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 53U) ^ RotL64(aNonceByteD, 42U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 15153U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 13718U)) & S_BLOCK1], 23U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 37U) ^ RotL64(aCarry, 51U)) ^ (RotL64(aPrevious, 5U) + RotL64(aCross, 24U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = (aWandererF + RotL64(aIngress, 57U)) + 11274974230580265396U;
            aOrbiterB = (aWandererG + RotL64(aCross, 19U)) + 16658438747342741547U;
            aOrbiterE = (aWandererD + RotL64(aPrevious, 27U)) + 16612986966106053844U;
            aOrbiterI = ((aWandererA + RotL64(aScatter, 42U)) + RotL64(aCarry, 13U)) + 9329502236843231290U;
            aOrbiterD = (((aWandererH + RotL64(aPrevious, 35U)) + RotL64(aCarry, 5U)) + 14088261356708344656U) + RotL64(aNonceByteH, 13U);
            aOrbiterF = ((aWandererB + RotL64(aScatter, 53U)) + 13692608802007789581U) + RotL64(aNonceByteE, 15U);
            aOrbiterH = (aWandererE + RotL64(aCross, 11U)) + 6824473946645682398U;
            aOrbiterA = (((aWandererI + RotL64(aIngress, 23U)) + RotL64(aCarry, 51U)) + 2072915876348570040U) + aOrbiterAssignSaltA[((aIndex + 7828U)) & S_SALT1];
            aOrbiterC = ((aWandererC + RotL64(aCross, 6U)) + 7420507753044460759U) + aOrbiterAssignSaltB[(((31U - aIndex) + 6603U)) & S_SALT1];
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 4677557318688502593U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 15081678577055628459U;
            aOrbiterE = RotL64((aOrbiterE * 16659305295251177155U), 53U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 7026792817486507482U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 14871665922943969918U;
            aOrbiterG = RotL64((aOrbiterG * 694073180313083145U), 47U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 6807734532159292872U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterB) ^ 17882797335141303280U) ^ RotL64(aNonceByteF, 56U);
            aOrbiterI = RotL64((aOrbiterI * 15439872930381050291U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 9233542707022629190U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 1205501586581350876U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 2268U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 2596053290311090589U), 35U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 10878718669747466677U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 8066049063548639241U;
            aOrbiterD = RotL64((aOrbiterD * 3031382633089381605U), 3U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterC) + 861295180226875235U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 5019U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 9134969787937288583U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 525U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 7565008208670843555U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 6726642007159809594U;
            aOrbiterH = (((aOrbiterH ^ aOrbiterA) ^ 8061661744643240470U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 5610U)) & S_SALT1]) ^ RotL64(aNonceByteC, 55U);
            aOrbiterH = RotL64((aOrbiterH * 6703498926835391813U), 57U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 13541412083111962884U;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 8617442758729315637U;
            aOrbiterA = RotL64((aOrbiterA * 15471862889276160953U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 16884403561131293362U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 9490680911678221233U;
            aOrbiterC = RotL64((aOrbiterC * 15988763830018001033U), 13U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterI, 5U);
            aIngress = aIngress + (RotL64(aOrbiterC, 60U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterD, 35U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterA, 57U));
            aIngress = aIngress + RotL64(aOrbiterE, 43U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aPrevious, 52U) + aOrbiterF) + RotL64(aOrbiterC, 18U)) + RotL64(aNonceByteG, 35U));
            aWandererB = aWandererB ^ (((RotL64(aScatter, 39U) + RotL64(aOrbiterA, 35U)) + aOrbiterF) + aWandererUpdateSaltA[((aIndex + 4709U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aCross, 23U) + aOrbiterE) + RotL64(aOrbiterC, 57U)) + RotL64(aNonceByteD, 43U));
            aWandererD = aWandererD ^ (((RotL64(aIngress, 27U) + RotL64(aOrbiterI, 43U)) + aOrbiterE) + aWandererUpdateSaltB[((aIndex + 6184U)) & S_SALT1]);
            aWandererE = aWandererE + ((RotL64(aCross, 57U) + RotL64(aOrbiterH, 3U)) + aOrbiterF);
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 13U) + RotL64(aOrbiterD, 11U)) + aOrbiterB);
            aWandererG = aWandererG + (((RotL64(aScatter, 6U) + aOrbiterD) + RotL64(aOrbiterI, 39U)) + RotL64(aCarry, 57U));
            aWandererH = aWandererH ^ ((RotL64(aIngress, 19U) + RotL64(aOrbiterI, 48U)) + aOrbiterF);
            aWandererI = aWandererI + (((RotL64(aPrevious, 35U) + RotL64(aOrbiterG, 29U)) + aOrbiterB) + RotL64(aCarry, 43U));
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererD, 12U));
            aCarry = aCarry + (RotL64(aWandererI, 19U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererC, 5U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererH, 29U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererA, 47U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 27U) ^ RotL64(aNonceByteB, 47U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 4104U)) & S_BLOCK1], 6U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 8762U)) & S_BLOCK1], 37U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 46U) ^ RotL64(aNonceByteD, 13U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 14025U)) & S_BLOCK1], 23U) ^ RotL64(aSource[((aIndex + 14467U)) & S_BLOCK1], 5U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 6U) ^ RotL64(aCarry, 41U)) ^ (RotL64(aIngress, 21U) + RotL64(aCross, 53U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterI = (((aWandererI + RotL64(aIngress, 58U)) + RotL64(aCarry, 51U)) + 12775735908960052604U) + aOrbiterAssignSaltA[((aIndex + 4841U)) & S_SALT1];
            aOrbiterG = (aWandererG + RotL64(aCross, 35U)) + 11791373812080296887U;
            aOrbiterC = (aWandererD + RotL64(aPrevious, 51U)) + 5537362877706057303U;
            aOrbiterE = (((aWandererA + RotL64(aScatter, 27U)) + RotL64(aCarry, 23U)) + 2023912048504189380U) + RotL64(aNonceByteC, 5U);
            aOrbiterH = (aWandererF + RotL64(aIngress, 47U)) + 17668828109963766893U;
            aOrbiterA = (aWandererB + RotL64(aPrevious, 13U)) + 558908629933941224U;
            aOrbiterD = (((aWandererC + RotL64(aCross, 5U)) + 1479633119685446888U) + aOrbiterAssignSaltB[(((31U - aIndex) + 8051U)) & S_SALT1]) + RotL64(aNonceByteE, 49U);
            aOrbiterF = (aWandererH + RotL64(aScatter, 41U)) + 15460320397843364063U;
            aOrbiterB = ((aWandererE + RotL64(aPrevious, 20U)) + RotL64(aCarry, 39U)) + 10059749397555469054U;
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 9987633811929693924U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterI) ^ 10087337844580228269U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 5650U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 13817142288940843815U), 13U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 4446204415503364254U;
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 15106063243302192717U;
            aOrbiterH = RotL64((aOrbiterH * 13273756657334709803U), 57U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterH) + 9430197906134676162U) + aOrbiterUpdateSaltB[((aIndex + 3767U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 1226048679997253363U;
            aOrbiterD = RotL64((aOrbiterD * 14247538885252664127U), 41U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 10611580584157624739U;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 3137391249289641509U;
            aOrbiterI = RotL64((aOrbiterI * 5462682413239873181U), 29U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterI) + 9327201928815412810U;
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 7890659377013147073U;
            aOrbiterE = RotL64((aOrbiterE * 13827717178378062047U), 37U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 10675114832750356941U) + RotL64(aNonceByteH, 38U);
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 8804440385852327267U;
            aOrbiterA = RotL64((aOrbiterA * 8520671775587260601U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 12871947817782057116U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 11015991745792051390U;
            aOrbiterF = RotL64((aOrbiterF * 17152451500505815031U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 6320437975845673731U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterH) ^ 702457937087191287U) ^ aOrbiterUpdateSaltA[((aIndex + 5732U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 17491257114676739589U), 51U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 16629064896250312921U;
            aOrbiterG = (((aOrbiterG ^ aOrbiterD) ^ 6054107387816339103U) ^ aOrbiterUpdateSaltC[((aIndex + 2887U)) & S_SALT1]) ^ RotL64(pNonce, 31U);
            aOrbiterG = RotL64((aOrbiterG * 6983767878966747219U), 47U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterD, 60U);
            aIngress = aIngress + (RotL64(aOrbiterB, 39U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterG, 29U));
            aIngress = aIngress + (RotL64(aOrbiterA, 47U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterF, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 6U) + RotL64(aOrbiterG, 10U)) + aOrbiterC);
            aWandererB = aWandererB + (((RotL64(aScatter, 23U) + aOrbiterB) + RotL64(aOrbiterG, 27U)) + RotL64(aCarry, 23U));
            aWandererC = aWandererC ^ ((RotL64(aCross, 13U) + RotL64(aOrbiterD, 39U)) + aOrbiterI);
            aWandererD = aWandererD + (((RotL64(aIngress, 57U) + RotL64(aOrbiterH, 35U)) + aOrbiterF) + RotL64(aNonceByteF, 11U));
            aWandererE = aWandererE ^ ((RotL64(aScatter, 52U) + RotL64(aOrbiterG, 18U)) + aOrbiterD);
            aWandererF = aWandererF + ((RotL64(aIngress, 19U) + aOrbiterE) + RotL64(aOrbiterG, 23U));
            aWandererG = aWandererG ^ ((((RotL64(aPrevious, 47U) + aOrbiterH) + RotL64(aOrbiterC, 3U)) + RotL64(aNonceByteG, 9U)) + aWandererUpdateSaltA[(((31U - aIndex) + 5923U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aCross, 27U) + aOrbiterB) + RotL64(aOrbiterI, 47U)) + RotL64(aCarry, 3U));
            aWandererI = aWandererI ^ (((RotL64(aScatter, 39U) + RotL64(aOrbiterA, 53U)) + aOrbiterE) + aWandererUpdateSaltB[(((31U - aIndex) + 849U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererA, 19U) ^ aWandererH);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererF, 5U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererB, 14U));
            aCarry = aCarry + (RotL64(aWandererI, 43U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererG, 47U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 43U) ^ RotL64(aNonceByteB, 18U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 6401U)) & S_BLOCK1], 51U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 8270U)) & S_BLOCK1], 27U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 54U) ^ RotL64(aNonceByteD, 3U)) ^ RotL64(aNonceByteE, 37U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 3935U)) & S_BLOCK1], 29U) ^ RotL64(aExpandLaneA[((aIndex + 11378U)) & S_BLOCK1], 21U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 10U) ^ RotL64(aCarry, 35U)) + (RotL64(aPrevious, 51U) ^ RotL64(aCross, 23U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = ((aWandererE + RotL64(aPrevious, 13U)) + RotL64(aCarry, 19U)) + 10336802574069791273U;
            aOrbiterI = (((aWandererI + RotL64(aScatter, 30U)) + RotL64(aCarry, 47U)) + 169025388197058936U) + RotL64(aNonceByteH, 13U);
            aOrbiterA = (aWandererD + RotL64(aIngress, 3U)) + 6541354188379168846U;
            aOrbiterH = ((aWandererG + RotL64(aCross, 37U)) + 16223920526599306104U) + aOrbiterAssignSaltA[((aIndex + 2995U)) & S_SALT1];
            aOrbiterD = (aWandererF + RotL64(aScatter, 47U)) + 12756613707692514808U;
            aOrbiterC = (aWandererH + RotL64(aCross, 43U)) + 5082475548176484035U;
            aOrbiterE = ((aWandererC + RotL64(aPrevious, 19U)) + 4907435526952698526U) + aOrbiterAssignSaltB[((aIndex + 4982U)) & S_SALT1];
            aOrbiterB = (((aWandererA + RotL64(aIngress, 51U)) + RotL64(aCarry, 11U)) + 14236627073831834337U) + RotL64(aNonceByteC, 10U);
            aOrbiterG = (aWandererB + RotL64(aCross, 58U)) + 11502511046130497584U;
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 3679044835550219497U) + aOrbiterUpdateSaltB[((aIndex + 2420U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 11254838916686736746U) ^ RotL64(aNonceByteF, 9U);
            aOrbiterA = RotL64((aOrbiterA * 8631695922983532915U), 43U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 10582608424233200966U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 10449735026385340313U;
            aOrbiterC = RotL64((aOrbiterC * 7363770199734997411U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 4628253464169957835U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 17664454668473204465U;
            aOrbiterB = RotL64((aOrbiterB * 4234720298731378527U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 3798386391743884889U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 1379331161819246587U;
            aOrbiterG = RotL64((aOrbiterG * 13086160171095077295U), 27U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 9816600392407327227U) + aOrbiterUpdateSaltC[((aIndex + 7954U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterD) ^ 16781971616348376878U) ^ RotL64(aNonceByteG, 35U);
            aOrbiterF = RotL64((aOrbiterF * 12503867584828289879U), 13U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 4807797577690520554U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 1293U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 2492057261148595922U;
            aOrbiterH = RotL64((aOrbiterH * 9453302540675483005U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 7909676419643119585U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 256053568910383007U;
            aOrbiterE = RotL64((aOrbiterE * 11965085163352053161U), 3U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 16179914439220412472U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 3968867762761955845U;
            aOrbiterI = RotL64((aOrbiterI * 7473632378251893139U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 7474832923901283742U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 4736994731050735779U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 2744U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 9839654409121414047U), 23U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterC, 14U);
            aIngress = aIngress + (RotL64(aOrbiterB, 57U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterG, 51U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterI, 43U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterE, 11U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((((RotL64(aIngress, 42U) + RotL64(aOrbiterA, 14U)) + aOrbiterD) + RotL64(aNonceByteD, 43U)) + aWandererUpdateSaltB[((aIndex + 5397U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aCross, 53U) + aOrbiterI) + RotL64(aOrbiterB, 43U)) + RotL64(aCarry, 53U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 37U) + RotL64(aOrbiterG, 27U)) + aOrbiterI);
            aWandererD = aWandererD + ((RotL64(aPrevious, 47U) + RotL64(aOrbiterB, 51U)) + aOrbiterD);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 4U) + RotL64(aOrbiterF, 23U)) + aOrbiterI);
            aWandererF = aWandererF + ((((RotL64(aScatter, 29U) + RotL64(aOrbiterH, 19U)) + aOrbiterE) + RotL64(aCarry, 23U)) + aWandererUpdateSaltA[(((31U - aIndex) + 5897U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 21U) + aOrbiterB) + RotL64(aOrbiterE, 39U));
            aWandererH = aWandererH + ((RotL64(aPrevious, 57U) + RotL64(aOrbiterA, 60U)) + aOrbiterC);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 13U) + aOrbiterA) + RotL64(aOrbiterH, 35U)) + RotL64(aNonceByteB, 11U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 41U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererG, 29U) ^ aWandererF);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererE, 60U));
            aCarry = aCarry + (RotL64(aWandererI, 21U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererA, 51U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneE[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 21U) ^ RotL64(aNonceByteB, 51U)) ^ RotL64(aNonceByteC, 13U));
            aIngress = aIngress ^ (RotL64(aExpandLaneE[((aIndex + 8938U)) & S_BLOCK1], 4U) ^ RotL64(aExpandLaneD[((aIndex + 9171U)) & S_BLOCK1], 41U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 39U) ^ RotL64(aNonceByteE, 47U)) ^ RotL64(aNonceByteF, 27U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 10243U)) & S_BLOCK1], 4U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 12493U)) & S_BLOCK1], 19U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 22U) ^ RotL64(aIngress, 5U)) + (RotL64(aPrevious, 35U) ^ RotL64(aCarry, 57U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = ((aWandererA + RotL64(aScatter, 4U)) + 3339283916456813609U) + RotL64(aNonceByteE, 5U);
            aOrbiterB = ((aWandererB + RotL64(aPrevious, 19U)) + RotL64(aCarry, 21U)) + 11339086426180649584U;
            aOrbiterE = (aWandererE + RotL64(aCross, 39U)) + 16819191669329316585U;
            aOrbiterA = ((aWandererH + RotL64(aIngress, 35U)) + 8361916937762630725U) + aOrbiterAssignSaltA[(((31U - aIndex) + 2726U)) & S_SALT1];
            aOrbiterC = ((aWandererG + RotL64(aScatter, 27U)) + RotL64(aCarry, 51U)) + 18031328374429899857U;
            aOrbiterF = (aWandererF + RotL64(aPrevious, 57U)) + 18261756894092897276U;
            aOrbiterD = ((((aWandererD + RotL64(aIngress, 47U)) + RotL64(aCarry, 11U)) + 4250319792907645666U) + aOrbiterAssignSaltB[((aIndex + 7799U)) & S_SALT1]) + RotL64(aNonceByteG, 26U);
            aOrbiterH = (aWandererC + RotL64(aCross, 12U)) + 1492411503643460886U;
            aOrbiterI = (aWandererI + RotL64(aIngress, 23U)) + 17369549067879344180U;
            //
            aOrbiterG = ((aOrbiterG + aOrbiterB) + 7301713524358676722U) + aOrbiterUpdateSaltA[((aIndex + 6149U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 2985193736033012535U) ^ aOrbiterUpdateSaltB[((aIndex + 1293U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 7473297294949338265U), 5U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 14086975808140927408U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 10390516547834639800U;
            aOrbiterC = RotL64((aOrbiterC * 11441293212275890819U), 35U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 18205555540941493267U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 16967799565443938873U;
            aOrbiterD = RotL64((aOrbiterD * 3009081009044782443U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 9209505304067579944U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 3522631966146762306U;
            aOrbiterH = RotL64((aOrbiterH * 3441982898533162599U), 21U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 8811497120829041188U;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 14707301680850257294U;
            aOrbiterI = RotL64((aOrbiterI * 11383709499376464085U), 53U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 10080595991787801029U) + aOrbiterUpdateSaltD[((aIndex + 203U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterC) ^ 6822892187784299166U) ^ RotL64(aNonceByteA, 53U);
            aOrbiterG = RotL64((aOrbiterG * 7417016898027778287U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 1981637172055758689U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 16463077485583119324U;
            aOrbiterA = RotL64((aOrbiterA * 2876782050665869121U), 57U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 8383837717361569465U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 2788511294985017326U) ^ aOrbiterUpdateSaltC[((aIndex + 5499U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 2809163242875130677U), 27U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 3529607472855930041U) + RotL64(aNonceByteD, 17U);
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 8850940802020173766U;
            aOrbiterB = RotL64((aOrbiterB * 7821450253655655943U), 39U);
            //
            aIngress = RotL64(aOrbiterA, 27U) ^ aOrbiterD;
            aIngress = aIngress + (RotL64(aOrbiterH, 47U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterB, 6U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterI, 3U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterE, 11U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aIngress, 3U) + RotL64(aOrbiterE, 5U)) + aOrbiterC) + RotL64(aNonceByteH, 23U));
            aWandererB = aWandererB ^ ((RotL64(aScatter, 47U) + RotL64(aOrbiterI, 46U)) + aOrbiterD);
            aWandererC = aWandererC + ((RotL64(aPrevious, 43U) + RotL64(aOrbiterF, 41U)) + aOrbiterA);
            aWandererD = aWandererD ^ (((RotL64(aCross, 20U) + aOrbiterI) + RotL64(aOrbiterF, 21U)) + aWandererUpdateSaltA[(((31U - aIndex) + 3353U)) & S_SALT1]);
            aWandererE = aWandererE + ((((RotL64(aIngress, 29U) + aOrbiterG) + RotL64(aOrbiterC, 53U)) + RotL64(aCarry, 39U)) + aWandererUpdateSaltB[(((31U - aIndex) + 3400U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterB, 28U)) + aOrbiterH);
            aWandererG = aWandererG + (((RotL64(aScatter, 51U) + aOrbiterH) + RotL64(aOrbiterC, 57U)) + RotL64(aCarry, 29U));
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 14U) + aOrbiterI) + RotL64(aOrbiterE, 37U));
            aWandererI = aWandererI + (((RotL64(aScatter, 39U) + aOrbiterF) + RotL64(aOrbiterB, 13U)) + RotL64(aNonceByteC, 51U));
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 26U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererD, 43U));
            aCarry = aCarry + (RotL64(aWandererE, 23U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererB, 11U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererG, 19U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneF[S_BLOCK1 - aIndex] = aIngress;
        }
    }
};

