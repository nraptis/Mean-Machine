#pragma once

#include "TwistExpander.hpp"

class TwistExpander_Achernar_Arx {
public:
    static void KDF_A_A(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_A_B(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_A_C(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_A_D(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_B_A(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_B_B(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_B_C(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_B_D(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_C_A(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_C_B(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_C_C(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_C_D(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_D_A(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_D_B(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_D_C(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void KDF_D_D(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     MUTABLE_PARAMS);
    static void SEED_A(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_B(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_C(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_D(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_E(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_F(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_G(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_H(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_I(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_J(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_K(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_L(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_M(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void SEED_N(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void KEY(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     MUTABLE_PARAMS);
    static void Twist_A(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint8_t *pSnowLaneA,
                     std::uint8_t *pSnowLaneB,
                     std::uint8_t *pSnowLaneC,
                     std::uint8_t *pSnowLaneD,
                     MUTABLE_PARAMS);
    static void Twist_B(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint8_t *pSnowLaneA,
                     std::uint8_t *pSnowLaneB,
                     std::uint8_t *pSnowLaneC,
                     std::uint8_t *pSnowLaneD,
                     MUTABLE_PARAMS);
    static void Twist_C(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint8_t *pSnowLaneA,
                     std::uint8_t *pSnowLaneB,
                     std::uint8_t *pSnowLaneC,
                     std::uint8_t *pSnowLaneD,
                     MUTABLE_PARAMS);
    static void Twist_D(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint8_t *pSnowLaneA,
                     std::uint8_t *pSnowLaneB,
                     std::uint8_t *pSnowLaneC,
                     std::uint8_t *pSnowLaneD,
                     MUTABLE_PARAMS);
    static void Twist_E(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint8_t *pSnowLaneA,
                     std::uint8_t *pSnowLaneB,
                     std::uint8_t *pSnowLaneC,
                     std::uint8_t *pSnowLaneD,
                     MUTABLE_PARAMS);
    static void Twist_F(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint8_t *pSnowLaneA,
                     std::uint8_t *pSnowLaneB,
                     std::uint8_t *pSnowLaneC,
                     std::uint8_t *pSnowLaneD,
                     MUTABLE_PARAMS);
    static void Twist_G(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint8_t *pSnowLaneA,
                     std::uint8_t *pSnowLaneB,
                     std::uint8_t *pSnowLaneC,
                     std::uint8_t *pSnowLaneD,
                     MUTABLE_PARAMS);
    static void Twist_H(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint8_t *pSnowLaneA,
                     std::uint8_t *pSnowLaneB,
                     std::uint8_t *pSnowLaneC,
                     std::uint8_t *pSnowLaneD,
                     MUTABLE_PARAMS);
    static void GROW_A_A(TwistWorkSpace *pWorkSpace,
                     MUTABLE_PARAMS);
    static void GROW_A_B(TwistWorkSpace *pWorkSpace,
                     MUTABLE_PARAMS);
    static void GROW_A_C(TwistWorkSpace *pWorkSpace,
                     MUTABLE_PARAMS);
    static void GROW_A_D(TwistWorkSpace *pWorkSpace,
                     MUTABLE_PARAMS);
    static void GROW_B_A(TwistWorkSpace *pWorkSpace,
                     MUTABLE_PARAMS);
    static void GROW_B_B(TwistWorkSpace *pWorkSpace,
                     MUTABLE_PARAMS);
    static void GROW_B_C(TwistWorkSpace *pWorkSpace,
                     MUTABLE_PARAMS);
    static void GROW_B_D(TwistWorkSpace *pWorkSpace,
                     MUTABLE_PARAMS);
};
