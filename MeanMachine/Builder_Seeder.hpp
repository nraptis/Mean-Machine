//
//  Builder_Seeder.hpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#ifndef Builder_Seeder_hpp
#define Builder_Seeder_hpp

#include <string>
#include <vector>
#include "GSnow.hpp"
#include "TwistWorkSpace.hpp"

class GTwistExpander;

class Builder_Seeder {
public:
    bool                                    Build(GTwistExpander *pExpander,
                                                  std::string *pErrorMessage);
    
    bool                                    Build_PostKDF(GTwistExpander *pExpander,
                                                  std::string *pErrorMessage);
    
    
    
    
};

#endif /* Builder_Seeder_hpp */
