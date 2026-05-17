//
//  ToonFarmSalt.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/6/26.
//

#ifndef ToonFarmSalt_hpp
#define ToonFarmSalt_hpp

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <limits>
#include "ToonCryptoScoring.hpp"
#include "ToonWorkSpace.hpp"

//16384 / 32 = 512 / / 8 = 64

// ((c / 8) / S_SALT)
#define SALT_CANDIDATE_COUNT ((S_BLOCK >> 3) >> S_SALT_DIVIDE_BITSHIFT)

struct ToonFarmSaltStats {
    std::uint64_t mCandidatesTested;
    std::uint64_t mAccepted;
    std::uint64_t mFallbackAccepted;

    std::uint64_t mRejectBitBalance;
    std::uint64_t mRejectByteSpread;
    std::uint64_t mRejectXorDrift;
    std::uint64_t mRejectAdjacencyPenalty;
    std::uint64_t mRejectMinDistance;

    int mBestBitBalance;
    int mBestByteSpread;
    int mBestXorDrift;
    int mBestAdjacencyPenalty;
    int mBestMinDistance;
    std::uint64_t mBestScore;
};

class ToonFarmSalt {
public:
    ToonFarmSalt();
    
    void                    Derive(const std::uint8_t *pSource,
                                   std::uint64_t *pSaltA,
                                   std::uint64_t *pSaltB,
                                   std::uint64_t *pSaltC,
                                   std::uint64_t *pSaltD,
                                   std::uint64_t *pSaltE,
                                   std::uint64_t *pSaltF);
    void                    Derive(const std::uint8_t *pSource,
                                   ToonDomainRoundMaterial *pRoundMaterial);

    std::uint64_t           *mCandidateSalt[SALT_CANDIDATE_COUNT];
    std::uint64_t           mCandidateSaltFlat[SALT_CANDIDATE_COUNT * S_SALT];
    std::int32_t            mCandidateScore[SALT_CANDIDATE_COUNT];
    std::int32_t            mCandidateClaimed[SALT_CANDIDATE_COUNT];
    
    std::uint64_t           *mFillSalt[SALT_CANDIDATE_COUNT];
    
    
private:
    
    ToonCryptoScoring                  mAnalyzer;
    
};

#endif /* ToonFarmSalt_hpp */
