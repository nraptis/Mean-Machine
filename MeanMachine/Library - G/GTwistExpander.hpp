//
//  GTwistExpander.hpp
//  MeanMachine
//

#ifndef GGTwistExpander_hpp
#define GGTwistExpander_hpp

#include "GSeedProgram.hpp"
#include "TwistExpander.hpp"

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

    void                                KDF_A(std::uint64_t pNonce,
                                              TwistDomainConstants *pDomainConstants,
                                              TwistDomainSaltSet *pDomainSaltSet) override;

    void                                KDF_B(std::uint64_t pNonce,
                                              TwistDomainConstants *pDomainConstants,
                                              TwistDomainSaltSet *pDomainSaltSet) override;

    void                                Seed(TwistWorkSpace *pWorkSpace,
                                             TwistFarmSalt *pFarmSalt,
                                             std::uint64_t pNonce,
                                             std::uint8_t *pSource,
                                             std::uint8_t *pPassword,
                                             unsigned int pPasswordByteLength) override;
    void                                TwistBlock(TwistWorkSpace *pWorkSpace,
                                                   std::uint64_t pNonce,
                                                   std::uint8_t *pSource,
                                                   std::uint8_t *pDestination) override;

    bool                                ExportCPPProjectRoot(const std::string &pRootPath,
                                                             std::string *pErrorMessage = nullptr) const;
    bool                                ExportJSONProjectRoot(const std::string &pRootPath,
                                                              std::string *pErrorMessage = nullptr) const;
    bool                                LoadJSONProjectRoot(const std::string &pJsonPath,
                                                            std::string *pErrorMessage = nullptr);

    void                                RefreshTablePointers();

    std::string                         mNameBase;
    TwistProgramBranch                  mKDF_A; // KDF-A branch
    TwistProgramBranch                  mKDF_B; // KDF-B branch
    TwistProgramBranch                  mSeed; // Seed branch
    TwistProgramBranch                  mTwister; // Twist branch

    unsigned char                       mInitialValue_Carry;
    unsigned char                       mInitialValue_Value;
    unsigned char                       mInitialValue_Permute;

private:
    void                                ExecuteKDFBranch(const TwistProgramBranch &pBranch,
                                                         const char *pBranchName,
                                                         std::uint64_t pNonce,
                                                         TwistDomainConstants *pDomainConstants,
                                                         TwistDomainSaltSet *pDomainSaltSet);

};

#endif /* GGTwistExpander_hpp */
