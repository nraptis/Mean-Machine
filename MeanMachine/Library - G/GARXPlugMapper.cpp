//
//  GARXPlugMapper.cpp
//  MeanMachine
//
//  Created by Dragon on 5/9/26.
//

#include "GARXPlugMapper.hpp"
#include "Random.hpp"


static std::vector<int> cPlugRotations = {
    5, 7, 11, 13,
    17, 19, 23, 29,
    31, 37, 41, 43,
    47, 53, 59, 61,
    3, 9, 15, 21,
    27, 33, 39, 45
};

static std::vector<int> cPlugOffsets = {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16,
    17, 18, 19, 20,
    21, 23, 25, 29
};

//
// Plug taps are intentionally limited to stream-context values.
//
// The salt plug is meant to perturb the ARX transition, not observe or expose
// the private ARX state. For that reason, plug-key operands are drawn only from
// the loop/input context:
//
//     input, previous, scatter, cross
//
// and not from:
//
//     rounds, states, carry
//
// Rounds and states are the protected internal recurrence state. Allowing
// them to directly address salt tables would turn each plug lookup into a small
// state-dependent side-channel snapshot, even if the final output only emits a
// heavily mixed low byte. By keeping plug taps restricted to stream-context
// values, the private state receives keyed disturbance without being used as
// the lookup address.
//
// This gives the design a cleaner boundary:
//
//     stream context -> salt plug -> ARX state
//
// rather than:
//
//     ARX state -> salt plug -> ARX state
//
// The latter may still be defensible, but it is harder to reason about and
// easier to overfit with local state observations. The current rule keeps salt
// plugs as contextual seasoning while rounds, states, and carry remain
// private evolving state.
//
static std::vector<GARXType> cPlugTypeList = {
    GARXType::kStreamCurrent,
    GARXType::kStreamPrevious,
    GARXType::kStreamScatter,
    GARXType::kStreamCross
};

static std::vector<GARXTypePair> MakePlugPairPool() {
    
    std::vector<GARXTypePair> aResult;
    
    for (GARXType aTypeA: cPlugTypeList) {
        for (GARXType aTypeB: cPlugTypeList) {
            
            if (aTypeA == aTypeB) {
                continue;
            }
            
            GARXTypePair aPair;
            aPair.mTypeA = aTypeA;
            aPair.mTypeB = aTypeB;
            aResult.push_back(aPair);
        }
    }
    
    return aResult;
}

static int CountPlugSlots(const std::vector<GARXStatementGroup *> &pGroups) {
    int aResult = 0;
    for (GARXStatementGroup *aGroup: pGroups) {
        for (GARXStatementPlan *aStatement: aGroup->mStatements) {
            for (const GARXDatum &aDatum: aStatement->mDatums) {
                if (aDatum.mKind == GARXDatumKind::kPlugKey) {
                    aResult++;
                }
            }
        }
    }
    
    return aResult;
}

static bool AssignPlugPairs(std::vector<GARXStatementGroup *> &pGroups,
                            std::vector<GARXTypePair> &pPairs,
                            std::vector<int> &pRotations,
                            std::vector<int> &pOffsets) {
    
    int aPlugSlotCount = CountPlugSlots(pGroups);
    const std::size_t aPlugSlotCountU = static_cast<std::size_t>(aPlugSlotCount);
    
    if (pPairs.empty()) {
        printf("Plug assignment failed: empty pair pool\n");
        return false;
    }
    
    if (aPlugSlotCountU > pRotations.size()) {
        printf("Plug rotation assignment failed: slots=%d rotations=%zu\n",
               aPlugSlotCount,
               pRotations.size());
        return false;
    }

    if (aPlugSlotCountU > pOffsets.size()) {
        printf("Plug offset assignment failed: slots=%d offsets=%zu\n",
               aPlugSlotCount,
               pOffsets.size());
        return false;
    }
    
    std::size_t aPlugIndex = 0;
    
    for (GARXStatementGroup *aGroup: pGroups) {
        for (GARXStatementPlan *aStatement: aGroup->mStatements) {
            for (GARXDatum &aDatum: aStatement->mDatums) {
                if (aDatum.mKind == GARXDatumKind::kPlugKey) {
                    if (aPlugIndex >= pRotations.size() ||
                        aPlugIndex >= pOffsets.size()) {
                        return false;
                    }

                    const GARXTypePair &aPair = pPairs[aPlugIndex % pPairs.size()];
                    aDatum.mPlugTypeA = aPair.mTypeA;
                    aDatum.mPlugTypeB = aPair.mTypeB;
                    aDatum.mRotationAmount = pRotations[aPlugIndex];
                    aDatum.mOffsetAmount = pOffsets[aPlugIndex];
                    
                    aPlugIndex++;
                }
            }
        }
    }
    
    return (aPlugIndex == aPlugSlotCountU);
}

bool GARXAssignPlugs(std::vector<GARXStatementGroup *> &pStatementGroups) {
    
    std::vector<GARXTypePair> aPlugPairs = MakePlugPairPool();
    std::vector<int> aPlugRotations = cPlugRotations;
    std::vector<int> aPlugOffsets = cPlugOffsets;
    
    Random::Shuffle(&aPlugPairs);
    Random::Shuffle(&aPlugRotations);
    Random::Shuffle(&aPlugOffsets);
    
    if (AssignPlugPairs(pStatementGroups, aPlugPairs, aPlugRotations, aPlugOffsets) == false) {
        return false;
    }
    
    return true;
}
