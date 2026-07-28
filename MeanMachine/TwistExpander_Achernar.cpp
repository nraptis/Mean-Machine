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
    std::uint64_t aPrevious = 0xB425C169377EA074ULL;
    std::uint64_t aIngress = 0xBF14CC8E4DB950EAULL;
    std::uint64_t aCarry = 0xA6AB2E6985EA773FULL;

    std::uint64_t aWandererA = 0x9E2D91C034E0BF42ULL;
    std::uint64_t aWandererB = 0xE2EA50D3560D3742ULL;
    std::uint64_t aWandererC = 0x86CF3DE33E3D5653ULL;
    std::uint64_t aWandererD = 0x968959E971A331FDULL;
    std::uint64_t aWandererE = 0xDCCFE5B9A0C7FD02ULL;
    std::uint64_t aWandererF = 0xE1869B02D5B1CE73ULL;
    std::uint64_t aWandererG = 0xBC4D6B23362C7EB5ULL;
    std::uint64_t aWandererH = 0xE3107B0A4105B4A6ULL;
    std::uint64_t aWandererI = 0xB7B511CB505AAAD3ULL;
    std::uint64_t aWandererJ = 0xC9ECBC938866C153ULL;
    std::uint64_t aWandererK = 0xD20A57B8A0731A7BULL;

    // [seed]
    ////////////////////////////////////////////////////////
    ////////        KeyRotate A
    ////////
    // Reset ARX state for KeyRotate A.
    aPrevious = 0xB0077797DE448ECCULL;
    aIngress = 0xF59FE82070830F37ULL;
    aCarry = 0xEBC6CC5D60EB7A90ULL;
    aWandererA = 0xF4A3210789C7F38DULL;
    aWandererB = 0xE0374752B9F0B394ULL;
    aWandererC = 0xA4B4F44F3A39BF16ULL;
    aWandererD = 0xD2AE3EACC21E4083ULL;
    aWandererE = 0x8358F879D2A727B5ULL;
    aWandererF = 0x894A613940DAF6E7ULL;
    aWandererG = 0xB531F02E32B322A0ULL;
    aWandererH = 0xF79C7C8E85AC332DULL;
    aWandererI = 0xA9FA6F7991393E3FULL;
    aWandererJ = 0x8DCEECC3F20B5910ULL;
    aWandererK = 0x8159601AF4D2F774ULL;
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
    aPrevious = 0xCE25BD847CC84F66ULL;
    aIngress = 0xFE579B7CC202CA91ULL;
    aCarry = 0xE67A2C5D55CE8F95ULL;
    aWandererA = 0x94B369ED8B2AE276ULL;
    aWandererB = 0xEE97E86E4D7C8556ULL;
    aWandererC = 0x88A335A347ABFFEBULL;
    aWandererD = 0xF47792915C1D758AULL;
    aWandererE = 0x8F87F9A42DF4753AULL;
    aWandererF = 0xF1A9B7CAD29E55BAULL;
    aWandererG = 0x8DC67256A89CE3B6ULL;
    aWandererH = 0xBB2712879B1B8112ULL;
    aWandererI = 0x838B0210FDEF92E2ULL;
    aWandererJ = 0xCE3101ACFF4C5828ULL;
    aWandererK = 0xB9D4ED44A80AE7B2ULL;
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
    aPrevious = 0xD7F38BE90B124900ULL;
    aIngress = 0xCA6F44464289F084ULL;
    aCarry = 0x85148C68CE026A13ULL;
    aWandererA = 0xB5CAD176F4D5D851ULL;
    aWandererB = 0xD978282B194E97BEULL;
    aWandererC = 0xF26F4A6DB1A2D07EULL;
    aWandererD = 0xAD2A32672CF2736DULL;
    aWandererE = 0xDA018F9281CDD543ULL;
    aWandererF = 0xA1AF5C5EC1EC4E27ULL;
    aWandererG = 0xCCEDFD592A5B4F4EULL;
    aWandererH = 0xA1E73F017AF07FDEULL;
    aWandererI = 0xE104FE251041FB02ULL;
    aWandererJ = 0xC03363573B09B5F3ULL;
    aWandererK = 0x910FB55C4B060FABULL;
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
    aPrevious = 0xCE110DD395257454ULL;
    aIngress = 0xA2CFF945A105D90AULL;
    aCarry = 0xD460414B2D26327FULL;
    aWandererA = 0xC068C8C7221A27E0ULL;
    aWandererB = 0xC4CF7AAF4DF48228ULL;
    aWandererC = 0xCBCAB4FE7AC5D301ULL;
    aWandererD = 0xFECE2618BA7AA510ULL;
    aWandererE = 0xBB6102BB3F5F626CULL;
    aWandererF = 0xA970271C9B505106ULL;
    aWandererG = 0xD4583463D1FDA54CULL;
    aWandererH = 0xBEE5FC65D6175FF7ULL;
    aWandererI = 0x868FF2039D3474A8ULL;
    aWandererJ = 0xAE8BBD2532070983ULL;
    aWandererK = 0xA6F38B75B8C4A614ULL;
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
    aPrevious = 0xC06DAE89E815BD0EULL;
    aIngress = 0x93847245527F3E17ULL;
    aCarry = 0xDCD514AD36718B55ULL;
    aWandererA = 0xDFD87F8F38BD55A6ULL;
    aWandererB = 0x819374BC025763DEULL;
    aWandererC = 0xDAFD933FAA70431DULL;
    aWandererD = 0xCA89FA670C3EE76BULL;
    aWandererE = 0xC31D42AB44B9411BULL;
    aWandererF = 0xA6F534B0F08D75B2ULL;
    aWandererG = 0xCB32ED4F7B27D4B4ULL;
    aWandererH = 0xF6F0BDA7DACDEF98ULL;
    aWandererI = 0xBE0EDC3CAB90B718ULL;
    aWandererJ = 0x915897EF196CDECFULL;
    aWandererK = 0x9728B323B4F970BAULL;
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
    aPrevious = 0x87C16856471E3E6BULL;
    aIngress = 0xEA3CC03C218BB2E6ULL;
    aCarry = 0xFF4B14D4CE0A1B43ULL;
    aWandererA = 0xD8B9B0A3E82AAA05ULL;
    aWandererB = 0xD7E8F38289F3E5CBULL;
    aWandererC = 0x8E76804619EC2F0CULL;
    aWandererD = 0xCB16BCD46F7CE821ULL;
    aWandererE = 0xCB6D3C0C7BCBDD84ULL;
    aWandererF = 0x8FD7BB710FF5C41EULL;
    aWandererG = 0xBE385069FEF72E75ULL;
    aWandererH = 0xF26A9BAEC804FE51ULL;
    aWandererI = 0x8BD222885603E5CDULL;
    aWandererJ = 0xBD469682522D04ECULL;
    aWandererK = 0xBE729418E0FBF72CULL;
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
    aPrevious = 0xF9D4033672E7FAA8ULL;
    aIngress = 0xCBF884CFB3D04A98ULL;
    aCarry = 0xE6D32CEB56A10AACULL;
    aWandererA = 0xC060921F7C4FDE45ULL;
    aWandererB = 0xC07E2B04A53069A4ULL;
    aWandererC = 0x9E8EF3AAFD0CA7DBULL;
    aWandererD = 0x85F17E10B76CBAF5ULL;
    aWandererE = 0xACBBE650AF37154EULL;
    aWandererF = 0xFF1471DA9BDCB63DULL;
    aWandererG = 0x8539AB1894B6AC77ULL;
    aWandererH = 0x9CE579374FC299B6ULL;
    aWandererI = 0x8EA7272DE856A701ULL;
    aWandererJ = 0xBCA9AA832B439317ULL;
    aWandererK = 0x92ADF5D0A6B0D6D9ULL;
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
    std::uint64_t aPrevious = 0xE0BCC818033CBBE4ULL; std::uint64_t aIngress = 0xA7D842A37791B89AULL; std::uint64_t aCarry = 0xC5061654BABD932BULL;

    std::uint64_t aWandererA = 0x94165FC8FBFA08AFULL; std::uint64_t aWandererB = 0x9D9768DA421C4819ULL; std::uint64_t aWandererC = 0x94DF4A34B83F6FC8ULL; std::uint64_t aWandererD = 0xD64F30DA27A45BF4ULL;
    std::uint64_t aWandererE = 0x8E213BF6EA5029D4ULL; std::uint64_t aWandererF = 0x93749FBE920EF1E2ULL; std::uint64_t aWandererG = 0x9DAE8DB3BA7E256CULL; std::uint64_t aWandererH = 0xA1EA95E1A1C84227ULL;
    std::uint64_t aWandererI = 0xFED34BC674356B08ULL; std::uint64_t aWandererJ = 0xA063276872AFFB6CULL; std::uint64_t aWandererK = 0x8A0724F0D7C4D0DEULL;

    // [twist]
        aPrevious = 0xBCA16E66D6D6CB27ULL;
        aCarry = 0x9515E06A62508FF8ULL;
        aWandererA = 0xE833EA1AAE010F00ULL;
        aWandererB = 0xF19AC71AE792BA99ULL;
        aWandererC = 0xE67F6149ED5135DCULL;
        aWandererD = 0xD59ED47D317029AFULL;
        aWandererE = 0xB3949D20C34E8B8EULL;
        aWandererF = 0xE043F72F160D3582ULL;
        aWandererG = 0xE75A80BE18709BAFULL;
        aWandererH = 0x9EC7C1F3EC2FF893ULL;
        aWandererI = 0xE6657A90F50AF4DFULL;
        aWandererJ = 0x8747468B1335FE89ULL;
        aWandererK = 0x9F495429E98D27CFULL;
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
            0x41EC7BF175985078ULL, 0x17E40BDE557EF26FULL, 0x521FF1C196B10972ULL, 0x0580F0D49F12D8D0ULL, 
            0xB9A40DE58447BDBFULL, 0xC8C8B438B989D6DDULL, 0xA4246029333AE683ULL, 0x15794F03831F9B0EULL, 
            0x9F77CB0D18C89808ULL, 0x1094BAE3ACFD2E20ULL, 0xB0D7AF67F9F681F9ULL, 0x834D78296AC5B1C3ULL, 
            0x74BED45B3309B9F6ULL, 0x4D74068F68D1BC47ULL, 0x300337436093369CULL, 0xB39057CCA64AC933ULL, 
            0x9644E0070DF195C4ULL, 0x00937D84099122C4ULL, 0x4E6888B200C2A316ULL, 0x0E553864F26ECADDULL, 
            0x5EFE31E8F989D379ULL, 0x6CFC82546908BBB2ULL, 0x1189742D298DE972ULL, 0x50A69CCDF9A8F262ULL, 
            0x396D21308978B84CULL, 0x3FAE8A1AA1EF1467ULL, 0x81D44573D317E320ULL, 0xCDF3FF1890116D0DULL, 
            0x830C0E780D754C06ULL, 0x7DC52AD1AD0361E0ULL, 0xE934BB12F746D9D5ULL, 0x26DE6BCF6F25CDB6ULL
        },
        {
            0x5FE6CFE92F7777DCULL, 0x4BDBD5F2E53679ECULL, 0x63953172B0BD50B3ULL, 0x386EB90D81163F9AULL, 
            0xB9F16DC91C3049E7ULL, 0x76A8D237CD916903ULL, 0x747C0A5DD1894A92ULL, 0x991666BD44821B97ULL, 
            0x8A54FCD5F085B1E9ULL, 0xFB02218ABFD9D25FULL, 0x58FB313257B7CD27ULL, 0x82BCD3D0CA4FD450ULL, 
            0x1A2233846F5676A1ULL, 0x066B6299F384F1DFULL, 0xF34343B1B701A3F1ULL, 0xF60D49936D10F1C2ULL, 
            0x484B39CA2E3C0882ULL, 0xB28120BC09701709ULL, 0xFE5ED0FF1A4AB3DFULL, 0x187473877D1A8B5EULL, 
            0xE7BF415585FCA91FULL, 0xEB29577E610C7047ULL, 0x46CEA9A3DE06342CULL, 0x3661E55A391FC4A2ULL, 
            0xBFFA8AFDF0C88244ULL, 0x5C439004BE6009D7ULL, 0xBFCE613EA7894E04ULL, 0xFEC93E9B3A9EC0ECULL, 
            0x7CF992D40D5EF7F3ULL, 0xCD9893FDEC4D2453ULL, 0x3833CD88084B4ADEULL, 0x1592BB148E792C9FULL
        },
        {
            0x01F235E38BDBFD50ULL, 0xFEC2A1B457229263ULL, 0x7A574F0CCDB5D003ULL, 0x8D8BDBF3BA6FA4B7ULL, 
            0xF36F2B60D1209112ULL, 0x29AA620C5704B444ULL, 0xCF761A16D92CA6D6ULL, 0x90D28886011C7593ULL, 
            0xEFD38E90305292E8ULL, 0xB057C9655119CD98ULL, 0xB63F887F85DEAC55ULL, 0x17D51DEF29BF789EULL, 
            0xF2B248FFB424C6B9ULL, 0x711DE88652A88DB4ULL, 0xBB99B784BB9C99D4ULL, 0xD04337C3DD724DB2ULL, 
            0xEAE56F78804BC4E3ULL, 0x6059DA9BCDBC7BC2ULL, 0xAD4C7D132E9C23F8ULL, 0xFDC1AE1F0B02E413ULL, 
            0x277E5698B7B2FE4AULL, 0x5B9FAA3608D1A299ULL, 0x5959B685273C306DULL, 0x1B87FCF924B456AAULL, 
            0x73A6DBA9205886C7ULL, 0x4A418BF82EC15673ULL, 0x998F857B29BC83E0ULL, 0x85F188BE5D754821ULL, 
            0xBC508563D015DB8BULL, 0xAA74FDA514A8FD71ULL, 0xE6FB2F94B525F6BDULL, 0x58CE8E9833E63746ULL
        },
        {
            0xF01D0625912D7241ULL, 0xAF50D44FA953343BULL, 0xFEDFB6B68088B131ULL, 0xD5970FD963D988F6ULL, 
            0xFF367229CF82B034ULL, 0x1D2102A0AFAE95A3ULL, 0xD6BF97BFB63721D8ULL, 0x768EDBD1BB762292ULL, 
            0xF32DF2F9A93DDA47ULL, 0xC1EFC7D8C8F6ED60ULL, 0x6BAC3D9F958F261FULL, 0x8C5394F5596745FAULL, 
            0xCDE648DC8AE72EABULL, 0x390FE8954C52454AULL, 0x25BF63695E87A228ULL, 0x10D14DB0059FD507ULL, 
            0x5E9A95396C19B2DCULL, 0x5FD7A77EFC2139D3ULL, 0x4EC189A30D096C95ULL, 0xDAAB4317558CFD7DULL, 
            0x4CE4CC6C75B51F68ULL, 0x18DBCA242F249C76ULL, 0xB645ACD2124A03A9ULL, 0xCB627ED1172012C3ULL, 
            0xEBB71853232141ACULL, 0x91F6EB0A0A246ACBULL, 0xEE164E261797B1F1ULL, 0x98C28A88FE6FE1ACULL, 
            0x55443293E68B4C73ULL, 0x136BDE51974CB7B8ULL, 0x83629C5D5E4AB2CDULL, 0x45B8B5813F4C6E22ULL
        },
        {
            0xB79B155B117205FFULL, 0x8D922FE06A04EA4FULL, 0x4CFB41905A0DE800ULL, 0xCBDB9DA188C26D00ULL, 
            0x247498B2F713A3D3ULL, 0x25732113B3F652B4ULL, 0xB67B0D3F809CEC0DULL, 0x5294FFF1043F4BA9ULL, 
            0xA8DA8978F46FE602ULL, 0x2B6ECE579713A317ULL, 0xCA99288A35FF103EULL, 0xC042203D8C2FD391ULL, 
            0x0107266493EBC825ULL, 0x1E73537752B6E3C2ULL, 0xB4DDF39FD0664D06ULL, 0x5571320DD79BDB85ULL, 
            0x8876A943DBF653D1ULL, 0x2627F88BE9EBDCB0ULL, 0x26C20795994CA33DULL, 0xC1E7BF02E2BD2D75ULL, 
            0x396D890F31FD866AULL, 0xCB44628660FD5102ULL, 0x63406C9770C7E0F5ULL, 0x48851DCD7694D018ULL, 
            0xC7E4D67A1BF8F593ULL, 0x401812625FB301C5ULL, 0xD3FDCC4745B0848EULL, 0x6A84D3A108DDFA1CULL, 
            0xD8420EA860567112ULL, 0x6A32C75DDDC5E8ACULL, 0xBC269008D9BE36B8ULL, 0x9CF07A4CA2CF6434ULL
        },
        {
            0x34A0C82C6C544C61ULL, 0xF835100011BDCE01ULL, 0xF1299B70AEFF4984ULL, 0x9DC317DA9E20F095ULL, 
            0x404FFEC4213312BFULL, 0x114A137FA4273504ULL, 0x73465E94ACE1CA57ULL, 0xF87D1947F34CF1F6ULL, 
            0x3458D715F92ADAC1ULL, 0xC92B208A9932856DULL, 0xE56047AFE1F7C81DULL, 0x81FF73B8B79F6D15ULL, 
            0x291CF487DC064323ULL, 0x7240D74F651DE878ULL, 0x923E7B34893ECF82ULL, 0x2F028B9571C8DD49ULL, 
            0xD6BA60C2F8B411D6ULL, 0x23E1892AC84275DFULL, 0x344CA90E47DB0F09ULL, 0x134019A327665D8AULL, 
            0x12BD6C8C56A1D895ULL, 0x742F1CF904A9B440ULL, 0x67EE9340D330A7DFULL, 0x735C91E5ACD8D439ULL, 
            0xEF480CD44398C70FULL, 0xB116B8BDBF30E359ULL, 0xE2C9EBFA37EB30C5ULL, 0x741A7EC47F587432ULL, 
            0x548D03FB78D8BDC3ULL, 0xF8C2BCB17303FCFBULL, 0xBA5DF4C688DD4E3FULL, 0x85A3E8605AE7890CULL
        }
    },
    {
        {
            0x13604061AB29B8F3ULL, 0x98F9B29EBC2F34E2ULL, 0xB6CBE9B14C45E257ULL, 0xC55A22F0F1925817ULL, 
            0xA0CE12F0A468002DULL, 0x12F65EC995A93040ULL, 0xE350E125621307F4ULL, 0xD20D7975AEFD4CE7ULL, 
            0xAF512715B20F237FULL, 0x46A06BFDD2AB636FULL, 0x0C3E0F1A3A7FA4A8ULL, 0x6F49B8BDDD2B7B7BULL, 
            0xAAB7F7C18F61C3DEULL, 0x86C1F538B84464C1ULL, 0x1C67CC98C91492B3ULL, 0x78EB621CAC9D382EULL, 
            0xCFF755069326FB1DULL, 0x77DCB71588C4867AULL, 0x6554B8FC99B77965ULL, 0x1EAAB55401383555ULL, 
            0x0F08D65FFDCE6925ULL, 0xE0CD5544C773BF0DULL, 0xF189CA98BC27E1A2ULL, 0x50D322296D866739ULL, 
            0x2EC6C812C5485B82ULL, 0x78C9299735AAA005ULL, 0xC758A7DDA0E4A3DFULL, 0x7446CD877A5D88B7ULL, 
            0x5602BED53193AACCULL, 0xDD49DA30C9987067ULL, 0x753BAD8539429220ULL, 0x8ED032D2CBAB9BEAULL
        },
        {
            0x7A9DF5DB1A900747ULL, 0x376A0ACA3E40FAFBULL, 0x17DCD39B50E9A690ULL, 0xD8AFCDD94E8A2501ULL, 
            0x3E9F0BF35A62E79BULL, 0x05A65E2080353884ULL, 0xC3A65D88176FB58FULL, 0x1DE0F3B15E16E7AEULL, 
            0x376D5AAB206E0696ULL, 0x08DC58B83DD04D2FULL, 0x56159C35761BAB19ULL, 0xC86B86CD79120171ULL, 
            0x1FBD3EC274E0134FULL, 0x6CF21B3B7B21FD21ULL, 0x021E47D221B6E6A2ULL, 0xC59D0FC31F5A9776ULL, 
            0x1546879D3E365ED0ULL, 0x450B7516F56CBD5FULL, 0x9F5CB0EA9529B492ULL, 0x041AFC059B8222D4ULL, 
            0x136639D17D2C58D6ULL, 0xC15EB044D3C15CF6ULL, 0x6B6A31E5077ADE69ULL, 0x3156F9434D6C4442ULL, 
            0x34EAC5FB343D7790ULL, 0x2B52B126C40DA013ULL, 0xD4828AEF01C41505ULL, 0x04A9548508A54675ULL, 
            0x7F2A4F1A962086C1ULL, 0x4E776F7388BE348DULL, 0x9BA55674E9212433ULL, 0x7C1BBA60C74AB62CULL
        },
        {
            0x40D276CED3194F5EULL, 0x4764F8A52722502FULL, 0xAC78A1E43BFF991AULL, 0x6C1BBACFFA0A9B8BULL, 
            0xB53B2180315FCB10ULL, 0x31918BA46213B3CFULL, 0xEA89AC42D78DACA9ULL, 0x2C05C0619A6E147CULL, 
            0x69311758C2265B08ULL, 0x968B5BAA3D85A1A6ULL, 0xBF37F7B005F1A82FULL, 0x9DBEC11F466EC5B4ULL, 
            0xA820FC77801D6629ULL, 0xF977CC9336518B26ULL, 0x2BDF54F85160C826ULL, 0x2C2F25C41088077CULL, 
            0x2293CA959E41F311ULL, 0x3C50C0C6965BC8DDULL, 0xFE66C641AD939220ULL, 0x1B4C9389FDB914BAULL, 
            0x7D81AB212FD95A60ULL, 0x3D67CA5EC13E3ABEULL, 0x4C5DAA3FD339DBE5ULL, 0xCD635F9C054A0733ULL, 
            0x148B7D25990BE7BEULL, 0x4F47FF43F2254707ULL, 0x1767B5C57AFDDEBFULL, 0xBD3055A75C787986ULL, 
            0x4CEA34650D824132ULL, 0xC5DE7A5EC47C2537ULL, 0x829DA8B69CB16841ULL, 0xC702FFCF72F9464AULL
        },
        {
            0x669DF1F0BAA08C15ULL, 0xA79B84761837E5F9ULL, 0xCD3DA9F7F3AF22BDULL, 0x02C2795F2EF5545DULL, 
            0x30A8BC6C17D1B259ULL, 0x0A0FFA7811810CE9ULL, 0xE77E5BB3D3463B80ULL, 0x26797161A42EB852ULL, 
            0x51DA4BFC21DAA566ULL, 0x598C729D859EEDDFULL, 0x717C082F5DAC4D7CULL, 0x762488943E529D93ULL, 
            0x085CC3516168B1D9ULL, 0x3CC97A5569EF4F98ULL, 0x59ABD99772BE76A9ULL, 0x2789C3311C75285FULL, 
            0xAA9BCE180511ECFCULL, 0xA30929D0B023EFF6ULL, 0x2C7C330BFD2345C6ULL, 0xADD88343D0FF5310ULL, 
            0xDD1D4FDAACF1B5D3ULL, 0x140863FFD67C7FA4ULL, 0xE52636268566C241ULL, 0x7F232868A2CAF3A6ULL, 
            0xBAB24E681A0DDB84ULL, 0x9FCF60DCDFE991F6ULL, 0xEE1341A33586DE22ULL, 0x5B61E76BA59FAD42ULL, 
            0x1309DBF5ED4287F8ULL, 0x38DA5739A6DAF64EULL, 0x78F5643750D0235BULL, 0x647BA6E53EC50F11ULL
        },
        {
            0x3EB77136DAED356CULL, 0x2A3B7039DC44C25BULL, 0xED3F47AD1CA12A71ULL, 0x9785132B6A997538ULL, 
            0x4651A1A1E1535B5BULL, 0x8838E29FB817B8C1ULL, 0x06EAC2354DACEEADULL, 0x769269741DC94EA2ULL, 
            0x6BEC358390F82967ULL, 0x5CA798CD8C7BF601ULL, 0xB5D2F6C342E4787BULL, 0xA11D2B3E59CA366AULL, 
            0x267E272A5EB59B2DULL, 0x02355FFCFA999DBCULL, 0x90C6A027ED59DEA2ULL, 0xB547E46C57A06AC9ULL, 
            0x1E1CC132AE746C75ULL, 0xB6798A4E6BC64E4BULL, 0x38B8A1BDEF4374F6ULL, 0x4802FE0DE32C3B7DULL, 
            0xB852769593DD0F7EULL, 0xDFF539C53D4D0FEFULL, 0x2AB3CD4967C16FD4ULL, 0x24C586FD0B0E9E0EULL, 
            0xC0BA4D46AFEC9BDBULL, 0x0DDADDD0A73F542AULL, 0x98E904F55B995943ULL, 0xCF281B9E4F9A1939ULL, 
            0xAEEA7010A83D6252ULL, 0xC0D9AD77CCC71BA9ULL, 0x40FF81FB1F791F8EULL, 0x9D53E91DCC2CB0C5ULL
        },
        {
            0x9EC211E660736603ULL, 0x3DA2338E8E00057DULL, 0x6BEB225874105425ULL, 0xEC574B424FE48FA1ULL, 
            0x45255D8EE7CC3832ULL, 0x35EDE9D8DA4137C7ULL, 0x21E246C72869BA91ULL, 0x451B41BDD5008200ULL, 
            0x62A73C88C8BE609BULL, 0x5EF93A19EA927AF8ULL, 0xD10A63ED0408D635ULL, 0x75359C29CF2DC243ULL, 
            0x14E571DE730CF97FULL, 0x244CD60CFDB217DCULL, 0xE7E130FBC113CD4CULL, 0x8145243485E25781ULL, 
            0x94795E5B8628AB84ULL, 0xFC409CA0AA4CBC49ULL, 0x26FDCEF2C4B21802ULL, 0xC20C9845877E44C9ULL, 
            0x7FB241E8F307430DULL, 0x67D68DB88BEEF55CULL, 0xD73F1FD22A1CBA6AULL, 0x609989A08F8BCB34ULL, 
            0x9D5C5F99378D9671ULL, 0x55CB8C27B9C9F891ULL, 0xF32CCD30AA1FF72DULL, 0x9F76FD0199C2ADD3ULL, 
            0x5BA4CCCB64622BA7ULL, 0xEA6065D70603CCBFULL, 0x18EE3696F1D1E1FFULL, 0x1F276E91D188C0FCULL
        }
    },
    {
        {
            0xD5BE19DCCA4ABBC2ULL, 0x636BB3AED9634F4DULL, 0x59D8929A8C423937ULL, 0xA7E49770965A8F3CULL, 
            0xEE7EE615AB9EEFF1ULL, 0x98A671ACC0E9DDB2ULL, 0xCBEF3DDBF0B452ECULL, 0x0BC88140FA3CB8C8ULL, 
            0xC185A3C862052DB9ULL, 0x633CA607D84ACEA4ULL, 0xA1DD39A0B2224C8CULL, 0x4FF9C79121B4D81FULL, 
            0xFD62718E807C9E15ULL, 0x4CB4DEBF855F3DB6ULL, 0x32D7052EE82A6EB3ULL, 0x9AB4E42FD7854CA0ULL, 
            0x514229AECCE0A778ULL, 0x329BD9E217E1B8EBULL, 0x226C15A31F9BF2C4ULL, 0x5FA6C401E181D39BULL, 
            0x694E221E7603DA7EULL, 0x583EF5987BB36A76ULL, 0xFFC623845EA0BB73ULL, 0x9887990C853916F3ULL, 
            0x558A1D3EB1BDF033ULL, 0x9DD63CBC20F4A1C4ULL, 0x9FE0C97089CD9248ULL, 0xBDFE1C274824DA27ULL, 
            0xDBBE931D7BB1A310ULL, 0xEDAC9DB00B911C23ULL, 0xCC865BDEA7FA8409ULL, 0x13CE12765B194582ULL
        },
        {
            0x2AF7122FDCF0B9F8ULL, 0x9349A885143CED57ULL, 0x69049591AEDDC7C7ULL, 0xF7CB464995237B30ULL, 
            0x98334016493CF62EULL, 0x6F0E6B0D071F0542ULL, 0x6184AB159BECF15BULL, 0xA80DFDD943AF6D2EULL, 
            0xD1D4E0216D79D1B2ULL, 0xB99A377FC17F4FA4ULL, 0x1E42D1B27E5095A5ULL, 0x7CFE5E565377CDF6ULL, 
            0x1AF26989EC16DDFBULL, 0x1DE4EAEC051DFD54ULL, 0xE03293F9CE831C3AULL, 0x6C83E60489357F83ULL, 
            0xF1B32F377AB0365DULL, 0xBA0B31457CFCD993ULL, 0xA2EF53A21A8C8361ULL, 0x56C9A6667AAB7F0BULL, 
            0xAB7543CAAC3C8077ULL, 0x8081417EEB05A2FFULL, 0xF6F7C5A4F6F6AF9CULL, 0x0D1623DA4F64AEA5ULL, 
            0x3F70AE5077590235ULL, 0x2540A7B7FD3E16D8ULL, 0x89A592B90880EDC9ULL, 0x95B1880502B4BE27ULL, 
            0x1458D4F965E55F70ULL, 0x2FE329581339B0E7ULL, 0x251A65703F05DE4EULL, 0x57003B3BEEEAC355ULL
        },
        {
            0xE2052043438AFC85ULL, 0xA8C37B3989656C0CULL, 0x10929C784FF22AACULL, 0xE3CF5F9E8734FAD0ULL, 
            0xF77F1F9787B18C21ULL, 0x2B83B0E2914E85E3ULL, 0xBCE4BF7250EDBC90ULL, 0xA8BD805ABDC67936ULL, 
            0x53E0CA00EBA6C3A1ULL, 0x6A8330CBABA49A5AULL, 0x4BA89A415EC86238ULL, 0xE75DA49BF6A032CAULL, 
            0xE162C67C1A0C48B1ULL, 0xA2EBC1041875D4CDULL, 0xF4DDC2C6773D9BA3ULL, 0xAFC114A06F47EAC0ULL, 
            0x25CFCC6CCDF2808EULL, 0x5449053991DD01F3ULL, 0x9E0C1FE978E17DA1ULL, 0xB7B33FFD9408D688ULL, 
            0x97EFE9960376441BULL, 0xD340F5A600CC2192ULL, 0x6B5DDEE21622D2F1ULL, 0x5410D05DBCE2B5CDULL, 
            0x4F54D209D4F86FA5ULL, 0xE103FF9ED44ADFC6ULL, 0xB88605B3CD855108ULL, 0x6E93A62EEF04F815ULL, 
            0xC296C8E216173DCFULL, 0xAC059A9B5BE105C1ULL, 0x1A523DF137FDBCA6ULL, 0xD95D6CA89BA85E61ULL
        },
        {
            0xF79F846E27D4CEC1ULL, 0x7E53161C7DB42249ULL, 0x7F9A5920D8805D1EULL, 0xC15128F43841B9DCULL, 
            0xD4E99434C99531FFULL, 0x0ED0C73A2BF35818ULL, 0xF1DF9ED00FD52045ULL, 0xF8AF58BB6F8B0C5FULL, 
            0x9CB50E78B22A59C4ULL, 0xEE5F3024321EF8D7ULL, 0xCDADB68D8FBE67B7ULL, 0xDB6AA06058A5E3F6ULL, 
            0x40E7EB8AC9BB132BULL, 0x6A68C24C4F877AC8ULL, 0xD3C00EA3783D3BBCULL, 0xD91F330ECA432C27ULL, 
            0x31B51A46CCE6F383ULL, 0x787B6F0EFFA87962ULL, 0x85510128CAF18017ULL, 0x2E10F19F96B43225ULL, 
            0x18D1D306A3067D1AULL, 0xA5A1C71EA4C0AE81ULL, 0x4F136733ADCE7627ULL, 0xEBAC5A12A64EEB09ULL, 
            0x49B970CE3F185249ULL, 0xA71C71B56CEFEFACULL, 0x0B17DC40EB3374A5ULL, 0xD418E3CF72A37877ULL, 
            0x555464A8E0D9FB39ULL, 0xF0540B65056A8247ULL, 0xB591800A0E6F0056ULL, 0xD0A63FF6DF52B524ULL
        },
        {
            0x2A026FF0BAC979DFULL, 0x8ADD251817515202ULL, 0x1E0C64B02E1D118EULL, 0xBE44AB1127FDA033ULL, 
            0xEEFA0A279D92DD7CULL, 0xA7799E333C48311EULL, 0xE8E2C6788D0D6A01ULL, 0x464CEEE37C5EA65EULL, 
            0x852EFE0E2ABEB0EEULL, 0x25E595F457011E82ULL, 0x78DE4A55CD9DE71EULL, 0x8FEC3B0DC40C7AF0ULL, 
            0x1015CA535C65BF5FULL, 0x34B5D170A8E0B199ULL, 0x835E8D1CCABA883FULL, 0x9E9BE3CB3F72F989ULL, 
            0x376008DDA38E56E1ULL, 0x77C6BAD25820FF17ULL, 0x776FA9AA63C2AA86ULL, 0x6AA02F6C87821BD1ULL, 
            0x6A13C71DBD933A8DULL, 0xCB3C9ADCD045867AULL, 0xAEA680085ED3A974ULL, 0xB0A4AE46FAC1611EULL, 
            0xAB99EE1BD0C5FEAAULL, 0xF77BADB7478020DFULL, 0x86D27B0A95428786ULL, 0xE33DA0AC42A65F2BULL, 
            0x8F536C83E2196335ULL, 0x604BFD5316005134ULL, 0xDAFECB5369CDF9DAULL, 0x0304C844EA6215CBULL
        },
        {
            0x2F77D3BDA6902141ULL, 0xB8726AB857B9A63FULL, 0xF3E8B9E3A5403CACULL, 0x3676CE85D1C7AA35ULL, 
            0x74EC0A64B4AAC1E9ULL, 0x3B78C66D21F1B441ULL, 0x55413422A5015029ULL, 0x3EB7EFA4F01E0FCFULL, 
            0xCD131D4541941C2FULL, 0x9E45C7E7034A912FULL, 0x5500CD5B0659EDD8ULL, 0x535C53522207A660ULL, 
            0x1529783BB9A7A706ULL, 0xCBB3176929247DD4ULL, 0x9DCC255C0B2245A1ULL, 0xBF4CA5A5EBD1D175ULL, 
            0x5D41B35A9E469C7CULL, 0x3D3D2FBB19BBF577ULL, 0xDB3DAD3F985F9585ULL, 0x1B6BBCF9BD5452D6ULL, 
            0xC3022CA42A0FB2D0ULL, 0xDA2FB59CA58334A3ULL, 0xE02C52743C051354ULL, 0x65968CC2D1238976ULL, 
            0x32B24BD5B6710B12ULL, 0x3BF308646F42A58BULL, 0xE6DC7CC523B42C41ULL, 0x87A965D4F0F8AE08ULL, 
            0x21BE2D41C69D2006ULL, 0x3FB4E880C50ED434ULL, 0x3E657B2E54800797ULL, 0xA76B8D678BC89E34ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kKeyRotateAConstants = {
    0xA5B4AB31D7A5B53AULL,
    0x403FB0F04AE8EF19ULL,
    0x0E8ABF63F1F2E494ULL,
    0xA5B4AB31D7A5B53AULL,
    0x403FB0F04AE8EF19ULL,
    0x0E8ABF63F1F2E494ULL,
    0x90E70C648313F806ULL,
    0x37E5A8F1E02A9751ULL,
    0x7C,
    0xC1,
    0xB0,
    0x07,
    0x43,
    0x53,
    0xB5,
    0x30
};

const TwistDomainSaltSet TwistExpander_Achernar::kKeyRotateBSalts = {
    {
        {
            0xD57CF699322022D2ULL, 0x8C72B813884B9ECCULL, 0xF8C867107AA8240BULL, 0xFC6B9EBE2505EA09ULL, 
            0xB0A3B6DF977EF7C8ULL, 0xD0EC0AE3D8C787DDULL, 0xBAEAA9784A39F1C7ULL, 0x8578983898FC69D0ULL, 
            0x9E1FEB11F04F99BAULL, 0xD7D781BD6A3FF2F9ULL, 0xDB29D12D48518BF7ULL, 0x5D95460D0A3F2DD2ULL, 
            0xEF3E13256EDD703CULL, 0x011A9ADA29053ECCULL, 0x3D29CBBF6C5EB0D9ULL, 0x7AF70650E2FC7608ULL, 
            0xE054F6EE0B70567DULL, 0xF0C3EC5036C1529EULL, 0xB8992630EE6DC907ULL, 0x481358CA0F3A2676ULL, 
            0x7BCB42FD6DD7B035ULL, 0x13328308AF443D06ULL, 0x2FB8E2B78ABC0E1FULL, 0xF6F38FDD2B7C89E3ULL, 
            0xECF0BE3A66DCD385ULL, 0x3155C3604808AD07ULL, 0xB4D08C60DE9FE67DULL, 0xB62CEE26C5C037DAULL, 
            0x74C6947DA21D9FC3ULL, 0x15234A8AE93C1FBEULL, 0xC79525D60AB6A048ULL, 0x3B9D7038D6D0DBD7ULL
        },
        {
            0x2BB6A8A5E43848E6ULL, 0x084616560CE3AC56ULL, 0x67DD19C9CE5FEBFEULL, 0x6BE00337A27A5692ULL, 
            0x3F96EBF718AE6597ULL, 0x6026760E19293349ULL, 0xC4CA693BD31524DAULL, 0xAB54A8B46BFB78ABULL, 
            0xD622577370AD9E10ULL, 0x4A16901367A011ECULL, 0x914536B94AFF4E03ULL, 0xB2C7878124DE0615ULL, 
            0xF3D3FBB4132D49FEULL, 0x2A3A0CCE3BD2C548ULL, 0x2959AD290061D1F0ULL, 0xDDE0454934E654C1ULL, 
            0xCA57B3EBCB148721ULL, 0x6EE4AAE90F396D38ULL, 0x9D79018F054049E7ULL, 0xF937102972A60B3CULL, 
            0x5547401BF8006699ULL, 0x2DA828168044C4D3ULL, 0xBE08E94948328B47ULL, 0x3E515AF4D336878BULL, 
            0x9222258B1C5DB4FDULL, 0x60DF776A165146F7ULL, 0xD24B762EC1C21463ULL, 0xCBBEA9641F8397EAULL, 
            0x56E554F5D8597EE7ULL, 0x12DA96BD526BB856ULL, 0xC4247CE1E1D29200ULL, 0x4A9CF3EB80619451ULL
        },
        {
            0xC7284D2E6F3C9F0EULL, 0xFD4C883F398490C6ULL, 0x530C824E8AF8CDAFULL, 0x67D0CD1C637CE760ULL, 
            0x06947647935490E5ULL, 0x0DA317DBA7C93F92ULL, 0x4417BE459DE6B3F0ULL, 0x4CDBF894A0336A86ULL, 
            0x426E86D430E74258ULL, 0x0F271C3A6EB3B076ULL, 0x6BE8C4560BA4F760ULL, 0xFEC37DD6477C3CECULL, 
            0xA5C359F913DA724BULL, 0x845CD36638181EE0ULL, 0x5AD3BCC062840C0FULL, 0x734523EF2DEEEA35ULL, 
            0x678CB5BF374FC154ULL, 0xBFEA525B8A30F380ULL, 0xB731903C0445A70CULL, 0xD942D6CF40928218ULL, 
            0x514A72433A14FF34ULL, 0xDD7587F8E3DC3F82ULL, 0xC5518AE8D63582FFULL, 0xDD6D07D25D6EC80EULL, 
            0x85C4BAD3BA9DD454ULL, 0xF81C073101DD235AULL, 0x6670E4805DE77243ULL, 0x4F49A85F1A803871ULL, 
            0x71DF74F20D96827BULL, 0x2387D2D3973B7F2EULL, 0xEADE5DEA44B311F1ULL, 0x79916F931C793FE6ULL
        },
        {
            0x8F973D8BC2CDA2AEULL, 0xB5B111D1A7AD0578ULL, 0x1CC5E0FE0908E6FAULL, 0x54C2A8BC1E2786FFULL, 
            0x61267E30D2883B63ULL, 0xD31D4F124D3CD215ULL, 0x57792B1145899E4EULL, 0x0D9379E2B6D2DDD9ULL, 
            0x62ADDFDCFAC3A6CEULL, 0x610C0CB420A21D56ULL, 0x4CDCB91F0DAD6026ULL, 0xBF5AE4927DC6D78AULL, 
            0x13CD3BB678F82392ULL, 0xF34933F5240B76E3ULL, 0xB7EF52B3737252D1ULL, 0x155805EE6BC21364ULL, 
            0xA4183EA04F8E207DULL, 0xC815A60C65689B9CULL, 0x7FA15E289266DA7AULL, 0xE6C0507367ABF0D5ULL, 
            0x750AF529E6143764ULL, 0x3F4E058E8DD76611ULL, 0x4365FDCF3F601865ULL, 0x02E043221DCF6F40ULL, 
            0xE07E4AECBE153F16ULL, 0x0EB8C1E9515ED7F7ULL, 0xFDDD166EF13B4E31ULL, 0x30B8AA0D3A9E542FULL, 
            0xAF8B16A8B822A989ULL, 0x5CB1E4B836913CB0ULL, 0xF8F146DAAEA9078EULL, 0x65FD232E076E743FULL
        },
        {
            0x69D8AFFA6DCBD1FCULL, 0x111039FAA62E75D4ULL, 0xAB2E33EEBF5A3084ULL, 0xCB392D03AB67F4D3ULL, 
            0xCB3703752B573EB8ULL, 0xA3B113C0F2BA7DC0ULL, 0x82B65226013F9027ULL, 0x28E363EF1877D573ULL, 
            0xBBE47A3A605986C7ULL, 0x963AFBC2B1910E4DULL, 0x85AAE1CD60DC8AC4ULL, 0xF5BDFFE82AF2E868ULL, 
            0x2D82F04539F2E97FULL, 0x1F515D1CF51C862DULL, 0x796E54F84C6F9B57ULL, 0xEC4D8CFE56D35228ULL, 
            0x4217CBF0F6B19FF8ULL, 0xB331D8940222749DULL, 0x6F7643F618BA72DAULL, 0xFFD0388DD9CE144BULL, 
            0x3774D24CB5B6A0ADULL, 0x9FFE49A5256EA227ULL, 0xB3B501FE9BE42E95ULL, 0x5F7E7A9CDD8968EAULL, 
            0xCE9D7B1E0D2E5B53ULL, 0xA179D12E9B460AC4ULL, 0x0AA20F0A002E0E10ULL, 0xED6A3B01943D8B40ULL, 
            0xBBEE608A396472D8ULL, 0x9B964A9E95A3A307ULL, 0xD37F23287A204EF4ULL, 0x893065E427CD07DFULL
        },
        {
            0xAF73F1A28881EDC2ULL, 0xBF6AEB66D75CF439ULL, 0x1AB272BC4B498B73ULL, 0x09CEA351C2ADC20EULL, 
            0x1CA3E538FD711820ULL, 0x78E281D7DFE82C5EULL, 0xFCD41B82923A7793ULL, 0xA46D5449E1F6C06AULL, 
            0xDC4A9A6CC62E0F59ULL, 0xF454E6A45A57A9F5ULL, 0x067B19A878E8CC71ULL, 0xEBC8CF828BB61C20ULL, 
            0xE0766CC2F63759EBULL, 0x1D03D7DC2B82CF1CULL, 0x9E1B68F2EAE29393ULL, 0xF5A3E807FC95251AULL, 
            0xBAF697674B9BAB0DULL, 0xC9512BA5654E5389ULL, 0x4EB018DB6B2DDC38ULL, 0xA3C2ACA1717FA8ABULL, 
            0x441D33656E3A5C3AULL, 0x89A5A1F691AD9E54ULL, 0xB04F81780FE22E89ULL, 0x17D8AA4EAF3D31EDULL, 
            0x43FBB14CA7F334D5ULL, 0x15AB46840A22627BULL, 0xD649F0EEF215C9D2ULL, 0xD9D51E6D1892A36EULL, 
            0xD6E5ECAAEF5049DBULL, 0xD9E7B7FED201040DULL, 0xC55B29D54E01415EULL, 0x7C4EA8533D5EEE5DULL
        }
    },
    {
        {
            0x48D87B2015E53304ULL, 0x6473FDB05CFC783DULL, 0xD2FC13A69E4BEAEFULL, 0x37B3584190923A77ULL, 
            0x45ADB76FA185E2A9ULL, 0x37646B1AC3B48A27ULL, 0x309DA2BDC801E7ABULL, 0x9091C9D3B676B529ULL, 
            0x93CCC93AEEC5A4ECULL, 0x297878EB9B5773FAULL, 0x3D83BAF54B86CBE5ULL, 0xBA3DCC8C26EE2962ULL, 
            0xA1B8691EC072CCECULL, 0x9D025E9FC8A7C9BCULL, 0xBCC315045658A1C1ULL, 0x074AC91C4787900DULL, 
            0x9A6BF416BC26B3DCULL, 0x67509FF27F51B6DDULL, 0xD30F257170B81F03ULL, 0x40D6D1A99CA4C187ULL, 
            0x64F55C7155031AF8ULL, 0x3F0975D8205A31BCULL, 0x2314CD4B049F923FULL, 0xF2D7E43DA776A645ULL, 
            0x630D6730B9A71037ULL, 0xA56E807F7EA73C25ULL, 0x808437667F12905BULL, 0x76961D3623606D61ULL, 
            0xE2950F243F5FA2DAULL, 0xE3223809079C846CULL, 0x765B1B55C47EBF92ULL, 0x318A3F80FBBFB17CULL
        },
        {
            0x93B9850A55D48962ULL, 0xC014D53BC0E38141ULL, 0x9980D924770D156EULL, 0xE36B37CF19371E24ULL, 
            0x9454664E5429CACDULL, 0x5586B2480B8A431CULL, 0xC5EA54F1565BB125ULL, 0x8DA3F15246538950ULL, 
            0x747D83953246C4E5ULL, 0x6C6A83A4E82E1A47ULL, 0xEB1258CD11C018CBULL, 0xF5D8C13A13516539ULL, 
            0xDE0EE651DC2CFA98ULL, 0x07C32506BB308FBEULL, 0x1479113B36AD4411ULL, 0x2C180F9DA5D9345CULL, 
            0x15E2D9D187DB1EA5ULL, 0xE685CEE33314BEECULL, 0x2ECAE68538BFAC3DULL, 0xC4BF395274C89FA6ULL, 
            0x2DAAA28ABC09F34BULL, 0xC1BC85894B0CB878ULL, 0xC4A1E8080A2EB1DFULL, 0xE67FF2AC73CD065CULL, 
            0xCDCF552A94ACBA24ULL, 0xA587C3596A6BCAC3ULL, 0x2DE0A62DBFEBA65CULL, 0x41BCB5BE19052EA4ULL, 
            0xD0191FF4C1CB048CULL, 0x43A0B3AC310BCCFFULL, 0xCC9E6703518768C4ULL, 0x68268A40AB2A910CULL
        },
        {
            0xE15A7773BA07B56FULL, 0xA187B2F5F0B38618ULL, 0x28650D86D22E6A1BULL, 0x34BA7D70370F596FULL, 
            0xCE82714114CDC11AULL, 0xBBD49637D23273ACULL, 0xCB289D87BBD7B87FULL, 0x0A1C8C07359B5893ULL, 
            0xED3F6EA539D81607ULL, 0x321C5C40479EE1BBULL, 0xF50CAD6E372B21ADULL, 0x3AB0BF1AB153B8C6ULL, 
            0xB11AF2FDEEAEA5FBULL, 0x458F6636C1AFE8C0ULL, 0xFB9C7EED683AFFB0ULL, 0xB7B78BE4F0FF187EULL, 
            0x08910A70CCF58E2BULL, 0x9FE753A94ACF533DULL, 0xCDE76D9C2F0F2ECBULL, 0xD3755B5539F17BC0ULL, 
            0x95E65B4DA16A9CAFULL, 0x92ACF02972A9BB1AULL, 0x5F794B95DE4ADDE1ULL, 0x9973C528E17F2F20ULL, 
            0xB002BB39CF50441BULL, 0x03DA273642C0BC2CULL, 0x2F5E183F4699ACDBULL, 0xF4ABD7A556EDEF75ULL, 
            0x5066E914DA7F8136ULL, 0x0AD74103E812E72CULL, 0xADB578752E5C50E1ULL, 0x18526770B777C9C3ULL
        },
        {
            0x9E5AA9E0EC0455E5ULL, 0x99FDB663C0DA3EF8ULL, 0xFD61412CA2C55154ULL, 0x439BC0FE49306729ULL, 
            0xECEC462BE8C4F43FULL, 0x37A09DE76912059FULL, 0xD953CFA32B63B553ULL, 0x37B54EF12939C4A1ULL, 
            0x9FD06BDB50E5DC8AULL, 0xD86E6342CFDE7E60ULL, 0xECD3AB09EF82CEDFULL, 0xEE6F0233A0C032F9ULL, 
            0x063D21A735FA61E1ULL, 0xDE3B6BE3E3D82A92ULL, 0x05C7B22C426DE15CULL, 0x0720472B701057ECULL, 
            0x948D1AF78690EA8AULL, 0x7ED0B769B94F0AA3ULL, 0xD7B9EBF41977C935ULL, 0x9DB54CFE50C4BA97ULL, 
            0x532F0FFD1B343FB6ULL, 0x1E3FB4F5F93F182DULL, 0xD172AAB7C3C49714ULL, 0xEDAED448F46EBB26ULL, 
            0x51F2DE5E3AD26474ULL, 0xA40EFF98284868ADULL, 0xDA439D91D1C8C940ULL, 0x41A578D9239CCF2AULL, 
            0xB2284DC453AC5F31ULL, 0x04BDBEA631A6A2D6ULL, 0x3DB91368939614AFULL, 0xDC6FB291331147FBULL
        },
        {
            0xCF5A2BE0C043D17EULL, 0x1E76095AAE9F60EBULL, 0xC80075E14A08EF37ULL, 0x589F350EFB167556ULL, 
            0x4D802AF32EC53EB9ULL, 0x6E7A2A62E2011D60ULL, 0xCD1659E7DB6D1709ULL, 0x6F0FBD9F2B03042CULL, 
            0x5D5180C66B95189CULL, 0x2F4F1E5E7E86BEF0ULL, 0xC257DDF4F14C61E0ULL, 0x91F6ADBD9A7B0425ULL, 
            0xC707903A35FC9E44ULL, 0x9ADE671BFB1AAED9ULL, 0x8337DF09BB93A3CFULL, 0x9F58F34E2A33E063ULL, 
            0x3082E659C3E3C490ULL, 0xEAAC4672058A4C72ULL, 0x9A87391433B00506ULL, 0x125DF1BC6505D580ULL, 
            0x679057001D15A1BDULL, 0x9EDFB675F5C7FEBDULL, 0x42411F4AF14C0C21ULL, 0xE87962CB30A4099BULL, 
            0x7A18B3897AA155C6ULL, 0x7EF05A6CA2EBD36AULL, 0x50001F5A058A38CEULL, 0x38156ED85C17D42AULL, 
            0x5D3319C2A7B04817ULL, 0xF2E6B32A0DE4C0B2ULL, 0xB6302A061654FABCULL, 0x895C329FF3FB77F1ULL
        },
        {
            0x9D3923CDA5330514ULL, 0x5176C116B4029E20ULL, 0xF072BA31E220C66EULL, 0xDC3DC4F88CDA1341ULL, 
            0x76EA80E6EBD165DCULL, 0x76138FF875D9F1A2ULL, 0x6D822C49C3A20086ULL, 0x47A58C6BB9005C85ULL, 
            0x82B223254A087A08ULL, 0xE13DB2CB21215AFCULL, 0x8F63519EA940330FULL, 0xB89E11E54C21884EULL, 
            0xF908FDF8AC04789AULL, 0x1C8CDEC45B70D7A4ULL, 0xCD4B4EE47292DB94ULL, 0xF267DBFAE840D237ULL, 
            0x0338B784530DC179ULL, 0xA79E88978DC1187AULL, 0xCC12CF097761AD6EULL, 0xBE9CF22BA017E84BULL, 
            0xC84F9C0B8C4EC35FULL, 0x4F3F366D95D786B5ULL, 0xCBF9D4DA9A5C9CDAULL, 0x705C5623D0DA9E06ULL, 
            0xF661CF9F04CFCC98ULL, 0x43CC5692E7F702BBULL, 0x342A068A042C6316ULL, 0x077CC3B97FBEC204ULL, 
            0x7F1EF4BED80EF09EULL, 0x0FF6A5C8497110CFULL, 0x78F4E544050030DFULL, 0xA15D577F81940BA0ULL
        }
    },
    {
        {
            0xF7AA45D1B6B00FC9ULL, 0x91EFA70E267F4C6EULL, 0x29C0F99F6EAC4C72ULL, 0x97D0EBFF00692765ULL, 
            0x6488795964773A5CULL, 0xF6B270E572318A13ULL, 0x8BAD2F811C54DE72ULL, 0xDABADF0CE6A0C657ULL, 
            0x0974798C913EFC06ULL, 0x76C96FEB9FDFBB6DULL, 0xFCC7544055DDF0D7ULL, 0x5E601A7C750742F3ULL, 
            0x96351E64DAB0A55CULL, 0xE1CCBCBDEF74267FULL, 0x387C461CEDE543B8ULL, 0xF0809D6C3EB3514EULL, 
            0xA37DABB77802B29FULL, 0x7BA6C705BD872DB9ULL, 0xB98A9922A99605F8ULL, 0xD59F846FBB4D4C3FULL, 
            0x570984678344F137ULL, 0x5281F0488AF1421CULL, 0x922A5C7C40A17F1FULL, 0xCCF5DB4ECB6AD73BULL, 
            0x573FB38E5E829397ULL, 0x0CD9F64EC9D9D769ULL, 0xE86B69BBFB3DC508ULL, 0x29732EC5928353B2ULL, 
            0x9B3E33B7C3817326ULL, 0x5CF3E1D190D18966ULL, 0x11B5C59456E99440ULL, 0xF5799E1B6E0CD9ABULL
        },
        {
            0x2A89F4CD57218E5BULL, 0x79AE672FE3449149ULL, 0x46744CD7C588A755ULL, 0xE70071B9BD89F3BEULL, 
            0xCB5C0C7F87AD4838ULL, 0xEE389C6CF8155EE7ULL, 0x479218BEC544B4D4ULL, 0x655485D4C1548D31ULL, 
            0x0693BC704E996715ULL, 0x60F0412566736847ULL, 0xF3E1D3F9421E8EA1ULL, 0xE7E851F3307D997CULL, 
            0xB95ECEC943DECE91ULL, 0xB413A61CB2F10FECULL, 0x7B877F22856901EDULL, 0x702869142A155644ULL, 
            0x67B16533D7F52717ULL, 0x1E7ADB9EFADFC653ULL, 0x8EA0E8F2FA3DF78BULL, 0x4AF8718C5B6C267FULL, 
            0x4AB1A055F27038BAULL, 0x1F63672E3CA65B89ULL, 0x7CC02CDE9B05C607ULL, 0x035D2832AFC078D9ULL, 
            0x3456A9DDCCB7729DULL, 0x3A215774651F2FDFULL, 0x0BBEF6FE5E5B7705ULL, 0x93264E1D4F61B811ULL, 
            0xE8553382E58F3932ULL, 0x5AE897874DDA5873ULL, 0x90A704F5AB4B97ECULL, 0x83016E09182437F0ULL
        },
        {
            0xA2AE60AE99CE0F82ULL, 0x56D37D3F27DAF206ULL, 0xFAFE9771919A74A1ULL, 0xA13093C56A10C7A9ULL, 
            0xBA8982B1F6535BFEULL, 0x878DC3E119BED5B5ULL, 0xDFE5776271B1F917ULL, 0x672094FAC7CF3357ULL, 
            0xB281D3802514BD80ULL, 0x57032C7C5BAD6344ULL, 0x6C9AE32B1E037A7CULL, 0xFF67D531F9508A60ULL, 
            0xDE5CD7704899A412ULL, 0x6DEA0BFF03709120ULL, 0xA299B9F6B4A088AAULL, 0x13485A77513F323CULL, 
            0xA8351CBB11687F33ULL, 0x5252AE9D3F703534ULL, 0x4F56E3320C83298BULL, 0xF2BFA8C7CF0B1B52ULL, 
            0x9830FAC204D99DF5ULL, 0x421B3F05F33FC121ULL, 0x1D76F6163E13B3DDULL, 0xFB24B0BC6048855EULL, 
            0x7E30F4C27C9252A3ULL, 0xEEFEAAB54D36E6C0ULL, 0x4FE53F36A43249E8ULL, 0xCC9094E20AD1C48EULL, 
            0xD78A0A9BA2D4AD15ULL, 0x68B80AB8DF839F0DULL, 0x0232F237A4E1B432ULL, 0xF8B754620469A20BULL
        },
        {
            0xF9F9F63EE20EF619ULL, 0xD4EE12F245AE7E5EULL, 0x81D653997FF5AE14ULL, 0xFE0617C9885F8F4AULL, 
            0xBF48A0B1AE8F816AULL, 0x2E373D01FAF4392FULL, 0x0858E1AE673B6E77ULL, 0x2498F26F0E8B2449ULL, 
            0x1A518E4AD004B719ULL, 0x2E0A8371467815E4ULL, 0x44D77EB642E58F49ULL, 0xB971059571C8A91BULL, 
            0x49B7DAC5A6BCB6CFULL, 0xCD8A7A0810AC64F5ULL, 0x8CAA3777612715E3ULL, 0xCDC8CB61719082E8ULL, 
            0xADD3E10143F956FCULL, 0x0A79D91A95A8D4B7ULL, 0x5406D923E280EA1AULL, 0x95CAEEAFF36CFF54ULL, 
            0x01CF72DD66DDF1B5ULL, 0xBED71EC881E8C345ULL, 0xA68BFDB4BAE20A20ULL, 0x19D0CF115F0799CCULL, 
            0xDE8AA99405ADB390ULL, 0x4CB571B2C6914F05ULL, 0x918FED6CE2FFAF0EULL, 0x4421CF240888F215ULL, 
            0x6A440D5B4F589D52ULL, 0x46EED60A56F3D7B8ULL, 0x4A413AC2BC14A3E2ULL, 0x756C2A2021025F59ULL
        },
        {
            0x94FCAB6F98226CD9ULL, 0x50D66E48BD156E13ULL, 0xDB47932B209D72D6ULL, 0x23F46DDB7C18A02CULL, 
            0xC28485943570D3A2ULL, 0xF417CD43F9CCD33BULL, 0x8CD75820AC18B1DCULL, 0xC37CAAC98CD6E79FULL, 
            0xCEB190CA73514117ULL, 0x139CAE52D042DAB6ULL, 0x7B5EFE17EA896C40ULL, 0xA454E40637FB625DULL, 
            0x9FBE6235057B6959ULL, 0x15ECAAA2DE1F2476ULL, 0x3CF79E80AD74A9B6ULL, 0xF859793CB33754D5ULL, 
            0xBBC1E51052EC02FAULL, 0x3E41A2108105D6B6ULL, 0x4C0FF850D4611FE6ULL, 0x8200664EEEF50611ULL, 
            0x091B5062FD946850ULL, 0xD2D7CA28CBFDF1AFULL, 0xA55DA2B4A5C25C4DULL, 0x0DFB9B0F9FECF01FULL, 
            0x8171D57661F0315DULL, 0xCA37C36504A89B6AULL, 0x9667C2FEE7C7914BULL, 0x70004558CD7A61A8ULL, 
            0xD5D89131BF5863B3ULL, 0xC0B2142EEFA632E9ULL, 0xD857EB03EB39ACEAULL, 0x1367BB3CEACDAC28ULL
        },
        {
            0xAF66AE99A0C5689FULL, 0xD4274D4A9715CA36ULL, 0x0F625F5E71251FB3ULL, 0x51C0EDF407711D43ULL, 
            0xC56422FC097E0D23ULL, 0x9EF9E606C0B989CBULL, 0x67E54D144F1E60DEULL, 0x402E149A47927553ULL, 
            0xB63DF94B42C34F0EULL, 0xC2C4F310627C26D6ULL, 0xAD6D973475F9D364ULL, 0x5CB4BB8D4EC452E8ULL, 
            0x5BEAC7010930BF62ULL, 0xE7E6B236D60B66D8ULL, 0x27DB2FC689E2C492ULL, 0x1E1EF880514E5F99ULL, 
            0xAFEEC29A3FB93C5FULL, 0x6D4E3920BC5CFA8DULL, 0x87409BD2D5F38615ULL, 0xAAD249707118A7FBULL, 
            0xD6F69BE8E2E9F601ULL, 0x255323A3A0C3F4E3ULL, 0xB2636B2086E623CBULL, 0x64735762163E152BULL, 
            0xADD89942EB1D431CULL, 0x6CE836B7991CBAEEULL, 0x504794E66514FC71ULL, 0x0D9609E3B7563F78ULL, 
            0x29F5A22441FA39D1ULL, 0x287612248BA55BD2ULL, 0x7132480FB5920380ULL, 0xEF7A70884DD653B2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kKeyRotateBConstants = {
    0xAE2F4553735B6B46ULL,
    0xB96AEB7DF8479D2AULL,
    0x1461CBC0F5C91470ULL,
    0xAE2F4553735B6B46ULL,
    0xB96AEB7DF8479D2AULL,
    0x1461CBC0F5C91470ULL,
    0x5F37A5CDEEF864D3ULL,
    0x905429E4D3FBDB60ULL,
    0xE8,
    0xD0,
    0xC6,
    0x4A,
    0x76,
    0x45,
    0x15,
    0x38
};

const TwistDomainSaltSet TwistExpander_Achernar::kKeySpawnASalts = {
    {
        {
            0x3C281E79C81230FBULL, 0x98BF357A1D98494DULL, 0x9A1B31F23A64A637ULL, 0xEFB2787509CE985EULL, 
            0xBD323C38D867A91BULL, 0x20293A27CC315376ULL, 0x43DC11C4D4E25678ULL, 0x826AF480BE9ECB2BULL, 
            0x759511B30C12F763ULL, 0xFDA569E9D1012E7FULL, 0x799FFB6595B5EDADULL, 0xD635C2512AE2E542ULL, 
            0xBAA67B4C8E923E29ULL, 0xD37ED6D02EA7750EULL, 0xE536F8A3D37394F5ULL, 0xD46D1CBA891DDA2DULL, 
            0xEC9E18B168DFFEC1ULL, 0xAEC5DF33A9BB836EULL, 0x96CEF7BA379C86C9ULL, 0xCC0F90BDB66FA6CDULL, 
            0x7DD213FF45C1FD5FULL, 0xB7532F36EBB07F9EULL, 0x97113BEAA3F235D1ULL, 0x79537108B58B263BULL, 
            0x43877E1773D6412EULL, 0x4EC5213A2B78286CULL, 0xA34673C028F3AC9EULL, 0x26C37D0502E9B30BULL, 
            0x61CA73B03D395C77ULL, 0x1D31091DC126D1EEULL, 0x6394E37E7F32B1F5ULL, 0x3DCB7B3DD43828A6ULL
        },
        {
            0x145DB3AB77F6F164ULL, 0xA4D191357CB1D8F1ULL, 0x6B20FC9CCF87A463ULL, 0x0B03E1A9C931C8BFULL, 
            0x49BCA66C4952DFB1ULL, 0x3C132EED5B0FF642ULL, 0xAC9231C8F289F7A0ULL, 0x186B9B39D2368675ULL, 
            0x59FDD957608F5929ULL, 0xF9FBFAE4041A7543ULL, 0xF9A3B03300939CE2ULL, 0xC19B5CCB489C9D15ULL, 
            0xC5092DF5DB531E89ULL, 0x2DDADBF8A5E55F87ULL, 0x7D9D411543FFB1ACULL, 0x2B96D8EDF9175AA3ULL, 
            0x6F4F2F77CFE6231AULL, 0x3AB6313DE4A2ECC3ULL, 0xD7964085DAF502ABULL, 0x995FBEF62CDAA162ULL, 
            0xB828B2B609677A7CULL, 0xDAEBEDA34C4F5C12ULL, 0x7E524A635AEE292CULL, 0x4F81CBB430025143ULL, 
            0xA4D72F82C06CBC98ULL, 0xEA43E03BB8B50833ULL, 0xED5C208275FDC638ULL, 0xCAB3BE70B06DC01EULL, 
            0x54C1E8071967C0C6ULL, 0x46EE75D196827E65ULL, 0x36016FC097EF0A2DULL, 0xF0A931AB462BD2F6ULL
        },
        {
            0xC98466B2F2FB3C3DULL, 0x57FF97215EBAB124ULL, 0x93EE7892FA1500ECULL, 0xA715319D9FA5BC6EULL, 
            0xEAD44A25B3AAEF18ULL, 0x2AA6984291C7970EULL, 0xDEA1F78C1FDD93D6ULL, 0x03721CC99EFAFD4CULL, 
            0x5327A28EF493B4D4ULL, 0x75A36DE16B8C1BFCULL, 0x7E83497D6942CD6FULL, 0x632A46A3D7E0C9FFULL, 
            0xE98BBD902E41666BULL, 0x6C58B3C1E91EB58CULL, 0x9631C772DFB06A41ULL, 0x88C57A4E8BE8CA51ULL, 
            0x6008783F5E3F43A0ULL, 0xC58EEB0DAFBAF5B6ULL, 0x21AB8D66F1064032ULL, 0x335B0648D357DC75ULL, 
            0x84D65147B5452258ULL, 0x2770A07BA60B1976ULL, 0x50CE9FD59A0420EBULL, 0xAB922E5857A32FA5ULL, 
            0xB78C754D3DD513FAULL, 0xF3A7E479E07D3504ULL, 0x6666C5786F61F4FAULL, 0x93A805936D58707EULL, 
            0x0A9D8A0F0B33DC5CULL, 0x67838FA28EAC6F5CULL, 0x5E5584D6F3EF3BA7ULL, 0xFBAAB71B8586C532ULL
        },
        {
            0xE01DB36F954DAFBDULL, 0xDEABFC3D142E6AB7ULL, 0x3723FA708FDE79E1ULL, 0xE4FB88DBE3260741ULL, 
            0x20CE724BFF94814CULL, 0xD9FF1B71E51C51ADULL, 0xB7DE6F0A9FFBFC92ULL, 0xF5F3631450680663ULL, 
            0xA9155EACA501BB1EULL, 0x87A5A9AD4ACF04B0ULL, 0x6006E72989C93477ULL, 0x84B6C5322AF5AC85ULL, 
            0xABFFFB8B0D85410CULL, 0x1ADD717BC421E32EULL, 0x8518CA78A028DA17ULL, 0x84A148B08EE05896ULL, 
            0x4F0086F7E7E9AD8FULL, 0x518F6BCE5485CBA5ULL, 0x95D4270E62DE1132ULL, 0xD391EAE54F8B0EB6ULL, 
            0xCF37D0EDA47B494DULL, 0xAE813483BC9A59A0ULL, 0xB172510F05BF4804ULL, 0xEE2433683984C8DFULL, 
            0x723C9E8D0FB518E2ULL, 0xDE5BF837C584438AULL, 0x47C864090DB9EE73ULL, 0x17998BBA0DECE892ULL, 
            0xCFC68922BC8B4D09ULL, 0x281C46958520E857ULL, 0xFFB24336A2C017DBULL, 0x084DBCEF130B1DC5ULL
        },
        {
            0x88D97FA7D1A559C5ULL, 0x7097FE4A9886F479ULL, 0xEF0CBBFB4DB73703ULL, 0x68CFE709357816AAULL, 
            0x42470912CA57E9B7ULL, 0xD2AD9B5AE92BED24ULL, 0x087BC3B6086A99F3ULL, 0x8029B290185417C7ULL, 
            0x703501FB5022F482ULL, 0x7F1973FD4A3F3CABULL, 0x78A0B291F155089FULL, 0x3776F0CA380EC5B6ULL, 
            0xF33B29844581D602ULL, 0x4BA30D295F49E5CEULL, 0xAA499303E48F814DULL, 0xD48521FF3719C39CULL, 
            0xAD17CFFDD9209E95ULL, 0x4E354E829E3FDFCAULL, 0xD04C02D4FB5088CFULL, 0xBE8C337464959A01ULL, 
            0x8651A30301985605ULL, 0x085CB1A81C66AF04ULL, 0x64DA2808E4A61DCBULL, 0xD39BC4855EED0E89ULL, 
            0x9F17D16C3CDF77E7ULL, 0x65DB385DF0EF4BEEULL, 0x4822263492C2EB5FULL, 0xA541C48AE5D31C62ULL, 
            0x0D2F1443B2D887B8ULL, 0x77C6EFC6B5CE5EF6ULL, 0x948E36FDBF4E0C9FULL, 0xD78E53281ABC88C1ULL
        },
        {
            0x45409F2F5D1F605EULL, 0x90F215B9C2734C0DULL, 0x2A89D9E70B8EC4B1ULL, 0x967454F93E9CC71BULL, 
            0x64489BCE9116AACEULL, 0xBF4FD294BE65913DULL, 0xA782A5F0D95B05BDULL, 0x57A524DD08547A6CULL, 
            0x01C519EFC2882247ULL, 0x4544950A5B93178AULL, 0x5896C76A3A4A51D5ULL, 0xBA11E04B6BE6A903ULL, 
            0x25777C9037B0B4CFULL, 0x91BD4F671B269424ULL, 0xAEF6E2FDED0F5168ULL, 0x746BF5A4B1EF2722ULL, 
            0x03C623285153998AULL, 0xCF8F1D7B33D5484CULL, 0x8369B20D6A15C4B9ULL, 0x1DCBBB8B2EF2E771ULL, 
            0xBB2FC35F52F76995ULL, 0xD4B8D0D092850430ULL, 0xFAD6741D7956EC77ULL, 0xB603CBF227EEB3D1ULL, 
            0xBCA21B353BB212BEULL, 0x12C8D5657F48D36EULL, 0xA92F2ED1DEE8DBACULL, 0x2982783A7B728852ULL, 
            0xAB0683180462409EULL, 0x03FE0D863DE221EEULL, 0xAC4F7F5D27E09757ULL, 0x95DC1E29C49D9F7AULL
        }
    },
    {
        {
            0xD1527AF6DCA0D036ULL, 0x80DD8D2B9F81D24EULL, 0x12C599AB1F012593ULL, 0x9F59A8FE91615E2FULL, 
            0x8DED6357E33497D4ULL, 0x42351B357E5DD7FCULL, 0x7B1F3AB480A9EB1DULL, 0x7770380C45B2DC27ULL, 
            0x67BD70E7F5829178ULL, 0xAAE60D1DFE29F8D6ULL, 0x5EF9C725E7C9F595ULL, 0x97EF11715C69FE41ULL, 
            0x1DC30C1D513DE2F0ULL, 0x13E162171D56DD89ULL, 0xF7A6451AEFC3C306ULL, 0x49DBF58E8FE4C33CULL, 
            0xDD03C2F68BCFADB9ULL, 0xF620AA4E78F752C7ULL, 0xBCE745A1CF6597C5ULL, 0x70AD61D62FB6922DULL, 
            0xA10FCF676478AC71ULL, 0xF50B3295766FAC6DULL, 0x81EACCF42634E876ULL, 0x8FC8891D13794BDFULL, 
            0x818A8C0FFE4FC8CCULL, 0xA40D639936534066ULL, 0xA39BE98960F8A47AULL, 0xF8B65456404BAC59ULL, 
            0x5B476822BE0F1C80ULL, 0xCF900EE34DD42846ULL, 0x6053BD1B5FFAB4EDULL, 0x69ACDEDB48F07764ULL
        },
        {
            0xD2324ABF919215C3ULL, 0x0FFE75E18A7D302EULL, 0x62A5A41292879111ULL, 0x6EDA9C2BF3C8B7BBULL, 
            0x6E711621B7AEF969ULL, 0xEB7D1518F1D4D0E3ULL, 0x0646F585B14BFBDEULL, 0xDE2EE8E5F207F129ULL, 
            0x294F5E63D3A1DAF4ULL, 0x19F354A892F248B8ULL, 0x571C4E26486DD215ULL, 0x9E9A68962608B388ULL, 
            0x5611BBBA3E9B79D0ULL, 0x9104B608386A7A92ULL, 0x60759A74BEDC51FEULL, 0x8108BF1686513957ULL, 
            0x3311CC624680DAAFULL, 0x76C210BE51E68CE4ULL, 0x139951B9A802279BULL, 0x46C6BA628C1F95E4ULL, 
            0x31F66B961542EC84ULL, 0x67C301950AA8D21BULL, 0x92F9B136C479E80BULL, 0x2ADBA9D92B057AE7ULL, 
            0x7E57FFE744043167ULL, 0x227760352BDEE981ULL, 0x87E8B27B78D1B2A6ULL, 0x45B3E09DEF1172F3ULL, 
            0x2015CE131BDF1E08ULL, 0x28CA57D383078E72ULL, 0x2FA58D08BB3D1375ULL, 0x80D3D0C70FD7844BULL
        },
        {
            0xC34CEAF4AD08298CULL, 0xA95938FDA6DF09ABULL, 0xAFB5E1437E603B01ULL, 0x8056873E8F715E11ULL, 
            0xE51BF5A18A196871ULL, 0xBE75F980FD4D73C2ULL, 0xDF87E81DD4C606A2ULL, 0x34469515200FB00CULL, 
            0xE66A8178D80CB6D1ULL, 0x47A5C135620B07DAULL, 0x396AB78929831232ULL, 0x0B7F2605A995305AULL, 
            0xBCC8FECD64EDDECBULL, 0xABD063E94063985AULL, 0x784D297C1566D00FULL, 0x96FAA74D19DFEC43ULL, 
            0x0478A45958924300ULL, 0x390B754DAC5B97BCULL, 0x8E89513D1E620C4AULL, 0x6B05162D6711D09AULL, 
            0xBDCCB8E0A198A9B6ULL, 0xA0E709EFA9FDC30AULL, 0xF0785AED9E13E044ULL, 0x842E5160943E2D31ULL, 
            0x5750046AB03C4AABULL, 0x01662E2433FE3790ULL, 0xD6FBA05FB9305985ULL, 0x2D27BEC10EB63DEFULL, 
            0x1E81346A75E16210ULL, 0x5F153C15F02498C8ULL, 0x3329B3B257595C5FULL, 0x4F0F669BDC3D4229ULL
        },
        {
            0xEF8CC71D3CAD5D83ULL, 0x9F5585A4C58F51B8ULL, 0x401D4AD0FBC76D34ULL, 0xB9D116FF75C1FEF3ULL, 
            0xEE2CA8AEA8E28F34ULL, 0xAB94B89BC4ECB9B0ULL, 0x506869D00746ADA5ULL, 0x4030CE2148B87E53ULL, 
            0x7AE6672CD361EE53ULL, 0x3CA824E568974357ULL, 0x28A6A18C8DEDF5E0ULL, 0xA81EBE1D92C7A86FULL, 
            0xBF1554995D9D0A3EULL, 0x27E14739DD875EE8ULL, 0x0E3725FD322D2F18ULL, 0xF5AB4D37E553E339ULL, 
            0xCD064EF615C4F6D0ULL, 0x953E659C7440B498ULL, 0xA6DCABEE9193E0E9ULL, 0x2CFF86AC291554D3ULL, 
            0xAA8EEEA087FC18B3ULL, 0x30ACAC6A68B745F1ULL, 0x1717EA04606554A7ULL, 0x921421F4FE5D68D7ULL, 
            0xDEB9471E25034D51ULL, 0xA798C7BACAEEFFA5ULL, 0x37DCDDEA4FBC644AULL, 0x445BCC2597396881ULL, 
            0xDA39ED70A2B12952ULL, 0x644D126E24D3DEB6ULL, 0xB1C7D4761FF502F3ULL, 0x966877F9A3F59C01ULL
        },
        {
            0xDB1E9B1CD3BFB523ULL, 0x839BFD494CD09F79ULL, 0xE972E97771F64BBBULL, 0x71FD6631DA0EF7F1ULL, 
            0xE1471CA50159B065ULL, 0x543BBA05909D9C87ULL, 0x577F8B62106998EAULL, 0x348DF7F56B489242ULL, 
            0x74666CB88B56CF24ULL, 0x9D09BF71E2FA535BULL, 0x117F899016D75BE1ULL, 0x134B6648CD9CED32ULL, 
            0xB4C40F5BE58DF984ULL, 0x1B7CBE2B2BEBE7ECULL, 0xA37B3EEA111B3600ULL, 0x8FBACEA4D670B59DULL, 
            0xA6B11432A42B8A2AULL, 0xF0C3AD17B6784ADDULL, 0xEB19497F4E2950F8ULL, 0x27C75F808CA55C4BULL, 
            0x19A43CC8CE943703ULL, 0xCC21B37B5796DBE7ULL, 0x7FA3589FE8E123E9ULL, 0x7E6B8E934FF0F36EULL, 
            0xE5FCE4C7373D52A7ULL, 0x7881A979DD828BDDULL, 0xCE4424B0E942D4CFULL, 0x465C33A44215384BULL, 
            0xFD79651F99FE4E51ULL, 0xE7357BD425A99609ULL, 0x45B5F2099CE009F7ULL, 0x475D63B5F5C875FAULL
        },
        {
            0x949F56CB2437524DULL, 0x783AE2E8A9067CF8ULL, 0xD1D86CC9780589F6ULL, 0x96F364EF6F9ADD20ULL, 
            0xE907B001A0E602BCULL, 0x89FEA79A37587B27ULL, 0x7C6815ABDBF42F76ULL, 0x47A90E5249DFF8B8ULL, 
            0x4CB1443E630688D4ULL, 0x26C5BB9EF9CF36F2ULL, 0x7CAEB948469864C0ULL, 0x05A09F6A89551996ULL, 
            0x4DA3FB08D9433045ULL, 0xFBE12C4C6210CD01ULL, 0x6731FC171123238BULL, 0x0BEB30080DCBDEA3ULL, 
            0xB9571BD2611705E2ULL, 0x69DA608D1CC8BAB9ULL, 0x9E267F4BA79138C4ULL, 0x973CF7AC59F7B66DULL, 
            0xF9EFE8FFB42D624AULL, 0x3A5B8EE5F5F05505ULL, 0x0D9601E9D09AAB09ULL, 0xA95470B3D9F6F1DAULL, 
            0xD5E2BD6E1F62B97EULL, 0xE0E6D38DBF308E0BULL, 0x525B086396C99619ULL, 0x048C81843ACFF122ULL, 
            0x30003376E7C5A8D7ULL, 0xC9ADDA1F1207AB48ULL, 0x0B484FC2C0549AF1ULL, 0xD3C05AAA9182F07DULL
        }
    },
    {
        {
            0x477C0F6BE4C9353EULL, 0x6783CB9F9AFAF77CULL, 0xBB5A7AC6F8809EC7ULL, 0xFE7069305BB1529DULL, 
            0xBD05CD620400B28DULL, 0xA18F13171A16E25CULL, 0xD68E4BDC0E7A8238ULL, 0xC4E839FA514BBD6EULL, 
            0x056ECC4DAB3FA0CDULL, 0x7951B3F969AEBAC2ULL, 0x53430B88DCA96A3AULL, 0x057C586F154047A0ULL, 
            0x982F7B8019D44F60ULL, 0xC01080113A1D4782ULL, 0x2D9A9693D33DFCCCULL, 0x0940FFB1ECF0AA5BULL, 
            0x8CBAFA414B02543EULL, 0xA421FB80EB4AF8D1ULL, 0xE3932491C9A97303ULL, 0x4012F103E870A0B5ULL, 
            0x7475D14E63F5027FULL, 0x393C31797450550CULL, 0x60EE5312A3CF3BABULL, 0xC22A94A53CDE0A42ULL, 
            0x458C38357DCED705ULL, 0xBA8D0634D2FB1BB7ULL, 0x42C5C93DA177B57DULL, 0x3578E14120B51826ULL, 
            0x33A45661E2CCD7E2ULL, 0xD023B8B29CE7673CULL, 0x21757633E95994FCULL, 0xBB90BF00A07DBC63ULL
        },
        {
            0x25BBF2520DDBCB9DULL, 0xA2EBA5DD44617D1EULL, 0xB602F182BE3F89FDULL, 0x85CC00301AA30687ULL, 
            0xA6B4C47574813283ULL, 0x00729E57CDFE9080ULL, 0x95B9135BAE78AA57ULL, 0xECF5B5A56173F932ULL, 
            0x955FD8418A669CC6ULL, 0x47B196452B0C6702ULL, 0x55BBFFF9C4025575ULL, 0xE5AE1E8A19B42D1CULL, 
            0xC0DAB1A023550E12ULL, 0x37FDC80AD44DCC79ULL, 0x81BC999DD3ABC999ULL, 0x801B4A4A6934163DULL, 
            0xCD944F07F9EB515EULL, 0x6274ABADDB1D487AULL, 0x191F687D44E93D79ULL, 0x7875498059A5654DULL, 
            0xAB7D98EE93D886DEULL, 0x2D44587063F2DD5AULL, 0x1E1B3760A81FFCFEULL, 0x52BE193E03D98C75ULL, 
            0x36EBD752822CFE5CULL, 0x53EFF7CF91ADF60BULL, 0x767883445C06BBAAULL, 0xD5259DD1C4FB4670ULL, 
            0x6DFB6B22A628F8FBULL, 0xD2D06BE3EE612FC6ULL, 0x893EB872F0B21D51ULL, 0x54241A79447793B3ULL
        },
        {
            0xB42EC8C707F6C924ULL, 0x8288BCB30C0685C1ULL, 0xE5B9BF169204BF58ULL, 0xB4E0B57493A0DCE1ULL, 
            0x984C4CC3784D8EABULL, 0xF2F8D397BF129126ULL, 0xA72DF03D0E30CB0CULL, 0xCB578C6FBFF0B6F9ULL, 
            0xF5ACBE97E30E75F7ULL, 0x2ECC8C0A5D4AF72FULL, 0xFCEF5E34E411AF17ULL, 0xEC0CE98B49932C34ULL, 
            0x61A602851E0CF7EEULL, 0x5ED6A5C512A0C475ULL, 0x5EA479576926EEBBULL, 0x05008ADDE327D82CULL, 
            0x692853EA496F2BBDULL, 0x183380973BA1DCAFULL, 0x6F0C5065686C1B2CULL, 0x18814F0FBBD72C94ULL, 
            0xD836C096911DD00AULL, 0xB643D2941A8A027AULL, 0xEB95B9154DCB0BD4ULL, 0x9AB4D9E2CEDC05BFULL, 
            0xF2D990A88FD55B91ULL, 0x265B0C6842F4CB5EULL, 0xE45D697B469F3579ULL, 0xE2E85CC8B36D361EULL, 
            0x841107A0CBE6797AULL, 0xC89B413E73BF0647ULL, 0x6E8BC1B14128B4B8ULL, 0xE55CED068C9AFA14ULL
        },
        {
            0x216288EB34E0B6DEULL, 0x3CCFE5953B1147F5ULL, 0xCA204C266CE2FBB6ULL, 0x5B316C32C35737ADULL, 
            0x59FA07C5768A2287ULL, 0x42ED33AD9442F906ULL, 0x35A1626E42BA07E0ULL, 0xFAF8334D72AB198CULL, 
            0x0832CBBE4E8CDA47ULL, 0x2170F367CE4BD814ULL, 0x571C75F57DEB460FULL, 0xAFB2F8682F8D8BC6ULL, 
            0xD74D3B7311084C54ULL, 0xAFA0FFCE67504C1BULL, 0x35A82836C1E7F134ULL, 0xA006148FE2773DC2ULL, 
            0x1C2A334C7F8B8CBDULL, 0x8F4E99F4BB87DC68ULL, 0xAC7BBAA71E3F7DD7ULL, 0xA72A661A522E55E0ULL, 
            0x459A17F1E3A5C83AULL, 0xC08BE92163E78383ULL, 0x3BE4A04096626C4DULL, 0x9A54F0EF1F4D9FCDULL, 
            0x5DB702496190BE39ULL, 0xAFF88879688DD1D7ULL, 0x461B154B6CB9D34AULL, 0xB65A9C7AEB51859BULL, 
            0x0DAA5E08FA606C93ULL, 0x1C04647A904D9369ULL, 0x9841C198C5B11B0DULL, 0x36F5CD48F8C76018ULL
        },
        {
            0x462E74687E0D6D0FULL, 0xDD433002BC11B9FDULL, 0x64D19BDFF6A78EFEULL, 0xEA212FFE6701CF04ULL, 
            0x0F1D0426257EFE36ULL, 0xC07A8D8BE8E5ECA1ULL, 0x600400592A4F20C5ULL, 0x908E925E6CE895F4ULL, 
            0x8D38D219A635878EULL, 0x2BF08E45F20103A0ULL, 0xA66FE44FA6ADAC84ULL, 0xD1DCE83DE6CEF14BULL, 
            0x4134256725604E0EULL, 0x0834585782F224F5ULL, 0x92E0B616C0C2FFDEULL, 0x59BE53F9BAA8D488ULL, 
            0xCB6A19755DFF5050ULL, 0x725D32EEA950DF1BULL, 0x854C495B183B51EEULL, 0x5472F318D60A0B3CULL, 
            0xB6A230AF70BF4920ULL, 0xFF55F7CE6DD7B9ECULL, 0xF0759D9D3420CDC5ULL, 0xB877673612D0669EULL, 
            0x6308F236DE2F1B1EULL, 0x210F97BE889B9306ULL, 0x5E317526EAD3AA50ULL, 0xE17F0DEABA7BD303ULL, 
            0x232C7999A745F23BULL, 0x49F69FC8CB8466A5ULL, 0x96502111896A329EULL, 0xAF45EE7A913672E2ULL
        },
        {
            0x9E7730446003E952ULL, 0xE0495B8F27C59A9BULL, 0xA38AF6F9AAC257C9ULL, 0xE8C1B555D94C4D7AULL, 
            0x88A43BE3BA3030AEULL, 0xE0FA94CAE7AE0AF3ULL, 0xAB89CAE7A91B91D1ULL, 0x7604E804DD4EC2EAULL, 
            0x8205179EF0C500E0ULL, 0x63F17D57738189D3ULL, 0xEAB1322B47EB52D4ULL, 0xB93407079F0B6AD0ULL, 
            0x82889B7144A29327ULL, 0xA39F60FB1A9C4531ULL, 0x691EC8D2E5F58A50ULL, 0xC69414871F515139ULL, 
            0x3C8BCD3AF0C097C7ULL, 0xC5BA7A54AE805636ULL, 0xB5DB4A37258553A8ULL, 0x35F8B7921ED4A0D7ULL, 
            0x684B2A5748D3210DULL, 0x6C4D948305D3101CULL, 0x43DC1E1BDF319A08ULL, 0x1D8AE9846F1A6EACULL, 
            0x24F272822C827AA6ULL, 0x9895C3E0A263DEABULL, 0x970B59827E66F7CDULL, 0xBEE617F4FDF9314FULL, 
            0x09446092E62ADF9DULL, 0xFBC49AB13E857D23ULL, 0xB73EDF9DBFC014B3ULL, 0xD514431539DFB9FFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kKeySpawnAConstants = {
    0xF25BE812443C5908ULL,
    0x71EDDBD528FA29C1ULL,
    0x91D0DF0A018ABFAFULL,
    0xF25BE812443C5908ULL,
    0x71EDDBD528FA29C1ULL,
    0x91D0DF0A018ABFAFULL,
    0xD9ECF8BC5471D598ULL,
    0x06985C1E4F1EC33DULL,
    0x52,
    0xD8,
    0x1F,
    0x94,
    0x1E,
    0xFA,
    0x5B,
    0x17
};

const TwistDomainSaltSet TwistExpander_Achernar::kKeySpawnBSalts = {
    {
        {
            0x59F41C6ED2B4E90DULL, 0x688F9E4CA52CF81FULL, 0x9BF465C8D0F8E572ULL, 0x48E26F718E02727DULL, 
            0x12F4D94C03E90BADULL, 0xE7A4508CA42A50B5ULL, 0x9A9EAC8EC85158DBULL, 0x71AE94BB790916ACULL, 
            0x29E00713BAF34841ULL, 0x29901F9DF45AC9C3ULL, 0xF02C93D1AADFAFABULL, 0x778BBAE3D83C997BULL, 
            0xCE5C3A6535C25AF3ULL, 0xD428921DB70CBD4AULL, 0x90F33CD56975CFB1ULL, 0x5EC3D5BB36EFBC0BULL, 
            0x58BAE325C933CA58ULL, 0x331AC3DD4997F4FCULL, 0xE4154E5E2EB131A2ULL, 0x34CBDEE8DC215949ULL, 
            0x883FBA999084DB37ULL, 0x6CBA150ED763D557ULL, 0x4AD2A29E878FA023ULL, 0x03F023CCF8651050ULL, 
            0xD9DB59B6B7C1AA05ULL, 0x024AC456A619F3C0ULL, 0x3C61D9B51945FFCAULL, 0x7611B4B428CB2AB9ULL, 
            0xECC5F7E25F6CB973ULL, 0x1845056CE6D47985ULL, 0xD9DE46E4EBE0DBFCULL, 0x18CEE3A9C73BD391ULL
        },
        {
            0x94AA507D8953E9F1ULL, 0x0AFEE76B12602C04ULL, 0xF80E64FFD72D4B88ULL, 0xF13C91BF08227A15ULL, 
            0xF872F3A802F4C45BULL, 0x6B000E317F14F1FEULL, 0xABB154E18702DC13ULL, 0x9C47CC7EFF5FD9B4ULL, 
            0x51ACDFF4153F4286ULL, 0xBDB0F4EA36641DEAULL, 0x5ADBABF728BA9C11ULL, 0x06032539EE1E6C54ULL, 
            0x5DAE83DAE8273FB7ULL, 0x3F4256F67FD689B2ULL, 0x5B8C2D10D924F9EBULL, 0xAE5B3B99AD912B4DULL, 
            0xF1BB07F074F8C20BULL, 0x36405B43737BC127ULL, 0x0B516FE1443A5404ULL, 0xA9CB4863927976F4ULL, 
            0xD2EF3765CCBB83E7ULL, 0x9568CD0C1DCE1407ULL, 0xCBC0C2D54437AAC2ULL, 0x715D2ABB17AF95FAULL, 
            0x082C5149F643E5C2ULL, 0x6FE78663C3B28BE2ULL, 0xD157DAE6C95854FBULL, 0x1E71234843008E5AULL, 
            0x9F994F5C15188B41ULL, 0x8FCE815AF06496E8ULL, 0x5C8CEA159153F078ULL, 0x3B3F50F48A675545ULL
        },
        {
            0x2B54D868DC7BE161ULL, 0xD9C04C24AFC8AFA3ULL, 0x3CDD0FD69D306CB9ULL, 0x838BA0639104EADCULL, 
            0x3C435E91257EBE1FULL, 0xA28D46E7D668C77DULL, 0x0B82457CCEB1B2ABULL, 0x413E200BCF798BD5ULL, 
            0x59F967D7BD1B2801ULL, 0x82379EED1D5C72DEULL, 0x0CFE9FD8016AE5D2ULL, 0x6E0227A6CBD0A7B8ULL, 
            0xB3BF04CF69D925C2ULL, 0x3F903F2995AA7C8DULL, 0xD4FD4AB2DB130B82ULL, 0x5DECA18094B66509ULL, 
            0x8BBF5DD4816822D2ULL, 0x4D4B8BE539E2A87AULL, 0x9E112D7EA52D0BC2ULL, 0x19AD69C00315DAAEULL, 
            0x1AC0736D23C7E33AULL, 0xFBC51C7848FB251FULL, 0x7D14776B5E741554ULL, 0x88A94B70F134FF92ULL, 
            0xCFBFA14598C2AD10ULL, 0x6516F25271CFB09FULL, 0xB59ACD1A8A4420C5ULL, 0xC582859C8C63D604ULL, 
            0xD1C9E30F0DB20986ULL, 0xE892C9B14A9FF9C1ULL, 0x96886DC7A41C2958ULL, 0x9357885E0866C7ACULL
        },
        {
            0x36DD4332575C206FULL, 0x9423D3004CFC32D9ULL, 0x34DEA6B78DDF9BD2ULL, 0xDEF5AB252F440687ULL, 
            0xFBF39A675BA382DAULL, 0x3F77818210F37EA5ULL, 0x2C546EA0C94EFA30ULL, 0xE504C61E70E9A178ULL, 
            0x255359D0879F596EULL, 0x0613F51C5FFA7BC6ULL, 0xDD0E470AEB64C03DULL, 0x12E609F82D0F76E7ULL, 
            0x8D4ED8416EFFF1ADULL, 0xFE4DA6B0088E7EC1ULL, 0x5689009F4FD12B40ULL, 0x7A9E0095FAB4B2C6ULL, 
            0xFB56C233C1D99104ULL, 0x6257A11E93E2204BULL, 0x09F724027EF87DEFULL, 0x993247328BDF19E7ULL, 
            0x79C5485CE4C2B10DULL, 0x8E952C044BDE6738ULL, 0x346A75426FC350CCULL, 0xB6B4272DE02E2202ULL, 
            0x90EF790F29C1AA47ULL, 0x0DAF0480156DBEEFULL, 0xAEDD2002B97E3896ULL, 0x27A14E866D6AB9C2ULL, 
            0xD4D0AD995CEAB295ULL, 0x06239AC977E7816DULL, 0xF419CC07E1EAF10EULL, 0x66086871653745C3ULL
        },
        {
            0x9D642AC8F0BEA744ULL, 0x82E9CB449AB71A85ULL, 0x8A627BC18DC1308DULL, 0x639885725845AEC5ULL, 
            0x17DEF0DD26A3F144ULL, 0x7CE54AA9CD3D39FDULL, 0x9D389E47F8BC3488ULL, 0x70159EA29CEF5007ULL, 
            0x449EBB3250E91523ULL, 0x93C7F1F85C3F0041ULL, 0x73F5D324D89D7DA7ULL, 0x151B9A9495BD332AULL, 
            0x092C44563B1B7241ULL, 0xAC13765C0C2C795FULL, 0x031305A0B066908EULL, 0x86129F2A35E60E3DULL, 
            0x9A10BF2AA7940ED5ULL, 0xB41BC3FC4F7F245FULL, 0x3C1E53BDC9FE9E82ULL, 0x8CC419B9EE93EC2EULL, 
            0x27AA409C0C4786EAULL, 0xE9DFB33941D0A3E0ULL, 0x9E622548AD491A9CULL, 0xA213E2133A37849CULL, 
            0x555B8024547ABA04ULL, 0xD8DAA5CE2C995C74ULL, 0x38189CC70E7CEB4FULL, 0xCD25D1F6730323B8ULL, 
            0xCCC99AF22A712291ULL, 0xAFAD24BC0B5169D5ULL, 0x13949DD4B1D7C67EULL, 0x1F2775F0E4561110ULL
        },
        {
            0xC2D4BF1441BEE0A6ULL, 0x74943E4A691ABF7EULL, 0xE3C210E982E70C50ULL, 0xB73418145BAAAA25ULL, 
            0x6F86362257A93963ULL, 0x3013883867DEF03FULL, 0xE9C78A5B6F30D449ULL, 0xA870895C55301278ULL, 
            0x41743D4F3ABB605BULL, 0x1892921C3E62F1F4ULL, 0x99C40F1F1EE2573BULL, 0xDB5A804CC2717162ULL, 
            0xD74B2E025EB6A5D5ULL, 0xA612643668F711D6ULL, 0xF536F39EE62F57F1ULL, 0xFAEB5A4F0CF389F9ULL, 
            0x3149A6EF305320F3ULL, 0x64F9AF7CBB1FDA40ULL, 0xA159EE07C114ACC5ULL, 0x9CE882FC8C03C5D6ULL, 
            0x8ED8E2EB39CBAFB3ULL, 0xC97E3A624531C46FULL, 0xD32B3CB979287454ULL, 0x43B4D2AF76665D12ULL, 
            0x0DE9FB7F0166FABDULL, 0xFEDD98647C377AADULL, 0x35D18B2F43944227ULL, 0x93CA996C90ACBEA1ULL, 
            0xAB92F3CE061AC62CULL, 0x30C88477E22E13F4ULL, 0x87E261536E48A53DULL, 0x64330F9B1B8AB6F6ULL
        }
    },
    {
        {
            0x2DFD53E446225431ULL, 0x68713E775679D2C6ULL, 0x51149ED080DD2170ULL, 0x3CD8C97FF5D48CDBULL, 
            0xFE6C1D984D8A510CULL, 0x96FC6CFE5B953105ULL, 0x836309051E018946ULL, 0x18D4A270DE6BE0CDULL, 
            0x1D6DCF77FECC231FULL, 0x2457F6249739506AULL, 0x020C9082D997AC82ULL, 0xC4EF6A27B2DFDD54ULL, 
            0x69FAAAB590EBE888ULL, 0xA8BE4EB93B93881CULL, 0x0A2804DD3C845F4AULL, 0x7B0D429B62B7582AULL, 
            0xED369928A8D00C87ULL, 0xD59202B7B53C8ECDULL, 0xFF861615CFA477D2ULL, 0x9008D9805AD1A3C2ULL, 
            0x717AFAB4CC9AB244ULL, 0xB6AD54CC323632AAULL, 0x6A91FD1854C969C5ULL, 0xA624907F0FFD6FDAULL, 
            0x9C4BBCC7382183B0ULL, 0x9DED051E1F473D06ULL, 0xE7086A2A2A3AE7CFULL, 0x4FAC20B2139124B9ULL, 
            0x282650FD367CA634ULL, 0xCEA74522322D65AEULL, 0x71970616E6D90D0DULL, 0x95CCFCC4FBB51CFAULL
        },
        {
            0x54B2564E6841775CULL, 0x6CA3FF277B64CE25ULL, 0x2ADD19299E017E8AULL, 0xB6EA210F4FEC0237ULL, 
            0xC581872226FF14B6ULL, 0x45307F5A20B8BD3BULL, 0x835680C98C4C4CFBULL, 0x1263062860340F0BULL, 
            0x14D1B5EE8FA5EBA6ULL, 0x8000152651965D43ULL, 0x655B77F3A681C312ULL, 0x226BF07EDD411BB2ULL, 
            0xD783FC7EBA6C2585ULL, 0xBD41A5D698D48352ULL, 0x3ECFE2C130D58066ULL, 0xA7CF82A49C284378ULL, 
            0x4510634053BCA486ULL, 0xC035B1AF4F9E4637ULL, 0xFCC79234F8710456ULL, 0x9B91BF886E1FCD44ULL, 
            0xEFEB2CF7E2B97B0BULL, 0x5A474F9D8A327352ULL, 0x5DA8E56B2C4898AEULL, 0x8DF1EE15490F7CCEULL, 
            0xE5D6967C36230368ULL, 0xCE107FDF1CDD091FULL, 0x14F51B21E2179754ULL, 0xADC7A1310E0CBD95ULL, 
            0xA9C1227B817FB87BULL, 0xC52DAEACBBDCEAFBULL, 0x1E4B6A38C1406AD7ULL, 0x810FF925E991BB9EULL
        },
        {
            0x924CAB4566920CDEULL, 0xE581D42D5EF09329ULL, 0xC0A054F0E189B706ULL, 0x15451212CB21A9E7ULL, 
            0x2B1F6A33D15B1A5FULL, 0xD8A53A051DB26103ULL, 0xAA4FF88E6AEED04BULL, 0x3C6CC8BF5DEC1F15ULL, 
            0xB7E714FEA02DBA6BULL, 0xFFFF041EA043A3ADULL, 0xFFC0CBEE89D10F78ULL, 0xD03BB23C1514FAF3ULL, 
            0x8A585F249749B2E0ULL, 0xB20753DA1F6AD496ULL, 0xC30D10BA4E2D80AAULL, 0xD1743CBA319ED9F3ULL, 
            0x6C4EFBFB0344E5D6ULL, 0x3807E808F73B1206ULL, 0x9EAC8468A5B1558FULL, 0xA7B0C629B711DCF4ULL, 
            0x83414E9D051EA785ULL, 0xC4467561A32791A3ULL, 0x5B9D1A071F24491CULL, 0x1E0F57A783D85548ULL, 
            0x1654FE79BEC5D3B9ULL, 0x8D5FFEAE8A9CDE37ULL, 0xBFE1F4A6D71CEDBEULL, 0x43FC2B8B7798D7EAULL, 
            0x5F6A19695B2283C2ULL, 0xED4DD85261B2118DULL, 0xCF6BCDC28D984F18ULL, 0x159DBF13B7CA5C86ULL
        },
        {
            0xD560288EA436C485ULL, 0xF623C2CDE9A1F2FAULL, 0xD72873C22C4DFAF9ULL, 0x1CED99BA1317EDB4ULL, 
            0x4D54D721363D8677ULL, 0xCA9AD6DD5CF5DFBFULL, 0xB6DB3D8FCEB4969DULL, 0x055342B43AA7D6F8ULL, 
            0xE8205748E9CC3F52ULL, 0x3E6A2349859AB9B7ULL, 0x2A401D095BA08BEEULL, 0x1B6ABF18F35DA1A1ULL, 
            0xAC03FDAD5C96AEA0ULL, 0xB6766145B4F7870DULL, 0xEF7203B882FE42CCULL, 0x9BFBA670342750B5ULL, 
            0x863E875DA64A13E8ULL, 0xE65969405D4B8F89ULL, 0xDB080B714274027AULL, 0x40ADC7E4F626DFCDULL, 
            0xD89BC6DE3C8F1F8CULL, 0x763E281B4805DB5EULL, 0xF277ABC9EA9B5862ULL, 0x10EC7F3F169B9A7DULL, 
            0xCF3B49C35D792755ULL, 0x6240EAF708BFFB64ULL, 0x8EF70A64309916EFULL, 0x5EDFF5C73DD8399EULL, 
            0xF04B226B26517451ULL, 0x2A3CCE9F8A94177EULL, 0x22DAA7A7233987D0ULL, 0xBCB0806D84C8D3EEULL
        },
        {
            0x2F75BA92760C3A45ULL, 0xD6513B825D9C1E84ULL, 0xAB8820A3D159495CULL, 0xCE560AD2B7A1C856ULL, 
            0xB4E7A104B9D83EE6ULL, 0x16960F3598CB9067ULL, 0xB4F464DFC9052052ULL, 0x8A16E453817FACCAULL, 
            0x16872D18380A9014ULL, 0x7798378885AA5764ULL, 0xE008F1832ECA81A4ULL, 0xDE4CA825162433F5ULL, 
            0xEB9789B9D4B3843EULL, 0xEAFF849AB72E0121ULL, 0x1FDCE1755CC34B1FULL, 0xDEA367C9DD15E3B9ULL, 
            0x2BB6068C3219D0EEULL, 0x93DE3CAB8B5FE88DULL, 0xB201E2BCF8BFB7DCULL, 0xD7F3126AD601BDAEULL, 
            0x28C79CECC44BB2C0ULL, 0x7BDD85A67AC73E14ULL, 0x44E49DF22B57DDCFULL, 0x9FF270E9323A20F6ULL, 
            0x022BCB58B5AF0521ULL, 0xD969112B99021AACULL, 0xB0A7F0F22D02F67AULL, 0x2B68E5F4535ADEC4ULL, 
            0xC2865523C1281DBAULL, 0x2BBD2E31ECF29C24ULL, 0xCC041E2238185615ULL, 0xC485C98BCBB20E8DULL
        },
        {
            0x27D6DEEFE8B2D46FULL, 0x493261147B81EBB7ULL, 0x56CA13562D6D692BULL, 0xF7A734C2A1634ABDULL, 
            0xE67979968FE85F21ULL, 0xFC94064EF9CD8003ULL, 0x883B0315EA818E74ULL, 0x32B07F30173AF158ULL, 
            0x45BBEAF6623AD0E8ULL, 0x62C26A69C6E8D004ULL, 0xC374D8A496EAC333ULL, 0x3EAAC7F936730BBFULL, 
            0xAFDB071E4B05741CULL, 0x026200C578C7876AULL, 0xA058A7B9B52F2F5DULL, 0x9F07A52B69951EE1ULL, 
            0x03336718085871BFULL, 0xAA9D9B0E67FF8544ULL, 0x2DF4BAADE89FC3C2ULL, 0xFDAAF5F966870E63ULL, 
            0x3683A403D63A3C24ULL, 0xFB8CAA4C95A60EABULL, 0x6E6BE1031162506FULL, 0x8BB235E2CC0554AFULL, 
            0x0F681E68B3A4FD84ULL, 0xAAB698673B120262ULL, 0x65F9B3EA3D11DE2EULL, 0x31DA30F63E44D182ULL, 
            0x56952AEDDAC690A6ULL, 0x147A90DFC8BA3FBDULL, 0xACEC849F230D23A0ULL, 0xAB6F30F2C7531AC2ULL
        }
    },
    {
        {
            0x52B4C5D728175A32ULL, 0x2561E76D163515FEULL, 0x22ADDAF49818CEDEULL, 0x5B4A1F831A003D28ULL, 
            0xCFFEEEF164A7D221ULL, 0x3DCBDE7789F83442ULL, 0xFDE2E0D2DB5B398CULL, 0x5D6215ED2E4A5B4DULL, 
            0x301ADB8475E1C294ULL, 0xF1B2E5BD137E7399ULL, 0x136920BA77924D7FULL, 0x26C30A7625B08114ULL, 
            0x198FED97C33CC160ULL, 0x9AC69739561670E9ULL, 0x8B981E3E623779BFULL, 0x3F7C72527E0DD53BULL, 
            0x581E5694650E1D90ULL, 0xBF583058CE4BA1BFULL, 0x75B39A604EC1485FULL, 0x813B4F8F6110507FULL, 
            0xB7772D81A9A38273ULL, 0xE1BFF2C2F8C9899FULL, 0x161A3BC96D727EF0ULL, 0x85312C9C815BAAD0ULL, 
            0xC919D4CCAD19BA20ULL, 0x567778FB661BC04FULL, 0x5BD15DBE5D256C9BULL, 0x5AC2B1203B944C15ULL, 
            0xD5DEA4CBE713EFC9ULL, 0xFA9179A5706148A1ULL, 0xF2AEB28100A1E408ULL, 0x047F7FF8B6082DD4ULL
        },
        {
            0xC7EC69B50ECCDAB7ULL, 0xE3157A192EFD7B3CULL, 0x317DB9C72ED43768ULL, 0x892EC94D94D9279FULL, 
            0xA4135438D7465040ULL, 0x939457A36BEAC524ULL, 0x627B26C5482FBBCDULL, 0xDC4E0D820F9726DFULL, 
            0x5890A8A7D147E0ABULL, 0x616B4442CEA78168ULL, 0xCC270B1651E37338ULL, 0xF661AB2C6DD9D63AULL, 
            0x711A2EB142E9978CULL, 0xD39EF3F077227FD4ULL, 0x10B8F04D0D2FDA39ULL, 0xF78B72D1CBDE2F36ULL, 
            0xDA06F93BB1665445ULL, 0x656F734AC38325D1ULL, 0xCCD40A78589DF077ULL, 0x68B7AE961DA0CB5AULL, 
            0xD7231FFF25444397ULL, 0xA2F9F63A3DDA0A2CULL, 0x5E07256E6F86D285ULL, 0xE559FC7558FBDC3DULL, 
            0x714D60053E04A05CULL, 0xEF1D0308075F3921ULL, 0xD4382C6F9462969AULL, 0x6A94B1C854984AC7ULL, 
            0x8780788D6A3E690FULL, 0x9A9C18B4813626F9ULL, 0x4D51118703C38B3EULL, 0xF0C1BB190646EB25ULL
        },
        {
            0x87FE56D1F7B3547BULL, 0xA98FD5841177521AULL, 0xBBA408663762469BULL, 0xE33AB453DDCA2DF5ULL, 
            0x284AE4A52B3148F4ULL, 0xCC3A99F7F4B5427CULL, 0xC7C9171D59589900ULL, 0x1569FA7F57F808BDULL, 
            0xB5D0A50AA0ED7728ULL, 0xF157E011ADC98400ULL, 0xA233CF2D2C17139DULL, 0xB5615C1DBF8C7ED6ULL, 
            0x455E5C59EFB07974ULL, 0xD41C1A69FD48C14FULL, 0x2E8EC05C360E5592ULL, 0x3917A224E6C79CB3ULL, 
            0x8FB5CC46DD2B194DULL, 0x518250CF89D15374ULL, 0xFE30C24F2B89FAA5ULL, 0xBAD25B13D937A8CEULL, 
            0x396C9D43BB00B8F3ULL, 0x3AEA84254EBC1726ULL, 0x44C196B1535D21E4ULL, 0x32F124AACCE37DB4ULL, 
            0x0FCF41D5EDDCD947ULL, 0x7C2BBE9061894A44ULL, 0xFE3FE4B1D4ADE3EEULL, 0xF2076430483E6827ULL, 
            0x5EF4ED34BEFE4674ULL, 0x2F94C5B8ACD5FD0AULL, 0xD650DF27911CD46BULL, 0xA492F2763AC01450ULL
        },
        {
            0x4979FCCABBA022BCULL, 0x38F4DF30F0985FBFULL, 0xDFCA25CC78F62702ULL, 0x3D147B561EF00F8FULL, 
            0x1EF89B2A3E098107ULL, 0x718046796EB0E92DULL, 0xD42763C2F0D6932DULL, 0x89D7200BE93319E8ULL, 
            0xA4C22DF008A21F18ULL, 0x5F08EAEE8A76513DULL, 0x2F2D634D81108637ULL, 0x34B68B99DACD71F6ULL, 
            0x469427E889D030CCULL, 0x4A9461D9754DE1A5ULL, 0x9EB453DFEC9DCFAFULL, 0x9D89F5866FEDEB0BULL, 
            0x3EF061E489079FBDULL, 0x8D24AC6ABBB72E70ULL, 0xB3383F5B0E33FDAAULL, 0x1543B7CBBDE6911EULL, 
            0x4A724F9C0C869069ULL, 0xAEA41E1948B327E8ULL, 0xD8F8FBAD103082B0ULL, 0x48D696466BAD053AULL, 
            0x9B93A03FA3DF32C5ULL, 0xC7914D21202406E7ULL, 0x91A995777BB7A2F1ULL, 0xB26CE8E154564E1CULL, 
            0xBC233BE0A66BA3C4ULL, 0x32DE2B11B9EC67E9ULL, 0x631201694D683146ULL, 0x347D752B8A7CD3ABULL
        },
        {
            0xCC4F5CDBF7E8F2C3ULL, 0xBDE9D7DFCD659E05ULL, 0x755BC6BF4CC3A4D5ULL, 0xBD6D43ADB02EEA16ULL, 
            0xFB1FDE6D0A2ED776ULL, 0x032371A2F21CB511ULL, 0x8B12C9862098E2C0ULL, 0x539C574C63716BD3ULL, 
            0xD4046EE36C5F8624ULL, 0xF36516488448DC27ULL, 0xB8228D5C2AE8D69DULL, 0x5B9730F484A06CC2ULL, 
            0xA917DFCDB55656F1ULL, 0x3F45ED89D7CC7251ULL, 0x5987920B9C4F4AF8ULL, 0x2A87D35EF8CFB9E5ULL, 
            0x63FD68DA21CFAC4EULL, 0x6134A99FD53EC6BAULL, 0x8F842F7C2DB2D90FULL, 0xC93212EDB4437904ULL, 
            0xB4B4219F28F0CA6DULL, 0x976B1CA9DE9C4E14ULL, 0xAD39704FB11B8A00ULL, 0x1746FBA856A57A93ULL, 
            0x496D2E59AB7DA811ULL, 0x2050B39FBCE033C8ULL, 0x886B00430823B30EULL, 0x98EB5683F176A394ULL, 
            0xE366982A7E2DCFF2ULL, 0x70CB01DA06565BD9ULL, 0x4C607F4DD0D0B785ULL, 0x9E1A4BF1718DD5B6ULL
        },
        {
            0xAD6112BC13852388ULL, 0xEAE4FE467D3F744CULL, 0x6C429488F3890A6DULL, 0xF0CB43DBF6FEBFF4ULL, 
            0x80900BE7050B7313ULL, 0xEC99FBDCC6791768ULL, 0x9F4007A079C5253AULL, 0x9A1C596867BB3B58ULL, 
            0x326B3CB532FEEF46ULL, 0xA3A7773B9E56A98BULL, 0xFA787F44C81DB02AULL, 0x1230CAD1C2C39591ULL, 
            0x8926495E347EFFC1ULL, 0xF812E729F2F3A178ULL, 0xC07BC8FC785DAFEDULL, 0x093D591B47CAEDB5ULL, 
            0x0B6E968C93D02F1CULL, 0x789A5E809968A686ULL, 0xDF6AE184A934C74BULL, 0x6713C00A09586C56ULL, 
            0x858A3EF7FDEEF7EEULL, 0x8FE13639CAEACC0AULL, 0x6A9B2DB215E2FB94ULL, 0xC797BB078D45D7E1ULL, 
            0xDCB53485A257BB8CULL, 0xF1E058E225FE7A4EULL, 0xB2A3ADE32FC195E0ULL, 0xA4DA5941CB8D1D86ULL, 
            0xC039342F2701B487ULL, 0x3A87229EC340519FULL, 0x62670784F4DF7A2CULL, 0x0459ECF4B6C0EA64ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kKeySpawnBConstants = {
    0x46294A38D8582505ULL,
    0xD4DC5E54A7C5372CULL,
    0xF0099BE7CD3586A0ULL,
    0x46294A38D8582505ULL,
    0xD4DC5E54A7C5372CULL,
    0xF0099BE7CD3586A0ULL,
    0xB0602216FBE78358ULL,
    0x6B935FF756CF7F8BULL,
    0x4E,
    0xEF,
    0xAC,
    0x0C,
    0x3F,
    0x38,
    0x62,
    0xAD
};

const TwistDomainSaltSet TwistExpander_Achernar::kSeedSalts = {
    {
        {
            0xAB5B2284C282A7B3ULL, 0xA9C3101C0EDE5AC4ULL, 0xB6614B113A9801ECULL, 0x782FB126D0E21589ULL, 
            0xB597567E2D032790ULL, 0xF815DB70C3761271ULL, 0x6D14A84B56C51532ULL, 0x18C15EB0E23CBDA1ULL, 
            0x59AA5E91BA74D5A8ULL, 0x1CFCF23AD6CA5CB3ULL, 0xA8357C42824A88A9ULL, 0x0F86FB47E325B7DFULL, 
            0x2D0695C61D2A605CULL, 0xD06D9FA91B2AD911ULL, 0x7D593E5F36480957ULL, 0x713B7BD6378D6D82ULL, 
            0xEB7193184F1BC067ULL, 0x09B4833BE5485CBBULL, 0xCAC03877BE423130ULL, 0x1A2F719AEA998EF8ULL, 
            0x0AE517313DEF4C8FULL, 0x4FFFBADF39C1B7BEULL, 0xA1F63F655B3EA636ULL, 0xFD16839D293FBAF0ULL, 
            0x9BB9ED16E6FE1754ULL, 0x233073BB41D8CF2DULL, 0x326B53D4AEAA028EULL, 0x1DA7170F9AABDCC8ULL, 
            0xDFDCB1C00F61F18CULL, 0x4665D40E9B9DD997ULL, 0x82872483EE404818ULL, 0x481F688E21C55175ULL
        },
        {
            0x93753299508CB245ULL, 0x0D66FAEE53251190ULL, 0x60789A16908E479EULL, 0x148523D422C0688FULL, 
            0xF7708FEC8BD02487ULL, 0x0ECEC0098C01408EULL, 0x4838A64CCB5C23CEULL, 0x6A341395190062F7ULL, 
            0xC35D697FB290A33CULL, 0x4E99B0B342824B73ULL, 0x8ACBAC8F07EEAF9BULL, 0xCC7D3F5C5801A4BFULL, 
            0x04BA2CB99E951707ULL, 0xB7F28F1C4E153D48ULL, 0xDAA05E118B5D871CULL, 0x22A2FCB316A09AAFULL, 
            0xFB20C9701A1C0B21ULL, 0x3B3DD6CA526AE302ULL, 0xF0A1D087EACCB62EULL, 0x94ED74A1B5B78346ULL, 
            0xFAC7356A34B99BCCULL, 0x9DEF4276D6C9B368ULL, 0x3885DFFFC7C57CD6ULL, 0x17273A814BB475F8ULL, 
            0x3ED0B588D712230BULL, 0xAB5DA0F30A8AD3F8ULL, 0x407BA4A6BF2E5336ULL, 0x9E7B8A278379802BULL, 
            0x637FCEF4293FD407ULL, 0xCBAA45E1547000D5ULL, 0x57503010B198A804ULL, 0x66C7D2DFA93ADBC1ULL
        },
        {
            0x946A1F4107454B20ULL, 0x683BD3F293B96FC5ULL, 0x773971DE4B594B48ULL, 0x75E26A0F6E4EAD25ULL, 
            0x8C636029E578A02AULL, 0x2000C190706693BCULL, 0x6E59DDFF9DD6DFECULL, 0x5F07FD406342331BULL, 
            0x27CEC7953A639678ULL, 0x75C8361F39770ABFULL, 0xFE6A6E4549480EAFULL, 0xAD38FF4CF29D5A04ULL, 
            0xB41CA8D37BBE8328ULL, 0x78181CB086129CC8ULL, 0xA6EB715FCB5A33ADULL, 0x1975934FFED8B2FDULL, 
            0x21BA5BE832B11366ULL, 0xA4F904219777085CULL, 0x3F232F1B6AF2D4E2ULL, 0xD64777080ECAF8F9ULL, 
            0xA5AFD29275788A2DULL, 0x675393079E803EF6ULL, 0x6E2C2950D0B0B1A3ULL, 0x1AEE6CE60D35DCC2ULL, 
            0xB7383B33FFD166FBULL, 0x1472D4A936327347ULL, 0x3142038783C5907EULL, 0x1D673AE5CB02AF80ULL, 
            0x51BF982D3EC1E938ULL, 0x629C48EBDE2258C9ULL, 0x08DBE1674A717CADULL, 0xE5A2021FF23C9CC9ULL
        },
        {
            0xC0DBA667170CAB14ULL, 0x4367D4C6F5FA7029ULL, 0x2BE25D2294739623ULL, 0x41F890B8BA7A28ADULL, 
            0x704DEB7924A705A8ULL, 0xD81A0E0DC91D0D56ULL, 0xA92F525A26615F94ULL, 0x32A914354A2B3FA6ULL, 
            0xEEAA8AD8812A453DULL, 0x91FCA784A4131109ULL, 0xECED780091180BCCULL, 0xDE22903FB94C4B84ULL, 
            0x4B6748DA6790C583ULL, 0xF3EE667A02D9AA76ULL, 0x1E0DB9962E9B2655ULL, 0xE5FA2064E0B7F5A7ULL, 
            0x4F5AED3CE290CDEFULL, 0x49183302D47528DBULL, 0xFAB3B735DB7FB4E3ULL, 0x6EE52F463FE3AEF1ULL, 
            0x54002F5C3D85D8D1ULL, 0xF7699331C1245342ULL, 0x889A8FE21E3D126FULL, 0xE4D81280DE5D83AEULL, 
            0xBE51FC62E7707E33ULL, 0x25B33E7CA5F1AFB4ULL, 0xAA988D571EC63445ULL, 0x363939D90A0E577AULL, 
            0xDFAB08E4AD538E25ULL, 0x677B70DEF81F8744ULL, 0x787BC0658AFF2F65ULL, 0xAEE02A79E6B0A23DULL
        },
        {
            0xD13BA97CC69C145AULL, 0x43EA92665A0E964BULL, 0x6BA4DC05243707B7ULL, 0x4F01A3D2E3C4CC92ULL, 
            0x26BA663D6C67BB04ULL, 0x24DAC94B42DF404BULL, 0x85BB888D7F12D6E3ULL, 0x55BD5FA6D1970020ULL, 
            0x8673C037E49850B6ULL, 0xF02148C00063AAE6ULL, 0xE21A21DA9FE25F50ULL, 0x5F42FAF7C64C0D00ULL, 
            0x4EA358B447DF4D47ULL, 0xE9E8310131E2989EULL, 0xD34573EF9C593724ULL, 0x064C3EE2A68DCF90ULL, 
            0x6269D08CA41D66CFULL, 0x3BA0C13783AE85B5ULL, 0x9AD785C01FD349B2ULL, 0xFDAC37A5A370F26BULL, 
            0x97602F4059C7A409ULL, 0x05BCD00CB5DC8D09ULL, 0x7ADB04172F7D1CCCULL, 0x5577FADA5E502CCBULL, 
            0x5FB2B10328503D1BULL, 0x2C6B01DC1808E049ULL, 0xD47CF6297A418D9FULL, 0xFC744CCEC1BE8745ULL, 
            0x88B046AEA3E756A4ULL, 0x1816AA42742F7FE6ULL, 0xDEE91E31EA3A83EFULL, 0x03BDD35FCD7B0740ULL
        },
        {
            0x0003A632E34B0D83ULL, 0xFF25E5DF9C3E3683ULL, 0xD3D8FDDB2C80A136ULL, 0xA0F689723DB821F5ULL, 
            0x9B58E2454B826207ULL, 0xBD4566AAD74E3B73ULL, 0xFA55193DE9B17DF4ULL, 0xFB1879512F127EB8ULL, 
            0xA62E77BF5B26124EULL, 0x0580252E964CDF03ULL, 0x499BD8F6D36EA673ULL, 0x65B054D9616232A5ULL, 
            0xEF5026441A63EAC5ULL, 0x5740417A0CC2AF5EULL, 0x2DBB1F53639FAF3EULL, 0x4BA377E281EA49A9ULL, 
            0x58F979288A7F6E56ULL, 0xB3E0926EF92D19CEULL, 0x72E9969ED2B1E8EFULL, 0x29D4298F220CC929ULL, 
            0x4EB1686BCE535CE9ULL, 0xA802BDD0B9F3B2B3ULL, 0xEE7BD797F9840AEDULL, 0xEF0BAEF7166A1C11ULL, 
            0x2C504E1430F1C7EDULL, 0xD550B1510C02F803ULL, 0x5C329E74EA18415EULL, 0x790523C23B0BB3C6ULL, 
            0xC32393AF66E5E98CULL, 0xD53D534C8F1B8B56ULL, 0x7176BED65707D893ULL, 0x602C291B689BB2CFULL
        }
    },
    {
        {
            0xB6B5418595A26A1BULL, 0xE625E57A8A079BD5ULL, 0xB920F348CDCE7323ULL, 0x835441A6CEEAAD09ULL, 
            0xAEAB26D6F467B58DULL, 0xFEE87FCED20D34B5ULL, 0x01AA924295FC59D5ULL, 0x94448D7EFB227D4DULL, 
            0xC1FD7FA5633C1646ULL, 0x8B1993E8CCF898EEULL, 0x6C937FD77AC90A5CULL, 0x036C06D93C1BE919ULL, 
            0x7AD36EE2738A3859ULL, 0x908C623BE5B3D5DBULL, 0xFDE792A5995C1E36ULL, 0xD6A3F8E0D4A0C006ULL, 
            0xCFBFB4FACBAE143FULL, 0xF8CA566E0631BA12ULL, 0x3B5BFF9CB87F88A4ULL, 0x97E74534D4216A86ULL, 
            0x20F1732FE26F8796ULL, 0xCA7A6AC2BF3295E8ULL, 0x9A9507B9F58F2575ULL, 0x53607DFD5ABD2236ULL, 
            0x1FC179896C93F6D2ULL, 0xCAFE56F0562BFBA6ULL, 0x2FA2FB7CF4243AD9ULL, 0x8D13EC9739609073ULL, 
            0x8BFF1323F3CA0A82ULL, 0xCCDDF7D728D3E782ULL, 0x9C2CF6AA4EC33395ULL, 0x8411859EF3D2C5DAULL
        },
        {
            0xF7DA2B995394847FULL, 0x5F4573FBEC8E046FULL, 0x2EC2C3FE7F8E5B41ULL, 0x80F7198AC6DFCACBULL, 
            0xAA746109974E5EA6ULL, 0xA88CC84AE08C50AAULL, 0x63D4D09AD1E5F6DAULL, 0xE2B8446E16968A86ULL, 
            0xE5E9DCEC45701272ULL, 0xC1AF8630F63F8FCFULL, 0xEA3CEE4C90537EEEULL, 0x73BDAF88FDBD8CE7ULL, 
            0x2B3C92C224983825ULL, 0xDE7D16D54A9B7E42ULL, 0x8785F3748374B8C1ULL, 0xC7EB754124B68227ULL, 
            0xC63572A69694625EULL, 0x5E8C0B5F8F6D0E16ULL, 0x52AE0B2CC3B75D4EULL, 0x48DC4100891EB6B0ULL, 
            0x674DBA6B132D1AF2ULL, 0x9D96E60A99C3F7AFULL, 0x57D92F258C567C2FULL, 0x85B675C173B405A8ULL, 
            0xD18088BBFF116633ULL, 0x121C22A5A87146AFULL, 0xAB5ED8B75C5DA5D2ULL, 0x482428130A77AFA6ULL, 
            0x89874ED5A89ED919ULL, 0x5B62780B76F26707ULL, 0xA66111A05A32A8FBULL, 0xFB608F3B01E729B0ULL
        },
        {
            0x93B041E7DF6E3EF6ULL, 0xCC80A905DB8ECFEFULL, 0x35658BCBD7D1C0BBULL, 0xD231BBF0F642C7F9ULL, 
            0xA69685C03CA01B98ULL, 0x445582C65879C924ULL, 0x762D0A240E8A3220ULL, 0x5BB63DDAC80A0218ULL, 
            0x1257BA09ACC9CB08ULL, 0xBD05732474E1ADAAULL, 0x5AB649EB5C7FEB78ULL, 0x7D2F9A0DA031EFFEULL, 
            0xD351C74F36AF69F4ULL, 0x66F8125643A38562ULL, 0xF86A4A9186D99254ULL, 0xD2397FBADFF7D9D1ULL, 
            0x61816739F589D6A9ULL, 0x9FC0FFFFE352FCCBULL, 0x0CA4E772235E9A12ULL, 0x85B8D7F9F1B6739FULL, 
            0xB8DA4DAE6C35EF88ULL, 0xC83E55D2E447B0B3ULL, 0x4F265F992BC47009ULL, 0x5453FF9B76F64FBCULL, 
            0x1525F08A70BDD66EULL, 0xF9C0083C94C93C5BULL, 0xCA07D648F63E0795ULL, 0x10B8E8EC89C6F9C1ULL, 
            0x6888A16474D7B48DULL, 0x9652D0542EE24F90ULL, 0x381EFA61B3C18C63ULL, 0xB2C604C61BAE98EAULL
        },
        {
            0xFA7100A92F98F71EULL, 0x78B957B35835563CULL, 0xDE977A23485CC2C5ULL, 0xA8C08EFA4C365760ULL, 
            0x1C2D9C15A89AEEADULL, 0x9921655F23AE15B2ULL, 0x066E5DA1AF6C2B63ULL, 0x365F815F448A3D29ULL, 
            0x1B38479453A3903CULL, 0x658213A0D74D83E9ULL, 0xEF8E549854ED7C46ULL, 0x05DCD2BEAE3F0BD8ULL, 
            0x3DDBCC92B7B364E0ULL, 0xFADCE16035763C32ULL, 0xF5603BD478A60C79ULL, 0x5956AFA2955FA877ULL, 
            0xF2731CFE3A7990A4ULL, 0x88BD97D0A9F2877DULL, 0x24C9DF972CE1292AULL, 0x33ABB6FCACBBA96CULL, 
            0x64B6AA21EFBC91CBULL, 0x36CB02B26A3CDA76ULL, 0xCF9FBCE46F36FF72ULL, 0x51418BDF615B4A8FULL, 
            0xE23F2695D9D8B30CULL, 0xADFBB7C4B379F866ULL, 0xB77AC4406B06BB8EULL, 0x7F49C8BB158D36F5ULL, 
            0x61DF1A6D0F2F6099ULL, 0x747746750D9AD8E8ULL, 0x4792E4964670D949ULL, 0x52E7F3991966D9B4ULL
        },
        {
            0xFA9CBCDA499BFA32ULL, 0x251B282FAA9A5A38ULL, 0x495E5A1B98D820E3ULL, 0xFB8BABD9009EDEA4ULL, 
            0x6888F3A247FC8B84ULL, 0x75C7C4C61E70AD79ULL, 0xF294DB3A6FFE00BCULL, 0xAEBD762F1B844CAEULL, 
            0x62669A46E0184A55ULL, 0x27D63DD78AD2F0F4ULL, 0x8D867F6372B5C292ULL, 0x6E7D20F98086E536ULL, 
            0x9B0072BCE185F6A7ULL, 0xA55464C4FD402C02ULL, 0x82D6556E700E6474ULL, 0x4134D4174D81B00FULL, 
            0xB9974908B9E607B8ULL, 0xDBBD9A05BF2ABF93ULL, 0xCAD1D142BE0D23A7ULL, 0x6850303C03DC30B8ULL, 
            0x09AF37D19A1F0406ULL, 0xF3AC7907A96513F4ULL, 0xD6BF0CE78F0314D5ULL, 0x08BAAB69E8641BC8ULL, 
            0x2EF6A268DE07DBC9ULL, 0xF91F7BA5D63512D7ULL, 0x8ACC7D6F24658399ULL, 0xE312600899789F2AULL, 
            0x4C919BD1BCAD7256ULL, 0xC551F3EC0F54B721ULL, 0x4BAF9EC4E5A59A5CULL, 0xF9A939301DDE9B11ULL
        },
        {
            0x0D396D41F1B55592ULL, 0x9C568F4AC3F9A4F0ULL, 0x17DACB8A605E54AEULL, 0x469FFB5ED30C84B7ULL, 
            0xE248F631FCC255B1ULL, 0x99466A32ACC6572DULL, 0xAF249840913E4857ULL, 0x8D19E42C18E76068ULL, 
            0xB89B5980FE76E217ULL, 0xF595E36BC4F43B79ULL, 0xE51A4BF68DE973F1ULL, 0xE20B7D24B4A2C15DULL, 
            0x6D4DF6BAC845F217ULL, 0x3BC87ED83DE53368ULL, 0x2C89CF5E0C8B90A1ULL, 0x489D2B42C0232AB4ULL, 
            0x67A1618D9D9A2354ULL, 0x9A555E278D08AB9FULL, 0x04C407FBCC48E112ULL, 0x7BEF51C437DAE9EEULL, 
            0x9CF332ABADEE086FULL, 0x93799934E8C066C8ULL, 0x2216FDED6982D615ULL, 0xAD2C4921E573E3CEULL, 
            0x5AD5BF2CC78C136DULL, 0x4E434594775ECCD3ULL, 0x5DE5CF0AFC3D77CBULL, 0xAB137118DA179CBFULL, 
            0x3607DF800FC4F8FBULL, 0x0DF90570615574F3ULL, 0x51823379757F0395ULL, 0x9395DF294CAFF694ULL
        }
    },
    {
        {
            0x76F16B39D44C0D8FULL, 0xD75B2A6F8B3FA935ULL, 0xA01DAE6B22DE9142ULL, 0x68CDBBBD337FF808ULL, 
            0x6091A628B53D9276ULL, 0xAFFAD9880EA64322ULL, 0xAAE7D16D03D9E0C0ULL, 0x5B7D8F444004EDBEULL, 
            0x5E1EA89FADE31B9CULL, 0x42C36EBADA82EE64ULL, 0x3904976DBC314058ULL, 0x0A3F0E0C226E544DULL, 
            0xE071989E54A6F817ULL, 0x0828D607E3B9091CULL, 0x0CC7FF3BA719FFDAULL, 0x3BF177928D82550AULL, 
            0xD6D0B3391AE2C0F2ULL, 0x7A23720BD423E162ULL, 0x33E2763306444D13ULL, 0xB862E47E14DC1325ULL, 
            0xDED2888B80E288E4ULL, 0xCE4B91506519EFDDULL, 0x576F385AB665C6EBULL, 0xCBCE25A6EF9E60A4ULL, 
            0x33B27B65869C0C09ULL, 0xBB2345D01A69A990ULL, 0x598A3FDF0A64884FULL, 0x3C9A8C378657B5F1ULL, 
            0x834836F6A7AA7B1EULL, 0x29498F3BABA5B59FULL, 0xBC1439603E009455ULL, 0x125B0081A77BC793ULL
        },
        {
            0x8825920A2DCA30FFULL, 0x60ED7CBFE50763EFULL, 0x0C829AA3488ECAE1ULL, 0x3B287EB3E496594DULL, 
            0x4BEB56EA68363B82ULL, 0xC64145BA27F87C7EULL, 0xEE6E43B6CD9699D2ULL, 0x182406811DE8306FULL, 
            0xF8BD68D3ACBB6A73ULL, 0xEDD7AEA349EB8C58ULL, 0x8F6093E3EFE1E4F6ULL, 0x7ED3C502F0ECEC7DULL, 
            0x72134FC44368E47EULL, 0x7B9F3B0D3B98D1BAULL, 0x8E1B9A29707790A2ULL, 0xC8940D029983A6B9ULL, 
            0x6026FC422B4D7941ULL, 0x2FC9B30E7ECC9333ULL, 0x5B4E861E702C04F5ULL, 0x7EF91E22AF705FC7ULL, 
            0x89E877FBD8615C58ULL, 0x48F77E48E3E3ACE0ULL, 0x3228BBA89BA7F39BULL, 0x05D1FCD2E394BF13ULL, 
            0xF7504B79A80D3C1BULL, 0x6E4A71365196CB07ULL, 0x74B88996132CC274ULL, 0x629D5DB690A18F2BULL, 
            0xF9214242EC7C4350ULL, 0xCD2D3A980364FD14ULL, 0xDEA132AF389206C2ULL, 0x66FDA5FB033B268DULL
        },
        {
            0x45FB1E2CAC9A3228ULL, 0x1FC31C4FA81937AFULL, 0x2D2CCAECCAF0C4CDULL, 0x961C0DE83BB9394CULL, 
            0x0702B1EEF4A8BDF1ULL, 0x47E73D3F297A75E5ULL, 0x549638256B72D95AULL, 0x63EB5D1C2C303BE3ULL, 
            0xF223176A30657E38ULL, 0x6FC91F4767FE189CULL, 0x09188E1AF63B4801ULL, 0x97872987CD987E2CULL, 
            0x347FC8882E91CDFAULL, 0x2C8D9D292E701EF0ULL, 0xF78F69D1EB2F1E70ULL, 0x5DC50216D7A090C6ULL, 
            0x0957B94F447E9FE5ULL, 0xF3C29257045C5A46ULL, 0x945678FDD23C1DF0ULL, 0xF01E2E7736627C0EULL, 
            0x625006778661D8BCULL, 0x44CFA69EE73B13BBULL, 0x6B77C8A5FA671600ULL, 0xA8D3F28D9BDE6C78ULL, 
            0xE99B0AC3778C1A5EULL, 0x777DA1D311369048ULL, 0x393C433C6211A6ABULL, 0xE3F1BC282F613423ULL, 
            0xC69A9EEB17773963ULL, 0x19C0A04D5ED1D139ULL, 0xC51333710CDFC186ULL, 0xF4A498738423AF43ULL
        },
        {
            0xEA83A53D5D25B09CULL, 0x39CAAC40AC55B9B7ULL, 0x17041CDF8F6AC0D9ULL, 0xD4145C8D04F6AD45ULL, 
            0xD34EFFBF00EC4622ULL, 0x441BC28AC1C95EFDULL, 0xA4EE3148F20CAFF1ULL, 0xA23BB67028A5DDB0ULL, 
            0x50B50544AE275BF1ULL, 0xD110B5C7BEAC54A1ULL, 0x20F472092AFBB17AULL, 0xF4D94134D9C30E14ULL, 
            0xE1D7A697245D5C0DULL, 0xDA393FB601B5A5DAULL, 0x545E3FBDBD78462DULL, 0xF4C3273FF8B8C1F9ULL, 
            0xCF6F8EE41979FF02ULL, 0x92EEDDD83FFE7343ULL, 0xA75B20C8975A6DA3ULL, 0x72A7C49C1ED4A859ULL, 
            0xC1EB4CEE51189CD4ULL, 0xB1E22B04999195EDULL, 0xD92C891881768A3EULL, 0xAD78928829B5FF11ULL, 
            0x7636C3190C52D512ULL, 0xABE7D15882381A55ULL, 0x3C8DFECED0C5F55EULL, 0xE04741D4321D6CA8ULL, 
            0x7899D8554ED25B0DULL, 0x458D0C0FC0D72010ULL, 0x8C390F28728BF7FCULL, 0x6357D200A4CED3BFULL
        },
        {
            0xCC59559C3045BAEBULL, 0x592F16DC7C737F59ULL, 0x5E5FA992A4C0DC13ULL, 0xDA556CC263AA74C7ULL, 
            0xD415A4498934DE1CULL, 0xEFDC7DF81140DD79ULL, 0xC5AC7D82CE964B03ULL, 0x6F568358208CCCA5ULL, 
            0x90BC29AB2A48D6B3ULL, 0xC7D055FAEA773FE4ULL, 0xFD1EFDFD96478A79ULL, 0xFE73C092E7CA8065ULL, 
            0xC4DABE4A4E610178ULL, 0x0B19760190F0DF56ULL, 0x1F1FD82A0CF6B7EDULL, 0x7BF5EBD1FFECB308ULL, 
            0x5B7F212B89D824A9ULL, 0xB8A6289F3DCE5179ULL, 0x9226AC20AC5ACE8BULL, 0x0364EDD36B52883FULL, 
            0x4C2DAFB9C926A8A0ULL, 0x96164DF3954E7B0DULL, 0x035806E93DAC054BULL, 0x273B6815F3A1FAB1ULL, 
            0x7E090040E7B1C1B7ULL, 0xDD6BC9D3D21FFA39ULL, 0xB3E1B7D412BB6B79ULL, 0xAB421D20E3C09B64ULL, 
            0x647F169435BA85EEULL, 0x6A4E1B88E83A1B21ULL, 0x02171A6FC3715958ULL, 0x371B574997E3E62FULL
        },
        {
            0xFEFA3D483C001B46ULL, 0x548CA15EBCE2E2E9ULL, 0x3179EE6E54F16415ULL, 0xF4874B51BA953FF2ULL, 
            0xC3CD9393C2EBDFC0ULL, 0x2E9226ED3A5CDA87ULL, 0xD828A6E06588D31DULL, 0x013C8CB6410E6175ULL, 
            0x6626DFD1365431DBULL, 0x175EC7C642609F46ULL, 0xC93CA9F50C898A2AULL, 0x326ADE992E56AF90ULL, 
            0x656CEE8F2484EB14ULL, 0x6A76C376CED631A1ULL, 0x5D356BDE65FB2357ULL, 0x4A8DEFB2E9239FC8ULL, 
            0xCE50DF0B0B78AE2FULL, 0x4B54CFF04F6D628AULL, 0xC8C1A0ABABF8FA74ULL, 0x19538B42B28154B1ULL, 
            0x1DD61AEB06A62A64ULL, 0x6A3BFC792918C451ULL, 0x646F068AA5F41D6AULL, 0x6498C0B04E8EB8AEULL, 
            0xCFA24566161D6A87ULL, 0x226BE250F5AB330EULL, 0xFC47BD5F7D147EE7ULL, 0xEF368C6C842A765FULL, 
            0x0AEB4D4D7078CA08ULL, 0xA2E46E77C1BCCD26ULL, 0x7795123C1390A3E3ULL, 0x9645437089902E36ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kSeedConstants = {
    0x13F6BB3341B672D5ULL,
    0xB239C3EEF30F5846ULL,
    0xCA03BE91DFF4A743ULL,
    0x13F6BB3341B672D5ULL,
    0xB239C3EEF30F5846ULL,
    0xCA03BE91DFF4A743ULL,
    0xEA1C4559DFCE430AULL,
    0x51C9452A7A2B2AEAULL,
    0xA1,
    0x37,
    0xFB,
    0x50,
    0x42,
    0xC9,
    0xBA,
    0x2D
};

const TwistDomainSaltSet TwistExpander_Achernar::kTwistSalts = {
    {
        {
            0xF828943D5231EC57ULL, 0xBB264AE2F67B906BULL, 0x00BBE84C68B2E6E8ULL, 0x7EF47021C17A42F8ULL, 
            0x18BF3E6F99FE111BULL, 0x2B48CBF2F21C33A3ULL, 0xF074FAC100B99145ULL, 0x625D39833525722AULL, 
            0x653572EA8D8D1E13ULL, 0x8767C840E37F99ECULL, 0xACDC2E34E24FFDE2ULL, 0xBC0E675227E16E8BULL, 
            0xF9E4715F991239DCULL, 0x32FE501057730F14ULL, 0x1DE36ACA28EFA19AULL, 0x1EA21A03BA8E2767ULL, 
            0x490282455BBC0367ULL, 0x2C0773F88B2F5AA0ULL, 0x10794B3580A2179FULL, 0x8FA3671E3118223AULL, 
            0x75441D4853E3C9BCULL, 0xEA84DD0620A2CA15ULL, 0x5B0ACF04C31C5153ULL, 0xDFF853CB41B0A638ULL, 
            0xBF16C841E3F6CEA1ULL, 0x3FB2E11BE0DFE392ULL, 0x2448E16D17A3B53AULL, 0x5315F346E933BBB5ULL, 
            0xA7CF78B42799BE52ULL, 0x8E2B53AEA4AA0E42ULL, 0x7EDD608D9DBE7A0EULL, 0x507F4A6D9A1ED2A1ULL
        },
        {
            0xE67AD7BAA4251339ULL, 0x1F9B44C3C55CCCA5ULL, 0x55F3D5E590E3E0C1ULL, 0x37F5600267462C00ULL, 
            0x93D0BC6800A1CA68ULL, 0x29775D3A96020173ULL, 0x97FE6B8A7849D174ULL, 0x9F646AA5A24CADA2ULL, 
            0xE3ED98F2B4445700ULL, 0x1E7B3CDFAE13F336ULL, 0xB316E556961A2174ULL, 0x218D163DE446919CULL, 
            0x24ABC2BA78BE9C23ULL, 0xCF78C3189AFED79DULL, 0x46692DEFE5837190ULL, 0x3ACD82E8D526165FULL, 
            0x74BD2D6344E641CDULL, 0xC7143F6480DF362AULL, 0x2B75678950C26B46ULL, 0x83744B2E209E70B2ULL, 
            0x1C73EFE080773459ULL, 0xCC2AB84E50D64BFBULL, 0x8626936B337F68ABULL, 0x061FB453E66C0603ULL, 
            0x6C7A8B3296FE62CAULL, 0x54BA0D60197CA7D4ULL, 0xC2397B7E850EB1C9ULL, 0xC993057322339FE9ULL, 
            0x17BDD7508E921EF9ULL, 0xCAF6565A2A07F49DULL, 0xBA995A5CBE47F3A1ULL, 0xFEFC5CFD2103D958ULL
        },
        {
            0x057263F5A76229F3ULL, 0xC60EA18C761F5B7CULL, 0xAEE02B60653B9D9AULL, 0xF249842E0A23D5D4ULL, 
            0x7E4EA9BC92646425ULL, 0xED135835A6A9A98AULL, 0x8C7FA18F6BCD7E0DULL, 0x3D462D823853D93CULL, 
            0x4C35F95A05EA8B38ULL, 0x5C5C2C1E44341CD9ULL, 0xAA6B3ED49A1E4CC0ULL, 0x949D3D4260AB4FE5ULL, 
            0x5F6BA3C546D1B286ULL, 0x3108CE1BA465D1EEULL, 0x26CC3A75632C22E2ULL, 0xB0A4008A2BDAB756ULL, 
            0x4961D01CE0D8DB96ULL, 0x8237386AEB510242ULL, 0x254E53679D6B97A0ULL, 0xDB329A496A597011ULL, 
            0x68934E936F8CBFE6ULL, 0x434C5D90E9E03F11ULL, 0xEE6B918D6B207FB8ULL, 0x20DAE86498D653B5ULL, 
            0xC361AE9626ECFC28ULL, 0x1771F5FC6D69111AULL, 0x78F2D669A9F51201ULL, 0x33E10327BB79B65CULL, 
            0xA23AF796AA0A46F3ULL, 0xEE1EE5ABF091AFA1ULL, 0x42D34FC183EA548AULL, 0x34E44438A6CCB11AULL
        },
        {
            0x636CD805EB289F2CULL, 0xD0A9C0F22761544BULL, 0x55F1DF33C718EBD8ULL, 0xFBF7AACA5B0ADF29ULL, 
            0x235B1B040027AA0CULL, 0x060BE88F86412596ULL, 0xC2E0FB0EADA1C5F2ULL, 0x30CDE2EC280350D2ULL, 
            0x3E53A67818203CA3ULL, 0xC6184F438113F1EBULL, 0xB779106048CC9320ULL, 0x8ABDDC0ACC01170FULL, 
            0x9D689BB6244250E1ULL, 0x791D64A4F2B88D9CULL, 0x5E6D74892F1B3D28ULL, 0xB9B223687875D373ULL, 
            0x94AED2056BC65F66ULL, 0xC5B41BD19A9AB1CEULL, 0x07F283982B53EFB7ULL, 0xEEF027340FAAFAE8ULL, 
            0xCD46CC2D495C077FULL, 0xB93239FD3CD0A3EFULL, 0x88C281DA7A511E2EULL, 0x57937C124FE27FF3ULL, 
            0x739D88966E24FD80ULL, 0x75322B6DB84558CDULL, 0x5240150AE74D7F78ULL, 0xCA116F9F5D4F1B54ULL, 
            0x6F4739F6EABBE7F1ULL, 0x755311034EEB7BF0ULL, 0x428CD68F4915233CULL, 0x40B9BEBF7D953E67ULL
        },
        {
            0xD95912D0672A2552ULL, 0x15FD3B4A3338B29FULL, 0x5D317A44DF0393B0ULL, 0x0CC0486D472CF95BULL, 
            0x533DE1E156C449AAULL, 0xA227A989E61AA266ULL, 0xAE1AFE2090017C52ULL, 0x5249C520D878C357ULL, 
            0xFDC5E74876B1393BULL, 0x6D5EA88643F09396ULL, 0xAE6717A192A083EEULL, 0xCED0C80FB9F0D88EULL, 
            0x802B0CB64BB6D7F8ULL, 0x6555E8DC5DE72CEEULL, 0x7C1A88A48A2A73AEULL, 0x125BAFAF53CB71C1ULL, 
            0x9A1F02FD4F30A578ULL, 0xEA30B3E1752FB973ULL, 0x70CCF5FA4B5021BEULL, 0x2680E1032E8C09F9ULL, 
            0xF9915D067537C4F5ULL, 0x258BD6069CB85DF4ULL, 0x12271146259B3561ULL, 0x30C5B65540B5A83AULL, 
            0x9B874BD4EF2D5C2CULL, 0xD9764FE360B1C0D2ULL, 0xD9F855A87A393DB4ULL, 0x604589F48517C1E3ULL, 
            0x839630C572EB39D4ULL, 0x822A162CB4599567ULL, 0x58E9B3608E6AEB2AULL, 0xE394C7EEE90E8A09ULL
        },
        {
            0x89FA1288160593BBULL, 0x4ADA92B2A0319E5FULL, 0xC4582FDB185E6F5BULL, 0x961B7AC1E8E22ACEULL, 
            0x6C2D3DC860EDDBF6ULL, 0x7F5CF99DD8DFBCE0ULL, 0xEC7AFCEB68FB5DC4ULL, 0xE6ECDC40757F5A61ULL, 
            0x2BE844D351EA1128ULL, 0x3C33F226BC108CE7ULL, 0x75D4C9CF6B2D0DB0ULL, 0xF37FB3E38560C596ULL, 
            0xAE287AD344E9987FULL, 0x491E9B0837BA3E98ULL, 0xB74CC1088F7CB5D5ULL, 0x45AE7B5D9653756BULL, 
            0xCFC811375B036D01ULL, 0x69899E9EBE5C4A67ULL, 0x90775D5E79BE1143ULL, 0xC9DBD61634593478ULL, 
            0x0909B1AFEADA069FULL, 0x38815B65466C6896ULL, 0xAE33476CBE785EEEULL, 0xC7EAA6673FAE3D91ULL, 
            0x091F8CCEF40A91B9ULL, 0x5E957EDCF3384745ULL, 0x90716886F23DBC94ULL, 0x612C57B92C697833ULL, 
            0x5F6617F395C43A92ULL, 0xBC5B78EBAC9C6EFFULL, 0x7032536CAF43EC31ULL, 0x3BD2DE6CAA164DBEULL
        }
    },
    {
        {
            0x4175753A369EA556ULL, 0x4F2BDDCC26FAC19EULL, 0x5185A14D10BD7F2FULL, 0x3B3A641EFA8C9433ULL, 
            0x8A0B08B2DD9CCEB3ULL, 0xA118EF1B675B13D0ULL, 0x9E2C178007D90689ULL, 0x139FC50EC539367FULL, 
            0x2102D3129A7538DAULL, 0xF10C4C2C9C0AA71BULL, 0x2C14E6A5F42DD248ULL, 0xA42850B4600C7E94ULL, 
            0xA3001E8A3919A350ULL, 0xECA0B7605DF113C8ULL, 0xA4E440DB2DF7C8D0ULL, 0xDE2925E9B89C66B3ULL, 
            0xA97551ED8086A849ULL, 0x7708F84B985BD8E3ULL, 0x3189024A2A2AC100ULL, 0xEF8124D9D589F4B7ULL, 
            0xE56CF3A238F72396ULL, 0xCF3A8170B7D99881ULL, 0x704A70C074A24F77ULL, 0x0FB5C1CBE41B4EADULL, 
            0x66405FC64C5EA327ULL, 0xCC7D59FE3902F677ULL, 0x771BE1B38D032F41ULL, 0x2650559F4102A6A0ULL, 
            0x5D2D16E7FBA563E3ULL, 0x5098E99C5F8ACED5ULL, 0xBC91E2ADD3C082CEULL, 0x9E8AE4372A3532FBULL
        },
        {
            0xB36B7EAF2CF15C73ULL, 0x75194E838D65A048ULL, 0x4271B1F6FE51D14FULL, 0xCC8B79158474204EULL, 
            0xC7E6A607767DF66DULL, 0x4B4B3A1B115533F9ULL, 0x1AB65B34CBE138C5ULL, 0xA23B1BBD525A190AULL, 
            0xE2DA07B3DA75C0F1ULL, 0x18670795902425BCULL, 0xF5BA8C388012AB08ULL, 0x733A791FCA419D1EULL, 
            0x0B6BF825C3389F64ULL, 0x12AE9E64A0935CAAULL, 0xA98BD045D3980FBEULL, 0xF77937A6A6A1210FULL, 
            0x333B65B03E1282F9ULL, 0x1A16E607098E13F2ULL, 0x032ADCC4844F8871ULL, 0xB0F8512D3CBCE840ULL, 
            0x55FD645F9BE7E547ULL, 0x877941B5A326F3EEULL, 0xA6ECE7F22EC858DBULL, 0xA943EFE3A5FC7523ULL, 
            0x9F8ABBDA3F176E36ULL, 0xAC16D8C802577ED3ULL, 0xE7B4FC2977015AEAULL, 0x53745AFC15DF44FBULL, 
            0xD6692C436A0B0112ULL, 0x5EB26B2CBA93D7B4ULL, 0xCC849762A7DA81F7ULL, 0xEB9A28F9B7C1A2F7ULL
        },
        {
            0x6C1AFCD6142A6C21ULL, 0xC5E09A3B2831C102ULL, 0x31A0C93134E6E757ULL, 0x74D9D9292C855C6DULL, 
            0xC4398FFB755AEECBULL, 0xB4391DD7C8AD27DFULL, 0xF5B453CF10F27E2AULL, 0x8AE3BB2AB4D25B68ULL, 
            0xD485D7F5371181A2ULL, 0x953F093856A64612ULL, 0x46E5D19183B7A3D8ULL, 0xC35193EFA1748B5CULL, 
            0x7B3CCF6FA387A932ULL, 0x91F4A4F1549DEB51ULL, 0x7038D9F56A06A804ULL, 0x8E160CC3C8E75A2CULL, 
            0xF3E83CCBC8824E29ULL, 0x19E2EEF178CC6B41ULL, 0xFF7E7BFC897B6FAFULL, 0xD141D6E60ED366DFULL, 
            0x55870C5A6FC27E45ULL, 0xD33BF3C61ED12BC1ULL, 0x53BC8193EC8AC2BEULL, 0x5ADB05A339C60D22ULL, 
            0xB6B70333D9851523ULL, 0x0F75B0FE9DE382D5ULL, 0x9DF822A8842D54ACULL, 0x1F647BB9E2C2290DULL, 
            0x8265180F04A75EBEULL, 0x938647034ABAA5E7ULL, 0x3F4FECEA9E806B11ULL, 0xE4B3854CC1B85F26ULL
        },
        {
            0xAC9279871493322BULL, 0x04264AF32425BCD4ULL, 0x214F48AB04BF9F9DULL, 0x7F7832BF154006AFULL, 
            0x6495420F733917F2ULL, 0xEAFEF25FF710C183ULL, 0x8FDB29A270B37D2EULL, 0x838A3946513D71D3ULL, 
            0x089FC841676E10A0ULL, 0x9B2EE9A22C6FD324ULL, 0x0F83354B907917A4ULL, 0x809E86F9D45C2636ULL, 
            0x357C7356FC0DD366ULL, 0x246445B2F3EB94B6ULL, 0x4794AE3C43DCA26DULL, 0x02DB6774B76D937CULL, 
            0xD28D9F0C2C3D9295ULL, 0x38BD08E869F5CFF4ULL, 0xDD76C9F7DDAB8515ULL, 0x34FDFCBC43111103ULL, 
            0x53D400A7A3CD50EBULL, 0x9619D91A5F2C0ED5ULL, 0xF59FA6A85E52CCCFULL, 0xC313A62A3173E7E8ULL, 
            0xEBAB9C9EAE925E7EULL, 0x4432BCD1E32A76F7ULL, 0x8CD083DE7EA28A02ULL, 0xD3732013FF6C069AULL, 
            0xA4508A8C982D0627ULL, 0x1CCD582193631323ULL, 0x87FAA5986628CAB9ULL, 0x1D74100C7481F682ULL
        },
        {
            0x5401F6DEB3BFB21AULL, 0x43F08BA476512DD3ULL, 0x64F28568820C0977ULL, 0xEDFAAAB985A8288EULL, 
            0xC7E13E3F62B938F2ULL, 0x80CFBF971CE672C6ULL, 0x58915650D6394739ULL, 0xFA1CA5F65FB059FEULL, 
            0x1214AFDE13942592ULL, 0x7A78D01396768736ULL, 0xD8237A038EA00DF4ULL, 0x005657FB3DC03F51ULL, 
            0x40CF3A7C1EE86FF2ULL, 0x552A01016E364C20ULL, 0xD29D4DAD961F44FCULL, 0xB9E20A0AA49EEA82ULL, 
            0xE0A8BF4F79394EA2ULL, 0x13AA607EB19AB7F4ULL, 0x953CE096AA09838AULL, 0x36B6057B960C3B7AULL, 
            0x11074C7E8D6A31B4ULL, 0xE4A0AC843A1570D5ULL, 0xA35A0246DF7DC3C0ULL, 0xEE4E9143BDE8341EULL, 
            0x6FA242CECD5449DDULL, 0xAFF3B3D2AB4B233AULL, 0x2DE85D05E1CE611BULL, 0x01FF9A613907569AULL, 
            0x28FA27578F1C1689ULL, 0xDF34825CAAFCDB7BULL, 0x019684B31A682235ULL, 0xFE6395B27BF60A4CULL
        },
        {
            0x5030DA2FC3F34071ULL, 0xCD4F7DBA425BBA4FULL, 0x12FC0120CD11B6DEULL, 0xD4DA4027D0B6670BULL, 
            0x3C986BD09815AB86ULL, 0x51E8FC4CDCD0782FULL, 0x15AF47081976C75BULL, 0xEE975372AE25E9CAULL, 
            0xFF726F7783E7E0FAULL, 0xFFBB47FB1CFA9347ULL, 0xAD4010F5714CCDEEULL, 0x80B8D2CA3CEEA86BULL, 
            0xD60FB6B76C603E9CULL, 0xAFC5E14C57D60C78ULL, 0x4072FA563CF56C92ULL, 0xE9927252374226E0ULL, 
            0xE88A011012830273ULL, 0x382AF24AE73A1A6AULL, 0xCCEEC8318EE0933CULL, 0xB7E2861AFD324A71ULL, 
            0x79DCEB0B675B5B49ULL, 0x5F7FFB7223F47EADULL, 0xFA5C35EF16E48E21ULL, 0xFC5841794EA12928ULL, 
            0x6BC307DEE0BD9AC9ULL, 0x3F0CF107759C5745ULL, 0x92C12751966295D6ULL, 0xFF39E4073BC91381ULL, 
            0x5E793F757CA217AFULL, 0x2D9370E27C820364ULL, 0x065F551DE841FB82ULL, 0x2E5012532CD05346ULL
        }
    },
    {
        {
            0x3B57AB9F3DC25BA5ULL, 0x6750BFA6B84E2494ULL, 0x942F57463D4B62CBULL, 0xC80885CF0AB76D11ULL, 
            0x05E8A73B6D8649EEULL, 0x1088B59BA9854E9AULL, 0xD7EC3CAB2B79C4BAULL, 0xD6FEA5B4122D8C05ULL, 
            0xC2BAF03B0FACF01DULL, 0xC44AED83BF82DB5BULL, 0x1EEBF1F47EFAA37CULL, 0x72E5F1E91746D7FEULL, 
            0xAAEAA12F1F4F9217ULL, 0x483CB81811AC0D52ULL, 0x7F942945D75990F4ULL, 0x0A8178E9D30AA187ULL, 
            0xB1A3E295F0101CACULL, 0xCCE7B81B1EEAF61BULL, 0x81953DD06C858446ULL, 0xCFEF86F1BE86E4FCULL, 
            0x1C692704DC1B908DULL, 0x9489A522EB177926ULL, 0x29539F5B3F8CCB19ULL, 0xE5021D81884405B4ULL, 
            0xAD657B3667962591ULL, 0x7DCE17466A65EA36ULL, 0x3E5B7B22E49F5EE9ULL, 0x22A8B7FEEE895269ULL, 
            0xDD718187002DEB81ULL, 0xBDF4DCFD8BA8CB20ULL, 0xE38161AAC38F2DB2ULL, 0x48988B13DAD53A0FULL
        },
        {
            0xBD50502E7367F5DCULL, 0xC5CB47F8777D3E73ULL, 0x9081E6E8C2E6907EULL, 0x628CAC0C13DF2BB3ULL, 
            0x076E5556FF9F9367ULL, 0x79F3CE48573E4E96ULL, 0xB822DF0C5DD71740ULL, 0x66FC060E43EE0BEBULL, 
            0xE68A7F048E3DEEDEULL, 0xB4AECD1818ADFFA6ULL, 0x1980B8BDDA00E418ULL, 0x6688013B4EF4CAB7ULL, 
            0x6E3DEA3964C5E55FULL, 0x7D53001A9162AFB0ULL, 0x289C27439F607B0DULL, 0xF2BB7F81EA7E1C0EULL, 
            0x103DACBA39813985ULL, 0xC57AD17F1712B30FULL, 0x0DD2FDAB5048A37EULL, 0x5D7D5746948778A8ULL, 
            0x9A28B3780C10780EULL, 0x3B3A9CC20E48BE14ULL, 0x4DC10ABC37FDC90EULL, 0x3887C86555C5612DULL, 
            0x61A6335DE05240D6ULL, 0x72B5C7634C6DB3FDULL, 0x360103A4C767DF5FULL, 0x8CA4A53AE7F60BC9ULL, 
            0x238CC02487ACBF4BULL, 0xEEC0CA506DC71C55ULL, 0xC73FDE254451828BULL, 0x6BC5CF134F6C1DE1ULL
        },
        {
            0x3BAB5D888EC4260BULL, 0xE1739E98FD65BB48ULL, 0x3B0EC9ABAD43F0CEULL, 0x81293EC5E3A49FD6ULL, 
            0xC06967054050C6BDULL, 0x5216E28C4868FE92ULL, 0xC60ACDE528C7C483ULL, 0xB062B9037AF38455ULL, 
            0xBD796987CAA2888BULL, 0xA01F756A0C17CABFULL, 0x5879EC3ADAAD8767ULL, 0x98643C3FC3F8EA9BULL, 
            0xB120B9EB1FBACF06ULL, 0x67A21C34C608CA9DULL, 0xAD7299B1ED1D9D96ULL, 0x6DF99967563E7D5AULL, 
            0x3FDB99BFE8F61CB5ULL, 0x974A202B476554E4ULL, 0x4D26CFA7BAD46961ULL, 0xCA3F7C3148B0DFF9ULL, 
            0xFCB0370531A2F602ULL, 0xB67F1998037D175FULL, 0x2F1346CC9FD41609ULL, 0x509F80BAA620EB6CULL, 
            0x27C7C82ACC63AA02ULL, 0xF86606F91CF2FFFAULL, 0xC76BECF7917EA232ULL, 0xA5C1DADE02D44487ULL, 
            0xC252F1130A6ECAEAULL, 0x4280F355DECAF872ULL, 0x323D75B2F83934FBULL, 0x0599F9C71C02FB37ULL
        },
        {
            0xAADF51C3E3C4C697ULL, 0xF8B3D02C6DB2B1AEULL, 0xACAB8043B5699358ULL, 0xAE2590C9547C2C29ULL, 
            0xBDE4491E6842454AULL, 0x7FCA75E8445CEC8FULL, 0x190569B2D8657145ULL, 0xEC3F45F363A9392CULL, 
            0xB30C0FD0BBC188BAULL, 0x0FED635E242C25A6ULL, 0xA0C8E60AAFDDE466ULL, 0xDEC33B29020C49B6ULL, 
            0xC2496151500CDF76ULL, 0x75978EC80EA3285FULL, 0x6758BD05D3C5B70BULL, 0xC01FED6893170E64ULL, 
            0xE55F359FF05B6F17ULL, 0x2F5804AA0D39E796ULL, 0xBD2F497599D6F02EULL, 0x6A65A1F3DAB297C3ULL, 
            0x4AC9F580A19A8758ULL, 0xB58C5E6B05D78E3FULL, 0x27AD8E57938D13E8ULL, 0x256D6B622F9CF70DULL, 
            0xB0E1E94E3AF51935ULL, 0x56240C8FCBF77D17ULL, 0xE497477E88FCB091ULL, 0x5E06CBBB3516BAACULL, 
            0xE509B0F9FA31C078ULL, 0x2A218A13C12935A3ULL, 0xF002C01BCBD494B9ULL, 0xE036616D4DF5E853ULL
        },
        {
            0x53B531368064FFA2ULL, 0x19338EB2E16E5C76ULL, 0xD427B1C58A8B0609ULL, 0x2E42C834BDDF3381ULL, 
            0xE09E1F0DDED98945ULL, 0x8ACAFBF27BD4FDD1ULL, 0xCBC8C5830F89E578ULL, 0x4522AC22E2CB3638ULL, 
            0xCF973F11BD88F8DCULL, 0x1DC9439497862DA3ULL, 0x3EB426D0B8BF5650ULL, 0x04266832CFF2C3DEULL, 
            0x9740AF21BD0E1EF2ULL, 0xE97B8CBEB120E6C6ULL, 0xB05A280E45AE000CULL, 0x01C94AE113BECF14ULL, 
            0x76E695EF55947A64ULL, 0xD73538BA10C8343FULL, 0x8863386959F10EC1ULL, 0xF0423962C18E4CE1ULL, 
            0xFB24F99A9F2872D9ULL, 0x879179638CBED039ULL, 0xF67970E5623F1180ULL, 0x6508F8A945D3B78EULL, 
            0x600B988488DB5B4CULL, 0x5EDC53E22657FF6AULL, 0x62AD012E8378A7F9ULL, 0x701FFBD0F539DA44ULL, 
            0xAA9A00AE1AE4C0F1ULL, 0xB33B83BFF41F228AULL, 0x6FCD39077997B3ABULL, 0xDAC06391803E74EDULL
        },
        {
            0x9FCFE80FFA6CAEA5ULL, 0x152A71CC44246380ULL, 0x5122CFC4A5E6756FULL, 0xD2D41293C57BE536ULL, 
            0x6C756A272D5AAFB1ULL, 0x4D8AFF486DD3E1A1ULL, 0x4C278A367EA8926CULL, 0x13806CCD545643F3ULL, 
            0x89BF1EDE2539CA7CULL, 0xFDA1E9659D3BD70AULL, 0x631F4FDD5F6E5E70ULL, 0xD0687D450C8ACFA2ULL, 
            0x20D60760C10037B1ULL, 0x8C59134136EC65D8ULL, 0x7BBDB20F29BA9103ULL, 0x72323AC88E2D84A0ULL, 
            0x5E6E0ED488E94143ULL, 0x2052AB4FDE3DCA97ULL, 0x79558D0ABDFFFD1AULL, 0x9741132A3A53D20CULL, 
            0xC08E383E15DFC9DFULL, 0x34D6C43CCC7F8838ULL, 0x216B24743FF1BD03ULL, 0xF0A04DF8A3AB9C84ULL, 
            0xDB782EE2E0ABE306ULL, 0x502B4B8D51425218ULL, 0x6CC97E71D56235CDULL, 0xEF3BD78CF17CC7E3ULL, 
            0x1FC1071DF9887962ULL, 0xA9DB33D70760E27BULL, 0x6FA2FFCB30BC3651ULL, 0x8C93D56A1C06F726ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kTwistConstants = {
    0x880F4630F8227DE6ULL,
    0x60C9112770BDC89AULL,
    0xF2E2C75571283677ULL,
    0x880F4630F8227DE6ULL,
    0x60C9112770BDC89AULL,
    0xF2E2C75571283677ULL,
    0xF51080C35CDB4719ULL,
    0xDDBE73C7934B1F8FULL,
    0x68,
    0x77,
    0x5D,
    0xAB,
    0x0D,
    0x62,
    0x6D,
    0x67
};

