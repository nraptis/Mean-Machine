//
//  Builder_GrowB.hpp
//  MeanMachine
//
//  Created by icarus black on 7/13/26.
//

#ifndef Builder_GrowB_hpp
#define Builder_GrowB_hpp

#include <string>

class GTwistExpander;

class Builder_GrowB {
public:
    bool                                    Build(GTwistExpander *pExpander,
                                                  std::string *pErrorMessage);
};

#endif /* Builder_GrowB_hpp */
