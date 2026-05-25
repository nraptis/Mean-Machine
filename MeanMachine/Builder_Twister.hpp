//
//  Builder_Twister.hpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#ifndef Builder_Twister_hpp
#define Builder_Twister_hpp

#include <string>

class GTwistExpander;

class Builder_Twister {
public:
    bool Build(GTwistExpander *pExpander,
               std::string *pErrorMessage);
};

#endif /* Builder_Twister_hpp */
