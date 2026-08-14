//
//  LoopScaffoldFarmer.hpp
//  MeanMachine
//

#ifndef LoopScaffoldFarmer_hpp
#define LoopScaffoldFarmer_hpp

#include <cstdint>
#include <string>

class LoopScaffoldFarmer {
public:
    static bool                                 Run(std::uint64_t pIterationCount,
                                                    std::string *pErrorMessage);
};

#endif /* LoopScaffoldFarmer_hpp */
