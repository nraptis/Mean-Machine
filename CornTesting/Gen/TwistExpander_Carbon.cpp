#include "TwistExpander_Carbon.hpp"
#include "TwistFunctional.hpp"
#include "TwistMasking.hpp"
#include "TwistMix64.hpp"
#include "TwistSnow.hpp"
#include "TwistMemory.hpp"
#include "TwistCryptoGenerator.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmSalt.hpp"

#include <cstring>

TwistExpander_Carbon::TwistExpander_Carbon()
: TwistExpander() {
    std::memcpy(mSBoxA, kSBoxA, sizeof(mSBoxA));
    std::memcpy(mSBoxB, kSBoxB, sizeof(mSBoxB));
    std::memcpy(mSBoxC, kSBoxC, sizeof(mSBoxC));
    std::memcpy(mSBoxD, kSBoxD, sizeof(mSBoxD));
    std::memcpy(mSBoxE, kSBoxE, sizeof(mSBoxE));
    std::memcpy(mSBoxF, kSBoxF, sizeof(mSBoxF));
    std::memcpy(mSBoxG, kSBoxG, sizeof(mSBoxG));
    std::memcpy(mSBoxH, kSBoxH, sizeof(mSBoxH));
    std::memcpy(mSaltA, kSaltA, sizeof(mSaltA));
    std::memcpy(mSaltB, kSaltB, sizeof(mSaltB));
    std::memcpy(mSaltC, kSaltC, sizeof(mSaltC));
    std::memcpy(mSaltD, kSaltD, sizeof(mSaltD));
    std::memcpy(mSaltE, kSaltE, sizeof(mSaltE));
    std::memcpy(mSaltF, kSaltF, sizeof(mSaltF));
    std::memcpy(mSaltG, kSaltG, sizeof(mSaltG));
    std::memcpy(mSaltH, kSaltH, sizeof(mSaltH));
    mDomainConstantPublicIngress = kDomainConstantPublicIngress;
    mDomainConstantPrivateIngress = kDomainConstantPrivateIngress;
    mDomainConstantCrossIngress = kDomainConstantCrossIngress;
    std::memcpy(mDomainSaltKeyBoxA, kDomainSaltKeyBoxA, sizeof(mDomainSaltKeyBoxA));
    std::memcpy(mDomainSaltKeyBoxB, kDomainSaltKeyBoxB, sizeof(mDomainSaltKeyBoxB));
    std::memcpy(mDomainSaltKeyBoxC, kDomainSaltKeyBoxC, sizeof(mDomainSaltKeyBoxC));
    std::memcpy(mDomainSaltKeyBoxD, kDomainSaltKeyBoxD, sizeof(mDomainSaltKeyBoxD));
    std::memcpy(mDomainSaltKeyBoxE, kDomainSaltKeyBoxE, sizeof(mDomainSaltKeyBoxE));
    std::memcpy(mDomainSaltKeyBoxF, kDomainSaltKeyBoxF, sizeof(mDomainSaltKeyBoxF));
    std::memcpy(mDomainSaltMaskBoxA, kDomainSaltMaskBoxA, sizeof(mDomainSaltMaskBoxA));
    std::memcpy(mDomainSaltMaskBoxB, kDomainSaltMaskBoxB, sizeof(mDomainSaltMaskBoxB));
    std::memcpy(mDomainSaltMaskBoxC, kDomainSaltMaskBoxC, sizeof(mDomainSaltMaskBoxC));
    std::memcpy(mDomainSaltMaskBoxD, kDomainSaltMaskBoxD, sizeof(mDomainSaltMaskBoxD));
    std::memcpy(mDomainSaltMaskBoxE, kDomainSaltMaskBoxE, sizeof(mDomainSaltMaskBoxE));
    std::memcpy(mDomainSaltMaskBoxF, kDomainSaltMaskBoxF, sizeof(mDomainSaltMaskBoxF));
    std::memcpy(mDomainSaltWandererA, kDomainSaltWandererA, sizeof(mDomainSaltWandererA));
    std::memcpy(mDomainSaltWandererB, kDomainSaltWandererB, sizeof(mDomainSaltWandererB));
    std::memcpy(mDomainSaltWandererC, kDomainSaltWandererC, sizeof(mDomainSaltWandererC));
    std::memcpy(mDomainSaltWandererD, kDomainSaltWandererD, sizeof(mDomainSaltWandererD));
    std::memcpy(mDomainSaltWandererE, kDomainSaltWandererE, sizeof(mDomainSaltWandererE));
    std::memcpy(mDomainSaltWandererF, kDomainSaltWandererF, sizeof(mDomainSaltWandererF));
    std::memcpy(mDomainSaltOrbiterA, kDomainSaltOrbiterA, sizeof(mDomainSaltOrbiterA));
    std::memcpy(mDomainSaltOrbiterB, kDomainSaltOrbiterB, sizeof(mDomainSaltOrbiterB));
    std::memcpy(mDomainSaltOrbiterC, kDomainSaltOrbiterC, sizeof(mDomainSaltOrbiterC));
    std::memcpy(mDomainSaltOrbiterD, kDomainSaltOrbiterD, sizeof(mDomainSaltOrbiterD));
    std::memcpy(mDomainSaltOrbiterE, kDomainSaltOrbiterE, sizeof(mDomainSaltOrbiterE));
    std::memcpy(mDomainSaltOrbiterF, kDomainSaltOrbiterF, sizeof(mDomainSaltOrbiterF));
    std::memcpy(mDomainSaltPrismA, kDomainSaltPrismA, sizeof(mDomainSaltPrismA));
    std::memcpy(mDomainSaltPrismB, kDomainSaltPrismB, sizeof(mDomainSaltPrismB));
    std::memcpy(mDomainSaltPrismC, kDomainSaltPrismC, sizeof(mDomainSaltPrismC));
    std::memcpy(mDomainSaltPrismD, kDomainSaltPrismD, sizeof(mDomainSaltPrismD));
    std::memcpy(mDomainSaltPrismE, kDomainSaltPrismE, sizeof(mDomainSaltPrismE));
    std::memcpy(mDomainSaltPrismF, kDomainSaltPrismF, sizeof(mDomainSaltPrismF));
    std::memcpy(mDomainSaltSourceA, kDomainSaltSourceA, sizeof(mDomainSaltSourceA));
    std::memcpy(mDomainSaltSourceB, kDomainSaltSourceB, sizeof(mDomainSaltSourceB));
    std::memcpy(mDomainSaltSourceC, kDomainSaltSourceC, sizeof(mDomainSaltSourceC));
    std::memcpy(mDomainSaltSourceD, kDomainSaltSourceD, sizeof(mDomainSaltSourceD));
    std::memcpy(mDomainSaltSourceE, kDomainSaltSourceE, sizeof(mDomainSaltSourceE));
    std::memcpy(mDomainSaltSourceF, kDomainSaltSourceF, sizeof(mDomainSaltSourceF));
}

void TwistExpander_Carbon::KDF(TwistDomain pDomain,
                                std::uint64_t pDomainConstantPublicIngress,
                                std::uint64_t pDomainConstantPrivateIngress,
                                std::uint64_t pDomainConstantCrossIngress,
                                std::uint64_t *pDomainSaltA,
                                std::uint64_t *pDomainSaltB,
                                std::uint64_t *pDomainSaltC,
                                std::uint64_t *pDomainSaltD,
                                std::uint64_t *pDomainSaltE,
                                std::uint64_t *pDomainSaltF) {
    TwistExpander::KDF(pDomain, pDomainConstantPublicIngress, pDomainConstantPrivateIngress, pDomainConstantCrossIngress, pDomainSaltA, pDomainSaltB, pDomainSaltC, pDomainSaltD, pDomainSaltE, pDomainSaltF);
    TwistWorkSpace *pWorkspace = mWorkspace;
    std::uint8_t *pSource = mSource;
    if ((pWorkspace == nullptr) || (pSource == nullptr)) { return; }
    (void)pDomain;
    (void)pDomainSaltA;
    (void)pDomainSaltB;
    (void)pDomainSaltC;
    (void)pDomainSaltD;
    (void)pDomainSaltE;
    (void)pDomainSaltF;
    (void)pDomainConstantPublicIngress;
    (void)pDomainConstantPrivateIngress;
    (void)pDomainConstantCrossIngress;

    {
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkspace->mOperationLaneA;
    std::uint64_t aPublicIngress = 0, aPublicIngressDomainWord = 0, aPublicPrevious = 0, aPublicScatter = 0;
    std::uint64_t aPrivateIngress = 0, aPrivateIngressDomainWord = 0, aPrivatePrevious = 0, aPrivateScatter = 0;
    std::uint64_t aCrossIngress = 0, aCrossIngressDomainWord = 0;
    std::uint64_t aCarry = 0;
    std::uint64_t aOrbitA = 0, aOrbitB = 0, aOrbitC = 0, aOrbitD = 0, aOrbitE = 0, aOrbitF = 0;
    std::uint64_t aWandererA = 0, aWandererB = 0, aWandererC = 0, aWandererD = 0, aWandererE = 0, aWandererF = 0;
    std::size_t aPlugKeyA = 0, aPlugKeyB = 0;
    std::uint64_t aPlugSalt0 = 0, aPlugSalt1 = 0, aPlugSalt2 = 0, aPlugSalt3 = 0, aPlugSalt4 = 0, aPlugSalt5 = 0;
    std::uint64_t aPlugSalt6 = 0, aPlugSalt7 = 0, aPlugSalt8 = 0, aPlugSalt9 = 0, aPlugSalt10 = 0, aPlugSalt11 = 0;

    aPublicIngressDomainWord = mDomainSaltSourceA[((0U) & static_cast<std::uint64_t>(S_SALT1))];
    aPrivateIngressDomainWord = mDomainSaltSourceB[((0U) & static_cast<std::uint64_t>(S_SALT1))];
    aCrossIngressDomainWord = mDomainSaltSourceC[((0U) & static_cast<std::uint64_t>(S_SALT1))];
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPublicPrevious = aPublicIngress;
        aPrivatePrevious = aPrivateIngress;
        aPublicIngress = RotL64(pSource[aIndex], 47U) ^ RotL64(pSource[(aIndex + 1U)], 41U);
        aPublicIngress = aPublicIngress + (RotL64(pSource[(aIndex + 17U)], 11U) ^ RotL64(pSource[S_BLOCK1 - aIndex], 23U));
        aPublicIngress = aPublicIngress ^ aPublicIngressDomainWord;
        aPublicIngress = TwistMix64::DiffuseA(aPublicIngress);
        aPrivateIngress = RotL64(pSource[(aIndex + 3U)], 13U) ^ RotL64(pSource[(aIndex + 29U)], 21U);
        aPrivateIngress = aPrivateIngress + (RotL64(pSource[(16383U - aIndex + 7U)], 53U) ^ RotL64(pSource[(16383U - aIndex + 23U)], 41U));
        aPrivateIngress = aPrivateIngress ^ aPrivateIngressDomainWord;
        aPrivateIngress = TwistMix64::DiffuseB(aPrivateIngress);
        aCrossIngress = RotL64(pSource[S_BLOCK1 - aIndex], 29U) ^ RotL64(pSource[(16383U - aIndex + 1U)], 47U);
        aCrossIngress = aCrossIngress + (RotL64(pSource[(aIndex + 11U)], 41U) ^ RotL64(pSource[(16383U - aIndex + 31U)], 9U));
        aCrossIngress = aCrossIngress ^ aCrossIngressDomainWord;
        aCrossIngress = TwistMix64::DiffuseC(aCrossIngress);
        //
        aPublicScatter = TwistMix64::DiffuseC((RotL64(aPublicIngress, 31U) ^ RotL64(aPublicPrevious, 11U)) + (RotL64(aCrossIngress, 47U) ^ RotL64(aPublicIngress, 19U)));
        aPrivateScatter = TwistMix64::DiffuseA((RotL64(aPrivateIngress, 35U) ^ RotL64(aPrivatePrevious, 27U)) + (RotL64(aCrossIngress, 51U) ^ RotL64(aCarry, 5U)));
        //
        aOrbitA = aWandererE;
        aOrbitA = aOrbitA + RotL64(aPrivateIngress, 53U);
        aOrbitA = aOrbitA + 5697928251815176134ULL;
        aOrbitB = aWandererA;
        aOrbitB = aOrbitB + RotL64(aPrivateScatter, 51U);
        aOrbitB = aOrbitB + 337587740689259575ULL;
        aOrbitC = aWandererF;
        aOrbitC = aOrbitC + RotL64(aPrivatePrevious, 17U);
        aOrbitC = aOrbitC + 4927686903263973950ULL;
        aOrbitC = aOrbitC + mDomainSaltSourceA[((31U - aIndex + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + mDomainSaltSourceB[((aIndex + 7U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererC;
        aOrbitD = aOrbitD + RotL64(aCarry, 45U);
        aOrbitD = aOrbitD + 3742409032569801033ULL;
        aOrbitD = aOrbitD + mDomainSaltSourceA[((31U - aIndex + 5U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + mDomainSaltSourceB[((aIndex + 29U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aWandererB;
        aOrbitE = aOrbitE + RotL64(aPrivateIngress, 29U);
        aOrbitE = aOrbitE + 1608092659172197650ULL;
        aOrbitF = aWandererD;
        aOrbitF = aOrbitF + RotL64(aPrivateScatter, 43U);
        aOrbitF = aOrbitF + 15848744267145717509ULL;
        //
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aCrossIngress, 29U) ^ aPublicScatter);
        aPlugSalt0 = mDomainSaltSourceC[((aPlugKeyA + 5U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aPublicIngress, 17U) ^ aPublicScatter);
        aPlugSalt1 = mDomainSaltSourceD[((aPlugKeyB + 1U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA + aOrbitB;
        aOrbitA = aOrbitA + 15300174177963339253ULL;
        aOrbitA = aOrbitA + aPlugSalt0;
        aOrbitD = aOrbitD + aOrbitA;
        aOrbitD = aOrbitD + 14162868453323648628ULL;
        aOrbitD = aOrbitD + aPlugSalt1;
        aOrbitD = RotL64(aOrbitD * 6302504235542433263ULL, 16U);
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aPublicPrevious, 37U) ^ aPublicScatter);
        aPlugSalt2 = mDomainSaltSourceD[((aPlugKeyB + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aPublicScatter, 41U) ^ aPublicIngress);
        aPlugSalt3 = mDomainSaltSourceC[((aPlugKeyA + 19U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB + aOrbitC;
        aOrbitB = aOrbitB + 12020167069983729869ULL;
        aOrbitB = aOrbitB + aPlugSalt2;
        aOrbitE = aOrbitE + aOrbitB;
        aOrbitE = aOrbitE + 16259538291658723956ULL;
        aOrbitE = aOrbitE + aPlugSalt3;
        aOrbitE = RotL64(aOrbitE * 6262123350804980887ULL, 21U);
        //
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aPublicScatter, 13U) ^ aPublicPrevious);
        aPlugSalt4 = mDomainSaltSourceC[((aPlugKeyA + 29U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aPublicScatter, 19U) ^ aCrossIngress);
        aPlugSalt5 = mDomainSaltSourceD[((aPlugKeyB + 3U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + aOrbitD;
        aOrbitC = aOrbitC + 8516686212464112245ULL;
        aOrbitC = aOrbitC + aPlugSalt4;
        aOrbitF = aOrbitF + aOrbitC;
        aOrbitF = aOrbitF + 3722184575520553132ULL;
        aOrbitF = aOrbitF + aPlugSalt5;
        aOrbitF = RotL64(aOrbitF * 8349884892252470343ULL, 32U);
        //
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aPublicIngress, 11U) ^ aCrossIngress);
        aPlugSalt6 = mDomainSaltSourceD[((aPlugKeyB + 15U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aPublicIngress, 7U) ^ aPublicPrevious);
        aPlugSalt7 = mDomainSaltSourceC[((aPlugKeyA + 13U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + aOrbitE;
        aOrbitD = aOrbitD + 5663609293306386784ULL;
        aOrbitD = aOrbitD + aPlugSalt6;
        aOrbitA = aOrbitA + aOrbitD;
        aOrbitA = aOrbitA + 15265344442454471986ULL;
        aOrbitA = aOrbitA + aPlugSalt7;
        aOrbitA = RotL64(aOrbitA * 15597397493542010979ULL, 29U);
        //
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aPublicPrevious, 43U) ^ aCrossIngress);
        aPlugSalt8 = mDomainSaltSourceC[((aPlugKeyA + 11U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aCrossIngress, 31U) ^ aPublicIngress);
        aPlugSalt9 = mDomainSaltSourceD[((aPlugKeyB + 9U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aOrbitE + aOrbitF;
        aOrbitE = aOrbitE + 3050323350098829515ULL;
        aOrbitE = aOrbitE + aPlugSalt8;
        aOrbitB = aOrbitB + aOrbitE;
        aOrbitB = aOrbitB + 1093356813820599238ULL;
        aOrbitB = aOrbitB + aPlugSalt9;
        aOrbitB = RotL64(aOrbitB * 7039855035597231687ULL, 24U);
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aCrossIngress, 23U) ^ aPublicPrevious);
        aPlugSalt10 = mDomainSaltSourceD[((aPlugKeyB + 17U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aPublicPrevious, 53U) ^ aPublicIngress);
        aPlugSalt11 = mDomainSaltSourceC[((aPlugKeyA + 7U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = aOrbitF + aOrbitA;
        aOrbitF = aOrbitF + 15167726103772238440ULL;
        aOrbitF = aOrbitF + aPlugSalt10;
        aOrbitC = aOrbitC + aOrbitF;
        aOrbitC = aOrbitC + 15170797965325981472ULL;
        aOrbitC = aOrbitC + aPlugSalt11;
        aOrbitC = RotL64(aOrbitC * 1024636833977775953ULL, 63U);
        //
        aPrivateIngress = TwistMix64::DiffuseC((aOrbitA ^ RotL64(aOrbitB, 23U)) + (aOrbitC ^ RotL64(aOrbitD, 31U)) + (RotL64(aOrbitE, 37U) ^ aOrbitF) + aPrivateScatter + aCarry);
        aWorkLaneA[aIndex] = aPrivateIngress;
        //
        aWandererA = aWandererA + RotL64(aPrivateIngress, 29U);
        aWandererA = aWandererA + RotL64(aPrivatePrevious, 19U);
        aWandererA = aWandererA + aOrbitA;
        aWandererA = aWandererA + mDomainSaltSourceE[((aIndex + 11U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererB = aWandererB + RotL64(aPrivateIngress, 57U);
        aWandererB = aWandererB + RotL64(aPrivateScatter, 31U);
        aWandererB = aWandererB + aOrbitE;
        aWandererC = aWandererC + aOrbitD;
        aWandererC = aWandererC + aOrbitF;
        aWandererD = aWandererD + RotL64(aPrivateIngress, 11U);
        aWandererD = aWandererD + RotL64(aPrivatePrevious, 41U);
        aWandererD = aWandererD + aOrbitF;
        aWandererD = aWandererD + mDomainSaltSourceF[((31U - aIndex + 21U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererE = aWandererE + RotL64(aPrivateIngress, 7U);
        aWandererE = aWandererE + RotL64(aPrivateScatter, 45U);
        aWandererE = aWandererE + aOrbitD;
        aWandererF = aWandererF + aOrbitF;
        aWandererF = aWandererF + aOrbitA;
        //
        aCarry = aCarry + (RotL64(aWandererA, 11U) ^ aWandererD) + (RotL64(aWandererB, 51U) ^ aWandererE) + (RotL64(aWandererC, 23U) ^ aWandererF) + RotL64(aPrivateIngress, 37U);
        aCarry = RotL64(aCarry * 6055682981584011189ULL, 19U);
        aCarry = aCarry ^ ShiftR64(aCarry, 37U);
    }
    aPublicIngressDomainWord = mDomainSaltSourceA[((1U) & static_cast<std::uint64_t>(S_SALT1))];
    aPrivateIngressDomainWord = mDomainSaltSourceB[((3U) & static_cast<std::uint64_t>(S_SALT1))];
    aCrossIngressDomainWord = mDomainSaltSourceC[((5U) & static_cast<std::uint64_t>(S_SALT1))];
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPublicPrevious = aPublicIngress;
        aPrivatePrevious = aPrivateIngress;
        aPublicIngress = RotL64(aOperationLaneA[aIndex], 53U) ^ RotL64(aOperationLaneA[(aIndex + 1U)], 7U);
        aPublicIngress = aPublicIngress + (RotL64(aOperationLaneA[(aIndex + 17U)], 21U) ^ RotL64(aOperationLaneA[S_BLOCK1 - aIndex], 35U));
        aPublicIngress = aPublicIngress ^ aPublicIngressDomainWord;
        aPublicIngress = TwistMix64::DiffuseA(aPublicIngress);
        aPrivateIngress = RotL64(aOperationLaneA[(aIndex + 3U)], 31U) ^ RotL64(aOperationLaneA[(aIndex + 29U)], 19U);
        aPrivateIngress = aPrivateIngress + (RotL64(aOperationLaneA[(16383U - aIndex + 7U)], 9U) ^ RotL64(aOperationLaneA[(16383U - aIndex + 23U)], 47U));
        aPrivateIngress = aPrivateIngress ^ aPrivateIngressDomainWord;
        aPrivateIngress = TwistMix64::DiffuseB(aPrivateIngress);
        aCrossIngress = RotL64(aOperationLaneA[S_BLOCK1 - aIndex], 41U) ^ RotL64(aOperationLaneA[(16383U - aIndex + 1U)], 21U);
        aCrossIngress = aCrossIngress + (RotL64(aOperationLaneA[(aIndex + 11U)], 51U) ^ RotL64(aOperationLaneA[(16383U - aIndex + 31U)], 13U));
        aCrossIngress = aCrossIngress ^ aCrossIngressDomainWord;
        aCrossIngress = TwistMix64::DiffuseC(aCrossIngress);
        //
        aPublicScatter = TwistMix64::DiffuseA((RotL64(aPublicIngress, 53U) ^ RotL64(aPublicPrevious, 29U)) + (RotL64(aCrossIngress, 13U) ^ RotL64(aPublicIngress, 43U)));
        aPrivateScatter = TwistMix64::DiffuseC((RotL64(aPrivateIngress, 37U) ^ RotL64(aPrivatePrevious, 5U)) + (RotL64(aCrossIngress, 57U) ^ RotL64(aCarry, 23U)));
        //
        aOrbitA = aWandererD;
        aOrbitA = aOrbitA + RotL64(aPrivateIngress, 53U);
        aOrbitA = aOrbitA + 5697928251815176134ULL;
        aOrbitB = aWandererB;
        aOrbitB = aOrbitB + RotL64(aPrivatePrevious, 11U);
        aOrbitB = aOrbitB + 337587740689259575ULL;
        aOrbitC = aWandererA;
        aOrbitC = aOrbitC + RotL64(aCarry, 41U);
        aOrbitC = aOrbitC + 4927686903263973950ULL;
        aOrbitC = aOrbitC + mDomainSaltSourceA[((aIndex + 15U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + mDomainSaltSourceB[((31U - aIndex + 31U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererC;
        aOrbitD = aOrbitD + RotL64(aPrivateScatter, 17U);
        aOrbitD = aOrbitD + 3742409032569801033ULL;
        aOrbitD = aOrbitD + mDomainSaltSourceA[((aIndex + 29U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + mDomainSaltSourceB[((31U - aIndex + 11U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aWandererE;
        aOrbitE = aOrbitE + RotL64(aPrivateIngress, 43U);
        aOrbitE = aOrbitE + 1608092659172197650ULL;
        aOrbitF = aWandererF;
        aOrbitF = aOrbitF + RotL64(aPrivatePrevious, 45U);
        aOrbitF = aOrbitF + 15848744267145717509ULL;
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aCrossIngress, 43U) ^ aPublicIngress);
        aPlugSalt0 = mDomainSaltSourceD[((aPlugKeyB + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aCrossIngress, 11U) ^ aPublicScatter);
        aPlugSalt1 = mDomainSaltSourceC[((aPlugKeyA + 7U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA + aOrbitB;
        aOrbitA = aOrbitA + 15300174177963339253ULL;
        aOrbitA = aOrbitA + aPlugSalt0;
        aOrbitD = aOrbitD + aOrbitA;
        aOrbitD = aOrbitD + 14162868453323648628ULL;
        aOrbitD = aOrbitD + aPlugSalt1;
        aOrbitD = RotL64(aOrbitD * 6302504235542433263ULL, 21U);
        //
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aPublicIngress, 41U) ^ aPublicPrevious);
        aPlugSalt2 = mDomainSaltSourceC[((aPlugKeyA + 3U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aCrossIngress, 17U) ^ aPublicPrevious);
        aPlugSalt3 = mDomainSaltSourceD[((aPlugKeyB + 15U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + aOrbitD;
        aOrbitC = aOrbitC + 12020167069983729869ULL;
        aOrbitC = aOrbitC + aPlugSalt2;
        aOrbitF = aOrbitF + aOrbitC;
        aOrbitF = aOrbitF + 16259538291658723956ULL;
        aOrbitF = aOrbitF + aPlugSalt3;
        aOrbitF = RotL64(aOrbitF * 6262123350804980887ULL, 24U);
        //
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aPublicPrevious, 29U) ^ aPublicIngress);
        aPlugSalt4 = mDomainSaltSourceD[((aPlugKeyB + 19U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aPublicScatter, 19U) ^ aCrossIngress);
        aPlugSalt5 = mDomainSaltSourceC[((aPlugKeyA + 5U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aOrbitE + aOrbitF;
        aOrbitE = aOrbitE + 8516686212464112245ULL;
        aOrbitE = aOrbitE + aPlugSalt4;
        aOrbitB = aOrbitB + aOrbitE;
        aOrbitB = aOrbitB + 3722184575520553132ULL;
        aOrbitB = aOrbitB + aPlugSalt5;
        aOrbitB = RotL64(aOrbitB * 8349884892252470343ULL, 43U);
        //
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aPublicScatter, 13U) ^ aPublicPrevious);
        aPlugSalt6 = mDomainSaltSourceC[((aPlugKeyA + 1U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aPublicIngress, 53U) ^ aPublicScatter);
        aPlugSalt7 = mDomainSaltSourceD[((aPlugKeyB + 17U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB + aOrbitC;
        aOrbitB = aOrbitB + 5663609293306386784ULL;
        aOrbitB = aOrbitB + aPlugSalt6;
        aOrbitE = aOrbitE + aOrbitB;
        aOrbitE = aOrbitE + 15265344442454471986ULL;
        aOrbitE = aOrbitE + aPlugSalt7;
        aOrbitE = RotL64(aOrbitE * 15597397493542010979ULL, 48U);
        //
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aPublicPrevious, 37U) ^ aPublicScatter);
        aPlugSalt8 = mDomainSaltSourceD[((aPlugKeyB + 11U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aPublicIngress, 23U) ^ aCrossIngress);
        aPlugSalt9 = mDomainSaltSourceC[((aPlugKeyA + 29U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + aOrbitE;
        aOrbitD = aOrbitD + 3050323350098829515ULL;
        aOrbitD = aOrbitD + aPlugSalt8;
        aOrbitA = aOrbitA + aOrbitD;
        aOrbitA = aOrbitA + 1093356813820599238ULL;
        aOrbitA = aOrbitA + aPlugSalt9;
        aOrbitA = RotL64(aOrbitA * 7039855035597231687ULL, 37U);
        //
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aPublicPrevious, 7U) ^ aCrossIngress);
        aPlugSalt10 = mDomainSaltSourceC[((aPlugKeyA + 9U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aPublicScatter, 31U) ^ aPublicIngress);
        aPlugSalt11 = mDomainSaltSourceD[((aPlugKeyB + 13U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = aOrbitF + aOrbitA;
        aOrbitF = aOrbitF + 15167726103772238440ULL;
        aOrbitF = aOrbitF + aPlugSalt10;
        aOrbitC = aOrbitC + aOrbitF;
        aOrbitC = aOrbitC + 15170797965325981472ULL;
        aOrbitC = aOrbitC + aPlugSalt11;
        aOrbitC = RotL64(aOrbitC * 1024636833977775953ULL, 32U);
        //
        aPrivateIngress = TwistMix64::DiffuseC((RotL64(aOrbitA, 37U) ^ aOrbitD) + (aOrbitB ^ RotL64(aOrbitE, 29U)) + (RotL64(aOrbitC, 31U) ^ aOrbitF) + aPrivateScatter + aCarry);
        aWorkLaneB[aIndex] = aPrivateIngress;
        //
        aWandererA = aWandererA + RotL64(aPrivateIngress, 43U);
        aWandererA = aWandererA + RotL64(aPrivatePrevious, 31U);
        aWandererA = aWandererA + aOrbitC;
        aWandererA = aWandererA + mDomainSaltSourceE[((aIndex + 9U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererB = aWandererB + RotL64(aPrivateIngress, 7U);
        aWandererB = aWandererB + RotL64(aPrivateScatter, 11U);
        aWandererB = aWandererB + aOrbitE;
        aWandererC = aWandererC + aOrbitF;
        aWandererC = aWandererC + aOrbitB;
        aWandererD = aWandererD + RotL64(aPrivateIngress, 41U);
        aWandererD = aWandererD + RotL64(aPrivatePrevious, 17U);
        aWandererD = aWandererD + aOrbitD;
        aWandererD = aWandererD + mDomainSaltSourceF[((31U - aIndex + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererE = aWandererE + RotL64(aPrivateIngress, 37U);
        aWandererE = aWandererE + RotL64(aPrivateScatter, 13U);
        aWandererE = aWandererE + aOrbitA;
        aWandererF = aWandererF + aOrbitF;
        aWandererF = aWandererF + aOrbitA;
        //
        aCarry = aCarry + (aWandererA ^ RotL64(aWandererE, 11U)) + (aWandererB ^ RotL64(aWandererF, 43U)) + (aWandererC ^ RotL64(aWandererD, 41U)) + RotL64(aPrivateIngress, 29U);
        aCarry = RotL64(aCarry * 6055682981584011189ULL, 31U);
        aCarry = aCarry ^ ShiftR64(aCarry, 33U);
    }
    aPublicIngressDomainWord = mDomainSaltSourceA[((2U) & static_cast<std::uint64_t>(S_SALT1))];
    aPrivateIngressDomainWord = mDomainSaltSourceB[((6U) & static_cast<std::uint64_t>(S_SALT1))];
    aCrossIngressDomainWord = mDomainSaltSourceC[((10U) & static_cast<std::uint64_t>(S_SALT1))];
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPublicPrevious = aPublicIngress;
        aPrivatePrevious = aPrivateIngress;
        aPublicIngress = RotL64(aWorkLaneA[aIndex], 49U) ^ RotL64(aWorkLaneA[(aIndex + 1U)], 13U);
        aPublicIngress = aPublicIngress + (RotL64(aWorkLaneA[(aIndex + 17U)], 35U) ^ RotL64(aWorkLaneA[S_BLOCK1 - aIndex], 27U));
        aPublicIngress = aPublicIngress ^ aPublicIngressDomainWord;
        aPublicIngress = TwistMix64::DiffuseA(aPublicIngress);
        aPrivateIngress = RotL64(aWorkLaneA[(aIndex + 3U)], 49U) ^ RotL64(aWorkLaneA[(aIndex + 29U)], 7U);
        aPrivateIngress = aPrivateIngress + (RotL64(aWorkLaneA[(16383U - aIndex + 7U)], 21U) ^ RotL64(aWorkLaneA[(16383U - aIndex + 23U)], 43U));
        aPrivateIngress = aPrivateIngress ^ aPrivateIngressDomainWord;
        aPrivateIngress = TwistMix64::DiffuseB(aPrivateIngress);
        aCrossIngress = RotL64(aWorkLaneA[S_BLOCK1 - aIndex], 21U) ^ RotL64(aWorkLaneA[(16383U - aIndex + 1U)], 5U);
        aCrossIngress = aCrossIngress + (RotL64(aWorkLaneA[(aIndex + 11U)], 31U) ^ RotL64(aWorkLaneA[(16383U - aIndex + 31U)], 49U));
        aCrossIngress = aCrossIngress ^ aCrossIngressDomainWord;
        aCrossIngress = TwistMix64::DiffuseC(aCrossIngress);
        //
        aPublicScatter = TwistMix64::DiffuseA((RotL64(aPublicIngress, 49U) ^ RotL64(aPublicPrevious, 41U)) + (RotL64(aCrossIngress, 7U) ^ RotL64(aPublicIngress, 29U)));
        aPrivateScatter = TwistMix64::DiffuseA((RotL64(aPrivateIngress, 31U) ^ RotL64(aPrivatePrevious, 51U)) + (RotL64(aCrossIngress, 29U) ^ RotL64(aCarry, 11U)));
        //
        aOrbitA = aWandererF;
        aOrbitA = aOrbitA + RotL64(aPrivateIngress, 13U);
        aOrbitA = aOrbitA + 5697928251815176134ULL;
        aOrbitB = aWandererA;
        aOrbitB = aOrbitB + RotL64(aPrivateScatter, 43U);
        aOrbitB = aOrbitB + 337587740689259575ULL;
        aOrbitC = aWandererD;
        aOrbitC = aOrbitC + RotL64(aPrivatePrevious, 57U);
        aOrbitC = aOrbitC + 4927686903263973950ULL;
        aOrbitC = aOrbitC + mDomainSaltSourceA[((31U - aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + mDomainSaltSourceB[((aIndex + 3U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererE;
        aOrbitD = aOrbitD + RotL64(aCarry, 41U);
        aOrbitD = aOrbitD + 3742409032569801033ULL;
        aOrbitD = aOrbitD + mDomainSaltSourceA[((31U - aIndex + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + mDomainSaltSourceB[((aIndex + 13U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aWandererB;
        aOrbitE = aOrbitE + RotL64(aPrivateIngress, 35U);
        aOrbitE = aOrbitE + 1608092659172197650ULL;
        aOrbitF = aWandererC;
        aOrbitF = aOrbitF + RotL64(aPrivateScatter, 29U);
        aOrbitF = aOrbitF + 15848744267145717509ULL;
        //
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aPublicIngress, 11U) ^ aPublicPrevious);
        aPlugSalt0 = mDomainSaltSourceC[((aPlugKeyA + 13U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aPublicScatter, 53U) ^ aCrossIngress);
        aPlugSalt1 = mDomainSaltSourceD[((aPlugKeyB + 9U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA + aOrbitF;
        aOrbitA = aOrbitA + 15300174177963339253ULL;
        aOrbitA = aOrbitA + aPlugSalt0;
        aOrbitD = aOrbitD + aOrbitA;
        aOrbitD = aOrbitD + 14162868453323648628ULL;
        aOrbitD = aOrbitD + aPlugSalt1;
        aOrbitD = RotL64(aOrbitD * 6302504235542433263ULL, 48U);
        //
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aPublicPrevious, 43U) ^ aPublicIngress);
        aPlugSalt2 = mDomainSaltSourceD[((aPlugKeyB + 15U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aPublicPrevious, 31U) ^ aPublicScatter);
        aPlugSalt3 = mDomainSaltSourceC[((aPlugKeyA + 11U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = aOrbitF + aOrbitE;
        aOrbitF = aOrbitF + 12020167069983729869ULL;
        aOrbitF = aOrbitF + aPlugSalt2;
        aOrbitC = aOrbitC + aOrbitF;
        aOrbitC = aOrbitC + 16259538291658723956ULL;
        aOrbitC = aOrbitC + aPlugSalt3;
        aOrbitC = RotL64(aOrbitC * 6262123350804980887ULL, 7U);
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aCrossIngress, 37U) ^ aPublicScatter);
        aPlugSalt4 = mDomainSaltSourceC[((aPlugKeyA + 3U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aCrossIngress, 7U) ^ aPublicIngress);
        aPlugSalt5 = mDomainSaltSourceD[((aPlugKeyB + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aOrbitE + aOrbitD;
        aOrbitE = aOrbitE + 8516686212464112245ULL;
        aOrbitE = aOrbitE + aPlugSalt4;
        aOrbitB = aOrbitB + aOrbitE;
        aOrbitB = aOrbitB + 3722184575520553132ULL;
        aOrbitB = aOrbitB + aPlugSalt5;
        aOrbitB = RotL64(aOrbitB * 8349884892252470343ULL, 51U);
        //
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aPublicIngress, 29U) ^ aCrossIngress);
        aPlugSalt6 = mDomainSaltSourceD[((aPlugKeyB + 29U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aPublicIngress, 41U) ^ aPublicScatter);
        aPlugSalt7 = mDomainSaltSourceC[((aPlugKeyA + 17U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + aOrbitC;
        aOrbitD = aOrbitD + 5663609293306386784ULL;
        aOrbitD = aOrbitD + aPlugSalt6;
        aOrbitA = aOrbitA + aOrbitD;
        aOrbitA = aOrbitA + 15265344442454471986ULL;
        aOrbitA = aOrbitA + aPlugSalt7;
        aOrbitA = RotL64(aOrbitA * 15597397493542010979ULL, 57U);
        //
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aCrossIngress, 19U) ^ aPublicPrevious);
        aPlugSalt8 = mDomainSaltSourceC[((aPlugKeyA + 5U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aPublicScatter, 13U) ^ aPublicIngress);
        aPlugSalt9 = mDomainSaltSourceD[((aPlugKeyB + 19U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + aOrbitB;
        aOrbitC = aOrbitC + 3050323350098829515ULL;
        aOrbitC = aOrbitC + aPlugSalt8;
        aOrbitF = aOrbitF + aOrbitC;
        aOrbitF = aOrbitF + 1093356813820599238ULL;
        aOrbitF = aOrbitF + aPlugSalt9;
        aOrbitF = RotL64(aOrbitF * 7039855035597231687ULL, 40U);
        //
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aPublicPrevious, 23U) ^ aCrossIngress);
        aPlugSalt10 = mDomainSaltSourceD[((aPlugKeyB + 1U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aPublicScatter, 17U) ^ aPublicPrevious);
        aPlugSalt11 = mDomainSaltSourceC[((aPlugKeyA + 7U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB + aOrbitA;
        aOrbitB = aOrbitB + 15167726103772238440ULL;
        aOrbitB = aOrbitB + aPlugSalt10;
        aOrbitE = aOrbitE + aOrbitB;
        aOrbitE = aOrbitE + 15170797965325981472ULL;
        aOrbitE = aOrbitE + aPlugSalt11;
        aOrbitE = RotL64(aOrbitE * 1024636833977775953ULL, 32U);
        //
        aPrivateIngress = TwistMix64::DiffuseC((aOrbitA ^ RotL64(aOrbitE, 31U)) + (RotL64(aOrbitB, 43U) ^ aOrbitF) + (RotL64(aOrbitC, 37U) ^ aOrbitD) + aPrivateScatter + aCarry);
        aWorkLaneC[aIndex] = aPrivateIngress;
        //
        aWandererA = aWandererA + RotL64(aPrivateIngress, 11U);
        aWandererA = aWandererA + RotL64(aPrivatePrevious, 7U);
        aWandererA = aWandererA + aOrbitD;
        aWandererA = aWandererA + mDomainSaltSourceE[((aIndex + 21U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererB = aWandererB + RotL64(aPrivateIngress, 57U);
        aWandererB = aWandererB + RotL64(aPrivateScatter, 29U);
        aWandererB = aWandererB + aOrbitA;
        aWandererC = aWandererC + aOrbitD;
        aWandererC = aWandererC + aOrbitB;
        aWandererD = aWandererD + RotL64(aPrivateIngress, 45U);
        aWandererD = aWandererD + RotL64(aPrivatePrevious, 19U);
        aWandererD = aWandererD + aOrbitC;
        aWandererD = aWandererD + mDomainSaltSourceF[((31U - aIndex + 1U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererE = aWandererE + RotL64(aPrivateIngress, 13U);
        aWandererE = aWandererE + RotL64(aPrivateScatter, 23U);
        aWandererE = aWandererE + aOrbitB;
        aWandererF = aWandererF + aOrbitB;
        aWandererF = aWandererF + aOrbitA;
        //
        aCarry = aCarry + (RotL64(aWandererA, 51U) ^ aWandererF) + (aWandererB ^ RotL64(aWandererD, 43U)) + (aWandererC ^ RotL64(aWandererE, 57U)) + RotL64(aPrivateIngress, 29U);
        aCarry = RotL64(aCarry * 6055682981584011189ULL, 11U);
        aCarry = aCarry ^ ShiftR64(aCarry, 33U);
    }
    aPublicIngressDomainWord = mDomainSaltSourceA[((3U) & static_cast<std::uint64_t>(S_SALT1))];
    aPrivateIngressDomainWord = mDomainSaltSourceB[((9U) & static_cast<std::uint64_t>(S_SALT1))];
    aCrossIngressDomainWord = mDomainSaltSourceC[((15U) & static_cast<std::uint64_t>(S_SALT1))];
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPublicPrevious = aPublicIngress;
        aPrivatePrevious = aPrivateIngress;
        aPublicIngress = RotL64(aWorkLaneB[aIndex], 47U) ^ RotL64(aWorkLaneB[(aIndex + 1U)], 21U);
        aPublicIngress = aPublicIngress + (RotL64(aWorkLaneB[(aIndex + 17U)], 7U) ^ RotL64(aWorkLaneB[S_BLOCK1 - aIndex], 31U));
        aPublicIngress = aPublicIngress ^ aPublicIngressDomainWord;
        aPublicIngress = TwistMix64::DiffuseA(aPublicIngress);
        aPrivateIngress = RotL64(aWorkLaneB[(aIndex + 3U)], 21U) ^ RotL64(aWorkLaneB[(aIndex + 29U)], 41U);
        aPrivateIngress = aPrivateIngress + (RotL64(aWorkLaneB[(16383U - aIndex + 7U)], 47U) ^ RotL64(aWorkLaneB[(16383U - aIndex + 23U)], 5U));
        aPrivateIngress = aPrivateIngress ^ aPrivateIngressDomainWord;
        aPrivateIngress = TwistMix64::DiffuseB(aPrivateIngress);
        aCrossIngress = RotL64(aWorkLaneB[S_BLOCK1 - aIndex], 49U) ^ RotL64(aWorkLaneB[(16383U - aIndex + 1U)], 29U);
        aCrossIngress = aCrossIngress + (RotL64(aWorkLaneB[(aIndex + 11U)], 43U) ^ RotL64(aWorkLaneB[(16383U - aIndex + 31U)], 9U));
        aCrossIngress = aCrossIngress ^ aCrossIngressDomainWord;
        aCrossIngress = TwistMix64::DiffuseC(aCrossIngress);
        //
        aPublicScatter = TwistMix64::DiffuseB((RotL64(aPublicIngress, 7U) ^ RotL64(aPublicPrevious, 51U)) + (RotL64(aCrossIngress, 43U) ^ RotL64(aPublicIngress, 21U)));
        aPrivateScatter = TwistMix64::DiffuseB((RotL64(aPrivateIngress, 29U) ^ RotL64(aPrivatePrevious, 5U)) + (RotL64(aCrossIngress, 47U) ^ RotL64(aCarry, 37U)));
        //
        aOrbitA = aWandererA;
        aOrbitA = aOrbitA + RotL64(aPrivateIngress, 13U);
        aOrbitA = aOrbitA + 5697928251815176134ULL;
        aOrbitB = aWandererB;
        aOrbitB = aOrbitB + RotL64(aPrivatePrevious, 41U);
        aOrbitB = aOrbitB + 337587740689259575ULL;
        aOrbitC = aWandererE;
        aOrbitC = aOrbitC + RotL64(aPrivateScatter, 37U);
        aOrbitC = aOrbitC + 4927686903263973950ULL;
        aOrbitC = aOrbitC + mDomainSaltSourceA[((aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + mDomainSaltSourceB[((31U - aIndex + 1U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererC;
        aOrbitD = aOrbitD + RotL64(aCarry, 53U);
        aOrbitD = aOrbitD + 3742409032569801033ULL;
        aOrbitD = aOrbitD + mDomainSaltSourceA[((31U - aIndex + 7U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + mDomainSaltSourceB[((aIndex + 31U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aWandererF;
        aOrbitE = aOrbitE + RotL64(aPrivateIngress, 23U);
        aOrbitE = aOrbitE + 1608092659172197650ULL;
        aOrbitF = aWandererD;
        aOrbitF = aOrbitF + RotL64(aPrivateScatter, 11U);
        aOrbitF = aOrbitF + 15848744267145717509ULL;
        //
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aPublicScatter, 17U) ^ aPublicPrevious);
        aPlugSalt0 = mDomainSaltSourceD[((aPlugKeyB + 9U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aCrossIngress, 41U) ^ aPublicScatter);
        aPlugSalt1 = mDomainSaltSourceC[((aPlugKeyA + 11U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA + aOrbitD;
        aOrbitA = aOrbitA + 15300174177963339253ULL;
        aOrbitA = aOrbitA + aPlugSalt0;
        aOrbitF = aOrbitF + aOrbitA;
        aOrbitF = aOrbitF + 14162868453323648628ULL;
        aOrbitF = aOrbitF + aPlugSalt1;
        aOrbitF = RotL64(aOrbitF * 6302504235542433263ULL, 63U);
        //
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aPublicScatter, 23U) ^ aPublicIngress);
        aPlugSalt2 = mDomainSaltSourceC[((aPlugKeyA + 19U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aCrossIngress, 31U) ^ aPublicIngress);
        aPlugSalt3 = mDomainSaltSourceD[((aPlugKeyB + 5U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB + aOrbitE;
        aOrbitB = aOrbitB + 12020167069983729869ULL;
        aOrbitB = aOrbitB + aPlugSalt2;
        aOrbitA = aOrbitA + aOrbitB;
        aOrbitA = aOrbitA + 16259538291658723956ULL;
        aOrbitA = aOrbitA + aPlugSalt3;
        aOrbitA = RotL64(aOrbitA * 6262123350804980887ULL, 48U);
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aPublicIngress, 11U) ^ aPublicPrevious);
        aPlugSalt4 = mDomainSaltSourceD[((aPlugKeyB + 3U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aPublicPrevious, 19U) ^ aPublicScatter);
        aPlugSalt5 = mDomainSaltSourceC[((aPlugKeyA + 7U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + aOrbitF;
        aOrbitC = aOrbitC + 8516686212464112245ULL;
        aOrbitC = aOrbitC + aPlugSalt4;
        aOrbitB = aOrbitB + aOrbitC;
        aOrbitB = aOrbitB + 3722184575520553132ULL;
        aOrbitB = aOrbitB + aPlugSalt5;
        aOrbitB = RotL64(aOrbitB * 8349884892252470343ULL, 13U);
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aCrossIngress, 29U) ^ aPublicPrevious);
        aPlugSalt6 = mDomainSaltSourceC[((aPlugKeyA + 1U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aPublicScatter, 7U) ^ aCrossIngress);
        aPlugSalt7 = mDomainSaltSourceD[((aPlugKeyB + 29U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + aOrbitA;
        aOrbitD = aOrbitD + 5663609293306386784ULL;
        aOrbitD = aOrbitD + aPlugSalt6;
        aOrbitC = aOrbitC + aOrbitD;
        aOrbitC = aOrbitC + 15265344442454471986ULL;
        aOrbitC = aOrbitC + aPlugSalt7;
        aOrbitC = RotL64(aOrbitC * 15597397493542010979ULL, 24U);
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aPublicIngress, 37U) ^ aPublicScatter);
        aPlugSalt8 = mDomainSaltSourceD[((aPlugKeyB + 17U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aPublicPrevious, 43U) ^ aCrossIngress);
        aPlugSalt9 = mDomainSaltSourceC[((aPlugKeyA + 13U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aOrbitE + aOrbitB;
        aOrbitE = aOrbitE + 3050323350098829515ULL;
        aOrbitE = aOrbitE + aPlugSalt8;
        aOrbitD = aOrbitD + aOrbitE;
        aOrbitD = aOrbitD + 1093356813820599238ULL;
        aOrbitD = aOrbitD + aPlugSalt9;
        aOrbitD = RotL64(aOrbitD * 7039855035597231687ULL, 57U);
        //
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aPublicPrevious, 53U) ^ aPublicIngress);
        aPlugSalt10 = mDomainSaltSourceC[((aPlugKeyA + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aPublicIngress, 13U) ^ aCrossIngress);
        aPlugSalt11 = mDomainSaltSourceD[((aPlugKeyB + 15U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = aOrbitF + aOrbitC;
        aOrbitF = aOrbitF + 15167726103772238440ULL;
        aOrbitF = aOrbitF + aPlugSalt10;
        aOrbitE = aOrbitE + aOrbitF;
        aOrbitE = aOrbitE + 15170797965325981472ULL;
        aOrbitE = aOrbitE + aPlugSalt11;
        aOrbitE = RotL64(aOrbitE * 1024636833977775953ULL, 32U);
        //
        aPrivateIngress = TwistMix64::DiffuseB((aOrbitA ^ RotL64(aOrbitF, 23U)) + (RotL64(aOrbitB, 53U) ^ aOrbitD) + (RotL64(aOrbitC, 11U) ^ aOrbitE) + aPrivateScatter + aCarry);
        aWorkLaneD[aIndex] = aPrivateIngress;
        //
        aWandererA = aWandererA + RotL64(aPrivateIngress, 11U);
        aWandererA = aWandererA + RotL64(aPrivatePrevious, 31U);
        aWandererA = aWandererA + aOrbitA;
        aWandererA = aWandererA + mDomainSaltSourceE[((31U - aIndex + 9U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererB = aWandererB + RotL64(aPrivateIngress, 13U);
        aWandererB = aWandererB + RotL64(aPrivateScatter, 19U);
        aWandererB = aWandererB + aOrbitC;
        aWandererC = aWandererC + aOrbitF;
        aWandererC = aWandererC + aOrbitB;
        aWandererD = aWandererD + RotL64(aPrivateIngress, 37U);
        aWandererD = aWandererD + RotL64(aPrivatePrevious, 17U);
        aWandererD = aWandererD + aOrbitD;
        aWandererD = aWandererD + mDomainSaltSourceF[((aIndex + 25U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererE = aWandererE + RotL64(aPrivateIngress, 7U);
        aWandererE = aWandererE + RotL64(aPrivateScatter, 43U);
        aWandererE = aWandererE + aOrbitE;
        aWandererF = aWandererF + aOrbitF;
        aWandererF = aWandererF + aOrbitC;
        //
        aCarry = aCarry + (aWandererA ^ RotL64(aWandererB, 37U)) + (aWandererC ^ RotL64(aWandererD, 23U)) + (aWandererE ^ RotL64(aWandererF, 17U)) + RotL64(aPrivateIngress, 7U);
        aCarry = RotL64(aCarry * 6055682981584011189ULL, 29U);
        aCarry = aCarry ^ ShiftR64(aCarry, 41U);
    }

    }
}

void TwistExpander_Carbon::Seed(TwistWorkSpace *pWorkspace,
                                 TwistCryptoGenerator *pCryptoGenerator,
                                 TwistFarmSBox *pFarmSBox,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint8_t *pSource,
                                 std::uint8_t *pPassword,
                                 unsigned int pPasswordByteLength) {
    TwistExpander::Seed(pWorkspace, pCryptoGenerator, pFarmSBox, pFarmSalt, pSource, pPassword, pPasswordByteLength);
    if ((pWorkspace == nullptr) || (pCryptoGenerator == nullptr) || (pFarmSBox == nullptr) || (pFarmSalt == nullptr)) { return; }

    {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkspace->mExpandLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkspace->mExpandLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkspace->mExpandLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkspace->mExpandLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkspace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkspace->mOperationLaneB;
    std::uint64_t aWalker = 0;
    std::uint64_t aPrism = 0;
    std::uint64_t aArgA = 0, aArgB = 0;
    std::uint64_t aKindA = 0, aKindB = 0;

    // [phase ii]
    // phase: workers -> expansion [offset 0]
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 16320U - aIndex;
        aPrism = aOperationLaneB[aIndex];
        switch (aPrism % 3U) {
        	case 0U: {
        		mMatrixA.LoadAndReset(aWorkLaneA + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneB + aIndex);
        		mMatrixA.FlipVerticalSixteenthsQuarterB(0U, 0U);
        		mMatrixA.RotateLeftEachQuarter(0U, 0U);
        		aArgA = aOperationLaneB[(aIndex + 1U)];
        		mMatrixA.ReverseRowEven(aArgA, 0U);
        		mMatrixA.PinwheelLeftQuarterB(0U, 0U);
        		aKindA = aOperationLaneB[(aIndex + 2U)];
        		mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kC, aKindA);
        		mMatrixB.RotateLeftSixteenthsQuarterD(0U, 0U);
        		aArgB = aOperationLaneB[(aIndex + 3U)];
        		mMatrixB.ReverseColEven(aArgB, 0U);
        		mMatrixB.TransposeAntiDiagonal(0U, 0U);
        		aArgA = aOperationLaneB[(aIndex + 4U)];
        		aArgB = aOperationLaneB[(aIndex + 5U)];
        		mMatrixB.SwapColsOdd(aArgA, aArgB);
        		mMatrixB.RotateLeftEachSixteenthQuarterC(0U, 0U);
        		aKindB = aOperationLaneB[(aIndex + 6U)];
        		mMatrixB.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
        		break;
        	}
        	case 1U: {
        		mMatrixA.LoadAndReset(aWorkLaneA + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneB + aIndex);
        		aArgA = aOperationLaneB[(aIndex + 1U)];
        		aArgB = aOperationLaneB[(aIndex + 2U)];
        		mMatrixA.RotateCol(aArgA, aArgB);
        		mMatrixA.RotateLeftQuarterA(0U, 0U);
        		mMatrixA.FlipHorizontalQuarterD(0U, 0U);
        		mMatrixA.TransposeAntiDiagonalEachSixteenthQuarterA(0U, 0U);
        		aKindA = aOperationLaneB[(aIndex + 3U)];
        		mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kA, aKindA);
        		aArgB = aOperationLaneB[(aIndex + 4U)];
        		mMatrixB.ShiftRing16F(aArgB, 0U);
        		aArgA = aOperationLaneB[(aIndex + 5U)];
        		aArgB = aOperationLaneB[(aIndex + 6U)];
        		mMatrixB.SwapSixteenths(aArgA, aArgB);
        		aArgA = aOperationLaneB[(aIndex + 7U)];
        		aArgB = aOperationLaneB[(aIndex + 8U)];
        		mMatrixB.RotateRow(aArgA, aArgB);
        		aKindB = aOperationLaneB[(aIndex + 9U)];
        		mMatrixB.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kC, aKindB);
        		break;
        	}
        	case 2U: {
        		mMatrixA.LoadAndReset(aWorkLaneA + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneB + aIndex);
        		aArgA = aOperationLaneB[(aIndex + 1U)];
        		aArgB = aOperationLaneB[(aIndex + 2U)];
        		mMatrixA.SwapRows(aArgA, aArgB);
        		aArgA = aOperationLaneB[(aIndex + 3U)];
        		mMatrixA.ReverseColEven(aArgA, 0U);
        		mMatrixA.PinwheelRight(0U, 0U);
        		mMatrixA.FlipVerticalSixteenthsQuarterD(0U, 0U);
        		aKindA = aOperationLaneB[(aIndex + 4U)];
        		mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
        		aArgB = aOperationLaneB[(aIndex + 5U)];
        		mMatrixB.ShiftRing20A(aArgB, 0U);
        		aArgB = aOperationLaneB[(aIndex + 6U)];
        		mMatrixB.ShiftRing8D(aArgB, 0U);
        		aArgB = aOperationLaneB[(aIndex + 7U)];
        		mMatrixB.ReverseRowOdd(aArgB, 0U);
        		aKindB = aOperationLaneB[(aIndex + 8U)];
        		mMatrixB.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
        		break;
        	}
        }
    }
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 16320U - aIndex;
        aPrism = aOperationLaneA[aIndex];
        switch (aPrism % 4U) {
        	case 0U: {
        		mMatrixA.LoadAndReset(aWorkLaneC + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneD + aIndex);
        		mMatrixA.FlipHorizontalSixteenthsQuarterD(0U, 0U);
        		mMatrixA.TransposeAntiDiagonalBlocks(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 1U)];
        		aArgB = aOperationLaneA[(aIndex + 2U)];
        		mMatrixA.SwapColsEven(aArgA, aArgB);
        		aKindA = aOperationLaneA[(aIndex + 3U)];
        		mMatrixA.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
        		mMatrixB.TransposeAntiDiagonalEachSixteenthQuarterD(0U, 0U);
        		aArgB = aOperationLaneA[(aIndex + 4U)];
        		mMatrixB.ShiftRing24A(aArgB, 0U);
        		aArgB = aOperationLaneA[(aIndex + 5U)];
        		mMatrixB.ReverseColEven(aArgB, 0U);
        		aArgB = aOperationLaneA[(aIndex + 6U)];
        		mMatrixB.ReverseRow(aArgB, 0U);
        		mMatrixB.FlipVerticalEachSixteenthQuarterD(0U, 0U);
        		aKindB = aOperationLaneA[(aIndex + 7U)];
        		mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kA, aKindB);
        		break;
        	}
        	case 1U: {
        		mMatrixA.LoadAndReset(aWorkLaneC + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneD + aIndex);
        		mMatrixA.RotateRightQuarterC(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 1U)];
        		mMatrixA.ReverseRowEven(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 2U)];
        		aArgB = aOperationLaneA[(aIndex + 3U)];
        		mMatrixA.SwapColsEven(aArgA, aArgB);
        		aKindA = aOperationLaneA[(aIndex + 4U)];
        		mMatrixA.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kD, aKindA);
        		mMatrixB.TransposeMainDiagonalEachQuarter(0U, 0U);
        		mMatrixB.RotateLeftEachSixteenthQuarterC(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 5U)];
        		aArgB = aOperationLaneA[(aIndex + 6U)];
        		mMatrixB.SwapRowsEven(aArgA, aArgB);
        		aKindB = aOperationLaneA[(aIndex + 7U)];
        		mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kB, aKindB);
        		break;
        	}
        	case 2U: {
        		mMatrixA.LoadAndReset(aWorkLaneC + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneD + aIndex);
        		aArgA = aOperationLaneA[(aIndex + 1U)];
        		mMatrixA.ShiftRing12D(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 2U)];
        		mMatrixA.ShiftRing16C(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 3U)];
        		aArgB = aOperationLaneA[(aIndex + 4U)];
        		mMatrixA.SwapColsEven(aArgA, aArgB);
        		aKindA = aOperationLaneA[(aIndex + 5U)];
        		mMatrixA.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kC, aKindA);
        		mMatrixB.PinwheelRightQuarterB(0U, 0U);
        		aArgB = aOperationLaneA[(aIndex + 6U)];
        		mMatrixB.ReverseColOdd(aArgB, 0U);
        		mMatrixB.RotateLeftBlocks(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 7U)];
        		aArgB = aOperationLaneA[(aIndex + 8U)];
        		mMatrixB.SwapRows(aArgA, aArgB);
        		aKindB = aOperationLaneA[(aIndex + 9U)];
        		mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
        		break;
        	}
        	case 3U: {
        		mMatrixA.LoadAndReset(aWorkLaneC + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneD + aIndex);
        		mMatrixA.RotateLeft(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 1U)];
        		mMatrixA.ShiftRing28A(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 2U)];
        		aArgB = aOperationLaneA[(aIndex + 3U)];
        		mMatrixA.SwapRowsOdd(aArgA, aArgB);
        		aKindA = aOperationLaneA[(aIndex + 4U)];
        		mMatrixA.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kA, aKindA);
        		aArgB = aOperationLaneA[(aIndex + 5U)];
        		mMatrixB.ReverseColOdd(aArgB, 0U);
        		aArgB = aOperationLaneA[(aIndex + 6U)];
        		mMatrixB.ShiftRing16D(aArgB, 0U);
        		mMatrixB.PinwheelRightQuarterA(0U, 0U);
        		aKindB = aOperationLaneA[(aIndex + 7U)];
        		mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kC, aKindB);
        		break;
        	}
        }
    }
    // phase: expansion -> workers [offset 20]
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 16320U - aIndex;
        aPrism = aOperationLaneB[(aIndex + 20U)];
        switch (aPrism % 3U) {
        	case 0U: {
        		mMatrixA.LoadAndReset(aExpandLaneA + aIndex);
        		mMatrixB.LoadAndReset(aExpandLaneC + aIndex);
        		mMatrixA.FlipHorizontalEachSixteenthQuarterA(0U, 0U);
        		aArgA = aOperationLaneB[(aIndex + 21U)];
        		aArgB = aOperationLaneB[(aIndex + 22U)];
        		mMatrixA.SwapSixteenths(aArgA, aArgB);
        		aArgA = aOperationLaneB[(aIndex + 23U)];
        		aArgB = aOperationLaneB[(aIndex + 24U)];
        		mMatrixA.SwapRowsEven(aArgA, aArgB);
        		aKindA = aOperationLaneB[(aIndex + 25U)];
        		mMatrixA.Store(aWorkLaneB + aIndex, TwistFastMatrixUnrollScheme::kC, aKindA);
        		aArgB = aOperationLaneB[(aIndex + 26U)];
        		mMatrixB.ReverseRow(aArgB, 0U);
        		mMatrixB.RotateRightQuarterD(0U, 0U);
        		aArgA = aOperationLaneB[(aIndex + 27U)];
        		aArgB = aOperationLaneB[(aIndex + 28U)];
        		mMatrixB.RotateCol(aArgA, aArgB);
        		aKindB = aOperationLaneB[(aIndex + 29U)];
        		mMatrixB.Store(aWorkLaneD + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
        		break;
        	}
        	case 1U: {
        		mMatrixA.LoadAndReset(aExpandLaneA + aIndex);
        		mMatrixB.LoadAndReset(aExpandLaneC + aIndex);
        		aArgA = aOperationLaneB[(aIndex + 21U)];
        		aArgB = aOperationLaneB[(aIndex + 22U)];
        		mMatrixA.SwapRows(aArgA, aArgB);
        		mMatrixA.RotateRightQuarterB(0U, 0U);
        		mMatrixA.FlipVertical(0U, 0U);
        		mMatrixA.TransposeAntiDiagonalBlocks(0U, 0U);
        		aKindA = aOperationLaneB[(aIndex + 23U)];
        		mMatrixA.Store(aWorkLaneB + aIndex, TwistFastMatrixUnrollScheme::kA, aKindA);
        		aArgB = aOperationLaneB[(aIndex + 24U)];
        		mMatrixB.ReverseCol(aArgB, 0U);
        		mMatrixB.RotateRightSixteenthsQuarterA(0U, 0U);
        		mMatrixB.TransposeAntiDiagonalEachSixteenthQuarterA(0U, 0U);
        		aKindB = aOperationLaneB[(aIndex + 25U)];
        		mMatrixB.Store(aWorkLaneD + aIndex, TwistFastMatrixUnrollScheme::kC, aKindB);
        		break;
        	}
        	case 2U: {
        		mMatrixA.LoadAndReset(aExpandLaneA + aIndex);
        		mMatrixB.LoadAndReset(aExpandLaneC + aIndex);
        		aArgA = aOperationLaneB[(aIndex + 21U)];
        		aArgB = aOperationLaneB[(aIndex + 22U)];
        		mMatrixA.RotateCol(aArgA, aArgB);
        		aArgA = aOperationLaneB[(aIndex + 23U)];
        		mMatrixA.ReverseRowOdd(aArgA, 0U);
        		mMatrixA.PinwheelRightQuarterC(0U, 0U);
        		aKindA = aOperationLaneB[(aIndex + 24U)];
        		mMatrixA.Store(aWorkLaneB + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
        		aArgB = aOperationLaneB[(aIndex + 25U)];
        		mMatrixB.ShiftRing20A(aArgB, 0U);
        		aArgA = aOperationLaneB[(aIndex + 26U)];
        		aArgB = aOperationLaneB[(aIndex + 27U)];
        		mMatrixB.SwapColsEven(aArgA, aArgB);
        		mMatrixB.RotateRightBlocks(0U, 0U);
        		mMatrixB.RotateLeft(0U, 0U);
        		aKindB = aOperationLaneB[(aIndex + 28U)];
        		mMatrixB.Store(aWorkLaneD + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
        		break;
        	}
        }
    }
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 16320U - aIndex;
        aPrism = aOperationLaneA[(aIndex + 20U)];
        switch (aPrism % 4U) {
        	case 0U: {
        		mMatrixA.LoadAndReset(aExpandLaneB + aIndex);
        		mMatrixB.LoadAndReset(aExpandLaneD + aWalker);
        		mMatrixA.RotateRightSixteenthsQuarterB(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 21U)];
        		aArgB = aOperationLaneA[(aIndex + 22U)];
        		mMatrixA.SwapColsEven(aArgA, aArgB);
        		aArgA = aOperationLaneA[(aIndex + 23U)];
        		mMatrixA.ReverseColEven(aArgA, 0U);
        		mMatrixA.FlipVerticalSixteenthsQuarterA(0U, 0U);
        		aKindA = aOperationLaneA[(aIndex + 24U)];
        		mMatrixA.Store(aWorkLaneA + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
        		aArgA = aOperationLaneA[(aIndex + 25U)];
        		aArgB = aOperationLaneA[(aIndex + 26U)];
        		mMatrixB.SwapSixteenths(aArgA, aArgB);
        		mMatrixB.FlipHorizontal(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 27U)];
        		aArgB = aOperationLaneA[(aIndex + 28U)];
        		mMatrixB.SwapRows(aArgA, aArgB);
        		mMatrixB.RotateLeftQuarterD(0U, 0U);
        		aKindB = aOperationLaneA[(aIndex + 29U)];
        		mMatrixB.Store(aWorkLaneC + aIndex, TwistFastMatrixUnrollScheme::kA, aKindB);
        		break;
        	}
        	case 1U: {
        		mMatrixA.LoadAndReset(aExpandLaneB + aIndex);
        		mMatrixB.LoadAndReset(aExpandLaneD + aWalker);
        		mMatrixA.TransposeAntiDiagonal(0U, 0U);
        		mMatrixA.RotateLeftSixteenthsQuarterB(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 21U)];
        		mMatrixA.ReverseColEven(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 22U)];
        		aArgB = aOperationLaneA[(aIndex + 23U)];
        		mMatrixA.SwapRows(aArgA, aArgB);
        		aKindA = aOperationLaneA[(aIndex + 24U)];
        		mMatrixA.Store(aWorkLaneA + aIndex, TwistFastMatrixUnrollScheme::kD, aKindA);
        		mMatrixB.TransposeAntiDiagonalSixteenthsQuarterA(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 25U)];
        		aArgB = aOperationLaneA[(aIndex + 26U)];
        		mMatrixB.SwapColsOdd(aArgA, aArgB);
        		mMatrixB.RotateRightBlocks(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 27U)];
        		aArgB = aOperationLaneA[(aIndex + 28U)];
        		mMatrixB.SwapSixteenths(aArgA, aArgB);
        		aKindB = aOperationLaneA[(aIndex + 29U)];
        		mMatrixB.Store(aWorkLaneC + aIndex, TwistFastMatrixUnrollScheme::kB, aKindB);
        		break;
        	}
        	case 2U: {
        		mMatrixA.LoadAndReset(aExpandLaneB + aIndex);
        		mMatrixB.LoadAndReset(aExpandLaneD + aWalker);
        		aArgA = aOperationLaneA[(aIndex + 21U)];
        		aArgB = aOperationLaneA[(aIndex + 22U)];
        		mMatrixA.RotateCol(aArgA, aArgB);
        		mMatrixA.FlipVerticalSixteenthsQuarterD(0U, 0U);
        		mMatrixA.RotateLeftEachSixteenthQuarterB(0U, 0U);
        		aKindA = aOperationLaneA[(aIndex + 23U)];
        		mMatrixA.Store(aWorkLaneA + aIndex, TwistFastMatrixUnrollScheme::kC, aKindA);
        		mMatrixB.FlipVerticalQuarterC(0U, 0U);
        		mMatrixB.TransposeMainDiagonalSixteenthsQuarterD(0U, 0U);
        		mMatrixB.TransposeMainDiagonalBlocks(0U, 0U);
        		mMatrixB.PinwheelLeft(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 24U)];
        		aArgB = aOperationLaneA[(aIndex + 25U)];
        		mMatrixB.SwapCols(aArgA, aArgB);
        		aKindB = aOperationLaneA[(aIndex + 26U)];
        		mMatrixB.Store(aWorkLaneC + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
        		break;
        	}
        	case 3U: {
        		mMatrixA.LoadAndReset(aExpandLaneB + aIndex);
        		mMatrixB.LoadAndReset(aExpandLaneD + aWalker);
        		mMatrixA.RotateLeftEachSixteenthQuarterA(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 21U)];
        		mMatrixA.ShiftRing24A(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 22U)];
        		mMatrixA.ShiftRing8C(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 23U)];
        		aArgB = aOperationLaneA[(aIndex + 24U)];
        		mMatrixA.SwapColsOdd(aArgA, aArgB);
        		aKindA = aOperationLaneA[(aIndex + 25U)];
        		mMatrixA.Store(aWorkLaneA + aIndex, TwistFastMatrixUnrollScheme::kA, aKindA);
        		mMatrixB.TransposeAntiDiagonalSixteenthsEachQuarter(0U, 0U);
        		mMatrixB.TransposeAntiDiagonalQuarterC(0U, 0U);
        		aArgB = aOperationLaneA[(aIndex + 26U)];
        		mMatrixB.ReverseColOdd(aArgB, 0U);
        		aArgA = aOperationLaneA[(aIndex + 27U)];
        		aArgB = aOperationLaneA[(aIndex + 28U)];
        		mMatrixB.SwapRowsOdd(aArgA, aArgB);
        		aKindB = aOperationLaneA[(aIndex + 29U)];
        		mMatrixB.Store(aWorkLaneC + aIndex, TwistFastMatrixUnrollScheme::kC, aKindB);
        		break;
        	}
        }
    }
    // phase: workers -> expansion [offset 40]
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 16320U - aIndex;
        aPrism = aOperationLaneB[(aIndex + 40U)];
        switch (aPrism % 3U) {
        	case 0U: {
        		mMatrixA.LoadAndReset(aWorkLaneA + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneD + aWalker);
        		mMatrixA.FlipVertical(0U, 0U);
        		mMatrixA.RotateLeftBlocks(0U, 0U);
        		mMatrixA.TransposeMainDiagonalQuarterC(0U, 0U);
        		aArgA = aOperationLaneB[(aIndex + 41U)];
        		mMatrixA.ReverseCol(aArgA, 0U);
        		mMatrixA.PinwheelRight(0U, 0U);
        		aKindA = aOperationLaneB[(aIndex + 42U)];
        		mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kC, aKindA);
        		aArgA = aOperationLaneB[(aIndex + 43U)];
        		aArgB = aOperationLaneB[(aIndex + 44U)];
        		mMatrixB.SwapCols(aArgA, aArgB);
        		mMatrixB.RotateLeftSixteenthsQuarterC(0U, 0U);
        		mMatrixB.FlipVerticalSixteenthsQuarterD(0U, 0U);
        		aKindB = aOperationLaneB[(aIndex + 45U)];
        		mMatrixB.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
        		break;
        	}
        	case 1U: {
        		mMatrixA.LoadAndReset(aWorkLaneA + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneD + aWalker);
        		aArgA = aOperationLaneB[(aIndex + 41U)];
        		mMatrixA.ReverseCol(aArgA, 0U);
        		mMatrixA.RotateLeft(0U, 0U);
        		aArgA = aOperationLaneB[(aIndex + 42U)];
        		aArgB = aOperationLaneB[(aIndex + 43U)];
        		mMatrixA.SwapRows(aArgA, aArgB);
        		aArgA = aOperationLaneB[(aIndex + 44U)];
        		mMatrixA.ShiftRing20E(aArgA, 0U);
        		aKindA = aOperationLaneB[(aIndex + 45U)];
        		mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kA, aKindA);
        		aArgA = aOperationLaneB[(aIndex + 46U)];
        		aArgB = aOperationLaneB[(aIndex + 47U)];
        		mMatrixB.RotateCol(aArgA, aArgB);
        		mMatrixB.TransposeMainDiagonalSixteenthsQuarterC(0U, 0U);
        		aArgB = aOperationLaneB[(aIndex + 48U)];
        		mMatrixB.ReverseRowEven(aArgB, 0U);
        		aKindB = aOperationLaneB[(aIndex + 49U)];
        		mMatrixB.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kC, aKindB);
        		break;
        	}
        	case 2U: {
        		mMatrixA.LoadAndReset(aWorkLaneA + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneD + aWalker);
        		mMatrixA.RotateLeftEachSixteenthQuarterD(0U, 0U);
        		mMatrixA.RotateRight(0U, 0U);
        		mMatrixA.TransposeAntiDiagonal(0U, 0U);
        		aArgA = aOperationLaneB[(aIndex + 41U)];
        		aArgB = aOperationLaneB[(aIndex + 42U)];
        		mMatrixA.SwapSixteenths(aArgA, aArgB);
        		mMatrixA.RotateLeftSixteenthsQuarterD(0U, 0U);
        		aKindA = aOperationLaneB[(aIndex + 43U)];
        		mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
        		mMatrixB.PinwheelRightEachQuarter(0U, 0U);
        		aArgA = aOperationLaneB[(aIndex + 44U)];
        		aArgB = aOperationLaneB[(aIndex + 45U)];
        		mMatrixB.SwapRowsEven(aArgA, aArgB);
        		mMatrixB.TransposeMainDiagonalEachSixteenthEachQuarter(0U, 0U);
        		mMatrixB.PinwheelLeft(0U, 0U);
        		aArgB = aOperationLaneB[(aIndex + 46U)];
        		mMatrixB.ReverseRowEven(aArgB, 0U);
        		aKindB = aOperationLaneB[(aIndex + 47U)];
        		mMatrixB.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
        		break;
        	}
        }
    }
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 16320U - aIndex;
        aPrism = aOperationLaneA[(aIndex + 40U)];
        switch (aPrism % 4U) {
        	case 0U: {
        		mMatrixA.LoadAndReset(aWorkLaneB + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneC + aWalker);
        		mMatrixA.TransposeAntiDiagonalSixteenthsQuarterB(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 41U)];
        		mMatrixA.ReverseRowEven(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 42U)];
        		mMatrixA.ShiftRing12C(aArgA, 0U);
        		aKindA = aOperationLaneA[(aIndex + 43U)];
        		mMatrixA.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
        		mMatrixB.TransposeMainDiagonalEachSixteenthEachQuarter(0U, 0U);
        		mMatrixB.RotateLeftEachSixteenthQuarterC(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 44U)];
        		aArgB = aOperationLaneA[(aIndex + 45U)];
        		mMatrixB.RotateRow(aArgA, aArgB);
        		aKindB = aOperationLaneA[(aIndex + 46U)];
        		mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kA, aKindB);
        		break;
        	}
        	case 1U: {
        		mMatrixA.LoadAndReset(aWorkLaneB + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneC + aWalker);
        		mMatrixA.PinwheelLeft(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 41U)];
        		mMatrixA.ReverseColEven(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 42U)];
        		mMatrixA.ShiftRing12E(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 43U)];
        		aArgB = aOperationLaneA[(aIndex + 44U)];
        		mMatrixA.SwapRowsOdd(aArgA, aArgB);
        		aKindA = aOperationLaneA[(aIndex + 45U)];
        		mMatrixA.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kD, aKindA);
        		mMatrixB.RotateRight(0U, 0U);
        		aArgB = aOperationLaneA[(aIndex + 46U)];
        		mMatrixB.ReverseRowOdd(aArgB, 0U);
        		mMatrixB.FlipVerticalBlocks(0U, 0U);
        		aArgB = aOperationLaneA[(aIndex + 47U)];
        		mMatrixB.ShiftRing8H(aArgB, 0U);
        		mMatrixB.TransposeMainDiagonalBlocks(0U, 0U);
        		aKindB = aOperationLaneA[(aIndex + 48U)];
        		mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kB, aKindB);
        		break;
        	}
        	case 2U: {
        		mMatrixA.LoadAndReset(aWorkLaneB + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneC + aWalker);
        		aArgA = aOperationLaneA[(aIndex + 41U)];
        		aArgB = aOperationLaneA[(aIndex + 42U)];
        		mMatrixA.SwapSixteenths(aArgA, aArgB);
        		mMatrixA.RotateRight(0U, 0U);
        		mMatrixA.TransposeAntiDiagonalBlocks(0U, 0U);
        		mMatrixA.RotateLeftSixteenthsEachQuarter(0U, 0U);
        		aKindA = aOperationLaneA[(aIndex + 43U)];
        		mMatrixA.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kC, aKindA);
        		mMatrixB.TransposeAntiDiagonalEachSixteenthEachQuarter(0U, 0U);
        		aArgA = aOperationLaneA[(aIndex + 44U)];
        		aArgB = aOperationLaneA[(aIndex + 45U)];
        		mMatrixB.SwapCols(aArgA, aArgB);
        		aArgB = aOperationLaneA[(aIndex + 46U)];
        		mMatrixB.ReverseColOdd(aArgB, 0U);
        		aKindB = aOperationLaneA[(aIndex + 47U)];
        		mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
        		break;
        	}
        	case 3U: {
        		mMatrixA.LoadAndReset(aWorkLaneB + aIndex);
        		mMatrixB.LoadAndReset(aWorkLaneC + aWalker);
        		aArgA = aOperationLaneA[(aIndex + 41U)];
        		mMatrixA.ReverseRow(aArgA, 0U);
        		aArgA = aOperationLaneA[(aIndex + 42U)];
        		aArgB = aOperationLaneA[(aIndex + 43U)];
        		mMatrixA.RotateRow(aArgA, aArgB);
        		mMatrixA.FlipHorizontalEachSixteenthEachQuarter(0U, 0U);
        		aKindA = aOperationLaneA[(aIndex + 44U)];
        		mMatrixA.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kA, aKindA);
        		mMatrixB.FlipVerticalBlocks(0U, 0U);
        		mMatrixB.TransposeAntiDiagonalQuarterA(0U, 0U);
        		mMatrixB.PinwheelLeft(0U, 0U);
        		aArgB = aOperationLaneA[(aIndex + 45U)];
        		mMatrixB.ReverseCol(aArgB, 0U);
        		aArgA = aOperationLaneA[(aIndex + 46U)];
        		aArgB = aOperationLaneA[(aIndex + 47U)];
        		mMatrixB.SwapRowsEven(aArgA, aArgB);
        		aKindB = aOperationLaneA[(aIndex + 48U)];
        		mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kC, aKindB);
        		break;
        	}
        }
    }

    }
}

void TwistExpander_Carbon::TwistBlock(TwistWorkSpace *pWorkspace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkspace, pSource, pDestination);
    if ((pWorkspace == nullptr) || (pDestination == nullptr)) { return; }
    std::memcpy(pDestination, pWorkspace->mWorkLaneD, S_BLOCK);
}

const std::uint8_t TwistExpander_Carbon::kSBoxA[S_SBOX] = {
    0x13, 0x64, 0x3C, 0x25, 0xEF, 0x89, 0x0A, 0x7F, 0x4D, 0x28, 0x90, 0xB9, 0xF6, 0xA5, 0x5D, 0x88, 
    0xA4, 0x0E, 0x66, 0xD0, 0x75, 0x2E, 0xED, 0x99, 0xA8, 0x67, 0x73, 0xDE, 0xCD, 0x86, 0x0B, 0x48, 
    0xE8, 0x34, 0x16, 0x14, 0xB8, 0x96, 0xD8, 0x51, 0xCE, 0x32, 0x02, 0x2D, 0xC9, 0x7E, 0xF9, 0x07, 
    0x1F, 0x09, 0x23, 0x8A, 0xAA, 0x21, 0xAB, 0x38, 0xDD, 0x46, 0x78, 0x43, 0x6D, 0xA0, 0xDF, 0x4A, 
    0xB2, 0xBA, 0xF8, 0xDC, 0x68, 0xBE, 0xEC, 0x05, 0x76, 0x15, 0x11, 0x6B, 0xCF, 0xF7, 0x3A, 0xFB, 
    0xC2, 0x50, 0x9C, 0x98, 0xE1, 0x80, 0x1D, 0x58, 0x3D, 0x10, 0xC6, 0x63, 0x40, 0xB5, 0x9A, 0x93, 
    0xE4, 0xEE, 0xE9, 0xC1, 0x6E, 0x01, 0x8F, 0x4F, 0x9B, 0xB7, 0xEA, 0xA6, 0x00, 0x54, 0x0F, 0x9F, 
    0xB4, 0xC7, 0xAC, 0xA3, 0xA2, 0x79, 0xD7, 0xAE, 0xB0, 0x5C, 0x08, 0x55, 0x30, 0x42, 0x5B, 0x92, 
    0xE5, 0x85, 0xF2, 0x2C, 0xDB, 0x95, 0x2F, 0x71, 0xCB, 0x44, 0x12, 0xE0, 0x52, 0xAD, 0x1E, 0xBF, 
    0xD1, 0xCC, 0x77, 0xFD, 0x97, 0x0D, 0xD4, 0xE2, 0x59, 0x5A, 0x33, 0xB3, 0x8B, 0x6F, 0xC4, 0xBC, 
    0x35, 0x3B, 0xA1, 0x70, 0x82, 0x69, 0x62, 0x19, 0x3E, 0x26, 0x1C, 0xA7, 0x60, 0xE3, 0xB6, 0x53, 
    0x74, 0xD2, 0x0C, 0x7C, 0xD5, 0xD3, 0xC3, 0x2B, 0xC8, 0xF5, 0x1A, 0xD9, 0xE6, 0x91, 0x6A, 0x06, 
    0x45, 0xE7, 0xD6, 0x8E, 0x29, 0xF0, 0x2A, 0xBD, 0xAF, 0x49, 0xFE, 0xEB, 0xF4, 0x04, 0x20, 0x94, 
    0x7D, 0x22, 0x9E, 0x24, 0x36, 0x5E, 0x6C, 0xF3, 0x65, 0x7A, 0x41, 0x87, 0x8D, 0xFC, 0x9D, 0xBB, 
    0x81, 0x03, 0x4E, 0x84, 0xFF, 0xCA, 0x17, 0x57, 0x8C, 0x5F, 0x39, 0x1B, 0x27, 0x37, 0x7B, 0x3F, 
    0x61, 0xB1, 0x56, 0x31, 0x72, 0xC0, 0xDA, 0x4B, 0x18, 0xFA, 0x4C, 0x47, 0xA9, 0x83, 0xF1, 0xC5
};

const std::uint8_t TwistExpander_Carbon::kSBoxB[S_SBOX] = {
    0x37, 0xCD, 0x70, 0x02, 0x4C, 0xB8, 0x45, 0xCE, 0xDE, 0x5D, 0xCA, 0xD9, 0x3E, 0x88, 0xD6, 0xBE, 
    0x8E, 0x60, 0xBC, 0x03, 0xC3, 0x09, 0x3D, 0xB0, 0xD7, 0xBA, 0x97, 0x2B, 0x54, 0x96, 0x43, 0xFD, 
    0x1E, 0x0C, 0x14, 0x65, 0xDF, 0x9E, 0x7F, 0x8F, 0x23, 0x58, 0x39, 0x7E, 0x71, 0xC8, 0x10, 0x1A, 
    0x6E, 0x32, 0x56, 0xCF, 0xA6, 0x27, 0xA0, 0x55, 0x5C, 0xD5, 0x9C, 0xF6, 0xB7, 0xAB, 0x2D, 0x8C, 
    0xD2, 0xAE, 0x16, 0x5A, 0x94, 0x8B, 0x3B, 0x6B, 0xB4, 0x63, 0x46, 0xE3, 0x25, 0x38, 0x24, 0x61, 
    0x7A, 0x89, 0x93, 0xB6, 0x64, 0xC2, 0x1F, 0xF5, 0x76, 0x40, 0x5F, 0x9F, 0x81, 0x80, 0xC7, 0xBD, 
    0x47, 0x4A, 0x18, 0x0D, 0xC0, 0x4E, 0xEC, 0xAF, 0xC1, 0xF1, 0x6F, 0xFF, 0x48, 0xAC, 0x66, 0xE4, 
    0x86, 0x59, 0xF2, 0xDC, 0xDA, 0x9A, 0x51, 0x83, 0xA3, 0xD0, 0x34, 0xAA, 0x29, 0xF0, 0x82, 0xBB, 
    0x41, 0xE1, 0x1B, 0x78, 0x08, 0xE9, 0x0F, 0xE6, 0x00, 0xA4, 0x31, 0x62, 0xF8, 0xF4, 0x68, 0x8D, 
    0x05, 0x52, 0xB2, 0x35, 0x98, 0x17, 0x26, 0x13, 0xF3, 0x84, 0x5E, 0xD4, 0xC9, 0xC6, 0x2E, 0xFA, 
    0x0A, 0x22, 0xAD, 0xE0, 0xB3, 0x92, 0x99, 0x3A, 0x01, 0x75, 0x19, 0xF9, 0xE8, 0x15, 0xF7, 0xFE, 
    0xC5, 0x72, 0x11, 0xB9, 0x20, 0x74, 0x7C, 0x2A, 0x77, 0x49, 0x4D, 0x79, 0x36, 0xCC, 0xE5, 0x1C, 
    0xA2, 0x30, 0x57, 0xEA, 0x5B, 0x6A, 0x2C, 0xFC, 0x85, 0xFB, 0x42, 0x69, 0x4F, 0x6D, 0x21, 0xEF, 
    0xBF, 0x50, 0xE2, 0x04, 0x7D, 0xA1, 0xB1, 0x1D, 0xCB, 0xED, 0x87, 0x90, 0x9D, 0x33, 0x95, 0xA8, 
    0xC4, 0x3F, 0xA9, 0xE7, 0x44, 0x06, 0x12, 0xDB, 0x9B, 0xA7, 0x53, 0x4B, 0x73, 0x7B, 0xEB, 0x07, 
    0xEE, 0xA5, 0xDD, 0x2F, 0x91, 0x0B, 0x0E, 0x8A, 0x3C, 0x67, 0xD8, 0xD3, 0xD1, 0xB5, 0x6C, 0x28
};

const std::uint8_t TwistExpander_Carbon::kSBoxC[S_SBOX] = {
    0x82, 0xF5, 0x44, 0x83, 0x6D, 0x23, 0x45, 0xED, 0xA5, 0x11, 0xE4, 0xB4, 0xAA, 0x1F, 0xB9, 0x06, 
    0x3A, 0x0C, 0x2A, 0xB7, 0xCC, 0x87, 0xB2, 0x3F, 0x8D, 0x0F, 0x5A, 0xDF, 0x39, 0x6E, 0x60, 0xC9, 
    0xDE, 0xBA, 0xEE, 0x31, 0x91, 0x72, 0x49, 0x0E, 0xC3, 0x2C, 0xBB, 0x7D, 0x70, 0xC8, 0xE7, 0xD7, 
    0x35, 0xBF, 0x15, 0xD9, 0x52, 0xCA, 0x77, 0x0D, 0x25, 0xA1, 0x5E, 0xCD, 0x2E, 0x73, 0xFA, 0x16, 
    0xB0, 0x4E, 0xC2, 0x00, 0x42, 0x07, 0x97, 0x08, 0x36, 0x14, 0x5D, 0xB8, 0xE6, 0x8F, 0xD2, 0x38, 
    0x74, 0x2B, 0x53, 0x1A, 0x05, 0xF8, 0xEA, 0xD5, 0x61, 0x78, 0x3D, 0x46, 0x37, 0x03, 0xC5, 0x1E, 
    0x69, 0x48, 0xFB, 0x8E, 0xD4, 0x41, 0xB5, 0x7A, 0xE0, 0xDC, 0x01, 0xE5, 0x64, 0x62, 0x29, 0xA9, 
    0x26, 0x18, 0xC4, 0x89, 0xAC, 0x7B, 0x04, 0x1B, 0x6F, 0x9C, 0x9A, 0x47, 0xF3, 0xE8, 0x2F, 0x3B, 
    0x4C, 0x94, 0xE3, 0x58, 0xB3, 0x88, 0xA2, 0x85, 0xAF, 0x7E, 0xA7, 0x20, 0xF4, 0xE1, 0x10, 0x22, 
    0x92, 0x1C, 0x13, 0xAE, 0x57, 0xF6, 0xFE, 0xFF, 0xF0, 0x0A, 0x09, 0x95, 0xFC, 0xF1, 0xE2, 0xD8, 
    0x9F, 0xF7, 0x56, 0xA0, 0x27, 0x67, 0x63, 0xA3, 0x9B, 0x79, 0xCF, 0xC0, 0xBC, 0xDA, 0xF9, 0xD1, 
    0xE9, 0x68, 0xD3, 0x17, 0xDB, 0x4D, 0x51, 0xEB, 0x55, 0x50, 0x59, 0x6C, 0xB6, 0xC1, 0x9D, 0xF2, 
    0x5B, 0x93, 0x21, 0x90, 0x34, 0x3C, 0xCE, 0xFD, 0x3E, 0xEC, 0x54, 0x24, 0x75, 0x2D, 0xEF, 0xAD, 
    0x32, 0x30, 0x8C, 0xA6, 0x65, 0x43, 0x0B, 0xC6, 0xD0, 0x81, 0x12, 0x4B, 0x6A, 0x8B, 0x76, 0x6B, 
    0xDD, 0x9E, 0x5F, 0xB1, 0x71, 0x8A, 0xCB, 0x98, 0x4F, 0x66, 0x28, 0x7C, 0x5C, 0x40, 0xA4, 0xBE, 
    0x99, 0x4A, 0xBD, 0xD6, 0x7F, 0xAB, 0x96, 0x33, 0x86, 0x1D, 0x80, 0x84, 0xA8, 0x02, 0x19, 0xC7
};

const std::uint8_t TwistExpander_Carbon::kSBoxD[S_SBOX] = {
    0x89, 0x3E, 0xC2, 0x11, 0x60, 0x0E, 0x5A, 0x7D, 0x3F, 0xE0, 0xDD, 0xDC, 0xB3, 0xF4, 0xC7, 0x2F, 
    0xD5, 0x80, 0xAE, 0xD3, 0xE7, 0xAA, 0xF0, 0xF6, 0x05, 0x8F, 0xAD, 0x93, 0xDA, 0x6F, 0x7B, 0xC4, 
    0x0B, 0xC8, 0x72, 0xE2, 0xFD, 0x97, 0xD9, 0x17, 0x6B, 0x82, 0x50, 0x1B, 0x00, 0x5C, 0xD2, 0xAB, 
    0x59, 0xEB, 0x5B, 0xBF, 0x95, 0xCB, 0xB4, 0x18, 0x22, 0x84, 0x16, 0x7F, 0x15, 0x0F, 0xB2, 0x54, 
    0x67, 0x6D, 0xF3, 0x03, 0xEE, 0xB7, 0xD1, 0x3B, 0x56, 0xC3, 0x19, 0x5F, 0x4A, 0x92, 0x88, 0x42, 
    0xBB, 0x36, 0x0D, 0xD7, 0x20, 0x25, 0xC9, 0x3C, 0xE3, 0x38, 0x61, 0x55, 0xCE, 0x0C, 0x47, 0x6C, 
    0xDB, 0x41, 0x2A, 0x0A, 0xA4, 0xE1, 0x44, 0xAF, 0x66, 0x9C, 0x9B, 0x45, 0xC0, 0xEC, 0xA1, 0xBC, 
    0x2D, 0x40, 0xDF, 0xBE, 0x9F, 0x37, 0xB8, 0x4F, 0xF7, 0xE6, 0xCA, 0xCD, 0x12, 0x5E, 0x8D, 0x4D, 
    0xFA, 0xDE, 0x69, 0x3A, 0x68, 0x26, 0x8B, 0x3D, 0x90, 0x14, 0xA8, 0x01, 0xA6, 0xFE, 0x78, 0x96, 
    0xF2, 0xFB, 0x77, 0x08, 0xB6, 0x31, 0x09, 0x91, 0x1D, 0xAC, 0xA3, 0x46, 0x9E, 0x85, 0xF1, 0x27, 
    0xE9, 0xA9, 0x2E, 0x1C, 0xB5, 0xCF, 0x74, 0x13, 0x52, 0xA0, 0xE8, 0x64, 0xE4, 0xB0, 0xBD, 0x87, 
    0xC6, 0x43, 0x10, 0xCC, 0x28, 0x62, 0x9A, 0x51, 0x21, 0x02, 0xA2, 0xF8, 0x4B, 0xFC, 0x7E, 0x8A, 
    0x35, 0x6A, 0x99, 0x65, 0xC1, 0xF9, 0x70, 0x06, 0x6E, 0xE5, 0xB9, 0xBA, 0x23, 0x1A, 0xEA, 0x07, 
    0xED, 0x7A, 0x9D, 0x30, 0x58, 0x76, 0x34, 0x48, 0x1F, 0x86, 0xEF, 0x4E, 0xD4, 0x29, 0x2C, 0x4C, 
    0x04, 0x71, 0x8E, 0xFF, 0x98, 0xB1, 0x53, 0x5D, 0xF5, 0x57, 0x39, 0x83, 0x81, 0x79, 0xA7, 0x73, 
    0xC5, 0xD6, 0x7C, 0x33, 0x8C, 0x2B, 0x49, 0x75, 0x32, 0x63, 0x1E, 0xA5, 0x24, 0x94, 0xD8, 0xD0
};

const std::uint8_t TwistExpander_Carbon::kSBoxE[S_SBOX] = {
    0xFB, 0x1D, 0x0A, 0x1F, 0x8E, 0x74, 0xEE, 0x81, 0x2D, 0x56, 0x61, 0x51, 0x9B, 0x04, 0x39, 0x7C, 
    0x0C, 0xA6, 0x94, 0x6B, 0x01, 0x97, 0x07, 0x60, 0x4D, 0x9C, 0xC0, 0xA3, 0x36, 0xB4, 0xE6, 0x6D, 
    0x47, 0x03, 0xBB, 0x32, 0x59, 0xA0, 0x62, 0x78, 0xB7, 0xC2, 0xE7, 0x16, 0x7E, 0x89, 0x5B, 0xA7, 
    0xBA, 0x6F, 0xDE, 0xF5, 0xC4, 0x57, 0xCC, 0x42, 0x22, 0xA5, 0x48, 0xE5, 0x1C, 0x44, 0xAB, 0xE4, 
    0xD9, 0xD0, 0x53, 0x2A, 0x5C, 0x98, 0x0F, 0x2E, 0x80, 0x3A, 0x72, 0xDD, 0xBF, 0x93, 0xCB, 0xD2, 
    0xF6, 0x70, 0x20, 0x68, 0x46, 0x75, 0x33, 0x79, 0x02, 0x7A, 0xBE, 0xD4, 0x64, 0x10, 0xE1, 0xE0, 
    0x06, 0x86, 0x4F, 0x77, 0x9D, 0x66, 0xB5, 0xA4, 0xE9, 0x99, 0xCE, 0x85, 0x6E, 0x38, 0xAE, 0xA1, 
    0x18, 0xB6, 0x05, 0xC5, 0xCD, 0x40, 0xA2, 0x8C, 0x50, 0x31, 0x67, 0x30, 0x4B, 0xED, 0xF8, 0xE8, 
    0x0E, 0x35, 0xD3, 0x1E, 0xE3, 0x21, 0x9F, 0x49, 0xF7, 0x2C, 0xF3, 0x4E, 0xF9, 0x0D, 0xB2, 0x90, 
    0x63, 0x3E, 0x88, 0x13, 0xA8, 0x27, 0x23, 0xC7, 0x71, 0xF0, 0xCA, 0xD1, 0xFD, 0x95, 0x37, 0x11, 
    0x0B, 0xC3, 0x4C, 0x41, 0xFC, 0x54, 0xDC, 0x7B, 0x83, 0x9E, 0x3B, 0x8D, 0x55, 0xCF, 0x91, 0xF1, 
    0x09, 0xE2, 0x2F, 0x00, 0x2B, 0xEA, 0xFE, 0xD7, 0x76, 0x1A, 0xFA, 0x6A, 0x8F, 0x69, 0xD5, 0xAF, 
    0x24, 0x87, 0xAA, 0xBD, 0x5E, 0x5A, 0xDF, 0x19, 0x84, 0x65, 0x92, 0xC6, 0x12, 0x26, 0x5F, 0x29, 
    0x08, 0xD6, 0xA9, 0x17, 0x8A, 0xB8, 0x14, 0xDB, 0x15, 0xC1, 0x6C, 0xBC, 0x3C, 0x1B, 0x28, 0xD8, 
    0x7D, 0xEF, 0xAC, 0x3D, 0x9A, 0xFF, 0xB3, 0xB9, 0x34, 0xB0, 0x4A, 0xF2, 0x96, 0x82, 0xC9, 0x8B, 
    0x5D, 0x58, 0xB1, 0x43, 0xC8, 0x7F, 0xEB, 0xEC, 0x73, 0xDA, 0x25, 0xAD, 0x45, 0xF4, 0x52, 0x3F
};

const std::uint8_t TwistExpander_Carbon::kSBoxF[S_SBOX] = {
    0x42, 0xA5, 0xFC, 0xD1, 0x5C, 0x0E, 0x6F, 0x95, 0x86, 0x6E, 0x23, 0x00, 0x71, 0x0A, 0x94, 0xA9, 
    0xAD, 0xEF, 0xB8, 0xF0, 0x10, 0xF3, 0x41, 0x1C, 0xB5, 0x1F, 0x8D, 0xF5, 0x5D, 0xAC, 0xC8, 0xA1, 
    0x66, 0x64, 0x65, 0x78, 0xA7, 0xBE, 0x68, 0x8C, 0xE7, 0xF9, 0xF7, 0x49, 0xDD, 0x32, 0xD3, 0xD0, 
    0x5A, 0xD5, 0x4C, 0xB4, 0xA8, 0x51, 0x0F, 0x7C, 0x4F, 0xA4, 0xAF, 0x83, 0x9A, 0x2D, 0x52, 0xBC, 
    0x22, 0xBA, 0x74, 0xE8, 0xBD, 0x3A, 0xE6, 0xCD, 0xAA, 0xDF, 0x5F, 0x07, 0x40, 0xD6, 0x61, 0xCE, 
    0xFF, 0x2B, 0x3B, 0xBB, 0x59, 0x31, 0x47, 0xB3, 0x5B, 0xF8, 0x7F, 0x9F, 0x39, 0x18, 0xA6, 0x99, 
    0x7E, 0xFB, 0xC1, 0x45, 0x20, 0x4D, 0x93, 0x9B, 0x01, 0x05, 0x7B, 0xB0, 0xEA, 0xAB, 0x48, 0x81, 
    0xBF, 0xD8, 0x35, 0x97, 0x30, 0x08, 0xCA, 0x28, 0x3F, 0x33, 0x72, 0x0C, 0xE4, 0x24, 0x09, 0x3E, 
    0xD9, 0x16, 0xF1, 0xEE, 0xD2, 0x04, 0x54, 0x90, 0xC0, 0xB9, 0xE5, 0xFE, 0x36, 0x92, 0xFD, 0x9D, 
    0x57, 0xFA, 0x0D, 0x53, 0x19, 0x55, 0x70, 0xE3, 0x14, 0xAE, 0x5E, 0x85, 0x13, 0x87, 0x62, 0x27, 
    0xC3, 0xC6, 0x8A, 0x37, 0x2C, 0x1A, 0x38, 0xC7, 0xE1, 0x6B, 0xE0, 0x17, 0x25, 0x44, 0xA2, 0x91, 
    0xB7, 0xED, 0xF2, 0x2F, 0xD7, 0x4A, 0x58, 0xD4, 0x7A, 0xCB, 0x7D, 0xCF, 0x63, 0x84, 0xA0, 0x77, 
    0x1E, 0xC4, 0x6D, 0x34, 0xC9, 0xEC, 0x73, 0x80, 0x8F, 0x06, 0xE9, 0xDC, 0x6C, 0x6A, 0xF6, 0xA3, 
    0x88, 0xEB, 0x26, 0x76, 0x79, 0x2E, 0x3D, 0x56, 0x02, 0xB2, 0x9E, 0x0B, 0x8E, 0xF4, 0x9C, 0x1D, 
    0x96, 0x50, 0x3C, 0xB1, 0x4E, 0x67, 0xC2, 0x11, 0x29, 0x89, 0xDB, 0xDA, 0xCC, 0xDE, 0x15, 0x46, 
    0x82, 0x98, 0xB6, 0x43, 0x2A, 0xE2, 0x75, 0x1B, 0x60, 0x69, 0x21, 0x03, 0x12, 0x8B, 0x4B, 0xC5
};

const std::uint8_t TwistExpander_Carbon::kSBoxG[S_SBOX] = {
    0x9C, 0x27, 0x46, 0xAC, 0x4E, 0x1D, 0x76, 0xEB, 0xA7, 0x7A, 0xF7, 0x77, 0xA4, 0x49, 0xE7, 0xB5, 
    0xE1, 0x0A, 0x01, 0xD4, 0xCF, 0x20, 0x68, 0x5D, 0x9F, 0xA9, 0x95, 0x8C, 0x42, 0xED, 0xDE, 0x73, 
    0xBC, 0x44, 0x48, 0x6E, 0xDF, 0xAD, 0xD6, 0x99, 0xCC, 0x1E, 0x74, 0xAE, 0x3E, 0x43, 0x54, 0xA0, 
    0xE2, 0xF8, 0xF6, 0x93, 0xB9, 0xD0, 0x11, 0x3A, 0x02, 0x2B, 0x19, 0xFF, 0x8D, 0x9D, 0x24, 0x55, 
    0xFB, 0xF9, 0xFC, 0xAA, 0x59, 0x85, 0xC0, 0x86, 0x41, 0xC6, 0xBA, 0xD7, 0x64, 0x0C, 0x1C, 0x72, 
    0xB2, 0x31, 0x89, 0xF5, 0x16, 0xB7, 0xC4, 0x33, 0xEE, 0x12, 0xCE, 0xD5, 0x71, 0x09, 0xD3, 0x79, 
    0xC2, 0xE6, 0x14, 0x3C, 0x03, 0xFA, 0x47, 0x81, 0x7B, 0x2F, 0x9A, 0xC7, 0x52, 0x4D, 0xA2, 0x07, 
    0xA1, 0x66, 0xE3, 0x13, 0xBB, 0xB1, 0x26, 0xC5, 0xDD, 0x4F, 0x50, 0xE5, 0x38, 0x57, 0xBD, 0xD1, 
    0x6A, 0x63, 0xD8, 0x06, 0x58, 0x23, 0x88, 0xB3, 0x18, 0x0D, 0x34, 0xBE, 0x17, 0x4B, 0x4A, 0x2D, 
    0x7C, 0xEA, 0xE9, 0x28, 0x05, 0x84, 0xA8, 0x98, 0x9B, 0x15, 0xB6, 0x53, 0x3B, 0xAB, 0xE8, 0xA3, 
    0xEC, 0xB4, 0x35, 0x1B, 0x91, 0xF1, 0x7D, 0xB8, 0x60, 0x22, 0x6C, 0x6F, 0x5B, 0x30, 0x87, 0xBF, 
    0x67, 0xF2, 0x2C, 0x65, 0x00, 0x5A, 0x1A, 0xF4, 0x96, 0x2A, 0x36, 0x7E, 0xE4, 0x5F, 0x7F, 0x08, 
    0xA5, 0x4C, 0x8E, 0xEF, 0xD2, 0xFE, 0x5C, 0x0B, 0x6D, 0xDB, 0xA6, 0x32, 0x82, 0x2E, 0x78, 0x8B, 
    0xCD, 0x5E, 0xAF, 0x04, 0x62, 0x69, 0x25, 0x70, 0x8F, 0x3F, 0xD9, 0x45, 0x61, 0x80, 0x21, 0x51, 
    0x1F, 0xDC, 0x29, 0xCB, 0x0E, 0xB0, 0xE0, 0xC3, 0xC9, 0xC1, 0x92, 0x9E, 0x8A, 0xCA, 0x97, 0xC8, 
    0xF3, 0x75, 0x6B, 0x90, 0x3D, 0x94, 0xF0, 0xFD, 0x10, 0xDA, 0x0F, 0x83, 0x37, 0x39, 0x56, 0x40
};

const std::uint8_t TwistExpander_Carbon::kSBoxH[S_SBOX] = {
    0x76, 0x3F, 0x8F, 0x58, 0x4B, 0xB4, 0xA1, 0xDF, 0xBD, 0x71, 0x63, 0xE1, 0x9C, 0x7E, 0x0F, 0xB0, 
    0x7A, 0xED, 0x08, 0x00, 0x89, 0x0A, 0x7C, 0x06, 0x57, 0x0C, 0xF2, 0x1A, 0x9B, 0xAA, 0xA5, 0xF5, 
    0x34, 0xEE, 0x3E, 0x09, 0xE5, 0x18, 0x61, 0x22, 0xA8, 0x95, 0xC0, 0x39, 0xD7, 0xDB, 0x82, 0x88, 
    0x5B, 0x92, 0x23, 0x87, 0x60, 0x14, 0x64, 0xC3, 0x29, 0xEF, 0xA0, 0xA7, 0x5A, 0x36, 0x1E, 0xC2, 
    0xB3, 0xD2, 0x86, 0x2D, 0x12, 0x9E, 0x78, 0xBF, 0xBA, 0x0D, 0x41, 0x21, 0xAC, 0x98, 0xF4, 0xB5, 
    0x85, 0x26, 0x4E, 0x02, 0x51, 0xD1, 0x6C, 0x47, 0x8B, 0x45, 0xC9, 0x40, 0x94, 0xCC, 0x35, 0x50, 
    0x19, 0x4F, 0x30, 0xB6, 0x69, 0xF3, 0xCF, 0x8A, 0x31, 0xFB, 0x03, 0x4D, 0xF7, 0x6A, 0xE9, 0x7D, 
    0xC8, 0xCD, 0x1B, 0x05, 0x01, 0xA4, 0x7F, 0x2C, 0x84, 0x0B, 0x96, 0x6E, 0xA2, 0xA3, 0x74, 0x54, 
    0x1D, 0x99, 0xD0, 0x3D, 0x52, 0x2B, 0x0E, 0xC5, 0xE0, 0xD8, 0x72, 0x55, 0x11, 0x1F, 0x5F, 0x9A, 
    0x04, 0x9F, 0xBE, 0xCE, 0x1C, 0xDE, 0x4C, 0x62, 0x43, 0x70, 0x91, 0xB7, 0x83, 0x6D, 0xFE, 0xA9, 
    0xEA, 0xF0, 0x32, 0xC1, 0xE6, 0x16, 0x44, 0x20, 0xB8, 0x6B, 0x68, 0x49, 0x73, 0x66, 0xFF, 0x15, 
    0x8D, 0x37, 0xDA, 0xEC, 0x48, 0x33, 0x81, 0x42, 0xD3, 0xAF, 0x13, 0x65, 0x2E, 0x67, 0x25, 0x8C, 
    0xDC, 0x2A, 0x7B, 0xCB, 0x75, 0xE7, 0x46, 0xAD, 0x28, 0xF1, 0xFD, 0x07, 0xAB, 0xBB, 0x10, 0x2F, 
    0xE8, 0x27, 0x79, 0x5C, 0xD9, 0x3C, 0x5E, 0xD4, 0x3B, 0x97, 0x90, 0xAE, 0xF8, 0xCA, 0x4A, 0xD6, 
    0xD5, 0xC4, 0x8E, 0x9D, 0xF9, 0xE4, 0x3A, 0x59, 0xFC, 0x38, 0xC7, 0x17, 0x6F, 0xDD, 0x93, 0xBC, 
    0x77, 0x80, 0x5D, 0xA6, 0xF6, 0xB2, 0x56, 0xC6, 0x24, 0xB1, 0xB9, 0xEB, 0x53, 0xE2, 0xE3, 0xFA
};

const std::uint64_t TwistExpander_Carbon::kSaltA[S_SALT] = {
    0x4CC691477BDF29AEULL, 0xAEE6AA9EB28D90D7ULL, 0xBB44F33BA5AF8046ULL, 0x2EC5B602ECC0E93AULL, 
    0x3BA69986676CA84CULL, 0x6BF2B268FE29A438ULL, 0x05DD6A2F8EE72198ULL, 0x49B0D8CE8220B214ULL, 
    0x23C0A386A6789E03ULL, 0xCBCCD7120440F3C8ULL, 0xAE1877F79598137CULL, 0x0D064580B33D974DULL, 
    0x7DD09472B2FE2FAAULL, 0xA2500E80F4621E84ULL, 0x8B334C2FDE6D4B0DULL, 0x6B9BEA3E7C233CE0ULL, 
    0x9FBC8A457FA52C98ULL, 0x9A4005B92C610A86ULL, 0x0AB768E8C149BFBDULL, 0x70C7C896D1A9C9D9ULL, 
    0x712417D0A99ABD8AULL, 0x2A67306B367DB2BBULL, 0x535E131CFB69238CULL, 0xD0D2A5E1E7B91845ULL, 
    0x35AECD0FA7C5FF14ULL, 0x682FA2129CC59B7CULL, 0x6517B6E665D32D0EULL, 0x504B70C4D98C0576ULL, 
    0x284314B9E638BCDBULL, 0x4C171064D9804C8EULL, 0x4F13CD788D660A48ULL, 0xEB4E39AAA53448B8ULL
};

const std::uint64_t TwistExpander_Carbon::kSaltB[S_SALT] = {
    0xCD85C9BB16CAF2CFULL, 0x9D431F60FC00A1BFULL, 0x987F0AD5460E25B5ULL, 0x5F531F4BBEBE66DCULL, 
    0x3F3C6A2C92D6EB41ULL, 0x31C7C90D8514F69EULL, 0xA1D4CEEEF0C44A47ULL, 0x7AABC85ECF56C8D0ULL, 
    0x73373D82D71A059AULL, 0xE5C50106478E602BULL, 0xC7A210810C3E171AULL, 0xB27B19A310B8B64CULL, 
    0xC4D3F182D7A5DB58ULL, 0x0C08257D863E447FULL, 0x9E96212E8E39AB43ULL, 0xD35FDCC58F2A0D76ULL, 
    0x9D063A58514B5B6FULL, 0x8EEEACD4DCF615B4ULL, 0x9F74604D15CDF829ULL, 0x1012891EC2A870A7ULL, 
    0x39184E6BF70C3057ULL, 0x0556C8E862D12620ULL, 0x6CC4C473928928E4ULL, 0xEFFD2ACE15988BA7ULL, 
    0x7551FD439DD9A77BULL, 0x0B4025609CF63C1CULL, 0x0A79B860BE9A8836ULL, 0xE53162DC6F171766ULL, 
    0x0C20F658B6EC94C8ULL, 0x179A737100F43C88ULL, 0xA261EAE9FD3BA1D7ULL, 0xD9EBBCC87F2730DAULL
};

const std::uint64_t TwistExpander_Carbon::kSaltC[S_SALT] = {
    0xBAF61E69208BEAF3ULL, 0xB215BD5FE550C8F8ULL, 0x48C4F2CEF0D31C2AULL, 0x49185F2E240B672CULL, 
    0xC14F3401C2FA696BULL, 0x92306843A81F3481ULL, 0x5EE66212C026FC6DULL, 0xDD59D9507DD7DF7DULL, 
    0x4FDDFA8966672E42ULL, 0xB60C0C15BEDF547AULL, 0x9C631BF6C6646E75ULL, 0x3B6860D56985A331ULL, 
    0x335A0E0AF84E0740ULL, 0xBC8F5B18A53FAF04ULL, 0xFC7FD9DB668CC139ULL, 0xDE7339207EAE8A63ULL, 
    0x4BD9D58FEFA9A23DULL, 0xE18FB1CE6DDAA8E2ULL, 0x0177FBAC4AC7E3A6ULL, 0x2A42041510E15995ULL, 
    0x1B528B1A6858245EULL, 0xFB784E404A1D677BULL, 0x3C037FDE619857BCULL, 0x774E803243437F32ULL, 
    0x3534E60D41055903ULL, 0x7E7C042C85455697ULL, 0xC70EBD26E0DD2D36ULL, 0xEC772A514463726AULL, 
    0x4EB6A5108AC5F9C9ULL, 0x12CB9A3915EF8F5BULL, 0x990F8F73922FA2D3ULL, 0xDA6B6B9DA24BC99BULL
};

const std::uint64_t TwistExpander_Carbon::kSaltD[S_SALT] = {
    0xEB3DBFEAD1EC3044ULL, 0x71D18B96B20A36F6ULL, 0xE00673E6CA3913A2ULL, 0xF000420C0C962A55ULL, 
    0xF246A429EBAEE4AEULL, 0x73E61A28A019F575ULL, 0x3646806C0735FCD2ULL, 0x265423936DCD483FULL, 
    0x382E624AF085731AULL, 0x23EF6635D0B75425ULL, 0x95E61009B6649792ULL, 0xD929E933C091539CULL, 
    0x14BFD21A0499CD95ULL, 0x4C3D56B9596A65F9ULL, 0xF2EF7060F3B66A4CULL, 0x175824EBE40C172CULL, 
    0xCEE3232DFB058D45ULL, 0x692068DE5C5E005BULL, 0x5FEBC7AE40C872EFULL, 0x4904106F36EE12E1ULL, 
    0xD7B95AA89766F842ULL, 0x50DFB92DB9E4B3BBULL, 0x153C00AD3C5C2788ULL, 0xADF69DFD6782997AULL, 
    0x6F3471C5631140D6ULL, 0xCEB7CAC1088F419AULL, 0x159970979387E9E4ULL, 0x26CAAED884D0ED77ULL, 
    0x42FAB3FC09C2BF0AULL, 0xA0D435E2C7590E2AULL, 0x0B7228D4A4ED280AULL, 0x3C785E68276E06A6ULL
};

const std::uint64_t TwistExpander_Carbon::kSaltE[S_SALT] = {
    0x2E6B571D444CCADEULL, 0xA122DBA2D0861A89ULL, 0x6DF19502882B3787ULL, 0x3A6522DAB73B9055ULL, 
    0x8C4F7524634421F5ULL, 0x65127E7E4E5AAC1AULL, 0x64A2CD94679B7329ULL, 0x5C3FBE3F16CF84B5ULL, 
    0xAE119C62C7B96FA7ULL, 0xFDB56842BD6EA28DULL, 0x1603C4B884758C4FULL, 0x4FB1AA1A20B2096EULL, 
    0x594EB1EE987197D5ULL, 0xA7F15995AC2666F8ULL, 0xEBF029A88F80848AULL, 0x0308595AFDDD27B1ULL, 
    0xD03F81F71C21C550ULL, 0x87442CD89C8B9EEAULL, 0x55DA797C0461C142ULL, 0xCB7BDCF7F326C57EULL, 
    0x9BCF4774F346885AULL, 0x8118FFA8F613BC46ULL, 0x8F29A075AA420B84ULL, 0xFD25390BF281F1DCULL, 
    0x32F98CF4E7C20D35ULL, 0xC64126BDBBCBBA6BULL, 0xD28A1D2A8427CB70ULL, 0x8F9E1C29E0B4441FULL, 
    0x47FD220769B4A617ULL, 0xA088AA730CCE6536ULL, 0xA3467FC0FEBD83ACULL, 0x22D39556FDC6BD0CULL
};

const std::uint64_t TwistExpander_Carbon::kSaltF[S_SALT] = {
    0x6A0D07261206795FULL, 0xAA32DBDF5C4338DFULL, 0xA9B17FABF84DFF92ULL, 0xAB26E343430677C4ULL, 
    0x98AAEB28E2DB2D78ULL, 0x39C10664A28AAC0EULL, 0x7040CE57BA39C6A5ULL, 0x4DF9073239023C37ULL, 
    0x63EB163CF9EA9C27ULL, 0x0A433C3C50CBDAD6ULL, 0x759842045C1CA576ULL, 0xE034F118A80488EBULL, 
    0x6BDA07E9BEB18C05ULL, 0x910C6D50510614E2ULL, 0x475F5A9C8FEC9C1CULL, 0xA2B5458AB208C6A4ULL, 
    0x5A1F450A7DCBF36AULL, 0x09FA285C46CB709AULL, 0x92212C406AAD7E60ULL, 0x4B57B6AC45DF0D20ULL, 
    0x01286FD3A1CCD9B6ULL, 0x98807D7D110328B6ULL, 0x502BB753632948D6ULL, 0x684D3610F68BB96AULL, 
    0x1A61CD2D2D3B92FFULL, 0x69C08EAC3252C545ULL, 0x1E4032AAD94466CBULL, 0x23163152DAE6C064ULL, 
    0xF47C5B7E980E2FE5ULL, 0x80018FE215AB948EULL, 0x3ECB2D64BB1EDC59ULL, 0x32C6AEA65CBC7483ULL
};

const std::uint64_t TwistExpander_Carbon::kSaltG[S_SALT] = {
    0xFB83742637AFDF8DULL, 0x3DB327CB53F27564ULL, 0xDFADD5B63B625FABULL, 0x2C1ABF5DC998BDD9ULL, 
    0x39D5264890A61831ULL, 0xEEA0D03C43E2636AULL, 0xEC46AC79419218A9ULL, 0xD75FF4FFA44A620DULL, 
    0x9DA5856DFA80EEBCULL, 0xB0DB93768E22367BULL, 0x1F81D821DFB7115EULL, 0x841165DB3A4CD14DULL, 
    0xC9CA6514F4D603B0ULL, 0xDA8CAA4C86FBFA6AULL, 0x556C40AEB209082EULL, 0x06496A5D85EBDDE9ULL, 
    0xAC1F61666178B44FULL, 0x7307E192B8057E67ULL, 0xC3D016DA89A9E8FDULL, 0x9664EB1B2C237DECULL, 
    0xB207C6F7D6D15D8EULL, 0xE45DDE55B999A317ULL, 0xC36B7AA6E0916A45ULL, 0x014EA2A8933B6429ULL, 
    0x38F0D3992361E09BULL, 0x52A22501643B232DULL, 0xDFC2B10052D178CCULL, 0x2778A6D2C9C2764BULL, 
    0xDC5C594FC366AA81ULL, 0x59332C52B8763D8EULL, 0x1196C4FA4F6EB819ULL, 0xDF56E403C40B3904ULL
};

const std::uint64_t TwistExpander_Carbon::kSaltH[S_SALT] = {
    0xE92E90066C607FECULL, 0x3B07148E61599F2FULL, 0x5CA412CCD2F59725ULL, 0x1BABA7BB7ADFA7D1ULL, 
    0xBC3A58BF346018CFULL, 0xC87896D2C6835FDBULL, 0x40E99A9532F5A0E4ULL, 0xE1B48199BCA9305DULL, 
    0xA96A985FEDAA245DULL, 0x3D306F715CDB9A4EULL, 0x570711F3F099BEA3ULL, 0x21A77A1987A3D643ULL, 
    0xCE39CDDEF925928BULL, 0xEF28B1911AFDA53AULL, 0x0079BF956470F24AULL, 0xE9546D6F604F9D4FULL, 
    0x48332305A4F794D6ULL, 0x93388AA41F7458E9ULL, 0x3E8489BCC1DD6647ULL, 0x4DDE7D6F505AF251ULL, 
    0xFA904E4231CCB256ULL, 0xF6DD20E189FA136EULL, 0xD14061745B813E4CULL, 0x7E813788BF025041ULL, 
    0x57C982F9927A3C38ULL, 0x236000B20143E496ULL, 0x2DAAE84BC14CDC7DULL, 0x42049B7D3B115907ULL, 
    0x47DFB0000312E78AULL, 0xF1221C7777A20005ULL, 0x420036F9C5226638ULL, 0x8AD9B243F891E645ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltKeyBoxA[S_SALT] = {
    0xBF45748331444061ULL, 0x0D1A2CBBCE19C130ULL, 0x54A157CAE137391CULL, 0x12EE3585D5DE64B9ULL, 
    0xA23FFA6C08D4B2F8ULL, 0x649CC2CECA976841ULL, 0xB5AF3CA65856C7FFULL, 0xFDED35A38854CF6BULL, 
    0x68BD08043982DBDBULL, 0x8B727D51146FC39CULL, 0xDFA1F73F4DFF7315ULL, 0x0F0268CBC79BB559ULL, 
    0x7839BCD5CEBCF90DULL, 0x09864374A4CC43F6ULL, 0xFF8A008F28D0FADFULL, 0x310BE792109CFFAFULL, 
    0xE97C0040E606DA8EULL, 0xD34AC42AF967B359ULL, 0xFD9F4DFAC81A7813ULL, 0xE4764110EAFA8C3DULL, 
    0x7AFD66B7F21384BAULL, 0x0155A8F4CD1B5C90ULL, 0x3A70509D8F0F1DC3ULL, 0x1FFB363428CB2AA9ULL, 
    0x553425928BBC3722ULL, 0xA16748611A229AA3ULL, 0xAF059F508CD8E3BAULL, 0x5000F4218E85987CULL, 
    0x753FDBC8222F3657ULL, 0xD3C087DDD06A4849ULL, 0xB1CC751372720F61ULL, 0x7D7CB57675FAE768ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltKeyBoxB[S_SALT] = {
    0x07C21BC36CABEAC5ULL, 0x77871F44504A0C31ULL, 0x01C3C1E60D45ED73ULL, 0xD7D481371D8A7705ULL, 
    0x2DA4F11F0DB9FE70ULL, 0x5F8162B91E8429E3ULL, 0x7ADC87264518602DULL, 0xAC3EFDADD8E2FE3AULL, 
    0x12B94E7F43EBE572ULL, 0xF9B0D0ADDC5D9ED0ULL, 0xE59EF912FA4CA105ULL, 0xC1B0DB58C1913E32ULL, 
    0xE5F9B899F4E08CF5ULL, 0x38582F7C7FDB2ED5ULL, 0xE5CC18E3E0707468ULL, 0xB1793F89535CE30DULL, 
    0x05F931509968CE9FULL, 0xD8A4432B64D08A9CULL, 0xD7C51AC4ACAFC7C2ULL, 0xAAB6A838DDE9A7FDULL, 
    0xF3A02502282C6769ULL, 0x10C3F453F9B95215ULL, 0x22E8544334758C10ULL, 0x686D8C0B5343D6C5ULL, 
    0x7A52186B36F273A9ULL, 0x4CF98C837E578BA9ULL, 0xAE6EBBA90C713732ULL, 0xA8391047D2F747EFULL, 
    0xF0C0D4E8E77AF418ULL, 0x8D5D23CB37B1CA70ULL, 0xC2131E033E64FC88ULL, 0x965D3E7BC6E13B8DULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltKeyBoxC[S_SALT] = {
    0xCED3A611717C3D74ULL, 0x262C1AAF9A34E526ULL, 0xE9BB8D729B5F19FBULL, 0x5C7DA860F474EC8AULL, 
    0xDE12CE624451F0DBULL, 0x45A03E3CA04C996EULL, 0xD36756D143930E19ULL, 0x00F0B6DB4B546B7FULL, 
    0x7FF0FE8B453AD6D3ULL, 0x0CED9912F42613C7ULL, 0x7455B6F5B16CE59CULL, 0x494C872DE57492E0ULL, 
    0x76D022A47E590116ULL, 0xC7A715CD47421A0CULL, 0xC223B33DCEA3624DULL, 0x7DBCFD3578672DE7ULL, 
    0xBCF3F3F6FA902756ULL, 0x5864663A67F8567AULL, 0x5A81611C5ED3CDC0ULL, 0xCB51FF1C9DCBCA76ULL, 
    0xA2662940BB52B909ULL, 0x64B9C655FE67CEDEULL, 0x08428BAF6C85BA45ULL, 0x70BEC853674D305EULL, 
    0x5B0E0552E60D1BE3ULL, 0x4127A5723BF25814ULL, 0xB187FAA0E4EDDAC2ULL, 0x82B37726A9248689ULL, 
    0xDB61EFC02159F3FCULL, 0xC03A84B47FBD874FULL, 0x8F68A6FD0E67EAD3ULL, 0x83502B6EA630BEFFULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltKeyBoxD[S_SALT] = {
    0xC2D9AD7199A0B158ULL, 0x6AA1059EFF762258ULL, 0xFB14F0A5AD0CE532ULL, 0xD2F0DD19311343EDULL, 
    0x863209EE1855E072ULL, 0x4631BAD4F54A7D18ULL, 0xBDA9521505BDE4F6ULL, 0x2AFF8D1D1C5F44A3ULL, 
    0xE5CB862CB2E51670ULL, 0xC18540A20BE62948ULL, 0xBDDD5D31929E4653ULL, 0xE03B4EFEFBB6A777ULL, 
    0x57C7D73FCC5BAC60ULL, 0x00728D1F834DEB7AULL, 0xA51B74FF6D0364F6ULL, 0xF1DB5C102FACD35EULL, 
    0xF7B8CE2E83B5F96DULL, 0xC9F6BF5292B2E56AULL, 0xF399CD7AC8B2A27FULL, 0xCDB877D2D886172BULL, 
    0xB5AF98BF9E59F0EDULL, 0x6FC29592F269C935ULL, 0xC22398EC2C09D139ULL, 0x0F96D6B1E2EDCA1AULL, 
    0x0A7E3788208419B7ULL, 0x483DB5AC9E003D84ULL, 0x09C4CAAAC8FCAA38ULL, 0x7D820E246A49A015ULL, 
    0x9E462BA1AC3733EFULL, 0x8EA72D521E048E8BULL, 0x685F3A8945DE3B9EULL, 0xCDCAFC303CBEF29EULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltKeyBoxE[S_SALT] = {
    0x71C5E9FA95B9E06CULL, 0x4B39CD6D0D15FF84ULL, 0x6E7FF18E2F5EF4DDULL, 0x0BE6728006C1E037ULL, 
    0xD016316052945332ULL, 0x29C542F7BE9BE221ULL, 0xF312D186748C2CE1ULL, 0x429CF9B094EE3C8FULL, 
    0xFCE0714C9E2F89A1ULL, 0xDE6134FA6F9FCF7DULL, 0xBBCF7E40C8E9256FULL, 0x5C91C52EE0086399ULL, 
    0x7D7265234187DF02ULL, 0xD6E8D5B6D8283D09ULL, 0x56E92ED0350994D8ULL, 0xF9F36015D4A0EFC0ULL, 
    0xB47D591C55C5AD6AULL, 0xB3F379C8A88A0F3EULL, 0x568C99DA1DC03517ULL, 0x8C7ECF54C5E9BAF1ULL, 
    0xBE5D45B3B9097599ULL, 0x5342803D308F6099ULL, 0xD6B8C4538D489A84ULL, 0x3C1988A0ED9265B7ULL, 
    0x2D5CE032087FF38EULL, 0x7C0CBF5F1C5482D6ULL, 0xBAB4BB1AF109107DULL, 0xD06A61E8B201C133ULL, 
    0x87A8A220130E34FFULL, 0xE28903729EA12632ULL, 0xC03E5C359D369253ULL, 0xC65C6B4B3E0860F1ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltKeyBoxF[S_SALT] = {
    0x2345F3C322E94EA7ULL, 0xB3D4B5D1015496C4ULL, 0xD232D99E7BE849FBULL, 0xCE04C7F77839D762ULL, 
    0xF3C394431E1170A3ULL, 0x3C18F3D6782D0987ULL, 0x6BE9A8C14DDBBEA7ULL, 0x294E97D408713B45ULL, 
    0xDC0EDA1E3BE4DDB3ULL, 0x2764853BCB90930DULL, 0x40971A8ED0FD65B7ULL, 0xB24DD4ECBC08EC4CULL, 
    0x6BAE4D81915FE803ULL, 0xADAEB6AB1A7C2644ULL, 0x0B4AF17DC640DC37ULL, 0x1354220342B5914EULL, 
    0x6493B68F29C8DFF0ULL, 0x5BEADBC748F2DDAEULL, 0xC05B71519013CA92ULL, 0x907E97D51EAA85C9ULL, 
    0x41CB287443561C84ULL, 0xB33FCE0A42B6A5C0ULL, 0x39ADD8F9E5EA4EBDULL, 0x1BE51845E0EE1895ULL, 
    0x484144C69361DAB8ULL, 0x6AE0FAFB6E0033FEULL, 0x1D21A9B82DDFEDFCULL, 0xCAFF44D4EA28F75FULL, 
    0xA2338DF31C22E5B6ULL, 0x239E49B28BBA8C0FULL, 0xA59F19374F9B29A5ULL, 0xC1F9E1590629829EULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltMaskBoxA[S_SALT] = {
    0x55C4999FAE946592ULL, 0xE73B74D138E0EDC9ULL, 0x69160F9C75191750ULL, 0xD7F41DADEA7B848EULL, 
    0x8E1A07A2AEB3F16CULL, 0x307389BB14685101ULL, 0x85BFBECD0C8CEAA6ULL, 0x3FEE889847DA82CDULL, 
    0x1E7D3FB6BEC28247ULL, 0x0E2735B06A86ADD5ULL, 0x2CDE5479977BB409ULL, 0xD3FF57AED8C70A66ULL, 
    0xF87433EAF0BA0797ULL, 0x8A5F11B355CC289FULL, 0x0D6EBA5E06898EDBULL, 0xC12F608E6808509EULL, 
    0xE94A7A727A1D0EE8ULL, 0x333E91158945D60BULL, 0xB6638D24C0986474ULL, 0x69C8D093C8171447ULL, 
    0x6666071D5526C14BULL, 0xC24E3520A1600E00ULL, 0x7E9457EC7E66769AULL, 0x6FFB80479B947F55ULL, 
    0xCBEF6FB42148C10BULL, 0x8C1398017CF4CCEAULL, 0x9616851471F77B2CULL, 0x899C96C0F880A4A4ULL, 
    0x2F273D7E7DE57803ULL, 0x0634107892CE930CULL, 0x734A1548DE51E113ULL, 0xA3BB20015A6E70D6ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltMaskBoxB[S_SALT] = {
    0x60667B60D302A13FULL, 0x57BAA7F5077805A9ULL, 0x3139941AEF9CE84BULL, 0x0A3B1A2D49A749C4ULL, 
    0x595E8FA3E5B01923ULL, 0x3CDF3E6BBC3BF6D6ULL, 0x16F8954BA61F0377ULL, 0xD10F6B54FFEFE6C4ULL, 
    0xEAB81D29A15C9210ULL, 0xCD9CDED1F1D17F86ULL, 0x326223D2A60FEE46ULL, 0x2DF82E17C891C943ULL, 
    0xDA2AAD3BD627E740ULL, 0xAA8AB5ADA966B959ULL, 0xB5E8473B85252BC8ULL, 0xA8625E7BD5ED1E49ULL, 
    0xA75A0ABACE2B3761ULL, 0x826C588ADC70DB55ULL, 0x31C922744484F421ULL, 0xC1D819E855760DE5ULL, 
    0xE3A04A65049423CCULL, 0xE14785892C179F77ULL, 0xB7AA56A9B0D7223DULL, 0xC28945D854516291ULL, 
    0xF00B588FAE995D81ULL, 0xAB94AA32F6A2A202ULL, 0x844BBB5DADEC1BB0ULL, 0x4E9B1196D13533C6ULL, 
    0xDFADA308B3AC944FULL, 0x5351E52935498011ULL, 0x649A48B5EA139117ULL, 0x44F773FE74D9F7A4ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltMaskBoxC[S_SALT] = {
    0xB827584E684E0092ULL, 0x8B718B2BC5CE5FFEULL, 0x4E83379A462710D4ULL, 0x03F85018B9BC3433ULL, 
    0x2BD7680354F197B9ULL, 0xA5C7B54B15A6AC5FULL, 0xB992602AEAC63B6AULL, 0x8A421A1AD8F4A0C4ULL, 
    0x8F79CD1A71F0989CULL, 0x72FF0A9786DA6219ULL, 0x80E726B1A66CAD45ULL, 0xAD0EA8555CC906CFULL, 
    0xFBD2217FB75AB5EEULL, 0x8B95A62831A9D436ULL, 0x82A9750196099974ULL, 0x73B7D4CA91339A37ULL, 
    0xED1A5A367611910FULL, 0x00122BA2A7C36C12ULL, 0x0799A2D87A9D8336ULL, 0x8831BD9EE97AB4C7ULL, 
    0x570C96E9B5DF0C0AULL, 0xB802F6F7B9399C8AULL, 0x40B06D67F4ECEDFBULL, 0xEC0C2C6A8802A299ULL, 
    0x2F2BC55E60912C86ULL, 0x60F8E5C808E96B5CULL, 0xD14797A2EF496354ULL, 0xFC64450E8FB42CE7ULL, 
    0x930A9F821ADE52C4ULL, 0xFF939692B3DC2311ULL, 0xFBE8F552CD91D9A2ULL, 0x75C4C4980AF1C4D1ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltMaskBoxD[S_SALT] = {
    0xF98FF75AA224808AULL, 0x0257091E3739F74FULL, 0x10FF34C9284EDEC7ULL, 0x113FB593CF890B1EULL, 
    0x5291F4A00DBF0B12ULL, 0x7D89FB46DAEE15BFULL, 0x033904317BAF2C75ULL, 0xA3C69458A11D5276ULL, 
    0xC23CC77361C3B9A3ULL, 0x79B7E4154D760812ULL, 0x247802811926062CULL, 0x418B3235BA37BF5BULL, 
    0xF722D67D43DC7B30ULL, 0xFAA431D6C519D62EULL, 0x8D927308DF856FCAULL, 0x0FC03A8EEDA2C17EULL, 
    0x63E345FCAC34F87DULL, 0x309022CBFFE0C715ULL, 0xDE951FAA55BCA997ULL, 0x2EDF48CA6C2FE4AEULL, 
    0xED48CD8BAE0EA785ULL, 0x08E46563638858B8ULL, 0x542A2C08D45894C3ULL, 0x544B2DD6423EB8A5ULL, 
    0x62B80BF2850C3956ULL, 0x5AC62A53026304C5ULL, 0xCFF626CA6008C0B1ULL, 0x69D34E9AAE5580B4ULL, 
    0x4325D76226A9D522ULL, 0x13C0C3BFF7BDA9C4ULL, 0x781D989A6801AFF8ULL, 0x2CC77A818920987AULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltMaskBoxE[S_SALT] = {
    0x67552C990FC36A02ULL, 0x2B8E7F9FCDD4CFCCULL, 0x1308A75EC8CAA121ULL, 0xDB1465E13433DE62ULL, 
    0xF652AB2554398CE6ULL, 0x7F2888BB03869CC1ULL, 0xF35806AE3041D976ULL, 0x1D0A5EDD2CC253BAULL, 
    0xEDBDFD8879246E5CULL, 0xBCE9FBF6790204E8ULL, 0x170B6533E9FA047CULL, 0x2AD0852BA55358C7ULL, 
    0x0D2C8B0D247A2B5CULL, 0x999B1587DA37DB1DULL, 0xCCE610EFFEA973C8ULL, 0x67C7F0654AF80C24ULL, 
    0x9ADFEAA4C0CBA33DULL, 0xA1FB17ABF549DA3BULL, 0x92C5F83E3EE65583ULL, 0xC537A9E76C52A80DULL, 
    0xB3D095940DCB4676ULL, 0x169741AF4B046C30ULL, 0x5889DE983427EC09ULL, 0xC1DB21EDBB7CA7B2ULL, 
    0x979C303D367A0F9AULL, 0xA03BC30D2771B684ULL, 0xA60EB3B5E8A4D11CULL, 0x42C030FBB50BC6B2ULL, 
    0x1D0FE7B0190DA4E6ULL, 0x1796C4DF2BC98C57ULL, 0x3E1D14A5E036857AULL, 0x6C0D1745AF081068ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltMaskBoxF[S_SALT] = {
    0x91B634BD035DA301ULL, 0xD1C8B2AAC034ACD1ULL, 0x10FE01D54D98D36AULL, 0xFB10FC2A689EB9B1ULL, 
    0x93FCD6B1CF436378ULL, 0xA5F8494354254F01ULL, 0x0DF9651333E84A27ULL, 0x1607DAB7CDFD3EECULL, 
    0x166689723FEF2762ULL, 0xE2D75F53B2AA46DEULL, 0xD417C2B29A315639ULL, 0x6A1AE2DAB709DCEBULL, 
    0x41F59A3148B5EB5CULL, 0x674127C3EEF56A50ULL, 0x25673E605D5772A3ULL, 0x0D097FBB709E4DDCULL, 
    0xF1712C893571563FULL, 0x5E249509673B31F3ULL, 0x50C18C9F3B55C3CEULL, 0x341688F646F34360ULL, 
    0xBF9E881BB245374EULL, 0x29A7F85C9186D091ULL, 0x4A0FDA04F999CC18ULL, 0x85B31000AC412B96ULL, 
    0x7A72CB90E6FFC0F5ULL, 0x98EA4928E0FC2E3BULL, 0x42071394B3EF87D9ULL, 0xA23DF8FC30A256EEULL, 
    0xD998465D760BE6D3ULL, 0x691D9D6A80C1C24EULL, 0x8B4EF4A990CF3039ULL, 0xB8C7CA5B1F1C0620ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltWandererA[S_SALT] = {
    0x15F0954D6082D4E1ULL, 0xA02038E3C9E823A3ULL, 0x9B150A871135DCD1ULL, 0x983F1DFF17CDB774ULL, 
    0x67D359EC65EB98B7ULL, 0xA9AF5C94CDECB4FCULL, 0xF5DBA300C29F1513ULL, 0x97C59B704F1C8D02ULL, 
    0x6EE7EB0BE81FCE6BULL, 0x3903F1CC5A498E00ULL, 0x44805DB2FFF11D0BULL, 0x3A3F2A1A8A59016DULL, 
    0x394E5D007D74007CULL, 0x171B395EF3081D1CULL, 0x8C7D7913F3E326D0ULL, 0x3D7837E748F59FCDULL, 
    0x78418B7D4EA0ED97ULL, 0x634F2D2C906C4382ULL, 0x37229F9083E58F55ULL, 0x585929463D991A08ULL, 
    0x18EEAA18951652DAULL, 0x8C627E46F58C15BAULL, 0x610ECFF65EC07746ULL, 0x6379AB6A5EE077F0ULL, 
    0x1D7AE843AA45156DULL, 0x7CF0D8DD9BA5A621ULL, 0xD11EC47523F9087DULL, 0xC29BE56DA1EB710FULL, 
    0x44D7379D45C3DA86ULL, 0xB403EA7842176832ULL, 0xE6E8D318D97940CAULL, 0x6B5057903F5CD299ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltWandererB[S_SALT] = {
    0xDC6D246E7838235EULL, 0xF60B299CAB1571A5ULL, 0x246787E417C735A4ULL, 0xC4D19BE29C95ACDFULL, 
    0x7BDA85DE887349D0ULL, 0xA39A89D0E1429146ULL, 0x0CCDD33E6AA5FC3FULL, 0x6E4A51948E3AF511ULL, 
    0x6F17A4DD2AC15A43ULL, 0x35377994173D0C4AULL, 0x8531D26F67AD7BAFULL, 0x223BB5F798A1F24AULL, 
    0x4EE9CC9CC300F232ULL, 0x0135356AFCDF86A1ULL, 0x9D84511C2BE27DC8ULL, 0xE86A9D427FB61867ULL, 
    0x2B5EAB74A516FEFEULL, 0x8E3CA237EEAC8B8CULL, 0x0AF943C797F670D8ULL, 0xF3AC0BEDEF10DA2AULL, 
    0x396FF73CA3BA9095ULL, 0x1D38D4587F8DB0CFULL, 0x6C5F87E4152C6314ULL, 0xC39479516E4D982EULL, 
    0xF1A00785F7681CC6ULL, 0x3B8E08EE1D1E2FA1ULL, 0x279700B352D916A9ULL, 0xEC0381DE58578C12ULL, 
    0xF77E97A98D3BDE69ULL, 0x978B4ABD1CCB044AULL, 0xEDE17E15D7441DC7ULL, 0xBFAFC475C0FE8546ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltWandererC[S_SALT] = {
    0x718872460E75198EULL, 0xF7C0848FA80382DCULL, 0xD3548BD75C3EBE22ULL, 0x1C7F7C593B9AB760ULL, 
    0x20629C2A1E89EC76ULL, 0xAF35692EE137C185ULL, 0x362CCA3A73AE607CULL, 0x791F5E13B6FEB5D2ULL, 
    0xB12AB178FCEC2A65ULL, 0xF9ED206D14E6E429ULL, 0x0E314C8B2A0C7378ULL, 0x886BCA6FD1472EA6ULL, 
    0x64836A9D74F6A7FEULL, 0xFBE6707C17D8358CULL, 0x8097E02F1181242FULL, 0x376E68617901F98FULL, 
    0xE14A49AAE7C9FF54ULL, 0x79937DCA938E1E54ULL, 0x9B80D79FB69201E0ULL, 0x9CF118775E92D155ULL, 
    0xFCA3ED092D04EB6FULL, 0x5A2BE3CB5BB8C0D8ULL, 0x4F6FBEDD503CCFF8ULL, 0x0B58C86E9C8DDA73ULL, 
    0xC25FA8EB1AD16F31ULL, 0x7751C0935E0892FAULL, 0x0786A562BA56EC17ULL, 0xE091605AB6639394ULL, 
    0xA0DFCF312604551FULL, 0xBCE5AA85A4CCFF6BULL, 0x5FF70F3D6E94C767ULL, 0xF58746F3B5EBB104ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltWandererD[S_SALT] = {
    0xB0A79CEC41EFDA41ULL, 0xC2A31C4F92EB5DD3ULL, 0x68BB3A40E41F1352ULL, 0x9F4A8D3A4259938BULL, 
    0xB11E54ADD9FCA077ULL, 0xAAAC784890F57E43ULL, 0x932247891383EE01ULL, 0x8AD79F80A97E8691ULL, 
    0x5579A6EA839D9940ULL, 0xABFD75F4CC925FA2ULL, 0x8EB58D11E3ABBA82ULL, 0x1B821250E70DBD0EULL, 
    0x7B2908D373F94626ULL, 0x1016E35E8563CD13ULL, 0xEF70BEDA838F9A19ULL, 0x162EBE3CDC9C9377ULL, 
    0xB0EC07C120D840E2ULL, 0x7172321CB9E4CF3FULL, 0x948E8D8DD1C7DAA7ULL, 0x7E54637CA229C10BULL, 
    0x3FA13ED5C91B1FE6ULL, 0x65FEBBFE9EE8154AULL, 0xFEE7DB4E69C6D134ULL, 0xAE38AB3B08DAF9B8ULL, 
    0x0F208BB06F83373DULL, 0x5FEA91798E0FA04DULL, 0xE2255F5D8CDB9E01ULL, 0x278F32B9C1DAD549ULL, 
    0x94855B5F0E181B95ULL, 0x30636E3CD58BE67BULL, 0x1DF9DEA12DCE67CEULL, 0x53A5DE6CF62E2850ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltWandererE[S_SALT] = {
    0xCE28A14B64726A76ULL, 0xB96DDCF9C65A80DBULL, 0x18CD41E716C31A44ULL, 0x654CE0DAEEE0E232ULL, 
    0xE602D852D67EDFFBULL, 0x65AED61960FAA2D5ULL, 0x087EFB38CDCAAFD0ULL, 0x7EF09F4D6500E37BULL, 
    0x5994FF97E234EB56ULL, 0x961F9052FAC1C22DULL, 0xBC5389DF30C867C7ULL, 0x43CC6F7FBFC311C8ULL, 
    0xE8703DBF12BC38A6ULL, 0x1DA66DDCDF3ED3B5ULL, 0xF0C4871358C1B2A7ULL, 0x59A94CAF353E414DULL, 
    0x16DC02F05C5659B7ULL, 0xFD2B758DF24690C2ULL, 0x8AF98A0694AFBB86ULL, 0x77B5DDC7AD864CC9ULL, 
    0xF0C48F7C0AF9514BULL, 0xDB8B3B742076B869ULL, 0x88B1EAA9737F5602ULL, 0xAF7EB52D04EBE01BULL, 
    0x19991D8332845D86ULL, 0xC93998F38BEF4867ULL, 0x96455ADCA810F1F1ULL, 0x6156E5F329D1F717ULL, 
    0x114EC4B1C81E8F3BULL, 0x3B49B610133A3D4FULL, 0xE325987A26E88B5CULL, 0x4956B5437D4C7DA6ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltWandererF[S_SALT] = {
    0x2A44D9FEDC4214AFULL, 0x991E2F792A1FA271ULL, 0x1D8CD0ABA1FCA0BFULL, 0x805437894A934F95ULL, 
    0x7D807222C0A8F9C4ULL, 0xBD90ADF9D808669AULL, 0x22A4516EF6DE039DULL, 0x0F5D94E2E165A92FULL, 
    0xD3BC24AA895B6145ULL, 0x21755FAE4915382EULL, 0x2ED371CF92C6D34CULL, 0xB23F966B2DCA5127ULL, 
    0xFE0780F988077E0DULL, 0x98A03843503A0EFAULL, 0x5613C0F26AFAC6A6ULL, 0x3DB5A0C9834CE3EAULL, 
    0x0CE978D708DF86AFULL, 0x3D10A3E5558777A2ULL, 0x5540A56EE8EF6DCAULL, 0xF1C578160A40FD2BULL, 
    0x7BC7E43BA2B061DDULL, 0xE7F91DE85242364BULL, 0x2F013D397D1DE3C5ULL, 0x3303A748937D0D73ULL, 
    0xB5C49DC436CBF5B8ULL, 0x875E7E8C3655E9B0ULL, 0x52447A6C9D78397CULL, 0x8890F5650B27DDACULL, 
    0xD6D5DAA65CF855D4ULL, 0xE225B537FC31CDE4ULL, 0x6B6AD82ACE079B9EULL, 0x724CD6E02D150A4AULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltOrbiterA[S_SALT] = {
    0x1E0AEFDC1407325DULL, 0xF3F3802EB277C03DULL, 0x8CEA321E3C5FD733ULL, 0x4972C4504D191F75ULL, 
    0x99ADE9BA976B40C3ULL, 0x6EF596C91828F1DEULL, 0xEAA238253CEDC390ULL, 0xEE48EC0353C587B1ULL, 
    0xD9F4D0298CA3953EULL, 0x3B1C2FABE8B31B93ULL, 0x65ACB6A3BC434C6DULL, 0xB965EA16B060B256ULL, 
    0xDCE37609545EF279ULL, 0x44708CFD3934C46FULL, 0x902178EC98DCA134ULL, 0x453753CEB033D3AFULL, 
    0xD162023981A825C0ULL, 0x760126372934CC42ULL, 0x1AA97C05A409C0C3ULL, 0x0BC96707337E2D16ULL, 
    0xCE18ECCC758B1212ULL, 0x728B2CA24EBC44FBULL, 0x53CDAEA5AD93EBDEULL, 0x4D4AB102C986B53AULL, 
    0x8939C481E9C10927ULL, 0xBFE92A7677388422ULL, 0xF2AD84E1AEC5C4ACULL, 0x1F8EC6F8CCB9B4A8ULL, 
    0x96E073F9DD30BEFBULL, 0xC1E729AABE265B94ULL, 0x5FA088248A447662ULL, 0x85D89906227402B0ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltOrbiterB[S_SALT] = {
    0x78F80AF5D9EEADAAULL, 0x6D1FD2BEAD4CF4A8ULL, 0xBC75A29DB253FF1EULL, 0xD8720F2C55D4EA1FULL, 
    0xC9C98CDD873CFE5FULL, 0x399A674339BB266AULL, 0x83504D26C8380730ULL, 0x64791786C88277DBULL, 
    0x6640A7DBFC1375F0ULL, 0x8C3205E51A6FC299ULL, 0x0AC992212A0E416BULL, 0x34C8062DBF3E8ED0ULL, 
    0x0348E3065D88D717ULL, 0x29AD503DE87ED33CULL, 0xC42CC6B29F30C3D8ULL, 0xF6D46198E56F52DCULL, 
    0xC29043ED8924032AULL, 0x0A97A3875BCE3BD7ULL, 0xD3EF67F5B75A1AEDULL, 0x71603060BF80AA66ULL, 
    0x2853E6F87D0BC22BULL, 0xC4FE2A715F9F7AABULL, 0xBAC9603BCDE94035ULL, 0x7B5036EDFE53963DULL, 
    0xCE6AC7003D8C8F16ULL, 0x3320DD63B3FA1774ULL, 0x9985BD15ED92D55FULL, 0x4BDF9B7B3D4D6118ULL, 
    0x3D4707F97F349DCBULL, 0xB63CC1EA17797854ULL, 0x2D454229F84B56F2ULL, 0x1CDB9E8415AF6CCEULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltOrbiterC[S_SALT] = {
    0x53F75AEB5F87591FULL, 0xEF61EEC929BBD821ULL, 0x949D0B1DFE74270FULL, 0xF3E277C7165C8000ULL, 
    0x43BFE032E2F9D279ULL, 0x4BCB64B4F2B68A4DULL, 0x7D9FB46DFE6604A8ULL, 0x1A02652262546C68ULL, 
    0xC198CE71F20BEA84ULL, 0x6281140EB830B7D9ULL, 0xFA188430EE1EABF1ULL, 0x0723228EA4C0F170ULL, 
    0x58329B2560D02D59ULL, 0x92A6E057E799F422ULL, 0x99AFEC059B7EC77CULL, 0xF48D7EF433C38D75ULL, 
    0x604D74AB0CDF2FD0ULL, 0xB0DDD01BDFCFCE20ULL, 0x5EE52C9D5BCD74CFULL, 0xA1EF014247E0E0B6ULL, 
    0xE419B04C9D52EBECULL, 0xB33A7A66D7FFEA05ULL, 0x28AF48CD3CFC2698ULL, 0x078CE1DACBCCFA79ULL, 
    0xDFEFA4F13009B2F4ULL, 0xA41A3A1F20BEE6DEULL, 0xB87977C116421A41ULL, 0x57FD50B2F28D035FULL, 
    0x90AAAF74D16E3CF7ULL, 0xA7D5B29761F85D4BULL, 0x2916C80245EB1E15ULL, 0x167A9B24A8390508ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltOrbiterD[S_SALT] = {
    0xB008E6A8F52FAB02ULL, 0x177FF91CCEC7774DULL, 0x96525965A592287DULL, 0xB374CA10DFEF23DAULL, 
    0x72A5FF55367B0C7DULL, 0xB46921DB23EF355FULL, 0x230F4BEE58A0038FULL, 0x05A438DA8E11ECD4ULL, 
    0xAB5547B682F2BA8BULL, 0x3B07E25A448C0C42ULL, 0xAC8858F2E753FAACULL, 0xAA877F394206EBB1ULL, 
    0x3F80B8898839B762ULL, 0x9FEBC699F1DB426AULL, 0xB5B41584684F4A50ULL, 0x100CC2DA14D22065ULL, 
    0x6CCA19E031D69B3CULL, 0x57D747EF1812AF1BULL, 0x2277ECFA9DA407C2ULL, 0xBAC8DB04C0560032ULL, 
    0xC01CD5BFC26A7DB1ULL, 0x8FAF9C0F29A62685ULL, 0x58292588BA7A4DE9ULL, 0xA2BE9BDB9B13C071ULL, 
    0xDE91FAF3627094BBULL, 0x6434149419AA9C57ULL, 0x6325737CA856E4DEULL, 0xFF75084D773A529EULL, 
    0x588D8C6DF8918DA1ULL, 0x7901FAFD3316E564ULL, 0x70265E3DDC4564D2ULL, 0x40B337DFD18018BAULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltOrbiterE[S_SALT] = {
    0x317A8E705AEAD561ULL, 0x00FDB79E29170880ULL, 0xBDAF3D29E29A080FULL, 0x43F79422EEFF9706ULL, 
    0x3821635F07A1D522ULL, 0xEA1086C185461E45ULL, 0xA6BAC73C5E474F45ULL, 0x12020925D9A7EBFDULL, 
    0x6B9E60EBBAD13698ULL, 0x9D0C5BF120DFF97DULL, 0xD9196748EDA1B169ULL, 0x71C2E3E27CB7C87CULL, 
    0x5788B90018055798ULL, 0x02806A120B6F28E6ULL, 0x36B957A64BD18892ULL, 0xF4F719A89D5594BBULL, 
    0x32DC1BBD67ACDAF1ULL, 0x03A59A37FCBA168AULL, 0x00F98F5EDFD004E8ULL, 0x19995D37F05B6C4BULL, 
    0xE2DC292EF25DAE83ULL, 0x7815294C309363A8ULL, 0x6742E8E39E0E3E14ULL, 0xA66960D661906ED8ULL, 
    0xB02BD76AE4BFCC0BULL, 0x9C57FA4A2980C914ULL, 0x5F78ABA240078671ULL, 0xB602E0C0C5B5684CULL, 
    0xBE7BBA7260740E93ULL, 0x54844586300644C7ULL, 0x798410F8258313C3ULL, 0x8EF75C152CAFBA63ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltOrbiterF[S_SALT] = {
    0xD8A336C5E32547D6ULL, 0x22A52D679DBE6C2BULL, 0xE9E38CF3F7F5AFB7ULL, 0xF5178878EC6484F4ULL, 
    0xB64453BB910E5582ULL, 0x5E56A337F64BF840ULL, 0x100C0F15776EFB05ULL, 0xD6B954B4E73D3B50ULL, 
    0x2A81020F1F12CADCULL, 0x4ECC086A24710314ULL, 0x3364B92D41722362ULL, 0xBA4FA133A2BFC467ULL, 
    0x26D7188E4E6EC921ULL, 0x54B796C0C74EB646ULL, 0x44233CCC3BD39700ULL, 0xC64E308A1527621FULL, 
    0xA58A56F8D7096845ULL, 0x914C9EECE7CA41E2ULL, 0xF22159D2A0588FE4ULL, 0x3C81E76ED13A1D94ULL, 
    0x3E3639DA95C0EFB3ULL, 0xFBC38014A208AA06ULL, 0xACA460D90B398EDAULL, 0xCD0A727D663451D5ULL, 
    0x287E56F9780CC8BFULL, 0x2CCA49084E386343ULL, 0xF68CC0BA61DAB3F7ULL, 0xC5D402DD8562194AULL, 
    0x8F2DE5498E7C12FBULL, 0x6FE6A687BA93AC3CULL, 0xE5993C36261C0EC5ULL, 0x5E595F0A38278E24ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltPrismA[S_SALT] = {
    0x1C8620F2E2C222E7ULL, 0x7BF3CAE045F6C9AAULL, 0xC159A9A170963207ULL, 0x53EBF52E10BEB557ULL, 
    0x039017DDAD33F739ULL, 0xF462E7425CB8FAA0ULL, 0x510AF550D6FEEDFDULL, 0xC1C39167B6331763ULL, 
    0x4F4281F076B5D58BULL, 0xB71EC9D649A26312ULL, 0x45E4394FA72C4772ULL, 0x8E3BB8BD92EE1150ULL, 
    0xF6ACBFA0BA1527D9ULL, 0x54C5A62AB79BCCAFULL, 0x6C05E495FB36A958ULL, 0x9665C71FD322950DULL, 
    0x8515E594EE74FD25ULL, 0xC9CBF80B6D1E20F3ULL, 0xBE88AE89BB6224D3ULL, 0xAB933BBC4FCBB231ULL, 
    0xEEE9E8783B9B3260ULL, 0x7ACA83DC1873D2A7ULL, 0xEE9299B5D36CA0E1ULL, 0x1C9E0693647EC493ULL, 
    0x53CA5E6CFD6FDFD6ULL, 0xC370ABBBEAA70DBCULL, 0x931E37656E43A90FULL, 0x3827753D017A429FULL, 
    0x620C5E2CD9D10904ULL, 0x3F61A864FA8378A6ULL, 0xBA3E0AFD4DFC4022ULL, 0x5DFC627382FACFB0ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltPrismB[S_SALT] = {
    0x7E7219A1B1E4940AULL, 0x3838253D79E4D414ULL, 0xFFE80C8B9A853774ULL, 0x7B410F9CD1CEFF26ULL, 
    0x6BBAC39757A69233ULL, 0xD6BF7421229EDD3EULL, 0x596F492C1856E772ULL, 0x4B6845619D84A66CULL, 
    0x9EC9D2F48063316EULL, 0xC3DEC734D6C0E7DEULL, 0x441929D15AF2CCC1ULL, 0x3F501D5AA51CD55AULL, 
    0x644AD6876DBEAFEDULL, 0xEF0B4CA494914696ULL, 0x5F46DF322F31AAA9ULL, 0x3485BA8DEE3F0227ULL, 
    0xACF27E0BDF4D62E7ULL, 0x1726D04F9924F721ULL, 0x9CDCBE424478590DULL, 0x00EDC4A2DB253B63ULL, 
    0xAB6872AA4D7F55CBULL, 0x4B1BC30218488F57ULL, 0xFC4C9DA5FD58AFA9ULL, 0xC9D47E7DB7D625E8ULL, 
    0x93A45496D7166A7AULL, 0x0B10AF0BBB8A14AAULL, 0x03C57FB7F5782885ULL, 0x4C33D5D28A973604ULL, 
    0xC1D7A7059AC43384ULL, 0x4BE082D4FC7841EEULL, 0x5B16CC2B42845A66ULL, 0xE4A3D5B24246E8FCULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltPrismC[S_SALT] = {
    0x48D717C893B94CE4ULL, 0x54C0B487F42C9DF9ULL, 0xA5CB695F3820ECFCULL, 0x26703E54A17806F0ULL, 
    0xD7DD78A09D337145ULL, 0xFB2FD936D599D4C9ULL, 0xF4D2D736F7055383ULL, 0x6FF5B215148C5265ULL, 
    0x5ACE36F7302205E5ULL, 0xA4B95E002AF91209ULL, 0x6C2D8AFC7652F0A6ULL, 0xBD5B17B4CDA527D3ULL, 
    0x531BBF0459AD68CCULL, 0xE1464CA8F144387DULL, 0xCD360D905A422E81ULL, 0x997782DE8B20C3CCULL, 
    0x49845A9B493E40DEULL, 0xF823B1BE1BB49F3DULL, 0x51032610007508FDULL, 0xF4BD3C9E4504437BULL, 
    0x3EBB326AB7124308ULL, 0xEE6A7E4A34346AD5ULL, 0x6FA039414EE0D58FULL, 0xCD6786C3D6318171ULL, 
    0x86CCF984B9D93651ULL, 0x7839B4F352436879ULL, 0xE5B0A4EED32740F9ULL, 0x71298DEE419BAF49ULL, 
    0x53D86FF256B91B41ULL, 0x012FB36F72A4B96EULL, 0x6F2E9D8FDB36C80AULL, 0x26464E13B27748E6ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltPrismD[S_SALT] = {
    0x0B027BF250AD5C4AULL, 0x6AFD7F8C44217425ULL, 0x9B3251FA6020847FULL, 0x18053CB827C5D657ULL, 
    0xE6FB6986668833D6ULL, 0x83B5AEC3D226D6DAULL, 0xE2F18196C5FA2597ULL, 0x78BD332F7DBF5EA3ULL, 
    0xBAEB17E21BF72ABEULL, 0xD0CF43C6477196AEULL, 0x2777AEED1E5688DFULL, 0xDF875074CCB21A92ULL, 
    0x3F1ED420D62BB306ULL, 0x6D25D32ED72D3B9CULL, 0xE4C3BDD1BD4E07A6ULL, 0xD8B85BF6A1D09BC1ULL, 
    0x189C09C888C3A9DAULL, 0xCCDE326268888C18ULL, 0x3880E48E6D65CEC6ULL, 0x24A4D14490897F9CULL, 
    0x855BE8655F0663E2ULL, 0xF18B9427C277B523ULL, 0x584CCF35AE6D93D5ULL, 0xFD82464F2F352BF3ULL, 
    0x445BB424000FE503ULL, 0x41A406C025B4AC39ULL, 0x374DCD2F935721E8ULL, 0x2F0EAB021BFACCACULL, 
    0xBA2C93F41F52C728ULL, 0xA6B1B2525A1F836BULL, 0x04BF54C578C67977ULL, 0xE7CDB0DACE4885BEULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltPrismE[S_SALT] = {
    0xBCF20D2949091A4DULL, 0x596D38B9806F91E5ULL, 0xABFA4E566D567FE9ULL, 0x57CF7C091936F3C7ULL, 
    0x876A87750B173BBFULL, 0xB77416DB92A5E71FULL, 0xC31752BC9DD4F7E1ULL, 0x4E38CEF2888D8D00ULL, 
    0x3BF1630CDDA43E0CULL, 0xE701319DD111ECEBULL, 0xE12B1D7B1B08495EULL, 0x07C4A287D0786324ULL, 
    0x6E793B88E1D577BCULL, 0xEE5A85C71B063AB2ULL, 0x6551F160CFD94AAAULL, 0xF2A00B442A74A714ULL, 
    0x049E0ECC3821CE44ULL, 0x6D62A094AAC55B33ULL, 0x2A819CD1DD065366ULL, 0x30CABC039B660174ULL, 
    0x34583F32C9019D24ULL, 0x9AA9B78DBBD52422ULL, 0x6E79988CCCA0951EULL, 0x5AD523F9504BA1A8ULL, 
    0xBAEEC5672869C5F9ULL, 0xCFE2B1A6A22C6400ULL, 0xEE5DCF16C602C4C9ULL, 0x0AE61EA17FEBCDF5ULL, 
    0xAB80C67031D368F5ULL, 0xCBA3FD7F4BAC00DBULL, 0xC8453E073C017709ULL, 0xE29288ECD783C980ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltPrismF[S_SALT] = {
    0x2C540E5FD9FC498FULL, 0xAC1512D267C8C6A8ULL, 0xE9D684DD004922B1ULL, 0xA0EC5A0498BDA8EFULL, 
    0x71544EEACC94CF7EULL, 0x0196C5E8DF130AABULL, 0x01B132030A242728ULL, 0x0F1CF29BA3EF479DULL, 
    0xB5694652FB84941FULL, 0xD74B12DCBAB1F1C5ULL, 0xF5DA7EE3F9435DA0ULL, 0x88B6847ED9B01C58ULL, 
    0xDE7A24241AE41473ULL, 0x0B2A509F396457B5ULL, 0x24192C02AF86311BULL, 0xD23B5E4EBF818AEFULL, 
    0xE70588F2B7070186ULL, 0x31BA1CCEA0BC5AC3ULL, 0xD30CE1086D8ECEE8ULL, 0x2CF6A31A2FE9D80AULL, 
    0xB7413253E4EFA23AULL, 0xC8CA18FE7821DE13ULL, 0x7679C7F2FDDD4B06ULL, 0x740064714644A0C6ULL, 
    0xC91D2FC95BFC8B72ULL, 0x9F5C47E2DAE963EFULL, 0xF6197768E0BA7730ULL, 0x76DD1B83F49CA3C9ULL, 
    0x7469380AC7952B70ULL, 0x6A5B580DEF2F4A85ULL, 0xCE646D4DD9EC1CCDULL, 0xDCA4F411F28D4081ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltSourceA[S_SALT] = {
    0x2F3A0097B3729B46ULL, 0x1B62C7F088E40D80ULL, 0x62D120A3DE641876ULL, 0x4E839B7A90049003ULL, 
    0x7968B912F3E97E70ULL, 0x1AD33BA3D8094CCEULL, 0x2C75FBC99729A60FULL, 0x4F58EBE7B21EB941ULL, 
    0x0ACF4D42EE0AB612ULL, 0xF63BC69A33E89A6AULL, 0x1022783F85573935ULL, 0x403675389A016704ULL, 
    0x8BBA29B303F02449ULL, 0xFD9355521B15568DULL, 0x1893BFDE60A14D2FULL, 0xF52E80C59535A1E5ULL, 
    0x069A2C9208370421ULL, 0x2DA1D235CDFB40B6ULL, 0x65385A109F03C9B9ULL, 0x3F94090798431AF5ULL, 
    0xAC64C6A2D3EE2646ULL, 0x74D1D17C7C0A3DDBULL, 0x5BED056FA48D5D02ULL, 0x611BC9650A5FECCDULL, 
    0x82348C227E23BDBCULL, 0x7F8FB2D32370E9E9ULL, 0x2CFA35F878607379ULL, 0x5617BB45D8BC5B5BULL, 
    0x54209DF1B4BB0869ULL, 0x4D1CB747E321839AULL, 0x520B994D1FC0A94BULL, 0x3FDD19D0B73EA418ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltSourceB[S_SALT] = {
    0x6E9B9BA89EDACAEBULL, 0x15C4A066A790283DULL, 0x16507859E9965D7FULL, 0x17EC669BE01C82E5ULL, 
    0x15960A2C5DEC1185ULL, 0xB786DD4D6994BC43ULL, 0x0580D0619F44CF3AULL, 0xFB4FA9CBBA85C499ULL, 
    0x4A6E00341A46A395ULL, 0xFB71487BD6D28020ULL, 0xBCA0E0935914BA7BULL, 0xB603EF25CFCE821FULL, 
    0x379BE2A5733BE1EDULL, 0x82D47F6DAE448EB0ULL, 0x81AF19D07DDD1261ULL, 0x2877979DEBA9E827ULL, 
    0x80AA141DB9E5B0E6ULL, 0xCBF3648E6D964302ULL, 0x4DF10946923CFEAEULL, 0xC100482DD8A6E9F8ULL, 
    0x7E58B00CD7FCA2C9ULL, 0x1B53B478C9D99AB6ULL, 0xF9A66C52583CBFFEULL, 0x63230D9632CCA80DULL, 
    0xBD007AF925D7BAE7ULL, 0xB775E76F1CF347D9ULL, 0xD5C9DFBEC46B57FCULL, 0x4340399EAE8A886EULL, 
    0xBDFEBDA07E8D56AEULL, 0xDF8842A528A7477EULL, 0x8D43D54371687CE8ULL, 0x8DCFEA93F6A257B4ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltSourceC[S_SALT] = {
    0x4F1D66B6FF757F62ULL, 0x4C3C422235AA98EDULL, 0x6626A4778212BDBDULL, 0x8D15DC0662511FA9ULL, 
    0x492586B25F86A20FULL, 0xA3E6F3DCA1F1EEDAULL, 0xEDF1414E82BDD6ADULL, 0xE9B0475A9F6B30D6ULL, 
    0x50E0C59375BE6A6CULL, 0xBBA8A03C399BCE9BULL, 0xCC6D15547CE4A223ULL, 0x126DD2F16C710DA3ULL, 
    0x3543D706700EB616ULL, 0x082F95955E597013ULL, 0xCA10EC6B3C8152A5ULL, 0x729A36E9D4EA51C6ULL, 
    0xD29C66EB6E0B6592ULL, 0x80498F9B03FDCCBCULL, 0x0754B770DDEEED0CULL, 0x280E278D6295DC38ULL, 
    0xC4C377B4FE66FA8AULL, 0x4E9BC3F538285060ULL, 0x3FF7D7492B4246B8ULL, 0xBDE31D188A795D1AULL, 
    0x6ACE100EE11DA76EULL, 0x8DD1359E9C90DAA6ULL, 0x009A1C9DB8E8EF60ULL, 0xB11415E9309A6DAFULL, 
    0x0CEFB56E20DFD0A4ULL, 0x83F0AE649496E143ULL, 0x39F642072E3CB36CULL, 0x107FB6CACB4CEB78ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltSourceD[S_SALT] = {
    0x2CB714F178B9D588ULL, 0x1EBF7C7F2A811A11ULL, 0x726F5D42A4857DEEULL, 0x213711A829E2490FULL, 
    0x0131C1DF52D7DE5CULL, 0x9061394335A2FA36ULL, 0xCA21FCC6793BE591ULL, 0x4F3DF1A27F9DEEB1ULL, 
    0xB4BB1044E6272E83ULL, 0xA96B4DAC881A2E8CULL, 0x77899939BFE1DDE6ULL, 0x13E9BD2048F5FDE0ULL, 
    0x87D8F6326B9795C3ULL, 0x446D27CA2B9CE8D1ULL, 0xC686506226397DC6ULL, 0x0806EA22197FFA01ULL, 
    0xBC5A71A859DAFBB1ULL, 0x6671BB5A34A27008ULL, 0x05C698A5087DAF3DULL, 0xA9B18C39299D3D6DULL, 
    0x832A7424D6265DACULL, 0x221FC346122BD1EEULL, 0xB3D1B4CAC9B1E554ULL, 0xFC0AE3EB06089253ULL, 
    0x783C79C73B3B60EBULL, 0x7F6FF54CB7AC5B79ULL, 0x5F0DF6167EAA209DULL, 0x3D845DFC3D2A311EULL, 
    0x611B087C4A76CE66ULL, 0xF5A9F5B64984B119ULL, 0xD298FC532262AEDDULL, 0x71D9C2EC371B7644ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltSourceE[S_SALT] = {
    0xE90878CA8EB78490ULL, 0x2168BC251CD5F2A3ULL, 0x838F8B615C0BE6D5ULL, 0xF8C05E813FC3B889ULL, 
    0x2862F4A684995640ULL, 0xDA67C5095B90C309ULL, 0x23C72A9B338120D3ULL, 0xF96F6659B7C12A40ULL, 
    0xF7BB829420DB5A56ULL, 0x5C3B44884B0D6842ULL, 0xB5521CC575A2B993ULL, 0x79E7D4E6E40B76A6ULL, 
    0xEC948AD08D3E4354ULL, 0x2CA32F109777C0D1ULL, 0x1919A329A343541DULL, 0x65E11DDDFFB2D112ULL, 
    0xE0A3F09ECEA2DC7DULL, 0x3ADFCB098B3E925FULL, 0x2DA2CD0B8C996C62ULL, 0x94A6E1AC0A6E7174ULL, 
    0xF4B5A3FF31C69CE6ULL, 0x55F2F8BB99B9C4C4ULL, 0xFFC52D5C2039D4D5ULL, 0x479998FEE877F483ULL, 
    0x7912D0D79CF2B021ULL, 0x0878CF4B66980612ULL, 0x979A55F72BF695DCULL, 0x8E5B5BC9C4F2DFC8ULL, 
    0xC5A1A62C8E67FC5CULL, 0xF8A0BD069ADD6D45ULL, 0xC94073D5EBC4A96AULL, 0xCDEF1A26F96646C4ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainSaltSourceF[S_SALT] = {
    0x550C7C39B23264F0ULL, 0x2A31E619C6FCA3A5ULL, 0x7908E812ECB85158ULL, 0x994EB1C2B556666FULL, 
    0x6728BFCED966F952ULL, 0x444B5230B07882DBULL, 0x308FA93706D93860ULL, 0xBC36660DD7B7B939ULL, 
    0x0D25CEBA6312231AULL, 0x4C780BF0399354F7ULL, 0xE6B7ACF9E1CE1FCAULL, 0x6812FD8F05F470C0ULL, 
    0x695D8432A919C169ULL, 0x2CF9C4B0C2EDCA16ULL, 0xB8750AF4F0D85422ULL, 0x6443B0F9E6730D78ULL, 
    0x6EDC8B637387831FULL, 0xC8208C6B107F7A27ULL, 0x5620BEF490CAD21FULL, 0x138B0662CDA38323ULL, 
    0x75A29D3A30F1CF7BULL, 0x32558C4A1D8EC9A9ULL, 0x93C76855CEDFF357ULL, 0x65CEBA7D9D359296ULL, 
    0x224B473C658E436BULL, 0x3792F62CEC695EB9ULL, 0x60A288CD1D8B70CFULL, 0x8725F03051919B82ULL, 
    0x076D833FF22AA34AULL, 0xE4E0C31E6DE975EEULL, 0xA3C4B4DCB7F5397BULL, 0x4553EFEF0E04D3B2ULL
};

const std::uint64_t TwistExpander_Carbon::kDomainConstantPublicIngress = 0xA8410506D52EC83FULL;
const std::uint64_t TwistExpander_Carbon::kDomainConstantPrivateIngress = 0xE6AF9375380CC021ULL;
const std::uint64_t TwistExpander_Carbon::kDomainConstantCrossIngress = 0xEC61BD890E0A60FEULL;
