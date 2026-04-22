//
//  TwistSeeder.hpp
//  Gorgon
//
//  Created by Sonic The Hedge Whore on 4/9/26.
//

#ifndef TwistSeeder_hpp
#define TwistSeeder_hpp

#include "GSeedProgram.hpp"
#include <vector>
#include "TwistWorkSpace.hpp"

class TwistSeeder {
public:
    TwistSeeder();
    virtual ~TwistSeeder();
    
    // Seeding establishes the reusable workspace state for a future twister.
    virtual void                        Seed(TwistWorkSpace *pWorkspace,
                                             std::uint8_t *pSource);

    void                                SetSeedBatch(const GBatch &pBatch);
    const GBatch&                       GetSeedBatch() const;
    std::string                         GetPrettyPrint() const;
    std::string                         GetJson(std::string *pError = nullptr) const;
    std::string                         GetCpp(const std::string &pFunctionName = "GeneratedTwistSeed",
                                               std::string *pError = nullptr) const;

    TwistWorkSpace                      *mWorkspace;
    GBatch                              mSeedBatch;

    std::uint8_t                        mSBoxA[S_SBOX];
    std::uint8_t                        mSBoxB[S_SBOX];
    std::uint8_t                        mSBoxC[S_SBOX];
    std::uint8_t                        mSBoxD[S_SBOX];

    std::uint8_t                        mSaltA[S_SALT];
    std::uint8_t                        mSaltB[S_SALT];
    std::uint8_t                        mSaltC[S_SALT];
    std::uint8_t                        mSaltD[S_SALT];
};


#endif /* TwistSeeder_hpp */
