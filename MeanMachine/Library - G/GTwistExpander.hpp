//
//  GTwistExpander.hpp
//  MeanMachine
//

#ifndef GGTwistExpander_hpp
#define GGTwistExpander_hpp

#include "GSeedProgram.hpp"
#include "GSeedRunStageConfig.hpp"
#include "TwistExpander.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

enum class TwistProgramBranchStepType : std::uint8_t {
    kBatch = 0,
    kLine = 1
};

struct TwistProgramBranchStep {
    TwistProgramBranchStepType              mType = TwistProgramBranchStepType::kBatch;
    std::size_t                             mIndex = 0U;
};

class TwistProgramBranch {
public:
    void                                AddBatch(const GBatch &pBatch);
    void                                AddLine(const std::string &pLine);
    void                                AddWorkspaceAliasLine(const std::string &pAliasName,
                                                              const std::string &pWorkSpaceFieldName);
    void                                AddAssignByteLine(const std::string &pName,
                                                          std::uint8_t pValue);
    void                                Clear();
    const std::vector<std::string>&     GetBatchJsonText() const;
    const std::vector<std::string>&     GetStringLines() const;
    const std::vector<TwistProgramBranchStep>& GetSteps() const;

private:
    std::vector<std::string>            mBatchJsonText;
    std::vector<std::string>            mStringLines;
    std::vector<TwistProgramBranchStep> mSteps;

    friend class GTwistExpander;
};

class GTwistExpander : public TwistExpander {
public:
    GTwistExpander();
    ~GTwistExpander() override;

    void                                KDF(std::uint64_t pNonce,
                                            TwistDomainConstants *pDomainConstants,
                                            TwistDomainSaltSet *pDomainSaltSet) override;

    void                                Seed(TwistWorkSpace *pWorkSpace,
                                             TwistFarmSalt *pFarmSalt,
                                             std::uint64_t pNonce,
                                             std::uint8_t *pPassword,
                                             std::size_t pPasswordByteLength,
                                             std::uint8_t *pDestination,
                                             MUTABLE_PARAMS) override;
    void                                TwistBlock(TwistWorkSpace *pWorkSpace,
                                                   std::uint8_t *pSource,
                                                   std::uint8_t *pCrossLaneA,
                                                   std::uint8_t *pCrossLaneB,
                                                   std::uint8_t *pCrossLaneC,
                                                   std::uint8_t *pCrossLaneD,
                                                   std::uint8_t *pDestination,
                                                   bool pStifleKey,
                                                   MUTABLE_PARAMS) override;
    void                                GrowKeyA(TwistWorkSpace *pWorkSpace,
                                                 std::uint8_t *pCrossLaneA,
                                                 std::uint8_t *pCrossLaneB,
                                                 MUTABLE_PARAMS) override;
    void                                GrowKeyB(TwistWorkSpace *pWorkSpace,
                                                 std::uint8_t *pCrossLaneA,
                                                 std::uint8_t *pCrossLaneB,
                                                 MUTABLE_PARAMS) override;

    bool                                ExportCPPProjectRoot(const std::string &pRootPath,
                                                             std::string *pErrorMessage = nullptr) const;
    bool                                ExportJSONProjectRoot(const std::string &pRootPath,
                                                              std::string *pErrorMessage = nullptr) const;
    bool                                LoadJSONProjectRoot(const std::string &pJsonPath,
                                                            std::string *pErrorMessage = nullptr);

    void                                RefreshTablePointers();

    std::string                         mNameBase;
    // Domain-major order: Rotate-A, Rotate-B, Spawn-A, Spawn-B, Twist, Seed.
    // Within each domain: KDF-A, KDF-B, KDF-C.
    std::array<TwistProgramBranch, 18>  mKDFDomainBranches;
    // Domain-major, then KDF family A-C, then stage A-D.
    std::vector<GSeedRunStageConfig>    mKDFStageConfigs;
    TwistProgramBranch                  mSeed; // Seed branch
    TwistProgramBranch                  mTwister; // Twist branch
    TwistProgramBranch                  mGrowKeyA; // Grow key A branch
    TwistProgramBranch                  mGrowKeyB; // Grow key B branch
    std::vector<GSeedRunStageConfig>    mSeedStageConfigs;
    std::vector<GSeedRunStageConfig>    mSeedKeyBoxStageConfigs;
    std::vector<TwistDomain>            mSeedMatrixDomains;
    std::vector<GSeedRunStageConfig>    mTwistStageConfigs;
    std::vector<TwistDomain>            mTwistMatrixDomains;
    // TwistForkKeyHalfA/B partition Twist's final Earth/Crystal pair with
    // complementary odd/even parity alternating across source lanes. Every
    // final block pairs source quarters 0/2 or 1/3, then braids each disjoint
    // half through three shared scratch families. Each fork keeps its W_KEY
    // results in a separate family for its Grow flow.
    std::array<TwistWorkSpaceSlot, 4>   mTwistForkEarthLanes = {{
        TwistWorkSpaceSlot::kEarthLaneA,
        TwistWorkSpaceSlot::kEarthLaneB,
        TwistWorkSpaceSlot::kEarthLaneC,
        TwistWorkSpaceSlot::kEarthLaneD,
    }};
    std::array<TwistWorkSpaceSlot, 4>   mTwistForkCrystalLanes = {{
        TwistWorkSpaceSlot::kCrystalLaneA,
        TwistWorkSpaceSlot::kCrystalLaneB,
        TwistWorkSpaceSlot::kCrystalLaneC,
        TwistWorkSpaceSlot::kCrystalLaneD,
    }};
    std::array<TwistWorkSpaceSlot, 4>   mTwistForkMuLanes = {{
        TwistWorkSpaceSlot::kCelestialLaneA,
        TwistWorkSpaceSlot::kCelestialLaneB,
        TwistWorkSpaceSlot::kCelestialLaneC,
        TwistWorkSpaceSlot::kCelestialLaneD,
    }};
    std::array<TwistWorkSpaceSlot, 4>   mTwistForkLelLanes = {{
        TwistWorkSpaceSlot::kAlchemyLaneA,
        TwistWorkSpaceSlot::kAlchemyLaneB,
        TwistWorkSpaceSlot::kAlchemyLaneC,
        TwistWorkSpaceSlot::kAlchemyLaneD,
    }};
    std::array<TwistWorkSpaceSlot, 4>   mTwistForkGozLanes = {{
        TwistWorkSpaceSlot::kAuguryLaneA,
        TwistWorkSpaceSlot::kAuguryLaneB,
        TwistWorkSpaceSlot::kAuguryLaneC,
        TwistWorkSpaceSlot::kAuguryLaneD,
    }};
    std::array<TwistWorkSpaceSlot, 4>   mTwistForkFinalALanes = {{
        TwistWorkSpaceSlot::kSpiritLaneA,
        TwistWorkSpaceSlot::kSpiritLaneB,
        TwistWorkSpaceSlot::kSpiritLaneC,
        TwistWorkSpaceSlot::kSpiritLaneD,
    }};
    std::array<TwistWorkSpaceSlot, 4>   mTwistForkFinalBLanes = {{
        TwistWorkSpaceSlot::kDivinationLaneA,
        TwistWorkSpaceSlot::kDivinationLaneB,
        TwistWorkSpaceSlot::kDivinationLaneC,
        TwistWorkSpaceSlot::kDivinationLaneD,
    }};
    std::vector<GSeedRunStageConfig>    mGrowAStageConfigs;
    std::vector<GSeedRunStageConfig>    mGrowBStageConfigs;
    TwistDomain                         mGrowAMatrixDomain = TwistDomain::kInvalid;
    TwistDomain                         mGrowBMatrixDomain = TwistDomain::kInvalid;
    std::size_t                         mControlCandidateIndex = 0U;

};

#endif /* GGTwistExpander_hpp */
