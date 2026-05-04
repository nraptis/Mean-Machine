#pragma once

#include <cstdint>
#include <string>

class GoldenDemo {
public:
    enum class LoopMode : std::uint8_t {
        kLoopA = 0,
        kLoopB = 1,
        kLoopC = 2,
        kLoopD = 3
    };

    GoldenDemo();
    ~GoldenDemo();

    GoldenDemo(const GoldenDemo &) = delete;
    GoldenDemo &operator=(const GoldenDemo &) = delete;

    bool                                RollOut(std::uint8_t *pPassword,
                                                 int pPasswordByteLength,
                                                 int pOutputByteLength);

    bool                                RollOut(std::uint8_t *pPassword,
                                                 int pPasswordByteLength,
                                                 int pOutputByteLength,
                                                 LoopMode pLoopMode);

    bool                                ExportByteStream(const std::string &pPath) const;
    bool                                ExportByteStreamProjectRoot(const std::string &pPath) const;

    std::uint8_t                        *mData;
    std::uint8_t                        *mSecureA;
    std::uint8_t                        *mSecureB;
    int                                 mBufferLength;

private:
    bool                                AllocateBuffers(int pLength);
    void                                FreeBuffers();

    bool                                RunBlock(const std::uint8_t *pInputBlock,
                                                  std::uint8_t *pOutputBlock,
                                                  std::uint8_t *pSecureBlockA,
                                                  std::uint8_t *pSecureBlockB,
                                                  LoopMode pLoopMode) const;

    static std::string                  EnsureBinExtension(const std::string &pPath);
};
