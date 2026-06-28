//
//  GRunMatrixDiffusion.hpp
//  MeanMachine
//
//  Created by Dragon on 5/15/26.
//

#ifndef GRunMatrixDiffusion_hpp
#define GRunMatrixDiffusion_hpp

#include "GSymbol.hpp"
#include "GSeedProgram.hpp"

#include <string>

struct GRunMatrixDiffusionConfig {
    
    GSymbol                                 mInputA;
    GSymbol                                 mInputB;
    GSymbol                                 mOutputA;
    GSymbol                                 mOutputB;

    GSymbol                                 mShuffleEntropyA;
    GSymbol                                 mShuffleEntropyB;
    
    GSymbol                                 mOperationSourceA;
    GSymbol                                 mOperationSourceB;
    
    bool                                    mUseDomainWords = true;
};

class GRunMatrixDiffusion {
public:
    static bool                             Bake(const GRunMatrixDiffusionConfig &pConfig,
                                                 GBatch *pBatch,
                                                 std::string *pErrorMessage);
};

#endif /* GRunMatrixDiffusion_hpp */
