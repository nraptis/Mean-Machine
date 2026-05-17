#ifndef GMoxPlanner_hpp
#define GMoxPlanner_hpp

#include <string>

#include "GMoxPlan.hpp"

class GMoxPlanner {
public:
    static bool Bake(GMoxPlan *plan,
                     const GMoxModel &model,
                     std::string *error);

private:
    static bool Configure(GMoxPlan *plan, std::string *error);
    static bool BuildSeeds(GMoxPassPlan *pass, const GMoxFormat &format);
    static bool BuildForward(GMoxPassPlan *pass, const GMoxSkeletonPass &skeleton);
    static bool BuildCrush(GMoxPassPlan *pass);
    static bool BuildUnwind(GMoxPassPlan *pass, const GMoxSkeletonPass &skeleton);
    static bool BuildCarry(GMoxPassPlan *pass);
};

#endif /* GMoxPlanner_hpp */
