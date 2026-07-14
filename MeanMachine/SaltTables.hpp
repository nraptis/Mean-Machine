//
//  SaltTables.hpp
//  MeanMachine
//
//  Created by John Snow on 4/27/26.
//

#ifndef SaltTables_hpp
#define SaltTables_hpp

#include <array>
#include <cstdint>
#include <vector>

class GTwistExpander;

class SaltTables {
public:
    using Salt = std::array<std::uint64_t, 32U>;

    static const std::vector<Salt>                              &Get();

    static void                                                 InjectRandomEight(GTwistExpander *pExpander);
    
};

#endif /* SaltTables_hpp */
