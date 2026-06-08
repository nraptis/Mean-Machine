//
//  Builder_Seeder.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Seeder.hpp"
#include "GKDF.hpp"
#include "GTwistExpander.hpp"
#include "GMemory.hpp"
#include "GFarm.hpp"

#include "Random.hpp"
#include "GInvest.hpp"

struct SymbolAndBox {
    GSymbol mSymbol;
    int mBox;
};

bool Builder_Seeder::Build(GTwistExpander *pExpander,
                           std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build received null expander";
        }
        return false;
    }
    
    const GSymbol aSource = GSymbol::Buf(TwistWorkSpaceSlot::kSource);
    
    pExpander->mSeed.AddLine("// [seed]");
    
    std::vector<GStatement> aStatements;
    
    
    GBatch aInitBatch;
    GStatement aSourceInitializeStatement = GStatement::RawLine(std::string( "mSource = pSourceInput;"));
    aStatements.push_back(aSourceInitializeStatement);
    aInitBatch.CommitStatements(&aStatements);
    pExpander->mSeed.AddBatch(aInitBatch);
    aStatements.clear();
    
    
    std::vector<GSymbol> aWorkLanes;
    aWorkLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneA));
    aWorkLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneB));
    aWorkLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneC));
    aWorkLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneD));
    
    std::vector<GSymbol> aExpansionLanes;
    aExpansionLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kExpansionLaneA));
    aExpansionLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kExpansionLaneB));
    aExpansionLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kExpansionLaneC));
    aExpansionLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kExpansionLaneD));
    
    std::vector<int> aBoxes = { 0, 1, 2, 3 };
    std::vector<SymbolAndBox> aInvestA;
    std::vector<SymbolAndBox> aInvestB;
    std::vector<SymbolAndBox> aInvestC;
    
    Random::Shuffle(&aExpansionLanes);
    Random::Shuffle(&aBoxes);
    aInvestA.push_back(SymbolAndBox{aExpansionLanes[0], aBoxes[0]});
    aInvestA.push_back(SymbolAndBox{aExpansionLanes[1], aBoxes[1]});
    aInvestA.push_back(SymbolAndBox{aExpansionLanes[2], aBoxes[2]});
    aInvestA.push_back(SymbolAndBox{aExpansionLanes[3], aBoxes[3]});
    Random::Shuffle(&aWorkLanes);
    Random::Shuffle(&aBoxes);
    aInvestA.push_back(SymbolAndBox{aWorkLanes[0], aBoxes[0]});
    aInvestA.push_back(SymbolAndBox{aWorkLanes[1], aBoxes[1]});
    aInvestA.push_back(SymbolAndBox{aWorkLanes[2], aBoxes[2]});
    aInvestA.push_back(SymbolAndBox{aWorkLanes[3], aBoxes[3]});
    
    
    std::vector<TwistDomain> aDomains;
    aDomains.push_back(TwistDomain::kPhaseA);
    aDomains.push_back(TwistDomain::kPhaseB);
    aDomains.push_back(TwistDomain::kPhaseC);
    aDomains.push_back(TwistDomain::kPhaseD);
    
    
    GSnowType mSnowType[4];
    GSymbol mSnowLane[4];
    
    
    GBatch aMemoryZeroBatch;
    GMemory aMemory;
    if (!aMemory.BakeZeroKeyBoxA(GSymbol::Buf(TwistWorkSpaceSlot::kKeyBoxUnrolledA), &aStatements, pErrorMessage)) {
        return false;
    }
    if (!aMemory.BakeZeroKeyBoxB(GSymbol::Buf(TwistWorkSpaceSlot::kKeyBoxUnrolledB), &aStatements, pErrorMessage)) {
        return false;
    }
    if (!aMemory.BakeZeroMaskBoxA(GSymbol::Buf(TwistWorkSpaceSlot::kMaskBoxUnrolledA), &aStatements, pErrorMessage)) {
        return false;
    }
    if (!aMemory.BakeZeroMaskBoxB(GSymbol::Buf(TwistWorkSpaceSlot::kMaskBoxUnrolledB), &aStatements, pErrorMessage)) {
        return false;
    }
    aMemoryZeroBatch.CommitStatements(&aStatements);
    aStatements.clear();
    pExpander->mSeed.AddBatch(aMemoryZeroBatch);
    
    mSnowType[0] = GSnowType::kAES;
    mSnowType[1] = GSnowType::kChaCha;
    mSnowType[2] = GSnowType::kSha;
    mSnowType[3] = GSnowType::kAria;
    
    for (int i = 3; i > 0; --i) {
        const int j = Random::Get(i + 1); // 0...i
        std::swap(mSnowType[i], mSnowType[j]);
    }
    
    mSnowLane[0] = GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneA);
    mSnowLane[1] = GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneB);
    mSnowLane[2] = GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneC);
    mSnowLane[3] = GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneD);
    for (int i = 3; i > 0; --i) {
        const int j = Random::Get(i + 1); // 0...i
        std::swap(mSnowLane[i], mSnowLane[j]);
    }
    
    
    GBatch aSnowBatch;
    for (int i=0;i<4;i++) {
        
        GSnow aSnow;
        switch (mSnowType[i]) {
            case GSnowType::kAES:
                aSnowBatch.AddComment("Making snow counter: aes 256");
                break;
            case GSnowType::kChaCha:
                aSnowBatch.AddComment("Making snow counter: cha cha 20");
                break;
            case GSnowType::kSha:
                aSnowBatch.AddComment("Making snow counter: sha 256");
                break;
            case GSnowType::kAria:
                aSnowBatch.AddComment("Making snow counter: aria 256");
                break;
            default:
                std::printf("bad snow type\n");
                return false;
        }
        
        if (!aSnow.Bake(mSnowType[i], aSource, mSnowLane[i], &aStatements, pErrorMessage)) {
            std::printf("snow bake failed: %s\n", (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "");
            return false;
        }
        
        aSnowBatch.CommitStatements(&aStatements);
        aStatements.clear();
    }
    pExpander->mSeed.AddBatch(aSnowBatch);
    
    
    
    for (std::size_t aDomainIndex = 0U; aDomainIndex < aDomains.size(); ++aDomainIndex) {
        
        std::string aDomainPartialName = "";
        if (aDomains[aDomainIndex] == TwistDomain::kPhaseA) {
            aDomainPartialName = "PhaseA";
        } else if (aDomains[aDomainIndex] == TwistDomain::kPhaseB) {
            aDomainPartialName = "PhaseB";
        } else if (aDomains[aDomainIndex] == TwistDomain::kPhaseC) {
            aDomainPartialName = "PhaseC";
        } else {
            aDomainPartialName = "PhaseD";
        }
        
        
        std::vector<GStatement> aStatementsKDFA;
        GKDF_A aKDF_A;
        aKDF_A.mSnow = mSnowLane[aDomainIndex % 4U];
        if (!aKDF_A.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kInbuilt,
                         &aStatementsKDFA,
                         pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake inbuilt KDF:\n" + *pErrorMessage;
            }
            return false;
        }
        for (const GStatement &aStatement : aStatementsKDFA) {
            if (!aStatement.IsRawLine()) {
                continue;
            }
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        
        
        std::vector<GStatement> aStatementsInvestA;
        GInvest aInvest;
        
        std::vector<SymbolAndBox> *aInvestData = &aInvestA;
        for (int i=0;i<4;i++) {
            int aBox = (*aInvestData)[i].mBox;
            if (aBox == 0) {
                if (!aInvest.BakeInvestBlockKeyBoxA((*aInvestData)[i].mSymbol, &aStatementsInvestA, pErrorMessage)) {
                    return false;
                }
            } else if (aBox == 1) {
                if (!aInvest.BakeInvestBlockKeyBoxB((*aInvestData)[i].mSymbol, &aStatementsInvestA, pErrorMessage)) {
                    return false;
                }
            } else if (aBox == 2) {
                if (!aInvest.BakeInvestBlockMaskBoxA((*aInvestData)[i].mSymbol, &aStatementsInvestA, pErrorMessage)) {
                    return false;
                }
            } else if (aBox == 3) {
                if (!aInvest.BakeInvestBlockMaskBoxB((*aInvestData)[i].mSymbol, &aStatementsInvestA, pErrorMessage)) {
                    return false;
                }
            } else {
                printf("null option\n");
                return false;
            }
        }
        for (const GStatement &aStatement : aStatementsInvestA) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        
        std::vector<GStatement> aStatementsFarmA;
        Random::Shuffle(&aExpansionLanes);
        GFarm aFarm;
        if (!aFarm.BakeEphemeral(aExpansionLanes[0],
                                 aExpansionLanes[1],
                                 aExpansionLanes[2],
                                 aExpansionLanes[3],
                                 aDomainPartialName,
                                 &aStatementsFarmA,
                                 pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake farm after KDFA:\n" + *pErrorMessage;
            }
            return false;
        }
        
        for (const GStatement &aStatement : aStatementsFarmA) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        
        std::vector<GStatement> aStatementsKDFB;
        GKDF_B aKDF_B;
        if (!aKDF_B.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kEphemeral,
                         &aStatementsKDFB,
                         pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake inbuilt KDF_B:\n" + *pErrorMessage;
            }
            return false;
        }
        for (const GStatement &aStatement : aStatementsKDFB) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        
        
        std::vector<GStatement> aStatementsFarmB;
        Random::Shuffle(&aWorkLanes);
        if (!aFarm.BakeWorkspace(aExpansionLanes[0],
                                 aExpansionLanes[1],
                                 aExpansionLanes[2],
                                 aExpansionLanes[3],
                                 aDomainPartialName,
                                 &aStatementsFarmB,
                                 pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake farm after KDFA:\n" + *pErrorMessage;
            }
            return false;
        }
        
        for (const GStatement &aStatement : aStatementsFarmB) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        
    }
    
    return true;
    
}
