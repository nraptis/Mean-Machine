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

const std::array<TwistWorkSpaceSlot, 6> kWorkLaneSlots = {
    TwistWorkSpaceSlot::kWorkLaneA,
    TwistWorkSpaceSlot::kWorkLaneB,
    TwistWorkSpaceSlot::kWorkLaneC,
    TwistWorkSpaceSlot::kWorkLaneD,
    TwistWorkSpaceSlot::kWorkLaneE,
    TwistWorkSpaceSlot::kWorkLaneF,
};

const std::array<TwistWorkSpaceSlot, 6> kOperationLaneSlots = {
    TwistWorkSpaceSlot::kOperationLaneA,
    TwistWorkSpaceSlot::kOperationLaneB,
    TwistWorkSpaceSlot::kOperationLaneC,
    TwistWorkSpaceSlot::kOperationLaneD,
    TwistWorkSpaceSlot::kOperationLaneE,
    TwistWorkSpaceSlot::kOperationLaneF,
};

const std::array<TwistWorkSpaceSlot, 6> kExpansionLaneSlots = {
    TwistWorkSpaceSlot::kExpansionLaneA,
    TwistWorkSpaceSlot::kExpansionLaneB,
    TwistWorkSpaceSlot::kExpansionLaneC,
    TwistWorkSpaceSlot::kExpansionLaneD,
    TwistWorkSpaceSlot::kExpansionLaneE,
    TwistWorkSpaceSlot::kExpansionLaneF,
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

    mARXSkeletons.clear();
    mHotPacks = GMagicNumbers::GetHotPacks(4);
}

bool GSeedRunKDF2::Plan(std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    Reset();
    if (!GAXSK::Bake(GAXSFormat::kSixSix,
                     {1, 2, 3, 4},
                     true,
                     &mARXSkeletons,
                     pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "GAXSK::Bake failed while planning GSeedRunKDF2";
        }
        return false;
    }
    return true;
}

bool GSeedRunKDF2::Build(TwistProgramBranch &pBranch,
                         std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    if (mARXSkeletons.empty() && !Plan(pErrorMessage)) {
        return false;
    }
    if (mARXSkeletons.empty()) {
        SetError(pErrorMessage, "GSeedRunKDF2 had no GAXSK skeletons to emit");
        return false;
    }
    

    pBranch.AddLine("// [gseed-run-kdf2]");
    for (int i = 0; i < 8; ++i) {
        pBranch.AddLine(NonceLine(GSymbol::Var(kNonceVariableNames[static_cast<std::size_t>(i)]), i));
    }
    
    pBranch.AddLine("std::uint64_t aDomainWordIngress = pConstants->mIngress;");
    pBranch.AddLine("std::uint64_t aDomainWordScatter = pConstants->mPrevious;");
    pBranch.AddLine("std::uint64_t aDomainWordCross = pConstants->mCross;");

    GBatch aBatch;
    aBatch.mName = "gseed_run_kdf2";
    
    std::vector<CSPRNGV2Slice> aSlices;
    
    CSPRNGV2Slice aSlice1;
    aSlice1.mARXSkeleton = mARXSkeletons[0];
    aSlice1.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSource));
    aSlice1.mDest = mWorkLanes[0];
    aSlice1.mDestWriteInverted = false;
    aSlice1.mHotPack = mHotPacks[0];
    aSlices.push_back(aSlice1);
    
    CSPRNGV2Slice aSlice2;
    aSlice2.mARXSkeleton = mARXSkeletons[1];
    aSlice2.mSources.push_back(mWorkLanes[0]);
    aSlice2.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSource));
    aSlice2.mDest = mWorkLanes[1];
    aSlice2.mDestWriteInverted = true;
    aSlice2.mHotPack = mHotPacks[1];
    aSlices.push_back(aSlice2);
    
    CSPRNGV2Slice aSlice3;
    aSlice3.mARXSkeleton = mARXSkeletons[2];
    aSlice3.mSources.push_back(mWorkLanes[1]);
    aSlice3.mSources.push_back(mWorkLanes[0]);
    aSlice3.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSource));
    aSlice3.mDest = mWorkLanes[2];
    aSlice3.mDestWriteInverted = false;
    aSlice3.mHotPack = mHotPacks[2];
    aSlices.push_back(aSlice3);
    
    CSPRNGV2Slice aSlice4;
    aSlice4.mARXSkeleton = mARXSkeletons[3];
    aSlice4.mSources.push_back(mWorkLanes[2]);
    aSlice4.mSources.push_back(mWorkLanes[1]);
    aSlice4.mSources.push_back(mWorkLanes[0]);
    aSlice4.mSources.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSource));
    aSlice4.mDest = mWorkLanes[3];
    aSlice4.mDestWriteInverted = true;
    aSlice4.mHotPack = mHotPacks[3];
    aSlices.push_back(aSlice4);
    
    if (!CSPRNGV2::Bake(aSlices,
                        mSaltsOrbiterAssign,
                        mSaltsOrbiterUpdate,
                        mSaltsWandererUpdate,
                        &aBatch.mLoops,
                        pErrorMessage)) {
        const char *aErrorText = (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "unknown error";
        printf("error with CSPRNGV2::Bake => %s\n", aErrorText);
        return false;
    }
    const std::size_t aBatchCountBefore = pBranch.GetBatchJsonText().size();
    pBranch.AddBatch(aBatch);
    if (pBranch.GetBatchJsonText().size() <= aBatchCountBefore) {
        SetError(pErrorMessage, "TwistProgramBranch::AddBatch failed while appending GSeedRunKDF2 batch");
        return false;
    }

    return true;
}
