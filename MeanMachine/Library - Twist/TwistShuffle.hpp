//
//  TwistShuffle.hpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#ifndef TwistShuffle_hpp
#define TwistShuffle_hpp

#include <cstddef>
#include <cstdint>

class TwistShuffle {
public:
    static void                         Execute(std::size_t *pIndexList256,
                                                const std::uint8_t *pBlockSizedEntropySource);

    //
    // Entropy is consumed from (pCeiling - 1) down to pStartIndex.
    // Each function performs at most pMaxIterations full shuffles.
    //
    static void                         ShuffleIndexList256(std::size_t *pIndexList,
                                                            const std::uint8_t *pEntropy,
                                                            std::size_t pStartIndex,
                                                            std::size_t pCeiling,
                                                            std::size_t pMaxIterations);

    static void                         ShufflePointerList2(void **pPointerList,
                                                            const std::uint8_t *pEntropy,
                                                            std::size_t pStartIndex,
                                                            std::size_t pCeiling,
                                                            std::size_t pMaxIterations);

    static void                         ShufflePointerList4(void **pPointerList,
                                                            const std::uint8_t *pEntropy,
                                                            std::size_t pStartIndex,
                                                            std::size_t pCeiling,
                                                            std::size_t pMaxIterations);

    static void                         ShufflePointerList8(void **pPointerList,
                                                            const std::uint8_t *pEntropy,
                                                            std::size_t pStartIndex,
                                                            std::size_t pCeiling,
                                                            std::size_t pMaxIterations);

    static void                         ShufflePointerList16(void **pPointerList,
                                                             const std::uint8_t *pEntropy,
                                                             std::size_t pStartIndex,
                                                             std::size_t pCeiling,
                                                             std::size_t pMaxIterations);

    static void                         ShufflePointerList32(void **pPointerList,
                                                             const std::uint8_t *pEntropy,
                                                             std::size_t pStartIndex,
                                                             std::size_t pCeiling,
                                                             std::size_t pMaxIterations);

    static void                         ShufflePointerList64(void **pPointerList,
                                                             const std::uint8_t *pEntropy,
                                                             std::size_t pStartIndex,
                                                             std::size_t pCeiling,
                                                             std::size_t pMaxIterations);

    static void                         ShufflePointerList128(void **pPointerList,
                                                              const std::uint8_t *pEntropy,
                                                              std::size_t pStartIndex,
                                                              std::size_t pCeiling,
                                                              std::size_t pMaxIterations);
};

#endif /* TwistShuffle_hpp */
