//
//  GRunMaskBraidDiffusion.hpp
//  MeanMachine
//
//  Created by nicholas on 5/25/26.
//

#ifndef GRunMaskBraidDiffusion_hpp
#define GRunMaskBraidDiffusion_hpp

#include "GMasking.hpp"
#include <string>

struct GRunMaskBraidDiffusionConfig {
    
    GSymbol                                 mInputA;
    GSymbol                                 mInputB;
    
    GSymbol                                 mMaskLane;
    GSymbol                                 mMaskDomainWord;
    
    TwistMaskBraidType                      mBraidType;
    
};

class GRunMaskBraidDiffusion {
public:
    static bool                             Bake(const GRunMaskBraidDiffusionConfig &pConfig,
                                                 GBatch *pBatch,
                                                 std::string *pErrorMessage);
};

#endif /* GRunMaskBraidDiffusion_hpp */
