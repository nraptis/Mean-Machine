//
//  GRunMatrixDiffusion.hpp
//  MeanMachine
//
//  Created by Dragon on 5/15/26.
//

#ifndef GRunMatrixDiffusion_hpp
#define GRunMatrixDiffusion_hpp

#include "GFastMatrix.hpp"

#include <string>

struct GRunMatrixDiffusionConfig {
    
    GSymbol                                 mSelect;
    
    GSymbol                                 mInputA;
    GSymbol                                 mInputB;
    GSymbol                                 mOutputA;
    GSymbol                                 mOutputB;

    GSymbol                                 mShuffleEntropyA;
    GSymbol                                 mShuffleEntropyB;
    GSymbol                                 mShuffleEntropyC;
    GSymbol                                 mShuffleEntropyD;

    GSymbol                                 mOperationSourceA;
    GSymbol                                 mOperationSourceB;
};

class GRunMatrixDiffusion {
public:
    static bool                             Bake(const GRunMatrixDiffusionConfig &pConfig,
                                                 GBatch *pBatch,
                                                 std::string *pErrorMessage);
};

#endif /* GRunMatrixDiffusion_hpp */
