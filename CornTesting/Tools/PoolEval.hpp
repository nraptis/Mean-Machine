//
//  PoolEval.hpp
//  CornTesting
//
//  Created by Magneto on 4/21/26.
//

#ifndef PoolEval_hpp
#define PoolEval_hpp

#include "GSymbol.hpp"
#include "GStatementRecipe.hpp"
#include "TwistWorkSpace.hpp"
#include <vector>

class PoolEval {
public:
    
    
    static int                          Count(const std::vector<GStatementSlot> &pSlots, const GSymbol pSymbol);
    static int                          Count(const std::vector<GStatementSlot> &pSlots, const GExpr pExpr);
    
    
    static void                         ResetTwo(std::vector<bool> &pAchieveA,
                                                 std::vector<bool> &pAchieveB);
    static bool                         UpdateTwo(int pMinA,
                                                  int pMaxA,
                                                  
                                                  int pCountA,
                                                  
                                                  int pMinB,
                                                  int pMaxB,
                                                  int pCountB,
                                                  
                                                  std::vector<bool> &pAchieveA,
                                                  std::vector<bool> &pAchieveB,
                                                  
                                                  int pTotalMin,
                                                  int pTotalMax,
                                                  bool &pHardFailure
                                                  
                                                  );
    
    static void                         ResetThree(std::vector<bool> &pAchieveA,
                                                   std::vector<bool> &pAchieveB,
                                                   std::vector<bool> &pAchieveC);
    static bool                         UpdateThree(int pMinA,
                                                    int pMaxA,
                                                    
                                                    int pCountA,
                                                    
                                                    int pMinB,
                                                    int pMaxB,
                                                    int pCountB,
                                                    
                                                    int pMinC,
                                                    int pMaxC,
                                                    int pCountC,
                                                    
                                                    std::vector<bool> &pAchieveA,
                                                    std::vector<bool> &pAchieveB,
                                                    std::vector<bool> &pAchieveC,
                                                    
                                                    int pTotalMin,
                                                    int pTotalMax,
                                                    bool &pHardFailure
                                                    
                                                    );
    
    
};

#endif /* PoolEval_hpp */
