//
//  TwistMix16.hpp
//  MeanMachine
//
//  Created by Dragon on 4/28/26.
//

#ifndef TwistMix16_hpp
#define TwistMix16_hpp

#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"

/*
 
 Mix161

 ├── Root 0: RotL(A,1) / RotL(B,2)
 │   ├── temp = SBox[OracleA ^ OracleB]
 │   │   ├── Rot 3 -> Mix161_000  X This was found to be weak
 │   │   └── Rot 5 -> Mix161_001  X This was found to be weak
 │   └── temp = SBox[OracleA + OracleB]
 │       ├── Rot 3 -> Mix161_002  X This was found to be weak
 │       └── Rot 5 -> Mix161_003  X This was found to be weak
 │
 ├── Root 1: RotL(A,2) / RotL(B,1)
 │   ├── temp = SBox[OracleA ^ OracleB]
 │   │   ├── Rot 3 -> Mix161_004  X This was found to be weak
 │   │   └── Rot 5 -> Mix161_005  X This was found to be weak
 │   └── temp = SBox[OracleA + OracleB]
 │       ├── Rot 3 -> Mix161_006  X This was found to be weak
 │       └── Rot 5 -> Mix161_007  X This was found to be weak
 │
 ├── Root 2: RotL(A,1) / B
 │   ├── temp = SBox[OracleA ^ OracleB]
 │   │   ├── Rot 3
 │   │   │   ├── A ^= temp         -> Mix161_000
 │   │   │   └── A ^= RotL(temp,1) -> Mix161_001
 │   │   └── Rot 5
 │   │       ├── A ^= temp         -> Mix161_002
 │   │       └── A ^= RotL(temp,1) -> Mix161_003
 │   │
 │   └── temp = SBox[OracleA + OracleB]
 │       ├── Rot 3
 │       │   ├── A ^= RotL(temp,1) -> Mix161_004
 │       │   └── A ^= temp         -> Mix161_005
 │       └── Rot 5
 │           ├── A ^= RotL(temp,1) -> Mix161_006
 │           └── A ^= temp         -> Mix161_007
 │
 └── Root 3: A / RotL(B,1)
     ├── temp = SBox[OracleA ^ OracleB]
     │   ├── Rot 3
     │   │   ├── A ^= temp         -> Mix161_008
     │   │   └── A ^= RotL(temp,1) -> Mix161_017  X This was found to be weak
     │   └── Rot 5
     │       ├── A ^= temp         -> Mix161_009
     │       └── A ^= RotL(temp,1) -> Mix161_019  X This was found to be weak
     │
     └── temp = SBox[OracleA + OracleB]
         ├── Rot 3
         │   ├── A ^= RotL(temp,1) -> Mix161_010
         │   └── A ^= temp         -> Mix161_011  TT This does a little worse on cycles
         └── Rot 5
             ├── A ^= RotL(temp,1) -> Mix161_011
             └── A ^= temp         -> Mix161_013  TT This does a little worse on cycles
 
 
 
 Mix162 — 48 variants
 
 ├── Root 0: RotL(A,1) / RotL(B,2)
 │   ├── C0: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B + temp]
 │   │   ├── A ^= RotL(B,3) -> Mix162_000  X This was found to be weak
 │   │   ├── A ^= RotL(B,5) -> Mix162_001  X This was found to be weak
 │   │   ├── A += RotL(B,3) -> Mix162_000
 │   │   └── A += RotL(B,5) -> Mix162_001
 │   ├── C1: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B ^ RotL(temp,3)]
 │   │   ├── A += RotL(B,3) -> Mix162_002
 │   │   └── A += RotL(B,5) -> Mix162_003
 │   ├── C1: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B ^ RotL(temp,5)]
 │   │   ├── A += RotL(B,3) -> Mix162_004
 │   │   └── A += RotL(B,5) -> Mix162_005
 │   ├── C2: temp = SBoxA[OracleA + OracleB], B = SBoxB[B ^ RotL(temp,3)]
 │   │   ├── A ^= RotL(B,3) -> Mix162_008  X This was found to be weak
 │   │   └── A ^= RotL(B,5) -> Mix162_009  X This was found to be weak
 │   └── C2: temp = SBoxA[OracleA + OracleB], B = SBoxB[B ^ RotL(temp,5)]
 │       ├── A ^= RotL(B,3) -> Mix162_010  X This was found to be weak
 │       └── A ^= RotL(B,5) -> Mix162_011  X This was found to be weak
 │
 ├── Root 1: RotL(A,2) / RotL(B,1)
 │   ├── C0: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B + temp]
 │   │   ├── A ^= RotL(B,3) -> Mix162_012  X This was found to be weak
 │   │   ├── A ^= RotL(B,5) -> Mix162_013  X This was found to be weak
 │   │   ├── A += RotL(B,3) -> Mix162_014  X This was found to be weak
 │   │   └── A += RotL(B,5) -> Mix162_015  X This was found to be weak
 │   ├── C1: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B ^ RotL(temp,3)]
 │   │   ├── A += RotL(B,3) -> Mix162_006
 │   │   └── A += RotL(B,5) -> Mix162_007
 │   ├── C1: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B ^ RotL(temp,5)]
 │   │   ├── A += RotL(B,3) -> Mix162_008
 │   │   └── A += RotL(B,5) -> Mix162_009
 │   ├── C2: temp = SBoxA[OracleA + OracleB], B = SBoxB[B ^ RotL(temp,3)]
 │   │   ├── A ^= RotL(B,3) -> Mix162_020  X This was found to be weak
 │   │   └── A ^= RotL(B,5) -> Mix162_021  X This was found to be weak
 │   └── C2: temp = SBoxA[OracleA + OracleB], B = SBoxB[B ^ RotL(temp,5)]
 │       ├── A ^= RotL(B,3) -> Mix162_022  X This was found to be weak
 │       └── A ^= RotL(B,5) -> Mix162_023  X This was found to be weak
 │
 ├── Root 2: RotL(A,1) / B
 │   ├── C0: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B + temp]
 │   │   ├── A ^= RotL(B,3) -> Mix162_024  X This was found to be weak
 │   │   ├── A ^= RotL(B,5) -> Mix162_025  X This was found to be weak
 │   │   ├── A += RotL(B,3) -> Mix162_010
 │   │   └── A += RotL(B,5) -> Mix162_011
 │   ├── C1: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B ^ RotL(temp,3)]
 │   │   ├── A += RotL(B,3) -> Mix162_012
 │   │   └── A += RotL(B,5) -> Mix162_013
 │   ├── C1: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B ^ RotL(temp,5)]
 │   │   ├── A += RotL(B,3) -> Mix162_014
 │   │   └── A += RotL(B,5) -> Mix162_015
 │   ├── C2: temp = SBoxA[OracleA + OracleB], B = SBoxB[B ^ RotL(temp,3)]
 │   │   ├── A ^= RotL(B,3) -> Mix162_032  X This was found to be weak
 │   │   └── A ^= RotL(B,5) -> Mix162_033  X This was found to be weak
 │   └── C2: temp = SBoxA[OracleA + OracleB], B = SBoxB[B ^ RotL(temp,5)]
 │       ├── A ^= RotL(B,3) -> Mix162_034  X This was found to be weak
 │       └── A ^= RotL(B,5) -> Mix162_035  X This was found to be weak
 │
 └── Root 3: A / RotL(B,1)
     ├── C0: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B + temp]
     │   ├── A ^= RotL(B,3) -> Mix162_036  X This was found to be weak
     │   ├── A ^= RotL(B,5) -> Mix162_037  X This was found to be weak
     │   ├── A += RotL(B,3) -> Mix162_038  X This was found to be weak
     │   └── A += RotL(B,5) -> Mix162_039  X This was found to be weak
     ├── C1: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B ^ RotL(temp,3)]
     │   ├── A += RotL(B,3) -> Mix162_016
     │   └── A += RotL(B,5) -> Mix162_017
     ├── C1: temp = SBoxA[OracleA ^ OracleB], B = SBoxB[B ^ RotL(temp,5)]
     │   ├── A += RotL(B,3) -> Mix162_018
     │   └── A += RotL(B,5) -> Mix162_019
     ├── C2: temp = SBoxA[OracleA + OracleB], B = SBoxB[B ^ RotL(temp,3)]
     │   ├── A ^= RotL(B,3) -> Mix162_044  X This was found to be weak
     │   └── A ^= RotL(B,5) -> Mix162_045  X This was found to be weak
     └── C2: temp = SBoxA[OracleA + OracleB], B = SBoxB[B ^ RotL(temp,5)]
         ├── A ^= RotL(B,3) -> Mix162_046  X This was found to be weak
         └── A ^= RotL(B,5) -> Mix162_047  X This was found to be weak
 
*/
 
class TwistMix16 {
    
public:
    
    static std::uint16_t Mix162(int pFunction, // if 0, call Mix162_000, etc
                                          const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static std::uint16_t Mix161(int pFunction, // if 0, call Mix161_000, etc
                                       const std::uint16_t aValue,
                                           const std::uint8_t *pSBox);

    

    static inline std::uint16_t Mix161_000(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_001(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_002(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_003(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_004(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_005(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_006(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_007(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_008(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_009(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    static inline std::uint16_t Mix161_010(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);

    static inline std::uint16_t Mix161_011(const std::uint16_t aValue,
                                         const std::uint8_t *pSBox);
    

    
    
    
    static inline std::uint16_t Mix162_000(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_001(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_002(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_003(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_004(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_005(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_006(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_007(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_008(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_009(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_010(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_011(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_012(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_013(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_014(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_015(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_016(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_017(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_018(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
    static inline std::uint16_t Mix162_019(const std::uint16_t aValue,
                                           const std::uint8_t *pSBoxA,
                                           const std::uint8_t *pSBoxB);
    
};

#endif /* TwistMix16_hpp */
