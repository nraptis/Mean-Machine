//
//  GRunMaskWeaveDiffusion.hpp
//  MeanMachine
//

#ifndef GRunMaskWeaveDiffusion_hpp
#define GRunMaskWeaveDiffusion_hpp

#include "GMasking.hpp"
#include <string>

struct GRunMaskWeaveDiffusionConfig {
    
    GSymbol                                 mInputA;
    GSymbol                                 mInputB;
    GSymbol                                 mOutput;
    
    GSymbol                                 mMaskLane;
    GSymbol                                 mMaskDomainWord;
    
    TwistMaskWeaveType                      mWeaveType;
    
};

class GRunMaskWeaveDiffusion {
public:
    static bool                             Bake(const GRunMaskWeaveDiffusionConfig &pConfig,
                                                 GBatch *pBatch,
                                                 std::string *pErrorMessage);
};

#endif /* GRunMaskWeaveDiffusion_hpp */
