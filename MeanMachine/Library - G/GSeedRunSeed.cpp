//
//  GSeedRunSeed.cpp
//  MeanMachine
//
//  Created by Codex on 5/11/26.
//

#include "GSeedRunSeed.hpp"
#include "GRunMatrixDiffusion.hpp"

GSeedRunSeed::GSeedRunSeed() {
}

GSeedRunSeed::~GSeedRunSeed() {
}

bool GSeedRunSeed::Plan(std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    return true;
}

bool GSeedRunSeed::Build(TwistProgramBranch &pBranch,
                         std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    GKDF aKDF;
    GBatch aBatch;

    const GSymbol aSource = BufSymbol(TwistWorkSpaceSlot::kSource);

    const GSymbol aExpandA = BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneA);
    const GSymbol aExpandB = BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneB);
    const GSymbol aExpandC = BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneC);
    const GSymbol aExpandD = BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneD);

    const GSymbol aWorkA = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
    const GSymbol aWorkB = BufSymbol(TwistWorkSpaceSlot::kWorkLaneB);
    const GSymbol aWorkC = BufSymbol(TwistWorkSpaceSlot::kWorkLaneC);
    const GSymbol aWorkD = BufSymbol(TwistWorkSpaceSlot::kWorkLaneD);

    const GSymbol aOperationA = BufSymbol(TwistWorkSpaceSlot::kOperationLaneA);
    const GSymbol aOperationB = BufSymbol(TwistWorkSpaceSlot::kOperationLaneB);
    const GSymbol aOperationC = BufSymbol(TwistWorkSpaceSlot::kOperationLaneC);
    const GSymbol aOperationD = BufSymbol(TwistWorkSpaceSlot::kOperationLaneD);

    const GSymbol aMaskA = BufSymbol(TwistWorkSpaceSlot::kMaskLaneA);
    const GSymbol aMaskB = BufSymbol(TwistWorkSpaceSlot::kMaskLaneB);

    auto EmitKDF = [&](const TwistDomain pDomain,
                       const GSymbol pSourceBuffer,
                       const GSymbol pDestBuffer,
                       const char *pComment) -> bool {
        std::vector<GStatement> aStatements;
        if (!aKDF.Bake(pDomain,
                       pSourceBuffer,
                       pDestBuffer,
                       &aStatements,
                       pErrorMessage)) {
            if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
                *pErrorMessage = "failed to build seed KDF call";
            }
            return false;
        }
        if ((pComment != nullptr) && (pComment[0] != '\0')) {
            aBatch.AddComment(pComment);
        }
        aBatch.CommitStatements(&aStatements);
        return true;
    };

    // 1..4 warm-up rounds
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneOrbiterInit, aSource, aExpandA, "seed-kdf: warm-up 1")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneOrbiterInit, aSource, aExpandB, "seed-kdf: warm-up 2")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneOrbiterInit, aSource, aExpandC, "seed-kdf: warm-up 3")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneOrbiterInit, aSource, aExpandD, "seed-kdf: warm-up 4")) { return false; }

    // 5..8 expansion -> workers
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneOrbiter, aExpandA, aWorkA, "seed-kdf: workers 1")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneOrbiter, aExpandB, aWorkB, "seed-kdf: workers 2")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneOrbiter, aExpandC, aWorkC, "seed-kdf: workers 3")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneOrbiter, aExpandD, aWorkD, "seed-kdf: workers 4")) { return false; }

    // 9..12 workers -> operation lanes
    if (!EmitKDF(TwistDomain::kSaltsOperationLaneOrbiter, aWorkA, aOperationA, "seed-kdf: operation 1")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsOperationLaneOrbiter, aWorkB, aOperationB, "seed-kdf: operation 2")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsOperationLaneOrbiter, aWorkC, aOperationC, "seed-kdf: operation 3")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsOperationLaneOrbiter, aWorkD, aOperationD, "seed-kdf: operation 4")) { return false; }

    // 13..16 operation lanes -> workers
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneUnwind, aOperationA, aWorkA, "seed-kdf: recycle 1")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneUnwind, aOperationB, aWorkB, "seed-kdf: recycle 2")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneUnwind, aOperationC, aWorkC, "seed-kdf: recycle 3")) { return false; }
    if (!EmitKDF(TwistDomain::kSaltsWorkLaneUnwind, aOperationD, aWorkD, "seed-kdf: recycle 4")) { return false; }

    GRunMatrixDiffusionConfig aDiffusionA;
    aDiffusionA.mInputA = aWorkA;
    aDiffusionA.mInputB = aWorkC;
    aDiffusionA.mOutputA = aMaskA;
    aDiffusionA.mOutputB = aMaskB;
    aDiffusionA.mShuffleEntropyA = aOperationA;
    aDiffusionA.mShuffleEntropyB = aOperationB;
    aDiffusionA.mShuffleEntropyC = aExpandC;
    aDiffusionA.mShuffleEntropyD = aExpandD;
    aDiffusionA.mOperationSourceA = aOperationC;
    aDiffusionA.mOperationSourceB = aOperationD;

    aBatch.AddComment("seed-matrix-diffusion: workA/workC -> maskA/maskB");
    if (!GRunMatrixDiffusion::Bake(aDiffusionA, &aBatch, pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "failed to build seed matrix diffusion pass A";
        }
        return false;
    }

    GRunMatrixDiffusionConfig aDiffusionB;
    aDiffusionB.mInputA = aWorkB;
    aDiffusionB.mInputB = aWorkD;
    aDiffusionB.mOutputA = aExpandC;
    aDiffusionB.mOutputB = aExpandD;
    aDiffusionB.mShuffleEntropyA = aOperationA;
    aDiffusionB.mShuffleEntropyB = aOperationB;
    aDiffusionB.mShuffleEntropyC = aExpandC;
    aDiffusionB.mShuffleEntropyD = aExpandD;
    aDiffusionB.mOperationSourceA = aOperationC;
    aDiffusionB.mOperationSourceB = aOperationD;

    aBatch.AddComment("seed-matrix-diffusion: workB/workD -> expanderC/expanderD");
    if (!GRunMatrixDiffusion::Bake(aDiffusionB, &aBatch, pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "failed to build seed matrix diffusion pass B";
        }
        return false;
    }

    pBranch.AddBatch(aBatch);
    return true;
}
