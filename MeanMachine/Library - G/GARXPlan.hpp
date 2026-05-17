//
//  GARXPlan.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/7/26.
//

#ifndef GARXPlan_hpp
#define GARXPlan_hpp

#include <cstdint>
#include <vector>
#include <unordered_set>
#include "GARXSkeleton.hpp"
#include "GARXFormat.hpp"

class GARXStatementPlan {
public:
    GARXStatementPlan();
    GARXStatementPlan(GARXStatementType pType, GARXType pTarget);
    
    GARXStatementType                               mStatementType;
    GARXGroupType                                   mGroupType;
    GARXType                                        mTarget;
    int                                             mRotationAmount;
    std::vector<GARXDatum>                          mDatums;
};

class GARXRoundSeedPlan {
public:
    GARXRoundSeedPlan();
    GARXRoundSeedPlan(GARXType pTarget, GARXType pState, GARXType pTap);
    
    GARXType                                        mTarget;
    GARXType                                        mState;
    GARXType                                        mTap;
};

class GARXStatementGroup {
public:
    GARXStatementGroup();
    GARXStatementGroup(GARXGroupType pKind);
    
    GARXGroupType                                   mGroupType;
    int                                             mZoneIndex;
    std::vector<GARXStatementPlan *>                mStatements;
    
    
    static const char                               *GetTypeName(GARXGroupType pType);
};

class GARXPassPlan {
public:
    GARXPassPlan();
    ~GARXPassPlan();
    
    std::vector<GARXRoundSeedPlan *>                mRoundSeeds;
    std::vector<GARXStatementPlan *>                mStatements;
    std::vector<GARXStatementGroup *>               mGroups;
    
    GARXBlendInputPlan                              mStreamInputBlend;
    GARXBlendInputPlan                              mSecretInputBlend;
    GARXBlendInputPlan                              mCrossInputBlend;

    GARXBlendInputPlan                              mStreamScatterBlend;
    GARXBlendInputPlan                              mSecretScatterBlend;
    
    GARXCrushPlan                                   mCrushPlan;
    GARXCarryPlan                                   mCarryPlan;
    
};

class GARXPlan;

class GARXPlanPrinter {
public:
    static void                                     Print(GARXPlan *pPlan);
    static void                                     Print(GARXPlan *pPlan,
                                                          bool pIncludePlugs,
                                                          bool pIncludeRotations);
};

class GARXPlan {
public:
    // TODO: Split SecretCurrent into SecretInput and SecretOutput.
    // TODO: Move builder/validator logic out of GARXPlan.cpp.
    // TODO: For byte input blends, interpret blend fields as byte shifts/placements rather than arbitrary 64-bit rotations.
    
    GARXPlan();
    ~GARXPlan();
    
    const GARXFormat                              *mFormat;
    GARXSkeleton                                    mSkeleton;
    std::vector<GARXPassPlan *>                     mPassPlans;
    
    static bool                                     IsValid(GARXPlan *pPlan);
    static bool                                     Bake(GARXPlan *pPlan);

    static bool                                     Configure(GARXPlan *pPlan);
    static bool                                     Configure_ProceedWithGroups(GARXPlan *pPlan);
    
    static void                                     Print(GARXPlan *pPlan);
    static void                                     Print(GARXPlan *pPlan,
                                                          bool pIncludePlugs,
                                                          bool pIncludeRotations);
};

#endif /* GARXPlan_hpp */
