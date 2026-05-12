//
//  TwistArray.hpp
//  MeanMachine
//

#ifndef TwistArray_hpp
#define TwistArray_hpp

#include <algorithm>
#include <cstddef>
#include <functional>
#include <limits>
#include <unordered_map>
#include <vector>

class TwistArray {
public:
    
    template <typename T>
    static void Append(std::vector<T>* pItems, const std::vector<T>* pItemsToAppend) {
        
        if (pItems == nullptr) {
            return;
        }
        
        if (pItemsToAppend == nullptr) {
            return;
        }
        
        pItems->insert(pItems->end(), pItemsToAppend->begin(), pItemsToAppend->end());
    }

    template <typename T>
    static void RemoveAll(std::vector<T>* pItems, const T& pItem) {
        if (pItems == nullptr) {
            return;
        }

        std::erase(*pItems, pItem);
        
    }
    
    template <typename T>
    static bool Contains(const std::vector<T>* pItems, const T& pItem) {
        if (pItems == nullptr) {
            return false;
        }
        
        return std::find(pItems->begin(), pItems->end(), pItem) != pItems->end();
    }
    
    template <typename T>
    static int MinimumDistance(const std::vector<T> *pItems, const T& pItem) {
        if (pItems == nullptr) {
            return -1;
        }
        
        int aMinimumDistance = -1;
        int aLastIndex = -1;
        
        for (int i = 0; i < static_cast<int>(pItems->size()); i++) {
            if ((*pItems)[static_cast<std::size_t>(i)] == pItem) {
                if (aLastIndex >= 0) {
                    int aDistance = i - aLastIndex;
                    if ((aMinimumDistance < 0) || (aDistance < aMinimumDistance)) {
                        aMinimumDistance = aDistance;
                    }
                }
                aLastIndex = i;
            }
        }
        
        return aMinimumDistance;
    }
    
    template <typename T, typename THash = std::hash<T>>
    static int CountInMap(const std::unordered_map<T, int, THash> *pCounts,
                          const T &pType) {
        if (pCounts == nullptr) {
            return 0;
        }
        
        auto aIterator = pCounts->find(pType);
        if (aIterator == pCounts->end()) {
            return 0;
        }
        
        return aIterator->second;
    }
    
    template <typename T, typename THash = std::hash<T>>
    static bool AllInValidRanges_Pessimistic(const std::vector<T> *pItems,
                                             const std::unordered_map<T, int, THash> *pLowRanges,
                                             const std::unordered_map<T, int, THash> *pHighRanges) {
        if (pItems == nullptr) {
            return false;
        }
        
        std::unordered_map<T, int, THash> aCounts;
        
        for (const T &aItem: *pItems) {
            aCounts[aItem] += 1;
        }
        
        if (pLowRanges != nullptr) {
            for (const auto &aPair: *pLowRanges) {
                const T &aType = aPair.first;
                const int aMinimum = aPair.second;
                const int aCount = CountInMap<T, THash>(&aCounts, aType);
                if (aCount < aMinimum) {
                    return false;
                }
            }
        }
        
        if (pHighRanges != nullptr) {
            for (const auto &aPair: *pHighRanges) {
                const T &aType = aPair.first;
                const int aMaximum = aPair.second;
                const int aCount = CountInMap<T, THash>(&aCounts, aType);
                if (aCount > aMaximum) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    template <typename T, typename THash = std::hash<T>>
    static bool AllInValidRanges_Optimistic(const std::vector<T> *pItems,
                                            const std::unordered_map<T, int, THash> *pLowRanges,
                                            const std::unordered_map<T, int, THash> *pHighRanges) {
        if (pItems == nullptr) {
            return false;
        }
        
        std::unordered_map<T, int, THash> aCounts;
        
        for (const T &aItem: *pItems) {
            aCounts[aItem] += 1;
        }
        
        if (pLowRanges != nullptr) {
            for (const auto &aPair: *pLowRanges) {
                const T &aType = aPair.first;
                const int aMinimum = aPair.second;
                if (aCounts.find(aType) != aCounts.end()) {
                    const int aCount = CountInMap<T, THash>(&aCounts, aType);
                    
                    if (aCount < aMinimum) {
                        return false;
                    }
                }
            }
        }
        
        if (pHighRanges != nullptr) {
            for (const auto &aPair: *pHighRanges) {
                const T &aType = aPair.first;
                const int aMaximum = aPair.second;
                if (aCounts.find(aType) != aCounts.end()) {
                    const int aCount = CountInMap<T, THash>(&aCounts, aType);
                    
                    if (aCount > aMaximum) {
                        return false;
                    }
                }
            }
        }
        
        return true;
    }
    
    template <typename T>
    static std::size_t CountElement(const std::vector<T>* pItems,
                                         const T& pItem) {
        if (pItems == nullptr) {
            return 0U;
        }

        return static_cast<std::size_t>(
            std::count(pItems->begin(), pItems->end(), pItem)
        );
    }

    template <typename T>
    static std::vector<T> Subtract(const std::vector<T>* pItemsA,
                                        const std::vector<T>* pItemsB) {
        std::vector<T> aResult;

        if (pItemsA == nullptr) {
            return aResult;
        }

        if (pItemsB == nullptr || pItemsB->empty()) {
            return *pItemsA;
        }

        aResult.reserve(pItemsA->size());

        for (const T& aItem : *pItemsA) {
            if (std::find(pItemsB->begin(), pItemsB->end(), aItem) == pItemsB->end()) {
                aResult.push_back(aItem);
            }
        }

        return aResult;
    }

    template <typename T>
    static std::vector<T> RemoveDuplicates(const std::vector<T>* pItems) {
        std::vector<T> aResult;

        if (pItems == nullptr) {
            return aResult;
        }

        aResult.reserve(pItems->size());

        for (const T& aItem : *pItems) {
            if (std::find(aResult.begin(), aResult.end(), aItem) == aResult.end()) {
                aResult.push_back(aItem);
            }
        }

        return aResult;
    }

};

#endif
