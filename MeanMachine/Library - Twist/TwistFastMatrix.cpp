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
        memcpy(mData + (aRowIndex << 3), pMatrix[aRowIndex], 8);
    }
}

TwistFastMatrix::TwistFastMatrix(const TwistFastMatrix &pMatrix) {
    memcpy(mData, pMatrix.mData, 64);
}

TwistFastMatrix::TwistFastMatrix() {
    
}

void TwistFastMatrix::LoadAndReset(const std::uint8_t *pSource) {
    memcpy(mData, pSource, 64);
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
    
    memcpy(pDest +  0, mData + (aOrder[0] << 3), 8);
    memcpy(pDest +  8, mData + (aOrder[1] << 3), 8);
    memcpy(pDest + 16, mData + (aOrder[2] << 3), 8);
    memcpy(pDest + 24, mData + (aOrder[3] << 3), 8);
    memcpy(pDest + 32, mData + (aOrder[4] << 3), 8);
    memcpy(pDest + 40, mData + (aOrder[5] << 3), 8);
    memcpy(pDest + 48, mData + (aOrder[6] << 3), 8);
    memcpy(pDest + 56, mData + (aOrder[7] << 3), 8);
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

bool TwistFastMatrix::OpUsesArg1(TwistFastMatrixOp pOp) {
    switch (pOp) {
        case TwistFastMatrixOp::kRotateRow:
        case TwistFastMatrixOp::kRotateCol:
        case TwistFastMatrixOp::kSwapRows:
        case TwistFastMatrixOp::kSwapRowsEven:
        case TwistFastMatrixOp::kSwapRowsOdd:
        case TwistFastMatrixOp::kSwapCols:
        case TwistFastMatrixOp::kSwapColsEven:
        case TwistFastMatrixOp::kSwapColsOdd:
        case TwistFastMatrixOp::kSwapSixteenths:
        case TwistFastMatrixOp::kReverseRow:
        case TwistFastMatrixOp::kReverseRowEven:
        case TwistFastMatrixOp::kReverseRowOdd:
        case TwistFastMatrixOp::kReverseCol:
        case TwistFastMatrixOp::kReverseColEven:
        case TwistFastMatrixOp::kReverseColOdd:
            return true;
        default:
            break;
    }

    if ((pOp >= TwistFastMatrixOp::kShiftRing28A) && (pOp <= TwistFastMatrixOp::kShiftRing8H)) {
        return true;
    }

    return false;
}

bool TwistFastMatrix::OpUsesArg2(TwistFastMatrixOp pOp) {
    switch (pOp) {
        case TwistFastMatrixOp::kRotateRow:
        case TwistFastMatrixOp::kRotateCol:
        case TwistFastMatrixOp::kSwapRows:
        case TwistFastMatrixOp::kSwapRowsEven:
        case TwistFastMatrixOp::kSwapRowsOdd:
        case TwistFastMatrixOp::kSwapCols:
        case TwistFastMatrixOp::kSwapColsEven:
        case TwistFastMatrixOp::kSwapColsOdd:
        case TwistFastMatrixOp::kSwapSixteenths:
            return true;
        default:
            return false;
    }
}

std::uint8_t TwistFastMatrix::OpValueByteCount(TwistFastMatrixOp pOp) {
    const bool aUsesArg1 = OpUsesArg1(pOp);
    const bool aUsesArg2 = OpUsesArg2(pOp);
    if (aUsesArg1 && aUsesArg2) {
        return 2U;
    }
    if (aUsesArg1) {
        return 1U;
    }
    return 0U;
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

    memcpy(mTemp,          mData + aRowA, 8);
    memcpy(mData + aRowA,  mData + aRowB, 8);
    memcpy(mData + aRowB,  mTemp,         8);
}

void TwistFastMatrix::SwapRowsEven(std::uint8_t pRowA, std::uint8_t pRowB) {

    std::uint8_t aRowA = (pRowA & 7) << 3;
    std::uint8_t aRowB = (pRowB & 7) << 3;

    if (aRowA == aRowB) { return; }

    std::uint8_t aHold;

    // swap only even columns: 0,2,4,6
    aHold = mData[aRowA + 0]; mData[aRowA + 0] = mData[aRowB + 0]; mData[aRowB + 0] = aHold;
    aHold = mData[aRowA + 2]; mData[aRowA + 2] = mData[aRowB + 2]; mData[aRowB + 2] = aHold;
    aHold = mData[aRowA + 4]; mData[aRowA + 4] = mData[aRowB + 4]; mData[aRowB + 4] = aHold;
    aHold = mData[aRowA + 6]; mData[aRowA + 6] = mData[aRowB + 6]; mData[aRowB + 6] = aHold;
}

void TwistFastMatrix::SwapRowsOdd(std::uint8_t pRowA, std::uint8_t pRowB) {

    std::uint8_t aRowA = (pRowA & 7) << 3;
    std::uint8_t aRowB = (pRowB & 7) << 3;

    if (aRowA == aRowB) { return; }

    std::uint8_t aHold;

    // swap only odd columns: 1,3,5,7
    aHold = mData[aRowA + 1]; mData[aRowA + 1] = mData[aRowB + 1]; mData[aRowB + 1] = aHold;
    aHold = mData[aRowA + 3]; mData[aRowA + 3] = mData[aRowB + 3]; mData[aRowB + 3] = aHold;
    aHold = mData[aRowA + 5]; mData[aRowA + 5] = mData[aRowB + 5]; mData[aRowB + 5] = aHold;
    aHold = mData[aRowA + 7]; mData[aRowA + 7] = mData[aRowB + 7]; mData[aRowB + 7] = aHold;
}

void TwistFastMatrix::ReverseRow(std::uint8_t pRow, std::uint8_t /*pArg2*/) {

    std::uint8_t aBase = (pRow & 7) << 3;
    std::uint8_t aHold;

    aHold = mData[aBase + 0]; mData[aBase + 0] = mData[aBase + 7]; mData[aBase + 7] = aHold;
    aHold = mData[aBase + 1]; mData[aBase + 1] = mData[aBase + 6]; mData[aBase + 6] = aHold;
    aHold = mData[aBase + 2]; mData[aBase + 2] = mData[aBase + 5]; mData[aBase + 5] = aHold;
    aHold = mData[aBase + 3]; mData[aBase + 3] = mData[aBase + 4]; mData[aBase + 4] = aHold;
}

void TwistFastMatrix::ReverseRowEven(std::uint8_t pRow, std::uint8_t /*pArg2*/) {

    std::uint8_t aBase = (pRow & 7) << 3;
    std::uint8_t aHold;

    // even columns: 0,2,4,6
    aHold = mData[aBase + 0]; mData[aBase + 0] = mData[aBase + 6]; mData[aBase + 6] = aHold;
    aHold = mData[aBase + 2]; mData[aBase + 2] = mData[aBase + 4]; mData[aBase + 4] = aHold;
}

void TwistFastMatrix::ReverseRowOdd(std::uint8_t pRow, std::uint8_t /*pArg2*/) {

    std::uint8_t aBase = (pRow & 7) << 3;
    std::uint8_t aHold;

    // odd columns: 1,3,5,7
    aHold = mData[aBase + 1]; mData[aBase + 1] = mData[aBase + 7]; mData[aBase + 7] = aHold;
    aHold = mData[aBase + 3]; mData[aBase + 3] = mData[aBase + 5]; mData[aBase + 5] = aHold;
}

void TwistFastMatrix::ReverseCol(std::uint8_t pCol, std::uint8_t /*pArg2*/) {

    std::uint8_t aBase = (pCol & 7);
    std::uint8_t aHold;

    aHold = mData[(0 << 3) + aBase]; mData[(0 << 3) + aBase] = mData[(7 << 3) + aBase]; mData[(7 << 3) + aBase] = aHold;
    aHold = mData[(1 << 3) + aBase]; mData[(1 << 3) + aBase] = mData[(6 << 3) + aBase]; mData[(6 << 3) + aBase] = aHold;
    aHold = mData[(2 << 3) + aBase]; mData[(2 << 3) + aBase] = mData[(5 << 3) + aBase]; mData[(5 << 3) + aBase] = aHold;
    aHold = mData[(3 << 3) + aBase]; mData[(3 << 3) + aBase] = mData[(4 << 3) + aBase]; mData[(4 << 3) + aBase] = aHold;
}

void TwistFastMatrix::ReverseColEven(std::uint8_t pCol, std::uint8_t /*pArg2*/) {

    std::uint8_t aCol = (pCol & 7);
    std::uint8_t aHold;

    // even rows: 0,2,4,6
    aHold = mData[(0 << 3) + aCol]; mData[(0 << 3) + aCol] = mData[(6 << 3) + aCol]; mData[(6 << 3) + aCol] = aHold;
    aHold = mData[(2 << 3) + aCol]; mData[(2 << 3) + aCol] = mData[(4 << 3) + aCol]; mData[(4 << 3) + aCol] = aHold;
}

void TwistFastMatrix::ReverseColOdd(std::uint8_t pCol, std::uint8_t /*pArg2*/) {

    std::uint8_t aCol = (pCol & 7);
    std::uint8_t aHold;

    // odd rows: 1,3,5,7
    aHold = mData[(1 << 3) + aCol]; mData[(1 << 3) + aCol] = mData[(7 << 3) + aCol]; mData[(7 << 3) + aCol] = aHold;
    aHold = mData[(3 << 3) + aCol]; mData[(3 << 3) + aCol] = mData[(5 << 3) + aCol]; mData[(5 << 3) + aCol] = aHold;
}

void TwistFastMatrix::RotateRow(std::uint8_t pRow, std::uint8_t pAmount) {

    std::uint8_t aBase   = (pRow & 7) << 3;
    std::uint8_t aAmount = pAmount & 7;

    if (aAmount == 0) { return; }

    for (std::uint8_t aColIndex = 0; aColIndex < 8; ++aColIndex) {
        mTemp[aColIndex] =
            mData[aBase + ((aColIndex + aAmount) & 7)];
    }

    memcpy(mData + aBase, mTemp, 8);
}

void TwistFastMatrix::SwapCols(std::uint8_t pColA, std::uint8_t pColB) {

    std::uint8_t aColA = pColA & 7;
    std::uint8_t aColB = pColB & 7;

    if (aColA == aColB) { return; }

    std::uint8_t aHold;

    for (std::uint8_t aRowIndex = 0; aRowIndex < 8; ++aRowIndex) {

        std::uint8_t aBase = aRowIndex << 3;

        aHold = mData[aBase + aColA];
        mData[aBase + aColA] = mData[aBase + aColB];
        mData[aBase + aColB] = aHold;
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

        aHold = mData[aBase + aColA];
        mData[aBase + aColA] = mData[aBase + aColB];
        mData[aBase + aColB] = aHold;
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

        aHold = mData[aBase + aColA];
        mData[aBase + aColA] = mData[aBase + aColB];
        mData[aBase + aColB] = aHold;
    }
}

void TwistFastMatrix::RotateCol(std::uint8_t pCol, std::uint8_t pAmount) {

    std::uint8_t aCol    = pCol & 7;
    std::uint8_t aAmount = pAmount & 7;

    if (aAmount == 0) { return; }

    // gather
    for (std::uint8_t aRowIndex = 0; aRowIndex < 8; ++aRowIndex) {
        mTemp[aRowIndex] =
            mData[((aRowIndex + 8 - aAmount) & 7) << 3 | aCol];
    }

    // scatter
    for (std::uint8_t aRowIndex = 0; aRowIndex < 8; ++aRowIndex) {
        mData[(aRowIndex << 3) + aCol] = mTemp[aRowIndex];
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
    aHold = mData[aBaseA0 + aColA + 0];
    mData[aBaseA0 + aColA + 0] = mData[aBaseB0 + aColB + 0];
    mData[aBaseB0 + aColB + 0] = aHold;

    // (0,1)
    aHold = mData[aBaseA0 + aColA + 1];
    mData[aBaseA0 + aColA + 1] = mData[aBaseB0 + aColB + 1];
    mData[aBaseB0 + aColB + 1] = aHold;

    // (1,0)
    aHold = mData[aBaseA1 + aColA + 0];
    mData[aBaseA1 + aColA + 0] = mData[aBaseB1 + aColB + 0];
    mData[aBaseB1 + aColB + 0] = aHold;

    // (1,1)
    aHold = mData[aBaseA1 + aColA + 1];
    mData[aBaseA1 + aColA + 1] = mData[aBaseB1 + aColB + 1];
    mData[aBaseB1 + aColB + 1] = aHold;
}

// 90° clockwise
void TwistFastMatrix::RotateRight(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    std::uint8_t *aSource = mData;
    std::uint8_t *aDest = mTemp;
    aDest[ 0] = aSource[56]; aDest[ 1] = aSource[48]; aDest[ 2] = aSource[40]; aDest[ 3] = aSource[32];
    aDest[ 4] = aSource[24]; aDest[ 5] = aSource[16]; aDest[ 6] = aSource[ 8]; aDest[ 7] = aSource[ 0];
    aDest[ 8] = aSource[57]; aDest[ 9] = aSource[49]; aDest[10] = aSource[41]; aDest[11] = aSource[33];
    aDest[12] = aSource[25]; aDest[13] = aSource[17]; aDest[14] = aSource[ 9]; aDest[15] = aSource[ 1];
    aDest[16] = aSource[58]; aDest[17] = aSource[50]; aDest[18] = aSource[42]; aDest[19] = aSource[34];
    aDest[20] = aSource[26]; aDest[21] = aSource[18]; aDest[22] = aSource[10]; aDest[23] = aSource[ 2];
    aDest[24] = aSource[59]; aDest[25] = aSource[51]; aDest[26] = aSource[43]; aDest[27] = aSource[35];
    aDest[28] = aSource[27]; aDest[29] = aSource[19]; aDest[30] = aSource[11]; aDest[31] = aSource[ 3];
    aDest[32] = aSource[60]; aDest[33] = aSource[52]; aDest[34] = aSource[44]; aDest[35] = aSource[36];
    aDest[36] = aSource[28]; aDest[37] = aSource[20]; aDest[38] = aSource[12]; aDest[39] = aSource[ 4];
    aDest[40] = aSource[61]; aDest[41] = aSource[53]; aDest[42] = aSource[45]; aDest[43] = aSource[37];
    aDest[44] = aSource[29]; aDest[45] = aSource[21]; aDest[46] = aSource[13]; aDest[47] = aSource[ 5];
    aDest[48] = aSource[62]; aDest[49] = aSource[54]; aDest[50] = aSource[46]; aDest[51] = aSource[38];
    aDest[52] = aSource[30]; aDest[53] = aSource[22]; aDest[54] = aSource[14]; aDest[55] = aSource[ 6];
    aDest[56] = aSource[63]; aDest[57] = aSource[55]; aDest[58] = aSource[47]; aDest[59] = aSource[39];
    aDest[60] = aSource[31]; aDest[61] = aSource[23]; aDest[62] = aSource[15]; aDest[63] = aSource[ 7];
    memcpy(mData, mTemp, 64);
}

// 90° counter-clockwise
void TwistFastMatrix::RotateLeft(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aDest = mTemp;
    aDest[ 0] = aSource[ 7]; aDest[ 1] = aSource[15]; aDest[ 2] = aSource[23]; aDest[ 3] = aSource[31];
    aDest[ 4] = aSource[39]; aDest[ 5] = aSource[47]; aDest[ 6] = aSource[55]; aDest[ 7] = aSource[63];
    aDest[ 8] = aSource[ 6]; aDest[ 9] = aSource[14]; aDest[10] = aSource[22]; aDest[11] = aSource[30];
    aDest[12] = aSource[38]; aDest[13] = aSource[46]; aDest[14] = aSource[54]; aDest[15] = aSource[62];
    aDest[16] = aSource[ 5]; aDest[17] = aSource[13]; aDest[18] = aSource[21]; aDest[19] = aSource[29];
    aDest[20] = aSource[37]; aDest[21] = aSource[45]; aDest[22] = aSource[53]; aDest[23] = aSource[61];
    aDest[24] = aSource[ 4]; aDest[25] = aSource[12]; aDest[26] = aSource[20]; aDest[27] = aSource[28];
    aDest[28] = aSource[36]; aDest[29] = aSource[44]; aDest[30] = aSource[52]; aDest[31] = aSource[60];
    aDest[32] = aSource[ 3]; aDest[33] = aSource[11]; aDest[34] = aSource[19]; aDest[35] = aSource[27];
    aDest[36] = aSource[35]; aDest[37] = aSource[43]; aDest[38] = aSource[51]; aDest[39] = aSource[59];
    aDest[40] = aSource[ 2]; aDest[41] = aSource[10]; aDest[42] = aSource[18]; aDest[43] = aSource[26];
    aDest[44] = aSource[34]; aDest[45] = aSource[42]; aDest[46] = aSource[50]; aDest[47] = aSource[58];
    aDest[48] = aSource[ 1]; aDest[49] = aSource[ 9]; aDest[50] = aSource[17]; aDest[51] = aSource[25];
    aDest[52] = aSource[33]; aDest[53] = aSource[41]; aDest[54] = aSource[49]; aDest[55] = aSource[57];
    aDest[56] = aSource[ 0]; aDest[57] = aSource[ 8]; aDest[58] = aSource[16]; aDest[59] = aSource[24];
    aDest[60] = aSource[32]; aDest[61] = aSource[40]; aDest[62] = aSource[48]; aDest[63] = aSource[56];
    memcpy(mData, mTemp, 64);
}

void TwistFastMatrix::RotateRightBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    // copy whole matrix to temp
    memcpy(aTmp, aSource, 64);

    // A <- C
    aSource[ 0] = aTmp[32]; aSource[ 1] = aTmp[33]; aSource[ 2] = aTmp[34]; aSource[ 3] = aTmp[35];
    aSource[ 8] = aTmp[40]; aSource[ 9] = aTmp[41]; aSource[10] = aTmp[42]; aSource[11] = aTmp[43];
    aSource[16] = aTmp[48]; aSource[17] = aTmp[49]; aSource[18] = aTmp[50]; aSource[19] = aTmp[51];
    aSource[24] = aTmp[56]; aSource[25] = aTmp[57]; aSource[26] = aTmp[58]; aSource[27] = aTmp[59];

    // B <- A
    aSource[ 4] = aTmp[ 0]; aSource[ 5] = aTmp[ 1]; aSource[ 6] = aTmp[ 2]; aSource[ 7] = aTmp[ 3];
    aSource[12] = aTmp[ 8]; aSource[13] = aTmp[ 9]; aSource[14] = aTmp[10]; aSource[15] = aTmp[11];
    aSource[20] = aTmp[16]; aSource[21] = aTmp[17]; aSource[22] = aTmp[18]; aSource[23] = aTmp[19];
    aSource[28] = aTmp[24]; aSource[29] = aTmp[25]; aSource[30] = aTmp[26]; aSource[31] = aTmp[27];

    // D <- B
    aSource[36] = aTmp[ 4]; aSource[37] = aTmp[ 5]; aSource[38] = aTmp[ 6]; aSource[39] = aTmp[ 7];
    aSource[44] = aTmp[12]; aSource[45] = aTmp[13]; aSource[46] = aTmp[14]; aSource[47] = aTmp[15];
    aSource[52] = aTmp[20]; aSource[53] = aTmp[21]; aSource[54] = aTmp[22]; aSource[55] = aTmp[23];
    aSource[60] = aTmp[28]; aSource[61] = aTmp[29]; aSource[62] = aTmp[30]; aSource[63] = aTmp[31];

    // C <- D
    aSource[32] = aTmp[36]; aSource[33] = aTmp[37]; aSource[34] = aTmp[38]; aSource[35] = aTmp[39];
    aSource[40] = aTmp[44]; aSource[41] = aTmp[45]; aSource[42] = aTmp[46]; aSource[43] = aTmp[47];
    aSource[48] = aTmp[52]; aSource[49] = aTmp[53]; aSource[50] = aTmp[54]; aSource[51] = aTmp[55];
    aSource[56] = aTmp[60]; aSource[57] = aTmp[61]; aSource[58] = aTmp[62]; aSource[59] = aTmp[63];
}

void TwistFastMatrix::RotateLeftBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    // copy whole matrix to temp
    memcpy(aTmp, aSource, 64);

    // A <- B
    aSource[ 0] = aTmp[ 4]; aSource[ 1] = aTmp[ 5]; aSource[ 2] = aTmp[ 6]; aSource[ 3] = aTmp[ 7];
    aSource[ 8] = aTmp[12]; aSource[ 9] = aTmp[13]; aSource[10] = aTmp[14]; aSource[11] = aTmp[15];
    aSource[16] = aTmp[20]; aSource[17] = aTmp[21]; aSource[18] = aTmp[22]; aSource[19] = aTmp[23];
    aSource[24] = aTmp[28]; aSource[25] = aTmp[29]; aSource[26] = aTmp[30]; aSource[27] = aTmp[31];

    // B <- D
    aSource[ 4] = aTmp[36]; aSource[ 5] = aTmp[37]; aSource[ 6] = aTmp[38]; aSource[ 7] = aTmp[39];
    aSource[12] = aTmp[44]; aSource[13] = aTmp[45]; aSource[14] = aTmp[46]; aSource[15] = aTmp[47];
    aSource[20] = aTmp[52]; aSource[21] = aTmp[53]; aSource[22] = aTmp[54]; aSource[23] = aTmp[55];
    aSource[28] = aTmp[60]; aSource[29] = aTmp[61]; aSource[30] = aTmp[62]; aSource[31] = aTmp[63];

    // D <- C
    aSource[36] = aTmp[32]; aSource[37] = aTmp[33]; aSource[38] = aTmp[34]; aSource[39] = aTmp[35];
    aSource[44] = aTmp[40]; aSource[45] = aTmp[41]; aSource[46] = aTmp[42]; aSource[47] = aTmp[43];
    aSource[52] = aTmp[48]; aSource[53] = aTmp[49]; aSource[54] = aTmp[50]; aSource[55] = aTmp[51];
    aSource[60] = aTmp[56]; aSource[61] = aTmp[57]; aSource[62] = aTmp[58]; aSource[63] = aTmp[59];

    // C <- A
    aSource[32] = aTmp[ 0]; aSource[33] = aTmp[ 1]; aSource[34] = aTmp[ 2]; aSource[35] = aTmp[ 3];
    aSource[40] = aTmp[ 8]; aSource[41] = aTmp[ 9]; aSource[42] = aTmp[10]; aSource[43] = aTmp[11];
    aSource[48] = aTmp[16]; aSource[49] = aTmp[17]; aSource[50] = aTmp[18]; aSource[51] = aTmp[19];
    aSource[56] = aTmp[24]; aSource[57] = aTmp[25]; aSource[58] = aTmp[26]; aSource[59] = aTmp[27];
}

void TwistFastMatrix::RotateRightQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 0] = aSource[24]; aTmp[ 1] = aSource[16]; aTmp[ 2] = aSource[ 8]; aTmp[ 3] = aSource[ 0];
    aTmp[ 8] = aSource[25]; aTmp[ 9] = aSource[17]; aTmp[10] = aSource[ 9]; aTmp[11] = aSource[ 1];
    aTmp[16] = aSource[26]; aTmp[17] = aSource[18]; aTmp[18] = aSource[10]; aTmp[19] = aSource[ 2];
    aTmp[24] = aSource[27]; aTmp[25] = aSource[19]; aTmp[26] = aSource[11]; aTmp[27] = aSource[ 3];

    aSource[ 0] = aTmp[ 0]; aSource[ 1] = aTmp[ 1]; aSource[ 2] = aTmp[ 2]; aSource[ 3] = aTmp[ 3];
    aSource[ 8] = aTmp[ 8]; aSource[ 9] = aTmp[ 9]; aSource[10] = aTmp[10]; aSource[11] = aTmp[11];
    aSource[16] = aTmp[16]; aSource[17] = aTmp[17]; aSource[18] = aTmp[18]; aSource[19] = aTmp[19];
    aSource[24] = aTmp[24]; aSource[25] = aTmp[25]; aSource[26] = aTmp[26]; aSource[27] = aTmp[27];
}

void TwistFastMatrix::RotateRightQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 4] = aSource[28]; aTmp[ 5] = aSource[20]; aTmp[ 6] = aSource[12]; aTmp[ 7] = aSource[ 4];
    aTmp[12] = aSource[29]; aTmp[13] = aSource[21]; aTmp[14] = aSource[13]; aTmp[15] = aSource[ 5];
    aTmp[20] = aSource[30]; aTmp[21] = aSource[22]; aTmp[22] = aSource[14]; aTmp[23] = aSource[ 6];
    aTmp[28] = aSource[31]; aTmp[29] = aSource[23]; aTmp[30] = aSource[15]; aTmp[31] = aSource[ 7];

    aSource[ 4] = aTmp[ 4]; aSource[ 5] = aTmp[ 5]; aSource[ 6] = aTmp[ 6]; aSource[ 7] = aTmp[ 7];
    aSource[12] = aTmp[12]; aSource[13] = aTmp[13]; aSource[14] = aTmp[14]; aSource[15] = aTmp[15];
    aSource[20] = aTmp[20]; aSource[21] = aTmp[21]; aSource[22] = aTmp[22]; aSource[23] = aTmp[23];
    aSource[28] = aTmp[28]; aSource[29] = aTmp[29]; aSource[30] = aTmp[30]; aSource[31] = aTmp[31];
}

void TwistFastMatrix::RotateRightQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[32] = aSource[56]; aTmp[33] = aSource[48]; aTmp[34] = aSource[40]; aTmp[35] = aSource[32];
    aTmp[40] = aSource[57]; aTmp[41] = aSource[49]; aTmp[42] = aSource[41]; aTmp[43] = aSource[33];
    aTmp[48] = aSource[58]; aTmp[49] = aSource[50]; aTmp[50] = aSource[42]; aTmp[51] = aSource[34];
    aTmp[56] = aSource[59]; aTmp[57] = aSource[51]; aTmp[58] = aSource[43]; aTmp[59] = aSource[35];

    aSource[32] = aTmp[32]; aSource[33] = aTmp[33]; aSource[34] = aTmp[34]; aSource[35] = aTmp[35];
    aSource[40] = aTmp[40]; aSource[41] = aTmp[41]; aSource[42] = aTmp[42]; aSource[43] = aTmp[43];
    aSource[48] = aTmp[48]; aSource[49] = aTmp[49]; aSource[50] = aTmp[50]; aSource[51] = aTmp[51];
    aSource[56] = aTmp[56]; aSource[57] = aTmp[57]; aSource[58] = aTmp[58]; aSource[59] = aTmp[59];
}

void TwistFastMatrix::RotateRightQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[36] = aSource[60]; aTmp[37] = aSource[52]; aTmp[38] = aSource[44]; aTmp[39] = aSource[36];
    aTmp[44] = aSource[61]; aTmp[45] = aSource[53]; aTmp[46] = aSource[45]; aTmp[47] = aSource[37];
    aTmp[52] = aSource[62]; aTmp[53] = aSource[54]; aTmp[54] = aSource[46]; aTmp[55] = aSource[38];
    aTmp[60] = aSource[63]; aTmp[61] = aSource[55]; aTmp[62] = aSource[47]; aTmp[63] = aSource[39];

    aSource[36] = aTmp[36]; aSource[37] = aTmp[37]; aSource[38] = aTmp[38]; aSource[39] = aTmp[39];
    aSource[44] = aTmp[44]; aSource[45] = aTmp[45]; aSource[46] = aTmp[46]; aSource[47] = aTmp[47];
    aSource[52] = aTmp[52]; aSource[53] = aTmp[53]; aSource[54] = aTmp[54]; aSource[55] = aTmp[55];
    aSource[60] = aTmp[60]; aSource[61] = aTmp[61]; aSource[62] = aTmp[62]; aSource[63] = aTmp[63];
}

void TwistFastMatrix::RotateRightEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    RotateRightQuarterA();
    RotateRightQuarterB();
    RotateRightQuarterC();
    RotateRightQuarterD();
}

void TwistFastMatrix::RotateLeftQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 0] = aSource[ 3]; aTmp[ 1] = aSource[11]; aTmp[ 2] = aSource[19]; aTmp[ 3] = aSource[27];
    aTmp[ 8] = aSource[ 2]; aTmp[ 9] = aSource[10]; aTmp[10] = aSource[18]; aTmp[11] = aSource[26];
    aTmp[16] = aSource[ 1]; aTmp[17] = aSource[ 9]; aTmp[18] = aSource[17]; aTmp[19] = aSource[25];
    aTmp[24] = aSource[ 0]; aTmp[25] = aSource[ 8]; aTmp[26] = aSource[16]; aTmp[27] = aSource[24];

    aSource[ 0] = aTmp[ 0]; aSource[ 1] = aTmp[ 1]; aSource[ 2] = aTmp[ 2]; aSource[ 3] = aTmp[ 3];
    aSource[ 8] = aTmp[ 8]; aSource[ 9] = aTmp[ 9]; aSource[10] = aTmp[10]; aSource[11] = aTmp[11];
    aSource[16] = aTmp[16]; aSource[17] = aTmp[17]; aSource[18] = aTmp[18]; aSource[19] = aTmp[19];
    aSource[24] = aTmp[24]; aSource[25] = aTmp[25]; aSource[26] = aTmp[26]; aSource[27] = aTmp[27];
}

void TwistFastMatrix::RotateLeftQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 4] = aSource[ 7]; aTmp[ 5] = aSource[15]; aTmp[ 6] = aSource[23]; aTmp[ 7] = aSource[31];
    aTmp[12] = aSource[ 6]; aTmp[13] = aSource[14]; aTmp[14] = aSource[22]; aTmp[15] = aSource[30];
    aTmp[20] = aSource[ 5]; aTmp[21] = aSource[13]; aTmp[22] = aSource[21]; aTmp[23] = aSource[29];
    aTmp[28] = aSource[ 4]; aTmp[29] = aSource[12]; aTmp[30] = aSource[20]; aTmp[31] = aSource[28];

    aSource[ 4] = aTmp[ 4]; aSource[ 5] = aTmp[ 5]; aSource[ 6] = aTmp[ 6]; aSource[ 7] = aTmp[ 7];
    aSource[12] = aTmp[12]; aSource[13] = aTmp[13]; aSource[14] = aTmp[14]; aSource[15] = aTmp[15];
    aSource[20] = aTmp[20]; aSource[21] = aTmp[21]; aSource[22] = aTmp[22]; aSource[23] = aTmp[23];
    aSource[28] = aTmp[28]; aSource[29] = aTmp[29]; aSource[30] = aTmp[30]; aSource[31] = aTmp[31];
}

void TwistFastMatrix::RotateLeftQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[32] = aSource[35]; aTmp[33] = aSource[43]; aTmp[34] = aSource[51]; aTmp[35] = aSource[59];
    aTmp[40] = aSource[34]; aTmp[41] = aSource[42]; aTmp[42] = aSource[50]; aTmp[43] = aSource[58];
    aTmp[48] = aSource[33]; aTmp[49] = aSource[41]; aTmp[50] = aSource[49]; aTmp[51] = aSource[57];
    aTmp[56] = aSource[32]; aTmp[57] = aSource[40]; aTmp[58] = aSource[48]; aTmp[59] = aSource[56];

    aSource[32] = aTmp[32]; aSource[33] = aTmp[33]; aSource[34] = aTmp[34]; aSource[35] = aTmp[35];
    aSource[40] = aTmp[40]; aSource[41] = aTmp[41]; aSource[42] = aTmp[42]; aSource[43] = aTmp[43];
    aSource[48] = aTmp[48]; aSource[49] = aTmp[49]; aSource[50] = aTmp[50]; aSource[51] = aTmp[51];
    aSource[56] = aTmp[56]; aSource[57] = aTmp[57]; aSource[58] = aTmp[58]; aSource[59] = aTmp[59];
}

void TwistFastMatrix::RotateLeftQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[36] = aSource[39]; aTmp[37] = aSource[47]; aTmp[38] = aSource[55]; aTmp[39] = aSource[63];
    aTmp[44] = aSource[38]; aTmp[45] = aSource[46]; aTmp[46] = aSource[54]; aTmp[47] = aSource[62];
    aTmp[52] = aSource[37]; aTmp[53] = aSource[45]; aTmp[54] = aSource[53]; aTmp[55] = aSource[61];
    aTmp[60] = aSource[36]; aTmp[61] = aSource[44]; aTmp[62] = aSource[52]; aTmp[63] = aSource[60];

    aSource[36] = aTmp[36]; aSource[37] = aTmp[37]; aSource[38] = aTmp[38]; aSource[39] = aTmp[39];
    aSource[44] = aTmp[44]; aSource[45] = aTmp[45]; aSource[46] = aTmp[46]; aSource[47] = aTmp[47];
    aSource[52] = aTmp[52]; aSource[53] = aTmp[53]; aSource[54] = aTmp[54]; aSource[55] = aTmp[55];
    aSource[60] = aTmp[60]; aSource[61] = aTmp[61]; aSource[62] = aTmp[62]; aSource[63] = aTmp[63];
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
    aHold = mData[ 1]; mData[ 1] = mData[ 8]; mData[ 8] = aHold;
    aHold = mData[ 2]; mData[ 2] = mData[16]; mData[16] = aHold;
    aHold = mData[ 3]; mData[ 3] = mData[24]; mData[24] = aHold;
    aHold = mData[ 4]; mData[ 4] = mData[32]; mData[32] = aHold;
    aHold = mData[ 5]; mData[ 5] = mData[40]; mData[40] = aHold;
    aHold = mData[ 6]; mData[ 6] = mData[48]; mData[48] = aHold;
    aHold = mData[ 7]; mData[ 7] = mData[56]; mData[56] = aHold;
    aHold = mData[10]; mData[10] = mData[17]; mData[17] = aHold;
    aHold = mData[11]; mData[11] = mData[25]; mData[25] = aHold;
    aHold = mData[12]; mData[12] = mData[33]; mData[33] = aHold;
    aHold = mData[13]; mData[13] = mData[41]; mData[41] = aHold;
    aHold = mData[14]; mData[14] = mData[49]; mData[49] = aHold;
    aHold = mData[15]; mData[15] = mData[57]; mData[57] = aHold;
    aHold = mData[19]; mData[19] = mData[26]; mData[26] = aHold;
    aHold = mData[20]; mData[20] = mData[34]; mData[34] = aHold;
    aHold = mData[21]; mData[21] = mData[42]; mData[42] = aHold;
    aHold = mData[22]; mData[22] = mData[50]; mData[50] = aHold;
    aHold = mData[23]; mData[23] = mData[58]; mData[58] = aHold;
    aHold = mData[28]; mData[28] = mData[35]; mData[35] = aHold;
    aHold = mData[29]; mData[29] = mData[43]; mData[43] = aHold;
    aHold = mData[30]; mData[30] = mData[51]; mData[51] = aHold;
    aHold = mData[31]; mData[31] = mData[59]; mData[59] = aHold;
    aHold = mData[37]; mData[37] = mData[44]; mData[44] = aHold;
    aHold = mData[38]; mData[38] = mData[52]; mData[52] = aHold;
    aHold = mData[39]; mData[39] = mData[60]; mData[60] = aHold;
    aHold = mData[46]; mData[46] = mData[53]; mData[53] = aHold;
    aHold = mData[47]; mData[47] = mData[61]; mData[61] = aHold;
    aHold = mData[55]; mData[55] = mData[62]; mData[62] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[ 1]; mData[ 1] = mData[ 8]; mData[ 8] = aHold;
    aHold = mData[ 2]; mData[ 2] = mData[16]; mData[16] = aHold;
    aHold = mData[ 3]; mData[ 3] = mData[24]; mData[24] = aHold;

    aHold = mData[10]; mData[10] = mData[17]; mData[17] = aHold;
    aHold = mData[11]; mData[11] = mData[25]; mData[25] = aHold;

    aHold = mData[19]; mData[19] = mData[26]; mData[26] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[ 5]; mData[ 5] = mData[12]; mData[12] = aHold;
    aHold = mData[ 6]; mData[ 6] = mData[20]; mData[20] = aHold;
    aHold = mData[ 7]; mData[ 7] = mData[28]; mData[28] = aHold;

    aHold = mData[14]; mData[14] = mData[21]; mData[21] = aHold;
    aHold = mData[15]; mData[15] = mData[29]; mData[29] = aHold;

    aHold = mData[23]; mData[23] = mData[30]; mData[30] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[33]; mData[33] = mData[40]; mData[40] = aHold;
    aHold = mData[34]; mData[34] = mData[48]; mData[48] = aHold;
    aHold = mData[35]; mData[35] = mData[56]; mData[56] = aHold;

    aHold = mData[42]; mData[42] = mData[49]; mData[49] = aHold;
    aHold = mData[43]; mData[43] = mData[57]; mData[57] = aHold;

    aHold = mData[51]; mData[51] = mData[58]; mData[58] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[37]; mData[37] = mData[44]; mData[44] = aHold;
    aHold = mData[38]; mData[38] = mData[52]; mData[52] = aHold;
    aHold = mData[39]; mData[39] = mData[60]; mData[60] = aHold;

    aHold = mData[46]; mData[46] = mData[53]; mData[53] = aHold;
    aHold = mData[47]; mData[47] = mData[61]; mData[61] = aHold;

    aHold = mData[55]; mData[55] = mData[62]; mData[62] = aHold;
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
    aHold = mData[ 0]; mData[ 0] = mData[63]; mData[63] = aHold;
    aHold = mData[ 1]; mData[ 1] = mData[55]; mData[55] = aHold;
    aHold = mData[ 2]; mData[ 2] = mData[47]; mData[47] = aHold;
    aHold = mData[ 3]; mData[ 3] = mData[39]; mData[39] = aHold;
    aHold = mData[ 4]; mData[ 4] = mData[31]; mData[31] = aHold;
    aHold = mData[ 5]; mData[ 5] = mData[23]; mData[23] = aHold;
    aHold = mData[ 6]; mData[ 6] = mData[15]; mData[15] = aHold;
    aHold = mData[ 8]; mData[ 8] = mData[62]; mData[62] = aHold;
    aHold = mData[ 9]; mData[ 9] = mData[54]; mData[54] = aHold;
    aHold = mData[10]; mData[10] = mData[46]; mData[46] = aHold;
    aHold = mData[11]; mData[11] = mData[38]; mData[38] = aHold;
    aHold = mData[12]; mData[12] = mData[30]; mData[30] = aHold;
    aHold = mData[13]; mData[13] = mData[22]; mData[22] = aHold;
    aHold = mData[16]; mData[16] = mData[61]; mData[61] = aHold;
    aHold = mData[17]; mData[17] = mData[53]; mData[53] = aHold;
    aHold = mData[18]; mData[18] = mData[45]; mData[45] = aHold;
    aHold = mData[19]; mData[19] = mData[37]; mData[37] = aHold;
    aHold = mData[20]; mData[20] = mData[29]; mData[29] = aHold;
    aHold = mData[24]; mData[24] = mData[60]; mData[60] = aHold;
    aHold = mData[25]; mData[25] = mData[52]; mData[52] = aHold;
    aHold = mData[26]; mData[26] = mData[44]; mData[44] = aHold;
    aHold = mData[27]; mData[27] = mData[36]; mData[36] = aHold;
    aHold = mData[32]; mData[32] = mData[59]; mData[59] = aHold;
    aHold = mData[33]; mData[33] = mData[51]; mData[51] = aHold;
    aHold = mData[34]; mData[34] = mData[43]; mData[43] = aHold;
    aHold = mData[40]; mData[40] = mData[58]; mData[58] = aHold;
    aHold = mData[41]; mData[41] = mData[50]; mData[50] = aHold;
    aHold = mData[48]; mData[48] = mData[57]; mData[57] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[ 0]; mData[ 0] = mData[27]; mData[27] = aHold;
    aHold = mData[ 1]; mData[ 1] = mData[19]; mData[19] = aHold;
    aHold = mData[ 2]; mData[ 2] = mData[11]; mData[11] = aHold;

    aHold = mData[ 8]; mData[ 8] = mData[26]; mData[26] = aHold;
    aHold = mData[ 9]; mData[ 9] = mData[18]; mData[18] = aHold;

    aHold = mData[16]; mData[16] = mData[25]; mData[25] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[ 4]; mData[ 4] = mData[31]; mData[31] = aHold;
    aHold = mData[ 5]; mData[ 5] = mData[23]; mData[23] = aHold;
    aHold = mData[ 6]; mData[ 6] = mData[15]; mData[15] = aHold;

    aHold = mData[12]; mData[12] = mData[30]; mData[30] = aHold;
    aHold = mData[13]; mData[13] = mData[22]; mData[22] = aHold;

    aHold = mData[20]; mData[20] = mData[29]; mData[29] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[32]; mData[32] = mData[59]; mData[59] = aHold;
    aHold = mData[33]; mData[33] = mData[51]; mData[51] = aHold;
    aHold = mData[34]; mData[34] = mData[43]; mData[43] = aHold;

    aHold = mData[40]; mData[40] = mData[58]; mData[58] = aHold;
    aHold = mData[41]; mData[41] = mData[50]; mData[50] = aHold;

    aHold = mData[48]; mData[48] = mData[57]; mData[57] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[36]; mData[36] = mData[63]; mData[63] = aHold;
    aHold = mData[37]; mData[37] = mData[55]; mData[55] = aHold;
    aHold = mData[38]; mData[38] = mData[47]; mData[47] = aHold;

    aHold = mData[44]; mData[44] = mData[62]; mData[62] = aHold;
    aHold = mData[45]; mData[45] = mData[54]; mData[54] = aHold;

    aHold = mData[52]; mData[52] = mData[61]; mData[61] = aHold;
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
    aHold = mData[ 0]; mData[ 0] = mData[ 7]; mData[ 7] = aHold;
    aHold = mData[ 1]; mData[ 1] = mData[ 6]; mData[ 6] = aHold;
    aHold = mData[ 2]; mData[ 2] = mData[ 5]; mData[ 5] = aHold;
    aHold = mData[ 3]; mData[ 3] = mData[ 4]; mData[ 4] = aHold;

    // row 1
    aHold = mData[ 8]; mData[ 8] = mData[15]; mData[15] = aHold;
    aHold = mData[ 9]; mData[ 9] = mData[14]; mData[14] = aHold;
    aHold = mData[10]; mData[10] = mData[13]; mData[13] = aHold;
    aHold = mData[11]; mData[11] = mData[12]; mData[12] = aHold;

    // row 2
    aHold = mData[16]; mData[16] = mData[23]; mData[23] = aHold;
    aHold = mData[17]; mData[17] = mData[22]; mData[22] = aHold;
    aHold = mData[18]; mData[18] = mData[21]; mData[21] = aHold;
    aHold = mData[19]; mData[19] = mData[20]; mData[20] = aHold;

    // row 3
    aHold = mData[24]; mData[24] = mData[31]; mData[31] = aHold;
    aHold = mData[25]; mData[25] = mData[30]; mData[30] = aHold;
    aHold = mData[26]; mData[26] = mData[29]; mData[29] = aHold;
    aHold = mData[27]; mData[27] = mData[28]; mData[28] = aHold;

    // row 4
    aHold = mData[32]; mData[32] = mData[39]; mData[39] = aHold;
    aHold = mData[33]; mData[33] = mData[38]; mData[38] = aHold;
    aHold = mData[34]; mData[34] = mData[37]; mData[37] = aHold;
    aHold = mData[35]; mData[35] = mData[36]; mData[36] = aHold;

    // row 5
    aHold = mData[40]; mData[40] = mData[47]; mData[47] = aHold;
    aHold = mData[41]; mData[41] = mData[46]; mData[46] = aHold;
    aHold = mData[42]; mData[42] = mData[45]; mData[45] = aHold;
    aHold = mData[43]; mData[43] = mData[44]; mData[44] = aHold;

    // row 6
    aHold = mData[48]; mData[48] = mData[55]; mData[55] = aHold;
    aHold = mData[49]; mData[49] = mData[54]; mData[54] = aHold;
    aHold = mData[50]; mData[50] = mData[53]; mData[53] = aHold;
    aHold = mData[51]; mData[51] = mData[52]; mData[52] = aHold;

    // row 7
    aHold = mData[56]; mData[56] = mData[63]; mData[63] = aHold;
    aHold = mData[57]; mData[57] = mData[62]; mData[62] = aHold;
    aHold = mData[58]; mData[58] = mData[61]; mData[61] = aHold;
    aHold = mData[59]; mData[59] = mData[60]; mData[60] = aHold;
}

void TwistFastMatrix::FlipVertical(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // row 0 ↔ row 7
    aHold = mData[ 0]; mData[ 0] = mData[56]; mData[56] = aHold;
    aHold = mData[ 1]; mData[ 1] = mData[57]; mData[57] = aHold;
    aHold = mData[ 2]; mData[ 2] = mData[58]; mData[58] = aHold;
    aHold = mData[ 3]; mData[ 3] = mData[59]; mData[59] = aHold;
    aHold = mData[ 4]; mData[ 4] = mData[60]; mData[60] = aHold;
    aHold = mData[ 5]; mData[ 5] = mData[61]; mData[61] = aHold;
    aHold = mData[ 6]; mData[ 6] = mData[62]; mData[62] = aHold;
    aHold = mData[ 7]; mData[ 7] = mData[63]; mData[63] = aHold;

    // row 1 ↔ row 6
    aHold = mData[ 8]; mData[ 8] = mData[48]; mData[48] = aHold;
    aHold = mData[ 9]; mData[ 9] = mData[49]; mData[49] = aHold;
    aHold = mData[10]; mData[10] = mData[50]; mData[50] = aHold;
    aHold = mData[11]; mData[11] = mData[51]; mData[51] = aHold;
    aHold = mData[12]; mData[12] = mData[52]; mData[52] = aHold;
    aHold = mData[13]; mData[13] = mData[53]; mData[53] = aHold;
    aHold = mData[14]; mData[14] = mData[54]; mData[54] = aHold;
    aHold = mData[15]; mData[15] = mData[55]; mData[55] = aHold;

    // row 2 ↔ row 5
    aHold = mData[16]; mData[16] = mData[40]; mData[40] = aHold;
    aHold = mData[17]; mData[17] = mData[41]; mData[41] = aHold;
    aHold = mData[18]; mData[18] = mData[42]; mData[42] = aHold;
    aHold = mData[19]; mData[19] = mData[43]; mData[43] = aHold;
    aHold = mData[20]; mData[20] = mData[44]; mData[44] = aHold;
    aHold = mData[21]; mData[21] = mData[45]; mData[45] = aHold;
    aHold = mData[22]; mData[22] = mData[46]; mData[46] = aHold;
    aHold = mData[23]; mData[23] = mData[47]; mData[47] = aHold;

    // row 3 ↔ row 4
    aHold = mData[24]; mData[24] = mData[32]; mData[32] = aHold;
    aHold = mData[25]; mData[25] = mData[33]; mData[33] = aHold;
    aHold = mData[26]; mData[26] = mData[34]; mData[34] = aHold;
    aHold = mData[27]; mData[27] = mData[35]; mData[35] = aHold;
    aHold = mData[28]; mData[28] = mData[36]; mData[36] = aHold;
    aHold = mData[29]; mData[29] = mData[37]; mData[37] = aHold;
    aHold = mData[30]; mData[30] = mData[38]; mData[38] = aHold;
    aHold = mData[31]; mData[31] = mData[39]; mData[39] = aHold;
}

void TwistFastMatrix::FlipHorizontalQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[ 0]; mData[ 0] = mData[ 3]; mData[ 3] = aHold;
    aHold = mData[ 1]; mData[ 1] = mData[ 2]; mData[ 2] = aHold;

    aHold = mData[ 8]; mData[ 8] = mData[11]; mData[11] = aHold;
    aHold = mData[ 9]; mData[ 9] = mData[10]; mData[10] = aHold;

    aHold = mData[16]; mData[16] = mData[19]; mData[19] = aHold;
    aHold = mData[17]; mData[17] = mData[18]; mData[18] = aHold;

    aHold = mData[24]; mData[24] = mData[27]; mData[27] = aHold;
    aHold = mData[25]; mData[25] = mData[26]; mData[26] = aHold;
}

void TwistFastMatrix::FlipHorizontalQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[ 4]; mData[ 4] = mData[ 7]; mData[ 7] = aHold;
    aHold = mData[ 5]; mData[ 5] = mData[ 6]; mData[ 6] = aHold;

    aHold = mData[12]; mData[12] = mData[15]; mData[15] = aHold;
    aHold = mData[13]; mData[13] = mData[14]; mData[14] = aHold;

    aHold = mData[20]; mData[20] = mData[23]; mData[23] = aHold;
    aHold = mData[21]; mData[21] = mData[22]; mData[22] = aHold;

    aHold = mData[28]; mData[28] = mData[31]; mData[31] = aHold;
    aHold = mData[29]; mData[29] = mData[30]; mData[30] = aHold;
}

void TwistFastMatrix::FlipHorizontalQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[32]; mData[32] = mData[35]; mData[35] = aHold;
    aHold = mData[33]; mData[33] = mData[34]; mData[34] = aHold;

    aHold = mData[40]; mData[40] = mData[43]; mData[43] = aHold;
    aHold = mData[41]; mData[41] = mData[42]; mData[42] = aHold;

    aHold = mData[48]; mData[48] = mData[51]; mData[51] = aHold;
    aHold = mData[49]; mData[49] = mData[50]; mData[50] = aHold;

    aHold = mData[56]; mData[56] = mData[59]; mData[59] = aHold;
    aHold = mData[57]; mData[57] = mData[58]; mData[58] = aHold;
}

void TwistFastMatrix::FlipHorizontalQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[36]; mData[36] = mData[39]; mData[39] = aHold;
    aHold = mData[37]; mData[37] = mData[38]; mData[38] = aHold;

    aHold = mData[44]; mData[44] = mData[47]; mData[47] = aHold;
    aHold = mData[45]; mData[45] = mData[46]; mData[46] = aHold;

    aHold = mData[52]; mData[52] = mData[55]; mData[55] = aHold;
    aHold = mData[53]; mData[53] = mData[54]; mData[54] = aHold;

    aHold = mData[60]; mData[60] = mData[63]; mData[63] = aHold;
    aHold = mData[61]; mData[61] = mData[62]; mData[62] = aHold;
}

void TwistFastMatrix::FlipHorizontalEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    FlipHorizontalQuarterA();
    FlipHorizontalQuarterB();
    FlipHorizontalQuarterC();
    FlipHorizontalQuarterD();
}

void TwistFastMatrix::FlipVerticalQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[ 0]; mData[ 0] = mData[24]; mData[24] = aHold;
    aHold = mData[ 1]; mData[ 1] = mData[25]; mData[25] = aHold;
    aHold = mData[ 2]; mData[ 2] = mData[26]; mData[26] = aHold;
    aHold = mData[ 3]; mData[ 3] = mData[27]; mData[27] = aHold;

    aHold = mData[ 8]; mData[ 8] = mData[16]; mData[16] = aHold;
    aHold = mData[ 9]; mData[ 9] = mData[17]; mData[17] = aHold;
    aHold = mData[10]; mData[10] = mData[18]; mData[18] = aHold;
    aHold = mData[11]; mData[11] = mData[19]; mData[19] = aHold;
}

void TwistFastMatrix::FlipVerticalQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[ 4]; mData[ 4] = mData[28]; mData[28] = aHold;
    aHold = mData[ 5]; mData[ 5] = mData[29]; mData[29] = aHold;
    aHold = mData[ 6]; mData[ 6] = mData[30]; mData[30] = aHold;
    aHold = mData[ 7]; mData[ 7] = mData[31]; mData[31] = aHold;

    aHold = mData[12]; mData[12] = mData[20]; mData[20] = aHold;
    aHold = mData[13]; mData[13] = mData[21]; mData[21] = aHold;
    aHold = mData[14]; mData[14] = mData[22]; mData[22] = aHold;
    aHold = mData[15]; mData[15] = mData[23]; mData[23] = aHold;
}

void TwistFastMatrix::FlipVerticalQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[32]; mData[32] = mData[56]; mData[56] = aHold;
    aHold = mData[33]; mData[33] = mData[57]; mData[57] = aHold;
    aHold = mData[34]; mData[34] = mData[58]; mData[58] = aHold;
    aHold = mData[35]; mData[35] = mData[59]; mData[59] = aHold;

    aHold = mData[40]; mData[40] = mData[48]; mData[48] = aHold;
    aHold = mData[41]; mData[41] = mData[49]; mData[49] = aHold;
    aHold = mData[42]; mData[42] = mData[50]; mData[50] = aHold;
    aHold = mData[43]; mData[43] = mData[51]; mData[51] = aHold;
}

void TwistFastMatrix::FlipVerticalQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[36]; mData[36] = mData[60]; mData[60] = aHold;
    aHold = mData[37]; mData[37] = mData[61]; mData[61] = aHold;
    aHold = mData[38]; mData[38] = mData[62]; mData[62] = aHold;
    aHold = mData[39]; mData[39] = mData[63]; mData[63] = aHold;

    aHold = mData[44]; mData[44] = mData[52]; mData[52] = aHold;
    aHold = mData[45]; mData[45] = mData[53]; mData[53] = aHold;
    aHold = mData[46]; mData[46] = mData[54]; mData[54] = aHold;
    aHold = mData[47]; mData[47] = mData[55]; mData[55] = aHold;
}

void TwistFastMatrix::FlipVerticalEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    FlipVerticalQuarterA();
    FlipVerticalQuarterB();
    FlipVerticalQuarterC();
    FlipVerticalQuarterD();
    
}

void TwistFastMatrix::FlipHorizontalBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    memcpy(aTmp, aSource, 64);

    // A <- B
    aSource[ 0] = aTmp[ 4]; aSource[ 1] = aTmp[ 5]; aSource[ 2] = aTmp[ 6]; aSource[ 3] = aTmp[ 7];
    aSource[ 8] = aTmp[12]; aSource[ 9] = aTmp[13]; aSource[10] = aTmp[14]; aSource[11] = aTmp[15];
    aSource[16] = aTmp[20]; aSource[17] = aTmp[21]; aSource[18] = aTmp[22]; aSource[19] = aTmp[23];
    aSource[24] = aTmp[28]; aSource[25] = aTmp[29]; aSource[26] = aTmp[30]; aSource[27] = aTmp[31];

    // B <- A
    aSource[ 4] = aTmp[ 0]; aSource[ 5] = aTmp[ 1]; aSource[ 6] = aTmp[ 2]; aSource[ 7] = aTmp[ 3];
    aSource[12] = aTmp[ 8]; aSource[13] = aTmp[ 9]; aSource[14] = aTmp[10]; aSource[15] = aTmp[11];
    aSource[20] = aTmp[16]; aSource[21] = aTmp[17]; aSource[22] = aTmp[18]; aSource[23] = aTmp[19];
    aSource[28] = aTmp[24]; aSource[29] = aTmp[25]; aSource[30] = aTmp[26]; aSource[31] = aTmp[27];

    // C <- D
    aSource[32] = aTmp[36]; aSource[33] = aTmp[37]; aSource[34] = aTmp[38]; aSource[35] = aTmp[39];
    aSource[40] = aTmp[44]; aSource[41] = aTmp[45]; aSource[42] = aTmp[46]; aSource[43] = aTmp[47];
    aSource[48] = aTmp[52]; aSource[49] = aTmp[53]; aSource[50] = aTmp[54]; aSource[51] = aTmp[55];
    aSource[56] = aTmp[60]; aSource[57] = aTmp[61]; aSource[58] = aTmp[62]; aSource[59] = aTmp[63];

    // D <- C
    aSource[36] = aTmp[32]; aSource[37] = aTmp[33]; aSource[38] = aTmp[34]; aSource[39] = aTmp[35];
    aSource[44] = aTmp[40]; aSource[45] = aTmp[41]; aSource[46] = aTmp[42]; aSource[47] = aTmp[43];
    aSource[52] = aTmp[48]; aSource[53] = aTmp[49]; aSource[54] = aTmp[50]; aSource[55] = aTmp[51];
    aSource[60] = aTmp[56]; aSource[61] = aTmp[57]; aSource[62] = aTmp[58]; aSource[63] = aTmp[59];
}

void TwistFastMatrix::FlipVerticalBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    memcpy(aTmp, aSource, 64);

    // A <- C
    aSource[ 0] = aTmp[32]; aSource[ 1] = aTmp[33]; aSource[ 2] = aTmp[34]; aSource[ 3] = aTmp[35];
    aSource[ 8] = aTmp[40]; aSource[ 9] = aTmp[41]; aSource[10] = aTmp[42]; aSource[11] = aTmp[43];
    aSource[16] = aTmp[48]; aSource[17] = aTmp[49]; aSource[18] = aTmp[50]; aSource[19] = aTmp[51];
    aSource[24] = aTmp[56]; aSource[25] = aTmp[57]; aSource[26] = aTmp[58]; aSource[27] = aTmp[59];

    // B <- D
    aSource[ 4] = aTmp[36]; aSource[ 5] = aTmp[37]; aSource[ 6] = aTmp[38]; aSource[ 7] = aTmp[39];
    aSource[12] = aTmp[44]; aSource[13] = aTmp[45]; aSource[14] = aTmp[46]; aSource[15] = aTmp[47];
    aSource[20] = aTmp[52]; aSource[21] = aTmp[53]; aSource[22] = aTmp[54]; aSource[23] = aTmp[55];
    aSource[28] = aTmp[60]; aSource[29] = aTmp[61]; aSource[30] = aTmp[62]; aSource[31] = aTmp[63];

    // C <- A
    aSource[32] = aTmp[ 0]; aSource[33] = aTmp[ 1]; aSource[34] = aTmp[ 2]; aSource[35] = aTmp[ 3];
    aSource[40] = aTmp[ 8]; aSource[41] = aTmp[ 9]; aSource[42] = aTmp[10]; aSource[43] = aTmp[11];
    aSource[48] = aTmp[16]; aSource[49] = aTmp[17]; aSource[50] = aTmp[18]; aSource[51] = aTmp[19];
    aSource[56] = aTmp[24]; aSource[57] = aTmp[25]; aSource[58] = aTmp[26]; aSource[59] = aTmp[27];

    // D <- B
    aSource[36] = aTmp[ 4]; aSource[37] = aTmp[ 5]; aSource[38] = aTmp[ 6]; aSource[39] = aTmp[ 7];
    aSource[44] = aTmp[12]; aSource[45] = aTmp[13]; aSource[46] = aTmp[14]; aSource[47] = aTmp[15];
    aSource[52] = aTmp[20]; aSource[53] = aTmp[21]; aSource[54] = aTmp[22]; aSource[55] = aTmp[23];
    aSource[60] = aTmp[28]; aSource[61] = aTmp[29]; aSource[62] = aTmp[30]; aSource[63] = aTmp[31];
}

void TwistFastMatrix::TransposeMainDiagonalBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    memcpy(aTmp, aSource, 64);

    // B <- C
    aSource[ 4] = aTmp[32]; aSource[ 5] = aTmp[33]; aSource[ 6] = aTmp[34]; aSource[ 7] = aTmp[35];
    aSource[12] = aTmp[40]; aSource[13] = aTmp[41]; aSource[14] = aTmp[42]; aSource[15] = aTmp[43];
    aSource[20] = aTmp[48]; aSource[21] = aTmp[49]; aSource[22] = aTmp[50]; aSource[23] = aTmp[51];
    aSource[28] = aTmp[56]; aSource[29] = aTmp[57]; aSource[30] = aTmp[58]; aSource[31] = aTmp[59];

    // C <- B
    aSource[32] = aTmp[ 4]; aSource[33] = aTmp[ 5]; aSource[34] = aTmp[ 6]; aSource[35] = aTmp[ 7];
    aSource[40] = aTmp[12]; aSource[41] = aTmp[13]; aSource[42] = aTmp[14]; aSource[43] = aTmp[15];
    aSource[48] = aTmp[20]; aSource[49] = aTmp[21]; aSource[50] = aTmp[22]; aSource[51] = aTmp[23];
    aSource[56] = aTmp[28]; aSource[57] = aTmp[29]; aSource[58] = aTmp[30]; aSource[59] = aTmp[31];

    // A and D unchanged
}

void TwistFastMatrix::TransposeAntiDiagonalBlocks(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    memcpy(aTmp, aSource, 64);

    // A <- D
    aSource[ 0] = aTmp[36]; aSource[ 1] = aTmp[37]; aSource[ 2] = aTmp[38]; aSource[ 3] = aTmp[39];
    aSource[ 8] = aTmp[44]; aSource[ 9] = aTmp[45]; aSource[10] = aTmp[46]; aSource[11] = aTmp[47];
    aSource[16] = aTmp[52]; aSource[17] = aTmp[53]; aSource[18] = aTmp[54]; aSource[19] = aTmp[55];
    aSource[24] = aTmp[60]; aSource[25] = aTmp[61]; aSource[26] = aTmp[62]; aSource[27] = aTmp[63];

    // D <- A
    aSource[36] = aTmp[ 0]; aSource[37] = aTmp[ 1]; aSource[38] = aTmp[ 2]; aSource[39] = aTmp[ 3];
    aSource[44] = aTmp[ 8]; aSource[45] = aTmp[ 9]; aSource[46] = aTmp[10]; aSource[47] = aTmp[11];
    aSource[52] = aTmp[16]; aSource[53] = aTmp[17]; aSource[54] = aTmp[18]; aSource[55] = aTmp[19];
    aSource[60] = aTmp[24]; aSource[61] = aTmp[25]; aSource[62] = aTmp[26]; aSource[63] = aTmp[27];

    // B and C unchanged
}

void TwistFastMatrix::RotateRightEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // --- block (0,0) ---
    aHold = mData[ 0];
    mData[ 0] = mData[ 8];
    mData[ 8] = mData[ 9];
    mData[ 9] = mData[ 1];
    mData[ 1] = aHold;

    // --- block (0,2) ---
    aHold = mData[ 2];
    mData[ 2] = mData[10];
    mData[10] = mData[11];
    mData[11] = mData[ 3];
    mData[ 3] = aHold;

    // --- block (2,0) ---
    aHold = mData[16];
    mData[16] = mData[24];
    mData[24] = mData[25];
    mData[25] = mData[17];
    mData[17] = aHold;

    // --- block (2,2) ---
    aHold = mData[18];
    mData[18] = mData[26];
    mData[26] = mData[27];
    mData[27] = mData[19];
    mData[19] = aHold;
}

void TwistFastMatrix::RotateRightEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[ 4];
    mData[ 4] = mData[12];
    mData[12] = mData[13];
    mData[13] = mData[ 5];
    mData[ 5] = aHold;

    // (0,2)
    aHold = mData[ 6];
    mData[ 6] = mData[14];
    mData[14] = mData[15];
    mData[15] = mData[ 7];
    mData[ 7] = aHold;

    // (2,0)
    aHold = mData[20];
    mData[20] = mData[28];
    mData[28] = mData[29];
    mData[29] = mData[21];
    mData[21] = aHold;

    // (2,2)
    aHold = mData[22];
    mData[22] = mData[30];
    mData[30] = mData[31];
    mData[31] = mData[23];
    mData[23] = aHold;
}

void TwistFastMatrix::RotateRightEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[32];
    mData[32] = mData[40];
    mData[40] = mData[41];
    mData[41] = mData[33];
    mData[33] = aHold;

    // (0,2)
    aHold = mData[34];
    mData[34] = mData[42];
    mData[42] = mData[43];
    mData[43] = mData[35];
    mData[35] = aHold;

    // (2,0)
    aHold = mData[48];
    mData[48] = mData[56];
    mData[56] = mData[57];
    mData[57] = mData[49];
    mData[49] = aHold;

    // (2,2)
    aHold = mData[50];
    mData[50] = mData[58];
    mData[58] = mData[59];
    mData[59] = mData[51];
    mData[51] = aHold;
}

void TwistFastMatrix::RotateRightEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[36];
    mData[36] = mData[44];
    mData[44] = mData[45];
    mData[45] = mData[37];
    mData[37] = aHold;

    // (0,2)
    aHold = mData[38];
    mData[38] = mData[46];
    mData[46] = mData[47];
    mData[47] = mData[39];
    mData[39] = aHold;

    // (2,0)
    aHold = mData[52];
    mData[52] = mData[60];
    mData[60] = mData[61];
    mData[61] = mData[53];
    mData[53] = aHold;

    // (2,2)
    aHold = mData[54];
    mData[54] = mData[62];
    mData[62] = mData[63];
    mData[63] = mData[55];
    mData[55] = aHold;
}

void TwistFastMatrix::RotateRightEachSixteenthEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    RotateRightEachSixteenthQuarterA();
    RotateRightEachSixteenthQuarterB();
    RotateRightEachSixteenthQuarterC();
    RotateRightEachSixteenthQuarterD();
}

void TwistFastMatrix::RotateLeftEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[0];
    mData[0] = mData[1];
    mData[1] = mData[9];
    mData[9] = mData[8];
    mData[8] = aHold;

    aHold = mData[2];
    mData[2] = mData[3];
    mData[3] = mData[11];
    mData[11] = mData[10];
    mData[10] = aHold;

    aHold = mData[16];
    mData[16] = mData[17];
    mData[17] = mData[25];
    mData[25] = mData[24];
    mData[24] = aHold;

    aHold = mData[18];
    mData[18] = mData[19];
    mData[19] = mData[27];
    mData[27] = mData[26];
    mData[26] = aHold;
}

void TwistFastMatrix::RotateLeftEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[4];
    mData[4] = mData[5];
    mData[5] = mData[13];
    mData[13] = mData[12];
    mData[12] = aHold;

    aHold = mData[6];
    mData[6] = mData[7];
    mData[7] = mData[15];
    mData[15] = mData[14];
    mData[14] = aHold;

    aHold = mData[20];
    mData[20] = mData[21];
    mData[21] = mData[29];
    mData[29] = mData[28];
    mData[28] = aHold;

    aHold = mData[22];
    mData[22] = mData[23];
    mData[23] = mData[31];
    mData[31] = mData[30];
    mData[30] = aHold;
}

void TwistFastMatrix::RotateLeftEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[32];
    mData[32] = mData[33];
    mData[33] = mData[41];
    mData[41] = mData[40];
    mData[40] = aHold;

    aHold = mData[34];
    mData[34] = mData[35];
    mData[35] = mData[43];
    mData[43] = mData[42];
    mData[42] = aHold;

    aHold = mData[48];
    mData[48] = mData[49];
    mData[49] = mData[57];
    mData[57] = mData[56];
    mData[56] = aHold;

    aHold = mData[50];
    mData[50] = mData[51];
    mData[51] = mData[59];
    mData[59] = mData[58];
    mData[58] = aHold;
}

void TwistFastMatrix::RotateLeftEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[36];
    mData[36] = mData[37];
    mData[37] = mData[45];
    mData[45] = mData[44];
    mData[44] = aHold;

    aHold = mData[38];
    mData[38] = mData[39];
    mData[39] = mData[47];
    mData[47] = mData[46];
    mData[46] = aHold;

    aHold = mData[52];
    mData[52] = mData[53];
    mData[53] = mData[61];
    mData[61] = mData[60];
    mData[60] = aHold;

    aHold = mData[54];
    mData[54] = mData[55];
    mData[55] = mData[63];
    mData[63] = mData[62];
    mData[62] = aHold;
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
    aHold = mData[0];  mData[0] = mData[1];  mData[1] = aHold;
    aHold = mData[8];  mData[8] = mData[9];  mData[9] = aHold;

    // block (0,2)
    aHold = mData[2];  mData[2] = mData[3];  mData[3] = aHold;
    aHold = mData[10]; mData[10] = mData[11]; mData[11] = aHold;

    // block (2,0)
    aHold = mData[16]; mData[16] = mData[17]; mData[17] = aHold;
    aHold = mData[24]; mData[24] = mData[25]; mData[25] = aHold;

    // block (2,2)
    aHold = mData[18]; mData[18] = mData[19]; mData[19] = aHold;
    aHold = mData[26]; mData[26] = mData[27]; mData[27] = aHold;
}

void TwistFastMatrix::FlipHorizontalEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mData[4];  mData[4] = mData[5];  mData[5] = aHold;
    aHold = mData[12]; mData[12] = mData[13]; mData[13] = aHold;

    // block (0,2)
    aHold = mData[6];  mData[6] = mData[7];  mData[7] = aHold;
    aHold = mData[14]; mData[14] = mData[15]; mData[15] = aHold;

    // block (2,0)
    aHold = mData[20]; mData[20] = mData[21]; mData[21] = aHold;
    aHold = mData[28]; mData[28] = mData[29]; mData[29] = aHold;

    // block (2,2)
    aHold = mData[22]; mData[22] = mData[23]; mData[23] = aHold;
    aHold = mData[30]; mData[30] = mData[31]; mData[31] = aHold;
}

void TwistFastMatrix::FlipHorizontalEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mData[32]; mData[32] = mData[33]; mData[33] = aHold;
    aHold = mData[40]; mData[40] = mData[41]; mData[41] = aHold;

    // block (0,2)
    aHold = mData[34]; mData[34] = mData[35]; mData[35] = aHold;
    aHold = mData[42]; mData[42] = mData[43]; mData[43] = aHold;

    // block (2,0)
    aHold = mData[48]; mData[48] = mData[49]; mData[49] = aHold;
    aHold = mData[56]; mData[56] = mData[57]; mData[57] = aHold;

    // block (2,2)
    aHold = mData[50]; mData[50] = mData[51]; mData[51] = aHold;
    aHold = mData[58]; mData[58] = mData[59]; mData[59] = aHold;
}

void TwistFastMatrix::FlipHorizontalEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mData[36]; mData[36] = mData[37]; mData[37] = aHold;
    aHold = mData[44]; mData[44] = mData[45]; mData[45] = aHold;

    // block (0,2)
    aHold = mData[38]; mData[38] = mData[39]; mData[39] = aHold;
    aHold = mData[46]; mData[46] = mData[47]; mData[47] = aHold;

    // block (2,0)
    aHold = mData[52]; mData[52] = mData[53]; mData[53] = aHold;
    aHold = mData[60]; mData[60] = mData[61]; mData[61] = aHold;

    // block (2,2)
    aHold = mData[54]; mData[54] = mData[55]; mData[55] = aHold;
    aHold = mData[62]; mData[62] = mData[63]; mData[63] = aHold;
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
    aHold = mData[0];  mData[0] = mData[8];  mData[8] = aHold;
    aHold = mData[1];  mData[1] = mData[9];  mData[9] = aHold;

    // block (0,2)
    aHold = mData[2];  mData[2] = mData[10]; mData[10] = aHold;
    aHold = mData[3];  mData[3] = mData[11]; mData[11] = aHold;

    // block (2,0)
    aHold = mData[16]; mData[16] = mData[24]; mData[24] = aHold;
    aHold = mData[17]; mData[17] = mData[25]; mData[25] = aHold;

    // block (2,2)
    aHold = mData[18]; mData[18] = mData[26]; mData[26] = aHold;
    aHold = mData[19]; mData[19] = mData[27]; mData[27] = aHold;
}

void TwistFastMatrix::FlipVerticalEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mData[4];  mData[4] = mData[12]; mData[12] = aHold;
    aHold = mData[5];  mData[5] = mData[13]; mData[13] = aHold;

    // block (0,2)
    aHold = mData[6];  mData[6] = mData[14]; mData[14] = aHold;
    aHold = mData[7];  mData[7] = mData[15]; mData[15] = aHold;

    // block (2,0)
    aHold = mData[20]; mData[20] = mData[28]; mData[28] = aHold;
    aHold = mData[21]; mData[21] = mData[29]; mData[29] = aHold;

    // block (2,2)
    aHold = mData[22]; mData[22] = mData[30]; mData[30] = aHold;
    aHold = mData[23]; mData[23] = mData[31]; mData[31] = aHold;
}

void TwistFastMatrix::FlipVerticalEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mData[32]; mData[32] = mData[40]; mData[40] = aHold;
    aHold = mData[33]; mData[33] = mData[41]; mData[41] = aHold;

    // block (0,2)
    aHold = mData[34]; mData[34] = mData[42]; mData[42] = aHold;
    aHold = mData[35]; mData[35] = mData[43]; mData[43] = aHold;

    // block (2,0)
    aHold = mData[48]; mData[48] = mData[56]; mData[56] = aHold;
    aHold = mData[49]; mData[49] = mData[57]; mData[57] = aHold;

    // block (2,2)
    aHold = mData[50]; mData[50] = mData[58]; mData[58] = aHold;
    aHold = mData[51]; mData[51] = mData[59]; mData[59] = aHold;
}

void TwistFastMatrix::FlipVerticalEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // block (0,0)
    aHold = mData[36]; mData[36] = mData[44]; mData[44] = aHold;
    aHold = mData[37]; mData[37] = mData[45]; mData[45] = aHold;

    // block (0,2)
    aHold = mData[38]; mData[38] = mData[46]; mData[46] = aHold;
    aHold = mData[39]; mData[39] = mData[47]; mData[47] = aHold;

    // block (2,0)
    aHold = mData[52]; mData[52] = mData[60]; mData[60] = aHold;
    aHold = mData[53]; mData[53] = mData[61]; mData[61] = aHold;

    // block (2,2)
    aHold = mData[54]; mData[54] = mData[62]; mData[62] = aHold;
    aHold = mData[55]; mData[55] = mData[63]; mData[63] = aHold;
}

void TwistFastMatrix::FlipVerticalEachSixteenthEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    FlipVerticalEachSixteenthQuarterA();
    FlipVerticalEachSixteenthQuarterB();
    FlipVerticalEachSixteenthQuarterC();
    FlipVerticalEachSixteenthQuarterD();
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[1];  mData[1] = mData[8];  mData[8] = aHold;
    aHold = mData[3];  mData[3] = mData[10]; mData[10] = aHold;
    aHold = mData[17]; mData[17] = mData[24]; mData[24] = aHold;
    aHold = mData[19]; mData[19] = mData[26]; mData[26] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[5];  mData[5] = mData[12]; mData[12] = aHold;
    aHold = mData[7];  mData[7] = mData[14]; mData[14] = aHold;
    aHold = mData[21]; mData[21] = mData[28]; mData[28] = aHold;
    aHold = mData[23]; mData[23] = mData[30]; mData[30] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[33]; mData[33] = mData[40]; mData[40] = aHold;
    aHold = mData[35]; mData[35] = mData[42]; mData[42] = aHold;
    aHold = mData[49]; mData[49] = mData[56]; mData[56] = aHold;
    aHold = mData[51]; mData[51] = mData[58]; mData[58] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    TransposeMainDiagonalEachSixteenthQuarterA();
    TransposeMainDiagonalEachSixteenthQuarterB();
    TransposeMainDiagonalEachSixteenthQuarterC();
    TransposeMainDiagonalEachSixteenthQuarterD();
}

void TwistFastMatrix::TransposeMainDiagonalEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[37]; mData[37] = mData[44]; mData[44] = aHold;
    aHold = mData[39]; mData[39] = mData[46]; mData[46] = aHold;
    aHold = mData[53]; mData[53] = mData[60]; mData[60] = aHold;
    aHold = mData[55]; mData[55] = mData[62]; mData[62] = aHold;
}


void TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterA(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[0];  mData[0] = mData[9];  mData[9] = aHold;
    aHold = mData[2];  mData[2] = mData[11]; mData[11] = aHold;
    aHold = mData[16]; mData[16] = mData[25]; mData[25] = aHold;
    aHold = mData[18]; mData[18] = mData[27]; mData[27] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[4];  mData[4] = mData[13]; mData[13] = aHold;
    aHold = mData[6];  mData[6] = mData[15]; mData[15] = aHold;
    aHold = mData[20]; mData[20] = mData[29]; mData[29] = aHold;
    aHold = mData[22]; mData[22] = mData[31]; mData[31] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[32]; mData[32] = mData[41]; mData[41] = aHold;
    aHold = mData[34]; mData[34] = mData[43]; mData[43] = aHold;
    aHold = mData[48]; mData[48] = mData[57]; mData[57] = aHold;
    aHold = mData[50]; mData[50] = mData[59]; mData[59] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalEachSixteenthQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    aHold = mData[36]; mData[36] = mData[45]; mData[45] = aHold;
    aHold = mData[38]; mData[38] = mData[47]; mData[47] = aHold;
    aHold = mData[52]; mData[52] = mData[61]; mData[61] = aHold;
    aHold = mData[54]; mData[54] = mData[63]; mData[63] = aHold;
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
    aHold = mData[0];
    mData[0]  = mData[16];
    mData[16] = mData[18];
    mData[18] = mData[2];
    mData[2]  = aHold;

    // --- position (0,1) ---
    aHold = mData[1];
    mData[1]  = mData[17];
    mData[17] = mData[19];
    mData[19] = mData[3];
    mData[3]  = aHold;

    // --- position (1,0) ---
    aHold = mData[8];
    mData[8]  = mData[24];
    mData[24] = mData[26];
    mData[26] = mData[10];
    mData[10] = aHold;

    // --- position (1,1) ---
    aHold = mData[9];
    mData[9]  = mData[25];
    mData[25] = mData[27];
    mData[27] = mData[11];
    mData[11] = aHold;
}

void TwistFastMatrix::RotateRightSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[4];
    mData[4]  = mData[20];
    mData[20] = mData[22];
    mData[22] = mData[6];
    mData[6]  = aHold;

    // (0,1)
    aHold = mData[5];
    mData[5]  = mData[21];
    mData[21] = mData[23];
    mData[23] = mData[7];
    mData[7]  = aHold;

    // (1,0)
    aHold = mData[12];
    mData[12] = mData[28];
    mData[28] = mData[30];
    mData[30] = mData[14];
    mData[14] = aHold;

    // (1,1)
    aHold = mData[13];
    mData[13] = mData[29];
    mData[29] = mData[31];
    mData[31] = mData[15];
    mData[15] = aHold;
}

void TwistFastMatrix::RotateRightSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[32];
    mData[32] = mData[48];
    mData[48] = mData[50];
    mData[50] = mData[34];
    mData[34] = aHold;

    // (0,1)
    aHold = mData[33];
    mData[33] = mData[49];
    mData[49] = mData[51];
    mData[51] = mData[35];
    mData[35] = aHold;

    // (1,0)
    aHold = mData[40];
    mData[40] = mData[56];
    mData[56] = mData[58];
    mData[58] = mData[42];
    mData[42] = aHold;

    // (1,1)
    aHold = mData[41];
    mData[41] = mData[57];
    mData[57] = mData[59];
    mData[59] = mData[43];
    mData[43] = aHold;
}

void TwistFastMatrix::RotateRightSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[36];
    mData[36] = mData[52];
    mData[52] = mData[54];
    mData[54] = mData[38];
    mData[38] = aHold;

    // (0,1)
    aHold = mData[37];
    mData[37] = mData[53];
    mData[53] = mData[55];
    mData[55] = mData[39];
    mData[39] = aHold;

    // (1,0)
    aHold = mData[44];
    mData[44] = mData[60];
    mData[60] = mData[62];
    mData[62] = mData[46];
    mData[46] = aHold;

    // (1,1)
    aHold = mData[45];
    mData[45] = mData[61];
    mData[61] = mData[63];
    mData[63] = mData[47];
    mData[47] = aHold;
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
    aHold = mData[0];
    mData[0]  = mData[2];
    mData[2]  = mData[18];
    mData[18] = mData[16];
    mData[16] = aHold;

    // (0,1)
    aHold = mData[1];
    mData[1]  = mData[3];
    mData[3]  = mData[19];
    mData[19] = mData[17];
    mData[17] = aHold;

    // (1,0)
    aHold = mData[8];
    mData[8]  = mData[10];
    mData[10] = mData[26];
    mData[26] = mData[24];
    mData[24] = aHold;

    // (1,1)
    aHold = mData[9];
    mData[9]  = mData[11];
    mData[11] = mData[27];
    mData[27] = mData[25];
    mData[25] = aHold;
}

void TwistFastMatrix::RotateLeftSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[4];
    mData[4]  = mData[6];
    mData[6]  = mData[22];
    mData[22] = mData[20];
    mData[20] = aHold;

    // (0,1)
    aHold = mData[5];
    mData[5]  = mData[7];
    mData[7]  = mData[23];
    mData[23] = mData[21];
    mData[21] = aHold;

    // (1,0)
    aHold = mData[12];
    mData[12] = mData[14];
    mData[14] = mData[30];
    mData[30] = mData[28];
    mData[28] = aHold;

    // (1,1)
    aHold = mData[13];
    mData[13] = mData[15];
    mData[15] = mData[31];
    mData[31] = mData[29];
    mData[29] = aHold;
}

void TwistFastMatrix::RotateLeftSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[32];
    mData[32] = mData[34];
    mData[34] = mData[50];
    mData[50] = mData[48];
    mData[48] = aHold;

    // (0,1)
    aHold = mData[33];
    mData[33] = mData[35];
    mData[35] = mData[51];
    mData[51] = mData[49];
    mData[49] = aHold;

    // (1,0)
    aHold = mData[40];
    mData[40] = mData[42];
    mData[42] = mData[58];
    mData[58] = mData[56];
    mData[56] = aHold;

    // (1,1)
    aHold = mData[41];
    mData[41] = mData[43];
    mData[43] = mData[59];
    mData[59] = mData[57];
    mData[57] = aHold;
}

void TwistFastMatrix::RotateLeftSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[36];
    mData[36] = mData[38];
    mData[38] = mData[54];
    mData[54] = mData[52];
    mData[52] = aHold;

    // (0,1)
    aHold = mData[37];
    mData[37] = mData[39];
    mData[39] = mData[55];
    mData[55] = mData[53];
    mData[53] = aHold;

    // (1,0)
    aHold = mData[44];
    mData[44] = mData[46];
    mData[46] = mData[62];
    mData[62] = mData[60];
    mData[60] = aHold;

    // (1,1)
    aHold = mData[45];
    mData[45] = mData[47];
    mData[47] = mData[63];
    mData[63] = mData[61];
    mData[61] = aHold;
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
    aHold = mData[2];
    mData[2]  = mData[16];
    mData[16] = aHold;

    // (0,1)
    aHold = mData[3];
    mData[3]  = mData[17];
    mData[17] = aHold;

    // (1,0)
    aHold = mData[10];
    mData[10] = mData[24];
    mData[24] = aHold;

    // (1,1)
    aHold = mData[11];
    mData[11] = mData[25];
    mData[25] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[6];
    mData[6]  = mData[20];
    mData[20] = aHold;

    // (0,1)
    aHold = mData[7];
    mData[7]  = mData[21];
    mData[21] = aHold;

    // (1,0)
    aHold = mData[14];
    mData[14] = mData[28];
    mData[28] = aHold;

    // (1,1)
    aHold = mData[15];
    mData[15] = mData[29];
    mData[29] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[34];
    mData[34] = mData[48];
    mData[48] = aHold;

    // (0,1)
    aHold = mData[35];
    mData[35] = mData[49];
    mData[49] = aHold;

    // (1,0)
    aHold = mData[42];
    mData[42] = mData[56];
    mData[56] = aHold;

    // (1,1)
    aHold = mData[43];
    mData[43] = mData[57];
    mData[57] = aHold;
}

void TwistFastMatrix::TransposeMainDiagonalSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[38];
    mData[38] = mData[52];
    mData[52] = aHold;

    // (0,1)
    aHold = mData[39];
    mData[39] = mData[53];
    mData[53] = aHold;

    // (1,0)
    aHold = mData[46];
    mData[46] = mData[60];
    mData[60] = aHold;

    // (1,1)
    aHold = mData[47];
    mData[47] = mData[61];
    mData[61] = aHold;
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
    aHold = mData[0];
    mData[0]  = mData[18];
    mData[18] = aHold;

    // (0,1)
    aHold = mData[1];
    mData[1]  = mData[19];
    mData[19] = aHold;

    // (1,0)
    aHold = mData[8];
    mData[8]  = mData[26];
    mData[26] = aHold;

    // (1,1)
    aHold = mData[9];
    mData[9]  = mData[27];
    mData[27] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[4];
    mData[4]  = mData[22];
    mData[22] = aHold;

    // (0,1)
    aHold = mData[5];
    mData[5]  = mData[23];
    mData[23] = aHold;

    // (1,0)
    aHold = mData[12];
    mData[12] = mData[30];
    mData[30] = aHold;

    // (1,1)
    aHold = mData[13];
    mData[13] = mData[31];
    mData[31] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[32];
    mData[32] = mData[50];
    mData[50] = aHold;

    // (0,1)
    aHold = mData[33];
    mData[33] = mData[51];
    mData[51] = aHold;

    // (1,0)
    aHold = mData[40];
    mData[40] = mData[58];
    mData[58] = aHold;

    // (1,1)
    aHold = mData[41];
    mData[41] = mData[59];
    mData[59] = aHold;
}

void TwistFastMatrix::TransposeAntiDiagonalSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[36];
    mData[36] = mData[54];
    mData[54] = aHold;

    // (0,1)
    aHold = mData[37];
    mData[37] = mData[55];
    mData[55] = aHold;

    // (1,0)
    aHold = mData[44];
    mData[44] = mData[62];
    mData[62] = aHold;

    // (1,1)
    aHold = mData[45];
    mData[45] = mData[63];
    mData[63] = aHold;
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
    aHold = mData[0];  mData[0] = mData[2];  mData[2] = aHold;
    aHold = mData[1];  mData[1] = mData[3];  mData[3] = aHold;
    aHold = mData[8];  mData[8] = mData[10]; mData[10] = aHold;
    aHold = mData[9];  mData[9] = mData[11]; mData[11] = aHold;

    // c ↔ d
    aHold = mData[16]; mData[16] = mData[18]; mData[18] = aHold;
    aHold = mData[17]; mData[17] = mData[19]; mData[19] = aHold;
    aHold = mData[24]; mData[24] = mData[26]; mData[26] = aHold;
    aHold = mData[25]; mData[25] = mData[27]; mData[27] = aHold;
}

void TwistFastMatrix::FlipHorizontalSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ b
    aHold = mData[4];  mData[4] = mData[6];  mData[6] = aHold;
    aHold = mData[5];  mData[5] = mData[7];  mData[7] = aHold;
    aHold = mData[12]; mData[12] = mData[14]; mData[14] = aHold;
    aHold = mData[13]; mData[13] = mData[15]; mData[15] = aHold;

    // c ↔ d
    aHold = mData[20]; mData[20] = mData[22]; mData[22] = aHold;
    aHold = mData[21]; mData[21] = mData[23]; mData[23] = aHold;
    aHold = mData[28]; mData[28] = mData[30]; mData[30] = aHold;
    aHold = mData[29]; mData[29] = mData[31]; mData[31] = aHold;
}

void TwistFastMatrix::FlipHorizontalSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ b
    aHold = mData[32]; mData[32] = mData[34]; mData[34] = aHold;
    aHold = mData[33]; mData[33] = mData[35]; mData[35] = aHold;
    aHold = mData[40]; mData[40] = mData[42]; mData[42] = aHold;
    aHold = mData[41]; mData[41] = mData[43]; mData[43] = aHold;

    // c ↔ d
    aHold = mData[48]; mData[48] = mData[50]; mData[50] = aHold;
    aHold = mData[49]; mData[49] = mData[51]; mData[51] = aHold;
    aHold = mData[56]; mData[56] = mData[58]; mData[58] = aHold;
    aHold = mData[57]; mData[57] = mData[59]; mData[59] = aHold;
}

void TwistFastMatrix::FlipHorizontalSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ b
    aHold = mData[36]; mData[36] = mData[38]; mData[38] = aHold;
    aHold = mData[37]; mData[37] = mData[39]; mData[39] = aHold;
    aHold = mData[44]; mData[44] = mData[46]; mData[46] = aHold;
    aHold = mData[45]; mData[45] = mData[47]; mData[47] = aHold;

    // c ↔ d
    aHold = mData[52]; mData[52] = mData[54]; mData[54] = aHold;
    aHold = mData[53]; mData[53] = mData[55]; mData[55] = aHold;
    aHold = mData[60]; mData[60] = mData[62]; mData[62] = aHold;
    aHold = mData[61]; mData[61] = mData[63]; mData[63] = aHold;
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
    aHold = mData[0];  mData[0] = mData[16]; mData[16] = aHold;
    aHold = mData[1];  mData[1] = mData[17]; mData[17] = aHold;
    aHold = mData[8];  mData[8] = mData[24]; mData[24] = aHold;
    aHold = mData[9];  mData[9] = mData[25]; mData[25] = aHold;

    // b ↔ d
    aHold = mData[2];  mData[2] = mData[18]; mData[18] = aHold;
    aHold = mData[3];  mData[3] = mData[19]; mData[19] = aHold;
    aHold = mData[10]; mData[10] = mData[26]; mData[26] = aHold;
    aHold = mData[11]; mData[11] = mData[27]; mData[27] = aHold;
}

void TwistFastMatrix::FlipVerticalSixteenthsQuarterB(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ c
    aHold = mData[4];  mData[4] = mData[20]; mData[20] = aHold;
    aHold = mData[5];  mData[5] = mData[21]; mData[21] = aHold;
    aHold = mData[12]; mData[12] = mData[28]; mData[28] = aHold;
    aHold = mData[13]; mData[13] = mData[29]; mData[29] = aHold;

    // b ↔ d
    aHold = mData[6];  mData[6] = mData[22]; mData[22] = aHold;
    aHold = mData[7];  mData[7] = mData[23]; mData[23] = aHold;
    aHold = mData[14]; mData[14] = mData[30]; mData[30] = aHold;
    aHold = mData[15]; mData[15] = mData[31]; mData[31] = aHold;
}

void TwistFastMatrix::FlipVerticalSixteenthsQuarterC(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ c
    aHold = mData[32]; mData[32] = mData[48]; mData[48] = aHold;
    aHold = mData[33]; mData[33] = mData[49]; mData[49] = aHold;
    aHold = mData[40]; mData[40] = mData[56]; mData[56] = aHold;
    aHold = mData[41]; mData[41] = mData[57]; mData[57] = aHold;

    // b ↔ d
    aHold = mData[34]; mData[34] = mData[50]; mData[50] = aHold;
    aHold = mData[35]; mData[35] = mData[51]; mData[51] = aHold;
    aHold = mData[42]; mData[42] = mData[58]; mData[58] = aHold;
    aHold = mData[43]; mData[43] = mData[59]; mData[59] = aHold;
}

void TwistFastMatrix::FlipVerticalSixteenthsQuarterD(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {

    std::uint8_t aHold;

    // a ↔ c
    aHold = mData[36]; mData[36] = mData[52]; mData[52] = aHold;
    aHold = mData[37]; mData[37] = mData[53]; mData[53] = aHold;
    aHold = mData[44]; mData[44] = mData[60]; mData[60] = aHold;
    aHold = mData[45]; mData[45] = mData[61]; mData[61] = aHold;

    // b ↔ d
    aHold = mData[38]; mData[38] = mData[54]; mData[54] = aHold;
    aHold = mData[39]; mData[39] = mData[55]; mData[55] = aHold;
    aHold = mData[46]; mData[46] = mData[62]; mData[62] = aHold;
    aHold = mData[47]; mData[47] = mData[63]; mData[63] = aHold;
}

void TwistFastMatrix::FlipVerticalSixteenthsEachQuarter(std::uint8_t /*pArg1*/, std::uint8_t /*pArg2*/) {
    FlipVerticalSixteenthsQuarterA();
    FlipVerticalSixteenthsQuarterB();
    FlipVerticalSixteenthsQuarterC();
    FlipVerticalSixteenthsQuarterD();
}

void TwistFastMatrix::PinwheelRight(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {
    std::uint8_t *aSource = mData;
    std::uint8_t *aDest = mTemp;
    aDest[ 0] = aSource[32]; aDest[ 1] = aSource[24]; aDest[ 2] = aSource[16]; aDest[ 3] = aSource[ 8];
    aDest[ 4] = aSource[ 0]; aDest[ 5] = aSource[ 1]; aDest[ 6] = aSource[ 2]; aDest[ 7] = aSource[ 3];
    aDest[ 8] = aSource[40]; aDest[ 9] = aSource[12]; aDest[10] = aSource[13]; aDest[11] = aSource[14];
    aDest[12] = aSource[22]; aDest[13] = aSource[30]; aDest[14] = aSource[38]; aDest[15] = aSource[ 4];
    aDest[16] = aSource[48]; aDest[17] = aSource[11]; aDest[18] = aSource[34]; aDest[19] = aSource[26];
    aDest[20] = aSource[18]; aDest[21] = aSource[19]; aDest[22] = aSource[46]; aDest[23] = aSource[ 5];
    aDest[24] = aSource[56]; aDest[25] = aSource[10]; aDest[26] = aSource[42]; aDest[27] = aSource[28];
    aDest[28] = aSource[36]; aDest[29] = aSource[20]; aDest[30] = aSource[54]; aDest[31] = aSource[ 6];
    aDest[32] = aSource[57]; aDest[33] = aSource[ 9]; aDest[34] = aSource[43]; aDest[35] = aSource[27];
    aDest[36] = aSource[35]; aDest[37] = aSource[21]; aDest[38] = aSource[53]; aDest[39] = aSource[ 7];
    aDest[40] = aSource[58]; aDest[41] = aSource[17]; aDest[42] = aSource[44]; aDest[43] = aSource[45];
    aDest[44] = aSource[37]; aDest[45] = aSource[29]; aDest[46] = aSource[52]; aDest[47] = aSource[15];
    aDest[48] = aSource[59]; aDest[49] = aSource[25]; aDest[50] = aSource[33]; aDest[51] = aSource[41];
    aDest[52] = aSource[49]; aDest[53] = aSource[50]; aDest[54] = aSource[51]; aDest[55] = aSource[23];
    aDest[56] = aSource[60]; aDest[57] = aSource[61]; aDest[58] = aSource[62]; aDest[59] = aSource[63];
    aDest[60] = aSource[55]; aDest[61] = aSource[47]; aDest[62] = aSource[39]; aDest[63] = aSource[31];
    memcpy(mData, mTemp, 64);
}

void TwistFastMatrix::PinwheelLeft(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {
    std::uint8_t *aSource = mData;
    std::uint8_t *aDest = mTemp;
    aDest[32] = aSource[ 0]; aDest[24] = aSource[ 1]; aDest[16] = aSource[ 2]; aDest[ 8] = aSource[ 3];
    aDest[ 0] = aSource[ 4]; aDest[ 1] = aSource[ 5]; aDest[ 2] = aSource[ 6]; aDest[ 3] = aSource[ 7];
    aDest[40] = aSource[ 8]; aDest[12] = aSource[ 9]; aDest[13] = aSource[10]; aDest[14] = aSource[11];
    aDest[22] = aSource[12]; aDest[30] = aSource[13]; aDest[38] = aSource[14]; aDest[ 4] = aSource[15];
    aDest[48] = aSource[16]; aDest[11] = aSource[17]; aDest[34] = aSource[18]; aDest[26] = aSource[19];
    aDest[18] = aSource[20]; aDest[19] = aSource[21]; aDest[46] = aSource[22]; aDest[ 5] = aSource[23];
    aDest[56] = aSource[24]; aDest[10] = aSource[25]; aDest[42] = aSource[26]; aDest[28] = aSource[27];
    aDest[36] = aSource[28]; aDest[20] = aSource[29]; aDest[54] = aSource[30]; aDest[ 6] = aSource[31];
    aDest[57] = aSource[32]; aDest[ 9] = aSource[33]; aDest[43] = aSource[34]; aDest[27] = aSource[35];
    aDest[35] = aSource[36]; aDest[21] = aSource[37]; aDest[53] = aSource[38]; aDest[ 7] = aSource[39];
    aDest[58] = aSource[40]; aDest[17] = aSource[41]; aDest[44] = aSource[42]; aDest[45] = aSource[43];
    aDest[37] = aSource[44]; aDest[29] = aSource[45]; aDest[52] = aSource[46]; aDest[15] = aSource[47];
    aDest[59] = aSource[48]; aDest[25] = aSource[49]; aDest[33] = aSource[50]; aDest[41] = aSource[51];
    aDest[49] = aSource[52]; aDest[50] = aSource[53]; aDest[51] = aSource[54]; aDest[23] = aSource[55];
    aDest[60] = aSource[56]; aDest[61] = aSource[57]; aDest[62] = aSource[58]; aDest[63] = aSource[59];
    aDest[55] = aSource[60]; aDest[47] = aSource[61]; aDest[39] = aSource[62]; aDest[31] = aSource[63];
    memcpy(mData, mTemp, 64);
}

void TwistFastMatrix::PinwheelRightQuarterA(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 0] = aSource[16]; aTmp[ 1] = aSource[ 8]; aTmp[ 2] = aSource[ 0]; aTmp[ 3] = aSource[ 1];
    aTmp[ 8] = aSource[24]; aTmp[ 9] = aSource[10]; aTmp[10] = aSource[18]; aTmp[11] = aSource[ 2];
    aTmp[16] = aSource[25]; aTmp[17] = aSource[ 9]; aTmp[18] = aSource[17]; aTmp[19] = aSource[ 3];
    aTmp[24] = aSource[26]; aTmp[25] = aSource[27]; aTmp[26] = aSource[19]; aTmp[27] = aSource[11];

    aSource[ 0] = aTmp[ 0]; aSource[ 1] = aTmp[ 1]; aSource[ 2] = aTmp[ 2]; aSource[ 3] = aTmp[ 3];
    aSource[ 8] = aTmp[ 8]; aSource[ 9] = aTmp[ 9]; aSource[10] = aTmp[10]; aSource[11] = aTmp[11];
    aSource[16] = aTmp[16]; aSource[17] = aTmp[17]; aSource[18] = aTmp[18]; aSource[19] = aTmp[19];
    aSource[24] = aTmp[24]; aSource[25] = aTmp[25]; aSource[26] = aTmp[26]; aSource[27] = aTmp[27];
}

void TwistFastMatrix::PinwheelRightQuarterB(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[ 4] = aSource[20]; aTmp[ 5] = aSource[12]; aTmp[ 6] = aSource[ 4]; aTmp[ 7] = aSource[ 5];
    aTmp[12] = aSource[28]; aTmp[13] = aSource[14]; aTmp[14] = aSource[22]; aTmp[15] = aSource[ 6];
    aTmp[20] = aSource[29]; aTmp[21] = aSource[13]; aTmp[22] = aSource[21]; aTmp[23] = aSource[ 7];
    aTmp[28] = aSource[30]; aTmp[29] = aSource[31]; aTmp[30] = aSource[23]; aTmp[31] = aSource[15];

    aSource[ 4] = aTmp[ 4]; aSource[ 5] = aTmp[ 5]; aSource[ 6] = aTmp[ 6]; aSource[ 7] = aTmp[ 7];
    aSource[12] = aTmp[12]; aSource[13] = aTmp[13]; aSource[14] = aTmp[14]; aSource[15] = aTmp[15];
    aSource[20] = aTmp[20]; aSource[21] = aTmp[21]; aSource[22] = aTmp[22]; aSource[23] = aTmp[23];
    aSource[28] = aTmp[28]; aSource[29] = aTmp[29]; aSource[30] = aTmp[30]; aSource[31] = aTmp[31];
}

void TwistFastMatrix::PinwheelRightQuarterC(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[32] = aSource[48]; aTmp[33] = aSource[40]; aTmp[34] = aSource[32]; aTmp[35] = aSource[33];
    aTmp[40] = aSource[56]; aTmp[41] = aSource[42]; aTmp[42] = aSource[50]; aTmp[43] = aSource[34];
    aTmp[48] = aSource[57]; aTmp[49] = aSource[41]; aTmp[50] = aSource[49]; aTmp[51] = aSource[35];
    aTmp[56] = aSource[58]; aTmp[57] = aSource[59]; aTmp[58] = aSource[51]; aTmp[59] = aSource[43];

    aSource[32]=aTmp[32]; aSource[33]=aTmp[33]; aSource[34]=aTmp[34]; aSource[35]=aTmp[35];
    aSource[40]=aTmp[40]; aSource[41]=aTmp[41]; aSource[42]=aTmp[42]; aSource[43]=aTmp[43];
    aSource[48]=aTmp[48]; aSource[49]=aTmp[49]; aSource[50]=aTmp[50]; aSource[51]=aTmp[51];
    aSource[56]=aTmp[56]; aSource[57]=aTmp[57]; aSource[58]=aTmp[58]; aSource[59]=aTmp[59];
}

void TwistFastMatrix::PinwheelRightQuarterD(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[36] = aSource[52]; aTmp[37] = aSource[44]; aTmp[38] = aSource[36]; aTmp[39] = aSource[37];
    aTmp[44] = aSource[60]; aTmp[45] = aSource[46]; aTmp[46] = aSource[54]; aTmp[47] = aSource[38];
    aTmp[52] = aSource[61]; aTmp[53] = aSource[45]; aTmp[54] = aSource[53]; aTmp[55] = aSource[39];
    aTmp[60] = aSource[62]; aTmp[61] = aSource[63]; aTmp[62] = aSource[55]; aTmp[63] = aSource[47];

    aSource[36]=aTmp[36]; aSource[37]=aTmp[37]; aSource[38]=aTmp[38]; aSource[39]=aTmp[39];
    aSource[44]=aTmp[44]; aSource[45]=aTmp[45]; aSource[46]=aTmp[46]; aSource[47]=aTmp[47];
    aSource[52]=aTmp[52]; aSource[53]=aTmp[53]; aSource[54]=aTmp[54]; aSource[55]=aTmp[55];
    aSource[60]=aTmp[60]; aSource[61]=aTmp[61]; aSource[62]=aTmp[62]; aSource[63]=aTmp[63];
}

void TwistFastMatrix::PinwheelRightEachQuarter(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {
    PinwheelRightQuarterA(pEmptyA, pEmptyB);
    PinwheelRightQuarterB(pEmptyA, pEmptyB);
    PinwheelRightQuarterC(pEmptyA, pEmptyB);
    PinwheelRightQuarterD(pEmptyA, pEmptyB);
}

void TwistFastMatrix::PinwheelLeftQuarterA(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[16] = aSource[ 0]; aTmp[ 8] = aSource[ 1]; aTmp[ 0] = aSource[ 2]; aTmp[ 1] = aSource[ 3];
    aTmp[24] = aSource[ 8]; aTmp[10] = aSource[ 9]; aTmp[18] = aSource[10]; aTmp[ 2] = aSource[11];
    aTmp[25] = aSource[16]; aTmp[ 9] = aSource[17]; aTmp[17] = aSource[18]; aTmp[ 3] = aSource[19];
    aTmp[26] = aSource[24]; aTmp[27] = aSource[25]; aTmp[19] = aSource[26]; aTmp[11] = aSource[27];

    aSource[ 0] = aTmp[ 0]; aSource[ 1] = aTmp[ 1]; aSource[ 2] = aTmp[ 2]; aSource[ 3] = aTmp[ 3];
    aSource[ 8] = aTmp[ 8]; aSource[ 9] = aTmp[ 9]; aSource[10] = aTmp[10]; aSource[11] = aTmp[11];
    aSource[16] = aTmp[16]; aSource[17] = aTmp[17]; aSource[18] = aTmp[18]; aSource[19] = aTmp[19];
    aSource[24] = aTmp[24]; aSource[25] = aTmp[25]; aSource[26] = aTmp[26]; aSource[27] = aTmp[27];
}

void TwistFastMatrix::PinwheelLeftQuarterB(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[20] = aSource[ 4]; aTmp[12] = aSource[ 5]; aTmp[ 4] = aSource[ 6]; aTmp[ 5] = aSource[ 7];
    aTmp[28] = aSource[12]; aTmp[14] = aSource[13]; aTmp[22] = aSource[14]; aTmp[ 6] = aSource[15];
    aTmp[29] = aSource[20]; aTmp[13] = aSource[21]; aTmp[21] = aSource[22]; aTmp[ 7] = aSource[23];
    aTmp[30] = aSource[28]; aTmp[31] = aSource[29]; aTmp[23] = aSource[30]; aTmp[15] = aSource[31];

    aSource[ 4] = aTmp[ 4]; aSource[ 5] = aTmp[ 5]; aSource[ 6] = aTmp[ 6]; aSource[ 7] = aTmp[ 7];
    aSource[12] = aTmp[12]; aSource[13] = aTmp[13]; aSource[14] = aTmp[14]; aSource[15] = aTmp[15];
    aSource[20] = aTmp[20]; aSource[21] = aTmp[21]; aSource[22] = aTmp[22]; aSource[23] = aTmp[23];
    aSource[28] = aTmp[28]; aSource[29] = aTmp[29]; aSource[30] = aTmp[30]; aSource[31] = aTmp[31];
}

void TwistFastMatrix::PinwheelLeftQuarterC(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[48] = aSource[32]; aTmp[40] = aSource[33]; aTmp[32] = aSource[34]; aTmp[33] = aSource[35];
    aTmp[56] = aSource[40]; aTmp[42] = aSource[41]; aTmp[50] = aSource[42]; aTmp[34] = aSource[43];
    aTmp[57] = aSource[48]; aTmp[41] = aSource[49]; aTmp[49] = aSource[50]; aTmp[35] = aSource[51];
    aTmp[58] = aSource[56]; aTmp[59] = aSource[57]; aTmp[51] = aSource[58]; aTmp[43] = aSource[59];

    aSource[32]=aTmp[32]; aSource[33]=aTmp[33]; aSource[34]=aTmp[34]; aSource[35]=aTmp[35];
    aSource[40]=aTmp[40]; aSource[41]=aTmp[41]; aSource[42]=aTmp[42]; aSource[43]=aTmp[43];
    aSource[48]=aTmp[48]; aSource[49]=aTmp[49]; aSource[50]=aTmp[50]; aSource[51]=aTmp[51];
    aSource[56]=aTmp[56]; aSource[57]=aTmp[57]; aSource[58]=aTmp[58]; aSource[59]=aTmp[59];
}

void TwistFastMatrix::PinwheelLeftQuarterD(std::uint8_t pEmptyA, std::uint8_t pEmptyB) {

    std::uint8_t *aSource = mData;
    std::uint8_t *aTmp = mTemp;

    aTmp[52] = aSource[36]; aTmp[44] = aSource[37]; aTmp[36] = aSource[38]; aTmp[37] = aSource[39];
    aTmp[60] = aSource[44]; aTmp[46] = aSource[45]; aTmp[54] = aSource[46]; aTmp[38] = aSource[47];
    aTmp[61] = aSource[52]; aTmp[45] = aSource[53]; aTmp[53] = aSource[54]; aTmp[39] = aSource[55];
    aTmp[62] = aSource[60]; aTmp[63] = aSource[61]; aTmp[55] = aSource[62]; aTmp[47] = aSource[63];

    aSource[36]=aTmp[36]; aSource[37]=aTmp[37]; aSource[38]=aTmp[38]; aSource[39]=aTmp[39];
    aSource[44]=aTmp[44]; aSource[45]=aTmp[45]; aSource[46]=aTmp[46]; aSource[47]=aTmp[47];
    aSource[52]=aTmp[52]; aSource[53]=aTmp[53]; aSource[54]=aTmp[54]; aSource[55]=aTmp[55];
    aSource[60]=aTmp[60]; aSource[61]=aTmp[61]; aSource[62]=aTmp[62]; aSource[63]=aTmp[63];
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
        std::uint8_t aSourceIndex = aIndex + aSize - aAmount;
        if (aSourceIndex >= aSize) { aSourceIndex -= aSize; }
        
        mTemp[aIndex] = mData[aIndices[aSourceIndex]];
    }
    for (std::uint8_t aIndex = 0; aIndex < aSize; ++aIndex) {
        mData[aIndices[aIndex]] = mTemp[aIndex];
    }
}


bool TwistFastMatrix::operator==(const TwistFastMatrix& other) const {
    return std::memcmp(mData, other.mData, 64) == 0;
}

bool TwistFastMatrix::operator!=(const TwistFastMatrix& other) const {
    return std::memcmp(mData, other.mData, 64) != 0;
}
