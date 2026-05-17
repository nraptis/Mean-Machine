//
//  GARXFormat.hpp
//  MeanMachine
//
//  Created by Dragon on 5/15/26.
//

#ifndef GARXFormat_hpp
#define GARXFormat_hpp

#include <cstdint>
#include <cstddef>
#include <vector>
#include "GARXTypes.hpp"

enum class GARXGroupType : std::uint8_t;

class GARXFormat {
public:
    virtual ~GARXFormat() = default;

    virtual const char *Name() const = 0;
    virtual std::size_t PlanWidth() const = 0;
    virtual std::size_t PassCount() const = 0;
    virtual std::size_t MaxPlanWidth() const = 0;

    virtual std::vector<GARXType> OrbiterTypes() const = 0;
    virtual std::vector<GARXType> UnwindTypes() const = 0;

    virtual const std::vector<int> &PassSaltBiases() const = 0;

    virtual int PickLoopSaltLane(GARXGroupType pGroupType,
                                 std::size_t pLoopKeyIndexInPhase,
                                 std::size_t pLoopKeyIndexInStatement) const = 0;
    virtual int PickForwardPlugSaltLane(std::size_t pPlugIndexInGroup,
                                        std::size_t pForwardGroupIndex,
                                        std::size_t pPassIndex) const = 0;
    virtual int PickSeedPlugSaltLane(std::size_t pPlugIndexInPhase) const = 0;
    virtual int PickUnwindPlugSaltLane(std::size_t pPlugIndexInPhase) const = 0;
};

class GARXFormatSixSixFour final : public GARXFormat {
public:
    static const GARXFormatSixSixFour &Shared();

    const char *Name() const override;
    std::size_t PlanWidth() const override;
    std::size_t PassCount() const override;
    std::size_t MaxPlanWidth() const override;

    std::vector<GARXType> OrbiterTypes() const override;
    std::vector<GARXType> UnwindTypes() const override;

    const std::vector<int> &PassSaltBiases() const override;

    int PickLoopSaltLane(GARXGroupType pGroupType,
                         std::size_t pLoopKeyIndexInPhase,
                         std::size_t pLoopKeyIndexInStatement) const override;
    int PickForwardPlugSaltLane(std::size_t pPlugIndexInGroup,
                                std::size_t pForwardGroupIndex,
                                std::size_t pPassIndex) const override;
    int PickSeedPlugSaltLane(std::size_t pPlugIndexInPhase) const override;
    int PickUnwindPlugSaltLane(std::size_t pPlugIndexInPhase) const override;
};

#endif /* GARXFormat_hpp */
