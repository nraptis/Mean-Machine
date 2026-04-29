//
//  TwistCryptoGenerator.hpp
//  MeanMachine
//
//  Created by Dragon on 4/28/26.
//

#ifndef TwistCryptoGenerator_hpp
#define TwistCryptoGenerator_hpp

#include <cstdint>
#include "TwistCryptoScoring.hpp"
#include "TwistWorkSpace.hpp"

#define CRYPTO_GENERATOR_ITERATIONS 4
#define CRYPTO_GENERATOR_SALT_HOP 16
#define CRYPTO_GENERATOR_SALT_COUNT (((S_BLOCK - S_SALT) / CRYPTO_GENERATOR_SALT_HOP) + 1)
#define CRYPTO_GENERATOR_SALT_MIN_DISTANCE 8

class TwistCryptoGenerator {
public:
    
    TwistCryptoGenerator();
    
    void                                Make(const std::uint8_t *pSource,
                                             std::uint8_t *pSBoxA,
                                             std::uint8_t *pSBoxB,
                                             std::uint8_t *pSBoxC,
                                             std::uint8_t *pSBoxD);
    
    void                                Make(const std::uint8_t *pSource,
                                             std::uint8_t *pSBoxA,
                                             std::uint8_t *pSBoxB,
                                             std::uint8_t *pSBoxC,
                                             std::uint8_t *pSBoxD,
                                             std::uint8_t *pExistingSBoxA,
                                             std::uint8_t *pExistingSBoxB,
                                             std::uint8_t *pExistingSBoxC,
                                             std::uint8_t *pExistingSBoxD);
    
    
    void                                Salt(const std::uint8_t *pSource,
                                             std::uint8_t *pSaltA,
                                             std::uint8_t *pSaltB,
                                             std::uint8_t *pSaltC,
                                             std::uint8_t *pSaltD,
                                             std::uint8_t *pSBoxA,
                                             std::uint8_t *pSBoxB,
                                             std::uint8_t *pSBoxC,
                                             std::uint8_t *pSBoxD);

    void                                Salt(const std::uint8_t *pSource,
                                             std::uint8_t *pSaltA,
                                             std::uint8_t *pSaltB,
                                             std::uint8_t *pSaltC,
                                             std::uint8_t *pSaltD,
                                             std::uint8_t *pExistingSaltA,
                                             std::uint8_t *pExistingSaltB,
                                             std::uint8_t *pExistingSaltC,
                                             std::uint8_t *pExistingSaltD,
                                             std::uint8_t *pSBoxA,
                                             std::uint8_t *pSBoxB,
                                             std::uint8_t *pSBoxC,
                                             std::uint8_t *pSBoxD,
                                             std::uint8_t *pSBoxE,
                                             std::uint8_t *pSBoxF,
                                             std::uint8_t *pSBoxG,
                                             std::uint8_t *pSBoxH);
    
    std::uint8_t                        mCandidates[CRYPTO_GENERATOR_ITERATIONS * 256][256];
    
private:
    
    
    
    int                                 mScores[CRYPTO_GENERATOR_ITERATIONS * 256];
    
    std::uint8_t                        mExp[512];
    std::uint8_t                        mLog[256];
    int                                 mExponents[5];
    bool                                mTablesBuilt;
    
    std::uint8_t                        *mSalts[CRYPTO_GENERATOR_SALT_COUNT];
    int                                 mSaltScores[CRYPTO_GENERATOR_SALT_COUNT];
    
    
    TwistCryptoScoring                  mAnalyzer;
    
    void                                ProceedWithTopSixteen(int *aBestIndex,
                                                              std::uint8_t *pSBoxA,
                                                              std::uint8_t *pSBoxB,
                                                              std::uint8_t *pSBoxC,
                                                              std::uint8_t *pSBoxD,
                                                              std::uint8_t *pExistingSBoxA,
                                                              std::uint8_t *pExistingSBoxB,
                                                              std::uint8_t *pExistingSBoxC,
                                                              std::uint8_t *pExistingSBoxD);
    
    void                                ProceedWithTopTwelve(int *aBestIndex,
                                                              std::uint8_t *pSaltA,
                                                              std::uint8_t *pSaltB,
                                                              std::uint8_t *pSaltC,
                                                              std::uint8_t *pSaltD,
                                                              std::uint8_t *pExistingSaltA,
                                                              std::uint8_t *pExistingSaltB,
                                                              std::uint8_t *pExistingSaltC,
                                                              std::uint8_t *pExistingSaltD,
                                                              std::uint8_t *pSBoxA,
                                                              std::uint8_t *pSBoxB,
                                                              std::uint8_t *pSBoxC,
                                                              std::uint8_t *pSBoxD,
                                                              std::uint8_t *pSBoxE,
                                                              std::uint8_t *pSBoxF,
                                                              std::uint8_t *pSBoxG,
                                                              std::uint8_t *pSBoxH);
    
    void                                BuildGFTables();
    
    std::uint8_t                        ReadSeed(const std::uint8_t *pSource, int pIndex);
    
    void                                BuildMatrix(const std::uint8_t *pSource,
                                                    int aIndex,
                                                    std::uint8_t *pMatrix);
    
    void                                ApplyMatrix(const std::uint8_t *pMatrix,
                                                    const std::uint8_t *pInput,
                                                    std::uint8_t *pOutput);
    
    void                                GenerateCandidate(const std::uint8_t *pSource,
                                                          const std::uint8_t *pFeedBack,
                                                          int aIndex,
                                                          std::uint8_t *pOutput);
    
    int                                 ScoreCandidate(const std::uint8_t *pBox);
    
};

#endif
