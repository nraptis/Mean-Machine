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
    { Slot::kEarthLaneA, 0x16DB92A470E85CF3ULL, 0xAB2E430695D817CFULL },
    { Slot::kEarthLaneB, 0x9E531A2CF860D47BULL, 0xAB2E430695D817CFULL },
    { Slot::kEarthLaneC, 0xD2975E603CA418BFULL, 0xAB2E430695D817CFULL },
    { Slot::kEarthLaneD, 0x27ECA3B581F96D04ULL, 0xAB2E430695D817CFULL },
    { Slot::kFireLaneA, 0x6BD12CF89E74A053ULL, 0x8A7E49B5C630F21DULL },
    { Slot::kFireLaneB, 0xE359A47016FC28DBULL, 0x8A7E49B5C630F21DULL },
    { Slot::kFireLaneC, 0x279DE8B45A306C1FULL, 0x8A7E49B5C630F21DULL },
    { Slot::kFireLaneD, 0x5AC01BE78D639F42ULL, 0x8A7E49B5C630F21DULL },
    { Slot::kWindLaneA, 0x6B20A1E8597CDF34ULL, 0x47D512083ABE96CFULL },
    { Slot::kWindLaneB, 0x38FD7EB52649AC01ULL, 0x47D512083ABE96CFULL },
    { Slot::kWindLaneC, 0x490E8FC6375ABD12ULL, 0x47D512083ABE96CFULL },
    { Slot::kWindLaneD, 0xC186074EBFD2359AULL, 0x47D512083ABE96CFULL },
    { Slot::kWaterLaneA, 0x83AB7694CF5D02E1ULL, 0x9658470CF1D23AEBULL },
    { Slot::kWaterLaneB, 0x61895472AD3BE0CFULL, 0x9658470CF1D23AEBULL },
    { Slot::kWaterLaneC, 0xE901DCFA25B36847ULL, 0x9658470CF1D23AEBULL },
    { Slot::kWaterLaneD, 0x0B23FE1C47D58A69ULL, 0x9658470CF1D23AEBULL },
    { Slot::kRainbowLaneA, 0xF637E015B894AD2CULL, 0xFA50629BE1738C4DULL },
    { Slot::kRainbowLaneB, 0x296A1348EBC7D05FULL, 0xFA50629BE1738C4DULL },
    { Slot::kRainbowLaneC, 0xB2F3ACD1745069E8ULL, 0xFA50629BE1738C4DULL },
    { Slot::kRainbowLaneD, 0x3A7B2459FCD8E160ULL, 0xFA50629BE1738C4DULL },
    { Slot::kLightningLaneA, 0x17ADBEC64902F538ULL, 0xEA956F21C87D43B0ULL },
    { Slot::kLightningLaneB, 0x4AD0E1F97C35286BULL, 0xEA956F21C87D43B0ULL },
    { Slot::kLightningLaneC, 0x9F25364EC18A7DB0ULL, 0xEA956F21C87D43B0ULL },
    { Slot::kLightningLaneD, 0x5BE1F20A8D46397CULL, 0xEA956F21C87D43B0ULL },
    { Slot::kIceLaneA, 0x285B1EF94730AD6CULL, 0xC73F2AD8594B60E1ULL },
    { Slot::kIceLaneB, 0x6C9F523D8B74E1A0ULL, 0xC73F2AD8594B60E1ULL },
    { Slot::kIceLaneC, 0x5B8E412C7A63D09FULL, 0xC73F2AD8594B60E1ULL },
    { Slot::kIceLaneD, 0x396C2F0A5841BE7DULL, 0xC73F2AD8594B60E1ULL },
    { Slot::kPlasmaLaneA, 0xFB74158362E0CD9AULL, 0xA8261DEC3495F70BULL },
    { Slot::kPlasmaLaneB, 0x40C96AD8B73512EFULL, 0xA8261DEC3495F70BULL },
    { Slot::kPlasmaLaneC, 0x3FB859C7A62401DEULL, 0xA8261DEC3495F70BULL },
    { Slot::kPlasmaLaneD, 0xEA63047251DFBC89ULL, 0xA8261DEC3495F70BULL },
    { Slot::kShadowLaneA, 0x0CB5A32F9E7618D4ULL, 0x4B57C0912AE83FD6ULL },
    { Slot::kShadowLaneB, 0xB7605EDA4921C38FULL, 0x4B57C0912AE83FD6ULL },
    { Slot::kShadowLaneC, 0xC8716FEB5A32D490ULL, 0x4B57C0912AE83FD6ULL },
    { Slot::kShadowLaneD, 0xEA93810D7C54F6B2ULL, 0x4B57C0912AE83FD6ULL },
    { Slot::kCrystalLaneA, 0x1F637B489D2AE05CULL, 0xDAC201438EFB7956ULL },
    { Slot::kCrystalLaneB, 0xA8FC04D126B379E5ULL, 0xDAC201438EFB7956ULL },
    { Slot::kCrystalLaneC, 0xCA1E26F348D59B07ULL, 0xDAC201438EFB7956ULL },
    { Slot::kCrystalLaneD, 0xDB2F370459E6AC18ULL, 0xDAC201438EFB7956ULL },
    { Slot::kAetherLaneA, 0xE32164B789DA0F5CULL, 0xDEF7A8241B6903C5ULL },
    { Slot::kAetherLaneB, 0x2765A8FBCD1E4390ULL, 0xDEF7A8241B6903C5ULL },
    { Slot::kAetherLaneC, 0xC10F429567B8ED3AULL, 0xDEF7A8241B6903C5ULL },
    { Slot::kAetherLaneD, 0x4987CA1DEF3065B2ULL, 0xDEF7A8241B6903C5ULL },
    { Slot::kCelestialLaneA, 0xBE96F2A314C8D507ULL, 0xDCA0B13F2689574EULL },
    { Slot::kCelestialLaneB, 0x58309C4DBE627FA1ULL, 0xDCA0B13F2689574EULL },
    { Slot::kCelestialLaneC, 0x03EB47F8691D2A5CULL, 0xDCA0B13F2689574EULL },
    { Slot::kCelestialLaneD, 0x6941AD5ECF7380B2ULL, 0xDCA0B13F2689574EULL },
    { Slot::kVaporLaneA, 0x62945A3B01C87EDFULL, 0xA5F71ED68CB94230ULL },
    { Slot::kVaporLaneB, 0xFB2DE3C49A510768ULL, 0xA5F71ED68CB94230ULL },
    { Slot::kVaporLaneC, 0xA6D89E7F450CB213ULL, 0xA5F71ED68CB94230ULL },
    { Slot::kVaporLaneD, 0x84B67C5D23EA90F1ULL, 0xA5F71ED68CB94230ULL },
    { Slot::kKineticLaneA, 0xA892B73506DEFC41ULL, 0x0C23D451FA87E9B6ULL },
    { Slot::kKineticLaneB, 0xDBC5EA6839012F74ULL, 0x0C23D451FA87E9B6ULL },
    { Slot::kKineticLaneC, 0x9781A624F5CDEB30ULL, 0x0C23D451FA87E9B6ULL },
    { Slot::kKineticLaneD, 0xFDE70C8A5B234196ULL, 0x0C23D451FA87E9B6ULL },
    { Slot::kSonicLaneA, 0x82179A0C5E34DFB6ULL, 0xC23FBE86D9501A74ULL },
    { Slot::kSonicLaneB, 0xF98E0173C5AB462DULL, 0xC23FBE86D9501A74ULL },
    { Slot::kSonicLaneC, 0x3DC245B709EF8A61ULL, 0xC23FBE86D9501A74ULL },
    { Slot::kSonicLaneD, 0xA439BC2E7056F1D8ULL, 0xC23FBE86D9501A74ULL },
    { Slot::kPlanarLaneA, 0x0E76CAD4F18B2539ULL, 0x39D0CA528147BE6FULL },
    { Slot::kPlanarLaneB, 0xA810647E9B25CFD3ULL, 0x39D0CA528147BE6FULL },
    { Slot::kPlanarLaneC, 0x2098ECF613AD475BULL, 0x39D0CA528147BE6FULL },
    { Slot::kPlanarLaneD, 0x31A9FD0724BE586CULL, 0x39D0CA528147BE6FULL },
    { Slot::kFrostLaneA, 0xC41A20BEDF895673ULL, 0xA423C75D8EF9610BULL },
    { Slot::kFrostLaneB, 0x4C92A8365701DEFBULL, 0xA423C75D8EF9610BULL },
    { Slot::kFrostLaneC, 0x7FC5DB698A34012EULL, 0xA423C75D8EF9610BULL },
    { Slot::kFrostLaneD, 0xA2F80E9CBD673451ULL, 0xA423C75D8EF9610BULL },
    { Slot::kArcaneLaneA, 0x78213CA9D5B40F6EULL, 0x72ABFEC48601359DULL },
    { Slot::kArcaneLaneB, 0x45FE0976A281DC3BULL, 0x72ABFEC48601359DULL },
    { Slot::kArcaneLaneC, 0xEF98A3104C2B76D5ULL, 0x72ABFEC48601359DULL },
    { Slot::kArcaneLaneD, 0x34EDF8659170CB2AULL, 0x72ABFEC48601359DULL },
    { Slot::kLunarLaneA, 0x105E26DC47B3FA89ULL, 0x1305DB8ACE6742F9ULL },
    { Slot::kLunarLaneB, 0xBAF8C076E15D9423ULL, 0x1305DB8ACE6742F9ULL },
    { Slot::kLunarLaneC, 0xFE3C04BA2591D867ULL, 0x1305DB8ACE6742F9ULL },
    { Slot::kLunarLaneD, 0x98D6AE54CF3B7201ULL, 0x1305DB8ACE6742F9ULL },
    { Slot::kRunicLaneA, 0x1DCBF59E8063A427ULL, 0x1C6437EAB5D92F80ULL },
    { Slot::kRunicLaneB, 0x62104AE3D5B8F97CULL, 0x1C6437EAB5D92F80ULL },
    { Slot::kRunicLaneC, 0xA6548E2719FC3DB0ULL, 0x1C6437EAB5D92F80ULL },
    { Slot::kRunicLaneD, 0x510F39D2C4A7E86BULL, 0x1C6437EAB5D92F80ULL },
    { Slot::kGloomLaneA, 0x079AE145F83CDB26ULL, 0xAE496510DBC3F287ULL },
    { Slot::kGloomLaneB, 0x8F1269CD70B453AEULL, 0xAE496510DBC3F287ULL },
    { Slot::kGloomLaneC, 0x4BDE25893C701F6AULL, 0xAE496510DBC3F287ULL },
    { Slot::kGloomLaneD, 0x29BC03671A5EFD48ULL, 0xAE496510DBC3F287ULL },
    { Slot::kSpiritLaneA, 0xB6FE1DA239584C70ULL, 0xD7540C219B83E6FAULL },
    { Slot::kSpiritLaneB, 0x72BAD96EF514083CULL, 0xD7540C219B83E6FAULL },
    { Slot::kSpiritLaneC, 0x3E76952AB1D0C4F8ULL, 0xD7540C219B83E6FAULL },
    { Slot::kSpiritLaneD, 0x94DCFB8017362A5EULL, 0xD7540C219B83E6FAULL },
    { Slot::kAbjurationLaneA, 0x4E68FDCB1350729AULL, 0x8D73695CE2A4FB10ULL },
    { Slot::kAbjurationLaneB, 0x93BD421068A5C7EFULL, 0x8D73695CE2A4FB10ULL },
    { Slot::kAbjurationLaneC, 0xE8029765BDFA1C34ULL, 0x8D73695CE2A4FB10ULL },
    { Slot::kAbjurationLaneD, 0x1B35CA98E02D4F67ULL, 0x8D73695CE2A4FB10ULL },
    { Slot::kDivinationLaneA, 0x195A3CE470DF8B26ULL, 0x2F3C157D084ABE96ULL },
    { Slot::kDivinationLaneB, 0x7FB0924AD635E18CULL, 0x2F3C157D084ABE96ULL },
    { Slot::kDivinationLaneC, 0xF7381AC25EBD6904ULL, 0x2F3C157D084ABE96ULL },
    { Slot::kDivinationLaneD, 0x5D9E7028B413CF6AULL, 0x2F3C157D084ABE96ULL },
    { Slot::kEvocationLaneA, 0xE3FAC9B542861D70ULL, 0x7A9C2F8453D6E0B1ULL },
    { Slot::kEvocationLaneB, 0xC1D8A7932064FB5EULL, 0x7A9C2F8453D6E0B1ULL },
    { Slot::kEvocationLaneC, 0x5A61302CB9FD84E7ULL, 0x7A9C2F8453D6E0B1ULL },
    { Slot::kEvocationLaneD, 0x051CEBD764A83F92ULL, 0x7A9C2F8453D6E0B1ULL },
    { Slot::kAlchemyLaneA, 0x7C8045E63B129FDAULL, 0xF978263D5A14ECB0ULL },
    { Slot::kAlchemyLaneB, 0xAFB378196E45C20DULL, 0xF978263D5A14ECB0ULL },
    { Slot::kAlchemyLaneC, 0xB0C4892A7F56D31EULL, 0xF978263D5A14ECB0ULL },
    { Slot::kAlchemyLaneD, 0x5A6E23C419F07DB8ULL, 0xF978263D5A14ECB0ULL },
    { Slot::kAuguryLaneA, 0x2890AFD75BCE1634ULL, 0xB83C5F1D4E2A0796ULL },
    { Slot::kAuguryLaneB, 0x8EF6053DB1247C9AULL, 0xB83C5F1D4E2A0796ULL },
    { Slot::kAuguryLaneC, 0x067E8DB539ACF412ULL, 0xB83C5F1D4E2A0796ULL },
    { Slot::kAuguryLaneD, 0xC23A4971F568B0DEULL, 0xB83C5F1D4E2A0796ULL },
    { Slot::kPsychicLaneA, 0xD4159EA8F02673CBULL, 0x7C6EA23F19540BD8ULL },
    { Slot::kPsychicLaneB, 0xE526AFB9013784DCULL, 0x7C6EA23F19540BD8ULL },
    { Slot::kPsychicLaneC, 0xB2F37C86DE0451A9ULL, 0x7C6EA23F19540BD8ULL },
    { Slot::kPsychicLaneD, 0x7EBF38429AC01D65ULL, 0x7C6EA23F19540BD8ULL },
    { Slot::kVoodooLaneA, 0xE2A57D1BF608C439ULL, 0xE7A4BDC5620138F9ULL },
    { Slot::kVoodooLaneB, 0x8C4F17B590A26ED3ULL, 0xE7A4BDC5620138F9ULL },
    { Slot::kVoodooLaneC, 0x480BD3715C6E2A9FULL, 0xE7A4BDC5620138F9ULL },
    { Slot::kVoodooLaneD, 0xD1946C0AE5F7B328ULL, 0xE7A4BDC5620138F9ULL },
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
