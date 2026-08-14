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
    GSymbol                                 mInputC;
    GSymbol                                 mInputD;
    GSymbol                                 mOutputA;
    GSymbol                                 mOutputB;
    GSymbol                                 mOutputC;
    GSymbol                                 mOutputD;

    GSymbol                                 mEntropyA;
    GSymbol                                 mEntropyB;
    GSymbol                                 mEntropyC;
    GSymbol                                 mEntropyD;
};

class GRunMatrixDiffusion {
public:
    static bool                             Bake(const GRunMatrixDiffusionConfig &pConfig,
                                                 GBatch *pBatch,
                                                 std::string *pErrorMessage);
};

#endif /* GRunMatrixDiffusion_hpp */
