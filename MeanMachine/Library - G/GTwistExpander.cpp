//
//  GTwistExpander.cpp
//  MeanMachine
//

#include "GTwistExpander.hpp"

#include "Random.hpp"
#include "SaltTables.hpp"

namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

std::uint8_t NonZeroRandomByte() {
    std::uint8_t aValue = Random::GetByte();
    if (aValue == 0U) {
        aValue = 1U;
    }
    return aValue;
}

void RandomizeDomainConstants(TwistDomainConstants *pConstants) {
    if (pConstants == nullptr) {
        return;
    }

    pConstants->mIngress = Random::Get64High();
    pConstants->mScatter = Random::Get64High();
    pConstants->mCross = Random::Get64High();
    pConstants->mMatrixSelectA = Random::Get64High();
    pConstants->mMatrixSelectB = Random::Get64High();
    pConstants->mMatrixUnrollA = NonZeroRandomByte();
    pConstants->mMatrixUnrollB = NonZeroRandomByte();
    pConstants->mMatrixArgA = NonZeroRandomByte();
    pConstants->mMatrixArgB = NonZeroRandomByte();
    pConstants->mMatrixArgC = NonZeroRandomByte();
    pConstants->mMatrixArgD = NonZeroRandomByte();
}

void RandomizeDomainBundleConstants(TwistDomainBundle *pBundle) {
    if (pBundle == nullptr) {
        return;
    }

    RandomizeDomainConstants(&pBundle->mKeyRotateAConstants);
    RandomizeDomainConstants(&pBundle->mKeyRotateBConstants);
    RandomizeDomainConstants(&pBundle->mKeySpawnAConstants);
    RandomizeDomainConstants(&pBundle->mKeySpawnBConstants);
    RandomizeDomainConstants(&pBundle->mSeedConstants);
    RandomizeDomainConstants(&pBundle->mTwistConstants);
}

} // namespace

GTwistExpander::GTwistExpander()
: TwistExpander() {
    mNameBase = "Generated";

    RandomizeDomainBundleConstants(&mDomainBundleInbuilt);
    SaltTables::InjectRandomDomains(this);
    RefreshTablePointers();
}

GTwistExpander::~GTwistExpander() {

}

void GTwistExpander::RefreshTablePointers() {
}

void GTwistExpander::KDF(std::uint64_t pNonce,
                         TwistDomainConstants *pDomainConstants,
                         TwistDomainSaltSet *pDomainSaltSet) {
    (void)pNonce;
    (void)pDomainConstants;
    (void)pDomainSaltSet;
}

void GTwistExpander::Seed(TwistWorkSpace *pWorkSpace,
                          TwistFarmSalt *pFarmSalt,
                          std::uint64_t pNonce,
                          std::uint8_t *pPassword,
                          std::size_t pPasswordByteLength,
                          std::uint8_t *pDestination,
                          MUTABLE_PARAMS) {
    RefreshTablePointers();
    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr) ||
        (pDestination == nullptr) || MUTABLE_PARAMS_ARE_NULL) {
        return;
    }
    UnrollPassword(pWorkSpace->mSourceLane,
                   pPassword,
                   pPasswordByteLength);
    UnrollNonce(pWorkSpace->mNonceLane, pNonce);
    mDomainBundleEphemeralA.Zero();
    mDomainBundleEphemeralB.Zero();
    pWorkSpace->mDomainBundle.Zero();
}

void GTwistExpander::TwistBlock(TwistWorkSpace *pWorkSpace,
                                std::uint8_t *pSource,
                                std::uint8_t *pCrossLaneA,
                                std::uint8_t *pCrossLaneB,
                                std::uint8_t *pCrossLaneC,
                                std::uint8_t *pCrossLaneD,
                                std::uint8_t *pDestination,
                                const bool pStifleKey,
                                MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pSource;
    (void)pCrossLaneA;
    (void)pCrossLaneB;
    (void)pCrossLaneC;
    (void)pCrossLaneD;
    (void)pDestination;
    (void)pStifleKey;
    (void)pIngress;
    (void)pCarry;
    (void)pWandererA;
    (void)pWandererB;
    (void)pWandererC;
    (void)pWandererD;
    (void)pWandererE;
    (void)pWandererF;
    (void)pWandererG;
    (void)pWandererH;
    (void)pWandererI;
    (void)pWandererJ;
    (void)pWandererK;
}

void GTwistExpander::GrowKeyA(TwistWorkSpace *pWorkSpace,
                              std::uint8_t *pCrossLaneA,
                              std::uint8_t *pCrossLaneB,
                              MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pCrossLaneA;
    (void)pCrossLaneB;
    (void)pIngress;
    (void)pCarry;
    (void)pWandererA;
    (void)pWandererB;
    (void)pWandererC;
    (void)pWandererD;
    (void)pWandererE;
    (void)pWandererF;
    (void)pWandererG;
    (void)pWandererH;
    (void)pWandererI;
    (void)pWandererJ;
    (void)pWandererK;
}

void GTwistExpander::GrowKeyB(TwistWorkSpace *pWorkSpace,
                              std::uint8_t *pCrossLaneA,
                              std::uint8_t *pCrossLaneB,
                              MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pCrossLaneA;
    (void)pCrossLaneB;
    (void)pIngress;
    (void)pCarry;
    (void)pWandererA;
    (void)pWandererB;
    (void)pWandererC;
    (void)pWandererD;
    (void)pWandererE;
    (void)pWandererF;
    (void)pWandererG;
    (void)pWandererH;
    (void)pWandererI;
    (void)pWandererJ;
    (void)pWandererK;
}

bool GTwistExpander::LoadJSONProjectRoot(const std::string &pJsonPath,
                                         std::string *pErrorMessage) {
    (void)pJsonPath;
    SetError(
        pErrorMessage,
        "GTwistExpander JSON loading has been removed; export and use generated C++ instead.");
    return false;
}
