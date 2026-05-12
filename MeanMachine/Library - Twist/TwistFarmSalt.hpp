//
//  TwistFarmSalt.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/6/26.
//

#ifndef TwistFarmSalt_hpp
#define TwistFarmSalt_hpp

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <limits>
#include "TwistCryptoScoring.hpp"
#include "TwistWorkSpace.hpp"

//16384 / 32 = 512 / / 8 = 64

// ((c / 8) / S_SALT)
#define SALT_CANDIDATE_COUNT ((S_BLOCK >> 3) >> S_SALT_DIVIDE_BITSHIFT)

struct TwistFarmSaltStats {
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

class TwistFarmSalt {
public:
    TwistFarmSalt();
    
    void Reset();
    
    // We try to get to pTargetCount passing salt grading.
    // if we failed, we return false.
    bool TillBytes(const std::uint8_t *pSource,
                   const std::uint8_t *pSnow,
                   std::uint64_t pTargetCount);
    
    
    void                    Derive(const std::uint8_t *pSource,
                                   std::uint64_t *pSaltA,
                                   std::uint64_t *pSaltB,
                                   std::uint64_t *pSaltC,
                                   std::uint64_t *pSaltD,
                                   std::uint64_t *pSaltE,
                                   std::uint64_t *pSaltF);

    std::uint64_t           *mCandidateSalt[SALT_CANDIDATE_COUNT];
    std::uint64_t           mCandidateSaltFlat[SALT_CANDIDATE_COUNT * S_SALT];
    std::int32_t            mCandidateScore[SALT_CANDIDATE_COUNT];
    std::int32_t            mCandidateClaimed[SALT_CANDIDATE_COUNT];
    
    std::uint64_t           *mFillSalt[SALT_CANDIDATE_COUNT];
    
    
    
    std::uint64_t mSalt[1024][S_SALT];
    std::uint64_t mScore[1024];
    std::uint64_t mCount;
    
private:
    
    TwistCryptoScoring                  mAnalyzer;
    
    static constexpr std::uint64_t kCapacity = 1024ULL;
    
    
    void BuildCandidate(const std::uint8_t *pSource,
                        const std::uint8_t *pSnow,
                        std::uint32_t pCandidateIndex);
    
    int ComputeNearestDistance(const std::uint64_t *pCandidate);
    
    bool AppendAccepted(const std::uint64_t *pCandidate,
                        std::uint64_t pScore);
    
};

#endif /* TwistFarmSalt_hpp */
