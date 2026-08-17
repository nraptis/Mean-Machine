//
//  GFlowPlans.hpp
//  MeanMachine
//
//  Ordered, semantic lane-flow plans shared by stage configuration and code
//  emission. Residual selection remains the responsibility of each runner.
//

#ifndef GFlowPlans_hpp
#define GFlowPlans_hpp

#include "TwistWorkSpace.hpp"

#include <array>
#include <initializer_list>
#include <string>
#include <vector>

enum class GFlowLane {
    kSource,
    kNonce,
    kKeyReadA,
    kKeyReadB,
    kCrossA,
    kCrossB,
    kCrossC,
    kCrossD,

    kAbjuration,
    kAether,
    kAlchemy,
    kArcane,
    kAugury,
    kCrystal,
    kDivination,
    kEarth,
    kEvocation,
    kFire,
    kFrost,
    kGloom,
    kIce,
    kKinetic,
    kLightning,
    kLunar,
    kPlanar,
    kPlasma,
    kPsychic,
    kRainbow,
    kRunic,
    kShadow,
    kSonic,
    kSpirit,
    kVapor,
    kVoodoo,
    kWater,
    kWind,
};

enum class GFlowStepKind {
    kARX,
    kDiffuse,
    kSquashDestination,
    kSquashKey,
};

enum class GFlowARXShape {
    kStarter,
    kMidstage,
    kTrunk,
    kGrowStarter,
    kKeyStarter,
};

struct GFlowStep {
    GFlowStepKind                       mKind = GFlowStepKind::kARX;
    char                                mLetter = '\0';
    std::vector<GFlowLane>              mInputs;
    GFlowLane                           mOutput = GFlowLane::kSource;
    GFlowLane                           mEntropy = GFlowLane::kSource;
    GFlowARXShape                       mARXShape = GFlowARXShape::kMidstage;
    int                                 mArrangementOffset = 0;
    std::vector<GFlowLane>              mForcedResiduals;
};

struct GFlowPlan {
    const char                         *mName = "";
    std::vector<GFlowStep>              mSteps;
};

namespace GFlowPlans {

using Slot = TwistWorkSpaceSlot;
using SlotArray4 = std::array<Slot, 4U>;

inline constexpr std::size_t kKeyFlowCount = 16U;
inline constexpr std::size_t kKeyBoxFlowCount = 8U;
inline constexpr std::size_t kKeyARXStageCount = 5U;
inline constexpr std::size_t kKeyStageConfigCount =
    kKeyFlowCount * kKeyARXStageCount;

inline GFlowStep ARX(const char pLetter,
                     const std::initializer_list<GFlowLane> pInputs,
                     const GFlowLane pOutput,
                     const GFlowARXShape pShape,
                     const int pArrangementOffset = 0,
                     const std::initializer_list<GFlowLane>
                         pForcedResiduals = {}) {
    GFlowStep aStep;
    aStep.mKind = GFlowStepKind::kARX;
    aStep.mLetter = pLetter;
    aStep.mInputs.assign(pInputs.begin(), pInputs.end());
    aStep.mOutput = pOutput;
    aStep.mARXShape = pShape;
    aStep.mArrangementOffset = pArrangementOffset;
    aStep.mForcedResiduals.assign(pForcedResiduals.begin(),
                                  pForcedResiduals.end());
    return aStep;
}

inline GFlowStep ARXWithResiduals(
    const char pLetter,
    const std::initializer_list<GFlowLane> pInputs,
    const GFlowLane pOutput,
    const GFlowARXShape pShape,
    const std::initializer_list<GFlowLane> pForcedResiduals,
    const int pArrangementOffset = 0) {
    return ARX(pLetter,
               pInputs,
               pOutput,
               pShape,
               pArrangementOffset,
               pForcedResiduals);
}

inline GFlowStep Diffuse(const GFlowLane pInput,
                         const GFlowLane pEntropy,
                         const GFlowLane pOutput) {
    GFlowStep aStep;
    aStep.mKind = GFlowStepKind::kDiffuse;
    aStep.mInputs = {pInput};
    aStep.mEntropy = pEntropy;
    aStep.mOutput = pOutput;
    return aStep;
}

inline GFlowStep SquashDestination(const GFlowLane pInput) {
    GFlowStep aStep;
    aStep.mKind = GFlowStepKind::kSquashDestination;
    aStep.mInputs = {pInput};
    return aStep;
}

inline GFlowStep SquashKey(const GFlowLane pInput) {
    GFlowStep aStep;
    aStep.mKind = GFlowStepKind::kSquashKey;
    aStep.mInputs = {pInput};
    return aStep;
}

inline Slot FirstSlot(const GFlowLane pLane) {
    switch (pLane) {
        case GFlowLane::kSource: return Slot::kSourceLane;
        case GFlowLane::kNonce: return Slot::kNonceLane;
        case GFlowLane::kKeyReadA: return Slot::kKeyRowReadA;
        case GFlowLane::kKeyReadB: return Slot::kKeyRowReadB;
        case GFlowLane::kCrossA: return Slot::kParamCrossA;
        case GFlowLane::kCrossB: return Slot::kParamCrossB;
        case GFlowLane::kCrossC: return Slot::kParamCrossC;
        case GFlowLane::kCrossD: return Slot::kParamCrossD;

        case GFlowLane::kAbjuration: return Slot::kAbjurationLaneA;
        case GFlowLane::kAether: return Slot::kAetherLaneA;
        case GFlowLane::kAlchemy: return Slot::kAlchemyLaneA;
        case GFlowLane::kArcane: return Slot::kArcaneLaneA;
        case GFlowLane::kAugury: return Slot::kAuguryLaneA;
        case GFlowLane::kCrystal: return Slot::kCrystalLaneA;
        case GFlowLane::kDivination: return Slot::kDivinationLaneA;
        case GFlowLane::kEarth: return Slot::kEarthLaneA;
        case GFlowLane::kEvocation: return Slot::kEvocationLaneA;
        case GFlowLane::kFire: return Slot::kFireLaneA;
        case GFlowLane::kFrost: return Slot::kFrostLaneA;
        case GFlowLane::kGloom: return Slot::kGloomLaneA;
        case GFlowLane::kIce: return Slot::kIceLaneA;
        case GFlowLane::kKinetic: return Slot::kKineticLaneA;
        case GFlowLane::kLightning: return Slot::kLightningLaneA;
        case GFlowLane::kLunar: return Slot::kLunarLaneA;
        case GFlowLane::kPlanar: return Slot::kPlanarLaneA;
        case GFlowLane::kPlasma: return Slot::kPlasmaLaneA;
        case GFlowLane::kPsychic: return Slot::kPsychicLaneA;
        case GFlowLane::kRainbow: return Slot::kRainbowLaneA;
        case GFlowLane::kRunic: return Slot::kRunicLaneA;
        case GFlowLane::kShadow: return Slot::kShadowLaneA;
        case GFlowLane::kSonic: return Slot::kSonicLaneA;
        case GFlowLane::kSpirit: return Slot::kSpiritLaneA;
        case GFlowLane::kVapor: return Slot::kVaporLaneA;
        case GFlowLane::kVoodoo: return Slot::kVoodooLaneA;
        case GFlowLane::kWater: return Slot::kWaterLaneA;
        case GFlowLane::kWind: return Slot::kWindLaneA;
    }
    return Slot::kSourceLane;
}

inline const char *LaneStem(const GFlowLane pLane) {
    switch (pLane) {
        case GFlowLane::kSource: return "Source";
        case GFlowLane::kNonce: return "Nonce";
        case GFlowLane::kKeyReadA: return "KeyReadA";
        case GFlowLane::kKeyReadB: return "KeyReadB";
        case GFlowLane::kCrossA: return "CrossA";
        case GFlowLane::kCrossB: return "CrossB";
        case GFlowLane::kCrossC: return "CrossC";
        case GFlowLane::kCrossD: return "CrossD";

        case GFlowLane::kAbjuration: return "Abjuration";
        case GFlowLane::kAether: return "Aether";
        case GFlowLane::kAlchemy: return "Alchemy";
        case GFlowLane::kArcane: return "Arcane";
        case GFlowLane::kAugury: return "Augury";
        case GFlowLane::kCrystal: return "Crystal";
        case GFlowLane::kDivination: return "Divination";
        case GFlowLane::kEarth: return "Earth";
        case GFlowLane::kEvocation: return "Evocation";
        case GFlowLane::kFire: return "Fire";
        case GFlowLane::kFrost: return "Frost";
        case GFlowLane::kGloom: return "Gloom";
        case GFlowLane::kIce: return "Ice";
        case GFlowLane::kKinetic: return "Kinetic";
        case GFlowLane::kLightning: return "Lightning";
        case GFlowLane::kLunar: return "Lunar";
        case GFlowLane::kPlanar: return "Planar";
        case GFlowLane::kPlasma: return "Plasma";
        case GFlowLane::kPsychic: return "Psychic";
        case GFlowLane::kRainbow: return "Rainbow";
        case GFlowLane::kRunic: return "Runic";
        case GFlowLane::kShadow: return "Shadow";
        case GFlowLane::kSonic: return "Sonic";
        case GFlowLane::kSpirit: return "Spirit";
        case GFlowLane::kVapor: return "Vapor";
        case GFlowLane::kVoodoo: return "Voodoo";
        case GFlowLane::kWater: return "Water";
        case GFlowLane::kWind: return "Wind";
    }
    return "Invalid";
}

inline bool IsFamily(const GFlowLane pLane) {
    return static_cast<int>(pLane) >=
        static_cast<int>(GFlowLane::kAbjuration);
}

inline SlotArray4 FamilySlots(const GFlowLane pLane) {
    const int aFirst = static_cast<int>(FirstSlot(pLane));
    return {{
        static_cast<Slot>(aFirst + 0),
        static_cast<Slot>(aFirst + 1),
        static_cast<Slot>(aFirst + 2),
        static_cast<Slot>(aFirst + 3),
    }};
}

inline std::vector<Slot> FamilySlotVector(const GFlowLane pLane) {
    const SlotArray4 aSlots = FamilySlots(pLane);
    return std::vector<Slot>(aSlots.begin(), aSlots.end());
}

inline std::vector<Slot> FamilySlotVector(
    const std::initializer_list<GFlowLane> pLanes) {
    std::vector<Slot> aResult;
    aResult.reserve(pLanes.size() * 4U);
    for (const GFlowLane aLane : pLanes) {
        const SlotArray4 aSlots = FamilySlots(aLane);
        aResult.insert(aResult.end(), aSlots.begin(), aSlots.end());
    }
    return aResult;
}

inline std::string FlowCommentName(const GFlowLane pLane) {
    switch (pLane) {
        case GFlowLane::kSource: return "source";
        case GFlowLane::kNonce: return "nonce";
        case GFlowLane::kKeyReadA: return "key_read_a";
        case GFlowLane::kKeyReadB: return "key_read_b";
        case GFlowLane::kCrossA: return "cross_a";
        case GFlowLane::kCrossB: return "cross_b";
        case GFlowLane::kCrossC: return "cross_c";
        case GFlowLane::kCrossD: return "cross_d";
        default:
            break;
    }

    std::string aName(LaneStem(pLane));
    for (char &aCharacter : aName) {
        if ((aCharacter >= 'A') && (aCharacter <= 'Z')) {
            aCharacter = static_cast<char>(
                aCharacter - 'A' + 'a');
        }
    }
    return "$" + aName;
}

inline std::string FlowCommentList(
    const std::vector<GFlowLane> &pLanes) {
    std::string aResult = "[";
    for (std::size_t aIndex = 0U;
         aIndex < pLanes.size();
         ++aIndex) {
        if (aIndex > 0U) {
            aResult += ", ";
        }
        aResult += FlowCommentName(pLanes[aIndex]);
    }
    aResult += "]";
    return aResult;
}

inline std::vector<Slot> InputSlots(const GFlowStep &pStep) {
    std::vector<Slot> aResult;
    for (const GFlowLane aLane : pStep.mInputs) {
        if (IsFamily(aLane)) {
            const SlotArray4 aFamily = FamilySlots(aLane);
            aResult.insert(aResult.end(), aFamily.begin(), aFamily.end());
        } else {
            aResult.push_back(FirstSlot(aLane));
        }
    }
    return aResult;
}

inline std::vector<Slot> ForcedResidualSlots(const GFlowStep &pStep) {
    std::vector<Slot> aResult;
    for (const GFlowLane aLane : pStep.mForcedResiduals) {
        if (IsFamily(aLane)) {
            const SlotArray4 aFamily = FamilySlots(aLane);
            aResult.insert(aResult.end(), aFamily.begin(), aFamily.end());
        } else {
            aResult.push_back(FirstSlot(aLane));
        }
    }
    return aResult;
}

inline std::vector<GFlowStep> ARXSteps(const GFlowPlan &pPlan) {
    std::vector<GFlowStep> aResult;
    for (const GFlowStep &aStep : pPlan.mSteps) {
        if (aStep.mKind == GFlowStepKind::kARX) {
            aResult.push_back(aStep);
        }
    }
    return aResult;
}

inline std::size_t ARXStepCount(const GFlowPlan &pPlan) {
    std::size_t aCount = 0U;
    for (const GFlowStep &aStep : pPlan.mSteps) {
        if (aStep.mKind == GFlowStepKind::kARX) {
            ++aCount;
        }
    }
    return aCount;
}

inline std::size_t DiffusionCount(const GFlowPlan &pPlan) {
    std::size_t aCount = 0U;
    for (const GFlowStep &aStep : pPlan.mSteps) {
        if (aStep.mKind == GFlowStepKind::kDiffuse) {
            ++aCount;
        }
    }
    return aCount;
}

// Each plan below is written in exported execution order. This is the single
// place to review the high-level ARX, diffusion, and terminal lane flow.

inline const GFlowPlan &KDFA() {
    static const GFlowPlan kPlan = {
        "KDF A",
        {
            ARX('A', {GFlowLane::kSource, GFlowLane::kNonce}, GFlowLane::kShadow, GFlowARXShape::kStarter),
            ARX('B', {GFlowLane::kShadow}, GFlowLane::kFire, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kFire, GFlowLane::kShadow, GFlowLane::kVapor),
            ARX('C', {GFlowLane::kVapor}, GFlowLane::kKinetic, GFlowARXShape::kTrunk, 7),
        }
    };
    return kPlan;
}

inline const GFlowPlan &KDFB() {
    static const GFlowPlan kPlan = {
        "KDF B",
        {
            ARX('A', {GFlowLane::kKinetic}, GFlowLane::kEvocation, GFlowARXShape::kMidstage),
            ARX('B', {GFlowLane::kEvocation}, GFlowLane::kRunic, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kRunic, GFlowLane::kEvocation, GFlowLane::kDivination),
            ARX('C', {GFlowLane::kDivination}, GFlowLane::kAbjuration, GFlowARXShape::kTrunk, 1),
        }
    };
    return kPlan;
}

inline const GFlowPlan &KDFC() {
    static const GFlowPlan kPlan = {
        "KDF C",
        {
            ARX('A', {GFlowLane::kAbjuration}, GFlowLane::kAether, GFlowARXShape::kMidstage),
            ARX('B', {GFlowLane::kAether}, GFlowLane::kLunar, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kLunar, GFlowLane::kAether, GFlowLane::kEarth),
            ARX('C', {GFlowLane::kEarth}, GFlowLane::kCrystal, GFlowARXShape::kTrunk, 12),
        }
    };
    return kPlan;
}

inline const GFlowPlan &Seed() {
    static const GFlowPlan kPlan = {
        "Seed",
        {
            ARX('A', {GFlowLane::kSource, GFlowLane::kNonce}, GFlowLane::kIce, GFlowARXShape::kStarter),
            ARXWithResiduals('B', {GFlowLane::kIce}, GFlowLane::kRainbow, GFlowARXShape::kMidstage, {GFlowLane::kSource, GFlowLane::kNonce}),
            Diffuse(GFlowLane::kRainbow, GFlowLane::kIce, GFlowLane::kAlchemy),

            ARXWithResiduals('C', {GFlowLane::kAlchemy}, GFlowLane::kAugury, GFlowARXShape::kTrunk, {GFlowLane::kSource, GFlowLane::kNonce}, 7),
            ARXWithResiduals('D', {GFlowLane::kAugury}, GFlowLane::kSpirit, GFlowARXShape::kMidstage, {GFlowLane::kSource, GFlowLane::kNonce}),
            Diffuse(GFlowLane::kSpirit, GFlowLane::kAugury, GFlowLane::kDivination),

            ARXWithResiduals('E', {GFlowLane::kDivination}, GFlowLane::kPsychic, GFlowARXShape::kTrunk, {GFlowLane::kSource, GFlowLane::kNonce}, 9),
            ARXWithResiduals('F', {GFlowLane::kPsychic}, GFlowLane::kVoodoo, GFlowARXShape::kMidstage, {GFlowLane::kSource, GFlowLane::kNonce}),
            Diffuse(GFlowLane::kVoodoo, GFlowLane::kPsychic, GFlowLane::kVapor),

            ARXWithResiduals('G', {GFlowLane::kVapor}, GFlowLane::kSonic, GFlowARXShape::kTrunk, {GFlowLane::kSource}, 13),
            ARXWithResiduals('H', {GFlowLane::kSonic}, GFlowLane::kPlanar, GFlowARXShape::kMidstage, {GFlowLane::kSource}),
            Diffuse(GFlowLane::kPlanar, GFlowLane::kSonic, GFlowLane::kFrost),

            ARXWithResiduals('I', {GFlowLane::kFrost}, GFlowLane::kGloom, GFlowARXShape::kTrunk, {GFlowLane::kSource}, 2),
            ARXWithResiduals('J', {GFlowLane::kGloom}, GFlowLane::kLightning, GFlowARXShape::kMidstage, {GFlowLane::kSource}),
            Diffuse(GFlowLane::kLightning, GFlowLane::kGloom, GFlowLane::kWind),

            ARXWithResiduals('K', {GFlowLane::kWind}, GFlowLane::kShadow, GFlowARXShape::kTrunk, {GFlowLane::kNonce}, 6),
            ARXWithResiduals('L', {GFlowLane::kShadow}, GFlowLane::kFire, GFlowARXShape::kMidstage, {GFlowLane::kNonce}),
            Diffuse(GFlowLane::kFire, GFlowLane::kShadow, GFlowLane::kKinetic),

            ARXWithResiduals('M', {GFlowLane::kKinetic}, GFlowLane::kEvocation, GFlowARXShape::kTrunk, {GFlowLane::kSource}, 11),
            ARXWithResiduals('N', {GFlowLane::kEvocation}, GFlowLane::kRunic, GFlowARXShape::kMidstage, {GFlowLane::kSource}),
            Diffuse(GFlowLane::kRunic, GFlowLane::kEvocation, GFlowLane::kAbjuration),

            ARXWithResiduals('O', {GFlowLane::kAbjuration}, GFlowLane::kAether, GFlowARXShape::kTrunk, {GFlowLane::kSource}, 5),
            ARXWithResiduals('P', {GFlowLane::kAether}, GFlowLane::kLunar, GFlowARXShape::kMidstage, {GFlowLane::kSource}),
            Diffuse(GFlowLane::kLunar, GFlowLane::kAether, GFlowLane::kEarth),

            ARX('Q', {GFlowLane::kEarth}, GFlowLane::kCrystal, GFlowARXShape::kTrunk, 3),
            SquashDestination(GFlowLane::kCrystal),
        }
    };
    return kPlan;
}

inline const GFlowPlan &Twist() {
    static const GFlowPlan kPlan = {
        "Twist",
        {
            ARX('A', {GFlowLane::kSource, GFlowLane::kKeyReadA, GFlowLane::kKeyReadB}, GFlowLane::kAether, GFlowARXShape::kStarter),
            ARX('B', {GFlowLane::kAether}, GFlowLane::kLunar, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kLunar, GFlowLane::kAether, GFlowLane::kEarth),
            ARX('C', {GFlowLane::kEarth}, GFlowLane::kCrystal, GFlowARXShape::kTrunk, 11),
            SquashDestination(GFlowLane::kCrystal),
        }
    };
    return kPlan;
}

inline const GFlowPlan &GrowA() {
    static const GFlowPlan kPlan = {
        "Grow A",
        {
            ARX('A', {GFlowLane::kSpirit, GFlowLane::kCrossA, GFlowLane::kCrossB}, GFlowLane::kArcane, GFlowARXShape::kGrowStarter),
            ARX('B', {GFlowLane::kArcane}, GFlowLane::kPlasma, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kPlasma, GFlowLane::kArcane, GFlowLane::kRainbow),
            ARX('C', {GFlowLane::kRainbow}, GFlowLane::kWater, GFlowARXShape::kTrunk, 5),
            ARX('D', {GFlowLane::kWater}, GFlowLane::kVapor, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kVapor, GFlowLane::kWater, GFlowLane::kFrost),
            ARX('E', {GFlowLane::kFrost}, GFlowLane::kIce, GFlowARXShape::kTrunk, 5),
            SquashKey(GFlowLane::kIce),
        }
    };
    return kPlan;
}

inline const GFlowPlan &GrowB() {
    static const GFlowPlan kPlan = {
        "Grow B",
        {
            ARX('A', {GFlowLane::kDivination, GFlowLane::kCrossA, GFlowLane::kCrossB}, GFlowLane::kArcane, GFlowARXShape::kGrowStarter),
            ARX('B', {GFlowLane::kArcane}, GFlowLane::kPlasma, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kPlasma, GFlowLane::kArcane, GFlowLane::kRainbow),
            ARX('C', {GFlowLane::kRainbow}, GFlowLane::kWater, GFlowARXShape::kTrunk, 3),
            ARX('D', {GFlowLane::kWater}, GFlowLane::kVapor, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kVapor, GFlowLane::kWater, GFlowLane::kFrost),
            ARX('E', {GFlowLane::kFrost}, GFlowLane::kIce, GFlowARXShape::kTrunk, 3),
            SquashKey(GFlowLane::kIce),
        }
    };
    return kPlan;
}

inline const GFlowPlan &Key() {
    static const GFlowPlan kPlan = {
        "Independent key row",
        {
            ARX('A', {GFlowLane::kEarth, GFlowLane::kCrystal}, GFlowLane::kArcane, GFlowARXShape::kKeyStarter),
            ARX('B', {GFlowLane::kArcane}, GFlowLane::kPlasma, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kPlasma, GFlowLane::kArcane, GFlowLane::kRainbow),
            ARX('C', {GFlowLane::kRainbow}, GFlowLane::kWater, GFlowARXShape::kTrunk),
            ARX('D', {GFlowLane::kWater}, GFlowLane::kVapor, GFlowARXShape::kMidstage),
            Diffuse(GFlowLane::kVapor, GFlowLane::kWater, GFlowLane::kFrost),
            ARX('E', {GFlowLane::kFrost}, GFlowLane::kIce, GFlowARXShape::kTrunk),
            SquashKey(GFlowLane::kIce),
        }
    };
    return kPlan;
}

} // namespace GFlowPlans

#endif /* GFlowPlans_hpp */
