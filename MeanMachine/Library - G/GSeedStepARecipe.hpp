//
//  GSeedStepARecipe.hpp
//  MeanMachine
//
//  Created by Magneto on 4/27/26.
//

#ifndef GSeedStepARecipe_hpp
#define GSeedStepARecipe_hpp

#include "GSeedProgram.hpp"
#include "GSymbol.hpp"
#include "GStatementRecipe.hpp"
#include "GQuick.hpp"
#include "Random.hpp"
#include <cstdint>
#include <vector>
#include <string>

#define SEED_WORK_LANE_COUNT 4

#define SEED_WORK_LANE_CARRY_MIN 1
#define SEED_WORK_LANE_CARRY_MAX 3

#define SEED_WORK_LANE_PERMUTE_MIN 1
#define SEED_WORK_LANE_PERMUTE_MAX 3

enum class SeedLoopOrder : std::uint8_t {
    kValueCarryPermute = 0,
    kValuePermuteCarry = 1,
};

enum class SeedConsumeOrder : std::uint8_t {
    kBeforeSBox = 0,
    kAfterSBox = 1,
};

enum class LoopSBoxBehavior : std::uint8_t {
    kInv = 0,
    kMixWithLoopIndex = 1,
    kPassSelfThroughLowBit = 2,
    kPassSelfThroughHighBit = 2,
};

enum class LoopSaltBehavior : std::uint8_t {
    kInv = 0,
    kLoopIndex = 1,
    kSourceA = 2,
    kSourceB = 3,
    kSourceC = 4,
    kValue = 5,
    kCarry = 6
};

enum class LoopAdditionalSourceMode : std::uint8_t {
    kInv = 0,
    kValue = 1,
    kCarry = 2,
    kPermute = 3
};

struct GSeedStepARecipeLoopContract {
    
    LoopSaltBehavior                        mValueSaltBehavior;
    SeedConsumeOrder                        mValueConsumeOrder_Carry;
    SeedConsumeOrder                        mValueConsumeOrder_SourceA;
    SeedConsumeOrder                        mValueConsumeOrder_SourceB;
    SeedConsumeOrder                        mValueConsumeOrder_SourceC;
    SeedConsumeOrder                        mValueConsumeOrder_Salt;
    
    bool                                    mCarryEnabled;
    LoopSaltBehavior                        mCarrySaltBehavior;
    LoopSBoxBehavior                        mCarrySBoxBehavior;
    SeedConsumeOrder                        mCarryConsumeOrder_Value;
    SeedConsumeOrder                        mCarryConsumeOrder_SourceB;
    SeedConsumeOrder                        mCarryConsumeOrder_SourceC;
    SeedConsumeOrder                        mCarryConsumeOrder_Salt;
    
    bool                                    mPermuteEnabled;
    LoopSaltBehavior                        mPermuteSaltBehavior;
    LoopSBoxBehavior                        mPermuteSBoxBehavior;
    SeedConsumeOrder                        mPermuteConsumeOrder_Carry;
    SeedConsumeOrder                        mPermuteConsumeOrder_Value;
    SeedConsumeOrder                        mPermuteConsumeOrder_Salt;
    SeedConsumeOrder                        mPermuteConsumeOrder_SourceB;
    SeedConsumeOrder                        mPermuteConsumeOrder_SourceC;
    bool                                    mPermuteUseCarry;
    
    bool                                    HasValueSourceA();
    bool                                    HasValueSourceB();
    bool                                    HasValueSourceC();
    
    bool                                    HasCarrySourceA();
    bool                                    HasCarrySourceB();
    bool                                    HasCarrySourceC();
    
    bool                                    HasPermuteSourceA();
    bool                                    HasPermuteSourceB();
    bool                                    HasPermuteSourceC();
    
    
    bool                                    mSecondSourceEnabled;
    LoopAdditionalSourceMode                mSecondSourceMode;
    
    GSymbol                                 mValueSalt;
    GSymbol                                 mValueSBoxA;
    GSymbol                                 mValueSBoxB;
    
    GSymbol                                 mCarrySalt;
    GSymbol                                 mCarrySBoxA;
    GSymbol                                 mCarrySBoxB;
    
    GSymbol                                 mPermuteSalt;
    GSymbol                                 mPermuteSBoxA;
    GSymbol                                 mPermuteSBoxB;
    
    GSymbol                                 mSourceA;
    GSymbol                                 mSourceB;
    GSymbol                                 mSourceC;
    
    GSymbol                                 mDest;
    
    SeedLoopOrder                           mLoopOrder;
    
};

struct GSeedStepARecipeWorkSpace {
public:
    GSeedStepARecipeWorkSpace();
    
    bool                                    Plan(bool pSecondPass, std::string &pErrorString);
    bool                                    Bake(std::vector<GLoop> &pResult, std::string &pErrorString);
    
    GSeedStepARecipeLoopContract            mLoopContracts[SEED_WORK_LANE_COUNT];
    
    GSymbol                                 mLoopIndex;
    
    GSymbol                                 mSource;
    
    GSymbol                                 mValue;
    GSymbol                                 mPermute;
    GSymbol                                 mCarry;
    
    GSymbol                                 mSBoxA;
    GSymbol                                 mSBoxB;
    GSymbol                                 mSBoxC;
    GSymbol                                 mSBoxD;
    
    GSymbol                                 mSaltA;
    GSymbol                                 mSaltB;
    GSymbol                                 mSaltC;
    GSymbol                                 mSaltD;
    
    GSymbol                                 mWorkerA;
    GSymbol                                 mWorkerB;
    GSymbol                                 mWorkerC;
    GSymbol                                 mWorkerD;
    
    bool                                    mSecondPass;
    
    GSymbol                                 mValueNibbleA;
    GSymbol                                 mValueNibbleB;
    GSymbol                                 mValueNibbleC;
    GSymbol                                 mValueNibbleD;
    
};


#endif /* GSeedStepARecipe_hpp */
