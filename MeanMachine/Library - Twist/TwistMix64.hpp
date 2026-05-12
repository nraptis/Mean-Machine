//
//  TwistMix64.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/1/26.
//

#ifndef TwistMix64_hpp
#define TwistMix64_hpp

#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"

enum class Mix64Type_1: std::uint8_t {
    kInv = 0,

    kGatePrism_1_8 = 1,

    kGateRoll_1_1 = 2,
    kGateRoll_1_4 = 3,
    kGateRoll_1_8 = 4,

    kGateTurn_1_1 = 5,
    kGateTurn_1_4 = 6,
    kGateTurn_1_8 = 7
};

enum class Mix64Type_4: std::uint8_t {
    kInv = 0,

    kGatePrismA_4_8 = 1,
    kGatePrismB_4_8 = 2,
    kGatePrismC_4_8 = 3,

    kGateRoll_4_4 = 4,
    kGateRollA_4_8 = 5,
    kGateRollB_4_8 = 6,
    kGateRollC_4_8 = 7,

    kGateTurn_4_4 = 8,
    kGateTurnA_4_8 = 9,
    kGateTurnB_4_8 = 10,
    kGateTurnC_4_8 = 11
};

enum class Mix64Type_8: std::uint8_t {
    kInv = 0,

    kGatePrism_8_8 = 1,

    kGateRoll_8_8 = 2,

    kGateTurn_8_8 = 3
};

class TwistMix64 {

public:
    
    static std::vector<Mix64Type_1>              GetAll_1();
    static std::vector<Mix64Type_4>              GetAll_4();
    static std::vector<Mix64Type_8>              GetAll_8();

    // Passes all bytes through one s-box.
    static std::uint64_t                         GatePrism_1_8(const std::uint64_t pValue,
                                                               const std::uint8_t *pSBoxA);

    static std::uint64_t                         GateRoll_1_1(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA);
    static std::uint64_t                         GateRoll_1_4(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA);
    static std::uint64_t                         GateRoll_1_8(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA);

    static std::uint64_t                         GateTurn_1_1(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA);
    static std::uint64_t                         GateTurn_1_4(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA);
    static std::uint64_t                         GateTurn_1_8(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA);

    // [aabbccdd]
    static std::uint64_t                         GatePrismA_4_8(const std::uint64_t pValue,
                                                                const std::uint8_t *pSBoxA,
                                                                const std::uint8_t *pSBoxB,
                                                                const std::uint8_t *pSBoxC,
                                                                const std::uint8_t *pSBoxD);

    // [abcdabcd]
    static std::uint64_t                         GatePrismB_4_8(const std::uint64_t pValue,
                                                                const std::uint8_t *pSBoxA,
                                                                const std::uint8_t *pSBoxB,
                                                                const std::uint8_t *pSBoxC,
                                                                const std::uint8_t *pSBoxD);

    // [abcddcba]
    static std::uint64_t                         GatePrismC_4_8(const std::uint64_t pValue,
                                                                const std::uint8_t *pSBoxA,
                                                                const std::uint8_t *pSBoxB,
                                                                const std::uint8_t *pSBoxC,
                                                                const std::uint8_t *pSBoxD);

    static std::uint64_t                         GateRoll_4_4(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA,
                                                              const std::uint8_t *pSBoxB,
                                                              const std::uint8_t *pSBoxC,
                                                              const std::uint8_t *pSBoxD);

    static std::uint64_t                         GateRollA_4_8(const std::uint64_t pValue,
                                                               const std::uint64_t pAmount,
                                                               const std::uint8_t *pSBoxA,
                                                               const std::uint8_t *pSBoxB,
                                                               const std::uint8_t *pSBoxC,
                                                               const std::uint8_t *pSBoxD);
    static std::uint64_t                         GateRollB_4_8(const std::uint64_t pValue,
                                                               const std::uint64_t pAmount,
                                                               const std::uint8_t *pSBoxA,
                                                               const std::uint8_t *pSBoxB,
                                                               const std::uint8_t *pSBoxC,
                                                               const std::uint8_t *pSBoxD);
    static std::uint64_t                         GateRollC_4_8(const std::uint64_t pValue,
                                                               const std::uint64_t pAmount,
                                                               const std::uint8_t *pSBoxA,
                                                               const std::uint8_t *pSBoxB,
                                                               const std::uint8_t *pSBoxC,
                                                               const std::uint8_t *pSBoxD);

    static std::uint64_t                         GateTurn_4_4(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA,
                                                              const std::uint8_t *pSBoxB,
                                                              const std::uint8_t *pSBoxC,
                                                              const std::uint8_t *pSBoxD);

    static std::uint64_t                         GateTurnA_4_8(const std::uint64_t pValue,
                                                               const std::uint64_t pAmount,
                                                               const std::uint8_t *pSBoxA,
                                                               const std::uint8_t *pSBoxB,
                                                               const std::uint8_t *pSBoxC,
                                                               const std::uint8_t *pSBoxD);
    static std::uint64_t                         GateTurnB_4_8(const std::uint64_t pValue,
                                                               const std::uint64_t pAmount,
                                                               const std::uint8_t *pSBoxA,
                                                               const std::uint8_t *pSBoxB,
                                                               const std::uint8_t *pSBoxC,
                                                               const std::uint8_t *pSBoxD);
    static std::uint64_t                         GateTurnC_4_8(const std::uint64_t pValue,
                                                               const std::uint64_t pAmount,
                                                               const std::uint8_t *pSBoxA,
                                                               const std::uint8_t *pSBoxB,
                                                               const std::uint8_t *pSBoxC,
                                                               const std::uint8_t *pSBoxD);

    static std::uint64_t                         GatePrism_8_8(const std::uint64_t pValue,
                                                               const std::uint8_t *pSBoxA,
                                                               const std::uint8_t *pSBoxB,
                                                               const std::uint8_t *pSBoxC,
                                                               const std::uint8_t *pSBoxD,
                                                               const std::uint8_t *pSBoxE,
                                                               const std::uint8_t *pSBoxF,
                                                               const std::uint8_t *pSBoxG,
                                                               const std::uint8_t *pSBoxH);

    static std::uint64_t                         GateRoll_8_8(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA,
                                                              const std::uint8_t *pSBoxB,
                                                              const std::uint8_t *pSBoxC,
                                                              const std::uint8_t *pSBoxD,
                                                              const std::uint8_t *pSBoxE,
                                                              const std::uint8_t *pSBoxF,
                                                              const std::uint8_t *pSBoxG,
                                                              const std::uint8_t *pSBoxH);

    static std::uint64_t                         GateTurn_8_8(const std::uint64_t pValue,
                                                              const std::uint64_t pAmount,
                                                              const std::uint8_t *pSBoxA,
                                                              const std::uint8_t *pSBoxB,
                                                              const std::uint8_t *pSBoxC,
                                                              const std::uint8_t *pSBoxD,
                                                              const std::uint8_t *pSBoxE,
                                                              const std::uint8_t *pSBoxF,
                                                              const std::uint8_t *pSBoxG,
                                                              const std::uint8_t *pSBoxH);
    
    
    static std::uint64_t                        DiffuseA(std::uint64_t pValue);
    static std::uint64_t                        DiffuseB(std::uint64_t pValue);
    static std::uint64_t                        DiffuseC(std::uint64_t pValue);
    
    

private:

    // Passes the low 8 bits through the s-box.
    // Other bytes are not changed.
    static std::uint64_t                         GatePrism_1_1(const std::uint64_t pValue,
                                                               const std::uint8_t *pSBoxA);

    // Passes the low 32 bits through the s-box.
    // Other bytes are not changed.
    static std::uint64_t                         GatePrism_1_4(const std::uint64_t pValue,
                                                               const std::uint8_t *pSBoxA);

    // Passes the low 32 bits through the 4 s-boxes.
    // Other bytes are not changed.
    static std::uint64_t                         GatePrism_4_4(const std::uint64_t pValue,
                                                               const std::uint8_t *pSBoxA,
                                                               const std::uint8_t *pSBoxB,
                                                               const std::uint8_t *pSBoxC,
                                                               const std::uint8_t *pSBoxD);

};

#endif /* TwistMix64_hpp */
