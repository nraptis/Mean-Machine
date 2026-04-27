//
//  SaltTables.hpp
//  MeanMachine
//
//  Created by John Snow on 4/27/26.
//

#ifndef SaltTables_hpp
#define SaltTables_hpp

#include <cstdint>
#include <vector>

class GTwistExpander;

class SaltTables {
public:
    static std::vector<std::vector<std::uint8_t>>               Get();

    static std::vector<std::uint8_t>                            GetDefaultA();
    static std::vector<std::uint8_t>                            GetDefaultB();
    static std::vector<std::uint8_t>                            GetDefaultC();
    static std::vector<std::uint8_t>                            GetDefaultD();

    static void                                                 InjectRandomFour(GTwistExpander *pExpander);
};

#endif /* SaltTables_hpp */
