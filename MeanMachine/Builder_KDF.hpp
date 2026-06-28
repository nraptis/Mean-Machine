//
//  Builder_KDF.hpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#ifndef Builder_KDF_hpp
#define Builder_KDF_hpp

#include <string>

class GTwistExpander;

class Builder_KDF {
public:
    bool Build(GTwistExpander *pExpander,
               std::string *pErrorMessage);
};

#endif /* Builder_KDF_hpp */
