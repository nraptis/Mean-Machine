#ifndef ResidualBucket_hpp
#define ResidualBucket_hpp

#include "Library - Twist/TwistWorkSpace.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

class ResidualBucket {
public:
    void                                    AddResiduals(const std::string &pStageName,
                                                        std::vector<TwistWorkSpaceSlot> pResiduals);
    void                                    AddResiduals(const std::string &pStageName,
                                                        std::vector<TwistWorkSpaceSlot> pResiduals,
                                                        std::uint8_t pInitialUsageCount);
    void                                    AddResiduals(std::vector<TwistWorkSpaceSlot> pResiduals,
                                                        std::uint8_t pInitialUsageCount = 0U);
    void                                    Remove(const std::vector<TwistWorkSpaceSlot> &pResiduals);
    std::size_t                             CountValidResiduals() const;
    std::vector<TwistWorkSpaceSlot>         Withdraw(const std::string &pStageName,
                                                     int pCount);
    void                                    Print(const std::string &pStageName) const;

private:
    struct Entry {
        TwistWorkSpaceSlot                  mResidual = TwistWorkSpaceSlot::kInvalid;
        std::uint8_t                        mUsageCount = 0U;
    };

    void                                    AddResidualsInternal(
                                                        const std::string &pStageName,
                                                        std::vector<TwistWorkSpaceSlot> pResiduals,
                                                        std::uint8_t pInitialUsageCount,
                                                        bool pPrintAddedResiduals);

    std::vector<Entry>                      mEntries;
};

#endif /* ResidualBucket_hpp */
