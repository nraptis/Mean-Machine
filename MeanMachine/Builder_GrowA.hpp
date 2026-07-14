//
//  Builder_GrowA.hpp
//  MeanMachine
//
//  Created by icarus black on 7/13/26.
//

#ifndef Builder_GrowA_hpp
#define Builder_GrowA_hpp

#include <string>

class GTwistExpander;

class Builder_GrowA {
public:
    bool                                    Build(GTwistExpander *pExpander,
                                                  std::string *pErrorMessage);
};

#endif /* Builder_GrowA_hpp */
