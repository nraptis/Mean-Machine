#include "GMoxPlugPolicy.hpp"

static const int kPlugRotations[] = {
    5, 7, 11, 13,
    17, 19, 23, 29,
    31, 37, 41, 43,
    47, 53, 59, 61
};

static const int kPlugOffsets[] = {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
};

std::vector<GMoxType> GMoxPlugPolicy::MakeTapPool(const GMoxFormat &format,
                                                  std::size_t passIndex,
                                                  std::size_t groupIndex) const {
    std::vector<GMoxType> result;

    result.push_back(GMoxType::Stream(GMoxStreamKind::kCurrent));
    result.push_back(GMoxType::Stream(GMoxStreamKind::kPrevious));
    result.push_back(GMoxType::Stream(GMoxStreamKind::kScatter));
    result.push_back(GMoxType::Stream(GMoxStreamKind::kCross));

    if (mTapClass == GMoxPlugTapClass::kStreamAndCarry ||
        mTapClass == GMoxPlugTapClass::kAnyNonOutputHidden) {
        result.push_back(GMoxType::Carry());
    }

    const bool allowIntermediateHidden =
        mTapClass == GMoxPlugTapClass::kStreamAndIntermediateHidden &&
        mEnableHiddenStatePlugOnIntermediateRound &&
        passIndex == mHiddenPlugPassIndex &&
        groupIndex >= mHiddenPlugGroupIndex;

    if (allowIntermediateHidden ||
        mTapClass == GMoxPlugTapClass::kAnyNonOutputHidden) {
        std::vector<GMoxType> wanderers = format.Wanderers();

        for (const GMoxType &wanderer : wanderers) {
            result.push_back(wanderer);
        }
    }

    return result;
}

bool GMoxPlugPolicy::Assign(std::vector<GMoxStatementGroup *> &groups,
                            const GMoxFormat &format,
                            std::size_t passIndex) const {
    
    std::size_t plugIndex = 0;

    for (std::size_t groupIndex = 0; groupIndex < groups.size(); groupIndex++) {
        GMoxStatementGroup *group = groups[groupIndex];

        if (group == nullptr) {
            return false;
        }

        std::vector<GMoxType> tapPool = MakeTapPool(format, 0, groupIndex);

        if (tapPool.size() < 2) {
            return false;
        }

        for (GMoxStatement *statement : group->mStatements) {
            if (statement == nullptr) {
                return false;
            }

            for (GMoxDatum &datum : statement->mDatums) {
                if (datum.mKind != GMoxDatumKind::kPlugKey) {
                    continue;
                }

                const std::size_t tapAIndex = plugIndex % tapPool.size();
                const std::size_t tapBIndex = (plugIndex + 1) % tapPool.size();

                datum.mPlugTypeA = tapPool[tapAIndex];
                datum.mPlugTypeB = tapPool[tapBIndex];

                datum.mRotationAmount =
                    kPlugRotations[plugIndex % (sizeof(kPlugRotations) / sizeof(kPlugRotations[0]))];

                datum.mOffsetAmount =
                    kPlugOffsets[plugIndex % (sizeof(kPlugOffsets) / sizeof(kPlugOffsets[0]))];

                datum.mSaltLaneIndex =
                    static_cast<int>(plugIndex % format.mPlugLaneCount);

                plugIndex++;
            }
        }
    }

    return true;
}
