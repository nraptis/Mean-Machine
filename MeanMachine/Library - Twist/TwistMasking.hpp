//
//  TwistMasking.hpp
//  MeanMachine
//
//  Created by Dragon on 5/1/26.
//

#ifndef TwistMasking_hpp
#define TwistMasking_hpp

#include <cstddef>
#include <cstdint>
#include <vector>

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

enum class TwistMaskType : std::uint8_t {
    kInv = 0,
    kBraid = 1,
    kWeave = 2
};

enum class TwistMaskBraidType : std::uint8_t {
    kInv = 0,
    kA = 1, // A forward, B forward
    kB = 2, // A forward, B reverse
    kC = 3  // A reverse, B forward
};

enum class TwistMaskWeaveType : std::uint8_t {
    kInv = 0,
    kA = 1, // A forward, B forward
    kB = 2, // A reverse, B forward
    kC = 3, // A forward, B reverse
    kD = 4  // A reverse, B reverse
};

class TwistMasking {
public:
    
    static std::vector<TwistMaskBraidType> GetAllBraidTypes() {
        return {
            TwistMaskBraidType::kA,
            TwistMaskBraidType::kB,
            TwistMaskBraidType::kC
        };
    }
    
    static std::vector<TwistMaskWeaveType> GetAllWeaveTypes() {
        return {
            TwistMaskWeaveType::kA,
            TwistMaskWeaveType::kB,
            TwistMaskWeaveType::kC,
            TwistMaskWeaveType::kD
        };
    }
    
    static void MaskBraid(TwistMaskBraidType pType,
                          std::uint8_t *pSourceA,
                          std::uint8_t *pSourceB,
                          std::size_t pBufferLength,
                          std::uint8_t *pMask,
                          std::size_t pMaskLength) {
        switch (pType) {
            case TwistMaskBraidType::kA:
                MaskBraidA(pSourceA, pSourceB, pBufferLength, pMask, pMaskLength);
                return;
            case TwistMaskBraidType::kB:
                MaskBraidB(pSourceA, pSourceB, pBufferLength, pMask, pMaskLength);
                return;
            case TwistMaskBraidType::kC:
                MaskBraidC(pSourceA, pSourceB, pBufferLength, pMask, pMaskLength);
                return;
            default:
                return;
        }
    }

    static void MaskWeave(TwistMaskWeaveType pType,
                          std::uint8_t *pSourceA,
                          std::uint8_t *pSourceB,
                          std::uint8_t *pDest,
                          std::size_t pBufferLength,
                          std::uint8_t *pMask,
                          std::size_t pMaskLength) {
        switch (pType) {
            case TwistMaskWeaveType::kA:
                MaskWeaveA(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength);
                return;
            case TwistMaskWeaveType::kB:
                MaskWeaveB(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength);
                return;
            case TwistMaskWeaveType::kC:
                MaskWeaveC(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength);
                return;
            case TwistMaskWeaveType::kD:
                MaskWeaveD(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength);
                return;
            default:
                return;
        }
    }

    // A starts at 0
    // B starts at 0
    // pBufferLength % 64 == 0
    // pMaskLength % 16 == 0
    // (pBufferLength == pMaskLength) != true [it may be, is not guaranteed]
    static void MaskBraidA(std::uint8_t *pSourceA, // bits in A matching the mask are swapped
                           std::uint8_t *pSourceB, // with bits in B matching the mask
                           std::size_t pBufferLength,
                           std::uint8_t *pMask,
                           std::size_t pMaskLength) {
        MaskBraidImpl(pSourceA, pSourceB, pBufferLength, pMask, pMaskLength, false, false);
    }

    // A starts at 0
    // B starts at pBufferLength - 1
    // pBufferLength % 64 == 0
    // pMaskLength % 16 == 0
    // (pBufferLength == pMaskLength) != true [it may be, is not guaranteed]
    static void MaskBraidB(std::uint8_t *pSourceA, // bits in A matching the mask are swapped
                           std::uint8_t *pSourceB, // with bits in B matching the mask
                           std::size_t pBufferLength,
                           std::uint8_t *pMask,
                           std::size_t pMaskLength) {
        MaskBraidImpl(pSourceA, pSourceB, pBufferLength, pMask, pMaskLength, false, true);
    }

    // A starts at pBufferLength - 1
    // B starts at 0
    // pBufferLength % 64 == 0
    // pMaskLength % 16 == 0
    // (pBufferLength == pMaskLength) != true [it may be, is not guaranteed]
    static void MaskBraidC(std::uint8_t *pSourceA, // bits in A matching the mask are swapped
                           std::uint8_t *pSourceB, // with bits in B matching the mask
                           std::size_t pBufferLength,
                           std::uint8_t *pMask,
                           std::size_t pMaskLength) {
        MaskBraidImpl(pSourceA, pSourceB, pBufferLength, pMask, pMaskLength, true, false);
    }

    // A starts at 0
    // B starts at 0
    // pBufferLength % 64 == 0
    // pMaskLength % 16 == 0
    // (pBufferLength == pMaskLength) != true [it may be, is not guaranteed]
    // pDest writes from 0..<pBufferLength
    static void MaskWeaveA(std::uint8_t *pSourceA, // dest = (a & mask) | (b & (~mask))
                           std::uint8_t *pSourceB,
                           std::uint8_t *pDest,
                           std::size_t pBufferLength,
                           std::uint8_t *pMask,
                           std::size_t pMaskLength) {
        MaskWeaveImpl(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength, false, false);
    }

    // A starts at pBufferLength - 1
    // B starts at 0
    // pBufferLength % 64 == 0
    // pMaskLength % 16 == 0
    // (pBufferLength == pMaskLength) != true [it may be, is not guaranteed]
    // pDest writes from 0..<pBufferLength
    static void MaskWeaveB(std::uint8_t *pSourceA, // dest = (a & mask) | (b & (~mask))
                           std::uint8_t *pSourceB,
                           std::uint8_t *pDest,
                           std::size_t pBufferLength,
                           std::uint8_t *pMask,
                           std::size_t pMaskLength) {
        MaskWeaveImpl(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength, true, false);
    }

    // A starts at 0
    // B starts at pBufferLength - 1
    // pBufferLength % 64 == 0
    // pMaskLength % 16 == 0
    // (pBufferLength == pMaskLength) != true [it may be, is not guaranteed]
    // pDest writes from 0..<pBufferLength
    static void MaskWeaveC(std::uint8_t *pSourceA, // dest = (a & mask) | (b & (~mask))
                           std::uint8_t *pSourceB,
                           std::uint8_t *pDest,
                           std::size_t pBufferLength,
                           std::uint8_t *pMask,
                           std::size_t pMaskLength) {
        MaskWeaveImpl(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength, false, true);
    }

    // A starts at pBufferLength - 1
    // B starts at pBufferLength - 1
    // pBufferLength % 64 == 0
    // pMaskLength % 16 == 0
    // (pBufferLength == pMaskLength) != true [it may be, is not guaranteed]
    // pDest writes from 0..<pBufferLength
    static void MaskWeaveD(std::uint8_t *pSourceA, // dest = (a & mask) | (b & (~mask))
                           std::uint8_t *pSourceB,
                           std::uint8_t *pDest,
                           std::size_t pBufferLength,
                           std::uint8_t *pMask,
                           std::size_t pMaskLength) {
        MaskWeaveImpl(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength, true, true);
    }

private:
    static bool IsValidArgs(const std::uint8_t *pSourceA,
                            const std::uint8_t *pSourceB,
                            const std::uint8_t *pMask,
                            std::size_t pBufferLength,
                            std::size_t pMaskLength) {
        return (pSourceA != nullptr) &&
               (pSourceB != nullptr) &&
               (pMask != nullptr) &&
               (pBufferLength > 0U) &&
               (pMaskLength > 0U);
    }

    static void MaskBraidSoft(std::uint8_t *pSourceA,
                              std::uint8_t *pSourceB,
                              std::size_t pBufferLength,
                              const std::uint8_t *pMask,
                              std::size_t pMaskLength,
                              const bool pReverseA,
                              const bool pReverseB) {
        std::uint8_t *aPtrA = pReverseA ? (pSourceA + (pBufferLength - 1U)) : pSourceA;
        std::uint8_t *aPtrB = pReverseB ? (pSourceB + (pBufferLength - 1U)) : pSourceB;
        const std::ptrdiff_t aStepA = pReverseA ? -1 : 1;
        const std::ptrdiff_t aStepB = pReverseB ? -1 : 1;

        std::size_t aMaskIndex = 0U;
        const std::uint8_t *aMaskPtr = pMask;

        for (std::size_t aIndex = 0U; aIndex < pBufferLength; ++aIndex) {
            const std::uint8_t aMask = *aMaskPtr;
            const std::uint8_t aA = *aPtrA;
            const std::uint8_t aB = *aPtrB;

            *aPtrA = static_cast<std::uint8_t>((aA & static_cast<std::uint8_t>(~aMask)) | (aB & aMask));
            *aPtrB = static_cast<std::uint8_t>((aB & static_cast<std::uint8_t>(~aMask)) | (aA & aMask));

            aPtrA += aStepA;
            aPtrB += aStepB;

            ++aMaskIndex;
            if (aMaskIndex == pMaskLength) {
                aMaskIndex = 0U;
                aMaskPtr = pMask;
            } else {
                ++aMaskPtr;
            }
        }
    }

    static void MaskWeaveSoft(const std::uint8_t *pSourceA,
                              const std::uint8_t *pSourceB,
                              std::uint8_t *pDest,
                              std::size_t pBufferLength,
                              const std::uint8_t *pMask,
                              std::size_t pMaskLength,
                              const bool pReverseA,
                              const bool pReverseB) {
        const std::uint8_t *aPtrA = pReverseA ? (pSourceA + (pBufferLength - 1U)) : pSourceA;
        const std::uint8_t *aPtrB = pReverseB ? (pSourceB + (pBufferLength - 1U)) : pSourceB;
        const std::ptrdiff_t aStepA = pReverseA ? -1 : 1;
        const std::ptrdiff_t aStepB = pReverseB ? -1 : 1;

        std::size_t aMaskIndex = 0U;
        const std::uint8_t *aMaskPtr = pMask;

        for (std::size_t aIndex = 0U; aIndex < pBufferLength; ++aIndex) {
            const std::uint8_t aMask = *aMaskPtr;
            const std::uint8_t aA = *aPtrA;
            const std::uint8_t aB = *aPtrB;
            pDest[aIndex] = static_cast<std::uint8_t>((aA & aMask) | (aB & static_cast<std::uint8_t>(~aMask)));

            aPtrA += aStepA;
            aPtrB += aStepB;

            ++aMaskIndex;
            if (aMaskIndex == pMaskLength) {
                aMaskIndex = 0U;
                aMaskPtr = pMask;
            } else {
                ++aMaskPtr;
            }
        }
    }

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
    static void MaskBraidNeon(std::uint8_t *pSourceA,
                              std::uint8_t *pSourceB,
                              std::size_t pBufferLength,
                              const std::uint8_t *pMask,
                              std::size_t pMaskLength,
                              const bool pReverseA,
                              const bool pReverseB) {
        std::uint8_t *aBlockPtrA = pReverseA ? (pSourceA + (pBufferLength - 16U)) : pSourceA;
        std::uint8_t *aBlockPtrB = pReverseB ? (pSourceB + (pBufferLength - 16U)) : pSourceB;
        const std::ptrdiff_t aBlockStepA = pReverseA ? -16 : 16;
        const std::ptrdiff_t aBlockStepB = pReverseB ? -16 : 16;
        std::size_t aMaskIndex = 0U;

        const std::size_t aBlockCount = pBufferLength / 16U;
        for (std::size_t aBlock = 0U; aBlock < aBlockCount; ++aBlock) {
            const uint8x16_t vA = vld1q_u8(aBlockPtrA);
            const uint8x16_t vB = vld1q_u8(aBlockPtrB);
            const uint8x16_t vMask = vld1q_u8(pMask + aMaskIndex);

            const uint8x16_t vOutA = vbslq_u8(vMask, vB, vA);
            const uint8x16_t vOutB = vbslq_u8(vMask, vA, vB);

            vst1q_u8(aBlockPtrA, vOutA);
            vst1q_u8(aBlockPtrB, vOutB);

            aBlockPtrA += aBlockStepA;
            aBlockPtrB += aBlockStepB;

            aMaskIndex += 16U;
            if (aMaskIndex == pMaskLength) {
                aMaskIndex = 0U;
            }
        }
    }

    static void MaskWeaveNeon(const std::uint8_t *pSourceA,
                              const std::uint8_t *pSourceB,
                              std::uint8_t *pDest,
                              std::size_t pBufferLength,
                              const std::uint8_t *pMask,
                              std::size_t pMaskLength,
                              const bool pReverseA,
                              const bool pReverseB) {
        const std::uint8_t *aBlockPtrA = pReverseA ? (pSourceA + (pBufferLength - 16U)) : pSourceA;
        const std::uint8_t *aBlockPtrB = pReverseB ? (pSourceB + (pBufferLength - 16U)) : pSourceB;
        const std::ptrdiff_t aBlockStepA = pReverseA ? -16 : 16;
        const std::ptrdiff_t aBlockStepB = pReverseB ? -16 : 16;
        std::size_t aMaskIndex = 0U;

        const std::size_t aBlockCount = pBufferLength / 16U;
        for (std::size_t aBlock = 0U; aBlock < aBlockCount; ++aBlock) {
            const uint8x16_t vA = vld1q_u8(aBlockPtrA);
            const uint8x16_t vB = vld1q_u8(aBlockPtrB);
            const uint8x16_t vMask = vld1q_u8(pMask + aMaskIndex);
            const uint8x16_t vOut = vbslq_u8(vMask, vA, vB);
            vst1q_u8(pDest, vOut);

            pDest += 16U;
            aBlockPtrA += aBlockStepA;
            aBlockPtrB += aBlockStepB;

            aMaskIndex += 16U;
            if (aMaskIndex == pMaskLength) {
                aMaskIndex = 0U;
            }
        }
    }
#endif

    static void MaskBraidImpl(std::uint8_t *pSourceA,
                              std::uint8_t *pSourceB,
                              std::size_t pBufferLength,
                              std::uint8_t *pMask,
                              std::size_t pMaskLength,
                              const bool pReverseA,
                              const bool pReverseB) {
        if (!IsValidArgs(pSourceA, pSourceB, pMask, pBufferLength, pMaskLength)) {
            return;
        }
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        MaskBraidNeon(pSourceA, pSourceB, pBufferLength, pMask, pMaskLength, pReverseA, pReverseB);
#else
        MaskBraidSoft(pSourceA, pSourceB, pBufferLength, pMask, pMaskLength, pReverseA, pReverseB);
#endif
    }

    static void MaskWeaveImpl(std::uint8_t *pSourceA,
                              std::uint8_t *pSourceB,
                              std::uint8_t *pDest,
                              std::size_t pBufferLength,
                              std::uint8_t *pMask,
                              std::size_t pMaskLength,
                              const bool pReverseA,
                              const bool pReverseB) {
        if ((pDest == nullptr) || !IsValidArgs(pSourceA, pSourceB, pMask, pBufferLength, pMaskLength)) {
            return;
        }
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        MaskWeaveNeon(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength, pReverseA, pReverseB);
#else
        MaskWeaveSoft(pSourceA, pSourceB, pDest, pBufferLength, pMask, pMaskLength, pReverseA, pReverseB);
#endif
    }
};

#endif /* TwistMasking_hpp */
