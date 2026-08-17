//
//  GSeedRunStageConfigValidator.hpp
//  MeanMachine
//

#ifndef GSeedRunStageConfigValidator_hpp
#define GSeedRunStageConfigValidator_hpp

#include "GSeedRunStageConfig.hpp"

#include <string>
#include <vector>

struct SlotAndDirection {
    TwistWorkSpaceSlot      mSlot = TwistWorkSpaceSlot::kInvalid;
    bool                    mForward = false;
};

class GSeedRunStageConfigValidator {
public:
    
    
    // 2 sources: FF, FB, BF, BB
    // 3 source key flow: source/key_a/key_b => FFB, FBF, BFB, BBF
    
    // entry point #1
    // max of 4 pPrimarySources
    // all combinations of pPrimarySources [forward, backward] are represented
    static bool                                             ValidateStarter(const GSeedRunStageConfig &pConfig,
                                                                            std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                            std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                            std::string *pErrorMessage);

    static bool                                             ValidateStarterWithResiduals(const GSeedRunStageConfig &pConfig,
                                                                                         std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                                         std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                                                         std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                                         std::string *pErrorMessage);

    // Exact four-pass key entry graph: eight fixed source lanes, eight
    // inherited residual lanes, and four destinations. Two residual lanes
    // deliberately bridge passes three and four.
    static bool                                             ValidateKeyEightInput(const GSeedRunStageConfig &pConfig,
                                                                                  std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                                  std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                                                  std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                                  std::string *pErrorMessage);

    // Exact four-pass Grow entry graph: four persistent branch lanes, two
    // cross parameters, twelve scheduled residual reads, and four destinations.
    static bool                                             ValidateGrowSixInput(const GSeedRunStageConfig &pConfig,
                                                                                 std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                                 std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                                                 std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                                 std::string *pErrorMessage);
    
    // entry point #2
    
    static bool                                             ValidateMidstage(const GSeedRunStageConfig &pConfig,
                                                                             std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                             std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                                             std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                             std::string *pErrorMessage);

    // entry point #3
    // A trunk starts immediately after matrix diffusion. Its four primary
    // lanes are simultaneous matrix outputs rather than ordered prior writes.
    // At least one residual is required for pass four's wildcard.
    static bool                                             ValidateTrunk(const GSeedRunStageConfig &pConfig,
                                                                          std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                          std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                                          std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                          std::string *pErrorMessage);

private:
    
    static bool                                             IsForcedForward(const GSeedRunStageSliceSpec &pSlice,
                                                                            TwistWorkSpaceSlot pSlot);
    
    static bool                                             IsForcedBackward(const GSeedRunStageSliceSpec &pSlice,
                                                                             TwistWorkSpaceSlot pSlot);
    
    static void                                             AllDirectionCombinationsHelper(std::vector<TwistWorkSpaceSlot> pSlots,
                                                                                           std::vector<bool> *pDirections,
                                                                                           std::vector<std::vector<SlotAndDirection>> *pResult
                                                                                           );
    static std::vector<std::vector<SlotAndDirection>>       AllDirectionCombinations(std::vector<TwistWorkSpaceSlot> pSlots);
    
    // GSeedRunStageConfig has destinations in the exact order
    // the "reversed" is exactly [false, true, false, true, ...]
    static bool                                             ValidateDestinations(const GSeedRunStageConfig &pConfig,
                                                                                 std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                                 std::string *pErrorMessage);
    
    
    // Exactly the items in pSources are in pConfig as sources
    // Exactly the items in pExpectedDestinations are in pConfig as destinations
    static bool                                             ValidateList(const GSeedRunStageConfig &pConfig,
                                                                         std::vector<TwistWorkSpaceSlot> pSources,
                                                                         std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                         std::string *pErrorMessage);

    // Midstages continue from ordered primary writes immediately preceding
    // the stage. Every primary whose fourth-read window reaches this stage
    // must appear in that window.
    static bool                                             ValidateMidstageList(const GSeedRunStageConfig &pConfig,
                                                                                 std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                                 std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                                                 std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                                 std::string *pErrorMessage);
    
    
    // We should not use any TwistWorkSpaceSlot twice in ingress
    // We should not use any TwistWorkSpaceSlot twice in cross
    // We should not use any TwistWorkSpaceSlot twice if either of them is 'random' e.g. the last item
    static bool                                             ValidateNonRedundancy(const GSeedRunStageConfig &pConfig,
                                                                                          std::string *pErrorMessage);
    
    // No destination may be read before it is written. After a write, its
    // required sliding schedule is:
    //      +1 pass: ingress[0]
    //      +2 pass: cross[0]
    //      +3 pass: ingress[1]
    // If another pass is available, it must appear exactly once more at
    // cross[1] at +4. It may not appear again outside that window.
    // Every required appearance is exact and exclusive within its pass.
    static bool                                             ValidateSourceGraph(const GSeedRunStageConfig &pConfig,
                                                                                std::vector<TwistWorkSpaceSlot> pSources,
                                                                                          std::string *pErrorMessage);

    // Apply the source graph to primary lanes written immediately before this
    // midstage, then continue normally through this stage's destinations.
    static bool                                             ValidateSourceGraphMidstage(const GSeedRunStageConfig &pConfig,
                                                                                        std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                                        std::vector<TwistWorkSpaceSlot> pSources,
                                                                                        std::string *pErrorMessage);

    // Validate the exact four-pass matrix-output entry graph, then apply the
    // normal destination source graph to all four or six trunk destinations.
    static bool                                             ValidateSourceGraphTrunk(const GSeedRunStageConfig &pConfig,
                                                                                     std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                                     std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                                                     std::vector<TwistWorkSpaceSlot> pSources,
                                                                                     std::string *pErrorMessage);
    
    
    // Residuals are unique lanes, each read exactly once. They occupy a
    // contiguous suffix of an ingress or cross source list so a pass may
    // carry more than the old single-random-position residual. Fuse lanes are
    // never valid residuals; Operation lanes are allowed. Capacity is four
    // residuals per slice, capped at 18.
    static bool                                             ValidateResidualGraph(const GSeedRunStageConfig &pConfig,
                                                                                std::vector<TwistWorkSpaceSlot> pResiduals,
                                                                                          std::string *pErrorMessage);
    
    
    static bool                                             ValidatePrimaryCombinations(const GSeedRunStageConfig &pConfig,
                                                                                  std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                                          std::string *pErrorMessage);
    
};

#endif /* GSeedRunStageConfigValidator_hpp */
