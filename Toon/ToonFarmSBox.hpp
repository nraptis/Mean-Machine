//
//  ToonFarmSBox.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/5/26.
//

#ifndef ToonFarmSBox_hpp
#define ToonFarmSBox_hpp

#include <cstdint>
#include "ToonCryptoScoring.hpp"
#include "ToonWorkSpace.hpp"

// ((c / 8) / S_SALT)
#define SBOX_BYTES_PER_CANDIDATE 18
#define SBOX_CANDIDATE_COUNT (S_BLOCK / SBOX_BYTES_PER_CANDIDATE)
#define SBOX_CANDIDATE_MINIMUM_PERMUTATION_COUNT 64

class ToonFarmSBox {
public:
    
    ToonFarmSBox();
    
    void                                Derive(const std::uint8_t *pSource,
                                               std::uint8_t *pSBoxA,
                                               std::uint8_t *pSBoxB,
                                               std::uint8_t *pSBoxC,
                                               std::uint8_t *pSBoxD,
                                               std::uint8_t *pSBoxE,
                                               std::uint8_t *pSBoxF,
                                               std::uint8_t *pSBoxG,
                                               std::uint8_t *pSBoxH);
    void                                Derive(const std::uint8_t *pSource,
                                               ToonDomainSBoxSet *pRoundMaterial);
    
    std::uint8_t                        *mCandidateSBox[SBOX_CANDIDATE_COUNT];
    std::uint8_t                        mCandidateSBoxFlat[SBOX_CANDIDATE_COUNT * S_SBOX];
    std::int32_t                        mCandidateScore[SBOX_CANDIDATE_COUNT];
    std::int32_t                        mCandidateClaimed[SBOX_CANDIDATE_COUNT];
    std::uint8_t                        *mFillSBox[SBOX_CANDIDATE_COUNT];
    
private:
    
    inline std::uint8_t                 ApplyMatrix8(const std::uint8_t *pMatrix,
                                                     std::uint8_t pValue);
    
    
    ToonCryptoScoring                   mAnalyzer;
    std::uint8_t                        mExp[512];
    std::uint8_t                        mLog[256];
    int                                 mExponents[5];
    bool                                mTablesBuilt;
    std::uint8_t                        mInputMatrix[8];
    std::uint8_t                        mOutputMatrix[8];
    
    
    
};

#endif /* ToonFarmSBox_hpp */
