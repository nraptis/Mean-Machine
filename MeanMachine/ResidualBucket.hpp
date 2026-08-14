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
    void                                    FlattenUsageCounts(std::uint8_t pUsageCount);
    std::size_t                             CountValidResiduals() const;
    std::vector<TwistWorkSpaceSlot>         Withdraw(const std::string &pStageName,
                                                     int pCount);
    void                                    Print(const std::string &pStageName) const;

    // Control generators use quiet recording to produce complete residual
    // flows. Production generation loads one of those flows and replays each
    // withdrawal exactly, while retaining the normal usage-tier checks.
    void                                    SetVerbose(bool pVerbose);
    void                                    BeginWithdrawalRecording();
    const std::vector<std::vector<TwistWorkSpaceSlot>> &
                                            RecordedWithdrawals() const;
    bool                                    SetPlannedWithdrawals(
                                                        const std::vector<std::vector<TwistWorkSpaceSlot>> &pWithdrawals,
                                                        std::string *pErrorMessage = nullptr);
    bool                                    FinishPlannedWithdrawals(
                                                        std::string *pErrorMessage = nullptr);

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
    bool                                    mVerbose = true;
    bool                                    mRecordWithdrawals = false;
    std::vector<std::vector<TwistWorkSpaceSlot>>
                                            mRecordedWithdrawals;
    std::vector<std::vector<TwistWorkSpaceSlot>>
                                            mPlannedWithdrawals;
    std::size_t                             mPlannedWithdrawalIndex = 0U;
};

#endif /* ResidualBucket_hpp */
