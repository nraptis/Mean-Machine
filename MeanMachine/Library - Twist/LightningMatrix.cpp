#include "LightningMatrix.hpp"

#include <algorithm>
#include <cstring>


constexpr std::array<std::size_t, LightningMatrix::kSize> kRotateRightMap = {
    12, 8, 4, 0,
    13, 9, 5, 1,
    14, 10, 6, 2,
    15, 11, 7, 3,
};

constexpr std::array<std::size_t, LightningMatrix::kSize> kRotateLeftMap = {
    3, 7, 11, 15,
    2, 6, 10, 14,
    1, 5, 9, 13,
    0, 4, 8, 12,
};

constexpr std::array<std::size_t, LightningMatrix::kSize> kFlipDiagBMap = {
    15, 11, 7, 3,
    14, 10, 6, 2,
    13, 9, 5, 1,
    12, 8, 4, 0,
};

template <typename Map>
void Remap(std::array<std::uint8_t, LightningMatrix::kSize>& data, const Map& map) {
  std::array<std::uint8_t, LightningMatrix::kSize> original = data;
  for (std::size_t i = 0; i < LightningMatrix::kSize; ++i) {
    data[i] = original[map[i]];
  }
}


LightningMatrix::LightningMatrix() = default;

LightningMatrix::LightningMatrix(const std::uint8_t* bytes) {
  Load(bytes);
}

std::uint8_t* LightningMatrix::Data() {
  return data_.data();
}

const std::uint8_t* LightningMatrix::Data() const {
  return data_.data();
}

void LightningMatrix::Clear() {
  data_.fill(0U);
}

void LightningMatrix::Fill(std::uint8_t value) {
  data_.fill(value);
}

void LightningMatrix::Load(const std::uint8_t* bytes) {
  if (bytes == nullptr) {
    Clear();
    return;
  }
  std::memcpy(data_.data(), bytes, kSize);
}

void LightningMatrix::Store(std::uint8_t* bytes) const {
  if (bytes == nullptr) {
    return;
  }
  std::memcpy(bytes, data_.data(), kSize);
}

std::uint8_t& LightningMatrix::At(std::size_t row, std::size_t column) {
  return data_[Offset(row, column)];
}

std::uint8_t LightningMatrix::At(std::size_t row, std::size_t column) const {
  return data_[Offset(row, column)];
}

void LightningMatrix::RotateRowLeft(std::size_t row, unsigned amount) {
  row = NormalizeIndex(row);
  const unsigned shift = NormalizeAmount(amount);
  if (shift == 0U) {
    return;
  }
  std::array<std::uint8_t, kWidth> copy{};
  for (std::size_t col = 0; col < kWidth; ++col) {
    copy[col] = At(row, col);
  }
  for (std::size_t col = 0; col < kWidth; ++col) {
    At(row, col) = copy[(col + shift) & 3U];
  }
}

void LightningMatrix::RotateRowRight(std::size_t row, unsigned amount) {
  RotateRowLeft(row, (kWidth - NormalizeAmount(amount)) & 3U);
}

void LightningMatrix::RotateColumnUp(std::size_t column, unsigned amount) {
  column = NormalizeIndex(column);
  const unsigned shift = NormalizeAmount(amount);
  if (shift == 0U) {
    return;
  }
  std::array<std::uint8_t, kHeight> copy{};
  for (std::size_t row = 0; row < kHeight; ++row) {
    copy[row] = At(row, column);
  }
  for (std::size_t row = 0; row < kHeight; ++row) {
    At(row, column) = copy[(row + shift) & 3U];
  }
}

void LightningMatrix::RotateColumnDown(std::size_t column, unsigned amount) {
  RotateColumnUp(column, (kHeight - NormalizeAmount(amount)) & 3U);
}

void LightningMatrix::SwapRows(std::size_t row_a, std::size_t row_b) {
  row_a = NormalizeIndex(row_a);
  row_b = NormalizeIndex(row_b);
  if (row_a == row_b) {
    return;
  }
  for (std::size_t col = 0; col < kWidth; ++col) {
    std::swap(At(row_a, col), At(row_b, col));
  }
}

void LightningMatrix::SwapColumns(std::size_t column_a, std::size_t column_b) {
  column_a = NormalizeIndex(column_a);
  column_b = NormalizeIndex(column_b);
  if (column_a == column_b) {
    return;
  }
  for (std::size_t row = 0; row < kHeight; ++row) {
    std::swap(At(row, column_a), At(row, column_b));
  }
}

void LightningMatrix::WeaveRows(std::size_t row_a, std::size_t row_b) {
  row_a = NormalizeIndex(row_a);
  row_b = NormalizeIndex(row_b);
  if (row_a == row_b) {
    return;
  }
  for (std::size_t col = 1; col < kWidth; col += 2U) {
    std::swap(At(row_a, col), At(row_b, col));
  }
}

void LightningMatrix::WeaveColumns(std::size_t column_a, std::size_t column_b) {
  column_a = NormalizeIndex(column_a);
  column_b = NormalizeIndex(column_b);
  if (column_a == column_b) {
    return;
  }
  for (std::size_t row = 1; row < kHeight; row += 2U) {
    std::swap(At(row, column_a), At(row, column_b));
  }
}

void LightningMatrix::RotateRight() {
  Remap(data_, kRotateRightMap);
}

void LightningMatrix::RotateLeft() {
  Remap(data_, kRotateLeftMap);
}

void LightningMatrix::FlipHorizontal() {
  for (std::size_t row = 0; row < kHeight; ++row) {
    std::swap(At(row, 0), At(row, 3));
    std::swap(At(row, 1), At(row, 2));
  }
}

void LightningMatrix::FlipVertical() {
  SwapRows(0, 3);
  SwapRows(1, 2);
}

void LightningMatrix::Transpose() {
  for (std::size_t row = 0; row < kHeight; ++row) {
    for (std::size_t column = row + 1U; column < kWidth; ++column) {
      std::swap(At(row, column), At(column, row));
    }
  }
}

void LightningMatrix::FlipDiagB() {
  Remap(data_, kFlipDiagBMap);
}

void LightningMatrix::RotateRing(unsigned amount) {
    static constexpr std::array<std::size_t, 12> kRing = {
        0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4,
    };
    const unsigned shift = amount % kRing.size();
    if (shift == 0U) {
        return;
    }
    std::array<std::uint8_t, kRing.size()> copy{};
    for (std::size_t i = 0; i < kRing.size(); ++i) {
        copy[i] = data_[kRing[i]];
    }
    for (std::size_t i = 0; i < kRing.size(); ++i) {
        data_[kRing[(i + shift) % kRing.size()]] = copy[i];
    }
}

void LightningMatrix::ApplyFastOp(LightningFastOp op, std::uint8_t arg0, std::uint8_t arg1) {
  switch (op) {
    case LightningFastOp::kRotateRowLeft:
      RotateRowLeft(arg0, arg1);
      break;
    case LightningFastOp::kRotateRowRight:
      RotateRowRight(arg0, arg1);
      break;
    case LightningFastOp::kRotateColumnUp:
      RotateColumnUp(arg0, arg1);
      break;
    case LightningFastOp::kRotateColumnDown:
      RotateColumnDown(arg0, arg1);
      break;
    case LightningFastOp::kSwapRows:
      SwapRows(arg0, arg1);
      break;
    case LightningFastOp::kSwapColumns:
      SwapColumns(arg0, arg1);
      break;
    case LightningFastOp::kWeaveRows:
      WeaveRows(arg0, arg1);
      break;
    case LightningFastOp::kWeaveColumns:
      WeaveColumns(arg0, arg1);
      break;
  }
}

void LightningMatrix::ApplySlowOp(LightningSlowOp op, std::uint8_t arg0, std::uint8_t arg1) {
  static_cast<void>(arg1);
  switch (op) {
    case LightningSlowOp::kRotateRight:
      RotateRight();
      break;
    case LightningSlowOp::kRotateLeft:
      RotateLeft();
      break;
    case LightningSlowOp::kFlipHorizontal:
      FlipHorizontal();
      break;
    case LightningSlowOp::kFlipVertical:
      FlipVertical();
      break;
    case LightningSlowOp::kTranspose:
      Transpose();
      break;
    case LightningSlowOp::kFlipDiagB:
      FlipDiagB();
      break;
    case LightningSlowOp::kRotateRing:
      RotateRing(arg0);
      break;
  }
}

std::size_t LightningMatrix::NormalizeIndex(std::size_t value) {
  return value & 3U;
}

unsigned LightningMatrix::NormalizeAmount(unsigned value) {
  return value & 3U;
}

std::size_t LightningMatrix::Offset(std::size_t row, std::size_t column) const {
  return (NormalizeIndex(row) * kWidth) + NormalizeIndex(column);
}
