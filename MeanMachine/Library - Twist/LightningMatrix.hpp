#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

enum class LightningFastOp : std::uint8_t {
    kRotateRowLeft = 0,
    kRotateRowRight = 1,
    kRotateColumnUp = 2,
    kRotateColumnDown = 3,
    kSwapRows = 4,
    kSwapColumns = 5,
    kWeaveRows = 10,
    kWeaveColumns = 11,
};

enum class LightningSlowOp : std::uint8_t {
    kRotateRight = 0,
    kRotateLeft = 1,
    kFlipHorizontal = 2,
    kFlipVertical = 3,
    kTranspose = 4,
    kFlipDiagB = 5,
    kRotateRing = 6,
};

class LightningMatrix final {
public:
    static constexpr std::size_t kWidth = 4;
    static constexpr std::size_t kHeight = 4;
    static constexpr std::size_t kSize = 16;
    
    LightningMatrix();
    explicit LightningMatrix(const std::uint8_t* bytes);
    
    std::uint8_t* Data();
    const std::uint8_t* Data() const;
    
    void Clear();
    void Fill(std::uint8_t value);
    void Load(const std::uint8_t* bytes);
    void Store(std::uint8_t* bytes) const;
    
    std::uint8_t& At(std::size_t row, std::size_t column);
    std::uint8_t At(std::size_t row, std::size_t column) const;
    
    void RotateRowLeft(std::size_t row, unsigned amount);
    void RotateRowRight(std::size_t row, unsigned amount);
    void RotateColumnUp(std::size_t column, unsigned amount);
    void RotateColumnDown(std::size_t column, unsigned amount);
    void SwapRows(std::size_t row_a, std::size_t row_b);
    void SwapColumns(std::size_t column_a, std::size_t column_b);
    
    // Missing WeaveRowsOdd, WeaveRowsEven
    // Missing WeaveColumnsOdd, WeaveColumnsEven
    void WeaveRows(std::size_t row_a, std::size_t row_b);
    void WeaveColumns(std::size_t column_a, std::size_t column_b);
    
    // Missing "Roll Right"
    void RotateRight();
    void RotateLeft();
    void FlipHorizontal();
    void FlipVertical();
    void Transpose();
    
    // Missing FlipDiagA
    void FlipDiagB();
    
    //rrrr
    //raar
    //raar
    //rrrr
    void RotateRing(unsigned amount);
    
    
    void ApplyFastOp(LightningFastOp op, std::uint8_t arg0, std::uint8_t arg1);
    void ApplySlowOp(LightningSlowOp op, std::uint8_t arg0, std::uint8_t arg1);
    
private:
    static std::size_t NormalizeIndex(std::size_t value);
    static unsigned NormalizeAmount(unsigned value);
    std::size_t Offset(std::size_t row, std::size_t column) const;
    
    std::array<std::uint8_t, kSize> data_{};
};
