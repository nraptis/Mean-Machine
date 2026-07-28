//
//  GKDF.hpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#ifndef GKDF_hpp
#define GKDF_hpp

#include "GSeedProgram.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

enum class GKDFMaterialBundle : std::uint8_t {
    kInbuilt = 0,
    kEphemeral = 1,
    kWorkspace = 2
};

class GKDF_A {
public:
    bool                                Bake(TwistDomain pDomain,
                                             GKDFMaterialBundle pBundle,
                                             std::vector<GStatement> *pStatements,
                                             std::string *pErrorMessage);
    
    std::array<GSymbol, 3>              mKDFSnowLanes;
    
};

class GKDF_B {
public:
    bool                                Bake(TwistDomain pDomain,
                                             GKDFMaterialBundle pBundle,
                                             std::vector<GStatement> *pStatements,
                                             std::string *pErrorMessage);

    std::array<GSymbol, 3>              mKDFSnowLanes;
};

class GKDF_C {
public:
    bool                                Bake(TwistDomain pDomain,
                                             GKDFMaterialBundle pBundle,
                                             std::vector<GStatement> *pStatements,
                                             std::string *pErrorMessage);

    std::array<GSymbol, 3>              mKDFSnowLanes;
};

class GKDF_D {
public:
    bool                                Bake(TwistDomain pDomain,
                                             GKDFMaterialBundle pBundle,
                                             std::vector<GStatement> *pStatements,
                                             std::string *pErrorMessage);

    std::array<GSymbol, 3>              mKDFSnowLanes;
};

#endif /* GKDF_hpp */
