//
//  FastMatrix8.hpp
//
//  Created by Helen of Troy on 4/25/26.
//

#ifndef FastMatrix8_hpp
#define FastMatrix8_hpp

#include "FastMatrixUnroll.hpp"
#include "FastMatrixRing.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

enum class FM8UnrollScheme : std::uint8_t {
    kA = 0,
    kB = 1,
    kC = 2,
    kD = 3
};

enum class FM8FastOp : std::uint8_t {
    kInv = 0,
};

enum class FM8SlowOp : std::uint8_t {
    kInv = 0,
};

class FM8 final {
public:
    using DataOpFn = void (FM8::*)(std::uint8_t, std::uint8_t);
    static constexpr std::size_t                 kDataOpByteCount = 256U;
    
    FM8(const std::uint8_t (&pMatrix)[8][8]);
    FM8(const FM8 &pMatrix);
    FM8();
    
    std::uint8_t                                mDataBase[64];
    
    void                                        LoadAndReset(const std::uint8_t *pSource);
    void                                        Store(std::uint8_t *pDest,
                                                      FM8UnrollScheme pUnrollScheme,
                                                      std::uint8_t pUnrollByte) const;
    void                                        ExecuteDataOp(std::uint8_t pOpByte,
                                                              std::uint8_t pArg1,
                                                              std::uint8_t pArg2);
    // FM8 dispatch remains permutation-only; no value mixing is performed here.
    static const std::array<DataOpFn, kDataOpByteCount> &
                                                GetDataOpTable();
    
    
    void                                        ReverseRow(std::uint8_t pRow, std::uint8_t pArg2 = 0U);
    void                                        ReverseRowEven(std::uint8_t pRow, std::uint8_t pArg2 = 0U);
    void                                        ReverseRowOdd(std::uint8_t pRow, std::uint8_t pArg2 = 0U);
    
    void                                        ReverseCol(std::uint8_t pCol, std::uint8_t pArg2 = 0U);
    void                                        ReverseColEven(std::uint8_t pCol, std::uint8_t pArg2 = 0U);
    void                                        ReverseColOdd(std::uint8_t pCol, std::uint8_t pArg2 = 0U);
    
    void                                        RotateRow(std::uint8_t pRow, std::uint8_t pAmount);
    
    void                                        RotateCol(std::uint8_t pColA, std::uint8_t pColB);
    
    void                                        SwapRows(std::uint8_t pRowA, std::uint8_t pRowB);
    void                                        SwapRowsEven(std::uint8_t pRowA, std::uint8_t pRowB);
    void                                        SwapRowsOdd(std::uint8_t pRowA, std::uint8_t pRowB);
    
    void                                        SwapCols(std::uint8_t pColA, std::uint8_t pColB);
    void                                        SwapColsEven(std::uint8_t pColA, std::uint8_t pColB);
    void                                        SwapColsOdd(std::uint8_t pColA, std::uint8_t pColB);
    
    
    // [0...15] for pBlockA, clipped
    // [0...15] for pBlockB, clipped
    void                                        SwapSixteenths(std::uint8_t pBlockA, std::uint8_t pBlockB);
    
    void                                        ShiftRing28A(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    
    void                                        ShiftRing24A(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing24B(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing24C(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing24D(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    
    void                                        ShiftRing20A(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing20B(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing20C(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing20D(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing20E(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    
    void                                        ShiftRing16A(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing16B(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing16C(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing16D(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing16E(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing16F(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing16G(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing16H(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    
    void                                        ShiftRing12A(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing12B(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing12C(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing12D(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing12E(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    
    void                                        ShiftRing8A(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing8B(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing8C(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing8D(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);

    void                                        ShiftRing8E(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing8F(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing8G(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    void                                        ShiftRing8H(std::uint8_t pAmount, std::uint8_t pArg2 = 0U);
    
    
    void                                        RotateRight(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightBlocks(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightSixteenthsQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightSixteenthsQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightSixteenthsQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightSixteenthsQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightSixteenthsEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightEachSixteenthQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightEachSixteenthQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightEachSixteenthQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightEachSixteenthQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateRightEachSixteenthEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    
    void                                        RotateLeft(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftBlocks(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftSixteenthsQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftSixteenthsQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftSixteenthsQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftSixteenthsQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftSixteenthsEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftEachSixteenthQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftEachSixteenthQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftEachSixteenthQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftEachSixteenthQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        RotateLeftEachSixteenthEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    
    void                                        TransposeMainDiagonal(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalBlocks(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U); // swaps b and c
    void                                        TransposeMainDiagonalQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalSixteenthsQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalSixteenthsQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalSixteenthsQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalSixteenthsQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalSixteenthsEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalEachSixteenthQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalEachSixteenthQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalEachSixteenthQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalEachSixteenthQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeMainDiagonalEachSixteenthEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    
    void                                        TransposeAntiDiagonal(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalBlocks(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U); // swaps a and d
    void                                        TransposeAntiDiagonalQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalSixteenthsQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalSixteenthsQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalSixteenthsQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalSixteenthsQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalSixteenthsEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalEachSixteenthQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalEachSixteenthQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalEachSixteenthQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalEachSixteenthQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        TransposeAntiDiagonalEachSixteenthEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    
    void                                        FlipHorizontal(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalBlocks(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalSixteenthsQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalSixteenthsQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalSixteenthsQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalSixteenthsQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalSixteenthsEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalEachSixteenthQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalEachSixteenthQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalEachSixteenthQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalEachSixteenthQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipHorizontalEachSixteenthEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    
    
    void                                        FlipVertical(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalBlocks(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalSixteenthsQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalSixteenthsQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalSixteenthsQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalSixteenthsQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalSixteenthsEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalEachSixteenthQuarterA(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalEachSixteenthQuarterB(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalEachSixteenthQuarterC(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalEachSixteenthQuarterD(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    void                                        FlipVerticalEachSixteenthEachQuarter(std::uint8_t pArg1 = 0U, std::uint8_t pArg2 = 0U);
    
    
    // 6 (12)
    void                                        PinwheelRight(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelRightQuarterA(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelRightQuarterB(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelRightQuarterC(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelRightQuarterD(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelRightEachQuarter(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    
    // 6
    void                                        PinwheelLeft(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelLeftQuarterA(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelLeftQuarterB(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelLeftQuarterC(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelLeftQuarterD(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    void                                        PinwheelLeftEachQuarter(std::uint8_t pEmptyA, std::uint8_t pEmptyB);
    

    
    bool                                        operator==(const FM8& other) const;
    bool                                        operator!=(const FM8& other) const;
    
    
private:
    
    std::uint8_t                                mTemp[64];
    
    void                                        PermuteRingBytes(std::uint8_t  pRingIndex, std::uint8_t pAmount);
    
    
};



#endif /* FastMatrix8_hpp */
