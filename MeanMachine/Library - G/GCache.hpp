//
//  GCache.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/3/26.
//

#ifndef GCache_hpp
#define GCache_hpp

#define CACHE_MAX_FETCH 8
#define CACHE_MAX_HISTORY 32
#define CACHE_MAX_STORAGE 64

#include <vector>

#include "GSymbol.hpp"
#include "Random.hpp"
#include "TwistMix64.hpp"
#include "TwistFastMatrix.hpp"
#include "GARXSkeleton.hpp"


template <typename T>
class GCacheHistory {
public:

    GCacheHistory() {
        mHistoryCount = 0;
    }
    
    void Record(T *pItemBus, int pCount) {
        if (pCount > 0) {
            ShiftHistory();
            int aCount = pCount;
            if (aCount > CACHE_MAX_FETCH) { aCount = CACHE_MAX_FETCH; }
            for (int n=0; n<aCount; n++) {
                mHistory[0][n] = pItemBus[n];
            }
            mHistoryChunkSize[0] = aCount;
            if (mHistoryCount < CACHE_MAX_HISTORY) {
                mHistoryCount++;
            }
        }
    }

    int Poll(T pItem) {
        for (int i=0; i<mHistoryCount; i++) {
            int aCeiling = mHistoryChunkSize[i];
            if (aCeiling > CACHE_MAX_FETCH) { aCeiling = CACHE_MAX_FETCH; }
            
            for (int n=0; n<aCeiling; n++) {
                if (mHistory[i][n] == pItem) {
                    return i;
                }
            }
        }
        // infinite distance, this item has
        // never been used.
        return CACHE_MAX_HISTORY;
    }

private:
    T                                           mHistory[CACHE_MAX_HISTORY][CACHE_MAX_FETCH];
    int                                         mHistoryChunkSize[CACHE_MAX_HISTORY];
    int                                         mHistoryCount;

    void ShiftHistory() {
        for (int i = CACHE_MAX_HISTORY - 1; i > 0; i--) {
            for (int n=0; n<CACHE_MAX_FETCH; n++) {
                mHistory[i][n] = mHistory[i - 1][n];
            }
            mHistoryChunkSize[i] = mHistoryChunkSize[i - 1];
        }
    }
};

template <typename T>
class GCache {
public:

    GCache() {
        mPoolCount = 0;
        mLimitTierS = 2;
        mLimitTierA = 3;
        mLimitTierB = 4;
    }

    void SetLimits(int pLimitTierS, int pLimitTierA, int pLimitTierB) {
        mLimitTierS = pLimitTierS;
        mLimitTierA = pLimitTierA;
        mLimitTierB = pLimitTierB;
    }

    void AddItem(T pItem) {
        
        if (mPoolCount >= CACHE_MAX_STORAGE) {
            printf("fatal: cache overflow...\n");
            return;
        }
        
        mPool[mPoolCount] = pItem;
        mPoolCount++;
    }

    void AddItems(std::vector<T> pItems) {
        for (int i=0; i<pItems.size(); i++) {
            AddItem(pItems[i]);
        }
    }
    
    void AddItems(std::vector<T> *pItems) {
        if (pItems != nullptr) {
            for (int i=0; i<pItems->size(); i++) {
                AddItem((*pItems)[i]);
            }
        }
    }
    
    void LinkSharedHistory(GCacheHistory<T> *pHistory) {
        mCaches.push_back(pHistory);
    }

    void Fetch(int pCount) {
        
        if (mPoolCount <= 0) {
            printf("fatal: bad cache usage, empty pool.\n");
            return;
        }
        
        int aFetchCount = pCount;
        if (aFetchCount > CACHE_MAX_FETCH) {
            printf("fatal: bad cache usage, trued to fetch too many.\n");
            aFetchCount = CACHE_MAX_FETCH;
        }
        if (aFetchCount <= 0) {
            printf("fatal: bad cache usage, empty fetch.\n");
            return;
        }
        
        for (int i=0; i<mPoolCount; i++) {
            mPoolUsage[i] = 0;
        }
        
        int aCollectedCount = 0;
        while (aCollectedCount < aFetchCount) {
            
            // consider the ones we've used the least number of times on this fetch.
            
            int aLowestUsage = CACHE_MAX_FETCH;
            for (int i=0; i<mPoolCount; i++) {
                aLowestUsage = std::min(aLowestUsage, mPoolUsage[i]);
            }
            
            int aPremiumCount = 0;
            for (int i=0; i<mPoolCount; i++) {
                if (mPoolUsage[i] == aLowestUsage) {
                    mPoolPremium[aPremiumCount] = mPool[i];
                    aPremiumCount++;
                }
            }
            
            if (aPremiumCount <= 0) {
                printf("fatal: universe fell into a blank hole\n");
                return;
            }
            
            std::vector<T> aPoolS;
            std::vector<T> aPoolA;
            std::vector<T> aPoolB;
            std::vector<T> aPoolC;
            
            for (int i=0; i<aPremiumCount; i++) {
                int aMinPoll = mHistory.Poll(mPoolPremium[i]);
                for (int q=0; q<mCaches.size(); q++) {
                    aMinPoll = std::min(aMinPoll, mCaches[q]->Poll(mPoolPremium[i]));
                }
                if (aMinPoll >= mLimitTierB) {
                    aPoolA.push_back(mPoolPremium[i]);
                } else if (aMinPoll >= mLimitTierA) {
                    aPoolB.push_back(mPoolPremium[i]);
                } else if (aMinPoll >= mLimitTierS) {
                    aPoolB.push_back(mPoolPremium[i]);
                } else {
                    aPoolC.push_back(mPoolPremium[i]);
                }
            }
            
            T aSelected;
            if (aPoolS.size() > 0) {
                aSelected = aPoolS[Random::Get((int)aPoolS.size())];
            } else if (aPoolA.size() > 0) {
                aSelected = aPoolA[Random::Get((int)aPoolA.size())];
            } else if (aPoolB.size() > 0) {
                aSelected = aPoolB[Random::Get((int)aPoolB.size())];
            } else if (aPoolC.size() > 0) {
                aSelected = aPoolC[Random::Get((int)aPoolC.size())];
            } else {
                printf("fatal: universe inverted into an incoorect plane\n");
                return;
            }
            
            mBus[aCollectedCount] = aSelected;
            aCollectedCount++;
            
            for (int i=0; i<mPoolCount; i++) {
                if (mPool[i] == aSelected) {
                    mPoolUsage[i]++;
                }
            }
        }
        
        for (int i=aFetchCount-1; i>0; i--) {
            int aPick = Random::Get(i + 1);
            T aTemp = mBus[i];
            mBus[i] = mBus[aPick];
            mBus[aPick] = aTemp;
        }
        
        // This all get used at the same time...
        mHistory.Record(mBus, aFetchCount);
    }

    T                                           mBus[CACHE_MAX_FETCH];
    
    GCacheHistory<T>                            mHistory;
    
private:
    
    // All the available items
    // that we can fetch
    T                                           mPool[CACHE_MAX_STORAGE];
    int                                         mPoolCount;
    
    // The items which were fetched
    // the lest number of times
    // on the current fetch
    T                                           mPoolPremium[CACHE_MAX_STORAGE];
    
    // How many times we've taken this
    // item on the current fetch.
    int                                         mPoolUsage[CACHE_MAX_STORAGE];
    
    std::vector<GCacheHistory<T> *>             mCaches;
    int                                         mLimitTierS;
    int                                         mLimitTierA;
    int                                         mLimitTierB;
    
};

// Original concrete names.
using GSymbolCacheHistory = GCacheHistory<GSymbol*>;
using GSymbolCache = GCache<GSymbol*>;

using GIntCacheHistory = GCacheHistory<int>;
using GIntCache = GCache<int>;

using GMix644CacheHistory = GCacheHistory<Mix64Type_4>;
using GMix644Cache = GCache<Mix64Type_4>;

using GMix648CacheHistory = GCacheHistory<Mix64Type_8>;
using GMix648Cache = GCache<Mix64Type_8>;

using GUnrollCacheHistory = GCacheHistory<TwistFastMatrixUnrollScheme>;
using GUnrollCache = GCache<TwistFastMatrixUnrollScheme>;

using GARXTypeCacheHistory = GCacheHistory<GARXType>;
using GARXTypeCache = GCache<GARXType>;



#endif /* GCache_hpp */
