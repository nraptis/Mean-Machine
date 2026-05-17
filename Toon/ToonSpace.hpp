//
//  ToonSpace.hpp
//  Valhalla
//
//  Created by Dragon on 5/16/26.
//

#ifndef ToonSpace_h
#define ToonSpace_h

#define S_BLOCK 16384 // 4,096 // 2,048

#define S_SBOX 256

#define S_SALT 32
#define S_SALT_DIVIDE_BITSHIFT 5

#define S_BLOCK1 16383
#define S_SBOX1 255
#define S_SALT1 31

#define W_KEY_A 512
#define W_KEY_A1 511
#define H_KEY_A 8
#define S_KEY_A (W_KEY_A * H_KEY_A)

#define W_KEY_B 1024
#define W_KEY_B1 1023
#define H_KEY_B 4
#define S_KEY_B (W_KEY_B * H_KEY_B)

#define W_KEY_C 512
#define W_KEY_C1 511
#define H_KEY_C 8
#define S_KEY_C (W_KEY_C * H_KEY_C)

#define W_KEY_D 1024
#define W_KEY_D1 1023
#define H_KEY_D 4
#define S_KEY_D (W_KEY_D * H_KEY_D)


#include <cstdint>

enum class ToonSpace : std::uint8_t {
    kInvalid = 0,
    kShared = 1,
    kLocalPacked = 2,
    kLocalEphemeral = 3,
};

#endif /* ToonSpace_h */
