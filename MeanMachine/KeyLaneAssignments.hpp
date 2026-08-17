#ifndef KeyLaneAssignments_hpp
#define KeyLaneAssignments_hpp

#include "TwistWorkSpace.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

namespace KeyLaneAssignments {

using Slot = TwistWorkSpaceSlot;

inline constexpr std::size_t kKeyFunctionCount = 16U;
inline constexpr std::size_t kActiveCandidateCount = 16U;
inline constexpr std::size_t kCandidateCount = 17U;

struct Assignment {
    Slot mLane;
    std::uint64_t mKeyOrder;
    std::uint64_t mSplitOrder;
};

// Each 64-bit word stores one shuffled permutation in sixteen nibbles. The
// active candidates cycle through the permutation as a Latin square. Thus, for
// every lane and key function, candidates 0-15 use all sixteen splits once;
// any two active candidates differ at every position.
//
// Members of a lane family were generated together. For every active candidate
// and logical key function, A/B/C/D select different sixteenths. Candidate 16
// deliberately maps every lane to split zero.
inline constexpr std::array<Assignment, 116U> kAssignments = {{
    { Slot::kEarthLaneA, 0xD67E235F8941BAC0ULL, 0xCD0B97E158632A4FULL },
    { Slot::kEarthLaneB, 0x7018CDF923EB546AULL, 0xCD0B97E158632A4FULL },
    { Slot::kEarthLaneC, 0xA34BF02C561E879DULL, 0xCD0B97E158632A4FULL },
    { Slot::kEarthLaneD, 0xE78F34609A52CBD1ULL, 0xCD0B97E158632A4FULL },
    { Slot::kFireLaneA, 0x2D8CE567019F3BA4ULL, 0xB42A198D0567EC3FULL },
    { Slot::kFireLaneB, 0xC7268F01AB39D54EULL, 0xB42A198D0567EC3FULL },
    { Slot::kFireLaneC, 0x3E9DF67812A04CB5ULL, 0xB42A198D0567EC3FULL },
    { Slot::kFireLaneD, 0x94F35CDE7806A21BULL, 0xB42A198D0567EC3FULL },
    { Slot::kWindLaneA, 0xE0B8AF3195D276C4ULL, 0xB4A76C85DF2E1930ULL },
    { Slot::kWindLaneB, 0x683027B91D5AFE4CULL, 0xB4A76C85DF2E1930ULL },
    { Slot::kWindLaneC, 0xF1C9B042A6E387D5ULL, 0xB4A76C85DF2E1930ULL },
    { Slot::kWindLaneD, 0x8A5249DB3F7C106EULL, 0xB4A76C85DF2E1930ULL },
    { Slot::kWaterLaneA, 0x14F7C03ABD96E258ULL, 0x05BFE389D621A7C4ULL },
    { Slot::kWaterLaneB, 0x7A5D269013FC48BEULL, 0x05BFE389D621A7C4ULL },
    { Slot::kWaterLaneC, 0xAD8059C3462F7BE1ULL, 0x05BFE389D621A7C4ULL },
    { Slot::kWaterLaneD, 0x2508D14BCEA7F369ULL, 0x05BFE389D621A7C4ULL },
    { Slot::kRainbowLaneA, 0x0726AF413EB98DC5ULL, 0x176F52BAE380C49DULL },
    { Slot::kRainbowLaneB, 0x8FAE27C9B631054DULL, 0x176F52BAE380C49DULL },
    { Slot::kRainbowLaneC, 0x90BF38DAC742165EULL, 0x176F52BAE380C49DULL },
    { Slot::kRainbowLaneD, 0x7E9D16B8A520F43CULL, 0x176F52BAE380C49DULL },
    { Slot::kLightningLaneA, 0x42F9B0351DEC67A8ULL, 0xE79F815A420B3D6CULL },
    { Slot::kLightningLaneB, 0x863DF4795120ABECULL, 0xE79F815A420B3D6CULL },
    { Slot::kLightningLaneC, 0x20D79E13FBCA4586ULL, 0xE79F815A420B3D6CULL },
    { Slot::kLightningLaneD, 0x752CE368401F9ADBULL, 0xE79F815A420B3D6CULL },
    { Slot::kIceLaneA, 0x576123AB40FDC9E8ULL, 0xA02B63FDE8C95471ULL },
    { Slot::kIceLaneB, 0x354F01892EDBA7C6ULL, 0xA02B63FDE8C95471ULL },
    { Slot::kIceLaneC, 0x243EF0781DCA96B5ULL, 0xA02B63FDE8C95471ULL },
    { Slot::kIceLaneD, 0x687234BC510EDAF9ULL, 0xA02B63FDE8C95471ULL },
    { Slot::kPlasmaLaneA, 0x416E0D983AC7B2F5ULL, 0x6EFAC7985014B2D3ULL },
    { Slot::kPlasmaLaneB, 0x527F1EA94BD8C306ULL, 0x6EFAC7985014B2D3ULL },
    { Slot::kPlasmaLaneC, 0x2F4CEB7618A590D3ULL, 0x6EFAC7985014B2D3ULL },
    { Slot::kPlasmaLaneD, 0x749130CB6DFAE528ULL, 0x6EFAC7985014B2D3ULL },
    { Slot::kShadowLaneA, 0xBF6792540CA31ED8ULL, 0x091D4F5C63B728AEULL },
    { Slot::kShadowLaneB, 0x37EF1ADC842B9650ULL, 0x091D4F5C63B728AEULL },
    { Slot::kShadowLaneC, 0x9D457032EA81FCB6ULL, 0x091D4F5C63B728AEULL },
    { Slot::kShadowLaneD, 0x48F02BED953CA761ULL, 0x091D4F5C63B728AEULL },
    { Slot::kCrystalLaneA, 0x23CE847BFA56D019ULL, 0xBCAE25D6F1403978ULL },
    { Slot::kCrystalLaneB, 0x7813D9C04FAB256EULL, 0xBCAE25D6F1403978ULL },
    { Slot::kCrystalLaneC, 0xF09B5148C723ADE6ULL, 0xBCAE25D6F1403978ULL },
    { Slot::kCrystalLaneD, 0xBC571D0483EF69A2ULL, 0xBCAE25D6F1403978ULL },
    { Slot::kAetherLaneA, 0x6C8A912FB754E0D3ULL, 0xB0FAD98EC5431762ULL },
    { Slot::kAetherLaneB, 0x9FBDC452EA871306ULL, 0xB0FAD98EC5431762ULL },
    { Slot::kAetherLaneC, 0xD3F108962ECB574AULL, 0xB0FAD98EC5431762ULL },
    { Slot::kAetherLaneD, 0xA0CED563FB982417ULL, 0xB0FAD98EC5431762ULL },
    { Slot::kCelestialLaneA, 0x298D5A613E70BCF4ULL, 0xC05B3FE7826D419AULL },
    { Slot::kCelestialLaneB, 0xA105D2E9B6F8347CULL, 0xC05B3FE7826D419AULL },
    { Slot::kCelestialLaneC, 0x8FE3B0C794D6125AULL, 0xC05B3FE7826D419AULL },
    { Slot::kCelestialLaneD, 0x5CB08D9461A3EF27ULL, 0xC05B3FE7826D419AULL },
    { Slot::kVaporLaneA, 0x24576D0AE913B8FCULL, 0xF16439ED78AC20B5ULL },
    { Slot::kVaporLaneB, 0xDF0218B594CE63A7ULL, 0xF16439ED78AC20B5ULL },
    { Slot::kVaporLaneC, 0x35687E1BFA24C90DULL, 0xF16439ED78AC20B5ULL },
    { Slot::kVaporLaneD, 0xBDE0F69372AC4185ULL, 0xF16439ED78AC20B5ULL },
    { Slot::kKineticLaneA, 0x679E503B12C48ADFULL, 0xFAD084B2735EC619ULL },
    { Slot::kKineticLaneB, 0xEF16D8B39A4C0257ULL, 0xFAD084B2735EC619ULL },
    { Slot::kKineticLaneC, 0x0138FAD5BC6E2479ULL, 0xFAD084B2735EC619ULL },
    { Slot::kKineticLaneD, 0xABD2947F5608CE13ULL, 0xFAD084B2735EC619ULL },
    { Slot::kSonicLaneA, 0xEF24D6051CAB8397ULL, 0xF79531DB4EC62A08ULL },
    { Slot::kSonicLaneB, 0xBCF1A3D2E9785064ULL, 0xF79531DB4EC62A08ULL },
    { Slot::kSonicLaneC, 0xF035E7162DBC94A8ULL, 0xF79531DB4EC62A08ULL },
    { Slot::kSonicLaneD, 0x125709384FDEB6CAULL, 0xF79531DB4EC62A08ULL },
    { Slot::kPlanarLaneA, 0x85DAB29716C340EFULL, 0xFC37D825AE964B01ULL },
    { Slot::kPlanarLaneB, 0xC91EF6DB5A078423ULL, 0xFC37D825AE964B01ULL },
    { Slot::kPlanarLaneC, 0x0D523A1F9E4BC867ULL, 0xFC37D825AE964B01ULL },
    { Slot::kPlanarLaneD, 0xA7FCD4B938E56201ULL, 0xFC37D825AE964B01ULL },
    { Slot::kFrostLaneA, 0xA21C7805E3F64D9BULL, 0xACDB51E7084936F2ULL },
    { Slot::kFrostLaneB, 0x6ED834C1AFB20957ULL, 0xACDB51E7084936F2ULL },
    { Slot::kFrostLaneC, 0xC43E9A2705186FBDULL, 0xACDB51E7084936F2ULL },
    { Slot::kFrostLaneD, 0xF761CD5A384B92E0ULL, 0xACDB51E7084936F2ULL },
    { Slot::kArcaneLaneA, 0x6A9C25F40D178E3BULL, 0xE1A2B0569C3D4F87ULL },
    { Slot::kArcaneLaneB, 0xE214AD7C859F06B3ULL, 0xE1A2B0569C3D4F87ULL },
    { Slot::kArcaneLaneC, 0x7BAD36051E289F4CULL, 0xE1A2B0569C3D4F87ULL },
    { Slot::kArcaneLaneD, 0x0436CF9EA7B128D5ULL, 0xE1A2B0569C3D4F87ULL },
    { Slot::kLunarLaneA, 0x31C02D7E865FB94AULL, 0x9B2053DE476A81FCULL },
    { Slot::kLunarLaneB, 0x861572C3DBA40E9FULL, 0x9B2053DE476A81FCULL },
    { Slot::kLunarLaneC, 0x0E9DFA4B532C8617ULL, 0x9B2053DE476A81FCULL },
    { Slot::kLunarLaneD, 0xDB6AC71820F953E4ULL, 0x9B2053DE476A81FCULL },
    { Slot::kRunicLaneA, 0xFE24371C0AD5B896ULL, 0x7A136E2C08DB4F59ULL },
    { Slot::kRunicLaneB, 0xDC0215FAE8B39674ULL, 0x7A136E2C08DB4F59ULL },
    { Slot::kRunicLaneC, 0xA9DFE2C7B5806341ULL, 0x7A136E2C08DB4F59ULL },
    { Slot::kRunicLaneD, 0x87BDC0A5936E412FULL, 0x7A136E2C08DB4F59ULL },
    { Slot::kGloomLaneA, 0xD5C31AB4962FE708ULL, 0x965274A3E8FD1CB0ULL },
    { Slot::kGloomLaneB, 0x4C3A812B0D965E7FULL, 0x965274A3E8FD1CB0ULL },
    { Slot::kGloomLaneC, 0x7F6DB45E30C981A2ULL, 0x965274A3E8FD1CB0ULL },
    { Slot::kGloomLaneD, 0xA290E78163FCB4D5ULL, 0x965274A3E8FD1CB0ULL },
    { Slot::kSpiritLaneA, 0x241F75CA0E638D9BULL, 0x013DACE748B96F52ULL },
    { Slot::kSpiritLaneB, 0x9B86EC3175DAF402ULL, 0x013DACE748B96F52ULL },
    { Slot::kSpiritLaneC, 0xF1EC4297DB305A68ULL, 0x013DACE748B96F52ULL },
    { Slot::kSpiritLaneD, 0xCEB91F64A80D2735ULL, 0x013DACE748B96F52ULL },
    { Slot::kAbjurationLaneA, 0x3E8071D6B5F2A49CULL, 0xEBA9C50DF3168724ULL },
    { Slot::kAbjurationLaneB, 0x83D5C62B0A47F9E1ULL, 0xEBA9C50DF3168724ULL },
    { Slot::kAbjurationLaneC, 0xFA4C3D9271BE6058ULL, 0xEBA9C50DF3168724ULL },
    { Slot::kAbjurationLaneD, 0x61B3A409E825D7CFULL, 0xEBA9C50DF3168724ULL },
    { Slot::kDivinationLaneA, 0x3D215F69AC87BE40ULL, 0x37CAF602B1DE8945ULL },
    { Slot::kDivinationLaneB, 0x1B0F3D478A659C2EULL, 0x37CAF602B1DE8945ULL },
    { Slot::kDivinationLaneC, 0x9387B5CF02ED14A6ULL, 0x37CAF602B1DE8945ULL },
    { Slot::kDivinationLaneD, 0xF9ED1B2568437A0CULL, 0x37CAF602B1DE8945ULL },
    { Slot::kEvocationLaneA, 0x0B1F723A45EC896DULL, 0xD072C9A8E3B64F51ULL },
    { Slot::kEvocationLaneB, 0x5064C78F9A31DEB2ULL, 0xD072C9A8E3B64F51ULL },
    { Slot::kEvocationLaneC, 0x3E42A56D781FBC90ULL, 0xD072C9A8E3B64F51ULL },
    { Slot::kEvocationLaneD, 0x94A80BC3DE7512F6ULL, 0xD072C9A8E3B64F51ULL },
    { Slot::kAlchemyLaneA, 0xD687325C91EA40BFULL, 0x46FE10532BADC798ULL },
    { Slot::kAlchemyLaneB, 0x8132ED074C95FB6AULL, 0x46FE10532BADC798ULL },
    { Slot::kAlchemyLaneC, 0xF8A9547EB30C62D1ULL, 0x46FE10532BADC798ULL },
    { Slot::kAlchemyLaneD, 0x4DFEA9C30851B726ULL, 0x46FE10532BADC798ULL },
    { Slot::kAuguryLaneA, 0x713B6A8F54DEC290ULL, 0x09BD16AF3874C52EULL },
    { Slot::kAuguryLaneB, 0x4E08375C21AB9F6DULL, 0x09BD16AF3874C52EULL },
    { Slot::kAuguryLaneC, 0xD791C0E5BA3428F6ULL, 0x09BD16AF3874C52EULL },
    { Slot::kAuguryLaneD, 0x1BD50429FE786C3AULL, 0x09BD16AF3874C52EULL },
    { Slot::kPsychicLaneA, 0xAC395486F012EB7DULL, 0xAC6783409EDF5B12ULL },
    { Slot::kPsychicLaneB, 0xBD4A65970123FC8EULL, 0xAC6783409EDF5B12ULL },
    { Slot::kPsychicLaneC, 0xDF6C87B923451EA0ULL, 0xAC6783409EDF5B12ULL },
    { Slot::kPsychicLaneD, 0x79062153CDEFB84AULL, 0xAC6783409EDF5B12ULL },
    { Slot::kVoodooLaneA, 0xD71B35CF9E06428AULL, 0x17D3405B6F9AC2E8ULL },
    { Slot::kVoodooLaneB, 0x71B5DF6938A0EC24ULL, 0x17D3405B6F9AC2E8ULL },
    { Slot::kVoodooLaneC, 0xA4E8029C6BD31F57ULL, 0x17D3405B6F9AC2E8ULL },
    { Slot::kVoodooLaneD, 0x93D7F18B5AC20E46ULL, 0x17D3405B6F9AC2E8ULL },
}};

constexpr std::uint8_t Nibble(const std::uint64_t pPacked,
                              const std::size_t pIndex) {
    return static_cast<std::uint8_t>(
        (pPacked >> (4U * pIndex)) & 0x0FULL
    );
}

constexpr bool IsPermutation(const std::uint64_t pPacked) {
    std::uint16_t aSeen = 0U;
    for (std::size_t i = 0U; i < kKeyFunctionCount; ++i) {
        const std::uint8_t aValue = Nibble(pPacked, i);
        const std::uint16_t aBit =
            static_cast<std::uint16_t>(1U << aValue);
        if ((aSeen & aBit) != 0U) {
            return false;
        }
        aSeen = static_cast<std::uint16_t>(aSeen | aBit);
    }
    return aSeen == 0xFFFFU;
}

constexpr const Assignment *Find(const Slot pLane) {
    for (const Assignment &aAssignment : kAssignments) {
        if (aAssignment.mLane == pLane) {
            return &aAssignment;
        }
    }
    return nullptr;
}

constexpr bool HasLane(const Slot pLane) {
    return Find(pLane) != nullptr;
}

constexpr std::uint8_t Split(const Assignment &pAssignment,
                             const std::size_t pLogicalKeyIndex,
                             const std::size_t pCandidateIndex) {
    if ((pCandidateIndex >= kActiveCandidateCount) ||
        (pLogicalKeyIndex >= kKeyFunctionCount)) {
        return 0U;
    }

    const std::size_t aKeyPosition =
        Nibble(pAssignment.mKeyOrder, pLogicalKeyIndex);
    const std::size_t aCycledPosition =
        (aKeyPosition + pCandidateIndex) & 15U;
    return Nibble(pAssignment.mSplitOrder, aCycledPosition);
}

constexpr std::uint8_t Split(const Slot pLane,
                             const std::size_t pLogicalKeyIndex,
                             const std::size_t pCandidateIndex) {
    if ((pCandidateIndex >= kActiveCandidateCount) ||
        (pLogicalKeyIndex >= kKeyFunctionCount)) {
        return 0U;
    }

    const Assignment *aAssignment = Find(pLane);
    if (aAssignment == nullptr) {
        return 0U;
    }
    return Split(*aAssignment, pLogicalKeyIndex, pCandidateIndex);
}

constexpr bool Validate() {
    for (std::size_t aLane = 0U;
         aLane < kAssignments.size();
         ++aLane) {
        const Assignment &aAssignment = kAssignments[aLane];
        if (!IsPermutation(aAssignment.mKeyOrder) ||
            !IsPermutation(aAssignment.mSplitOrder)) {
            return false;
        }

        for (std::size_t aOther = aLane + 1U;
             aOther < kAssignments.size();
             ++aOther) {
            if (aAssignment.mLane == kAssignments[aOther].mLane) {
                return false;
            }
        }

    }
    return true;
}

template <std::size_t N>
constexpr bool ValidateLaneFamily(
    const std::array<Slot, N> &pFamily) {
    std::array<const Assignment *, N> aAssignments = {};
    for (std::size_t aLane = 0U; aLane < N; ++aLane) {
        aAssignments[aLane] = Find(pFamily[aLane]);
        if (aAssignments[aLane] == nullptr) {
            return false;
        }
    }

    for (std::size_t aCandidateIndex = 0U;
         aCandidateIndex < kActiveCandidateCount;
         ++aCandidateIndex) {
        for (std::size_t aLogicalKeyIndex = 0U;
             aLogicalKeyIndex < kKeyFunctionCount;
             ++aLogicalKeyIndex) {
            for (std::size_t aLaneA = 0U; aLaneA < N; ++aLaneA) {
                for (std::size_t aLaneB = aLaneA + 1U;
                     aLaneB < N;
                     ++aLaneB) {
                    if (Split(*aAssignments[aLaneA],
                              aLogicalKeyIndex,
                              aCandidateIndex) ==
                        Split(*aAssignments[aLaneB],
                              aLogicalKeyIndex,
                              aCandidateIndex)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

static_assert(Validate(),
              "Every key-lane assignment must contain two permutations.");

// Keep these as separate assertions. A single combined constexpr evaluation
// over every family exceeds Clang's default constexpr step budget.
#define KEY_LANE_FAMILY_ASSERT(pA, pB, pC, pD) \
    static_assert(ValidateLaneFamily(std::array<Slot, 4U>{ \
        Slot::pA, Slot::pB, Slot::pC, Slot::pD }), \
        "Members of a key lane family must use different sixteenths.")

KEY_LANE_FAMILY_ASSERT(kEarthLaneA, kEarthLaneB,
                       kEarthLaneC, kEarthLaneD);
KEY_LANE_FAMILY_ASSERT(kFireLaneA, kFireLaneB,
                       kFireLaneC, kFireLaneD);
KEY_LANE_FAMILY_ASSERT(kWindLaneA, kWindLaneB,
                       kWindLaneC, kWindLaneD);
KEY_LANE_FAMILY_ASSERT(kWaterLaneA, kWaterLaneB,
                       kWaterLaneC, kWaterLaneD);
KEY_LANE_FAMILY_ASSERT(kRainbowLaneA, kRainbowLaneB,
                       kRainbowLaneC, kRainbowLaneD);
KEY_LANE_FAMILY_ASSERT(kLightningLaneA, kLightningLaneB,
                       kLightningLaneC, kLightningLaneD);
KEY_LANE_FAMILY_ASSERT(kIceLaneA, kIceLaneB,
                       kIceLaneC, kIceLaneD);
KEY_LANE_FAMILY_ASSERT(kPlasmaLaneA, kPlasmaLaneB,
                       kPlasmaLaneC, kPlasmaLaneD);
KEY_LANE_FAMILY_ASSERT(kShadowLaneA, kShadowLaneB,
                       kShadowLaneC, kShadowLaneD);
KEY_LANE_FAMILY_ASSERT(kCrystalLaneA, kCrystalLaneB,
                       kCrystalLaneC, kCrystalLaneD);
KEY_LANE_FAMILY_ASSERT(kAetherLaneA, kAetherLaneB,
                       kAetherLaneC, kAetherLaneD);
KEY_LANE_FAMILY_ASSERT(kCelestialLaneA, kCelestialLaneB,
                       kCelestialLaneC, kCelestialLaneD);
KEY_LANE_FAMILY_ASSERT(kVaporLaneA, kVaporLaneB,
                       kVaporLaneC, kVaporLaneD);
KEY_LANE_FAMILY_ASSERT(kKineticLaneA, kKineticLaneB,
                       kKineticLaneC, kKineticLaneD);
KEY_LANE_FAMILY_ASSERT(kSonicLaneA, kSonicLaneB,
                       kSonicLaneC, kSonicLaneD);
KEY_LANE_FAMILY_ASSERT(kPlanarLaneA, kPlanarLaneB,
                       kPlanarLaneC, kPlanarLaneD);
KEY_LANE_FAMILY_ASSERT(kFrostLaneA, kFrostLaneB,
                       kFrostLaneC, kFrostLaneD);
KEY_LANE_FAMILY_ASSERT(kArcaneLaneA, kArcaneLaneB,
                       kArcaneLaneC, kArcaneLaneD);
KEY_LANE_FAMILY_ASSERT(kLunarLaneA, kLunarLaneB,
                       kLunarLaneC, kLunarLaneD);
KEY_LANE_FAMILY_ASSERT(kRunicLaneA, kRunicLaneB,
                       kRunicLaneC, kRunicLaneD);
KEY_LANE_FAMILY_ASSERT(kGloomLaneA, kGloomLaneB,
                       kGloomLaneC, kGloomLaneD);
KEY_LANE_FAMILY_ASSERT(kSpiritLaneA, kSpiritLaneB,
                       kSpiritLaneC, kSpiritLaneD);
KEY_LANE_FAMILY_ASSERT(kAbjurationLaneA, kAbjurationLaneB,
                       kAbjurationLaneC, kAbjurationLaneD);
KEY_LANE_FAMILY_ASSERT(kDivinationLaneA, kDivinationLaneB,
                       kDivinationLaneC, kDivinationLaneD);
KEY_LANE_FAMILY_ASSERT(kEvocationLaneA, kEvocationLaneB,
                       kEvocationLaneC, kEvocationLaneD);
#undef KEY_LANE_FAMILY_ASSERT

// Cycling one permutation through another is a Latin-square construction:
// all sixteen active candidates necessarily differ at every lane/key position,
// and every candidate necessarily uses all sixteen splits for each lane.
static_assert(Split(Slot::kAetherLaneA, 0U, 16U) == 0U,
              "The seventeenth candidate must always use split zero.");

} // namespace KeyLaneAssignments

#endif /* KeyLaneAssignments_hpp */
