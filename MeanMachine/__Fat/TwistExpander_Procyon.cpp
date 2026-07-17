#include "TwistExpander_Procyon.hpp"
#include "TwistDiffuse.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix32.hpp"
#include "TwistMix64.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmConstants.hpp"
#include "TwistMemory.hpp"
#include "TwistShiftBox.hpp"
#include "TwistSnow.hpp"
#include "TwistSquash.hpp"

#include <cstdint>
#include <cstring>

TwistExpander_Procyon::TwistExpander_Procyon()
: TwistExpander() {
    mDomainBundleInbuilt.mPhaseASalts = kPhaseASalts;
    mDomainBundleInbuilt.mPhaseAConstants = kPhaseAConstants;
    mDomainBundleInbuilt.mPhaseBSalts = kPhaseBSalts;
    mDomainBundleInbuilt.mPhaseBConstants = kPhaseBConstants;
    mDomainBundleInbuilt.mPhaseCSalts = kPhaseCSalts;
    mDomainBundleInbuilt.mPhaseCConstants = kPhaseCConstants;
    mDomainBundleInbuilt.mPhaseDSalts = kPhaseDSalts;
    mDomainBundleInbuilt.mPhaseDConstants = kPhaseDConstants;
    mDomainBundleInbuilt.mPhaseESalts = kPhaseESalts;
    mDomainBundleInbuilt.mPhaseEConstants = kPhaseEConstants;
    mDomainBundleInbuilt.mPhaseFSalts = kPhaseFSalts;
    mDomainBundleInbuilt.mPhaseFConstants = kPhaseFConstants;
    mDomainBundleInbuilt.mPhaseGSalts = kPhaseGSalts;
    mDomainBundleInbuilt.mPhaseGConstants = kPhaseGConstants;
    mDomainBundleInbuilt.mPhaseHSalts = kPhaseHSalts;
    mDomainBundleInbuilt.mPhaseHConstants = kPhaseHConstants;
    mDomainBundleEphemeral.Zero();
}

void TwistExpander_Procyon::KDF_A(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  std::uint8_t *pSnow,
                                  int pIndexKDF) {
    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pSnow, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr) || (pSnow == nullptr)) { return; }
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
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
    std::uint64_t aPrevious = 0xBC11D522505EB2ACULL; std::uint64_t aIngress = 0xB23A8FD876720902ULL; std::uint64_t aCarry = 0xFED6B81F88723E62ULL;

    std::uint64_t aWandererA = 0xF263176FD58FDE4FULL; std::uint64_t aWandererB = 0x9CEBB0023C8CAA62ULL; std::uint64_t aWandererC = 0xC6A60F42D46FC725ULL; std::uint64_t aWandererD = 0xC8C9A98C2CCAC654ULL;
    std::uint64_t aWandererE = 0x94946409B36B70BDULL; std::uint64_t aWandererF = 0xFF53D690650B9F12ULL; std::uint64_t aWandererG = 0xEDAF4D1D197119A3ULL; std::uint64_t aWandererH = 0xF82F13391F68E92DULL;
    std::uint64_t aWandererI = 0xA7FD25671CD7690FULL; std::uint64_t aWandererJ = 0xBFC1AB572B09F7E8ULL; std::uint64_t aWandererK = 0x94700C2D54524023ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14755363362214065559U;
        aCarry = 14264152111062399840U;
        aWandererA = 15052467130733197370U;
        aWandererB = 11035946445599965261U;
        aWandererC = 10889550340641510466U;
        aWandererD = 9800077840242461485U;
        aWandererE = 11415667749829483112U;
        aWandererF = 12014812942634353843U;
        aWandererG = 17594839179115536568U;
        aWandererH = 13922831442957035512U;
        aWandererI = 14751337024807963154U;
        aWandererJ = 15271641883253967216U;
        aWandererK = 14138954528279721599U;
    TwistExpander_Procyon_Arx::KDF_A_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
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

    TwistExpander_Procyon_Arx::KDF_A_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
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

    TwistExpander_Procyon_Arx::KDF_A_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
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

    TwistExpander_Procyon_Arx::KDF_A_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
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

    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aWindLaneA, aWindLaneB, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aWindLaneC, aWindLaneD, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    TwistExpander_Procyon_Arx::KDF_A_E(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
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

}

void TwistExpander_Procyon::KDF_B(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  int pIndexKDF) {
    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xCDB49A7BAF7414D0ULL; std::uint64_t aIngress = 0xC4E3CBA118371202ULL; std::uint64_t aCarry = 0x88ED9B27DFB516EDULL;

    std::uint64_t aWandererA = 0xEEE7CC759BBBF4D9ULL; std::uint64_t aWandererB = 0xEA891EEF94C1B726ULL; std::uint64_t aWandererC = 0xCFC066AA0B0B3702ULL; std::uint64_t aWandererD = 0xE46EDD6A9DF2BC7AULL;
    std::uint64_t aWandererE = 0x899163F838F08DA1ULL; std::uint64_t aWandererF = 0xC26EA68E9CF2A700ULL; std::uint64_t aWandererG = 0xEB651FDFCF3369D7ULL; std::uint64_t aWandererH = 0xD2A6C722DA7E5104ULL;
    std::uint64_t aWandererI = 0xD967115AF548B029ULL; std::uint64_t aWandererJ = 0xF327CDBAC5D9A0A4ULL; std::uint64_t aWandererK = 0xEFE71E0C7A6CBE45ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15968034260830204674U;
        aCarry = 12435555375305454732U;
        aWandererA = 15982152130465455160U;
        aWandererB = 12211097490358993274U;
        aWandererC = 13021295646654693541U;
        aWandererD = 11300263281828097481U;
        aWandererE = 15402020826806109044U;
        aWandererF = 13857745056726536046U;
        aWandererG = 18025413161542297265U;
        aWandererH = 13065256123595594128U;
        aWandererI = 12821701151231893585U;
        aWandererJ = 15181140007893797107U;
        aWandererK = 10931176584227352229U;
    TwistExpander_Procyon_Arx::KDF_B_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
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

    TwistExpander_Procyon_Arx::KDF_B_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
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

    TwistExpander_Procyon_Arx::KDF_B_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
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

    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aWorkLaneA, aWorkLaneB, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aWorkLaneC, aWorkLaneD, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    TwistExpander_Procyon_Arx::KDF_B_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
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

}

void TwistExpander_Procyon::Seed(TwistWorkSpace *pWorkSpace,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint64_t pNonce,
                                 std::uint8_t *pPassword,
                                 std::size_t pPasswordByteLength,
                                 std::uint8_t *pDestination) {
    TwistExpander::Seed(pWorkSpace, pFarmSalt, pNonce, pPassword, pPasswordByteLength, pDestination);
    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr)) { return; }
    std::uint8_t *aSource = pWorkSpace->mSource;
    std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    std::uint8_t *aSnowLaneC = pWorkSpace->mSnowLaneC;
    std::uint8_t *aSnowLaneD = pWorkSpace->mSnowLaneD;
    std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
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
    std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    std::uint8_t *aInvestLaneE = pWorkSpace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = pWorkSpace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = pWorkSpace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = pWorkSpace->mInvestLaneH;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xF8296C8DCE25D45FULL;
    std::uint64_t aIngress = 0xE585C317D4CA1421ULL;
    std::uint64_t aCarry = 0xE4F550D38C18F6BDULL;

    std::uint64_t aWandererA = 0x934D0DE23639DF7AULL;
    std::uint64_t aWandererB = 0xD286B271E2570BA9ULL;
    std::uint64_t aWandererC = 0x8BF0EB75149BB0B9ULL;
    std::uint64_t aWandererD = 0xF95F894C0AC7E7B6ULL;
    std::uint64_t aWandererE = 0xD4BAE7C4DA92272EULL;
    std::uint64_t aWandererF = 0xBFADEC0466D97196ULL;
    std::uint64_t aWandererG = 0xFB561C69E45643CEULL;
    std::uint64_t aWandererH = 0xE09ABF1EC1EDB879ULL;
    std::uint64_t aWandererI = 0xC14E971EDB578097ULL;
    std::uint64_t aWandererJ = 0xE1A73B620E15F24DULL;
    std::uint64_t aWandererK = 0x8072F137A1A26481ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneD, 0);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseAConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseAConstants), &(mDomainBundleEphemeral.mPhaseASalts), 0);
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseAConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase B
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneA, 1);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseBConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseBConstants), &(mDomainBundleEphemeral.mPhaseBSalts), 1);
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseBConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase C
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneB, 2);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseCConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseCConstants), &(mDomainBundleEphemeral.mPhaseCSalts), 2);
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseCConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase D
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneC, 3);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseDConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseDConstants), &(mDomainBundleEphemeral.mPhaseDSalts), 3);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseDConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase E
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneD, 4);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseEConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseEConstants), &(mDomainBundleEphemeral.mPhaseESalts), 4);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseEConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase F
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneA, 5);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseFConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseFConstants), &(mDomainBundleEphemeral.mPhaseFSalts), 5);
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseFConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase G
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneB, 6);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseGConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseGConstants), &(mDomainBundleEphemeral.mPhaseGSalts), 6);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseGConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase H
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneC, 7);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseHConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseHConstants), &(mDomainBundleEphemeral.mPhaseHSalts), 7);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseHConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    // GSquashInvestToKeyBoxes (start)
    SquashInvestToKeyBoxes();
    // GSquashInvestToKeyBoxes (end)
    //
    TwistExpander_Procyon_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aFireLaneA, aFireLaneB, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aFireLaneC, aFireLaneD, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    TwistExpander_Procyon_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
    //
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aInvestLaneE, aInvestLaneF, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aInvestLaneG, aInvestLaneH, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    TwistExpander_Procyon_Arx::Seed_I(pWorkSpace,
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

        TwistSquash::SquashC(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Procyon_Arx::GROW_A(pWorkSpace,
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

    GrowKeyA(pWorkSpace);
    TwistExpander_Procyon_Arx::GROW_B(pWorkSpace,
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

    GrowKeyB(pWorkSpace);
    Zero_PostSeed();
}

// SmartSquash candidate 26 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 45307
void TwistExpander_Procyon::SquashInvestToKeyBoxes() {
    static_assert((S_BLOCK / W_KEY) == 16, "SquashInvestToKeyBoxes expects 16 invest fragments.");
    static_assert(H_KEY == 8, "SquashInvestToKeyBoxes expects 8 key rows per box.");
    if (mWorkspace == nullptr) { return; }
    std::uint8_t *aInvestLaneA = mWorkspace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = mWorkspace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = mWorkspace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = mWorkspace->mInvestLaneD;
    std::uint8_t *aInvestLaneE = mWorkspace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = mWorkspace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = mWorkspace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = mWorkspace->mInvestLaneH;

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1286U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2004U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1712U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 361U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1688U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1372U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1369U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1121U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1195U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1459U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 380U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 441U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1753U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1929U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 820U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1772U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1213U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 417U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1855U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1635U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 461U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1137U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1013U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1671U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 783U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 367U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1922U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1582U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1059U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1295U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 842U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 686U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 299U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 539U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 174U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1382U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 889U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 728U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1547U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 306U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 199U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 734U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 887U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1076U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2042U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1925U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1241U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 168U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 569U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1355U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1253U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 235U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1594U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1412U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 401U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 99U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1397U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 536U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 787U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 38U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 544U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1974U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1579U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1852U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1959U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1328U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1518U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 562U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 604U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1609U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1826U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 816U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 90U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1235U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 504U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 586U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1616U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1782U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1248U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1455U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 111U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1123U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 387U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1915U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1127U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1166U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 37U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1007U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1716U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 921U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 335U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1387U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1391U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 634U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 984U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2028U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 262U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 793U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 280U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 429U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 809U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 963U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1441U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1298U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 503U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1146U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1653U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 415U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 455U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1103U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 766U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1350U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 204U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 638U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 82U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1494U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 383U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 325U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 391U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 761U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 729U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 792U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 342U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 612U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 22U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 691U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 876U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1089U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Procyon::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xFD6647A7A67CC100ULL; std::uint64_t aIngress = 0xD43793B4D7C9CDF8ULL; std::uint64_t aCarry = 0xF2502F8C89C682C1ULL;

    std::uint64_t aWandererA = 0xA3A2C3C775EF3EC6ULL; std::uint64_t aWandererB = 0xCC1B31D334361B9AULL; std::uint64_t aWandererC = 0x8563DB1328F79801ULL; std::uint64_t aWandererD = 0xB2FCE4BC7045EEE2ULL;
    std::uint64_t aWandererE = 0xD45F562D2D2E9320ULL; std::uint64_t aWandererF = 0x9621891D73AAAA64ULL; std::uint64_t aWandererG = 0x975453E6EB49EE65ULL; std::uint64_t aWandererH = 0xAD3F5CB80432C8C3ULL;
    std::uint64_t aWandererI = 0xB8E0B21B57D18B86ULL; std::uint64_t aWandererJ = 0x879BF7084FD13059ULL; std::uint64_t aWandererK = 0x856B398AF3414683ULL;

    // [seed]
        aPrevious = 11598630553811754964U;
        aCarry = 12809035138725771419U;
        aWandererA = 9515111164826209186U;
        aWandererB = 10540988036698341382U;
        aWandererC = 17264497376859582467U;
        aWandererD = 13884037044267056143U;
        aWandererE = 14461950833352316343U;
        aWandererF = 10787062786649172915U;
        aWandererG = 14479993617513684257U;
        aWandererH = 14052422302902679426U;
        aWandererI = 12842132454424580320U;
        aWandererJ = 12272187761226062016U;
        aWandererK = 18044086224604111837U;
    TwistExpander_Procyon_Arx::Twist_A(pWorkSpace,
                 pSource,
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

    TwistExpander_Procyon_Arx::Twist_B(pWorkSpace,
                 pSource,
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

    TwistExpander_Procyon_Arx::Twist_C(pWorkSpace,
                 pSource,
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

    TwistExpander_Procyon_Arx::Twist_D(pWorkSpace,
                 pSource,
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

    TwistExpander_Procyon_Arx::Twist_E(pWorkSpace,
                 pSource,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aFireLaneA, aFireLaneB, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aFireLaneC, aFireLaneD, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Procyon_Arx::Twist_F(pWorkSpace,
                 pSource,
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

    TwistExpander_Procyon_Arx::Twist_G(pWorkSpace,
                 pSource,
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
        TwistSquash::SquashB(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Procyon_Arx::GROW_A(pWorkSpace,
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

    GrowKeyA(pWorkSpace);
    TwistExpander_Procyon_Arx::GROW_B(pWorkSpace,
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

    GrowKeyB(pWorkSpace);
}

// GrowA candidate 26 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13528; nearest pair: 467 / 674
void TwistExpander_Procyon::GrowKeyA(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) { return; }
    std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    std::uint8_t *aScrapLaneA = pWorkSpace->mScrapLaneA;
    std::uint8_t *aScrapLaneB = pWorkSpace->mScrapLaneB;
    std::uint8_t *aScrapLaneC = pWorkSpace->mScrapLaneC;
    std::uint8_t *aScrapLaneD = pWorkSpace->mScrapLaneD;
    std::uint8_t *aMergeLaneA = pWorkSpace->mMergeLaneA;
    std::uint8_t *aMergeLaneB = pWorkSpace->mMergeLaneB;
    std::uint8_t *aMergeLaneC = pWorkSpace->mMergeLaneC;
    std::uint8_t *aMergeLaneD = pWorkSpace->mMergeLaneD;
    std::uint8_t *aKeyRowWriteA = &(pWorkSpace->mKeyBoxA[0][0]);
    static_assert((S_BLOCK / S_QUARTER) == 4, "GrowKeyA expects four expansion-lane quarters.");
    static_assert((S_QUARTER / W_KEY) == 4, "GrowKeyA expects four key chunks per quarter.");
    TwistShiftBox::ShiftKeyBoxA(pWorkSpace);
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7073U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 907U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1840U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2175U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 692U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1733U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1939U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5094U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 221U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6356U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7458U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6166U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7695U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2351U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 238U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2874U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 514U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1108U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1690U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 672U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 857U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 418U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 115U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1401U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1193U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1428U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 173U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2029U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 799U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1985U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 666U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 359U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 821U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 937U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1672U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1074U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 26 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13520; nearest pair: 476 / 674
void TwistExpander_Procyon::GrowKeyB(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aScrapLaneA = pWorkSpace->mScrapLaneA;
    std::uint8_t *aScrapLaneB = pWorkSpace->mScrapLaneB;
    std::uint8_t *aScrapLaneC = pWorkSpace->mScrapLaneC;
    std::uint8_t *aScrapLaneD = pWorkSpace->mScrapLaneD;
    std::uint8_t *aMergeLaneA = pWorkSpace->mMergeLaneA;
    std::uint8_t *aMergeLaneB = pWorkSpace->mMergeLaneB;
    std::uint8_t *aMergeLaneC = pWorkSpace->mMergeLaneC;
    std::uint8_t *aMergeLaneD = pWorkSpace->mMergeLaneD;
    std::uint8_t *aKeyRowWriteB = &(pWorkSpace->mKeyBoxB[0][0]);
    static_assert((S_BLOCK / S_QUARTER) == 4, "GrowKeyB expects four work-lane quarters.");
    static_assert((S_QUARTER / W_KEY) == 4, "GrowKeyB expects four key chunks per quarter.");
    TwistShiftBox::ShiftKeyBoxB(pWorkSpace);
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4639U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2048U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7577U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8034U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2897U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 609U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 781U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6269U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1558U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5701U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2833U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6755U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 8128U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 115U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5734U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5018U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 266U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 408U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 571U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1049U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 368U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1870U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1303U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2011U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 521U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1921U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1258U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 202U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 918U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 829U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 942U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2024U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1832U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 907U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1913U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 701U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseASalts = {
    {
        {
            0xFD4471E68BC825BCULL, 0xF507105801EDE661ULL, 0xE0F9F679E9F82500ULL, 0xA4C0BE6DC7132259ULL, 
            0x25FD5CBEBFD8DDE2ULL, 0xFA973596411D11CCULL, 0x25EC01B0E2E0C521ULL, 0xE570663615394DA5ULL, 
            0xB4D125199F363F1EULL, 0x4A8BCA12D84FEAE3ULL, 0xB37EAA87675E6C0DULL, 0x3F7FC39A367263A2ULL, 
            0x3C03DD53A8188B22ULL, 0x4CC7D276CE9D3B34ULL, 0x56EBFE16C5A93FE7ULL, 0x112D420A04986052ULL, 
            0x5FC71FB5EEFFFA9AULL, 0xD7A5C97EBAAA031FULL, 0x1ACCA2965FACE726ULL, 0xD3BDBEECB1D80999ULL, 
            0x2DA6D8DF3E0A3CB2ULL, 0xE3AC63F0B2129F1AULL, 0xADDD484AB8521EF6ULL, 0x524386798331CCFDULL, 
            0xAA53B4511EDDC796ULL, 0x944B5D3A83762CB1ULL, 0x3A9106186A5ACF13ULL, 0xF07E248E4AB967C2ULL, 
            0x9B346287311D4F1AULL, 0xB666B4E5FE9907A1ULL, 0xF4C9011017027E50ULL, 0x4DB4855E4FBCDD21ULL
        },
        {
            0x87011E088301500CULL, 0x64A9E256026C6B2EULL, 0x761B68359C509B64ULL, 0x320B86B4697DDC28ULL, 
            0x07337A0C0741C527ULL, 0x85CA63C26ED5F33BULL, 0x878A1916A8EA0CE2ULL, 0xAA5C26F176A41C8CULL, 
            0x1EDFF7C543C52BEAULL, 0xD7B56013FB08670CULL, 0x43108573BC85D51CULL, 0x3D6055C905878500ULL, 
            0xDC7CD0D30630F257ULL, 0x9B238D3F4362FE57ULL, 0x9D9648E277626361ULL, 0xEE2920D7BD698C4DULL, 
            0xDAF0930A5ECCDF12ULL, 0x3396DC09E537D513ULL, 0x6BCAB36C1D769148ULL, 0x75D2082183AB8E8BULL, 
            0x1AEEF676F20BD816ULL, 0xC7D8C20E62AA4269ULL, 0x321A9DB42A1076CBULL, 0xFF689857F184E56FULL, 
            0xBB341FF02BC126B2ULL, 0x1CCCFDFAD5CACD4DULL, 0xE58861182CBEB7C6ULL, 0x1BD3DED2BAB638D7ULL, 
            0x839BD9D776AD9F65ULL, 0xED65211B423ED4DBULL, 0xA6015E7EBD0E4036ULL, 0x6268DBA7A313572FULL
        },
        {
            0x1995659497CF430AULL, 0xA322FF4F31B2E8AEULL, 0x9964FC83FA12018DULL, 0x90EAEEB8DC27EE85ULL, 
            0x42AD543CF2A0CE71ULL, 0xEACCCC91A1DE0D29ULL, 0x667B4335215ED205ULL, 0x462CD9559FB5C33BULL, 
            0xA19756FF8560E044ULL, 0xBAF560A24E3F8B82ULL, 0x43499F26B8D3961AULL, 0x44F3EF60D4F31CFBULL, 
            0x412D089DBD38545AULL, 0x6344D6BA8DA61692ULL, 0x84926D091D0E7F32ULL, 0xC8B2F51A21C134C9ULL, 
            0xCDF33AC80658414CULL, 0x945D531F5CF799ADULL, 0xE1F402E2E9C8B3A2ULL, 0x9863278AE63F2ED3ULL, 
            0x4CA1F40E5F90A7A2ULL, 0xAA245120DD4E7C4AULL, 0xE96A6D282C6E95B7ULL, 0x622E2DFE60CAD76EULL, 
            0x40A2AC1293D57376ULL, 0xBFAFFFFE5CE52571ULL, 0xF591A704AFBE5713ULL, 0x8D5B19B7B7DB3AE9ULL, 
            0x2823ABC71C13425DULL, 0xA2D52E66EFEEAEB2ULL, 0x5712F550428A66E5ULL, 0x8939625DB779EF5CULL
        },
        {
            0x1EAB2C65105802E7ULL, 0x769A62F71929D5CFULL, 0xF05AE2E004D3C732ULL, 0x769526573C704E0AULL, 
            0x4DB929C5F5022CB9ULL, 0xAFA123A256D264C9ULL, 0x8A30D032F042EF95ULL, 0xB2255C6AB04F365AULL, 
            0x87DF946A0A0C09E6ULL, 0x53BB3DB5835CE444ULL, 0x3FEB208F852C5AC1ULL, 0xD172F85F2FC0C28DULL, 
            0x103EA2201B543220ULL, 0x60F71D3773884C56ULL, 0x3401750D0F65B0C5ULL, 0x1FE8724BFDDD818CULL, 
            0xAAFA8DF8C274C8B6ULL, 0x5B523B6B28396365ULL, 0x79AFCD7CD50673D8ULL, 0x0EDCD9F802671837ULL, 
            0x6A5BA9C7122B6849ULL, 0xD02DF4B874E39A77ULL, 0xF7CAE5B2F5F63F00ULL, 0xEFFCD2E831B4C60AULL, 
            0x2BB65E6BAD8AEA58ULL, 0xE2FFF36EE7124A28ULL, 0x07F08CAED9796C56ULL, 0x28E6B80F95EEAC99ULL, 
            0xA04A8635B53349C9ULL, 0x8D96D4BA7CE35698ULL, 0x5FBB3F892B1ECD17ULL, 0x0B20E77B07431E19ULL
        },
        {
            0x9D299C62565C898BULL, 0x4ECFFCA4316A41F5ULL, 0x704A7EC1E25FA54BULL, 0xF18096259C169A20ULL, 
            0x61D277B447388377ULL, 0x033C750DA06674C7ULL, 0x4CF4EF527714CDF7ULL, 0xBCA26D9416C8A818ULL, 
            0x330D92E35F29540FULL, 0x57853ECA3B590F6BULL, 0xA83077772792D914ULL, 0x024B9A93AA744D5CULL, 
            0xDAA821DC56D63B64ULL, 0xB1A3E74A163E2436ULL, 0x54E177208B9678D3ULL, 0xB37C96A66D798DDBULL, 
            0x4832CBA00AD69C30ULL, 0xA3AE2074B9B23CE4ULL, 0xAD3705144FE065B3ULL, 0x87FD9E20368B9AF7ULL, 
            0x6CD48E849B08F958ULL, 0x02A79014D3D01465ULL, 0x0892C84C3A7CF2E1ULL, 0xF7C33A0D965973E9ULL, 
            0xED9EB8D01DDBD96AULL, 0x8413D3CE102D49BCULL, 0x6003909E2E0BB56AULL, 0x0CD6510A3A660D0EULL, 
            0xA420BFC7EF33E9E6ULL, 0xED2AB91B935557ECULL, 0x9022D01D24DF50B7ULL, 0x87FDC1AE7316802FULL
        },
        {
            0xD9F2D3DB2BF2571FULL, 0xF4158F627526984BULL, 0x3A1EA74B890AA5E5ULL, 0xF5402D7A61AFA44FULL, 
            0x67C6BCB70329A8E0ULL, 0xEA6A77305B3B172FULL, 0xC7D9C16B3E129964ULL, 0xA7456C9D3B3C76DEULL, 
            0xBBC1B78994888F2FULL, 0x664A16D1CA1F651FULL, 0x6ED3B455AB92F0D2ULL, 0x9021089743328F52ULL, 
            0x51E670CF7CE5BBFBULL, 0x9BD89F5AC06EBB07ULL, 0x25E993C08C1BFD2FULL, 0xD4AF4C497ABE46B1ULL, 
            0x78A0F8A52C510974ULL, 0x8B6DF20B96F6242FULL, 0x5B1675C05881DC58ULL, 0x88CAF8422047F65EULL, 
            0x42728E83F98A0AC0ULL, 0xA724223E3121AFA0ULL, 0x78B82225A1E66D8AULL, 0x18781722A2F51BE3ULL, 
            0x24B0D0D134FA1E6AULL, 0x958EE7EE910801B4ULL, 0x694ADBAFF03B9839ULL, 0xCE91978286A36CE5ULL, 
            0x7FAA42EC19564B9EULL, 0x17BF31FF40441DBCULL, 0x17E3BC690DD28033ULL, 0x309EEE56887F2615ULL
        }
    },
    {
        {
            0x3463C3F3EE5A5C83ULL, 0xB2C2809612660D01ULL, 0xBC3D8BEB978BF3E6ULL, 0xAEF0924502D230BEULL, 
            0xFFA680ACB5111276ULL, 0xF75C048C97A6A41CULL, 0x8D68990548B2698CULL, 0x57961CAB5CCE6BACULL, 
            0x9A2E6DB893BF2B71ULL, 0x4E1F144099A95D9FULL, 0x95063A661C542B92ULL, 0x0B494E3C9B16E4A4ULL, 
            0x6EF9E631210342BDULL, 0xC232BBFE8F09E586ULL, 0xBF06A7075B00F4DFULL, 0x3D069A923C5E1290ULL, 
            0x742F722ED6C9E589ULL, 0x1E8B32D8FA181D98ULL, 0xF06D9F99DB999F82ULL, 0x6CCB6BAE0D3F5948ULL, 
            0x6B8DC1BBB183D3A1ULL, 0xC1B3E724F7899701ULL, 0x59637C8C1C9319F3ULL, 0x7E29342657E103EBULL, 
            0xF4B0A2EADDA865C5ULL, 0x853031F8CF3D7598ULL, 0x11FF1DA69EAA70B9ULL, 0x551210DC3E9174B8ULL, 
            0x45ECDF33C687BCCAULL, 0x1C3D0045242FC585ULL, 0xCE5845D436D89BA9ULL, 0xE2846AB817EB2216ULL
        },
        {
            0xA21B4F055DEDE625ULL, 0x37F21637A097595BULL, 0x8C0F481E74199225ULL, 0x87CC95207CBAAC11ULL, 
            0x6E1346D8F906F9DDULL, 0x38EE4CC45F01B135ULL, 0x8D0C725ACEFB889AULL, 0x1B45CD903ECD19DEULL, 
            0xE382168999436B1BULL, 0xC8705ED800595453ULL, 0x6F43878978A4A548ULL, 0x21D50B74C24AD6EFULL, 
            0x0A7D590AEBB00B27ULL, 0x139A9C5D75FB0A72ULL, 0xF50C748AFC09BC93ULL, 0x78C5CC2C5D9CC623ULL, 
            0xDAF4949F285FBEC4ULL, 0x669A734620401736ULL, 0x1090B8EE2A91B851ULL, 0x2CB38580322B64C5ULL, 
            0x9C6ED5589DB28FDCULL, 0x4E0C02FD62D3FDBBULL, 0x1BDC548D76B858BFULL, 0xB80EF0F048F1877EULL, 
            0x4CA621ED209D9224ULL, 0xD5843705DA982557ULL, 0x137D35010730965DULL, 0x894D2AE6CF255101ULL, 
            0xB45D5C71007E2C1DULL, 0xB294F640583BFAC1ULL, 0xD29537955258A1AAULL, 0x018232A2A7E25749ULL
        },
        {
            0x35CAD22DCC399C15ULL, 0xC099EB98177D3DAAULL, 0xCE28BCC0C820BC18ULL, 0x1272B4BC103B1288ULL, 
            0xD670747094D0A9D7ULL, 0x010662BDF6E09A51ULL, 0x9719558A8190B38BULL, 0xA782E13691606016ULL, 
            0xD1698DBA79A32691ULL, 0x9F900DF1D711EB9AULL, 0xB7704FEB659524E1ULL, 0xD9AEFE9F6D1F2EF1ULL, 
            0x1AA8505BF8BF2C10ULL, 0x3C3C9690121A718BULL, 0x6FF3BF737B9F4F03ULL, 0x9A6AE37FDEDB630CULL, 
            0xCA54E7BD989F68ADULL, 0x4FCE1286A9EDF5A1ULL, 0x33D5AD22BA945C38ULL, 0x31035F105E0513CDULL, 
            0xDD1AB6D23A300DC2ULL, 0x605E3F7EA9971BDBULL, 0x583EFC9EC4207E3CULL, 0xE3144D1D110A75C6ULL, 
            0x044E5C01CB5DEE2FULL, 0x82626787F2FCBE78ULL, 0xBCBB554A0F8DF6A4ULL, 0xFE910C1ED31F58B3ULL, 
            0x76A95A1119075FA5ULL, 0x978997625F411938ULL, 0xD003ABEA70A95BA0ULL, 0x478199B3019B17C1ULL
        },
        {
            0x39043954A4CEE712ULL, 0x927A9AA706A8B54BULL, 0x7AD06A126A353E63ULL, 0xB35A5EB52CDEC0F1ULL, 
            0x99CCCCE2C6982F9EULL, 0x3DBE43EC7F8EC7CEULL, 0xCD6FF0B74584FE92ULL, 0x28C7918F5B983157ULL, 
            0x5D2AD362EE38C428ULL, 0x36B9B795163B4417ULL, 0x275F23BE9105F113ULL, 0xF54DEDA194153811ULL, 
            0x72F176031E8FB35AULL, 0x50B205E9115736EDULL, 0xC8F745ED3FDD9C64ULL, 0x08558CA0091329A7ULL, 
            0xC23F0DF92C69A036ULL, 0xD570CA14E2DCEB2FULL, 0x42053B9846B3E247ULL, 0xB91E2AC1A1884F20ULL, 
            0x973A129D410D0AD6ULL, 0x1EFD2FCCFC14258BULL, 0x69D60342575E6383ULL, 0x6C4BB8450681F8FFULL, 
            0xAA70C8EB69C3C796ULL, 0xB597190745A581D9ULL, 0x7107A3CF6C52C067ULL, 0x275BDF919123780FULL, 
            0x914FD1656337F2BBULL, 0x382626197E8CA395ULL, 0xFCCE54270F2AECD0ULL, 0xA7D917E06B17D3AAULL
        },
        {
            0xC8FBFDF0254324EAULL, 0x184DC637BDE37536ULL, 0x7FABA3D92D149A6FULL, 0x9FEE7202FA7FDF41ULL, 
            0x1917EA366F9DA4D9ULL, 0x334156F7DF7232A0ULL, 0xA03112D990820141ULL, 0x90BF357E788FA7C5ULL, 
            0x46D5A06EF50D4E6CULL, 0xF8833052F0182433ULL, 0x06AC819974453245ULL, 0x07BD1D619CC48FABULL, 
            0x4C8B20B90591B63EULL, 0xEF78CCD78FD6A2CAULL, 0x424A84728BDE166FULL, 0x34C87909DD7D3609ULL, 
            0x4292DA7425203060ULL, 0x46ABC82CB00EC5B1ULL, 0x1F9EAA36E96652EBULL, 0x239151C3C3155BCBULL, 
            0x4108AFD7CF0AA399ULL, 0x3DE9D36AF28D3820ULL, 0xB2D8A5F3249CCB1EULL, 0x840849F07EFA7A55ULL, 
            0x5BCA081F4074738FULL, 0x923A5395BDB350CEULL, 0xDAA1B2D8962AFBE5ULL, 0x13A067069BBD0797ULL, 
            0x1E83709AD184AD7AULL, 0x46EA476EAC3AF8E0ULL, 0xFFAA33D0AB6EDB4FULL, 0x9D349C6B89FA9B3EULL
        },
        {
            0x5ECBA7DB97DEB0DFULL, 0x14825D60F132F0B3ULL, 0x29284CCE94B0559FULL, 0x9C020DBAFEF9FCB7ULL, 
            0x9354B68C5DC3559AULL, 0x185987215AE6D9C9ULL, 0x8EEA55ADD676FD2EULL, 0x0A52342F35C5ECF1ULL, 
            0x4C00034B9365512AULL, 0xD331B81F87BB9C6DULL, 0x650DDEF68B8D0FBAULL, 0xFBB0A6094C264839ULL, 
            0x58D8A23927860630ULL, 0x2295EA5088999FB1ULL, 0xAA2DDB0F496858EDULL, 0x83C16E0C34686A34ULL, 
            0xABA54468122AEF96ULL, 0x2164531A8AA9F52BULL, 0xEF51056EDA9FD1A8ULL, 0xB032AE6CB7EF7554ULL, 
            0xCA686C2116FB7330ULL, 0xFEB16A02123A54AFULL, 0x38570926C6C1589CULL, 0x6E0FAFBA19D45122ULL, 
            0x6EB282E3F856E3F7ULL, 0x0BCFC2DC914DEC0FULL, 0xB95368B1F390690DULL, 0x02B269280871047CULL, 
            0x90D841C77D1165A7ULL, 0xC4689563A58566A9ULL, 0x11A7A4235AAAE642ULL, 0x1D71C92D79F0ED00ULL
        }
    },
    {
        {
            0xFF0DFE94E15D2D42ULL, 0x771616D846DC04F0ULL, 0x760AD07C4D118C46ULL, 0x7CE5AB3AF55EF02DULL, 
            0xF5B18FE918E6A630ULL, 0x92CE70120C6E684BULL, 0x75FC332F4E4112C0ULL, 0x1BA48327822AF60DULL, 
            0x55365D73AB5EF1B6ULL, 0x181CD00572038B35ULL, 0xCBB81FEE713D4428ULL, 0x9CDFD56D31AAE506ULL, 
            0x0DF74E625CB9EFDDULL, 0xA37F30B1B9CC9BA5ULL, 0x652A7E2BDDE289A1ULL, 0x2C4AB267A6BAC99AULL, 
            0x8419C479799EE186ULL, 0x104F581D7C091382ULL, 0x134A987ABF45C708ULL, 0x14653EFF24EABAF1ULL, 
            0x9FC991428EFCCC87ULL, 0xFB09773D52C1B089ULL, 0x9DBA90290CB7E796ULL, 0x61AF909D52A6EB7EULL, 
            0x612EE9CE83E8F9A0ULL, 0x88DA89A2F769628EULL, 0x4446038EC323F948ULL, 0x9966862687C67280ULL, 
            0x62ED7F147F9EEF51ULL, 0x7B11A4749EC34C71ULL, 0xBF45BFBA16EE9E74ULL, 0x8891D1C8421BCFD8ULL
        },
        {
            0x84EA35A9215035E9ULL, 0xCD33C20580FF4ED3ULL, 0x761FCC726D4AC8FEULL, 0xACF505A9C5CCD15BULL, 
            0xA7E40BF320ECB2F1ULL, 0x2EAC251E147055FAULL, 0xEDE67DF1D9923857ULL, 0xDAB4E75C0329FDC4ULL, 
            0x8976DD761AA14697ULL, 0xB2BACC4AFED86E64ULL, 0x075B1B97D6BDEFD7ULL, 0x41BB9186166BFAA2ULL, 
            0xD15DB8B6932B95F3ULL, 0x2BD88DECA9B16F52ULL, 0x26955C48BE6BDAF2ULL, 0x86C304C414DD90D3ULL, 
            0x74B9625AD8B53184ULL, 0xCE0698DEC2185F10ULL, 0xBDB887434442E1A6ULL, 0xD2DAFAC8BC9008D7ULL, 
            0xE378C8C590786860ULL, 0xF2C7FC9D9B9FBC4DULL, 0x95DE52F52E4334E5ULL, 0x21858868A44911ADULL, 
            0xCADEB9C6B410E7A0ULL, 0x909386CBD88332E9ULL, 0x65ADED09D46A3D81ULL, 0xFE4ED82ABECC764EULL, 
            0xA3E82F9975656025ULL, 0x5A79628CAB218FC2ULL, 0x2F016E9606D70715ULL, 0xE94EFAD670608799ULL
        },
        {
            0x56B8C894FC9F237BULL, 0xCA4D44D25FF323D4ULL, 0x9415510F5425F07FULL, 0x0253AA33BEC1C59AULL, 
            0x47302BB54F2F4706ULL, 0x94FA069538F9729AULL, 0x3CB1EFAE450812BCULL, 0x3A0F4A5F3E8640FAULL, 
            0x2D9AE265B575DA7EULL, 0x32C1E45A48828239ULL, 0x3BF4066CD1A1E79CULL, 0xF7D238486CD5B7DDULL, 
            0xBFBDCABF26838771ULL, 0xFACBC313589AC07AULL, 0xC53211C8A53BACF9ULL, 0x99BA32964221E30CULL, 
            0x89D59F8393F3229FULL, 0x908D99B12EC977B6ULL, 0x14EC0769353E3B9FULL, 0xACAAA613ADBE9265ULL, 
            0x7AFFEFC10631C2A8ULL, 0x306C62A609A756FCULL, 0x42A47F922CABA63DULL, 0xCF69A24DA00CFB76ULL, 
            0xCCF6F34C19492C87ULL, 0xD068AE32FCDE80E9ULL, 0x35A089A9025F21BEULL, 0x2DEF1743A4D34486ULL, 
            0x5AE2688524C4C599ULL, 0x22413285A5FEAADFULL, 0x18133A4B49FD2761ULL, 0xB09DCDE882C40D5BULL
        },
        {
            0x993BD26281CB0C68ULL, 0xA5E8D4F0D5D524A7ULL, 0xB3627993DEB16ABEULL, 0x36D3F909B21A96F7ULL, 
            0xF024727F63040D94ULL, 0x9B27F6AEAFE255BFULL, 0xC2D014F09BD3235BULL, 0x2ED6F493A1E1DFEEULL, 
            0xC409A613FDC5B43FULL, 0x1AA0D5FCAC2DF32AULL, 0xE69EDF63FC3F2888ULL, 0x1490B61744991A29ULL, 
            0x78B806D52A276F93ULL, 0xBBE1726B7672D401ULL, 0x56E8248AD3DDA571ULL, 0xDA17F8D68AD80E1AULL, 
            0xBBF996BA4CD6860EULL, 0xAB002DC3B41B4001ULL, 0xBA16D967940FAB56ULL, 0x2F848FFEEA1E656CULL, 
            0x1DD740803D13B3F6ULL, 0x746071DCB4459B13ULL, 0xB4F589DA4AAEED09ULL, 0x62C7460C8750C8B8ULL, 
            0x76BE8A8109FFDD9DULL, 0xCA1EA1F80FCFC013ULL, 0x7834C29366A3FEBDULL, 0x3FD731C5DF739D3FULL, 
            0x218E1FE95553514EULL, 0xE6A68C6AE9F22754ULL, 0x3529D3A3D068EACCULL, 0x4BCAA5DA55940D7CULL
        },
        {
            0x91D5B5912BD270DAULL, 0x951D39D34CEE016AULL, 0x29B49976CFCFA06CULL, 0xF59423DBB7EBEA12ULL, 
            0x012652C367516F2FULL, 0x505FE580BFB4D0E0ULL, 0x781C17046810620BULL, 0x3E6DC8E9F8A786FBULL, 
            0x776E4F8F6131E9C0ULL, 0xFBF3360954E0352FULL, 0x29434008F02C3DAAULL, 0x1094693FE96BC64FULL, 
            0x2A5D944567184E5EULL, 0x25147B7FED51E5FCULL, 0x8247F4349216458CULL, 0x0C9B7D924123E68DULL, 
            0x9E7E9973DC540417ULL, 0xCAFBE0F68A776B4AULL, 0x67CA0F6FA8AA2F7DULL, 0x80464C954BE0873FULL, 
            0x9DB7AE4B8BF47D7DULL, 0x413D502F9F8D2F97ULL, 0x9F1831415434A366ULL, 0x9032D22B0E6A1028ULL, 
            0x97AA363E0BA9C502ULL, 0x6B2E302193D90F26ULL, 0x64538D0DF8385384ULL, 0x2591DF3510640B0FULL, 
            0xB6412FC5B4490A5AULL, 0x684550490AAF0441ULL, 0x75CD6C4C73E1DF5AULL, 0xD21D70F2989EB740ULL
        },
        {
            0xB7B99891AF3959D3ULL, 0xCAC4FB8C71219A57ULL, 0x26F5293A87C3F97CULL, 0x29676FEACFF61D3FULL, 
            0x4DD1DDE5ACB0EDE3ULL, 0x82FFE5C33E23F7A1ULL, 0x91FB6A184463EC46ULL, 0xA2CBF12D7B315838ULL, 
            0x3F268B78B90B7787ULL, 0x85B45BD78986FF0AULL, 0x14953EEEDCCDD817ULL, 0x7E180C8FA4AB4535ULL, 
            0xAA01CCF6943927CEULL, 0x6D254D47B506072BULL, 0xAE19EF836D5238CBULL, 0xD90187ACC31ED711ULL, 
            0x49B04DAE27BE3D2BULL, 0x13EB05EC4F5FC8DBULL, 0xCCF4264C5BC6EDFDULL, 0xFEB5B60A858FE57AULL, 
            0xDF9EAF26EA87D37CULL, 0x097A96A2CDE39894ULL, 0xD137E8B2FA783012ULL, 0x89B5B0E8F5D66EC9ULL, 
            0x66A76D0FF945C00AULL, 0x7488503BE5420C40ULL, 0x6833CC319CB2DE90ULL, 0x8E019A24F6CFC524ULL, 
            0xA092C69178768AFEULL, 0xCC9C3DC778FAA039ULL, 0xEEF24B4CF463FC54ULL, 0x607562D50F065130ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseAConstants = {
    0xE5C196899C3C92BEULL,
    0xBCE3E259D9425C2AULL,
    0x056B6D9C8FF48E52ULL,
    0xE5C196899C3C92BEULL,
    0xBCE3E259D9425C2AULL,
    0x056B6D9C8FF48E52ULL,
    0x26B35EC1BF539CC0ULL,
    0x5683B9ECCAFC5FEAULL,
    0x81,
    0x57,
    0x28,
    0x45,
    0x24,
    0xEC,
    0x7E,
    0xF2
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseBSalts = {
    {
        {
            0x4139FEEDE9A68990ULL, 0x76FF7E7D7E4239B6ULL, 0xCE1CC214A95FB5BCULL, 0x03BAFF7EF25CACB3ULL, 
            0xC924DD0459CD2B0EULL, 0x230D43AAB0BBEF7BULL, 0xB8E8073ADCA8D1DAULL, 0x553C553DA4958D96ULL, 
            0x6E33866C698DC616ULL, 0x8E217B0C59F0808EULL, 0x545538A5FCD31B7BULL, 0x3F1B811C20B2BE6DULL, 
            0xA009638F28343460ULL, 0xAC6C821967096E19ULL, 0xD97E9FC60E6A556EULL, 0x73D86307B3E95E92ULL, 
            0xA2466E8131CBB4DEULL, 0x57ACEE75D8FA6521ULL, 0x111C942372788263ULL, 0xE76F9DCED5BFC97EULL, 
            0x79DA47371B4E76AFULL, 0x0F3411B88E59105EULL, 0x3C9BDFD20A029CCDULL, 0xD9B4914C2BB4C60DULL, 
            0x4B3D9CACB06D1EC2ULL, 0x196702B73E465E60ULL, 0x53767DAC8152E2E4ULL, 0x9909DB5F5DA9E03CULL, 
            0x6B69EC5E56485DD3ULL, 0x4CF02F306C2E5EECULL, 0xAD8D94EBCDF74C05ULL, 0xF18940771822F596ULL
        },
        {
            0x3DD221940E58493AULL, 0xB768649BDD4E116DULL, 0x07AACB45072C6C18ULL, 0x31C1EE4BD32C13B9ULL, 
            0x19C0B0F1B8D19B66ULL, 0x8A23CF329DE679DEULL, 0xE7145B60BFFB3557ULL, 0xCD988026E6686305ULL, 
            0xDFAF08B05C191CB4ULL, 0x2A34681102E12E70ULL, 0x60CDE4FC7A558D3BULL, 0x43991D4C7D523D43ULL, 
            0x38E3A0E17BA7F3F6ULL, 0x6FFA496C13089CF6ULL, 0xC34AD53E079A5E6EULL, 0x6FBB98FFA7D7AC2DULL, 
            0x52DF879BF808B629ULL, 0x65F12FAA590A7300ULL, 0xA7FD348B41F7FF83ULL, 0x952083D0AF301FD4ULL, 
            0xF721533DE43CBCC5ULL, 0xB51AE791EED87298ULL, 0xE7EA7CEB3E205044ULL, 0x8B2D49A7806499FBULL, 
            0x7AA3D7CBCCCC8FABULL, 0xB2033F33227FAE56ULL, 0xE12352CEEDCBD8BFULL, 0x60E25EED54173577ULL, 
            0xE3D11D867A7C90C8ULL, 0x9636E0F80ADD10F2ULL, 0xB6ACB5072ADC522EULL, 0x307960E19F02B145ULL
        },
        {
            0xDD49E96C4DF4AFE0ULL, 0x14CCFCE5B5B55FC5ULL, 0x43A880571DAA5A37ULL, 0x029B7961A8BB3018ULL, 
            0xA68AE7A616ABD13EULL, 0x072F86FCC9C064F9ULL, 0x2B30810BCDC563E1ULL, 0x72139957EF18C942ULL, 
            0x4F22A866F7D1FD8CULL, 0xBCD341AED1A6F077ULL, 0x18B7CE469655AC73ULL, 0x565773424A4DF393ULL, 
            0xB2B35EC30AEE477FULL, 0x8C17BADF74040CDBULL, 0x16746672489FA0ACULL, 0xCF8E153BF7D26851ULL, 
            0xE5FA8BC4FC07A8F5ULL, 0xDB799EA373AD5791ULL, 0x8ED68DC2B1B846CCULL, 0xCD16FBE8BE393EF2ULL, 
            0x7FB0CEADD0E0926EULL, 0xBE008257C27CFF88ULL, 0x28022D08675CB304ULL, 0x05741BAA3FB1FD08ULL, 
            0x0008DFD0505008C9ULL, 0xB9F923D2DF33127DULL, 0x54E7B2C646000EBEULL, 0xC32253400D311F03ULL, 
            0x84257471BF29411EULL, 0xFEC0EB34A1575253ULL, 0x6373C25E96336DD5ULL, 0x69F61DF1C61BE852ULL
        },
        {
            0xBC79B28E2E7EDDA8ULL, 0x3F083A93153500E2ULL, 0xB61CBFDFA7DD079BULL, 0x457A39EEB9300785ULL, 
            0xC3FCCA0086973BA0ULL, 0x70A8C15367D1F535ULL, 0x536D5EF2720D5918ULL, 0xD1DF4A28E6083D42ULL, 
            0xCFA31BA51B16150EULL, 0xEE85B68EE1F33A45ULL, 0xF06888BBDDB788DFULL, 0x57D0C1710E8A6672ULL, 
            0xE0630514A63D65CFULL, 0xF921AE6BB370048CULL, 0x8DFD02E9B4EDA9ADULL, 0x4A1A12EFA5AD7047ULL, 
            0xA8F27BDB9F3051EEULL, 0x5A42401208D48ED9ULL, 0xAA624BE8CC6B0876ULL, 0x58F2077B3C0ADF06ULL, 
            0xA541B1236FD4CF17ULL, 0x2F53AC67F7981EA7ULL, 0xFE7904F895FDD46BULL, 0x5E3EBBFAEE70DE75ULL, 
            0x92A034C6CF29EF6DULL, 0xE384798608075CE0ULL, 0xA188EB6F2B387F7BULL, 0x0828768368FAC5E6ULL, 
            0x784A5F51ABF1B39AULL, 0x666F155A69DE6458ULL, 0x65F525E946EBC80AULL, 0x444440D7F7EF0F5EULL
        },
        {
            0xD70A42D1F1A38D5DULL, 0x08750AEC1B8CA105ULL, 0x4D79F224D78CF934ULL, 0x19107FBE1F901EE7ULL, 
            0x5D9BA105A835767CULL, 0x3D732EA38B5826B2ULL, 0xBBE3B72C13D1021AULL, 0xF08863993AA2D7E2ULL, 
            0xA53B890737FCBC50ULL, 0x57E69201881A6DC6ULL, 0x01127AB10CA03F41ULL, 0xAC729408488F3614ULL, 
            0xDDDAB81E883A9B05ULL, 0xCCD675DDB2656AFFULL, 0xC321E1C891C70684ULL, 0x9F00BA98C90DAC84ULL, 
            0x8BC58ACBF82172BFULL, 0xA12E1F2E93C2651BULL, 0x268323F7C8919E4AULL, 0x3807AA4C961405B4ULL, 
            0x1B93558CE69805BBULL, 0xE35436493A77FBF7ULL, 0x7C3F190DE7AC8667ULL, 0x120651174F66FCFEULL, 
            0x2D6BB17576ECAAFEULL, 0xED714CA8843D98D4ULL, 0x98ADC90FEA326E1EULL, 0x9D94E7C856BC48EAULL, 
            0x47BFA612F78BA04CULL, 0xAAAC25D26EF7D5DAULL, 0x8111C08A76054E2CULL, 0x0F7EE455AB1F4F9AULL
        },
        {
            0xEE36A3395D015C8EULL, 0x973C7A92F8FC06E3ULL, 0xA5299923AD68A322ULL, 0xE050F1EF0F9944A7ULL, 
            0xBB043D3A72A81F64ULL, 0xBE9569091D792598ULL, 0xE196331B3727D3B9ULL, 0xB459B5274367CFD6ULL, 
            0x9C8232091B237F8FULL, 0xEA9BE4D6B939E139ULL, 0xBEEC96FC575E24C6ULL, 0x6628C0822241A33BULL, 
            0x08D93613A29ADB80ULL, 0x3C9433B55C8B0E9BULL, 0x0ED50707898C682DULL, 0x5B99E91CDB7519FAULL, 
            0x5FD9809568A3B9B5ULL, 0x5892201C71D3F55EULL, 0xF3BE66AA9001BC54ULL, 0x7F73C7F9509B0B10ULL, 
            0xF4D1E1277FB9C848ULL, 0xF818452FAF6F93FFULL, 0x91B65C16C909710CULL, 0xBD2CE84B7ACF473FULL, 
            0x09108D52DBD81B11ULL, 0xAC1838D5B4FAFCDBULL, 0x9CBEBA226C6D6E9FULL, 0x0A6B209D6B71D04FULL, 
            0xC45ACF0232B15F3EULL, 0x5AB80EEA457809EDULL, 0x961EF1B8DADACF2BULL, 0xDE7B3BDD93A60961ULL
        }
    },
    {
        {
            0xD8E78F22CA599F14ULL, 0xE27C109B9E9B1799ULL, 0xE7C5F4E9F65F2214ULL, 0x5776E00B38FEE66FULL, 
            0x779D8CE8A474E3E2ULL, 0xE94C2911148B4A9EULL, 0x84456108163C81FAULL, 0x511B76B2322BA269ULL, 
            0xEB3D520DE9E7B2A0ULL, 0x356E5B0264F7EF94ULL, 0x8C43E252A62E71BFULL, 0x22EA7B25EF76DE4CULL, 
            0xA05FE7AEAE459C4AULL, 0x4FC1C07BF32799ADULL, 0x154013C311352FC8ULL, 0xE81B1F88E4748971ULL, 
            0x754604BB715E4643ULL, 0x560924A87F2254D1ULL, 0xCE36D091B0BABB8CULL, 0x9AFC22730762BE0EULL, 
            0x113261E109ED3CB7ULL, 0x2B54D197C25B3E07ULL, 0x015F4BEED51E0838ULL, 0x773CE817AE900CF2ULL, 
            0x2C8651FDB9036AA0ULL, 0x67E2A2B3C8A21131ULL, 0x5EFBCD7B7B77E1CDULL, 0xD106612DA2DC9CA1ULL, 
            0x0BE8F2A4E0CEE42DULL, 0xFB6CA0C5EB0ACB9BULL, 0xF1911A3F5FE850F6ULL, 0x1D25E036509313AEULL
        },
        {
            0x2321FBDE0E3A9756ULL, 0x4A17574A9B657269ULL, 0xB7C924E2324B4FC6ULL, 0xEB5B08567625DB89ULL, 
            0xF82B4B5C8E4F2867ULL, 0x566DEF0108527F5BULL, 0xC9EB0F9A50860100ULL, 0xAB44C66D41C169C0ULL, 
            0x7D6A24CAA927C76AULL, 0xF9DCAF839B0265DCULL, 0xAA9AA8D6E0E851F4ULL, 0x7D4EC8FA5182F1C8ULL, 
            0x7B3A94C15CA20687ULL, 0x06DE443865D04A3EULL, 0xE79241F84C3863FDULL, 0x02E20A4AB396EAE8ULL, 
            0xC3168C48D8B05E90ULL, 0xBA8FD797020ECE14ULL, 0x59E0AF39F56A224CULL, 0xDD01AB9C2506E387ULL, 
            0xAA8374AD0903A84FULL, 0xD7CA15B082C118A8ULL, 0xBE71ED39EBFC30C3ULL, 0x6DEE1153759289FEULL, 
            0x764394100D1B51F5ULL, 0xAFDC3578803DAF95ULL, 0x427BD9C0F01DAC45ULL, 0xC79F33FACF15836AULL, 
            0x5805FCA89836B058ULL, 0x36D66C0044797DD1ULL, 0x51710E6E0CC60AA1ULL, 0x139A7205080C4A1FULL
        },
        {
            0x75A9172B2B0E8B86ULL, 0x3E98767FA71EBE40ULL, 0x27EC840A7E8E529FULL, 0x9940CBEA5D56E4B9ULL, 
            0x52E970830B6A7F41ULL, 0x6C29C2DA4F448DC6ULL, 0x76D77C2201BD1793ULL, 0x6EC7EB763CEA5079ULL, 
            0x717AE1C03FD3E5DDULL, 0x46D49E6C96C25A4EULL, 0x143BF3B7BFD03F01ULL, 0xB8C35D3ABD03F607ULL, 
            0x341F199513BD7294ULL, 0x33610AE44ED24286ULL, 0xD5F9740A9F240FA8ULL, 0x0003B2BF7D3AC048ULL, 
            0x286E5AFAEC87D318ULL, 0xECD7FFAE70DA238BULL, 0x38516203CA819766ULL, 0x684CE36913F40E6EULL, 
            0x11B791175AE8346DULL, 0x1E1C167C7D4D9C93ULL, 0xE169B397F6348562ULL, 0x8E275B9B2914A5AFULL, 
            0x14C2142A9C269B09ULL, 0x929106E4687A960BULL, 0xBB4D6EE99C3C6FA0ULL, 0x00FD567737154511ULL, 
            0x8A968A8AE983ECA9ULL, 0x16E2AAEDEEAAFFFBULL, 0xC02661D2735D8743ULL, 0x79E2C22AF7035335ULL
        },
        {
            0xA4EA088DB12948F3ULL, 0x70E5974E21C21F87ULL, 0x057CCC60B67F1B53ULL, 0x6ABDD38DA5829C9AULL, 
            0x7EF18432D53FB8DEULL, 0xC9D57CC8F44923B1ULL, 0xC679B59686ED82BEULL, 0x38EE6B65509CC05EULL, 
            0x23EA1C3D7A98B79EULL, 0xB576CAB489D63CD7ULL, 0xEA88222ED410B2A8ULL, 0x95F5DB8DF3CD42ACULL, 
            0x44A69A9ACC433D9CULL, 0x89E1E2AF23979A8FULL, 0xF2D7EC63913BB2FAULL, 0x76086995D004CB2BULL, 
            0xDD0441B279E625A0ULL, 0xEDAE5B566F7C24A6ULL, 0xAC381275D10C3375ULL, 0xB15F10933A124AECULL, 
            0x634D4FC7688243E8ULL, 0x803BD82D204478A2ULL, 0xE34F1ADA9974B13AULL, 0x6B6FF0797AE5CA97ULL, 
            0x06312EE338F2514FULL, 0x46F2D05288F66B96ULL, 0x6D95AE13EA69433BULL, 0x7ECF098A89241F1BULL, 
            0x0D5CD2A3CD7A32E8ULL, 0xC72D62BD53CCA66EULL, 0x75E5D9D65B1CF74BULL, 0xDA6B8B953FFDC505ULL
        },
        {
            0x612F848F454028D3ULL, 0xD8364A937BF74A3BULL, 0x47833EDBF3618D21ULL, 0xF273BCCA1C8606D1ULL, 
            0x0AE1564156FE0A9EULL, 0x96BB24A50EF00068ULL, 0xD8C09F64E206431BULL, 0xB761EB8579D09E88ULL, 
            0xDF5F1EAB078306EFULL, 0x96D3B102C2D6439AULL, 0xD3B62BBE24F53632ULL, 0x74338226DBF920FBULL, 
            0x135C45812B8FA7D7ULL, 0x805F28E11B420BE7ULL, 0x6A99E6A306C9D0AFULL, 0x639BE12507CD1CF2ULL, 
            0x360B40BA8C08FF35ULL, 0xFBDA903ED2F1ED78ULL, 0xB4A64CC8AC2603FBULL, 0x1F30E0C1B7F92A12ULL, 
            0xD3D7D7D2A0267BB2ULL, 0x4B1C272686E9FF90ULL, 0x457433E15FAED57AULL, 0x0D42E09AE45465D0ULL, 
            0xE49B9D9FB1D9AE05ULL, 0xE3AA772BD3A44DB6ULL, 0x7671B903A153BA05ULL, 0xBB8A166D73ECDA91ULL, 
            0x124EC3EE9FE01F9AULL, 0xC31B64F6E6232EB5ULL, 0xDB070FBE42CD68A2ULL, 0x02CE387D1A29B13FULL
        },
        {
            0x16D01A0B4BB87C80ULL, 0x41FE5C180034B210ULL, 0x07F37FA48CF41F10ULL, 0x8B81B8704515F65CULL, 
            0x5C2C16AD56CE6E93ULL, 0xF107E4A41F8FCA17ULL, 0xA82D1A66A6FE91B7ULL, 0x9062807C76DFF1E0ULL, 
            0xAAD597505D13F19CULL, 0xAEDDA9DE6306FBA8ULL, 0x82B00D1894011172ULL, 0x457858647F8CF3BDULL, 
            0xB9EC235341D8E8B3ULL, 0x7AB87D1A240AF4BEULL, 0xC660D44725F6527DULL, 0x45FB599E3960419DULL, 
            0x3971422BF90EEFD4ULL, 0x74DBE560A54E04E0ULL, 0x21BACBF6C0E87860ULL, 0xD2F7B370A9F9A001ULL, 
            0x72B3CE732D41187FULL, 0x9861C6A28BDDD772ULL, 0x6BC4120CAA080D60ULL, 0x907349713FA52F0CULL, 
            0x48E6B0241345D136ULL, 0x379FC0208C806E3CULL, 0x9E55AC19357EC980ULL, 0xC848C6C490F4BFABULL, 
            0xDB8B28D40822127BULL, 0xCAAEC39DE521E195ULL, 0x174730DD761AEE72ULL, 0x7C4FB8E3D7DE35BBULL
        }
    },
    {
        {
            0xD6EF69654CA5605CULL, 0x7A6D49E6F811EA8FULL, 0x64819526F6A02A9AULL, 0x789628B1D145AD9BULL, 
            0x3FC8594463467F0FULL, 0x5D5BCD85F17348EFULL, 0xDA0E311075B1C371ULL, 0xF335D3D2E0DD1F93ULL, 
            0x9871C11DCE3A1467ULL, 0x9250CF20AB337ADDULL, 0xAD118A1070DD51FFULL, 0x88D9E61278B5DDD2ULL, 
            0x5D8AD0E56865BD61ULL, 0xB70F00050EA63906ULL, 0x4A63BBBA304BCCBDULL, 0x68F43E9C7D11F4FCULL, 
            0x9CC61644481BC474ULL, 0x37BD2E84AC6E91CFULL, 0xD9039C6F280243A6ULL, 0x07984CA625390DE4ULL, 
            0xF72DE532A3502ECEULL, 0x628670FEA995ED42ULL, 0x496AD6D43EA927F5ULL, 0xF5E2D6425814A15FULL, 
            0x6DF8435B4C047C90ULL, 0x1E4E981A37972708ULL, 0x514A57776BD5E0E9ULL, 0xFAB9A60EC81421AEULL, 
            0x505837628C59AB8AULL, 0xB6B51D0BD1A2C68DULL, 0xEA55D3DAE5F4893CULL, 0x1E8D4B7300F83079ULL
        },
        {
            0x41986EC00A2F669DULL, 0xF8994C9EFDF9CC6EULL, 0x40989E3CD612C657ULL, 0xF380F9AB66F8A76EULL, 
            0x151ED8235223490BULL, 0xCC0C96F81CFD5BA7ULL, 0x29D5B94DFF125EFCULL, 0x5A3F25E511009C05ULL, 
            0xA2C2A90207FBDF1AULL, 0x98B265388594C60FULL, 0x0E34BC860AD1584EULL, 0x10CFA1AA7D630560ULL, 
            0x53BAA977BAC7000BULL, 0x25C064F5E92D003CULL, 0x7B10F244F23CDCCFULL, 0x88BED5C4881DBFF3ULL, 
            0xB70E719F00263EB5ULL, 0xE63CD96117141E81ULL, 0x969DE220DED7A62DULL, 0x6E0586A8E08A0BF4ULL, 
            0xB24FA8DFB4163697ULL, 0xF744C0F6D60FEE64ULL, 0xAC42F46D43E7D4A1ULL, 0x02C4F3EECD2B4D93ULL, 
            0xBAE2841D815CDA1EULL, 0x48223CF225B6B2C7ULL, 0x248579426A4FDC87ULL, 0x1715F4944F1DE9E8ULL, 
            0x03A842773FDB0935ULL, 0xE56CA13E383485ADULL, 0xCBD85597FBFBBCFAULL, 0x0D67BDC23D4F7B66ULL
        },
        {
            0xE0622E778EFCD03EULL, 0x0D009B693232C0EFULL, 0x29C81EF22A1E4100ULL, 0x9C9A4EEEC38304FAULL, 
            0x85454ADC1F1D5847ULL, 0xD23F91558B3ACD7BULL, 0x9E512C3E99C08F69ULL, 0xDBC6FB127318909AULL, 
            0x1E95F5C884A5301AULL, 0x8EDBA14FDE270FFAULL, 0x7449B4E3A0886C6AULL, 0x149A8E4C77ED4C9CULL, 
            0xD2F048D400F4B551ULL, 0xFAE84C1E0731A72BULL, 0x07E40595E8505A84ULL, 0x86A14FCC041C33B3ULL, 
            0xDD33CA0B05048CEBULL, 0xE79BED59D011DFC4ULL, 0x12FBD023DCFEA88AULL, 0x129C7B0EBED7A07AULL, 
            0xC60D80BACA1B0268ULL, 0x5CE0366908702869ULL, 0xF9908669469E1907ULL, 0x391555B311AED600ULL, 
            0x612350D4D725583FULL, 0x8EB232EC84DBBF75ULL, 0xCC90E5D6CE3F6FFAULL, 0x226AEE8B8C2AC792ULL, 
            0x88066D92DC0661A5ULL, 0x68FB839F00A66780ULL, 0xEAC8D01699C47E51ULL, 0x566EACD984AD0F32ULL
        },
        {
            0xBB3762C2BB7A09A8ULL, 0xE996FD0F3F6B0E1AULL, 0x4C78046556EE32ACULL, 0xDE1B7CC797A19D85ULL, 
            0x60357320D7475E53ULL, 0x5A4548DDAAE49FC3ULL, 0x7D1794298E4B68B0ULL, 0x809F083DBE4679D4ULL, 
            0x3F1B6FB4CFDD3763ULL, 0xC270333964FB0D14ULL, 0x2B0E1DF50FC2B41DULL, 0xF3F1771EF96BB90BULL, 
            0x67E27653C6E6685AULL, 0x28A59029B8C65744ULL, 0x0261F67FF279D2D4ULL, 0xC43CBDF05F74EF04ULL, 
            0x5C9246E3E4EE7778ULL, 0x1D3ADB20E7E4248AULL, 0x75F0AA57EBED4655ULL, 0x1BC7E772B1923052ULL, 
            0x7CEBE0364D0184C2ULL, 0x5986080C16784907ULL, 0x21FC9BB8B127D5C6ULL, 0x696F93DF83493344ULL, 
            0x64F1AD04AE9255AAULL, 0xDFB7CA024B19F09DULL, 0x874DC95C07C1A90BULL, 0x79CA9DFDC12EC9E0ULL, 
            0x5E07169698A2AB93ULL, 0xFF09168A7BA1D134ULL, 0x86F59CB02979DA2CULL, 0xAFFA45481C190EB5ULL
        },
        {
            0x10F06E240D54C2A2ULL, 0x724079A63E9EF586ULL, 0xEF1F578094F92FAFULL, 0x54FD230DB585945BULL, 
            0xF205143E379B728CULL, 0xB8F949066E8E5242ULL, 0x9F9BCFF34A360891ULL, 0xB48A017A3FC3B69DULL, 
            0x7BFECCFA2242634FULL, 0xE605AD2D0E71F058ULL, 0xD97C3B8503D33CBEULL, 0xD125D855FBCC207BULL, 
            0xA65165FA3BE1BF47ULL, 0xCB7DBCB1F5800316ULL, 0xEA6212D7C4C7D9B9ULL, 0x74A3E7C4B8C5EC9FULL, 
            0x52FD8BD9339DB31EULL, 0xBF9EC84B881B21F5ULL, 0x5204B73C31DD1AA0ULL, 0xA32912374A1D8667ULL, 
            0xE7CFF6CD11068A6DULL, 0xFEB4ED1465833E62ULL, 0x35A46AB168EB37A3ULL, 0x39536E04609240BFULL, 
            0xC80C60528EAFF7FAULL, 0x2C8B72019B21DBC2ULL, 0xBB5846195ED2A658ULL, 0x8E05427B25E4768AULL, 
            0x352E4AD90C4D9037ULL, 0x67B0A51D16424D3BULL, 0x7F23B4F5DA2E6FA0ULL, 0xB4E8CA58E33A66D4ULL
        },
        {
            0x4AD2F52C7D85732AULL, 0x8EFB53919D5D6959ULL, 0xBB6A6D10E1414F38ULL, 0x2E79C475E8AC0184ULL, 
            0xABDEE6613B2BDCE8ULL, 0xC48BA6D8C0AD2386ULL, 0x6AAFCE1345643FA5ULL, 0x4589FDEBB3E7FA55ULL, 
            0x328FB9A3ED944F96ULL, 0x2953EC7A19C727E3ULL, 0xB2AC83D7FB09FDEEULL, 0x9BC1802FDC863EE3ULL, 
            0xAD0F3999D58AED62ULL, 0xA2C93ED8264020D9ULL, 0xBFF4CF0E070047DFULL, 0x0569F3941F700D96ULL, 
            0x271981F78DC97CBEULL, 0x0E21358E9C302B70ULL, 0xE7FBF8C67EB5B3D9ULL, 0xBEE351F60083D3B1ULL, 
            0x1AB6612FCF225A3CULL, 0x0DC5AA322EFD62E0ULL, 0xDA4B504372A9051BULL, 0x05C9072A57BD24F8ULL, 
            0x1004603908D826DBULL, 0xFB3B7E1BE6B5E074ULL, 0x35EAB9FB62E83B74ULL, 0x217755480E1FDED2ULL, 
            0xE931A0FA4C206826ULL, 0x3568BD48676B7403ULL, 0xA994F3C59B897F39ULL, 0x5D1F67C26D13292CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseBConstants = {
    0x7B552DAD4B912871ULL,
    0x886860C54AF8714DULL,
    0xED8B4A1FFD2A49F4ULL,
    0x7B552DAD4B912871ULL,
    0x886860C54AF8714DULL,
    0xED8B4A1FFD2A49F4ULL,
    0xBE2A9CD2F9DC1DABULL,
    0xD58ACFA82728971DULL,
    0x3C,
    0x59,
    0x17,
    0xEF,
    0xF1,
    0x6A,
    0xA8,
    0x53
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseCSalts = {
    {
        {
            0xD3A6C0EAC4BCD7AEULL, 0x44BE8776FA1BCDFCULL, 0xE8AAED84602692AFULL, 0x1B904BC6E2B137A7ULL, 
            0x09E4569F32749A31ULL, 0xC6401CFD12BD37ECULL, 0xC2D89040F37CD63DULL, 0xB75382C8B4063A80ULL, 
            0xADE9B3CB027A58FCULL, 0x38AE813AB1366F74ULL, 0xF3F1D0CFAF3D7272ULL, 0x7C5D620899651AB5ULL, 
            0xDE722634AA48D65DULL, 0xA0D1BEB0DA49945AULL, 0x04E3E9719B6A49DDULL, 0xF4A10C3B23FAA908ULL, 
            0x3A1D344527403ED7ULL, 0x765168A129E32BBCULL, 0x44CB49753270BDEDULL, 0xEDB00A2996C4BCF7ULL, 
            0x2D896B9F1DCD5237ULL, 0x0FE2C38B953474B2ULL, 0x1D41D52CD61BEDFAULL, 0x7DBCD84EDE8A1F81ULL, 
            0x6DB67C13CF1193FEULL, 0x808C99E04BBB0021ULL, 0xA5B85DB86761DD25ULL, 0xD742B984E9B0961AULL, 
            0x2B33C76C6DB5A557ULL, 0xECB9B0F6C2E2966EULL, 0xF250789DE64542DFULL, 0xC4BA22037C86FFF2ULL
        },
        {
            0x9792153E483B6798ULL, 0xEC2BEAFABB29652BULL, 0x859DCC88F43DADF8ULL, 0x3461AF84600E6FB6ULL, 
            0xDA9B3B46BCD3AE07ULL, 0x438ACF6C899C4FB5ULL, 0x15F2764F2F153A56ULL, 0x2EA13037D14707A3ULL, 
            0x116EBFA52FF6DB8EULL, 0x577CAAF7B1F9D558ULL, 0x69F2EDB151929D6EULL, 0x9D53DF192B62F4B0ULL, 
            0x7540F86FA2B6B12AULL, 0x61E2E87A0DE64E5DULL, 0x7580042B1FB32D0EULL, 0x09EB3D67C559C887ULL, 
            0xFB12729211EE6A51ULL, 0xBAE8785B2A8043D8ULL, 0x5777D6B0A37EEAFCULL, 0xC96E471B16884E5CULL, 
            0xA284C7C5E724C741ULL, 0x3AA8D2B04B37C6C5ULL, 0x88D2CEE05A6A28F4ULL, 0xC343DCA11E735A66ULL, 
            0xAB0AE961A59FC445ULL, 0x6CA35304B4CD425FULL, 0x21A0A52894EE9C78ULL, 0x47E2B8F7F3C0FC3BULL, 
            0xAF3D6B8ED5B44C4BULL, 0x5331C86D47ADAC7AULL, 0xA6E1EC6729AB2B33ULL, 0x9D7749384D57F911ULL
        },
        {
            0x6AC0EC8860F52466ULL, 0x05365B87FC399940ULL, 0x58ADCF49D178BE17ULL, 0x1BDA9807D71AC0D4ULL, 
            0xA117BB9AC9E4FF99ULL, 0xCF27B61F315239FEULL, 0xB9AA9A62CEDE91ADULL, 0x92C851EBF03C397EULL, 
            0xD5FFBEF052ED254BULL, 0xCE972579240F91F4ULL, 0x9B583F77AD4240EBULL, 0x11D272D30DA86BC5ULL, 
            0x7D7ABE0E5BA80288ULL, 0xA142AF42D8029613ULL, 0xE7B147B2ED8939A8ULL, 0xE7B8CB0F485D5C0AULL, 
            0x493D201E1804B5ACULL, 0xE632373EF7E41E69ULL, 0x4BEE1FF74A92727EULL, 0x60772ADAA695C353ULL, 
            0xBA6DB5EE64DFE65BULL, 0x420D7D2C1777B706ULL, 0x265D3539071B0687ULL, 0x093C6877B518D0C8ULL, 
            0x425047D2412B2F06ULL, 0x7B1965607D402FCDULL, 0xA54C644BFD7E2F90ULL, 0xFF4F84C736D49B2FULL, 
            0x3AA6BCFF86D2FA34ULL, 0x7468D16FFC9845E0ULL, 0xF28FD7C29F88FBA5ULL, 0xC3B395281E8DAC93ULL
        },
        {
            0x94290D84AEE68515ULL, 0x3A8A3744DC371103ULL, 0xF9544A001A5CD7B7ULL, 0xECA52B20C6C00AF8ULL, 
            0x8568ACABA0E462ACULL, 0x7EB3E47904EABC84ULL, 0x51F2BA0DDF761E12ULL, 0x45F5F276BC455131ULL, 
            0x2E3054FAC41453C8ULL, 0xAA40CECC5DC56012ULL, 0x3406FD9E2C705107ULL, 0x4B968D17DCD9917BULL, 
            0x383FDDACEB486C27ULL, 0x4F6B492F9545F6A8ULL, 0x030C72E2652BB9F4ULL, 0xF41F3049848BF8EBULL, 
            0xCC121C0D688D1BD5ULL, 0xD371DADDFE7DD1B7ULL, 0xF6D078F1B030CE30ULL, 0x42EB0C93D4DDA527ULL, 
            0x3F227A11E501F8F9ULL, 0x16B3534437D21D35ULL, 0x1608E43997537DECULL, 0xDE2700050E39A735ULL, 
            0x29739AF346C2B146ULL, 0xF269622E7B568E45ULL, 0x202B26E1118E503CULL, 0x2D412EDBD012EFA4ULL, 
            0x639CC7EFEC76D9C3ULL, 0xFAAA28581BA9E3B6ULL, 0xB53BC51403E1D844ULL, 0xD53F1FCD46E44C64ULL
        },
        {
            0x6B2E1FBB4F1C8D85ULL, 0x2241974B5A02986AULL, 0x7265B706FC7805C8ULL, 0x39D10224A37F2B86ULL, 
            0xEC32B3F6E199B29AULL, 0x974927DFA25C9FD2ULL, 0x479A8D2AB18D91F8ULL, 0x8C285D33860B444BULL, 
            0x90912ACDDE544139ULL, 0x00BA20B1680DA68EULL, 0xB784E0CCE59BD863ULL, 0x48C63DA4F495918FULL, 
            0xC790C6782DC3C35FULL, 0xC8B8BF753A69D7E7ULL, 0xDA957B13A5C9097CULL, 0x923CA3A304932A3DULL, 
            0x646DDBA282912313ULL, 0x48A8E58AFB585132ULL, 0x181E9A24B5FF9AACULL, 0x97028B801D0DBFABULL, 
            0xCDA3393CB5D4D48CULL, 0xAEBFDA78DDC49138ULL, 0x9F31E5060A581F51ULL, 0x2BAE79D5483697C8ULL, 
            0xAF77E3317BDA4000ULL, 0xDC31DA5EECE61AB4ULL, 0xBE869EE7D640D747ULL, 0x8DFEA6A1CB63CAC1ULL, 
            0x53CFDBA145C8220AULL, 0x5081F3AD78695473ULL, 0x9F72ABA888A8E804ULL, 0x8906B9D36EC01A86ULL
        },
        {
            0xEAD3F2A697694CF2ULL, 0xD5CAFA4B72355922ULL, 0x10554166E3D9C7FEULL, 0xF11853E0134F15B9ULL, 
            0x3B2D472EB7F95B5FULL, 0x33AF9EE445227B53ULL, 0xC30C03A911178CD7ULL, 0x0D2B6B82713353F5ULL, 
            0x675D5348C004AC3BULL, 0x7A7E2BEF000FD4E5ULL, 0x651ED61C67F66DFFULL, 0x141450D3E03D56B6ULL, 
            0x9A38A30FFC3C26BBULL, 0x03FB143A5CB0F718ULL, 0x35142FFB2289E981ULL, 0x010198C911879B0FULL, 
            0x947BFA77E793BAECULL, 0x67A163FA8CB03387ULL, 0x474F2F0AD6462E25ULL, 0x5FDAF6BDC64045BAULL, 
            0x2B0FE937B14F99D4ULL, 0xBFE013A50B663BC4ULL, 0x0B3ECF6C828D1394ULL, 0xF1650D113BE73EB8ULL, 
            0x02C6D2C4147E8C0EULL, 0x5558DCB5C20CADF3ULL, 0x0E1595164E4076A4ULL, 0xA2A99D72521FAD09ULL, 
            0x6CEEEB51211E5F02ULL, 0x4066A5A21F75D837ULL, 0x9FBB4CE3A9FA2F3FULL, 0x30530CA2B38BE12FULL
        }
    },
    {
        {
            0x2EC7553A70BE7ADBULL, 0x7A7D91B75BA17AFBULL, 0x829DCF60E2D70781ULL, 0xA7D013DD91DD5297ULL, 
            0x3A0CBB42EBF32FD2ULL, 0x3AA6355DB47956E0ULL, 0x4685861660F3B28FULL, 0xC18CE76E47E74D1BULL, 
            0x29B3CADCFDC3BB58ULL, 0xB7555B41B6C98E2FULL, 0x0470FEE6F66D2760ULL, 0x576DF0262B631F22ULL, 
            0xD30021ED634C8F58ULL, 0x774978BB0A352308ULL, 0x7230852FAE022CE9ULL, 0x0FB19F99117889F8ULL, 
            0x3F5CD0E99D082ED9ULL, 0x04A34FBFB197CE27ULL, 0x2FAD25D4C503E146ULL, 0x8865F3EB3ADEAE2EULL, 
            0x9D4BFE4560707B21ULL, 0xCB1923F67D250E0BULL, 0xC27B88DD024CC833ULL, 0xDB14E8423124ED40ULL, 
            0xB9276DEF8D23898EULL, 0x4801D7B0CA1E9544ULL, 0xD5865975C16EB660ULL, 0xD99E5046557C7497ULL, 
            0xC6761178CA372BA5ULL, 0x662DAECF418FA5BBULL, 0x07B440B2176348D4ULL, 0xBBF347F949B6770DULL
        },
        {
            0x187AFA808093E187ULL, 0x0B487ABD2F189557ULL, 0xD8D0AF70BDF9D5CAULL, 0x66CB21ACAECB628FULL, 
            0xADE5F947564CE080ULL, 0x32A0726CFD56CC34ULL, 0x6312861CDF7C5015ULL, 0x7F5E29942584E7DCULL, 
            0x87FA1029F7D11E65ULL, 0x5F573C2B6E773849ULL, 0xEA8A05C93007ED0DULL, 0xCFA0431EB162FE8AULL, 
            0xFDAAA4D2C5D1582DULL, 0xB2FD24F59E1F4CE5ULL, 0x6117E6F337500829ULL, 0x1F5CA0776CFCCD54ULL, 
            0xA210D2768D28014FULL, 0xDD3E03CD35018C42ULL, 0xB5B03224827C275CULL, 0x7751CB1775159A32ULL, 
            0xF5234D469A237EDFULL, 0xFF0E291A5BE4B703ULL, 0x70EABBA6ABF6224BULL, 0xB7A561B6C8812F6BULL, 
            0x1239CB429050271DULL, 0xAC28FE768B36136AULL, 0x2B8BDECB8BCC6988ULL, 0x868623CAC8A91259ULL, 
            0xED231D15713F41ACULL, 0x3B222F3BC6B0275FULL, 0x88673E9AF3F7C952ULL, 0xF51629B0EA5D9220ULL
        },
        {
            0x8F1DC701687E4693ULL, 0x1B8EE47B04B84BDDULL, 0x4B57B76F907F6B1DULL, 0x787FB7A37B3F37ECULL, 
            0x28B37FC787FC505CULL, 0x905161B99E80FBD7ULL, 0x76B1624A6CE91504ULL, 0xD5EAB6DBE8BD4693ULL, 
            0x5B268DA4DE0236DCULL, 0x9B091E4C7DAB9A29ULL, 0xEC62A003C639813AULL, 0x8F2952F47814CA3DULL, 
            0x14BF429F968BD0A8ULL, 0xF9CE0973E097C303ULL, 0x91FE5257A970EADAULL, 0x5760E85C6439F4B7ULL, 
            0xE61DF99BA8E5F84AULL, 0x0A2572BB6BEC6A02ULL, 0xD6810DAF0553C623ULL, 0xCF4F996345019028ULL, 
            0xB595B8EC1ED75206ULL, 0xEE4958098B51D2DCULL, 0x745E8E030318A8F2ULL, 0xB73FB3F7A38C0019ULL, 
            0xB58E8E52AA48B821ULL, 0x5C23DD09071A35A9ULL, 0xEAA66C98FBCDAF4AULL, 0x960D27D5ADB4E66EULL, 
            0xAB64409177B35EABULL, 0xCFC7AB5C573BA138ULL, 0xCD0448A2C3EF8C25ULL, 0xAFC14F94E5BF4501ULL
        },
        {
            0x9A7E734B0CF7D723ULL, 0x2B77783133F33AE1ULL, 0x26053B479EFE8A43ULL, 0x2AB24A7496C25E6FULL, 
            0x6B16838AA4CD4992ULL, 0x35E6384AE94D3F38ULL, 0xB31246D0474C8DEDULL, 0x06961AD024A3D90AULL, 
            0x0F5F3C2A10FB95E6ULL, 0xA516EE5CA1FAC1E3ULL, 0x006CD179A18946D8ULL, 0xA128975D17689CB1ULL, 
            0x70248788C9B76763ULL, 0x85F7BC9099791ECBULL, 0x78ED0374B71B1F6EULL, 0x329061B578B0E6F3ULL, 
            0x2FC8C4A102DBCA93ULL, 0xD5D040DF6157C811ULL, 0xF45CEE0CA2BCC09EULL, 0x0A4ED7A6E1234196ULL, 
            0xA15CEB5D8961B206ULL, 0x85AF15D7A875F0D8ULL, 0xA4E2DA454409893FULL, 0x6211F61BE7ABF379ULL, 
            0x06338356C66919D9ULL, 0xB45944DFB85EC615ULL, 0xFFEB6A765DD2A506ULL, 0x73DC93F1935B8F6CULL, 
            0xD3A79E4972A2DB7DULL, 0xC08CD217E937AC36ULL, 0x665F38B5A66E393AULL, 0xDE2E53F14CAE9F51ULL
        },
        {
            0x97FEE219D4C19B79ULL, 0x717E924BAAA32154ULL, 0x0F9A50EA0500B89EULL, 0xD5A984F16B65BEEFULL, 
            0x3E75B30B310E131EULL, 0x2FCEAFC2832E0F17ULL, 0x2B45470F2B4883C0ULL, 0x35CDEBA0BF7929FCULL, 
            0x8551F00B9F2E9ADBULL, 0x4F36BFD6DD08A4FFULL, 0xB38791E51CFCE610ULL, 0xE7E5EB50AAA66A36ULL, 
            0x3B1720FF8AF4D803ULL, 0x6FCABB8A6D7F8F00ULL, 0xDAD8F7C90D26A391ULL, 0xD452E1C770ACCCB5ULL, 
            0x538BE0BD26194BAAULL, 0xBB031B416DDD5BCEULL, 0x5EA33B920B2A73FBULL, 0x5C22915A90A03033ULL, 
            0x035F2A27144B5C7FULL, 0x096B95148D5ECFFEULL, 0x2A66336492B1F432ULL, 0x6CD8C1BC85EA5BFFULL, 
            0x1DE81298256A0B5FULL, 0x64FAC237743BA96FULL, 0x780037F889C0BBF8ULL, 0x9BE01C0B8E10BDA0ULL, 
            0x414215EB89D6DD73ULL, 0xACE6A087B630223BULL, 0x4587038A93B74D8AULL, 0x7B0FAC6B95B09DFBULL
        },
        {
            0xCCE284B1D90A5D68ULL, 0xCBA21D8F9DD517B8ULL, 0xC537A9EC6D82C326ULL, 0xA9CFB7AAE3D6FAA2ULL, 
            0x03C89E55506CB4ADULL, 0xC028260B41FF7E7EULL, 0xAA91886B28C1ED6EULL, 0x3D490D4E3C84F0E1ULL, 
            0x453B05A678DB580EULL, 0xEE2681E9494915E1ULL, 0xB5D7FF6FB57A337BULL, 0x689F001521F53064ULL, 
            0xF2553DCFEBEB8203ULL, 0xEA6117C607F21902ULL, 0x03F0C5F64E827089ULL, 0x6F1C184B36ECBABAULL, 
            0x2CB2718741E8DC23ULL, 0x5AF26B3B836F8D46ULL, 0x774515BF837E7A36ULL, 0x28BDF1BC94E8A52DULL, 
            0xE208B2EF0F4D59BEULL, 0xAC481FA2566A8051ULL, 0x50CD408777178B65ULL, 0x5C958C8135FABFF3ULL, 
            0x1921FD4EBB51F059ULL, 0x6186A9805B7E043CULL, 0x21336F7F1C9BDDC4ULL, 0xF727D7B8D0CE9BC3ULL, 
            0xBC93D4CED3BABA5AULL, 0x1E22F5E0056ED801ULL, 0x279705C8D3FC24FDULL, 0xFD7AA788BBCDD0DDULL
        }
    },
    {
        {
            0x8FA2DDDA3EAB3A87ULL, 0xE6AD4C79A0D1C8D2ULL, 0x4A87AC0016541FA7ULL, 0x85D3B4152575B1D7ULL, 
            0x08862419DD3A90E5ULL, 0x7EDACEB4002B50A9ULL, 0x49AB02F2E86FC1D8ULL, 0x23F0B2A224E4CADAULL, 
            0x9D4842F3903C61CDULL, 0xFCE5D65BBF6AF04FULL, 0x8031DC6B802E3B5FULL, 0x778D8F8944AF5F5BULL, 
            0x6CCEFB063E950F08ULL, 0x2F630FD8F90269AAULL, 0x4BC751153D37FB29ULL, 0x7380D7D2DB0471F9ULL, 
            0x398F8FBD63301F05ULL, 0xA821EB8BCB9E0B3BULL, 0xC01888B4F194ACD6ULL, 0x9885447D6ABF42A9ULL, 
            0x99420AEE5881D5BAULL, 0x031E3A598F26A072ULL, 0x383E1C3A6027C8EFULL, 0xB9C261892BA682EFULL, 
            0xA0BC1834BDE7205EULL, 0x46BE1D6F3BC18CC4ULL, 0xEA5C36A5A06C180DULL, 0xAB8AAEF268B46A3AULL, 
            0x2C2CCCC6509D7FBDULL, 0x89DFC80CA4B09DB6ULL, 0x7959023CA46753D6ULL, 0xE077C3424CB9E1E1ULL
        },
        {
            0xC4A1B1A20DFA6300ULL, 0x1BE095F09FCC37D3ULL, 0x0453D2A98AE9402BULL, 0x9582AFDB33A22731ULL, 
            0xC197780B1258FEE7ULL, 0xD50EE4832E0B0CADULL, 0xD11B5368FFC1F151ULL, 0x8C70A3ED27247A0BULL, 
            0x402F8DFE5BED20CDULL, 0xFBAC79A4602D7826ULL, 0xE782A71325FCCE79ULL, 0xD2097D9280156737ULL, 
            0xC19D5649CCE7D54DULL, 0x564013BC74B6E6B0ULL, 0x75A3E3971746F4EFULL, 0xEEF9E868D9FDA9A5ULL, 
            0x8D99DC714C6C1E83ULL, 0x6CBAF2014457DEB2ULL, 0x7F762C38739ADEFAULL, 0x05D99C3AB8D4DE12ULL, 
            0xE474D177773F0E4EULL, 0x37645D1311225FCCULL, 0x7F86A2CBCF898447ULL, 0xA6C853B2797CEDD6ULL, 
            0xB2D7EF30A0FB3D50ULL, 0xC87769BBF36B22FEULL, 0x4F1B3AA87A5CC0AEULL, 0x167BD80B00B655ECULL, 
            0xACA6E941BFC763FAULL, 0x0C0C0E01DF101F78ULL, 0x48B9B329DE24135BULL, 0x9903662FD9E949C1ULL
        },
        {
            0x4970D0D4173A3B7CULL, 0x66936B51106CFF16ULL, 0xBFA1982804C1088CULL, 0x9D55CDBEDE509040ULL, 
            0x96F53535E0FF0546ULL, 0xE9452D63542963EAULL, 0x97F4E9CA0AF234C1ULL, 0x9BAE6A41C0D6BF00ULL, 
            0x5FD39D35BEBEF437ULL, 0x9BC13ACB832417A1ULL, 0xC6305EA1EAFDE19BULL, 0xF0FC7482624E7B47ULL, 
            0xD9FB06651B2BD2F5ULL, 0x7BF8513ACCE01F80ULL, 0x7B6858B29F8B871FULL, 0x6D4BCDAA3C27BBF8ULL, 
            0x49971FA8D0337501ULL, 0xDCFD57A4E8F9BBEFULL, 0xDA3EEC724D662ECDULL, 0xA35347194BE9ED60ULL, 
            0x4256AFC73AE26900ULL, 0xD3F3144A5BAB178BULL, 0x9CB9440D7A3AB823ULL, 0xECE5C8E26F8E3932ULL, 
            0xA2B2E6812FE86149ULL, 0x15073C40C40334B3ULL, 0x554417E5EDA197FAULL, 0x1ADA022FC871667CULL, 
            0x1BCF97A57C6F9E47ULL, 0x68A33C174E5D0DFDULL, 0xBE51EC2A6F4912CCULL, 0x2114AE8A31DC2C2EULL
        },
        {
            0xC3639736D372BF1BULL, 0xAD6DF6F42EAE88A9ULL, 0xEF3CE1EB3214F3CDULL, 0x9BE3F4E721A73BDAULL, 
            0x6FF57C0BC3D2AEFCULL, 0x0EFAA25F0F2C60F0ULL, 0xB45E19C1FAFA70DAULL, 0xCF7D30943C6FC16CULL, 
            0x33BA8E05EEC77E23ULL, 0xE5C969BA030B1A22ULL, 0x516FD753A3C09D8CULL, 0x9BE9D2535ED418A4ULL, 
            0xAA4A59E93C44F1A9ULL, 0x7B61BE470DC211BFULL, 0xEAD7A7B253948DE4ULL, 0x5DFD7A8B58FC76A9ULL, 
            0x311ABEB8C7F51D7DULL, 0x6CC93940DB9E159AULL, 0xDCA9109A96EF3646ULL, 0xC1F8F46DE446F654ULL, 
            0x2D8C14AFC0034412ULL, 0x0D2C93FCFDDC182CULL, 0x0FD8D1F4030978A9ULL, 0x35D56B68F476F654ULL, 
            0x8BBE23931F2A2ECEULL, 0xFABC0399BD987406ULL, 0x1A637C9583051278ULL, 0x5457912773124744ULL, 
            0xDDCF852D08AA6B3AULL, 0x305487942F0256C4ULL, 0xF066CA1D0B53D754ULL, 0xF13530934EEF15B2ULL
        },
        {
            0x634F790467A50F27ULL, 0xDD95647859E47373ULL, 0xE6B5DC46E8E06580ULL, 0x34C552B31A8EF802ULL, 
            0x369DDFF69BFE14F7ULL, 0x142D0F9F5537B613ULL, 0xCFA9CDAA439F36EAULL, 0x68494A558A6B444DULL, 
            0x20B0795DCF91FD6DULL, 0x67EDBB07A79E521FULL, 0xB6F43EB8C911600CULL, 0x19EB1B42EF8D711DULL, 
            0x9FD247CF544308FFULL, 0x47FC3DE87C6DA46DULL, 0x6D26DE07E95427BAULL, 0xC05A5423BA67D50DULL, 
            0xCFAA8EBD7470FF2EULL, 0x06672AAE46FA9C3DULL, 0x703040E0BB260CADULL, 0x7B48D5D83827A9A0ULL, 
            0x6E965CBF0EAC51EEULL, 0xC5B4F00351C14856ULL, 0xA24B276DEEB00B95ULL, 0x33F54B53FECD7C20ULL, 
            0x604E51A304AB3905ULL, 0xBA44412408639FD6ULL, 0xDDCDFF48CBFAE7CCULL, 0x0051C933610D4EDEULL, 
            0xACC45BF8E38828D7ULL, 0x2069F74DC8448E92ULL, 0x8270E37EF1460652ULL, 0xB8783685E039C69DULL
        },
        {
            0x2534B4CF9FB03422ULL, 0xEF2B7A1728DDA238ULL, 0xD8859B79441961C5ULL, 0x101ACA5C01A067A2ULL, 
            0xE63BAF6DAEAFCE63ULL, 0xAAB9D7080689801EULL, 0x0FDA74A4634B6823ULL, 0x13DAB278824F6F71ULL, 
            0x2DE72DAA2FF75FF2ULL, 0x0F79C2B3EB6C730CULL, 0x0FE1BA9A8BA1B92BULL, 0xFA53843411665A26ULL, 
            0xA2957D10732AD35DULL, 0x8754E1A5C1DD10CDULL, 0xBD4D5BD22F2CF9CBULL, 0x53471432E330E974ULL, 
            0x7B2C5C9A7A54DE3FULL, 0x15D6D06459CB587FULL, 0xAEF9CAA7E6233D57ULL, 0x5D5EAF77C3E25BBEULL, 
            0x8E81A2F7849D6512ULL, 0xC4E5DEF93FD20BD7ULL, 0x815457C8D74888ABULL, 0x01AEC527D8948E72ULL, 
            0x37B3556426F8EC4FULL, 0xCF07771DAB37B3F8ULL, 0xD874F0727226AF74ULL, 0xC9169C16B87ADE91ULL, 
            0x651D684F879944F3ULL, 0x930976BBCB6ED98FULL, 0xACE2480F8C39F875ULL, 0x689EC881F7AE74D8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseCConstants = {
    0x67A5944ADC0C9970ULL,
    0xBA7E40467B884E97ULL,
    0x1E847910454BE86DULL,
    0x67A5944ADC0C9970ULL,
    0xBA7E40467B884E97ULL,
    0x1E847910454BE86DULL,
    0x533C592562571BF0ULL,
    0x25C3830214B46756ULL,
    0x39,
    0x0F,
    0x22,
    0xD7,
    0xB9,
    0xEF,
    0xD2,
    0xF7
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseDSalts = {
    {
        {
            0xF4512B56517C9A92ULL, 0x9F4B05408A08CCD1ULL, 0xEC154049A8C51A82ULL, 0x314FA9EF2072F0ECULL, 
            0x199BDD6C8A57DDD2ULL, 0xE1B49E71F88D2677ULL, 0xAB15C95657C5EFF9ULL, 0xE1DD08B641B7ABBDULL, 
            0xC357EA5B01F788C9ULL, 0xF96A23D4B2B3C8D9ULL, 0x10637B8234A602D8ULL, 0xD57F97B4507F145CULL, 
            0x653E81CD89AC870DULL, 0x701B2BC3CBBD35A0ULL, 0x89EC7A7144FDA313ULL, 0xBB56D2D0CE38D5C6ULL, 
            0x513A3CCCD19612D7ULL, 0x84B50A6B02F52078ULL, 0x55A0D6A48AA7F068ULL, 0xB830C4BA42920B00ULL, 
            0xA13DBCA905EE148CULL, 0x37D23F75E2B47922ULL, 0x366989FA30CDE9F3ULL, 0x74BBF3E3D5CF104FULL, 
            0xEC496AB8134D703FULL, 0x38FE168FEA3DFD0EULL, 0x4502BF581AD74DCBULL, 0x3050C6DAC6FD0B3AULL, 
            0x5B3A6A1AE8740503ULL, 0xC8ECA4ACC94490DEULL, 0x1C977D3A38527471ULL, 0x16820130A3BBD8F7ULL
        },
        {
            0xC27EEDECED53FB36ULL, 0xD27FAB38670B1AB9ULL, 0x9F685C0E2DE0CEA7ULL, 0x8C72BE84CA9AD4D9ULL, 
            0x1454320D8AF3EA2EULL, 0xB306FE3786352749ULL, 0x834676893E20FF7CULL, 0x9C3E53F9E0F41672ULL, 
            0xB094B800DC3BE779ULL, 0x75CB73B6CFFDB578ULL, 0x38489C6787C9B08AULL, 0xDCEDDBB7BBF83942ULL, 
            0xF916AF6204D29F32ULL, 0xB259901478394A29ULL, 0x9A93FC6A68ECC00CULL, 0xAD21A4BD928B0183ULL, 
            0x012C70D307695E55ULL, 0x3E94211961ACD480ULL, 0x82CE5B50AEB98F35ULL, 0x7EC6ED61CF9AA20AULL, 
            0xFA8B02306A1C0D42ULL, 0x2311C46012F61368ULL, 0x5A0672EE8427A2C7ULL, 0xA589E3D128F3C8C2ULL, 
            0x6E482FEE4220B24BULL, 0x846D04DFB2288324ULL, 0xB040DCF333779AF7ULL, 0x559A0A2FF3A953C4ULL, 
            0x13B5246F5AD46199ULL, 0x4DCD2F6DECC5ECEDULL, 0x305751856AF19D69ULL, 0xBF006964FB38D32DULL
        },
        {
            0x2A810C1F5D18673EULL, 0xA9511BDA6AC8D3F2ULL, 0x35A30BE0F6A7B16AULL, 0x9DAD45BB95BC8446ULL, 
            0x89BA505734F07107ULL, 0xA75940C8B5E9B587ULL, 0x051B4EEC5B284F4BULL, 0xEE7652B0D11A0D0BULL, 
            0xF2CCFAC0B8821465ULL, 0xEAD293E90471E2D1ULL, 0xEB925CBAEF1CD05EULL, 0x0EC9B08E04670E63ULL, 
            0x4B0F2552F18F6370ULL, 0x69BF1CF4B13EFDCFULL, 0x58C65E81FAC1BB1DULL, 0x7A757823A4F8CA62ULL, 
            0x0F766A1D317248A6ULL, 0x410954673D598F5DULL, 0x03B1C9A96B9A0037ULL, 0x868D0063383C3754ULL, 
            0x2C7C8AA55324AA2EULL, 0x4D57E08D4798CE77ULL, 0x66A4C2EF50E46183ULL, 0x77BDFBAA409B9AD1ULL, 
            0xEAD9592349B8C7CFULL, 0x7A636B95E9E8227AULL, 0xA04B8B96204C3D87ULL, 0x92A669C1DC344959ULL, 
            0xF14D01D42DA1CED9ULL, 0xF4E662106ED135C6ULL, 0x45B658CB3A3713DDULL, 0x338320100B7A5710ULL
        },
        {
            0x6ABC098DD348785BULL, 0x31B8E53671D53DF7ULL, 0xA10E83372CD2B5B5ULL, 0x461FA6E0ABA5F6DDULL, 
            0x7E1E3C25D1C2E579ULL, 0xBB6972C8CC58C478ULL, 0xDE08E5042EE78183ULL, 0xF943297ABBD62D81ULL, 
            0x7B7FBFE70664D479ULL, 0x233A07231DA97AF2ULL, 0xB0A80875138A8F1BULL, 0x6AA04D10F0D44DC4ULL, 
            0x1412D0B8303154FAULL, 0x4D988561E70094EFULL, 0x12FC86E4EAF7E2D9ULL, 0x3512FB51D726BDF6ULL, 
            0x4E18D643C5E91616ULL, 0xFBC731CA2F504237ULL, 0x1BDCED5007846CA3ULL, 0x30F07F3D06A83D18ULL, 
            0x668D19B186D6ADA8ULL, 0xF1F934EB467CB16CULL, 0xFBEE053145625488ULL, 0x76C722E5CEC4D918ULL, 
            0x9C9F15803FDACB39ULL, 0x81377F9B469C52D7ULL, 0xF3D2110AA35CA623ULL, 0xF511951E48AACCB9ULL, 
            0x32F93AB658B37DE9ULL, 0x6B2F267BDAEB243EULL, 0x6642FFCFDD7585F2ULL, 0xD77A8234047D2AA5ULL
        },
        {
            0xB5D291B3F358968DULL, 0x5FEC6497EAD03459ULL, 0xC97F8E2E14E56D61ULL, 0x7B958F8CFEC67C62ULL, 
            0xBEC52758F6E8C919ULL, 0x7E10B48ED16C67FFULL, 0xE33CEA9210BDE927ULL, 0xB3E9B918C5BDDF20ULL, 
            0xF6B32BE40AB21D9AULL, 0x12B715281FADE53EULL, 0x0FBBD4C36402E62EULL, 0x5FFE6EAA9CF6B60DULL, 
            0x64A6A6F652F52DE5ULL, 0xDACE96C69D97A5DBULL, 0x21D8DD136646F3C6ULL, 0xF16AA1DC31F522A1ULL, 
            0xBD49BA77408A7E43ULL, 0xC7387232F355F380ULL, 0x9190D77ADDCDF8C4ULL, 0xC237F6EFDE1EDF1AULL, 
            0xA5C090FF4F91B529ULL, 0xCD9C561D2AF9AA2AULL, 0x58ED916304281422ULL, 0x156F2485D5472ED6ULL, 
            0xF8CA8DEE93A41DFDULL, 0x6E3BF51F63E87B95ULL, 0x01DC3A4DAAEDDD4AULL, 0x022577B48A7EFE92ULL, 
            0xBDA27F60C4746CC1ULL, 0x3F5C8788266E9F11ULL, 0x08812BE0128DAFFDULL, 0x83AEA1B32AB80861ULL
        },
        {
            0x10EE0DFBB9A31722ULL, 0x5F2E478D216C89A8ULL, 0x72898797A5B32D2EULL, 0xD2647E3FC50B7205ULL, 
            0x98CA3209C8D09D84ULL, 0xBB941B4082C44D1CULL, 0xEF83014ABC404A1CULL, 0x3776D4827ABF13C9ULL, 
            0x6B8BA872DFD2B1D2ULL, 0x989F1B8A38DDBA8AULL, 0x5DE4956008966B73ULL, 0xB296BEA8BB152E0FULL, 
            0x462F028C0C6CDF3AULL, 0x5AB53FC109E04D64ULL, 0x29565CBE4FB1287FULL, 0x9C1DE6B94BE34CFFULL, 
            0x1A77203A2447EA2FULL, 0x69D1A084FED7BFD4ULL, 0xA7E3346F7626C331ULL, 0x317F42EC68CBC66FULL, 
            0xDB85A498798E199DULL, 0x338C83440C1F514EULL, 0xCB904FCC2168EDFDULL, 0x20BC74B94EE3C51BULL, 
            0x9D23F269D26A0AE3ULL, 0x5E5A49001E30AEE1ULL, 0x4A7DAEE74894049BULL, 0xDC0B5C593F683977ULL, 
            0xF9E32C1BCF0E517BULL, 0xB521FC6903FCEB7EULL, 0xB16A024A889E73C8ULL, 0x3147E3A82B2DF136ULL
        }
    },
    {
        {
            0x40CA04136B75C511ULL, 0xA26A151DEF5907A2ULL, 0xA00255AA65D981CAULL, 0x8176AF5A78AE2622ULL, 
            0x4266094B7A728358ULL, 0xC1A41AE67C14D870ULL, 0x1981A62BC22FDD6EULL, 0xC8F2CE00D94F4372ULL, 
            0x81C9D861C742CF72ULL, 0x4AA9208F654D9BFDULL, 0x0AF22079FB2670BAULL, 0x4731FB0311676905ULL, 
            0xDEA66BC701B5D0D0ULL, 0xAF056A239CC904D4ULL, 0xCDCA39D83F0AA27CULL, 0x8DCAFF5A5A68E426ULL, 
            0x516B5D393509D39DULL, 0x6DEA65F6A4E301F6ULL, 0xFCC578C154C34B9CULL, 0x9504071CCFBAB75FULL, 
            0x8F66E967D1BE12E6ULL, 0xB38A2FAD45020869ULL, 0x07DF649317067A44ULL, 0xEE3A2C9648C2A606ULL, 
            0xBA731D3CC8090F8CULL, 0xAC8E61B5701841EBULL, 0x741C27129EB8947AULL, 0x055A88BC4323608FULL, 
            0x751DA93F8C89571EULL, 0x51F67C2C2916CE55ULL, 0xC79185E81E72DD0CULL, 0xE27E7C83FB6732F6ULL
        },
        {
            0x8A8F00F2F46BE3DEULL, 0xEC5FF408B481CF49ULL, 0xF3538FC0A679FACDULL, 0x86E567FDFBDE173CULL, 
            0x7C95B33E11CD1AE1ULL, 0xEC31A2686D274943ULL, 0x7C90911178897F5AULL, 0x1A8E0A78D460A53AULL, 
            0x1A212407E1185C9BULL, 0xDCF8E26A3E35B529ULL, 0xBBAC82D750126516ULL, 0xF3A4BBEB6AF710F8ULL, 
            0xCCD02B14A51FD19CULL, 0x13EFF1BE5793EE33ULL, 0xDB3FEB25FADB5203ULL, 0x3991C1221D2DF078ULL, 
            0x2D43DAD554F25BDFULL, 0xDF146F2273BEDE3FULL, 0x3AB1ABFD7B248112ULL, 0x857D2FFA7DDF76E3ULL, 
            0x221417A6CE973062ULL, 0x0C7A06C499E73D94ULL, 0x70AAD2FC96CF7CE4ULL, 0xDF9793BC8348B6A5ULL, 
            0xA47BF9FE3F105F18ULL, 0xC3D17583E3F448CAULL, 0x21F0E51E7FDD2CE7ULL, 0x1E9B9E6532DBA141ULL, 
            0xE5B16AB571043784ULL, 0xAB2F9AE1739785A1ULL, 0x0BC1A6F86F5A4721ULL, 0xC127D88400F4770EULL
        },
        {
            0xBFCA807A77AFB4EFULL, 0xC61B340CDE2ADF9AULL, 0xE6C6F99F1BB71790ULL, 0x3F9EDEA15665C1B0ULL, 
            0x2F75331240C0F2E2ULL, 0x76E0E5B0B58F9B4AULL, 0x6052F8C913E35FF4ULL, 0x69C04DD75361B984ULL, 
            0x72195DA339EFEEBEULL, 0x83D91106545C8792ULL, 0xB7054118FD78DF58ULL, 0xDB63472AA74C7272ULL, 
            0x4FB8036682BBA705ULL, 0xB69B7A78039F9BD8ULL, 0x78C02C790FE09CAEULL, 0x11350B140E89E911ULL, 
            0x3CA99B4061BE20C0ULL, 0x4A50368BD20F3F17ULL, 0x9CA2E756BE214775ULL, 0xE9870FDAE167D843ULL, 
            0xEFF83D478C5AD465ULL, 0x21AD236BD79A19E6ULL, 0x9E5C0F6D60EA24AEULL, 0x2949A9075E31DF0AULL, 
            0xBAE182C1197D2540ULL, 0xF02D52BFDCCE4371ULL, 0x610A80B67589DB1DULL, 0x46F01E74223C269CULL, 
            0xE6446559D9746BD7ULL, 0x7F06FB38CC7944A3ULL, 0x258F29943C9BEA01ULL, 0xDEA4B8E2EF48DF1CULL
        },
        {
            0xD8272562FBC56BA1ULL, 0xA64DC18A286722EFULL, 0x822036E86B117CBAULL, 0xD393DE48F264CB94ULL, 
            0x9465483ED098FCFFULL, 0xF0124C2B7ADD7471ULL, 0x29CA5D3CE9E41BAFULL, 0xFBB0830CE9669987ULL, 
            0x5F34FB6D2F87353EULL, 0x3ED58BBDAAB19877ULL, 0x1F33C4277A290CF9ULL, 0xDA13C3267BE8D80CULL, 
            0x40DFD36E8B8F89BDULL, 0xE59610651C794840ULL, 0x1230F1791FF7E725ULL, 0xFF263AF9C53E6A3AULL, 
            0x5B6D170C8C6AF0A1ULL, 0xA2AE7564E77F44C2ULL, 0x0354A5D97A1636CDULL, 0x81CDED0AF465EADFULL, 
            0x1D96860F57F3E84BULL, 0x8B1BA30F52B590CEULL, 0x7E8791E5454DC956ULL, 0x2DFAF93AE0054470ULL, 
            0x6F93262BF41BD15AULL, 0x1D4CB01F02FFD6E5ULL, 0xF7B1B908A4ACA621ULL, 0x872E2CFA5E690BD5ULL, 
            0x238BC068ECD21BB7ULL, 0xA84D234B0D219D60ULL, 0x91C6CE3E1D79321DULL, 0x175DADB24EE2C20FULL
        },
        {
            0xD75456CC37997C0BULL, 0x9BB370C1ABD4F649ULL, 0xE8B7B830238666C4ULL, 0xBF0A32D798581892ULL, 
            0xC54B8250CDB4E8C5ULL, 0x1BC662799783C5B0ULL, 0x666C62D0B33FABC1ULL, 0xBBD7650CAB4976BCULL, 
            0xB3D31C19A2AD49CCULL, 0xA5B82F7D6BDA892DULL, 0x841C29872FED79E9ULL, 0xD638076AC990EFBCULL, 
            0xFE221C1BFE67FEE0ULL, 0xB966ACE8A45D13AAULL, 0x24E63DD929FF2E22ULL, 0xC787F9CCD060C714ULL, 
            0x919BB6962A14614EULL, 0xC66FFF1167A4D64CULL, 0x4A10FDC893149EFEULL, 0x6083930429E7E2F4ULL, 
            0x5396E3B1A61ACDE6ULL, 0x132E75FC2C3BDC10ULL, 0x5897B52C5EDE4684ULL, 0x7773DB0BDC97EC88ULL, 
            0x5D23CD1254CBB980ULL, 0xAD9FB34BF176D190ULL, 0x18B895A4F59D1435ULL, 0x8B942E55622299E6ULL, 
            0xF8AF3394E8EA6242ULL, 0x1B989DFDF6626672ULL, 0xE2974BCA71DC0567ULL, 0x8ACBC85035F7A752ULL
        },
        {
            0x979BF7E1F70A5CE9ULL, 0x4501A7EE4F66E9B7ULL, 0xEF0FEAF758CE87CBULL, 0xAC712B8CDE7D2CEFULL, 
            0xBED14D3973648997ULL, 0xB415E9F3C7F4AEE8ULL, 0x15632A1CD103A99EULL, 0x346E7C3ECF775075ULL, 
            0x09C56A92D691FF0DULL, 0x3E4AEA2C6A119223ULL, 0xE0A3E6C1077342B6ULL, 0x5BA625FD60143251ULL, 
            0x00B6BCE6A9CDDA5AULL, 0x4012CDE18C931261ULL, 0x7EA2493E0B60CB74ULL, 0xB54511BF7719450EULL, 
            0x02D820CBF2883665ULL, 0xD21C7FC3293D71AFULL, 0xA75EAE82222B0D44ULL, 0x090C88528AFAA419ULL, 
            0xD6B7F0F0EEC52077ULL, 0x53234FE74EAADAB6ULL, 0x312EDBE62DDA2E90ULL, 0x1AA0F6F01B186634ULL, 
            0x8CA82B02825FAC13ULL, 0x468543559DF9CAB9ULL, 0xD1DD895024F0CCB3ULL, 0xD216F3C373AB3CCCULL, 
            0x67E41676E4E7CA91ULL, 0x2341EC9F9FC09C86ULL, 0x502A1E6B08AB949CULL, 0x9136965A25DE8B0FULL
        }
    },
    {
        {
            0x020969D5A383781FULL, 0xA76C9C61E7B754A7ULL, 0x30DA1C6218C5CBE8ULL, 0xAF41DD3E5D20EFF5ULL, 
            0x0544213E049A74F5ULL, 0xE11DB64390A9DF41ULL, 0x138E2A75C658B9B1ULL, 0x99E533F57644F957ULL, 
            0xB2469405DBB614F0ULL, 0x02BFAC65A56A3878ULL, 0x4B87074195882905ULL, 0xE02DDCB0ED4BBB99ULL, 
            0x3D27D62E1F0D7B21ULL, 0x4EDFCCBA99464921ULL, 0x9BE09F16C838E98CULL, 0x68681DB62B8A5C17ULL, 
            0x52B3C42AD360FEE7ULL, 0x49A258D9D81D59F6ULL, 0x766D46C136C6B347ULL, 0x2DD43AC84624F771ULL, 
            0x8D696B70AFF7407AULL, 0x76849B91C450B71EULL, 0xB12EE54AB152EB12ULL, 0xF02DC611C5227FF5ULL, 
            0xB12390E17B92EA4AULL, 0xF5FBE0B5F8F3D183ULL, 0x8FDB35DC4DF57BD9ULL, 0x2F2AD6AC9CFEB1FBULL, 
            0x5C18BCAFCD10892FULL, 0x74E661165A463DFAULL, 0xD8B425E0007D5714ULL, 0x1F5C9C85E2008B4BULL
        },
        {
            0x0EE033554347B668ULL, 0xC72DCC1F1C0096B2ULL, 0xBE6A752F979D5605ULL, 0xB257AC20FC8BFB99ULL, 
            0x4DB7429BF473D394ULL, 0x8711E3E0EB75F590ULL, 0x85B0A1A7CDD1022EULL, 0xA2D013D101B013D9ULL, 
            0xB5039C932D2DDB6DULL, 0xAC161B52266F4195ULL, 0x39571A79A63644F5ULL, 0x2BF6928CA77B724EULL, 
            0xC573889368A5AF03ULL, 0x1A1CFE24374BF5E3ULL, 0x0315AEAB9407EA0EULL, 0xE8993908099DF22AULL, 
            0x4EFB5339D93A89F9ULL, 0x6C09F8BF0F29F3ECULL, 0x91618DE41FF52122ULL, 0xE925DACFFE203F80ULL, 
            0x2787A342BE6B6995ULL, 0x87D128DCCEF1F7CFULL, 0xE871F2D9EAFE7AAAULL, 0x51E9AB2CBA34AEFEULL, 
            0xE83A0249F34CDEB5ULL, 0x33A73C4359F2B34EULL, 0x5534696290B359A7ULL, 0xF5AA897F38E4CFA3ULL, 
            0xF2C3E84D79DEE787ULL, 0xC720DDD6349740BFULL, 0x30FC45962FEA079EULL, 0x788051218A1017ADULL
        },
        {
            0xDA5A70E1B736532CULL, 0xC07FF966475AE79CULL, 0x89E5B1F473A2AF37ULL, 0x4B5D130740D4BE24ULL, 
            0xFBA4997FC1B3744EULL, 0x2DD5CF2658A6C6B3ULL, 0x23ABEA87DC9EBD76ULL, 0x4100EC52EC1F41C7ULL, 
            0x489928F826FD86A9ULL, 0xF3631193B53A3709ULL, 0x4D9BD785AFFE5464ULL, 0xBEBAF5E4A22A268EULL, 
            0xA00EE3D25C8E8528ULL, 0x591C1819663E314AULL, 0x4D1233C7CA72D02FULL, 0xAB012CA87F2DD11FULL, 
            0x3671494BB2C68C08ULL, 0x67641E83BE8A42D2ULL, 0x0DA36C609F7B7131ULL, 0xF0483FE887AA7F74ULL, 
            0x543E3731186B0DF2ULL, 0x52532453A4C7B6CBULL, 0x1895F0A04B70DE0CULL, 0x34865A74150C3617ULL, 
            0xDB9AE7B5F0E65996ULL, 0xDD1E0E0F17F4631DULL, 0x971D0A2D13EB5FBCULL, 0x372DC81DB6C65F0BULL, 
            0x867B05341F9D87ECULL, 0x9EF0AC1053439F9AULL, 0x4E8B964F0686D796ULL, 0x5C1D0D36E1E0AF97ULL
        },
        {
            0x4E73030CA8B23088ULL, 0xD5A9E16FFB955B5AULL, 0x29DBC14B01A5D35CULL, 0xEBCF64EF00D89F19ULL, 
            0x3F44E577AF73C6D8ULL, 0x971EE4113CD4F801ULL, 0xB68514D1A468FF21ULL, 0xCDF2C80A36540FBBULL, 
            0x7C0B4322F59273C9ULL, 0x923CC93874F9C410ULL, 0xA1C02C6531559E43ULL, 0x815127A619C6D7B5ULL, 
            0xBF11888E8CF88BA7ULL, 0xBE57DA1E31D1A2E5ULL, 0x4D07DA4DB634F14BULL, 0x22600E197B5EC4CFULL, 
            0xE9A7518B9CA70C84ULL, 0x12D287D21D34413DULL, 0xFC4125D83ADB8DD7ULL, 0x9F78DE2AE33944B0ULL, 
            0x610F6E9C2C54EAC7ULL, 0x8B67BCDEE8A53571ULL, 0xF7C8E2E4741FFE51ULL, 0xAAA8D637519E3521ULL, 
            0x06B8143796D9BC84ULL, 0x53CDE833536FD9C8ULL, 0x0676C153E6468524ULL, 0xDAE617E0991639AFULL, 
            0x17182C5F8E00776BULL, 0x549D4090C0D0D44FULL, 0x5437F36FA21C746FULL, 0x1D3F6EBFD203F60FULL
        },
        {
            0xA49F67FE8A9578A0ULL, 0x541227E35A2B8783ULL, 0xE202F1643D6F0439ULL, 0xBDB81629C9EA9519ULL, 
            0x6D738499ECFF5362ULL, 0xB2FBA79A934DB3CDULL, 0x464E044CDC6E756AULL, 0xC9E2D8F177CDA3DEULL, 
            0x79F2C3234E6E4794ULL, 0xC0FD962195BBBB93ULL, 0xE5E13462656977B8ULL, 0x0FC27ACBFCBA819FULL, 
            0x866B5DAEC743EAEFULL, 0x6382DB0ED2129B26ULL, 0xB26DF4F0244D1A0AULL, 0xA3426E6FF6B67D4BULL, 
            0x040CE52ACD285AEEULL, 0xF5F3A10063283192ULL, 0xE015B278C338A4E5ULL, 0x3C5AEB7D3DA50449ULL, 
            0x1D5C44B40BAFC19BULL, 0xE45255024033C423ULL, 0x79B5C218D20692A0ULL, 0x999F071B8DFCF614ULL, 
            0xA20DD7345C2FAB4FULL, 0x1B24C732C053B488ULL, 0xEE29C93F2A2ED0CBULL, 0xBFC889B54DC4AF19ULL, 
            0x10F784FAF6D82EECULL, 0xA308F8FB9FF95B47ULL, 0xDD2F02F893DC916BULL, 0x093C081744A66CD6ULL
        },
        {
            0x00E5215313F177C8ULL, 0x2C822801D77691F8ULL, 0x42BA04B2BBA36AE0ULL, 0xC5330D68CCEDDACCULL, 
            0xA69951BAAF5F5C89ULL, 0x26B0097722245FDEULL, 0x424B80B3C10E0D5CULL, 0x2A99227FC28AB74DULL, 
            0x770FF931CE6A5A81ULL, 0x8D06D8EEA5D1F687ULL, 0xAAA30A7DF1D0B9DAULL, 0x7EBCC21BB195CB17ULL, 
            0x34EFDBD2B8EAE410ULL, 0x9EC7441E34E66A2FULL, 0x2FAB18D291432573ULL, 0x48B43A99D83EFC8DULL, 
            0x3A667A729BC31244ULL, 0x2E101966F0397F67ULL, 0xD0B63CED8B8EE7CDULL, 0x532192DB35E818D3ULL, 
            0x502593DA2ACE0B76ULL, 0xA493D35904C96628ULL, 0xC3BA36FC19AB7259ULL, 0x49016D176F45ECF1ULL, 
            0xA1484B843BF02A4BULL, 0xC2BBF33ABF5750FBULL, 0xFABE12FE59434373ULL, 0xDA736242213BE3C3ULL, 
            0xD9CBDCFF8496B3D1ULL, 0x78727CCAE931E774ULL, 0x87FF0852E8849130ULL, 0x2BF5DAA66E433AE3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseDConstants = {
    0x0DE8668796B26B68ULL,
    0x5CBC351021F76AB0ULL,
    0x37101414A2C73EE7ULL,
    0x0DE8668796B26B68ULL,
    0x5CBC351021F76AB0ULL,
    0x37101414A2C73EE7ULL,
    0x88FCFE5379D1A5DBULL,
    0xC9B8DD1CE3ECFF28ULL,
    0xA7,
    0xC9,
    0x78,
    0x35,
    0xA2,
    0xFD,
    0x64,
    0x6A
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseESalts = {
    {
        {
            0x184F02D09F97E8D0ULL, 0x843F40CE9CD753C4ULL, 0x4886AFAB861F964FULL, 0x0BF9B23BA78D7740ULL, 
            0xA7C6C7A68BCFF29BULL, 0x157402FDBD288B98ULL, 0x884620725BEF647AULL, 0x64BEE5030EC00A3AULL, 
            0xFC933F9AE70AD4BBULL, 0xD69338DB09F9CBB4ULL, 0x10EF613F342DC28EULL, 0x5160D24D4FB0A539ULL, 
            0xB8C7D929479B5A09ULL, 0x9AE12402F86278F8ULL, 0x4905946596C8C16FULL, 0xF0F592017CED3C06ULL, 
            0xFE96B9EE958F6382ULL, 0x55B5188300C58ECAULL, 0xF33A44FA5B87D282ULL, 0x2D878FFF03F13C05ULL, 
            0x9C551BB77137AA1FULL, 0x66523C3D9DCC22F1ULL, 0x731500576D0FB16FULL, 0xDD504A1BBE08BBC7ULL, 
            0xCF61BA4ED76756ECULL, 0x7C2F4C528FB3EA30ULL, 0xD3F4C55D9FA99EFBULL, 0x75F6F87BBC83AB63ULL, 
            0x70B42F97C28DD417ULL, 0x92F6075E56C5B576ULL, 0x31617C55F3C9ADDFULL, 0x03CA8F713317A508ULL
        },
        {
            0x8D57A562D26B161AULL, 0xCF9D4C24BC13EBF8ULL, 0x286BE5481D488F6FULL, 0xE9B49805F2DFE23CULL, 
            0x4B795073A30E05C3ULL, 0x98126B974824EAA0ULL, 0x2E2A460674F2F60DULL, 0x7CB551708EF5FC1BULL, 
            0x9F41D222593A4DCFULL, 0xF5FB0287227CAE8CULL, 0xD101634FD9B0BE3EULL, 0x9E8E9E321331993CULL, 
            0xC786C8EC418EF780ULL, 0x56DAB512429FE024ULL, 0xC2C9B61850611956ULL, 0xBCA985CB7A1BAF31ULL, 
            0x6422564F32DDFE95ULL, 0x0D060B261A9B71C0ULL, 0x1B05D7A188C6483FULL, 0x92150228716D2348ULL, 
            0xBAEECA631524D26AULL, 0x1BE5FC4255CA399BULL, 0x60EDAC21962AD080ULL, 0x12217850858A80C9ULL, 
            0xB1F977A42B034564ULL, 0x2C30F7A614CBD901ULL, 0xC0C6BFC1496F4885ULL, 0x7A6DA781E1557035ULL, 
            0x7426B0F8744FEAD8ULL, 0xA9A276AF2FE3A7DEULL, 0x6E9F0CE24716B741ULL, 0x7FA92E3EC9214E23ULL
        },
        {
            0xFDFA8AA0343EB432ULL, 0xBAF003F60A304425ULL, 0xACF324C48D1920B9ULL, 0x2E03EE01493D5404ULL, 
            0x34DF1F24007A390FULL, 0x7C9EBDDD20518E01ULL, 0x79874260F455E9D3ULL, 0xB4A629FEE780F3E8ULL, 
            0x6DA6171CB5D6D0FEULL, 0x3D5F9B0F28CA52CAULL, 0x7DBD4D48C69F74A5ULL, 0x631045822413B050ULL, 
            0xE5EAEB2F02F3709CULL, 0xB7E032F4D5C291C3ULL, 0x08B5E48F7854FC2CULL, 0x5047B7D4A8D2E2EBULL, 
            0x7A80A50DF31FEC09ULL, 0x2E7B33E3D1A2DABDULL, 0x6EC890F17E0E0CD2ULL, 0xF8256FEE7F6EC67DULL, 
            0xF2FFD8A140742964ULL, 0x3571AA5D9D60A88AULL, 0xE5CE0B211CA06FFEULL, 0xE88A7CC1949B975BULL, 
            0x04A99DCD1D670CAAULL, 0x6FAF28FDCCC15DB2ULL, 0xDDDC181A0064CBAEULL, 0x26CF41607DCF5D07ULL, 
            0x121FC63365038DB6ULL, 0xD8B8327E5067A2F4ULL, 0x1B73B7C4974875C8ULL, 0x75DD45C716528240ULL
        },
        {
            0x56BD2D11EDF08EBFULL, 0x89999BBEA181F982ULL, 0x497BC3F7AD347C80ULL, 0x64D88F9921638773ULL, 
            0xBBA1EAF8347F5B61ULL, 0xE803ECF61FDF382FULL, 0x6AA1121666B90A76ULL, 0x737AC1844BDA3947ULL, 
            0xD15161DCD7DF0901ULL, 0x7DBB880CE9523752ULL, 0x0BDD587982A67CFEULL, 0x5B710851105C335EULL, 
            0xB9EB967A2FCF0EB6ULL, 0x6D817FE14366C654ULL, 0x9FC0BA8E15BBA08CULL, 0x0E427564A865EAD4ULL, 
            0x361F5AD6FA49FC2BULL, 0x21D552438032270FULL, 0x6B436EC55298D3B2ULL, 0x92D6E3E0DDB7A0EBULL, 
            0xE8B7FD3084064EE4ULL, 0x9CE41D0A7DA78E2EULL, 0xC43B1D50E4281F30ULL, 0x340D3AE45F418356ULL, 
            0x4B29ABBC4C62C306ULL, 0x027B7364FEEA9310ULL, 0x0E495695DDE4B310ULL, 0xBDE17D7A343BD159ULL, 
            0xC3B625A57D75CC5DULL, 0xC1DB0397C820AB5FULL, 0xCBE3E08ABD06A8B7ULL, 0x704C0B01706A9B07ULL
        },
        {
            0xE92F85F2763C5841ULL, 0x9CC58D98C200819CULL, 0xCDABB174B112F2D7ULL, 0x685B3099A78B6F30ULL, 
            0x46EBA7B962933110ULL, 0x1E0C8CC46EDA32ADULL, 0x91189425244E70E4ULL, 0xC510303FA99D120AULL, 
            0x5E006CB098FC3DE3ULL, 0xAE561F8E1E3C7423ULL, 0x4D0B8AF5B741F7A5ULL, 0x9F7129BAF206E91FULL, 
            0xE6C4E39D4530A554ULL, 0x0304F6F0334F132DULL, 0xC5FC1633795FBBAEULL, 0x01BBE325BC0FA2DCULL, 
            0xBD7600C4414B5C9DULL, 0x43D5D9D9A1407821ULL, 0xA2EFA2E8FECBD93FULL, 0x74C833014AE9F4C3ULL, 
            0xB4E9F95E90096815ULL, 0x869934F787063701ULL, 0x047F4C5EA110C181ULL, 0x822E8B3EF510BEFDULL, 
            0x818AA23DDBAD5B5DULL, 0x5CA55B50A65EC450ULL, 0xD47E1FD48C5D875EULL, 0x2B680575B0A730F1ULL, 
            0xC1679748F3D4079DULL, 0x3B463EED8DDCCADFULL, 0x4C582EBC10686C6BULL, 0x4CB0CE14FBECA539ULL
        },
        {
            0x5CCB1E14BEF5EB47ULL, 0x3A43647616B09646ULL, 0xFAA7BE62EDCA383CULL, 0x8131A8ABAD15EF68ULL, 
            0x2A7404C4572A9609ULL, 0x95F8A0D6BB677BC2ULL, 0x91FE7B2345A545B7ULL, 0xA5B98891A7D2E394ULL, 
            0x71F2E6F39631686EULL, 0xB4CB4FF403BD5FDFULL, 0x58F20BECAD12389DULL, 0xEAC60637C519F688ULL, 
            0x38B4ADA60F7E4CE7ULL, 0xD1B6311BBF194A9CULL, 0xF367A6C661C4BAF6ULL, 0xD06FE3C1988F10DBULL, 
            0xD594E2ED60FF8471ULL, 0xFF5569F40184728CULL, 0x44B3F2F40F2F12F1ULL, 0x7712B116C4E780D1ULL, 
            0x211E9871D86426A9ULL, 0xB6BB06A5892B7577ULL, 0x7513349826B008B6ULL, 0x63EA5631B89B2A6EULL, 
            0x2E579D802FCB413DULL, 0x573E35BC12BB8AE4ULL, 0xB3F833160BA01F04ULL, 0x45333FA302EBE925ULL, 
            0x43C9F4E243DA9AC0ULL, 0xFCB928AD996573BBULL, 0x2C3EE185FBEBEAE1ULL, 0xB8BA51423FADEE0EULL
        }
    },
    {
        {
            0x1C5BD35C00D2380EULL, 0x1614770258F71B28ULL, 0xC12A0F243046B6FCULL, 0x4996A16AD185A007ULL, 
            0x9EFBCC76E3CEF3B7ULL, 0x6BF9544A9CE7C704ULL, 0x8CBF1F56438250EFULL, 0xD8A938F48FDB6FF0ULL, 
            0x895AB4BFC9C42B3FULL, 0xA622B98AC97548BDULL, 0x547B715A8413606DULL, 0xEA6616E4376BF74EULL, 
            0xE5A4AEB3D6EE6D7DULL, 0x81627CAF3EBFD68BULL, 0x6D1DA78614149AFEULL, 0x85D6A6601AD8A793ULL, 
            0x5061B5211D381DCBULL, 0x83C353E524F4ADE0ULL, 0xFA196D297010C3FEULL, 0x398511E816840D2BULL, 
            0xB14B58D1AA5B81ABULL, 0x6895FC4C146B3A36ULL, 0xB521E89CF23CEB54ULL, 0xC9E92EB9CD42A3D5ULL, 
            0x439890E31ECA0CD0ULL, 0x4DBCF12B2985CD15ULL, 0x8351A1F1A2956AC8ULL, 0x5BA8CC2A3C28457EULL, 
            0x5CF25C6EEB540263ULL, 0xD94EE0141A42ECF1ULL, 0x9B26850D362A5983ULL, 0x76FC14D556ECCEFFULL
        },
        {
            0xDD2CAD32AD4EF1DAULL, 0x6C95811D5FC6C897ULL, 0x068D1A19F4B9DA99ULL, 0x9AB5A8FC56CEE4ECULL, 
            0x10F26DA1ACA65EEAULL, 0xAFF8EF7C6C2632EAULL, 0x5F84D3938E674201ULL, 0x131378BAE7DB65ABULL, 
            0xFF9D18F23A006394ULL, 0xF471EF47E5350811ULL, 0xAF387D28CCE37BA3ULL, 0xD9F307B354101953ULL, 
            0x2FA3CB9705FC45D7ULL, 0xFD4AB404487BFE55ULL, 0x6588A375ADC26742ULL, 0x3DEECAD3E6CF9E3BULL, 
            0x609B2DDB673C03FDULL, 0x568980FEF88BD1D0ULL, 0x518B8A817E75FEFAULL, 0xC6F7E14478E3696DULL, 
            0x1E307D3FDD249381ULL, 0x7635637846A46812ULL, 0xD13AE13D1BE446D6ULL, 0x356F57483500DBE8ULL, 
            0x390C701104D12636ULL, 0x8BB4201FB64CE1C3ULL, 0x80F72869EC4B099FULL, 0x52FE2F5489F9FF2BULL, 
            0x5C0D9AB955935AEFULL, 0x8F03444187E42B98ULL, 0xA0F0643670CAC3D9ULL, 0x94C512C31D2E972DULL
        },
        {
            0xAE7DF21AD191C647ULL, 0x176ED179BF4748B0ULL, 0x59AF2E6CD8FBFB02ULL, 0x8CB1C722ECA720A3ULL, 
            0x7766CA5ABA7F9474ULL, 0x4931DF38EFC7DB19ULL, 0x29ED99C8750B5179ULL, 0x79E7B093D2B9EE55ULL, 
            0x26B848A97EBB6AB3ULL, 0x4C935263450774BBULL, 0x8C0FD40750CE15A6ULL, 0xFC02F98B7ACB3AFEULL, 
            0xD2EC549F0CCA4B4BULL, 0xE1D81594176B58D6ULL, 0x8143F912269EFC95ULL, 0xD4A020815CD2FB99ULL, 
            0xF04189D127899FCDULL, 0x20D741E63EBF2547ULL, 0x8174A04E691EA558ULL, 0xD186656FD27BB5BAULL, 
            0x997471411752EFEBULL, 0xEDE53D2DC5FE109BULL, 0xE9EA467D3B7F2725ULL, 0x0C8168DDBECD5643ULL, 
            0x90AFF4D0BE6C4F2AULL, 0x3C3D3AC3E08D000FULL, 0x23C88F8437A0E998ULL, 0xA8DFAD4E94E0A56BULL, 
            0xC05036E3270EE4DBULL, 0x7519AFBF7AA68ACAULL, 0xA76AAB670F64F8FAULL, 0x82DE0177C0BD4E37ULL
        },
        {
            0xCD5EA2ED40BEE6FBULL, 0xD27C78FBE791C0D6ULL, 0xE86219EBD2F9925EULL, 0xC83C5A7E476102A0ULL, 
            0x565DAA9C581226DEULL, 0x07B2FA6E275C82B0ULL, 0x42E0F667614E9DA9ULL, 0x4A0924AA6A0DB1DDULL, 
            0x69F6B57A887B63C4ULL, 0x513CD7F1CFD3D3A5ULL, 0xA140BBAEF06934F9ULL, 0x94B84885DA9BBA81ULL, 
            0xCF0E0DDACF5628DFULL, 0xCB57FFC0926BD643ULL, 0x8EEB3D2E637C93CBULL, 0x13DAA1A9C2DCBB23ULL, 
            0xB8EDD0DC5E85B954ULL, 0x2AA06026ECE63DD6ULL, 0xEC33EC9A8E774A6DULL, 0x0F06692D3A4D9DEBULL, 
            0xE2D0396D99BD39C9ULL, 0x8FC47CE285D8B14DULL, 0x8F5E7F39AB3382B2ULL, 0x494E7029EBDE094EULL, 
            0x1D1F70921520CDB4ULL, 0x7CC90A24EACE0BFDULL, 0x6967D30DAFA165D3ULL, 0x25F334D133F7C743ULL, 
            0x6D30DE622E63471CULL, 0xA995664FDCCE52A5ULL, 0xAAFA8C81500F65FAULL, 0x2B335BC25A810B03ULL
        },
        {
            0x0739B6DEDFB21024ULL, 0xA0E2FCC022F531C7ULL, 0x7B2CF9895632C82AULL, 0x524CBFE244A0EF3FULL, 
            0x5DB0D68FB923DB03ULL, 0x2C315F94DA1C14E2ULL, 0x60AEEB5736E002D3ULL, 0x0F133FF51CBE1B38ULL, 
            0xF2EF092E767837A4ULL, 0x23231D4F7FA4A1BDULL, 0x77A382FCA5D944D8ULL, 0x6C14E0FB06547F8DULL, 
            0xEA94E073C8D27CFBULL, 0xC2BAB0A8B83D8417ULL, 0xE71728BA6ED8CA84ULL, 0x27E9CA1CFA24DB63ULL, 
            0xFD15A5F654A5DDEEULL, 0x6F4AAE7F7F57281BULL, 0x6D87574FE2DC3ACBULL, 0xFEFDFA5705D6E51CULL, 
            0xD54130FF4B97D5CEULL, 0xE8F357FAFEDE3FBEULL, 0x303A0818F98A0CEFULL, 0x86DA0C29C138E6FFULL, 
            0xFBE6DDE59178D4FEULL, 0x2ED7B867246A1AD0ULL, 0xBE3F1EAB340371B2ULL, 0x7BBC5BAD39B16F3AULL, 
            0x76B086FD07C71F38ULL, 0xF49A4C2FA2D35796ULL, 0xA14507F051950AA0ULL, 0x19220A11CC7C1C00ULL
        },
        {
            0x374C2BCEA8C7F82EULL, 0xF44A5859FBA3C1DCULL, 0x3AE1A8DDB32572D6ULL, 0x1464D16DD4708666ULL, 
            0x08F0DAFC6EC78031ULL, 0xAF9D778980BD46C9ULL, 0x70433C498DDBCBC3ULL, 0x5DB19CBBB69E3558ULL, 
            0xF7AD9E1A767F07B6ULL, 0x06655721BDD73B8DULL, 0xB85DAC91E39FFC7FULL, 0x8A1C2F42906C60BDULL, 
            0x5C6D91A33346626EULL, 0x0770C8BCD2C6598FULL, 0xC5D6A86B7ABC9F6BULL, 0x205716B6FE26F695ULL, 
            0xB7A3A928CBD3CDC3ULL, 0x1848F1F98734EDACULL, 0x691D7EE45535254EULL, 0x1CBD405780617B00ULL, 
            0xAB35D5EA09A7ECE5ULL, 0x3D78121D630F589AULL, 0x9C0C7184550E9935ULL, 0xFFFEE6B5EBF84920ULL, 
            0x26B8EBAB9C5CB4D3ULL, 0x5288457E0E9D312BULL, 0xE17A3986C32ED29FULL, 0x58C04B725DE85784ULL, 
            0x14979EA43EC75206ULL, 0xA8AABFEDE904EB42ULL, 0xC697FCCB3BB069CFULL, 0xC3AEFD46D12F05F5ULL
        }
    },
    {
        {
            0x9EF6C9BEBD3D7F61ULL, 0xDA31DF5F94A358D9ULL, 0xE87558A936BC0E10ULL, 0xE4CEB914C50E649DULL, 
            0x67F62422B65BF453ULL, 0xDFD90376A65ECC8BULL, 0xBE405031167A2E25ULL, 0x643752CB8537142EULL, 
            0x6C680196E1BE4252ULL, 0x3857B6977882121EULL, 0xA8F1CBE48F2182A1ULL, 0x400B07AF1FF8EC38ULL, 
            0xF8E392E5E493E111ULL, 0x466021B45C7BC515ULL, 0xB58E1F60227B8120ULL, 0xF1448E03A3A4E056ULL, 
            0xCE17032662135406ULL, 0x95F5C672E4407D27ULL, 0x761DA94B8F147BE0ULL, 0x7B25623AE6ABC176ULL, 
            0x9936005E814618D0ULL, 0x0B05B9E0A7830DCDULL, 0x73E7CB49AA490B59ULL, 0x264516432D06400DULL, 
            0xFA95AD3C3886CEE6ULL, 0x0BF758C079595258ULL, 0xAD4BAB17605BD11DULL, 0x23177C6291B94665ULL, 
            0xFC91AA523790BC48ULL, 0xEEC067F689A7337AULL, 0x3104549F8DA214A8ULL, 0xD6EBC7B3EB4C5F76ULL
        },
        {
            0xAF794E6F61AA8BADULL, 0xA2955C5D16120D4FULL, 0xFD360C064DCAFFFFULL, 0x9CE4F87F362F9B2CULL, 
            0xAE51A8D29A8B6C22ULL, 0x0D8B18B0B9CFE4A3ULL, 0x4D8948FC034FD243ULL, 0xF7D8B6383F02C94BULL, 
            0x9871309DD12D18CAULL, 0xC03E32B76833CF4AULL, 0x9B004FB28CD1B1D0ULL, 0x563E70245629F397ULL, 
            0x31DD182B47B43E48ULL, 0xCA92ADB3676F923AULL, 0x814228370CD38689ULL, 0x4A0F64002082B276ULL, 
            0xCA80665163C4496FULL, 0x0E8750EA7F7A8967ULL, 0xB73891DDEFBB57E1ULL, 0xF0DCFFFD10942328ULL, 
            0x1925F71F14004E66ULL, 0x79C306D9CD8BE935ULL, 0xC0EAAE949F48ED93ULL, 0xD0D5E879E4B50408ULL, 
            0x252B59A7410930C9ULL, 0xBCB07A11149B26B1ULL, 0xF5BB00B870A11A41ULL, 0xC0CE1E98A013530AULL, 
            0x6DA50E411D0E46D2ULL, 0x1D5055B8F1B342B7ULL, 0x6C11A1A3CBEE2D40ULL, 0x1868AF155463504DULL
        },
        {
            0xE4F4FB2EDD24C88CULL, 0x40812A81617EB1F3ULL, 0xF321CABA45C78E47ULL, 0xA06C6B8073DE150EULL, 
            0x52C2B595C4058B39ULL, 0x4FBC0FB9F4CD84CAULL, 0xE486B94A7D4A514DULL, 0xC2A86602F3D64BB0ULL, 
            0x03AD6C84C0976FA7ULL, 0x0BB4AD5F5F9C0CA0ULL, 0x116EA9F7F7A26FEBULL, 0xFF90B8C6CAA2EF12ULL, 
            0x5F6F8922F5985679ULL, 0xB6AFD0A16E2A88E1ULL, 0x01E856D8F589DFB3ULL, 0xD6EBFE28CC493476ULL, 
            0xAD69F3A8A3C8D5DCULL, 0xD6D06B60DE44F002ULL, 0xAAD08DA14C44955BULL, 0x5D83889169A11C4DULL, 
            0x3FD7C16ACAF44CBEULL, 0xDF14E45481DEDD5FULL, 0x6BA49D8F2D1871EDULL, 0x6136A686F9221086ULL, 
            0x77AD9797379961E1ULL, 0x583EEBEF978E4931ULL, 0x74A55BBC7AF3EA19ULL, 0xBFA366FB10C10629ULL, 
            0x0532C0760800D7AFULL, 0x288C21762DDBC188ULL, 0x85D28CE05AE7B248ULL, 0x844CD8013BE6AC4AULL
        },
        {
            0x38F7DCD08A4879E2ULL, 0xDAD903D6A0703D24ULL, 0xB3DF1E6E859CEACFULL, 0x5A9E4FF1F7D6CCABULL, 
            0x540C533E23491C18ULL, 0x97985DF2F82B059EULL, 0xA3303157AB543870ULL, 0x816C350978D4CBAEULL, 
            0x7F4BA07416D052D6ULL, 0x6A5D2C05FC260F59ULL, 0x75DF7A8342041D13ULL, 0xF93F5CB4F03ECA1BULL, 
            0x6275B990397A7A26ULL, 0x26DD81F279C57AFFULL, 0x90723305731CF3D3ULL, 0x90A28B54A4581C8CULL, 
            0xC52EEE4B914CE8ECULL, 0xCD40B8526CF44781ULL, 0x9B4A76CDCF24750FULL, 0x5B0E77A1C728E172ULL, 
            0xEBB1A5170918403CULL, 0xBA35E6529741F537ULL, 0xE901C012B03CAE27ULL, 0x3E00D7FAB5F11502ULL, 
            0xB429810C58C655D2ULL, 0x5E83686044FCC036ULL, 0xEA02372E6D610280ULL, 0xDBE8F575957EBE23ULL, 
            0x6A45B1EFAA147492ULL, 0x650A1F16431FE6DBULL, 0x8A5BAF13DDE92786ULL, 0xC726FF64BDFAB509ULL
        },
        {
            0x25B5057ED11D734DULL, 0x89F605489AE288DDULL, 0x39D9D5B3568D7926ULL, 0xAF6C3BB7D6D0E24DULL, 
            0x93320911DB89BF9EULL, 0x060A93FFF9D4B600ULL, 0xD206E5D04F810644ULL, 0x84444A47C3F0197DULL, 
            0x574A52846F00059DULL, 0xC244BED6EAB1A0E4ULL, 0x573D7A2807AAA47DULL, 0xFC654E2EA3DFB661ULL, 
            0x19548606080EB662ULL, 0x74344C5754609A95ULL, 0x5595E98421554A03ULL, 0x6178E74FB5545D48ULL, 
            0xA94784F3711FDAA1ULL, 0xDF90BBCDF9AA86CEULL, 0x03A4D225A293C69BULL, 0x9589B6FB856A5688ULL, 
            0x880BE35B7C80E73DULL, 0x625D4B8D04CC1C13ULL, 0x60F908472D7E9350ULL, 0x74514C6A6972860DULL, 
            0x8E39D95B75A8B7AEULL, 0xB158B548A6A6C3C9ULL, 0x19F2B0B241A8C8D7ULL, 0xFC5DD364B374FD38ULL, 
            0xC04BAD797A2E87EBULL, 0x98288756615AE827ULL, 0xEA2049E022C2B019ULL, 0xE0A0AB7DC00DEE71ULL
        },
        {
            0x120FA17E10D78FFDULL, 0x6952C84DB8019285ULL, 0xE38C484BAD7B5BDCULL, 0xD15347D76D2F6D7FULL, 
            0x19F46E1EC590E34DULL, 0x0751270CF073DB8BULL, 0x7BEE67F0A0F74EC6ULL, 0xF87E7D88135CD909ULL, 
            0xBD9D2189231D2383ULL, 0xD913B502A9E3972DULL, 0x2666F72CE279D48AULL, 0x01EC07EB73B46D2CULL, 
            0xBE7A801C41B72F29ULL, 0x892CD57AFEC66F5DULL, 0x0C9B7BF3B7D35C14ULL, 0x357AE4534130C9D0ULL, 
            0x48EC2540A1DAF060ULL, 0x766CB980AF85BDAEULL, 0x9FA95BDDBC3586FFULL, 0xEB3030BBC900D69CULL, 
            0x862865C5B90BA381ULL, 0x9EA126D94C10F324ULL, 0x466123309F9C5AFDULL, 0x195B8ED6D2E0305CULL, 
            0xEBE3583DA4BCC3FEULL, 0x9EEB87D9E5C04498ULL, 0x914C2BA8C66FFB67ULL, 0xAC0F905B49B10686ULL, 
            0x9415D12513165D7CULL, 0x7C7246E585CD3E3DULL, 0x1F9461282DD9B1D4ULL, 0x0B031B30FABBF8A4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseEConstants = {
    0x256F6FD1E13A060CULL,
    0x72AF53210057347CULL,
    0x217901E248D0AA36ULL,
    0x256F6FD1E13A060CULL,
    0x72AF53210057347CULL,
    0x217901E248D0AA36ULL,
    0xA5AE52FC4749A2A0ULL,
    0x4A214DCEB19FDE08ULL,
    0xD6,
    0x1B,
    0x47,
    0x8B,
    0xAA,
    0xD9,
    0x1A,
    0x40
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseFSalts = {
    {
        {
            0xE19A33896E8920C2ULL, 0x467B033424BDBB2BULL, 0x2677547421965CB9ULL, 0xB3C331A38CCAEF75ULL, 
            0x99D7B978479A24ABULL, 0x181512380FCBC520ULL, 0xD890F81E36A3DA2AULL, 0x74D0DA75BD9362D5ULL, 
            0xC2687E1280484EE1ULL, 0x3E1E06CAE2DB339AULL, 0x7CA3DC4EDBEA4D8FULL, 0x3EE5711590494EE0ULL, 
            0xD31FC1694F2B1110ULL, 0xD05403ADE45BAA55ULL, 0x633D6A4395BC54E5ULL, 0xF8F7B22B14B22CD8ULL, 
            0x7480BF6F5B889B61ULL, 0x567837427CBC91C0ULL, 0xD48189DD379E2F6EULL, 0x5E960F1A281C10BCULL, 
            0x0CAD0E79BD7AE958ULL, 0x66188070106CB412ULL, 0x18DB9CACC589BEA3ULL, 0xD8B25DB586DD7BF2ULL, 
            0xFC1AE402959073B5ULL, 0x937368F37CB3FFF7ULL, 0x2CF32EE6EE661705ULL, 0x3C173BB3E5F618D0ULL, 
            0xFF45C1EC4564F4FCULL, 0x4684D411A31F710FULL, 0x280852B66296936CULL, 0x99895D70848B3A8EULL
        },
        {
            0x1E67C1D771E5F2AAULL, 0x35B3D79536DB27D5ULL, 0xDC31CEA43E226066ULL, 0x6AD9FBCB9AD54976ULL, 
            0x918A0EF45947DB51ULL, 0x4B218A8278AE5345ULL, 0x6A0C089BB51EBD95ULL, 0x182EC9E90D131DB3ULL, 
            0xAC0F9E799542893AULL, 0x891CC03BC2C66539ULL, 0x11B7FC3753B46BB4ULL, 0x9DAF073850959C86ULL, 
            0x109DFBC506417C8BULL, 0xE3801E40CD5E7136ULL, 0x141F7E8A6CCDC6FFULL, 0x8370B3DBCD420BBCULL, 
            0x71CE25E6D48C1F34ULL, 0x3C5F3242D509981DULL, 0x2F7FF5373D964BC5ULL, 0xB3F5F34859760FF3ULL, 
            0x5515EE0F148F84EDULL, 0x5105134212242B54ULL, 0x8079A687B6A241B0ULL, 0x826F379BC89E522BULL, 
            0x0DCD1E8057A7D707ULL, 0x3ADA788E0E71EE89ULL, 0xA23526B76DF35900ULL, 0xB7153F4A26360A70ULL, 
            0x92CE5417109A3D6BULL, 0xC255F0B99C4F1710ULL, 0x62106A157648E141ULL, 0x4CCFAEA6C20FA91FULL
        },
        {
            0x961D42AA2D35259BULL, 0xDC564137E5C278BBULL, 0x3633A07EDAC0EA5CULL, 0x1FABFF14C339CB05ULL, 
            0x29AC33024F89ECDFULL, 0x5B33EB008351CFD0ULL, 0x45B6D775BA6BB129ULL, 0xE068CF14BC7D577AULL, 
            0x16084E175B6D68A3ULL, 0x5F8356141DBEF14AULL, 0x8E0D0D193FACD528ULL, 0xD74A2DDEF9CD42F1ULL, 
            0xBE5EC39A78A7F730ULL, 0x295C7F9829211AB0ULL, 0x589A423D9548F3BAULL, 0x6C346915B1B4F416ULL, 
            0xAEB8A1949EA0F138ULL, 0x8C0EF07AC95AA65CULL, 0xF665188B1CDD611EULL, 0x66F8D8B3EB4A8DD5ULL, 
            0x1F968F7315DAC20DULL, 0xEDA3388601DA9317ULL, 0x1D74854190AA4778ULL, 0x8E089E1EE82AB72DULL, 
            0xD519E9C0206A119BULL, 0xB328757DA2B1969AULL, 0x9B1BFC74EC7201B1ULL, 0x9ED9D380C1707004ULL, 
            0x3C1F3130329B6347ULL, 0x0A095956E2137635ULL, 0x16656DC32A08CE53ULL, 0xEE172C11C965757DULL
        },
        {
            0x11B651D11FE7DBA9ULL, 0x7C2994EFFDC01E2CULL, 0x6FA4B6F3BBD3B33FULL, 0xE6A564581320CF8DULL, 
            0x86C76B02A971D244ULL, 0xC84B0407098AE9DCULL, 0x0AC89EDA8E6B7759ULL, 0x77F65F3BD62EFD0BULL, 
            0x3FA5425369F67F9EULL, 0x9D95AD9A2B5408AAULL, 0x2D2C65E81C5FBAEAULL, 0x3342A074CC144C33ULL, 
            0x285EEC01B9199151ULL, 0xF6A42018BC838D28ULL, 0x4D29114615ACC28AULL, 0x35C34F2FCF6096D8ULL, 
            0x49E5F60CB32CED45ULL, 0xEF389FB27CC48AD4ULL, 0x6040D4100BE4899EULL, 0xB7AFC4572A325EEAULL, 
            0xF47CE4BD1FE83B04ULL, 0x82B1CDC7AB25A477ULL, 0xF2C33F3D8F4855EDULL, 0x1C0D60CE1087C137ULL, 
            0xF7ACDB41FA792EBDULL, 0x3BBFE1BE3BF21C74ULL, 0x46561B234D622E2DULL, 0x7C47970690489D1CULL, 
            0xDFDAA3C995365C11ULL, 0x152F7DA3E0CCF694ULL, 0xEC83678599868913ULL, 0xA4E9ED54E1B663B8ULL
        },
        {
            0x21DC6B7E1DD4D28FULL, 0xD837F6DAADBCAC25ULL, 0x9F3040B2FB23B322ULL, 0x914C3CC2B9FC2274ULL, 
            0x328365EAF5D5B81AULL, 0xDB7D12CDF66A4789ULL, 0x61F0148288A4C043ULL, 0xD3B57A700084436FULL, 
            0x3859662D000EC1FAULL, 0xB3ED203E1B2C1DBBULL, 0x58C401EC3A20E729ULL, 0xA17274AE3DD6ACEEULL, 
            0x15FAF23F81303554ULL, 0x3C2643E7EB0FF0BAULL, 0xE881D8304AE219A2ULL, 0x3E3D3FA56878403EULL, 
            0x1B2E13685CEFBFE7ULL, 0x384F0DDE89600FFCULL, 0x303196CE9F7E816BULL, 0x9D745A49B3BB30AAULL, 
            0x7359AE7BFFD0EF5CULL, 0xAE267B210E0A8DC6ULL, 0x4408ACDFEAB617F7ULL, 0x9101AF4255FA31E7ULL, 
            0xC3CBB1B5E195EC9EULL, 0x7A1BFDA67E715411ULL, 0x0C123DF469C04C0DULL, 0xE457E0BEFA01558DULL, 
            0x592F8C8F22BB133EULL, 0x0144552B7A7F8878ULL, 0x255B3FD9DA769E00ULL, 0x48B42AB3322A4177ULL
        },
        {
            0x8098D5B34F02DD3FULL, 0x4D13D278D32EEBADULL, 0xBD2C26274844C02AULL, 0x8A5EB22B85A0A12AULL, 
            0x4B1603CC3036B68DULL, 0x2FD1B0800F5F3E23ULL, 0x81DA49A55678D577ULL, 0x6C373ADE9C22DDE4ULL, 
            0x7E78DCAF0F95BBEAULL, 0x8C8FEC8E0F16735CULL, 0x5138F21395BE56A1ULL, 0x739D401ED0D1966CULL, 
            0xBADD99B35733DB35ULL, 0x1A431F5783A1B641ULL, 0xE8FE09FD688D4262ULL, 0xB32FFE1D4267EBD8ULL, 
            0x5D46B7F21810CAC6ULL, 0x11C561C82472938CULL, 0xE8C695E16A8854B0ULL, 0x9A8E48590CB7100DULL, 
            0x508BE554198361C1ULL, 0xCB6947E33A7A18F9ULL, 0x6ABC4E1AB10935ACULL, 0xCF93FF8FD5C2E65BULL, 
            0x7F27096BEF112CA8ULL, 0x179E0E48374EC5E4ULL, 0xCD92716D5F6DAACBULL, 0x8465EE5D7CF1F5BDULL, 
            0x1F5B72DCE1155E42ULL, 0x23468FAF6F7668C1ULL, 0xBED21F0541946247ULL, 0xB89663E772783CE8ULL
        }
    },
    {
        {
            0x11AE768B4134C5A1ULL, 0x35FBB52EB3C70AFBULL, 0x8628FF745A3CD009ULL, 0x11A54DA205EF3058ULL, 
            0x047CA760EF0A2E17ULL, 0x0D4F2BE48E1B525CULL, 0xE47FA1FAEC491801ULL, 0xD646E3353F1EF8A4ULL, 
            0xC15DDD453786FD1DULL, 0xFC2A6741E84D4AC7ULL, 0x6C7A26644381249DULL, 0xA568971AFEB1ED43ULL, 
            0x8551EAF9B38BF8BDULL, 0x4CDFA5307C91EAD8ULL, 0x8794FFB9B3EE79D2ULL, 0x724C361F9485A3DDULL, 
            0x24E81132B0BCBCC7ULL, 0x4AE412598CF617CCULL, 0x8D25A7B90E5A766CULL, 0xB04E033FF3DF406CULL, 
            0x6F1832D2D6628D53ULL, 0x8DFEC2A946D78E33ULL, 0x6E0CD6DCC0A850DCULL, 0x44CA3EB8E15C9F68ULL, 
            0xC1B56A1E91BEDDEBULL, 0xCD7EBD9A42609B94ULL, 0xC9C8E83A3A61159BULL, 0xACD55F4DB90AEA9FULL, 
            0xC5E0823A66729707ULL, 0x9890A17BB52DE66FULL, 0xCF9B096CE5CFCC5AULL, 0x8D557E1719901E75ULL
        },
        {
            0x762890829077A781ULL, 0xFDB69494C17F3B1BULL, 0x966F310814FBDE1EULL, 0x0AE04873ABBECB74ULL, 
            0xB43AE26998BB3602ULL, 0x192810330DDAF1BEULL, 0xC5B3231FE2FB9824ULL, 0x3D31BC84E327B284ULL, 
            0x15FFA5027B223325ULL, 0xC927AEF0ED329074ULL, 0x5392ED9B5BFBBAD7ULL, 0x92B8102AEDAD694CULL, 
            0xFA8594C12405C23AULL, 0x29BBC040F1679208ULL, 0x2B7A63D0D977165FULL, 0x6523917E16210D38ULL, 
            0xC863D99FFE9AF4D5ULL, 0x63C9E370E8C4EA54ULL, 0x7AC90D6E4385B3C6ULL, 0x013EDBF90EFE244DULL, 
            0x1D4D1E584797A577ULL, 0x175362E8F0FB90C7ULL, 0xA61037BA86C3C38BULL, 0x3263DDD37CF5E1C1ULL, 
            0xC279F7E640AC16CFULL, 0xE7007361CCE7A9F8ULL, 0x3754467BDF2CFA24ULL, 0xFE96EA6A019BEBE8ULL, 
            0x22C22BFDC4A637C5ULL, 0xC8956B8DD7728672ULL, 0x09F700D3BBC73AA4ULL, 0xB30FB8DDB393150AULL
        },
        {
            0xF29394A6CE03495FULL, 0xA33E3DBC0E69C67AULL, 0x6E09A7F8E4FE9883ULL, 0x5ED70C4055BA548EULL, 
            0xF38302F6CF8BDFD4ULL, 0xA4049967BD4FEE27ULL, 0xCC9BABF3C720ADC9ULL, 0x500F7605C4D4D420ULL, 
            0xC6DA57C11ADD9A69ULL, 0x71FC9DD182014B00ULL, 0x13EA5AC8E5429836ULL, 0x390D42EBC9155072ULL, 
            0xCB8E22EFE069B775ULL, 0x5E2B2343953B9F8DULL, 0xFDA0160F11B3B4F7ULL, 0x9958CD85D0C4C58CULL, 
            0xB04F9976F1D3EE79ULL, 0x074C13F826ABEFFFULL, 0x71F509E47532D973ULL, 0xB84AF3289CCEBAAFULL, 
            0xD58A214FDA091952ULL, 0xD287493CE56AF70AULL, 0x31CECC096CFFFFE0ULL, 0x67BE4A9027BEC87AULL, 
            0x3CF9B1B2FB021158ULL, 0xD6E43FC0A40671E1ULL, 0xB810999BCC05FA65ULL, 0x1007FAF26D7072F5ULL, 
            0xD0BBF08BC8B7D96EULL, 0x3A4218D8582E7E33ULL, 0x72F0CF107FBD7793ULL, 0x369FD392C1717F41ULL
        },
        {
            0x16A5E67068E827B3ULL, 0xB7A9683074D53A5FULL, 0x9866DC2F44FA7FC0ULL, 0xF3D71769C03BA76AULL, 
            0x7FECE5E531A741E5ULL, 0xCA2E651817BDD0EEULL, 0xA6C415CAA21BE2B8ULL, 0xAC6F8FF697D01CB2ULL, 
            0xB29110760EB51DCEULL, 0x8D6971161623714CULL, 0x9E07BD018DD8401AULL, 0xE4E0F44869F72AFBULL, 
            0x37C5249CFEF2A894ULL, 0x1DAE0C3647DAF0C7ULL, 0x2C6831DE2F539CFCULL, 0x4CFB854FA6F1CAC1ULL, 
            0xCE88A657C8EDD915ULL, 0x0025B87B259089EEULL, 0xD3A984760CF54BEFULL, 0xB878F8E5F49A689BULL, 
            0x43B6170BF3D4A63DULL, 0x290FE728639DD7F3ULL, 0x7E72BF1A2BC1C836ULL, 0xAE99DC3A079040F9ULL, 
            0x0D56CFA726E5B907ULL, 0x3AEAB88C828448E5ULL, 0x4245622971CE4144ULL, 0xC3FCC49386538420ULL, 
            0x8B9C7619B5CCEDFAULL, 0x611647AAB18CB136ULL, 0x31ECFA9C230F25A2ULL, 0x59CE02B39B4037F2ULL
        },
        {
            0xC630D8C7057704F0ULL, 0xFA33AF4BA59CA7F1ULL, 0x87D5D5E595267091ULL, 0x15423F3467DE2E05ULL, 
            0x7C72BA8EDF1B6592ULL, 0xB22B28B8294549C7ULL, 0x216660F8EFCE3D39ULL, 0x845FB95488E94E79ULL, 
            0x62CA6048B67BCDDFULL, 0xDC979659F594E718ULL, 0xAB1AA9CA276F90B7ULL, 0xC3FE541EFB58DAF0ULL, 
            0x011D7F33A01614F3ULL, 0x1BEACFC51AD6C876ULL, 0xC8F7BB506F3BA89FULL, 0x9C27C28A983C2DEFULL, 
            0x94CD3E46A020DA5AULL, 0xEBFF104C223F4896ULL, 0x96B8F4C2EC3444F4ULL, 0x760FECB2E6C10E4DULL, 
            0x2784614D9237157DULL, 0x613338A6EC69B38CULL, 0x2AF6AFCA13A3C50DULL, 0xB8DD8E4164EEEBBDULL, 
            0x1BD6671A921A8C08ULL, 0xFC1EE34151803AFCULL, 0x306C5D891CEBE0A3ULL, 0xDCE40957E390E980ULL, 
            0xBB7ED0A60627BDCAULL, 0xD6E752A13420EEF6ULL, 0xE3513F0BA86CFF78ULL, 0x5FA5F108A640008DULL
        },
        {
            0x593B280E50AE6C3BULL, 0xB6457FC0168BEC5EULL, 0x04CA21715BB2A730ULL, 0xCBEFCC263243EE67ULL, 
            0x30E477D6FBC15653ULL, 0x755A4B7CEA99CB52ULL, 0x8F354DC48D1C9842ULL, 0x001B2E20416E3E18ULL, 
            0xD0258BA0E38A5370ULL, 0x200DCD5B7BE2C0D1ULL, 0x06E5B7683BDB8FBEULL, 0x42030EA3DD623257ULL, 
            0x0920E3C2ACA83F43ULL, 0x5D10637D2D194FF0ULL, 0x776AD951A173FD0BULL, 0xB934786F5E03A213ULL, 
            0xF48090DDA6163264ULL, 0x6289227AA0CD57EEULL, 0xFFB756561CA8F26EULL, 0x416D40B38D44DB29ULL, 
            0xEF68E52D4D11145DULL, 0x899DAA30D542531EULL, 0xB3AD6F8F6585EA80ULL, 0x582B4F3BEA4F207CULL, 
            0x1B11C1CC5918A393ULL, 0x8EA50C3FB1FB373AULL, 0x7C8A13906FE82F1DULL, 0xFA602D46BF687A9DULL, 
            0x3A387A42611CFDEDULL, 0xCADCFF539511F5EBULL, 0x9F8376A35451F070ULL, 0x53A18DA1DF9185F6ULL
        }
    },
    {
        {
            0x8AB464E3377EACEAULL, 0x3E3C419311C0C2EEULL, 0xE965DD70C8AC86EDULL, 0x8A3AC0A26792E0B0ULL, 
            0xB96A55FC45DA2872ULL, 0x49A2EEA44EB9D6DDULL, 0x8CED425713BCB534ULL, 0xDD12A7606270768FULL, 
            0x236B143CA93147B9ULL, 0x0580C97AC0C77FB8ULL, 0x24972D0096EC0971ULL, 0xECD33C7C41C55383ULL, 
            0x3D5FB761098CFF7DULL, 0x74F3123B2F69BF91ULL, 0xBA68DE7198701E81ULL, 0x982D5F611003FC73ULL, 
            0xDABB1E319991021BULL, 0x7E5EA502190A59BEULL, 0x71E2626A29327105ULL, 0x5B0798687C538872ULL, 
            0x74AF89BD2535F27FULL, 0x0E415E7B2CD94E5FULL, 0xADE24657D787DB56ULL, 0x44CF6B778A5B5375ULL, 
            0x2CDAF24DDDA916BBULL, 0x0CAA023A180AB038ULL, 0xCDD32B62650ECF57ULL, 0x6ED1B67D69FEE203ULL, 
            0xCC249449D55FA312ULL, 0x437C7FD69657A22DULL, 0x1703207152F488C4ULL, 0x0F7C35A223F9326BULL
        },
        {
            0x6BAD2BFA971A4784ULL, 0xCA92DE8286CE8311ULL, 0x93CD288AE28A708DULL, 0x4EBC9FF048DBE3B0ULL, 
            0xD265D6D207B5478FULL, 0x0E947D26F027A2A6ULL, 0x523AE1599B8C83ECULL, 0x6EC3E46E24B5503CULL, 
            0x8220F4241D32C1A1ULL, 0x1A3D4625513003BBULL, 0xE43C830D2C828B2BULL, 0x466B27427363A664ULL, 
            0x0C1A4B2AE51FFF8AULL, 0x6EBAD647BAE34CF9ULL, 0x0DC3D989BC17A7A5ULL, 0x74A2D21903CE6AACULL, 
            0x933EEFDEB08F2409ULL, 0xA748057F6CE33276ULL, 0x620B2217E401463DULL, 0xD427F131723EEA1EULL, 
            0x91CF978EF95211B4ULL, 0xCA970231B2CC21CDULL, 0x7EE8527A99B01B75ULL, 0x036BFE9D9975CDEFULL, 
            0x1FCD4C4772FADD03ULL, 0x46454564209B98FEULL, 0x18230E6A2E422F82ULL, 0x5EA6BB9A1E8CB003ULL, 
            0x4EE42E4F6D839490ULL, 0xE6B12EA8812699F6ULL, 0x814D3E67AB3C977CULL, 0x420424D34FBFA316ULL
        },
        {
            0x53A2C20E141D2D63ULL, 0x484D15BBCE6E942AULL, 0xC13D411F279C42D1ULL, 0xC493290A9806F10FULL, 
            0x7D4ACBC1ECC53BD4ULL, 0x2F0CBA3F1FF4E79EULL, 0x7C2451D0310C3BC7ULL, 0x3556A349B84FB25DULL, 
            0xA60A1E076B8C09BFULL, 0x12CD34DA6B50CEBAULL, 0x7F7CC5A9432BBB4BULL, 0xADEAA1EFA729C84CULL, 
            0xFAA47978A2FB318EULL, 0x6518647BBF96724DULL, 0x92CF4EAC632338F3ULL, 0xA1F166D9B8B33B8CULL, 
            0xD638B6C62500C9F2ULL, 0x606132F52FCA0AAEULL, 0x826D5B6DCD62F4F8ULL, 0xC5ADBF5ADD7C705BULL, 
            0x31CA124E5F6A2CF7ULL, 0x1D273F5DA9274159ULL, 0x22812986D2435B79ULL, 0x43588358BDAA85D8ULL, 
            0x2969094F6FCDD2EDULL, 0x6C4D54D9BCA3B771ULL, 0xB906B8C0DF054BC3ULL, 0xAA0E8D251B68191EULL, 
            0xF761049EF8375EB4ULL, 0xFD925952AF923AE2ULL, 0x59558D78B78548BDULL, 0xBDC6D80ABAFF091CULL
        },
        {
            0xDF0F4C61577369A4ULL, 0x18C6A1A10CFA74C9ULL, 0x2A241345F5EE1856ULL, 0xB9EA4709E9B4DB15ULL, 
            0x33E8A50D9E086BA0ULL, 0x9F71862B477DA611ULL, 0xE4AC071E60D99DD7ULL, 0x215B44A4B281EBBAULL, 
            0xA2A141C955B42FF3ULL, 0xB5D92DA5BC42269CULL, 0x54F079FF305C68D6ULL, 0xEA63BD4EA56F0485ULL, 
            0x4DD544644D1C07D7ULL, 0x897E0AA4930F760DULL, 0x5AB57B395A812FFCULL, 0x044FE760673050F6ULL, 
            0xAC5967EF2DA74A63ULL, 0x02873AB7D299807BULL, 0x0D471750C1131F48ULL, 0xC5BD94C10FD2B785ULL, 
            0x81B759D6D70C2237ULL, 0x6E949CC0A9A1F8A5ULL, 0x20323047583E0A15ULL, 0xEB15B487B6FA673CULL, 
            0x097938B8A394EA26ULL, 0x4B0A0F89125F68E7ULL, 0x87693DBA0653DA05ULL, 0xA4631D3584F56083ULL, 
            0x89144BF59591FE7CULL, 0x40AE501C42DFC2E8ULL, 0xC5F448EDD6614D56ULL, 0xDBCBB98E03D08BE4ULL
        },
        {
            0x6338F654DD05636BULL, 0xC7773BD06C2205EFULL, 0x3613B9FF90F0842AULL, 0x30F3BF1474EC33C1ULL, 
            0x8049A7DB8363A125ULL, 0x5E1CE644880C52BFULL, 0xA43DB0DC74D0F7B5ULL, 0x3C556455A149F1EFULL, 
            0x034CE5DED03CCE7BULL, 0x594DA4073E9181C1ULL, 0x9731FF59BD44DCC0ULL, 0x653C1CBEBA665633ULL, 
            0xED62BBE631D22E5FULL, 0x9073FCD5E5A743C7ULL, 0x83CF9BE9A7A7C0F2ULL, 0xC257FB9C515C221AULL, 
            0xD5489E8007B2D308ULL, 0x446D40EE93D40F81ULL, 0xA04BA44CDCB1B2DDULL, 0x4460756FF12DA085ULL, 
            0xED94662C54A2C3A2ULL, 0x9BF1E6829AA36FEEULL, 0x6AA2116641DBFAC1ULL, 0x2F563F627C125EDFULL, 
            0x96E2A52140EC2988ULL, 0xC222CA5884BEC28FULL, 0x437AF8346C5780D1ULL, 0x973F197A2B9723C5ULL, 
            0xB5F372638DB8C55DULL, 0xF9626D45E42626B6ULL, 0xF144E81378B436C4ULL, 0x4AEC401196432EC9ULL
        },
        {
            0x1FA813CA696BC328ULL, 0x6F2E77AB828EDF16ULL, 0x7E726C88B83DFC6CULL, 0xF8DB3E3BE2FC5FCEULL, 
            0x8EDC73EE71EB690FULL, 0xDCA0C179F566DCBCULL, 0xA27216A1C1493692ULL, 0x1A83AB22663F4597ULL, 
            0xD700B079ED9257C2ULL, 0xA0599FB5FA5DC485ULL, 0x9F6E679ABA34D833ULL, 0x87C16E9E61DE0790ULL, 
            0x3FBC0C11455F8463ULL, 0xB2C714F5E2491409ULL, 0xCE5A95E1B4DA8230ULL, 0x089239B3F1A3CBEFULL, 
            0x79F768541D48D898ULL, 0x3E73EBF1ECA5E07CULL, 0xADBDD4183CB4E153ULL, 0xA05457FB6503C3C9ULL, 
            0x64E432661C996F9FULL, 0x88A423E0C11CF812ULL, 0x4B8A0EBCD1E4286EULL, 0x1D40E9A372645269ULL, 
            0xFFCDE7849EE930B8ULL, 0x7AD83C9D345FAE77ULL, 0x93349ADA61846DC9ULL, 0x55A18C469149DF6BULL, 
            0xDBF3611A10F34E2FULL, 0x9D97863FB11FF033ULL, 0xFBF208B81CF3C5D0ULL, 0x5C70286B9FBE46D3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseFConstants = {
    0x9AA852611331CFC7ULL,
    0x2FD236D5523AA85DULL,
    0xE2453586AD8CEA55ULL,
    0x9AA852611331CFC7ULL,
    0x2FD236D5523AA85DULL,
    0xE2453586AD8CEA55ULL,
    0x1DEC53AE4D362D56ULL,
    0xFA32B92C863A9832ULL,
    0x1E,
    0x6B,
    0xF2,
    0xDE,
    0x21,
    0xE5,
    0x97,
    0xA7
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseGSalts = {
    {
        {
            0xE21BB9F0BB7EA786ULL, 0x8BFAB92BC43AB1DDULL, 0x88ACC267C200BFFAULL, 0x2067D951A1F1A7BBULL, 
            0x2ABEE5F4CFA5E97FULL, 0xD18335A20E02B61FULL, 0x35C158B381B2C7ECULL, 0x51884782CA97A273ULL, 
            0x9ACE32D9CFB16FADULL, 0x5D46341A626F0C70ULL, 0x9FE1E9F679FEC96DULL, 0x9D014CF7403A4B9BULL, 
            0xB055C15C276C9B8EULL, 0x6231A2E862CEF58BULL, 0xC040454D26ABC114ULL, 0x58CE27BE8AD3A948ULL, 
            0x546B691CF42F7306ULL, 0xC015F8EDF85FB85CULL, 0x6AF8EA6E86EC650BULL, 0xAC6FDF6CB8B12BEAULL, 
            0xBC693246834BC2DFULL, 0x852390E4D55BFCC2ULL, 0x6E59CCA607838CD2ULL, 0x62A46F008F3F8026ULL, 
            0xD6B7355442F304C7ULL, 0x5A692B24E7F0DB6DULL, 0x250F75DBE65B753DULL, 0x912BC425C06879D7ULL, 
            0x1B6E00DB2013A5CFULL, 0x8C9867A7A09084ECULL, 0x8EE748264CED7B99ULL, 0xE2A8785D10B6BFC4ULL
        },
        {
            0x4E16933C73B2EE6DULL, 0x21C32F8D2AAEC51FULL, 0x94090D661F730295ULL, 0x50CA5A88EE881C0CULL, 
            0x81C027E1813FF11FULL, 0xA4A5A4D9ACD8240EULL, 0x82D15A2DD5446C8EULL, 0x9BCF51F32C2BF6A9ULL, 
            0xF19B79C47F795538ULL, 0xDBA7B8A2769BDCACULL, 0x4AEDC6CDDDC1C914ULL, 0x7F3937F42666CD5FULL, 
            0x644D3EA55F74A7B8ULL, 0x59CB26037493FD1CULL, 0x5D37A3B0461F7D8CULL, 0xC22014144D01AEB4ULL, 
            0xF99D132F9F4E02A1ULL, 0x5548F213B7D58C76ULL, 0xCC3AB29855984718ULL, 0x19496122A2A410E9ULL, 
            0xB0A2255BF905C8DAULL, 0xDE66EE2A7953A990ULL, 0x239EF399C33997FAULL, 0x86E127A94036D43EULL, 
            0x7D241EE6710F9795ULL, 0x67FC3441A5BE0E1DULL, 0xD1B71CEC68829D91ULL, 0x590E546307FA2489ULL, 
            0x7851F7FA40CE624EULL, 0x92374257DFF07E3AULL, 0xA6F69D9698662CB6ULL, 0x5F2CE4D74524F9C3ULL
        },
        {
            0x859D5615C676F7EDULL, 0x73C11FF04E65C5FCULL, 0x93CE910DBC6042A6ULL, 0xC0C43D0F2D9E17CBULL, 
            0xB86B19B1FE6D3C31ULL, 0x9A07E7B7245EF86AULL, 0xC56EA7F6DEB2B51FULL, 0x9F5AE2BF7475CDFDULL, 
            0xF0309155289A25D6ULL, 0xD82461BBD69DF728ULL, 0xB272DA589D38F8A6ULL, 0x06403316284DF250ULL, 
            0x9D52C300D60B1F1CULL, 0x8F2F6CD9E286D4C1ULL, 0x18997A2423D3D1FEULL, 0xF2F93100C1CAE780ULL, 
            0xB1545337DE05EFFEULL, 0xEC1257FBD762E100ULL, 0x915FC55878BA08D1ULL, 0x34D312F0D0F6595BULL, 
            0x7272544D5BDCE91FULL, 0x5AD0AE077E9EA50BULL, 0x95A660E18F4E2AB6ULL, 0xAC88EF01F94A2909ULL, 
            0xF50237EE3D7B3057ULL, 0x6B902C23E426C6C2ULL, 0x49DEB99A0BBBFF42ULL, 0xD3E01CC2ABFD8FF5ULL, 
            0xE29557D9C61BC56EULL, 0xA3A3E4C0A3FA5E5FULL, 0xFB380832F5FB42FAULL, 0x1C218486A25F9F93ULL
        },
        {
            0x2B1ACF7FCFFEEDD9ULL, 0xC68DC80E0DFC1546ULL, 0x91948BDCEA3F7E1DULL, 0x0D52A4921C9A3FAAULL, 
            0xD67F8EF3052938CEULL, 0x8E6C9E13BDF882BDULL, 0xCE53D63DCC97692DULL, 0x1B8738396FF7667CULL, 
            0xBFF75016194545F0ULL, 0x1F08374C00872D40ULL, 0x74ABDDE685B0D4BBULL, 0x7ABB8F6BDBF04F77ULL, 
            0xA21E372255421B0CULL, 0xBBAC594F5E91C7C6ULL, 0xB4EC8B65A08E1A53ULL, 0x58F5DED674AF42D5ULL, 
            0x56876F95A115833CULL, 0xF4DBEA1710E2D0E5ULL, 0x0478B3E8483C74C3ULL, 0x3A3091CD1826D30FULL, 
            0xFBE9BDE0C85C4AA1ULL, 0xA58546E958F0A42EULL, 0x812E4E8D42CEF160ULL, 0x86E6C49CC3A6F6DDULL, 
            0x87CAD1266DB70988ULL, 0x3267D7F08B2E95ABULL, 0x7417DED4C59630F8ULL, 0x230443DA14283769ULL, 
            0x0712A368C60C1FE3ULL, 0x5070DB00A64E2540ULL, 0x68020D7C3BD90B74ULL, 0xAADBB4BDA26B0583ULL
        },
        {
            0xA8CA70CE5A052738ULL, 0x9F5405544B4E4F71ULL, 0xBE3A8DD00A259C69ULL, 0x01A9A43818F31207ULL, 
            0xB3688D40685E995FULL, 0x053CD1762646D7C8ULL, 0x273FDFA49D8FE8F4ULL, 0x052862A412E8C0A0ULL, 
            0xE210C87B864FFDA2ULL, 0x4D2A3AC5DA478F79ULL, 0xBC3ACD7EE44E72F1ULL, 0x3198F1400D709F7AULL, 
            0x09DF00F8C31326ACULL, 0x370F2D4EB79E68D0ULL, 0xB9DCF5D77A077243ULL, 0x1A8E3BF0104BE102ULL, 
            0x31F58C97AF6A5503ULL, 0x0741DFC96E159127ULL, 0xC0FCE8A211B8F3DBULL, 0xABB4CD19EC85DF21ULL, 
            0xE23493ECC022082AULL, 0x91C9522051249132ULL, 0xB51527506FA9CD45ULL, 0xC13E1F781E6B5F26ULL, 
            0xBAC8E6C8470D9627ULL, 0x29C7BDEFC5D30A60ULL, 0xA3F679C8F7DA7C34ULL, 0xC5205E80105140F6ULL, 
            0x295A34FDC323F1FAULL, 0xC7DA548E9C6E130DULL, 0x5EFD2D9EAD80FC98ULL, 0x16A4530987845B59ULL
        },
        {
            0x48D57724FDADE4CCULL, 0x458B982D5768280AULL, 0x96980E196830D958ULL, 0x5D45B9FE722DB7B9ULL, 
            0xCEAB8129A38EE12DULL, 0x387A3B64EFF652FDULL, 0xC6E94302AC156F32ULL, 0xA08B961F8F91236CULL, 
            0x711361B25B6D659EULL, 0x76F814F0D9180BF4ULL, 0x21DAAEC1B7225D4EULL, 0xB3676C91D579FC71ULL, 
            0x201AB95F7CD10252ULL, 0x12E0EBCA03AD76A7ULL, 0xB92EE661292EA6D0ULL, 0xA322C4E8B2E35470ULL, 
            0x73EF2EF8DDFE9A09ULL, 0x3AC0BA169A7E221BULL, 0x90CF4096D634DB4BULL, 0x92555D8FE3872A5DULL, 
            0x845853A5773057F8ULL, 0x5BA321434463FC2AULL, 0x9079C11B40AC03DBULL, 0xAABD0398D432C58CULL, 
            0x5889A317510FCFDAULL, 0x8AA6638DA99C3E94ULL, 0xB2B3C723B025B066ULL, 0xA17E50C36F35FF2FULL, 
            0xB61E09A4E61D0748ULL, 0x69F766DC2F9EFC86ULL, 0x25D2741AF7FACD0EULL, 0x43C37577568A84B6ULL
        }
    },
    {
        {
            0xDB4AEE18F989A6C0ULL, 0xAC0D47BCD3366B82ULL, 0xA169354D7B337D57ULL, 0xE414C1DE9C06E7E6ULL, 
            0x083CDB1E2DD09E26ULL, 0x17727F8DD724531DULL, 0x8F35DDFB5E05B6C1ULL, 0xF5AE8BA1021547DBULL, 
            0xBB2CB2EC5EB15C7CULL, 0x228DD9C9A04663D6ULL, 0x63298DDACAB9BC75ULL, 0x38787039F0D8DDD0ULL, 
            0x7D867F5AF3DFFD3CULL, 0x14992840CB95E64FULL, 0x487DC18F96B6A6EFULL, 0x76C983237735BCD2ULL, 
            0x0B7C7E940EE66965ULL, 0x46FFC1D64E39757CULL, 0xB88C685B8CF2672EULL, 0x70AB62D787E363CFULL, 
            0xE5FF9F11DC04D068ULL, 0xE2E3372D2018DA5EULL, 0x2A71679D483EA742ULL, 0x94FD0C79BD674D94ULL, 
            0x2CE74BBFE87AAC32ULL, 0x9145777172D067D9ULL, 0xC838D2632C0BB5EFULL, 0x0FFE6B7A82B3153EULL, 
            0x7342203E70A12F4DULL, 0x965E018E58F44BEDULL, 0x55DD2C640F5D08B2ULL, 0xEE6F7B6E35DDFFA7ULL
        },
        {
            0xFF73B35532E03D94ULL, 0x1D837C8226FCC276ULL, 0x10F659A2EFA49B4CULL, 0x78F20F75A5291DE6ULL, 
            0x8E5313A7A4C442C2ULL, 0x9071C6AA7513D4A8ULL, 0xCEBD8C5F49355E59ULL, 0xAD4E4E0EBDC6498CULL, 
            0xE604DC3BDB3963D4ULL, 0xE19CACB9A29CF21CULL, 0x2D49AD7397318DD8ULL, 0x2A65C6B8D9C2B301ULL, 
            0xE8842F9AD44DF3ABULL, 0xCD67F7513C517D70ULL, 0x600E743EA04176AFULL, 0xDA421A5E8D37412CULL, 
            0xFE93FF43B4CB4BCEULL, 0xDE42177C0F1527DFULL, 0x8FE1675292218467ULL, 0x4422BE9260532850ULL, 
            0x16A5257CFFCB86ECULL, 0x898521D3B5CE3250ULL, 0xA23587ABA07C7693ULL, 0xB762511E3FEF5F69ULL, 
            0x6B76E37138DF540BULL, 0x066A54669AEAF6E1ULL, 0xE45B0271B084CD16ULL, 0x29A42A1B49DCB66BULL, 
            0x66C6E80A49CC3062ULL, 0x97AB808317B66806ULL, 0xE7867FEE442AF8F3ULL, 0x19D1934A5652498FULL
        },
        {
            0xD40EDCD190DBCA81ULL, 0xAD14DF8F2B4E7DA2ULL, 0x3E16044735EB9F9CULL, 0xCD1D970AC993565AULL, 
            0xF04629C24075E1F2ULL, 0x0CB2755DA82CE166ULL, 0x9A44C1FDB48CDC3FULL, 0xB2FFF42790830AB2ULL, 
            0x39A8735AF2608EEDULL, 0x7FB17E1B2BD1DE61ULL, 0x00B8FB5309A6BC6CULL, 0x199EFAE37C439FC3ULL, 
            0xA344F79DDAD1F056ULL, 0x2B51E5A6AF332FDBULL, 0xBFF7B9EFD5B6B0D3ULL, 0xCC9FFFC644763430ULL, 
            0xFFB8C3898A234DABULL, 0xA8E4EFED08588B5DULL, 0xE47604A9D6657832ULL, 0xEB0B59088F1D11CAULL, 
            0xD16E41E51AC89858ULL, 0xCCAA771EF996740FULL, 0x215D9AA4BB83328BULL, 0xF3DD54D96ECAAFE6ULL, 
            0xDDE72F34031BFB9EULL, 0x3435F96DC1BAAEADULL, 0x2312F3DCA8B0EF35ULL, 0x322702F0F7135B13ULL, 
            0xA67B294393AC0326ULL, 0x175E74052087FD00ULL, 0x1A4A2EA3BA50CA03ULL, 0x293966842EBF5EE0ULL
        },
        {
            0xB2C87FC42B7AFB6AULL, 0xB37AAA6CC86871FEULL, 0x965C2DC555F94746ULL, 0x876768F4CA62EC75ULL, 
            0x42701D515CC31C2CULL, 0x409D8C6187FF7CA0ULL, 0x785149D218DECCF8ULL, 0x8E3AC9AF5F7C1EADULL, 
            0x5CC78CD8F891F109ULL, 0xBDA4EC56A7EE6DBBULL, 0x1242E0DB6598B5A4ULL, 0x9082875389C6B541ULL, 
            0xF4D904888F3568C8ULL, 0x9C70775E9B07839EULL, 0x3A4ED846BE599856ULL, 0x75D110F14F4365E0ULL, 
            0x69ECCD1FE301F1E7ULL, 0x3B99F8AE2ED97C4FULL, 0x8BE898136C0EF9C2ULL, 0xBD16E63E22EB7096ULL, 
            0x8676AA11113B77BCULL, 0xDE5A3D5D1F667082ULL, 0x7A19D0B3C5A595EBULL, 0x9DA41DA3B86C76F9ULL, 
            0xFCB05326D3FA4B3FULL, 0x8C72E84CBDA1C755ULL, 0xA0A0C65067D4B697ULL, 0xC5A8A0086AC2808CULL, 
            0xAE438A00B291F85AULL, 0x7CA11DF77EB20410ULL, 0x6BCB4148678B6168ULL, 0xA177D34959EF8014ULL
        },
        {
            0x88D7A56E9C73F143ULL, 0xBEDAE0DC16394E9EULL, 0xE4FEEC9FABEA3E56ULL, 0x78525A5B053D151DULL, 
            0xD0FF066CD8E623EFULL, 0x7E1318ACBA2961B8ULL, 0x9EE320AE712A7BF8ULL, 0x658546FD39993BB5ULL, 
            0x0CFA98811E08B4C2ULL, 0x8186BD4079D04DC8ULL, 0x5DADBC425B392163ULL, 0x53FCA70C9F5610B5ULL, 
            0x97E7CF6AACC011DBULL, 0xEC75345FCBD7BD1EULL, 0x4B01B036F48CBE17ULL, 0xAFBECB99167F2502ULL, 
            0x87D8255643D65796ULL, 0xB6B873EDCBD60038ULL, 0x9748D53B1BAC71D8ULL, 0x97FF67247912E885ULL, 
            0x6F61E9DACFC1D571ULL, 0x7AAC0CD96ADD0352ULL, 0x9E9296EF61E39A67ULL, 0x7E85AE90ED336FA3ULL, 
            0xC49A5534B4D40AE5ULL, 0x48F2EE06F21948B1ULL, 0x3D83EB73E9B143F5ULL, 0x6DA7D4844ED4EFD3ULL, 
            0x566FB980270E1449ULL, 0xE1901E7EF95C8861ULL, 0xC80FD59EE4E972CBULL, 0xABB7F74D85AAFF1CULL
        },
        {
            0x2C8AEDADF3EFBFA8ULL, 0x51A613C0152556DEULL, 0xEFB1F451FB31430EULL, 0x5843D51CDAD30415ULL, 
            0xD0813DADD2085B17ULL, 0x53876AA79C932576ULL, 0xD75AB24C6AD4DCC8ULL, 0xDA281B96169C9287ULL, 
            0xE756A41CA38F8934ULL, 0x0405A5B22DFE814FULL, 0xCC8DD089AF98A40BULL, 0x9EE8AF2ED2A40EA6ULL, 
            0x31DA14ACC2FFC4D9ULL, 0x3645F22DF42FBA5AULL, 0xA6EB9374673A79EBULL, 0xF698EB6DDBB71739ULL, 
            0x17F06CB0FB2CCD1BULL, 0x3FF8CD176F67F1CEULL, 0x10F88529968C7DF2ULL, 0x1BDD634637D3039AULL, 
            0x32A02ED09C17D71AULL, 0x1726356789AD2E83ULL, 0x7D6B860ECD52BB35ULL, 0xE919F363C55D6055ULL, 
            0xE69E188F44B4C09FULL, 0x9901C9D57038AE5EULL, 0xCBE1F0C236C2AC45ULL, 0xB582976019C39681ULL, 
            0xB49CCFAB4538E538ULL, 0x6B51860E5F99CEDCULL, 0x48ACF30CCBB197BCULL, 0x1FC1226F8D7CC1BAULL
        }
    },
    {
        {
            0x73C56E614106E9A0ULL, 0x7EB4FAD5C5B934D7ULL, 0x71D04267084F1628ULL, 0x510B27028DCF24FCULL, 
            0xFAC68CD24F28BDC5ULL, 0x360EFCF50E86A9A9ULL, 0xB23605B394140EBAULL, 0x3A3E78823BF4670EULL, 
            0x19A1A7BBA0A032ECULL, 0xEEF031D4523FA193ULL, 0xA73994ACC66C6C72ULL, 0xC925F630BF145185ULL, 
            0xF2CC0A687A1E8381ULL, 0x53B1B443465DC41AULL, 0x107B324E3EEE4023ULL, 0x8DFA63572681A4F3ULL, 
            0xA670C3552A5E2E1CULL, 0x9F8B3755108DDD85ULL, 0xE2FA96333F85782AULL, 0x6D28EC035A08FDFAULL, 
            0x96F765DAF1E1C637ULL, 0x6D005416A317EFBBULL, 0x8BAB1BEF3BE2C313ULL, 0xBA27B5AF3C1639F8ULL, 
            0x720E00FF7656330FULL, 0x76BE9E2278C7F6F4ULL, 0x009A4756DA80278DULL, 0x38605B814C270718ULL, 
            0xDBD01ED899EE23C5ULL, 0x1460FE55D2055AAEULL, 0xEF324B741948A10DULL, 0xFDCE9E9066628959ULL
        },
        {
            0xA1B74C8D4F0FDA46ULL, 0x3B5BFD0ED2674F13ULL, 0xBDB9CC0A7B461081ULL, 0xB73EBA538C88089EULL, 
            0x3F0E0D17589A01C0ULL, 0x75418BDC3A1D3B1EULL, 0xECF2E6F5D2DA5B42ULL, 0x280D7579BF9E2A36ULL, 
            0xAF5A9F42323815A9ULL, 0x18718FB07A19BAF6ULL, 0x5D301CFD0F4EC05BULL, 0x60568E423FF6BB09ULL, 
            0x8A50A78D616B7EB9ULL, 0xABAF4947298EC245ULL, 0x5AB9AB0CE1915A01ULL, 0xBE2FE73E79117E87ULL, 
            0xA24D523FAE8A4BE8ULL, 0xA9CBC80708C218A6ULL, 0x00500C67A6C0039BULL, 0x292DC74D1147C8E8ULL, 
            0x21BB54913E673F14ULL, 0x9893E6AA168A4B83ULL, 0x010044F9791FE549ULL, 0xF51619A6A8D3F725ULL, 
            0xF84AA43E830E6A33ULL, 0xB9A838AF5977975CULL, 0x3BC22E68DA90FDF8ULL, 0xF6949F88227B8857ULL, 
            0x1554737ED5159760ULL, 0x8C98268421869309ULL, 0x3DA0DBE6C2859199ULL, 0x9456316E1121FF7DULL
        },
        {
            0xA52EE3353011BE5BULL, 0x4D656FCCDD0B0246ULL, 0x0CE931ADE6F5D8AFULL, 0x7FF7044B7DA616D6ULL, 
            0xCDBAA7F796A640B0ULL, 0x1469C593F2084A4DULL, 0xC56E6B18AC5ABF16ULL, 0xD0B81A3BF9E03934ULL, 
            0xBB07A6AE7116EB75ULL, 0xB811E5F1E49BE5FFULL, 0x9394919A4A60619FULL, 0xA7880BF960FEBB76ULL, 
            0x8D13441AF3FA3599ULL, 0x0F62C70583939490ULL, 0x3D253A3721A8531CULL, 0x0400F41FE93101CFULL, 
            0xCA7EF83315690614ULL, 0x1D4E9DFD624D5934ULL, 0x42173D2089BB686DULL, 0x5FF528306123520CULL, 
            0x2E1940B902ECC30EULL, 0x8CD34CEA94339542ULL, 0xAEA6DBFA2CEC3E84ULL, 0x5F26BB3606A4B448ULL, 
            0x2EE29E2141FCCDDFULL, 0xED7D847E367B1FA7ULL, 0x391EC88280175507ULL, 0x886B298808D45B9EULL, 
            0xB4814F5DDA122E6EULL, 0xA5E52E13FBD72CE4ULL, 0xB1E4446DA30F481EULL, 0xF4CFC223808D38DBULL
        },
        {
            0xAE590D954CCAFE5AULL, 0x1CD398558C7F75E1ULL, 0x5BBD30DADD0FF497ULL, 0xF489BD25A09883A7ULL, 
            0xEC6D3D4039FE9E4FULL, 0x8DA092FEE5CEDE01ULL, 0x4E8AE5F85EE79DE3ULL, 0x7430605D4DE81D4AULL, 
            0x147B52329B2B4FD2ULL, 0x9904220A7EF13DA5ULL, 0x3E8F665991DA9420ULL, 0x3ED7D26AF803D484ULL, 
            0xA581E3D486D30718ULL, 0x7F9CA7619ADD2150ULL, 0x5E068D3755227789ULL, 0x795E1724EBFA04F9ULL, 
            0xE8B11D37AEFC2283ULL, 0xE0E2F5210468FB0CULL, 0x25DC05B3582A26FFULL, 0xFCCD60CE29FEA867ULL, 
            0x1CBF3EAE46FBF7FAULL, 0x5C8A93F025C81574ULL, 0xF7DA592E7B164DEFULL, 0x625DAB5906FC8872ULL, 
            0xC8AEAF0B0D3F8B4AULL, 0x13257D9307D0ACE7ULL, 0x0ADA22EEB06D7A97ULL, 0xF56AC6E773B22FFCULL, 
            0xE9B3E097CF5C0101ULL, 0x8A3E222E11CABE68ULL, 0xC77FA5BF09154A93ULL, 0x8A84EBC275BB9095ULL
        },
        {
            0x7CE83B704BE8CE78ULL, 0x8DDF7AF491563918ULL, 0xF9F324A54775C70EULL, 0x9AC4602A8B1A24AFULL, 
            0x19FD1997BA12EDADULL, 0x8FC7BC4B22EAB763ULL, 0x72706D4CED341843ULL, 0xC3B5610837B2BAEEULL, 
            0xB932B14EF9658976ULL, 0xF04EAB78BF1283B4ULL, 0x12249DB3DFE02C5BULL, 0x4786B62A19D5EA75ULL, 
            0xB36140D269F42A0DULL, 0x570C51444AEBD4E9ULL, 0xAFB8E8A35BC7A856ULL, 0xA1ED88E2CCF1F0E0ULL, 
            0xB3770CA92FAC38D8ULL, 0xAE4D0548AB3F2176ULL, 0xAA65DFD931C1917AULL, 0x20041F032C49F6A4ULL, 
            0xA6E90332F0F1F7F9ULL, 0x18C06E354FCC1DDBULL, 0x7DB2FE5916733CA8ULL, 0x8EC441F166FAD5DBULL, 
            0x1F9003E6AD48B6A4ULL, 0xA0B8FD7FB77327FDULL, 0x0C6C40E51FBEA847ULL, 0xBA7DFC8BC6964FA2ULL, 
            0x4EC24E10E4C72C81ULL, 0xEA4F01BEDA24E6F3ULL, 0x46A16A64A0F3233BULL, 0xB4052D52F6BC4B31ULL
        },
        {
            0xEEDD6961558510ACULL, 0x1F2E0CDC4CEBC2E9ULL, 0x2462755FFBA62846ULL, 0xDCD5C199E853C2CBULL, 
            0xEC9B22490E6E934BULL, 0xA2FC29E3E19EE8ACULL, 0xB7A8220B7C363A0AULL, 0x7ED20922C43DA7A5ULL, 
            0x5EDAADC519611EEFULL, 0x8F0E2529309E81D4ULL, 0x67B578639B7A5E60ULL, 0x304D21B4003BCE35ULL, 
            0xED67CBD1C674352AULL, 0x1A1A511F609A83DBULL, 0xEFDD3AD6A80BADA8ULL, 0x03E5188807F09B0BULL, 
            0x5C65D77C001CF842ULL, 0x179AAB4159B79FA9ULL, 0xCEA01B7C4D60F0A5ULL, 0xEA8190C85D8FD99FULL, 
            0x7A2F9F011DB0AC93ULL, 0x8CDF6A1CF6FDF260ULL, 0xB0C5FBFE14FFC19BULL, 0x42021F4DEE657DA9ULL, 
            0x20DE3A32B1EB24F1ULL, 0x4ECE5570AFE74CACULL, 0x76C1F4311AFE36C6ULL, 0x192D6C61BD9419E7ULL, 
            0xCF16CDED5CAA4EBEULL, 0x06DF7C9F46FF65E7ULL, 0x915170A3315B4FF9ULL, 0x7C56A62FD4CE749CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseGConstants = {
    0x6E9CA07C7E14F27AULL,
    0x15738B3CDF1715FDULL,
    0x0A0A3CC74215B4C5ULL,
    0x6E9CA07C7E14F27AULL,
    0x15738B3CDF1715FDULL,
    0x0A0A3CC74215B4C5ULL,
    0x55C1B58FA63F3AF2ULL,
    0x06C7BAF55ABC770CULL,
    0x1F,
    0x63,
    0x86,
    0x9C,
    0x7B,
    0x77,
    0x53,
    0x73
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseHSalts = {
    {
        {
            0xDC9F44C5AD1E338AULL, 0xBE867328CC2B7422ULL, 0x76B0A1FE22F31561ULL, 0x2DBE3ABA8639EFF1ULL, 
            0x0C3848CC933E46FCULL, 0x6F46CF9566644666ULL, 0xEA68813D820042F4ULL, 0xE522E928BAA2F7C4ULL, 
            0x2705D4298AE53237ULL, 0x293CFB0725864798ULL, 0x2E2FDD4349CD563CULL, 0x9E4BE3EF93387E36ULL, 
            0xB03B324CACCEC160ULL, 0x2D65921C489CC4A7ULL, 0x6E75619EEF7FF298ULL, 0x31FA9CDA68953445ULL, 
            0x61D05B2F7E0B7AB2ULL, 0x455F10E54D4959F0ULL, 0xA688D4CCA0623422ULL, 0xC1C40C69CE907180ULL, 
            0x0FCA5F9AACA0FC29ULL, 0x421E16733595AA15ULL, 0x71660D70AF0E4AB1ULL, 0x96ADD7CC76D338E4ULL, 
            0x3AECDB34C3E0D81CULL, 0x371B5E812ACB266BULL, 0x2CFBB97129D34957ULL, 0x2826DB4A2A4CB235ULL, 
            0x9AE84ACBBE299B03ULL, 0x8879BFE1D35C793FULL, 0x671BE4F364C2A4A7ULL, 0x38A4FD1EB8124E77ULL
        },
        {
            0x8E765AB632595AB2ULL, 0x86D75A2DB17C082AULL, 0xC4153771967BFAD8ULL, 0xB32A71E14EA095EDULL, 
            0xED85BE5B6A484383ULL, 0x90AC00AE0CCA54FFULL, 0xBA133A2BE54A9F25ULL, 0x706CAC6CB4240B53ULL, 
            0x870DB6AC45E194CBULL, 0x6940E909ADB01ACCULL, 0xE0952E6F6B00A0F6ULL, 0xA3279C95BB332C52ULL, 
            0x3A5582586B72EBB1ULL, 0xD53AF25C8DC549C5ULL, 0xAA914E3A71AE53BDULL, 0xC72144BB55871811ULL, 
            0x243AF29EEB59E157ULL, 0x9FF4BA7026FF3866ULL, 0x5BDB13FB6C9FBF7DULL, 0xD8314C00CEE6BEECULL, 
            0x3F02A8D927C6853DULL, 0xF21E5C332EB774A2ULL, 0xC5BEB00BC475E51AULL, 0xFA507BE87949CDB4ULL, 
            0xDC21B695DD71B85AULL, 0x45E5049FAD948A70ULL, 0x7C4C6009FAE4FAE0ULL, 0xCAE395C89E071A4BULL, 
            0x9DC37FA4F479C9B7ULL, 0xF7B29CB6F7871698ULL, 0x6E073966B857765AULL, 0x049D9CE734211178ULL
        },
        {
            0xF50B0181ADDFE0D1ULL, 0x690A47374E20178CULL, 0x5066E0D5824CDF07ULL, 0xD97E7C97A48D1ACEULL, 
            0x3CDBA2AA8B39C862ULL, 0x2D7A8AD95181FD73ULL, 0x6657299487AD8460ULL, 0xC6FBD90F0DA6823DULL, 
            0x55611A810370D9FEULL, 0x0C7DDC943737DD99ULL, 0x873C348965B68CFDULL, 0xAACCDCF58397C68DULL, 
            0x89FC5E89F34DEDBAULL, 0x3259725E9FEF667BULL, 0xBB5DE5FD57AB0043ULL, 0x8890524CF8E29E34ULL, 
            0x2BBB1A334C4E7F9AULL, 0xBE6C0D6719615011ULL, 0x0DC7A522E75557EEULL, 0xA8265021440005EBULL, 
            0xF8329E109570166DULL, 0xFA3270290534345FULL, 0xC4FF021902E941B1ULL, 0xDA5015B8F17DEE72ULL, 
            0xFE9FD481A406CDB3ULL, 0xBB2E9F6BB076A318ULL, 0xB55BBADDFF9425C4ULL, 0xCBF3AFE2772015EDULL, 
            0x9DF55BD7326D04B6ULL, 0xF2D421D68AF617B3ULL, 0x7957A12FA1292EB6ULL, 0x98EEC8C1820EA496ULL
        },
        {
            0xD96B60740949DF09ULL, 0x0FF8738173301D2BULL, 0x506C080CDF2400C8ULL, 0xB03AE0AC486E95CDULL, 
            0x9D8A5EEE80E4EAC8ULL, 0xEDA5A62DA398CF70ULL, 0xCBF4BC5646FA9667ULL, 0x86D26E88F5011115ULL, 
            0x2588573BFE6457FFULL, 0xD97F70C3FEBF22BEULL, 0xDE1D88A589A7DF2CULL, 0x81D355FA48466A18ULL, 
            0xA05BE380D0F022FBULL, 0x7588E1EF628CECD7ULL, 0x7DC905CA6CE44A69ULL, 0x36163104DF5E124EULL, 
            0xFA0028579F132D0EULL, 0xBBDE5F1F8E7C3C33ULL, 0xE08F5CC74DA4E6A5ULL, 0xD85444F6C8A049DEULL, 
            0x917316C3091324F3ULL, 0x49097B86FA0C35D6ULL, 0x01D6F1C07AD6BABDULL, 0xAC3C335A9778E998ULL, 
            0x1C178619AD34F10AULL, 0x02C216054EBCB3CDULL, 0x481AA8C792AED501ULL, 0x046871AD0B75E2B3ULL, 
            0xFDB10BFDF5E92016ULL, 0xEAD6FF98FA0C64B3ULL, 0x3654DB21679188BDULL, 0x77A2C55A742D7C2DULL
        },
        {
            0x126909F2D1972A4DULL, 0x0D85ECFD9A8AC2CCULL, 0xC60A15AF8E55EB38ULL, 0x7D12BF72C3FB2F10ULL, 
            0x3735132D29A2FA51ULL, 0x992F4BB8BD01EDEAULL, 0x8C08B6D097D7A3E7ULL, 0xE52341D3920016F8ULL, 
            0xA927A8AC26B1ADB6ULL, 0x52164C1EC2233382ULL, 0x66A5ADDF3073ED59ULL, 0xAF6CE829A2F6F758ULL, 
            0xD052B2D7192998CCULL, 0x281B0AE0A319C3DEULL, 0x68C33AC1DAB5900AULL, 0xEE8113ED3D824017ULL, 
            0x2B21460E4CC6CF3AULL, 0x019804D04D142945ULL, 0x21294E069886FC4FULL, 0x743FEDD264198917ULL, 
            0x9EDFC1E62332CE1AULL, 0x75448A633958241FULL, 0x154F4D115C9C53F4ULL, 0x5DD4F373F6F2C02AULL, 
            0x45F583FF369C4F48ULL, 0xB0D4B0A789C7BDA4ULL, 0x707017D686C2BAF8ULL, 0x36F95A135F1E1BCCULL, 
            0x2062888638C5D261ULL, 0x5B6DBEF2A70B366FULL, 0x71935D5AB9A8BF7FULL, 0x21EE702B837449D5ULL
        },
        {
            0xFBA0F77387CCFC1AULL, 0x31C8BF4EC2B5A422ULL, 0xCBD74B472849EA6DULL, 0xF45EDBF54B5F1039ULL, 
            0x42603002ED67DA2BULL, 0x9D5DB114C1CBDAC1ULL, 0x447AB96F5E9E3929ULL, 0x2A06626967C82E27ULL, 
            0x1D73C1A395A0D969ULL, 0x3A96D1571F95C654ULL, 0xE810574E06E378B9ULL, 0xF789647708895EA6ULL, 
            0x0C5FA1A8CB9A6352ULL, 0xD7B22BE90C9088F3ULL, 0x5ED78E1D3A013DBFULL, 0x75E8444E5E908F5DULL, 
            0x454D7D497EFD9D81ULL, 0x389DA538BC53EBC0ULL, 0x566EF5AE3F3ACB84ULL, 0x97D2C0E4F7300EDCULL, 
            0x2697C6BD69E181D1ULL, 0x158F38C70FBDF97EULL, 0x7EBB69B2E1351158ULL, 0x5A5955F41411E65EULL, 
            0x164F560AA2B0C017ULL, 0xAD995411A24054F9ULL, 0x7FE7683787485CBFULL, 0xD63AFA497A1017F8ULL, 
            0xF285B7BC91369B5CULL, 0xBB0B1AA7B3064968ULL, 0x38168F1C14DE66E4ULL, 0xE35A2C061FB2B041ULL
        }
    },
    {
        {
            0xB23384D2DF59AC82ULL, 0x54E9279FFD300232ULL, 0x65B35162E7887FC2ULL, 0x7B3FDF2D680F3057ULL, 
            0x9ECB748769FC38EBULL, 0x431A0E815EBFD154ULL, 0x6E87605ECDE92ED1ULL, 0x47B7EB308D054439ULL, 
            0x7EB8788B826A07CCULL, 0xC9BC5F85FB6CE970ULL, 0x74BD76E64451FF90ULL, 0x15E833F3831EB946ULL, 
            0x783A2150D5365DCBULL, 0xBA6B65EC7A30D837ULL, 0xA01C30E68AD47F8DULL, 0x21566DA9EE51D43CULL, 
            0x4004CB7CE25F5A5CULL, 0x7A87ADA63CD7B027ULL, 0xAFD0C6CC9E1498F7ULL, 0xC78EE1C691922696ULL, 
            0xDAA43A3982A93A96ULL, 0x0C361DA1AC277B6CULL, 0xDB236FD820B6F3D3ULL, 0x62E79AB004DB36C8ULL, 
            0x49987C8964860443ULL, 0x1039BEFE5DEC7413ULL, 0xF09261996B4CABF6ULL, 0x21AB63485090C4A2ULL, 
            0x9693CA5DA4D0A697ULL, 0x6DFD79D03FB4D5F5ULL, 0xA7A93EA19D913F20ULL, 0xB507CC9898F12625ULL
        },
        {
            0xE099D9B611023E26ULL, 0x71336183BB23C14FULL, 0x7B17BAA4F3E9D08AULL, 0xC7BE320EE05B59FBULL, 
            0xDC29555269FA993EULL, 0xAAA5F8D6BAB89404ULL, 0xDBA0B59469263F7AULL, 0xFCAA194BE3964231ULL, 
            0x95BFADC4CCCC0162ULL, 0x3C0B92D30EDF9808ULL, 0x70D2E082418ECAC4ULL, 0x4FFB25657AAB14B2ULL, 
            0x6AEA45FE016E1AEEULL, 0x98765A51FC3F9ED4ULL, 0x18BC431AB78E6D45ULL, 0x994DF2F28B4CD0F6ULL, 
            0x2BC8C1809888087FULL, 0x60463582FE0B297EULL, 0x4679764BC005B643ULL, 0xF92A6D75F043245AULL, 
            0xFC3562B2AADA73AAULL, 0x8188AB85FFD5D753ULL, 0x7691244A3AD78254ULL, 0xACE0AE3848B0D90FULL, 
            0x69D33D8BB6B1E09FULL, 0x3D2493F876C0D3B7ULL, 0xD91B5E8125EA2F7EULL, 0x3E98A3B93DCD580EULL, 
            0x9067856B0D9FE0F9ULL, 0x6883DC7A56668603ULL, 0x12CE285C8949D6D7ULL, 0x5B66313A31D5715EULL
        },
        {
            0xD0DAE6616BBD620AULL, 0x10458F1F2FE3AA03ULL, 0xF4B29028213E6E0CULL, 0x1E1D16B9DA49B8BAULL, 
            0x8253DA3F1014BDB4ULL, 0x3A3580BC56CC5EFEULL, 0x85EE516B7DC432B9ULL, 0x371FE5AF86B97EBCULL, 
            0xADF384A9B29B5D66ULL, 0x232DDF0BDE1A8332ULL, 0xF783A630992674A0ULL, 0xF4F4B963E57D5802ULL, 
            0xCB9EACB3C60F977EULL, 0x321BFF445F1A7A00ULL, 0xD3073FC6BC27B412ULL, 0x5331430E32ECEA99ULL, 
            0x45B0B1521A458A40ULL, 0xA9E4657518F008E9ULL, 0x053A466E2CFA396FULL, 0x26EDC7D2EA9D971EULL, 
            0xCC0EE9A8B9AE77E5ULL, 0x1F9FF59B01A80A1BULL, 0x16CC101D408821BFULL, 0xBE9211DE5B626DDAULL, 
            0x51CA8199154B0AC5ULL, 0x281AC7F0DF78A619ULL, 0xBB6FAA844020649DULL, 0x08FF201BE33DB6AAULL, 
            0xDA45B44B90B6BAFBULL, 0xF38671E31AAA58D6ULL, 0x46B879F9C0D33547ULL, 0x98DEA0CCF6B33ED3ULL
        },
        {
            0x87DA2207100120A1ULL, 0x132E496DF5EC70D1ULL, 0xE7A7BAFE94FFD769ULL, 0xE823E566F1EA62FFULL, 
            0xA3B925F0E64D885CULL, 0xF12E21630A56E9A0ULL, 0x61EA9762E7E96525ULL, 0xE72F6F0A7E29C367ULL, 
            0x6338C13519C0B138ULL, 0xFD2CA58C443BB220ULL, 0x12E071D01AC2B950ULL, 0x63E3AEB31EB194C1ULL, 
            0xF787C6EDB6746A63ULL, 0xAEBEAA49013E5976ULL, 0x358D71C58DD8C827ULL, 0xB9B7E607AFEBF749ULL, 
            0xC1CF58FE8B634141ULL, 0xAD2C3F0284FB1BF7ULL, 0x5C6C461D266AD4B7ULL, 0x69E7DF9E261201AEULL, 
            0x45F004224ABDD967ULL, 0x764ABFA8CA55468FULL, 0x29CE8615C138DEA5ULL, 0xFA991AD80436DD33ULL, 
            0x6413443B93AB0CFDULL, 0x002B1463C87A15B7ULL, 0xC52940F313C939BCULL, 0x7933943B945ACF32ULL, 
            0x6A2509E691F8580BULL, 0xF81838820888E4CEULL, 0x1E31A89A86200EE6ULL, 0x15D78F46F545E934ULL
        },
        {
            0x1AEBCE8B9550481CULL, 0xE0BB7E8117B014FCULL, 0x2754E4120B92AA11ULL, 0x613E21FFC914541AULL, 
            0xAF64D662772D45DCULL, 0xBC69AB10A8B25256ULL, 0x440E32CD2C700B94ULL, 0x6478CD2E06AB45B0ULL, 
            0x5A352070B6E2DDDCULL, 0x516F52B573790F03ULL, 0x1B5146E337702DE9ULL, 0x90A0906B98A03C2DULL, 
            0xDC04B513045F956DULL, 0x043D6BDFE8B2312AULL, 0x6AD028B26CAC8CA1ULL, 0x989C592CC6A31F04ULL, 
            0x90C75DDDCC5D4881ULL, 0x2A1E9C6F7E11C0C9ULL, 0x0973A993E1B5D580ULL, 0x8214AA90B10DC18CULL, 
            0x9FA0D730881024CFULL, 0x4DCDF649D0CBDD68ULL, 0xA45C71208C87BCF2ULL, 0xDD49E46DB7E1855DULL, 
            0x18DBC9B0FC74CE94ULL, 0x143C075667313FF8ULL, 0xD114720F3E0E7B9FULL, 0x979CBB634DB041DFULL, 
            0x984F0CD88727A9BBULL, 0xD5EB532C94E847E1ULL, 0x2AAC3C7CC25A95F2ULL, 0x0CEA16CFA9BF89F5ULL
        },
        {
            0x8C8D6778B0076AADULL, 0x0E87DC92F128353FULL, 0x900A7212721EFFB9ULL, 0x05BF13ADB37918DEULL, 
            0x6F36807F63EBBCB4ULL, 0xDBC94283617D38BBULL, 0x507804C17BAA0E2EULL, 0xA45EF34D50303CF6ULL, 
            0xEEB3EFA9369401D7ULL, 0xA0A667157ED8DA81ULL, 0xD246752EE9636BCBULL, 0xCBEA319A048FB865ULL, 
            0xF485138580556931ULL, 0x6B442D25578F8E97ULL, 0xC57FEF1A9190D2DDULL, 0x44CC55EF1DEDAFA3ULL, 
            0x80FFD7E78B92B218ULL, 0x19A4F1A9EAE1B3FBULL, 0xF58B9D07E36135B9ULL, 0x6A788011DA93601AULL, 
            0x7AFB678BD11E382EULL, 0xCBEA7E49FFBEFBA6ULL, 0xF9DEF93CC535C337ULL, 0xE39F648786CF3B34ULL, 
            0x29224B2EB905F2C2ULL, 0x306C6D7C93214D25ULL, 0x575E00BDFC6B354BULL, 0xE268529DBE2D68B5ULL, 
            0xADA5AD79CFDB91F8ULL, 0x7A9EFC3924DC0F29ULL, 0x2A4E223C4433A394ULL, 0xCFD0BE7217C921F4ULL
        }
    },
    {
        {
            0x2448A53ADA5ED349ULL, 0xC1C1F153A52A6223ULL, 0xA041E48C78168CCAULL, 0xABC81669A2AF2566ULL, 
            0x9A7645E4F2FE012CULL, 0xD88CD210328B2CA3ULL, 0x2CF2DC64E2455E0EULL, 0x366B6C8B8C414142ULL, 
            0xA756C0E932388714ULL, 0x267255A12EB4A2F6ULL, 0x1FA0A245532C6321ULL, 0xA108CC84C78D17CAULL, 
            0x4D74D71FF6C0F986ULL, 0x00D7D800C88F871DULL, 0x579F26F69D7260F8ULL, 0xE75302203D95880AULL, 
            0xED8B30F1301BF10BULL, 0x4429A49EEB2F8E32ULL, 0x879C46BA25086B4EULL, 0x11BC195205A82B1DULL, 
            0xED9F94E9029F3543ULL, 0xEA26C92C0EB5B13DULL, 0xC2397E0234AA6C62ULL, 0xB9D3C7867231784EULL, 
            0xA8D3344A5AF9369DULL, 0xD6BA44E3F950A0DFULL, 0xE57166BE8F5B8EDCULL, 0xB2271C29569C142BULL, 
            0x31D29EBB88AC578BULL, 0xFAE54CE914C3927CULL, 0xFFE43668D4EFEF7DULL, 0xA9D4FA458F39CC8CULL
        },
        {
            0x1D669881AC725998ULL, 0x7A43CA1F47350341ULL, 0xD99359A571AA1738ULL, 0x170B61482B7B0A5CULL, 
            0x840C131FE7CD4050ULL, 0x5ED3332C6714CE05ULL, 0x7BBA04D596A19E8FULL, 0x6833CA8337E114D3ULL, 
            0xC6AAF3A63D2888A4ULL, 0x546F5851069CC682ULL, 0xC1FE7C7D931B5000ULL, 0xFE6929DB23544A6FULL, 
            0x4BFE219C9C21C09EULL, 0xCF121344F4090DAFULL, 0xE95A76387C86FC39ULL, 0xA61F1D5B03D45C01ULL, 
            0xFB1ABE64710D0A94ULL, 0x4A9B35D3D619A569ULL, 0xC06E2DEFD88E8E11ULL, 0x77D2F1F710E20523ULL, 
            0xE402E7691E087D65ULL, 0xCA8E59002028EEFDULL, 0xB08C9C263CAA8286ULL, 0x7992F4E92974C66CULL, 
            0x271D2E86D722DF2AULL, 0xBDA97EB042B008CFULL, 0xF2BBB1D25A8192CAULL, 0x1CFE812ACE01FF29ULL, 
            0xE34D754F2902AB19ULL, 0x47AAA09FD221844BULL, 0xF83004AFA9C36F9AULL, 0x799FCAEDC5C35D8AULL
        },
        {
            0x969A1C44072394FDULL, 0xAE751432A707B0EDULL, 0x42E3FBC95DB680D9ULL, 0x4833C9F469C925D0ULL, 
            0xC13FC71F068912BDULL, 0xF0E770DCE53FE5B7ULL, 0x533F853C333231B6ULL, 0xA83E201026702297ULL, 
            0xDB70D9CC15F6531DULL, 0x1542C0320E236502ULL, 0x95673F5B97E35466ULL, 0xB1548C5351B624A4ULL, 
            0x76A213146A06DC65ULL, 0xA5DC905963B056E2ULL, 0x8F593AA82C37B663ULL, 0x1647B77AB319B9DBULL, 
            0x772A4D1376CDE705ULL, 0xEF5DFFE9CFEAE009ULL, 0x64A3403CF73FE8B6ULL, 0x621C6286B964A038ULL, 
            0x8221B394E2DE1446ULL, 0x68A8E19E3EA3F86FULL, 0xC05E11E4CE0475C7ULL, 0x05193FDF33B96F58ULL, 
            0x0F1E432B4D7AE0CCULL, 0xE0BA00DC47C65DBAULL, 0x67033C4631C10A86ULL, 0x58A25BA49159D51DULL, 
            0xC2343CEAE609DF95ULL, 0xAF2A9E2CF0BAF8FFULL, 0x5AE936C152CDE815ULL, 0x817B2278CD267452ULL
        },
        {
            0x8746AA84CAE814C1ULL, 0xAC6BE743965C551DULL, 0x8C3C6481B2FFA9C6ULL, 0x2CB5FEE2FFFCE761ULL, 
            0x294974B4A2D633D4ULL, 0x5734F9D82FD5619BULL, 0x519FA93073367AADULL, 0x36CBF235A44E53DFULL, 
            0x6080CDF030D508BFULL, 0xAF237847E659199FULL, 0x86717DE0623D9BC9ULL, 0x0FFE3BB11C6549EEULL, 
            0x6539894ED3F3439AULL, 0x2089388C44787F5DULL, 0x5E6558B7E8D07D65ULL, 0xA1DEC43479C6BC88ULL, 
            0x39E1E5BA7DCD2ED2ULL, 0x8AA456201E3C5DD2ULL, 0x1D6CB4C207ED526CULL, 0x0357FEA24062D729ULL, 
            0xC7E02220B9761A81ULL, 0xF9D8CF7DD533ABEBULL, 0x8B9B8571F8F29254ULL, 0x06A2BEE52519BF3FULL, 
            0x4E1DFDA504EF15DFULL, 0x5C40FF463DF772CFULL, 0x1F060AC5EE0CF966ULL, 0xC68EBA49895C9FC4ULL, 
            0x023407E9F125BBEBULL, 0x45EFB4099E353994ULL, 0xD0B728704FBA9083ULL, 0xAC1AF298CCBDA1C1ULL
        },
        {
            0xD7B75609217AABC8ULL, 0xC7032C49B0BCED77ULL, 0xA1FD2EF263BF01E3ULL, 0xB19D61F2055458DAULL, 
            0x337D54C85324DAE6ULL, 0x8BD0D381B03897C3ULL, 0x63C8E7CB4DD80961ULL, 0xE396D88033B0C7F5ULL, 
            0x0A9A74EBD48577D7ULL, 0xA9B229A42E16C93BULL, 0x8F75574CA6D7B5DEULL, 0x36D81D76D4795C79ULL, 
            0x8F4FE2B6AFA7CD3FULL, 0xDFC25FFF67124D92ULL, 0x46B466F797E2B30AULL, 0xFFEDFAC8AC69CCD2ULL, 
            0xCE1B027EE9E3A5AFULL, 0x8BB5BC5341FE5ABDULL, 0x77F3105A31DA79B8ULL, 0x25876B6CACD83562ULL, 
            0x03049ED0D8F9A709ULL, 0x1228289C68CBAB50ULL, 0x2D90A245CBC21C83ULL, 0x6557A814ED3E7941ULL, 
            0x8AC45C77E30E6FFFULL, 0xB7FC8F708A33E8FCULL, 0x3258EFEF4BBA4431ULL, 0xEE8D64B05F6768E4ULL, 
            0x8119E69371456878ULL, 0x55400D0146CD0CF2ULL, 0x2E73D762DCE7C221ULL, 0x34C17954880365C1ULL
        },
        {
            0xE1B26F1DD989E813ULL, 0xC04004D81E7C0AD9ULL, 0x661D398EE1859A25ULL, 0x36E44A3B19CC70E0ULL, 
            0xE1882FA6449AC9E4ULL, 0x9922104FE6B5BA30ULL, 0xB6EB5F3DCFC2F7E4ULL, 0xCA4A8BABB0689181ULL, 
            0x91DD9FBC79BD647DULL, 0x9642E03C98068BC1ULL, 0x8FE50536B7BA1D55ULL, 0xE9A779EBDB09B5CCULL, 
            0x4ECC800D0B252DB7ULL, 0xDD05368C3DBC4F52ULL, 0x2265305504B71827ULL, 0x52F1B501212970E6ULL, 
            0x3B569DA4D367A640ULL, 0x55D6BDE146642E44ULL, 0x0FCA97B08C0A37A5ULL, 0x98089B01BE9D11CCULL, 
            0xECA239A421217F95ULL, 0x92A38E7DD88FCF6EULL, 0xC175E7B5FC04A8F3ULL, 0xF4A5708768831132ULL, 
            0x940734C7CCC9CA20ULL, 0x8C7A4DDF90CCEE9CULL, 0x8A146AEF61F66846ULL, 0xF8BE224FA0F2D1BCULL, 
            0xD8F7B5E8952D3667ULL, 0x047FED4F353AC23AULL, 0x8A2B8C8C26D8E0A7ULL, 0xEDB4D9F246580125ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseHConstants = {
    0x32B9DB9F4784E437ULL,
    0xBA839F41FBA7A8A8ULL,
    0x07FA04CC148E8024ULL,
    0x32B9DB9F4784E437ULL,
    0xBA839F41FBA7A8A8ULL,
    0x07FA04CC148E8024ULL,
    0xD99BC31BDC92F676ULL,
    0x22E26E9953E80C42ULL,
    0x11,
    0x6E,
    0xA8,
    0x9E,
    0x06,
    0x67,
    0x50,
    0xDA
};

