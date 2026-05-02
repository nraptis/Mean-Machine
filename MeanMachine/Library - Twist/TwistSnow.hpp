//
//  TwistSnow.hpp
//  MeanMachine
//

#ifndef TwistSnow_hpp
#define TwistSnow_hpp

#include <cstdint>
#include <cstddef>

#include "TwistWorkSpace.hpp"

class TwistSnow {
public:

    static void                         Sha256Counter(std::uint8_t *pSource,
                                                      std::uint8_t *pDest);
    
    static void                         AES256Counter(std::uint8_t *pSource,
                                                      std::uint8_t *pDest);
    
    static void                         ChaCha20Counter(std::uint8_t *pSource,
                                                      std::uint8_t *pDest);
    
    static void                         Aria256Counter(std::uint8_t *pSource,
                                                      std::uint8_t *pDest);
    
    static void                         MurmurHash(std::uint8_t *pSource,
                                                   std::uint8_t *pDest);
    
private:

    static inline std::uint32_t          Load32BE(const std::uint8_t *pData);

    static inline void                   Store32BE(std::uint8_t *pData,
                                                   std::uint32_t pValue);

    static void                          DigestSingleBlockSHA256(const std::uint8_t *pBlock,
                                                                 std::uint8_t *pDest);
};

#endif /* TwistSnow_hpp */
