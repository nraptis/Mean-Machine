//
//  Builder.hpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#ifndef Builder_hpp
#define Builder_hpp

#include <string>

class Builder {
public:
    static bool Go(const std::string &pOutputRoot,
                   const std::string &pFilePrefix,
                   std::string *pErrorMessage);
};

#endif /* Builder_hpp */
