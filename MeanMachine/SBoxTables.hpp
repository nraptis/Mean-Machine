//
//  SBoxTables.hpp
//  MeanMachine
//
//  Created by John Snow on 4/20/26.
//

#ifndef SBoxTables_hpp
#define SBoxTables_hpp

#include <cstdint>
#include <vector>

class GTwistExpander;

class SBoxTables {
public:
    
    static std::vector<std::vector<std::uint8_t>>               Get();
    
    // ddt: 4 wal: 32 deg: (7, 7) sac: (5.125000, 12) bic: (6.589286, 16)
    static std::vector<std::uint8_t>                            GetDefaultA();
    
    // ddt: 4 wal: 32 deg: (7, 7) sac: (5.062500, 12) bic: (6.500000, 16)
    static std::vector<std::uint8_t>                            GetDefaultB();
    
    // ddt: 4 wal: 32 deg: (7, 7) sac: (5.125000, 16) bic: (6.446429, 16)
    static std::vector<std::uint8_t>                            GetDefaultC();
    
    // ddt: 4 wal: 32 deg: (7, 7) sac: (5.125000, 16) bic: (6.571429, 16)
    static std::vector<std::uint8_t>                            GetDefaultD();

    static void                                                 InjectRandomFour(GTwistExpander *pExpander);
    
    
    
};

#endif /* SBoxTables_hpp */
