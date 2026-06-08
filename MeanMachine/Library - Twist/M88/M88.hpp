//
//  M88.hpp
//  CyberMatrix
//
//  Created by Six Pack Abs on 5/29/26.
//

#ifndef M88_hpp
#define M88_hpp

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <cstring>

class M88 {
public:
    M88();
    
    void                                        Reset();
    void                                        Print() const;
    

    std::uint8_t                                mData[64];

    // ignores bytes 1 and 2, uses last byte to unroll
    void                                        Dispatch(std::uint8_t *pOperationData,
                                                         std::size_t pOperationIndex,
                                                         std::uint8_t *pSource,
                                                         std::size_t pSourceIndex,
                                                         std::uint8_t *pDestination,
                                                         std::size_t pDestinationIndex,
                                                         std::uint8_t pUnrollDomainWord,
                                                         std::uint8_t pArgADomainWord,
                                                         std::uint8_t pArgBDomainWord,
                                                         std::uint8_t pArgCDomainWord,
                                                         std::uint8_t pArgDDomainWord);
    
    void                                        DispatchUnroll(std::uint8_t *pDestination,
                                                                std::uint8_t pByteSwapsA,
                                                                std::uint8_t pByteSwapsB,
                                                                std::uint8_t pByteSwapsC,
                                                                std::uint8_t pByteSwapsD,
                                                                
                                                                std::uint8_t pByteSwapsE,
                                                                std::uint8_t pByteSwapsF,
                                                                std::uint8_t pByteSwapsG,
                                                                std::uint8_t pByteSwapsH);


    // ============================================================
    // Byte Dispatch
    // ============================================================
    void                                        DispatchMini(std::uint8_t pByte);
    void                                        DispatchQuadA(std::uint8_t pByte);
    void                                        DispatchQuadB(std::uint8_t pByte);
    void                                        DispatchQuadC(std::uint8_t pByte);
    void                                        DispatchQuadD(std::uint8_t pByte);
    void                                        DispatchFullA(std::uint8_t pByte);
    void                                        DispatchFullB(std::uint8_t pByte);
    
    void                                        DispatchSwapsA(std::uint8_t pByteA, std::uint8_t pByteB);
    void                                        DispatchSwapsB(std::uint8_t pByte);
    
    void                                        DispatchPermute(std::uint8_t pByteSelect_QuadA_A,
                                                                 std::uint8_t pByteSelect_QuadA_B,
                                                                 std::uint8_t pByteSelect_QuadB_A,
                                                                 std::uint8_t pByteSelect_QuadB_B,
                                                                 std::uint8_t pByteSelect_QuadC_A,
                                                                 std::uint8_t pByteSelect_QuadC_B,
                                                                 std::uint8_t pByteSelect_QuadD_A,
                                                                 std::uint8_t pByteSelect_QuadD_B,
                                                                 
                                                                 std::uint8_t pByteSwapsA,
                                                                 std::uint8_t pByteSwapsB,
                                                                 std::uint8_t pByteSwapsC,
                                                                 std::uint8_t pByteSwapsD,
                                                                 std::uint8_t pByteSwapsE,
                                                                 std::uint8_t pByteSwapsF,
                                                                 std::uint8_t pByteSwapsG,
                                                                 std::uint8_t pByteSwapsH,
                                                                 
                                                                 std::uint8_t pByteAmount);
    
    std::uint8_t                                mPermute[16];
    std::uint8_t                                mPermuteTemp[16];
    std::uint8_t                                mPermuteData[16];
    
    void                                        SwapRows(std::uint8_t pRowA, std::uint8_t pRowB);
    void                                        SwapColumns(std::uint8_t pColA, std::uint8_t pColB);
    void                                        SwapMinis(std::uint8_t pBlockA, std::uint8_t pBlockB);
    

    
};

#endif /* M88_hpp */
