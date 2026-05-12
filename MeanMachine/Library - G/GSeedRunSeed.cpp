//
//  GSeedRunSeed.cpp
//  MeanMachine
//
//  Created by Codex on 5/11/26.
//

#include "GSeedRunSeed.hpp"

GSeedRunSeed::GSeedRunSeed() {
    mSampleKDFTarget = BufSymbol(TwistWorkSpaceSlot::kDerivedSaltWandererA);
}

GSeedRunSeed::~GSeedRunSeed() {
}

bool GSeedRunSeed::Plan(std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    mSampleKDFTarget = BufSymbol(TwistWorkSpaceSlot::kDerivedSaltWandererA);
    return true;
}

bool GSeedRunSeed::Build(TwistProgramBranch &pBranch,
                         std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    GKDF aKDF;
    std::vector<GStatement> aStatements;
    if (!aKDF.Bake(TwistDomain::kSaltsWorkLaneWanderer,
                   mSampleKDFTarget,
                   &aStatements,
                   pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "failed to build sample seed KDF call";
        }
        return false;
    }

    pBranch.AddLine("// sample seed KDF");
    for (const GStatement &aStatement : aStatements) {
        if (!aStatement.IsRawLine()) {
            continue;
        }
        pBranch.AddLine(aStatement.mRawLine);
    }
    return true;
}

