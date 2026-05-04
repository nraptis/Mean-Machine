//
//  TwistArray.hpp
//  MeanMachine
//

#ifndef TwistArray_hpp
#define TwistArray_hpp

#include <algorithm>
#include <cstddef>
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
