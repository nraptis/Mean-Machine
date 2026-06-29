//
//  SnapShotter.hpp
//  MeanMachine
//
//  Created by icarus black on 6/28/26.
//

#ifndef SnapShotter_hpp
#define SnapShotter_hpp

#include "TwistWorkSpace.hpp"
#include "TwistExpander.hpp"
#include <string>
#include <vector>

struct SnapShotterSlice {
    
    std::string                             mName;
    
    std::uint8_t                            mKeyBoxA[H_KEY][W_KEY];
    std::uint8_t                            mKeyBoxB[H_KEY][W_KEY];
    
    std::uint8_t                            mSource[S_BLOCK];
    
    std::uint8_t                            mExpansionLaneA[S_BLOCK];
    std::uint8_t                            mExpansionLaneB[S_BLOCK];
    std::uint8_t                            mExpansionLaneC[S_BLOCK];
    std::uint8_t                            mExpansionLaneD[S_BLOCK];
    
    std::uint8_t                            mWorkLaneA[S_BLOCK];
    std::uint8_t                            mWorkLaneB[S_BLOCK];
    std::uint8_t                            mWorkLaneC[S_BLOCK];
    std::uint8_t                            mWorkLaneD[S_BLOCK];
    
    std::uint8_t                            mOperationLaneA[S_BLOCK];
    std::uint8_t                            mOperationLaneB[S_BLOCK];
    std::uint8_t                            mOperationLaneC[S_BLOCK];
    std::uint8_t                            mOperationLaneD[S_BLOCK];
    
    std::uint8_t                            mSnowLaneA[S_BLOCK];
    std::uint8_t                            mSnowLaneB[S_BLOCK];
    std::uint8_t                            mSnowLaneC[S_BLOCK];
    std::uint8_t                            mSnowLaneD[S_BLOCK];
    
    std::uint8_t                            mFireLaneA[S_BLOCK];
    std::uint8_t                            mFireLaneB[S_BLOCK];
    std::uint8_t                            mFireLaneC[S_BLOCK];
    std::uint8_t                            mFireLaneD[S_BLOCK];
    
    std::uint8_t                            mInvestLaneA[S_BLOCK];
    std::uint8_t                            mInvestLaneB[S_BLOCK];
    std::uint8_t                            mInvestLaneC[S_BLOCK];
    std::uint8_t                            mInvestLaneD[S_BLOCK];
    
    std::uint8_t                            mInvestLaneE[S_BLOCK];
    std::uint8_t                            mInvestLaneF[S_BLOCK];
    std::uint8_t                            mInvestLaneG[S_BLOCK];
    std::uint8_t                            mInvestLaneH[S_BLOCK];
    
    TwistDomainBundle                       mDomainBundle;
    
    TwistDomainBundle                       mDomainBundleInbuilt;
    TwistDomainBundle                       mDomainBundleEphemeral;
    
};

class SnapShotter {
public:
    
    static void SnapStart_KDFA(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander);
    static void SnapUpdate_KDFA(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander, std::string pName);
    
    static void SnapStart_KDFB(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander);
    static void SnapUpdate_KDFB(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander, std::string pName);
    
    
    static void SnapStart_SEED(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander);
    static void SnapUpdate_SEED(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander, std::string pName);
    
    static void SnapStart_TWIST(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander);
    static void SnapUpdate_TWIST(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander, std::string pName);
    
    static const std::vector<SnapShotterSlice> &Slices_KDFA();
    static const std::vector<SnapShotterSlice> &Slices_KDFB();
    static const std::vector<SnapShotterSlice> &Slices_SEED();
    static const std::vector<SnapShotterSlice> &Slices_TWIST();
    
    static void ClearAll();
    
    static bool SaveProjectRoot(const std::string &pFolder,
                                const std::string &pFileName);
    
};

#endif /* SnapShotter_hpp */
