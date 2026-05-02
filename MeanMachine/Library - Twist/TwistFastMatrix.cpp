//
//  TwistFastMatrix.cpp
//
//  Created by Helen of Troy on 4/25/26.
//

#include "TwistFastMatrix.hpp"

#include <cctype>
#include <unordered_set>

namespace {



enum class MatrixOpSpeed : std::uint8_t {
    kFast = 0,
    kMedium = 1,
    kSlow = 2
};

struct TwistFastMatrixOpBinding {
    TwistFastMatrixOp                      mOp = TwistFastMatrixOp::kInv;
    TwistFastMatrix::DataOpFn             mFn = nullptr;
    const char                            *mToken = "";
    MatrixOpSpeed                         mSpeed = MatrixOpSpeed::kMedium;
};

constexpr TwistFastMatrixOpBinding kTwistFastMatrixOpBindings[] = {
    { TwistFastMatrixOp::kReverseRow, &TwistFastMatrix::ReverseRow, "kReverseRow", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kReverseRowEven, &TwistFastMatrix::ReverseRowEven, "kReverseRowEven", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kReverseRowOdd, &TwistFastMatrix::ReverseRowOdd, "kReverseRowOdd", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kReverseCol, &TwistFastMatrix::ReverseCol, "kReverseCol", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kReverseColEven, &TwistFastMatrix::ReverseColEven, "kReverseColEven", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kReverseColOdd, &TwistFastMatrix::ReverseColOdd, "kReverseColOdd", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kRotateRow, &TwistFastMatrix::RotateRow, "kRotateRow", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kRotateCol, &TwistFastMatrix::RotateCol, "kRotateCol", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kSwapRows, &TwistFastMatrix::SwapRows, "kSwapRows", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kSwapRowsEven, &TwistFastMatrix::SwapRowsEven, "kSwapRowsEven", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kSwapRowsOdd, &TwistFastMatrix::SwapRowsOdd, "kSwapRowsOdd", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kSwapCols, &TwistFastMatrix::SwapCols, "kSwapCols", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kSwapColsEven, &TwistFastMatrix::SwapColsEven, "kSwapColsEven", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kSwapColsOdd, &TwistFastMatrix::SwapColsOdd, "kSwapColsOdd", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kSwapSixteenths, &TwistFastMatrix::SwapSixteenths, "kSwapSixteenths", MatrixOpSpeed::kFast },
    { TwistFastMatrixOp::kShiftRing28A, &TwistFastMatrix::ShiftRing28A, "kShiftRing28A", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing24A, &TwistFastMatrix::ShiftRing24A, "kShiftRing24A", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing24B, &TwistFastMatrix::ShiftRing24B, "kShiftRing24B", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing24C, &TwistFastMatrix::ShiftRing24C, "kShiftRing24C", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing24D, &TwistFastMatrix::ShiftRing24D, "kShiftRing24D", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing20A, &TwistFastMatrix::ShiftRing20A, "kShiftRing20A", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing20B, &TwistFastMatrix::ShiftRing20B, "kShiftRing20B", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing20C, &TwistFastMatrix::ShiftRing20C, "kShiftRing20C", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing20D, &TwistFastMatrix::ShiftRing20D, "kShiftRing20D", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing20E, &TwistFastMatrix::ShiftRing20E, "kShiftRing20E", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing16A, &TwistFastMatrix::ShiftRing16A, "kShiftRing16A", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing16B, &TwistFastMatrix::ShiftRing16B, "kShiftRing16B", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing16C, &TwistFastMatrix::ShiftRing16C, "kShiftRing16C", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing16D, &TwistFastMatrix::ShiftRing16D, "kShiftRing16D", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing16E, &TwistFastMatrix::ShiftRing16E, "kShiftRing16E", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing16F, &TwistFastMatrix::ShiftRing16F, "kShiftRing16F", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing16G, &TwistFastMatrix::ShiftRing16G, "kShiftRing16G", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing16H, &TwistFastMatrix::ShiftRing16H, "kShiftRing16H", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing12A, &TwistFastMatrix::ShiftRing12A, "kShiftRing12A", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing12B, &TwistFastMatrix::ShiftRing12B, "kShiftRing12B", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing12C, &TwistFastMatrix::ShiftRing12C, "kShiftRing12C", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing12D, &TwistFastMatrix::ShiftRing12D, "kShiftRing12D", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing12E, &TwistFastMatrix::ShiftRing12E, "kShiftRing12E", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing8A, &TwistFastMatrix::ShiftRing8A, "kShiftRing8A", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing8B, &TwistFastMatrix::ShiftRing8B, "kShiftRing8B", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing8C, &TwistFastMatrix::ShiftRing8C, "kShiftRing8C", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing8D, &TwistFastMatrix::ShiftRing8D, "kShiftRing8D", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing8E, &TwistFastMatrix::ShiftRing8E, "kShiftRing8E", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing8F, &TwistFastMatrix::ShiftRing8F, "kShiftRing8F", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing8G, &TwistFastMatrix::ShiftRing8G, "kShiftRing8G", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kShiftRing8H, &TwistFastMatrix::ShiftRing8H, "kShiftRing8H", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRight, &TwistFastMatrix::RotateRight, "kRotateRight", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kRotateRightBlocks, &TwistFastMatrix::RotateRightBlocks, "kRotateRightBlocks", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kRotateRightQuarterA, &TwistFastMatrix::RotateRightQuarterA, "kRotateRightQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightQuarterB, &TwistFastMatrix::RotateRightQuarterB, "kRotateRightQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightQuarterC, &TwistFastMatrix::RotateRightQuarterC, "kRotateRightQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightQuarterD, &TwistFastMatrix::RotateRightQuarterD, "kRotateRightQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightEachQuarter, &TwistFastMatrix::RotateRightEachQuarter, "kRotateRightEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightSixteenthsQuarterA, &TwistFastMatrix::RotateRightSixteenthsQuarterA, "kRotateRightSixteenthsQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightSixteenthsQuarterB, &TwistFastMatrix::RotateRightSixteenthsQuarterB, "kRotateRightSixteenthsQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightSixteenthsQuarterC, &TwistFastMatrix::RotateRightSixteenthsQuarterC, "kRotateRightSixteenthsQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightSixteenthsQuarterD, &TwistFastMatrix::RotateRightSixteenthsQuarterD, "kRotateRightSixteenthsQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightSixteenthsEachQuarter, &TwistFastMatrix::RotateRightSixteenthsEachQuarter, "kRotateRightSixteenthsEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightEachSixteenthQuarterA, &TwistFastMatrix::RotateRightEachSixteenthQuarterA, "kRotateRightEachSixteenthQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightEachSixteenthQuarterB, &TwistFastMatrix::RotateRightEachSixteenthQuarterB, "kRotateRightEachSixteenthQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightEachSixteenthQuarterC, &TwistFastMatrix::RotateRightEachSixteenthQuarterC, "kRotateRightEachSixteenthQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightEachSixteenthQuarterD, &TwistFastMatrix::RotateRightEachSixteenthQuarterD, "kRotateRightEachSixteenthQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateRightEachSixteenthEachQuarter, &TwistFastMatrix::RotateRightEachSixteenthEachQuarter, "kRotateRightEachSixteenthEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeft, &TwistFastMatrix::RotateLeft, "kRotateLeft", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kRotateLeftBlocks, &TwistFastMatrix::RotateLeftBlocks, "kRotateLeftBlocks", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kRotateLeftQuarterA, &TwistFastMatrix::RotateLeftQuarterA, "kRotateLeftQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftQuarterB, &TwistFastMatrix::RotateLeftQuarterB, "kRotateLeftQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftQuarterC, &TwistFastMatrix::RotateLeftQuarterC, "kRotateLeftQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftQuarterD, &TwistFastMatrix::RotateLeftQuarterD, "kRotateLeftQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftEachQuarter, &TwistFastMatrix::RotateLeftEachQuarter, "kRotateLeftEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftSixteenthsQuarterA, &TwistFastMatrix::RotateLeftSixteenthsQuarterA, "kRotateLeftSixteenthsQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftSixteenthsQuarterB, &TwistFastMatrix::RotateLeftSixteenthsQuarterB, "kRotateLeftSixteenthsQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftSixteenthsQuarterC, &TwistFastMatrix::RotateLeftSixteenthsQuarterC, "kRotateLeftSixteenthsQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftSixteenthsQuarterD, &TwistFastMatrix::RotateLeftSixteenthsQuarterD, "kRotateLeftSixteenthsQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftSixteenthsEachQuarter, &TwistFastMatrix::RotateLeftSixteenthsEachQuarter, "kRotateLeftSixteenthsEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterA, &TwistFastMatrix::RotateLeftEachSixteenthQuarterA, "kRotateLeftEachSixteenthQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterB, &TwistFastMatrix::RotateLeftEachSixteenthQuarterB, "kRotateLeftEachSixteenthQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterC, &TwistFastMatrix::RotateLeftEachSixteenthQuarterC, "kRotateLeftEachSixteenthQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterD, &TwistFastMatrix::RotateLeftEachSixteenthQuarterD, "kRotateLeftEachSixteenthQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kRotateLeftEachSixteenthEachQuarter, &TwistFastMatrix::RotateLeftEachSixteenthEachQuarter, "kRotateLeftEachSixteenthEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonal, &TwistFastMatrix::TransposeMainDiagonal, "kTransposeMainDiagonal", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kTransposeMainDiagonalBlocks, &TwistFastMatrix::TransposeMainDiagonalBlocks, "kTransposeMainDiagonalBlocks", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kTransposeMainDiagonalQuarterA, &TwistFastMatrix::TransposeMainDiagonalQuarterA, "kTransposeMainDiagonalQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalQuarterB, &TwistFastMatrix::TransposeMainDiagonalQuarterB, "kTransposeMainDiagonalQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalQuarterC, &TwistFastMatrix::TransposeMainDiagonalQuarterC, "kTransposeMainDiagonalQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalQuarterD, &TwistFastMatrix::TransposeMainDiagonalQuarterD, "kTransposeMainDiagonalQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalEachQuarter, &TwistFastMatrix::TransposeMainDiagonalEachQuarter, "kTransposeMainDiagonalEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterA, &TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterA, "kTransposeMainDiagonalSixteenthsQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterB, &TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterB, "kTransposeMainDiagonalSixteenthsQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterC, &TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterC, "kTransposeMainDiagonalSixteenthsQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterD, &TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterD, "kTransposeMainDiagonalSixteenthsQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsEachQuarter, &TwistFastMatrix::TransposeMainDiagonalSixteenthsEachQuarter, "kTransposeMainDiagonalSixteenthsEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterA, &TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterA, "kTransposeMainDiagonalEachSixteenthQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterB, &TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterB, "kTransposeMainDiagonalEachSixteenthQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterC, &TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterC, "kTransposeMainDiagonalEachSixteenthQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterD, &TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterD, "kTransposeMainDiagonalEachSixteenthQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthEachQuarter, &TwistFastMatrix::TransposeMainDiagonalEachSixteenthEachQuarter, "kTransposeMainDiagonalEachSixteenthEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonal, &TwistFastMatrix::TransposeAntiDiagonal, "kTransposeAntiDiagonal", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kTransposeAntiDiagonalBlocks, &TwistFastMatrix::TransposeAntiDiagonalBlocks, "kTransposeAntiDiagonalBlocks", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kTransposeAntiDiagonalQuarterA, &TwistFastMatrix::TransposeAntiDiagonalQuarterA, "kTransposeAntiDiagonalQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalQuarterB, &TwistFastMatrix::TransposeAntiDiagonalQuarterB, "kTransposeAntiDiagonalQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalQuarterC, &TwistFastMatrix::TransposeAntiDiagonalQuarterC, "kTransposeAntiDiagonalQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalQuarterD, &TwistFastMatrix::TransposeAntiDiagonalQuarterD, "kTransposeAntiDiagonalQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalEachQuarter, &TwistFastMatrix::TransposeAntiDiagonalEachQuarter, "kTransposeAntiDiagonalEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterA, &TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterA, "kTransposeAntiDiagonalSixteenthsQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterB, &TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterB, "kTransposeAntiDiagonalSixteenthsQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterC, &TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterC, "kTransposeAntiDiagonalSixteenthsQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterD, &TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterD, "kTransposeAntiDiagonalSixteenthsQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsEachQuarter, &TwistFastMatrix::TransposeAntiDiagonalSixteenthsEachQuarter, "kTransposeAntiDiagonalSixteenthsEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterA, &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterA, "kTransposeAntiDiagonalEachSixteenthQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterB, &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterB, "kTransposeAntiDiagonalEachSixteenthQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterC, &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterC, "kTransposeAntiDiagonalEachSixteenthQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterD, &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterD, "kTransposeAntiDiagonalEachSixteenthQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthEachQuarter, &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthEachQuarter, "kTransposeAntiDiagonalEachSixteenthEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontal, &TwistFastMatrix::FlipHorizontal, "kFlipHorizontal", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kFlipHorizontalBlocks, &TwistFastMatrix::FlipHorizontalBlocks, "kFlipHorizontalBlocks", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kFlipHorizontalQuarterA, &TwistFastMatrix::FlipHorizontalQuarterA, "kFlipHorizontalQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalQuarterB, &TwistFastMatrix::FlipHorizontalQuarterB, "kFlipHorizontalQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalQuarterC, &TwistFastMatrix::FlipHorizontalQuarterC, "kFlipHorizontalQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalQuarterD, &TwistFastMatrix::FlipHorizontalQuarterD, "kFlipHorizontalQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalEachQuarter, &TwistFastMatrix::FlipHorizontalEachQuarter, "kFlipHorizontalEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterA, &TwistFastMatrix::FlipHorizontalSixteenthsQuarterA, "kFlipHorizontalSixteenthsQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterB, &TwistFastMatrix::FlipHorizontalSixteenthsQuarterB, "kFlipHorizontalSixteenthsQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterC, &TwistFastMatrix::FlipHorizontalSixteenthsQuarterC, "kFlipHorizontalSixteenthsQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterD, &TwistFastMatrix::FlipHorizontalSixteenthsQuarterD, "kFlipHorizontalSixteenthsQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalSixteenthsEachQuarter, &TwistFastMatrix::FlipHorizontalSixteenthsEachQuarter, "kFlipHorizontalSixteenthsEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterA, &TwistFastMatrix::FlipHorizontalEachSixteenthQuarterA, "kFlipHorizontalEachSixteenthQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterB, &TwistFastMatrix::FlipHorizontalEachSixteenthQuarterB, "kFlipHorizontalEachSixteenthQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterC, &TwistFastMatrix::FlipHorizontalEachSixteenthQuarterC, "kFlipHorizontalEachSixteenthQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterD, &TwistFastMatrix::FlipHorizontalEachSixteenthQuarterD, "kFlipHorizontalEachSixteenthQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipHorizontalEachSixteenthEachQuarter, &TwistFastMatrix::FlipHorizontalEachSixteenthEachQuarter, "kFlipHorizontalEachSixteenthEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVertical, &TwistFastMatrix::FlipVertical, "kFlipVertical", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kFlipVerticalBlocks, &TwistFastMatrix::FlipVerticalBlocks, "kFlipVerticalBlocks", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kFlipVerticalQuarterA, &TwistFastMatrix::FlipVerticalQuarterA, "kFlipVerticalQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalQuarterB, &TwistFastMatrix::FlipVerticalQuarterB, "kFlipVerticalQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalQuarterC, &TwistFastMatrix::FlipVerticalQuarterC, "kFlipVerticalQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalQuarterD, &TwistFastMatrix::FlipVerticalQuarterD, "kFlipVerticalQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalEachQuarter, &TwistFastMatrix::FlipVerticalEachQuarter, "kFlipVerticalEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterA, &TwistFastMatrix::FlipVerticalSixteenthsQuarterA, "kFlipVerticalSixteenthsQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterB, &TwistFastMatrix::FlipVerticalSixteenthsQuarterB, "kFlipVerticalSixteenthsQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterC, &TwistFastMatrix::FlipVerticalSixteenthsQuarterC, "kFlipVerticalSixteenthsQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterD, &TwistFastMatrix::FlipVerticalSixteenthsQuarterD, "kFlipVerticalSixteenthsQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalSixteenthsEachQuarter, &TwistFastMatrix::FlipVerticalSixteenthsEachQuarter, "kFlipVerticalSixteenthsEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterA, &TwistFastMatrix::FlipVerticalEachSixteenthQuarterA, "kFlipVerticalEachSixteenthQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterB, &TwistFastMatrix::FlipVerticalEachSixteenthQuarterB, "kFlipVerticalEachSixteenthQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterC, &TwistFastMatrix::FlipVerticalEachSixteenthQuarterC, "kFlipVerticalEachSixteenthQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterD, &TwistFastMatrix::FlipVerticalEachSixteenthQuarterD, "kFlipVerticalEachSixteenthQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kFlipVerticalEachSixteenthEachQuarter, &TwistFastMatrix::FlipVerticalEachSixteenthEachQuarter, "kFlipVerticalEachSixteenthEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelRight, &TwistFastMatrix::PinwheelRight, "kPinwheelRight", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kPinwheelRightQuarterA, &TwistFastMatrix::PinwheelRightQuarterA, "kPinwheelRightQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelRightQuarterB, &TwistFastMatrix::PinwheelRightQuarterB, "kPinwheelRightQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelRightQuarterC, &TwistFastMatrix::PinwheelRightQuarterC, "kPinwheelRightQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelRightQuarterD, &TwistFastMatrix::PinwheelRightQuarterD, "kPinwheelRightQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelRightEachQuarter, &TwistFastMatrix::PinwheelRightEachQuarter, "kPinwheelRightEachQuarter", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelLeft, &TwistFastMatrix::PinwheelLeft, "kPinwheelLeft", MatrixOpSpeed::kSlow },
    { TwistFastMatrixOp::kPinwheelLeftQuarterA, &TwistFastMatrix::PinwheelLeftQuarterA, "kPinwheelLeftQuarterA", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelLeftQuarterB, &TwistFastMatrix::PinwheelLeftQuarterB, "kPinwheelLeftQuarterB", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelLeftQuarterC, &TwistFastMatrix::PinwheelLeftQuarterC, "kPinwheelLeftQuarterC", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelLeftQuarterD, &TwistFastMatrix::PinwheelLeftQuarterD, "kPinwheelLeftQuarterD", MatrixOpSpeed::kMedium },
    { TwistFastMatrixOp::kPinwheelLeftEachQuarter, &TwistFastMatrix::PinwheelLeftEachQuarter, "kPinwheelLeftEachQuarter", MatrixOpSpeed::kMedium },
};

bool StartsWithText(const std::string &pText,
                    const std::string &pPrefix) {
    if (pPrefix.size() > pText.size()) {
        return false;
    }
    return pText.compare(0U, pPrefix.size(), pPrefix) == 0;
}

std::string TrimCopy(const std::string &pText) {
    std::size_t aBegin = 0U;
    while (aBegin < pText.size() && std::isspace(static_cast<unsigned char>(pText[aBegin])) != 0) {
        ++aBegin;
    }

    std::size_t aEnd = pText.size();
    while (aEnd > aBegin && std::isspace(static_cast<unsigned char>(pText[aEnd - 1U])) != 0) {
        --aEnd;
    }
    return pText.substr(aBegin, aEnd - aBegin);
}

constexpr TwistFastMatrix::DataOpFn kTwistFastMatrixBasePermuteOps[] = {
    &TwistFastMatrix::FlipHorizontal,
    &TwistFastMatrix::FlipHorizontalBlocks,
    &TwistFastMatrix::FlipHorizontalEachQuarter,
    &TwistFastMatrix::FlipHorizontalEachSixteenthEachQuarter,
    &TwistFastMatrix::FlipHorizontalEachSixteenthQuarterA,
    &TwistFastMatrix::FlipHorizontalEachSixteenthQuarterB,
    &TwistFastMatrix::FlipHorizontalEachSixteenthQuarterC,
    &TwistFastMatrix::FlipHorizontalEachSixteenthQuarterD,
    &TwistFastMatrix::FlipHorizontalQuarterA,
    &TwistFastMatrix::FlipHorizontalQuarterB,
    &TwistFastMatrix::FlipHorizontalQuarterC,
    &TwistFastMatrix::FlipHorizontalQuarterD,
    &TwistFastMatrix::FlipHorizontalSixteenthsEachQuarter,
    &TwistFastMatrix::FlipHorizontalSixteenthsQuarterA,
    &TwistFastMatrix::FlipHorizontalSixteenthsQuarterB,
    &TwistFastMatrix::FlipHorizontalSixteenthsQuarterC,
    &TwistFastMatrix::FlipHorizontalSixteenthsQuarterD,
    &TwistFastMatrix::FlipVertical,
    &TwistFastMatrix::FlipVerticalBlocks,
    &TwistFastMatrix::FlipVerticalEachQuarter,
    &TwistFastMatrix::FlipVerticalEachSixteenthEachQuarter,
    &TwistFastMatrix::FlipVerticalEachSixteenthQuarterA,
    &TwistFastMatrix::FlipVerticalEachSixteenthQuarterB,
    &TwistFastMatrix::FlipVerticalEachSixteenthQuarterC,
    &TwistFastMatrix::FlipVerticalEachSixteenthQuarterD,
    &TwistFastMatrix::FlipVerticalQuarterA,
    &TwistFastMatrix::FlipVerticalQuarterB,
    &TwistFastMatrix::FlipVerticalQuarterC,
    &TwistFastMatrix::FlipVerticalQuarterD,
    &TwistFastMatrix::FlipVerticalSixteenthsEachQuarter,
    &TwistFastMatrix::FlipVerticalSixteenthsQuarterA,
    &TwistFastMatrix::FlipVerticalSixteenthsQuarterB,
    &TwistFastMatrix::FlipVerticalSixteenthsQuarterC,
    &TwistFastMatrix::FlipVerticalSixteenthsQuarterD,
    &TwistFastMatrix::PinwheelLeft,
    &TwistFastMatrix::PinwheelLeftEachQuarter,
    &TwistFastMatrix::PinwheelLeftQuarterA,
    &TwistFastMatrix::PinwheelLeftQuarterB,
    &TwistFastMatrix::PinwheelLeftQuarterC,
    &TwistFastMatrix::PinwheelLeftQuarterD,
    &TwistFastMatrix::PinwheelRight,
    &TwistFastMatrix::PinwheelRightQuarterA,
    &TwistFastMatrix::PinwheelRightQuarterB,
    &TwistFastMatrix::PinwheelRightQuarterC,
    &TwistFastMatrix::PinwheelRightQuarterD,
    &TwistFastMatrix::ReverseCol,
    &TwistFastMatrix::ReverseColEven,
    &TwistFastMatrix::ReverseColOdd,
    &TwistFastMatrix::ReverseRow,
    &TwistFastMatrix::ReverseRowEven,
    &TwistFastMatrix::ReverseRowOdd,
    &TwistFastMatrix::RotateCol,
    &TwistFastMatrix::RotateLeft,
    &TwistFastMatrix::RotateLeftBlocks,
    &TwistFastMatrix::RotateLeftEachQuarter,
    &TwistFastMatrix::RotateLeftEachSixteenthEachQuarter,
    &TwistFastMatrix::RotateLeftEachSixteenthQuarterA,
    &TwistFastMatrix::RotateLeftEachSixteenthQuarterB,
    &TwistFastMatrix::RotateLeftEachSixteenthQuarterC,
    &TwistFastMatrix::RotateLeftEachSixteenthQuarterD,
    &TwistFastMatrix::RotateLeftQuarterA,
    &TwistFastMatrix::RotateLeftQuarterB,
    &TwistFastMatrix::RotateLeftQuarterC,
    &TwistFastMatrix::RotateLeftQuarterD,
    &TwistFastMatrix::RotateLeftSixteenthsEachQuarter,
    &TwistFastMatrix::RotateLeftSixteenthsQuarterA,
    &TwistFastMatrix::RotateLeftSixteenthsQuarterB,
    &TwistFastMatrix::RotateLeftSixteenthsQuarterC,
    &TwistFastMatrix::RotateLeftSixteenthsQuarterD,
    &TwistFastMatrix::RotateRight,
    &TwistFastMatrix::RotateRightBlocks,
    &TwistFastMatrix::RotateRightEachQuarter,
    &TwistFastMatrix::RotateRightEachSixteenthEachQuarter,
    &TwistFastMatrix::RotateRightEachSixteenthQuarterA,
    &TwistFastMatrix::RotateRightEachSixteenthQuarterB,
    &TwistFastMatrix::RotateRightEachSixteenthQuarterC,
    &TwistFastMatrix::RotateRightEachSixteenthQuarterD,
    &TwistFastMatrix::RotateRightQuarterA,
    &TwistFastMatrix::RotateRightQuarterB,
    &TwistFastMatrix::RotateRightQuarterC,
    &TwistFastMatrix::RotateRightQuarterD,
    &TwistFastMatrix::RotateRightSixteenthsEachQuarter,
    &TwistFastMatrix::RotateRightSixteenthsQuarterA,
    &TwistFastMatrix::RotateRightSixteenthsQuarterB,
    &TwistFastMatrix::RotateRightSixteenthsQuarterC,
    &TwistFastMatrix::RotateRightSixteenthsQuarterD,
    &TwistFastMatrix::RotateRow,
    &TwistFastMatrix::ShiftRing12A,
    &TwistFastMatrix::ShiftRing12B,
    &TwistFastMatrix::ShiftRing12C,
    &TwistFastMatrix::ShiftRing12D,
    &TwistFastMatrix::ShiftRing12E,
    &TwistFastMatrix::ShiftRing16A,
    &TwistFastMatrix::ShiftRing16B,
    &TwistFastMatrix::ShiftRing16C,
    &TwistFastMatrix::ShiftRing16D,
    &TwistFastMatrix::ShiftRing16E,
    &TwistFastMatrix::ShiftRing16F,
    &TwistFastMatrix::ShiftRing16G,
    &TwistFastMatrix::ShiftRing16H,
    &TwistFastMatrix::ShiftRing20A,
    &TwistFastMatrix::ShiftRing20B,
    &TwistFastMatrix::ShiftRing20C,
    &TwistFastMatrix::ShiftRing20D,
    &TwistFastMatrix::ShiftRing20E,
    &TwistFastMatrix::ShiftRing24A,
    &TwistFastMatrix::ShiftRing24B,
    &TwistFastMatrix::ShiftRing24C,
    &TwistFastMatrix::ShiftRing24D,
    &TwistFastMatrix::ShiftRing28A,
    &TwistFastMatrix::ShiftRing8A,
    &TwistFastMatrix::ShiftRing8B,
    &TwistFastMatrix::ShiftRing8C,
    &TwistFastMatrix::ShiftRing8D,
    &TwistFastMatrix::ShiftRing8E,
    &TwistFastMatrix::ShiftRing8F,
    &TwistFastMatrix::ShiftRing8G,
    &TwistFastMatrix::ShiftRing8H,
    &TwistFastMatrix::SwapCols,
    &TwistFastMatrix::SwapColsEven,
    &TwistFastMatrix::SwapColsOdd,
    &TwistFastMatrix::SwapRows,
    &TwistFastMatrix::SwapRowsEven,
    &TwistFastMatrix::SwapRowsOdd,
    &TwistFastMatrix::SwapSixteenths,
    &TwistFastMatrix::TransposeAntiDiagonal,
    &TwistFastMatrix::TransposeAntiDiagonalBlocks,
    &TwistFastMatrix::TransposeAntiDiagonalEachQuarter,
    &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthEachQuarter,
    &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterA,
    &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterB,
    &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterC,
    &TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterD,
    &TwistFastMatrix::TransposeAntiDiagonalQuarterA,
    &TwistFastMatrix::TransposeAntiDiagonalQuarterB,
    &TwistFastMatrix::TransposeAntiDiagonalQuarterC,
    &TwistFastMatrix::TransposeAntiDiagonalQuarterD,
    &TwistFastMatrix::TransposeAntiDiagonalSixteenthsEachQuarter,
    &TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterA,
    &TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterB,
    &TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterC,
    &TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterD,
    &TwistFastMatrix::TransposeMainDiagonal,
    &TwistFastMatrix::TransposeMainDiagonalBlocks,
    &TwistFastMatrix::TransposeMainDiagonalEachQuarter,
    &TwistFastMatrix::TransposeMainDiagonalEachSixteenthEachQuarter,
    &TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterA,
    &TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterB,
    &TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterC,
    &TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterD,
    &TwistFastMatrix::TransposeMainDiagonalQuarterA,
    &TwistFastMatrix::TransposeMainDiagonalQuarterB,
    &TwistFastMatrix::TransposeMainDiagonalQuarterC,
    &TwistFastMatrix::TransposeMainDiagonalQuarterD,
    &TwistFastMatrix::TransposeMainDiagonalSixteenthsEachQuarter,
    &TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterA,
    &TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterB,
    &TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterC,
    &TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterD,
};

std::array<TwistFastMatrix::DataOpFn, TwistFastMatrix::kDataOpByteCount> BuildTwistFastMatrixDataOpTable() {
    std::array<TwistFastMatrix::DataOpFn, TwistFastMatrix::kDataOpByteCount> aResult{};
    constexpr std::size_t aBaseOpCount = sizeof(kTwistFastMatrixBasePermuteOps) / sizeof(kTwistFastMatrixBasePermuteOps[0]);
    for (std::size_t aIndex = 0U; aIndex < aResult.size(); aIndex += 1U) {
        aResult[aIndex] = kTwistFastMatrixBasePermuteOps[aIndex % aBaseOpCount];
    }
    return aResult;
}

} // namespace

TwistFastMatrix::TwistFastMatrix(const std::uint8_t (&pMatrix)[8][8]) {
    for (std::uint8_t aRowIndex = 0; aRowIndex < 8; ++aRowIndex) {
        memcpy(mDataBase + (aRowIndex << 3), pMatrix[aRowIndex], 8);
    }
}

TwistFastMatrix::TwistFastMatrix(const TwistFastMatrix &pMatrix) {
    memcpy(mDataBase, pMatrix.mDataBase, 64);
}

TwistFastMatrix::TwistFastMatrix() {
    
}

void TwistFastMatrix::LoadAndReset(const std::uint8_t *pSource) {
    memcpy(mDataBase, pSource, 64);
}


std::vector<TwistFastMatrixOp> TwistFastMatrix::GetConflictingOps(std::vector<TwistFastMatrixOp> pOps) {
    std::vector<TwistFastMatrixOp> aResult;

    std::unordered_set<TwistFastMatrixOp> aExisting;
    for (int aIndex = 0; aIndex < static_cast<int>(pOps.size()); aIndex++) {
        aExisting.insert(pOps[aIndex]);
    }

    auto AddConflict = [&](TwistFastMatrixOp pOp) {
        if (std::find(aResult.begin(), aResult.end(), pOp) != aResult.end()) {
            return;
        }

        aResult.push_back(pOp);
    };
    
    auto AddAllRingConflictsIfNeeded = [&]() {
        static const std::vector<TwistFastMatrixOp> kRingOps = {
            TwistFastMatrixOp::kShiftRing28A,

            TwistFastMatrixOp::kShiftRing24A,
            TwistFastMatrixOp::kShiftRing24B,
            TwistFastMatrixOp::kShiftRing24C,
            TwistFastMatrixOp::kShiftRing24D,

            TwistFastMatrixOp::kShiftRing20A,
            TwistFastMatrixOp::kShiftRing20B,
            TwistFastMatrixOp::kShiftRing20C,
            TwistFastMatrixOp::kShiftRing20D,
            TwistFastMatrixOp::kShiftRing20E,

            TwistFastMatrixOp::kShiftRing16A,
            TwistFastMatrixOp::kShiftRing16B,
            TwistFastMatrixOp::kShiftRing16C,
            TwistFastMatrixOp::kShiftRing16D,
            TwistFastMatrixOp::kShiftRing16E,
            TwistFastMatrixOp::kShiftRing16F,
            TwistFastMatrixOp::kShiftRing16G,
            TwistFastMatrixOp::kShiftRing16H,

            TwistFastMatrixOp::kShiftRing12A,
            TwistFastMatrixOp::kShiftRing12B,
            TwistFastMatrixOp::kShiftRing12C,
            TwistFastMatrixOp::kShiftRing12D,
            TwistFastMatrixOp::kShiftRing12E,

            TwistFastMatrixOp::kShiftRing8A,
            TwistFastMatrixOp::kShiftRing8B,
            TwistFastMatrixOp::kShiftRing8C,
            TwistFastMatrixOp::kShiftRing8D,
            TwistFastMatrixOp::kShiftRing8E,
            TwistFastMatrixOp::kShiftRing8F,
            TwistFastMatrixOp::kShiftRing8G,
            TwistFastMatrixOp::kShiftRing8H,
        };

        int aRingCount = 0;

        for (TwistFastMatrixOp aOp : kRingOps) {
            if (aExisting.contains(aOp)) {
                aRingCount += 1;
            }
        }

        if (aRingCount >= 2) {
            for (TwistFastMatrixOp aOp : kRingOps) {
                AddConflict(aOp);
            }
        }
    };

    // All ops are self-conflicting.
    for (TwistFastMatrixOp aOp : aExisting) {
        AddConflict(aOp);
    }

    struct TwistFastMatrixConflictPair {
        TwistFastMatrixOp mA;
        TwistFastMatrixOp mB;
    };

    struct TwistFastMatrixConflictGroup {
        std::vector<TwistFastMatrixOp> mOps;
    };

    static const std::vector<TwistFastMatrixConflictPair> kPairConflicts = {
        {
            TwistFastMatrixOp::kRotateRight,
            TwistFastMatrixOp::kRotateLeft,
        },
        {
            TwistFastMatrixOp::kRotateRightBlocks,
            TwistFastMatrixOp::kRotateLeftBlocks,
        },
        {
            TwistFastMatrixOp::kRotateRightEachQuarter,
            TwistFastMatrixOp::kRotateLeftEachQuarter,
        },

        {
            TwistFastMatrixOp::kPinwheelRight,
            TwistFastMatrixOp::kPinwheelLeft,
        },
        {
            TwistFastMatrixOp::kPinwheelRightQuarterA,
            TwistFastMatrixOp::kPinwheelLeftQuarterA,
        },
        {
            TwistFastMatrixOp::kPinwheelRightQuarterB,
            TwistFastMatrixOp::kPinwheelLeftQuarterB,
        },
        {
            TwistFastMatrixOp::kPinwheelRightQuarterC,
            TwistFastMatrixOp::kPinwheelLeftQuarterC,
        },
        {
            TwistFastMatrixOp::kPinwheelRightQuarterD,
            TwistFastMatrixOp::kPinwheelLeftQuarterD,
        },
        {
            TwistFastMatrixOp::kPinwheelRightEachQuarter,
            TwistFastMatrixOp::kPinwheelLeftEachQuarter,
        },

        {
            TwistFastMatrixOp::kRotateRightQuarterA,
            TwistFastMatrixOp::kRotateLeftQuarterA,
        },
        {
            TwistFastMatrixOp::kRotateRightQuarterB,
            TwistFastMatrixOp::kRotateLeftQuarterB,
        },
        {
            TwistFastMatrixOp::kRotateRightQuarterC,
            TwistFastMatrixOp::kRotateLeftQuarterC,
        },
        {
            TwistFastMatrixOp::kRotateRightQuarterD,
            TwistFastMatrixOp::kRotateLeftQuarterD,
        },

        {
            TwistFastMatrixOp::kRotateRightSixteenthsQuarterA,
            TwistFastMatrixOp::kRotateLeftSixteenthsQuarterA,
        },
        {
            TwistFastMatrixOp::kRotateRightSixteenthsQuarterB,
            TwistFastMatrixOp::kRotateLeftSixteenthsQuarterB,
        },
        {
            TwistFastMatrixOp::kRotateRightSixteenthsQuarterC,
            TwistFastMatrixOp::kRotateLeftSixteenthsQuarterC,
        },
        {
            TwistFastMatrixOp::kRotateRightSixteenthsQuarterD,
            TwistFastMatrixOp::kRotateLeftSixteenthsQuarterD,
        },
        {
            TwistFastMatrixOp::kRotateRightSixteenthsEachQuarter,
            TwistFastMatrixOp::kRotateLeftSixteenthsEachQuarter,
        },

        {
            TwistFastMatrixOp::kRotateRightEachSixteenthQuarterA,
            TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterA,
        },
        {
            TwistFastMatrixOp::kRotateRightEachSixteenthQuarterB,
            TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterB,
        },
        {
            TwistFastMatrixOp::kRotateRightEachSixteenthQuarterC,
            TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterC,
        },
        {
            TwistFastMatrixOp::kRotateRightEachSixteenthQuarterD,
            TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterD,
        },
        {
            TwistFastMatrixOp::kRotateRightEachSixteenthEachQuarter,
            TwistFastMatrixOp::kRotateLeftEachSixteenthEachQuarter,
        },
        
        {
            TwistFastMatrixOp::kTransposeMainDiagonal,
            TwistFastMatrixOp::kTransposeAntiDiagonal,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalBlocks,
            TwistFastMatrixOp::kTransposeAntiDiagonalBlocks,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalQuarterA,
            TwistFastMatrixOp::kTransposeAntiDiagonalQuarterA,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalQuarterB,
            TwistFastMatrixOp::kTransposeAntiDiagonalQuarterB,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalQuarterC,
            TwistFastMatrixOp::kTransposeAntiDiagonalQuarterC,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalQuarterD,
            TwistFastMatrixOp::kTransposeAntiDiagonalQuarterD,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalEachQuarter,
            TwistFastMatrixOp::kTransposeAntiDiagonalEachQuarter,
        },

        {
            TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterA,
            TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterA,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterB,
            TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterB,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterC,
            TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterC,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterD,
            TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterD,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsEachQuarter,
            TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsEachQuarter,
        },

        {
            TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterA,
            TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterA,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterB,
            TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterB,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterC,
            TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterC,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterD,
            TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterD,
        },
        {
            TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthEachQuarter,
            TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthEachQuarter,
        },
        {
            TwistFastMatrixOp::kFlipHorizontal,
            TwistFastMatrixOp::kFlipVertical,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalBlocks,
            TwistFastMatrixOp::kFlipVerticalBlocks,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalQuarterA,
            TwistFastMatrixOp::kFlipVerticalQuarterA,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalQuarterB,
            TwistFastMatrixOp::kFlipVerticalQuarterB,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalQuarterC,
            TwistFastMatrixOp::kFlipVerticalQuarterC,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalQuarterD,
            TwistFastMatrixOp::kFlipVerticalQuarterD,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalEachQuarter,
            TwistFastMatrixOp::kFlipVerticalEachQuarter,
        },

        {
            TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterA,
            TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterA,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterB,
            TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterB,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterC,
            TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterC,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterD,
            TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterD,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalSixteenthsEachQuarter,
            TwistFastMatrixOp::kFlipVerticalSixteenthsEachQuarter,
        },

        {
            TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterA,
            TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterA,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterB,
            TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterB,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterC,
            TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterC,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterD,
            TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterD,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalEachSixteenthEachQuarter,
            TwistFastMatrixOp::kFlipVerticalEachSixteenthEachQuarter,
        },
        // Shift-ring corner adjacency conflicts.
        // A/B/C/D are the four corners.
        // Adjacent corners conflict; opposite corners do not.
        // Extra labels E/F/G/H are not included here.
        {
            TwistFastMatrixOp::kShiftRing24A,
            TwistFastMatrixOp::kShiftRing24B,
        },
        {
            TwistFastMatrixOp::kShiftRing24B,
            TwistFastMatrixOp::kShiftRing24C,
        },
        {
            TwistFastMatrixOp::kShiftRing24C,
            TwistFastMatrixOp::kShiftRing24D,
        },
        {
            TwistFastMatrixOp::kShiftRing24D,
            TwistFastMatrixOp::kShiftRing24A,
        },

        {
            TwistFastMatrixOp::kShiftRing20A,
            TwistFastMatrixOp::kShiftRing20B,
        },
        {
            TwistFastMatrixOp::kShiftRing20B,
            TwistFastMatrixOp::kShiftRing20C,
        },
        {
            TwistFastMatrixOp::kShiftRing20C,
            TwistFastMatrixOp::kShiftRing20D,
        },
        {
            TwistFastMatrixOp::kShiftRing20D,
            TwistFastMatrixOp::kShiftRing20A,
        },

        {
            TwistFastMatrixOp::kShiftRing16B,
            TwistFastMatrixOp::kShiftRing16C,
        },
        {
            TwistFastMatrixOp::kShiftRing16C,
            TwistFastMatrixOp::kShiftRing16D,
        },
        {
            TwistFastMatrixOp::kShiftRing16D,
            TwistFastMatrixOp::kShiftRing16E,
        },
        {
            TwistFastMatrixOp::kShiftRing16E,
            TwistFastMatrixOp::kShiftRing16B,
        },

        {
            TwistFastMatrixOp::kShiftRing16F,
            TwistFastMatrixOp::kShiftRing16H,
        },
        {
            TwistFastMatrixOp::kShiftRing16H,
            TwistFastMatrixOp::kShiftRing16A,
        },
        {
            TwistFastMatrixOp::kShiftRing16A,
            TwistFastMatrixOp::kShiftRing16G,
        },
        {
            TwistFastMatrixOp::kShiftRing16G,
            TwistFastMatrixOp::kShiftRing16F,
        },

        {
            TwistFastMatrixOp::kShiftRing12A,
            TwistFastMatrixOp::kShiftRing12B,
        },
        {
            TwistFastMatrixOp::kShiftRing12B,
            TwistFastMatrixOp::kShiftRing12C,
        },
        {
            TwistFastMatrixOp::kShiftRing12C,
            TwistFastMatrixOp::kShiftRing12D,
        },
        {
            TwistFastMatrixOp::kShiftRing12D,
            TwistFastMatrixOp::kShiftRing12A,
        },
        
        {
            TwistFastMatrixOp::kShiftRing8C,
            TwistFastMatrixOp::kShiftRing8A,
        },
        {
            TwistFastMatrixOp::kShiftRing8A,
            TwistFastMatrixOp::kShiftRing8B,
        },
        {
            TwistFastMatrixOp::kShiftRing8B,
            TwistFastMatrixOp::kShiftRing8D,
        },
        {
            TwistFastMatrixOp::kShiftRing8D,
            TwistFastMatrixOp::kShiftRing8C,
        },

        {
            TwistFastMatrixOp::kShiftRing8E,
            TwistFastMatrixOp::kShiftRing8F,
        },
        {
            TwistFastMatrixOp::kShiftRing8F,
            TwistFastMatrixOp::kShiftRing8G,
        },
        {
            TwistFastMatrixOp::kShiftRing8G,
            TwistFastMatrixOp::kShiftRing8H,
        },
        {
            TwistFastMatrixOp::kShiftRing8H,
            TwistFastMatrixOp::kShiftRing8E,
        },
        {
            TwistFastMatrixOp::kFlipVertical,
            TwistFastMatrixOp::kRotateLeft,
        },
        {
            TwistFastMatrixOp::kFlipVertical,
            TwistFastMatrixOp::kRotateRight,
        },
        {
            TwistFastMatrixOp::kFlipHorizontal,
            TwistFastMatrixOp::kRotateLeft,
        },
        {
            TwistFastMatrixOp::kFlipHorizontal,
            TwistFastMatrixOp::kRotateRight,
        },
        {
            TwistFastMatrixOp::kFlipVerticalBlocks,
            TwistFastMatrixOp::kRotateLeftBlocks,
        },
        {
            TwistFastMatrixOp::kFlipVerticalBlocks,
            TwistFastMatrixOp::kRotateRightBlocks,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalBlocks,
            TwistFastMatrixOp::kRotateLeftBlocks,
        },
        {
            TwistFastMatrixOp::kFlipHorizontalBlocks,
            TwistFastMatrixOp::kRotateRightBlocks,
        },
    };

    static const std::vector<TwistFastMatrixConflictGroup> kConflictGroups = {
        // Rotate-right primary group.
        {
            {
                TwistFastMatrixOp::kRotateRight,
                TwistFastMatrixOp::kRotateRightQuarterA,
                TwistFastMatrixOp::kRotateRightQuarterB,
                TwistFastMatrixOp::kRotateRightQuarterC,
                TwistFastMatrixOp::kRotateRightQuarterD,
                TwistFastMatrixOp::kRotateRightEachQuarter,
            }
        },

        // Rotate-left primary group.
        {
            {
                TwistFastMatrixOp::kRotateLeft,
                TwistFastMatrixOp::kRotateLeftQuarterA,
                TwistFastMatrixOp::kRotateLeftQuarterB,
                TwistFastMatrixOp::kRotateLeftQuarterC,
                TwistFastMatrixOp::kRotateLeftQuarterD,
                TwistFastMatrixOp::kRotateLeftEachQuarter,
            }
        },

        // Block-level rotation is its own "1 of these total" group.
        {
            {
                TwistFastMatrixOp::kRotateRightBlocks,
                TwistFastMatrixOp::kRotateLeftBlocks,
            }
        },

        // Flip vertical primary group.
        {
            {
                TwistFastMatrixOp::kFlipVertical,
                TwistFastMatrixOp::kFlipVerticalBlocks,
                TwistFastMatrixOp::kFlipVerticalQuarterA,
                TwistFastMatrixOp::kFlipVerticalQuarterB,
                TwistFastMatrixOp::kFlipVerticalQuarterC,
                TwistFastMatrixOp::kFlipVerticalQuarterD,
                TwistFastMatrixOp::kFlipVerticalEachQuarter,
            }
        },
        
        {
            {
                TwistFastMatrixOp::kFlipHorizontal,
                TwistFastMatrixOp::kFlipHorizontalBlocks,
                TwistFastMatrixOp::kFlipHorizontalQuarterA,
                TwistFastMatrixOp::kFlipHorizontalQuarterB,
                TwistFastMatrixOp::kFlipHorizontalQuarterC,
                TwistFastMatrixOp::kFlipHorizontalQuarterD,
                TwistFastMatrixOp::kFlipHorizontalEachQuarter,
            }
        },

        // Flip vertical sixteenths-inside-quarter group.
        {
            {
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterA,
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterB,
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterC,
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterD,
                TwistFastMatrixOp::kFlipVerticalSixteenthsEachQuarter,
            }
        },

        // Flip vertical each-sixteenth group.
        {
            {
                TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterA,
                TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterB,
                TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterC,
                TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterD,
                TwistFastMatrixOp::kFlipVerticalEachSixteenthEachQuarter,
            }
        },

        // Pinwheel-right primary group.
        {
            {
                TwistFastMatrixOp::kPinwheelRight,
                TwistFastMatrixOp::kPinwheelRightQuarterA,
                TwistFastMatrixOp::kPinwheelRightQuarterB,
                TwistFastMatrixOp::kPinwheelRightQuarterC,
                TwistFastMatrixOp::kPinwheelRightQuarterD,
                TwistFastMatrixOp::kPinwheelRightEachQuarter,
            }
        },

        // Pinwheel-left primary group.
        {
            {
                TwistFastMatrixOp::kPinwheelLeft,
                TwistFastMatrixOp::kPinwheelLeftQuarterA,
                TwistFastMatrixOp::kPinwheelLeftQuarterB,
                TwistFastMatrixOp::kPinwheelLeftQuarterC,
                TwistFastMatrixOp::kPinwheelLeftQuarterD,
                TwistFastMatrixOp::kPinwheelLeftEachQuarter,
            }
        },
        {
               {
                   TwistFastMatrixOp::kReverseRow,
                   TwistFastMatrixOp::kReverseRowEven,
                   TwistFastMatrixOp::kReverseRowOdd,
               }
           },
           {
               {
                   TwistFastMatrixOp::kReverseCol,
                   TwistFastMatrixOp::kReverseColEven,
                   TwistFastMatrixOp::kReverseColOdd,
               }
           },
           {
               {
                   TwistFastMatrixOp::kSwapRows,
                   TwistFastMatrixOp::kSwapRowsEven,
                   TwistFastMatrixOp::kSwapRowsOdd,
               }
           },
           {
               {
                   TwistFastMatrixOp::kSwapCols,
                   TwistFastMatrixOp::kSwapColsEven,
                   TwistFastMatrixOp::kSwapColsOdd,
               }
           },
        
        {
            {
                TwistFastMatrixOp::kRotateRightQuarterA,
                TwistFastMatrixOp::kRotateRightQuarterB,
                TwistFastMatrixOp::kRotateRightQuarterC,
                TwistFastMatrixOp::kRotateRightQuarterD,
            }
        },
        {
            {
                TwistFastMatrixOp::kRotateLeftQuarterA,
                TwistFastMatrixOp::kRotateLeftQuarterB,
                TwistFastMatrixOp::kRotateLeftQuarterC,
                TwistFastMatrixOp::kRotateLeftQuarterD,
            }
        },

        {
            {
                TwistFastMatrixOp::kTransposeMainDiagonalQuarterA,
                TwistFastMatrixOp::kTransposeMainDiagonalQuarterB,
                TwistFastMatrixOp::kTransposeMainDiagonalQuarterC,
                TwistFastMatrixOp::kTransposeMainDiagonalQuarterD,
            }
        },
        {
            {
                TwistFastMatrixOp::kTransposeAntiDiagonalQuarterA,
                TwistFastMatrixOp::kTransposeAntiDiagonalQuarterB,
                TwistFastMatrixOp::kTransposeAntiDiagonalQuarterC,
                TwistFastMatrixOp::kTransposeAntiDiagonalQuarterD,
            }
        },

        {
            {
                TwistFastMatrixOp::kFlipHorizontalQuarterA,
                TwistFastMatrixOp::kFlipHorizontalQuarterB,
                TwistFastMatrixOp::kFlipHorizontalQuarterC,
                TwistFastMatrixOp::kFlipHorizontalQuarterD,
            }
        },
        {
            {
                TwistFastMatrixOp::kFlipVerticalQuarterA,
                TwistFastMatrixOp::kFlipVerticalQuarterB,
                TwistFastMatrixOp::kFlipVerticalQuarterC,
                TwistFastMatrixOp::kFlipVerticalQuarterD,
            }
        },

        {
            {
                TwistFastMatrixOp::kPinwheelRightQuarterA,
                TwistFastMatrixOp::kPinwheelRightQuarterB,
                TwistFastMatrixOp::kPinwheelRightQuarterC,
                TwistFastMatrixOp::kPinwheelRightQuarterD,
            }
        },
        {
            {
                TwistFastMatrixOp::kPinwheelLeftQuarterA,
                TwistFastMatrixOp::kPinwheelLeftQuarterB,
                TwistFastMatrixOp::kPinwheelLeftQuarterC,
                TwistFastMatrixOp::kPinwheelLeftQuarterD,
            }
        },
        {
            {
                TwistFastMatrixOp::kRotateLeftSixteenthsQuarterA,
                TwistFastMatrixOp::kRotateLeftSixteenthsQuarterB,
                TwistFastMatrixOp::kRotateLeftSixteenthsQuarterC,
                TwistFastMatrixOp::kRotateLeftSixteenthsQuarterD,
            }
        },

        {
            {
                TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterA,
                TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterB,
                TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterC,
                TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterD,
            }
        },
        {
            {
                TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterA,
                TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterB,
                TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterC,
                TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterD,
            }
        },

        {
            {
                TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterA,
                TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterB,
                TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterC,
                TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterD,
            }
        },
        {
            {
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterA,
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterB,
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterC,
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterD,
            }
        },
        
        {
            {
                TwistFastMatrixOp::kRotateRightEachSixteenthQuarterA,
                TwistFastMatrixOp::kRotateRightEachSixteenthQuarterB,
                TwistFastMatrixOp::kRotateRightEachSixteenthQuarterC,
                TwistFastMatrixOp::kRotateRightEachSixteenthQuarterD,
                TwistFastMatrixOp::kRotateRightEachSixteenthEachQuarter,
            }
        },
        {
            {
                TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterA,
                TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterB,
                TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterC,
                TwistFastMatrixOp::kRotateLeftEachSixteenthQuarterD,
                TwistFastMatrixOp::kRotateLeftEachSixteenthEachQuarter,
            }
        },
        {
            {
                TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterA,
                TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterB,
                TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterC,
                TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthQuarterD,
                TwistFastMatrixOp::kTransposeMainDiagonalEachSixteenthEachQuarter,
            }
        },
        {
            {
                TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterA,
                TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterB,
                TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterC,
                TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthQuarterD,
                TwistFastMatrixOp::kTransposeAntiDiagonalEachSixteenthEachQuarter,
            }
        },
        {
            {
                TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterA,
                TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterB,
                TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterC,
                TwistFastMatrixOp::kFlipHorizontalEachSixteenthQuarterD,
                TwistFastMatrixOp::kFlipHorizontalEachSixteenthEachQuarter,
            }
        },
        {
            {
                TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterA,
                TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterB,
                TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterC,
                TwistFastMatrixOp::kFlipVerticalEachSixteenthQuarterD,
                TwistFastMatrixOp::kFlipVerticalEachSixteenthEachQuarter,
            }
        },
        
        
        {
            {
                TwistFastMatrixOp::kRotateRightSixteenthsQuarterA,
                TwistFastMatrixOp::kRotateRightSixteenthsQuarterB,
                TwistFastMatrixOp::kRotateRightSixteenthsQuarterC,
                TwistFastMatrixOp::kRotateRightSixteenthsQuarterD,
                TwistFastMatrixOp::kRotateRightSixteenthsEachQuarter,
            }
        },
        {
            {
                TwistFastMatrixOp::kRotateLeftSixteenthsQuarterA,
                TwistFastMatrixOp::kRotateLeftSixteenthsQuarterB,
                TwistFastMatrixOp::kRotateLeftSixteenthsQuarterC,
                TwistFastMatrixOp::kRotateLeftSixteenthsQuarterD,
                TwistFastMatrixOp::kRotateLeftSixteenthsEachQuarter,
            }
        },

        {
            {
                TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterA,
                TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterB,
                TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterC,
                TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsQuarterD,
                TwistFastMatrixOp::kTransposeMainDiagonalSixteenthsEachQuarter,
            }
        },
        {
            {
                TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterA,
                TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterB,
                TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterC,
                TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsQuarterD,
                TwistFastMatrixOp::kTransposeAntiDiagonalSixteenthsEachQuarter,
            }
        },

        {
            {
                TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterA,
                TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterB,
                TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterC,
                TwistFastMatrixOp::kFlipHorizontalSixteenthsQuarterD,
                TwistFastMatrixOp::kFlipHorizontalSixteenthsEachQuarter,
            }
        },
        {
            {
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterA,
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterB,
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterC,
                TwistFastMatrixOp::kFlipVerticalSixteenthsQuarterD,
                TwistFastMatrixOp::kFlipVerticalSixteenthsEachQuarter,
            }
        },
        
        {
            {
                TwistFastMatrixOp::kTransposeMainDiagonal,
                TwistFastMatrixOp::kTransposeMainDiagonalBlocks,
                TwistFastMatrixOp::kTransposeMainDiagonalQuarterA,
                TwistFastMatrixOp::kTransposeMainDiagonalQuarterB,
                TwistFastMatrixOp::kTransposeMainDiagonalQuarterC,
                TwistFastMatrixOp::kTransposeMainDiagonalQuarterD,
                TwistFastMatrixOp::kTransposeMainDiagonalEachQuarter,
            }
        },
        {
            {
                TwistFastMatrixOp::kTransposeAntiDiagonal,
                TwistFastMatrixOp::kTransposeAntiDiagonalBlocks,
                TwistFastMatrixOp::kTransposeAntiDiagonalQuarterA,
                TwistFastMatrixOp::kTransposeAntiDiagonalQuarterB,
                TwistFastMatrixOp::kTransposeAntiDiagonalQuarterC,
                TwistFastMatrixOp::kTransposeAntiDiagonalQuarterD,
                TwistFastMatrixOp::kTransposeAntiDiagonalEachQuarter,
            }
        },
        
    };

    for (const TwistFastMatrixConflictPair& aPair : kPairConflicts) {
        const bool aContainsA = aExisting.contains(aPair.mA);
        const bool aContainsB = aExisting.contains(aPair.mB);

        if (aContainsA) {
            AddConflict(aPair.mB);
        }

        if (aContainsB) {
            AddConflict(aPair.mA);
        }
    }

    for (const TwistFastMatrixConflictGroup& aGroup : kConflictGroups) {
        bool aContainsAny = false;

        for (TwistFastMatrixOp aOp : aGroup.mOps) {
            if (aExisting.contains(aOp)) {
                aContainsAny = true;
                break;
            }
        }

        if (!aContainsAny) {
            continue;
        }

        for (TwistFastMatrixOp aOp : aGroup.mOps) {
            AddConflict(aOp);
        }
    }
    
    
    AddAllRingConflictsIfNeeded();
    
    return aResult;
}

void TwistFastMatrix::Store(std::uint8_t *pDest,
                TwistFastMatrixUnrollScheme pUnrollScheme,
                std::uint8_t pUnrollByte) const {

    const std::uint8_t *aOrder;
    switch (pUnrollScheme) {
        case TwistFastMatrixUnrollScheme::kA:
            aOrder = TwistFastMatrixUnrollTableA::kUnrollTable[pUnrollByte];
            break;
        case TwistFastMatrixUnrollScheme::kB:
            aOrder = TwistFastMatrixUnrollTableB::kUnrollTable[pUnrollByte];
            break;
        case TwistFastMatrixUnrollScheme::kC:
            aOrder = TwistFastMatrixUnrollTableC::kUnrollTable[pUnrollByte];
            break;
        default:
            aOrder = TwistFastMatrixUnrollTableD::kUnrollTable[pUnrollByte];
            break;
    }
    
    memcpy(pDest +  0, mDataBase + (aOrder[0] << 3), 8);
    memcpy(pDest +  8, mDataBase + (aOrder[1] << 3), 8);
    memcpy(pDest + 16, mDataBase + (aOrder[2] << 3), 8);
    memcpy(pDest + 24, mDataBase + (aOrder[3] << 3), 8);
    memcpy(pDest + 32, mDataBase + (aOrder[4] << 3), 8);
    memcpy(pDest + 40, mDataBase + (aOrder[5] << 3), 8);
    memcpy(pDest + 48, mDataBase + (aOrder[6] << 3), 8);
    memcpy(pDest + 56, mDataBase + (aOrder[7] << 3), 8);
}

void TwistFastMatrix::ExecuteOp(TwistFastMatrixOp pOp,
                std::uint8_t pArg1,
                std::uint8_t pArg2) {
    for (const TwistFastMatrixOpBinding &aBinding : kTwistFastMatrixOpBindings) {
        if (aBinding.mOp == pOp) {
            (this->*(aBinding.mFn))(pArg1, pArg2);
            return;
        }
    }
}

void TwistFastMatrix::ExecuteDataOp(std::uint8_t pOpByte,
                        std::uint8_t pArg1,
                        std::uint8_t pArg2) {
    const std::array<DataOpFn, kDataOpByteCount> &aTable = GetDataOpTable();
    const DataOpFn aOp = aTable[pOpByte];
    (this->*aOp)(pArg1, pArg2);
}

const std::array<TwistFastMatrix::DataOpFn, TwistFastMatrix::kDataOpByteCount> &
TwistFastMatrix::GetDataOpTable() {
    static const std::array<DataOpFn, kDataOpByteCount> kTable = BuildTwistFastMatrixDataOpTable();
    return kTable;
}

std::vector<TwistFastMatrixOp> TwistFastMatrix::GetAllTypes() {
    std::vector<TwistFastMatrixOp> aResult;
    aResult.reserve(sizeof(kTwistFastMatrixOpBindings) / sizeof(kTwistFastMatrixOpBindings[0]));
    for (const TwistFastMatrixOpBinding &aBinding : kTwistFastMatrixOpBindings) {
        aResult.push_back(aBinding.mOp);
    }
    return aResult;
}

std::vector<TwistFastMatrixOp> TwistFastMatrix::GetAllTypesFast() {
    std::vector<TwistFastMatrixOp> aResult;
    for (const TwistFastMatrixOpBinding &aBinding : kTwistFastMatrixOpBindings) {
        if (aBinding.mSpeed == MatrixOpSpeed::kFast) {
            aResult.push_back(aBinding.mOp);
        }
    }
    return aResult;
}

std::vector<TwistFastMatrixOp> TwistFastMatrix::GetAllTypesMedium() {
    std::vector<TwistFastMatrixOp> aResult;
    for (const TwistFastMatrixOpBinding &aBinding : kTwistFastMatrixOpBindings) {
        if (aBinding.mSpeed == MatrixOpSpeed::kMedium) {
            aResult.push_back(aBinding.mOp);
        }
    }
    return aResult;
}

std::vector<TwistFastMatrixOp> TwistFastMatrix::GetAllTypesSlow() {
    std::vector<TwistFastMatrixOp> aResult;
    for (const TwistFastMatrixOpBinding &aBinding : kTwistFastMatrixOpBindings) {
        if (aBinding.mSpeed == MatrixOpSpeed::kSlow) {
            aResult.push_back(aBinding.mOp);
        }
    }
    return aResult;
}

std::string TwistFastMatrix::OpToken(TwistFastMatrixOp pOp) {
    for (const TwistFastMatrixOpBinding &aBinding : kTwistFastMatrixOpBindings) {
        if (aBinding.mOp == pOp) {
            return aBinding.mToken;
        }
    }
    return "kInv";
}

bool TwistFastMatrix::OpFromToken(const std::string &pToken,
                                  TwistFastMatrixOp *pOp) {
    if (pOp == nullptr) {
        return false;
    }

    std::string aToken = TrimCopy(pToken);
    if (StartsWithText(aToken, "TwistFastMatrixOp::")) {
        aToken = aToken.substr(19U);
    }

    if (aToken == "kInv") {
        *pOp = TwistFastMatrixOp::kInv;
        return true;
    }

    for (const TwistFastMatrixOpBinding &aBinding : kTwistFastMatrixOpBindings) {
        if (aToken == aBinding.mToken) {
            *pOp = aBinding.mOp;
            return true;
        }
    }
    return false;
}

std::string TwistFastMatrix::GetFunctionName(TwistFastMatrixOp pOp) {
    for (const TwistFastMatrixOpBinding &aBinding : kTwistFastMatrixOpBindings) {
        if (aBinding.mOp == pOp) {
            const char *aToken = aBinding.mToken;
            if ((aToken != nullptr) && (aToken[0] == 'k')) {
                return std::string(aToken + 1);
            }
            return (aToken != nullptr) ? std::string(aToken) : "";
        }
    }
    return "";
}

bool TwistFastMatrix::OpFromFunctionName(const std::string &pFunctionName,
                                         TwistFastMatrixOp *pOp) {
    if (pOp == nullptr) {
        return false;
    }

    const std::string aName = TrimCopy(pFunctionName);
    if (aName.empty()) {
        return false;
    }

    for (const TwistFastMatrixOpBinding &aBinding : kTwistFastMatrixOpBindings) {
        if (GetFunctionName(aBinding.mOp) == aName) {
            *pOp = aBinding.mOp;
            return true;
        }
    }
    return false;
}

std::string TwistFastMatrix::UnrollSchemeToken(TwistFastMatrixUnrollScheme pScheme) {
    switch (pScheme) {
        case TwistFastMatrixUnrollScheme::kA: return "TwistFastMatrixUnrollScheme::kA";
        case TwistFastMatrixUnrollScheme::kB: return "TwistFastMatrixUnrollScheme::kB";
        case TwistFastMatrixUnrollScheme::kC: return "TwistFastMatrixUnrollScheme::kC";
        case TwistFastMatrixUnrollScheme::kD: return "TwistFastMatrixUnrollScheme::kD";
        default: return "TwistFastMatrixUnrollScheme::kA";
    }
}

bool TwistFastMatrix::UnrollSchemeFromToken(const std::string &pToken,
                                            TwistFastMatrixUnrollScheme *pScheme) {
    if (pScheme == nullptr) {
        return false;
    }

    std::string aToken = TrimCopy(pToken);
    if (StartsWithText(aToken, "TwistFastMatrixUnrollScheme::")) {
        aToken = aToken.substr(29U);
    }

    if (aToken == "kA") { *pScheme = TwistFastMatrixUnrollScheme::kA; return true; }
    if (aToken == "kB") { *pScheme = TwistFastMatrixUnrollScheme::kB; return true; }
    if (aToken == "kC") { *pScheme = TwistFastMatrixUnrollScheme::kC; return true; }
    if (aToken == "kD") { *pScheme = TwistFastMatrixUnrollScheme::kD; return true; }
    return false;
}


void TwistFastMatrix::SwapRows(std::uint8_t pRowA, std::uint8_t pRowB) {

    std::uint8_t aRowA = (pRowA & 7) << 3;
    std::uint8_t aRowB = (pRowB & 7) << 3;

    if (aRowA == aRowB) { return; }

    memcpy(mTemp,          mDataBase + aRowA, 8);
    memcpy(mDataBase + aRowA,  mDataBase + aRowB, 8);
    memcpy(mDataBase + aRowB,  mTemp,         8);
}

void TwistFastMatrix::SwapRowsEven(std::uint8_t pRowA, std::uint8_t pRowB) {

    std::uint8_t aRowA = (pRowA & 7) << 3;
    std::uint8_t aRowB = (pRowB & 7) << 3;

    if (aRowA == aRowB) { return; }

    std::uint8_t aHold;

    // swap only even columns: 0,2,4,6
    aHold = mDataBase[aRowA + 0]; mDataBase[aRowA + 0] = mDataBase[aRowB + 0]; mDataBase[aRowB + 0] = aHold;
    aHold = mDataBase[aRowA + 2]; mDataBase[aRowA + 2] = mDataBase[aRowB + 2]; mDataBase[aRowB + 2] = aHold;
    aHold = mDataBase[aRowA + 4]; mDataBase[aRowA + 4] = mDataBase[aRowB + 4]; mDataBase[aRowB + 4] = aHold;
    aHold = mDataBase[aRowA + 6]; mDataBase[aRowA + 6] = mDataBase[aRowB + 6]; mDataBase[aRowB + 6] = aHold;
}

void TwistFastMatrix::SwapRowsOdd(std::uint8_t pRowA, std::uint8_t pRowB) {

    std::uint8_t aRowA = (pRowA & 7) << 3;
    std::uint8_t aRowB = (pRowB & 7) << 3;

    if (aRowA == aRowB) { return; }

    std::uint8_t aHold;

    // swap only odd columns: 1,3,5,7
    aHold = mDataBase[aRowA + 1]; mDataBase[aRowA + 1] = mDataBase[aRowB + 1]; mDataBase[aRowB + 1] = aHold;
    aHold = mDataBase[aRowA + 3]; mDataBase[aRowA + 3] = mDataBase[aRowB + 3]; mDataBase[aRowB + 3] = aHold;
    aHold = mDataBase[aRowA + 5]; mDataBase[aRowA + 5] = mDataBase[aRowB + 5]; mDataBase[aRowB + 5] = aHold;
    aHold = mDataBase[aRowA + 7]; mDataBase[aRowA + 7] = mDataBase[aRowB + 7]; mDataBase[aRowB + 7] = aHold;
}

void TwistFastMatrix::ReverseRow(std::uint8_t pRow, std::uint8_t /*pArg2*/) {

    std::uint8_t aBase = (pRow & 7) << 3;
    std::uint8_t aHold;

    aHold = mDataBase[aBase + 0]; mDataBase[aBase + 0] = mDataBase[aBase + 7]; mDataBase[aBase + 7] = aHold;
    aHold = mDataBase[aBase + 1]; mDataBase[aBase + 1] = mDataBase[aBase + 6]; mDataBase[aBase + 6] = aHold;
    aHold = mDataBase[aBase + 2]; mDataBase[aBase + 2] = mDataBase[aBase + 5]; mDataBase[aBase + 5] = aHold;
    aHold = mDataBase[aBase + 3]; mDataBase[aBase + 3] = mDataBase[aBase + 4]; mDataBase[aBase + 4] = aHold;
}

void TwistFastMatrix::ReverseRowEven(std::uint8_t pRow, std::uint8_t /*pArg2*/) {

    std::uint8_t aBase = (pRow & 7) << 3;
    std::uint8_t aHold;

    // even columns: 0,2,4,6
    aHold = mDataBase[aBase + 0]; mDataBase[aBase + 0] = mDataBase[aBase + 6]; mDataBase[aBase + 6] = aHold;
    aHold = mDataBase[aBase + 2]; mDataBase[aBase + 2] = mDataBase[aBase + 4]; mDataBase[aBase + 4] = aHold;
}

void TwistFastMatrix::ReverseRowOdd(std::uint8_t pRow, std::uint8_t /*pArg2*/) {

    std::uint8_t aBase = (pRow & 7) << 3;
    std::uint8_t aHold;

    // odd columns: 1,3,5,7
    aHold = mDataBase[aBase + 1]; mDataBase[aBase + 1] = mDataBase[aBase + 7]; mDataBase[aBase + 7] = aHold;
    aHold = mDataBase[aBase + 3]; mDataBase[aBase + 3] = mDataBase[aBase + 5]; mDataBase[aBase + 5] = aHold;
}

void TwistFastMatrix::ReverseCol(std::uint8_t pCol, std::uint8_t /*pArg2*/) {

    std::uint8_t aBase = (pCol & 7);
    std::uint8_t aHold;

    aHold = mDataBase[(0 << 3) + aBase]; mDataBase[(0 << 3) + aBase] = mDataBase[(7 << 3) + aBase]; mDataBase[(7 << 3) + aBase] = aHold;
    aHold = mDataBase[(1 << 3) + aBase]; mDataBase[(1 << 3) + aBase] = mDataBase[(6 << 3) + aBase]; mDataBase[(6 << 3) + aBase] = aHold;
    aHold = mDataBase[(2 << 3) + aBase]; mDataBase[(2 << 3) + aBase] = mDataBase[(5 << 3) + aBase]; mDataBase[(5 << 3) + aBase] = aHold;
    aHold = mDataBase[(3 << 3) + aBase]; mDataBase[(3 << 3) + aBase] = mDataBase[(4 << 3) + aBase]; mDataBase[(4 << 3) + aBase] = aHold;
}

void TwistFastMatrix::ReverseColEven(std::uint8_t pCol, std::uint8_t /*pArg2*/) {

    std::uint8_t aCol = (pCol & 7);
    std::uint8_t aHold;

    // even rows: 0,2,4,6
    aHold = mDataBase[(0 << 3) + aCol]; mDataBase[(0 << 3) + aCol] = mDataBase[(6 << 3) + aCol]; mDataBase[(6 << 3) + aCol] = aHold;
    aHold = mDataBase[(2 << 3) + aCol]; mDataBase[(2 << 3) + aCol] = mDataBase[(4 << 3) + aCol]; mDataBase[(4 << 3) + aCol] = aHold;
}

void TwistFastMatrix::ReverseColOdd(std::uint8_t pCol, std::uint8_t /*pArg2*/) {

    std::uint8_t aCol = (pCol & 7);
    std::uint8_t aHold;

    // odd rows: 1,3,5,7
    aHold = mDataBase[(1 << 3) + aCol]; mDataBase[(1 << 3) + aCol] = mDataBase[(7 << 3) + aCol]; mDataBase[(7 << 3) + aCol] = aHold;
    aHold = mDataBase[(3 << 3) + aCol]; mDataBase[(3 << 3) + aCol] = mDataBase[(5 << 3) + aCol]; mDataBase[(5 << 3) + aCol] = aHold;
}

void TwistFastMatrix::RotateRow(std::uint8_t pRow, std::uint8_t pAmount) {

    std::uint8_t aBase   = (pRow & 7) << 3;
    std::uint8_t aAmount = pAmount & 7;

    if (aAmount == 0) { return; }

    for (std::uint8_t aColIndex = 0; aColIndex < 8; ++aColIndex) {
        mTemp[aColIndex] =
            mDataBase[aBase + ((aColIndex + aAmount) & 7)];
    }

    memcpy(mDataBase + aBase, mTemp, 8);
}

void TwistFastMatrix::SwapCols(std::uint8_t pColA, std::uint8_t pColB) {

    std::uint8_t aColA = pColA & 7;
    std::uint8_t aColB = pColB & 7;

    if (aColA == aColB) { return; }

    std::uint8_t aHold;

    for (std::uint8_t aRowIndex = 0; aRowIndex < 8; ++aRowIndex) {

        std::uint8_t aBase = aRowIndex << 3;

        aHold = mDataBase[aBase + aColA];
        mDataBase[aBase + aColA] = mDataBase[aBase + aColB];
        mDataBase[aBase + aColB] = aHold;
    }
}

void TwistFastMatrix::SwapColsEven(std::uint8_t pColA, std::uint8_t pColB) {

    std::uint8_t aColA = pColA & 7;
    std::uint8_t aColB = pColB & 7;

    if (aColA == aColB) { return; }

    std::uint8_t aHold;

    // only even rows: 0,2,4,6
    for (std::uint8_t aRowIndex = 0; aRowIndex < 8; aRowIndex += 2) {

        std::uint8_t aBase = aRowIndex << 3;

        aHold = mDataBase[aBase + aColA];
        mDataBase[aBase + aColA] = mDataBase[aBase + aColB];
        mDataBase[aBase + aColB] = aHold;
    }
}

void TwistFastMatrix::SwapColsOdd(std::uint8_t pColA, std::uint8_t pColB) {

    std::uint8_t aColA = pColA & 7;
    std::uint8_t aColB = pColB & 7;

    if (aColA == aColB) { return; }

    std::uint8_t aHold;

    // only odd rows: 1,3,5,7
    for (std::uint8_t aRowIndex = 1; aRowIndex < 8; aRowIndex += 2) {

        std::uint8_t aBase = aRowIndex << 3;

        aHold = mDataBase[aBase + aColA];
        mDataBase[aBase + aColA] = mDataBase[aBase + aColB];
        mDataBase[aBase + aColB] = aHold;
    }
}

void TwistFastMatrix::RotateCol(std::uint8_t pCol, std::uint8_t pAmount) {

    std::uint8_t aCol    = pCol & 7;
    std::uint8_t aAmount = pAmount & 7;

    if (aAmount == 0) { return; }

    // gather
    for (std::uint8_t aRowIndex = 0; aRowIndex < 8; ++aRowIndex) {
        mTemp[aRowIndex] =
            mDataBase[((aRowIndex + 8 - aAmount) & 7) << 3 | aCol];
    }

    // scatter
    for (std::uint8_t aRowIndex = 0; aRowIndex < 8; ++aRowIndex) {
        mDataBase[(aRowIndex << 3) + aCol] = mTemp[aRowIndex];
    }
}

void TwistFastMatrix::SwapSixteenths(std::uint8_t pBlockA, std::uint8_t pBlockB) {

    std::uint8_t aBlockA = pBlockA & 15;
    std::uint8_t aBlockB = pBlockB & 15;

    if (aBlockA == aBlockB) { return; }

    // decode A
    std::uint8_t aRowA = (aBlockA >> 2) << 1;
    std::uint8_t aColA = (aBlockA & 3) << 1;

    // decode B
    std::uint8_t aRowB = (aBlockB >> 2) << 1;
    std::uint8_t aColB = (aBlockB & 3) << 1;

    std::uint8_t aBaseA0 = (aRowA + 0) << 3;
    std::uint8_t aBaseA1 = (aRowA + 1) << 3;

    std::uint8_t aBaseB0 = (aRowB + 0) << 3;
    std::uint8_t aBaseB1 = (aRowB + 1) << 3;

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[aBaseA0 + aColA + 0];
    mDataBase[aBaseA0 + aColA + 0] = mDataBase[aBaseB0 + aColB + 0];
    mDataBase[aBaseB0 + aColB + 0] = aHold;

    // (0,1)
    aHold = mDataBase[aBaseA0 + aColA + 1];
    mDataBase[aBaseA0 + aColA + 1] = mDataBase[aBaseB0 + aColB + 1];
    mDataBase[aBaseB0 + aColB + 1] = aHold;

    // (1,0)
    aHold = mDataBase[aBaseA1 + aColA + 0];
    mDataBase[aBaseA1 + aColA + 0] = mDataBase[aBaseB1 + aColB + 0];
    mDataBase[aBaseB1 + aColB + 0] = aHold;

    // (1,1)
    aHold = mDataBase[aBaseA1 + aColA + 1];
    mDataBase[aBaseA1 + aColA + 1] = mDataBase[aBaseB1 + aColB + 1];
    mDataBase[aBaseB1 + aColB + 1] = aHold;
}

// 90° clockwise
void TwistFastMatrix::RotateRight(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aDst = mTemp;
    aDst[ 0] = aSrc[56]; aDst[ 1] = aSrc[48]; aDst[ 2] = aSrc[40]; aDst[ 3] = aSrc[32];
    aDst[ 4] = aSrc[24]; aDst[ 5] = aSrc[16]; aDst[ 6] = aSrc[ 8]; aDst[ 7] = aSrc[ 0];
    aDst[ 8] = aSrc[57]; aDst[ 9] = aSrc[49]; aDst[10] = aSrc[41]; aDst[11] = aSrc[33];
    aDst[12] = aSrc[25]; aDst[13] = aSrc[17]; aDst[14] = aSrc[ 9]; aDst[15] = aSrc[ 1];
    aDst[16] = aSrc[58]; aDst[17] = aSrc[50]; aDst[18] = aSrc[42]; aDst[19] = aSrc[34];
    aDst[20] = aSrc[26]; aDst[21] = aSrc[18]; aDst[22] = aSrc[10]; aDst[23] = aSrc[ 2];
    aDst[24] = aSrc[59]; aDst[25] = aSrc[51]; aDst[26] = aSrc[43]; aDst[27] = aSrc[35];
    aDst[28] = aSrc[27]; aDst[29] = aSrc[19]; aDst[30] = aSrc[11]; aDst[31] = aSrc[ 3];
    aDst[32] = aSrc[60]; aDst[33] = aSrc[52]; aDst[34] = aSrc[44]; aDst[35] = aSrc[36];
    aDst[36] = aSrc[28]; aDst[37] = aSrc[20]; aDst[38] = aSrc[12]; aDst[39] = aSrc[ 4];
    aDst[40] = aSrc[61]; aDst[41] = aSrc[53]; aDst[42] = aSrc[45]; aDst[43] = aSrc[37];
    aDst[44] = aSrc[29]; aDst[45] = aSrc[21]; aDst[46] = aSrc[13]; aDst[47] = aSrc[ 5];
    aDst[48] = aSrc[62]; aDst[49] = aSrc[54]; aDst[50] = aSrc[46]; aDst[51] = aSrc[38];
    aDst[52] = aSrc[30]; aDst[53] = aSrc[22]; aDst[54] = aSrc[14]; aDst[55] = aSrc[ 6];
    aDst[56] = aSrc[63]; aDst[57] = aSrc[55]; aDst[58] = aSrc[47]; aDst[59] = aSrc[39];
    aDst[60] = aSrc[31]; aDst[61] = aSrc[23]; aDst[62] = aSrc[15]; aDst[63] = aSrc[ 7];
    memcpy(mDataBase, mTemp, 64);
}

// 90° counter-clockwise
void TwistFastMatrix::RotateLeft(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aDst = mTemp;
    aDst[ 0] = aSrc[ 7]; aDst[ 1] = aSrc[15]; aDst[ 2] = aSrc[23]; aDst[ 3] = aSrc[31];
    aDst[ 4] = aSrc[39]; aDst[ 5] = aSrc[47]; aDst[ 6] = aSrc[55]; aDst[ 7] = aSrc[63];
    aDst[ 8] = aSrc[ 6]; aDst[ 9] = aSrc[14]; aDst[10] = aSrc[22]; aDst[11] = aSrc[30];
    aDst[12] = aSrc[38]; aDst[13] = aSrc[46]; aDst[14] = aSrc[54]; aDst[15] = aSrc[62];
    aDst[16] = aSrc[ 5]; aDst[17] = aSrc[13]; aDst[18] = aSrc[21]; aDst[19] = aSrc[29];
    aDst[20] = aSrc[37]; aDst[21] = aSrc[45]; aDst[22] = aSrc[53]; aDst[23] = aSrc[61];
    aDst[24] = aSrc[ 4]; aDst[25] = aSrc[12]; aDst[26] = aSrc[20]; aDst[27] = aSrc[28];
    aDst[28] = aSrc[36]; aDst[29] = aSrc[44]; aDst[30] = aSrc[52]; aDst[31] = aSrc[60];
    aDst[32] = aSrc[ 3]; aDst[33] = aSrc[11]; aDst[34] = aSrc[19]; aDst[35] = aSrc[27];
    aDst[36] = aSrc[35]; aDst[37] = aSrc[43]; aDst[38] = aSrc[51]; aDst[39] = aSrc[59];
    aDst[40] = aSrc[ 2]; aDst[41] = aSrc[10]; aDst[42] = aSrc[18]; aDst[43] = aSrc[26];
    aDst[44] = aSrc[34]; aDst[45] = aSrc[42]; aDst[46] = aSrc[50]; aDst[47] = aSrc[58];
    aDst[48] = aSrc[ 1]; aDst[49] = aSrc[ 9]; aDst[50] = aSrc[17]; aDst[51] = aSrc[25];
    aDst[52] = aSrc[33]; aDst[53] = aSrc[41]; aDst[54] = aSrc[49]; aDst[55] = aSrc[57];
    aDst[56] = aSrc[ 0]; aDst[57] = aSrc[ 8]; aDst[58] = aSrc[16]; aDst[59] = aSrc[24];
    aDst[60] = aSrc[32]; aDst[61] = aSrc[40]; aDst[62] = aSrc[48]; aDst[63] = aSrc[56];
    memcpy(mDataBase, mTemp, 64);
}

void TwistFastMatrix::RotateRightBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    // copy whole matrix to temp
    memcpy(aTmp, aSrc, 64);

    // A <- C
    aSrc[ 0] = aTmp[32]; aSrc[ 1] = aTmp[33]; aSrc[ 2] = aTmp[34]; aSrc[ 3] = aTmp[35];
    aSrc[ 8] = aTmp[40]; aSrc[ 9] = aTmp[41]; aSrc[10] = aTmp[42]; aSrc[11] = aTmp[43];
    aSrc[16] = aTmp[48]; aSrc[17] = aTmp[49]; aSrc[18] = aTmp[50]; aSrc[19] = aTmp[51];
    aSrc[24] = aTmp[56]; aSrc[25] = aTmp[57]; aSrc[26] = aTmp[58]; aSrc[27] = aTmp[59];

    // B <- A
    aSrc[ 4] = aTmp[ 0]; aSrc[ 5] = aTmp[ 1]; aSrc[ 6] = aTmp[ 2]; aSrc[ 7] = aTmp[ 3];
    aSrc[12] = aTmp[ 8]; aSrc[13] = aTmp[ 9]; aSrc[14] = aTmp[10]; aSrc[15] = aTmp[11];
    aSrc[20] = aTmp[16]; aSrc[21] = aTmp[17]; aSrc[22] = aTmp[18]; aSrc[23] = aTmp[19];
    aSrc[28] = aTmp[24]; aSrc[29] = aTmp[25]; aSrc[30] = aTmp[26]; aSrc[31] = aTmp[27];

    // D <- B
    aSrc[36] = aTmp[ 4]; aSrc[37] = aTmp[ 5]; aSrc[38] = aTmp[ 6]; aSrc[39] = aTmp[ 7];
    aSrc[44] = aTmp[12]; aSrc[45] = aTmp[13]; aSrc[46] = aTmp[14]; aSrc[47] = aTmp[15];
    aSrc[52] = aTmp[20]; aSrc[53] = aTmp[21]; aSrc[54] = aTmp[22]; aSrc[55] = aTmp[23];
    aSrc[60] = aTmp[28]; aSrc[61] = aTmp[29]; aSrc[62] = aTmp[30]; aSrc[63] = aTmp[31];

    // C <- D
    aSrc[32] = aTmp[36]; aSrc[33] = aTmp[37]; aSrc[34] = aTmp[38]; aSrc[35] = aTmp[39];
    aSrc[40] = aTmp[44]; aSrc[41] = aTmp[45]; aSrc[42] = aTmp[46]; aSrc[43] = aTmp[47];
    aSrc[48] = aTmp[52]; aSrc[49] = aTmp[53]; aSrc[50] = aTmp[54]; aSrc[51] = aTmp[55];
    aSrc[56] = aTmp[60]; aSrc[57] = aTmp[61]; aSrc[58] = aTmp[62]; aSrc[59] = aTmp[63];
}

void TwistFastMatrix::RotateLeftBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    // copy whole matrix to temp
    memcpy(aTmp, aSrc, 64);

    // A <- B
    aSrc[ 0] = aTmp[ 4]; aSrc[ 1] = aTmp[ 5]; aSrc[ 2] = aTmp[ 6]; aSrc[ 3] = aTmp[ 7];
    aSrc[ 8] = aTmp[12]; aSrc[ 9] = aTmp[13]; aSrc[10] = aTmp[14]; aSrc[11] = aTmp[15];
    aSrc[16] = aTmp[20]; aSrc[17] = aTmp[21]; aSrc[18] = aTmp[22]; aSrc[19] = aTmp[23];
    aSrc[24] = aTmp[28]; aSrc[25] = aTmp[29]; aSrc[26] = aTmp[30]; aSrc[27] = aTmp[31];

    // B <- D
    aSrc[ 4] = aTmp[36]; aSrc[ 5] = aTmp[37]; aSrc[ 6] = aTmp[38]; aSrc[ 7] = aTmp[39];
    aSrc[12] = aTmp[44]; aSrc[13] = aTmp[45]; aSrc[14] = aTmp[46]; aSrc[15] = aTmp[47];
    aSrc[20] = aTmp[52]; aSrc[21] = aTmp[53]; aSrc[22] = aTmp[54]; aSrc[23] = aTmp[55];
    aSrc[28] = aTmp[60]; aSrc[29] = aTmp[61]; aSrc[30] = aTmp[62]; aSrc[31] = aTmp[63];

    // D <- C
    aSrc[36] = aTmp[32]; aSrc[37] = aTmp[33]; aSrc[38] = aTmp[34]; aSrc[39] = aTmp[35];
    aSrc[44] = aTmp[40]; aSrc[45] = aTmp[41]; aSrc[46] = aTmp[42]; aSrc[47] = aTmp[43];
    aSrc[52] = aTmp[48]; aSrc[53] = aTmp[49]; aSrc[54] = aTmp[50]; aSrc[55] = aTmp[51];
    aSrc[60] = aTmp[56]; aSrc[61] = aTmp[57]; aSrc[62] = aTmp[58]; aSrc[63] = aTmp[59];

    // C <- A
    aSrc[32] = aTmp[ 0]; aSrc[33] = aTmp[ 1]; aSrc[34] = aTmp[ 2]; aSrc[35] = aTmp[ 3];
    aSrc[40] = aTmp[ 8]; aSrc[41] = aTmp[ 9]; aSrc[42] = aTmp[10]; aSrc[43] = aTmp[11];
    aSrc[48] = aTmp[16]; aSrc[49] = aTmp[17]; aSrc[50] = aTmp[18]; aSrc[51] = aTmp[19];
    aSrc[56] = aTmp[24]; aSrc[57] = aTmp[25]; aSrc[58] = aTmp[26]; aSrc[59] = aTmp[27];
}

void TwistFastMatrix::RotateRightQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 0] = aSrc[24]; aTmp[ 1] = aSrc[16]; aTmp[ 2] = aSrc[ 8]; aTmp[ 3] = aSrc[ 0];
    aTmp[ 8] = aSrc[25]; aTmp[ 9] = aSrc[17]; aTmp[10] = aSrc[ 9]; aTmp[11] = aSrc[ 1];
    aTmp[16] = aSrc[26]; aTmp[17] = aSrc[18]; aTmp[18] = aSrc[10]; aTmp[19] = aSrc[ 2];
    aTmp[24] = aSrc[27]; aTmp[25] = aSrc[19]; aTmp[26] = aSrc[11]; aTmp[27] = aSrc[ 3];

    aSrc[ 0] = aTmp[ 0]; aSrc[ 1] = aTmp[ 1]; aSrc[ 2] = aTmp[ 2]; aSrc[ 3] = aTmp[ 3];
    aSrc[ 8] = aTmp[ 8]; aSrc[ 9] = aTmp[ 9]; aSrc[10] = aTmp[10]; aSrc[11] = aTmp[11];
    aSrc[16] = aTmp[16]; aSrc[17] = aTmp[17]; aSrc[18] = aTmp[18]; aSrc[19] = aTmp[19];
    aSrc[24] = aTmp[24]; aSrc[25] = aTmp[25]; aSrc[26] = aTmp[26]; aSrc[27] = aTmp[27];
}

void TwistFastMatrix::RotateRightQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 4] = aSrc[28]; aTmp[ 5] = aSrc[20]; aTmp[ 6] = aSrc[12]; aTmp[ 7] = aSrc[ 4];
    aTmp[12] = aSrc[29]; aTmp[13] = aSrc[21]; aTmp[14] = aSrc[13]; aTmp[15] = aSrc[ 5];
    aTmp[20] = aSrc[30]; aTmp[21] = aSrc[22]; aTmp[22] = aSrc[14]; aTmp[23] = aSrc[ 6];
    aTmp[28] = aSrc[31]; aTmp[29] = aSrc[23]; aTmp[30] = aSrc[15]; aTmp[31] = aSrc[ 7];

    aSrc[ 4] = aTmp[ 4]; aSrc[ 5] = aTmp[ 5]; aSrc[ 6] = aTmp[ 6]; aSrc[ 7] = aTmp[ 7];
    aSrc[12] = aTmp[12]; aSrc[13] = aTmp[13]; aSrc[14] = aTmp[14]; aSrc[15] = aTmp[15];
    aSrc[20] = aTmp[20]; aSrc[21] = aTmp[21]; aSrc[22] = aTmp[22]; aSrc[23] = aTmp[23];
    aSrc[28] = aTmp[28]; aSrc[29] = aTmp[29]; aSrc[30] = aTmp[30]; aSrc[31] = aTmp[31];
}

void TwistFastMatrix::RotateRightQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[32] = aSrc[56]; aTmp[33] = aSrc[48]; aTmp[34] = aSrc[40]; aTmp[35] = aSrc[32];
    aTmp[40] = aSrc[57]; aTmp[41] = aSrc[49]; aTmp[42] = aSrc[41]; aTmp[43] = aSrc[33];
    aTmp[48] = aSrc[58]; aTmp[49] = aSrc[50]; aTmp[50] = aSrc[42]; aTmp[51] = aSrc[34];
    aTmp[56] = aSrc[59]; aTmp[57] = aSrc[51]; aTmp[58] = aSrc[43]; aTmp[59] = aSrc[35];

    aSrc[32] = aTmp[32]; aSrc[33] = aTmp[33]; aSrc[34] = aTmp[34]; aSrc[35] = aTmp[35];
    aSrc[40] = aTmp[40]; aSrc[41] = aTmp[41]; aSrc[42] = aTmp[42]; aSrc[43] = aTmp[43];
    aSrc[48] = aTmp[48]; aSrc[49] = aTmp[49]; aSrc[50] = aTmp[50]; aSrc[51] = aTmp[51];
    aSrc[56] = aTmp[56]; aSrc[57] = aTmp[57]; aSrc[58] = aTmp[58]; aSrc[59] = aTmp[59];
}

void TwistFastMatrix::RotateRightQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[36] = aSrc[60]; aTmp[37] = aSrc[52]; aTmp[38] = aSrc[44]; aTmp[39] = aSrc[36];
    aTmp[44] = aSrc[61]; aTmp[45] = aSrc[53]; aTmp[46] = aSrc[45]; aTmp[47] = aSrc[37];
    aTmp[52] = aSrc[62]; aTmp[53] = aSrc[54]; aTmp[54] = aSrc[46]; aTmp[55] = aSrc[38];
    aTmp[60] = aSrc[63]; aTmp[61] = aSrc[55]; aTmp[62] = aSrc[47]; aTmp[63] = aSrc[39];

    aSrc[36] = aTmp[36]; aSrc[37] = aTmp[37]; aSrc[38] = aTmp[38]; aSrc[39] = aTmp[39];
    aSrc[44] = aTmp[44]; aSrc[45] = aTmp[45]; aSrc[46] = aTmp[46]; aSrc[47] = aTmp[47];
    aSrc[52] = aTmp[52]; aSrc[53] = aTmp[53]; aSrc[54] = aTmp[54]; aSrc[55] = aTmp[55];
    aSrc[60] = aTmp[60]; aSrc[61] = aTmp[61]; aSrc[62] = aTmp[62]; aSrc[63] = aTmp[63];
}

void TwistFastMatrix::RotateRightEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    RotateRightQuarterA();
    RotateRightQuarterB();
    RotateRightQuarterC();
    RotateRightQuarterD();
}

void TwistFastMatrix::RotateLeftQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 0] = aSrc[ 3]; aTmp[ 1] = aSrc[11]; aTmp[ 2] = aSrc[19]; aTmp[ 3] = aSrc[27];
    aTmp[ 8] = aSrc[ 2]; aTmp[ 9] = aSrc[10]; aTmp[10] = aSrc[18]; aTmp[11] = aSrc[26];
    aTmp[16] = aSrc[ 1]; aTmp[17] = aSrc[ 9]; aTmp[18] = aSrc[17]; aTmp[19] = aSrc[25];
    aTmp[24] = aSrc[ 0]; aTmp[25] = aSrc[ 8]; aTmp[26] = aSrc[16]; aTmp[27] = aSrc[24];

    aSrc[ 0] = aTmp[ 0]; aSrc[ 1] = aTmp[ 1]; aSrc[ 2] = aTmp[ 2]; aSrc[ 3] = aTmp[ 3];
    aSrc[ 8] = aTmp[ 8]; aSrc[ 9] = aTmp[ 9]; aSrc[10] = aTmp[10]; aSrc[11] = aTmp[11];
    aSrc[16] = aTmp[16]; aSrc[17] = aTmp[17]; aSrc[18] = aTmp[18]; aSrc[19] = aTmp[19];
    aSrc[24] = aTmp[24]; aSrc[25] = aTmp[25]; aSrc[26] = aTmp[26]; aSrc[27] = aTmp[27];
}

void TwistFastMatrix::RotateLeftQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 4] = aSrc[ 7]; aTmp[ 5] = aSrc[15]; aTmp[ 6] = aSrc[23]; aTmp[ 7] = aSrc[31];
    aTmp[12] = aSrc[ 6]; aTmp[13] = aSrc[14]; aTmp[14] = aSrc[22]; aTmp[15] = aSrc[30];
    aTmp[20] = aSrc[ 5]; aTmp[21] = aSrc[13]; aTmp[22] = aSrc[21]; aTmp[23] = aSrc[29];
    aTmp[28] = aSrc[ 4]; aTmp[29] = aSrc[12]; aTmp[30] = aSrc[20]; aTmp[31] = aSrc[28];

    aSrc[ 4] = aTmp[ 4]; aSrc[ 5] = aTmp[ 5]; aSrc[ 6] = aTmp[ 6]; aSrc[ 7] = aTmp[ 7];
    aSrc[12] = aTmp[12]; aSrc[13] = aTmp[13]; aSrc[14] = aTmp[14]; aSrc[15] = aTmp[15];
    aSrc[20] = aTmp[20]; aSrc[21] = aTmp[21]; aSrc[22] = aTmp[22]; aSrc[23] = aTmp[23];
    aSrc[28] = aTmp[28]; aSrc[29] = aTmp[29]; aSrc[30] = aTmp[30]; aSrc[31] = aTmp[31];
}

void TwistFastMatrix::RotateLeftQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[32] = aSrc[35]; aTmp[33] = aSrc[43]; aTmp[34] = aSrc[51]; aTmp[35] = aSrc[59];
    aTmp[40] = aSrc[34]; aTmp[41] = aSrc[42]; aTmp[42] = aSrc[50]; aTmp[43] = aSrc[58];
    aTmp[48] = aSrc[33]; aTmp[49] = aSrc[41]; aTmp[50] = aSrc[49]; aTmp[51] = aSrc[57];
    aTmp[56] = aSrc[32]; aTmp[57] = aSrc[40]; aTmp[58] = aSrc[48]; aTmp[59] = aSrc[56];

    aSrc[32] = aTmp[32]; aSrc[33] = aTmp[33]; aSrc[34] = aTmp[34]; aSrc[35] = aTmp[35];
    aSrc[40] = aTmp[40]; aSrc[41] = aTmp[41]; aSrc[42] = aTmp[42]; aSrc[43] = aTmp[43];
    aSrc[48] = aTmp[48]; aSrc[49] = aTmp[49]; aSrc[50] = aTmp[50]; aSrc[51] = aTmp[51];
    aSrc[56] = aTmp[56]; aSrc[57] = aTmp[57]; aSrc[58] = aTmp[58]; aSrc[59] = aTmp[59];
}

void TwistFastMatrix::RotateLeftQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[36] = aSrc[39]; aTmp[37] = aSrc[47]; aTmp[38] = aSrc[55]; aTmp[39] = aSrc[63];
    aTmp[44] = aSrc[38]; aTmp[45] = aSrc[46]; aTmp[46] = aSrc[54]; aTmp[47] = aSrc[62];
    aTmp[52] = aSrc[37]; aTmp[53] = aSrc[45]; aTmp[54] = aSrc[53]; aTmp[55] = aSrc[61];
    aTmp[60] = aSrc[36]; aTmp[61] = aSrc[44]; aTmp[62] = aSrc[52]; aTmp[63] = aSrc[60];

    aSrc[36] = aTmp[36]; aSrc[37] = aTmp[37]; aSrc[38] = aTmp[38]; aSrc[39] = aTmp[39];
    aSrc[44] = aTmp[44]; aSrc[45] = aTmp[45]; aSrc[46] = aTmp[46]; aSrc[47] = aTmp[47];
    aSrc[52] = aTmp[52]; aSrc[53] = aTmp[53]; aSrc[54] = aTmp[54]; aSrc[55] = aTmp[55];
    aSrc[60] = aTmp[60]; aSrc[61] = aTmp[61]; aSrc[62] = aTmp[62]; aSrc[63] = aTmp[63];
}

void TwistFastMatrix::RotateLeftEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    RotateLeftQuarterA();
    RotateLeftQuarterB();
    RotateLeftQuarterC();
    RotateLeftQuarterD();
}

// main diagonal flip (same as transpose)
void TwistFastMatrix::TransposeMainDiagonal(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    std::uint8_t aHold;
    aHold = mDataBase[ 1]; mDataBase[ 1] = mDataBase[ 8]; mDataBase[ 8] = aHold;
    aHold = mDataBase[ 2]; mDataBase[ 2] = mDataBase[16]; mDataBase[16] = aHold;
    aHold = mDataBase[ 3]; mDataBase[ 3] = mDataBase[24]; mDataBase[24] = aHold;
    aHold = mDataBase[ 4]; mDataBase[ 4] = mDataBase[32]; mDataBase[32] = aHold;
    aHold = mDataBase[ 5]; mDataBase[ 5] = mDataBase[40]; mDataBase[40] = aHold;
    aHold = mDataBase[ 6]; mDataBase[ 6] = mDataBase[48]; mDataBase[48] = aHold;
    aHold = mDataBase[ 7]; mDataBase[ 7] = mDataBase[56]; mDataBase[56] = aHold;
    aHold = mDataBase[10]; mDataBase[10] = mDataBase[17]; mDataBase[17] = aHold;
    aHold = mDataBase[11]; mDataBase[11] = mDataBase[25]; mDataBase[25] = aHold;
    aHold = mDataBase[12]; mDataBase[12] = mDataBase[33]; mDataBase[33] = aHold;
    aHold = mDataBase[13]; mDataBase[13] = mDataBase[41]; mDataBase[41] = aHold;
    aHold = mDataBase[14]; mDataBase[14] = mDataBase[49]; mDataBase[49] = aHold;
    aHold = mDataBase[15]; mDataBase[15] = mDataBase[57]; mDataBase[57] = aHold;
    aHold = mDataBase[19]; mDataBase[19] = mDataBase[26]; mDataBase[26] = aHold;
    aHold = mDataBase[20]; mDataBase[20] = mDataBase[34]; mDataBase[34] = aHold;
    aHold = mDataBase[21]; mDataBase[21] = mDataBase[42]; mDataBase[42] = aHold;
    aHold = mDataBase[22]; mDataBase[22] = mDataBase[50]; mDataBase[50] = aHold;
    aHold = mDataBase[23]; mDataBase[23] = mDataBase[58]; mDataBase[58] = aHold;
    aHold = mDataBase[28]; mDataBase[28] = mDataBase[35]; mDataBase[35] = aHold;
    aHold = mDataBase[29]; mDataBase[29] = mDataBase[43]; mDataBase[43] = aHold;
    aHold = mDataBase[30]; mDataBase[30] = mDataBase[51]; mDataBase[51] = aHold;
    aHold = mDataBase[31]; mDataBase[31] = mDataBase[59]; mDataBase[59] = aHold;
    aHold = mDataBase[37]; mDataBase[37] = mDataBase[44]; mDataBase[44] = aHold;
    aHold = mDataBase[38]; mDataBase[38] = mDataBase[52]; mDataBase[52] = aHold;
    aHold = mDataBase[39]; mDataBase[39] = mDataBase[60]; mDataBase[60] = aHold;
    aHold = mDataBase[46]; mDataBase[46] = mDataBase[53]; mDataBase[53] = aHold;
    aHold = mDataBase[47]; mDataBase[47] = mDataBase[61]; mDataBase[61] = aHold;
    aHold = mDataBase[55]; mDataBase[55] = mDataBase[62]; mDataBase[62] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[ 1]; mDataBase[ 1] = mDataBase[ 8]; mDataBase[ 8] = aHold;
    aHold = mDataBase[ 2]; mDataBase[ 2] = mDataBase[16]; mDataBase[16] = aHold;
    aHold = mDataBase[ 3]; mDataBase[ 3] = mDataBase[24]; mDataBase[24] = aHold;

    aHold = mDataBase[10]; mDataBase[10] = mDataBase[17]; mDataBase[17] = aHold;
    aHold = mDataBase[11]; mDataBase[11] = mDataBase[25]; mDataBase[25] = aHold;

    aHold = mDataBase[19]; mDataBase[19] = mDataBase[26]; mDataBase[26] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[ 5]; mDataBase[ 5] = mDataBase[12]; mDataBase[12] = aHold;
    aHold = mDataBase[ 6]; mDataBase[ 6] = mDataBase[20]; mDataBase[20] = aHold;
    aHold = mDataBase[ 7]; mDataBase[ 7] = mDataBase[28]; mDataBase[28] = aHold;

    aHold = mDataBase[14]; mDataBase[14] = mDataBase[21]; mDataBase[21] = aHold;
    aHold = mDataBase[15]; mDataBase[15] = mDataBase[29]; mDataBase[29] = aHold;

    aHold = mDataBase[23]; mDataBase[23] = mDataBase[30]; mDataBase[30] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[33]; mDataBase[33] = mDataBase[40]; mDataBase[40] = aHold;
    aHold = mDataBase[34]; mDataBase[34] = mDataBase[48]; mDataBase[48] = aHold;
    aHold = mDataBase[35]; mDataBase[35] = mDataBase[56]; mDataBase[56] = aHold;

    aHold = mDataBase[42]; mDataBase[42] = mDataBase[49]; mDataBase[49] = aHold;
    aHold = mDataBase[43]; mDataBase[43] = mDataBase[57]; mDataBase[57] = aHold;

    aHold = mDataBase[51]; mDataBase[51] = mDataBase[58]; mDataBase[58] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[37]; mDataBase[37] = mDataBase[44]; mDataBase[44] = aHold;
    aHold = mDataBase[38]; mDataBase[38] = mDataBase[52]; mDataBase[52] = aHold;
    aHold = mDataBase[39]; mDataBase[39] = mDataBase[60]; mDataBase[60] = aHold;

    aHold = mDataBase[46]; mDataBase[46] = mDataBase[53]; mDataBase[53] = aHold;
    aHold = mDataBase[47]; mDataBase[47] = mDataBase[61]; mDataBase[61] = aHold;

    aHold = mDataBase[55]; mDataBase[55] = mDataBase[62]; mDataBase[62] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    TransposeMainDiagonalQuarterA();
    TransposeMainDiagonalQuarterB();
    TransposeMainDiagonalQuarterC();
    TransposeMainDiagonalQuarterD();
}


// anti-diagonal flip
void TwistFastMatrix::TransposeAntiDiagonal(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;
    aHold = mDataBase[ 0]; mDataBase[ 0] = mDataBase[63]; mDataBase[63] = aHold;
    aHold = mDataBase[ 1]; mDataBase[ 1] = mDataBase[55]; mDataBase[55] = aHold;
    aHold = mDataBase[ 2]; mDataBase[ 2] = mDataBase[47]; mDataBase[47] = aHold;
    aHold = mDataBase[ 3]; mDataBase[ 3] = mDataBase[39]; mDataBase[39] = aHold;
    aHold = mDataBase[ 4]; mDataBase[ 4] = mDataBase[31]; mDataBase[31] = aHold;
    aHold = mDataBase[ 5]; mDataBase[ 5] = mDataBase[23]; mDataBase[23] = aHold;
    aHold = mDataBase[ 6]; mDataBase[ 6] = mDataBase[15]; mDataBase[15] = aHold;
    aHold = mDataBase[ 8]; mDataBase[ 8] = mDataBase[62]; mDataBase[62] = aHold;
    aHold = mDataBase[ 9]; mDataBase[ 9] = mDataBase[54]; mDataBase[54] = aHold;
    aHold = mDataBase[10]; mDataBase[10] = mDataBase[46]; mDataBase[46] = aHold;
    aHold = mDataBase[11]; mDataBase[11] = mDataBase[38]; mDataBase[38] = aHold;
    aHold = mDataBase[12]; mDataBase[12] = mDataBase[30]; mDataBase[30] = aHold;
    aHold = mDataBase[13]; mDataBase[13] = mDataBase[22]; mDataBase[22] = aHold;
    aHold = mDataBase[16]; mDataBase[16] = mDataBase[61]; mDataBase[61] = aHold;
    aHold = mDataBase[17]; mDataBase[17] = mDataBase[53]; mDataBase[53] = aHold;
    aHold = mDataBase[18]; mDataBase[18] = mDataBase[45]; mDataBase[45] = aHold;
    aHold = mDataBase[19]; mDataBase[19] = mDataBase[37]; mDataBase[37] = aHold;
    aHold = mDataBase[20]; mDataBase[20] = mDataBase[29]; mDataBase[29] = aHold;
    aHold = mDataBase[24]; mDataBase[24] = mDataBase[60]; mDataBase[60] = aHold;
    aHold = mDataBase[25]; mDataBase[25] = mDataBase[52]; mDataBase[52] = aHold;
    aHold = mDataBase[26]; mDataBase[26] = mDataBase[44]; mDataBase[44] = aHold;
    aHold = mDataBase[27]; mDataBase[27] = mDataBase[36]; mDataBase[36] = aHold;
    aHold = mDataBase[32]; mDataBase[32] = mDataBase[59]; mDataBase[59] = aHold;
    aHold = mDataBase[33]; mDataBase[33] = mDataBase[51]; mDataBase[51] = aHold;
    aHold = mDataBase[34]; mDataBase[34] = mDataBase[43]; mDataBase[43] = aHold;
    aHold = mDataBase[40]; mDataBase[40] = mDataBase[58]; mDataBase[58] = aHold;
    aHold = mDataBase[41]; mDataBase[41] = mDataBase[50]; mDataBase[50] = aHold;
    aHold = mDataBase[48]; mDataBase[48] = mDataBase[57]; mDataBase[57] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[ 0]; mDataBase[ 0] = mDataBase[27]; mDataBase[27] = aHold;
    aHold = mDataBase[ 1]; mDataBase[ 1] = mDataBase[19]; mDataBase[19] = aHold;
    aHold = mDataBase[ 2]; mDataBase[ 2] = mDataBase[11]; mDataBase[11] = aHold;

    aHold = mDataBase[ 8]; mDataBase[ 8] = mDataBase[26]; mDataBase[26] = aHold;
    aHold = mDataBase[ 9]; mDataBase[ 9] = mDataBase[18]; mDataBase[18] = aHold;

    aHold = mDataBase[16]; mDataBase[16] = mDataBase[25]; mDataBase[25] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[ 4]; mDataBase[ 4] = mDataBase[31]; mDataBase[31] = aHold;
    aHold = mDataBase[ 5]; mDataBase[ 5] = mDataBase[23]; mDataBase[23] = aHold;
    aHold = mDataBase[ 6]; mDataBase[ 6] = mDataBase[15]; mDataBase[15] = aHold;

    aHold = mDataBase[12]; mDataBase[12] = mDataBase[30]; mDataBase[30] = aHold;
    aHold = mDataBase[13]; mDataBase[13] = mDataBase[22]; mDataBase[22] = aHold;

    aHold = mDataBase[20]; mDataBase[20] = mDataBase[29]; mDataBase[29] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[32]; mDataBase[32] = mDataBase[59]; mDataBase[59] = aHold;
    aHold = mDataBase[33]; mDataBase[33] = mDataBase[51]; mDataBase[51] = aHold;
    aHold = mDataBase[34]; mDataBase[34] = mDataBase[43]; mDataBase[43] = aHold;

    aHold = mDataBase[40]; mDataBase[40] = mDataBase[58]; mDataBase[58] = aHold;
    aHold = mDataBase[41]; mDataBase[41] = mDataBase[50]; mDataBase[50] = aHold;

    aHold = mDataBase[48]; mDataBase[48] = mDataBase[57]; mDataBase[57] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[36]; mDataBase[36] = mDataBase[63]; mDataBase[63] = aHold;
    aHold = mDataBase[37]; mDataBase[37] = mDataBase[55]; mDataBase[55] = aHold;
    aHold = mDataBase[38]; mDataBase[38] = mDataBase[47]; mDataBase[47] = aHold;

    aHold = mDataBase[44]; mDataBase[44] = mDataBase[62]; mDataBase[62] = aHold;
    aHold = mDataBase[45]; mDataBase[45] = mDataBase[54]; mDataBase[54] = aHold;

    aHold = mDataBase[52]; mDataBase[52] = mDataBase[61]; mDataBase[61] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    TransposeAntiDiagonalQuarterA();
    TransposeAntiDiagonalQuarterB();
    TransposeAntiDiagonalQuarterC();
    TransposeAntiDiagonalQuarterD();
}

void TwistFastMatrix::FlipHorizontal(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // row 0
    aHold = mDataBase[ 0]; mDataBase[ 0] = mDataBase[ 7]; mDataBase[ 7] = aHold;
    aHold = mDataBase[ 1]; mDataBase[ 1] = mDataBase[ 6]; mDataBase[ 6] = aHold;
    aHold = mDataBase[ 2]; mDataBase[ 2] = mDataBase[ 5]; mDataBase[ 5] = aHold;
    aHold = mDataBase[ 3]; mDataBase[ 3] = mDataBase[ 4]; mDataBase[ 4] = aHold;

    // row 1
    aHold = mDataBase[ 8]; mDataBase[ 8] = mDataBase[15]; mDataBase[15] = aHold;
    aHold = mDataBase[ 9]; mDataBase[ 9] = mDataBase[14]; mDataBase[14] = aHold;
    aHold = mDataBase[10]; mDataBase[10] = mDataBase[13]; mDataBase[13] = aHold;
    aHold = mDataBase[11]; mDataBase[11] = mDataBase[12]; mDataBase[12] = aHold;

    // row 2
    aHold = mDataBase[16]; mDataBase[16] = mDataBase[23]; mDataBase[23] = aHold;
    aHold = mDataBase[17]; mDataBase[17] = mDataBase[22]; mDataBase[22] = aHold;
    aHold = mDataBase[18]; mDataBase[18] = mDataBase[21]; mDataBase[21] = aHold;
    aHold = mDataBase[19]; mDataBase[19] = mDataBase[20]; mDataBase[20] = aHold;

    // row 3
    aHold = mDataBase[24]; mDataBase[24] = mDataBase[31]; mDataBase[31] = aHold;
    aHold = mDataBase[25]; mDataBase[25] = mDataBase[30]; mDataBase[30] = aHold;
    aHold = mDataBase[26]; mDataBase[26] = mDataBase[29]; mDataBase[29] = aHold;
    aHold = mDataBase[27]; mDataBase[27] = mDataBase[28]; mDataBase[28] = aHold;

    // row 4
    aHold = mDataBase[32]; mDataBase[32] = mDataBase[39]; mDataBase[39] = aHold;
    aHold = mDataBase[33]; mDataBase[33] = mDataBase[38]; mDataBase[38] = aHold;
    aHold = mDataBase[34]; mDataBase[34] = mDataBase[37]; mDataBase[37] = aHold;
    aHold = mDataBase[35]; mDataBase[35] = mDataBase[36]; mDataBase[36] = aHold;

    // row 5
    aHold = mDataBase[40]; mDataBase[40] = mDataBase[47]; mDataBase[47] = aHold;
    aHold = mDataBase[41]; mDataBase[41] = mDataBase[46]; mDataBase[46] = aHold;
    aHold = mDataBase[42]; mDataBase[42] = mDataBase[45]; mDataBase[45] = aHold;
    aHold = mDataBase[43]; mDataBase[43] = mDataBase[44]; mDataBase[44] = aHold;

    // row 6
    aHold = mDataBase[48]; mDataBase[48] = mDataBase[55]; mDataBase[55] = aHold;
    aHold = mDataBase[49]; mDataBase[49] = mDataBase[54]; mDataBase[54] = aHold;
    aHold = mDataBase[50]; mDataBase[50] = mDataBase[53]; mDataBase[53] = aHold;
    aHold = mDataBase[51]; mDataBase[51] = mDataBase[52]; mDataBase[52] = aHold;

    // row 7
    aHold = mDataBase[56]; mDataBase[56] = mDataBase[63]; mDataBase[63] = aHold;
    aHold = mDataBase[57]; mDataBase[57] = mDataBase[62]; mDataBase[62] = aHold;
    aHold = mDataBase[58]; mDataBase[58] = mDataBase[61]; mDataBase[61] = aHold;
    aHold = mDataBase[59]; mDataBase[59] = mDataBase[60]; mDataBase[60] = aHold;
}

void TwistFastMatrix::FlipVertical(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // row 0 ↔ row 7
    aHold = mDataBase[ 0]; mDataBase[ 0] = mDataBase[56]; mDataBase[56] = aHold;
    aHold = mDataBase[ 1]; mDataBase[ 1] = mDataBase[57]; mDataBase[57] = aHold;
    aHold = mDataBase[ 2]; mDataBase[ 2] = mDataBase[58]; mDataBase[58] = aHold;
    aHold = mDataBase[ 3]; mDataBase[ 3] = mDataBase[59]; mDataBase[59] = aHold;
    aHold = mDataBase[ 4]; mDataBase[ 4] = mDataBase[60]; mDataBase[60] = aHold;
    aHold = mDataBase[ 5]; mDataBase[ 5] = mDataBase[61]; mDataBase[61] = aHold;
    aHold = mDataBase[ 6]; mDataBase[ 6] = mDataBase[62]; mDataBase[62] = aHold;
    aHold = mDataBase[ 7]; mDataBase[ 7] = mDataBase[63]; mDataBase[63] = aHold;

    // row 1 ↔ row 6
    aHold = mDataBase[ 8]; mDataBase[ 8] = mDataBase[48]; mDataBase[48] = aHold;
    aHold = mDataBase[ 9]; mDataBase[ 9] = mDataBase[49]; mDataBase[49] = aHold;
    aHold = mDataBase[10]; mDataBase[10] = mDataBase[50]; mDataBase[50] = aHold;
    aHold = mDataBase[11]; mDataBase[11] = mDataBase[51]; mDataBase[51] = aHold;
    aHold = mDataBase[12]; mDataBase[12] = mDataBase[52]; mDataBase[52] = aHold;
    aHold = mDataBase[13]; mDataBase[13] = mDataBase[53]; mDataBase[53] = aHold;
    aHold = mDataBase[14]; mDataBase[14] = mDataBase[54]; mDataBase[54] = aHold;
    aHold = mDataBase[15]; mDataBase[15] = mDataBase[55]; mDataBase[55] = aHold;

    // row 2 ↔ row 5
    aHold = mDataBase[16]; mDataBase[16] = mDataBase[40]; mDataBase[40] = aHold;
    aHold = mDataBase[17]; mDataBase[17] = mDataBase[41]; mDataBase[41] = aHold;
    aHold = mDataBase[18]; mDataBase[18] = mDataBase[42]; mDataBase[42] = aHold;
    aHold = mDataBase[19]; mDataBase[19] = mDataBase[43]; mDataBase[43] = aHold;
    aHold = mDataBase[20]; mDataBase[20] = mDataBase[44]; mDataBase[44] = aHold;
    aHold = mDataBase[21]; mDataBase[21] = mDataBase[45]; mDataBase[45] = aHold;
    aHold = mDataBase[22]; mDataBase[22] = mDataBase[46]; mDataBase[46] = aHold;
    aHold = mDataBase[23]; mDataBase[23] = mDataBase[47]; mDataBase[47] = aHold;

    // row 3 ↔ row 4
    aHold = mDataBase[24]; mDataBase[24] = mDataBase[32]; mDataBase[32] = aHold;
    aHold = mDataBase[25]; mDataBase[25] = mDataBase[33]; mDataBase[33] = aHold;
    aHold = mDataBase[26]; mDataBase[26] = mDataBase[34]; mDataBase[34] = aHold;
    aHold = mDataBase[27]; mDataBase[27] = mDataBase[35]; mDataBase[35] = aHold;
    aHold = mDataBase[28]; mDataBase[28] = mDataBase[36]; mDataBase[36] = aHold;
    aHold = mDataBase[29]; mDataBase[29] = mDataBase[37]; mDataBase[37] = aHold;
    aHold = mDataBase[30]; mDataBase[30] = mDataBase[38]; mDataBase[38] = aHold;
    aHold = mDataBase[31]; mDataBase[31] = mDataBase[39]; mDataBase[39] = aHold;
}

void TwistFastMatrix::FlipHorizontalQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[ 0]; mDataBase[ 0] = mDataBase[ 3]; mDataBase[ 3] = aHold;
    aHold = mDataBase[ 1]; mDataBase[ 1] = mDataBase[ 2]; mDataBase[ 2] = aHold;

    aHold = mDataBase[ 8]; mDataBase[ 8] = mDataBase[11]; mDataBase[11] = aHold;
    aHold = mDataBase[ 9]; mDataBase[ 9] = mDataBase[10]; mDataBase[10] = aHold;

    aHold = mDataBase[16]; mDataBase[16] = mDataBase[19]; mDataBase[19] = aHold;
    aHold = mDataBase[17]; mDataBase[17] = mDataBase[18]; mDataBase[18] = aHold;

    aHold = mDataBase[24]; mDataBase[24] = mDataBase[27]; mDataBase[27] = aHold;
    aHold = mDataBase[25]; mDataBase[25] = mDataBase[26]; mDataBase[26] = aHold;
}

void TwistFastMatrix::FlipHorizontalQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[ 4]; mDataBase[ 4] = mDataBase[ 7]; mDataBase[ 7] = aHold;
    aHold = mDataBase[ 5]; mDataBase[ 5] = mDataBase[ 6]; mDataBase[ 6] = aHold;

    aHold = mDataBase[12]; mDataBase[12] = mDataBase[15]; mDataBase[15] = aHold;
    aHold = mDataBase[13]; mDataBase[13] = mDataBase[14]; mDataBase[14] = aHold;

    aHold = mDataBase[20]; mDataBase[20] = mDataBase[23]; mDataBase[23] = aHold;
    aHold = mDataBase[21]; mDataBase[21] = mDataBase[22]; mDataBase[22] = aHold;

    aHold = mDataBase[28]; mDataBase[28] = mDataBase[31]; mDataBase[31] = aHold;
    aHold = mDataBase[29]; mDataBase[29] = mDataBase[30]; mDataBase[30] = aHold;
}

void TwistFastMatrix::FlipHorizontalQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[32]; mDataBase[32] = mDataBase[35]; mDataBase[35] = aHold;
    aHold = mDataBase[33]; mDataBase[33] = mDataBase[34]; mDataBase[34] = aHold;

    aHold = mDataBase[40]; mDataBase[40] = mDataBase[43]; mDataBase[43] = aHold;
    aHold = mDataBase[41]; mDataBase[41] = mDataBase[42]; mDataBase[42] = aHold;

    aHold = mDataBase[48]; mDataBase[48] = mDataBase[51]; mDataBase[51] = aHold;
    aHold = mDataBase[49]; mDataBase[49] = mDataBase[50]; mDataBase[50] = aHold;

    aHold = mDataBase[56]; mDataBase[56] = mDataBase[59]; mDataBase[59] = aHold;
    aHold = mDataBase[57]; mDataBase[57] = mDataBase[58]; mDataBase[58] = aHold;
}

void TwistFastMatrix::FlipHorizontalQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[36]; mDataBase[36] = mDataBase[39]; mDataBase[39] = aHold;
    aHold = mDataBase[37]; mDataBase[37] = mDataBase[38]; mDataBase[38] = aHold;

    aHold = mDataBase[44]; mDataBase[44] = mDataBase[47]; mDataBase[47] = aHold;
    aHold = mDataBase[45]; mDataBase[45] = mDataBase[46]; mDataBase[46] = aHold;

    aHold = mDataBase[52]; mDataBase[52] = mDataBase[55]; mDataBase[55] = aHold;
    aHold = mDataBase[53]; mDataBase[53] = mDataBase[54]; mDataBase[54] = aHold;

    aHold = mDataBase[60]; mDataBase[60] = mDataBase[63]; mDataBase[63] = aHold;
    aHold = mDataBase[61]; mDataBase[61] = mDataBase[62]; mDataBase[62] = aHold;
}

void TwistFastMatrix::FlipHorizontalEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    FlipHorizontalQuarterA();
    FlipHorizontalQuarterB();
    FlipHorizontalQuarterC();
    FlipHorizontalQuarterD();
}

void TwistFastMatrix::FlipVerticalQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[ 0]; mDataBase[ 0] = mDataBase[24]; mDataBase[24] = aHold;
    aHold = mDataBase[ 1]; mDataBase[ 1] = mDataBase[25]; mDataBase[25] = aHold;
    aHold = mDataBase[ 2]; mDataBase[ 2] = mDataBase[26]; mDataBase[26] = aHold;
    aHold = mDataBase[ 3]; mDataBase[ 3] = mDataBase[27]; mDataBase[27] = aHold;

    aHold = mDataBase[ 8]; mDataBase[ 8] = mDataBase[16]; mDataBase[16] = aHold;
    aHold = mDataBase[ 9]; mDataBase[ 9] = mDataBase[17]; mDataBase[17] = aHold;
    aHold = mDataBase[10]; mDataBase[10] = mDataBase[18]; mDataBase[18] = aHold;
    aHold = mDataBase[11]; mDataBase[11] = mDataBase[19]; mDataBase[19] = aHold;
}

void TwistFastMatrix::FlipVerticalQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[ 4]; mDataBase[ 4] = mDataBase[28]; mDataBase[28] = aHold;
    aHold = mDataBase[ 5]; mDataBase[ 5] = mDataBase[29]; mDataBase[29] = aHold;
    aHold = mDataBase[ 6]; mDataBase[ 6] = mDataBase[30]; mDataBase[30] = aHold;
    aHold = mDataBase[ 7]; mDataBase[ 7] = mDataBase[31]; mDataBase[31] = aHold;

    aHold = mDataBase[12]; mDataBase[12] = mDataBase[20]; mDataBase[20] = aHold;
    aHold = mDataBase[13]; mDataBase[13] = mDataBase[21]; mDataBase[21] = aHold;
    aHold = mDataBase[14]; mDataBase[14] = mDataBase[22]; mDataBase[22] = aHold;
    aHold = mDataBase[15]; mDataBase[15] = mDataBase[23]; mDataBase[23] = aHold;
}

void TwistFastMatrix::FlipVerticalQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[32]; mDataBase[32] = mDataBase[56]; mDataBase[56] = aHold;
    aHold = mDataBase[33]; mDataBase[33] = mDataBase[57]; mDataBase[57] = aHold;
    aHold = mDataBase[34]; mDataBase[34] = mDataBase[58]; mDataBase[58] = aHold;
    aHold = mDataBase[35]; mDataBase[35] = mDataBase[59]; mDataBase[59] = aHold;

    aHold = mDataBase[40]; mDataBase[40] = mDataBase[48]; mDataBase[48] = aHold;
    aHold = mDataBase[41]; mDataBase[41] = mDataBase[49]; mDataBase[49] = aHold;
    aHold = mDataBase[42]; mDataBase[42] = mDataBase[50]; mDataBase[50] = aHold;
    aHold = mDataBase[43]; mDataBase[43] = mDataBase[51]; mDataBase[51] = aHold;
}

void TwistFastMatrix::FlipVerticalQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[36]; mDataBase[36] = mDataBase[60]; mDataBase[60] = aHold;
    aHold = mDataBase[37]; mDataBase[37] = mDataBase[61]; mDataBase[61] = aHold;
    aHold = mDataBase[38]; mDataBase[38] = mDataBase[62]; mDataBase[62] = aHold;
    aHold = mDataBase[39]; mDataBase[39] = mDataBase[63]; mDataBase[63] = aHold;

    aHold = mDataBase[44]; mDataBase[44] = mDataBase[52]; mDataBase[52] = aHold;
    aHold = mDataBase[45]; mDataBase[45] = mDataBase[53]; mDataBase[53] = aHold;
    aHold = mDataBase[46]; mDataBase[46] = mDataBase[54]; mDataBase[54] = aHold;
    aHold = mDataBase[47]; mDataBase[47] = mDataBase[55]; mDataBase[55] = aHold;
}

void TwistFastMatrix::FlipVerticalEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    FlipVerticalQuarterA();
    FlipVerticalQuarterB();
    FlipVerticalQuarterC();
    FlipVerticalQuarterD();
    
}

void TwistFastMatrix::FlipHorizontalBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    memcpy(aTmp, aSrc, 64);

    // A <- B
    aSrc[ 0] = aTmp[ 4]; aSrc[ 1] = aTmp[ 5]; aSrc[ 2] = aTmp[ 6]; aSrc[ 3] = aTmp[ 7];
    aSrc[ 8] = aTmp[12]; aSrc[ 9] = aTmp[13]; aSrc[10] = aTmp[14]; aSrc[11] = aTmp[15];
    aSrc[16] = aTmp[20]; aSrc[17] = aTmp[21]; aSrc[18] = aTmp[22]; aSrc[19] = aTmp[23];
    aSrc[24] = aTmp[28]; aSrc[25] = aTmp[29]; aSrc[26] = aTmp[30]; aSrc[27] = aTmp[31];

    // B <- A
    aSrc[ 4] = aTmp[ 0]; aSrc[ 5] = aTmp[ 1]; aSrc[ 6] = aTmp[ 2]; aSrc[ 7] = aTmp[ 3];
    aSrc[12] = aTmp[ 8]; aSrc[13] = aTmp[ 9]; aSrc[14] = aTmp[10]; aSrc[15] = aTmp[11];
    aSrc[20] = aTmp[16]; aSrc[21] = aTmp[17]; aSrc[22] = aTmp[18]; aSrc[23] = aTmp[19];
    aSrc[28] = aTmp[24]; aSrc[29] = aTmp[25]; aSrc[30] = aTmp[26]; aSrc[31] = aTmp[27];

    // C <- D
    aSrc[32] = aTmp[36]; aSrc[33] = aTmp[37]; aSrc[34] = aTmp[38]; aSrc[35] = aTmp[39];
    aSrc[40] = aTmp[44]; aSrc[41] = aTmp[45]; aSrc[42] = aTmp[46]; aSrc[43] = aTmp[47];
    aSrc[48] = aTmp[52]; aSrc[49] = aTmp[53]; aSrc[50] = aTmp[54]; aSrc[51] = aTmp[55];
    aSrc[56] = aTmp[60]; aSrc[57] = aTmp[61]; aSrc[58] = aTmp[62]; aSrc[59] = aTmp[63];

    // D <- C
    aSrc[36] = aTmp[32]; aSrc[37] = aTmp[33]; aSrc[38] = aTmp[34]; aSrc[39] = aTmp[35];
    aSrc[44] = aTmp[40]; aSrc[45] = aTmp[41]; aSrc[46] = aTmp[42]; aSrc[47] = aTmp[43];
    aSrc[52] = aTmp[48]; aSrc[53] = aTmp[49]; aSrc[54] = aTmp[50]; aSrc[55] = aTmp[51];
    aSrc[60] = aTmp[56]; aSrc[61] = aTmp[57]; aSrc[62] = aTmp[58]; aSrc[63] = aTmp[59];
}

void TwistFastMatrix::FlipVerticalBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    memcpy(aTmp, aSrc, 64);

    // A <- C
    aSrc[ 0] = aTmp[32]; aSrc[ 1] = aTmp[33]; aSrc[ 2] = aTmp[34]; aSrc[ 3] = aTmp[35];
    aSrc[ 8] = aTmp[40]; aSrc[ 9] = aTmp[41]; aSrc[10] = aTmp[42]; aSrc[11] = aTmp[43];
    aSrc[16] = aTmp[48]; aSrc[17] = aTmp[49]; aSrc[18] = aTmp[50]; aSrc[19] = aTmp[51];
    aSrc[24] = aTmp[56]; aSrc[25] = aTmp[57]; aSrc[26] = aTmp[58]; aSrc[27] = aTmp[59];

    // B <- D
    aSrc[ 4] = aTmp[36]; aSrc[ 5] = aTmp[37]; aSrc[ 6] = aTmp[38]; aSrc[ 7] = aTmp[39];
    aSrc[12] = aTmp[44]; aSrc[13] = aTmp[45]; aSrc[14] = aTmp[46]; aSrc[15] = aTmp[47];
    aSrc[20] = aTmp[52]; aSrc[21] = aTmp[53]; aSrc[22] = aTmp[54]; aSrc[23] = aTmp[55];
    aSrc[28] = aTmp[60]; aSrc[29] = aTmp[61]; aSrc[30] = aTmp[62]; aSrc[31] = aTmp[63];

    // C <- A
    aSrc[32] = aTmp[ 0]; aSrc[33] = aTmp[ 1]; aSrc[34] = aTmp[ 2]; aSrc[35] = aTmp[ 3];
    aSrc[40] = aTmp[ 8]; aSrc[41] = aTmp[ 9]; aSrc[42] = aTmp[10]; aSrc[43] = aTmp[11];
    aSrc[48] = aTmp[16]; aSrc[49] = aTmp[17]; aSrc[50] = aTmp[18]; aSrc[51] = aTmp[19];
    aSrc[56] = aTmp[24]; aSrc[57] = aTmp[25]; aSrc[58] = aTmp[26]; aSrc[59] = aTmp[27];

    // D <- B
    aSrc[36] = aTmp[ 4]; aSrc[37] = aTmp[ 5]; aSrc[38] = aTmp[ 6]; aSrc[39] = aTmp[ 7];
    aSrc[44] = aTmp[12]; aSrc[45] = aTmp[13]; aSrc[46] = aTmp[14]; aSrc[47] = aTmp[15];
    aSrc[52] = aTmp[20]; aSrc[53] = aTmp[21]; aSrc[54] = aTmp[22]; aSrc[55] = aTmp[23];
    aSrc[60] = aTmp[28]; aSrc[61] = aTmp[29]; aSrc[62] = aTmp[30]; aSrc[63] = aTmp[31];
}

void TwistFastMatrix::TransposeMainDiagonalBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    memcpy(aTmp, aSrc, 64);

    // B <- C
    aSrc[ 4] = aTmp[32]; aSrc[ 5] = aTmp[33]; aSrc[ 6] = aTmp[34]; aSrc[ 7] = aTmp[35];
    aSrc[12] = aTmp[40]; aSrc[13] = aTmp[41]; aSrc[14] = aTmp[42]; aSrc[15] = aTmp[43];
    aSrc[20] = aTmp[48]; aSrc[21] = aTmp[49]; aSrc[22] = aTmp[50]; aSrc[23] = aTmp[51];
    aSrc[28] = aTmp[56]; aSrc[29] = aTmp[57]; aSrc[30] = aTmp[58]; aSrc[31] = aTmp[59];

    // C <- B
    aSrc[32] = aTmp[ 4]; aSrc[33] = aTmp[ 5]; aSrc[34] = aTmp[ 6]; aSrc[35] = aTmp[ 7];
    aSrc[40] = aTmp[12]; aSrc[41] = aTmp[13]; aSrc[42] = aTmp[14]; aSrc[43] = aTmp[15];
    aSrc[48] = aTmp[20]; aSrc[49] = aTmp[21]; aSrc[50] = aTmp[22]; aSrc[51] = aTmp[23];
    aSrc[56] = aTmp[28]; aSrc[57] = aTmp[29]; aSrc[58] = aTmp[30]; aSrc[59] = aTmp[31];

    // A and D unchanged
}

void TwistFastMatrix::TransposeAntiDiagonalBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    memcpy(aTmp, aSrc, 64);

    // A <- D
    aSrc[ 0] = aTmp[36]; aSrc[ 1] = aTmp[37]; aSrc[ 2] = aTmp[38]; aSrc[ 3] = aTmp[39];
    aSrc[ 8] = aTmp[44]; aSrc[ 9] = aTmp[45]; aSrc[10] = aTmp[46]; aSrc[11] = aTmp[47];
    aSrc[16] = aTmp[52]; aSrc[17] = aTmp[53]; aSrc[18] = aTmp[54]; aSrc[19] = aTmp[55];
    aSrc[24] = aTmp[60]; aSrc[25] = aTmp[61]; aSrc[26] = aTmp[62]; aSrc[27] = aTmp[63];

    // D <- A
    aSrc[36] = aTmp[ 0]; aSrc[37] = aTmp[ 1]; aSrc[38] = aTmp[ 2]; aSrc[39] = aTmp[ 3];
    aSrc[44] = aTmp[ 8]; aSrc[45] = aTmp[ 9]; aSrc[46] = aTmp[10]; aSrc[47] = aTmp[11];
    aSrc[52] = aTmp[16]; aSrc[53] = aTmp[17]; aSrc[54] = aTmp[18]; aSrc[55] = aTmp[19];
    aSrc[60] = aTmp[24]; aSrc[61] = aTmp[25]; aSrc[62] = aTmp[26]; aSrc[63] = aTmp[27];

    // B and C unchanged
}

void TwistFastMatrix::RotateRightEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // --- block (0,0) ---
    aHold = mDataBase[ 0];
    mDataBase[ 0] = mDataBase[ 8];
    mDataBase[ 8] = mDataBase[ 9];
    mDataBase[ 9] = mDataBase[ 1];
    mDataBase[ 1] = aHold;

    // --- block (0,2) ---
    aHold = mDataBase[ 2];
    mDataBase[ 2] = mDataBase[10];
    mDataBase[10] = mDataBase[11];
    mDataBase[11] = mDataBase[ 3];
    mDataBase[ 3] = aHold;

    // --- block (2,0) ---
    aHold = mDataBase[16];
    mDataBase[16] = mDataBase[24];
    mDataBase[24] = mDataBase[25];
    mDataBase[25] = mDataBase[17];
    mDataBase[17] = aHold;

    // --- block (2,2) ---
    aHold = mDataBase[18];
    mDataBase[18] = mDataBase[26];
    mDataBase[26] = mDataBase[27];
    mDataBase[27] = mDataBase[19];
    mDataBase[19] = aHold;
}

void TwistFastMatrix::RotateRightEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[ 4];
    mDataBase[ 4] = mDataBase[12];
    mDataBase[12] = mDataBase[13];
    mDataBase[13] = mDataBase[ 5];
    mDataBase[ 5] = aHold;

    // (0,2)
    aHold = mDataBase[ 6];
    mDataBase[ 6] = mDataBase[14];
    mDataBase[14] = mDataBase[15];
    mDataBase[15] = mDataBase[ 7];
    mDataBase[ 7] = aHold;

    // (2,0)
    aHold = mDataBase[20];
    mDataBase[20] = mDataBase[28];
    mDataBase[28] = mDataBase[29];
    mDataBase[29] = mDataBase[21];
    mDataBase[21] = aHold;

    // (2,2)
    aHold = mDataBase[22];
    mDataBase[22] = mDataBase[30];
    mDataBase[30] = mDataBase[31];
    mDataBase[31] = mDataBase[23];
    mDataBase[23] = aHold;
}

void TwistFastMatrix::RotateRightEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[32];
    mDataBase[32] = mDataBase[40];
    mDataBase[40] = mDataBase[41];
    mDataBase[41] = mDataBase[33];
    mDataBase[33] = aHold;

    // (0,2)
    aHold = mDataBase[34];
    mDataBase[34] = mDataBase[42];
    mDataBase[42] = mDataBase[43];
    mDataBase[43] = mDataBase[35];
    mDataBase[35] = aHold;

    // (2,0)
    aHold = mDataBase[48];
    mDataBase[48] = mDataBase[56];
    mDataBase[56] = mDataBase[57];
    mDataBase[57] = mDataBase[49];
    mDataBase[49] = aHold;

    // (2,2)
    aHold = mDataBase[50];
    mDataBase[50] = mDataBase[58];
    mDataBase[58] = mDataBase[59];
    mDataBase[59] = mDataBase[51];
    mDataBase[51] = aHold;
}

void TwistFastMatrix::RotateRightEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[36];
    mDataBase[36] = mDataBase[44];
    mDataBase[44] = mDataBase[45];
    mDataBase[45] = mDataBase[37];
    mDataBase[37] = aHold;

    // (0,2)
    aHold = mDataBase[38];
    mDataBase[38] = mDataBase[46];
    mDataBase[46] = mDataBase[47];
    mDataBase[47] = mDataBase[39];
    mDataBase[39] = aHold;

    // (2,0)
    aHold = mDataBase[52];
    mDataBase[52] = mDataBase[60];
    mDataBase[60] = mDataBase[61];
    mDataBase[61] = mDataBase[53];
    mDataBase[53] = aHold;

    // (2,2)
    aHold = mDataBase[54];
    mDataBase[54] = mDataBase[62];
    mDataBase[62] = mDataBase[63];
    mDataBase[63] = mDataBase[55];
    mDataBase[55] = aHold;
}

void TwistFastMatrix::RotateRightEachSixteenthEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    RotateRightEachSixteenthQuarterA();
    RotateRightEachSixteenthQuarterB();
    RotateRightEachSixteenthQuarterC();
    RotateRightEachSixteenthQuarterD();
}

void TwistFastMatrix::RotateLeftEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[0];
    mDataBase[0] = mDataBase[1];
    mDataBase[1] = mDataBase[9];
    mDataBase[9] = mDataBase[8];
    mDataBase[8] = aHold;

    aHold = mDataBase[2];
    mDataBase[2] = mDataBase[3];
    mDataBase[3] = mDataBase[11];
    mDataBase[11] = mDataBase[10];
    mDataBase[10] = aHold;

    aHold = mDataBase[16];
    mDataBase[16] = mDataBase[17];
    mDataBase[17] = mDataBase[25];
    mDataBase[25] = mDataBase[24];
    mDataBase[24] = aHold;

    aHold = mDataBase[18];
    mDataBase[18] = mDataBase[19];
    mDataBase[19] = mDataBase[27];
    mDataBase[27] = mDataBase[26];
    mDataBase[26] = aHold;
}

void TwistFastMatrix::RotateLeftEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[4];
    mDataBase[4] = mDataBase[5];
    mDataBase[5] = mDataBase[13];
    mDataBase[13] = mDataBase[12];
    mDataBase[12] = aHold;

    aHold = mDataBase[6];
    mDataBase[6] = mDataBase[7];
    mDataBase[7] = mDataBase[15];
    mDataBase[15] = mDataBase[14];
    mDataBase[14] = aHold;

    aHold = mDataBase[20];
    mDataBase[20] = mDataBase[21];
    mDataBase[21] = mDataBase[29];
    mDataBase[29] = mDataBase[28];
    mDataBase[28] = aHold;

    aHold = mDataBase[22];
    mDataBase[22] = mDataBase[23];
    mDataBase[23] = mDataBase[31];
    mDataBase[31] = mDataBase[30];
    mDataBase[30] = aHold;
}

void TwistFastMatrix::RotateLeftEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[32];
    mDataBase[32] = mDataBase[33];
    mDataBase[33] = mDataBase[41];
    mDataBase[41] = mDataBase[40];
    mDataBase[40] = aHold;

    aHold = mDataBase[34];
    mDataBase[34] = mDataBase[35];
    mDataBase[35] = mDataBase[43];
    mDataBase[43] = mDataBase[42];
    mDataBase[42] = aHold;

    aHold = mDataBase[48];
    mDataBase[48] = mDataBase[49];
    mDataBase[49] = mDataBase[57];
    mDataBase[57] = mDataBase[56];
    mDataBase[56] = aHold;

    aHold = mDataBase[50];
    mDataBase[50] = mDataBase[51];
    mDataBase[51] = mDataBase[59];
    mDataBase[59] = mDataBase[58];
    mDataBase[58] = aHold;
}

void TwistFastMatrix::RotateLeftEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[36];
    mDataBase[36] = mDataBase[37];
    mDataBase[37] = mDataBase[45];
    mDataBase[45] = mDataBase[44];
    mDataBase[44] = aHold;

    aHold = mDataBase[38];
    mDataBase[38] = mDataBase[39];
    mDataBase[39] = mDataBase[47];
    mDataBase[47] = mDataBase[46];
    mDataBase[46] = aHold;

    aHold = mDataBase[52];
    mDataBase[52] = mDataBase[53];
    mDataBase[53] = mDataBase[61];
    mDataBase[61] = mDataBase[60];
    mDataBase[60] = aHold;

    aHold = mDataBase[54];
    mDataBase[54] = mDataBase[55];
    mDataBase[55] = mDataBase[63];
    mDataBase[63] = mDataBase[62];
    mDataBase[62] = aHold;
}

void TwistFastMatrix::RotateLeftEachSixteenthEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    RotateLeftEachSixteenthQuarterA();
    RotateLeftEachSixteenthQuarterB();
    RotateLeftEachSixteenthQuarterC();
    RotateLeftEachSixteenthQuarterD();
}


void TwistFastMatrix::FlipHorizontalEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mDataBase[0];  mDataBase[0] = mDataBase[1];  mDataBase[1] = aHold;
    aHold = mDataBase[8];  mDataBase[8] = mDataBase[9];  mDataBase[9] = aHold;

    // block (0,2)
    aHold = mDataBase[2];  mDataBase[2] = mDataBase[3];  mDataBase[3] = aHold;
    aHold = mDataBase[10]; mDataBase[10] = mDataBase[11]; mDataBase[11] = aHold;

    // block (2,0)
    aHold = mDataBase[16]; mDataBase[16] = mDataBase[17]; mDataBase[17] = aHold;
    aHold = mDataBase[24]; mDataBase[24] = mDataBase[25]; mDataBase[25] = aHold;

    // block (2,2)
    aHold = mDataBase[18]; mDataBase[18] = mDataBase[19]; mDataBase[19] = aHold;
    aHold = mDataBase[26]; mDataBase[26] = mDataBase[27]; mDataBase[27] = aHold;
}

void TwistFastMatrix::FlipHorizontalEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mDataBase[4];  mDataBase[4] = mDataBase[5];  mDataBase[5] = aHold;
    aHold = mDataBase[12]; mDataBase[12] = mDataBase[13]; mDataBase[13] = aHold;

    // block (0,2)
    aHold = mDataBase[6];  mDataBase[6] = mDataBase[7];  mDataBase[7] = aHold;
    aHold = mDataBase[14]; mDataBase[14] = mDataBase[15]; mDataBase[15] = aHold;

    // block (2,0)
    aHold = mDataBase[20]; mDataBase[20] = mDataBase[21]; mDataBase[21] = aHold;
    aHold = mDataBase[28]; mDataBase[28] = mDataBase[29]; mDataBase[29] = aHold;

    // block (2,2)
    aHold = mDataBase[22]; mDataBase[22] = mDataBase[23]; mDataBase[23] = aHold;
    aHold = mDataBase[30]; mDataBase[30] = mDataBase[31]; mDataBase[31] = aHold;
}

void TwistFastMatrix::FlipHorizontalEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mDataBase[32]; mDataBase[32] = mDataBase[33]; mDataBase[33] = aHold;
    aHold = mDataBase[40]; mDataBase[40] = mDataBase[41]; mDataBase[41] = aHold;

    // block (0,2)
    aHold = mDataBase[34]; mDataBase[34] = mDataBase[35]; mDataBase[35] = aHold;
    aHold = mDataBase[42]; mDataBase[42] = mDataBase[43]; mDataBase[43] = aHold;

    // block (2,0)
    aHold = mDataBase[48]; mDataBase[48] = mDataBase[49]; mDataBase[49] = aHold;
    aHold = mDataBase[56]; mDataBase[56] = mDataBase[57]; mDataBase[57] = aHold;

    // block (2,2)
    aHold = mDataBase[50]; mDataBase[50] = mDataBase[51]; mDataBase[51] = aHold;
    aHold = mDataBase[58]; mDataBase[58] = mDataBase[59]; mDataBase[59] = aHold;
}

void TwistFastMatrix::FlipHorizontalEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mDataBase[36]; mDataBase[36] = mDataBase[37]; mDataBase[37] = aHold;
    aHold = mDataBase[44]; mDataBase[44] = mDataBase[45]; mDataBase[45] = aHold;

    // block (0,2)
    aHold = mDataBase[38]; mDataBase[38] = mDataBase[39]; mDataBase[39] = aHold;
    aHold = mDataBase[46]; mDataBase[46] = mDataBase[47]; mDataBase[47] = aHold;

    // block (2,0)
    aHold = mDataBase[52]; mDataBase[52] = mDataBase[53]; mDataBase[53] = aHold;
    aHold = mDataBase[60]; mDataBase[60] = mDataBase[61]; mDataBase[61] = aHold;

    // block (2,2)
    aHold = mDataBase[54]; mDataBase[54] = mDataBase[55]; mDataBase[55] = aHold;
    aHold = mDataBase[62]; mDataBase[62] = mDataBase[63]; mDataBase[63] = aHold;
}

void TwistFastMatrix::FlipHorizontalEachSixteenthEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    FlipHorizontalEachSixteenthQuarterA();
    FlipHorizontalEachSixteenthQuarterB();
    FlipHorizontalEachSixteenthQuarterC();
    FlipHorizontalEachSixteenthQuarterD();
}

void TwistFastMatrix::FlipVerticalEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mDataBase[0];  mDataBase[0] = mDataBase[8];  mDataBase[8] = aHold;
    aHold = mDataBase[1];  mDataBase[1] = mDataBase[9];  mDataBase[9] = aHold;

    // block (0,2)
    aHold = mDataBase[2];  mDataBase[2] = mDataBase[10]; mDataBase[10] = aHold;
    aHold = mDataBase[3];  mDataBase[3] = mDataBase[11]; mDataBase[11] = aHold;

    // block (2,0)
    aHold = mDataBase[16]; mDataBase[16] = mDataBase[24]; mDataBase[24] = aHold;
    aHold = mDataBase[17]; mDataBase[17] = mDataBase[25]; mDataBase[25] = aHold;

    // block (2,2)
    aHold = mDataBase[18]; mDataBase[18] = mDataBase[26]; mDataBase[26] = aHold;
    aHold = mDataBase[19]; mDataBase[19] = mDataBase[27]; mDataBase[27] = aHold;
}

void TwistFastMatrix::FlipVerticalEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mDataBase[4];  mDataBase[4] = mDataBase[12]; mDataBase[12] = aHold;
    aHold = mDataBase[5];  mDataBase[5] = mDataBase[13]; mDataBase[13] = aHold;

    // block (0,2)
    aHold = mDataBase[6];  mDataBase[6] = mDataBase[14]; mDataBase[14] = aHold;
    aHold = mDataBase[7];  mDataBase[7] = mDataBase[15]; mDataBase[15] = aHold;

    // block (2,0)
    aHold = mDataBase[20]; mDataBase[20] = mDataBase[28]; mDataBase[28] = aHold;
    aHold = mDataBase[21]; mDataBase[21] = mDataBase[29]; mDataBase[29] = aHold;

    // block (2,2)
    aHold = mDataBase[22]; mDataBase[22] = mDataBase[30]; mDataBase[30] = aHold;
    aHold = mDataBase[23]; mDataBase[23] = mDataBase[31]; mDataBase[31] = aHold;
}

void TwistFastMatrix::FlipVerticalEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mDataBase[32]; mDataBase[32] = mDataBase[40]; mDataBase[40] = aHold;
    aHold = mDataBase[33]; mDataBase[33] = mDataBase[41]; mDataBase[41] = aHold;

    // block (0,2)
    aHold = mDataBase[34]; mDataBase[34] = mDataBase[42]; mDataBase[42] = aHold;
    aHold = mDataBase[35]; mDataBase[35] = mDataBase[43]; mDataBase[43] = aHold;

    // block (2,0)
    aHold = mDataBase[48]; mDataBase[48] = mDataBase[56]; mDataBase[56] = aHold;
    aHold = mDataBase[49]; mDataBase[49] = mDataBase[57]; mDataBase[57] = aHold;

    // block (2,2)
    aHold = mDataBase[50]; mDataBase[50] = mDataBase[58]; mDataBase[58] = aHold;
    aHold = mDataBase[51]; mDataBase[51] = mDataBase[59]; mDataBase[59] = aHold;
}

void TwistFastMatrix::FlipVerticalEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mDataBase[36]; mDataBase[36] = mDataBase[44]; mDataBase[44] = aHold;
    aHold = mDataBase[37]; mDataBase[37] = mDataBase[45]; mDataBase[45] = aHold;

    // block (0,2)
    aHold = mDataBase[38]; mDataBase[38] = mDataBase[46]; mDataBase[46] = aHold;
    aHold = mDataBase[39]; mDataBase[39] = mDataBase[47]; mDataBase[47] = aHold;

    // block (2,0)
    aHold = mDataBase[52]; mDataBase[52] = mDataBase[60]; mDataBase[60] = aHold;
    aHold = mDataBase[53]; mDataBase[53] = mDataBase[61]; mDataBase[61] = aHold;

    // block (2,2)
    aHold = mDataBase[54]; mDataBase[54] = mDataBase[62]; mDataBase[62] = aHold;
    aHold = mDataBase[55]; mDataBase[55] = mDataBase[63]; mDataBase[63] = aHold;
}

void TwistFastMatrix::FlipVerticalEachSixteenthEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    FlipVerticalEachSixteenthQuarterA();
    FlipVerticalEachSixteenthQuarterB();
    FlipVerticalEachSixteenthQuarterC();
    FlipVerticalEachSixteenthQuarterD();
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[1];  mDataBase[1] = mDataBase[8];  mDataBase[8] = aHold;
    aHold = mDataBase[3];  mDataBase[3] = mDataBase[10]; mDataBase[10] = aHold;
    aHold = mDataBase[17]; mDataBase[17] = mDataBase[24]; mDataBase[24] = aHold;
    aHold = mDataBase[19]; mDataBase[19] = mDataBase[26]; mDataBase[26] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[5];  mDataBase[5] = mDataBase[12]; mDataBase[12] = aHold;
    aHold = mDataBase[7];  mDataBase[7] = mDataBase[14]; mDataBase[14] = aHold;
    aHold = mDataBase[21]; mDataBase[21] = mDataBase[28]; mDataBase[28] = aHold;
    aHold = mDataBase[23]; mDataBase[23] = mDataBase[30]; mDataBase[30] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[33]; mDataBase[33] = mDataBase[40]; mDataBase[40] = aHold;
    aHold = mDataBase[35]; mDataBase[35] = mDataBase[42]; mDataBase[42] = aHold;
    aHold = mDataBase[49]; mDataBase[49] = mDataBase[56]; mDataBase[56] = aHold;
    aHold = mDataBase[51]; mDataBase[51] = mDataBase[58]; mDataBase[58] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    TransposeMainDiagonalEachSixteenthQuarterA();
    TransposeMainDiagonalEachSixteenthQuarterB();
    TransposeMainDiagonalEachSixteenthQuarterC();
    TransposeMainDiagonalEachSixteenthQuarterD();
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[37]; mDataBase[37] = mDataBase[44]; mDataBase[44] = aHold;
    aHold = mDataBase[39]; mDataBase[39] = mDataBase[46]; mDataBase[46] = aHold;
    aHold = mDataBase[53]; mDataBase[53] = mDataBase[60]; mDataBase[60] = aHold;
    aHold = mDataBase[55]; mDataBase[55] = mDataBase[62]; mDataBase[62] = aHold;
}


void TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[0];  mDataBase[0] = mDataBase[9];  mDataBase[9] = aHold;
    aHold = mDataBase[2];  mDataBase[2] = mDataBase[11]; mDataBase[11] = aHold;
    aHold = mDataBase[16]; mDataBase[16] = mDataBase[25]; mDataBase[25] = aHold;
    aHold = mDataBase[18]; mDataBase[18] = mDataBase[27]; mDataBase[27] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[4];  mDataBase[4] = mDataBase[13]; mDataBase[13] = aHold;
    aHold = mDataBase[6];  mDataBase[6] = mDataBase[15]; mDataBase[15] = aHold;
    aHold = mDataBase[20]; mDataBase[20] = mDataBase[29]; mDataBase[29] = aHold;
    aHold = mDataBase[22]; mDataBase[22] = mDataBase[31]; mDataBase[31] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[32]; mDataBase[32] = mDataBase[41]; mDataBase[41] = aHold;
    aHold = mDataBase[34]; mDataBase[34] = mDataBase[43]; mDataBase[43] = aHold;
    aHold = mDataBase[48]; mDataBase[48] = mDataBase[57]; mDataBase[57] = aHold;
    aHold = mDataBase[50]; mDataBase[50] = mDataBase[59]; mDataBase[59] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mDataBase[36]; mDataBase[36] = mDataBase[45]; mDataBase[45] = aHold;
    aHold = mDataBase[38]; mDataBase[38] = mDataBase[47]; mDataBase[47] = aHold;
    aHold = mDataBase[52]; mDataBase[52] = mDataBase[61]; mDataBase[61] = aHold;
    aHold = mDataBase[54]; mDataBase[54] = mDataBase[63]; mDataBase[63] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalEachSixteenthEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    TransposeAntiDiagonalEachSixteenthQuarterA();
    TransposeAntiDiagonalEachSixteenthQuarterB();
    TransposeAntiDiagonalEachSixteenthQuarterC();
    TransposeAntiDiagonalEachSixteenthQuarterD();
}

void TwistFastMatrix::RotateRightSixteenthsQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // --- position (0,0) within each 2x2 ---
    aHold = mDataBase[0];
    mDataBase[0]  = mDataBase[16];
    mDataBase[16] = mDataBase[18];
    mDataBase[18] = mDataBase[2];
    mDataBase[2]  = aHold;

    // --- position (0,1) ---
    aHold = mDataBase[1];
    mDataBase[1]  = mDataBase[17];
    mDataBase[17] = mDataBase[19];
    mDataBase[19] = mDataBase[3];
    mDataBase[3]  = aHold;

    // --- position (1,0) ---
    aHold = mDataBase[8];
    mDataBase[8]  = mDataBase[24];
    mDataBase[24] = mDataBase[26];
    mDataBase[26] = mDataBase[10];
    mDataBase[10] = aHold;

    // --- position (1,1) ---
    aHold = mDataBase[9];
    mDataBase[9]  = mDataBase[25];
    mDataBase[25] = mDataBase[27];
    mDataBase[27] = mDataBase[11];
    mDataBase[11] = aHold;
}

void TwistFastMatrix::RotateRightSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[4];
    mDataBase[4]  = mDataBase[20];
    mDataBase[20] = mDataBase[22];
    mDataBase[22] = mDataBase[6];
    mDataBase[6]  = aHold;

    // (0,1)
    aHold = mDataBase[5];
    mDataBase[5]  = mDataBase[21];
    mDataBase[21] = mDataBase[23];
    mDataBase[23] = mDataBase[7];
    mDataBase[7]  = aHold;

    // (1,0)
    aHold = mDataBase[12];
    mDataBase[12] = mDataBase[28];
    mDataBase[28] = mDataBase[30];
    mDataBase[30] = mDataBase[14];
    mDataBase[14] = aHold;

    // (1,1)
    aHold = mDataBase[13];
    mDataBase[13] = mDataBase[29];
    mDataBase[29] = mDataBase[31];
    mDataBase[31] = mDataBase[15];
    mDataBase[15] = aHold;
}

void TwistFastMatrix::RotateRightSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[32];
    mDataBase[32] = mDataBase[48];
    mDataBase[48] = mDataBase[50];
    mDataBase[50] = mDataBase[34];
    mDataBase[34] = aHold;

    // (0,1)
    aHold = mDataBase[33];
    mDataBase[33] = mDataBase[49];
    mDataBase[49] = mDataBase[51];
    mDataBase[51] = mDataBase[35];
    mDataBase[35] = aHold;

    // (1,0)
    aHold = mDataBase[40];
    mDataBase[40] = mDataBase[56];
    mDataBase[56] = mDataBase[58];
    mDataBase[58] = mDataBase[42];
    mDataBase[42] = aHold;

    // (1,1)
    aHold = mDataBase[41];
    mDataBase[41] = mDataBase[57];
    mDataBase[57] = mDataBase[59];
    mDataBase[59] = mDataBase[43];
    mDataBase[43] = aHold;
}

void TwistFastMatrix::RotateRightSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[36];
    mDataBase[36] = mDataBase[52];
    mDataBase[52] = mDataBase[54];
    mDataBase[54] = mDataBase[38];
    mDataBase[38] = aHold;

    // (0,1)
    aHold = mDataBase[37];
    mDataBase[37] = mDataBase[53];
    mDataBase[53] = mDataBase[55];
    mDataBase[55] = mDataBase[39];
    mDataBase[39] = aHold;

    // (1,0)
    aHold = mDataBase[44];
    mDataBase[44] = mDataBase[60];
    mDataBase[60] = mDataBase[62];
    mDataBase[62] = mDataBase[46];
    mDataBase[46] = aHold;

    // (1,1)
    aHold = mDataBase[45];
    mDataBase[45] = mDataBase[61];
    mDataBase[61] = mDataBase[63];
    mDataBase[63] = mDataBase[47];
    mDataBase[47] = aHold;
}

void TwistFastMatrix::RotateRightSixteenthsEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    RotateRightSixteenthsQuarterA();
    RotateRightSixteenthsQuarterB();
    RotateRightSixteenthsQuarterC();
    RotateRightSixteenthsQuarterD();
}

void TwistFastMatrix::RotateLeftSixteenthsQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[0];
    mDataBase[0]  = mDataBase[2];
    mDataBase[2]  = mDataBase[18];
    mDataBase[18] = mDataBase[16];
    mDataBase[16] = aHold;

    // (0,1)
    aHold = mDataBase[1];
    mDataBase[1]  = mDataBase[3];
    mDataBase[3]  = mDataBase[19];
    mDataBase[19] = mDataBase[17];
    mDataBase[17] = aHold;

    // (1,0)
    aHold = mDataBase[8];
    mDataBase[8]  = mDataBase[10];
    mDataBase[10] = mDataBase[26];
    mDataBase[26] = mDataBase[24];
    mDataBase[24] = aHold;

    // (1,1)
    aHold = mDataBase[9];
    mDataBase[9]  = mDataBase[11];
    mDataBase[11] = mDataBase[27];
    mDataBase[27] = mDataBase[25];
    mDataBase[25] = aHold;
}

void TwistFastMatrix::RotateLeftSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[4];
    mDataBase[4]  = mDataBase[6];
    mDataBase[6]  = mDataBase[22];
    mDataBase[22] = mDataBase[20];
    mDataBase[20] = aHold;

    // (0,1)
    aHold = mDataBase[5];
    mDataBase[5]  = mDataBase[7];
    mDataBase[7]  = mDataBase[23];
    mDataBase[23] = mDataBase[21];
    mDataBase[21] = aHold;

    // (1,0)
    aHold = mDataBase[12];
    mDataBase[12] = mDataBase[14];
    mDataBase[14] = mDataBase[30];
    mDataBase[30] = mDataBase[28];
    mDataBase[28] = aHold;

    // (1,1)
    aHold = mDataBase[13];
    mDataBase[13] = mDataBase[15];
    mDataBase[15] = mDataBase[31];
    mDataBase[31] = mDataBase[29];
    mDataBase[29] = aHold;
}

void TwistFastMatrix::RotateLeftSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[32];
    mDataBase[32] = mDataBase[34];
    mDataBase[34] = mDataBase[50];
    mDataBase[50] = mDataBase[48];
    mDataBase[48] = aHold;

    // (0,1)
    aHold = mDataBase[33];
    mDataBase[33] = mDataBase[35];
    mDataBase[35] = mDataBase[51];
    mDataBase[51] = mDataBase[49];
    mDataBase[49] = aHold;

    // (1,0)
    aHold = mDataBase[40];
    mDataBase[40] = mDataBase[42];
    mDataBase[42] = mDataBase[58];
    mDataBase[58] = mDataBase[56];
    mDataBase[56] = aHold;

    // (1,1)
    aHold = mDataBase[41];
    mDataBase[41] = mDataBase[43];
    mDataBase[43] = mDataBase[59];
    mDataBase[59] = mDataBase[57];
    mDataBase[57] = aHold;
}

void TwistFastMatrix::RotateLeftSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[36];
    mDataBase[36] = mDataBase[38];
    mDataBase[38] = mDataBase[54];
    mDataBase[54] = mDataBase[52];
    mDataBase[52] = aHold;

    // (0,1)
    aHold = mDataBase[37];
    mDataBase[37] = mDataBase[39];
    mDataBase[39] = mDataBase[55];
    mDataBase[55] = mDataBase[53];
    mDataBase[53] = aHold;

    // (1,0)
    aHold = mDataBase[44];
    mDataBase[44] = mDataBase[46];
    mDataBase[46] = mDataBase[62];
    mDataBase[62] = mDataBase[60];
    mDataBase[60] = aHold;

    // (1,1)
    aHold = mDataBase[45];
    mDataBase[45] = mDataBase[47];
    mDataBase[47] = mDataBase[63];
    mDataBase[63] = mDataBase[61];
    mDataBase[61] = aHold;
}

void TwistFastMatrix::RotateLeftSixteenthsEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    RotateLeftSixteenthsQuarterA();
    RotateLeftSixteenthsQuarterB();
    RotateLeftSixteenthsQuarterC();
    RotateLeftSixteenthsQuarterD();
}

void TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[2];
    mDataBase[2]  = mDataBase[16];
    mDataBase[16] = aHold;

    // (0,1)
    aHold = mDataBase[3];
    mDataBase[3]  = mDataBase[17];
    mDataBase[17] = aHold;

    // (1,0)
    aHold = mDataBase[10];
    mDataBase[10] = mDataBase[24];
    mDataBase[24] = aHold;

    // (1,1)
    aHold = mDataBase[11];
    mDataBase[11] = mDataBase[25];
    mDataBase[25] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[6];
    mDataBase[6]  = mDataBase[20];
    mDataBase[20] = aHold;

    // (0,1)
    aHold = mDataBase[7];
    mDataBase[7]  = mDataBase[21];
    mDataBase[21] = aHold;

    // (1,0)
    aHold = mDataBase[14];
    mDataBase[14] = mDataBase[28];
    mDataBase[28] = aHold;

    // (1,1)
    aHold = mDataBase[15];
    mDataBase[15] = mDataBase[29];
    mDataBase[29] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[34];
    mDataBase[34] = mDataBase[48];
    mDataBase[48] = aHold;

    // (0,1)
    aHold = mDataBase[35];
    mDataBase[35] = mDataBase[49];
    mDataBase[49] = aHold;

    // (1,0)
    aHold = mDataBase[42];
    mDataBase[42] = mDataBase[56];
    mDataBase[56] = aHold;

    // (1,1)
    aHold = mDataBase[43];
    mDataBase[43] = mDataBase[57];
    mDataBase[57] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[38];
    mDataBase[38] = mDataBase[52];
    mDataBase[52] = aHold;

    // (0,1)
    aHold = mDataBase[39];
    mDataBase[39] = mDataBase[53];
    mDataBase[53] = aHold;

    // (1,0)
    aHold = mDataBase[46];
    mDataBase[46] = mDataBase[60];
    mDataBase[60] = aHold;

    // (1,1)
    aHold = mDataBase[47];
    mDataBase[47] = mDataBase[61];
    mDataBase[61] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalSixteenthsEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    TransposeMainDiagonalSixteenthsQuarterA();
    TransposeMainDiagonalSixteenthsQuarterB();
    TransposeMainDiagonalSixteenthsQuarterC();
    TransposeMainDiagonalSixteenthsQuarterD();
}

void TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[0];
    mDataBase[0]  = mDataBase[18];
    mDataBase[18] = aHold;

    // (0,1)
    aHold = mDataBase[1];
    mDataBase[1]  = mDataBase[19];
    mDataBase[19] = aHold;

    // (1,0)
    aHold = mDataBase[8];
    mDataBase[8]  = mDataBase[26];
    mDataBase[26] = aHold;

    // (1,1)
    aHold = mDataBase[9];
    mDataBase[9]  = mDataBase[27];
    mDataBase[27] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[4];
    mDataBase[4]  = mDataBase[22];
    mDataBase[22] = aHold;

    // (0,1)
    aHold = mDataBase[5];
    mDataBase[5]  = mDataBase[23];
    mDataBase[23] = aHold;

    // (1,0)
    aHold = mDataBase[12];
    mDataBase[12] = mDataBase[30];
    mDataBase[30] = aHold;

    // (1,1)
    aHold = mDataBase[13];
    mDataBase[13] = mDataBase[31];
    mDataBase[31] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[32];
    mDataBase[32] = mDataBase[50];
    mDataBase[50] = aHold;

    // (0,1)
    aHold = mDataBase[33];
    mDataBase[33] = mDataBase[51];
    mDataBase[51] = aHold;

    // (1,0)
    aHold = mDataBase[40];
    mDataBase[40] = mDataBase[58];
    mDataBase[58] = aHold;

    // (1,1)
    aHold = mDataBase[41];
    mDataBase[41] = mDataBase[59];
    mDataBase[59] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mDataBase[36];
    mDataBase[36] = mDataBase[54];
    mDataBase[54] = aHold;

    // (0,1)
    aHold = mDataBase[37];
    mDataBase[37] = mDataBase[55];
    mDataBase[55] = aHold;

    // (1,0)
    aHold = mDataBase[44];
    mDataBase[44] = mDataBase[62];
    mDataBase[62] = aHold;

    // (1,1)
    aHold = mDataBase[45];
    mDataBase[45] = mDataBase[63];
    mDataBase[63] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalSixteenthsEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    TransposeAntiDiagonalSixteenthsQuarterA();
    TransposeAntiDiagonalSixteenthsQuarterB();
    TransposeAntiDiagonalSixteenthsQuarterC();
    TransposeAntiDiagonalSixteenthsQuarterD();
}

void TwistFastMatrix::FlipHorizontalSixteenthsQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ b
    aHold = mDataBase[0];  mDataBase[0] = mDataBase[2];  mDataBase[2] = aHold;
    aHold = mDataBase[1];  mDataBase[1] = mDataBase[3];  mDataBase[3] = aHold;
    aHold = mDataBase[8];  mDataBase[8] = mDataBase[10]; mDataBase[10] = aHold;
    aHold = mDataBase[9];  mDataBase[9] = mDataBase[11]; mDataBase[11] = aHold;

    // c ↔ d
    aHold = mDataBase[16]; mDataBase[16] = mDataBase[18]; mDataBase[18] = aHold;
    aHold = mDataBase[17]; mDataBase[17] = mDataBase[19]; mDataBase[19] = aHold;
    aHold = mDataBase[24]; mDataBase[24] = mDataBase[26]; mDataBase[26] = aHold;
    aHold = mDataBase[25]; mDataBase[25] = mDataBase[27]; mDataBase[27] = aHold;
}

void TwistFastMatrix::FlipHorizontalSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ b
    aHold = mDataBase[4];  mDataBase[4] = mDataBase[6];  mDataBase[6] = aHold;
    aHold = mDataBase[5];  mDataBase[5] = mDataBase[7];  mDataBase[7] = aHold;
    aHold = mDataBase[12]; mDataBase[12] = mDataBase[14]; mDataBase[14] = aHold;
    aHold = mDataBase[13]; mDataBase[13] = mDataBase[15]; mDataBase[15] = aHold;

    // c ↔ d
    aHold = mDataBase[20]; mDataBase[20] = mDataBase[22]; mDataBase[22] = aHold;
    aHold = mDataBase[21]; mDataBase[21] = mDataBase[23]; mDataBase[23] = aHold;
    aHold = mDataBase[28]; mDataBase[28] = mDataBase[30]; mDataBase[30] = aHold;
    aHold = mDataBase[29]; mDataBase[29] = mDataBase[31]; mDataBase[31] = aHold;
}

void TwistFastMatrix::FlipHorizontalSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ b
    aHold = mDataBase[32]; mDataBase[32] = mDataBase[34]; mDataBase[34] = aHold;
    aHold = mDataBase[33]; mDataBase[33] = mDataBase[35]; mDataBase[35] = aHold;
    aHold = mDataBase[40]; mDataBase[40] = mDataBase[42]; mDataBase[42] = aHold;
    aHold = mDataBase[41]; mDataBase[41] = mDataBase[43]; mDataBase[43] = aHold;

    // c ↔ d
    aHold = mDataBase[48]; mDataBase[48] = mDataBase[50]; mDataBase[50] = aHold;
    aHold = mDataBase[49]; mDataBase[49] = mDataBase[51]; mDataBase[51] = aHold;
    aHold = mDataBase[56]; mDataBase[56] = mDataBase[58]; mDataBase[58] = aHold;
    aHold = mDataBase[57]; mDataBase[57] = mDataBase[59]; mDataBase[59] = aHold;
}

void TwistFastMatrix::FlipHorizontalSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ b
    aHold = mDataBase[36]; mDataBase[36] = mDataBase[38]; mDataBase[38] = aHold;
    aHold = mDataBase[37]; mDataBase[37] = mDataBase[39]; mDataBase[39] = aHold;
    aHold = mDataBase[44]; mDataBase[44] = mDataBase[46]; mDataBase[46] = aHold;
    aHold = mDataBase[45]; mDataBase[45] = mDataBase[47]; mDataBase[47] = aHold;

    // c ↔ d
    aHold = mDataBase[52]; mDataBase[52] = mDataBase[54]; mDataBase[54] = aHold;
    aHold = mDataBase[53]; mDataBase[53] = mDataBase[55]; mDataBase[55] = aHold;
    aHold = mDataBase[60]; mDataBase[60] = mDataBase[62]; mDataBase[62] = aHold;
    aHold = mDataBase[61]; mDataBase[61] = mDataBase[63]; mDataBase[63] = aHold;
}

void TwistFastMatrix::FlipHorizontalSixteenthsEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    FlipHorizontalSixteenthsQuarterA();
    FlipHorizontalSixteenthsQuarterB();
    FlipHorizontalSixteenthsQuarterC();
    FlipHorizontalSixteenthsQuarterD();
}

void TwistFastMatrix::FlipVerticalSixteenthsQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ c
    aHold = mDataBase[0];  mDataBase[0] = mDataBase[16]; mDataBase[16] = aHold;
    aHold = mDataBase[1];  mDataBase[1] = mDataBase[17]; mDataBase[17] = aHold;
    aHold = mDataBase[8];  mDataBase[8] = mDataBase[24]; mDataBase[24] = aHold;
    aHold = mDataBase[9];  mDataBase[9] = mDataBase[25]; mDataBase[25] = aHold;

    // b ↔ d
    aHold = mDataBase[2];  mDataBase[2] = mDataBase[18]; mDataBase[18] = aHold;
    aHold = mDataBase[3];  mDataBase[3] = mDataBase[19]; mDataBase[19] = aHold;
    aHold = mDataBase[10]; mDataBase[10] = mDataBase[26]; mDataBase[26] = aHold;
    aHold = mDataBase[11]; mDataBase[11] = mDataBase[27]; mDataBase[27] = aHold;
}

void TwistFastMatrix::FlipVerticalSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ c
    aHold = mDataBase[4];  mDataBase[4] = mDataBase[20]; mDataBase[20] = aHold;
    aHold = mDataBase[5];  mDataBase[5] = mDataBase[21]; mDataBase[21] = aHold;
    aHold = mDataBase[12]; mDataBase[12] = mDataBase[28]; mDataBase[28] = aHold;
    aHold = mDataBase[13]; mDataBase[13] = mDataBase[29]; mDataBase[29] = aHold;

    // b ↔ d
    aHold = mDataBase[6];  mDataBase[6] = mDataBase[22]; mDataBase[22] = aHold;
    aHold = mDataBase[7];  mDataBase[7] = mDataBase[23]; mDataBase[23] = aHold;
    aHold = mDataBase[14]; mDataBase[14] = mDataBase[30]; mDataBase[30] = aHold;
    aHold = mDataBase[15]; mDataBase[15] = mDataBase[31]; mDataBase[31] = aHold;
}

void TwistFastMatrix::FlipVerticalSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ c
    aHold = mDataBase[32]; mDataBase[32] = mDataBase[48]; mDataBase[48] = aHold;
    aHold = mDataBase[33]; mDataBase[33] = mDataBase[49]; mDataBase[49] = aHold;
    aHold = mDataBase[40]; mDataBase[40] = mDataBase[56]; mDataBase[56] = aHold;
    aHold = mDataBase[41]; mDataBase[41] = mDataBase[57]; mDataBase[57] = aHold;

    // b ↔ d
    aHold = mDataBase[34]; mDataBase[34] = mDataBase[50]; mDataBase[50] = aHold;
    aHold = mDataBase[35]; mDataBase[35] = mDataBase[51]; mDataBase[51] = aHold;
    aHold = mDataBase[42]; mDataBase[42] = mDataBase[58]; mDataBase[58] = aHold;
    aHold = mDataBase[43]; mDataBase[43] = mDataBase[59]; mDataBase[59] = aHold;
}

void TwistFastMatrix::FlipVerticalSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ c
    aHold = mDataBase[36]; mDataBase[36] = mDataBase[52]; mDataBase[52] = aHold;
    aHold = mDataBase[37]; mDataBase[37] = mDataBase[53]; mDataBase[53] = aHold;
    aHold = mDataBase[44]; mDataBase[44] = mDataBase[60]; mDataBase[60] = aHold;
    aHold = mDataBase[45]; mDataBase[45] = mDataBase[61]; mDataBase[61] = aHold;

    // b ↔ d
    aHold = mDataBase[38]; mDataBase[38] = mDataBase[54]; mDataBase[54] = aHold;
    aHold = mDataBase[39]; mDataBase[39] = mDataBase[55]; mDataBase[55] = aHold;
    aHold = mDataBase[46]; mDataBase[46] = mDataBase[62]; mDataBase[62] = aHold;
    aHold = mDataBase[47]; mDataBase[47] = mDataBase[63]; mDataBase[63] = aHold;
}

void TwistFastMatrix::FlipVerticalSixteenthsEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    FlipVerticalSixteenthsQuarterA();
    FlipVerticalSixteenthsQuarterB();
    FlipVerticalSixteenthsQuarterC();
    FlipVerticalSixteenthsQuarterD();
}

void TwistFastMatrix::PinwheelRight(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {
    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aDst = mTemp;
    aDst[ 0] = aSrc[32]; aDst[ 1] = aSrc[24]; aDst[ 2] = aSrc[16]; aDst[ 3] = aSrc[ 8];
    aDst[ 4] = aSrc[ 0]; aDst[ 5] = aSrc[ 1]; aDst[ 6] = aSrc[ 2]; aDst[ 7] = aSrc[ 3];
    aDst[ 8] = aSrc[40]; aDst[ 9] = aSrc[12]; aDst[10] = aSrc[13]; aDst[11] = aSrc[14];
    aDst[12] = aSrc[22]; aDst[13] = aSrc[30]; aDst[14] = aSrc[38]; aDst[15] = aSrc[ 4];
    aDst[16] = aSrc[48]; aDst[17] = aSrc[11]; aDst[18] = aSrc[34]; aDst[19] = aSrc[26];
    aDst[20] = aSrc[18]; aDst[21] = aSrc[19]; aDst[22] = aSrc[46]; aDst[23] = aSrc[ 5];
    aDst[24] = aSrc[56]; aDst[25] = aSrc[10]; aDst[26] = aSrc[42]; aDst[27] = aSrc[28];
    aDst[28] = aSrc[36]; aDst[29] = aSrc[20]; aDst[30] = aSrc[54]; aDst[31] = aSrc[ 6];
    aDst[32] = aSrc[57]; aDst[33] = aSrc[ 9]; aDst[34] = aSrc[43]; aDst[35] = aSrc[27];
    aDst[36] = aSrc[35]; aDst[37] = aSrc[21]; aDst[38] = aSrc[53]; aDst[39] = aSrc[ 7];
    aDst[40] = aSrc[58]; aDst[41] = aSrc[17]; aDst[42] = aSrc[44]; aDst[43] = aSrc[45];
    aDst[44] = aSrc[37]; aDst[45] = aSrc[29]; aDst[46] = aSrc[52]; aDst[47] = aSrc[15];
    aDst[48] = aSrc[59]; aDst[49] = aSrc[25]; aDst[50] = aSrc[33]; aDst[51] = aSrc[41];
    aDst[52] = aSrc[49]; aDst[53] = aSrc[50]; aDst[54] = aSrc[51]; aDst[55] = aSrc[23];
    aDst[56] = aSrc[60]; aDst[57] = aSrc[61]; aDst[58] = aSrc[62]; aDst[59] = aSrc[63];
    aDst[60] = aSrc[55]; aDst[61] = aSrc[47]; aDst[62] = aSrc[39]; aDst[63] = aSrc[31];
    memcpy(mDataBase, mTemp, 64);
}

void TwistFastMatrix::PinwheelLeft(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {
    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aDst = mTemp;
    aDst[32] = aSrc[ 0]; aDst[24] = aSrc[ 1]; aDst[16] = aSrc[ 2]; aDst[ 8] = aSrc[ 3];
    aDst[ 0] = aSrc[ 4]; aDst[ 1] = aSrc[ 5]; aDst[ 2] = aSrc[ 6]; aDst[ 3] = aSrc[ 7];
    aDst[40] = aSrc[ 8]; aDst[12] = aSrc[ 9]; aDst[13] = aSrc[10]; aDst[14] = aSrc[11];
    aDst[22] = aSrc[12]; aDst[30] = aSrc[13]; aDst[38] = aSrc[14]; aDst[ 4] = aSrc[15];
    aDst[48] = aSrc[16]; aDst[11] = aSrc[17]; aDst[34] = aSrc[18]; aDst[26] = aSrc[19];
    aDst[18] = aSrc[20]; aDst[19] = aSrc[21]; aDst[46] = aSrc[22]; aDst[ 5] = aSrc[23];
    aDst[56] = aSrc[24]; aDst[10] = aSrc[25]; aDst[42] = aSrc[26]; aDst[28] = aSrc[27];
    aDst[36] = aSrc[28]; aDst[20] = aSrc[29]; aDst[54] = aSrc[30]; aDst[ 6] = aSrc[31];
    aDst[57] = aSrc[32]; aDst[ 9] = aSrc[33]; aDst[43] = aSrc[34]; aDst[27] = aSrc[35];
    aDst[35] = aSrc[36]; aDst[21] = aSrc[37]; aDst[53] = aSrc[38]; aDst[ 7] = aSrc[39];
    aDst[58] = aSrc[40]; aDst[17] = aSrc[41]; aDst[44] = aSrc[42]; aDst[45] = aSrc[43];
    aDst[37] = aSrc[44]; aDst[29] = aSrc[45]; aDst[52] = aSrc[46]; aDst[15] = aSrc[47];
    aDst[59] = aSrc[48]; aDst[25] = aSrc[49]; aDst[33] = aSrc[50]; aDst[41] = aSrc[51];
    aDst[49] = aSrc[52]; aDst[50] = aSrc[53]; aDst[51] = aSrc[54]; aDst[23] = aSrc[55];
    aDst[60] = aSrc[56]; aDst[61] = aSrc[57]; aDst[62] = aSrc[58]; aDst[63] = aSrc[59];
    aDst[55] = aSrc[60]; aDst[47] = aSrc[61]; aDst[39] = aSrc[62]; aDst[31] = aSrc[63];
    memcpy(mDataBase, mTemp, 64);
}

void TwistFastMatrix::PinwheelRightQuarterA(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 0] = aSrc[16]; aTmp[ 1] = aSrc[ 8]; aTmp[ 2] = aSrc[ 0]; aTmp[ 3] = aSrc[ 1];
    aTmp[ 8] = aSrc[24]; aTmp[ 9] = aSrc[10]; aTmp[10] = aSrc[18]; aTmp[11] = aSrc[ 2];
    aTmp[16] = aSrc[25]; aTmp[17] = aSrc[ 9]; aTmp[18] = aSrc[17]; aTmp[19] = aSrc[ 3];
    aTmp[24] = aSrc[26]; aTmp[25] = aSrc[27]; aTmp[26] = aSrc[19]; aTmp[27] = aSrc[11];

    aSrc[ 0] = aTmp[ 0]; aSrc[ 1] = aTmp[ 1]; aSrc[ 2] = aTmp[ 2]; aSrc[ 3] = aTmp[ 3];
    aSrc[ 8] = aTmp[ 8]; aSrc[ 9] = aTmp[ 9]; aSrc[10] = aTmp[10]; aSrc[11] = aTmp[11];
    aSrc[16] = aTmp[16]; aSrc[17] = aTmp[17]; aSrc[18] = aTmp[18]; aSrc[19] = aTmp[19];
    aSrc[24] = aTmp[24]; aSrc[25] = aTmp[25]; aSrc[26] = aTmp[26]; aSrc[27] = aTmp[27];
}

void TwistFastMatrix::PinwheelRightQuarterB(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 4] = aSrc[20]; aTmp[ 5] = aSrc[12]; aTmp[ 6] = aSrc[ 4]; aTmp[ 7] = aSrc[ 5];
    aTmp[12] = aSrc[28]; aTmp[13] = aSrc[14]; aTmp[14] = aSrc[22]; aTmp[15] = aSrc[ 6];
    aTmp[20] = aSrc[29]; aTmp[21] = aSrc[13]; aTmp[22] = aSrc[21]; aTmp[23] = aSrc[ 7];
    aTmp[28] = aSrc[30]; aTmp[29] = aSrc[31]; aTmp[30] = aSrc[23]; aTmp[31] = aSrc[15];

    aSrc[ 4] = aTmp[ 4]; aSrc[ 5] = aTmp[ 5]; aSrc[ 6] = aTmp[ 6]; aSrc[ 7] = aTmp[ 7];
    aSrc[12] = aTmp[12]; aSrc[13] = aTmp[13]; aSrc[14] = aTmp[14]; aSrc[15] = aTmp[15];
    aSrc[20] = aTmp[20]; aSrc[21] = aTmp[21]; aSrc[22] = aTmp[22]; aSrc[23] = aTmp[23];
    aSrc[28] = aTmp[28]; aSrc[29] = aTmp[29]; aSrc[30] = aTmp[30]; aSrc[31] = aTmp[31];
}

void TwistFastMatrix::PinwheelRightQuarterC(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[32] = aSrc[48]; aTmp[33] = aSrc[40]; aTmp[34] = aSrc[32]; aTmp[35] = aSrc[33];
    aTmp[40] = aSrc[56]; aTmp[41] = aSrc[42]; aTmp[42] = aSrc[50]; aTmp[43] = aSrc[34];
    aTmp[48] = aSrc[57]; aTmp[49] = aSrc[41]; aTmp[50] = aSrc[49]; aTmp[51] = aSrc[35];
    aTmp[56] = aSrc[58]; aTmp[57] = aSrc[59]; aTmp[58] = aSrc[51]; aTmp[59] = aSrc[43];

    aSrc[32]=aTmp[32]; aSrc[33]=aTmp[33]; aSrc[34]=aTmp[34]; aSrc[35]=aTmp[35];
    aSrc[40]=aTmp[40]; aSrc[41]=aTmp[41]; aSrc[42]=aTmp[42]; aSrc[43]=aTmp[43];
    aSrc[48]=aTmp[48]; aSrc[49]=aTmp[49]; aSrc[50]=aTmp[50]; aSrc[51]=aTmp[51];
    aSrc[56]=aTmp[56]; aSrc[57]=aTmp[57]; aSrc[58]=aTmp[58]; aSrc[59]=aTmp[59];
}

void TwistFastMatrix::PinwheelRightQuarterD(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[36] = aSrc[52]; aTmp[37] = aSrc[44]; aTmp[38] = aSrc[36]; aTmp[39] = aSrc[37];
    aTmp[44] = aSrc[60]; aTmp[45] = aSrc[46]; aTmp[46] = aSrc[54]; aTmp[47] = aSrc[38];
    aTmp[52] = aSrc[61]; aTmp[53] = aSrc[45]; aTmp[54] = aSrc[53]; aTmp[55] = aSrc[39];
    aTmp[60] = aSrc[62]; aTmp[61] = aSrc[63]; aTmp[62] = aSrc[55]; aTmp[63] = aSrc[47];

    aSrc[36]=aTmp[36]; aSrc[37]=aTmp[37]; aSrc[38]=aTmp[38]; aSrc[39]=aTmp[39];
    aSrc[44]=aTmp[44]; aSrc[45]=aTmp[45]; aSrc[46]=aTmp[46]; aSrc[47]=aTmp[47];
    aSrc[52]=aTmp[52]; aSrc[53]=aTmp[53]; aSrc[54]=aTmp[54]; aSrc[55]=aTmp[55];
    aSrc[60]=aTmp[60]; aSrc[61]=aTmp[61]; aSrc[62]=aTmp[62]; aSrc[63]=aTmp[63];
}

void TwistFastMatrix::PinwheelRightEachQuarter(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {
    PinwheelRightQuarterA(pEmptyA, pEmptyB);
    PinwheelRightQuarterB(pEmptyA, pEmptyB);
    PinwheelRightQuarterC(pEmptyA, pEmptyB);
    PinwheelRightQuarterD(pEmptyA, pEmptyB);
}

void TwistFastMatrix::PinwheelLeftQuarterA(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[16] = aSrc[ 0]; aTmp[ 8] = aSrc[ 1]; aTmp[ 0] = aSrc[ 2]; aTmp[ 1] = aSrc[ 3];
    aTmp[24] = aSrc[ 8]; aTmp[10] = aSrc[ 9]; aTmp[18] = aSrc[10]; aTmp[ 2] = aSrc[11];
    aTmp[25] = aSrc[16]; aTmp[ 9] = aSrc[17]; aTmp[17] = aSrc[18]; aTmp[ 3] = aSrc[19];
    aTmp[26] = aSrc[24]; aTmp[27] = aSrc[25]; aTmp[19] = aSrc[26]; aTmp[11] = aSrc[27];

    aSrc[ 0] = aTmp[ 0]; aSrc[ 1] = aTmp[ 1]; aSrc[ 2] = aTmp[ 2]; aSrc[ 3] = aTmp[ 3];
    aSrc[ 8] = aTmp[ 8]; aSrc[ 9] = aTmp[ 9]; aSrc[10] = aTmp[10]; aSrc[11] = aTmp[11];
    aSrc[16] = aTmp[16]; aSrc[17] = aTmp[17]; aSrc[18] = aTmp[18]; aSrc[19] = aTmp[19];
    aSrc[24] = aTmp[24]; aSrc[25] = aTmp[25]; aSrc[26] = aTmp[26]; aSrc[27] = aTmp[27];
}

void TwistFastMatrix::PinwheelLeftQuarterB(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[20] = aSrc[ 4]; aTmp[12] = aSrc[ 5]; aTmp[ 4] = aSrc[ 6]; aTmp[ 5] = aSrc[ 7];
    aTmp[28] = aSrc[12]; aTmp[14] = aSrc[13]; aTmp[22] = aSrc[14]; aTmp[ 6] = aSrc[15];
    aTmp[29] = aSrc[20]; aTmp[13] = aSrc[21]; aTmp[21] = aSrc[22]; aTmp[ 7] = aSrc[23];
    aTmp[30] = aSrc[28]; aTmp[31] = aSrc[29]; aTmp[23] = aSrc[30]; aTmp[15] = aSrc[31];

    aSrc[ 4] = aTmp[ 4]; aSrc[ 5] = aTmp[ 5]; aSrc[ 6] = aTmp[ 6]; aSrc[ 7] = aTmp[ 7];
    aSrc[12] = aTmp[12]; aSrc[13] = aTmp[13]; aSrc[14] = aTmp[14]; aSrc[15] = aTmp[15];
    aSrc[20] = aTmp[20]; aSrc[21] = aTmp[21]; aSrc[22] = aTmp[22]; aSrc[23] = aTmp[23];
    aSrc[28] = aTmp[28]; aSrc[29] = aTmp[29]; aSrc[30] = aTmp[30]; aSrc[31] = aTmp[31];
}

void TwistFastMatrix::PinwheelLeftQuarterC(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[48] = aSrc[32]; aTmp[40] = aSrc[33]; aTmp[32] = aSrc[34]; aTmp[33] = aSrc[35];
    aTmp[56] = aSrc[40]; aTmp[42] = aSrc[41]; aTmp[50] = aSrc[42]; aTmp[34] = aSrc[43];
    aTmp[57] = aSrc[48]; aTmp[41] = aSrc[49]; aTmp[49] = aSrc[50]; aTmp[35] = aSrc[51];
    aTmp[58] = aSrc[56]; aTmp[59] = aSrc[57]; aTmp[51] = aSrc[58]; aTmp[43] = aSrc[59];

    aSrc[32]=aTmp[32]; aSrc[33]=aTmp[33]; aSrc[34]=aTmp[34]; aSrc[35]=aTmp[35];
    aSrc[40]=aTmp[40]; aSrc[41]=aTmp[41]; aSrc[42]=aTmp[42]; aSrc[43]=aTmp[43];
    aSrc[48]=aTmp[48]; aSrc[49]=aTmp[49]; aSrc[50]=aTmp[50]; aSrc[51]=aTmp[51];
    aSrc[56]=aTmp[56]; aSrc[57]=aTmp[57]; aSrc[58]=aTmp[58]; aSrc[59]=aTmp[59];
}

void TwistFastMatrix::PinwheelLeftQuarterD(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSrc = mDataBase;
    std::uint8_t *aTmp = mTemp;

    aTmp[52] = aSrc[36]; aTmp[44] = aSrc[37]; aTmp[36] = aSrc[38]; aTmp[37] = aSrc[39];
    aTmp[60] = aSrc[44]; aTmp[46] = aSrc[45]; aTmp[54] = aSrc[46]; aTmp[38] = aSrc[47];
    aTmp[61] = aSrc[52]; aTmp[45] = aSrc[53]; aTmp[53] = aSrc[54]; aTmp[39] = aSrc[55];
    aTmp[62] = aSrc[60]; aTmp[63] = aSrc[61]; aTmp[55] = aSrc[62]; aTmp[47] = aSrc[63];

    aSrc[36]=aTmp[36]; aSrc[37]=aTmp[37]; aSrc[38]=aTmp[38]; aSrc[39]=aTmp[39];
    aSrc[44]=aTmp[44]; aSrc[45]=aTmp[45]; aSrc[46]=aTmp[46]; aSrc[47]=aTmp[47];
    aSrc[52]=aTmp[52]; aSrc[53]=aTmp[53]; aSrc[54]=aTmp[54]; aSrc[55]=aTmp[55];
    aSrc[60]=aTmp[60]; aSrc[61]=aTmp[61]; aSrc[62]=aTmp[62]; aSrc[63]=aTmp[63];
}

void TwistFastMatrix::PinwheelLeftEachQuarter(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {
    PinwheelLeftQuarterA(pEmptyA, pEmptyB);
    PinwheelLeftQuarterB(pEmptyA, pEmptyB);
    PinwheelLeftQuarterC(pEmptyA, pEmptyB);
    PinwheelLeftQuarterD(pEmptyA, pEmptyB);
}

// ===== 28 =====
void TwistFastMatrix::ShiftRing28A(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(0, pAmount); }

// ===== 24 =====
void TwistFastMatrix::ShiftRing24A(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(1, pAmount); }
void TwistFastMatrix::ShiftRing24B(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(2, pAmount); }
void TwistFastMatrix::ShiftRing24C(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(3, pAmount); }
void TwistFastMatrix::ShiftRing24D(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(4, pAmount); }

// ===== 20 =====
void TwistFastMatrix::ShiftRing20A(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(5, pAmount); }
void TwistFastMatrix::ShiftRing20B(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(6, pAmount); }
void TwistFastMatrix::ShiftRing20C(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(7, pAmount); }
void TwistFastMatrix::ShiftRing20D(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(8, pAmount); }
void TwistFastMatrix::ShiftRing20E(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(9, pAmount); }


// ===== 16 =====
void TwistFastMatrix::ShiftRing16A(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(10, pAmount); }
void TwistFastMatrix::ShiftRing16B(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(11, pAmount); }
void TwistFastMatrix::ShiftRing16C(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(12, pAmount); }
void TwistFastMatrix::ShiftRing16D(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(13, pAmount); }
void TwistFastMatrix::ShiftRing16E(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(14, pAmount); }
void TwistFastMatrix::ShiftRing16F(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(15, pAmount); }
void TwistFastMatrix::ShiftRing16G(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(16, pAmount); }
void TwistFastMatrix::ShiftRing16H(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(17, pAmount); }

// ===== 12 =====
void TwistFastMatrix::ShiftRing12A(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(18, pAmount); }
void TwistFastMatrix::ShiftRing12B(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(19, pAmount); }
void TwistFastMatrix::ShiftRing12C(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(20, pAmount); }
void TwistFastMatrix::ShiftRing12D(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(21, pAmount); }
void TwistFastMatrix::ShiftRing12E(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(22, pAmount); }


// ===== 8 =====
void TwistFastMatrix::ShiftRing8A(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(23, pAmount); }
void TwistFastMatrix::ShiftRing8B(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(24, pAmount); }
void TwistFastMatrix::ShiftRing8C(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(25, pAmount); }
void TwistFastMatrix::ShiftRing8D(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(26, pAmount); }
void TwistFastMatrix::ShiftRing8E(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(27, pAmount); }
void TwistFastMatrix::ShiftRing8F(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(28, pAmount); }
void TwistFastMatrix::ShiftRing8G(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(29, pAmount); }
void TwistFastMatrix::ShiftRing8H(std::uint8_t pAmount, std::uint8_t /*pArg2*/) { PermuteRingBytes(30, pAmount); }



void TwistFastMatrix::PermuteRingBytes(std::uint8_t  pRingIndex, std::uint8_t pAmount) {
    
    std::uint16_t aOffset = TwistFastMatrixRingTable::kRingOffsets[pRingIndex];
    std::uint8_t aSize   = TwistFastMatrixRingTable::kRingSizes[pRingIndex];
    std::uint8_t aAmount = pAmount % aSize;
    const std::uint8_t* aIndices = &TwistFastMatrixRingTable::kRingTable[aOffset];
    for (std::uint8_t aIndex = 0; aIndex < aSize; ++aIndex) {
        std::uint8_t aSrcIndex = aIndex + aSize - aAmount;
        if (aSrcIndex >= aSize) { aSrcIndex -= aSize; }
        
        mTemp[aIndex] = mDataBase[aIndices[aSrcIndex]];
    }
    for (std::uint8_t aIndex = 0; aIndex < aSize; ++aIndex) {
        mDataBase[aIndices[aIndex]] = mTemp[aIndex];
    }
}


bool TwistFastMatrix::operator==(const TwistFastMatrix& other) const {
    return std::memcmp(mDataBase, other.mDataBase, 64) == 0;
}

bool TwistFastMatrix::operator!=(const TwistFastMatrix& other) const {
    return std::memcmp(mDataBase, other.mDataBase, 64) != 0;
}
