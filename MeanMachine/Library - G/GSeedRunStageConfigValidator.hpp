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
    // always calls ValidateDestinations, ValidateList, ValidateSequencing
    // max of 4 pPrimarySources
    // all combinations of pPrimarySources [forward, backward] are represented
    static bool                                             ValidateStarter(const GSeedRunStageConfig &pConfig,
                                                                            std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                            std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                            bool pIsSpecialTwelvePassLoop,
                                                                            std::string *pErrorMessage);
    
    // entry point #2
    // always calls ValidateDestinations, ValidateList, ValidateSequencing
    
    static bool                                             ValidateMidstage(const GSeedRunStageConfig &pConfig,
                                                                             std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                             std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                                             std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                                             std::string *pErrorMessage);

    // Terminal midstage packs write lanes for the next non-ARX operation.
    // They still validate source shape and residual use, but they do not require
    // written destinations to be read by later slices.
    static bool                                             ValidateTerminalMidstage(const GSeedRunStageConfig &pConfig,
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
    
    
    // No source is read before it is available from pAllSources or prior destination writes.
    static bool                                             ValidateSequencing(const GSeedRunStageConfig &pConfig,
                                                                               std::vector<TwistWorkSpaceSlot> pAllSources,
                                                                               std::string *pErrorMessage);
    
    
    static bool                                             ValidateImmediatelyUsePreviousDest(const GSeedRunStageConfig &pConfig,
                                                                                               std::string *pErrorMessage);
    
    
    // After a dest is written:
    //      If tail pressure is enabled, it must be used min(remaining passes, 3) times later.
    //      Otherwise, one later use is enough.
    //      If it is required once, that use must force it forward.
    //      If it is required twice or more, it must be forced forward and backward.
    //      The final dest is not expected to have any later use.
    static bool                                             ValidateSufficientDestUsage(const GSeedRunStageConfig &pConfig,
                                                                                       bool pRequireTailReadPressure,
                                                                                       std::string *pErrorMessage);
    
    // We should not use any TwistWorkSpaceSlot twice in ingress
    // We should not use any TwistWorkSpaceSlot twice in cross
    // We should not use any TwistWorkSpaceSlot twice if either of them is 'random' e.g. the last item
    static bool                                             ValidateNonRedundancy(const GSeedRunStageConfig &pConfig,
                                                                                          std::string *pErrorMessage);
    
    // We keep a running list of sources.
    // For each slice:
    //      If source count is 0 or 1, immediately fail
    //      If source count is 2, there must be this exact pattern: ingress = [a, b], cross = [b, a]
    //      If source count is 3, there must be this exact pattern: ingress = [a, b], cross = [a, c]
    //      If source count is 4 or greater, there must be no duplicate. for example ingress = [a, b], cross = [c, a] <= invalid, because 2 a
    static bool                                             ValidateSourceGraph(const GSeedRunStageConfig &pConfig,
                                                                                std::vector<TwistWorkSpaceSlot> pSources,
                                                                                          std::string *pErrorMessage);
    
    
    /*
     residuals are [a, b, c]
     
     we must have slices
     [ingress_1.last = res.a]
     [ingress_2.last = res.b]
     [ingress_3.last = res.c]
     [ingress_4.last = not residual]
     
     
     residuals are [a, b, c, d, e]
     
     we must have slices
     [ingress_1.last = res.a]
     [ceoss_1.last = res.b]
     
     [ingress_2.last = res.c]
     [ingress_3.last = res.d]
     [ingress_4.last = res.e]
     
     residuals.count > (lane.count * 2) => fail
     
     */
    static bool                                             ValidateResidualGraph(const GSeedRunStageConfig &pConfig,
                                                                                std::vector<TwistWorkSpaceSlot> pResiduals,
                                                                                          std::string *pErrorMessage);
    
    
    static bool                                             ValidatePrimaryCombinations(const GSeedRunStageConfig &pConfig,
                                                                                  std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                                          std::string *pErrorMessage);
    
    
    //
    static bool                                             ValidateMidstageSourceDiversity(const GSeedRunStageConfig &pConfig,
                                                                                  std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                                          std::string *pErrorMessage);
    

    
    
    
    
};

#endif /* GSeedRunStageConfigValidator_hpp */
