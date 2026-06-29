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
                   int pTrialNumber,
                   int pLeadingZeros,
                   std::string *pErrorMessage);
    static bool Go(const std::string &pOutputRoot,
                   const std::string &pFilePrefix,
                   int pTrialNumber,
                   int pLeadingZeros,
                   bool pUseSnapShotter,
                   std::string *pErrorMessage);

private:
    static std::string MakeNameBase(const std::string &pFilePrefix,
                                    int pTrialNumber,
                                    int pLeadingZeros);
};

#endif /* Builder_hpp */
