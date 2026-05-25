//
//  GSeedRunKDF2.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#include "GSeedRunKDF2.hpp"

#include <array>
#include <cstdio>
#include <sstream>

namespace {

const std::array<TwistWorkSpaceSlot, 6> kOrbiterAssignSaltSlots = {
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF,
};

const std::array<TwistWorkSpaceSlot, 6> kOrbiterUpdateSaltSlots = {
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE,
    TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF,
};

const std::array<TwistWorkSpaceSlot, 6> kWandererUpdateSaltSlots = {
    TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA,
    TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB,
    TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC,
    TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD,
    TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE,
    TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF,
};

const std::array<TwistWorkSpaceSlot, 4> kWorkLaneSlots = {
    TwistWorkSpaceSlot::kWorkLaneA,
    TwistWorkSpaceSlot::kWorkLaneB,
    TwistWorkSpaceSlot::kWorkLaneC,
    TwistWorkSpaceSlot::kWorkLaneD,
};

const std::array<TwistWorkSpaceSlot, 4> kOperationLaneSlots = {
    TwistWorkSpaceSlot::kOperationLaneA,
    TwistWorkSpaceSlot::kOperationLaneB,
    TwistWorkSpaceSlot::kOperationLaneC,
    TwistWorkSpaceSlot::kOperationLaneD,
};

const std::array<TwistWorkSpaceSlot, 4> kExpansionLaneSlots = {
    TwistWorkSpaceSlot::kExpansionLaneA,
    TwistWorkSpaceSlot::kExpansionLaneB,
    TwistWorkSpaceSlot::kExpansionLaneC,
    TwistWorkSpaceSlot::kExpansionLaneD,
};

const std::array<const char *, 8> kNonceVariableNames = {
    "aNonceByteA",
    "aNonceByteB",
    "aNonceByteC",
    "aNonceByteD",
    "aNonceByteE",
    "aNonceByteF",
    "aNonceByteG",
    "aNonceByteH",
};

const std::array<TwistVariable, 13> kInitialRandomVariables = {
    TwistVariable::kPrevious,
    TwistVariable::kCarry,
    TwistVariable::kWandererA,
    TwistVariable::kWandererB,
    TwistVariable::kWandererC,
    TwistVariable::kWandererD,
    TwistVariable::kWandererE,
    TwistVariable::kWandererF,
    TwistVariable::kWandererG,
    TwistVariable::kWandererH,
    TwistVariable::kWandererI,
    TwistVariable::kWandererJ,
    TwistVariable::kWandererK,
};

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

std::string NonceLine(const GSymbol &pNonceSymbol,
                      const int pIndex) {
    std::ostringstream aLine;
    aLine << "[[maybe_unused]] std::uint64_t " << pNonceSymbol.mName
          << " = ((pNonce >> " << (pIndex * 8) << "U) & 0xFFULL);";
    return aLine.str();
}

} // namespace

GSeedRunKDF2::GSeedRunKDF2() {
    Reset();
}

GSeedRunKDF2::~GSeedRunKDF2() {

}

void GSeedRunKDF2::Reset() {
    
    mSaltsOrbiterAssign.clear();
    for (TwistWorkSpaceSlot aSlot : kOrbiterAssignSaltSlots) {
        mSaltsOrbiterAssign.push_back(BufSymbol(aSlot));
    }

    mSaltsOrbiterUpdate.clear();
    for (TwistWorkSpaceSlot aSlot : kOrbiterUpdateSaltSlots) {
        mSaltsOrbiterUpdate.push_back(BufSymbol(aSlot));
    }

    mSaltsWandererUpdate.clear();
    for (TwistWorkSpaceSlot aSlot : kWandererUpdateSaltSlots) {
        mSaltsWandererUpdate.push_back(BufSymbol(aSlot));
    }

    mWorkLanes.clear();
    for (TwistWorkSpaceSlot aSlot : kWorkLaneSlots) {
        mWorkLanes.push_back(BufSymbol(aSlot));
    }

    mOperationLanes.clear();
    for (TwistWorkSpaceSlot aSlot : kOperationLaneSlots) {
        mOperationLanes.push_back(BufSymbol(aSlot));
    }

    mExpansionLanes.clear();
    for (TwistWorkSpaceSlot aSlot : kExpansionLaneSlots) {
        mExpansionLanes.push_back(BufSymbol(aSlot));
    }

    mARXSkeletonsA.clear();
    mARXSkeletonsB.clear();
    mARXSkeletonsC.clear();
    
    
    mHotPacksA = GMagicNumbers::GetHotPacks(12);
    mHotPacksB = GMagicNumbers::GetHotPacks(12);
    mHotPacksC = GMagicNumbers::GetHotPacks(12);
    
}

bool GSeedRunKDF2::Plan(std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    Reset();
    
    GAXSK *aAXSK = new GAXSK();
    if (!aAXSK->Bake(GAXSFormat::kN5,
                     {2, 3, 4, 4},
                     true,
                     &mARXSkeletonsA,
                     pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "GAXSK::Bake failed while planning GSeedRunKDF2";
        }
        delete aAXSK;
        return false;
    }
    delete aAXSK;
    
    
    aAXSK = new GAXSK();
    if (!aAXSK->Bake(GAXSFormat::kN5,
                     {4, 4, 4, 4},
                     true,
                     &mARXSkeletonsB,
                     pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "GAXSK::Bake failed while planning GSeedRunKDF2";
        }
        delete aAXSK;
        return false;
    }
    delete aAXSK;
    
    
    aAXSK = new GAXSK();
    if (!aAXSK->Bake(GAXSFormat::kN5,
                     {4, 4, 4, 4},
                     true,
                     &mARXSkeletonsC,
                     pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "GAXSK::Bake failed while planning GSeedRunKDF2";
        }
        delete aAXSK;
        return false;
    }
    delete aAXSK;
    
    
    
    return true;
}

bool GSeedRunKDF2::Build(TwistProgramBranch &pBranch,
                         std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    
    if (mARXSkeletonsA.size() != 6 ||
        mARXSkeletonsB.size() != 6 ||
        mARXSkeletonsC.size() != 6) {
        SetError(pErrorMessage, "GSeedRunKDF2 had incorrect GAXSK skeleton counts");
        return false;
    }
    
    
    pBranch.AddLine("// [gseed-run-kdf2]");
    for (int i = 0; i < 8; ++i) {
        pBranch.AddLine(NonceLine(GSymbol::Var(kNonceVariableNames[static_cast<std::size_t>(i)]), i));
    }
    
    pBranch.AddLine("std::uint64_t aDomainWordIngress = pConstants->mIngress;");
    pBranch.AddLine("std::uint64_t aDomainWordScatter = pConstants->mScatter;");
    pBranch.AddLine("std::uint64_t aDomainWordCross = pConstants->mCross;");
    pBranch.AddLine("std::uint8_t aDomainWordMaskMutateA = pConstants->mMaskMutateA;");
    pBranch.AddLine("std::uint8_t aDomainWordMaskMutateB = pConstants->mMaskMutateB;");

    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;");
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;");

    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;");

    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;");
    
    GBatch aInitBatch;
    std::vector<GStatement> aInitStatements;
    aInitBatch.mName = "init varz";
    for (TwistVariable aVariable : kInitialRandomVariables) {
        aInitStatements.push_back(
            GQuick::MakeAssignVariableStatement(GSymbol::Var(aVariable),
                                                GExpr::Const(Random::Get64High())));
    }



    aInitBatch.CommitStatements(&aInitStatements);
    
    
    
    GBatch aBatch;
    aBatch.mName = "gseed_run_kdf2";
    
    std::vector<CSPRNGV2Slice> aSlicesA;
    
    CSPRNGV2Slice aSliceA1;
    aSliceA1.mARXSkeleton = mARXSkeletonsA[0];
    aSliceA1.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSource));
    aSliceA1.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnow));
    aSliceA1.mDest = mExpansionLanes[0];
    aSliceA1.mDestWriteInverted = false;
    aSliceA1.mHotPack = mHotPacksA[0];
    aSlicesA.push_back(aSliceA1);
    
    CSPRNGV2Slice aSliceA2;
    aSliceA2.mARXSkeleton = mARXSkeletonsA[1];
    aSliceA2.mSources.push_back(mExpansionLanes[0]);
    aSliceA2.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSource));
    aSliceA2.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnow));
    aSliceA2.mDest = mExpansionLanes[1];
    aSliceA2.mDestWriteInverted = true;
    aSliceA2.mHotPack = mHotPacksA[1];
    aSlicesA.push_back(aSliceA2);
    
    CSPRNGV2Slice aSliceA3;
    aSliceA3.mARXSkeleton = mARXSkeletonsA[2];
    aSliceA3.mSources.push_back(mExpansionLanes[1]);
    aSliceA3.mSources.push_back(mExpansionLanes[0]);
    aSliceA3.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSource));
    aSliceA3.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnow));
    aSliceA3.mDest = mExpansionLanes[2];
    aSliceA3.mDestWriteInverted = false;
    aSliceA3.mHotPack = mHotPacksA[2];
    aSlicesA.push_back(aSliceA3);
    
    CSPRNGV2Slice aSliceA4;
    aSliceA4.mARXSkeleton = mARXSkeletonsA[3];
    aSliceA4.mSources.push_back(mExpansionLanes[2]);
    aSliceA4.mSources.push_back(mExpansionLanes[1]);
    aSliceA4.mSources.push_back(mExpansionLanes[0]);
    aSliceA4.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSource));
    aSliceA4.mDest = mExpansionLanes[3];
    aSliceA4.mDestWriteInverted = true;
    aSliceA4.mHotPack = mHotPacksA[3];
    aSlicesA.push_back(aSliceA4);
    
    if (!CSPRNGV2::Bake(aSlicesA,
                        mSaltsOrbiterAssign,
                        mSaltsOrbiterUpdate,
                        mSaltsWandererUpdate,
                        &aBatch.mLoops,
                        pErrorMessage)) {
        const char *aErrorText = (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "unknown error";
        printf("error with CSPRNGV2::Bake A => %s\n", aErrorText);
        return false;
    }
    
    
    
    std::vector<CSPRNGV2Slice> aSlicesB;

    std::vector<GSymbol> aRecentSourcesB = {
        mExpansionLanes[0],
        mExpansionLanes[1],
        mExpansionLanes[2],
        mExpansionLanes[3],
    };

    for (int aIndex = 0; aIndex < 4; aIndex++) {
        CSPRNGV2Slice aSlice;

        aSlice.mARXSkeleton = mARXSkeletonsB[static_cast<std::size_t>(aIndex)];

        for (auto aIt = aRecentSourcesB.rbegin();
                 aIt != aRecentSourcesB.rend();
                 ++aIt) {
                aSlice.mSources.push_back(*aIt);
            }

        aSlice.mDest = mOperationLanes[static_cast<std::size_t>(aIndex)];
        aSlice.mDestWriteInverted = ((aIndex & 1) != 0);
        aSlice.mHotPack = mHotPacksB[static_cast<std::size_t>(aIndex)];

        aSlicesB.push_back(aSlice);

        aRecentSourcesB.erase(aRecentSourcesB.begin());
        aRecentSourcesB.push_back(aSlice.mDest);
    }

    if (!CSPRNGV2::Bake(aSlicesB,
                        mSaltsOrbiterAssign,
                        mSaltsOrbiterUpdate,
                        mSaltsWandererUpdate,
                        &aBatch.mLoops,
                        pErrorMessage)) {
        const char *aErrorText = (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "unknown error";
        printf("error with CSPRNGV2::Bake B => %s\n", aErrorText);
        return false;
    }
    
    
    
    
    
    std::vector<CSPRNGV2Slice> aSlicesC;

    std::vector<GSymbol> aRecentSourcesC = {
        mOperationLanes[0],
        mOperationLanes[1],
        mOperationLanes[2],
        mOperationLanes[3],
    };

    for (int aIndex = 0; aIndex < 4; aIndex++) {
        CSPRNGV2Slice aSlice;

        aSlice.mARXSkeleton = mARXSkeletonsC[static_cast<std::size_t>(aIndex)];

        for (auto aIt = aRecentSourcesC.rbegin();
             aIt != aRecentSourcesC.rend();
             ++aIt) {
            aSlice.mSources.push_back(*aIt);
        }

        aSlice.mDest = mWorkLanes[static_cast<std::size_t>(aIndex)];
        aSlice.mDestWriteInverted = ((aIndex & 1) != 0);
        aSlice.mHotPack = mHotPacksC[static_cast<std::size_t>(aIndex)];

        aSlicesC.push_back(aSlice);

        aRecentSourcesC.erase(aRecentSourcesC.begin());
        aRecentSourcesC.push_back(aSlice.mDest);
    }

    if (!CSPRNGV2::Bake(aSlicesC,
                        mSaltsOrbiterAssign,
                        mSaltsOrbiterUpdate,
                        mSaltsWandererUpdate,
                        &aBatch.mLoops,
                        pErrorMessage)) {
        const char *aErrorText = (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "unknown error";
        printf("error with CSPRNGV2::Bake C => %s\n", aErrorText);
        return false;
    }

    
    
    
    pBranch.AddBatch(aInitBatch);
    
    pBranch.AddBatch(aBatch);
    
    return true;
}
