//
//  GSBoxFamily.hpp
//  MeanMachine
//
//  Created by Dragon on 5/2/26.
//

#ifndef GSBoxFamily_hpp
#define GSBoxFamily_hpp

#include "Random.hpp"
#include "GSymbol.hpp"
#include <vector>
#include <limits>

#define FAMILY_SIZE 4
#define FAMILY_DEPTH 8
#define FAMILY_MAX_CANDIDATE_COUNT 12

class GBoxFamily {
    
public:
    
    // pList is a list of all unique s-boxes
    // pCount can be > pList.size()
    // We want to minimize collisions.
    // Order doesn't matter.
    void                    Build(std::vector<GSymbol> pList, int pCount);
    
    GSymbol                 mBox[FAMILY_SIZE][FAMILY_DEPTH];
    
private:
    
    // Which one we picked for this slot.
    int                     mChosen[FAMILY_SIZE][FAMILY_DEPTH];
    
    // Global usage
    int                     mReserved[FAMILY_MAX_CANDIDATE_COUNT];
    
};

class GRotationFamily {
public:
    
    static std::vector<int>     GetListLow();
    static std::vector<int>     GetListMedium();
    static std::vector<int>     GetListHigh();
    static std::vector<int>     GetListAll();
    
    
    // Max pCount is 8.
    void                        Build(int pCount);
    
    int                         mLow[FAMILY_SIZE][FAMILY_DEPTH];
    int                         mMedium[FAMILY_SIZE][FAMILY_DEPTH];
    int                         mHigh[FAMILY_SIZE][FAMILY_DEPTH];
    int                         mHealthy[FAMILY_SIZE][FAMILY_DEPTH];
    
private:
    
    void                        BuildGroup(int pDest[FAMILY_SIZE][FAMILY_DEPTH],
                                       std::vector<int> pList,
                                       int pCount,
                                       bool pAvoidExisting);
    
    int                         GetExistingCollisionScore(int pFamily,
                                                     int pSlot,
                                                     int pValue);
    
    void                        ShuffleFamilies();
    
};

class GOperationFamily {
public:
    
    // pOptions is a list of operation IDs.
    // pCount can be > pOptions.size().
    // Max pCount is FAMILY_DEPTH.
    void                    Build(int pCount, std::vector<std::uint8_t> pOptions);
    
    std::uint8_t            mOperation[FAMILY_SIZE][FAMILY_DEPTH];
    
private:
    
    void                    BuildGroup(std::uint8_t pDest[FAMILY_SIZE][FAMILY_DEPTH],
                                       std::vector<std::uint8_t> pList,
                                       int pCount,
                                       bool pAvoidExisting);
    
    int                     GetExistingCollisionScore(int pFamily,
                                                      int pSlot,
                                                      std::uint8_t pValue);
    
    void                    ShuffleFamilies();
};


#endif /* GSBoxFamily_hpp */
