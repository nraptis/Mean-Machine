#include "TwistExpander_Achernar.hpp"
#include "TwistDiffuse.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix32.hpp"
#include "TwistMix64.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmConstants.hpp"
#include "TwistSquash.hpp"
#include "TwistShiftBox.hpp"

#include <cstdint>
#include <cstring>

TwistExpander_Achernar::TwistExpander_Achernar()
: TwistExpander() {
    mDomainBundleInbuilt.mKeyRotateASalts = kKeyRotateASalts;
    mDomainBundleInbuilt.mKeyRotateAConstants = kKeyRotateAConstants;
    mDomainBundleInbuilt.mKeyRotateBSalts = kKeyRotateBSalts;
    mDomainBundleInbuilt.mKeyRotateBConstants = kKeyRotateBConstants;
    mDomainBundleInbuilt.mKeySpawnASalts = kKeySpawnASalts;
    mDomainBundleInbuilt.mKeySpawnAConstants = kKeySpawnAConstants;
    mDomainBundleInbuilt.mKeySpawnBSalts = kKeySpawnBSalts;
    mDomainBundleInbuilt.mKeySpawnBConstants = kKeySpawnBConstants;
    mDomainBundleInbuilt.mSeedSalts = kSeedSalts;
    mDomainBundleInbuilt.mSeedConstants = kSeedConstants;
    mDomainBundleInbuilt.mTwistSalts = kTwistSalts;
    mDomainBundleInbuilt.mTwistConstants = kTwistConstants;
    mDomainBundleEphemeral.Zero();
}

void TwistExpander_Achernar::KDF_A(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               std::uint8_t *pSnowLaneA,
               std::uint8_t *pSnowLaneB,
               std::uint8_t *pSnowLaneC,
               MUTABLE_PARAMS) {
    TwistExpander::KDF_A(pWorkSpace, pNonce, pConstants, pDomainSaltSet,
                        pSnowLaneA, pSnowLaneB, pSnowLaneC,
                        pPrevious, pIngress, pCarry,
                        pWandererA, pWandererB, pWandererC, pWandererD,
                        pWandererE, pWandererF, pWandererG, pWandererH,
                        pWandererI, pWandererJ, pWandererK);
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr) ||
        (pSnowLaneA == nullptr) || (pSnowLaneB == nullptr) ||
        (pSnowLaneC == nullptr) || (pPrevious == nullptr) ||
        (pIngress == nullptr) || (pCarry == nullptr) ||
        (pWandererA == nullptr) || (pWandererB == nullptr) ||
        (pWandererC == nullptr) || (pWandererD == nullptr) ||
        (pWandererE == nullptr) || (pWandererF == nullptr) ||
        (pWandererG == nullptr) || (pWandererH == nullptr) ||
        (pWandererI == nullptr) || (pWandererJ == nullptr) ||
        (pWandererK == nullptr)) { return; }
    std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint8_t *aWaterLaneA = pWorkSpace->mWaterLaneA;
    std::uint8_t *aWaterLaneB = pWorkSpace->mWaterLaneB;
    std::uint8_t *aWaterLaneC = pWorkSpace->mWaterLaneC;
    std::uint8_t *aWaterLaneD = pWorkSpace->mWaterLaneD;
    std::uint8_t *aWindLaneA = pWorkSpace->mWindLaneA;
    std::uint8_t *aWindLaneB = pWorkSpace->mWindLaneB;
    std::uint8_t *aWindLaneC = pWorkSpace->mWindLaneC;
    std::uint8_t *aWindLaneD = pWorkSpace->mWindLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
    TwistExpander_Achernar_Arx::KDF_A_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::KDF_A_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::KDF_A_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aWaterLaneA, aWaterLaneB,
                         aWaterLaneC, aWaterLaneD, // output lanes
                         aFireLaneC, aFireLaneD, aWindLaneC, aWindLaneD, // index shuffle seeds
                         aWindLaneA, aWindLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Achernar_Arx::KDF_A_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

}

void TwistExpander_Achernar::KDF_B(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               std::uint8_t *pSnowLaneA,
               std::uint8_t *pSnowLaneB,
               std::uint8_t *pSnowLaneC,
               MUTABLE_PARAMS) {
    TwistExpander::KDF_B(pWorkSpace, pNonce, pConstants, pDomainSaltSet,
                        pSnowLaneA, pSnowLaneB, pSnowLaneC,
                        pPrevious, pIngress, pCarry,
                        pWandererA, pWandererB, pWandererC, pWandererD,
                        pWandererE, pWandererF, pWandererG, pWandererH,
                        pWandererI, pWandererJ, pWandererK);
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr) ||
        (pSnowLaneA == nullptr) || (pSnowLaneB == nullptr) ||
        (pSnowLaneC == nullptr) || (pPrevious == nullptr) ||
        (pIngress == nullptr) || (pCarry == nullptr) ||
        (pWandererA == nullptr) || (pWandererB == nullptr) ||
        (pWandererC == nullptr) || (pWandererD == nullptr) ||
        (pWandererE == nullptr) || (pWandererF == nullptr) ||
        (pWandererG == nullptr) || (pWandererH == nullptr) ||
        (pWandererI == nullptr) || (pWandererJ == nullptr) ||
        (pWandererK == nullptr)) { return; }
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::uint8_t *aLightningLaneA = pWorkSpace->mLightningLaneA;
    std::uint8_t *aLightningLaneB = pWorkSpace->mLightningLaneB;
    std::uint8_t *aLightningLaneC = pWorkSpace->mLightningLaneC;
    std::uint8_t *aLightningLaneD = pWorkSpace->mLightningLaneD;
    std::uint8_t *aSoilLaneC = pWorkSpace->mSoilLaneC;
    std::uint8_t *aSoilLaneD = pWorkSpace->mSoilLaneD;
    std::uint8_t *aIceLaneA = pWorkSpace->mIceLaneA;
    std::uint8_t *aIceLaneB = pWorkSpace->mIceLaneB;
    std::uint8_t *aIceLaneC = pWorkSpace->mIceLaneC;
    std::uint8_t *aIceLaneD = pWorkSpace->mIceLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
    TwistExpander_Achernar_Arx::KDF_B_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::KDF_B_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::KDF_B_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aIceLaneA, aIceLaneB,
                         aIceLaneC, aIceLaneD, // output lanes
                         aSoilLaneC, aSoilLaneD, aLightningLaneC, aLightningLaneD, // index shuffle seeds
                         aLightningLaneA, aLightningLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Achernar_Arx::KDF_B_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

}

void TwistExpander_Achernar::KDF_C(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               std::uint8_t *pSnowLaneA,
               std::uint8_t *pSnowLaneB,
               std::uint8_t *pSnowLaneC,
               MUTABLE_PARAMS) {
    TwistExpander::KDF_C(pWorkSpace, pNonce, pConstants, pDomainSaltSet,
                        pSnowLaneA, pSnowLaneB, pSnowLaneC,
                        pPrevious, pIngress, pCarry,
                        pWandererA, pWandererB, pWandererC, pWandererD,
                        pWandererE, pWandererF, pWandererG, pWandererH,
                        pWandererI, pWandererJ, pWandererK);
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr) ||
        (pSnowLaneA == nullptr) || (pSnowLaneB == nullptr) ||
        (pSnowLaneC == nullptr) || (pPrevious == nullptr) ||
        (pIngress == nullptr) || (pCarry == nullptr) ||
        (pWandererA == nullptr) || (pWandererB == nullptr) ||
        (pWandererC == nullptr) || (pWandererD == nullptr) ||
        (pWandererE == nullptr) || (pWandererF == nullptr) ||
        (pWandererG == nullptr) || (pWandererH == nullptr) ||
        (pWandererI == nullptr) || (pWandererJ == nullptr) ||
        (pWandererK == nullptr)) { return; }
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::uint8_t *aMagmaLaneC = pWorkSpace->mMagmaLaneC;
    std::uint8_t *aMagmaLaneD = pWorkSpace->mMagmaLaneD;
    std::uint8_t *aPlasmaLaneA = pWorkSpace->mPlasmaLaneA;
    std::uint8_t *aPlasmaLaneB = pWorkSpace->mPlasmaLaneB;
    std::uint8_t *aPlasmaLaneC = pWorkSpace->mPlasmaLaneC;
    std::uint8_t *aPlasmaLaneD = pWorkSpace->mPlasmaLaneD;
    std::uint8_t *aShadowLaneA = pWorkSpace->mShadowLaneA;
    std::uint8_t *aShadowLaneB = pWorkSpace->mShadowLaneB;
    std::uint8_t *aShadowLaneC = pWorkSpace->mShadowLaneC;
    std::uint8_t *aShadowLaneD = pWorkSpace->mShadowLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;

    // [kdf-c]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
    TwistExpander_Achernar_Arx::KDF_C_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::KDF_C_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::KDF_C_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aShadowLaneA, aShadowLaneB,
                         aShadowLaneC, aShadowLaneD, // output lanes
                         aMagmaLaneC, aMagmaLaneD, aPlasmaLaneC, aPlasmaLaneD, // index shuffle seeds
                         aPlasmaLaneA, aPlasmaLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Achernar_Arx::KDF_C_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

}

void TwistExpander_Achernar::KDF_D(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               std::uint8_t *pSnowLaneA,
               std::uint8_t *pSnowLaneB,
               std::uint8_t *pSnowLaneC,
               MUTABLE_PARAMS) {
    TwistExpander::KDF_D(pWorkSpace, pNonce, pConstants, pDomainSaltSet,
                        pSnowLaneA, pSnowLaneB, pSnowLaneC,
                        pPrevious, pIngress, pCarry,
                        pWandererA, pWandererB, pWandererC, pWandererD,
                        pWandererE, pWandererF, pWandererG, pWandererH,
                        pWandererI, pWandererJ, pWandererK);
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr) ||
        (pSnowLaneA == nullptr) || (pSnowLaneB == nullptr) ||
        (pSnowLaneC == nullptr) || (pPrevious == nullptr) ||
        (pIngress == nullptr) || (pCarry == nullptr) ||
        (pWandererA == nullptr) || (pWandererB == nullptr) ||
        (pWandererC == nullptr) || (pWandererD == nullptr) ||
        (pWandererE == nullptr) || (pWandererF == nullptr) ||
        (pWandererG == nullptr) || (pWandererH == nullptr) ||
        (pWandererI == nullptr) || (pWandererJ == nullptr) ||
        (pWandererK == nullptr)) { return; }
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::uint8_t *aAetherLaneC = pWorkSpace->mAetherLaneC;
    std::uint8_t *aAetherLaneD = pWorkSpace->mAetherLaneD;
    std::uint8_t *aCelestialLaneA = pWorkSpace->mCelestialLaneA;
    std::uint8_t *aCelestialLaneB = pWorkSpace->mCelestialLaneB;
    std::uint8_t *aCelestialLaneC = pWorkSpace->mCelestialLaneC;
    std::uint8_t *aCelestialLaneD = pWorkSpace->mCelestialLaneD;
    std::uint8_t *aVaporLaneA = pWorkSpace->mVaporLaneA;
    std::uint8_t *aVaporLaneB = pWorkSpace->mVaporLaneB;
    std::uint8_t *aVaporLaneC = pWorkSpace->mVaporLaneC;
    std::uint8_t *aVaporLaneD = pWorkSpace->mVaporLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;

    // [kdf-d]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
    TwistExpander_Achernar_Arx::KDF_D_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::KDF_D_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::KDF_D_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aVaporLaneA, aVaporLaneB,
                         aVaporLaneC, aVaporLaneD, // output lanes
                         aAetherLaneC, aAetherLaneD, aCelestialLaneC, aCelestialLaneD, // index shuffle seeds
                         aCelestialLaneA, aCelestialLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Achernar_Arx::KDF_D_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnowLaneA,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

}

void TwistExpander_Achernar::Seed(TwistWorkSpace *pWorkSpace,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint64_t pNonce,
                                 std::uint8_t *pPassword,
                                 std::size_t pPasswordByteLength,
                                 std::uint8_t *pSnowLaneA,
                                 std::uint8_t *pSnowLaneB,
                                 std::uint8_t *pSnowLaneC,
                                 std::uint8_t *pSnowLaneD,
                                 std::uint8_t *pDestination) {
    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr) ||
        (pSnowLaneA == nullptr) || (pSnowLaneB == nullptr) ||
        (pSnowLaneC == nullptr) || (pSnowLaneD == nullptr) ||
        (pDestination == nullptr)) { return; }

    UnrollPasswordToSource(pWorkSpace->mSource, pPassword, pPasswordByteLength);
    mDomainBundleInbuilt.mKeyRotateASalts = kKeyRotateASalts;
    mDomainBundleInbuilt.mKeyRotateAConstants = kKeyRotateAConstants;
    mDomainBundleInbuilt.mKeyRotateBSalts = kKeyRotateBSalts;
    mDomainBundleInbuilt.mKeyRotateBConstants = kKeyRotateBConstants;
    mDomainBundleInbuilt.mKeySpawnASalts = kKeySpawnASalts;
    mDomainBundleInbuilt.mKeySpawnAConstants = kKeySpawnAConstants;
    mDomainBundleInbuilt.mKeySpawnBSalts = kKeySpawnBSalts;
    mDomainBundleInbuilt.mKeySpawnBConstants = kKeySpawnBConstants;
    mDomainBundleInbuilt.mSeedSalts = kSeedSalts;
    mDomainBundleInbuilt.mSeedConstants = kSeedConstants;
    mDomainBundleInbuilt.mTwistSalts = kTwistSalts;
    mDomainBundleInbuilt.mTwistConstants = kTwistConstants;
    mDomainBundleEphemeral.Zero();
    pWorkSpace->mDomainBundle.Zero();
    std::uint8_t *aHeartLaneA = pWorkSpace->mHeartLaneA;
    std::uint8_t *aHeartLaneB = pWorkSpace->mHeartLaneB;
    std::uint8_t *aHeartLaneC = pWorkSpace->mHeartLaneC;
    std::uint8_t *aHeartLaneD = pWorkSpace->mHeartLaneD;
    std::uint8_t *aPoisonLaneA = pWorkSpace->mPoisonLaneA;
    std::uint8_t *aPoisonLaneB = pWorkSpace->mPoisonLaneB;
    std::uint8_t *aPoisonLaneC = pWorkSpace->mPoisonLaneC;
    std::uint8_t *aPoisonLaneD = pWorkSpace->mPoisonLaneD;
    std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint8_t *aEarthLaneA = pWorkSpace->mEarthLaneA;
    std::uint8_t *aEarthLaneB = pWorkSpace->mEarthLaneB;
    std::uint8_t *aEarthLaneC = pWorkSpace->mEarthLaneC;
    std::uint8_t *aEarthLaneD = pWorkSpace->mEarthLaneD;
    std::uint8_t *aWindLaneA = pWorkSpace->mWindLaneA;
    std::uint8_t *aWindLaneB = pWorkSpace->mWindLaneB;
    std::uint8_t *aWindLaneC = pWorkSpace->mWindLaneC;
    std::uint8_t *aWindLaneD = pWorkSpace->mWindLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::uint8_t *aWoodLaneA = pWorkSpace->mWoodLaneA;
    std::uint8_t *aWoodLaneB = pWorkSpace->mWoodLaneB;
    std::uint8_t *aWoodLaneC = pWorkSpace->mWoodLaneC;
    std::uint8_t *aWoodLaneD = pWorkSpace->mWoodLaneD;
    std::uint8_t *aLightningLaneC = pWorkSpace->mLightningLaneC;
    std::uint8_t *aLightningLaneD = pWorkSpace->mLightningLaneD;
    std::uint8_t *aMagmaLaneA = pWorkSpace->mMagmaLaneA;
    std::uint8_t *aMagmaLaneB = pWorkSpace->mMagmaLaneB;
    std::uint8_t *aMagmaLaneC = pWorkSpace->mMagmaLaneC;
    std::uint8_t *aMagmaLaneD = pWorkSpace->mMagmaLaneD;
    std::uint8_t *aPlasmaLaneC = pWorkSpace->mPlasmaLaneC;
    std::uint8_t *aPlasmaLaneD = pWorkSpace->mPlasmaLaneD;
    std::uint8_t *aCrystalLaneA = pWorkSpace->mCrystalLaneA;
    std::uint8_t *aCrystalLaneB = pWorkSpace->mCrystalLaneB;
    std::uint8_t *aCrystalLaneC = pWorkSpace->mCrystalLaneC;
    std::uint8_t *aCrystalLaneD = pWorkSpace->mCrystalLaneD;
    std::uint8_t *aAetherLaneC = pWorkSpace->mAetherLaneC;
    std::uint8_t *aAetherLaneD = pWorkSpace->mAetherLaneD;
    std::uint8_t *aCelestialLaneA = pWorkSpace->mCelestialLaneA;
    std::uint8_t *aCelestialLaneB = pWorkSpace->mCelestialLaneB;
    std::uint8_t *aCelestialLaneC = pWorkSpace->mCelestialLaneC;
    std::uint8_t *aCelestialLaneD = pWorkSpace->mCelestialLaneD;
    std::uint8_t *aIceLaneA = pWorkSpace->mIceLaneA;
    std::uint8_t *aIceLaneB = pWorkSpace->mIceLaneB;
    std::uint8_t *aIceLaneC = pWorkSpace->mIceLaneC;
    std::uint8_t *aIceLaneD = pWorkSpace->mIceLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xA8AC9C5C8F318A60ULL;
    std::uint64_t aIngress = 0xE96F11016EE48697ULL;
    std::uint64_t aCarry = 0xF26F983778627CECULL;

    std::uint64_t aWandererA = 0xFDD168B7B6D43BA2ULL;
    std::uint64_t aWandererB = 0xDE179C9B1D477C4EULL;
    std::uint64_t aWandererC = 0xB98C7191ADAF807CULL;
    std::uint64_t aWandererD = 0xD05AF556929B7B9BULL;
    std::uint64_t aWandererE = 0x96AC18DF3BE530F3ULL;
    std::uint64_t aWandererF = 0xF935C586B4A9CDD7ULL;
    std::uint64_t aWandererG = 0xFF8609BE2C30A481ULL;
    std::uint64_t aWandererH = 0x88A9265BDD3CFE68ULL;
    std::uint64_t aWandererI = 0xC5B2F34C1A1692CDULL;
    std::uint64_t aWandererJ = 0xCD50D4A0C91D0A49ULL;
    std::uint64_t aWandererK = 0x9B214DF2C74EF6AFULL;

    // [seed]
    ////////////////////////////////////////////////////////
    ////////        KeyRotate A
    ////////
    // Reset ARX state for KeyRotate A.
    aPrevious = 0xC472132F4792A253ULL;
    aIngress = 0x8F24A057B7E81750ULL;
    aCarry = 0xBBFB790F7DF8BEBBULL;
    aWandererA = 0x8E5453D6B1B1794BULL;
    aWandererB = 0xCC8515DF07D0CD93ULL;
    aWandererC = 0xB62F8E6F36D5BAD9ULL;
    aWandererD = 0xF55B97487AAC0CF0ULL;
    aWandererE = 0x8125E9529357797CULL;
    aWandererF = 0xEDF9910600D6EDC0ULL;
    aWandererG = 0xF1863F408BF483BFULL;
    aWandererH = 0x99CBED9E8CA069A0ULL;
    aWandererI = 0xF77CD36AD34ACF5DULL;
    aWandererJ = 0xB47774B2408FD606ULL;
    aWandererK = 0xE73D8CFE3C389F21ULL;
    KDF_A(pWorkSpace, pNonce, &(mDomainBundleInbuilt.mKeyRotateAConstants), &(mDomainBundleInbuilt.mKeyRotateASalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    pFarmSalt->Derive(aHeartLaneA, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aHeartLaneB, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aHeartLaneC, mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltF);
    ////////
    TwistFarmConstants::Derive(aHeartLaneD, &(mDomainBundleEphemeral.mKeyRotateAConstants));
    ////////
    KDF_B(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeyRotateAConstants), &(mDomainBundleEphemeral.mKeyRotateASalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // wood lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aWoodLaneA, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWoodLaneB, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWoodLaneC, pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWoodLaneD, &(pWorkSpace->mDomainBundle.mKeyRotateAConstants));
    ////////
    KDF_C(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeyRotateAConstants), &(mDomainBundleEphemeral.mKeyRotateASalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // crystal lanes to mDomainBundleEphemeral
    pFarmSalt->Derive(aCrystalLaneA, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aCrystalLaneB, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aCrystalLaneC, mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aCrystalLaneD, &(mDomainBundleEphemeral.mKeyRotateAConstants));
    ////////
    KDF_D(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeyRotateAConstants), &(mDomainBundleEphemeral.mKeyRotateASalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // poison lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aPoisonLaneA, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aPoisonLaneB, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aPoisonLaneC, pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aPoisonLaneD, &(pWorkSpace->mDomainBundle.mKeyRotateAConstants));
    ////////
    TwistSquash::SquashC(aPoisonLaneA, aPoisonLaneB, aPoisonLaneC, aPoisonLaneD, pWorkSpace->mDomainLaneKeyRotateA);
    ////////
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        KeyRotate B
    ////////
    // Reset ARX state for KeyRotate B.
    aPrevious = 0xBE17510693BB02EBULL;
    aIngress = 0x82D95DDA631373C3ULL;
    aCarry = 0x8C5C13FB3503D486ULL;
    aWandererA = 0x9D4973BE52BC307FULL;
    aWandererB = 0xD8B22EDDC354B9F9ULL;
    aWandererC = 0x9E869506958EEA38ULL;
    aWandererD = 0xFF3BAD4363AA4920ULL;
    aWandererE = 0xE9329A228CF5832FULL;
    aWandererF = 0x826650A3B205E936ULL;
    aWandererG = 0x9753B827BF7128BCULL;
    aWandererH = 0xED0EE5E06B63818AULL;
    aWandererI = 0xEF1CD24C0D85CA6BULL;
    aWandererJ = 0xBA6EC6B4EFC4A0DAULL;
    aWandererK = 0x95CBED6C08D79687ULL;
    KDF_A(pWorkSpace, pNonce, &(mDomainBundleInbuilt.mKeyRotateBConstants), &(mDomainBundleInbuilt.mKeyRotateBSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    pFarmSalt->Derive(aHeartLaneA, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aHeartLaneB, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aHeartLaneC, mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltF);
    ////////
    TwistFarmConstants::Derive(aHeartLaneD, &(mDomainBundleEphemeral.mKeyRotateBConstants));
    ////////
    KDF_B(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeyRotateBConstants), &(mDomainBundleEphemeral.mKeyRotateBSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // wood lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aWoodLaneA, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWoodLaneB, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWoodLaneC, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWoodLaneD, &(pWorkSpace->mDomainBundle.mKeyRotateBConstants));
    ////////
    KDF_C(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeyRotateBConstants), &(mDomainBundleEphemeral.mKeyRotateBSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // crystal lanes to mDomainBundleEphemeral
    pFarmSalt->Derive(aCrystalLaneA, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aCrystalLaneB, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aCrystalLaneC, mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeyRotateBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aCrystalLaneD, &(mDomainBundleEphemeral.mKeyRotateBConstants));
    ////////
    KDF_D(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeyRotateBConstants), &(mDomainBundleEphemeral.mKeyRotateBSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // poison lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aPoisonLaneA, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aPoisonLaneB, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aPoisonLaneC, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeyRotateBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aPoisonLaneD, &(pWorkSpace->mDomainBundle.mKeyRotateBConstants));
    ////////
    TwistSquash::SquashA(aPoisonLaneA, aPoisonLaneB, aPoisonLaneC, aPoisonLaneD, pWorkSpace->mDomainLaneKeyRotateB);
    ////////
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        KeySpawn A
    ////////
    // Reset ARX state for KeySpawn A.
    aPrevious = 0xC86FE44E00193B4EULL;
    aIngress = 0x8407CBE8B7646D88ULL;
    aCarry = 0xDB65BB411D050477ULL;
    aWandererA = 0x8E0F02EF30C47725ULL;
    aWandererB = 0xF002E3097414866CULL;
    aWandererC = 0xB299A8B054073399ULL;
    aWandererD = 0x86C15740DB894C2FULL;
    aWandererE = 0xC043799E1610C0B6ULL;
    aWandererF = 0xD57C2C8ADE4D9691ULL;
    aWandererG = 0xFA824DFA57AB0759ULL;
    aWandererH = 0xC24437BA6BB29E53ULL;
    aWandererI = 0xF315141BBEA2AF03ULL;
    aWandererJ = 0xEB68B01F9997A28DULL;
    aWandererK = 0xFB7C105CE5353D79ULL;
    KDF_A(pWorkSpace, pNonce, &(mDomainBundleInbuilt.mKeySpawnAConstants), &(mDomainBundleInbuilt.mKeySpawnASalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    pFarmSalt->Derive(aHeartLaneA, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aHeartLaneB, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aHeartLaneC, mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltF);
    ////////
    TwistFarmConstants::Derive(aHeartLaneD, &(mDomainBundleEphemeral.mKeySpawnAConstants));
    ////////
    KDF_B(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeySpawnAConstants), &(mDomainBundleEphemeral.mKeySpawnASalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // wood lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aWoodLaneA, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWoodLaneB, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWoodLaneC, pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWoodLaneD, &(pWorkSpace->mDomainBundle.mKeySpawnAConstants));
    ////////
    KDF_C(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeySpawnAConstants), &(mDomainBundleEphemeral.mKeySpawnASalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // crystal lanes to mDomainBundleEphemeral
    pFarmSalt->Derive(aCrystalLaneA, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aCrystalLaneB, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aCrystalLaneC, mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aCrystalLaneD, &(mDomainBundleEphemeral.mKeySpawnAConstants));
    ////////
    KDF_D(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeySpawnAConstants), &(mDomainBundleEphemeral.mKeySpawnASalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // poison lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aPoisonLaneA, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aPoisonLaneB, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aPoisonLaneC, pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aPoisonLaneD, &(pWorkSpace->mDomainBundle.mKeySpawnAConstants));
    ////////
    TwistSquash::SquashB(aPoisonLaneA, aPoisonLaneB, aPoisonLaneC, aPoisonLaneD, pWorkSpace->mDomainLaneKeySpawnA);
    ////////
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        KeySpawn B
    ////////
    // Reset ARX state for KeySpawn B.
    aPrevious = 0x8E902C0E52DE2667ULL;
    aIngress = 0xAE984127A23D487CULL;
    aCarry = 0x907C1BDC791DA3D1ULL;
    aWandererA = 0x93A3B96FC47BF9F7ULL;
    aWandererB = 0xA61F31035004CDE7ULL;
    aWandererC = 0xD6335B44C6FEE0EDULL;
    aWandererD = 0xEF86029A9B2605E8ULL;
    aWandererE = 0xF10EE318F7EE458BULL;
    aWandererF = 0xECD61332C1486056ULL;
    aWandererG = 0xE3308FC36086E4CCULL;
    aWandererH = 0x885D744321798ED7ULL;
    aWandererI = 0xEB7BC2BC833D54BBULL;
    aWandererJ = 0x9A635B8F69A33F85ULL;
    aWandererK = 0xE0896ADDAC69DF13ULL;
    KDF_A(pWorkSpace, pNonce, &(mDomainBundleInbuilt.mKeySpawnBConstants), &(mDomainBundleInbuilt.mKeySpawnBSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    pFarmSalt->Derive(aHeartLaneA, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aHeartLaneB, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aHeartLaneC, mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltF);
    ////////
    TwistFarmConstants::Derive(aHeartLaneD, &(mDomainBundleEphemeral.mKeySpawnBConstants));
    ////////
    KDF_B(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeySpawnBConstants), &(mDomainBundleEphemeral.mKeySpawnBSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // wood lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aWoodLaneA, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWoodLaneB, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWoodLaneC, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWoodLaneD, &(pWorkSpace->mDomainBundle.mKeySpawnBConstants));
    ////////
    KDF_C(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeySpawnBConstants), &(mDomainBundleEphemeral.mKeySpawnBSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // crystal lanes to mDomainBundleEphemeral
    pFarmSalt->Derive(aCrystalLaneA, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aCrystalLaneB, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aCrystalLaneC, mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mKeySpawnBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aCrystalLaneD, &(mDomainBundleEphemeral.mKeySpawnBConstants));
    ////////
    KDF_D(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mKeySpawnBConstants), &(mDomainBundleEphemeral.mKeySpawnBSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // poison lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aPoisonLaneA, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aPoisonLaneB, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aPoisonLaneC, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mKeySpawnBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aPoisonLaneD, &(pWorkSpace->mDomainBundle.mKeySpawnBConstants));
    ////////
    TwistSquash::SquashC(aPoisonLaneA, aPoisonLaneB, aPoisonLaneC, aPoisonLaneD, pWorkSpace->mDomainLaneKeySpawnB);
    ////////
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Twist
    ////////
    // Reset ARX state for Twist.
    aPrevious = 0xF29F66223DC46939ULL;
    aIngress = 0xD1AA430F22E6763EULL;
    aCarry = 0xD3A3B51018F2A313ULL;
    aWandererA = 0xC36A508AB66C59A2ULL;
    aWandererB = 0xF98819403B862320ULL;
    aWandererC = 0xF4EA1D1BC6F56A63ULL;
    aWandererD = 0xCDB697DF5CE5E9E8ULL;
    aWandererE = 0xCD35D5120B4AEF34ULL;
    aWandererF = 0xB1E32F30760A8683ULL;
    aWandererG = 0xCAF8D7E8596ABD66ULL;
    aWandererH = 0x9088F0FD373D6852ULL;
    aWandererI = 0xDCD1B4CC026B5BFCULL;
    aWandererJ = 0xF80129BF905CE12CULL;
    aWandererK = 0xEF0F1F6BA51CCAFDULL;
    KDF_A(pWorkSpace, pNonce, &(mDomainBundleInbuilt.mTwistConstants), &(mDomainBundleInbuilt.mTwistSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    pFarmSalt->Derive(aHeartLaneA, mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aHeartLaneB, mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aHeartLaneC, mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltF);
    ////////
    TwistFarmConstants::Derive(aHeartLaneD, &(mDomainBundleEphemeral.mTwistConstants));
    ////////
    KDF_B(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mTwistConstants), &(mDomainBundleEphemeral.mTwistSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // wood lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aWoodLaneA, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWoodLaneB, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWoodLaneC, pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWoodLaneD, &(pWorkSpace->mDomainBundle.mTwistConstants));
    ////////
    KDF_C(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mTwistConstants), &(mDomainBundleEphemeral.mTwistSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // crystal lanes to mDomainBundleEphemeral
    pFarmSalt->Derive(aCrystalLaneA, mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aCrystalLaneB, mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mTwistSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aCrystalLaneC, mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mTwistSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aCrystalLaneD, &(mDomainBundleEphemeral.mTwistConstants));
    ////////
    KDF_D(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mTwistConstants), &(mDomainBundleEphemeral.mTwistSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // poison lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aPoisonLaneA, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aPoisonLaneB, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mTwistSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aPoisonLaneC, pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mTwistSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aPoisonLaneD, &(pWorkSpace->mDomainBundle.mTwistConstants));
    ////////
    TwistSquash::SquashA(aPoisonLaneA, aPoisonLaneB, aPoisonLaneC, aPoisonLaneD, pWorkSpace->mDomainLaneTwist);
    ////////
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Seed
    ////////
    // Reset ARX state for Seed.
    aPrevious = 0xF9B7D79C562D7FFFULL;
    aIngress = 0xCD7CE83A54710DE0ULL;
    aCarry = 0x922D8FAA3DD27ED9ULL;
    aWandererA = 0xBF88D3572DD61222ULL;
    aWandererB = 0xAE116A7800DDD24BULL;
    aWandererC = 0x8C3C7CE81203BCD8ULL;
    aWandererD = 0xF111C17DAC583011ULL;
    aWandererE = 0xCC7D069E4651B587ULL;
    aWandererF = 0xE0E4EF893B2827B3ULL;
    aWandererG = 0x854710A79E321C47ULL;
    aWandererH = 0xF3DC44BCCE227134ULL;
    aWandererI = 0xAD0BAD47A5D19287ULL;
    aWandererJ = 0xAD6CB0C549D1A840ULL;
    aWandererK = 0xB0057330C6E8C1C8ULL;
    KDF_A(pWorkSpace, pNonce, &(mDomainBundleInbuilt.mSeedConstants), &(mDomainBundleInbuilt.mSeedSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    pFarmSalt->Derive(aHeartLaneA, mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aHeartLaneB, mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aHeartLaneC, mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltF);
    ////////
    TwistFarmConstants::Derive(aHeartLaneD, &(mDomainBundleEphemeral.mSeedConstants));
    ////////
    KDF_B(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mSeedConstants), &(mDomainBundleEphemeral.mSeedSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // wood lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aWoodLaneA, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWoodLaneB, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWoodLaneC, pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWoodLaneD, &(pWorkSpace->mDomainBundle.mSeedConstants));
    ////////
    KDF_C(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mSeedConstants), &(mDomainBundleEphemeral.mSeedSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // crystal lanes to mDomainBundleEphemeral
    pFarmSalt->Derive(aCrystalLaneA, mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aCrystalLaneB, mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mSeedSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aCrystalLaneC, mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mSeedSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aCrystalLaneD, &(mDomainBundleEphemeral.mSeedConstants));
    ////////
    KDF_D(pWorkSpace, pNonce, &(mDomainBundleEphemeral.mSeedConstants), &(mDomainBundleEphemeral.mSeedSalts), pSnowLaneA, pSnowLaneB, pSnowLaneC, &aPrevious, &aIngress, &aCarry, &aWandererA, &aWandererB, &aWandererC, &aWandererD, &aWandererE, &aWandererF, &aWandererG, &aWandererH, &aWandererI, &aWandererJ, &aWandererK);
    ////////
    // poison lanes to pWorkSpace->mDomainBundle
    pFarmSalt->Derive(aPoisonLaneA, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aPoisonLaneB, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mSeedSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aPoisonLaneC, pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mSeedSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aPoisonLaneD, &(pWorkSpace->mDomainBundle.mSeedConstants));
    ////////
    TwistSquash::SquashC(aPoisonLaneA, aPoisonLaneB, aPoisonLaneC, aPoisonLaneD, pWorkSpace->mDomainLaneSeed);
    ////////
    ////////
    ////////
    ////////////////////////////////////////////////////////
    // Reset ARX state for Seed stages.
    aPrevious = 0xFBDB1D07B9A0FFF4ULL;
    aIngress = 0xCC6F80B3AC230F67ULL;
    aCarry = 0xBD398318079643D3ULL;
    aWandererA = 0x907E9EC379E01D08ULL;
    aWandererB = 0xAE6A5E974212494EULL;
    aWandererC = 0x8479597F7FAA885AULL;
    aWandererD = 0x9622B1642D1611BAULL;
    aWandererE = 0x8D336B63C02785A8ULL;
    aWandererF = 0xDFC34EE6FB8E35B9ULL;
    aWandererG = 0xA2E62719F87DFE40ULL;
    aWandererH = 0x86ABFC8A76F76C22ULL;
    aWandererI = 0xE11310240A5CA312ULL;
    aWandererJ = 0xD45E607276F49B80ULL;
    aWandererK = 0x95B09F9DB674C5C2ULL;
    TwistExpander_Achernar_Arx::SEED_A(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::SEED_B(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::SEED_C(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mSeedConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mSeedConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mSeedConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mSeedConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mSeedConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mSeedConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mSeedConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mSeedConstants.mMatrixArgD;
    //
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aHeartLaneA, aHeartLaneB,
                         aHeartLaneC, aHeartLaneD, // output lanes
                         aPlasmaLaneC, aPlasmaLaneD, aMagmaLaneC, aMagmaLaneD, // index shuffle seeds
                         aMagmaLaneA, aMagmaLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Achernar_Arx::SEED_D(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::SEED_E(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::SEED_F(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aWindLaneA, aWindLaneB,
                         aWindLaneC, aWindLaneD, // output lanes
                         aCrystalLaneC, aCrystalLaneD, aEarthLaneC, aEarthLaneD, // index shuffle seeds
                         aEarthLaneA, aEarthLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Achernar_Arx::SEED_G(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::SEED_H(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::SEED_I(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aCelestialLaneA, aCelestialLaneB,
                         aCelestialLaneC, aCelestialLaneD, // output lanes
                         aAetherLaneC, aAetherLaneD, aFireLaneC, aFireLaneD, // index shuffle seeds
                         aFireLaneA, aFireLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Achernar_Arx::SEED_J(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::SEED_K(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::SEED_L(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aWoodLaneA, aWoodLaneB,
                         aWoodLaneC, aWoodLaneD, // output lanes
                         aLightningLaneC, aLightningLaneD, aIceLaneC, aIceLaneD, // index shuffle seeds
                         aIceLaneA, aIceLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Achernar_Arx::SEED_M(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::SEED_N(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // [KEY — sixteen key rows, lane splits A-P]
    //
    TwistExpander_Achernar_Arx::KEY(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    FoldSeed(pWorkSpace, pDestination);
    GrowKeyA(pWorkSpace,
             &aPrevious,
             &aIngress,
             &aCarry,
             &aWandererA,
             &aWandererB,
             &aWandererC,
             &aWandererD,
             &aWandererE,
             &aWandererF,
             &aWandererG,
             &aWandererH,
             &aWandererI,
             &aWandererJ,
             &aWandererK);
    GrowKeyB(pWorkSpace,
             &aPrevious,
             &aIngress,
             &aCarry,
             &aWandererA,
             &aWandererB,
             &aWandererC,
             &aWandererD,
             &aWandererE,
             &aWandererF,
             &aWandererG,
             &aWandererH,
             &aWandererI,
             &aWandererJ,
             &aWandererK);
    FoldKeyRows(pWorkSpace);
    pWorkSpace->Zero_PostSeed();
    Zero_PostSeed();
}

void TwistExpander_Achernar::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pSnowLaneA,
                                       std::uint8_t *pSnowLaneB,
                                       std::uint8_t *pSnowLaneC,
                                       std::uint8_t *pSnowLaneD,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace,
                              pSource,
                              pSnowLaneA,
                              pSnowLaneB,
                              pSnowLaneC,
                              pSnowLaneD,
                              pDestination);
    if ((pWorkSpace == nullptr) || (pSource == nullptr) ||
        (pSnowLaneA == nullptr) || (pSnowLaneB == nullptr) ||
        (pSnowLaneC == nullptr) || (pSnowLaneD == nullptr) ||
        (pDestination == nullptr)) { return; }
    std::uint8_t *aHeartLaneA = pWorkSpace->mHeartLaneA;
    std::uint8_t *aHeartLaneB = pWorkSpace->mHeartLaneB;
    std::uint8_t *aHeartLaneC = pWorkSpace->mHeartLaneC;
    std::uint8_t *aHeartLaneD = pWorkSpace->mHeartLaneD;
    std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint8_t *aWaterLaneA = pWorkSpace->mWaterLaneA;
    std::uint8_t *aWaterLaneB = pWorkSpace->mWaterLaneB;
    std::uint8_t *aWaterLaneC = pWorkSpace->mWaterLaneC;
    std::uint8_t *aWaterLaneD = pWorkSpace->mWaterLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::uint8_t *aWoodLaneA = pWorkSpace->mWoodLaneA;
    std::uint8_t *aWoodLaneB = pWorkSpace->mWoodLaneB;
    std::uint8_t *aWoodLaneC = pWorkSpace->mWoodLaneC;
    std::uint8_t *aWoodLaneD = pWorkSpace->mWoodLaneD;
    std::uint8_t *aLightningLaneC = pWorkSpace->mLightningLaneC;
    std::uint8_t *aLightningLaneD = pWorkSpace->mLightningLaneD;
    std::uint8_t *aIceLaneA = pWorkSpace->mIceLaneA;
    std::uint8_t *aIceLaneB = pWorkSpace->mIceLaneB;
    std::uint8_t *aIceLaneC = pWorkSpace->mIceLaneC;
    std::uint8_t *aIceLaneD = pWorkSpace->mIceLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0x9BA311BDBF5C134EULL; std::uint64_t aIngress = 0x91B57BEF9488B670ULL; std::uint64_t aCarry = 0xA298D430D2C64D2CULL;

    std::uint64_t aWandererA = 0xCA62C25D834B5F32ULL; std::uint64_t aWandererB = 0xEE01985C211038D4ULL; std::uint64_t aWandererC = 0xA8B7B85F45CCABB2ULL; std::uint64_t aWandererD = 0xEB2589190E85D521ULL;
    std::uint64_t aWandererE = 0xAC2D31EFEDAF50ABULL; std::uint64_t aWandererF = 0xE040C15C6ABE5E1CULL; std::uint64_t aWandererG = 0xA80E54B7C5703699ULL; std::uint64_t aWandererH = 0xB97F3EE6566E8472ULL;
    std::uint64_t aWandererI = 0xE3734C6645C6723FULL; std::uint64_t aWandererJ = 0xBD900DA0416E63A3ULL; std::uint64_t aWandererK = 0xC71A145547FA2D85ULL;

    // [twist]
        aPrevious = 0xA09A2AF1428616B8ULL;
        aCarry = 0xBB36EE41396AF470ULL;
        aWandererA = 0xADD49B06BD159B06ULL;
        aWandererB = 0xA18EBFCDD7AD98C3ULL;
        aWandererC = 0xD92373DD4E84E9E7ULL;
        aWandererD = 0xE5D5499966663BE6ULL;
        aWandererE = 0xB01AF0F5807F09ECULL;
        aWandererF = 0xE3CCDC1FE8F4B777ULL;
        aWandererG = 0xC391F5EBC645CF7DULL;
        aWandererH = 0xF842BDC022621EA5ULL;
        aWandererI = 0xBE178B5EA1C79D44ULL;
        aWandererJ = 0x8E58A023730C2CC8ULL;
        aWandererK = 0x853685BBB585C1CEULL;
    TwistExpander_Achernar_Arx::Twist_A(pWorkSpace,
                 pSource,
                 pSnowLaneA,
                 pSnowLaneB,
                 pSnowLaneC,
                 pSnowLaneD,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::Twist_B(pWorkSpace,
                 pSource,
                 pSnowLaneA,
                 pSnowLaneB,
                 pSnowLaneC,
                 pSnowLaneD,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::Twist_C(pWorkSpace,
                 pSource,
                 pSnowLaneA,
                 pSnowLaneB,
                 pSnowLaneC,
                 pSnowLaneD,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mTwistConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mTwistConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mTwistConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mTwistConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mTwistConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mTwistConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mTwistConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mTwistConstants.mMatrixArgD;
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aHeartLaneA, aHeartLaneB,
                         aHeartLaneC, aHeartLaneD, // output lanes
                         aFireLaneC, aFireLaneD, aWaterLaneC, aWaterLaneD, // index shuffle seeds
                         aWaterLaneA, aWaterLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    //
    TwistExpander_Achernar_Arx::Twist_D(pWorkSpace,
                 pSource,
                 pSnowLaneA,
                 pSnowLaneB,
                 pSnowLaneC,
                 pSnowLaneD,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::Twist_E(pWorkSpace,
                 pSource,
                 pSnowLaneA,
                 pSnowLaneB,
                 pSnowLaneC,
                 pSnowLaneD,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::Twist_F(pWorkSpace,
                 pSource,
                 pSnowLaneA,
                 pSnowLaneB,
                 pSnowLaneC,
                 pSnowLaneD,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aWoodLaneA, aWoodLaneB,
                         aWoodLaneC, aWoodLaneD, // output lanes
                         aLightningLaneC, aLightningLaneD, aIceLaneC, aIceLaneD, // index shuffle seeds
                         aIceLaneA, aIceLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    //
    TwistExpander_Achernar_Arx::Twist_G(pWorkSpace,
                 pSource,
                 pSnowLaneA,
                 pSnowLaneB,
                 pSnowLaneC,
                 pSnowLaneD,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Achernar_Arx::Twist_H(pWorkSpace,
                 pSource,
                 pSnowLaneA,
                 pSnowLaneB,
                 pSnowLaneC,
                 pSnowLaneD,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    FoldTwist(pWorkSpace, pDestination);
    GrowKeyA(pWorkSpace,
             &aPrevious,
             &aIngress,
             &aCarry,
             &aWandererA,
             &aWandererB,
             &aWandererC,
             &aWandererD,
             &aWandererE,
             &aWandererF,
             &aWandererG,
             &aWandererH,
             &aWandererI,
             &aWandererJ,
             &aWandererK);
    GrowKeyB(pWorkSpace,
             &aPrevious,
             &aIngress,
             &aCarry,
             &aWandererA,
             &aWandererB,
             &aWandererC,
             &aWandererD,
             &aWandererE,
             &aWandererF,
             &aWandererG,
             &aWandererH,
             &aWandererI,
             &aWandererJ,
             &aWandererK);
    FoldKeyRows(pWorkSpace);
}

void TwistExpander_Achernar::GrowKeyA(TwistWorkSpace *pWorkSpace,
                  MUTABLE_PARAMS) {
    TwistExpander::GrowKeyA(pWorkSpace,
             pPrevious,
             pIngress,
             pCarry,
             pWandererA,
             pWandererB,
             pWandererC,
             pWandererD,
             pWandererE,
             pWandererF,
             pWandererG,
             pWandererH,
             pWandererI,
             pWandererJ,
             pWandererK);
    if ((pWorkSpace == nullptr) || (pPrevious == nullptr) ||
        (pIngress == nullptr) || (pCarry == nullptr) ||
        (pWandererA == nullptr) || (pWandererB == nullptr) ||
        (pWandererC == nullptr) || (pWandererD == nullptr) ||
        (pWandererE == nullptr) || (pWandererF == nullptr) ||
        (pWandererG == nullptr) || (pWandererH == nullptr) ||
        (pWandererI == nullptr) || (pWandererJ == nullptr) ||
        (pWandererK == nullptr)) { return; }
    std::uint8_t *aWindLaneA = pWorkSpace->mWindLaneA;
    std::uint8_t *aWindLaneB = pWorkSpace->mWindLaneB;
    std::uint8_t *aWindLaneC = pWorkSpace->mWindLaneC;
    std::uint8_t *aWindLaneD = pWorkSpace->mWindLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::uint8_t *aShadowLaneC = pWorkSpace->mShadowLaneC;
    std::uint8_t *aShadowLaneD = pWorkSpace->mShadowLaneD;
    std::uint8_t *aVaporLaneA = pWorkSpace->mVaporLaneA;
    std::uint8_t *aVaporLaneB = pWorkSpace->mVaporLaneB;
    std::uint8_t *aVaporLaneC = pWorkSpace->mVaporLaneC;
    std::uint8_t *aVaporLaneD = pWorkSpace->mVaporLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;

    // [grow key a]
    TwistExpander_Achernar_Arx::GROW_A_A(pWorkSpace,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::GROW_A_B(pWorkSpace,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::GROW_A_C(pWorkSpace,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    //
    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mKeyRotateAConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mKeyRotateAConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mKeyRotateAConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mKeyRotateAConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mKeyRotateAConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mKeyRotateAConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mKeyRotateAConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mKeyRotateAConstants.mMatrixArgD;
    //
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aVaporLaneA, aVaporLaneB,
                         aVaporLaneC, aVaporLaneD, // output lanes
                         aShadowLaneC, aShadowLaneD, aWindLaneC, aWindLaneD, // index shuffle seeds
                         aWindLaneA, aWindLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    //
    TwistExpander_Achernar_Arx::GROW_A_D(pWorkSpace,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

}

void TwistExpander_Achernar::GrowKeyB(TwistWorkSpace *pWorkSpace,
                  MUTABLE_PARAMS) {
    TwistExpander::GrowKeyB(pWorkSpace,
             pPrevious,
             pIngress,
             pCarry,
             pWandererA,
             pWandererB,
             pWandererC,
             pWandererD,
             pWandererE,
             pWandererF,
             pWandererG,
             pWandererH,
             pWandererI,
             pWandererJ,
             pWandererK);
    if ((pWorkSpace == nullptr) || (pPrevious == nullptr) ||
        (pIngress == nullptr) || (pCarry == nullptr) ||
        (pWandererA == nullptr) || (pWandererB == nullptr) ||
        (pWandererC == nullptr) || (pWandererD == nullptr) ||
        (pWandererE == nullptr) || (pWandererF == nullptr) ||
        (pWandererG == nullptr) || (pWandererH == nullptr) ||
        (pWandererI == nullptr) || (pWandererJ == nullptr) ||
        (pWandererK == nullptr)) { return; }
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::uint8_t *aCelestialLaneA = pWorkSpace->mCelestialLaneA;
    std::uint8_t *aCelestialLaneB = pWorkSpace->mCelestialLaneB;
    std::uint8_t *aCelestialLaneC = pWorkSpace->mCelestialLaneC;
    std::uint8_t *aCelestialLaneD = pWorkSpace->mCelestialLaneD;
    std::uint8_t *aKineticLaneC = pWorkSpace->mKineticLaneC;
    std::uint8_t *aKineticLaneD = pWorkSpace->mKineticLaneD;
    std::uint8_t *aChanceLaneA = pWorkSpace->mChanceLaneA;
    std::uint8_t *aChanceLaneB = pWorkSpace->mChanceLaneB;
    std::uint8_t *aChanceLaneC = pWorkSpace->mChanceLaneC;
    std::uint8_t *aChanceLaneD = pWorkSpace->mChanceLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;

    // [grow key b]
    TwistExpander_Achernar_Arx::GROW_B_A(pWorkSpace,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::GROW_B_B(pWorkSpace,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    TwistExpander_Achernar_Arx::GROW_B_C(pWorkSpace,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

    //
    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mKeyRotateBConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mKeyRotateBConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mKeyRotateBConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mKeyRotateBConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mKeyRotateBConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mKeyRotateBConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mKeyRotateBConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mKeyRotateBConstants.mMatrixArgD;
    //
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,
                         aFuseLaneC, aFuseLaneD,  // input lanes
                         aChanceLaneA, aChanceLaneB,
                         aChanceLaneC, aChanceLaneD, // output lanes
                         aKineticLaneC, aKineticLaneD, aCelestialLaneC, aCelestialLaneD, // index shuffle seeds
                         aCelestialLaneA, aCelestialLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    //
    TwistExpander_Achernar_Arx::GROW_B_D(pWorkSpace,
                 pPrevious,
                 pIngress,
                 pCarry,
                 pWandererA,
                 pWandererB,
                 pWandererC,
                 pWandererD,
                 pWandererE,
                 pWandererF,
                 pWandererG,
                 pWandererH,
                 pWandererI,
                 pWandererJ,
                 pWandererK);

}

void TwistExpander_Achernar::FoldKeyRows(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) { return; }
    // GrowAControl candidate 1 of 33
    // Exploration cases: 0
    // Structural distance: baseline candidate
    std::uint8_t *aGrowAAetherLaneA = pWorkSpace->mAetherLaneA;
    std::uint8_t *aGrowAAetherLaneB = pWorkSpace->mAetherLaneB;
    std::uint8_t *aGrowAAetherLaneC = pWorkSpace->mAetherLaneC;
    std::uint8_t *aGrowAAetherLaneD = pWorkSpace->mAetherLaneD;
    std::uint8_t *aGrowAVaporLaneA = pWorkSpace->mVaporLaneA;
    std::uint8_t *aGrowAVaporLaneB = pWorkSpace->mVaporLaneB;
    std::uint8_t *aGrowAVaporLaneC = pWorkSpace->mVaporLaneC;
    std::uint8_t *aGrowAVaporLaneD = pWorkSpace->mVaporLaneD;
    std::uint8_t *aGrowAShadowLaneA = pWorkSpace->mShadowLaneA;
    std::uint8_t *aGrowAShadowLaneB = pWorkSpace->mShadowLaneB;
    std::uint8_t *aGrowAShadowLaneC = pWorkSpace->mShadowLaneC;
    std::uint8_t *aGrowAShadowLaneD = pWorkSpace->mShadowLaneD;
    std::uint8_t *aGrowAKeyRowWrite = &(pWorkSpace->mKeyBoxA[0][0]);
    static_assert((S_BLOCK / S_QUARTER) == 4, "GrowKeyA expects four expansion-lane quarters.");
    static_assert((S_QUARTER / W_KEY) == 4, "GrowKeyA expects four key chunks per quarter.");
    TwistShiftBox::ShiftKeyBoxA(pWorkSpace);
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7879U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 137U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3828U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4008U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowAAetherLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aGrowAAetherLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aGrowAAetherLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aGrowAAetherLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aGrowAVaporLaneA[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3738U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7789U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4188U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3558U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowAAetherLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aGrowAAetherLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aGrowAAetherLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aGrowAAetherLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aGrowAVaporLaneB[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7969U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8149U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7699U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4098U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowAAetherLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aGrowAAetherLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aGrowAAetherLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aGrowAAetherLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aGrowAVaporLaneC[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3648U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8059U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 47U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3918U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowAAetherLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aGrowAAetherLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aGrowAAetherLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aGrowAAetherLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aGrowAVaporLaneD[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1375U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1825U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1960U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1915U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowAVaporLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aGrowAVaporLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aGrowAVaporLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aGrowAVaporLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aGrowAShadowLaneA[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2005U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1870U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1465U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1780U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowAVaporLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aGrowAVaporLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aGrowAVaporLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aGrowAVaporLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aGrowAShadowLaneB[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 92U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1510U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1420U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1330U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowAVaporLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aGrowAVaporLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aGrowAVaporLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aGrowAVaporLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aGrowAShadowLaneC[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1555U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1600U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1735U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowAVaporLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aGrowAVaporLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aGrowAVaporLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aGrowAVaporLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aGrowAShadowLaneD[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1690U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1645U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 47U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 137U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowAShadowLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aGrowAShadowLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aGrowAShadowLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aGrowAShadowLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aGrowAKeyRowWrite[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    //
    // GrowBControl candidate 1 of 33
    // Exploration cases: 0
    // Structural distance: baseline candidate
    std::uint8_t *aGrowBCrystalLaneA = pWorkSpace->mCrystalLaneA;
    std::uint8_t *aGrowBCrystalLaneB = pWorkSpace->mCrystalLaneB;
    std::uint8_t *aGrowBCrystalLaneC = pWorkSpace->mCrystalLaneC;
    std::uint8_t *aGrowBCrystalLaneD = pWorkSpace->mCrystalLaneD;
    std::uint8_t *aGrowBVaporLaneA = pWorkSpace->mVaporLaneA;
    std::uint8_t *aGrowBVaporLaneB = pWorkSpace->mVaporLaneB;
    std::uint8_t *aGrowBVaporLaneC = pWorkSpace->mVaporLaneC;
    std::uint8_t *aGrowBVaporLaneD = pWorkSpace->mVaporLaneD;
    std::uint8_t *aGrowBShadowLaneA = pWorkSpace->mShadowLaneA;
    std::uint8_t *aGrowBShadowLaneB = pWorkSpace->mShadowLaneB;
    std::uint8_t *aGrowBShadowLaneC = pWorkSpace->mShadowLaneC;
    std::uint8_t *aGrowBShadowLaneD = pWorkSpace->mShadowLaneD;
    std::uint8_t *aGrowBKeyRowWrite = &(pWorkSpace->mKeyBoxB[0][0]);
    static_assert((S_BLOCK / S_QUARTER) == 4, "GrowKeyB expects four operation-lane quarters.");
    static_assert((S_QUARTER / W_KEY) == 4, "GrowKeyB expects four key chunks per quarter.");
    TwistShiftBox::ShiftKeyBoxB(pWorkSpace);
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7249U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2928U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3198U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3018U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowBCrystalLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aGrowBCrystalLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aGrowBCrystalLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aGrowBCrystalLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aGrowBVaporLaneA[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7609U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7159U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3288U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7429U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowBCrystalLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aGrowBCrystalLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aGrowBCrystalLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aGrowBCrystalLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aGrowBVaporLaneB[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3108U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7519U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6979U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7069U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowBCrystalLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aGrowBCrystalLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aGrowBCrystalLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aGrowBCrystalLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aGrowBVaporLaneC[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3378U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7339U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3468U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2838U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowBCrystalLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aGrowBCrystalLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aGrowBCrystalLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aGrowBCrystalLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aGrowBVaporLaneD[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1195U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 880U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1015U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1060U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowBVaporLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aGrowBVaporLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aGrowBVaporLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aGrowBVaporLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aGrowBShadowLaneA[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 565U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 970U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 745U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 655U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowBVaporLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aGrowBVaporLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aGrowBVaporLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aGrowBVaporLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aGrowBShadowLaneB[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 835U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 790U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1285U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1240U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowBVaporLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aGrowBVaporLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aGrowBVaporLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aGrowBVaporLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aGrowBShadowLaneC[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 520U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 925U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 700U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 430U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowBVaporLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aGrowBVaporLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aGrowBVaporLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aGrowBVaporLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aGrowBShadowLaneD[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1150U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1105U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 610U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 475U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aGrowBShadowLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aGrowBShadowLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aGrowBShadowLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aGrowBShadowLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aGrowBKeyRowWrite[aIndex] = static_cast<std::uint8_t>(aFoldWord);
        }
    }
}

// FoldSeedControl candidate 1 of 33
// Exploration cases: persisted candidate
// Structural distance: initial random-shuffle baseline
void TwistExpander_Achernar::FoldSeed(TwistWorkSpace *pWorkSpace,
                                      std::uint8_t *pDestination) {
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }

    std::uint8_t *aPoisonLaneA = pWorkSpace->mPoisonLaneA;
    std::uint8_t *aPoisonLaneB = pWorkSpace->mPoisonLaneB;
    std::uint8_t *aPoisonLaneC = pWorkSpace->mPoisonLaneC;
    std::uint8_t *aPoisonLaneD = pWorkSpace->mPoisonLaneD;

    std::uint8_t *aDestinationLaneA = pDestination + (0U * W_KEY);
    std::uint8_t *aDestinationLaneB = pDestination + (1U * W_KEY);
    std::uint8_t *aDestinationLaneC = pDestination + (2U * W_KEY);
    std::uint8_t *aDestinationLaneD = pDestination + (3U * W_KEY);
    std::uint8_t *aDestinationLaneE = pDestination + (4U * W_KEY);
    std::uint8_t *aDestinationLaneF = pDestination + (5U * W_KEY);
    std::uint8_t *aDestinationLaneG = pDestination + (6U * W_KEY);
    std::uint8_t *aDestinationLaneH = pDestination + (7U * W_KEY);
    std::uint8_t *aDestinationLaneI = pDestination + (8U * W_KEY);
    std::uint8_t *aDestinationLaneJ = pDestination + (9U * W_KEY);
    std::uint8_t *aDestinationLaneK = pDestination + (10U * W_KEY);
    std::uint8_t *aDestinationLaneL = pDestination + (11U * W_KEY);
    std::uint8_t *aDestinationLaneM = pDestination + (12U * W_KEY);
    std::uint8_t *aDestinationLaneN = pDestination + (13U * W_KEY);
    std::uint8_t *aDestinationLaneO = pDestination + (14U * W_KEY);
    std::uint8_t *aDestinationLaneP = pDestination + (15U * W_KEY);

    static_assert((S_BLOCK / W_KEY) == 16,
                  "FoldSeed expects sixteen key-width chunks per lane.");

    //
    // FoldSeed — Chunk A
    //
    {
        const std::size_t aFoldBaseA = 15U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 15U * W_KEY;
        const std::size_t aFoldBaseD = 12U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1871U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 115U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 48U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1713U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aDestinationLaneA[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk B
    //
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 5U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 13U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 160U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 340U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 250U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1646U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneB[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk C
    //
    {
        const std::size_t aFoldBaseA = 4U * W_KEY;
        const std::size_t aFoldBaseB = 12U * W_KEY;
        const std::size_t aFoldBaseC = 4U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 183U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 543U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 633U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2006U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneC[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk D
    //
    {
        const std::size_t aFoldBaseA = 8U * W_KEY;
        const std::size_t aFoldBaseB = 7U * W_KEY;
        const std::size_t aFoldBaseC = 8U * W_KEY;
        const std::size_t aFoldBaseD = 7U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 903U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 295U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 858U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 498U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneD[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk E
    //
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 7U * W_KEY;
        const std::size_t aFoldBaseD = 4U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1443U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1173U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1736U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1578U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneE[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk F
    //
    {
        const std::size_t aFoldBaseA = 10U * W_KEY;
        const std::size_t aFoldBaseB = 10U * W_KEY;
        const std::size_t aFoldBaseC = 12U * W_KEY;
        const std::size_t aFoldBaseD = 10U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 993U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 70U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1848U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 408U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneF[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk G
    //
    {
        const std::size_t aFoldBaseA = 7U * W_KEY;
        const std::size_t aFoldBaseB = 4U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 11U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1083U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1533U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1803U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 363U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneG[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk H
    //
    {
        const std::size_t aFoldBaseA = 11U * W_KEY;
        const std::size_t aFoldBaseB = 9U * W_KEY;
        const std::size_t aFoldBaseC = 13U * W_KEY;
        const std::size_t aFoldBaseD = 6U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1983U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 813U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 588U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1668U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneH[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk I
    //
    {
        const std::size_t aFoldBaseA = 14U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 14U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 228U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 273U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 453U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1488U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneI[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk J
    //
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 6U * W_KEY;
        const std::size_t aFoldBaseC = 10U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 723U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 93U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 678U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1038U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneJ[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk K
    //
    {
        const std::size_t aFoldBaseA = 9U * W_KEY;
        const std::size_t aFoldBaseB = 13U * W_KEY;
        const std::size_t aFoldBaseC = 9U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1128U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1623U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1758U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 318U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneK[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk L
    //
    {
        const std::size_t aFoldBaseA = 5U * W_KEY;
        const std::size_t aFoldBaseB = 11U * W_KEY;
        const std::size_t aFoldBaseC = 11U * W_KEY;
        const std::size_t aFoldBaseD = 9U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1938U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1218U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 948U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1916U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneL[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk M
    //
    {
        const std::size_t aFoldBaseA = 12U * W_KEY;
        const std::size_t aFoldBaseB = 15U * W_KEY;
        const std::size_t aFoldBaseC = 5U * W_KEY;
        const std::size_t aFoldBaseD = 8U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1893U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 25U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1308U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1691U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aDestinationLaneM[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk N
    //
    {
        const std::size_t aFoldBaseA = 6U * W_KEY;
        const std::size_t aFoldBaseB = 8U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 15U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1353U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 138U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 385U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1263U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aDestinationLaneN[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk O
    //
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 14U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1398U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2028U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 205U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1826U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aDestinationLaneO[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldSeed — Chunk P
    //
    {
        const std::size_t aFoldBaseA = 13U * W_KEY;
        const std::size_t aFoldBaseB = 14U * W_KEY;
        const std::size_t aFoldBaseC = 6U * W_KEY;
        const std::size_t aFoldBaseD = 5U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 768U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1961U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1781U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneP[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }
}

// FoldTwistControl candidate 1 of 33
// Exploration cases: persisted candidate
// Structural distance: initial random-shuffle baseline
void TwistExpander_Achernar::FoldTwist(TwistWorkSpace *pWorkSpace,
                                      std::uint8_t *pDestination) {
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }

    std::uint8_t *aPoisonLaneA = pWorkSpace->mPoisonLaneA;
    std::uint8_t *aPoisonLaneB = pWorkSpace->mPoisonLaneB;
    std::uint8_t *aPoisonLaneC = pWorkSpace->mPoisonLaneC;
    std::uint8_t *aPoisonLaneD = pWorkSpace->mPoisonLaneD;

    std::uint8_t *aDestinationLaneA = pDestination + (0U * W_KEY);
    std::uint8_t *aDestinationLaneB = pDestination + (1U * W_KEY);
    std::uint8_t *aDestinationLaneC = pDestination + (2U * W_KEY);
    std::uint8_t *aDestinationLaneD = pDestination + (3U * W_KEY);
    std::uint8_t *aDestinationLaneE = pDestination + (4U * W_KEY);
    std::uint8_t *aDestinationLaneF = pDestination + (5U * W_KEY);
    std::uint8_t *aDestinationLaneG = pDestination + (6U * W_KEY);
    std::uint8_t *aDestinationLaneH = pDestination + (7U * W_KEY);
    std::uint8_t *aDestinationLaneI = pDestination + (8U * W_KEY);
    std::uint8_t *aDestinationLaneJ = pDestination + (9U * W_KEY);
    std::uint8_t *aDestinationLaneK = pDestination + (10U * W_KEY);
    std::uint8_t *aDestinationLaneL = pDestination + (11U * W_KEY);
    std::uint8_t *aDestinationLaneM = pDestination + (12U * W_KEY);
    std::uint8_t *aDestinationLaneN = pDestination + (13U * W_KEY);
    std::uint8_t *aDestinationLaneO = pDestination + (14U * W_KEY);
    std::uint8_t *aDestinationLaneP = pDestination + (15U * W_KEY);

    static_assert((S_BLOCK / W_KEY) == 16,
                  "FoldTwist expects sixteen key-width chunks per lane.");

    //
    // FoldTwist — Chunk A
    //
    {
        const std::size_t aFoldBaseA = 9U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 12U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1421U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1151U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1264U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 904U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneA[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk B
    //
    {
        const std::size_t aFoldBaseA = 13U * W_KEY;
        const std::size_t aFoldBaseB = 4U * W_KEY;
        const std::size_t aFoldBaseC = 15U * W_KEY;
        const std::size_t aFoldBaseD = 4U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1984U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 881U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1061U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2029U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneB[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk C
    //
    {
        const std::size_t aFoldBaseA = 6U * W_KEY;
        const std::size_t aFoldBaseB = 7U * W_KEY;
        const std::size_t aFoldBaseC = 10U * W_KEY;
        const std::size_t aFoldBaseD = 13U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 431U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 746U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1196U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 521U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneC[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk D
    //
    {
        const std::size_t aFoldBaseA = 11U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 6U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1286U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1624U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1039U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1219U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneD[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk E
    //
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 6U * W_KEY;
        const std::size_t aFoldBaseC = 9U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1016U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 26U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 566U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 206U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneE[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk F
    //
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 10U * W_KEY;
        const std::size_t aFoldBaseC = 7U * W_KEY;
        const std::size_t aFoldBaseD = 5U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1354U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1669U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 251U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1129U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneF[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk G
    //
    {
        const std::size_t aFoldBaseA = 12U * W_KEY;
        const std::size_t aFoldBaseB = 14U * W_KEY;
        const std::size_t aFoldBaseC = 5U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 814U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1241U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1714U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1556U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aDestinationLaneG[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk H
    //
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 12U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 14U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 926U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1174U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1331U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 161U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneH[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk I
    //
    {
        const std::size_t aFoldBaseA = 10U * W_KEY;
        const std::size_t aFoldBaseB = 5U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 971U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1804U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1894U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1601U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneI[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk J
    //
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 15U * W_KEY;
        const std::size_t aFoldBaseC = 8U * W_KEY;
        const std::size_t aFoldBaseD = 11U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1489U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 476U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1376U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1399U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aDestinationLaneJ[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk K
    //
    {
        const std::size_t aFoldBaseA = 14U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 11U * W_KEY;
        const std::size_t aFoldBaseD = 15U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1939U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1444U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1309U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1534U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aDestinationLaneK[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk L
    //
    {
        const std::size_t aFoldBaseA = 5U * W_KEY;
        const std::size_t aFoldBaseB = 11U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 12U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 994U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 791U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1466U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 386U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aDestinationLaneL[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk M
    //
    {
        const std::size_t aFoldBaseA = 8U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 14U * W_KEY;
        const std::size_t aFoldBaseD = 8U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1106U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 296U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 656U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1849U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneM[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk N
    //
    {
        const std::size_t aFoldBaseA = 4U * W_KEY;
        const std::size_t aFoldBaseB = 9U * W_KEY;
        const std::size_t aFoldBaseC = 6U * W_KEY;
        const std::size_t aFoldBaseD = 10U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 341U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1759U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 949U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 859U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aDestinationLaneN[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk O
    //
    {
        const std::size_t aFoldBaseA = 15U * W_KEY;
        const std::size_t aFoldBaseB = 8U * W_KEY;
        const std::size_t aFoldBaseC = 13U * W_KEY;
        const std::size_t aFoldBaseD = 7U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1511U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 836U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 611U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 71U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 24U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneO[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }

    //
    // FoldTwist — Chunk P
    //
    {
        const std::size_t aFoldBaseA = 7U * W_KEY;
        const std::size_t aFoldBaseB = 13U * W_KEY;
        const std::size_t aFoldBaseC = 4U * W_KEY;
        const std::size_t aFoldBaseD = 9U * W_KEY;
        for (std::size_t aIndex = 0U;
             aIndex < static_cast<std::size_t>(W_KEY);
             aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 701U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1084U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1579U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 116U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << 8U) |
                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << 0U) |
                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aDestinationLaneP[aIndex] =
                static_cast<std::uint8_t>(aFoldWord);
        }
    }
}

const TwistDomainSaltSet TwistExpander_Achernar::kKeyRotateASalts = {
    {
        {
            0x4BE83D3A25DBFFF9ULL, 0xF8D742A537EDE2FDULL, 0x2AB8EE5794EF9DEAULL, 0xC2FF8868DB96268EULL, 
            0x4F32B9BDDE2CDBCCULL, 0xB18D7DF11790663FULL, 0xD5D2FD975FBD1398ULL, 0xA60E618B99338A77ULL, 
            0xF3022E55048F6D97ULL, 0xD095210B9C51D9EDULL, 0x921C954AC67D51AAULL, 0x91FEBBB66C30D4D8ULL, 
            0x0654BEF3EC0F0BC5ULL, 0x92336A079D70E226ULL, 0x25B70915EF23BB9CULL, 0xED98C6A9CBCDD93EULL, 
            0x5D25A4F255FBAE8AULL, 0x40AE48594CFB4DFBULL, 0x2D200D4B0497C966ULL, 0x8EAE25C044BF42EDULL, 
            0x4CBC136A95F50378ULL, 0x984C4D94AEE07160ULL, 0x2E92B88D62C6599BULL, 0x551467F43CF6B69CULL, 
            0xFA631732240852E6ULL, 0xB153305DB11982EBULL, 0x75685EB756B216A9ULL, 0xB90AC1106B14BF20ULL, 
            0x77EF01AB22302E06ULL, 0x893DD7B6AF2970C4ULL, 0x9080EEA4CFF52AECULL, 0xCF86247E7CF666EEULL
        },
        {
            0xE3C9907BA17E47D3ULL, 0xA5A8444836EBF288ULL, 0x73B8CFB9AA8FB8C7ULL, 0x96A0E35AB094CA15ULL, 
            0xCCEBD5DBF97DC343ULL, 0x9BFF8C9B7DA8451FULL, 0xCEC5BE9024AD7132ULL, 0x2E559D41E9A09186ULL, 
            0x472E4B33D35C8F83ULL, 0xDAB730D38596D91AULL, 0x1FBA72FB24B8BF01ULL, 0x5F516796FAA08B9EULL, 
            0x294F64DDCAD3BAF0ULL, 0x3E9C664EF9F7E9E0ULL, 0xC119B846A5137519ULL, 0x9490109703428747ULL, 
            0xF82DCAED9B5CC237ULL, 0x5ABE92872EE14AC7ULL, 0x3FF1F7A6883A397EULL, 0x2903A533433885DBULL, 
            0x7B6485E725ABEF5CULL, 0x2A1CFEAD1DB4D943ULL, 0x41AD856F6CCB56A6ULL, 0x767AA0D885B96C89ULL, 
            0x359C45DD4A4C0B24ULL, 0x3A2364376A4B4AF3ULL, 0x366126C9FB56C6A6ULL, 0x343B955B1AF0C6C9ULL, 
            0xA67D99DC8223AF2AULL, 0x8C6E95E047AD4B02ULL, 0x7E2D1EDFB7439B22ULL, 0x73D4CD7717282F6FULL
        },
        {
            0x887C2C8D0FAAE53FULL, 0x0CBB8957414CF221ULL, 0x3C9A8F45DFE26307ULL, 0x054F0F8C781998CAULL, 
            0xD64D12DF81CA351DULL, 0xE2FC97B139BA2A9CULL, 0x064BF4196083BF6FULL, 0x6B4FCCB836C94AA9ULL, 
            0xDF2E165868124CA3ULL, 0x824A3630DF60AA78ULL, 0x6A458ABC50B111A2ULL, 0xD54192DD77E92C6FULL, 
            0x08C3590674FBE97CULL, 0x86573C58D0A0137AULL, 0x1FF392B8606442FDULL, 0xABC564AF090C0B60ULL, 
            0x736E25BF52D707C9ULL, 0xF0223AEE6062A409ULL, 0xA275A6473F0A9B7FULL, 0x627A4816A2F70B4FULL, 
            0xC96E6B3A0B02EDDAULL, 0x5A75A3EBB6ABE1EFULL, 0x9D774737A91E82DFULL, 0x9BD96AC4A6155062ULL, 
            0xB90C8A0A4B475325ULL, 0xBCD60312AA36847EULL, 0x97C99A2ED702DCD7ULL, 0x93A9640BC95E4CE5ULL, 
            0x24B72F8216E266D9ULL, 0x0B4F84425E83CB22ULL, 0x1DA28AF1FC10AC7FULL, 0x7494AD4E8B285FCBULL
        },
        {
            0x152351437BC64088ULL, 0x54111387E476BC5DULL, 0x0A01574CDB0487AFULL, 0x871F90ABE9F59FA5ULL, 
            0x3F5E5E3BDC815AD4ULL, 0x19A8D9B266A19130ULL, 0x5F86DB4F55F3A972ULL, 0x369D1C70359CCD93ULL, 
            0x5F72DB3D3CE05143ULL, 0x3F1BCE73B9C69807ULL, 0x8DF0B86909CBA798ULL, 0x0DC2E518CF84C9F7ULL, 
            0xF9A4CB51FE5FDB7FULL, 0xF03BB1CDC9548C10ULL, 0x6DB3B091ED13DC9AULL, 0x3F42C877C1413716ULL, 
            0x5D70F83EB4D2DE6CULL, 0xF74F64550EB12A7EULL, 0x2A7870ECDFAFB9CFULL, 0xC333B4DF366BB26CULL, 
            0x8A16EF9D0546DB4BULL, 0x55586C8074C0755DULL, 0xD0F2E08A5199917DULL, 0xA7503EA949A070A9ULL, 
            0xB145131BFDF6EF1CULL, 0x9929C63E89C346B0ULL, 0x40972E532E6CBF7AULL, 0xD05FC0ABD19D4B65ULL, 
            0x46CE8D76C60BFCBAULL, 0x6808522AD585E2CAULL, 0x374053860B8629B3ULL, 0x0784CD7FD3946F27ULL
        },
        {
            0x16A713626946C2F5ULL, 0x5935836AF5C75139ULL, 0x480CEE06F163CC2FULL, 0x2230B8756BDD2296ULL, 
            0x83C7F16C77766B83ULL, 0xB796871FA0F92468ULL, 0xCD6E241939D407A3ULL, 0xD9A1E368509BA323ULL, 
            0xADAE40BA51E7C972ULL, 0x01D066BE8A9C21E4ULL, 0x6E6E06A208DF8F6DULL, 0x139E9480A0C57162ULL, 
            0x4B72B19BDB8BB532ULL, 0x92D8CBA25F1AA5CBULL, 0x5878B3EB677F0957ULL, 0x76552F75CEB66904ULL, 
            0x3A4A2587EF45BFD2ULL, 0x6C2B4ABE9A3B2210ULL, 0x5A09C9E40FDD54E3ULL, 0xA2E917DF3C2998FBULL, 
            0xD2B28F99D60FEB62ULL, 0xE9323F81C80E6180ULL, 0xE27A8BEDB2415B17ULL, 0x38E7C896745764AFULL, 
            0x9D96651C40710C94ULL, 0x435518795A2D006AULL, 0x292275075A21BF62ULL, 0xAF06A14A65594FC8ULL, 
            0xA59904930A536825ULL, 0x113AD51F2659A460ULL, 0x19150860982621AAULL, 0x31AF0BAC2C86D3A0ULL
        },
        {
            0x34CE6AF2BFA3AB4EULL, 0xB73D4CF667A5F432ULL, 0xA85293F34A62168CULL, 0x892721AAD377E8D1ULL, 
            0xBE4769E157240C90ULL, 0x2B2B06CC09C4F2F4ULL, 0x8E07D760EB91E7EBULL, 0x0C7CC8C41C7D0040ULL, 
            0x798666CDF5E59F82ULL, 0x522610EF79197014ULL, 0x987CCC2167A70A2AULL, 0x00386FE619FF6E8DULL, 
            0x70B347A96AF6BFCBULL, 0x7C29CC52E2BF07E7ULL, 0xB29DA8798128581AULL, 0x1ECDE1A7A1CBC403ULL, 
            0x27C943A30C1ADFCAULL, 0x8DDF17BA2494D972ULL, 0x02E54FAB4C3A4AF3ULL, 0x76C6E9FD8D13DD05ULL, 
            0xD391ACCC081AFA13ULL, 0xB94D5C16B6ADAF08ULL, 0x700AB6A209A611F0ULL, 0xD76F852BBED49F23ULL, 
            0xFEE7970F3C64E160ULL, 0x9FA624E46D0431C3ULL, 0xDDA9A3CEF0DB2D85ULL, 0x1FF59F875B143890ULL, 
            0xEC7D73D3778B4860ULL, 0x9EA68C10FCF9BD84ULL, 0xC703B7EB8EFD98FDULL, 0x0D1B379EDFB7FF89ULL
        }
    },
    {
        {
            0xC3F7122B9D4D8935ULL, 0x3ACCF78D9E8A64B8ULL, 0x1CA295063711C49FULL, 0x3C74BA08483D9FAEULL, 
            0xBA8FEF1859BE16B1ULL, 0x8333A4D010E76A16ULL, 0xEF0FE4E080BC1A17ULL, 0x931458230926D597ULL, 
            0xDA2223C08098E96EULL, 0x3719E20E73C99B6FULL, 0x1D0CCEE45FC7A845ULL, 0xCC5988280ADC9E54ULL, 
            0xBA61D245802B9AB3ULL, 0x889BC6768B1A3574ULL, 0xF97CEA469AF59A21ULL, 0x83302607803C708AULL, 
            0x957E0FDDCAD445FBULL, 0x73BB9FAB6FFFF4EBULL, 0xDE70DB021DDDE77DULL, 0x2BB1E738A072E541ULL, 
            0x71D99CAA24B6E7EEULL, 0xEF1AA5825AC72AABULL, 0x66608E4E2F7A2A5DULL, 0xE6AF893BDD8C7B3CULL, 
            0x08FBA59237F17A30ULL, 0xFB00174BA8D4C107ULL, 0x3C06BC367EBD00F6ULL, 0x93A54C254104E8E3ULL, 
            0x2C57AAA441310F63ULL, 0xC534C68646B80068ULL, 0xDA9446293D21F11EULL, 0x228BC50C71108211ULL
        },
        {
            0xE75E1CAFC103485DULL, 0x8D337A65ACB3C739ULL, 0x5FF71C65C8F5180CULL, 0xDBA78EA0B0F4FC0BULL, 
            0xAAC7BDEA448090C8ULL, 0x5D85468D5BA7C323ULL, 0x35AB33585A5D2D67ULL, 0x207A258B79760437ULL, 
            0x0A656138F1E53ED1ULL, 0xCA683BB1859360FDULL, 0x8850BDA39A4400F6ULL, 0x4DF8191702418CF0ULL, 
            0xEC11959005308449ULL, 0xAE64E6686BFBC752ULL, 0x7628270475BB848BULL, 0xB987799CC7E0713FULL, 
            0x201B7F8378B4A572ULL, 0x4005F5D3A891F771ULL, 0x01E4C687EC867E38ULL, 0x23357EC22130F935ULL, 
            0xD7FFA8A6BDDFC789ULL, 0x93869BC087759593ULL, 0x1CED98C70E064077ULL, 0x0FEC173CE96058D0ULL, 
            0x59BF03B1B1A0307AULL, 0x744A244682B87144ULL, 0x1D8C2B19C5BFFC35ULL, 0xC0C953445E4A1999ULL, 
            0x2368EAD2ADED47B1ULL, 0x9A0068DB600827B7ULL, 0xB028F3C86A492A0AULL, 0xB83E01E228B22FFFULL
        },
        {
            0x3A8D37A43A54DF30ULL, 0x82EDF86713F1FF07ULL, 0xC5834519E5751D46ULL, 0xEF994CD20BE951EAULL, 
            0xD6C6816A39B064AEULL, 0xE3174B89048FF0BAULL, 0x945880F6B524F457ULL, 0xFAE8A16B5F432D59ULL, 
            0x2E21B782C1E05059ULL, 0x506FF167457205C6ULL, 0x2DB3C5B62C9AF459ULL, 0xB1EAC9E3BF54CEA9ULL, 
            0x425ED9D3D6AB807EULL, 0x3B3512031FC02BA7ULL, 0xD9D91CC3579692DBULL, 0x7F8603D854887062ULL, 
            0xE27E85B59BE2FD2DULL, 0x0B93A118ACEF0CDFULL, 0x2C4CEAAFFD3295BEULL, 0x98C25F58FEF496CEULL, 
            0xE57999E5B2B39DF2ULL, 0x30ADCF56FFF5B947ULL, 0x81D2E867DFB5FF16ULL, 0x56A42CB10D2C77A7ULL, 
            0x4E542E94511E2CB2ULL, 0x59D3E1A0355E5182ULL, 0xA6B82AF6EB832057ULL, 0x3E323F76C0B06806ULL, 
            0xA592A379644D82E1ULL, 0xDF3FD15E82A15DEFULL, 0xDB80714FB77F8C56ULL, 0x5410A2A6392BAC4CULL
        },
        {
            0xED8426613E403921ULL, 0x71929EAC223FB8C3ULL, 0xD19923DDE80A91D1ULL, 0x4A2B9F32CD43F84CULL, 
            0x4716799768B1D71AULL, 0xFD5E710528CCE127ULL, 0x236E24542F2FF727ULL, 0x6A08B552E1DB0A81ULL, 
            0x6E5A10B3BB5E7496ULL, 0xA39721BF9E1252E9ULL, 0xC2646CFAFC66D4F0ULL, 0x2E3C50B66B2FBF40ULL, 
            0x0BAE3A91EC45D107ULL, 0x85936E775D2FCF6AULL, 0x39E65FCF36638D39ULL, 0xE64E6AFF5B3B4738ULL, 
            0x7A4BAE00A9EC018FULL, 0xA85448B090FB923DULL, 0x70407A8EEFDAE29FULL, 0x1FB2DDC4B0885567ULL, 
            0x30C75BB6B4E5B62EULL, 0x62F3631110585DFBULL, 0xC5B6FF1B8B5CBD95ULL, 0x509473EFD93E7BD0ULL, 
            0xBBF175E0DD216C0BULL, 0xC429B37512AF38B5ULL, 0x4B834B6915CAF2D5ULL, 0xAC8C7F936BA163D3ULL, 
            0xACB976A012837803ULL, 0x3A27AF7EC0D62900ULL, 0x57D747093FFBB851ULL, 0x1EA2C927F21CF72BULL
        },
        {
            0xEB8C23F6279CC839ULL, 0xDD2F7F101697EA40ULL, 0x8BA0960B8115F507ULL, 0x39D6320BF22C7157ULL, 
            0x7E79392F575445CBULL, 0x6E178396D66D81AAULL, 0xC2F63180682D2799ULL, 0x765263CB837512BCULL, 
            0x146BB44335B6F5A9ULL, 0x8534E61574872154ULL, 0x45EFD903F8D9DDA1ULL, 0xC11335C9BA97FED2ULL, 
            0x09FBBCA3C357190AULL, 0x294E5CDB635AB982ULL, 0x5E04C6055904A3BBULL, 0xE8FC6A9304B87F6AULL, 
            0xF3BBDA1CB92B2304ULL, 0xA35EF0413DF7B07AULL, 0x9964654CFD907A5AULL, 0x9536E1CA7C546E28ULL, 
            0xE97B4FF1DAE7BADEULL, 0xEC5A9F06FBC7AF70ULL, 0x06B1F6D81BA21150ULL, 0x74FEDDD2D004F20EULL, 
            0xACD4E4DD8E872363ULL, 0xB901490C1C8106E7ULL, 0x8A791F9C74F29E47ULL, 0x98AC5B5A00C93871ULL, 
            0x00E39B7C82A8C914ULL, 0xCD2778ECB2FB91DDULL, 0xB2661AC513717591ULL, 0x408B0C423A9F82B6ULL
        },
        {
            0xAA614743E009BC7BULL, 0x40A661201434FCCFULL, 0x3DF01434A5D64A92ULL, 0xD87DE97368AEA6B0ULL, 
            0x50B6035633D49AB8ULL, 0x5965DC8C2915F790ULL, 0xBE038A4712227047ULL, 0x1B83B5BD6CC74C03ULL, 
            0x84718F473AE012E2ULL, 0x252B3A665C989582ULL, 0xD653889876D35BF8ULL, 0x4D6B58626C7654EDULL, 
            0xB158A454CE7FF2FFULL, 0x08AC89CFD08E7EDBULL, 0x90B44D71CE3EB6A1ULL, 0x82A5F54369B82471ULL, 
            0x7F9B23DDCA199DA3ULL, 0x4FD409C8D236E331ULL, 0xC95716F4193995C0ULL, 0xA31064E07103B5FFULL, 
            0x4B99B20925C377AEULL, 0xEEADFBC35EC702F4ULL, 0x2D4EFECE85EA0174ULL, 0x67D09912878A79D4ULL, 
            0x3CB753DCFB81D44DULL, 0x187390467B2D108DULL, 0xA8A12AFD1C4E594BULL, 0x400FFA19E361FA63ULL, 
            0x005B54175D106517ULL, 0x15F1DF10A16DADA5ULL, 0x6F5BF7758288F3B3ULL, 0x5B58AED2703222D0ULL
        }
    },
    {
        {
            0x3810D04D5B807933ULL, 0xA416A7F00D945D9BULL, 0x70CE6833D240A4C8ULL, 0xE9603A97FEC75E7DULL, 
            0x2DC7EE1A93239B80ULL, 0x9B6AAB632E4928DBULL, 0x44E98FAA627CCFFEULL, 0x037D3E7680B1441CULL, 
            0x5FFEEF1A1A8D8194ULL, 0x74BA5F36A16D7237ULL, 0xEA55AFD82645E437ULL, 0x6219DF3A22876D36ULL, 
            0x966DB3C7D05B6B3EULL, 0x5DF005EAE18F26CEULL, 0x95D8481056D041D1ULL, 0xA8FE1B70E7A80BC0ULL, 
            0x13BF4B0F3BC9E0C9ULL, 0x342789D55C7B7B20ULL, 0x579391FCFA498C53ULL, 0x9C02D2FEABD816D1ULL, 
            0xAA259DF12D599536ULL, 0xD2AD2D7AB1701902ULL, 0x6C39B0BA4BAAE951ULL, 0x5B4A6E04844D82E4ULL, 
            0xD05F6AA63204387BULL, 0xDDA9C5EEB9E8E87FULL, 0xBBC08B5FA076A400ULL, 0xDE8C8FCD26C7C085ULL, 
            0x1928533989DB4F4CULL, 0xAF8069F6E9DCF3A6ULL, 0xC47C5E70C4ACD698ULL, 0x447F0E802ECA1B58ULL
        },
        {
            0xC32A46258C55C170ULL, 0x8EA86F43C312C0C6ULL, 0x6E31AB865E3E1FDDULL, 0x1FB8C94D02ECE5E0ULL, 
            0xAE8DAA9DAB02B2A7ULL, 0x0B8A7BCF87FA47A0ULL, 0xDE06CDE0464873D8ULL, 0xF9F5095A8D5DB877ULL, 
            0x516125E9B3E0DB31ULL, 0xE4C8EA85DBD4CD36ULL, 0xDB867BD01DF2DB7EULL, 0xC7479B0C4DDE447BULL, 
            0xC6417E2A8EB2E07EULL, 0x44A72CBF51F4E7BCULL, 0x90B75FA72BAE7FC8ULL, 0x7D14CE6DF4214A60ULL, 
            0x8364555820C36A99ULL, 0xEC3355C6EA019D59ULL, 0xDB415DD4B6046826ULL, 0x88FF83928994ADE0ULL, 
            0x01F211DB7FFDF87DULL, 0x0FEEF771E4573CE2ULL, 0xDB3C5096FC596291ULL, 0x4DA4C609C59100A5ULL, 
            0x328D804256FA60EEULL, 0x8F11DF38A558D231ULL, 0xEFB8555E72856AD2ULL, 0x43A1A7278865591DULL, 
            0xF5988165D8204CF7ULL, 0x77C363D156DD0BE6ULL, 0xD7110EC8DE3F7ACAULL, 0xCDA3F29D2D61693EULL
        },
        {
            0x39AEDF2EE4B3D2D0ULL, 0xF292AED53A96364CULL, 0x5C4ACFF6163EB885ULL, 0xB6D062CA60FC9FDAULL, 
            0x6E0A060060CA96A6ULL, 0x6BCCFF79294FC020ULL, 0x388E3D2C63AC3BDEULL, 0xAB18F8BEE7021C4FULL, 
            0xCD06E99EC9022BFCULL, 0xEF2EA24B3E423874ULL, 0x9A5DBB9979ED4621ULL, 0xE06DECE0E8CE44CFULL, 
            0xE2072EDEC9196CF5ULL, 0x6973CECAA5C37EF9ULL, 0xB0CA3F7BD696A971ULL, 0x219B20C8C9C7AB3DULL, 
            0x0905BEF27B0BBA02ULL, 0x91B36E9439C95A63ULL, 0x63AAC55CF5F53ED0ULL, 0x622A577A370DC194ULL, 
            0x02B2A5EA2EF0B265ULL, 0xB4DD4F6D9AF1B061ULL, 0xAF2BA4B5A6BD4F29ULL, 0x1C19D60CFE3D5A8EULL, 
            0x1AAB4A6DA6ADFAAEULL, 0x84B4A3EB76845EE6ULL, 0x90D0806DF47BDE64ULL, 0xEB9D3D0B76CCC7FCULL, 
            0x9947B60DD933CBFEULL, 0x33AACB85DE580D79ULL, 0xBA8AABAF50D99BFFULL, 0x20DB8B47D39BA3EEULL
        },
        {
            0xA5367D4606D5B0BCULL, 0x07285A69372FB8D8ULL, 0x2F0233492FB5CD6FULL, 0xD6F9966C35F6F6A8ULL, 
            0x528AB739F50E78D3ULL, 0x07EBCBF34F67E74EULL, 0xC62746F15BAB46B5ULL, 0x8FFA7E4EC82A868AULL, 
            0x6A040174531840EAULL, 0xF51EC5E2C16FFE56ULL, 0x328E85CA782B0428ULL, 0x5130FBE3AD1699DAULL, 
            0xE066AFB148A062FEULL, 0x9E96C613AEAB4959ULL, 0x5EB03D33A190A43AULL, 0xC1A368E67CF61C1EULL, 
            0xB9E92B7E04A3A82EULL, 0x4CFDADC6589BEBB6ULL, 0xFF9B7084DF79A08FULL, 0xB33F6380180D868DULL, 
            0x7D832AE383B9EFF3ULL, 0x201489869F2F2FA6ULL, 0xC31DCF7C9D89CA3EULL, 0x8EEDB636EF4ABACDULL, 
            0x4A6BADDFC3FCD567ULL, 0x5B1C1BDB5CA05450ULL, 0x79EE568ABB58CD9CULL, 0x60012E7C0142CACEULL, 
            0x1D595EC30C52C76FULL, 0x96C86CB846630247ULL, 0xFC3B1ABC2DBC4431ULL, 0x883C2A74357EFA51ULL
        },
        {
            0xDB644E9E2CA67CE9ULL, 0xADC4C34799C1BB66ULL, 0x12B6B9328CCE892CULL, 0x4BCA7249C65195B6ULL, 
            0x783A6A15EDE942E0ULL, 0xEA1774C6B5D79FE3ULL, 0x160EBDDD84A99238ULL, 0x43A283094661B074ULL, 
            0xB72DBF2F60BEE0D0ULL, 0x0E57A0D1ABAFE9E8ULL, 0x568886C5E9B58174ULL, 0x7D28B4DDC51050CFULL, 
            0xDD7125EFC0904E65ULL, 0x34606DE0EB5E1492ULL, 0x9D0D8028AE14D553ULL, 0x46341C448FE9E0C8ULL, 
            0xF470E8ABD926C905ULL, 0xD7913A0C47E65434ULL, 0x706513D7F21A2B40ULL, 0x50A5B5FEF2CD0CF8ULL, 
            0x35DA21E8163AA138ULL, 0x0A99D991E6EB6353ULL, 0xE7831FEA95575F52ULL, 0x9483E964A000FFDBULL, 
            0x2A69E6DE95C2CCFDULL, 0x7DDC6E32A0554EAAULL, 0xF6DB66E6EF1E3F31ULL, 0xF87AD5BE6650AB66ULL, 
            0x53BDAC66646A0BE7ULL, 0x95B4666B4AD454C1ULL, 0xA7C21A19EDC3488FULL, 0x705A3908DA9E7C03ULL
        },
        {
            0xF82936C14C4CBF43ULL, 0xCFE583D7E15F3755ULL, 0xA9DE3306E41D0283ULL, 0x25547540138D2D3BULL, 
            0xC8679174BA366268ULL, 0xC32BBC593EAE82EFULL, 0x2D33459C6AF4580CULL, 0x4204B31D8750B584ULL, 
            0x4437069545ED35F6ULL, 0xC27E2C337FA9D7FFULL, 0x2BCEC295DE3E9644ULL, 0x46E19D02EA0266E5ULL, 
            0x1E2AF65CCD29A1D7ULL, 0x18491842F720A41AULL, 0xAA84AE037A34F1C9ULL, 0x2AC1DFC007303F26ULL, 
            0xB04819055F8D3611ULL, 0xF7CD4BE306170546ULL, 0x6B43E5811B33590BULL, 0xD7549290C703B0A0ULL, 
            0x52B0511621908A7AULL, 0xCEF6E30D8DF44642ULL, 0x4FE1C903B24D13B5ULL, 0x65AA93D3A160B232ULL, 
            0x0BC9B67FC0969EDAULL, 0x2CE09ED971FC69D0ULL, 0xF5ED0C76E09C6AABULL, 0x192515B1D0498454ULL, 
            0xB85D457F434B4E2DULL, 0xD69D3ABD428E39A1ULL, 0xC3B8437BA01478FBULL, 0x476634499AACD1E2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kKeyRotateAConstants = {
    0xAB4FF4BCEDCB6D3AULL,
    0x0EDED9F8380B1E46ULL,
    0x5CC7DC829B20ABCEULL,
    0xAB4FF4BCEDCB6D3AULL,
    0x0EDED9F8380B1E46ULL,
    0x5CC7DC829B20ABCEULL,
    0x8CAA120186A16674ULL,
    0x3968FA7E889C4C5DULL,
    0x64,
    0x90,
    0x96,
    0x81,
    0xC8,
    0x1C,
    0x49,
    0x71
};

const TwistDomainSaltSet TwistExpander_Achernar::kKeyRotateBSalts = {
    {
        {
            0xBC58862735508EFFULL, 0x12B06AB31EB4B7C5ULL, 0x21F0CC8A5A29EC33ULL, 0xFB748078DF136F07ULL, 
            0x24282C5716D4A0D0ULL, 0x40EDEB2F547EB79CULL, 0x5B55E069415E26BFULL, 0x7EA5E26378E473B9ULL, 
            0x543FC9C06F7B475AULL, 0xD9874F66E28C8120ULL, 0x4D216A07B2B1A1D7ULL, 0xFC4A1E19A9AE3901ULL, 
            0x6710726313CADB0BULL, 0xDE83B6C1A7AA9CE0ULL, 0x783FE60DA9605D34ULL, 0x7A0CA34E8447452AULL, 
            0x77DD76D2A0CDD7BBULL, 0xB25F564312683FD2ULL, 0xEE7C3565BB8BA697ULL, 0xA88DD90F080CBA3AULL, 
            0xE0DF07838576E597ULL, 0xBC4016BA4817FD87ULL, 0x073D1666C3A1D399ULL, 0xBDC846C3D31812B6ULL, 
            0x082DDDE7C615AC28ULL, 0x6B2711AFFF526705ULL, 0x0BF88BCB20532FB4ULL, 0xF4E202C66D68D680ULL, 
            0x9746F004A6EDD507ULL, 0x634DC60F8B90833FULL, 0x99D9F94072E4BF39ULL, 0xAC304E30CA2E70BFULL
        },
        {
            0x736E95DF0A4986B9ULL, 0x955961313AA96DDFULL, 0x1945EB5DF35E4434ULL, 0x6AF301E53B91EA9BULL, 
            0x9E3EFDA989AF5055ULL, 0xD99FDF35359D9A08ULL, 0xC77264F5E63C0883ULL, 0xF29276B79358C626ULL, 
            0xF64EE444914E9BF0ULL, 0xBB0D01E246DB0B0DULL, 0x57356F5DA9D7D0B4ULL, 0x577606F7C3813C86ULL, 
            0x022BB89089973201ULL, 0x86DC1CA60EC5964AULL, 0xFC5F40406723FD69ULL, 0x99300B0C50A3E70FULL, 
            0x65767FDC78CC56BEULL, 0xBF9A18A577EFF8F8ULL, 0x866285C6F7462056ULL, 0x5544DFA5ED365CB1ULL, 
            0x08B0F9F3A2ACCCB8ULL, 0xE564B739A32C5689ULL, 0x574598FFEB9B63DDULL, 0xFEC23FEAF6BE43E6ULL, 
            0xB57EEEB97BB3A7A8ULL, 0x50803231A59E1E71ULL, 0xED45F04056BCD968ULL, 0xF5FEA966A2CA18B1ULL, 
            0xB69E67CBC2B11590ULL, 0x80C14F9ABF59AF1CULL, 0xBCFAC75B49EDA044ULL, 0xF166691D01BF85CDULL
        },
        {
            0x7A53A9D51A75D4A9ULL, 0xE908B0CE95A7C4EAULL, 0xCF0D34E6DE54142EULL, 0x2915F884AE383CC4ULL, 
            0xC9AF6107118E97D4ULL, 0x3B1AF066F02A19B8ULL, 0x0E44E01243DB8BE5ULL, 0xD91ED263B2136091ULL, 
            0x0BCBC93B1AAF1AA0ULL, 0xA51908C62C089860ULL, 0x087B733AF301A652ULL, 0x358EE6637AA57E81ULL, 
            0xDA844D02EC3FBCB7ULL, 0xB0CCCBEC5BCFC21CULL, 0x2B5A1A0B919C2B71ULL, 0x1EB2E1527759B2C6ULL, 
            0x601BD5C780D6EC31ULL, 0x8B02B748FF1AC82EULL, 0xFA91107E3E5946B5ULL, 0x3BCA0843A8B4E672ULL, 
            0xDF34725AF4BBE630ULL, 0x2C1AFD9B551D9561ULL, 0x0C517186ADAD133FULL, 0x23DB90373DF02A5EULL, 
            0xA00AC94CEC893479ULL, 0xD93D4C54A7ECAAFBULL, 0xA294A51F16AAAD22ULL, 0xE2FC71EFCADBEC09ULL, 
            0xA8D8769E53B26832ULL, 0xCB4B1EAFB1B40465ULL, 0x9CB4997F3B74C529ULL, 0x0D9900593CCE6250ULL
        },
        {
            0xE544C1702D895FBFULL, 0x56CBF10F9DE2EDE0ULL, 0x50AEF58B68049F0CULL, 0xD5E0E68DC94E9362ULL, 
            0x033EA2DC785A1C04ULL, 0xF2D4EB1EF1A2123AULL, 0x88BCE33BE784880FULL, 0xA5C8D9648B9DDEC0ULL, 
            0x5287AF3D1883B3E9ULL, 0x2492EF5FFF806B8BULL, 0x79B53913E29AB54EULL, 0xDA4ECA2E35851074ULL, 
            0x8D65F3C5EE89112FULL, 0x2537E16675475E93ULL, 0x53C52095BC6E1522ULL, 0xBD04D475530E91F9ULL, 
            0x2F5ADD94BD5BF9C6ULL, 0xDCA7161A7E46595EULL, 0x987801F1D022D9E8ULL, 0xF790A8D782EFB8E5ULL, 
            0xC559139AA735ACFEULL, 0x87C8AD0F0DC950EAULL, 0x91ED3C2513D1D7B4ULL, 0x8E9B30E1518CB227ULL, 
            0x010E0876986E284DULL, 0x69FAAB8999FAEAA4ULL, 0x94DAB06471AD547FULL, 0x69D417C6A4073BB6ULL, 
            0x862FCBD05F75F1EFULL, 0x8C1F66CEB73E5D38ULL, 0x3C69A3E4D229DE8CULL, 0xC6AF04448F90C3B1ULL
        },
        {
            0x10C9CEBDDE28E460ULL, 0x155F1186A3DA4664ULL, 0x88BD159218009AB7ULL, 0x5D3502AA25C374AEULL, 
            0x6685C39D4599A09AULL, 0x79F86D62551E560CULL, 0x97A49E245735932DULL, 0x1CD1184B87270115ULL, 
            0x99F1D4C768CBD9C5ULL, 0x61259CC85656DFD7ULL, 0x7B7C0B048E6966BAULL, 0x4FC6C5D20229F3A6ULL, 
            0x714107137C1806E3ULL, 0x727E5090EEA8EE42ULL, 0x2441839FF536A4B5ULL, 0xA2DCDEE382A79D8FULL, 
            0x38E1711C98FF2439ULL, 0x02B6FDAA3C46C41FULL, 0xCF4A748779747B4FULL, 0xEFE608D22DE1BDDEULL, 
            0x1C0B7A91C0E92588ULL, 0x238740313E537E0AULL, 0x60B8324C4A5AAACFULL, 0x1A3A9A2066973F81ULL, 
            0xC1D83330901858F1ULL, 0xB6E63E991F2D424BULL, 0x2C72BD75639A6768ULL, 0xFA13B4F66711ECCCULL, 
            0x666DCA37CDFE2AE7ULL, 0xEDEDB1A7ACDDFAF7ULL, 0xFB754EAAF3825FA5ULL, 0x32957923D9F68C34ULL
        },
        {
            0xE7E89E5E26C7EB23ULL, 0xB2F30E06F0450899ULL, 0x8E9B7CB807EB9265ULL, 0x4A43261A53B81069ULL, 
            0x93DB02E52C5C677BULL, 0xC22EE61B719D57EEULL, 0xD77630EDA8B5F8E6ULL, 0x6C52808AA96B009BULL, 
            0x299DEC53273FA037ULL, 0x9EC986C063F37F15ULL, 0x38D1B7EA14C8F75FULL, 0x9497CAF70393BEA4ULL, 
            0x0EECF2B4EF0FDA47ULL, 0x5B42F4192AD9BED4ULL, 0x65AE05501B8E0AFDULL, 0x66120CA492B380E1ULL, 
            0x4511D7E15B3E00A3ULL, 0xA4BF0A03AC5F2CC1ULL, 0xB49FEA0B35D09CE0ULL, 0x6A6191B6D3AE0D34ULL, 
            0x517F66CDD7C58436ULL, 0xCE6F2027C04C7BA4ULL, 0x32E255D189EF7D3EULL, 0x63A73D17DC600D58ULL, 
            0xBD2DD4093FCA7427ULL, 0x7EB379BB8A894EA0ULL, 0xE0CE12A35613B31AULL, 0xEA1A9724936BB19EULL, 
            0x7CD6A656978B2B12ULL, 0xD550392523A54E39ULL, 0x7A34FA11B1029F97ULL, 0xF0BDDFDEAE7F78E5ULL
        }
    },
    {
        {
            0xD32D4C5BFD431F11ULL, 0x6DF3E511F841A4C5ULL, 0xAB348AC5858BC13DULL, 0x6570419D6BA324FBULL, 
            0x630BBAED1ABDF8B4ULL, 0xB6CB5E0EF8087C36ULL, 0xA954BF4D0EF494D5ULL, 0xB3035E1C87989CB5ULL, 
            0x5E21ECD5EB886343ULL, 0x89941D5BE1D087B3ULL, 0x2F1F126F83DC9E8DULL, 0xE5384A3813691247ULL, 
            0xF5E07CAC04AB0E31ULL, 0x7A4D560F48940585ULL, 0xFB464276AB8F028DULL, 0x4DEFF5CE3853F04FULL, 
            0x84AC5610476C5BACULL, 0x69DE22D0ADAB80F7ULL, 0x56BF89E6D0C3BA33ULL, 0xEE66137A39F9A31AULL, 
            0x537738D6FE9964F9ULL, 0x9F2F34C5FD8012A4ULL, 0xE345813EBB1FE002ULL, 0x4CD511C74916F8A0ULL, 
            0xD64AA0562EFC6647ULL, 0x20A194275D86626EULL, 0xA035517FBCA7C852ULL, 0xCE7B09E81E12C998ULL, 
            0x1B207CE5BF6937BCULL, 0xC79624A81C8694D2ULL, 0xA0803E396BA587E9ULL, 0x7957CD69373966CFULL
        },
        {
            0xD4F3C1B144C28DF7ULL, 0xBF2EE7C1D0B71D4FULL, 0xD608B806BC30BF96ULL, 0x53D55D8916D5BF87ULL, 
            0xCBA70F66B679BFCBULL, 0xD5A6850A9CA27781ULL, 0x9E04574E14D828EBULL, 0x3A87C202134F55E5ULL, 
            0x7A3DEABCC135FCC2ULL, 0xD48EE4F682C793C6ULL, 0x20D719C040ACFD16ULL, 0x798E7794668E0397ULL, 
            0xB7B6D6EC1B398448ULL, 0xCD38D335B56425FCULL, 0xB1C2D570E69E8C7CULL, 0x31297B3DB2D33815ULL, 
            0x17776AF938E2E839ULL, 0x73D07AB2CCCFAACBULL, 0x43CBE9AB326D7CD4ULL, 0xBC1508F69B2B7386ULL, 
            0x0E38C3C570F3E1A9ULL, 0xDB7D1F9C4AFF2638ULL, 0xFA33B473E2D07958ULL, 0x5C334B3A5CC99D08ULL, 
            0x3347D2EFA4BEED7AULL, 0xC0FCEEF778D1A0D5ULL, 0xDBD6D31F4191EDA9ULL, 0xB9D9622D4640156BULL, 
            0x266F38690E7EE394ULL, 0xE8D217FE0624AF3FULL, 0x698E6FD168C37B0BULL, 0x0B87E01C1C52F371ULL
        },
        {
            0xCCD8C8F72FB381F9ULL, 0x5CC37B801BC4F112ULL, 0x978419CA67AB67E9ULL, 0x267FF898DE894D62ULL, 
            0xA98111FBCA036220ULL, 0x062FF6CA8097A7D5ULL, 0x1130FDA51F9CA1CEULL, 0x8E0D0ED237119834ULL, 
            0xF2191545BF17952DULL, 0x47006B11BEAD5719ULL, 0x1DFBD1CB214F58B1ULL, 0x25D9B542B3D87618ULL, 
            0xE7458F6DDA3DA7DCULL, 0xA3AD307D2F2D5A99ULL, 0x57AE5CE67AE444DBULL, 0xCF145CA21130849DULL, 
            0xA0CD222D40C37AD2ULL, 0xACA4A75759C666F4ULL, 0x912246DA9B25105CULL, 0xDF2C056A80CF1923ULL, 
            0xA69575DDEC0EB1FFULL, 0x3DC4AE2F28914A72ULL, 0x784A254A9D94B173ULL, 0xD1005DE4872808FBULL, 
            0x7CE890B4EDF2D9A4ULL, 0x6EB47907F87ADDE9ULL, 0x334CE55A88718718ULL, 0xCF7ED1BB4662B591ULL, 
            0xD6F01BE5A31DCF42ULL, 0x9E6F30A5E29D8963ULL, 0xD08AAD1178E87745ULL, 0x1C1FE6200E731E0CULL
        },
        {
            0xDF439C5613C31F85ULL, 0x3820A62C7332C907ULL, 0xB07DE155DB2DDC0DULL, 0x54FD6E8F5E4B280BULL, 
            0x6607371AC2E282F3ULL, 0x7507CDACC6C38008ULL, 0x0C75C917F75339EAULL, 0x7D62049ACBC9ACA6ULL, 
            0x8CDD2E13EC9CAAEAULL, 0x6798567C3072E3B6ULL, 0xE6892FFF162C08B7ULL, 0x00CE1489FF4C4035ULL, 
            0xDBF1BF649FCF365EULL, 0x5AB8A1CA81B528F3ULL, 0x2C1C911B2627F0E2ULL, 0xEF2F9E859AC33B7CULL, 
            0x74E45C197A678741ULL, 0x564996D2F5853B98ULL, 0x0B444D106D3BBEA5ULL, 0xA3A518EAB57B74ACULL, 
            0x61DD6DF277276555ULL, 0xBF8AA22AB26D7FC6ULL, 0x293838F1466040C5ULL, 0x55904EABA853C198ULL, 
            0x8377D08364B1EBDDULL, 0x2FCE6EAEB4CFA553ULL, 0x5F7C46D9E7AF3DD2ULL, 0x4EF8D4723D23C956ULL, 
            0x216060688224CC39ULL, 0xE2798740ED0041D9ULL, 0xD9C3A61DA9839E42ULL, 0x17365CA12170B418ULL
        },
        {
            0xACE10DEF57A285D1ULL, 0xA97256E4A4B17FC0ULL, 0x1DEB1396EB094DB7ULL, 0x251B5BFD769C13F8ULL, 
            0x96548A2A702D1A86ULL, 0x36D9DDA8D0443D96ULL, 0x5A82109F1C5D1497ULL, 0x7FDA79F62FEC76E4ULL, 
            0xE9FED6AA19D0F6C6ULL, 0x4FA5504D66FFF9DEULL, 0x18974C60201F189EULL, 0xDA1F0424140085F3ULL, 
            0xDB4810E24730C7AEULL, 0x29EDC5A1E2F8E307ULL, 0x6D7229AD83AA31A6ULL, 0x3FB6AC3DB1429835ULL, 
            0x8B5491D65458F1DDULL, 0xC4F509D2006EF022ULL, 0x348F0F54C84899E6ULL, 0xEAD662E6129F739CULL, 
            0x92D269991B951473ULL, 0xBD96F14C5E74837DULL, 0xC7C28B3394870A85ULL, 0xAAB8E52421D6196FULL, 
            0x8B752DE37DDB6362ULL, 0x455319AAEA5F3392ULL, 0x7E26FFFB3A3DC015ULL, 0xEE6D3F243D47B989ULL, 
            0x1AE7837EF987BF37ULL, 0x23CE675DEF63FED2ULL, 0xFCF2195C25B35DCCULL, 0x1F372ED24FD0E952ULL
        },
        {
            0xA7DCF8E7DA7EBCE4ULL, 0x173796225A4E0246ULL, 0x2D249F9B5562F4F2ULL, 0x4553F3B4C76D74B8ULL, 
            0x5C44BDB62AAD2DC9ULL, 0x274317EF98CCF30FULL, 0xA911CF6116EC3EF6ULL, 0xE612C0302D36A874ULL, 
            0xAEC0551462EB3F44ULL, 0x3CBB9873B8ED6873ULL, 0xCD2087085C19931AULL, 0x2CE30939B7EB6634ULL, 
            0xB180CB53431E05C6ULL, 0xB6D02772A6793536ULL, 0xE4A137EDBA04C185ULL, 0x2004BA69F1D957B0ULL, 
            0xB229EEC91BA4748EULL, 0x0F644C0A1D99DCBDULL, 0x541EF587BF94A19DULL, 0x6E313D5A03547224ULL, 
            0x7C594C931AC7FA80ULL, 0x3534877537AA54A4ULL, 0xEEFE840107C2C1A2ULL, 0x725943D4BB8D0B61ULL, 
            0xB6E7ECE648716800ULL, 0xB4863B751A962317ULL, 0x9AD89BF0C0FF9D25ULL, 0x9A7F29B3C1C016DFULL, 
            0xCC0F2B6F01956A37ULL, 0x69FA9C1C850E32FBULL, 0xDA0CA67130C7EF74ULL, 0x0F5286959ECF7DD2ULL
        }
    },
    {
        {
            0xA086E3940C18B587ULL, 0xDD0BE3812B65B2ECULL, 0xC9B2B9B112C63D82ULL, 0x3C1784DBD8DCE91EULL, 
            0x6C0C5FBA567D2813ULL, 0x6DCF928E2D258E2EULL, 0x831EC603703E612BULL, 0x8F9258B350DE3B1EULL, 
            0xCC128611D74E62ACULL, 0x333C5E688332A01BULL, 0x22048AF3873D686DULL, 0xA2A39490295AB628ULL, 
            0x07CCF439E93EB679ULL, 0xA267073AD1A30866ULL, 0xAC29FC918463B11AULL, 0x670DEE7A98573E5DULL, 
            0xFE6CE267B4A923B9ULL, 0x7620D78B3594C2A8ULL, 0xB38E195304623A29ULL, 0x868C563EE419000FULL, 
            0xBE66F004E52E7A98ULL, 0xEA42EF0EE056A1DAULL, 0x2561535FA466812EULL, 0x89E3C20EF9A41DD6ULL, 
            0xD8DE753F23A285E7ULL, 0x7C1677B74FC80BF0ULL, 0xEFCF61916878C100ULL, 0x6B62A910B7E216BDULL, 
            0xC7971E69877C375FULL, 0xB9D9E55701E1047FULL, 0x6BDBBEC1A0BA4B8AULL, 0x1489AE4BFE2F9CE3ULL
        },
        {
            0x0D37BEB77B1D1D47ULL, 0x13A0AFEA0817D3F8ULL, 0x0D5AC8217485632DULL, 0xA2794810AA37D431ULL, 
            0x94CF25E71057F2C9ULL, 0xEB5E4325BCCC89A3ULL, 0xE17F3D49BF2681DCULL, 0xBE805C6C9189C1B1ULL, 
            0x551F1C1ED207EF93ULL, 0xB071A649C65524BFULL, 0x3CF4DC05C71E8E07ULL, 0xA2632B1584CCFC59ULL, 
            0x322E7AC58836419AULL, 0x48CC39B453232789ULL, 0xE519BC956543D8ECULL, 0x221B1BC2A686BCD7ULL, 
            0x64B629B59E5192D3ULL, 0x16D4DDC1FCEB8519ULL, 0x54FE6647CC871E2AULL, 0x6DE3C9744B182CEAULL, 
            0x4B59502DA082A61AULL, 0xB87803C8D72EE87FULL, 0xD2A7B1B70B79B3B9ULL, 0x21DE6868A206DFB2ULL, 
            0x8C2EB30B6B2F3D05ULL, 0xB52BCC596BC128C8ULL, 0xE11652377CDA1CCFULL, 0x1D0A58AA65424C20ULL, 
            0xB1866687A5645758ULL, 0xDAF2060CB5AF6954ULL, 0x978FF5D2238184AAULL, 0xC37B8A85A0187B0DULL
        },
        {
            0x3433082727DBEA55ULL, 0x0A5C497731F0FF6BULL, 0x1AD3E6DFCF5D00C3ULL, 0x45BBFB0EADC011F2ULL, 
            0x84B248E5C4E495C0ULL, 0xDBB113AD9DB8EFC4ULL, 0xDB88D4DF7280B7F5ULL, 0xC995FD9C27D9FAC9ULL, 
            0x51B9A070EE0837CCULL, 0x796CEB930916CA0CULL, 0x4D03669BC600862FULL, 0x23CD5BAB92E4EBA3ULL, 
            0xB8D8ACDD8CED148AULL, 0xC8F601B59FC567D4ULL, 0x43188BBC2BE41427ULL, 0xBC7D11274CDBD269ULL, 
            0x811C83DC11A5453AULL, 0xC7EEA3B21F794AE3ULL, 0xDDCC94E2C041CD5CULL, 0xDB959DCF1B9CD13BULL, 
            0x291DC24BA6A7C461ULL, 0xEFFA453282252C6AULL, 0xD3CEE2AA3F94EFAFULL, 0x8686D820522D91C5ULL, 
            0xDF87F1D2CC4567F2ULL, 0x047D91339C0F0B3BULL, 0x1DFBF6E4213117E3ULL, 0xA5FED09789405A1DULL, 
            0x469AB416B359A49DULL, 0x899025A6E0FFFF3DULL, 0x9FB25DE50EA8ABC4ULL, 0x3DB5A8D1D27EC18AULL
        },
        {
            0xB4793627D562FE99ULL, 0xBE32442F255D9A53ULL, 0x64E4B6B108919B7DULL, 0x205500ACF3E4C0A0ULL, 
            0x7C33CE915BB60DD4ULL, 0x787B9B85DD75790FULL, 0x23601F622D376999ULL, 0x1A51E00B6E36B41CULL, 
            0x2896B3A2FB8F7619ULL, 0xEA98B67B6ABC1417ULL, 0xE74E0C35C5CFF4E2ULL, 0x27F3FC0ADFB1D4DCULL, 
            0x652C0E9A439AE02DULL, 0x58E19BDCCCFB7BEDULL, 0x9C729C7F8EC53744ULL, 0x44DC5D7E72262192ULL, 
            0x53A8EE0A6A93ED01ULL, 0x3678A688B2C86C44ULL, 0xB2345723F087BA49ULL, 0x6BA1F99E8AB40EB8ULL, 
            0x4CD34E24236E767AULL, 0x4AB2BDC9FF72ED19ULL, 0x7CA30ACDE3287A21ULL, 0x8537E86AB1E253B9ULL, 
            0xA52B3CB912EC7A12ULL, 0xD2D1AD01D0E24D63ULL, 0xD062E2A4417B8F46ULL, 0xDD2F903CB2EF97F4ULL, 
            0xD5B1C5ADCDCFE82FULL, 0x7F2BFBD48E51CA5BULL, 0xB3CCCC5D2D2F7916ULL, 0xD6DCCEBAA1F67681ULL
        },
        {
            0x3E54ACA0E66ECF37ULL, 0xE734554C0CA9F14DULL, 0xF640BA0D86A144BDULL, 0xFDC1ADC8ACD6662FULL, 
            0x0A2CC682224F1C4EULL, 0xEE9B24BF9CE47B41ULL, 0x672E186FD086DB0CULL, 0x61A9E8587A15482BULL, 
            0x5F09FF21FB51BD9FULL, 0x16C7F56B71CE10B6ULL, 0x285EB8350691E46BULL, 0x3FAA45546D92B80BULL, 
            0x659EF8BD51FFE31AULL, 0xF252136D6B228198ULL, 0xF687BDA2B41B8A7DULL, 0xEB72D9C8912ED433ULL, 
            0x920681F74577B074ULL, 0x6A5D18CD424D4285ULL, 0x636CFBBC3A4AEA00ULL, 0xDA5E33406B5E94B1ULL, 
            0xEFB0EE4462015C13ULL, 0x393BB260EA1588D0ULL, 0xFAEB84F5A8A0E9C0ULL, 0xF1453CE698A6B412ULL, 
            0x06E319638A55B06AULL, 0x02D3CC8512739C15ULL, 0x3B279F43713DFEECULL, 0x30290A8C73A74DABULL, 
            0xEE34C64844263795ULL, 0xC48F3F01AFB93EC0ULL, 0x3865BC126279A1F3ULL, 0xCF35740F1F2D492FULL
        },
        {
            0x62D0B4F5FD780B67ULL, 0x0844F768237E7479ULL, 0xDC4C23712663834DULL, 0x5FB8CDED631DDDBAULL, 
            0x2122FCFAD4BD16D3ULL, 0x3F230A64D83B1C5CULL, 0x621FAE27E4110917ULL, 0x9357BB687C96F155ULL, 
            0xBE122351F0708FD8ULL, 0x16F0A59E19A0A560ULL, 0x25492B9BDD8E84D2ULL, 0x5595A2821970CDB7ULL, 
            0xCA2BD571E82F6307ULL, 0x3D7E958C5B2D5FF0ULL, 0x70EE9509D72E0203ULL, 0x116916FA919ADA2FULL, 
            0xBBE7B8B933052034ULL, 0xBA4114DC04358CFEULL, 0xA2B90737C19387ECULL, 0xA03F7DB9960BE3E8ULL, 
            0xABA1CA6A139547FEULL, 0xCDE72DA2BD7B38C3ULL, 0x524405C7D022D8F3ULL, 0x25DD9289497E40CEULL, 
            0x36193C6ACAD8965AULL, 0x7F25028530E66E7AULL, 0x1BBF0C27239D6469ULL, 0xEB66950A55B3AF8AULL, 
            0xA70FF89A4DBAC62CULL, 0x7CDEE99BFD926208ULL, 0x02EB73C04143E943ULL, 0x08EC659093C4A3C3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kKeyRotateBConstants = {
    0x62C251DFEBC21F79ULL,
    0xB778FE3F027F2199ULL,
    0xADAA4EC8A7401222ULL,
    0x62C251DFEBC21F79ULL,
    0xB778FE3F027F2199ULL,
    0xADAA4EC8A7401222ULL,
    0x16A43750CFEAC558ULL,
    0x22559A9B0FAECAF7ULL,
    0x27,
    0x64,
    0xC6,
    0xF1,
    0x73,
    0xD6,
    0x58,
    0x45
};

const TwistDomainSaltSet TwistExpander_Achernar::kKeySpawnASalts = {
    {
        {
            0x5ADE95C16B8A5F4FULL, 0xCE60E90B5A2E911DULL, 0x41B3723D1B3A58CCULL, 0x7B8257A88271345AULL, 
            0xB9A9E66F4A31B3E6ULL, 0x21F8776B2C38537FULL, 0xFCFF52DB6CDA63FBULL, 0x24D597D35F70F90CULL, 
            0x37DA322B4A68751AULL, 0x5C05064AB1E74130ULL, 0xBD9D91B837FFB0ADULL, 0x9CFE17F5D4607CF4ULL, 
            0x12AC42BE7C91A203ULL, 0x67C8273371C72950ULL, 0xD9CF3AEFE7B6B7C6ULL, 0xFACC776290D5FC45ULL, 
            0xFE3C9E0719A5AEB1ULL, 0x546B23C9A4598BA2ULL, 0x9ABD10D0B5C4209EULL, 0x67B04DB48F6FE055ULL, 
            0xAAC8DE65AF0E5AF2ULL, 0x08AB9861AF5796C5ULL, 0x245C525D21431583ULL, 0x2C133DE859E8F6AEULL, 
            0xE674EBAFC0BC0E4EULL, 0xE86E5F783DA75F22ULL, 0x3148926D2EF1FAA5ULL, 0x5609A03E2F86D662ULL, 
            0x9B70D6285A8B7622ULL, 0x1AA742F698A6959EULL, 0xEE05A2AEA5124F85ULL, 0x3B1C263E1A51DD7EULL
        },
        {
            0x2A79ACB3BAF553BDULL, 0x6D03B5FA73C6BB48ULL, 0x9C26CC0CE628D4F6ULL, 0x29ECB81B826EF6F9ULL, 
            0xCA45C34269B11ED3ULL, 0x43833626F3AF4686ULL, 0x8BCC1BF9AD95D340ULL, 0xDE4CC98390B052C1ULL, 
            0x2735FBF4806D95D9ULL, 0xA2AF8F1A62F5CD8BULL, 0x4D9F257CC1EEC980ULL, 0x4445092FD2DAEB9FULL, 
            0x48D52CA16228ABDCULL, 0x178B5A72D9E419C6ULL, 0x81FFD796A17FEACBULL, 0x8B8D7FC4B6E1C7BEULL, 
            0xEABD1CEE9A1F89FDULL, 0x4C0565A60D49F921ULL, 0x25CCC876DCBDC801ULL, 0xA739F10C9A897372ULL, 
            0xD93CFEFCB4AEBE0EULL, 0x20A05358698AA254ULL, 0x01D27CF9762C3569ULL, 0xA3367B396F69D2BEULL, 
            0x750BE1E7753F884AULL, 0xA0C05F45A5E48C37ULL, 0x1AF7D6E59DB4476CULL, 0xD46CA5961F30E020ULL, 
            0x364C2C9B4AECA17CULL, 0xFF645DB8F6FE74B1ULL, 0x03EC91505B85F289ULL, 0xDE6715D096BCA097ULL
        },
        {
            0x7C830610BFE50B14ULL, 0xD46A012DF922C6A5ULL, 0x39922A01671472D2ULL, 0x1642AF7637F6B257ULL, 
            0x52069124F5B2FC4AULL, 0x83DCC1B7A7A8D954ULL, 0xA89C8BA12E369C83ULL, 0x5CE0377EC3B16A63ULL, 
            0x4E22234FAEB98E1CULL, 0xF9D6AAE4B9D2F252ULL, 0x177305B6C0F351FCULL, 0x0B32327ED7B2516CULL, 
            0x47DFEC4C18872272ULL, 0x14F92914AE9AEEB5ULL, 0x08FF3E804E21B702ULL, 0x551E30E5BE7C2D5AULL, 
            0x9C5BDD55108304FAULL, 0xAF221B94B48ADA34ULL, 0x03FD38ED04BD29F7ULL, 0xE897B63F4437EB1CULL, 
            0x9B7DF05ECAB0C801ULL, 0xB4E9649BD5021146ULL, 0xFCB4A5E08F054266ULL, 0x56F103B98855EDA1ULL, 
            0xE7E0E93154082CA3ULL, 0xDE4C0277A2139F44ULL, 0x376804C5663B8787ULL, 0xFB27A49A2F2AEE22ULL, 
            0x53A4E914A48F8774ULL, 0xDCAE44C48C2E591DULL, 0xD4C92B409BE2B25CULL, 0xB4C4391D0C236FD8ULL
        },
        {
            0x98D1A7385ABC448BULL, 0x48C466AA229F66C9ULL, 0x55C067736A526A2CULL, 0x5310A796E1A3FA29ULL, 
            0x71785FAD1E900287ULL, 0x071C0C59934D6614ULL, 0xF96BFF5863635E20ULL, 0x8B8F6D535A971881ULL, 
            0x630C8CF615396AF3ULL, 0x59173E7DCF15CCC4ULL, 0x11316AF883D46832ULL, 0xCDD9475BD6624843ULL, 
            0xC4EE5A33F4B0A28BULL, 0xF527A0DFB516CEA8ULL, 0x082454E9E7FEFAEDULL, 0xE5042A95D4D71B93ULL, 
            0x53C5D0429FBF95C1ULL, 0x81318F54DBC6E46CULL, 0x8EE696F94094BCA6ULL, 0xB47743233921128FULL, 
            0x62DCBDF995CA9829ULL, 0xFCE15080947BAADFULL, 0xEBB7B591862EC935ULL, 0xE474AFFF7DF4A26EULL, 
            0x883F51FCF17B4666ULL, 0x8BB5362A986DE501ULL, 0x9C0A530F3359E75AULL, 0xD247CB4E7F9B9D2FULL, 
            0x79D43CF9000E5959ULL, 0x211739E03B4C1C4EULL, 0xC01EBB30BC929658ULL, 0x833ED62F2FDF4B48ULL
        },
        {
            0x70E393F856F98FDDULL, 0x715F58FB71FAE0D7ULL, 0x6E9740B4A946E8EAULL, 0xAEA09D784259535FULL, 
            0x4566B3A27E7924EEULL, 0x62F5E677A13C390BULL, 0xFBA8B27C861F4F14ULL, 0x51224B97C76484A8ULL, 
            0x36982855EAB2413DULL, 0x11FBBEF520E8E85FULL, 0x336E49FCDE8FB833ULL, 0x59155E0DA10C4C5CULL, 
            0xB580942861B02F8BULL, 0x221E50D39A7AEC06ULL, 0x4AE7B34D8B79BD85ULL, 0x1C339A3A0D9E749BULL, 
            0x28F20D9EEC58F749ULL, 0x17855FA84201AEA3ULL, 0xD95DFD9C6FD83C47ULL, 0x022F9DBDC2BB8E70ULL, 
            0xD871912F295854DFULL, 0xF136F3B71EA220F5ULL, 0x44503E6780968538ULL, 0x2575572DE92DABE6ULL, 
            0x5EC6AD6ACEE2464CULL, 0xE9FDA3C4117A0591ULL, 0xA9ED433AF029363FULL, 0x4C9C5F87680EDAD1ULL, 
            0xE7459D294D432A2AULL, 0x84A6F769B232F2AFULL, 0x223A56157979DD83ULL, 0x59190CE56E1A01C5ULL
        },
        {
            0xC938B2D80778358DULL, 0xF88678DD0B5F3C11ULL, 0x8D100B29FD756C6FULL, 0x516315FA5B7F4602ULL, 
            0xCD911CB3FEA0336CULL, 0xE9182CBC2C5F73F7ULL, 0x5AE6E04C3B1E579BULL, 0xFD11175B9824BDFCULL, 
            0x587FD63415EDF4E6ULL, 0xBFD761F6D07318C4ULL, 0xB485D4EBC8057F7EULL, 0x76AD4540D25F78E9ULL, 
            0x9FD7D9C25D8D8BC8ULL, 0x3F4F886D20D8060DULL, 0x56854CF2AF0D9DFEULL, 0xEA5D20323E2E751DULL, 
            0x6F3E80C54ABAF704ULL, 0x31FD3E52F5E287FBULL, 0xDB339588AF2892DDULL, 0x6EC67C43F99C9DE5ULL, 
            0x396C85E837D78F6CULL, 0x387D237E10DFF9D6ULL, 0xD43A1BB24426E3E7ULL, 0x6F80E8F72C154086ULL, 
            0xCCF375D9CE508D78ULL, 0x3E930E5E84E631AAULL, 0xA26C8FFFFEBFF145ULL, 0x666F19ABEA3C1D68ULL, 
            0xCCD45B7BE395564BULL, 0x67A240703D057CF1ULL, 0x412CCA24077BDB68ULL, 0xA3DDD504CAE1F2A3ULL
        }
    },
    {
        {
            0x9B01438EA9A38798ULL, 0xEF36BBADE0BE8444ULL, 0x30065C18A5E53871ULL, 0x819CDD8EF024CD9AULL, 
            0xEF5CB6B01CC83F9BULL, 0xA72F911CE2759A58ULL, 0xB7FABC470D8C6854ULL, 0xDE551506F535A1DCULL, 
            0x3E192151D080778AULL, 0xACB6A715065E862EULL, 0x563B430FDBCDAE80ULL, 0xE8E602B3F632F4A5ULL, 
            0x70B1EF8042D5188DULL, 0xC995DFAA3BA779C0ULL, 0x970A4ED9718D2026ULL, 0x576D4CD539E73D5CULL, 
            0xAF4A36C762C8E845ULL, 0x2D592FD3D1DBF5E0ULL, 0xB4D9E6FD27F14142ULL, 0x4ADFDB6735DC240DULL, 
            0x6F80654885B092C2ULL, 0x16108A4AF86F7124ULL, 0x23A19B9C0EED880BULL, 0xEE46A9EB2E78A31EULL, 
            0xFE5B566511B21E18ULL, 0xF7C3283A5C9B3DF0ULL, 0xC0B773DD0D71281CULL, 0xD923A5FEFA1B8CCCULL, 
            0x51FE8F0C2C0F3801ULL, 0x5B021800F24D250BULL, 0xAF779B9595E62324ULL, 0x5D1A027CAC84656BULL
        },
        {
            0x21BB7071B7DE0E10ULL, 0xA46EA83E2BB4FA53ULL, 0xD08CE6903C3572A8ULL, 0x0BDD8A65866E8996ULL, 
            0xF18C4A932956C76EULL, 0xFDA623ABE6205291ULL, 0xB05CB99D7352B527ULL, 0xED5BC433403F3AF6ULL, 
            0x0727A8863DDAF7EEULL, 0x81340CD12C80DE85ULL, 0x393DC6C9B49AAD98ULL, 0xC63B0F73400F4CDAULL, 
            0xE26C63C60E5EB32CULL, 0x52575E390BA1D99EULL, 0xF92AC9EE69BFA42EULL, 0xA6102121144436CAULL, 
            0x63ED3BFDE69A7D0DULL, 0x01742067C92B9403ULL, 0x690843E0506926BCULL, 0x2203FD982B069169ULL, 
            0x1514E100FE56BF01ULL, 0x51CF1642FD959492ULL, 0xE0C764612832F2B1ULL, 0xEBFDA670E8374559ULL, 
            0xDD1244700A06F00BULL, 0xFF9114EB8E33ADDEULL, 0x51A5093C233111EDULL, 0xCFB52052F8A90712ULL, 
            0x7629824782B72D1CULL, 0x7F5EBF1D0D2FEA71ULL, 0xA41E5721BB59E8DFULL, 0xCE32A06C0D1FEAE3ULL
        },
        {
            0x7FB7F267AC4D1E6BULL, 0x50C8DFDE085A2D63ULL, 0xA98735719E51E7ABULL, 0xCFF4EE8717A03A2AULL, 
            0x6E9C0B8D985B37A3ULL, 0xE97971038C84B352ULL, 0x092398F21A931B43ULL, 0xCCED49A0D728B44AULL, 
            0x29194FEA35733B04ULL, 0x396CC5037DCF2E80ULL, 0x1369993E434A606BULL, 0xAE9FCD01058970D6ULL, 
            0x4ED1342B4EC41C49ULL, 0x69FD5995119589FAULL, 0x9E9E9A324EE9828DULL, 0x90479E68C7D8084FULL, 
            0xBCCE82D626BC8AC6ULL, 0x4B8681773E01778CULL, 0x8D7AA4F0C28838BFULL, 0x21A10D639302FAC2ULL, 
            0x68F78AE297C496E2ULL, 0xBF71EFB132E1076DULL, 0xDFC06BFD578DDCA2ULL, 0x90EC816A41BBC7CAULL, 
            0x3844CA0152FC7D6AULL, 0xAF861386183B3B76ULL, 0x3FFF65075A6D7431ULL, 0x1008C8017622EA00ULL, 
            0xBDF6A86F3F5BD5CFULL, 0x4203676570BDE0CFULL, 0x17D1A892AF33320FULL, 0x084F35F1A32B9AD6ULL
        },
        {
            0x566E1127BC330642ULL, 0x3CE43C7ABDA23D50ULL, 0x4615B64CE3722984ULL, 0x88471D6D69643BB9ULL, 
            0x45805A8858A36FEEULL, 0xCE1E3880F5F45923ULL, 0xE9CB25F9906BA498ULL, 0xEE53C38243355F62ULL, 
            0x41BC8888F439E6D2ULL, 0x65352ACC5A92F9D2ULL, 0x691D1193C2E1687AULL, 0x8CE40AD49EAF16B4ULL, 
            0xF7C1FFD35A58BA80ULL, 0xC596DD59B21FE2F7ULL, 0x4E42411F7DFF59F3ULL, 0x43353D097C982212ULL, 
            0x6EA17827E6821ED3ULL, 0x7E6FD570EAE969CBULL, 0x40C620A9CAF12E97ULL, 0xD9D9E514F5F3129FULL, 
            0xBAE6CD36A37F7F05ULL, 0x173D238C9F2E6A12ULL, 0xFDFEC8C6336D6B1CULL, 0x23F1EF91DABB4B6BULL, 
            0xE587AD0CF8FE1F16ULL, 0x2B2F6D0076B0F969ULL, 0x5F84576AA16EE95AULL, 0x0EFC2BCE368834D6ULL, 
            0x2273569E515DFE48ULL, 0x8D9D31BFBC3A713DULL, 0xA7288FEB2979DADAULL, 0xDB105A9F2C4125BDULL
        },
        {
            0xA60AE85819E956F0ULL, 0x47411EB599CCAFDBULL, 0x243D6F0B699DDA46ULL, 0x43C947BC502B3D1FULL, 
            0x42B6BA8F92F59A72ULL, 0xFE0ACC1DC20E0357ULL, 0x88D9A6BE07738F62ULL, 0x046517484FE79EDCULL, 
            0x14ECCA0C0DCE33BDULL, 0x677D315ED75DFD02ULL, 0xCABB96F0387B8551ULL, 0x79100FE5C4924910ULL, 
            0xC85D27EEDDE6321FULL, 0x082A577A350030BAULL, 0x8216AC9F04F500B8ULL, 0x0DA8B464E2C1A0C3ULL, 
            0x7600EC6E4830E76FULL, 0x57327A8962B5F534ULL, 0x4FAE57428E89C8BFULL, 0x80146C5634D84660ULL, 
            0xA8B8C0AB21FD9194ULL, 0x3951DD8593243FB7ULL, 0x0CC3370731578FB6ULL, 0xB287724E2539DD60ULL, 
            0xA8B7B886FCF543A9ULL, 0x9A575FF46CC8F8A0ULL, 0x7FCD697B5A4236F1ULL, 0x88BF1AC743CAF22DULL, 
            0xD3022E5CD019384AULL, 0x8CE1F1350CD6A372ULL, 0xF8B2F4BE55C73809ULL, 0x64D389FF5C329FE0ULL
        },
        {
            0x2BE49C40002E8C09ULL, 0xD8E3BC748F3E4FB4ULL, 0xF807B1BCF5BAE7B0ULL, 0xC89DDECED33F4B22ULL, 
            0xA2E42C12C32859C8ULL, 0x2328E34B6E42355DULL, 0xE584F86DBFB9F26DULL, 0xDB488D15838ED4AFULL, 
            0x3725239012E838A6ULL, 0x1310F23A3F307506ULL, 0xCFC1C5DE783BE3AAULL, 0xD50FBA462F42DB9AULL, 
            0x4C8B762EF2D3BDF1ULL, 0x51C6866BD27B4FC3ULL, 0x8CE663C6D0C9F3BCULL, 0xE2C28B44AA5CDC55ULL, 
            0xA46A87900D1662CEULL, 0xE8339FDBD5DA19C1ULL, 0x5AA9D1AE9D16EC58ULL, 0xC23B5FE61A09F77DULL, 
            0xB6F4A0D0F4A67E32ULL, 0x37947C84BF2E3EADULL, 0x5DC5B285F8635507ULL, 0x6E3A8BE12A3CE8F3ULL, 
            0xB8013EC29C755B09ULL, 0x83546857D012B9CBULL, 0xD4FEE381EC90B30CULL, 0x15720F90CEACEB8BULL, 
            0x0387A774249C10C1ULL, 0x808A7FB3B03AF105ULL, 0x3B0E12FD679FEBF9ULL, 0x2E9ECC2B9B109866ULL
        }
    },
    {
        {
            0x95269B19F110F9E9ULL, 0x641182AB45AA0369ULL, 0xB116118C3C37ED70ULL, 0x7A234C31E87F533DULL, 
            0x05FE7661DF2BBD32ULL, 0x28C1065EF688FFC0ULL, 0x3C5F80E87F550376ULL, 0x3E4197C1D9A729CAULL, 
            0x69BF51E19BC30E37ULL, 0x6C760B169DF14159ULL, 0xCA071D0070631FB8ULL, 0x75B3290DA5F80D78ULL, 
            0xF102FE5B83AC50ADULL, 0x23CD0CDC2E7CDF3EULL, 0x49516932D14BC8B0ULL, 0x52EF798DED3AA20BULL, 
            0x50999C12FCDAB1F4ULL, 0x314A1B0A549D2E37ULL, 0x7906B75E83549735ULL, 0xDBBA866309F7C71BULL, 
            0x8C88B4CC35ADAB29ULL, 0xCB06C708613FFED5ULL, 0xB7E97F98102E2A1EULL, 0x8903D73853206595ULL, 
            0x50A2A72ED823E7D5ULL, 0xBAA3603CD0BDAD63ULL, 0x771A9D4325BAB423ULL, 0x0E61758D7FBBE085ULL, 
            0x3E943DE7DA3050B4ULL, 0xC9656D8DF91405D7ULL, 0x6A1F894EC906C608ULL, 0xC1432EDF84B606E0ULL
        },
        {
            0x84BCD3EBF19778BCULL, 0x47D0D9C5505CE819ULL, 0x0F63ECC18FA855F6ULL, 0xB8B6C588F2ACEB2EULL, 
            0x54B51D730917022EULL, 0xAEDDDE158BF5306EULL, 0x23D2A7A3478A309DULL, 0x88A605D9A97C0BFAULL, 
            0x33707E3EBDAE9A3EULL, 0x8F7EB349AE1B1FB8ULL, 0x25C6902BBB5BE192ULL, 0x4DC1A40328C2B6CEULL, 
            0xD4A62CCB7E03C2D2ULL, 0x5423A73A143FEC82ULL, 0xFEEAB8E645A413C9ULL, 0xCB18ABB45DF7AFB5ULL, 
            0x4CD6E70042F282EDULL, 0x5EB86B9D2FBBCE2FULL, 0x2D6913BEE7FAC31CULL, 0x09D7ECC8F594C300ULL, 
            0xDDAB8FEF6DF4FE87ULL, 0x8FCF9B7058A1C56DULL, 0x2E8187073912D937ULL, 0xCD4AC8F240997FE9ULL, 
            0xE6472542B8700EDDULL, 0xC46C59252C785B95ULL, 0x8B45A65CA6A40FB7ULL, 0x41FC13555A33C50BULL, 
            0x713B7750180D2D0BULL, 0x2A56905C87661486ULL, 0x692C24FB6393FCE3ULL, 0xEEA3E7CE4A1883CEULL
        },
        {
            0xF8DAE65487270DF6ULL, 0x6990C9A337ADA990ULL, 0xD13F6B8FE40A5B25ULL, 0xB45EF503A5F88E2AULL, 
            0x68A2211FE43D3058ULL, 0xC3087C7D927E174CULL, 0x0CFBC0478C848CACULL, 0xCED5379A245DBBD3ULL, 
            0x4CD29F2DE38D1DF9ULL, 0xA9FAD7F86BD6A9FEULL, 0xC26C5332EE349657ULL, 0xBC4B874CD75CEA6EULL, 
            0x54C7561B736E3138ULL, 0x41488BE77732BAC7ULL, 0x1409247358DA58EBULL, 0xAB5A63CFD98BD2A6ULL, 
            0x531660ACC2887FF4ULL, 0xF11678B2F34A50EBULL, 0xF9A7C547B4A809DAULL, 0xC4B65BA051BC7449ULL, 
            0x58B1923021EBC64EULL, 0xE0F893598C8FEF6AULL, 0x7460A8051A0CD7F3ULL, 0x6003571069CAF17AULL, 
            0x406CC49B5221AE0DULL, 0xED221087DD244489ULL, 0xD12311F15708ACF3ULL, 0x8F332BCA0AAD6CEFULL, 
            0x5AC8A4AA8F398941ULL, 0xCB031A65B5189063ULL, 0xE935B5F900EC1FDDULL, 0x382DB5E56CE93F19ULL
        },
        {
            0x78D56929685693A5ULL, 0xCC86D81386ADFBE4ULL, 0x20C2C9695455F522ULL, 0x8487A52C5D163E16ULL, 
            0x9DAF0CEA76057F00ULL, 0x395F69C8BA550B59ULL, 0x5BE7F37B78514A39ULL, 0xE3065930049FEAA7ULL, 
            0x6A3284AE2C4B999DULL, 0x99774B451AA9D2FAULL, 0x644718927B47240CULL, 0x7733A63C1A348811ULL, 
            0x2B808C775EA32A95ULL, 0x2C80417960CBF1C7ULL, 0x6987C024165083F2ULL, 0x73203F7A094513D4ULL, 
            0x5151A5461F7FDD31ULL, 0x3440DCCB4AAE2520ULL, 0x8BBF90EC4FF9F245ULL, 0xED293BA4F9C09090ULL, 
            0xA5B0588B5995DC4AULL, 0x5588BE1C728A5DA2ULL, 0xC87DFC8F69F25531ULL, 0x3855BE3AD0784940ULL, 
            0x9360C048453560A4ULL, 0xE02FF129AD0FDCFBULL, 0xDEF5DED69FA4DFC2ULL, 0x1254C9072E33C3B7ULL, 
            0xDB61D2B2ACFF62C1ULL, 0x07C648026523B9EDULL, 0x724E6A2B2092A234ULL, 0x3E19E9FA6231B19FULL
        },
        {
            0xA1BC92D9A7247445ULL, 0x3EF4F7143DD4100DULL, 0xC285A0507A73C878ULL, 0xD1A0C125ACAD1C8FULL, 
            0xA3807685631A6CA7ULL, 0x63875710EEE79233ULL, 0xAC507EABEE011881ULL, 0x4D06A82D5FF8A1DCULL, 
            0x4FD4AC04984C6451ULL, 0xD5B8CB7394196490ULL, 0xB5ED515B92BA2213ULL, 0x49BB1BEA2A30179FULL, 
            0xFB10C08400DB8727ULL, 0x09ED229BE798B8B7ULL, 0xDF03F2A0CC5DA10BULL, 0xBFD47228AE553907ULL, 
            0x731A6E1104F94A8FULL, 0x0E50DC451508B930ULL, 0xF72822BDF0A17B84ULL, 0x4AECD5C411DB3899ULL, 
            0x47AB41968F14C825ULL, 0xA0ABCE673960F63DULL, 0x32BDDE4C4CC35561ULL, 0x4863941083D77934ULL, 
            0x601112077C608984ULL, 0xFE84CFE61B5BCCD2ULL, 0xEE34D192A113C37AULL, 0x3B7F8928056B1D38ULL, 
            0xEFE67567B0DBCB2AULL, 0x5EED5FB0A9748F90ULL, 0x805A01387E9FF71AULL, 0x524B19E9D4DECC45ULL
        },
        {
            0x7AB88C8E4CA1AB6FULL, 0x6A4E8836FD4F44ECULL, 0x5E4D86E8E2D0CD3AULL, 0xB3027E83F5A74A9DULL, 
            0xC931FD43F773E649ULL, 0x985C07E02A257A4FULL, 0xDDB87F94615A9B3DULL, 0x309DB6B8353D22B5ULL, 
            0x58F5FEAD1C60B515ULL, 0xB00626C4F3026C72ULL, 0x218A0650862E1284ULL, 0xC8D116AC7B03F5D3ULL, 
            0x83CE1BFAD0AD43A7ULL, 0x5CB071357E67C9C3ULL, 0x0DBF615A7A519056ULL, 0xDA63380056E544EBULL, 
            0x87AF050B7D78BEC5ULL, 0x7B451B8B0FF4E634ULL, 0xEC8B05891881D7C7ULL, 0xE713F63A671117B3ULL, 
            0x2BB33D7787B3E667ULL, 0xA77D92D86C294A47ULL, 0x21A75C455F69C9DEULL, 0xBD91B6170BCAA195ULL, 
            0xEEEA8D1C92D02376ULL, 0x197AFEF044E17ACEULL, 0xC2FD39CB0795A318ULL, 0xE3F9BDC9B160855DULL, 
            0xA1A4CD39AF4E7D6DULL, 0x87DABDB40AABEF6EULL, 0xD6AB87BD3C71E636ULL, 0x6A3EBF543D017306ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kKeySpawnAConstants = {
    0x9076A9F9796E4B6BULL,
    0xF8F5D2252E8864B8ULL,
    0xA945DB9A46AD152EULL,
    0x9076A9F9796E4B6BULL,
    0xF8F5D2252E8864B8ULL,
    0xA945DB9A46AD152EULL,
    0x3810437EEB219922ULL,
    0x7FCA8B02201E1FB1ULL,
    0x08,
    0x43,
    0x45,
    0x4C,
    0x6E,
    0xA5,
    0x88,
    0x20
};

const TwistDomainSaltSet TwistExpander_Achernar::kKeySpawnBSalts = {
    {
        {
            0x58214D49F362FC71ULL, 0x16564519A5592A18ULL, 0x3943B1313C7F63B5ULL, 0x2B1423FECB4EF551ULL, 
            0xF4ECF1CFC2BE730EULL, 0xF8E8E4016DA6745AULL, 0x22E00AFFB1A83ADEULL, 0x9C8FA33E0973D6D7ULL, 
            0xC72C193C0FCA1F7EULL, 0x30D443C531DCC431ULL, 0x16735D6D85D05965ULL, 0x0E3B44DF7AEF3D21ULL, 
            0xAA4B0576309F91BEULL, 0x13C982BF311FC44AULL, 0x221E6014B29E3240ULL, 0x97A15392ADB9E232ULL, 
            0x6A01BA900BCB842BULL, 0xBD1E1366CF94AF1CULL, 0xCE453ED6B8F1621FULL, 0x27E1E707D75B4ACBULL, 
            0x9852D8FFAA4F1639ULL, 0x620D4788BD415AFFULL, 0x63CA53BACBD8289EULL, 0x836737C06EFE9769ULL, 
            0x00C54D14F8CE4864ULL, 0x5127042A33F07DA8ULL, 0xEA30D6D8D5952BE5ULL, 0x4A7C6A064A3E8568ULL, 
            0xC2E384A4AF352413ULL, 0x6B9E6C4A0EDCB983ULL, 0x9100DB7B52FC5EFEULL, 0xFEA6274C5C17E6BBULL
        },
        {
            0x9F78F88CD83693EFULL, 0xCADF110E1FDBBE42ULL, 0x436AE65CD0698463ULL, 0x3CBD3A07C90CE0F1ULL, 
            0xAF17E28BD6151FDFULL, 0x3466FC732E37146CULL, 0xE770E15BAD46AFA2ULL, 0xA0AB7AFFA893478FULL, 
            0xB2194B1CF3E648DAULL, 0x15A6027860AB4047ULL, 0xE12843E60061E09EULL, 0x32C9520860CBECE3ULL, 
            0xB4E771E5D95A90E2ULL, 0xC0473D6CF1601D5EULL, 0x543805E119B47EA4ULL, 0x442CB64400C91566ULL, 
            0x93E0B6CAFE3A4F4FULL, 0x7A9E1CCF05A47BA8ULL, 0x839A07401380DA82ULL, 0x5EFD3CADE7ACE3CFULL, 
            0xEB981AE420B7FDAAULL, 0x6F9B3C7220361C0CULL, 0x58B1B38F6B71E021ULL, 0xE2D5C05B6B250D5FULL, 
            0xE5CC40868CBB91C1ULL, 0x118AD800D6CD5D3DULL, 0x1D780A8906F3B15AULL, 0x5A425F9C4A30C5FBULL, 
            0x1356B80E8C15C254ULL, 0xFDB58F48FEDE61D0ULL, 0x7E19FD8B18EDBD0BULL, 0x8133E66DC4760D77ULL
        },
        {
            0x85799CCA9F386199ULL, 0xE244A6B3D6DC6187ULL, 0x8F249DC91AF971A4ULL, 0x505D099983107057ULL, 
            0x04D748D85957E485ULL, 0x300BA24E2253BBA1ULL, 0xF16B8B6DFF41E8F8ULL, 0x604A30771FE75E52ULL, 
            0x5F5CE419906B06ADULL, 0x72376F0C8FCE8096ULL, 0xA43B2EC27AFE433AULL, 0xFC78F3C3F02C6246ULL, 
            0xB81E909B714487CDULL, 0xEFFA9788A8F6B1B7ULL, 0xA066313F85296A0CULL, 0x35CA1192985F743DULL, 
            0x2FB5A9CFC5D81587ULL, 0x2153230E29B71E8EULL, 0x97FD1FCBC69F677FULL, 0x0FDEFF790B8E127BULL, 
            0xBE24306D51EABEF8ULL, 0x9B739BA7741097A6ULL, 0xF2A881B459144322ULL, 0xD53DEE7A7653A066ULL, 
            0x21314CC14ADDE07BULL, 0x6388C751AB195DAAULL, 0x108EE31A39C94DA6ULL, 0x0D67BE926F0051A6ULL, 
            0x43E2362705B156BBULL, 0xA267B8F357202363ULL, 0xF6F7FE81000A27C3ULL, 0xC18FC860110DA274ULL
        },
        {
            0xD879DCF982EE27E3ULL, 0x523D0B1407F518C1ULL, 0xA47163FDDAE0EBFAULL, 0xDE284D07BD6E0CB9ULL, 
            0x43E3D7D6B41B794AULL, 0xE25B1C3FC38B7120ULL, 0x10E28AE80D63A97FULL, 0x019A1B7EC7BF1037ULL, 
            0xE5031A723AB9233BULL, 0x0BD65D6A035F9219ULL, 0x3D0641E9632D96A5ULL, 0x677C27BEC2127506ULL, 
            0x147FF95ADD428595ULL, 0xEE64FCE41F83FBD2ULL, 0xAF95534865B6999BULL, 0x42EE1BDFBD96CBF6ULL, 
            0xDB31C29382DEBC9EULL, 0x124495F4D177EE5BULL, 0x8744AFA120C70824ULL, 0x3F6DAD9CF81BA3C8ULL, 
            0x30932EAB158AD16CULL, 0x065BC1C1E8FAB95BULL, 0xD332128DC24B78F4ULL, 0xC90DEF1FE88025C0ULL, 
            0xD64922EE242BA1A5ULL, 0xF9098CD44E6A3F6EULL, 0x070C00A7C5797CD3ULL, 0xD90DD5BB315339ABULL, 
            0xD97EBE12FF1FABD3ULL, 0xF47238E431E56EF9ULL, 0x54E69FFE8D3B173AULL, 0x348D8F8314B741DEULL
        },
        {
            0x8D32634C6233EE9EULL, 0x871D6A99FD8EE693ULL, 0x5F83E25110A43F5DULL, 0x1026D763C6128DA8ULL, 
            0xC68ED8C434C70E57ULL, 0xE0DEB668FC6005E7ULL, 0x4D0990A125B5385AULL, 0x3052264A7BEF2D44ULL, 
            0xF0A25A62F571322FULL, 0x27828E3A8E325DDEULL, 0x283D60750AFCE37EULL, 0xCB6E2CCED4BD39BDULL, 
            0xFB711826805DF5F7ULL, 0xF4C6FE456B1A83C7ULL, 0xE0DCEAEADCF8C0C3ULL, 0xF5EDF56B6D929002ULL, 
            0x78236B9B41A2C809ULL, 0x1E8879658237EB8BULL, 0x096047571E7EB875ULL, 0x9BEF01A0A73FA983ULL, 
            0x22113339AFF6F43AULL, 0x2EB1125ADEEFB4B7ULL, 0xD451A58FA7134CB0ULL, 0xC0F5D51BF8373A2FULL, 
            0xEFACDBC98E6EC297ULL, 0x289C8D3148420312ULL, 0xA6DB7EBDCC129DF1ULL, 0x8CCF3D4898D26AAFULL, 
            0xF9B31903D92A2A20ULL, 0xEB33444E7FB4260BULL, 0x074661917984C827ULL, 0x0EC1C94C0FF8DF77ULL
        },
        {
            0xF431DBDA14948D7FULL, 0x074BBC9D23F6D106ULL, 0xE87A49BA177D8554ULL, 0x6C23298FBA169974ULL, 
            0x9C437D4704D82A04ULL, 0xEB29779AA29A11AFULL, 0x8DEF08C04F038CFCULL, 0xA496F78D83DAD518ULL, 
            0xF8A1B564856EC7FCULL, 0x27BC614AC1ECBE23ULL, 0xF9B3188FF1B6E1EBULL, 0x122863525D9EF8C7ULL, 
            0x003F4910D2B31969ULL, 0x57F819EEF794FBEDULL, 0xA5FB6D4FBC336BFDULL, 0xB6DFCEB87DFB5E1FULL, 
            0x4FAB12CB3A4B263DULL, 0xE0510F8B22ABD851ULL, 0xBC0AE57DCEAB97E2ULL, 0x7FC3D0FFFBC6B05FULL, 
            0xB7773A892019D152ULL, 0xA6FA2BCCBE4A5F92ULL, 0x07BE5DEB4DBF3CD8ULL, 0x5CE5696CB23740BDULL, 
            0x39834AA2ED396B39ULL, 0x7034227C6F43D404ULL, 0x83A3594319286A66ULL, 0xA1F9F19E0320D54BULL, 
            0x4D217244D0B1BD5FULL, 0x5167E90354AED196ULL, 0xACB6E5FF95335DEDULL, 0x8B0141C363882C1BULL
        }
    },
    {
        {
            0xDDF5533A351D3456ULL, 0xA4B61ACB0D6C90D2ULL, 0x0AEA31B7E9102F19ULL, 0x0D12526A1389C456ULL, 
            0x29194E32F9E79B31ULL, 0x8B1A23FE2815B2B9ULL, 0x3DF9D5C4B2552D7EULL, 0xC2107482F13F75C1ULL, 
            0xFD51C5507FCC6B51ULL, 0x46C63E088CFBFD4AULL, 0xADAAB9FB2AD514FDULL, 0x5BC890D4D3729CA6ULL, 
            0x64FEBCD53FE3324BULL, 0x1ACC04ED95F6881DULL, 0x6A203B5EA496B7E2ULL, 0x9CE9A5698541D774ULL, 
            0x27E0666A67D0E30AULL, 0xCE98E82969962022ULL, 0xC3D06114F407DB37ULL, 0x1EA57FD45FA7648FULL, 
            0xC61D549679FA2DFCULL, 0xE51DA00DEBA311B0ULL, 0x278997146CF27B0DULL, 0xA436F2DB51F5208CULL, 
            0x6BF9CA75297F3EFBULL, 0xB1454609C4E65771ULL, 0xA905375B6123E6AAULL, 0xE65E5FBEB9A4F663ULL, 
            0x37701C76ED2F82B4ULL, 0xB0A2A728E222AD86ULL, 0x03F3A443C75C39C3ULL, 0x218F6A0518E4BBB6ULL
        },
        {
            0x3CC7C2941ED0ADA6ULL, 0x1338DBABF3926CBCULL, 0x05AAFCA4ACD55C39ULL, 0x24E34D8429EE8CD8ULL, 
            0xA5C54F511118E766ULL, 0x3A456C76381FD5EEULL, 0x3F6E4DC9FEF765AFULL, 0xDD0DA14DD41916B2ULL, 
            0x58077880573F3E09ULL, 0x1F6C2A2F899CC4C2ULL, 0x4006BEDED8D91901ULL, 0x3243D2F236F87823ULL, 
            0xA5F7BDD04832B209ULL, 0x8623B4BBD8400D76ULL, 0x5D5F0462C962E018ULL, 0xE8ECCA496C786046ULL, 
            0x73EF00564E387153ULL, 0x4F1F54D248F1CE38ULL, 0x75B9D8C817493A98ULL, 0xF1DF5C93FF2D339EULL, 
            0x387D7DDB3618773CULL, 0x7A228CF1455EBBE5ULL, 0x8E0CA1DE4A4C1293ULL, 0xAE0B5635C48E8708ULL, 
            0xD8A9DA1EF2F59F3AULL, 0xD6E129779DD710DCULL, 0x72DED3B594ECBFCBULL, 0xE4800D3E993A8B39ULL, 
            0xA54854E0D769EB3DULL, 0x3296EE3305E44A72ULL, 0x0208D7EC20DE1FABULL, 0xFFB203AB7B8189B8ULL
        },
        {
            0x0E65B65E7B9BC044ULL, 0xAC96F7B87E8CDBBBULL, 0xABC00607AEE9FA56ULL, 0x40C8047490CE41EBULL, 
            0xCDAEF7192019507BULL, 0xEF3B79B85CC58FABULL, 0x361A3011220DE894ULL, 0x1DE710CEEDE4AE9CULL, 
            0x0EE88998B7F74C36ULL, 0x2FCBCDD08954C216ULL, 0x74671CE48578596CULL, 0xE8B946CBEFD3CF4EULL, 
            0x626B471F27BF1B3FULL, 0xE151550B13587E20ULL, 0x3C97B9FC8F4DFC6AULL, 0x08750A9A633619DFULL, 
            0x780F2224A7B1C206ULL, 0x3BADEFE9675DC826ULL, 0xA274EF17DAB95922ULL, 0xAC0D1B3F769AD3D1ULL, 
            0x5982A27EBAA7766CULL, 0x026E399DB707A42CULL, 0x600B885C5CF7BCF8ULL, 0xB35AC62C136DAAEBULL, 
            0x437A419D38DC0E11ULL, 0xAA16F991C8D148FAULL, 0x2F2592F912F4583FULL, 0x360F6C749E320091ULL, 
            0x307CFEBC006898DFULL, 0xF76D370A2F45BAFFULL, 0x76BD6C7AD416347CULL, 0x36F8E577EF85818CULL
        },
        {
            0xBBF91243EE7C776EULL, 0xE367CA42A9B0EDBAULL, 0xB029355615D91E0DULL, 0x091F32CB9642981FULL, 
            0x739B73C65CD8DEEBULL, 0x82EABAE40B421BF1ULL, 0x8C4D2397EFE24F71ULL, 0x1BE80023D0D80EC3ULL, 
            0xC8FD357C330AEAF3ULL, 0x623F0C47392FDD43ULL, 0x991E34A193007466ULL, 0xDF6FC063D0B7CCEEULL, 
            0xA6EA1F8FFBE251B0ULL, 0xA7345355CD4DD497ULL, 0x2D889B0ABE6CDEF7ULL, 0xE8B0941135EBDC60ULL, 
            0x8A477023EEC1A383ULL, 0x7F442948C4FF7C19ULL, 0x6967D5162C449670ULL, 0x8E6447B8F04CB9E0ULL, 
            0xD522DCF271B17D7AULL, 0x019F3C17A3EF7B40ULL, 0xA9E2467CA00F6E4FULL, 0xFD676AE29B49A5BCULL, 
            0xF5AC3749EC0F4DB8ULL, 0x45E842B416CA38C2ULL, 0x99C9A2505A03A6B2ULL, 0xFC46370FF3A35380ULL, 
            0xDE1DF1338A8770BFULL, 0x67FF508420236AAFULL, 0x39677CDED81ECA4DULL, 0x79ACD53EB1CE5EE6ULL
        },
        {
            0x8104074E9CB53266ULL, 0x5F33FF1F0E0D6F82ULL, 0x18738D7E1DE4D9E7ULL, 0x2F4781A93B0E9B66ULL, 
            0xE4F524B4D79CCC9CULL, 0xAD825E6CE5B45CDEULL, 0x887EBB56C31F6C55ULL, 0x5F3BF394F380E382ULL, 
            0x7C7059B5F8F2D086ULL, 0x2812F6578FA8FBFEULL, 0xCBA6C95BB239413AULL, 0x133EC20D26AE3D49ULL, 
            0x7D315D1D121AD611ULL, 0x998A6BCD2C1B6F9DULL, 0x78F5D14C6C018C94ULL, 0x59B5E1AF1612C131ULL, 
            0x18D06130F752A372ULL, 0x0DF87BB044760682ULL, 0x5D6F072441153861ULL, 0x9F1659856A0E1685ULL, 
            0xD3B2F298416861FAULL, 0xF0A054D81DD7FA59ULL, 0x76F44C6A40DA65A9ULL, 0x34FC4D0A41C2C1E4ULL, 
            0xB5701480DA7878EBULL, 0x96DFBE33E3B5F159ULL, 0x91B3338B8407CFA0ULL, 0x091BAF07E8529789ULL, 
            0x5482A26DBF7727AEULL, 0x0399BA3BDF6CB1D3ULL, 0x99B534CB2F6B289CULL, 0x8D7F75920AC57396ULL
        },
        {
            0x1452DDA00CD9CEABULL, 0xBA9505C7F765BF42ULL, 0x903F0370F1593DBCULL, 0x20222475E4165E92ULL, 
            0xC0D46AD896C4DA40ULL, 0x2CE522688A545AAFULL, 0xD597C3EA7A718B45ULL, 0x303A608D0DB906C1ULL, 
            0x3AC2D80FDCFB64DCULL, 0xE5FE7BF0868A2E7FULL, 0x4846BB290AA516F8ULL, 0x7F4DE8C27854CC0CULL, 
            0x1F07174891AA393FULL, 0xB946F7CCD06EFFC0ULL, 0x5AA7A1E44ADF20CDULL, 0x130F78A535DAA5F5ULL, 
            0xC4E9887B138C60D2ULL, 0xBCCCC4A1E83A3F50ULL, 0x46544A3E0762BE91ULL, 0x5699198CD35C342BULL, 
            0xD23423129CDBBAB6ULL, 0x2A5BF031A9989E00ULL, 0x47ED48F4E98AAA0AULL, 0x075335B7EE63853FULL, 
            0xFEA7BDB23361B7F7ULL, 0x5C75E3BBFCB6B96FULL, 0x1477CFB9D3A60548ULL, 0xB3E8FF2EDAFC7D92ULL, 
            0x06ACCFF483FE255BULL, 0xD3192D62E619187DULL, 0xECF7978F8F1CC47AULL, 0x001BF8CB1906C4D4ULL
        }
    },
    {
        {
            0xEFDF597CAE1F0A06ULL, 0xAE419AC4B24F85D5ULL, 0x846A24280AE8B135ULL, 0x31A4F0DD75F39F7BULL, 
            0xD874E6E69D98DDF5ULL, 0x1A18B94D65A76B63ULL, 0xC91358CF957D5E0FULL, 0x2C935C59DCBDAC88ULL, 
            0xC274C4AEB281A1AEULL, 0x44B91B8F72F81D7BULL, 0x4247EE7A294454E2ULL, 0x854B823525718161ULL, 
            0x3F4A96439533949BULL, 0x91B5DFAC39003FD8ULL, 0xA83DA503F71CEAAAULL, 0x2F34963D24CC068FULL, 
            0x4A5B0CA49BABFDE8ULL, 0x985E2E6EC93EAD32ULL, 0x13DC30B635C55E36ULL, 0xB459E246569C56C9ULL, 
            0x214B5BC5B96F4455ULL, 0x1592C3D2934BC18EULL, 0xAB50C791F17BCE5CULL, 0xED645D2AA0AC7AFEULL, 
            0xB223A5BBAB070C25ULL, 0xAC6CFE8D54BDC3A1ULL, 0x82E39E5C667F906CULL, 0x8198E36E7EAEF72FULL, 
            0x0C1A40586CBFE911ULL, 0x4490F415E1E61558ULL, 0x1DB554F54C79E064ULL, 0x67D8E1D3B213D752ULL
        },
        {
            0x24B6287330E19792ULL, 0x94B4F6A790CD74D6ULL, 0x5CA17121292C46DCULL, 0x3C374981F7D71C96ULL, 
            0x144E341FC9860401ULL, 0x80FB612C0B47E19AULL, 0xD9DCB00551217C21ULL, 0xD49705A0560298C3ULL, 
            0xEE9A4301B3405822ULL, 0x0F97B1A36027DC95ULL, 0xBF3B74BBBF01018FULL, 0xBBAF59166168B129ULL, 
            0xC906E2EAF383AAAEULL, 0x854A5DCB389CF24EULL, 0x5284CE9796BD7FFFULL, 0x3FCD1CF181A4E72CULL, 
            0x6C51ABFA7AE5B65AULL, 0xB717D3406256B4DFULL, 0xD46D73264823C233ULL, 0x836A042EBC8C3182ULL, 
            0x0BFF4AFCE616B46CULL, 0x3FE20EE2544A48D4ULL, 0x6F18C8E7600C9E90ULL, 0x3F206607D121913EULL, 
            0x4FD39590DBB3B4BFULL, 0x98A4C518B3403512ULL, 0xFFD987EB247EE893ULL, 0x09D7B36DBAB57A9AULL, 
            0xD0B3547D1527FE7EULL, 0x9B6AD1B8004B349FULL, 0x0D9639E364460897ULL, 0xD670B8BDC622F0FFULL
        },
        {
            0x69D49556A4E26684ULL, 0xCCFD75380799DAB2ULL, 0xB2DDC72151F6D5AAULL, 0x76747A875DC08266ULL, 
            0x3F6C17F81E9A5050ULL, 0x14F7F94D8C74F1F5ULL, 0xEC03F4DAAF6F30BDULL, 0x317B3275851F1DE7ULL, 
            0x401B8F1CFBE33F21ULL, 0x2B1E5E22697EB5EDULL, 0x5E1E3646645E78FEULL, 0x7572727310701DFAULL, 
            0x622F9CE8023F12DFULL, 0xE27DE0DC71301630ULL, 0x4D7C84F8361DCF8BULL, 0x6D57D9BE8373A216ULL, 
            0xFF23F56B4505CD41ULL, 0xEE6603E0AFF54946ULL, 0xF22B99051C41FE5AULL, 0xBB6AEA02CAC95772ULL, 
            0x589834BADF636E07ULL, 0x5900E3C8289C285BULL, 0x4B8522A65486D3F0ULL, 0x5FA4B2FDE6B12D9DULL, 
            0x672390B97B5C9AD2ULL, 0x1375801F0AB2473CULL, 0x8C28B8C7D05F437FULL, 0x84AC6382694366B5ULL, 
            0xD5A41C5BBA443565ULL, 0x3A77F84D35C86317ULL, 0xF1F87DA2E0B43F4DULL, 0xCBCE4F27278F51DEULL
        },
        {
            0x3D6D8AFC6B54EB7CULL, 0x3FAFDBE4022C224EULL, 0xC6680DDAA18A588CULL, 0x4C7A71488906C72DULL, 
            0x405E203FCBA2DBDAULL, 0x95AAB5C77A888579ULL, 0x2ED1DBD04D4B0624ULL, 0x5FD7B002B97F7190ULL, 
            0x3F0D853BCE536B51ULL, 0xC5221266E8645FD0ULL, 0x19B689692245A864ULL, 0xF79A2EE6654D414AULL, 
            0x804D8613F442EABBULL, 0x8D8A63C35AD50463ULL, 0x0A251AE6B1923041ULL, 0x0DAE90AC30147A86ULL, 
            0x2647BF61B2AAA5D7ULL, 0xFF4FFD22402E1E8FULL, 0x8FB38193F58DA43AULL, 0x1D17586F9AC32824ULL, 
            0xD4C2BB4DDE951E71ULL, 0xA5D225804B4F51E0ULL, 0xC26F0B9F7B4208D0ULL, 0x859ABDC0F431B2CAULL, 
            0xC8E9D6E6C4CF16C5ULL, 0xABC2717B03C634CFULL, 0x9B363FEA67887E1DULL, 0x04655CE8B276CBA2ULL, 
            0x89310C34429F987CULL, 0x35AEF92282FD728DULL, 0x93A84A612B33AD50ULL, 0x1E933CB25DFAA4DAULL
        },
        {
            0x6EF8A9A3A081A1FBULL, 0x701145F3E7EDDF49ULL, 0x276D2D2A8F457355ULL, 0x0AD0A63B44F01F57ULL, 
            0x1ADABE9CAD40AE67ULL, 0x91ACC4FFB0C81F5AULL, 0x0C1B88365531C8E6ULL, 0x1DC359C189E6343DULL, 
            0x61FD02D95CFFF137ULL, 0xA858A7A4843FDDB5ULL, 0x797754BC741670CEULL, 0xBF65F044B09D4E5BULL, 
            0x4383BFE60E0E14BCULL, 0xA377908932FD3DA0ULL, 0x44F1E47383AF2B53ULL, 0xE9E5E5E82EB1A602ULL, 
            0xC020FADCD5C41EE1ULL, 0x21580B5ECCAE2DDFULL, 0x35468D7557C942F8ULL, 0x5C59DE6EB70D217AULL, 
            0x385FB7FE94B28202ULL, 0xE6E11906CD20548FULL, 0x67182FF094FE5A9BULL, 0xF0EC78EE6A7419EBULL, 
            0xBF54AB573DFACAD4ULL, 0x4C8F28EF85C82C56ULL, 0x908BD41B7CE317BDULL, 0xB56ADCD0B4FD4F9CULL, 
            0xF0DD813E754082F1ULL, 0x1B8DF41361DF3285ULL, 0x3FD88C9D9C713B0DULL, 0xD4ADFB3478E393C1ULL
        },
        {
            0x8E387906341065C2ULL, 0x9C9B2785736B1B6DULL, 0x1799D3F532EEE2F2ULL, 0xBE84D45A67487C04ULL, 
            0x40995578EB97A68EULL, 0x73A181C643A2E3F3ULL, 0xC236AEBD57507DA0ULL, 0xCE4C73356E6F1458ULL, 
            0xBBF81F784CAA7E0FULL, 0x6CC7F9BC0C2BBAC6ULL, 0xBA8C5680D13A69EDULL, 0xAB0620E8592A5FE9ULL, 
            0xFA63BE5044DF7179ULL, 0xA58E6E1686F28579ULL, 0x30F92C483A993294ULL, 0x14F088CC0D930B55ULL, 
            0x6312F6278A0F487FULL, 0x33B8287DE5F1205EULL, 0x9D9D79FF5E988123ULL, 0xBEF3C40E19AFDB3CULL, 
            0x7CC8BFE130028B66ULL, 0xB9F5E7BD0DDCE6E3ULL, 0xE84BB0470337E51AULL, 0xF9CDD0E40A6420B3ULL, 
            0x8FD07D01D672E70BULL, 0xC8593C3FC3B15625ULL, 0x265E6F693253540DULL, 0x44477C9EE7B314F5ULL, 
            0x33FD5F0DBD028958ULL, 0x712C3DA687344D14ULL, 0x2DEDCBF3DD31D521ULL, 0xD80D0269BA681297ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kKeySpawnBConstants = {
    0x53CB268F485D560BULL,
    0x90E88590762CF8A6ULL,
    0x2817FAB41BEA0452ULL,
    0x53CB268F485D560BULL,
    0x90E88590762CF8A6ULL,
    0x2817FAB41BEA0452ULL,
    0x3D0896CB9F0B940DULL,
    0x3638BDACDF57FEDDULL,
    0xE4,
    0xF7,
    0x5A,
    0x5D,
    0xF0,
    0x60,
    0x53,
    0x51
};

const TwistDomainSaltSet TwistExpander_Achernar::kSeedSalts = {
    {
        {
            0x2042167EEEC33E33ULL, 0x29DE220E268DA8A9ULL, 0xBF05CF861443FF01ULL, 0x820FF8A846D70104ULL, 
            0x804E4DB6538C304BULL, 0xFF6A815478DB03FFULL, 0x33BE727F26FC114DULL, 0x74D101DD359C139CULL, 
            0x5B1E6AE7505F59F5ULL, 0x3E7C0C7DECE6E784ULL, 0x006C28EF18DF8591ULL, 0x7F819542F9A4AC3EULL, 
            0x842FC3E633779396ULL, 0x5278F284E756AC01ULL, 0x5972842C0DA50352ULL, 0xC92D5FCEF85FA4F0ULL, 
            0x677402A06B42F0D9ULL, 0x545E001FCAEEB58DULL, 0x1D0C2C4EA571F66FULL, 0x7D8692502FEC8461ULL, 
            0x4FF67768FD0124DBULL, 0x47AB88E29963C898ULL, 0x5EBF31BCCE6A3B84ULL, 0x59C59E492968C227ULL, 
            0x8BA19028979C367CULL, 0x920BD62FDC38086BULL, 0xE440B684E42B0758ULL, 0x494D1BCBD41FFAF3ULL, 
            0xBEC0D7736897F29DULL, 0xBA93BC15C4B0EAF1ULL, 0x4B8497F83CB63E69ULL, 0xF026393937BAA2D6ULL
        },
        {
            0x79EF61DE55B09C47ULL, 0xBCC3C102E8F92332ULL, 0x019F34C564AE1041ULL, 0x825AE862F6D981F8ULL, 
            0xA445CD7EE5F5949BULL, 0x32FDC18C97AE9D54ULL, 0x02D55831E247013CULL, 0x8A9FD99A50AA187BULL, 
            0x908AF7269CC5F903ULL, 0x39C5CB74E7142B27ULL, 0x6C0BE9D4846DA297ULL, 0x127FF25AE17BB6DBULL, 
            0x4A78BCE0585A8CA7ULL, 0x6DD17B5CF7D86EEEULL, 0xAE006F838DB69BA6ULL, 0xC82CBCA0CE4FDDA5ULL, 
            0x23CD95200181E35AULL, 0x6D6F4AE7B55723F8ULL, 0x80BBDC28C267CB57ULL, 0x1526F0B91BFBB229ULL, 
            0xD1F5B7A421CCAECCULL, 0x201927C9E22C02EFULL, 0xBFF805091554BFEBULL, 0xE7955DDE285F2480ULL, 
            0x74C559724DF6D76FULL, 0xF5677BFF6489FC08ULL, 0x6E36BB5B948ED995ULL, 0xFB777E29183A7411ULL, 
            0xF663620D263DEAF4ULL, 0x8152689C18AE2CDCULL, 0x40F29023A2FBF6D2ULL, 0x048643F3072CC9F1ULL
        },
        {
            0xFA53565F70D51A55ULL, 0x22BAAB02700A65ECULL, 0x97C63032BF789F81ULL, 0x0E1406CD25AEE462ULL, 
            0x8FE818199EA1913EULL, 0xEE5A8B19CEFCF25EULL, 0x96D8C85F40D686C5ULL, 0x7A020EE13FE6D6B3ULL, 
            0xC35346DC28ABDDE3ULL, 0xA73FFBA29D236175ULL, 0x33AF3599BBE989C7ULL, 0xD3D5070C99AF3CC3ULL, 
            0xE091D41BDB96EF42ULL, 0x32859C9F9911D63CULL, 0x6C13CD5B230C1098ULL, 0x09E017C87C47ED44ULL, 
            0x619B7BCCDFB66786ULL, 0x4BD37ED78308512FULL, 0x2D3CA702BE1C8724ULL, 0xC1F8F4B3057885C8ULL, 
            0xB911F56022628138ULL, 0x25A4A9BA18AB011AULL, 0xDDBC02297A3815E2ULL, 0xF2203D5E94A69B87ULL, 
            0x402245E869C1D1B7ULL, 0xD0C037D94AD60972ULL, 0x4311B7D509746653ULL, 0x416F6B10F671E09DULL, 
            0x56C8D247BD10A015ULL, 0x7350773D44021B15ULL, 0xE1DDC160BEC01478ULL, 0x9EFE0B1B44B9018FULL
        },
        {
            0x4D94985A9B471A54ULL, 0xEC5667122A9F724BULL, 0xD6CF595D9047D7ACULL, 0x32800E655104DBBAULL, 
            0xC3F356EFB5A7D0A0ULL, 0xBBD80F95A11472FDULL, 0x76E7CD42DB6ECA02ULL, 0x98360AAD8E0C7DCEULL, 
            0x305465987B9A3678ULL, 0x9D231AB0AB49674BULL, 0xEF83EDF56BD34A6BULL, 0x4AF5F3C8F63B75EDULL, 
            0x06FC3C620036E2C2ULL, 0x374163806236C85EULL, 0xC244083CDCB21852ULL, 0x514C0882AFC6FAEEULL, 
            0x634185EF56406686ULL, 0xBB8E315ACD082EC6ULL, 0xED2B1A2074DBB817ULL, 0x0FB2F3B61E6845E5ULL, 
            0x501CA0FEA6267BDDULL, 0x56E50A04042A4FDBULL, 0x2BC56F0DD77502D8ULL, 0x31F9F2A1B6D57B5EULL, 
            0x1C75873AA8E46A44ULL, 0x49286D39533FC39DULL, 0x6ACDB69E58F6CF3BULL, 0x042BE2492B0039CEULL, 
            0xF79468EBD90ECB27ULL, 0x73F2EF34EE24DB53ULL, 0xE806A15E034FAA05ULL, 0x561C3B16C42F7EEAULL
        },
        {
            0xAB953857B71EBC4CULL, 0x2E2C24CC983F8A22ULL, 0xB24B5F32520F685AULL, 0x11491BF0B704E629ULL, 
            0xA7BF2334998A010AULL, 0x5CFDF11A9613680AULL, 0x99D813D3267240CCULL, 0x203A238E987A3DDBULL, 
            0x1C48A27C43CB4F12ULL, 0x5A9462B2BA919FBFULL, 0xF7636463CF2A5F7BULL, 0x67003832A74AF67EULL, 
            0xD6BA9A5BF8441289ULL, 0xD9E72583BF7B1FF0ULL, 0xFA184C4E481524E5ULL, 0x6FB5AFCCF44B114AULL, 
            0xC1A3F9E7FB77D602ULL, 0xF55675F25410B44EULL, 0x22F027447CC088B2ULL, 0xD28FA7CBDDD85B30ULL, 
            0x5E6EBE6F83455C13ULL, 0x72EA9D6B639D7DD3ULL, 0xFD70618A54CBC42EULL, 0xA58D6359999BEC7FULL, 
            0x319904C49763CBD0ULL, 0xE7A8EF4C079F71C1ULL, 0xE3C7F9434612F6BAULL, 0x9562AE4793847A59ULL, 
            0xD2194105C3EB88A2ULL, 0x9D097A4E7BFBDDA1ULL, 0x7D81753BB5A86ADFULL, 0xFFBD9440080CC76BULL
        },
        {
            0xFC320FA4233BCAA7ULL, 0xBE89E8A94E41D668ULL, 0x4346CDB817DA663BULL, 0xA0ED41A47FF7DEB1ULL, 
            0xCA35A31498C76126ULL, 0x42EDB936EEF6C7DCULL, 0xA3188EDF85F11FD8ULL, 0xD9681490E4DD79ADULL, 
            0xF9BE99210EEB9C06ULL, 0x2EC0A99FB9A9EF26ULL, 0xB57C1C3205AE2236ULL, 0x865D4ABFA961889CULL, 
            0x389B572AF3B6D1B2ULL, 0x8C2CD011B59D59CFULL, 0x0C5665BE0E358F1CULL, 0x4CE7459D605A5099ULL, 
            0x1A33DE5CB14F8386ULL, 0xC0AFB02F0C2F00FFULL, 0x044AC0D5909DB002ULL, 0xCA50BA651954A6A1ULL, 
            0x9CFEE9554B8AB9FAULL, 0x8338FACA279DB232ULL, 0xD10E410CC0B75FA0ULL, 0x19D974A829A34580ULL, 
            0x036F9103F40BD1E1ULL, 0x60FA7C2ECE207912ULL, 0x40EEDFF9FE785812ULL, 0xD872CA1DFBEF9AC1ULL, 
            0x456AF1385770CDE2ULL, 0x657C1112EFA7C2E7ULL, 0x3C6B9F41DFB9555BULL, 0x74047539893AD212ULL
        }
    },
    {
        {
            0x71B08729AC2B2759ULL, 0x3DCEF99436412F35ULL, 0xB38325AA4B6786D1ULL, 0x04079CF4977DA979ULL, 
            0x0D69F471A654C25CULL, 0x9FD3F5508FCA970CULL, 0x4C7E2C76D7B5A22DULL, 0xAB4485DC79277007ULL, 
            0xCB12DB80774A8209ULL, 0x921D5C2DE2A96B4BULL, 0xC163C6743497366FULL, 0x77A2759F2B68A324ULL, 
            0x7DB1C7F5653CF783ULL, 0xE28F561E4459597FULL, 0xFB93431FA8348E38ULL, 0xAC530FA7446F8761ULL, 
            0xFFE4C9E93E6C807FULL, 0x2E742B72A5F89618ULL, 0x208F4495EBC3F504ULL, 0x918F4FE98AAB200CULL, 
            0xBBD32E7F026144B6ULL, 0x4B286D975D052621ULL, 0x851493BBD5293AFCULL, 0x3AB8C131268E63A1ULL, 
            0xE087D33A13C743E1ULL, 0xAFD4AA45C4A60DF2ULL, 0x64E04F70C7787967ULL, 0xAA1940A0A0BABB15ULL, 
            0x02151F6379160FD4ULL, 0xF2DFE84D28CC2BA1ULL, 0xC01E756D3FBCD7B6ULL, 0x8CA2F2CFBE396156ULL
        },
        {
            0xD5521C2A6555409FULL, 0x4FB031696C23F996ULL, 0x606B994F9F2E0FBEULL, 0xE6E23A3E90DD28E7ULL, 
            0xD4F1A165B117711DULL, 0x6DA5270B8ED03949ULL, 0x476DD68EFE80FA34ULL, 0x81050D3C00C38F7AULL, 
            0x8A87E8DD99C639D3ULL, 0x70BBC46043CE5B57ULL, 0xDECABBC1DE0D4CCBULL, 0xBA673E47C15FAAF3ULL, 
            0x58175EA3123E1B02ULL, 0x56BE9FB5FE0286A0ULL, 0x7A51FB8B4A47CB92ULL, 0x75330CF9D081F857ULL, 
            0xFD6B0A8F25EB744AULL, 0x6727BBB0833F5870ULL, 0x7F63A153241ED7B6ULL, 0xB5566F51205B795FULL, 
            0x8EF5B40025723698ULL, 0x0CB3F07BA050DAB7ULL, 0x183D4BD5F82CF8DAULL, 0xB40465C24BF9B9D5ULL, 
            0x101EACF4060C174AULL, 0x635A69A62C678975ULL, 0xE05BE15B99D6D77EULL, 0xD860456ECD0EC32EULL, 
            0xB49FB33A4C8A6FF1ULL, 0x6E874652D2469CF4ULL, 0x73690536DC693F2AULL, 0x03FD5FD06C52A0F1ULL
        },
        {
            0xE41A4357597704F9ULL, 0x7F38091931DA4308ULL, 0xBE79969084804195ULL, 0x308C6A47CBBA7B95ULL, 
            0xFEF571A6971B02ACULL, 0x12B2EBACD5ABB4E1ULL, 0x5DBFD20D32024075ULL, 0xB27130B6D725F807ULL, 
            0xD5B360DD320E2D83ULL, 0x6A817D1902ED1994ULL, 0xB0BE19D3B462B880ULL, 0x6AF88EEF09572B20ULL, 
            0x70E099144C2A9413ULL, 0x520791F605D68897ULL, 0x1CC2A3569EBBAA53ULL, 0xE515874F9D6A14EBULL, 
            0x8D56ED9CE5A4B82AULL, 0x1F0C72D3BF4EB8E8ULL, 0xDFF2C3EDCA20D322ULL, 0x1116F3CE331D14FEULL, 
            0xD5FF72D6DCCAC421ULL, 0x53F02B1552234398ULL, 0xA5FCAC830BF9D2FAULL, 0x0B6EA411CB06637EULL, 
            0xADDC03DEF58E3018ULL, 0x404EF38330232349ULL, 0x13C381E34E6B8D51ULL, 0xAB87F960523224F3ULL, 
            0xE4D91FE97C7A3F7FULL, 0x58D146D34F6484ECULL, 0x8BA10164409329FDULL, 0x9ADD14609984AD6CULL
        },
        {
            0x1F0D29ED3D72C1CDULL, 0x3841F02224C21AAAULL, 0x18FDA7972CC422CFULL, 0x551154755D041F82ULL, 
            0x6D5C46A0FE9B501CULL, 0x58BFEDCD01740B42ULL, 0x61ACF92FDBD25D55ULL, 0x217E51B5F9356745ULL, 
            0xE493D42CC639E8B4ULL, 0xBC2DC2F02B271553ULL, 0xC6847FAB4CE274DCULL, 0x3465712C6D4FC90BULL, 
            0x2A8012BC2FCD303BULL, 0x14EAAF188071D094ULL, 0x751F758A91B6566CULL, 0x07738FFE9B8CD261ULL, 
            0x33DB7F943D2BD0C5ULL, 0xB757D892593B1AEFULL, 0x9DA55FE55299F4CEULL, 0x208E8650D02151BAULL, 
            0x1170390E740F04AFULL, 0x493530F2096A1A50ULL, 0x71F7252CD7D42D68ULL, 0xDE1E759D01F9FCFAULL, 
            0x851BA69524D3ECF9ULL, 0xD2141439288FCCBEULL, 0x245BC65271EFF51AULL, 0x1CA853A2526D2DCDULL, 
            0x27118127657EB13AULL, 0x59F9BBAF2B605AF7ULL, 0x512590606928EA11ULL, 0x38FE7E516CB5FFD8ULL
        },
        {
            0xD83F528E0E4ABA1EULL, 0x1710AF843CC1CD97ULL, 0xA6B7DC77EADD7594ULL, 0x87835B78B2B2D703ULL, 
            0xD42B0805C8E18F1FULL, 0x598FD9E2D92C8DD8ULL, 0x9ABC61D16A730AA7ULL, 0xE5BD26243792A8F6ULL, 
            0x0377BA9444F5C57EULL, 0xFE97458CB94D38A5ULL, 0xB1B1B6BAE43194A1ULL, 0xE6A7CBC065917401ULL, 
            0x4C0D9DAAEA84E167ULL, 0xFA9DBFD20AE6BD21ULL, 0x4128536ADAAB3EB7ULL, 0x56294556522B2822ULL, 
            0x0D52ABEEA1AE7F8EULL, 0xCFB1A1F2E32ABCACULL, 0x1954486AF03930D2ULL, 0xB5B86166E96F08EEULL, 
            0xDF36041014E661A8ULL, 0xA7BAC077A6F4D38CULL, 0x88CA64B0DA92708BULL, 0x2F21C66DFFDEBDE4ULL, 
            0x39D09188B7B7C601ULL, 0x54DB68D4C0427ED7ULL, 0x895C6E275DA525D5ULL, 0x31A2201BA3E0EFCAULL, 
            0x280E244B86A1C672ULL, 0xD7D2FEB5C91BBC57ULL, 0xE8C0075E576E8E2AULL, 0x66FC49895C5B97C2ULL
        },
        {
            0xAADE5A5F08249D21ULL, 0xE69C27145EBDBE68ULL, 0xEF459B80999AA11AULL, 0xF6224D0363DB10E5ULL, 
            0x3E7359AFD1BC421FULL, 0xE39343E629D42CB5ULL, 0xD899F2BCAE7F8DE2ULL, 0x421518A2B1E3DF7BULL, 
            0x8A063C9E938CFB27ULL, 0x730F858F1BB294B2ULL, 0x465CB8627D127CB6ULL, 0x87AC432DFEF2F0DCULL, 
            0x94E1D1F98AAC32FFULL, 0x226F2AAA4AB5F0CDULL, 0xAEC6C658CC6EA5B3ULL, 0x7BB6D31B506A2F08ULL, 
            0xC11A557B2900DC84ULL, 0xE16A0D880F3A5DEAULL, 0x6B994D397D3D746DULL, 0x759E9528BF620C76ULL, 
            0x533F416995ACD522ULL, 0xD6747E0908C0D8B0ULL, 0xA6A7FD7193427B85ULL, 0x91CE0FF34D278C93ULL, 
            0xA70C15531CCD5C0DULL, 0xC1379975D76020CFULL, 0x9699221A660A91C7ULL, 0x3ECA4B4F682B6653ULL, 
            0x58A6427084910EB6ULL, 0xB8508EBA5DECE62BULL, 0x58EBC2E9B1CDA05EULL, 0x9FAF10F42DE99E5DULL
        }
    },
    {
        {
            0xD9FF39FD07525D32ULL, 0x1AB275D6E3942A02ULL, 0x1B61D09B88A3DFD2ULL, 0xD428C0979119705AULL, 
            0x6FAE265273CF4AA8ULL, 0x117CFAFAC1970CB4ULL, 0x839D82FE37EABB64ULL, 0x505DC1DC2F580B4FULL, 
            0x41F5DF29984C04C2ULL, 0xE2FE07313FD0D05AULL, 0x116FFB7CF1FF5B75ULL, 0xB10D2AFCBFAC5D6DULL, 
            0x8313417599FF17FCULL, 0x89A445DBA22BB9EEULL, 0xD1C9F9D32A2D9F3AULL, 0x91DE30D2D330E60BULL, 
            0x138BF88377117EEDULL, 0x4CE6CEDAED9CF4F9ULL, 0x865A82660FCAD1E9ULL, 0x96E402F8093F9828ULL, 
            0x6859785FB3ECA298ULL, 0x907F1D02DD213B9FULL, 0x81F9CBAA146DBD9DULL, 0x08BC8C3E06F2C558ULL, 
            0xD18F173C66D690EFULL, 0x179B052B9D2B9A07ULL, 0xA620DFA463435897ULL, 0x5C2B3F71EAD50E60ULL, 
            0x13E64AA710805B88ULL, 0x52548A39868C57DDULL, 0xF70DAF920921094CULL, 0xE21B9CB8ABB8BF8FULL
        },
        {
            0xCDBC72480173E640ULL, 0x0C4810DF55212C2FULL, 0x7CF78FBFCEBDC40FULL, 0x69CA25579663E1A4ULL, 
            0xD2EB3EBB35B4F5E9ULL, 0x06A4CC11B2390533ULL, 0x5C0C1BCE6AEA6405ULL, 0x272C9C32D6E00412ULL, 
            0x35543831CCD9AF51ULL, 0x85FF2F9A5A736D4EULL, 0x70374712A69A5DC3ULL, 0x8C741B09FF7C86CBULL, 
            0xDB8FD046261AEFE4ULL, 0xDEA95376CC197923ULL, 0x6295F45F124ED5CEULL, 0x08A68EE022CDA1FFULL, 
            0x74DAE45DE31438CEULL, 0x9601417C757F3024ULL, 0x3F85B168934BF7B2ULL, 0x402C3D2201AFB509ULL, 
            0x8A109A15BEA904F6ULL, 0x8C194B1D88B4602EULL, 0x80AAB2C46A061360ULL, 0xFF6CB568E9D6F69EULL, 
            0x193E9648809A049EULL, 0xC2B2C08F8206C3B6ULL, 0xE4C873B5C0DC81D1ULL, 0x2D598E2486033FC0ULL, 
            0x26B147380B8F0007ULL, 0x072322D1F16D6250ULL, 0x9ECA2EC5C9D8D6E1ULL, 0x5EE30091E5C745DDULL
        },
        {
            0x927EABF86E0F2EC8ULL, 0x4DF79D727A1CE93EULL, 0xBF6E735626C84726ULL, 0xFCB32F0EB5AA4EDAULL, 
            0x4737A5E71424D3ECULL, 0x2A2CCC59EE1E1C2FULL, 0x83635817A9904771ULL, 0x7EF3732CC6933B3CULL, 
            0x869606A67DB95D49ULL, 0xC7CE4EDAF8F42E70ULL, 0xCCE6BB5FDE4945A9ULL, 0x7DF5E833A8F01FB4ULL, 
            0x2FA4B69BB026177DULL, 0x35F9900BF5071902ULL, 0x30551DCD9675FF90ULL, 0xF289F8EA68156977ULL, 
            0x8230A55477A93FC3ULL, 0x0A2EFD49934D9C45ULL, 0x20263092E7C7AA03ULL, 0xEB2566AE9F901DADULL, 
            0xA994EE2703F5A48EULL, 0xF4BB617351C2017CULL, 0x133DFEC9F8385484ULL, 0x5DC31BE52DB1FCC7ULL, 
            0x9BB8BDD59A6F8A74ULL, 0x114B6D2650408D8EULL, 0x00AC373A09687ACEULL, 0x0C77941D18A27860ULL, 
            0xA123C03964941D51ULL, 0x583AAAB952E6D82CULL, 0x6D1FE34F782DBD52ULL, 0x5B00B18019700AF3ULL
        },
        {
            0xA48215F15AABE17EULL, 0xAE751B3E519C5AA4ULL, 0xEC87A5578D8E2D22ULL, 0x2205BEB6BD15CB28ULL, 
            0xAD6AE96E5612A585ULL, 0x8D0EBE80F00B783AULL, 0x986EF7EDD28AEF6CULL, 0x0D78D5E58BC61F1FULL, 
            0xF23ED9531427B192ULL, 0x98D3D3BA9E22A338ULL, 0x4EA1F47352A81257ULL, 0x9AD5703EE005F552ULL, 
            0x12730D246C89132BULL, 0x82C6C5B1A44E2F80ULL, 0xA25D53A780B2C42FULL, 0x656F0E99F74613ACULL, 
            0xA882A81AB1CABFCCULL, 0xED838ACA3B06D8A2ULL, 0x68B3D8DC0ACE6F93ULL, 0xB277897710F171A6ULL, 
            0x7BC8B3C4F59D10C2ULL, 0x6FE72FB6BCC3F4B1ULL, 0x3BEAC8657045AA85ULL, 0x2BC93F3552A451A1ULL, 
            0xD08101CB0FD8864EULL, 0x52A9599D41FF2CDFULL, 0x6BBA235B4B5B16A5ULL, 0xB3DA75E3317EBACBULL, 
            0x6E22489B4C81E98CULL, 0x2457BD31D9C003F5ULL, 0x22ADC4E56F00E107ULL, 0xA81CF7380457C206ULL
        },
        {
            0xA36E8EE50DE521EDULL, 0xD4B4B02277E245E4ULL, 0xD492CF181A477CBEULL, 0x362913A6C774943CULL, 
            0xFC59C6FD555421EBULL, 0x2EA977EB7C58FA03ULL, 0x79513233F1ADC5BEULL, 0x0EFF8362ECE08863ULL, 
            0x731F0E692CD7AD10ULL, 0x85051F8E57564400ULL, 0x1CACD2BA15F38516ULL, 0x0BCFD242799C3559ULL, 
            0xC04E7A9C5DF1D141ULL, 0x0F6AE94E18AD6782ULL, 0x67AE13F35AB56FFAULL, 0xC4B97D433BD21103ULL, 
            0xFB9F8CCF95BA101AULL, 0x55A600662B8325C3ULL, 0x04CF81F3B683758CULL, 0x9AF51CCD019DAE08ULL, 
            0xB6BE89EEFADF63E4ULL, 0x9A94F0C66E723A1AULL, 0x9E82D21CB28736A4ULL, 0xC99DEA8F8D33BEF1ULL, 
            0x3D4B2F24896D914BULL, 0xCB4A825D7C5DB101ULL, 0x4D3C44191CF96707ULL, 0x2A05676E1C8F55D3ULL, 
            0xF67B0CA88224472EULL, 0x9EC7A3161E6CF107ULL, 0x6698623F8B23DA31ULL, 0x74B6CE2FAC69B1CAULL
        },
        {
            0x11419232D0E25FBFULL, 0xEA083DF38DE30306ULL, 0x73B9D6F14E7AA4EEULL, 0x744529FE27B61B0BULL, 
            0xAA20D62C48A48B83ULL, 0x87D1260B53D823D3ULL, 0xAC3ECD43E34BD40CULL, 0x099112A6ACA7735AULL, 
            0x667E7B246E1C5B25ULL, 0x5289815D04CE0B36ULL, 0x1525D59ED09D8002ULL, 0xB5A80D59CF3AE65CULL, 
            0xEEC79623C68840DFULL, 0xF1D9928942EEA273ULL, 0x6F622DA9E79BEE6EULL, 0x1368B6FC2E1C9F80ULL, 
            0xEF13CFAF8945E24DULL, 0xBCCE83798FF267F3ULL, 0xBB0DE44896966008ULL, 0xD1E1CA4057C9AC66ULL, 
            0x7F88E87AC32269F0ULL, 0x9F5593FC24A0A63AULL, 0x9CD3D0B488FA8143ULL, 0x4A0FD34F4A2705EFULL, 
            0x12E2A76CCAD8D0EBULL, 0xB4B52E3F5CE51D7AULL, 0xC1B094E79AE6B786ULL, 0x4C940F2A86D39EFBULL, 
            0x81B83DA6957DF5FEULL, 0x12D9F4743307B4F7ULL, 0x5DDF165129BC8CDEULL, 0x161609D05ED9FC29ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kSeedConstants = {
    0xC782CF3F6E59024CULL,
    0x1FBFDBEEF7F0FD80ULL,
    0x90241918EBE11FF8ULL,
    0xC782CF3F6E59024CULL,
    0x1FBFDBEEF7F0FD80ULL,
    0x90241918EBE11FF8ULL,
    0x7921736CCD1467AAULL,
    0x9667C2CE9791B9CFULL,
    0x3F,
    0xF2,
    0x94,
    0xF7,
    0x3B,
    0xA1,
    0x55,
    0x1C
};

const TwistDomainSaltSet TwistExpander_Achernar::kTwistSalts = {
    {
        {
            0x9F84E5CAEA2FEC81ULL, 0x39D2BD42BA62631BULL, 0x2DC5959E38C2F67BULL, 0x75CEC89F00A66975ULL, 
            0x3B36688D048037CDULL, 0x53199E9BE5465507ULL, 0x657586EFC9666602ULL, 0x72AFF77B85ECA65BULL, 
            0x7C003EB880740129ULL, 0x348C2FB48B5D4F4DULL, 0x76743E0A34C2AF1EULL, 0x6DFC4041898FC699ULL, 
            0xF28802125897735EULL, 0x71ACD2580921F46EULL, 0xAB228954EB4EB5C7ULL, 0x642EDF7BD38EEB2CULL, 
            0xB410374BF34AE748ULL, 0xEE96D7D0FC34A912ULL, 0x4D88486E4421C4AFULL, 0x7A9A611BCFCFC4E4ULL, 
            0xB66BE16F23B7B84CULL, 0xFA3E28226D478542ULL, 0x922A0C69FE71243FULL, 0xE8BC64F25305A744ULL, 
            0x9AE856FADC9CD2C9ULL, 0x1CCC0F84E30ED238ULL, 0xF375FC4A0EDD5A9FULL, 0xACAD943F0BE97829ULL, 
            0x27D37BD726B4CCB0ULL, 0x02124C7DED33DE15ULL, 0x8A74802C7DA43544ULL, 0xE4D63CD940D39B97ULL
        },
        {
            0x43B13F2D13668C3CULL, 0x27D4CBACDCA7764DULL, 0xE14D7D2DFA7A6728ULL, 0x479EC9FA0BA2248EULL, 
            0xB055F629FEC1DD04ULL, 0x86832F33F6941468ULL, 0xEFF02B90274A7578ULL, 0x3437028952DE6817ULL, 
            0x688CAAA188401D88ULL, 0xB5FBCAF29D01D885ULL, 0xDA610BE73B1DFD9CULL, 0x2C6212E32406E5D2ULL, 
            0x79348FB7643768C6ULL, 0x94E1517AF2BE7D1BULL, 0x9F9B48762D206009ULL, 0xF4CB1502D3E4D7B7ULL, 
            0x2477D780CC276B27ULL, 0x6129EE7417852A13ULL, 0x1C4AC294858081A5ULL, 0xE4C83F72207029BDULL, 
            0x518A84B050B796FAULL, 0x7206F6399FABDAC3ULL, 0x397983A63B7C726EULL, 0xD9A163A5BB6D0420ULL, 
            0xACC0E98D19FE45D5ULL, 0xC64474502AE1D1B1ULL, 0xC99472FCA5AEF149ULL, 0xD1E4386EA3D22DC7ULL, 
            0xFB3DAED2C7F2FD14ULL, 0x3B55D1D8B7AAFA1DULL, 0x612C4744C7452428ULL, 0x085FECFFEAA686C4ULL
        },
        {
            0x143F2D971AE2F9DBULL, 0x5DC321586F9F52A8ULL, 0xCD0997227746763FULL, 0xB7A29D1A5CAE7AB4ULL, 
            0x818F5524C07108C2ULL, 0x97E2008DEA93AC15ULL, 0x88FCA1828F45C078ULL, 0x8853D7D771DEB206ULL, 
            0xEF01CD60A61B1770ULL, 0x984A218913FC2F2DULL, 0x67EE51D92A9AE03DULL, 0xD04B6E1E72B1BD63ULL, 
            0x2E8F86B1B025EA10ULL, 0x90EB4129BB1EA74FULL, 0x75D1D10B752EEE50ULL, 0x8AEA6749AE0DDB43ULL, 
            0x6F64AF731D9CF670ULL, 0xCCF1DD5A9BBE8A85ULL, 0x991E5609A9961D09ULL, 0x5982EA9B373F3192ULL, 
            0x4AE32AE14CF44DA1ULL, 0x9BCE3A75B5834187ULL, 0x3E33335E3EEA1434ULL, 0xD5A5B60DE1F53089ULL, 
            0xE65F5A6EBA06A011ULL, 0xAC31E12759B4E8FEULL, 0x13F1BF9EAA8AC133ULL, 0x04C201D4897882DDULL, 
            0xC9DCB34A1602BA70ULL, 0x9692CBA21E096AABULL, 0x07A582A81D56D961ULL, 0x96C5B397E9E37661ULL
        },
        {
            0x21CC26C191F06BC2ULL, 0x9E07D2B762A9D2C9ULL, 0x1F5585BAE9B55C19ULL, 0x349EE1CD97451201ULL, 
            0x827D2868BB3E28B8ULL, 0x76579D33B1CF8C5AULL, 0xFA06D3A4AE9213BFULL, 0xFEAD8C335103F702ULL, 
            0xCB26B8E6D72AA054ULL, 0x4F1443FC5418177DULL, 0xED96E98FE2057DA0ULL, 0xAA32E5984D86B248ULL, 
            0xECA1368114D33EBBULL, 0x2AC211A49A23ECE0ULL, 0x9D06830251B8447FULL, 0xB9E77B487A8D5E0EULL, 
            0x82132C358C231F12ULL, 0x024C675890B1EEC0ULL, 0x247081E2C18BE18BULL, 0x9A780D4C29EDC9F4ULL, 
            0xF34355DAB9504246ULL, 0xABF404B476C93E73ULL, 0x564171678DBD194BULL, 0x8D3F2CE39354DE82ULL, 
            0x6BBEBBAF479CD547ULL, 0x4D30529DD6D27824ULL, 0x8686311B5F8C27E3ULL, 0x23637741AEC1D431ULL, 
            0x8933DD1E8A48216FULL, 0x7BA711A1D71FB8C7ULL, 0xB68B159A97A39BC4ULL, 0xA3BAD9D537F920D9ULL
        },
        {
            0x3FB43B82AE169ADAULL, 0x3BE9B4A70D8CE455ULL, 0x104F1B2FCD5F4FC5ULL, 0x5E1C7CDBA24A8711ULL, 
            0x669B21DF55801A1EULL, 0x17DBA63D89E7B697ULL, 0xA751CB76BC429F56ULL, 0xAEBD65B45349B8C6ULL, 
            0x071BE64D82D785A3ULL, 0xD5A93B947CD96B63ULL, 0x94BC667E1C1EA948ULL, 0xDFB4F83795E2A002ULL, 
            0xE17DF9673EC71608ULL, 0xA15E4AC9FF16ACF1ULL, 0x64FFB44B20CA0F7BULL, 0x80A9EED4B582BCBFULL, 
            0x21C53625FB5EDA2DULL, 0x50A33A9AC34DD3DDULL, 0xB6B942588402499AULL, 0x968CDAD959D99B7BULL, 
            0xB8DBB8B2F4ABE07CULL, 0x6798FA615F6FB213ULL, 0x9E468A750B640909ULL, 0x8B50E3832F7DAE75ULL, 
            0x61C0DBA09F0A84C1ULL, 0x8C8038727AA4B84BULL, 0x8FB577DBF02466E2ULL, 0xAB0BA42C2E135BEBULL, 
            0x39B3D6CE22C4639BULL, 0x6AE7410BF363BB4CULL, 0xD6805F62906F62F0ULL, 0x4FEAFA931964191AULL
        },
        {
            0x812DCE7F496BA761ULL, 0x90F208E8346A5B3AULL, 0xCDB557F4E93BED66ULL, 0x3BC84DF5E69D76F0ULL, 
            0xB584F249B54CA8E5ULL, 0xF626DA2F5FF5D9C2ULL, 0x08F0A2AA4EE9B955ULL, 0x788D4CC3D52FAE7AULL, 
            0x405F7B2AB2365A79ULL, 0xA787B4E31EDEEF5FULL, 0xA391B266CE298384ULL, 0x51E64E0EBCA568FCULL, 
            0x8EE64D16C4E7215AULL, 0xFFFE5285F12C774EULL, 0x6577BF2D5D9EF1DBULL, 0x2CEC539DB5FA9D3DULL, 
            0x08C67C8D9B41A19BULL, 0x27B62F80D709DBCAULL, 0x74A08F33100107F2ULL, 0x6C7747522FC4CE96ULL, 
            0x2F6ED9EC64613265ULL, 0x1C2DD77175CF6A42ULL, 0x15DDF476275AE3A0ULL, 0xDDF51CF371419A10ULL, 
            0x9803A5585DF45928ULL, 0xA937880648822E2FULL, 0x8764B3E21FBA4250ULL, 0xD674B399EC4C09EFULL, 
            0xA6BC463FF83D7F08ULL, 0xE5C116B8E1F49A23ULL, 0xD5AA61C2FCB8CFA9ULL, 0x8134039AC3EBF783ULL
        }
    },
    {
        {
            0x44FE9C516F41B66EULL, 0xD889FDB8F01CB7BDULL, 0xA32070ACA7EEC69AULL, 0xD9D4040B63DA36CFULL, 
            0xCD137984CEEA74D3ULL, 0xE202BBDC561221B4ULL, 0x3934BC6BA9E785D0ULL, 0x7ACF0AF717074325ULL, 
            0x2CD52574D7C54E2BULL, 0x3B628CAF6F108CCEULL, 0xB9BF303E1971BC32ULL, 0xD507959CC292E2C2ULL, 
            0xAE8240B0A887FF13ULL, 0xE14A0CFC48E8B817ULL, 0x441139B89D4A0861ULL, 0x39DB0EA54743040FULL, 
            0x9F64772F20FAACD4ULL, 0x745A758384A0D03EULL, 0xF5B1E5FA06841ADFULL, 0x30A09BF85BA936D6ULL, 
            0x2015A8BC826D4BADULL, 0x82F694F43C0DB0FDULL, 0xF8D9311421ABA911ULL, 0x3B1976C03082836BULL, 
            0x12E95723BC6A2DC3ULL, 0x02CC53913D8C9BF7ULL, 0x9FF641B398F7B9D4ULL, 0x4CC363CE3A24728BULL, 
            0x8D511B4C3B8DF2A6ULL, 0x9BB1CD2F778E542DULL, 0x893E667A432412ECULL, 0x6D374BD056234415ULL
        },
        {
            0x525CBAD412E078E7ULL, 0xFA3ED3CD877CBB24ULL, 0x57293C40B9E0E5CCULL, 0xDDB6AD41FC6EAED3ULL, 
            0x18690032DB120152ULL, 0x8351F768D55821BCULL, 0x086136DA6176D526ULL, 0xE120561CCFB71E97ULL, 
            0x3D437889D580CA39ULL, 0xB7F2E02577945315ULL, 0x27D32041AA15172FULL, 0xB7A904445ADFA216ULL, 
            0x5372AEE5256B1E89ULL, 0x19214ED3048865F0ULL, 0x3F76EED104BE4FB0ULL, 0xA9AD879913C86DBDULL, 
            0xFC8C568A0AC510BFULL, 0x577E17B22FDBF0B4ULL, 0xF689E13CF9E37EB9ULL, 0x39FB328A1254A566ULL, 
            0x0CAB2DC1657E4EEFULL, 0x80518B3BB8F0CCD5ULL, 0x84AD19EF6BF9F269ULL, 0x5944470280F4F398ULL, 
            0x8E7872E84F68B5FBULL, 0xBDC1DB6D511F901EULL, 0xAB49127EC5A810FCULL, 0xF82DFC85C416B6ACULL, 
            0xC52245DD1DE793E4ULL, 0xA0C3200C3F4BD08CULL, 0x2739478D673E2855ULL, 0x558685B53250048BULL
        },
        {
            0x7BB2722E63626AFBULL, 0x64BCCCD48BB8B01FULL, 0xC1C1059BF213EE54ULL, 0xC67752D227CA2AC5ULL, 
            0x6B6FB7FD6B83FF09ULL, 0x7AF53D70D0FE20D0ULL, 0x8B349C06430E384EULL, 0x5831D32C41C16173ULL, 
            0xBEAC76A5B9D627AFULL, 0x6C803703AED459B2ULL, 0x86D20064C01D16A4ULL, 0x64DD9C268E690E31ULL, 
            0x235E7C823AC2C2DCULL, 0x178B65AB2049390FULL, 0x351EE90B4149309BULL, 0x83F32ECEDB3922D0ULL, 
            0x72330329EFACD9DEULL, 0xE1B36004FB719D5CULL, 0x36723901C88008A7ULL, 0x559A9B160508FD89ULL, 
            0x73CBEBDB9D059C7FULL, 0xA56717D38762131CULL, 0x4A08A655283941CCULL, 0x927A15862C662A32ULL, 
            0x7266E2558274172BULL, 0x2202CDA7291510BAULL, 0xE36415F191D2EB05ULL, 0x0A2A0560A111D2FFULL, 
            0x170D29ECD167064DULL, 0xD2C53CEB144BF733ULL, 0x0487846C33CD5603ULL, 0x16FA60F6F3FF3847ULL
        },
        {
            0xE334A0DEF34EEC8BULL, 0x310ADC551113F5A4ULL, 0x46ED69987AB7746EULL, 0x72749458FA14CEF1ULL, 
            0xD77F7AE076DD39B7ULL, 0x1021149B7296AD97ULL, 0x8C084EAF666D6E36ULL, 0x0B7D601D81083907ULL, 
            0xCC3FC945D1C9504AULL, 0x37CA2A8760214B96ULL, 0xEE44638DA098BC69ULL, 0x16C5C39D4776759EULL, 
            0x23D9656035657202ULL, 0x8CD3DCB4631EBE1CULL, 0x4DD3D2333B500A81ULL, 0x6ABD411360C687B6ULL, 
            0x4BBD4311A6308394ULL, 0x011CF2F9DDFE4951ULL, 0x2787195E1FE1E20CULL, 0x2110ADE02C5763ACULL, 
            0xB6CCA783595F3B8FULL, 0x52EFAE64FE797EC6ULL, 0x0931B6F93D6F1FE7ULL, 0xB7F89837FF3352D6ULL, 
            0xDFBFFB64BAECF103ULL, 0xD918984EF66353CFULL, 0xCB2AFCE94A203A2FULL, 0x9B797D92A437B8E9ULL, 
            0xE92010466C8D2BE3ULL, 0x83F2DDBC10A5241AULL, 0x745DC5EF9DCB9419ULL, 0x45260FF5DED17FFAULL
        },
        {
            0x274C20128F89E503ULL, 0x8A548C78E26B78DEULL, 0x5A2AD1F1BBD2CCD5ULL, 0xE4DE4D90BBB19CA1ULL, 
            0xC36870BCE75B99D7ULL, 0x8B3AEA43AB9205FBULL, 0xB2B3703464DA860EULL, 0xB0CC32B7F9A8E471ULL, 
            0xE80D690DD51D86BDULL, 0x0EEA949F0E1367A1ULL, 0xDB82676189EA6E61ULL, 0xA2CFE9448405B53EULL, 
            0x094389A9E2C38C67ULL, 0x05AE50F9FF92EE55ULL, 0x03240FC1CB883F08ULL, 0xD40938AA1A9C20E5ULL, 
            0x85169259CD9E2677ULL, 0x8E7029BF624CD492ULL, 0x5772D190E18C7ACAULL, 0xD515621500A1CBA6ULL, 
            0xC85443089781AB74ULL, 0x7C05A9B35F1ABF87ULL, 0xB9730832B2EC13D3ULL, 0x47EE875639EC5FC8ULL, 
            0xD791F3042BE22CB7ULL, 0x5F47BC1606205AFEULL, 0x24F4B45CEC3D2851ULL, 0x01D87E68457CB51EULL, 
            0x518C435D826F68DDULL, 0x68A8F1BEA8D430E1ULL, 0xCE8FC436FA88447EULL, 0x884785BE43F5549BULL
        },
        {
            0xFBB8EC1B50C114F9ULL, 0xAF843D0AB3BA79B2ULL, 0xDD45702B90F22676ULL, 0x0D916F836D421957ULL, 
            0x55609A7FACB7EE00ULL, 0xBBABEC8105666F5BULL, 0xDC31A48FC2FEDB4EULL, 0xE469B4B4537CCD53ULL, 
            0x65BE71C1453AF5F8ULL, 0xFF1CBED97B2E4BBAULL, 0x575F4BAA041ACAEEULL, 0x6D220FCC4F4E39B4ULL, 
            0xA55477D23F96C0BEULL, 0x143F2B856BB3C8EEULL, 0xBB981465A3E1C302ULL, 0xF5B977329C5B2E25ULL, 
            0xA1A2260013CB121DULL, 0xAA834B3BF136D813ULL, 0xCFDD4D2D0A1D51B3ULL, 0x169048C5A5789DDEULL, 
            0x9CB6FFD6D79E7604ULL, 0x112D022221392B0AULL, 0x7137283E385CEB50ULL, 0xB1170C0C1C823DC4ULL, 
            0x34A973B2A89C44C9ULL, 0x981ADDB205E5EF18ULL, 0x2B08F8775EAA2588ULL, 0xBA8CF2710776677FULL, 
            0x4EAA19A8C936A95AULL, 0x457B1AD7B8F25F42ULL, 0x3D3B157F140A105EULL, 0xE895533A6D914FA4ULL
        }
    },
    {
        {
            0x20FCF024CC57E056ULL, 0x26CD351974D24535ULL, 0x891A67CD7918ACBEULL, 0x9B8E46F94687C8E4ULL, 
            0x1E2E2EB02A17826AULL, 0x8C65E3A5A0D64444ULL, 0x500AE64BC3EE831EULL, 0x6A1365FFAA93DDB7ULL, 
            0x816FA19B17BD1D66ULL, 0xF4A137CF66765538ULL, 0x364F75E343D41F45ULL, 0x54EF6A621B753E18ULL, 
            0xBB8FA52B27B22CE1ULL, 0xECA7C97ADDD42219ULL, 0x11957F3F79F6EE24ULL, 0x4F32D1BC8E7C855DULL, 
            0xC7F3B4A6D076F60EULL, 0x6CFA96D5FDAD47AAULL, 0x5205997D450E2402ULL, 0x76FE2C8F9A714CBAULL, 
            0xC0F8EE31A5E433CAULL, 0x21CEA137B72BBC55ULL, 0xCAB291B8B309B275ULL, 0x9653CB090B135B58ULL, 
            0xBAD6AB3D31FE7CDBULL, 0xD8EB4EDF90CC8D15ULL, 0x7BFE765CF1417E25ULL, 0x3353DC3D2A7CE1EEULL, 
            0x45988594D79B99A1ULL, 0xD78F1A7B965036FFULL, 0x76DB4EF143808F33ULL, 0x9874A5C91EBC24F4ULL
        },
        {
            0xCF0A1A8AF930CAB0ULL, 0x878F22D908FBD528ULL, 0xCF4B683473D6EEF1ULL, 0xC5BC8C5EE64DF1BBULL, 
            0x9CC5154B24A104E4ULL, 0x591D592A6EA328C4ULL, 0x9A401A66BBE6C3B3ULL, 0x3315A9D4C6DAB3B9ULL, 
            0x451D85926121BA75ULL, 0x3ED20FBA62E59CC1ULL, 0x5A9E34E993AD69CDULL, 0x8B51CD7E20699DF5ULL, 
            0x90EC99309632B13AULL, 0xFA689BE1BD1F8B3FULL, 0x37087DA61AC5DF83ULL, 0xD14188E60028868AULL, 
            0xFCC4A730EC089E48ULL, 0x3D07EDC3451E6D8DULL, 0xFFA9259A1D080A4EULL, 0x5C69EE6B05D32260ULL, 
            0xBED1A465FFD3EF4EULL, 0x82330BE0B3B2C22BULL, 0x7179446A8F288B4DULL, 0xF590991B46B62FE2ULL, 
            0xDF2C376E5C4AE355ULL, 0xDBB7E59949278120ULL, 0x83951A832AAB7D66ULL, 0xD0BAC7FB8E1EF5A1ULL, 
            0x3C7C96FD6564A470ULL, 0x29CFA192D46D7746ULL, 0x13E6D1CD23373339ULL, 0xE5350180697C80CAULL
        },
        {
            0xB3D4BE2DFBF48C82ULL, 0xCDB93D5FB1A034CDULL, 0x4524A8DAB04D11B4ULL, 0x510FF62D3894843CULL, 
            0x8813D15DCE6788A2ULL, 0x27202A51F710D27EULL, 0x69C45AA00AA59D4BULL, 0x748779E0DDA50EE7ULL, 
            0x66D6FCC03FDF0AA5ULL, 0xC8C29FFC43F8FE84ULL, 0x888FC5230969F121ULL, 0xE4AA759044A040FAULL, 
            0x2D64ED220B31C39AULL, 0x9197977F823E0BF5ULL, 0xD32E087009F2F49EULL, 0x822ABC520E6B4A53ULL, 
            0x757FC74F2EA80191ULL, 0x4B47357B1041A446ULL, 0x4B9C078F4200BABFULL, 0xF7410F295058D445ULL, 
            0xAA8D17929530084DULL, 0x95C671D1FBBE603EULL, 0x301115A4A99E7FFEULL, 0x6AFEC4A9F3DE746AULL, 
            0xAF2F05F1BD4F346FULL, 0x19B6023ECC0256D4ULL, 0x892D8C4E8CECCE22ULL, 0xF0B2333EE24BBD1EULL, 
            0x8BDFBACB1E4507B0ULL, 0xA76DFDBF069846C6ULL, 0x1B4FB22ACDA30A35ULL, 0xA07CA06F8F2F1E64ULL
        },
        {
            0x6C7DBA6E57CD3D17ULL, 0xB1700280E628C12EULL, 0x494472E7D4F8952BULL, 0x0667CDE8034BE70DULL, 
            0x3B3D0DC6C94F5424ULL, 0xD3691E99D15B164BULL, 0xB16CCA48E2DC9056ULL, 0xF5C8B1912812F00AULL, 
            0x8DA1BFAF4EED9491ULL, 0xABDA1A21ED0DA27BULL, 0x6541D87FCEB7D7A2ULL, 0xF07FC85D3099B31EULL, 
            0x61A62CA99AE05687ULL, 0x78B99CEA219563DEULL, 0x54C9166AA1611B59ULL, 0x662EF6CD0AA575B1ULL, 
            0x2EF29B8B68BFC69CULL, 0x99BE346B714BB648ULL, 0x6D0F98C22EADDED9ULL, 0x8837D44EDA5160CEULL, 
            0x9CFC7B4170AFE968ULL, 0xE4A61751BAC0B68BULL, 0xB6F316A7A4038563ULL, 0x21E879D84BF3CF8DULL, 
            0xA98F671E7287663FULL, 0xE0CBBF680E5DFA03ULL, 0xD212FAB47731E4FDULL, 0x7995AB4D66B8C6DAULL, 
            0xD7DA7A85B3EA3202ULL, 0x9F88FB922704F870ULL, 0x33A16C5AE0E4F487ULL, 0x88DB39FF02FEB2B6ULL
        },
        {
            0xE97DE8FCD605C56BULL, 0x72CBB9D6A36D58EFULL, 0xE3BE635F183E96B2ULL, 0xEA6424C5EB5D5BA3ULL, 
            0x25D66CC280344C0AULL, 0x073DB317BFA856B5ULL, 0xF68A92431D966CEAULL, 0xAE85AC1C90DCFF13ULL, 
            0xA7E1D33EE86EFD74ULL, 0x1CFEF55C5EACC886ULL, 0xD60304A7B0F6165FULL, 0x6B8366B9D645D033ULL, 
            0x4E9FA8DF2AD9FAC1ULL, 0x377F7D259B462BDDULL, 0x873696B9350CDD17ULL, 0x5FF53BE8AD2E79C9ULL, 
            0x0951BC44E0E23298ULL, 0x55E49505CAEEB8F4ULL, 0xDDA251E2EDF90E1BULL, 0xB2111FFF38EEC195ULL, 
            0xC49368388B06835CULL, 0x012D7229FF9BA3A1ULL, 0xCC5379F3C2846BDEULL, 0x45CC9F47BE49055EULL, 
            0xCF6056E3B0D1AB3CULL, 0x12B1CFB9C3179552ULL, 0x97A40BC020B94058ULL, 0x7360A73923A8B406ULL, 
            0xFA387D98F770002DULL, 0x927EE511E266ECA6ULL, 0xABF3939AF4A12F44ULL, 0x9131BC1C35CD2D6DULL
        },
        {
            0x155A37618E90B8DAULL, 0x6094C9904BEE4820ULL, 0x256848930C3AD08DULL, 0xA84AEB4716AE3048ULL, 
            0x5E7F7F4C5B5407D5ULL, 0x7D387D1EA4984885ULL, 0x93475F831C457F7AULL, 0x928B05A088409195ULL, 
            0x9042DB7C66B28378ULL, 0xEA2EA72E158E4E82ULL, 0xC36120C51BF295F8ULL, 0x43433DA11689B308ULL, 
            0xFD1050BF178918B8ULL, 0x204E6E2E8B7D8036ULL, 0x6675DD451C949E0FULL, 0xE1A4A7441953227CULL, 
            0x7FBD4E77F28597AEULL, 0x3572A23505F986D6ULL, 0xFAA7EF83F5136243ULL, 0x221A2A7B66145EFDULL, 
            0x0AD67822294F3056ULL, 0xECFA073220FC5C08ULL, 0x15B6DA4AF553D497ULL, 0x008CD0282A3391C9ULL, 
            0x5D66AD30B0B52AD2ULL, 0xF723E633B674661FULL, 0xE4E3A6018289B781ULL, 0x492BA705550FEE76ULL, 
            0x342F9164003D8488ULL, 0x5807423E7CD6AE30ULL, 0x0ED664151D4453BCULL, 0x41E3B2FC35D1BA47ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kTwistConstants = {
    0xF4F12D0C2A3684D4ULL,
    0xC2AACA70678200A7ULL,
    0x52F64467D0043D87ULL,
    0xF4F12D0C2A3684D4ULL,
    0xC2AACA70678200A7ULL,
    0x52F64467D0043D87ULL,
    0x7C875E3445E48C59ULL,
    0xE9A8382D0181E7F5ULL,
    0x1E,
    0xED,
    0x47,
    0x33,
    0x68,
    0xA4,
    0x0A,
    0xB1
};

