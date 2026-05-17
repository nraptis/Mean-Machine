#include "TwistExpander_Gollum.hpp"
#include "TwistFunctional.hpp"
#include "TwistMasking.hpp"
#include "TwistMix64.hpp"
#include "TwistSnow.hpp"
#include "TwistMemory.hpp"
#include "TwistCryptoGenerator.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmSalt.hpp"

#include <cstring>

TwistExpander_Gollum::TwistExpander_Gollum()
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
}

void TwistExpander_Gollum::Seed(TwistWorkSpace *pWorkspace,
                                 TwistCryptoGenerator *pCryptoGenerator,
                                 TwistFarmSBox *pFarmSBox,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint8_t *pSource,
                                 std::uint8_t *pPassword,
                                 unsigned int pPasswordByteLength) {
    TwistExpander::Seed(pWorkspace, pCryptoGenerator, pFarmSBox, pFarmSalt, pSource, pPassword, pPasswordByteLength);
    if ((pWorkspace == nullptr) || (pCryptoGenerator == nullptr) || (pFarmSBox == nullptr) || (pFarmSalt == nullptr)) { return; }
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
    std::uint64_t aReloop = 0;
    std::uint64_t aPrevious = 0;
    std::uint64_t aCurrent = 0;
    std::uint64_t aCross = 0;
    std::uint64_t aScatter = 0;
    std::uint64_t aOrbitB = 0;
    std::uint64_t aWandererD = 0;
    std::uint64_t aOrbitD = 0;
    std::uint64_t aOrbitA = 0;
    std::uint64_t aOrbitC = 0;
    std::uint64_t aWandererA = 0;
    std::uint64_t aWandererC = 0;
    std::uint64_t aCarry = 0;
    std::uint64_t aPrism = 0;
    std::uint64_t aWandererB = 0;
    std::uint64_t aWalker = 0;
    std::uint64_t aArgA = 0;
    std::uint64_t aArgB = 0;
    std::uint64_t aKindA = 0;
    std::uint64_t aKindB = 0;

    // Reset farm state for this seed pass.
    pFarmSBox->Reset();
    pFarmSalt->Reset();
    // Making snow counter: aes 256
    TwistSnow::AES256Counter(pSource, aExpandLaneA);
    // Initialize worker lane for this pass.
    TwistMemory::Copy(aWorkLaneA, pSource, 8192U);
    aReloop = 1U;
    while (aReloop != 0) {
        for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
            aPrevious = aCurrent;
            aCurrent = aWorkLaneA[aIndex] ^ ShiftL64(aExpandLaneA[S_BLOCK1 - aIndex], 32U);
            aCross = aWorkLaneA[S_BLOCK1 - aIndex];
            // __START_CSPRNG
            aScatter = TwistMix64::DiffuseA(aCurrent ^ ShiftL64(aCross, 32U) ^ RotL64(aPrevious, 13U));
            aOrbitB = aWandererD + RotL64(aCurrent, 27U) + 14084573094707411164ULL + mSaltD[((aOrbitD + RotL64(aOrbitA, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = aWandererA ^ RotL64(aPrevious, 37U) ^ 11998092425188837914ULL ^ mSaltA[((RotL64(aCross, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = aWandererC + RotL64(aCross, 51U) + mSaltH[((aIndex + 14U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltC[((31U - aIndex + 4U) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aCarry, 45U) ^ RotL64(aCurrent, 11U) ^ mSaltH[((31U - aIndex + 17U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltB[((aIndex + 15U) & static_cast<std::uint64_t>(S_SALT1))];
            aPrism = aCurrent;
            aOrbitB = aOrbitB + aOrbitC + 9446146461917371001ULL + mSaltG[((RotL64(aWandererA, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitB ^ 2436634976323244521ULL ^ mSaltB[((RotL64(aScatter, 13U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD * 858231167973157581ULL, 35U);
            aPrism = (aPrism ^ (RotL64(aOrbitA, 43U) + mSaltB[((aWandererD + RotL64(aCarry, 27U)) & static_cast<std::uint64_t>(S_SALT1))]) ^ 400160012451876105ULL) * 13111053245761316747ULL;
            aOrbitA = aOrbitA + aOrbitD + 14746306801475654464ULL + mSaltC[((RotL64(aOrbitB, 21U) ^ aScatter) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = aOrbitC ^ aOrbitA ^ 6141991388400820570ULL ^ mSaltH[((RotL64(aOrbitD, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = RotL64(aOrbitC, 11U);
            aPrism = (aPrism + (RotL64(aPrevious, 29U) ^ RotL64(aCross, 3U) ^ mSaltG[((RotL64(aWandererC, 13U) + aPrevious) & static_cast<std::uint64_t>(S_SALT1))]) + 15157286770213647983ULL) * 4831709003335146725ULL;
            aOrbitB = aOrbitB + aOrbitC + 17962197713055811155ULL + mSaltH[((aCross ^ RotL64(aOrbitC, 27U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitB ^ 10822226552713854908ULL ^ mSaltG[((RotL64(aOrbitA, 21U) ^ aWandererA) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD * 16097986033423648211ULL, 53U);
            aPrism = (aPrism ^ (RotL64(aOrbitC, 51U) + aWandererD) ^ 15497556631046481162ULL) * 7179932469301202219ULL;
            aOrbitA = aOrbitA + aOrbitD + 3411681759945001263ULL + mSaltB[((aOrbitB + RotL64(aScatter, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = aOrbitC ^ aOrbitA ^ 12380230130222911915ULL ^ mSaltC[((RotL64(aScatter, 11U) + aCarry) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = RotL64(aOrbitC * 889013264706150319ULL, 45U);
            aPrism = (aPrism + (RotL64(aOrbitD, 1U) ^ RotL64(aCarry, 29U)) + 10497461372169751719ULL) * 12269539857655536619ULL;
            aCurrent = (RotL64(aOrbitB, 13U) ^ aOrbitC) + (RotL64(aOrbitA, 27U) ^ aOrbitD);
            aCurrent = TwistMix64::DiffuseA(aCurrent + aScatter);
            aExpandLaneB[aIndex] = aCurrent;
            aPrism = TwistMix64::DiffuseB(aPrism);
            switch (aPrism % 3U) {
            	case 0U: {
            		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 5ULL, mSBoxE, mSBoxA, mSBoxG, mSBoxH, mSBoxD, mSBoxF, mSBoxB, mSBoxC);
            		break;
            	}
            	case 1U: {
            		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, mSBoxD, mSBoxH, mSBoxC, mSBoxE, mSBoxB, mSBoxG, mSBoxF, mSBoxA);
            		break;
            	}
            	case 2U: {
            		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 7ULL, mSBoxG, mSBoxE, mSBoxB, mSBoxH, mSBoxF, mSBoxA, mSBoxC, mSBoxD);
            		break;
            	}
            }
            aWandererD = aWandererD + (aCurrent ^ RotL64(aPrevious, 11U) ^ aOrbitD);
            aWandererD = RotL64((aWandererD + mSaltH[((aIndex + 20U) & static_cast<std::uint64_t>(S_SALT1))]) * 17816531704553483557ULL, 35U);
            aWandererA = aWandererA ^ (aCurrent + RotL64(aCross, 37U) + aOrbitB);
            aWandererA = RotL64((aWandererA ^ mSaltG[((aIndex + 20U) & static_cast<std::uint64_t>(S_SALT1))]) * 6945486613706339303ULL, 43U);
            aWandererC = aWandererC + (aOrbitC ^ RotL64(aOrbitA, 19U) ^ mSaltC[((aIndex + 8U) & static_cast<std::uint64_t>(S_SALT1))]);
            aWandererC = RotL64(aWandererC * 3146837208238096023ULL, 13U);
            aCarry = aCarry + (aWandererD ^ aWandererA ^ aWandererC ^ RotL64(aCurrent, 3U));
            aCarry = RotL64(aCarry * 11997943534441521277ULL, 51U);
            aCarry = aCarry ^ ShiftR64(aCarry, 29U);
            // __END_CSPRNG
        }
        aReloop = pFarmSBox->TillBytes(aExpandLaneB, aExpandLaneA, 16ULL) ? 0ULL : 1ULL;
        for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
            aPrevious = aCurrent;
            aCurrent = aExpandLaneB[aIndex] ^ ShiftL64(aExpandLaneA[aIndex], 32U);
            aCross = aWorkLaneA[aIndex];
            // __START_CSPRNG
            aScatter = TwistMix64::DiffuseA(ShiftL64(aCurrent, 32U) ^ aCross ^ RotL64(aPrevious, 13U));
            aOrbitC = aWandererB + RotL64(aCurrent, 27U) + 12700750867941402889ULL + mSaltE[((RotL64(aOrbitA, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aWandererC ^ RotL64(aPrevious, 29U) ^ 15030797346540340471ULL ^ mSaltF[((aScatter ^ RotL64(aCross, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = aWandererD + RotL64(aCross, 11U) + mSaltB[((31U - aIndex + 15U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltG[((aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aCarry, 37U) ^ RotL64(aCurrent, 1U) ^ mSaltG[((31U - aIndex + 31U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltH[((aIndex + 21U) & static_cast<std::uint64_t>(S_SALT1))];
            aPrism = aCurrent;
            aOrbitC = aOrbitC + aOrbitB + 14084573094707411164ULL + mSaltC[((RotL64(aWandererD, 13U) ^ aWandererC) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitC ^ 11998092425188837914ULL ^ mSaltB[((aOrbitD ^ RotL64(aOrbitB, 27U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD * 4665533052640681397ULL, 21U);
            aPrism = (aPrism + aOrbitA + RotL64(aCarry, 35U) + 9446146461917371001ULL) * 10213158099001462037ULL;
            aOrbitA = aOrbitA + aOrbitD + 2436634976323244521ULL + mSaltG[((RotL64(aWandererB, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitA ^ 400160012451876105ULL ^ mSaltB[((RotL64(aCarry, 19U) ^ aOrbitC) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB, 11U);
            aPrism = (aPrism ^ (RotL64(aPrevious, 51U) + mSaltH[((aScatter ^ RotL64(aOrbitA, 13U)) & static_cast<std::uint64_t>(S_SALT1))]) ^ mSaltC[((aCross ^ RotL64(aPrevious, 27U)) & static_cast<std::uint64_t>(S_SALT1))] ^ 14746306801475654464ULL) * 1654934424986155677ULL;
            aOrbitC = aOrbitC + aOrbitB + 6141991388400820570ULL + mSaltH[((RotL64(aScatter, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitC ^ 15157286770213647983ULL ^ mSaltC[((RotL64(aOrbitD, 29U) ^ aOrbitB) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD * 4831709003335146725ULL, 53U);
            aPrism = (aPrism + (aOrbitB ^ RotL64(aWandererB, 45U)) + 17962197713055811155ULL) * 17180159925948402441ULL;
            aOrbitA = aOrbitA + aOrbitD + 10822226552713854908ULL + mSaltG[((RotL64(aWandererC, 19U) ^ aWandererD) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitA ^ 15497556631046481162ULL ^ mSaltB[((aWandererB + RotL64(aScatter, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB * 7179932469301202219ULL, 43U);
            aPrism = (aPrism ^ (RotL64(aOrbitD, 13U) + RotL64(aCross, 37U)) ^ 3411681759945001263ULL) * 9516248637769029335ULL;
            aCurrent = (RotL64(aOrbitC, 27U) ^ aOrbitB) + (RotL64(aOrbitA, 21U) ^ aOrbitD);
            aCurrent = TwistMix64::DiffuseC(aCurrent + aScatter);
            aWorkLaneA[aIndex] = aCurrent;
            aPrism = TwistMix64::DiffuseB(aPrism);
            switch (aPrism % 4U) {
            	case 0U: {
            		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 35ULL, mSBoxG, mSBoxH, mSBoxC, mSBoxB, mSBoxE, mSBoxF, mSBoxA, mSBoxD);
            		break;
            	}
            	case 1U: {
            		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 29ULL, mSBoxH, mSBoxD, mSBoxG, mSBoxF, mSBoxA, mSBoxE, mSBoxB, mSBoxC);
            		break;
            	}
            	case 2U: {
            		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, mSBoxD, mSBoxE, mSBoxA, mSBoxG, mSBoxH, mSBoxC, mSBoxB, mSBoxF);
            		break;
            	}
            	case 3U: {
            		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 5ULL, mSBoxA, mSBoxG, mSBoxB, mSBoxF, mSBoxE, mSBoxH, mSBoxC, mSBoxD);
            		break;
            	}
            }
            aWandererB = aWandererB + (aCurrent ^ aPrevious ^ RotL64(aOrbitD, 35U));
            aWandererB = RotL64((aWandererB + mSaltB[((aIndex + 7U) & static_cast<std::uint64_t>(S_SALT1))]) * 889013264706150319ULL, 19U);
            aWandererC = aWandererC ^ (aCurrent + aCross + RotL64(aOrbitC, 51U));
            aWandererC = RotL64((aWandererC ^ mSaltH[((31U - aIndex + 29U) & static_cast<std::uint64_t>(S_SALT1))]) * 12269539857655536619ULL, 53U);
            aWandererD = aWandererD + (RotL64(aOrbitB, 45U) ^ aOrbitA ^ mSaltC[((aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))]);
            aWandererD = RotL64(aWandererD * 17816531704553483557ULL, 43U);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererC, 1U) ^ aWandererD ^ aCurrent);
            aCarry = RotL64(aCarry * 6945486613706339303ULL, 37U);
            aCarry = aCarry ^ ShiftR64(aCarry, 43U);
            // __END_CSPRNG
        }
        aReloop = pFarmSalt->TillBytes(aWorkLaneA, aExpandLaneA, 16ULL) ? aReloop : 1ULL;
    }
    // Secure zero on snow + scratch expansion lanes.
    TwistMemory::ZeroBlock(aExpandLaneA);
    TwistMemory::ZeroBlock(aExpandLaneB);
    // Making snow counter: sha 256
    TwistSnow::Sha256Counter(pSource, aExpandLaneB);
    // Initialize worker lane for this pass.
    TwistMemory::Copy(aWorkLaneB, aWorkLaneA, 8192U);
    aReloop = 1U;
    while (aReloop != 0) {
        for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
            aPrevious = aCurrent;
            aCurrent = aWorkLaneB[aIndex] ^ ShiftL64(aExpandLaneB[aIndex], 32U);
            aCross = aWorkLaneB[S_BLOCK1 - aIndex];
            // __START_CSPRNG
            aScatter = TwistMix64::DiffuseA(aCurrent ^ ShiftL64(aCross, 32U) ^ RotL64(aPrevious, 11U));
            aOrbitA = aWandererD + RotL64(aCurrent, 1U) + 8180012735795991620ULL + mSaltA[((aOrbitD + RotL64(aScatter, 13U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aWandererC ^ RotL64(aPrevious, 21U) ^ 4487632548363940723ULL ^ mSaltH[((RotL64(aPrevious, 27U) ^ aWandererA) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aWandererA + RotL64(aCross, 37U) + mSaltE[((aIndex + 6U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltC[((31U - aIndex + 13U) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = RotL64(aCarry, 7U) ^ RotL64(aCurrent, 29U) ^ mSaltF[((aIndex + 25U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltD[((31U - aIndex + 11U) & static_cast<std::uint64_t>(S_SALT1))];
            aPrism = aCurrent;
            aOrbitA = aOrbitA + aOrbitD + 4793355477246298217ULL + mSaltD[((RotL64(aOrbitA, 19U) ^ aCross) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = aOrbitC ^ aOrbitA ^ 11825404724233465862ULL ^ mSaltE[((aWandererC + RotL64(aOrbitB, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = RotL64(aOrbitC * 6055487080818625621ULL, 35U);
            aPrism = (aPrism ^ ((RotL64(aOrbitB, 3U) ^ mSaltF[((RotL64(aScatter, 13U) ^ aWandererD) & static_cast<std::uint64_t>(S_SALT1))]) + mSaltD[((RotL64(aCarry, 21U)) & static_cast<std::uint64_t>(S_SALT1))]) ^ 14567887748880294370ULL) * 1103821198506817233ULL;
            aOrbitB = aOrbitB + aOrbitC + 11739815016060312177ULL + mSaltC[((RotL64(aScatter, 27U) + aPrevious) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitB ^ 6130115005348103676ULL ^ mSaltF[((aOrbitA + RotL64(aOrbitC, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD, 43U);
            aPrism = (aPrism + (RotL64(aPrevious, 53U) ^ RotL64(aCarry, 45U)) + 15237821000276351604ULL) * 5721561496560966777ULL;
            aOrbitA = aOrbitA + aOrbitD + 7009993126737152515ULL + mSaltE[((RotL64(aCross, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = aOrbitC ^ aOrbitA ^ 13468685917767566488ULL ^ mSaltD[((RotL64(aOrbitB, 11U) + aWandererC) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = RotL64(aOrbitC * 3031109925569525585ULL, 51U);
            aPrism = (aPrism ^ RotL64(aOrbitD, 13U) ^ RotL64(aWandererD, 21U) ^ 10451634458242703838ULL) * 12324623690072122945ULL;
            aOrbitB = aOrbitB + aOrbitC + 7455700557403774923ULL + mSaltF[((RotL64(aOrbitD, 27U) ^ aWandererD) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitB ^ 15597398830011408849ULL ^ mSaltC[((aScatter + RotL64(aWandererA, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD * 8066836458459940135ULL, 5U);
            aPrism = (aPrism + RotL64(aOrbitC, 29U) + RotL64(aCross, 1U) + 10676085577108177914ULL) * 2844432091392960027ULL;
            aCurrent = (aOrbitA ^ RotL64(aOrbitC, 11U)) + (RotL64(aOrbitD, 21U) ^ aOrbitB);
            aCurrent = TwistMix64::DiffuseB(aCurrent ^ aScatter);
            aExpandLaneC[aIndex] = aCurrent;
            aPrism = TwistMix64::DiffuseC(aPrism);
            switch (aPrism % 2U) {
            	case 0U: {
            		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, mSBoxC, mSBoxB, mSBoxA, mSBoxD, mSBoxF, mSBoxG, mSBoxH, mSBoxE);
            		break;
            	}
            	case 1U: {
            		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 3ULL, mSBoxC, mSBoxD, mSBoxF, mSBoxH, mSBoxG, mSBoxE, mSBoxB, mSBoxA);
            		break;
            	}
            }
            aWandererD = aWandererD + (aCurrent ^ RotL64(aPrevious, 5U) ^ aOrbitC);
            aWandererD = RotL64((aWandererD + mSaltE[((31U - aIndex + 15U) & static_cast<std::uint64_t>(S_SALT1))]) * 13273130330270357309ULL, 27U);
            aWandererC = aWandererC ^ (aCurrent + aCross + RotL64(aOrbitA, 19U));
            aWandererC = RotL64((aWandererC ^ mSaltE[((31U - aIndex + 15U) & static_cast<std::uint64_t>(S_SALT1))]) * 17024492006014096099ULL, 13U);
            aWandererA = aWandererA + (RotL64(aOrbitD, 45U) ^ aOrbitB ^ mSaltD[((31U - aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))]);
            aWandererA = RotL64(aWandererA * 12545261339544312959ULL, 29U);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererC, 11U) ^ aWandererA ^ aCurrent);
            aCarry = RotL64(aCarry * 17420819641258581859ULL, 21U);
            aCarry = aCarry ^ ShiftR64(aCarry, 37U);
            // __END_CSPRNG
        }
        aReloop = pFarmSBox->TillBytes(aExpandLaneC, aExpandLaneB, 32ULL) ? 0ULL : 1ULL;
        for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
            aPrevious = aCurrent;
            aCurrent = aExpandLaneC[aIndex] ^ ShiftL64(aExpandLaneB[S_BLOCK1 - aIndex], 32U);
            aCross = aWorkLaneB[aIndex];
            // __START_CSPRNG
            aScatter = TwistMix64::DiffuseA(ShiftL64(aCurrent, 32U) ^ aCross ^ RotL64(aPrevious, 29U));
            aOrbitC = aWandererB + RotL64(aCurrent, 21U) + 8180012735795991620ULL + mSaltB[((RotL64(aWandererD, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aWandererD ^ RotL64(aPrevious, 43U) ^ 4487632548363940723ULL ^ mSaltG[((aOrbitD + RotL64(aScatter, 13U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aWandererC + RotL64(aCross, 45U) + mSaltE[((31U - aIndex + 14U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltC[((aIndex + 7U) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = RotL64(aCarry, 37U) ^ RotL64(aCurrent, 1U) ^ mSaltC[((aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltF[((31U - aIndex + 5U) & static_cast<std::uint64_t>(S_SALT1))];
            aPrism = aCurrent;
            aOrbitC = aOrbitC + aOrbitD + 4793355477246298217ULL + mSaltD[((RotL64(aOrbitB, 27U) ^ aCross) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = aOrbitA ^ aOrbitC ^ 11825404724233465862ULL ^ mSaltE[((aWandererC ^ RotL64(aPrevious, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = RotL64(aOrbitA * 6055487080818625621ULL, 35U);
            aPrism = (aPrism + RotL64(aOrbitB, 53U) + mSaltF[((RotL64(aOrbitC, 29U)) & static_cast<std::uint64_t>(S_SALT1))] + 14567887748880294370ULL) * 1103821198506817233ULL;
            aOrbitB = aOrbitB + aOrbitA + 11739815016060312177ULL + mSaltD[((RotL64(aWandererB, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitB ^ 6130115005348103676ULL ^ mSaltC[((RotL64(aCarry, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD, 51U);
            aPrism = (aPrism ^ (RotL64(aCross, 3U) + RotL64(aPrevious, 13U)) ^ 15237821000276351604ULL) * 5721561496560966777ULL;
            aOrbitC = aOrbitC + aOrbitD + 7009993126737152515ULL + mSaltF[((RotL64(aWandererD, 27U) ^ aOrbitA) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = aOrbitA ^ aOrbitC ^ 13468685917767566488ULL ^ mSaltF[((RotL64(aScatter, 19U) + aOrbitD) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = RotL64(aOrbitA * 3031109925569525585ULL, 45U);
            aPrism = (aPrism + (aOrbitD ^ RotL64(aWandererB, 43U) ^ mSaltD[((aOrbitB ^ RotL64(aCross, 29U)) & static_cast<std::uint64_t>(S_SALT1))]) + 10451634458242703838ULL) * 12324623690072122945ULL;
            aOrbitB = aOrbitB + aOrbitA + 7455700557403774923ULL + mSaltE[((aWandererC + RotL64(aPrevious, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitB ^ 15597398830011408849ULL ^ mSaltD[((RotL64(aScatter, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD * 8066836458459940135ULL, 37U);
            aPrism = (aPrism ^ (RotL64(aOrbitA, 51U) + RotL64(aCarry, 53U)) ^ 10676085577108177914ULL) * 2844432091392960027ULL;
            aCurrent = (aOrbitC ^ RotL64(aOrbitD, 13U)) + (RotL64(aOrbitB, 27U) ^ aOrbitA);
            aCurrent = TwistMix64::DiffuseC(aCurrent ^ aScatter);
            aWorkLaneB[S_BLOCK1 - aIndex] = aCurrent;
            aPrism = TwistMix64::DiffuseB(aPrism);
            switch (aPrism % 2U) {
            	case 0U: {
            		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 5ULL, mSBoxA, mSBoxH, mSBoxC, mSBoxF, mSBoxG, mSBoxB, mSBoxD, mSBoxE);
            		break;
            	}
            	case 1U: {
            		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, mSBoxD, mSBoxB, mSBoxF, mSBoxE, mSBoxC, mSBoxA, mSBoxH, mSBoxG);
            		break;
            	}
            }
            aWandererB = aWandererB + (RotL64(aCurrent, 7U) ^ aPrevious ^ aOrbitA);
            aWandererB = RotL64((aWandererB + mSaltC[((31U - aIndex) & static_cast<std::uint64_t>(S_SALT1))]) * 13273130330270357309ULL, 29U);
            aWandererD = aWandererD ^ (aCurrent + aCross + RotL64(aOrbitC, 21U));
            aWandererD = RotL64((aWandererD ^ mSaltF[((aIndex + 2U) & static_cast<std::uint64_t>(S_SALT1))]) * 17024492006014096099ULL, 11U);
            aWandererC = aWandererC + (RotL64(aOrbitD, 43U) ^ aOrbitB ^ mSaltD[((aIndex + 5U) & static_cast<std::uint64_t>(S_SALT1))]);
            aWandererC = RotL64(aWandererC * 12545261339544312959ULL, 45U);
            aCarry = aCarry + (aWandererB ^ aWandererD ^ RotL64(aWandererC, 1U) ^ aCurrent);
            aCarry = RotL64(aCarry * 17420819641258581859ULL, 13U);
            aCarry = aCarry ^ ShiftR64(aCarry, 41U);
            // __END_CSPRNG
        }
        aReloop = pFarmSalt->TillBytes(aWorkLaneB, aExpandLaneB, 32ULL) ? aReloop : 1ULL;
    }
    // Secure zero on snow + scratch expansion lanes.
    TwistMemory::ZeroBlock(aExpandLaneB);
    TwistMemory::ZeroBlock(aExpandLaneC);
    // Making snow counter: aria 256
    TwistSnow::Aria256Counter(pSource, aExpandLaneC);
    // Initialize worker lane for this pass.
    TwistMemory::Copy(aWorkLaneC, aWorkLaneB, 8192U);
    aReloop = 1U;
    while (aReloop != 0) {
        for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
            aPrevious = aCurrent;
            aCurrent = aWorkLaneC[aIndex] ^ ShiftL64(aExpandLaneC[S_BLOCK1 - aIndex], 32U);
            aCross = aWorkLaneC[S_BLOCK1 - aIndex];
            // __START_CSPRNG
            aScatter = TwistMix64::DiffuseA(aCurrent ^ ShiftL64(aCross, 32U) ^ RotL64(aPrevious, 21U));
            aOrbitC = aWandererB + RotL64(aCurrent, 13U) + 2073881356398517866ULL + mSaltH[((RotL64(aPrevious, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aWandererA ^ RotL64(aPrevious, 53U) ^ 1542242311709492533ULL ^ mSaltG[((RotL64(aWandererD, 27U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = aWandererD + RotL64(aCross, 37U) + mSaltE[((aIndex + 19U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltB[((31U - aIndex + 6U) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aCarry, 45U) ^ RotL64(aCurrent, 35U) ^ mSaltF[((31U - aIndex + 1U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltA[((aIndex + 10U) & static_cast<std::uint64_t>(S_SALT1))];
            aPrism = aCurrent;
            aOrbitC = aOrbitC + aOrbitD + 3861757145688643445ULL + mSaltB[((RotL64(aOrbitC, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitC ^ 7107198819402508709ULL ^ mSaltE[((RotL64(aWandererB, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB * 10616804309208265063ULL, 43U);
            aPrism = (aPrism ^ (RotL64(aOrbitA, 51U) + aPrevious) ^ 15193416499581203364ULL) * 2190639254739351351ULL;
            aOrbitA = aOrbitA + aOrbitB + 10225770088324741144ULL + mSaltB[((RotL64(aCarry, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitA ^ 12868349447288203855ULL ^ mSaltF[((aScatter + RotL64(aScatter, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD, 27U);
            aPrism = (aPrism + (RotL64(aCross, 37U) ^ aCarry) + 15648982584675595500ULL) * 3332942701590945879ULL;
            aOrbitC = aOrbitC + aOrbitD + 7688815676248272995ULL + mSaltA[((RotL64(aWandererA, 29U) + aOrbitB) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitC ^ 14904434324034388986ULL ^ mSaltB[((aOrbitA ^ RotL64(aOrbitD, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB * 7279187742599832857ULL, 53U);
            aPrism = (aPrism ^ (RotL64(aOrbitD, 45U) + RotL64(aWandererB, 1U)) ^ 7883086871465684595ULL) * 18026924179256320139ULL;
            aOrbitA = aOrbitA + aOrbitB + 7400630808808783295ULL + mSaltE[((RotL64(aCross, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitA ^ 15354024231420105295ULL ^ mSaltE[((aWandererD ^ RotL64(aPrevious, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD * 10228955576945638795ULL, 43U);
            aPrism = (aPrism + ((RotL64(aOrbitB, 3U) + mSaltA[((RotL64(aOrbitC, 13U) ^ aCarry) & static_cast<std::uint64_t>(S_SALT1))]) ^ mSaltF[((RotL64(aWandererA, 27U) ^ aScatter) & static_cast<std::uint64_t>(S_SALT1))]) + 2570248700782545083ULL) * 16460245735004858149ULL;
            aCurrent = (aOrbitC ^ RotL64(aOrbitB, 29U)) + (RotL64(aOrbitD, 11U) ^ aOrbitA);
            aCurrent = TwistMix64::DiffuseC(aCurrent + aScatter);
            aExpandLaneD[aIndex] = aCurrent;
            aPrism = TwistMix64::DiffuseC(aPrism);
            switch (aPrism % 3U) {
            	case 0U: {
            		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 7ULL, mSBoxA, mSBoxG, mSBoxC, mSBoxD, mSBoxB, mSBoxE, mSBoxF, mSBoxH);
            		break;
            	}
            	case 1U: {
            		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 5ULL, mSBoxB, mSBoxH, mSBoxC, mSBoxA, mSBoxD, mSBoxE, mSBoxF, mSBoxG);
            		break;
            	}
            	case 2U: {
            		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, mSBoxE, mSBoxC, mSBoxB, mSBoxD, mSBoxH, mSBoxA, mSBoxG, mSBoxF);
            		break;
            	}
            }
            aWandererB = aWandererB + (aCurrent ^ RotL64(aPrevious, 21U) ^ aOrbitB);
            aWandererB = RotL64((aWandererB + mSaltF[((31U - aIndex + 10U) & static_cast<std::uint64_t>(S_SALT1))]) * 18255761041207007501ULL, 27U);
            aWandererA = aWandererA ^ (aCurrent + aCross + RotL64(aOrbitC, 35U));
            aWandererA = RotL64((aWandererA ^ mSaltA[((31U - aIndex + 10U) & static_cast<std::uint64_t>(S_SALT1))]) * 16814780665206993361ULL, 13U);
            aWandererD = aWandererD + (aOrbitD ^ RotL64(aOrbitA, 51U) ^ mSaltB[((aIndex + 9U) & static_cast<std::uint64_t>(S_SALT1))]);
            aWandererD = RotL64(aWandererD * 17898183497550008181ULL, 11U);
            aCarry = aCarry + (aWandererB ^ aWandererA ^ aWandererD ^ RotL64(aCurrent, 29U));
            aCarry = RotL64(aCarry * 12884190393772392497ULL, 21U);
            aCarry = aCarry ^ ShiftR64(aCarry, 41U);
            // __END_CSPRNG
        }
        aReloop = pFarmSBox->TillBytes(aExpandLaneD, aExpandLaneC, 48ULL) ? 0ULL : 1ULL;
        for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
            aPrevious = aCurrent;
            aCurrent = aExpandLaneD[aIndex] ^ ShiftL64(aExpandLaneC[aIndex], 32U);
            aCross = aWorkLaneC[aIndex];
            // __START_CSPRNG
            aScatter = TwistMix64::DiffuseA(aCurrent ^ ShiftL64(aCross, 32U) ^ RotL64(aPrevious, 19U));
            aOrbitA = aWandererC + RotL64(aCurrent, 5U) + 1542242311709492533ULL + mSaltD[((aWandererC + RotL64(aOrbitD, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aWandererD ^ RotL64(aPrevious, 7U) ^ 3861757145688643445ULL ^ mSaltC[((aScatter ^ RotL64(aCross, 27U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = aWandererB + RotL64(aCross, 11U) + mSaltA[((31U - aIndex + 22U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltF[((aIndex + 12U) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aCarry, 43U) ^ RotL64(aCurrent, 13U) ^ mSaltA[((31U - aIndex + 7U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltB[((aIndex + 13U) & static_cast<std::uint64_t>(S_SALT1))];
            aPrism = aCurrent;
            aOrbitA = aOrbitA + aOrbitB + 7107198819402508709ULL + mSaltE[((aWandererB + RotL64(aScatter, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitA ^ 15193416499581203364ULL ^ mSaltE[((RotL64(aWandererD, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD * 2190639254739351351ULL, 51U);
            aPrism = (aPrism ^ RotL64(aOrbitC, 45U) ^ RotL64(aPrevious, 21U) ^ 10225770088324741144ULL) * 2341683444710587833ULL;
            aOrbitC = aOrbitC + aOrbitD + 12868349447288203855ULL + mSaltF[((aOrbitA ^ RotL64(aPrevious, 27U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitC ^ 15648982584675595500ULL ^ mSaltA[((aOrbitC ^ RotL64(aCarry, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB, 37U);
            aPrism = (aPrism + (RotL64(aCarry, 35U) ^ RotL64(aCross, 53U)) + 7688815676248272995ULL) * 893743006767686457ULL;
            aOrbitA = aOrbitA + aOrbitB + 14904434324034388986ULL + mSaltB[((aWandererC ^ RotL64(aScatter, 13U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = aOrbitD ^ aOrbitA ^ 7883086871465684595ULL ^ mSaltB[((RotL64(aWandererB, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitD = RotL64(aOrbitD * 18026924179256320139ULL, 51U);
            aPrism = (aPrism ^ RotL64(aOrbitB, 43U) ^ mSaltB[((RotL64(aCross, 19U)) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltE[((RotL64(aScatter, 21U) + aWandererD) & static_cast<std::uint64_t>(S_SALT1))] ^ 7400630808808783295ULL) * 8645542920601721621ULL;
            aOrbitC = aOrbitC + aOrbitD + 15354024231420105295ULL + mSaltE[((RotL64(aOrbitB, 27U) + aPrevious) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitC ^ 2570248700782545083ULL ^ mSaltF[((RotL64(aOrbitA, 11U) + aOrbitC) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB * 16460245735004858149ULL, 45U);
            aPrism = (aPrism + aOrbitD + RotL64(aWandererC, 13U) + 5989818739053789111ULL) * 18255761041207007501ULL;
            aCurrent = (aOrbitA ^ RotL64(aOrbitB, 29U)) + (RotL64(aOrbitC, 19U) ^ aOrbitD);
            aCurrent = TwistMix64::DiffuseA(aCurrent + aScatter);
            aWorkLaneC[aIndex] = aCurrent;
            aPrism = TwistMix64::DiffuseB(aPrism);
            switch (aPrism % 4U) {
            	case 0U: {
            		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 21ULL, mSBoxC, mSBoxF, mSBoxG, mSBoxE, mSBoxH, mSBoxB, mSBoxD, mSBoxA);
            		break;
            	}
            	case 1U: {
            		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 1ULL, mSBoxB, mSBoxC, mSBoxF, mSBoxG, mSBoxE, mSBoxH, mSBoxD, mSBoxA);
            		break;
            	}
            	case 2U: {
            		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, mSBoxE, mSBoxF, mSBoxC, mSBoxG, mSBoxH, mSBoxD, mSBoxB, mSBoxA);
            		break;
            	}
            	case 3U: {
            		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 11ULL, mSBoxD, mSBoxC, mSBoxE, mSBoxF, mSBoxB, mSBoxH, mSBoxA, mSBoxG);
            		break;
            	}
            }
            aWandererC = aWandererC + (aCurrent ^ aPrevious ^ RotL64(aOrbitD, 53U));
            aWandererC = RotL64((aWandererC + mSaltA[((31U - aIndex + 2U) & static_cast<std::uint64_t>(S_SALT1))]) * 16814780665206993361ULL, 35U);
            aWandererD = aWandererD ^ (aCurrent + aCross + RotL64(aOrbitA, 7U));
            aWandererD = RotL64((aWandererD ^ mSaltB[((31U - aIndex) & static_cast<std::uint64_t>(S_SALT1))]) * 17898183497550008181ULL, 37U);
            aWandererB = aWandererB + (aOrbitB ^ RotL64(aOrbitC, 51U) ^ mSaltA[((aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))]);
            aWandererB = RotL64(aWandererB * 12884190393772392497ULL, 43U);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererD, 45U) ^ aWandererB ^ aCurrent);
            aCarry = RotL64(aCarry * 11647722971741053063ULL, 21U);
            aCarry = aCarry ^ ShiftR64(aCarry, 23U);
            // __END_CSPRNG
        }
        aReloop = pFarmSalt->TillBytes(aWorkLaneC, aExpandLaneC, 48ULL) ? aReloop : 1ULL;
    }
    // Secure zero on snow + scratch expansion lanes.
    TwistMemory::ZeroBlock(aExpandLaneC);
    TwistMemory::ZeroBlock(aExpandLaneD);
    // Making snow counter: cha cha 20
    TwistSnow::ChaCha20Counter(pSource, aExpandLaneD);
    // Initialize worker lane for this pass.
    TwistMemory::Copy(aWorkLaneD, aWorkLaneC, 8192U);
    aReloop = 1U;
    while (aReloop != 0) {
        for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
            aPrevious = aCurrent;
            aCurrent = aWorkLaneD[aIndex] ^ ShiftL64(aExpandLaneD[aIndex], 32U);
            aCross = aWorkLaneD[S_BLOCK1 - aIndex];
            // __START_CSPRNG
            aScatter = TwistMix64::DiffuseA(ShiftL64(aCurrent, 32U) ^ aCross ^ RotL64(aPrevious, 13U));
            aOrbitD = aWandererA + RotL64(aCurrent, 11U) + 14225520429492553865ULL + mSaltD[((aPrevious ^ RotL64(aOrbitD, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aWandererD ^ RotL64(aPrevious, 27U) ^ 6051788685487487430ULL ^ mSaltG[((RotL64(aScatter, 29U) ^ aCarry) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = aWandererC + RotL64(aCross, 37U) + mSaltB[((aIndex + 13U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltA[((31U - aIndex + 6U) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = RotL64(aCarry, 45U) ^ RotL64(aCurrent, 7U) ^ mSaltH[((aIndex + 3U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltH[((31U - aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))];
            aPrism = aCurrent;
            aOrbitD = aOrbitD + aOrbitB + 269145807845880446ULL + mSaltC[((RotL64(aWandererD, 21U) ^ aOrbitA) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = aOrbitA ^ aOrbitD ^ 3093792480720877685ULL ^ mSaltB[((RotL64(aScatter, 13U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = RotL64(aOrbitA * 445703599430895705ULL, 11U);
            aPrism = (aPrism ^ (RotL64(aOrbitC, 19U) + mSaltH[((RotL64(aOrbitB, 27U)) & static_cast<std::uint64_t>(S_SALT1))]) ^ 15966139434135024991ULL) * 3130650767718574631ULL;
            aOrbitC = aOrbitC + aOrbitA + 12048098856795507291ULL + mSaltA[((aOrbitC ^ RotL64(aWandererA, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitC ^ 16051192479946208979ULL ^ mSaltC[((aCross ^ RotL64(aOrbitD, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB, 13U);
            aPrism = (aPrism + aCross + RotL64(aCarry, 35U) + mSaltC[((RotL64(aScatter, 11U)) & static_cast<std::uint64_t>(S_SALT1))] + 10313110232703171055ULL) * 4423851756184666997ULL;
            aOrbitD = aOrbitD + aOrbitB + 9185258274633192882ULL + mSaltH[((aPrevious ^ RotL64(aWandererD, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = aOrbitA ^ aOrbitD ^ 12213658970859535924ULL ^ mSaltH[((aCarry + RotL64(aScatter, 27U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = RotL64(aOrbitA * 14677633960671988805ULL, 53U);
            aPrism = (aPrism ^ (aOrbitB + RotL64(aPrevious, 5U)) ^ 10178864425399601784ULL) * 516844171872484935ULL;
            aOrbitC = aOrbitC + aOrbitA + 18007105490619936222ULL + mSaltB[((aOrbitB + RotL64(aOrbitC, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitC ^ 2613844046083763710ULL ^ mSaltA[((aOrbitA ^ RotL64(aWandererC, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB * 14596143124969169081ULL, 43U);
            aPrism = (aPrism + (aOrbitA ^ RotL64(aWandererA, 51U)) + 11837566500311073101ULL) * 10891758202301845007ULL;
            aCurrent = (RotL64(aOrbitD, 13U) ^ aOrbitA) + (aOrbitB ^ RotL64(aOrbitC, 11U));
            aCurrent = TwistMix64::DiffuseA(aCurrent ^ aScatter);
            aExpandLaneA[aIndex] = aCurrent;
            aPrism = TwistMix64::DiffuseB(aPrism);
            switch (aPrism % 3U) {
                case 0U: {
                    aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 1ULL, mSBoxD, mSBoxA, mSBoxH, mSBoxB, mSBoxE, mSBoxC, mSBoxF, mSBoxG);
                    break;
                }
                case 1U: {
                    aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 19ULL, mSBoxC, mSBoxG, mSBoxF, mSBoxA, mSBoxH, mSBoxE, mSBoxB, mSBoxD);
                    break;
                }
                case 2U: {
                    aCurrent = TwistMix64::GatePrism_8_8(aCurrent, mSBoxG, mSBoxC, mSBoxF, mSBoxE, mSBoxD, mSBoxB, mSBoxH, mSBoxA);
                    break;
                }
            }
            aWandererA = aWandererA + (RotL64(aCurrent, 35U) ^ aPrevious ^ aOrbitA);
            aWandererA = RotL64((aWandererA + mSaltC[((31U - aIndex + 12U) & static_cast<std::uint64_t>(S_SALT1))]) * 4971105095007972629ULL, 27U);
            aWandererD = aWandererD ^ (RotL64(aCurrent, 29U) + aCross + aOrbitD);
            aWandererD = RotL64((aWandererD ^ mSaltC[((31U - aIndex + 12U) & static_cast<std::uint64_t>(S_SALT1))]) * 1215101204641181467ULL, 37U);
            aWandererC = aWandererC + (RotL64(aOrbitB, 13U) ^ aOrbitC ^ mSaltH[((31U - aIndex + 12U) & static_cast<std::uint64_t>(S_SALT1))]);
            aWandererC = RotL64(aWandererC * 1021811810760825677ULL, 21U);
            aCarry = aCarry + (aWandererA ^ aWandererD ^ aWandererC ^ RotL64(aCurrent, 27U));
            aCarry = RotL64(aCarry * 11289625450815393413ULL, 11U);
            aCarry = aCarry ^ ShiftR64(aCarry, 31U);
            // __END_CSPRNG
        }
        aReloop = pFarmSBox->TillBytes(aExpandLaneA, aExpandLaneD, 64ULL) ? 0ULL : 1ULL;
        for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
            aPrevious = aCurrent;
            aCurrent = aExpandLaneA[aIndex] ^ ShiftL64(aExpandLaneD[S_BLOCK1 - aIndex], 32U);
            aCross = aWorkLaneD[aIndex];
            // __START_CSPRNG
            aScatter = TwistMix64::DiffuseA(ShiftL64(aCurrent, 32U) ^ aCross ^ RotL64(aPrevious, 19U));
            aOrbitD = aWandererB + RotL64(aCurrent, 1U) + 2486098360787209352ULL + mSaltE[((RotL64(aWandererD, 13U) ^ aCarry) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aWandererC ^ RotL64(aPrevious, 53U) ^ 7732688477561655418ULL ^ mSaltF[((aScatter + RotL64(aWandererC, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitA = aWandererD + RotL64(aCross, 35U) + mSaltH[((aIndex + 14U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltC[((31U - aIndex + 26U) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = RotL64(aCarry, 43U) ^ RotL64(aCurrent, 27U) ^ mSaltC[((aIndex + 10U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltA[((31U - aIndex + 12U) & static_cast<std::uint64_t>(S_SALT1))];
            aPrism = aCurrent;
            aOrbitD = aOrbitD + aOrbitB + 14225520429492553865ULL + mSaltB[((RotL64(aOrbitB, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = aOrbitC ^ aOrbitD ^ 6051788685487487430ULL ^ mSaltH[((RotL64(aOrbitD, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = RotL64(aOrbitC * 7108575819100278935ULL, 51U);
            aPrism = (aPrism ^ (RotL64(aOrbitA, 19U) + aPrevious) ^ 269145807845880446ULL) * 2274096424334469945ULL;
            aOrbitA = aOrbitA + aOrbitC + 3093792480720877685ULL + mSaltC[((RotL64(aOrbitA, 29U) ^ aWandererB) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitA ^ 15966139434135024991ULL ^ mSaltC[((RotL64(aPrevious, 13U) ^ aScatter) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB, 45U);
            aPrism = (aPrism + (RotL64(aCarry, 11U) ^ aCross ^ mSaltB[((aOrbitC + RotL64(aWandererD, 21U)) & static_cast<std::uint64_t>(S_SALT1))]) + 12048098856795507291ULL) * 9290756262770726387ULL;
            aOrbitD = aOrbitD + aOrbitB + 16051192479946208979ULL + mSaltA[((RotL64(aScatter, 29U) + aWandererC) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = aOrbitC ^ aOrbitD ^ 10313110232703171055ULL ^ mSaltB[((RotL64(aOrbitB, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitC = RotL64(aOrbitC * 4423851756184666997ULL, 37U);
            aPrism = (aPrism ^ (RotL64(aOrbitB, 13U) + RotL64(aWandererB, 3U)) ^ 9185258274633192882ULL) * 14835872973309634213ULL;
            aOrbitA = aOrbitA + aOrbitC + 12213658970859535924ULL + mSaltH[((RotL64(aOrbitA, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = aOrbitB ^ aOrbitA ^ 10178864425399601784ULL ^ mSaltH[((aOrbitD + RotL64(aCarry, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
            aOrbitB = RotL64(aOrbitB * 516844171872484935ULL, 19U);
            aPrism = (aPrism + (RotL64(aOrbitC, 53U) ^ mSaltA[((RotL64(aWandererB, 29U) ^ aPrevious) & static_cast<std::uint64_t>(S_SALT1))]) + 18007105490619936222ULL) * 5786377212033764029ULL;
            aCurrent = (aOrbitD ^ RotL64(aOrbitB, 11U)) + (RotL64(aOrbitA, 13U) ^ aOrbitC);
            aCurrent = TwistMix64::DiffuseA(aCurrent + aScatter);
            aWorkLaneD[S_BLOCK1 - aIndex] = aCurrent;
            aPrism = TwistMix64::DiffuseA(aPrism);
            switch (aPrism % 3U) {
            	case 0U: {
            		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, mSBoxH, mSBoxD, mSBoxA, mSBoxF, mSBoxC, mSBoxG, mSBoxB, mSBoxE);
            		break;
            	}
            	case 1U: {
            		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 5ULL, mSBoxG, mSBoxD, mSBoxF, mSBoxC, mSBoxE, mSBoxH, mSBoxB, mSBoxA);
            		break;
            	}
            	case 2U: {
            		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 43ULL, mSBoxB, mSBoxC, mSBoxA, mSBoxH, mSBoxG, mSBoxF, mSBoxD, mSBoxE);
            		break;
            	}
            }
            aWandererB = aWandererB + (aCurrent ^ RotL64(aPrevious, 35U) ^ aOrbitC);
            aWandererB = RotL64((aWandererB + mSaltC[((31U - aIndex + 3U) & static_cast<std::uint64_t>(S_SALT1))]) * 14596143124969169081ULL, 27U);
            aWandererC = aWandererC ^ (RotL64(aCurrent, 51U) + aCross + aOrbitD);
            aWandererC = RotL64((aWandererC ^ mSaltA[((aIndex + 8U) & static_cast<std::uint64_t>(S_SALT1))]) * 10891758202301845007ULL, 45U);
            aWandererD = aWandererD + (aOrbitB ^ RotL64(aOrbitA, 21U) ^ mSaltB[((aIndex + 26U) & static_cast<std::uint64_t>(S_SALT1))]);
            aWandererD = RotL64(aWandererD * 4971105095007972629ULL, 37U);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererC, 19U) ^ aWandererD ^ aCurrent);
            aCarry = RotL64(aCarry * 1215101204641181467ULL, 11U);
            aCarry = aCarry ^ ShiftR64(aCarry, 23U);
            // __END_CSPRNG
        }
        aReloop = pFarmSalt->TillBytes(aWorkLaneD, aExpandLaneD, 64ULL) ? aReloop : 1ULL;
    }
    // Secure zero on snow + scratch expansion lanes.
    TwistMemory::ZeroBlock(aExpandLaneD);
    TwistMemory::ZeroBlock(aExpandLaneA);
    // Generate operation lanes from source + worker pairs.
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = ShiftL64(pSource[S_BLOCK1 - aIndex], 16U) | ShiftL64(aWorkLaneA[S_BLOCK1 - aIndex], 8U) | aWorkLaneB[S_BLOCK1 - aIndex];
        aCross = ShiftL64(aWorkLaneA[S_BLOCK1 - aIndex], 8U) | aWorkLaneB[S_BLOCK1 - aIndex];
        aScatter = TwistMix64::DiffuseA(aCurrent ^ ShiftL64(aCross, 32U) ^ RotL64(aPrevious, 11U));
        aOrbitC = aWandererC + RotL64(aCurrent, 7U) + 15030797346540340471ULL + mSaltD[((aPrevious + RotL64(aCarry, 13U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aWandererD ^ RotL64(aPrevious, 21U) ^ 14084573094707411164ULL ^ mSaltA[((aWandererD + RotL64(aOrbitD, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererB + RotL64(aCross, 51U) + mSaltG[((aIndex + 24U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltB[((31U - aIndex + 1U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = RotL64(aCarry, 53U) ^ RotL64(aCurrent, 45U) ^ mSaltG[((31U - aIndex + 10U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltC[((aIndex + 14U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC + aOrbitB + 11998092425188837914ULL + mSaltH[((aOrbitB ^ RotL64(aWandererB, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA ^ aOrbitC ^ 9446146461917371001ULL ^ mSaltG[((aWandererC + RotL64(aCross, 27U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = RotL64(aOrbitA * 10213158099001462037ULL, 37U);
        aOrbitD = aOrbitD + aOrbitA + 400160012451876105ULL + mSaltB[((RotL64(aScatter, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB ^ aOrbitD ^ 14746306801475654464ULL ^ mSaltG[((RotL64(aPrevious, 13U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = RotL64(aOrbitB, 21U);
        aOrbitC = aOrbitC + aOrbitB + 15157286770213647983ULL + mSaltC[((RotL64(aOrbitA, 29U) + aScatter) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA ^ aOrbitC ^ 17962197713055811155ULL ^ mSaltH[((RotL64(aCarry, 19U) + aOrbitD) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = RotL64(aOrbitA * 17180159925948402441ULL, 27U);
        aOrbitD = aOrbitD + aOrbitA + 15497556631046481162ULL + mSaltH[((RotL64(aWandererB, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB ^ aOrbitD ^ 3411681759945001263ULL ^ mSaltB[((RotL64(aWandererC, 13U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = RotL64(aOrbitB * 9516248637769029335ULL, 1U);
        aCurrent = (RotL64(aOrbitC, 21U) ^ aOrbitB) + (aOrbitD ^ RotL64(aOrbitA, 29U));
        aCurrent = TwistMix64::DiffuseA(aCurrent + aScatter);
        aOperationLaneA[aIndex] = aCurrent;
        aWandererC = aWandererC + (aCurrent ^ aPrevious ^ RotL64(aOrbitA, 43U));
        aWandererC = RotL64((aWandererC + mSaltG[((aIndex + 25U) & static_cast<std::uint64_t>(S_SALT1))]) * 12269539857655536619ULL, 19U);
        aWandererD = aWandererD ^ (aCurrent + aCross + RotL64(aOrbitC, 35U));
        aWandererD = RotL64((aWandererD ^ mSaltC[((31U - aIndex + 17U) & static_cast<std::uint64_t>(S_SALT1))]) * 17816531704553483557ULL, 27U);
        aWandererB = aWandererB + (RotL64(aOrbitB, 11U) ^ aOrbitD ^ mSaltC[((31U - aIndex + 12U) & static_cast<std::uint64_t>(S_SALT1))]);
        aWandererB = RotL64(aWandererB * 6945486613706339303ULL, 21U);
        aCarry = aCarry + (aWandererC ^ aWandererD ^ aWandererB ^ RotL64(aCurrent, 3U));
        aCarry = RotL64(aCarry * 3146837208238096023ULL, 53U);
        aCarry = aCarry ^ ShiftR64(aCarry, 43U);
    }
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = ShiftL64(pSource[aIndex], 16U) | ShiftL64(aWorkLaneC[aIndex], 8U) | aWorkLaneD[aIndex];
        aCross = ShiftL64(aWorkLaneC[aIndex], 8U) | aWorkLaneD[aIndex];
        aScatter = TwistMix64::DiffuseA(ShiftL64(aCurrent, 32U) ^ aCross ^ RotL64(aPrevious, 21U));
        aOrbitA = aWandererC + RotL64(aCurrent, 11U) + 3861757145688643445ULL + mSaltD[((aOrbitC ^ RotL64(aWandererD, 29U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aWandererB ^ RotL64(aPrevious, 43U) ^ 7107198819402508709ULL ^ mSaltC[((aCross + RotL64(aWandererB, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitD = aWandererD + RotL64(aCross, 13U) + mSaltE[((31U - aIndex + 27U) & static_cast<std::uint64_t>(S_SALT1))] + mSaltB[((aIndex + 15U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = RotL64(aCarry, 45U) ^ RotL64(aCurrent, 27U) ^ mSaltB[((31U - aIndex + 25U) & static_cast<std::uint64_t>(S_SALT1))] ^ mSaltA[((aIndex + 11U) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitA = aOrbitA + aOrbitB + 15193416499581203364ULL + mSaltF[((RotL64(aScatter, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC ^ aOrbitA ^ 10225770088324741144ULL ^ mSaltE[((RotL64(aWandererC, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = RotL64(aOrbitC * 2341683444710587833ULL, 19U);
        aOrbitD = aOrbitD + aOrbitC + 15648982584675595500ULL + mSaltF[((RotL64(aScatter, 29U) ^ aOrbitA) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB ^ aOrbitD ^ 7688815676248272995ULL ^ mSaltB[((aOrbitB ^ RotL64(aCarry, 27U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = RotL64(aOrbitB, 37U);
        aOrbitA = aOrbitA + aOrbitB + 7883086871465684595ULL + mSaltA[((aWandererD + RotL64(aPrevious, 21U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = aOrbitC ^ aOrbitA ^ 7400630808808783295ULL ^ mSaltE[((aOrbitC + RotL64(aWandererB, 11U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitC = RotL64(aOrbitC * 8645542920601721621ULL, 35U);
        aOrbitD = aOrbitD + aOrbitC + 2570248700782545083ULL + mSaltB[((aOrbitD ^ RotL64(aCross, 19U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = aOrbitB ^ aOrbitD ^ 5989818739053789111ULL ^ mSaltF[((aScatter ^ RotL64(aOrbitA, 27U)) & static_cast<std::uint64_t>(S_SALT1))];
        aOrbitB = RotL64(aOrbitB * 18255761041207007501ULL, 53U);
        aCurrent = (RotL64(aOrbitA, 29U) ^ aOrbitB) + (RotL64(aOrbitD, 21U) ^ aOrbitC);
        aCurrent = TwistMix64::DiffuseA(aCurrent + aScatter);
        aOperationLaneB[aIndex] = aCurrent;
        aWandererC = aWandererC + (aCurrent ^ RotL64(aPrevious, 5U) ^ aOrbitC);
        aWandererC = RotL64((aWandererC + mSaltF[((31U - aIndex + 9U) & static_cast<std::uint64_t>(S_SALT1))]) * 17898183497550008181ULL, 19U);
        aWandererB = aWandererB ^ (RotL64(aCurrent, 51U) + aCross + aOrbitA);
        aWandererB = RotL64((aWandererB ^ mSaltA[((aIndex + 16U) & static_cast<std::uint64_t>(S_SALT1))]) * 12884190393772392497ULL, 43U);
        aWandererD = aWandererD + (aOrbitB ^ RotL64(aOrbitD, 45U) ^ mSaltE[((31U - aIndex + 26U) & static_cast<std::uint64_t>(S_SALT1))]);
        aWandererD = RotL64(aWandererD * 11647722971741053063ULL, 37U);
        aCarry = aCarry + (aWandererC ^ RotL64(aWandererB, 11U) ^ aWandererD ^ aCurrent);
        aCarry = RotL64(aCarry * 17094836863079093551ULL, 51U);
        aCarry = aCarry ^ ShiftR64(aCarry, 33U);
    }

    // [phase ii]
    // phase: workers -> expansion [offset 0]
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 8128U - aIndex;
        aPrism = aOperationLaneA[aIndex];
        switch (aPrism % 2U) {
            case 0U: {
                mMatrixA.LoadAndReset(aWorkLaneA + aWalker);
                mMatrixB.LoadAndReset(aWorkLaneB + aIndex);
                aArgA = aOperationLaneA[(aIndex + 1U)];
                aArgB = aOperationLaneA[(aIndex + 2U)];
                mMatrixA.SwapCols(aArgA, aArgB);
                mMatrixA.FlipHorizontalQuarterD(0U, 0U);
                mMatrixA.PinwheelRight(0U, 0U);
                aKindA = aOperationLaneA[(aIndex + 3U)];
                mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
                mMatrixB.TransposeAntiDiagonalQuarterD(0U, 0U);
                mMatrixB.RotateRightSixteenthsEachQuarter(0U, 0U);
                aArgA = aOperationLaneA[(aIndex + 4U)];
                aArgB = aOperationLaneA[(aIndex + 5U)];
                mMatrixB.SwapSixteenths(aArgA, aArgB);
                aKindB = aOperationLaneA[(aIndex + 6U)];
                mMatrixB.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
                break;
            }
            case 1U: {
                mMatrixA.LoadAndReset(aWorkLaneA + aWalker);
                mMatrixB.LoadAndReset(aWorkLaneB + aIndex);
                aArgA = aOperationLaneA[(aIndex + 1U)];
                aArgB = aOperationLaneA[(aIndex + 2U)];
                mMatrixA.SwapRowsEven(aArgA, aArgB);
                mMatrixA.FlipVerticalSixteenthsQuarterC(0U, 0U);
                aArgA = aOperationLaneA[(aIndex + 3U)];
                mMatrixA.ShiftRing20C(aArgA, 0U);
                mMatrixA.TransposeAntiDiagonalEachQuarter(0U, 0U);
                aKindA = aOperationLaneA[(aIndex + 4U)];
                mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kC, aKindA);
                mMatrixB.RotateLeftSixteenthsEachQuarter(0U, 0U);
                aArgB = aOperationLaneA[(aIndex + 5U)];
                mMatrixB.ReverseRowOdd(aArgB, 0U);
                aArgB = aOperationLaneA[(aIndex + 6U)];
                mMatrixB.ReverseColEven(aArgB, 0U);
                aKindB = aOperationLaneA[(aIndex + 7U)];
                mMatrixB.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kA, aKindB);
                break;
            }
        }
    }
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 8128U - aIndex;
        aPrism = aOperationLaneB[aIndex];
        switch (aPrism % 2U) {
            case 0U: {
                mMatrixA.LoadAndReset(aWorkLaneC + aWalker);
                mMatrixB.LoadAndReset(aWorkLaneD + aWalker);
                aArgA = aOperationLaneB[(aIndex + 1U)];
                mMatrixA.ReverseCol(aArgA, 0U);
                aArgA = aOperationLaneB[(aIndex + 2U)];
                aArgB = aOperationLaneB[(aIndex + 3U)];
                mMatrixA.SwapColsEven(aArgA, aArgB);
                aArgA = aOperationLaneB[(aIndex + 4U)];
                mMatrixA.ShiftRing16B(aArgA, 0U);
                mMatrixA.TransposeMainDiagonalEachSixteenthQuarterA(0U, 0U);
                aKindA = aOperationLaneB[(aIndex + 5U)];
                mMatrixA.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
                mMatrixB.TransposeAntiDiagonalQuarterA(0U, 0U);
                mMatrixB.TransposeAntiDiagonalSixteenthsQuarterD(0U, 0U);
                aArgB = aOperationLaneB[(aIndex + 6U)];
                mMatrixB.ReverseRowEven(aArgB, 0U);
                aKindB = aOperationLaneB[(aIndex + 7U)];
                mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kC, aKindB);
                break;
            }
            case 1U: {
                mMatrixA.LoadAndReset(aWorkLaneC + aWalker);
                mMatrixB.LoadAndReset(aWorkLaneD + aWalker);
                mMatrixA.TransposeMainDiagonalEachSixteenthQuarterD(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 1U)];
                mMatrixA.ShiftRing8G(aArgA, 0U);
                aArgA = aOperationLaneB[(aIndex + 2U)];
                mMatrixA.ReverseRowOdd(aArgA, 0U);
                aKindA = aOperationLaneB[(aIndex + 3U)];
                mMatrixA.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kD, aKindA);
                mMatrixB.RotateLeftQuarterC(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 4U)];
                aArgB = aOperationLaneB[(aIndex + 5U)];
                mMatrixB.SwapColsOdd(aArgA, aArgB);
                mMatrixB.RotateRightBlocks(0U, 0U);
                mMatrixB.PinwheelLeftQuarterA(0U, 0U);
                mMatrixB.TransposeMainDiagonalBlocks(0U, 0U);
                aKindB = aOperationLaneB[(aIndex + 6U)];
                mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kA, aKindB);
                break;
            }
        }
    }
    // phase: expansion -> workers [offset 20]
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 8128U - aIndex;
        aPrism = aOperationLaneA[(aIndex + 20U)];
        switch (aPrism % 2U) {
            case 0U: {
                mMatrixA.LoadAndReset(aExpandLaneA + aIndex);
                mMatrixB.LoadAndReset(aExpandLaneC + aWalker);
                aArgA = aOperationLaneA[(aIndex + 21U)];
                aArgB = aOperationLaneA[(aIndex + 22U)];
                mMatrixA.SwapCols(aArgA, aArgB);
                aArgA = aOperationLaneA[(aIndex + 23U)];
                mMatrixA.ReverseRowEven(aArgA, 0U);
                mMatrixA.PinwheelRightQuarterA(0U, 0U);
                mMatrixA.RotateLeftEachSixteenthQuarterB(0U, 0U);
                aKindA = aOperationLaneA[(aIndex + 24U)];
                mMatrixA.Store(aWorkLaneB + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
                mMatrixB.FlipHorizontalBlocks(0U, 0U);
                mMatrixB.TransposeMainDiagonalQuarterD(0U, 0U);
                aArgB = aOperationLaneA[(aIndex + 25U)];
                mMatrixB.ReverseColOdd(aArgB, 0U);
                aKindB = aOperationLaneA[(aIndex + 26U)];
                mMatrixB.Store(aWorkLaneD + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
                break;
            }
            case 1U: {
                mMatrixA.LoadAndReset(aExpandLaneA + aIndex);
                mMatrixB.LoadAndReset(aExpandLaneC + aWalker);
                mMatrixA.TransposeAntiDiagonalEachSixteenthEachQuarter(0U, 0U);
                mMatrixA.FlipVertical(0U, 0U);
                aArgA = aOperationLaneA[(aIndex + 21U)];
                aArgB = aOperationLaneA[(aIndex + 22U)];
                mMatrixA.SwapRowsOdd(aArgA, aArgB);
                aArgA = aOperationLaneA[(aIndex + 23U)];
                mMatrixA.ReverseRowEven(aArgA, 0U);
                mMatrixA.FlipHorizontalBlocks(0U, 0U);
                aKindA = aOperationLaneA[(aIndex + 24U)];
                mMatrixA.Store(aWorkLaneB + aIndex, TwistFastMatrixUnrollScheme::kC, aKindA);
                mMatrixB.PinwheelLeft(0U, 0U);
                aArgB = aOperationLaneA[(aIndex + 25U)];
                mMatrixB.ShiftRing8A(aArgB, 0U);
                mMatrixB.FlipVerticalEachSixteenthQuarterC(0U, 0U);
                aArgB = aOperationLaneA[(aIndex + 26U)];
                mMatrixB.ReverseColOdd(aArgB, 0U);
                mMatrixB.TransposeMainDiagonalBlocks(0U, 0U);
                aKindB = aOperationLaneA[(aIndex + 27U)];
                mMatrixB.Store(aWorkLaneD + aIndex, TwistFastMatrixUnrollScheme::kA, aKindB);
                break;
            }
        }
    }
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 8128U - aIndex;
        aPrism = aOperationLaneB[(aIndex + 20U)];
        switch (aPrism % 2U) {
            case 0U: {
                mMatrixA.LoadAndReset(aExpandLaneB + aWalker);
                mMatrixB.LoadAndReset(aExpandLaneD + aWalker);
                mMatrixA.TransposeMainDiagonalBlocks(0U, 0U);
                mMatrixA.RotateLeftEachSixteenthQuarterD(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 21U)];
                aArgB = aOperationLaneB[(aIndex + 22U)];
                mMatrixA.SwapColsEven(aArgA, aArgB);
                aKindA = aOperationLaneB[(aIndex + 23U)];
                mMatrixA.Store(aWorkLaneA + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
                mMatrixB.PinwheelLeft(0U, 0U);
                mMatrixB.TransposeAntiDiagonalEachSixteenthQuarterD(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 24U)];
                aArgB = aOperationLaneB[(aIndex + 25U)];
                mMatrixB.RotateRow(aArgA, aArgB);
                mMatrixB.FlipHorizontal(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 26U)];
                aArgB = aOperationLaneB[(aIndex + 27U)];
                mMatrixB.SwapRowsEven(aArgA, aArgB);
                aKindB = aOperationLaneB[(aIndex + 28U)];
                mMatrixB.Store(aWorkLaneC + aIndex, TwistFastMatrixUnrollScheme::kC, aKindB);
                break;
            }
            case 1U: {
                mMatrixA.LoadAndReset(aExpandLaneB + aWalker);
                mMatrixB.LoadAndReset(aExpandLaneD + aWalker);
                aArgA = aOperationLaneB[(aIndex + 21U)];
                mMatrixA.ShiftRing20C(aArgA, 0U);
                mMatrixA.FlipHorizontalQuarterC(0U, 0U);
                mMatrixA.TransposeAntiDiagonalQuarterD(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 22U)];
                aArgB = aOperationLaneB[(aIndex + 23U)];
                mMatrixA.SwapColsOdd(aArgA, aArgB);
                aKindA = aOperationLaneB[(aIndex + 24U)];
                mMatrixA.Store(aWorkLaneA + aIndex, TwistFastMatrixUnrollScheme::kD, aKindA);
                mMatrixB.PinwheelRight(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 25U)];
                aArgB = aOperationLaneB[(aIndex + 26U)];
                mMatrixB.SwapRowsOdd(aArgA, aArgB);
                mMatrixB.TransposeMainDiagonalEachSixteenthQuarterA(0U, 0U);
                aKindB = aOperationLaneB[(aIndex + 27U)];
                mMatrixB.Store(aWorkLaneC + aIndex, TwistFastMatrixUnrollScheme::kA, aKindB);
                break;
            }
        }
    }
    // phase: workers -> expansion [offset 40]
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 8128U - aIndex;
        aPrism = aOperationLaneB[(aIndex + 40U)];
        switch (aPrism % 2U) {
            case 0U: {
                mMatrixA.LoadAndReset(aWorkLaneA + aIndex);
                mMatrixB.LoadAndReset(aWorkLaneD + aWalker);
                mMatrixA.RotateLeftEachSixteenthQuarterB(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 41U)];
                mMatrixA.ShiftRing8B(aArgA, 0U);
                aArgA = aOperationLaneB[(aIndex + 42U)];
                aArgB = aOperationLaneB[(aIndex + 43U)];
                mMatrixA.SwapCols(aArgA, aArgB);
                mMatrixA.TransposeMainDiagonal(0U, 0U);
                mMatrixA.FlipVertical(0U, 0U);
                aKindA = aOperationLaneB[(aIndex + 44U)];
                mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
                mMatrixB.PinwheelRightQuarterA(0U, 0U);
                aArgB = aOperationLaneB[(aIndex + 45U)];
                mMatrixB.ReverseColOdd(aArgB, 0U);
                aArgB = aOperationLaneB[(aIndex + 46U)];
                mMatrixB.ReverseRowEven(aArgB, 0U);
                mMatrixB.PinwheelLeft(0U, 0U);
                aKindB = aOperationLaneB[(aIndex + 47U)];
                mMatrixB.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kD, aKindB);
                break;
            }
            case 1U: {
                mMatrixA.LoadAndReset(aWorkLaneA + aIndex);
                mMatrixB.LoadAndReset(aWorkLaneD + aWalker);
                aArgA = aOperationLaneB[(aIndex + 41U)];
                aArgB = aOperationLaneB[(aIndex + 42U)];
                mMatrixA.RotateCol(aArgA, aArgB);
                mMatrixA.RotateLeftSixteenthsQuarterA(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 43U)];
                mMatrixA.ReverseRow(aArgA, 0U);
                aKindA = aOperationLaneB[(aIndex + 44U)];
                mMatrixA.Store(aExpandLaneA + aIndex, TwistFastMatrixUnrollScheme::kC, aKindA);
                mMatrixB.TransposeMainDiagonalSixteenthsQuarterD(0U, 0U);
                aArgA = aOperationLaneB[(aIndex + 45U)];
                aArgB = aOperationLaneB[(aIndex + 46U)];
                mMatrixB.SwapRowsEven(aArgA, aArgB);
                aArgB = aOperationLaneB[(aIndex + 47U)];
                mMatrixB.ReverseColEven(aArgB, 0U);
                mMatrixB.RotateRightBlocks(0U, 0U);
                aKindB = aOperationLaneB[(aIndex + 48U)];
                mMatrixB.Store(aExpandLaneC + aIndex, TwistFastMatrixUnrollScheme::kA, aKindB);
                break;
            }
        }
    }
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 64U) {
        aWalker = 8128U - aIndex;
        aPrism = aOperationLaneA[(aIndex + 40U)];
        switch (aPrism % 2U) {
            case 0U: {
                mMatrixA.LoadAndReset(aWorkLaneB + aIndex);
                mMatrixB.LoadAndReset(aWorkLaneC + aIndex);
                aArgA = aOperationLaneA[(aIndex + 41U)];
                aArgB = aOperationLaneA[(aIndex + 42U)];
                mMatrixA.SwapRowsEven(aArgA, aArgB);
                aArgA = aOperationLaneA[(aIndex + 43U)];
                mMatrixA.ReverseColOdd(aArgA, 0U);
                aArgA = aOperationLaneA[(aIndex + 44U)];
                mMatrixA.ShiftRing20B(aArgA, 0U);
                mMatrixA.PinwheelLeft(0U, 0U);
                mMatrixA.RotateLeftBlocks(0U, 0U);
                aKindA = aOperationLaneA[(aIndex + 45U)];
                mMatrixA.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kB, aKindA);
                mMatrixB.RotateLeftEachSixteenthQuarterD(0U, 0U);
                mMatrixB.FlipHorizontalEachSixteenthQuarterB(0U, 0U);
                mMatrixB.TransposeAntiDiagonal(0U, 0U);
                mMatrixB.TransposeMainDiagonalSixteenthsQuarterB(0U, 0U);
                aArgA = aOperationLaneA[(aIndex + 46U)];
                aArgB = aOperationLaneA[(aIndex + 47U)];
                mMatrixB.SwapCols(aArgA, aArgB);
                aKindB = aOperationLaneA[(aIndex + 48U)];
                mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kC, aKindB);
                break;
            }
            case 1U: {
                mMatrixA.LoadAndReset(aWorkLaneB + aIndex);
                mMatrixB.LoadAndReset(aWorkLaneC + aIndex);
                aArgA = aOperationLaneA[(aIndex + 41U)];
                aArgB = aOperationLaneA[(aIndex + 42U)];
                mMatrixA.SwapSixteenths(aArgA, aArgB);
                mMatrixA.FlipVerticalSixteenthsQuarterC(0U, 0U);
                aArgA = aOperationLaneA[(aIndex + 43U)];
                mMatrixA.ReverseRow(aArgA, 0U);
                aKindA = aOperationLaneA[(aIndex + 44U)];
                mMatrixA.Store(aExpandLaneB + aIndex, TwistFastMatrixUnrollScheme::kD, aKindA);
                aArgA = aOperationLaneA[(aIndex + 45U)];
                aArgB = aOperationLaneA[(aIndex + 46U)];
                mMatrixB.SwapColsEven(aArgA, aArgB);
                mMatrixB.FlipHorizontalBlocks(0U, 0U);
                aArgA = aOperationLaneA[(aIndex + 47U)];
                aArgB = aOperationLaneA[(aIndex + 48U)];
                mMatrixB.SwapRows(aArgA, aArgB);
                mMatrixB.TransposeMainDiagonalQuarterB(0U, 0U);
                aKindB = aOperationLaneA[(aIndex + 49U)];
                mMatrixB.Store(aExpandLaneD + aIndex, TwistFastMatrixUnrollScheme::kA, aKindB);
                break;
            }
        }
    }

}

void TwistExpander_Gollum::TwistBlock(TwistWorkSpace *pWorkspace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkspace, pSource, pDestination);
    if ((pWorkspace == nullptr) || (pDestination == nullptr)) { return; }
    std::memcpy(pDestination, pWorkspace->mWorkLaneD, S_BLOCK);
}

const std::uint8_t TwistExpander_Gollum::kSBoxA[S_SBOX] = {
    0x3C, 0x90, 0x9B, 0x87, 0x75, 0x71, 0x20, 0xD7, 0x51, 0x56, 0x6D, 0xAC, 0x69, 0xD5, 0xA1, 0x29, 
    0x8D, 0x1D, 0xCB, 0x22, 0x38, 0x30, 0x2E, 0x81, 0x04, 0x93, 0x5E, 0xF0, 0x03, 0xFB, 0x78, 0x34, 
    0x4B, 0x2F, 0x59, 0x02, 0xF4, 0x0B, 0x96, 0x28, 0x00, 0x49, 0x94, 0x33, 0x3E, 0x8F, 0xE3, 0xF1, 
    0xB5, 0x23, 0xE1, 0x72, 0x5F, 0xBA, 0x07, 0xA6, 0xF3, 0xE6, 0xE9, 0x83, 0x7C, 0xB0, 0xA8, 0x6F, 
    0x1B, 0xAF, 0xBB, 0xAB, 0x19, 0x92, 0x76, 0xAA, 0x3B, 0x5A, 0x67, 0x1A, 0x58, 0x31, 0xFD, 0xB8, 
    0x89, 0x70, 0xE4, 0xD9, 0xA7, 0x9D, 0xEE, 0xC4, 0xC3, 0x3F, 0xB4, 0xAE, 0x80, 0x25, 0x82, 0x6E, 
    0xC2, 0x2D, 0x13, 0x8A, 0x7F, 0x97, 0x17, 0x0A, 0xDA, 0x7E, 0x10, 0xD6, 0xCF, 0x4D, 0x45, 0xE7, 
    0x7D, 0xEC, 0x39, 0xB3, 0xEB, 0xB1, 0x1C, 0x62, 0x40, 0xF9, 0x7B, 0x15, 0x12, 0xDB, 0xC7, 0x36, 
    0x9A, 0xF8, 0x54, 0x6B, 0x95, 0x08, 0x68, 0x05, 0x65, 0xBD, 0x64, 0xFF, 0x2B, 0x61, 0xED, 0xCA, 
    0x7A, 0x5B, 0x63, 0xDE, 0x53, 0x1E, 0x1F, 0xA4, 0x9C, 0x9F, 0x11, 0x43, 0x2A, 0x27, 0xEF, 0xC9, 
    0x77, 0xA5, 0xE8, 0x5D, 0xC6, 0x41, 0xF6, 0xD3, 0xC0, 0x84, 0xB6, 0x8E, 0xAD, 0xFC, 0x26, 0x73, 
    0x60, 0x79, 0x46, 0xD4, 0x47, 0x21, 0xD1, 0x55, 0x66, 0x6A, 0xD0, 0xCE, 0x99, 0x35, 0x42, 0xA9, 
    0xE5, 0xC1, 0x44, 0x4F, 0x0E, 0x0F, 0x0D, 0x91, 0x3A, 0x6C, 0xDD, 0x48, 0x32, 0xF2, 0xE2, 0x50, 
    0x8C, 0xB9, 0xBF, 0xDF, 0x74, 0xA2, 0x24, 0x0C, 0xC8, 0xB2, 0xD8, 0xA3, 0x4C, 0x86, 0xBC, 0xF7, 
    0xC5, 0xCC, 0x52, 0xA0, 0x85, 0x3D, 0x01, 0x4E, 0x14, 0xFA, 0xFE, 0x88, 0xDC, 0x2C, 0xEA, 0x98, 
    0xF5, 0x18, 0x16, 0x4A, 0x06, 0xD2, 0xCD, 0x37, 0x8B, 0xE0, 0x09, 0xBE, 0x5C, 0x9E, 0x57, 0xB7
};

const std::uint8_t TwistExpander_Gollum::kSBoxB[S_SBOX] = {
    0x44, 0x82, 0x2E, 0xCC, 0x34, 0x77, 0xA6, 0xBD, 0x97, 0xB9, 0x95, 0x80, 0xD6, 0x70, 0xA2, 0xC7, 
    0xC0, 0x04, 0x5F, 0x6B, 0x07, 0xC6, 0xE9, 0x42, 0x05, 0xEF, 0x78, 0x73, 0x2B, 0xDF, 0x16, 0x85, 
    0xFB, 0x49, 0x56, 0x8B, 0x30, 0xEA, 0x0C, 0x67, 0x46, 0x36, 0xC1, 0xAB, 0x89, 0x0D, 0x7E, 0xD3, 
    0x81, 0xCB, 0xB3, 0x1A, 0xD8, 0x6E, 0x68, 0x8C, 0x1E, 0x9D, 0x72, 0x8F, 0x55, 0x62, 0xC3, 0x58, 
    0x8A, 0xED, 0xCE, 0xAE, 0x47, 0x4F, 0x59, 0x0E, 0x6A, 0x3B, 0x99, 0x2A, 0xF6, 0x66, 0x51, 0xA3, 
    0x83, 0xD7, 0x50, 0xF2, 0x2C, 0xA0, 0x5C, 0xB0, 0x9E, 0x29, 0x21, 0x4D, 0xE2, 0x45, 0x2F, 0xF8, 
    0x3E, 0x84, 0x4B, 0xEE, 0x38, 0xAC, 0x08, 0x4A, 0x9F, 0x98, 0x26, 0x1D, 0x1C, 0x75, 0xB4, 0x3D, 
    0xF5, 0x91, 0xA7, 0x0F, 0xBF, 0xC2, 0xA4, 0x7A, 0x57, 0x12, 0x7B, 0xC5, 0xEB, 0x3F, 0xDD, 0x48, 
    0x8E, 0xB2, 0x74, 0x1B, 0x61, 0x87, 0x76, 0xA5, 0x54, 0x40, 0xF4, 0x9C, 0x0A, 0x17, 0x31, 0xFF, 
    0xDB, 0x9B, 0xDA, 0xDC, 0x5A, 0x69, 0xC9, 0x41, 0x00, 0x6D, 0x86, 0x3A, 0xAA, 0x88, 0xFC, 0x92, 
    0xF9, 0xE1, 0xD2, 0x15, 0x7D, 0xF7, 0xFD, 0xFE, 0xF3, 0xA1, 0xEC, 0xAD, 0x20, 0xF1, 0x28, 0xBA, 
    0xB7, 0xB6, 0xD9, 0xD0, 0x79, 0x06, 0x33, 0xD4, 0x39, 0xBB, 0x93, 0xBC, 0xE3, 0x25, 0x9A, 0x63, 
    0xF0, 0x53, 0x14, 0xB8, 0x09, 0xA9, 0x64, 0x22, 0xCA, 0x35, 0xB1, 0x96, 0x0B, 0xBE, 0xDE, 0x37, 
    0x60, 0x03, 0x8D, 0x7C, 0x94, 0xCF, 0xE5, 0xC4, 0x32, 0xAF, 0x52, 0x6F, 0xD5, 0x6C, 0xE0, 0x5D, 
    0x10, 0x71, 0xFA, 0x02, 0x01, 0xE4, 0xE6, 0x18, 0x65, 0x7F, 0x3C, 0x23, 0x11, 0x24, 0x1F, 0x43, 
    0x90, 0xE7, 0xA8, 0x5B, 0xC8, 0x5E, 0xD1, 0xE8, 0x4E, 0x13, 0x27, 0x2D, 0xB5, 0xCD, 0x19, 0x4C
};

const std::uint8_t TwistExpander_Gollum::kSBoxC[S_SBOX] = {
    0xC0, 0xB5, 0xFA, 0x40, 0xDE, 0x0E, 0x7A, 0x19, 0x3F, 0x5B, 0xB4, 0x3E, 0x64, 0x80, 0x38, 0xAC, 
    0x22, 0xDC, 0xA3, 0xE3, 0x10, 0xEB, 0xC8, 0x09, 0x9B, 0x01, 0xA0, 0x4C, 0xFF, 0x03, 0xD8, 0x3B, 
    0xCC, 0xE5, 0xC4, 0xD2, 0x9C, 0x04, 0xFC, 0x81, 0x4B, 0x55, 0x65, 0x5F, 0x59, 0xBB, 0x69, 0x61, 
    0x79, 0xCE, 0xF0, 0xBA, 0x8D, 0xE6, 0x2F, 0x5C, 0xF8, 0x94, 0x0B, 0x90, 0x08, 0x84, 0xEE, 0x2D, 
    0x95, 0x8A, 0xCB, 0x5A, 0x0C, 0x2C, 0x6A, 0x77, 0xA4, 0x70, 0xD6, 0xB8, 0xE9, 0xC6, 0x4A, 0x7F, 
    0xF2, 0x23, 0x0D, 0xAB, 0x71, 0xB3, 0x6F, 0x3C, 0x58, 0x74, 0x54, 0xA7, 0x24, 0x87, 0xBD, 0x00, 
    0x75, 0x7C, 0x6E, 0x46, 0xBC, 0xD1, 0xBE, 0x29, 0x1F, 0x91, 0xDA, 0x34, 0x73, 0x85, 0x7E, 0xB9, 
    0x25, 0xF6, 0x3D, 0x30, 0x92, 0xA9, 0xF1, 0x2B, 0x83, 0x9A, 0x6C, 0x27, 0x43, 0x32, 0x88, 0xA2, 
    0xD7, 0xB7, 0xC2, 0xFD, 0x48, 0xB0, 0x49, 0xB6, 0x4F, 0x82, 0x62, 0xD3, 0x35, 0x9F, 0xDB, 0x8E, 
    0x41, 0x5D, 0x06, 0xCF, 0xA6, 0x68, 0x45, 0xC5, 0x9E, 0x2A, 0xF7, 0x37, 0x18, 0x1E, 0x42, 0x3A, 
    0x47, 0xE8, 0x26, 0x14, 0xA5, 0xAE, 0x05, 0xC9, 0xEC, 0xF4, 0xCD, 0x96, 0x13, 0x67, 0x33, 0x97, 
    0xB2, 0xF5, 0xCA, 0xAD, 0xE7, 0x57, 0x50, 0xEF, 0xFB, 0xD0, 0x7D, 0x5E, 0x63, 0x16, 0x1A, 0xC3, 
    0x20, 0xC1, 0x53, 0x1C, 0xF9, 0xD4, 0x4D, 0x98, 0x89, 0x99, 0x7B, 0x78, 0x72, 0xD5, 0x44, 0x12, 
    0x0F, 0x52, 0x1B, 0xE2, 0xF3, 0x8C, 0xAA, 0x60, 0x17, 0x1D, 0x86, 0xA1, 0xA8, 0x6D, 0xAF, 0x28, 
    0x11, 0xC7, 0x8B, 0x15, 0xD9, 0xED, 0x66, 0x31, 0x0A, 0x2E, 0xFE, 0xDF, 0x56, 0x51, 0xBF, 0x4E, 
    0xB1, 0x21, 0x93, 0xE1, 0x02, 0xE4, 0xEA, 0x8F, 0x6B, 0xDD, 0x9D, 0x36, 0x39, 0x07, 0x76, 0xE0
};

const std::uint8_t TwistExpander_Gollum::kSBoxD[S_SBOX] = {
    0x4B, 0x55, 0x21, 0xEB, 0xA6, 0xDF, 0x81, 0x52, 0x74, 0xA2, 0x15, 0x34, 0x6C, 0x1A, 0x71, 0xBD, 
    0x78, 0x07, 0x98, 0xC9, 0x32, 0xE9, 0x6B, 0xDA, 0x53, 0xFA, 0x79, 0x2F, 0x85, 0x5B, 0xE3, 0x90, 
    0x8F, 0x8C, 0xAF, 0x62, 0x56, 0x5E, 0x64, 0x5A, 0x2A, 0xC7, 0x2C, 0x46, 0x03, 0x30, 0xE8, 0xC8, 
    0x60, 0x2E, 0xA0, 0x70, 0x9E, 0x6D, 0xFC, 0xA7, 0x80, 0x76, 0x7B, 0x92, 0x9A, 0xFE, 0x4D, 0x5D, 
    0x36, 0x9B, 0x8A, 0xE2, 0x7E, 0x1D, 0x09, 0x05, 0x9D, 0x00, 0x86, 0xD1, 0x48, 0x0E, 0x6A, 0x25, 
    0x01, 0x38, 0x3E, 0xB8, 0x40, 0x10, 0xAD, 0x95, 0x43, 0xE4, 0x87, 0x7C, 0x3D, 0x1F, 0x75, 0xBA, 
    0xA4, 0xC4, 0xED, 0xAE, 0x35, 0x83, 0x94, 0xB9, 0x17, 0xD2, 0x42, 0xB5, 0xE1, 0xBE, 0x65, 0x91, 
    0x7D, 0xE5, 0xD5, 0x51, 0x33, 0x19, 0xE0, 0x18, 0xFB, 0x13, 0x4C, 0xDC, 0x0A, 0xF0, 0x3A, 0xD8, 
    0xC6, 0xF4, 0xEA, 0x24, 0xCB, 0xF1, 0x8B, 0xB4, 0xCE, 0xBB, 0x29, 0x22, 0xF5, 0xB7, 0x02, 0x7F, 
    0xAB, 0xE7, 0xFF, 0x6E, 0x3C, 0xA8, 0x4F, 0xEF, 0xF7, 0x58, 0xA5, 0x54, 0x12, 0x57, 0x4A, 0xD0, 
    0xEE, 0x08, 0x9C, 0xD6, 0xDD, 0x1C, 0x1E, 0x2B, 0xEC, 0x44, 0xCF, 0xD7, 0xD3, 0x8D, 0xB0, 0x97, 
    0x50, 0x04, 0xCA, 0xFD, 0x2D, 0x66, 0x63, 0x0D, 0x61, 0xC3, 0x84, 0x06, 0x69, 0x77, 0xB3, 0xAA, 
    0xD9, 0x0B, 0x82, 0xF6, 0xC0, 0x27, 0x6F, 0xB2, 0x7A, 0xF2, 0xC1, 0x20, 0xA1, 0x67, 0x0F, 0x93, 
    0x9F, 0xC2, 0xF3, 0x89, 0x41, 0xDE, 0xF8, 0x88, 0x37, 0xB6, 0x5F, 0x39, 0x59, 0x0C, 0x5C, 0xF9, 
    0x72, 0x4E, 0xDB, 0x96, 0xA3, 0xAC, 0xCD, 0x11, 0x3B, 0xBC, 0xC5, 0xE6, 0x26, 0x23, 0xD4, 0x8E, 
    0xB1, 0x99, 0x73, 0x68, 0x1B, 0xCC, 0xA9, 0x3F, 0x49, 0x47, 0x16, 0x14, 0x31, 0xBF, 0x45, 0x28
};

const std::uint8_t TwistExpander_Gollum::kSBoxE[S_SBOX] = {
    0x4C, 0xB9, 0xA4, 0x8C, 0xF2, 0x77, 0x64, 0xC1, 0xA8, 0x52, 0x5F, 0x4E, 0xDA, 0xE0, 0xF7, 0x58, 
    0xCF, 0xCD, 0xE9, 0x45, 0xC9, 0xAB, 0xA2, 0x28, 0x3E, 0xC6, 0x30, 0xE4, 0xC4, 0xF9, 0x4B, 0x2E, 
    0x24, 0xFC, 0xCA, 0x9A, 0x61, 0xA6, 0x1D, 0x06, 0xBB, 0x05, 0x3C, 0xD4, 0x6D, 0xEE, 0x54, 0xBA, 
    0xBD, 0x1B, 0x75, 0x08, 0x6E, 0x25, 0x41, 0x0D, 0x9B, 0x8F, 0x17, 0x09, 0xCE, 0x66, 0xCB, 0x7E, 
    0x69, 0x31, 0x7B, 0xB4, 0x48, 0x98, 0x8D, 0xEA, 0xB6, 0xB5, 0x1C, 0x37, 0x94, 0xF5, 0x5D, 0x04, 
    0x4A, 0x29, 0xAE, 0x07, 0x53, 0x00, 0xED, 0x71, 0x8B, 0x33, 0xE3, 0x6F, 0x76, 0xBF, 0x57, 0x20, 
    0xD5, 0xDD, 0x0B, 0x35, 0xB1, 0x43, 0x8E, 0xF8, 0x78, 0xEF, 0x74, 0x9F, 0x6C, 0x80, 0xE2, 0xD1, 
    0x90, 0xCC, 0x97, 0x19, 0x36, 0x38, 0x93, 0xC7, 0x39, 0xD8, 0x34, 0xAF, 0x55, 0x26, 0x0E, 0x0F, 
    0xFA, 0x86, 0x73, 0xFB, 0x62, 0xD9, 0x84, 0x60, 0x3D, 0xDF, 0x63, 0x7C, 0x79, 0xB8, 0x92, 0xB7, 
    0x6A, 0xEB, 0x99, 0xFD, 0x89, 0xB2, 0xEC, 0x2C, 0x5E, 0x21, 0x2A, 0x46, 0x27, 0x9E, 0xB3, 0xC8, 
    0xD3, 0x72, 0x49, 0x4F, 0x50, 0x67, 0x40, 0x44, 0xF4, 0xF3, 0xC2, 0xB0, 0x10, 0x03, 0xC0, 0x56, 
    0xE6, 0x15, 0x9D, 0xBE, 0xC3, 0x3A, 0x65, 0x2D, 0x42, 0xA5, 0x3B, 0x32, 0x85, 0x70, 0x18, 0x95, 
    0xF0, 0xAA, 0xBC, 0xA1, 0x7D, 0x23, 0x02, 0xE7, 0xE8, 0x01, 0x82, 0x5B, 0x8A, 0xC5, 0x0A, 0xF6, 
    0x91, 0x5A, 0xFE, 0xA3, 0xAC, 0x88, 0xE1, 0x5C, 0x96, 0x47, 0x59, 0xD6, 0xDE, 0xD2, 0x81, 0x1E, 
    0x2F, 0x13, 0xD7, 0xA9, 0xAD, 0x12, 0xE5, 0xFF, 0xF1, 0xA7, 0x22, 0x14, 0xDC, 0x83, 0x68, 0xDB, 
    0x3F, 0x16, 0xD0, 0x7A, 0x1F, 0x1A, 0x4D, 0x51, 0x6B, 0x2B, 0x87, 0xA0, 0x11, 0x7F, 0x0C, 0x9C
};

const std::uint8_t TwistExpander_Gollum::kSBoxF[S_SBOX] = {
    0x14, 0x27, 0x18, 0x13, 0xD7, 0xEC, 0x1F, 0xAB, 0xAE, 0xFB, 0xE7, 0x6E, 0xDC, 0x8E, 0x4F, 0x05, 
    0x67, 0x1D, 0xA0, 0x3A, 0x2F, 0x7E, 0x50, 0x0D, 0x66, 0x49, 0xAA, 0xBC, 0x33, 0x83, 0xF6, 0x45, 
    0xBB, 0x1B, 0xFF, 0x78, 0x87, 0x62, 0x39, 0x4E, 0x5D, 0x9E, 0x1C, 0x10, 0x31, 0x42, 0xB3, 0xF7, 
    0x15, 0x71, 0x96, 0x82, 0xE1, 0x11, 0x08, 0x1A, 0xD2, 0xC3, 0xC7, 0x28, 0xCD, 0x65, 0x55, 0xC2, 
    0x03, 0x00, 0x5A, 0x3B, 0x26, 0x02, 0xB9, 0x70, 0x41, 0x91, 0x93, 0x48, 0xB4, 0x35, 0x9D, 0x34, 
    0x5C, 0xA7, 0xE6, 0xE4, 0x51, 0x06, 0x92, 0xA4, 0xF1, 0x7A, 0x5E, 0x4B, 0x46, 0x6F, 0x63, 0x89, 
    0xBA, 0x3E, 0x52, 0x32, 0xA3, 0x72, 0x69, 0x29, 0x8A, 0xE8, 0x3C, 0xE0, 0x9B, 0xA5, 0xF4, 0x88, 
    0x86, 0xB7, 0x64, 0x0B, 0xE2, 0x2E, 0x56, 0xE3, 0x84, 0xA6, 0x98, 0x4C, 0x19, 0xC1, 0xCA, 0x60, 
    0x53, 0xED, 0xDE, 0xF9, 0x57, 0x0C, 0x97, 0x2D, 0xB6, 0x44, 0xFD, 0xB8, 0x20, 0x8D, 0xFC, 0xEB, 
    0xD3, 0xDA, 0xA8, 0xB1, 0x8B, 0x73, 0x38, 0x3F, 0x4D, 0x23, 0x77, 0xEA, 0x6B, 0x4A, 0xD9, 0x85, 
    0xF2, 0x74, 0x8C, 0xC4, 0x81, 0xCF, 0xA2, 0x90, 0x9F, 0x7D, 0x7B, 0x09, 0x25, 0xD6, 0x01, 0xC9, 
    0xC6, 0xBD, 0x9A, 0xC5, 0xD1, 0x54, 0xB5, 0x95, 0xD8, 0xB2, 0xFE, 0xD0, 0x3D, 0x0E, 0xA1, 0x1E, 
    0xAD, 0xD4, 0xBF, 0x80, 0x12, 0x59, 0x7C, 0x6C, 0x0A, 0xAC, 0xDF, 0xD5, 0x5B, 0x99, 0xF8, 0xE5, 
    0x2C, 0x7F, 0x61, 0xFA, 0x9C, 0x21, 0x24, 0x37, 0xCE, 0x40, 0xAF, 0x6A, 0xEE, 0x58, 0x0F, 0xE9, 
    0xEF, 0xF5, 0xC0, 0x04, 0x36, 0x5F, 0x16, 0xCB, 0x07, 0xC8, 0xF3, 0x17, 0x94, 0x75, 0xA9, 0x76, 
    0xCC, 0x6D, 0x22, 0xF0, 0x43, 0xDB, 0xBE, 0x2B, 0x79, 0xDD, 0x47, 0x2A, 0x8F, 0x68, 0xB0, 0x30
};

const std::uint8_t TwistExpander_Gollum::kSBoxG[S_SBOX] = {
    0x44, 0x17, 0xA0, 0x85, 0x68, 0x03, 0x61, 0xEF, 0x66, 0x9C, 0x26, 0x57, 0x4D, 0x76, 0x12, 0x4F, 
    0x3A, 0x29, 0xCA, 0xF8, 0x2F, 0x09, 0xB5, 0x77, 0x6F, 0x86, 0xBA, 0x70, 0x95, 0xC7, 0x2D, 0x62, 
    0xB1, 0xBD, 0x40, 0x9D, 0x1B, 0xB3, 0xE5, 0x47, 0x04, 0x28, 0x7C, 0x98, 0xDD, 0xA3, 0x89, 0x78, 
    0x11, 0xF0, 0x10, 0x92, 0xB2, 0xCD, 0xFE, 0xE8, 0xE1, 0xEA, 0x36, 0xEE, 0x46, 0x72, 0x3C, 0xBF, 
    0xDB, 0xC6, 0xC5, 0xAD, 0x42, 0x8E, 0xF9, 0xA5, 0xBE, 0xD1, 0x99, 0xD3, 0x48, 0x01, 0x35, 0x54, 
    0x51, 0x0B, 0x73, 0x3B, 0xE0, 0x52, 0xCC, 0x16, 0xEC, 0xD5, 0x19, 0xCE, 0x7F, 0x02, 0xE6, 0xB7, 
    0xE4, 0x24, 0xFD, 0xC0, 0xD7, 0xED, 0x96, 0xBB, 0xAA, 0xDF, 0x6C, 0xE7, 0xA1, 0x43, 0x65, 0xE2, 
    0x4E, 0x55, 0x27, 0xE3, 0xAF, 0x7A, 0x21, 0xFA, 0x06, 0x5E, 0xBC, 0x0F, 0xF5, 0xA2, 0x87, 0xFB, 
    0xA8, 0x56, 0x05, 0xD4, 0x74, 0x22, 0x45, 0x67, 0x00, 0x37, 0x08, 0xAC, 0xD6, 0x6B, 0x5D, 0xC2, 
    0xB4, 0xD9, 0xF2, 0xC1, 0xFF, 0xB8, 0xB0, 0x71, 0x5A, 0xCB, 0x64, 0x97, 0xDE, 0x9B, 0xC4, 0x53, 
    0xF1, 0x79, 0x3E, 0x2B, 0x8F, 0x0E, 0x82, 0x84, 0x7D, 0x14, 0x80, 0xAB, 0x5F, 0x3D, 0x93, 0x9A, 
    0x63, 0x25, 0xF4, 0x7E, 0xFC, 0x69, 0x1D, 0x0D, 0x91, 0xDC, 0x15, 0xA9, 0x39, 0x6A, 0x9F, 0x34, 
    0x7B, 0x75, 0x6D, 0xDA, 0xD0, 0xD8, 0x41, 0x1F, 0xB6, 0x2E, 0x50, 0x20, 0x90, 0xE9, 0x81, 0x6E, 
    0x32, 0x5C, 0xAE, 0xC9, 0x60, 0x83, 0x0A, 0x49, 0x5B, 0xEB, 0x33, 0x8B, 0x4B, 0x8D, 0x3F, 0x8A, 
    0x1E, 0x30, 0xF7, 0x1A, 0x1C, 0x4C, 0x0C, 0xD2, 0x07, 0xCF, 0xA4, 0x59, 0x58, 0x2C, 0xA7, 0x31, 
    0x13, 0x4A, 0x9E, 0xB9, 0xF6, 0x8C, 0x38, 0xF3, 0xC8, 0x18, 0x2A, 0xA6, 0x23, 0xC3, 0x94, 0x88
};

const std::uint8_t TwistExpander_Gollum::kSBoxH[S_SBOX] = {
    0xB5, 0x3B, 0xEF, 0x6D, 0x26, 0x4A, 0x37, 0x53, 0x0B, 0x0E, 0xC8, 0xF8, 0xA4, 0x79, 0x6A, 0xC9, 
    0xFA, 0xB7, 0xD1, 0x1D, 0xD9, 0x64, 0xCC, 0x2B, 0x1A, 0x52, 0xB3, 0x17, 0x1F, 0xC3, 0xB4, 0x08, 
    0xCF, 0x8F, 0xB6, 0x5C, 0x7B, 0xA2, 0x7D, 0x8A, 0x76, 0xE5, 0x57, 0x0D, 0x9F, 0xD0, 0x2D, 0x54, 
    0x55, 0x5E, 0x07, 0x23, 0xF0, 0xED, 0x73, 0x6F, 0x7E, 0x02, 0xBA, 0x01, 0xD8, 0x7A, 0x94, 0xE2, 
    0xF1, 0x91, 0xAE, 0xFD, 0xDB, 0x11, 0x4F, 0xBE, 0xB0, 0xDF, 0x5F, 0xB2, 0xF5, 0x27, 0x85, 0xC7, 
    0x96, 0x09, 0x28, 0xA8, 0x2C, 0xA9, 0xBF, 0x69, 0x6C, 0xDC, 0x16, 0xD2, 0x68, 0x18, 0x42, 0xA1, 
    0x2F, 0xA5, 0x4C, 0xFF, 0xB1, 0x3E, 0x20, 0xE1, 0xC1, 0xF2, 0x25, 0x10, 0xBD, 0x89, 0x34, 0x41, 
    0x9B, 0x95, 0x9A, 0x13, 0x90, 0x39, 0xF4, 0x70, 0x1B, 0xE9, 0xDD, 0x0A, 0x0F, 0x82, 0x00, 0x22, 
    0xAC, 0xAA, 0x24, 0x8E, 0x14, 0xCB, 0xE7, 0x59, 0x75, 0xE8, 0x36, 0xAF, 0xE3, 0x19, 0xD6, 0x92, 
    0x9E, 0x9C, 0x33, 0xAD, 0x21, 0xDE, 0x9D, 0x45, 0xEA, 0x83, 0x66, 0x72, 0xA0, 0x32, 0xFC, 0xFB, 
    0x0C, 0x06, 0xF9, 0xDA, 0x43, 0x58, 0x51, 0x3F, 0x05, 0x04, 0x3C, 0x93, 0xBB, 0xC6, 0x71, 0x60, 
    0x5A, 0xF7, 0x5D, 0x3A, 0x1E, 0x74, 0x15, 0x67, 0x1C, 0xCD, 0x56, 0xFE, 0xC5, 0x4B, 0x31, 0xD7, 
    0x6B, 0x46, 0x77, 0xA3, 0x8D, 0xCE, 0xE4, 0x78, 0xF3, 0x8B, 0xC4, 0xA6, 0x4E, 0x3D, 0x6E, 0x48, 
    0xB9, 0x84, 0xC2, 0xEE, 0x65, 0x03, 0x5B, 0xA7, 0xB8, 0x50, 0xEB, 0x40, 0xCA, 0x2E, 0xAB, 0x12, 
    0x2A, 0xD4, 0x62, 0x29, 0x47, 0xF6, 0x35, 0xE0, 0x49, 0x80, 0xEC, 0xD5, 0x87, 0xE6, 0xD3, 0x86, 
    0x38, 0x98, 0x63, 0x8C, 0x30, 0x7C, 0x97, 0x61, 0xBC, 0x44, 0x88, 0x81, 0x99, 0xC0, 0x4D, 0x7F
};

const std::uint64_t TwistExpander_Gollum::kSaltA[S_SALT] = {
    0x1AF4D6984AC31B2AULL, 0x5DC4E398453FCC0EULL, 0x68374FB62038A6CDULL, 0x57D92D6B4F1A4384ULL, 
    0x9F2E6110899B57CAULL, 0x1F74495FF1806C8FULL, 0x932601F0833CF0A1ULL, 0xF6031E5992984AFFULL, 
    0xF61A9BA01DAE98C0ULL, 0xC36A8731C267EAF9ULL, 0x4B73546D55D775BBULL, 0xDB5A0E8AC523839DULL, 
    0x24CCD27616C8B1CCULL, 0x6F13F898F79055DAULL, 0xC353C8FCD0D7724DULL, 0x8327540796D153ABULL, 
    0xE1566C9BB24450B7ULL, 0x3C5EF51766763FA7ULL, 0x9C39D0038E11C480ULL, 0x03F4E6EBE97682C4ULL, 
    0xFA37BDBE3B0597F8ULL, 0x2DA621C8DE19EEA3ULL, 0xC790E879241B2D1AULL, 0x29AA662A7D0B5B1DULL, 
    0x7A052D98907CBFBCULL, 0x1C3AEE0A98B9164CULL, 0xFC253D28754EAAE6ULL, 0xE17FDD8F1FA84384ULL, 
    0x8E5FB3B368E553BEULL, 0x1508190EAECBEEB5ULL, 0x2BD75DABEE2FD63FULL, 0x39A56A01BB03FC02ULL
};

const std::uint64_t TwistExpander_Gollum::kSaltB[S_SALT] = {
    0x20216FA495836C26ULL, 0x0F4D7BB8F73B606EULL, 0xD9DA66FC5A43E579ULL, 0x67D56D8C6AC876F7ULL, 
    0xBDE0929A104FF83CULL, 0x836A8AB8B6562760ULL, 0x471C34EABF1923A0ULL, 0x3D99402AE49C10B0ULL, 
    0x47A186C2764BC857ULL, 0x311BEAF1F84BC65DULL, 0xB1552DB965D58D53ULL, 0xCC10472200BFB531ULL, 
    0xC100E9D51927C38EULL, 0xCE3BA9A5D40949A1ULL, 0x7006F0775630EF19ULL, 0xEABB32CFBAC22851ULL, 
    0xBFC01FB48636A681ULL, 0x8E57E205CA8F4B17ULL, 0xE0DD810796628AB7ULL, 0x6158B2FE4EC0E0ABULL, 
    0xAFEAD0DE236E37B3ULL, 0xEC5E4256FB652EABULL, 0xD8A0454BAD05B436ULL, 0x527F7867EE39A0EDULL, 
    0xD5885540703337E3ULL, 0xA99D0625C3C166EAULL, 0x94F40E3E5751E0EAULL, 0x6ADF165E82E9AA9BULL, 
    0x4DEBD9AA551850D8ULL, 0xD7786613D31D78A0ULL, 0xF45EB6B253A83351ULL, 0x0CF81AFF976D61A7ULL
};

const std::uint64_t TwistExpander_Gollum::kSaltC[S_SALT] = {
    0xD364B46F9A1E749DULL, 0x3F284ADFCC598D87ULL, 0x00ABD6834FD31CA1ULL, 0x17E96AFF1542A561ULL, 
    0xE2FE35A19B978FEAULL, 0x48D2A17225C422FFULL, 0x218AE23BF2F482AAULL, 0xEBC4585CB8BA2096ULL, 
    0x045587AE92003C22ULL, 0xAF5ED255276B1293ULL, 0x05DD9458DD1BED54ULL, 0xDB1F036C10CE41FCULL, 
    0x40DECAFDE395F856ULL, 0xCE933B89C3845EC0ULL, 0x718A481FE3CD83FAULL, 0xB0A07F37F9AAE46DULL, 
    0x2BB3BDF7C1147D8CULL, 0x49607B85EF5B1016ULL, 0x958706DFFE4F935CULL, 0x41AB280FE9F69E06ULL, 
    0x6CD460C4E1C8C2D0ULL, 0x1ADC35E2AB45C7D2ULL, 0x1D0B95C5F9B4FCCCULL, 0x5C6C34F87A4C2E14ULL, 
    0x7D8AE0E7B47CE968ULL, 0xBF4061A5888C9D51ULL, 0x0F8564EF8DC74D6EULL, 0x784575A6111EF214ULL, 
    0xC11A406CF50272FAULL, 0x81BF5DE4579EBD73ULL, 0x8881268361377613ULL, 0x3DC9AD1BA136D815ULL
};

const std::uint64_t TwistExpander_Gollum::kSaltD[S_SALT] = {
    0x1E1B841AB14B7FFCULL, 0x95AA3F00BD9B6206ULL, 0x8D2B9F2F542D6C1BULL, 0xF765A15728D5B991ULL, 
    0x1B65D7AB5C1E6EB2ULL, 0x0BFD5D94868CA88BULL, 0xED118B5956E21EDBULL, 0xEFF48F9D6679B5EBULL, 
    0xF3D00BFA1D079EFBULL, 0x95B5E1912FBD4394ULL, 0xAE4F57762A653F93ULL, 0xF15B34CDF70DBBA6ULL, 
    0x0EA4793BB6FBED38ULL, 0x544E9401BAAD822BULL, 0x3D83A02861EC1691ULL, 0xAB7ECF14BEEEE15EULL, 
    0xFE4901B3A9E86F0AULL, 0x2662ECCFE413F3B7ULL, 0x2585F0BB0951E2B8ULL, 0xCF5606BD5BD360BFULL, 
    0xB1613F4BEC7C0AA5ULL, 0xB0A3C244087EDA17ULL, 0x0E8D0476EE521D86ULL, 0x3CD099ADF76B2E44ULL, 
    0x0E407931C1613E90ULL, 0x7E312A81BC10A8E8ULL, 0x8EBE5391CC52B757ULL, 0xA4A5EF551DA66A83ULL, 
    0xA471412552341C5EULL, 0x6A026BCE36EFF65EULL, 0x7A896E4F89DDEDC0ULL, 0x8EAE617236A4EABEULL
};

const std::uint64_t TwistExpander_Gollum::kSaltE[S_SALT] = {
    0x572DD5B3D8367E18ULL, 0x661FE9366A83AB66ULL, 0x83D5A98D6084FDF4ULL, 0xD3D6BA5099D03374ULL, 
    0xFC8F14E9C5E1ABC0ULL, 0x9B973951B844EC4BULL, 0x106910CE0E969F23ULL, 0xFA7DF55F32C99BC0ULL, 
    0xCB679286699F2127ULL, 0x44820E4568943865ULL, 0x23580FADA6948D2CULL, 0x0A9634932E4C5698ULL, 
    0xB12C29C5A2AB1B9BULL, 0x851939164C6A93A0ULL, 0xCFF309E2035C6A11ULL, 0x518AFD45699FE62EULL, 
    0xBF1C07375606378BULL, 0xF61DC970D217A6B5ULL, 0xC1C6B0C4C3CF8597ULL, 0xA650A5A3876FC660ULL, 
    0xF08BA6E027428313ULL, 0xE408F044AD6E62F9ULL, 0x9E1175619AA82FCDULL, 0x4214D2A07BB30925ULL, 
    0x922A9B460714E601ULL, 0x1499E17165485435ULL, 0x8E95191D708F2714ULL, 0x4F8B6F76E1C2E180ULL, 
    0x306A005FD747EFFDULL, 0x4C9B2B3427DF4E55ULL, 0xF281FE0475DD28C3ULL, 0x57B46EE9948F7B53ULL
};

const std::uint64_t TwistExpander_Gollum::kSaltF[S_SALT] = {
    0x0F75A4EEDD38744CULL, 0x21F145CB78DB383CULL, 0x6F368886FD69D5EBULL, 0x2885C0A5061EE6E1ULL, 
    0x75E1D506F5A7ADB5ULL, 0xAEBCA1EF5B740D06ULL, 0x45F52B55A7810172ULL, 0x39A182AFC2026E50ULL, 
    0x31243770E1A13F67ULL, 0x7D377F4DE9F7B671ULL, 0x68181B3EC193BE69ULL, 0xEF2FB6F95CBE457FULL, 
    0x594FA1D788DA9C62ULL, 0xD98437227025CD19ULL, 0xAF1CE183F104FF08ULL, 0x83194C3DF3AFDF88ULL, 
    0x12F9DE97E98D5AA9ULL, 0x1046F2290C8CD044ULL, 0xC6F9D6FFB4DDC33FULL, 0xA5759A9A52C06956ULL, 
    0x0AD3396744E902A7ULL, 0xDDE28F1FB1FE497DULL, 0xD8D863AEB2492CBFULL, 0xD673806C2CD8D897ULL, 
    0x46490C56B4B2423CULL, 0xDE34F2D2A30775AAULL, 0xB6527135D26102E0ULL, 0x690A1B025FA9DA5AULL, 
    0xA677FEB7691337BCULL, 0xA2C24C9927E2C877ULL, 0x84DBC669B8D39CBFULL, 0x1DD3F3C254387A16ULL
};

const std::uint64_t TwistExpander_Gollum::kSaltG[S_SALT] = {
    0xF06B67FEBBAD614DULL, 0x264D8E43888B39A0ULL, 0xCA8A649A50BDF637ULL, 0xF3DE393F76A560FBULL, 
    0xE944A14AD6FD4E8FULL, 0xB4EC770DAA0E6FB2ULL, 0x74293D3B29BDE871ULL, 0x174B963679997517ULL, 
    0x5BADB9F7FB180A25ULL, 0x25CCC709A7A0B6A3ULL, 0x4CDFA527CE75370AULL, 0x19AC837CB8D1DA40ULL, 
    0xFEB172B6B531DE38ULL, 0xDCC0F086510B1A8BULL, 0xEB34B6E753973809ULL, 0xDD46CF1550D58F3DULL, 
    0xCC26686376602B2AULL, 0x14C16E28F0802CDAULL, 0x6DBC4026E078BF42ULL, 0xE3F8E862B571C9D4ULL, 
    0x29E1E9D36CD6CB57ULL, 0x438A6B9BE79C57D9ULL, 0x515626C315C47D22ULL, 0x5F264E6C530282C8ULL, 
    0xB93D27C485DD7904ULL, 0x841B123FCA11EACDULL, 0xC06F977B4522489BULL, 0xDBDC08F31D6F39B4ULL, 
    0x02316E701FF79EF3ULL, 0x77077EDD36AECADDULL, 0x55F744FB3D2A646FULL, 0xEA7CDAECCFCCD2D7ULL
};

const std::uint64_t TwistExpander_Gollum::kSaltH[S_SALT] = {
    0x869A46047161610FULL, 0xF81C6BD166F8BB81ULL, 0xCE60BC630FB9475FULL, 0xBCD8C69BF44405BCULL, 
    0xBA1CCAE4AAB60C8BULL, 0xCC014EE1772FE20DULL, 0x5E67C8C40E68F7D7ULL, 0x77433C011B2FEE58ULL, 
    0xA66A711B5B95588FULL, 0x9A0CFEF47EEDD602ULL, 0xD53D13FEDE490378ULL, 0x9DB2E03A026A9067ULL, 
    0xCC8E5AD3CC7FF070ULL, 0x180EC378D836C79EULL, 0x85BFB0C2C12633D1ULL, 0x543A48D87A45E534ULL, 
    0x67FDEB01FB6E3046ULL, 0x4D2BE888015DE6B9ULL, 0xB913319BF9730E5BULL, 0xBF7F4AA5DA365487ULL, 
    0x99BFA1EC2A390760ULL, 0x486E7223C2C1E68FULL, 0x59A6B058D36D654EULL, 0x7A7EE82E68990221ULL, 
    0x12EBAA5C166BB7C7ULL, 0xFECB9959DD87E809ULL, 0xA74055419B69685EULL, 0x1B7DBEC7A37D81FDULL, 
    0xAA97EB2E2AFA3145ULL, 0xC37BB6179C192933ULL, 0xDF646C32B5FDEFACULL, 0x9BE7591DDEFCF267ULL
};
