//
//  LardExpander.cpp
//  MeanMachine
//
//  Created by Dragon on 5/10/26.
//

#include "LardExpander.hpp"
#include "LardExpander.hpp"
#include "TwistFunctional.hpp"
#include "TwistMasking.hpp"
#include "TwistMix64.hpp"
#include "TwistSnow.hpp"
#include "TwistMemory.hpp"
#include "TwistCryptoGenerator.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmSalt.hpp"

#include <cstring>

LardExpander::LardExpander()
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

void LardExpander::Roll() {

    std::uint64_t aStreamPrevious = 0;
    std::uint64_t aStreamCurrent = 0;
    std::uint64_t aSecretPrevious = 0;
    std::uint64_t aSecretCurrent = 0;
    std::uint64_t aCross = 0;
    std::uint64_t aStreamScatter = 0;
    std::uint64_t aSecretScatter = 0;
    std::uint64_t aCarry = 0;
    std::uint64_t aOrbitA = 0;
    std::uint64_t aWandererE = 0;
    std::uint64_t aOrbitB = 0;
    std::uint64_t aWandererA = 0;
    std::uint64_t aOrbitC = 0;
    std::uint64_t aWandererB = 0;
    std::uint64_t aOrbitD = 0;
    std::uint64_t aWandererF = 0;
    std::uint64_t aOrbitE = 0;
    std::uint64_t aWandererD = 0;
    std::uint64_t aOrbitF = 0;
    std::uint64_t aWandererC = 0;
    std::size_t aPlugKeyA = 0;
    std::size_t aPlugKeyB = 0;
    
    std::uint64_t aState = 0x00;
    for (std::uint32_t aIndex = 0U; aIndex < mDataLength; aIndex += 1U) {
        aState = RotL64(aState, 3) ^ mPassword[aIndex];
        aState = RotL64(aState, 3) ^ (aState * 3333333333333333333ULL);
        mLaneD[aIndex] = (aState >> 56);
    }
    return;
    
    //mDest
    

    for (std::uint32_t aIndex = 0U; aIndex < mDataLength; aIndex += 1U) {
        aStreamPrevious = aStreamCurrent;
        aSecretPrevious = aSecretCurrent;
        aStreamCurrent = mPassword[aIndex];
        aSecretCurrent = mPassword[aIndex];
        aCross = mPassword[(mDataLength - 1) - aIndex];
        aStreamScatter = TwistMix64::DiffuseC((RotL64(aStreamCurrent, 57U) ^ RotL64(aStreamPrevious, 23U)) + (RotL64(aCross, 35U) ^ RotL64(aStreamCurrent, 7U)));
        aSecretScatter = TwistMix64::DiffuseC((RotL64(aSecretCurrent, 23U) ^ RotL64(aSecretPrevious, 35U)) + (RotL64(aCross, 49U) ^ RotL64(aCarry, 9U)));
        //
        aOrbitA = aWandererE + RotL64(aSecretCurrent, 43U) + 3339283916456813609ULL;
        aOrbitB = aWandererA + RotL64(aSecretScatter, 29U) + 11339086426180649584ULL;
        aOrbitC = aWandererB + RotL64(aSecretPrevious, 45U) + 16819191669329316585ULL + mDomainSaltSourceA[((31U - aIndex + 25U) & static_cast<std::uint64_t>(S_SALT1))] + mDomainSaltSourceB[((aIndex + 9U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererF + RotL64(aCarry, 37U) + 8361916937762630725ULL + mDomainSaltSourceA[((aIndex + 7U) & static_cast<std::uint64_t>(S_SALT1))] + mDomainSaltSourceB[((31U - aIndex + 21U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aWandererD + RotL64(aSecretCurrent, 17U) + 18031328374429899857ULL;
        aOrbitF = aWandererC + RotL64(aSecretPrevious, 13U) + 18261756894092897276ULL;
        //
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aStreamScatter, 7U) ^ aStreamPrevious);
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aStreamScatter, 37U) ^ aCross);
        aOrbitA = aOrbitA + aOrbitB + 4250319792907645666ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + aOrbitA + 1492411503643460886ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = RotL64(aOrbitD * 4769002811843360111ULL, 63U);
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aCross, 19U) ^ aStreamScatter);
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aStreamScatter, 43U) ^ aStreamCurrent);
        aOrbitB = aOrbitB + aOrbitC + 17369549067879344180ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aOrbitE + aOrbitB + 7301713524358676722ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = RotL64(aOrbitE * 5482075718916115653ULL, 48U);
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aStreamCurrent, 17U) ^ aStreamPrevious);
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aStreamPrevious, 31U) ^ aStreamScatter);
        aOrbitC = aOrbitC + aOrbitD + 2985193736033012535ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = aOrbitF + aOrbitC + 14086975808140927408ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = RotL64(aOrbitF * 16571111608827957869ULL, 32U);
        //
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aStreamCurrent, 29U) ^ aCross);
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aStreamCurrent, 53U) ^ aStreamScatter);
        aOrbitD = aOrbitD + aOrbitE + 10390516547834639800ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA + aOrbitD + 18205555540941493267ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = RotL64(aOrbitA * 6237270336037546621ULL, 13U);
        //
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aCross, 23U) ^ aStreamCurrent);
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aStreamPrevious, 11U) ^ aStreamCurrent);
        aOrbitE = aOrbitE + aOrbitF + 16967799565443938873ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB + aOrbitE + 9209505304067579944ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = RotL64(aOrbitB * 2940173663395339111ULL, 24U);
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aStreamPrevious, 41U) ^ aCross);
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aCross, 13U) ^ aStreamPrevious);
        aOrbitF = aOrbitF + aOrbitA + 3522631966146762306ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + aOrbitF + 8811497120829041188ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = RotL64(aOrbitC * 14448158961650673449ULL, 7U);
        //
        aSecretCurrent = TwistMix64::DiffuseA((aOrbitA ^ RotL64(aOrbitB, 41U)) + (RotL64(aOrbitC, 31U) ^ aOrbitD) + (RotL64(aOrbitE, 43U) ^ aOrbitF) + aSecretScatter + aCarry);
        mLaneA[aIndex] = aSecretCurrent;
        //
        aWandererA = aWandererA + RotL64(aSecretCurrent, 45U) + RotL64(aSecretPrevious, 17U) + aOrbitB + mDomainSaltSourceE[((aIndex + 5U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererB = aWandererB + RotL64(aSecretCurrent, 29U) + RotL64(aSecretScatter, 37U) + aOrbitC;
        aWandererC = aWandererC + aOrbitD + aOrbitF;
        aWandererD = aWandererD + RotL64(aSecretCurrent, 7U) + RotL64(aSecretPrevious, 23U) + aOrbitF + mDomainSaltSourceF[((31U - aIndex + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererE = aWandererE + RotL64(aSecretCurrent, 57U) + RotL64(aSecretScatter, 31U) + aOrbitD;
        aWandererF = aWandererF + aOrbitF + aOrbitA;
        //
        aCarry = aCarry + (RotL64(aWandererA, 37U) ^ aWandererD) + (aWandererB ^ RotL64(aWandererE, 19U)) + (aWandererC ^ RotL64(aWandererF, 53U)) + RotL64(aSecretCurrent, 17U);
        aCarry = RotL64(aCarry * 2809163242875130677ULL, 43U);
        aCarry = aCarry ^ ShiftR64(aCarry, 31U);
    }
    for (std::uint32_t aIndex = 0U; aIndex < mDataLength; aIndex += 1U) {
        aStreamPrevious = aStreamCurrent;
        aSecretPrevious = aSecretCurrent;
        aStreamCurrent = mLaneA[aIndex];
        aSecretCurrent = mLaneA[aIndex];
        aCross = mLaneA[(mDataLength - 1) - aIndex];
        aStreamScatter = TwistMix64::DiffuseA((RotL64(aStreamCurrent, 41U) ^ RotL64(aStreamPrevious, 57U)) + (RotL64(aCross, 7U) ^ RotL64(aStreamCurrent, 19U)));
        aSecretScatter = TwistMix64::DiffuseA((RotL64(aSecretCurrent, 23U) ^ RotL64(aSecretPrevious, 43U)) + (RotL64(aCross, 51U) ^ RotL64(aCarry, 13U)));
        //
        aOrbitA = aWandererE + RotL64(aSecretCurrent, 23U) + 3339283916456813609ULL;
        aOrbitB = aWandererF + RotL64(aSecretPrevious, 13U) + 11339086426180649584ULL;
        aOrbitC = aWandererB + RotL64(aSecretScatter, 19U) + 16819191669329316585ULL + mDomainSaltSourceA[((aIndex + 1U) & static_cast<std::uint64_t>(S_SALT1))] + mDomainSaltSourceB[((31U - aIndex + 19U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererC + RotL64(aSecretCurrent, 17U) + 8361916937762630725ULL + mDomainSaltSourceA[((aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))] + mDomainSaltSourceB[((31U - aIndex + 9U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aWandererD + RotL64(aCarry, 35U) + 18031328374429899857ULL;
        aOrbitF = aWandererA + RotL64(aSecretScatter, 43U) + 18261756894092897276ULL;
        //
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aStreamCurrent, 13U) ^ aStreamScatter);
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aCross, 17U) ^ aStreamScatter);
        aOrbitA = aOrbitA + aOrbitB + 4250319792907645666ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + aOrbitA + 1492411503643460886ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = RotL64(aOrbitD * 4769002811843360111ULL, 48U);
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aCross, 19U) ^ aStreamCurrent);
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aStreamCurrent, 41U) ^ aStreamPrevious);
        aOrbitC = aOrbitC + aOrbitD + 17369549067879344180ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = aOrbitF + aOrbitC + 7301713524358676722ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = RotL64(aOrbitF * 5482075718916115653ULL, 40U);
        //
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aStreamScatter, 29U) ^ aCross);
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aStreamPrevious, 43U) ^ aStreamCurrent);
        aOrbitE = aOrbitE + aOrbitF + 2985193736033012535ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB + aOrbitE + 14086975808140927408ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = RotL64(aOrbitB * 16571111608827957869ULL, 32U);
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aStreamPrevious, 37U) ^ aCross);
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aStreamCurrent, 7U) ^ aCross);
        aOrbitB = aOrbitB + aOrbitC + 10390516547834639800ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aOrbitE + aOrbitB + 18205555540941493267ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = RotL64(aOrbitE * 6237270336037546621ULL, 16U);
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aCross, 23U) ^ aStreamPrevious);
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aStreamScatter, 11U) ^ aStreamPrevious);
        aOrbitD = aOrbitD + aOrbitE + 16967799565443938873ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA + aOrbitD + 9209505304067579944ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = RotL64(aOrbitA * 2940173663395339111ULL, 29U);
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aStreamPrevious, 31U) ^ aStreamScatter);
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aStreamScatter, 53U) ^ aStreamCurrent);
        aOrbitF = aOrbitF + aOrbitA + 3522631966146762306ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + aOrbitF + 8811497120829041188ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = RotL64(aOrbitC * 14448158961650673449ULL, 63U);
        //
        aSecretCurrent = TwistMix64::DiffuseA((aOrbitA ^ RotL64(aOrbitD, 17U)) + (RotL64(aOrbitB, 19U) ^ aOrbitE) + (aOrbitC ^ RotL64(aOrbitF, 31U)) + aSecretScatter + aCarry);
        mLaneB[aIndex] = aSecretCurrent;
        //
        aWandererA = aWandererA + RotL64(aSecretCurrent, 29U) + RotL64(aSecretPrevious, 41U) + aOrbitE + mDomainSaltSourceE[((31U - aIndex + 25U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererB = aWandererB + RotL64(aSecretCurrent, 53U) + RotL64(aSecretScatter, 19U) + aOrbitF;
        aWandererC = aWandererC + aOrbitF + aOrbitB;
        aWandererD = aWandererD + RotL64(aSecretCurrent, 11U) + RotL64(aSecretPrevious, 37U) + aOrbitD + mDomainSaltSourceF[((aIndex + 15U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererE = aWandererE + RotL64(aSecretCurrent, 23U) + RotL64(aSecretScatter, 7U) + aOrbitC;
        aWandererF = aWandererF + aOrbitF + aOrbitA;
        //
        aCarry = aCarry + (aWandererA ^ RotL64(aWandererE, 41U)) + (RotL64(aWandererB, 11U) ^ aWandererF) + (RotL64(aWandererC, 57U) ^ aWandererD) + RotL64(aSecretCurrent, 51U);
        aCarry = RotL64(aCarry * 2809163242875130677ULL, 31U);
        aCarry = aCarry ^ ShiftR64(aCarry, 29U);
    }
    for (std::uint32_t aIndex = 0U; aIndex < mDataLength; aIndex += 1U) {
        aStreamPrevious = aStreamCurrent;
        aSecretPrevious = aSecretCurrent;
        aStreamCurrent = mLaneB[aIndex];
        aSecretCurrent = mLaneB[aIndex];
        aCross = mLaneA[aIndex];
        aStreamScatter = TwistMix64::DiffuseB((RotL64(aStreamCurrent, 9U) ^ RotL64(aStreamPrevious, 21U)) + (RotL64(aCross, 51U) ^ RotL64(aStreamCurrent, 43U)));
        aSecretScatter = TwistMix64::DiffuseB((RotL64(aSecretCurrent, 23U) ^ RotL64(aSecretPrevious, 11U)) + (RotL64(aCross, 47U) ^ RotL64(aCarry, 35U)));
        //
        aOrbitA = aWandererB + RotL64(aSecretCurrent, 41U) + 3339283916456813609ULL;
        aOrbitB = aWandererC + RotL64(aSecretScatter, 53U) + 11339086426180649584ULL;
        aOrbitC = aWandererE + RotL64(aSecretPrevious, 11U) + 16819191669329316585ULL + mDomainSaltSourceA[((aIndex + 21U) & static_cast<std::uint64_t>(S_SALT1))] + mDomainSaltSourceB[((31U - aIndex + 15U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererD + RotL64(aSecretCurrent, 35U) + 8361916937762630725ULL + mDomainSaltSourceA[((aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))] + mDomainSaltSourceB[((31U - aIndex + 7U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aWandererF + RotL64(aCarry, 37U) + 18031328374429899857ULL;
        aOrbitF = aWandererA + RotL64(aSecretPrevious, 23U) + 18261756894092897276ULL;
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aStreamCurrent, 43U) ^ aStreamScatter);
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aStreamCurrent, 19U) ^ aCross);
        aOrbitA = aOrbitA + aOrbitF + 4250319792907645666ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + aOrbitA + 1492411503643460886ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = RotL64(aOrbitD * 4769002811843360111ULL, 32U);
        //
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aStreamScatter, 17U) ^ aCross);
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aStreamPrevious, 29U) ^ aCross);
        aOrbitF = aOrbitF + aOrbitE + 17369549067879344180ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + aOrbitF + 7301713524358676722ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = RotL64(aOrbitC * 5482075718916115653ULL, 16U);
        //
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aCross, 53U) ^ aStreamScatter);
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aCross, 37U) ^ aStreamCurrent);
        aOrbitE = aOrbitE + aOrbitD + 2985193736033012535ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB + aOrbitE + 14086975808140927408ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = RotL64(aOrbitB * 16571111608827957869ULL, 63U);
        //
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aStreamPrevious, 31U) ^ aStreamScatter);
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aCross, 41U) ^ aStreamPrevious);
        aOrbitD = aOrbitD + aOrbitC + 10390516547834639800ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA + aOrbitD + 18205555540941493267ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = RotL64(aOrbitA * 6237270336037546621ULL, 24U);
        //
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aStreamScatter, 23U) ^ aStreamPrevious);
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aStreamScatter, 11U) ^ aStreamCurrent);
        aOrbitC = aOrbitC + aOrbitB + 16967799565443938873ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = aOrbitF + aOrbitC + 9209505304067579944ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = RotL64(aOrbitF * 2940173663395339111ULL, 7U);
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aStreamPrevious, 13U) ^ aStreamCurrent);
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aStreamCurrent, 7U) ^ aStreamPrevious);
        aOrbitB = aOrbitB + aOrbitA + 3522631966146762306ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aOrbitE + aOrbitB + 8811497120829041188ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = RotL64(aOrbitE * 14448158961650673449ULL, 48U);
        //
        aSecretCurrent = TwistMix64::DiffuseB((aOrbitA ^ RotL64(aOrbitE, 17U)) + (aOrbitB ^ RotL64(aOrbitF, 53U)) + (aOrbitC ^ RotL64(aOrbitD, 37U)) + aSecretScatter + aCarry);
        mLaneC[aIndex] = aSecretCurrent;
        //
        aWandererA = aWandererA + RotL64(aSecretCurrent, 7U) + RotL64(aSecretPrevious, 11U) + aOrbitA + mDomainSaltSourceE[((aIndex + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererB = aWandererB + RotL64(aSecretCurrent, 57U) + RotL64(aSecretScatter, 29U) + aOrbitE;
        aWandererC = aWandererC + aOrbitD + aOrbitB;
        aWandererD = aWandererD + RotL64(aSecretCurrent, 31U) + RotL64(aSecretPrevious, 53U) + aOrbitF + mDomainSaltSourceF[((31U - aIndex + 3U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererE = aWandererE + RotL64(aSecretCurrent, 13U) + RotL64(aSecretScatter, 43U) + aOrbitD;
        aWandererF = aWandererF + aOrbitB + aOrbitA;
        //
        aCarry = aCarry + (RotL64(aWandererA, 11U) ^ aWandererF) + (aWandererB ^ RotL64(aWandererD, 31U)) + (RotL64(aWandererC, 13U) ^ aWandererE) + RotL64(aSecretCurrent, 51U);
        aCarry = RotL64(aCarry * 2809163242875130677ULL, 41U);
        aCarry = aCarry ^ ShiftR64(aCarry, 31U);
    }
    for (std::uint32_t aIndex = 0U; aIndex < mDataLength; aIndex += 1U) {
        aStreamPrevious = aStreamCurrent;
        aSecretPrevious = aSecretCurrent;
        aStreamCurrent = mLaneC[aIndex];
        aSecretCurrent = mLaneC[aIndex];
        aCross = mLaneB[aIndex];
        aStreamScatter = TwistMix64::DiffuseB((RotL64(aStreamCurrent, 29U) ^ RotL64(aStreamPrevious, 43U)) + (RotL64(aCross, 11U) ^ RotL64(aStreamCurrent, 53U)));
        aSecretScatter = TwistMix64::DiffuseC((RotL64(aSecretCurrent, 57U) ^ RotL64(aSecretPrevious, 35U)) + (RotL64(aCross, 5U) ^ RotL64(aCarry, 23U)));
        //
        aOrbitA = aWandererA + RotL64(aSecretCurrent, 45U) + 3339283916456813609ULL;
        aOrbitB = aWandererC + RotL64(aSecretScatter, 37U) + 11339086426180649584ULL;
        aOrbitC = aWandererD + RotL64(aCarry, 13U) + 16819191669329316585ULL + mDomainSaltSourceA[((31U - aIndex + 1U) & static_cast<std::uint64_t>(S_SALT1))] + mDomainSaltSourceB[((aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererF + RotL64(aSecretCurrent, 35U) + 8361916937762630725ULL + mDomainSaltSourceA[((aIndex + 31U) & static_cast<std::uint64_t>(S_SALT1))] + mDomainSaltSourceB[((31U - aIndex + 25U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aWandererB + RotL64(aSecretScatter, 41U) + 18031328374429899857ULL;
        aOrbitF = aWandererE + RotL64(aSecretPrevious, 31U) + 18261756894092897276ULL;
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aStreamPrevious, 43U) ^ aStreamScatter);
        aPlugKeyA = TwistMix64::DiffuseA(RotL64(aStreamCurrent, 31U) ^ aCross);
        aOrbitA = aOrbitA + aOrbitD + 4250319792907645666ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = aOrbitF + aOrbitA + 1492411503643460886ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitF = RotL64(aOrbitF * 4769002811843360111ULL, 32U);
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aStreamCurrent, 23U) ^ aStreamScatter);
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aStreamPrevious, 29U) ^ aCross);
        aOrbitB = aOrbitB + aOrbitE + 17369549067879344180ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA + aOrbitB + 7301713524358676722ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = RotL64(aOrbitA * 5482075718916115653ULL, 40U);
        //
        aPlugKeyB = TwistMix64::DiffuseB(RotL64(aCross, 19U) ^ aStreamCurrent);
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aCross, 13U) ^ aStreamPrevious);
        aOrbitC = aOrbitC + aOrbitF + 2985193736033012535ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB + aOrbitC + 14086975808140927408ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = RotL64(aOrbitB * 16571111608827957869ULL, 21U);
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aStreamScatter, 11U) ^ aStreamCurrent);
        aPlugKeyB = TwistMix64::DiffuseC(RotL64(aStreamScatter, 37U) ^ aStreamPrevious);
        aOrbitD = aOrbitD + aOrbitA + 10390516547834639800ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + aOrbitD + 18205555540941493267ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = RotL64(aOrbitC * 6237270336037546621ULL, 48U);
        //
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aCross, 17U) ^ aStreamScatter);
        aPlugKeyA = TwistMix64::DiffuseC(RotL64(aStreamPrevious, 53U) ^ aStreamCurrent);
        aOrbitE = aOrbitE + aOrbitB + 16967799565443938873ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aOrbitD + aOrbitE + 9209505304067579944ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = RotL64(aOrbitD * 2940173663395339111ULL, 13U);
        //
        aPlugKeyA = TwistMix64::DiffuseB(RotL64(aStreamCurrent, 7U) ^ aStreamPrevious);
        aPlugKeyB = TwistMix64::DiffuseA(RotL64(aStreamScatter, 41U) ^ aCross);
        aOrbitF = aOrbitF + aOrbitC + 3522631966146762306ULL + mDomainSaltSourceC[((aPlugKeyA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = aOrbitE + aOrbitF + 8811497120829041188ULL + mDomainSaltSourceD[((aPlugKeyB) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitE = RotL64(aOrbitE * 14448158961650673449ULL, 16U);
        //
        aSecretCurrent = TwistMix64::DiffuseB((aOrbitA ^ RotL64(aOrbitF, 47U)) + (aOrbitB ^ RotL64(aOrbitD, 11U)) + (aOrbitC ^ RotL64(aOrbitE, 19U)) + aSecretScatter + aCarry);
        mLaneD[aIndex] = aSecretCurrent;
        //
        aWandererA = aWandererA + RotL64(aSecretCurrent, 19U) + RotL64(aSecretPrevious, 45U) + aOrbitC + mDomainSaltSourceE[((31U - aIndex + 23U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererB = aWandererB + RotL64(aSecretCurrent, 13U) + RotL64(aSecretScatter, 51U) + aOrbitA;
        aWandererC = aWandererC + aOrbitF + aOrbitB;
        aWandererD = aWandererD + RotL64(aSecretCurrent, 43U) + RotL64(aSecretPrevious, 31U) + aOrbitB + mDomainSaltSourceF[((aIndex + 19U) & static_cast<std::uint64_t>(S_SALT1))];
        aWandererE = aWandererE + RotL64(aSecretCurrent, 53U) + RotL64(aSecretScatter, 17U) + aOrbitD;
        aWandererF = aWandererF + aOrbitF + aOrbitC;
        //
        aCarry = aCarry + (RotL64(aWandererA, 31U) ^ aWandererB) + (RotL64(aWandererC, 51U) ^ aWandererD) + (RotL64(aWandererE, 43U) ^ aWandererF) + RotL64(aSecretCurrent, 19U);
        aCarry = RotL64(aCarry * 2809163242875130677ULL, 11U);
        aCarry = aCarry ^ ShiftR64(aCarry, 41U);
    }
}

const std::uint8_t LardExpander::kSBoxA[S_SBOX] = {
    0x39, 0xFA, 0xF6, 0x1F, 0x74, 0xC3, 0xD0, 0xE0, 0x4C, 0xE7, 0x2A, 0x9C, 0x9D, 0x10, 0xD7, 0x2C,
    0xFF, 0x5A, 0x09, 0x20, 0x8E, 0x9E, 0x87, 0x58, 0xE8, 0xE6, 0xF7, 0xC4, 0x43, 0xC8, 0x3F, 0x29,
    0xE2, 0x6B, 0x5C, 0xAF, 0x73, 0x53, 0xBD, 0xC0, 0x5F, 0x12, 0x4D, 0x82, 0xC9, 0x0F, 0x96, 0x28,
    0x2E, 0xCC, 0x66, 0xDF, 0x1B, 0x95, 0xF4, 0x7C, 0xD8, 0xCD, 0x76, 0xA8, 0x88, 0x75, 0x2B, 0xDA,
    0x1D, 0x80, 0x79, 0x37, 0xED, 0x0A, 0x68, 0xDB, 0x92, 0x40, 0xCA, 0xF1, 0xB0, 0x72, 0x8F, 0x65,
    0x48, 0x2F, 0x3D, 0xB7, 0x90, 0xB1, 0xDD, 0xB2, 0x19, 0x25, 0xC2, 0x6C, 0xB4, 0x8B, 0x44, 0x36,
    0xF5, 0x9B, 0x0D, 0x54, 0x94, 0x51, 0xBA, 0xBF, 0xAB, 0x78, 0x11, 0x0C, 0xBE, 0xA5, 0xB5, 0x21,
    0x64, 0x2D, 0x62, 0x69, 0x86, 0x99, 0xB6, 0x91, 0xEE, 0x38, 0x23, 0x4A, 0xE1, 0x47, 0xAE, 0xD9,
    0x1A, 0xD4, 0x17, 0x6D, 0xA1, 0x4F, 0x71, 0x04, 0x3A, 0x3E, 0xD6, 0x7F, 0xDC, 0x8D, 0xC1, 0xE5,
    0xCF, 0xAC, 0x7D, 0x1C, 0xBC, 0x46, 0xAA, 0x8C, 0x5D, 0x41, 0xFD, 0xF2, 0x30, 0x7B, 0x31, 0xF9,
    0x84, 0x60, 0x9A, 0xEB, 0x42, 0x02, 0x83, 0x57, 0x05, 0x03, 0x32, 0xE3, 0x70, 0x63, 0x97, 0x33,
    0x61, 0xD3, 0xA9, 0xFC, 0x45, 0x3C, 0xA7, 0xFB, 0x26, 0x81, 0x4B, 0x52, 0x06, 0xC5, 0x1E, 0xC7,
    0xD1, 0xE9, 0x59, 0x55, 0x08, 0xE4, 0x14, 0x16, 0x7E, 0xC6, 0x00, 0xFE, 0x6E, 0x34, 0x7A, 0xA0,
    0x13, 0x89, 0xCE, 0xF0, 0x98, 0xCB, 0x67, 0xF8, 0x15, 0x85, 0x5B, 0x27, 0x49, 0xF3, 0xD2, 0x6F,
    0x5E, 0xA2, 0x50, 0x3B, 0xEF, 0xD5, 0xB3, 0xB9, 0xA6, 0x24, 0x93, 0xA4, 0xEC, 0x77, 0x6A, 0xEA,
    0x9F, 0x01, 0x56, 0x0E, 0x18, 0xBB, 0x4E, 0x35, 0xB8, 0x8A, 0xA3, 0x22, 0x07, 0xAD, 0x0B, 0xDE
};

const std::uint8_t LardExpander::kSBoxB[S_SBOX] = {
    0x79, 0x0E, 0x60, 0x58, 0x82, 0xEE, 0x41, 0xAD, 0xBC, 0xE3, 0xD6, 0x64, 0xBA, 0xC4, 0x0F, 0x46,
    0x6C, 0x71, 0x95, 0x28, 0x15, 0x48, 0x19, 0x5D, 0x7F, 0x3D, 0xBE, 0xA0, 0x20, 0xCE, 0xE9, 0x24,
    0x81, 0x43, 0xE1, 0x7A, 0xCC, 0x7D, 0x0B, 0x1C, 0x13, 0xE8, 0x62, 0x7B, 0x10, 0x05, 0x9A, 0xFA,
    0x6A, 0x72, 0xF3, 0xDD, 0xE4, 0x68, 0x4C, 0x50, 0x93, 0xAC, 0xAE, 0x34, 0x85, 0x5C, 0x08, 0xBF,
    0x74, 0x57, 0x32, 0x3B, 0x1D, 0x67, 0xB1, 0x61, 0x26, 0xD2, 0xE2, 0x2E, 0xBB, 0x12, 0xCB, 0x01,
    0x00, 0xB4, 0xC5, 0xF5, 0x0A, 0x65, 0xF1, 0x97, 0xC8, 0x4A, 0x30, 0x0D, 0x07, 0x77, 0x6E, 0xE5,
    0x92, 0x2A, 0x29, 0x33, 0xB6, 0x51, 0x45, 0x27, 0xC6, 0xEC, 0x1A, 0xF7, 0xF9, 0x84, 0xD9, 0xF6,
    0xDF, 0x98, 0x4F, 0x6F, 0xC7, 0x06, 0x2B, 0xD4, 0xEF, 0xA7, 0xDA, 0x2C, 0x73, 0x9C, 0xA4, 0x4D,
    0x3A, 0xFD, 0x8A, 0xD3, 0x38, 0x4E, 0xE0, 0x25, 0x8B, 0x37, 0xD1, 0xA2, 0x2F, 0xE7, 0xC2, 0xCF,
    0x80, 0x88, 0x8E, 0xAA, 0xD5, 0x42, 0x18, 0x39, 0x3F, 0x0C, 0x40, 0xDC, 0x75, 0x1E, 0xAB, 0xFC,
    0xEB, 0x63, 0xF4, 0x8D, 0xFE, 0xB5, 0xA5, 0xC1, 0xFB, 0x6B, 0x59, 0x5F, 0x3E, 0x91, 0x44, 0x87,
    0xBD, 0xB3, 0xEA, 0x9E, 0xB0, 0x1B, 0xA8, 0xD0, 0xB8, 0x89, 0xF2, 0xA3, 0x09, 0x7E, 0x86, 0x52,
    0x9F, 0xA1, 0x83, 0xED, 0x4B, 0x11, 0x78, 0x54, 0x7C, 0x8C, 0x99, 0xB2, 0x21, 0xC9, 0xC0, 0xE6,
    0x36, 0x5B, 0x5E, 0xF0, 0xD8, 0x3C, 0x2D, 0x22, 0xA6, 0x35, 0xAF, 0x66, 0xDE, 0x02, 0x6D, 0xFF,
    0xCD, 0xCA, 0x8F, 0x55, 0x31, 0x23, 0x49, 0xB7, 0x76, 0x94, 0xF8, 0x5A, 0xC3, 0x70, 0x9D, 0x53,
    0x96, 0x47, 0x1F, 0xDB, 0x16, 0x9B, 0x90, 0x17, 0x69, 0xA9, 0x14, 0x04, 0xD7, 0x56, 0xB9, 0x03
};

const std::uint8_t LardExpander::kSBoxC[S_SBOX] = {
    0xA2, 0x38, 0xDD, 0xA7, 0x11, 0xC8, 0xD8, 0xD3, 0x48, 0x06, 0xB2, 0xC2, 0x6B, 0x20, 0x0D, 0xCE,
    0x26, 0x46, 0xA9, 0x2B, 0x7B, 0x09, 0x80, 0x8D, 0x81, 0xAF, 0x74, 0x1D, 0xCF, 0xF8, 0xDE, 0xD0,
    0x18, 0xE4, 0x3A, 0xAB, 0xC4, 0xBD, 0x12, 0xAA, 0x58, 0xEB, 0xE1, 0x9E, 0x51, 0xD5, 0x5B, 0x79,
    0x05, 0x4F, 0xA8, 0x5F, 0x10, 0x39, 0x16, 0x43, 0x8A, 0xE6, 0xDA, 0x7E, 0x07, 0xB8, 0x1B, 0x41,
    0x6C, 0x55, 0x5D, 0x8C, 0x9F, 0xCB, 0x86, 0xE8, 0xEC, 0xAD, 0x33, 0x08, 0x5E, 0x6D, 0xD2, 0xCA,
    0xFF, 0xAC, 0x15, 0x8B, 0x27, 0xF7, 0x94, 0x95, 0xDB, 0x35, 0x61, 0x31, 0xE9, 0x65, 0x1A, 0x25,
    0xBF, 0x17, 0x1E, 0x68, 0x90, 0x76, 0xC7, 0xD9, 0x1C, 0xF4, 0x89, 0xB7, 0x70, 0x32, 0x40, 0x82,
    0x63, 0x67, 0x1F, 0x2F, 0x29, 0xDC, 0x22, 0x8E, 0xFD, 0x0B, 0x49, 0x34, 0x7A, 0x78, 0x02, 0x23,
    0xB9, 0x6F, 0xF5, 0x98, 0x85, 0x2A, 0x0F, 0xE5, 0xC0, 0x77, 0xA4, 0x21, 0x3D, 0x19, 0x03, 0xCD,
    0x2D, 0xC9, 0xEA, 0xC5, 0xBB, 0xD1, 0xB5, 0xB0, 0x93, 0x04, 0xED, 0x6A, 0x59, 0x96, 0xF0, 0x5A,
    0xE2, 0xD4, 0xBE, 0xE3, 0x66, 0x99, 0x37, 0x0A, 0x4C, 0x30, 0x92, 0xB1, 0xA6, 0xB6, 0xF2, 0x3B,
    0x7D, 0xBA, 0xD7, 0x44, 0xB3, 0xBC, 0xF9, 0x91, 0x57, 0xFC, 0x9D, 0x14, 0x2E, 0xB4, 0x0E, 0x7F,
    0x71, 0x28, 0x24, 0xC1, 0x00, 0x64, 0x97, 0x5C, 0x88, 0xD6, 0x52, 0x8F, 0xFA, 0xEE, 0x3F, 0x2C,
    0x42, 0xAE, 0x84, 0xA1, 0x75, 0x9A, 0x01, 0xF3, 0x3E, 0x4B, 0xEF, 0xFE, 0x56, 0xC3, 0x13, 0x53,
    0xF1, 0xE7, 0xDF, 0x69, 0x54, 0xC6, 0x3C, 0xA5, 0x50, 0x9C, 0x45, 0x9B, 0x36, 0x73, 0x4D, 0x4A,
    0xA0, 0xFB, 0xA3, 0x7C, 0x72, 0x6E, 0x83, 0x47, 0x0C, 0xCC, 0x4E, 0xE0, 0x87, 0x60, 0x62, 0xF6
};

const std::uint8_t LardExpander::kSBoxD[S_SBOX] = {
    0x89, 0xF9, 0x4F, 0x77, 0x72, 0x38, 0xB1, 0x7A, 0x58, 0x92, 0x00, 0xA1, 0x4A, 0x7E, 0x59, 0x03,
    0x45, 0x6D, 0x42, 0xB5, 0xC3, 0xF5, 0xC9, 0x39, 0x9B, 0x79, 0xA4, 0xD0, 0x51, 0x66, 0x8A, 0xBF,
    0x2E, 0x4D, 0x6E, 0xD5, 0x9A, 0x67, 0xB7, 0x87, 0xD1, 0x2A, 0xB3, 0x75, 0x8D, 0x41, 0x14, 0x54,
    0x57, 0x31, 0x10, 0xB8, 0x20, 0xAB, 0x1B, 0x93, 0x50, 0xDA, 0x26, 0x3D, 0xC0, 0x99, 0xEB, 0x04,
    0x23, 0x21, 0x2F, 0x6B, 0x27, 0xFD, 0xF2, 0xEF, 0x43, 0xEE, 0x32, 0xA7, 0xEA, 0x71, 0x28, 0xAF,
    0x0F, 0xBC, 0xDE, 0x02, 0x17, 0x01, 0xEC, 0xBE, 0x74, 0x09, 0xD3, 0xA5, 0xBD, 0x7F, 0xB9, 0x80,
    0xF0, 0x49, 0x15, 0x8F, 0x40, 0x33, 0x5F, 0xE3, 0x82, 0xC4, 0x95, 0xFE, 0x08, 0x60, 0x56, 0x5E,
    0x44, 0xE8, 0x47, 0x19, 0x22, 0x1D, 0xE9, 0xFC, 0x98, 0x62, 0x0A, 0x5B, 0x91, 0x06, 0x3E, 0xBB,
    0xCB, 0xE6, 0x96, 0x4E, 0x37, 0xE7, 0xCE, 0x1F, 0x36, 0x61, 0xB2, 0x2C, 0x07, 0x7C, 0x6C, 0xC6,
    0x8E, 0x6A, 0x78, 0xC8, 0x5C, 0xED, 0x69, 0x97, 0x85, 0x05, 0x11, 0x18, 0x83, 0x7B, 0x68, 0x46,
    0x76, 0x13, 0xA2, 0x24, 0xBA, 0x1C, 0x9E, 0x30, 0xF4, 0xF7, 0xD7, 0xC5, 0x25, 0xAC, 0xFF, 0x3C,
    0xF8, 0x0E, 0xD6, 0xFA, 0x52, 0x35, 0x34, 0x12, 0xB6, 0xCA, 0xB0, 0x8C, 0x4B, 0x3B, 0x9C, 0x6F,
    0x5A, 0x70, 0xD2, 0x64, 0xA9, 0x2D, 0x29, 0x7D, 0xC7, 0x84, 0x48, 0xAE, 0xF1, 0xD4, 0x90, 0xDC,
    0xC1, 0x2B, 0x65, 0x4C, 0xF6, 0xD9, 0xFB, 0xAD, 0xC2, 0x9D, 0x86, 0x5D, 0xE4, 0xF3, 0xE5, 0x1A,
    0x3A, 0x88, 0xD8, 0xDD, 0x73, 0x0D, 0x55, 0xE0, 0xDF, 0xE2, 0xA8, 0x8B, 0xCC, 0xCD, 0xA6, 0xCF,
    0x1E, 0xA3, 0xDB, 0xAA, 0x9F, 0xB4, 0x0C, 0x3F, 0x0B, 0x94, 0x63, 0xE1, 0xA0, 0x81, 0x16, 0x53
};

const std::uint8_t LardExpander::kSBoxE[S_SBOX] = {
    0x2C, 0xDE, 0xF1, 0x22, 0x20, 0x45, 0xFF, 0x97, 0xC5, 0xBC, 0x96, 0x8D, 0xF3, 0x84, 0xD4, 0xC3,
    0x02, 0xA3, 0x44, 0xEC, 0x49, 0x7A, 0xBA, 0x54, 0x1A, 0xC2, 0x8F, 0x6E, 0x63, 0x41, 0x79, 0x1F,
    0x60, 0xB5, 0xF6, 0x6C, 0x0B, 0x50, 0xA8, 0xCC, 0x7F, 0x73, 0xBB, 0x66, 0x3F, 0x11, 0xF7, 0x61,
    0x34, 0xE3, 0xE4, 0x59, 0x80, 0x7E, 0x06, 0xAD, 0x72, 0x9D, 0xD7, 0x47, 0x1C, 0x5E, 0xE8, 0x85,
    0xD5, 0x91, 0x71, 0xF4, 0xC6, 0xCD, 0x3C, 0xFB, 0x55, 0xEA, 0xB6, 0xDA, 0xF9, 0x75, 0x37, 0x6D,
    0x67, 0x4A, 0x8E, 0xD2, 0xA2, 0x87, 0xAE, 0x0E, 0x77, 0x30, 0x3B, 0x9E, 0x5B, 0x95, 0x48, 0x8A,
    0x78, 0xA6, 0xE6, 0x7B, 0x00, 0xA7, 0x83, 0x5F, 0xCE, 0x0F, 0xFA, 0x98, 0x21, 0x16, 0x25, 0x92,
    0x13, 0xBD, 0x46, 0x42, 0xC4, 0x51, 0xAC, 0xDC, 0x4F, 0x52, 0x65, 0x90, 0xE9, 0xC1, 0x12, 0x0C,
    0xFE, 0x5D, 0xAF, 0xE0, 0xB4, 0x4C, 0xFC, 0x15, 0xA5, 0x07, 0xAA, 0x24, 0xD0, 0xC0, 0xB2, 0x4B,
    0x6A, 0xE5, 0xD3, 0xAB, 0xD6, 0xBF, 0xB0, 0xBE, 0x88, 0x94, 0xF5, 0x53, 0xDF, 0x86, 0xA1, 0x57,
    0x33, 0xB1, 0xD8, 0x93, 0x1D, 0x40, 0x18, 0xF2, 0x6B, 0x3E, 0x28, 0x1E, 0x82, 0x38, 0x89, 0x56,
    0xCF, 0x76, 0x39, 0x8B, 0x36, 0xF0, 0xE1, 0xA0, 0xB9, 0xEF, 0xEE, 0x2E, 0xE2, 0x10, 0x5C, 0xE7,
    0x81, 0x64, 0x2A, 0x05, 0x3A, 0x35, 0x26, 0xD1, 0x5A, 0x99, 0xB7, 0x7C, 0x69, 0x7D, 0xF8, 0xCA,
    0x0D, 0x62, 0x14, 0xA4, 0x2F, 0xC8, 0x9A, 0x29, 0x58, 0x4D, 0xDD, 0xC7, 0x19, 0x2D, 0x08, 0x17,
    0x01, 0x3D, 0xD9, 0xDB, 0x31, 0x23, 0x70, 0x0A, 0x9F, 0x4E, 0x2B, 0x68, 0xB8, 0xA9, 0xCB, 0xED,
    0x04, 0xC9, 0x8C, 0x6F, 0x09, 0xFD, 0x32, 0x03, 0x74, 0xEB, 0x43, 0x1B, 0x9C, 0x9B, 0xB3, 0x27
};

const std::uint8_t LardExpander::kSBoxF[S_SBOX] = {
    0xF6, 0x4B, 0x0A, 0x45, 0x9B, 0xBE, 0xB9, 0x13, 0x93, 0xAD, 0xF1, 0x29, 0xD4, 0x59, 0x07, 0xB2,
    0x55, 0x8A, 0x5C, 0xF3, 0xD3, 0x89, 0x8C, 0x2A, 0xB1, 0x50, 0xF7, 0x00, 0x8F, 0x41, 0xB5, 0xAC,
    0xB3, 0xDD, 0xC9, 0xDE, 0x25, 0xD5, 0x24, 0xE3, 0x94, 0xF9, 0x6E, 0x92, 0xBC, 0x1F, 0x2B, 0x51,
    0x12, 0xA2, 0x61, 0xA5, 0xA6, 0x76, 0xAA, 0x39, 0x1B, 0x5F, 0x3B, 0x60, 0x90, 0x66, 0x0C, 0xBB,
    0xE5, 0x32, 0x27, 0x17, 0xAF, 0x01, 0x80, 0x46, 0xC8, 0xD2, 0xE1, 0xB4, 0x98, 0xD8, 0x2E, 0x3C,
    0x70, 0xEF, 0x15, 0x26, 0x68, 0x65, 0x05, 0x38, 0x06, 0xED, 0x43, 0x63, 0x7B, 0xCD, 0x31, 0xEA,
    0x57, 0x97, 0xBF, 0x6B, 0x8B, 0x75, 0x9A, 0x84, 0x3D, 0xDA, 0xA4, 0x42, 0x79, 0xDC, 0x86, 0x0E,
    0xC1, 0x4F, 0x82, 0x7D, 0x71, 0x37, 0xDB, 0x95, 0xF2, 0x0B, 0xAE, 0xD0, 0xEE, 0x6C, 0x23, 0xE6,
    0x5B, 0x5A, 0xE7, 0x9E, 0x3F, 0xCE, 0x85, 0xE0, 0xAB, 0x48, 0xFA, 0x64, 0xF8, 0x8E, 0x1E, 0x0D,
    0xFF, 0x83, 0xC4, 0x18, 0xD9, 0x91, 0xC0, 0x73, 0x34, 0x2F, 0xF5, 0xE9, 0xA9, 0x87, 0x54, 0x16,
    0xD1, 0x22, 0x6A, 0xEC, 0x72, 0xA3, 0x6F, 0x36, 0x1D, 0x5E, 0x09, 0x4E, 0x78, 0x7F, 0xD6, 0xF4,
    0xDF, 0xE4, 0x9D, 0x08, 0xCC, 0xE8, 0x7C, 0xB6, 0xB0, 0xCF, 0x2D, 0x28, 0x40, 0xFD, 0xB8, 0x5D,
    0x44, 0x4C, 0xD7, 0x96, 0xA1, 0xF0, 0xBA, 0x1A, 0x99, 0xA0, 0x03, 0xA8, 0xC3, 0x4A, 0x7A, 0xC2,
    0x04, 0x6D, 0x02, 0x49, 0xCA, 0x1C, 0x9C, 0xEB, 0x47, 0x2C, 0x77, 0x4D, 0x8D, 0x14, 0x19, 0x3E,
    0x69, 0x62, 0x88, 0x56, 0x0F, 0xA7, 0xC5, 0xC7, 0x81, 0x10, 0x35, 0x21, 0x52, 0xC6, 0x20, 0x11,
    0x74, 0xFE, 0xCB, 0xE2, 0xFB, 0x67, 0x33, 0xB7, 0x3A, 0x30, 0x9F, 0x53, 0xBD, 0x7E, 0xFC, 0x58
};

const std::uint8_t LardExpander::kSBoxG[S_SBOX] = {
    0xBA, 0x8F, 0xDB, 0xD8, 0x6A, 0xD6, 0xB9, 0x26, 0xE5, 0x40, 0xD5, 0xBF, 0x69, 0xAE, 0xDF, 0x65,
    0x1D, 0x18, 0x25, 0x31, 0x06, 0x4B, 0xC0, 0xEC, 0x36, 0x96, 0x0D, 0xB0, 0x93, 0xE4, 0x0A, 0xF7,
    0xD2, 0x51, 0xA8, 0x02, 0x0C, 0xDE, 0xBB, 0xF4, 0x8A, 0x5A, 0x33, 0x52, 0x32, 0x95, 0x5B, 0x21,
    0x91, 0xA0, 0xD3, 0xCF, 0x9C, 0x79, 0x2F, 0x7A, 0xA9, 0x76, 0x9E, 0x64, 0xB6, 0xBC, 0x03, 0x5D,
    0x2C, 0xA6, 0xE8, 0x1A, 0xA4, 0x07, 0x73, 0x8B, 0x1F, 0xB1, 0x10, 0xBD, 0x39, 0xDA, 0xD0, 0xF1,
    0xA1, 0x47, 0xFE, 0x5F, 0xEB, 0xEF, 0x3B, 0xCD, 0x68, 0xA3, 0x00, 0x37, 0x7D, 0x94, 0xF5, 0xCC,
    0xF9, 0xD9, 0x61, 0xB8, 0xAF, 0x2A, 0xDD, 0x4F, 0x46, 0x3E, 0x78, 0xB7, 0x99, 0xE6, 0xAB, 0xE7,
    0x27, 0xB3, 0x97, 0xA5, 0x16, 0x2D, 0x89, 0x3D, 0x86, 0x6C, 0x13, 0x55, 0xF0, 0xD7, 0xD4, 0x7F,
    0x4A, 0xFD, 0xC8, 0xE1, 0xA2, 0xC7, 0xF8, 0xA7, 0x98, 0xDC, 0x09, 0x58, 0xED, 0x24, 0x22, 0xB4,
    0x82, 0x20, 0xAC, 0xFA, 0x6D, 0x01, 0x90, 0xF2, 0x7E, 0x67, 0xE9, 0x9F, 0x7C, 0x1C, 0xAA, 0xAD,
    0xE2, 0x63, 0x0F, 0x14, 0x45, 0x17, 0x84, 0x9A, 0x71, 0xC1, 0x88, 0x04, 0x2E, 0x41, 0x8D, 0x5E,
    0xB5, 0x9B, 0xB2, 0x3F, 0x23, 0x28, 0x12, 0x59, 0x81, 0x70, 0x83, 0x08, 0x53, 0x66, 0x0E, 0x92,
    0x6F, 0xE0, 0x3A, 0x6E, 0xF3, 0x62, 0xEA, 0x1E, 0x8E, 0x44, 0xE3, 0xCB, 0xC3, 0x38, 0xCA, 0x74,
    0x8C, 0x60, 0x54, 0x6B, 0xFB, 0xC6, 0x05, 0x7B, 0x3C, 0x34, 0xCE, 0x57, 0x77, 0x49, 0x4D, 0x15,
    0x5C, 0x80, 0xFC, 0x4E, 0x50, 0x2B, 0x1B, 0xFF, 0xC4, 0x75, 0xC9, 0x30, 0x72, 0x48, 0x87, 0xC2,
    0x9D, 0x35, 0x4C, 0x43, 0xBE, 0x0B, 0x11, 0xEE, 0x29, 0x42, 0x56, 0xC5, 0x85, 0xF6, 0xD1, 0x19
};

const std::uint8_t LardExpander::kSBoxH[S_SBOX] = {
    0x17, 0x28, 0xBD, 0x29, 0x4B, 0x4E, 0x83, 0xB1, 0x84, 0xC1, 0xDA, 0x76, 0xDF, 0xA4, 0xF3, 0x03,
    0xE9, 0x88, 0x25, 0x96, 0x12, 0xC7, 0x46, 0x39, 0x4C, 0x68, 0x14, 0x3E, 0x09, 0xAB, 0xCE, 0xC2,
    0x00, 0x13, 0x51, 0x5C, 0x3B, 0xDC, 0x38, 0x56, 0x49, 0x15, 0x2D, 0x87, 0x02, 0xFC, 0x3A, 0x6B,
    0xB2, 0xC3, 0x2F, 0x0E, 0x41, 0x22, 0x0C, 0xB6, 0x7E, 0x6A, 0xFA, 0x2C, 0xCB, 0xE2, 0x73, 0xCF,
    0x98, 0x36, 0x77, 0x33, 0x8D, 0x3D, 0x0B, 0x66, 0x52, 0x11, 0x1A, 0xCD, 0x04, 0x92, 0xBB, 0x37,
    0xEC, 0x1B, 0x7F, 0x74, 0xE3, 0xAD, 0xBF, 0xB5, 0xF0, 0x57, 0xE7, 0x63, 0x6C, 0xD3, 0x79, 0x9A,
    0xA5, 0x06, 0x4D, 0xAC, 0x8B, 0x6D, 0x48, 0x89, 0x34, 0xDE, 0x0D, 0xE4, 0x20, 0x10, 0xC5, 0x3F,
    0x9E, 0xAA, 0x47, 0xA2, 0xEF, 0xB7, 0xDD, 0x4A, 0x95, 0xBE, 0x8E, 0x5D, 0x18, 0x61, 0xF5, 0xD7,
    0xE8, 0xEB, 0xD4, 0xCA, 0x78, 0x9C, 0x8A, 0x19, 0x0F, 0x67, 0x5A, 0xAE, 0x16, 0x0A, 0xFF, 0x70,
    0xDB, 0x44, 0x1F, 0x31, 0x91, 0xC8, 0x9D, 0xA3, 0xF8, 0xB8, 0x58, 0xD5, 0x43, 0xC6, 0xEA, 0x30,
    0x5E, 0xF6, 0xAF, 0x54, 0xA0, 0xC0, 0x2E, 0xB4, 0xB0, 0x69, 0xF2, 0xA9, 0x23, 0xEE, 0x93, 0x5B,
    0x5F, 0x9B, 0x85, 0xF1, 0xD0, 0xD6, 0xA1, 0x81, 0x4F, 0x9F, 0xF4, 0x75, 0xA8, 0x97, 0x80, 0x26,
    0x2A, 0xE5, 0x90, 0x05, 0x8C, 0xD9, 0xCC, 0x7D, 0x07, 0x8F, 0x71, 0x40, 0xD2, 0x2B, 0x6F, 0xD1,
    0xBC, 0x62, 0x72, 0x64, 0x1E, 0xB3, 0x86, 0x99, 0x65, 0xF7, 0x21, 0xE6, 0x45, 0x7C, 0x32, 0x7B,
    0xE0, 0x60, 0xC4, 0xA6, 0x3C, 0x42, 0x1C, 0x50, 0x08, 0xFE, 0xFB, 0xB9, 0x24, 0x53, 0xBA, 0xFD,
    0x6E, 0xD8, 0x1D, 0x55, 0x59, 0xE1, 0x35, 0x82, 0xF9, 0x7A, 0xC9, 0x27, 0x01, 0xED, 0x94, 0xA7
};

const std::uint64_t LardExpander::kSaltA[S_SALT] = {
    0x324422C0F3B551EAULL, 0x04E1F6BA562BEB92ULL, 0x8D78A93DE23D77E1ULL, 0x2C2AF8CDD5513678ULL,
    0xABD70F2706ACF3C7ULL, 0x77B21890246356E8ULL, 0xA59BADC60BDED0F5ULL, 0xF339B357E4C483D4ULL,
    0x6C7826F1B2E7FC52ULL, 0xA12381AEDE7454A0ULL, 0xD3755E39CB1B7B88ULL, 0x66DB7C403E78BA58ULL,
    0x1D5F4D4B087693BFULL, 0xF7853F06658CA793ULL, 0x759DEAD48144981DULL, 0xB08487095B2A201DULL,
    0x40FE32C61AACB637ULL, 0xE5EE1BBA6AECBADFULL, 0x9DA9AC6076A564B5ULL, 0xCA25C36435E23FEFULL,
    0x3B3A4C787D9A6155ULL, 0xA60F51D5B5630A3DULL, 0x7D1A0ABFA385D9A7ULL, 0xE08AD9DBFF5F92A3ULL,
    0x0DD0AB9724128269ULL, 0x6D11E2DF57C0B8EEULL, 0xF69CD880770BB58AULL, 0x0EAE093183690B4CULL,
    0xD5439ADE319203D2ULL, 0x192008C826A28D97ULL, 0xE2689D2C967ED770ULL, 0x117E75C8D5DFBE6FULL
};

const std::uint64_t LardExpander::kSaltB[S_SALT] = {
    0x9C9B08E22BB13032ULL, 0x75F8C1D706AB0E0BULL, 0x1B33BB0DBD9C5524ULL, 0xC3E65C709DD93368ULL,
    0xB10C704036004F74ULL, 0xA8B3741FA2DB812BULL, 0x7001DC8F92028A8FULL, 0xC2F56C1906FAC0CFULL,
    0xFBFC7DC14D278314ULL, 0x8BFA0BEEFEE2E4F6ULL, 0x910825CA4C853832ULL, 0xF47098442BA29AEAULL,
    0x081342A0C436F297ULL, 0x21905A895A33936AULL, 0x67AEA49658B82063ULL, 0xBF3AC63EC6B517FFULL,
    0xC1B9ADEACF85A8AFULL, 0xB3DD66221BD665A7ULL, 0xE5502B61A240B00AULL, 0x8EDEF39D3BFD0281ULL,
    0xF7D5FBC7D9B7D09BULL, 0x747003EA2B29A7C2ULL, 0xE6FD9183F5DB231EULL, 0xFA6180597844236AULL,
    0x536A823C561D6123ULL, 0x7C8B43FAE5CE32C7ULL, 0xD80532E9A61C36B8ULL, 0xF8F504FE3334A539ULL,
    0x5458907E9E70CA83ULL, 0x3FB83CB480FF9685ULL, 0xE924ABEE38FD3D6FULL, 0xD1D4E920BBAD3EE3ULL
};

const std::uint64_t LardExpander::kSaltC[S_SALT] = {
    0x040753F0CAA9C68FULL, 0xDFB767CE2FFF445DULL, 0x3CD1AC4336D19FEAULL, 0x3661E89FBF450A7AULL,
    0x5BFBEEE6CE973487ULL, 0xD2073E02CB4173CCULL, 0x58115826DB944FD8ULL, 0xA52495ADBF56942BULL,
    0xB8BB01A07A99DC17ULL, 0x0AC24941A676B0EBULL, 0x63D94AC93302A30DULL, 0x1DAA1EC23E24C38EULL,
    0xDABBD2C378ECE0FEULL, 0xD7AF655F9329AD9DULL, 0xE57A53A5F7DF0E05ULL, 0x92C35827FBD708B8ULL,
    0x04D57CE100FD3C1FULL, 0x43020E72325DDD9AULL, 0x89DBA811AED97F10ULL, 0xCBA14A24E148C359ULL,
    0x0F217BB0CBD6B6EEULL, 0x5834CEBD72775255ULL, 0xAF1B218AAB061E41ULL, 0xA4E932E090A7A1EEULL,
    0xD09482E230ECA0CFULL, 0x0507EDFC1316A000ULL, 0x0E4B14770EF5EFE9ULL, 0xCA67D4A0759C15C8ULL,
    0x44C0FE10660D48CDULL, 0xD7EB3C263D9819B7ULL, 0x721F8A24CD33E880ULL, 0x85E8750758CF875BULL
};

const std::uint64_t LardExpander::kSaltD[S_SALT] = {
    0x05990B94DABEA076ULL, 0x1AA29E589C75496CULL, 0xF6E9065026D47454ULL, 0x778F1C6FEAC05859ULL,
    0x987D8CCBF5D8662FULL, 0x7982D2AE4FB3F57FULL, 0x1EA5E39E558EF317ULL, 0x59F3CEAF9D37A0D5ULL,
    0x3FA345C11DE8DA47ULL, 0xE652FEA404CEE706ULL, 0x66D5A387D4E5558CULL, 0x4AE6A073BE716E5FULL,
    0x8CAE9BCC25C33801ULL, 0xA11A2330CCD053B8ULL, 0x0FB49FC220769C0CULL, 0x7F0DBF42E29A6E71ULL,
    0x50631303C54BDF1CULL, 0x57ABF56BD9BA87E3ULL, 0x0ADF40F63AF05E73ULL, 0x446EFA51096FBD0CULL,
    0xC000A0AFDF7363DFULL, 0xF99CE523D7E51F44ULL, 0xE73A5A947F763C43ULL, 0x5753B8600794CD4FULL,
    0x4B724892F7AAC2A9ULL, 0x4A6F74352CE924D2ULL, 0x366FCDBC28BF90EBULL, 0x7BB173E4ADE724F0ULL,
    0x46BA394715E549CBULL, 0x6DD97B127FB0592BULL, 0x23844ED9626E7EC8ULL, 0x3D6784C4DBD2B5FBULL
};

const std::uint64_t LardExpander::kSaltE[S_SALT] = {
    0x6BB781E246A192A0ULL, 0x13029AF3C556279BULL, 0x92B73EE4AA4A0446ULL, 0xC126C8689791A775ULL,
    0x64411C6D1CD4E5FCULL, 0x40A4A9079798B4A7ULL, 0x4635E081A3BBCE3AULL, 0x5ED67CA3BBDA9CC9ULL,
    0xB662F6D3A3C16624ULL, 0xE084DF9F422C2285ULL, 0xC328E2040F591FC9ULL, 0x8358710F0717C739ULL,
    0x04A32E13E20CF6B6ULL, 0xB473561187DA7D63ULL, 0xBF3F486ED8B3F30AULL, 0xF7A9569D90E2088EULL,
    0x2178EFCF5D416F0EULL, 0x36B1F0679B7A3104ULL, 0x9D296EF7BD61C7BAULL, 0xB35D6FF704E1975BULL,
    0x2BC995DA24AEC02EULL, 0x1F119AA59AD0C33AULL, 0x31DA8991BD0FDDE5ULL, 0x9CD2F7C0FB071489ULL,
    0x96305CF167DC87A9ULL, 0xB890AF360DF59315ULL, 0x722F278DC0AEA3C6ULL, 0xCD1EF3CAFF449EBEULL,
    0x76F679BEBBD90521ULL, 0xA29024DE7FD39ADBULL, 0x2558BA8A73E22402ULL, 0xD41DB45589EB13FFULL
};

const std::uint64_t LardExpander::kSaltF[S_SALT] = {
    0xEDD172F46F7C5E47ULL, 0xDAF4BD2B6C920B75ULL, 0x7364DC9762CA699AULL, 0x7B4625F6D8AA1DB9ULL,
    0x55A76DDC0C8F5C2AULL, 0x3A2C53991AD84B5CULL, 0x46BECB4CDBBF9C39ULL, 0x3469A330A40DB1CAULL,
    0x6D02885751620391ULL, 0x9406C1328C54523EULL, 0xCD7D37EC2F6E980EULL, 0xF9FBB5FDB1C6226CULL,
    0x378DF69A2D98DBAEULL, 0x97377DF406FC5AD2ULL, 0x4A690CBE874408E5ULL, 0x3BF4BEE7E2BA1D48ULL,
    0x0B4F3D161036F63DULL, 0x44DC2F99A21C63C3ULL, 0xA2B77841A942283EULL, 0x49C35C58E08CE49AULL,
    0x6873872FECDA1C04ULL, 0x361E0DEC182C3C45ULL, 0x183C0C42FE10F993ULL, 0x50E0D1B1D560027DULL,
    0x2CFB28F4B8AF431FULL, 0xFE2F4ED1BBF82BA1ULL, 0xEAA881B7BE670593ULL, 0xFCC414C7A68D7382ULL,
    0xE0A6054AB5A302EAULL, 0x9257A06D47ED1CD6ULL, 0x214B82D05EE2FC5EULL, 0x4273FF8161DE4B41ULL
};

const std::uint64_t LardExpander::kSaltG[S_SALT] = {
    0x3FB0FBF01BDA7378ULL, 0x7B29399B10F3DAE4ULL, 0x0FB1792793A5D3FAULL, 0x7CA6B2DCE0AE49D6ULL,
    0x75F4BA4FC63602E7ULL, 0x28BC57FEF9049BD1ULL, 0x803F651DCED62B61ULL, 0xD88C379DE1CCD448ULL,
    0x9863FC698D8BB4D6ULL, 0x11827E3FA25F0AC8ULL, 0x7CB672A336F4FAB2ULL, 0x59E0BBDAC3EB9B6FULL,
    0xC8879A1AF366F1F1ULL, 0xE69F10C0C9904A52ULL, 0x39F75C94DDF437A9ULL, 0xD97BFB463F818B1DULL,
    0x20F659597CFCE592ULL, 0x2702D0C8DD9E7FB5ULL, 0xED77F500D6BC0664ULL, 0x40B77407BE97A0A0ULL,
    0xEC61C6B85BE47B39ULL, 0xEA28DCBA8C95CDF6ULL, 0x12E09BC10F42ADD9ULL, 0x3C6DD4607DA8F084ULL,
    0x9756AEF13B8B5C40ULL, 0x4E763FB04285C07EULL, 0x5B6F29A625B9698CULL, 0x21CAA24A1ED7DF57ULL,
    0xFE22E7C1BDCDB570ULL, 0xC1D7C689582FE4C7ULL, 0xFB4336A29C227E92ULL, 0xF0DA4A5F0E689D82ULL
};

const std::uint64_t LardExpander::kSaltH[S_SALT] = {
    0xAAF9061B68211A04ULL, 0xD422D09E2D9CE9D9ULL, 0xDE2BBF1B3E116077ULL, 0x9F859C15E1837A3CULL,
    0x3DD651E756458F54ULL, 0x49A1DBD1D008C876ULL, 0x964A5AAF9AA0F7AEULL, 0x441F2125683EBE46ULL,
    0x817113812CD8BD79ULL, 0xC6D4D04F67017845ULL, 0x9F659421D4FD01CBULL, 0x2B8BD38B3ACDCEA7ULL,
    0x94BAD8A19204BCF8ULL, 0x232CD746A777E83DULL, 0xF204D4FF24D0804AULL, 0x3C5766AD04ED8003ULL,
    0x7E56B7DF8B90DE16ULL, 0x43BB0F157014F196ULL, 0xD6A6874777B952F0ULL, 0x988A882BD4F4E5AFULL,
    0x19205DC6F05899ACULL, 0x7AA26AAB6E3F3A78ULL, 0x6ADEEB0CFD4CF218ULL, 0x158B73900BFCAB04ULL,
    0x71D85A62AA114156ULL, 0x5E2564A90F38258EULL, 0x858B3311A3EB55E1ULL, 0x91726E5C01C37F07ULL,
    0x255E6DAB42F5A295ULL, 0x21B1728EA8C84960ULL, 0x1B6CCEFFA9E2A9D1ULL, 0x7B5772C02DBFB112ULL
};

const std::uint64_t LardExpander::kDomainSaltKeyBoxA[S_SALT] = {
    0xD25329621F0BCF47ULL, 0xCFA338F809F24749ULL, 0x13E6FDBB5C0F7FB9ULL, 0x1BD59A666E52B796ULL,
    0xD00E17B88F8AADF6ULL, 0x1DFA15ADC70DB3B4ULL, 0x7CA77A77BE5919D9ULL, 0xD2AF1DDEB35D225DULL,
    0xCCF57D599CA2E9F0ULL, 0xB4BD8992AF76285FULL, 0x3D1FB1E3FDAF3203ULL, 0x06FD57C83AA643BBULL,
    0x3A8DE2ABEA0A8AB7ULL, 0xB1474C554C8A089CULL, 0x59E154BC2A27C606ULL, 0xA82058B48BB903E3ULL,
    0x19799BCB44915AC1ULL, 0x7778C4FC7FBF94AFULL, 0x6E372736081AE100ULL, 0x5AB3518FBDFF8346ULL,
    0xF8AEA8B44E5E282BULL, 0x259284788A432537ULL, 0xBF74E01692DC5069ULL, 0xDE18EF9350E14CCEULL,
    0x3E4CCAF65F55FA1AULL, 0x39362FDC1DE209E4ULL, 0xCEDDAB4120D29B7FULL, 0x3A9461782F11BAB6ULL,
    0x0A855077793DD651ULL, 0xEDB240857CCE6FD6ULL, 0x6F9401A216537DE2ULL, 0x9403A158F4FEFA05ULL
};

const std::uint64_t LardExpander::kDomainSaltKeyBoxB[S_SALT] = {
    0x274E111BE2231534ULL, 0xC84F73E758DB1CA0ULL, 0x8E5C9571C331938AULL, 0xF1605E1BB1271D5BULL,
    0xCF2FA1CEF4127855ULL, 0x27B84D747EB4C72BULL, 0x409EC549CE787B27ULL, 0xB99F30F88BF1086DULL,
    0xDA9CE3A3248968B5ULL, 0x48DB0767BA3E4B69ULL, 0x9D49C0824FA1386EULL, 0xD0D7B82420FBA202ULL,
    0xDB750B4CD49CFF2EULL, 0x579CDF3E5A8CAA26ULL, 0xB02D3659C3ABE90FULL, 0x1EAB567BF8BBDD68ULL,
    0x87D13C29A5C7B2ACULL, 0x290C17F7E6BEC02FULL, 0x6DF98068EE2D7D8DULL, 0x1A93498A8A242726ULL,
    0x5B02F3A9D5EB2CDFULL, 0xEAABB5BA82EC6AEDULL, 0x3C4E57DDF43900C6ULL, 0x82F7C23AFDA7FFE2ULL,
    0x03ABEE95D8AF9B93ULL, 0xAE4C086A8D226688ULL, 0x87B11FCC82F29463ULL, 0xBDCDE3F513A2098DULL,
    0x1FC7033AF19BDD4FULL, 0x6E560434AC0B3209ULL, 0x9426CE64827D4E8BULL, 0x662B4237C43AAFE2ULL
};

const std::uint64_t LardExpander::kDomainSaltKeyBoxC[S_SALT] = {
    0x3F081F063827A030ULL, 0xB7B1650312CD99E2ULL, 0x7D4EEC799B947FABULL, 0x2ADA919179A03FCDULL,
    0x1EBAAA1D44DC5B1EULL, 0x157B691174537D9BULL, 0x78A790BED20424C1ULL, 0x3AEAC18FE9696E21ULL,
    0x5FE33DEB2FFA000CULL, 0xBE5CBC15A5C87893ULL, 0x1A60E602E21F11BBULL, 0xD160F14154BCA86CULL,
    0xF24D7480E4C963A8ULL, 0x53C07409ED893273ULL, 0xD22387AD768CFC28ULL, 0x6F824625FDF476E2ULL,
    0xF9CDDF67DF697C8DULL, 0x4A2DD2A19B25DC70ULL, 0xBF2A4614690123C4ULL, 0xBD5AD697F3057979ULL,
    0xD35B7F0CB13FBD20ULL, 0x7E966AB6B2AC073CULL, 0x6F662FACC0ADF2B9ULL, 0xE59FD3021DB81FEFULL,
    0xA1ABD81D4EA73282ULL, 0xF8A7ADBD7416344BULL, 0xC2B79520854645FCULL, 0x88DDE20DE26FA01DULL,
    0xFF0F13AAE7174048ULL, 0x569BED59BDEF2B70ULL, 0x9C8FB3DA9B8570D7ULL, 0xE8E3457E3A2C24BFULL
};

const std::uint64_t LardExpander::kDomainSaltKeyBoxD[S_SALT] = {
    0x6240B90B5449D3F1ULL, 0x4216CB634972EB9AULL, 0xDAD446B161107DF5ULL, 0x71C6F665D2790030ULL,
    0x4E9063D553B879BAULL, 0x03ACAE85318DB9FEULL, 0xC691EEF2B5819641ULL, 0xE8DAA3DE2F93EEA8ULL,
    0x0C8FAE8B0A2FDD4AULL, 0x2ED93218D16216E2ULL, 0x4BDF1E3D403B7C94ULL, 0xA717ECD5192687ABULL,
    0x920E750ACC24868CULL, 0xB38EDE9B59A3CE1BULL, 0x1066D71264E98D19ULL, 0xC718F7401357277BULL,
    0x9B24AD80C7C48D79ULL, 0xEC0399621C7574A6ULL, 0x559D1F91132EE02FULL, 0x2BD82A09BEE8BE71ULL,
    0xE5ADEBA9C4C1E884ULL, 0xE3921E92D26B1A46ULL, 0xFEC0BC9A9F18A2F3ULL, 0x321119E87BF3583FULL,
    0x86347B3060C3D3FEULL, 0x12F9915ADAC2CA6EULL, 0xFA3234CAC75AE8E4ULL, 0x613D2A31BA58903FULL,
    0xDF33E0BA206CC64BULL, 0xD75217E1A10A46DFULL, 0xDCCBAD921DDAC5D1ULL, 0xAC8DBF1ABE50950FULL
};

const std::uint64_t LardExpander::kDomainSaltKeyBoxE[S_SALT] = {
    0x9E6AEF0D768C0A00ULL, 0x07FA134874A9A726ULL, 0xDE29CE3FAB65302FULL, 0x41B62F52C9F406B2ULL,
    0x2B61FBC8782CB3ECULL, 0x3181FBD51A6CA92EULL, 0x30EE420981270ED7ULL, 0x59C0A354AFFFF263ULL,
    0xDEA31034F57FF418ULL, 0x72B11A9C39C33589ULL, 0xE5E12D71E3C28479ULL, 0xDA839CAFCFD264CFULL,
    0x5D976EC0D8E46F63ULL, 0x265720EA85F633A6ULL, 0x0ACE9F1DC644AB8CULL, 0x0611589444FE853DULL,
    0x11C5556EF9DBFFE4ULL, 0xE456B1BB3494C241ULL, 0x36770C1A8856C06CULL, 0x2A5960D7F972EA51ULL,
    0x10DADC6071D38CB2ULL, 0x1F9AF4C547FA132FULL, 0xF3194B6B63D892C2ULL, 0xE5D0E6FFE3254865ULL,
    0x5A6FD0EA1B05E5BCULL, 0x09D4612D29489DB3ULL, 0x72AD77E6EF0B50F1ULL, 0x977EAA595C4D224EULL,
    0x97DC4864BDD901BEULL, 0x71942BCC8EF46D94ULL, 0x31DB31DD5710AEC7ULL, 0x7A8A12738AF16F13ULL
};

const std::uint64_t LardExpander::kDomainSaltKeyBoxF[S_SALT] = {
    0x946A1767DBDEE43EULL, 0xD3BB8278F36D73E5ULL, 0x880D8C0FD5BCD429ULL, 0x50FD9C765E2FAB52ULL,
    0x66AB23B66DEA512EULL, 0x72D82083BCB5EBB9ULL, 0x8B6D045CDFE20D59ULL, 0x3347E758987122CCULL,
    0x3BCCA3B83E446291ULL, 0x7670039BCB52D794ULL, 0x2D431D64C51A48CAULL, 0x11CC08580D691FB9ULL,
    0xEBE66E8E924E66FCULL, 0xAFF0DBE3BD2AC32DULL, 0x76766522949140FCULL, 0x5EC3347BA63255ADULL,
    0x7B97F1AFAF3611D4ULL, 0xD205367172EB7F82ULL, 0xADCFB6BD03DAEE79ULL, 0xF04FC9FDEBC93BD7ULL,
    0x7D673C8A937AB030ULL, 0x207F04EAB6A2963CULL, 0xB8A6D923B2EF81B7ULL, 0xC30AB04FFA30A00CULL,
    0x1D4D3DE2E5380A30ULL, 0xE350AD615E7967F6ULL, 0xA4B0EF40A98ECCE7ULL, 0x4AE81056F2CD19F7ULL,
    0x5C299C2AEBBF994FULL, 0x20FD68B3C9321F7CULL, 0xFD1EB6E9A7932E29ULL, 0xD52F86598D93A5D8ULL
};

const std::uint64_t LardExpander::kDomainSaltMaskBoxA[S_SALT] = {
    0xA8260C73B5A5AE16ULL, 0x834655BC2EE2CFC2ULL, 0xC0F3E20D4F2295FAULL, 0x6CB72C0FFC29EB4CULL,
    0x222B087B366D7B29ULL, 0x3836C375DC4F8E9DULL, 0x7C6ABAF4FCB4D937ULL, 0x4E0F894053465F57ULL,
    0x62A116C9BE02D9D9ULL, 0x9EB2ADADB76AA549ULL, 0xD0D1DA9ED94ED70BULL, 0x5FBCBE1EC285EA02ULL,
    0x63A56CBF08F06AFDULL, 0xB224D2A5C8CDC6AEULL, 0xDC17919228FEA9C9ULL, 0x0389A66EB04DC681ULL,
    0x8A5E9E6369F7A905ULL, 0x696A579F053C9C39ULL, 0x4D4E5447DE02E327ULL, 0x8A1C9BBDBCD0DF25ULL,
    0xBEF617A65737D196ULL, 0x4430475CF1A85287ULL, 0x2B7C35E8F2772F40ULL, 0x7E213C775B0F2AC0ULL,
    0x91686D7B49786269ULL, 0x3EC138ADC85ADC6EULL, 0xE54B5F21155B4275ULL, 0x75DDE48CDAC34E61ULL,
    0xC692A2EC7B051FACULL, 0x936EB8B3AD1666BBULL, 0x3B84E2F4B52D57EAULL, 0x9D4496B2BB85E803ULL
};

const std::uint64_t LardExpander::kDomainSaltMaskBoxB[S_SALT] = {
    0x1F8DFDA9DB779DF6ULL, 0x4D21E7F8FE9BB4E4ULL, 0xFE0C8C90720DD2EDULL, 0x540AD01652EBB400ULL,
    0x3D5B9697671BCA5DULL, 0x3CE700F4F955012AULL, 0x0E70F73B7C197973ULL, 0x7249D5DAF618FC21ULL,
    0x7D51FB861C4E31D9ULL, 0x97BFEAF02EEB283BULL, 0x090E4B88A16A8FEEULL, 0xB372ACEBF6D4A1D7ULL,
    0x8E78878603D9A3FCULL, 0xC6203BB5DB8443CDULL, 0x61CB251308D8B046ULL, 0x99835E7E56C77EB7ULL,
    0x86AB03FAF76B0A02ULL, 0xFB3AAB71599728A2ULL, 0x6BA03C8C65373DE5ULL, 0xCD78E7000933854AULL,
    0x02EA8148EFFECDE2ULL, 0xA04E252FEF38D06FULL, 0x09BBEF45B867F79FULL, 0x6F38439F42052BB4ULL,
    0xAAFE4569414F3A25ULL, 0x99176F52908B8477ULL, 0xCB5C6CAB12DE41CDULL, 0x5167D8EDBFE71B6DULL,
    0xDA9C0A8A3A461F20ULL, 0xDFEA457578110DD4ULL, 0x318868943EF2F02DULL, 0xE087F2F21D36B77BULL
};

const std::uint64_t LardExpander::kDomainSaltMaskBoxC[S_SALT] = {
    0x7AEA8A1E875A6832ULL, 0xE681E4034A1B7822ULL, 0xF4DB9596FCE892C6ULL, 0x70C689EFAF8D95B5ULL,
    0xAE75EA9CD2277AA0ULL, 0x94030FD10CC5FA85ULL, 0x67BB85453F47B1E7ULL, 0xEE287E4E03AC175BULL,
    0x62D70E88D97BFA90ULL, 0x413D8CAF27EFA8ACULL, 0x8008521C5CC2215BULL, 0x2D242561F18769FFULL,
    0x01D3175678BDF386ULL, 0x3A788BBC8C38BCDAULL, 0x576AA544EA170304ULL, 0x55C756540B88412BULL,
    0x1E87524B5C5CD4DCULL, 0x8E28AB21CE316D3AULL, 0x668B972E851654ABULL, 0x8FF33F7FA9EC47F1ULL,
    0xE55BDD5D3AB05EA2ULL, 0x6B15DDB1EA9D50B8ULL, 0x937BB486DEA86BBFULL, 0x0F905D68DA7C105BULL,
    0x2E5CC3D28E03C379ULL, 0xF0697DE12C9C4A98ULL, 0x7BE277B4D52F5D3BULL, 0xA48464D311F3BCCCULL,
    0xC9F9F1481E98233CULL, 0x21A9D3EC3007BC84ULL, 0x7AB08E3A92B772FCULL, 0x890DC772280DD86BULL
};

const std::uint64_t LardExpander::kDomainSaltMaskBoxD[S_SALT] = {
    0x953040394D6362C1ULL, 0xBE83295DF7F86512ULL, 0x779FCF206B5BCF98ULL, 0xEC33305CFF17F229ULL,
    0x24D6362A2C5B3C56ULL, 0x3AF43B3A5A94D64BULL, 0x2FF1F7E9BC6F381DULL, 0x385B9458072789CFULL,
    0x1D1B429AB9385F2FULL, 0xF0A3033FF8377A3FULL, 0xB61135DD2E87E3B7ULL, 0xD9402CDA7BA8E59CULL,
    0xF63FE24EDFDD39EAULL, 0x80D2BD847EE45F81ULL, 0xC27CF40107EE4DA5ULL, 0x2F61B33E9BEAA6ECULL,
    0x5EDF2CF167522FB0ULL, 0x62FAB7BDC322D449ULL, 0x26C5D0525C8AC6A4ULL, 0x1A923DEB54B8F8E1ULL,
    0xC28218FC1D3AA530ULL, 0xD7F31D8DB872C006ULL, 0x8799BF96EAB41B14ULL, 0x1747837E72C1AC68ULL,
    0xBAC66A60C02DF06BULL, 0x3FBD495523C85CB9ULL, 0x6D7813FDACD72171ULL, 0x9E2E4927F02B659CULL,
    0xC39A6F8DFF28622BULL, 0x8886A6A939A48D8BULL, 0xBFAAB847B7FF381CULL, 0x61406A300758C89CULL
};

const std::uint64_t LardExpander::kDomainSaltMaskBoxE[S_SALT] = {
    0x01D70030D82C45C7ULL, 0x0F80D961246D80D2ULL, 0x0A36A647E57DEC12ULL, 0x4CAB9125EC3D365BULL,
    0x039928792BB921B6ULL, 0x13700EF927DB15B0ULL, 0xD82989D4A7EB5315ULL, 0x49473F607811C0D0ULL,
    0x82FD8F08A8C4CB78ULL, 0x1BF31D887902FC90ULL, 0x50DAC6C781013CA5ULL, 0x3B494B0288D332F5ULL,
    0x775218D86E651A4AULL, 0xB5782EE2A7F0E79CULL, 0xB4FA051980DB2E44ULL, 0x4C07658534FBAF72ULL,
    0x550E57D1D5FE8062ULL, 0x3B69106C90CAD6D4ULL, 0x08DF9EC5D643EE15ULL, 0x4B55405F56E2F77AULL,
    0x4CB146F337975426ULL, 0xD74B3C0B8B74047CULL, 0xF1777097278551D9ULL, 0x0B5B0B70EA9E8B48ULL,
    0x1EE3E3D856BEEBD6ULL, 0x6DE4BB3D4968EF8AULL, 0x1A65A35A2461F35DULL, 0xE3DB31CC67016105ULL,
    0xA5B736A18101E591ULL, 0x4A04C635612FAEF1ULL, 0x9710A4775D8CBD4DULL, 0x3414C13B9D0FDC18ULL
};

const std::uint64_t LardExpander::kDomainSaltMaskBoxF[S_SALT] = {
    0x481F24ADD8D14255ULL, 0xF56BEB55E3A0BD29ULL, 0x78DE3956FAD9C910ULL, 0x2B72EB9FED0C3DB3ULL,
    0xC68BABCF7933A0ABULL, 0x7F2912A385B08E27ULL, 0x40DC07A65B52CBA2ULL, 0xA2FAB5BDCD5769A0ULL,
    0xFED26E8D91AA6F8AULL, 0x83D657BA7C8521EAULL, 0x6E6B0BB0096293A6ULL, 0x8B43B3D1DCE639A1ULL,
    0x63432F30C5ECD226ULL, 0xB65DEBC90A277DCEULL, 0xEC6EAA3EAE4DF500ULL, 0x2E59D9615EDC1553ULL,
    0x49F0F1835D079BA4ULL, 0x7AC446BC96055C02ULL, 0x1F0A2426010365C7ULL, 0x19F6ABF0A935431AULL,
    0x7D138860B4261B27ULL, 0x240612B2A1BF899BULL, 0x8129F71171FED912ULL, 0xD66A866A924FCE06ULL,
    0xE3012A8767409004ULL, 0x9B2625FB50C87E88ULL, 0xB1C806E971934EA8ULL, 0x04E2DE6E26E5710BULL,
    0x2CB9DD95AEE96E0BULL, 0xEFB1414072727A87ULL, 0xDEBC0EEAF8C476F5ULL, 0xDA39EB02A18B5686ULL
};

const std::uint64_t LardExpander::kDomainSaltWandererA[S_SALT] = {
    0x2E533CFDCBB5B552ULL, 0xD68AA0240A7E7B33ULL, 0xAE9FDE8E0BAABEE1ULL, 0xCAC2186DE1C476F2ULL,
    0xC8C7B9BF0D838CC4ULL, 0xCF77D772BC3CE599ULL, 0xDDE29C5FC6F37887ULL, 0xEB8324E24A7B476FULL,
    0x5FC8A78B7BDD4F1DULL, 0x196209E5A1AEA368ULL, 0xDB38AE599B6C33A4ULL, 0xA96E810285EA7164ULL,
    0xBC068C641C4722E0ULL, 0xC9CE212F7021B32EULL, 0x94487324650A080AULL, 0x981FFF13B5ECC880ULL,
    0xAB56D1869A4FBE0EULL, 0xAF8C5C8EAF2A9D05ULL, 0x6ECCC291D12279A1ULL, 0xA161717EF0D7EBFFULL,
    0x41FF520E5D5369A8ULL, 0x35869DF9B932F64FULL, 0x9765421F8BEF9F7AULL, 0x35B7896F1957194BULL,
    0xBA3BFED0FB59EF78ULL, 0x03886DE1FF8F23C5ULL, 0x0632204BEBD61531ULL, 0x4F1963E2AAFDF5C5ULL,
    0xFB46356AAC7196C3ULL, 0xF3488F7A5DCDB8A1ULL, 0x2F3DDE48904C8AB4ULL, 0xF669C9963ADDBAF6ULL
};

const std::uint64_t LardExpander::kDomainSaltWandererB[S_SALT] = {
    0xE04080D8A4F333EBULL, 0x6DBBD9200934ADB9ULL, 0x4098D1CA9BCFADADULL, 0x5A2B4675998FEE53ULL,
    0xE0FE06D344353DD8ULL, 0x5594741A49358A09ULL, 0x90BAF8B9C99BAC80ULL, 0xE6F28F9A243F83C6ULL,
    0x200A5A5E1BAEF942ULL, 0x5AB54DF0B20D84CCULL, 0x563EA5DB85EA835FULL, 0xAC464EE7C91FD46EULL,
    0x16A13BE9D1599EAAULL, 0x841D26CE83CFFFC4ULL, 0xCDB6EC08CF2B940FULL, 0x3B5E861C752151E1ULL,
    0x90EB479F382D4551ULL, 0xDE6E9D5C56841F7AULL, 0xC3098F64F5ABCDE3ULL, 0x03812D162CBAD139ULL,
    0x0977DB73D362F3ACULL, 0x7D4BBCD8DB1599F1ULL, 0xFAE5E91BECD8F3E5ULL, 0x19560FB57F8E2AD9ULL,
    0x7B366BAD3045FE49ULL, 0x11FBF57C92341CA7ULL, 0xAF493D3C0B270A50ULL, 0xFC23C3671F6B56EFULL,
    0x98B9C165E7DB8EC3ULL, 0xF41783513FD0D4E1ULL, 0x103ADF9190A75518ULL, 0xED08775E8C7463C2ULL
};

const std::uint64_t LardExpander::kDomainSaltWandererC[S_SALT] = {
    0x5EFDD2B25BD5342CULL, 0x1595AF49824F443AULL, 0x0221B960B1A9206CULL, 0x75365F9F8D418788ULL,
    0x71D28EA83ED7DFEAULL, 0xE83F8E0AC9709C27ULL, 0xB3F8F64936B81E39ULL, 0x3009B28A7DDFAF25ULL,
    0x7DFFBCF6244E0C6AULL, 0x35496A02E768C45CULL, 0xB9C931C29CA53533ULL, 0xC3F5CAA6F9BE3E05ULL,
    0x467B94A7B5F8800AULL, 0x997083DA152A560BULL, 0x18954526A39A2EA7ULL, 0x6DE9750DC73F5833ULL,
    0xE5903EE0AEF32B27ULL, 0x4EC355C9C40F887AULL, 0xE9A03B2D37ED340FULL, 0xDE00E048927C2FE8ULL,
    0xECE1222E20893BA9ULL, 0x90F40D317876DCA4ULL, 0xD34575F0D238A537ULL, 0x24124EF696B3402DULL,
    0xAC7C84627D23018DULL, 0x35974215CB116A47ULL, 0x1AAF7A8F9B635105ULL, 0xC1AF4EFAB1188E97ULL,
    0xA3125FE3BAB138E4ULL, 0xDBBCFC86321073D2ULL, 0x254F948228CA4A8CULL, 0x3BCCC4624DC23A28ULL
};

const std::uint64_t LardExpander::kDomainSaltWandererD[S_SALT] = {
    0x52F7F510CF61CCB2ULL, 0xE951636CF637B787ULL, 0xE65866D39C4E01B0ULL, 0xF414FD477D931112ULL,
    0x3F8861A6FA0A754BULL, 0xDD06845D99F20EBBULL, 0xF3B9426F1872B51FULL, 0x3F865F208A1019A5ULL,
    0x87FCE9ACD76DB491ULL, 0xA8D8EB13341EA05EULL, 0x642D2E46A779CDF5ULL, 0x5CCC3768BBBD69EAULL,
    0x2E2515CC232D0C1AULL, 0x99F1255E8F7090FCULL, 0x305B95E9235C3BB0ULL, 0x6D0C6C3BD1470193ULL,
    0xA9705F44D8FFBFC9ULL, 0x2BA752ABA8AC3764ULL, 0x3F1E297D90A9D879ULL, 0x85257C71013B5901ULL,
    0x7C32A093346ABF24ULL, 0x0EDB5194779A655FULL, 0x76845CC3598A9B90ULL, 0xD2D989049826A79FULL,
    0xAF90D05BB2E52380ULL, 0xC7F7D97311867B3DULL, 0x208F665088178D6CULL, 0x4797C369B5A69469ULL,
    0xFC0764DBBDCDB1F1ULL, 0x923AC94AB5292B7EULL, 0x6C15412FDA7F5ED3ULL, 0x6C6673C3A53B74FDULL
};

const std::uint64_t LardExpander::kDomainSaltWandererE[S_SALT] = {
    0xEA4DA403F890808AULL, 0x0808AFB4A10217F6ULL, 0xF479BFB78CCE5F4DULL, 0x20F3270650D45EC5ULL,
    0xAC9AEC6457A72040ULL, 0x9CCFED9314D0C242ULL, 0x5B0A8C1952738180ULL, 0x9FCC446834A5BA45ULL,
    0x99C7ADE977DD0712ULL, 0x7B6CC435DAE551DFULL, 0x02F3D86DB805B72FULL, 0x474720352803A575ULL,
    0x9BD0CB49C611B421ULL, 0xCA6ED042B4DAD391ULL, 0x41BEC17B89BCF36EULL, 0xAB7446EEE3C5A0DCULL,
    0x8CD99EB4254C300DULL, 0x4A4F19CB5397318AULL, 0x3E170D47D284D8F6ULL, 0x1ED335CB973BF682ULL,
    0xDE2CFB45159054B0ULL, 0x7B6F824ED32B8BCEULL, 0x9E266A94AE920AC3ULL, 0xFBB1CB060C491B6FULL,
    0xF5FA33550FBE472BULL, 0x466C14AFBD13C743ULL, 0x9DFDF69B9BE84023ULL, 0x2AA2A42CDABAEBF0ULL,
    0x94EA01D1B4DB6BCCULL, 0xE05FBDF7D5FB26CBULL, 0xC994C42FB0F577BDULL, 0x898240156690EFC6ULL
};

const std::uint64_t LardExpander::kDomainSaltWandererF[S_SALT] = {
    0xEE4BD41A142AF32EULL, 0x0801B9040989D416ULL, 0xB023477CCCDBF41DULL, 0x732175ACFB1B3FC9ULL,
    0x0D521832B2A73DDBULL, 0x727A58685AB316F9ULL, 0x66C378AF41E1706BULL, 0xF744C89821BBE6CBULL,
    0x614DC1DB05068599ULL, 0x2F37902A1EC00102ULL, 0x759C61556F9C8228ULL, 0xB91AB9715FD6B594ULL,
    0x1309994F5B095E4DULL, 0x62D2A8C9BC022DD8ULL, 0x6F0BA0438CF8DC88ULL, 0xF542DAC126C54D1FULL,
    0x460B6470A7F0E7FCULL, 0xCD37AF4B549AB243ULL, 0x91061F7BD48B9CC9ULL, 0xFA680FCFE68E1C7BULL,
    0xA79435C981BEA7BEULL, 0x009D39CE67675035ULL, 0x7D6F24224960A1C5ULL, 0x7000AC56C92C835EULL,
    0x618F9CB1FEB6F0C5ULL, 0x72E68E0422DED4EDULL, 0xA716481D6890BB0DULL, 0x56A83AB0B6CC9F47ULL,
    0xF93D07370AEFB017ULL, 0x86EE620554175673ULL, 0xB4EC3354F47DFC15ULL, 0x1BB597C56655D227ULL
};

const std::uint64_t LardExpander::kDomainSaltOrbiterA[S_SALT] = {
    0xD0D5E8AD163B151EULL, 0x90F2AD7CF41967ACULL, 0x73F608C841D8A69BULL, 0x06945E37F9503757ULL,
    0x54FCACA1F769FDE0ULL, 0xD88DB749317E4E05ULL, 0x4087110F3C29826EULL, 0x5AD4865552CE782FULL,
    0x2FDFE07DE598268FULL, 0x943AFD4643958ECFULL, 0x6E202027B23AC8A1ULL, 0x0530BC7F89C2F618ULL,
    0x9864DACB07E8FD95ULL, 0x812945CD5D44C255ULL, 0xF91AD72C67ACB07BULL, 0x1A3567B3C449C787ULL,
    0xA8919B238E3AB77CULL, 0xB115B2923623C14DULL, 0x545D51AB52D155DBULL, 0x51C89BBCA89262B0ULL,
    0x2EBA3D613335000DULL, 0x21F68F89624E8E82ULL, 0x564611E787252C25ULL, 0x0E0171411030380CULL,
    0x9D25C5223DC9F155ULL, 0x500076ED99D0A439ULL, 0x112A00755E4E9C63ULL, 0x4CD8D2F726676C34ULL,
    0x85619C1EACD097FAULL, 0x747D93FE456E5855ULL, 0x5458DC87B34D0E0BULL, 0x09B000360027040EULL
};

const std::uint64_t LardExpander::kDomainSaltOrbiterB[S_SALT] = {
    0x3017BB46289786AEULL, 0x17EF1DF0F9645B95ULL, 0x4006288DB1189CA6ULL, 0x3B5D08E59B170C2CULL,
    0xEB654E4E9A0CDDC3ULL, 0x2F576A5512A64929ULL, 0xEC27DB3D54238736ULL, 0xD8BA5D011C10E24BULL,
    0x84067BD705641D5AULL, 0x8FC6F4CBFC83C18DULL, 0x52C244BCE70D2FA9ULL, 0x62F43A62F769664FULL,
    0x59670D76EA2AAC68ULL, 0x7F3FAF825B2EFABCULL, 0xB989B846A3F1CE71ULL, 0x7B1B024B616CC376ULL,
    0x6E7B2E150F721F91ULL, 0xD716ED54923DCDF1ULL, 0xFD1D9BDB5447950CULL, 0x06A25104FA2277FBULL,
    0xB656BC3902CD2E68ULL, 0x7F3E8E1814A0B9ABULL, 0x01F4D8DC624EB097ULL, 0x3DC822159D98136BULL,
    0xB531F79E37A2C2B5ULL, 0xA66F0871FF0AD853ULL, 0xA0CC8DB0CB7D99BBULL, 0x3ABD94CE564B3CAEULL,
    0x8D36DE021344715EULL, 0x31D4D1D8104D8B86ULL, 0xBBB2AF0CB2F46127ULL, 0xA969942D2362C4FAULL
};

const std::uint64_t LardExpander::kDomainSaltOrbiterC[S_SALT] = {
    0x03422943D80B97F1ULL, 0xFCDAB0B8F0A908CBULL, 0xC499504C2724FC8EULL, 0x1C0DE5EC0C66A15CULL,
    0x6EBF4EE7CEEA491CULL, 0xC7B0DAED85158D06ULL, 0xB4648B36C6A5380CULL, 0xF01CF6C77162BD9EULL,
    0xA5147F0758FBC420ULL, 0x50A43F0DF08B9B0BULL, 0xF6B140A3EFC08186ULL, 0xE6BD8ACB2B6E8272ULL,
    0xD10C44F6465CC285ULL, 0xA8FBEE8B2C627299ULL, 0x7B22B15C3E62183DULL, 0x84216E5367C162D3ULL,
    0x696BBD7CF359A2F8ULL, 0x422D339AA5589CF4ULL, 0xF47CDFC73D6FFF69ULL, 0x433A76CF81FC0441ULL,
    0x777FD2C8E79B98CFULL, 0x105EA961BA62DCF5ULL, 0x1677B9E55F20C5F0ULL, 0x39162D66EAC0B4A9ULL,
    0x8D92A102F2A41389ULL, 0x1BA8009277AE2D39ULL, 0x9B5EF36FD6954E6AULL, 0x2511C007F47E50A0ULL,
    0xF20C1053DEE7EEA7ULL, 0x643762B71610CA83ULL, 0x8D986FF7B6E16A51ULL, 0xEEC6DF6A0B78623CULL
};

const std::uint64_t LardExpander::kDomainSaltOrbiterD[S_SALT] = {
    0x7ECB56B0EF4B8A46ULL, 0x855B683F03294B5CULL, 0xAE52E40A1E3B6B3FULL, 0x6C9F75039AF647D5ULL,
    0x994385E38532DC80ULL, 0x46D1F0C019CA9960ULL, 0xA2DDCFDD111E0F7EULL, 0x2DE5A01B069BBD70ULL,
    0x893B4447976D86A7ULL, 0x9B281651077EF2A2ULL, 0xF707F65259F68669ULL, 0x7050BC0BC85260A6ULL,
    0xB2E61A94EDC651D6ULL, 0x5B8B522A2A5E042CULL, 0x963F5F38A1202326ULL, 0x2398C6083169DF8EULL,
    0xC41F498E1C42C1D4ULL, 0xAB342DD28014E4B8ULL, 0xC7C5D51BDE9946F4ULL, 0xD996C3C71FF74B88ULL,
    0x0A7687826D58FD91ULL, 0xCDC2531BEAAE6225ULL, 0x804D6FDE42D7B579ULL, 0xBA8B4B9A4A143E15ULL,
    0x367415DD128DB21EULL, 0x392363C42E899479ULL, 0xD0BBE24BD693A6E5ULL, 0x0159B30E5DE857EEULL,
    0xE24804A6CF204652ULL, 0x74F76D48BCC7EE9CULL, 0xCA6F6B83410E2856ULL, 0x2E33F4357CEE74F5ULL
};

const std::uint64_t LardExpander::kDomainSaltOrbiterE[S_SALT] = {
    0xB187E7A331E9791DULL, 0x9AF296F87E16973BULL, 0x1AB9240656C431D8ULL, 0xA162707000F2BD06ULL,
    0xA6E7287537E7381BULL, 0x6FFEE955FCE2AD7BULL, 0x34A9AB338B64927EULL, 0xCFF0779145B45BBBULL,
    0x4209174DDE1137C2ULL, 0xA4E4C803DF574C02ULL, 0xB65A13C70B1A3EFAULL, 0x4B100FEAD41053AEULL,
    0x7E9E531409155DD8ULL, 0x213DEB3C0A3415DFULL, 0x0D09FBD3F0072645ULL, 0xE7D75887C40295C0ULL,
    0xFB493C062182A178ULL, 0xB3C71B17A51DFDA3ULL, 0xD3CA9EDDA8017B2CULL, 0xD053087E0C68386FULL,
    0xC31BB1C9E0877276ULL, 0xC584B127A94B10E5ULL, 0x66B7FD485469DAACULL, 0x8C6FAE1B567D3FAFULL,
    0xE7B94403DFEF7FD8ULL, 0xC97711972CFACC99ULL, 0xEE005850AF0B64ADULL, 0x1C4FE2E5B0FF0F36ULL,
    0xF7B5DB6747FE16CEULL, 0x74BFBE9D794A2827ULL, 0x1E0611AF741E5FC6ULL, 0xC034621A4BDBEAA4ULL
};

const std::uint64_t LardExpander::kDomainSaltOrbiterF[S_SALT] = {
    0xDDA9CCB015FC3EA0ULL, 0x2AE3BAA0F3E365E9ULL, 0xE5BCCAFD746A2255ULL, 0xB9C0567DF1A03C5DULL,
    0x311D0E86BEE4F857ULL, 0xEC5629C0B18B8E11ULL, 0x738E810423FF204CULL, 0x639BBD4450A982A4ULL,
    0x1EF4DA35BE4684FDULL, 0x9FD9D447FE0C7236ULL, 0x430E62CFBFD426DFULL, 0xE34A99FEDACBB150ULL,
    0x4BCCA1B146382008ULL, 0x461409009313490BULL, 0x86BCC4441A0CFB41ULL, 0xDE724FAE6F1D2DE6ULL,
    0x690BBC6B0B10F95EULL, 0x56B81ADEAAD4A831ULL, 0x9F4F11DB473771C7ULL, 0x94EE5900F4F141F8ULL,
    0x6B7CA250CC713297ULL, 0x3AD53886FAE3D67FULL, 0x67D51EE85E0A380CULL, 0x398491093589290FULL,
    0x15611411FDBCA62AULL, 0x73A6E40CEC21807EULL, 0x0855B6E269D83644ULL, 0xF2D140FCE2D5B7D5ULL,
    0x5DD56C770DC3090AULL, 0xD3A045029C43B647ULL, 0x1AB7658E2C963357ULL, 0x5819171F7BA37953ULL
};

const std::uint64_t LardExpander::kDomainSaltPrismA[S_SALT] = {
    0x1F5C278B28A4D4A9ULL, 0xC510771D5F600584ULL, 0x36E3551AB038E3B8ULL, 0xDEA4162F259D3DDCULL,
    0xABD61E2F3FEADD03ULL, 0x956D6980ABACE36EULL, 0xFB767C06BF2FADA2ULL, 0x63AE845066E49062ULL,
    0x43EF09C225DA0C70ULL, 0xE53B403ED55E5736ULL, 0x646186F43174537FULL, 0xFC51F49B99F1AC84ULL,
    0xA96859B1A89E515DULL, 0x8532330D34EF8ED7ULL, 0xC336DD8C95792F6EULL, 0x855C52CE379E3C68ULL,
    0xE9B9B933DE8D6C44ULL, 0x3F3EDCAB7B9CB587ULL, 0x308EDD07648AEAF9ULL, 0x62A760D276781695ULL,
    0x11C9249C8E5BE707ULL, 0x54C3077358D7F19EULL, 0xA25E903100B02824ULL, 0xB09E79C51B9ADE8FULL,
    0xEF3353CD7DA00E48ULL, 0xAB5859E2641F56D6ULL, 0x7BF05C806B63A90AULL, 0xB9BB5045DDCE49E9ULL,
    0x72001CA34B6A7612ULL, 0x1C7892C73B1CBCB6ULL, 0x2077D5E540B2B311ULL, 0xA41FC4C6D99600B3ULL
};

const std::uint64_t LardExpander::kDomainSaltPrismB[S_SALT] = {
    0x16BC8A384DD3C1D4ULL, 0xCF5480328323A904ULL, 0x60D443FF1FA2C18BULL, 0xC2DE65A890C1B12AULL,
    0xF624F62C1726574CULL, 0x987D3814A22F1815ULL, 0xF1939CCC9ED1D3B4ULL, 0x236603DB8A403351ULL,
    0x4E1DFB11648B2A4FULL, 0xAE8449D500C17CB8ULL, 0x02A1534E0F9C2C97ULL, 0x24DE983B752F3F3CULL,
    0x92D9E97908F89A9DULL, 0xC8E788078420F17FULL, 0xBE05C5EC2AE7CBCBULL, 0x92F02A07874C3BDFULL,
    0x80FC59FA83FC7B2AULL, 0x7286854EB4BDC03AULL, 0x179AB2FADBE10DA4ULL, 0x857BF2CA25268F50ULL,
    0xA371E01C2EE9C7D2ULL, 0x145513F2CACD8EEBULL, 0x5EC74EC1978DC949ULL, 0x152618692C5C8DB5ULL,
    0x990EEFF215A2057DULL, 0xE0CBB95DBE9AC896ULL, 0xAB0BD9D912178028ULL, 0xF970B33D5EED5C43ULL,
    0x39C4D97500D6B096ULL, 0x2BCA1DBD01D1EEADULL, 0x9B64DA8948475260ULL, 0xDAE5807231BE73EBULL
};

const std::uint64_t LardExpander::kDomainSaltPrismC[S_SALT] = {
    0x6E7447283403BB9CULL, 0x79F0155A9A5BBBFEULL, 0x153A035C9DCD8084ULL, 0xA884364C791309D1ULL,
    0x7C39028D44D3202BULL, 0xC2C8BDF8A75A4121ULL, 0x8E6443C5F57337B5ULL, 0x5BF323A25FC32F1AULL,
    0x7C4659BDB54B9635ULL, 0x04591289B77FBADCULL, 0x8EA86D7790B479C8ULL, 0x1A3683BA9893EF28ULL,
    0x368D9319627313BCULL, 0x5CF0A32648DAD862ULL, 0x316085B0AEEBF42EULL, 0xD10686467DA73270ULL,
    0x3AF9F23D60BE9799ULL, 0xE18CF8E4FE2C8B40ULL, 0x3183F32498E51117ULL, 0xBA089D706D159469ULL,
    0xBE54D2350D4041DEULL, 0x6200B5E55E842F92ULL, 0x3203214D0937F7E0ULL, 0x398B2629B669F9E8ULL,
    0x84CAC372BDD9DABBULL, 0x28DA9E1BFFBC169BULL, 0x3E29D6D3307B5D9DULL, 0x2960814A28550158ULL,
    0x26C16F85955428B2ULL, 0xF81CA4D39A4E33DAULL, 0xC6D00488E76EC229ULL, 0x7CF6A55C2255A38FULL
};

const std::uint64_t LardExpander::kDomainSaltPrismD[S_SALT] = {
    0x62A7AF1017D874A0ULL, 0x80787F9546120A4CULL, 0xD09E71CDAE80616EULL, 0x553664A25D359D9DULL,
    0xBFFA640B54D21079ULL, 0xAC274236C8060E9CULL, 0x8A03A98DD9C74CC1ULL, 0x7587A89728EC3C4BULL,
    0xC3C66795B2BF58FFULL, 0x3442452BEFB8E2F3ULL, 0x31A25A5E40E7823EULL, 0xF7BB6CA93306760DULL,
    0x291224A47534C945ULL, 0xFBE901FFF25896C7ULL, 0x09D73C14CB41AC1DULL, 0xA6FE7F6C0580AABBULL,
    0x5C55958DA88C3CCAULL, 0x57373FAD06C2E092ULL, 0xE62DC16FFD85BBE9ULL, 0xB9B2D2E962799D98ULL,
    0x020ABB00D1047571ULL, 0x2042E164D0F83A8FULL, 0x60A2F5B35E9FE4E5ULL, 0xF310CE08A6E12DB1ULL,
    0x76133136BF2E9F82ULL, 0xD9FF75D8FBA47938ULL, 0xA16F9A59A413365FULL, 0x92C0A861440F9502ULL,
    0x59C19C8063C91A76ULL, 0x6FA9813622E8D42AULL, 0x173A8B6B1857B879ULL, 0xAA810F7AB7211A54ULL
};

const std::uint64_t LardExpander::kDomainSaltPrismE[S_SALT] = {
    0x409F83F93BE7FD4DULL, 0x91E484F6FA8E26A0ULL, 0x0E319ABFF51493A3ULL, 0x90F7119026598369ULL,
    0x58CD18C26B4A4D12ULL, 0x52AC255943E978D1ULL, 0xFCB54E754B59F926ULL, 0x8D20B0316EF02CB8ULL,
    0x60E47C42E6E130B8ULL, 0x63D2C704A0CA69F4ULL, 0x0496CB96B0C98EB4ULL, 0xCD5E2CEE909268FDULL,
    0x49D73D0822BE5694ULL, 0xB12B708F6F0A4E81ULL, 0x6DCB5DC3F823A516ULL, 0x87F1263DC156B0B9ULL,
    0x3714756209349AF6ULL, 0xDC500CF3DCECF298ULL, 0xD45EE56C5699B3F5ULL, 0x2A95C7366C20C287ULL,
    0x0015893B0AFBBC0BULL, 0x668E224F801EC712ULL, 0xF7895FFEF78DA95EULL, 0x8B7DE7F3729B783BULL,
    0x5385327548AC7828ULL, 0x3543B54F6AE5837DULL, 0xC1EEDFC273183308ULL, 0x2F294DE599141E3EULL,
    0x5E1DFF189A5B7272ULL, 0x37561C87BB474F23ULL, 0xE6F2318FA0795F2DULL, 0xE9E9D6BE20E73608ULL
};

const std::uint64_t LardExpander::kDomainSaltPrismF[S_SALT] = {
    0xD99ED125652145E9ULL, 0x4818DAB6B1CE0039ULL, 0x89D2F1A3D75CBAA7ULL, 0xBC58252590AC4F5BULL,
    0xA73666900FB247A6ULL, 0xC806230814FB6CD9ULL, 0x2D5A103A0D8EA415ULL, 0x2443145B57778425ULL,
    0xE3ECBFE0F31A0999ULL, 0x43DEB5AEFF319333ULL, 0xA93544D92880E356ULL, 0xC790E84A98396C68ULL,
    0x72431DA8097C3F0AULL, 0xDF4105F8C7004273ULL, 0xAD1F0F57EE679484ULL, 0x781B9884C4D1B0C5ULL,
    0xEB5D0F7329078202ULL, 0xB6ED2205E342F158ULL, 0x59C40A682D39A97BULL, 0x2D823BF9A1F8DD8AULL,
    0x807DBAC4E7862329ULL, 0xD765C1613728E7B1ULL, 0x15894ED3FC7E03B7ULL, 0xD49EA8ACE1184C62ULL,
    0xEE0AFB9ABAA162B8ULL, 0x147C0CDAC5E6B780ULL, 0x7F98D2E2CA12123CULL, 0x05F08FC47086C2DEULL,
    0xC485D23E49E296F9ULL, 0xB240BCF38DAF1C6BULL, 0x11E7374107AB0A0AULL, 0x78383EF4282B0E63ULL
};

const std::uint64_t LardExpander::kDomainSaltSourceA[S_SALT] = {
    0xF69527E0A5794791ULL, 0x4B4C4B2EEE2CB403ULL, 0x3BC08999C955D639ULL, 0xDA4263D65D288361ULL,
    0x1F70522033BAA7B0ULL, 0xB84C66EB6D7E493CULL, 0xB59C3971DF21340BULL, 0xEDCC84DCF83CFC7CULL,
    0xD2FFCA4E1A1FB36DULL, 0x3E68DBA00871E730ULL, 0x63D0B75560327FE3ULL, 0x86CD088F1DF850CFULL,
    0x1AEFF4D40A12755FULL, 0x7C1F0DE7505DE41FULL, 0xD65E574545DF80D1ULL, 0xD6DAF3338939D5B0ULL,
    0x23886468B64C4858ULL, 0x6D36D9727707C92FULL, 0xF233FB74B2EB5B52ULL, 0x5E77273DF88F82ABULL,
    0xB5A5B83D586A7F3BULL, 0x206CBC09BC9492B1ULL, 0xC179B5C0490EAE83ULL, 0x306288C508B67E4DULL,
    0xB3AFDC62700AEDF1ULL, 0xF4BE73BC4F9A1E24ULL, 0x8B24A7535A93EADFULL, 0xF57A3F03BBE0A23EULL,
    0xF4DB34D456A8591DULL, 0x9083B5A6E7743BD7ULL, 0x317F1C63B2FADC18ULL, 0x0FAE067C5887BBC7ULL
};

const std::uint64_t LardExpander::kDomainSaltSourceB[S_SALT] = {
    0x2910987C888A5135ULL, 0x262385AEB201265BULL, 0xBB04A6D7AA403D3DULL, 0x1B6417CDB1D96858ULL,
    0x91C2A014D98A3078ULL, 0x4EDF738B1BFF474CULL, 0xDADBE757408C620DULL, 0xEC5C744A7D322B5EULL,
    0xA8A636DB4BE75C2DULL, 0xAA751039A7E13E86ULL, 0x5F05FBED0A9E1EC4ULL, 0x87E41B2FCF877C4DULL,
    0x371F7528A6B26DFFULL, 0xC4BFBD5B7C8827BFULL, 0x0185532C3D92A9EBULL, 0x1D9E04BC0FE0B3B2ULL,
    0x8D49456E131BC37AULL, 0x02F0FC74E476BE02ULL, 0x8AA6F57C7560A6F8ULL, 0x9AA3101DDB2485B9ULL,
    0x56E38CAB3770111FULL, 0x589C2033059B5BE8ULL, 0x1A3690BD955D8DF7ULL, 0x280C4B42571F1E3FULL,
    0xAC2CC4B0D4C5BAC6ULL, 0x89C4FE77A3BECF3FULL, 0xB4046BA287E903B5ULL, 0xF9A27BBE176AFE4AULL,
    0x54D85B9E67573522ULL, 0x5C39C2D520B33C1EULL, 0x0E6E80C21D80F3AFULL, 0x18CCF4073832E2B1ULL
};

const std::uint64_t LardExpander::kDomainSaltSourceC[S_SALT] = {
    0xDCDE12144EDF88C4ULL, 0x25426F1723D04596ULL, 0xDBA1A3389413137EULL, 0xC73824041BFF123CULL,
    0x9C9954EF6B92766BULL, 0x35DF23D14DF721F9ULL, 0x9ABBBD2D8F732FBFULL, 0x58AE679F47523D66ULL,
    0xE88E29B45141C9EBULL, 0x134E129AE15B0204ULL, 0x2D57596909EBF3ADULL, 0xBA37511B7B75596DULL,
    0x65273B6B5138353BULL, 0xD8C9FF6D864596DBULL, 0x433BE4D85A248572ULL, 0x6230245C467BE897ULL,
    0x440DAA4AF6CE3934ULL, 0xBB2E32706300C3E0ULL, 0xE14D25EE4D1DE67EULL, 0x2D85F13A620C082BULL,
    0x66EECADC6AF523FBULL, 0x5A0C454D0E72146FULL, 0x4275A949C4AEC432ULL, 0x18EE070F47217ADDULL,
    0xA2E639030CC69FC2ULL, 0x02F9D3FF4A10DF38ULL, 0x7ED71719A8FBFF6EULL, 0x0F843A2DB045D8C5ULL,
    0xED16890CE3313237ULL, 0xEF1DD612AFB9E7B0ULL, 0xF6C066778D4E03E2ULL, 0x93E27D5DC3BA66F9ULL
};

const std::uint64_t LardExpander::kDomainSaltSourceD[S_SALT] = {
    0x4714A9BC57DDFDF0ULL, 0x695B8E150D1D4F2FULL, 0x864E723CA96CBDD0ULL, 0x9BF7A8D748F24FA9ULL,
    0xD7679221F26B3B04ULL, 0xF227E8FCD8B068E5ULL, 0x9299E4C9D8367EBAULL, 0x99E630CA463178D9ULL,
    0x75676D26EC249D46ULL, 0xCE272A1FF5E6468BULL, 0xDF157348A559A136ULL, 0x8A7F040CCBAE6ECDULL,
    0xF5B532FBB7744841ULL, 0x8C60205AA58C0F2BULL, 0xF8FB52FB5F10D3D4ULL, 0x2EFC4D59A38E9817ULL,
    0x1E1DA827F62DE5C7ULL, 0xF4BD70FE7D558914ULL, 0x3D5F4C963B5411C6ULL, 0x9CBCCAF9CB06C1D3ULL,
    0x2832D45E6954449BULL, 0x86EA46A00ACF2158ULL, 0x01B957EB4485376BULL, 0xE4569CAC937A724CULL,
    0x5EB8433DE6E49DB7ULL, 0x9A2311A7EA650A87ULL, 0xE81B83B64D65D19BULL, 0xBA333D8727EFBF53ULL,
    0x79590F631A1BA977ULL, 0x189D1220B877318EULL, 0xF509E5A66307BCCEULL, 0x2D33ECE43516439DULL
};

const std::uint64_t LardExpander::kDomainSaltSourceE[S_SALT] = {
    0x4D22262A5DA1AD59ULL, 0x36970CB384E2F651ULL, 0x022EED5D6D4C4BF3ULL, 0x4A047A959BBCF2B1ULL,
    0x51A7AEB42EA476DCULL, 0x8C42496B814348DDULL, 0x65350EDC2CC658A7ULL, 0xCE5BD3D6D5CA7E9AULL,
    0xD07CCA5EC7238A36ULL, 0xD9B4C0F72D97E91FULL, 0xBDCD9E37F16074A6ULL, 0x20865195DAD69AC4ULL,
    0x725ED37DFBC876B9ULL, 0xC20A8ECF519A0BAEULL, 0x25154CDC3FA4CFDCULL, 0x20147988D92A093BULL,
    0x8F5CE285E683D2F2ULL, 0x1E7873101563A017ULL, 0x6C69B8AE45B87A2BULL, 0xD668DDDA83B79A58ULL,
    0xB11395690F199203ULL, 0x9CC5E837C525A02FULL, 0x4FB830E4CBE704CCULL, 0x13297955D147FE52ULL,
    0x7FD37781B4141EE8ULL, 0x72C70FED52893C0CULL, 0xBC1C7E5C48A9133FULL, 0x1F6A9BEA04DC4F48ULL,
    0xD7719B4FC8C37217ULL, 0x87F4372B736A6CB6ULL, 0x3EC76E2EA51EA9CEULL, 0xC70E6A24A0645A2FULL
};

const std::uint64_t LardExpander::kDomainSaltSourceF[S_SALT] = {
    0x97B1F471EEF12116ULL, 0x82B1ED54ED0F9D45ULL, 0xD65C46AC89CFF57AULL, 0xB0A9A647505FE9B0ULL,
    0x6454C7E4C7C4517EULL, 0x26067C4995EDED5DULL, 0xFFB90922920A703CULL, 0x93A1AA01309D9624ULL,
    0x5645E3CEED5C7A2AULL, 0xC8224167ACA254FFULL, 0x4A875739C3D7B69EULL, 0x0EEEEBE66CF40E89ULL,
    0x52622FF6C0D0CCF5ULL, 0xC625572AE80AEBA7ULL, 0xC81CA7B3624629B6ULL, 0x30A9D6E5A5C92332ULL,
    0x0B18428187F9D314ULL, 0xC9D61CBA1AAE72ACULL, 0x032132196364376BULL, 0xC5C46512948A9795ULL,
    0x5B71F3E139195210ULL, 0xF958E3614A828E30ULL, 0x096F5DD6D106C6EDULL, 0x8696E9D7D627925AULL,
    0x47849D23EE76178AULL, 0x870E50068AB3FEA1ULL, 0xD16D1917EB412E4FULL, 0xC71E69CA02FF0852ULL,
    0xE3A4261BCB921F2AULL, 0xF288DFCED3DCB9D9ULL, 0xE8B5930FE73C3227ULL, 0x397B20338B3FB30AULL
};
