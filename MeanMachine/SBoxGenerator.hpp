//
//  SBoxGenerator.hpp
//  MeanMachine
//
//  Created by Dragon on 4/28/26.
//

#ifndef SBoxGenerator_hpp
#define SBoxGenerator_hpp

#include <cstdint>
#include "ByteString.hpp"
#include "SBoxAnalyzer.hpp"
#include "TwistWorkSpace.hpp"

class SBoxGenerator {
public:
    
    SBoxGenerator();
    ~SBoxGenerator();
    
    void                            Make(const std::uint8_t *pSource,
                                         std::uint8_t *pSBoxA,
                                         std::uint8_t *pSBoxB,
                                         std::uint8_t *pSBoxC,
                                         std::uint8_t *pSBoxD);
    
    std::uint8_t                    mCandidates[256][256];
    
private:
    
    std::uint8_t                    mMatrices[256][8];
    int                             mScores[256];
    
    std::uint8_t                    mExp[512];
    std::uint8_t                    mLog[256];
    int                             mExponents[5];
    bool                            mTablesBuilt;
    
    SBoxAnalyzer                    mAnalyzer;
    
    void                            BuildGFTables();
    
    std::uint8_t                    ReadSeed(const std::uint8_t *pSource, int pIndex);
    
    void                            BuildMatrix(const std::uint8_t *pSource,
                                                int aIndex,
                                                std::uint8_t *pMatrix);
    
    void                            ApplyMatrix(const std::uint8_t *pMatrix,
                                                const std::uint8_t *pInput,
                                                std::uint8_t *pOutput);
    
    void                            GenerateCandidate(const std::uint8_t *pSource,
                                                      int aIndex,
                                                      std::uint8_t *pOutput);
    
    int                             ScoreCandidate(const std::uint8_t *pBox);
    
};

#endif
