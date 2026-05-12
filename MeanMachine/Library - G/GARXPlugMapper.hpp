//
//  GARXPlugMapper.hpp
//  MeanMachine
//
//  Created by Dragon on 5/9/26.
//

#ifndef GARXPlugMapper_hpp
#define GARXPlugMapper_hpp

#include <stdio.h>
#include <vector>
#include "GARXPlan.hpp"

struct GARXPlugZone {
    int                 mStartIndex;
    int                 mEndIndex;
};

class GARXPlugMapper {
public:
    GARXPlugMapper(std::vector<GARXStatementGroup *> pStatementGroups);
    std::vector<GARXStatementGroup *> mStatementGroups;
    bool AttemptAssignment();
};

#endif /* GARXPlugMapper_hpp */
