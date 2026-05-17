#ifndef GMoxPrinter_hpp
#define GMoxPrinter_hpp

#include <string>

#include "GMoxPlan.hpp"

class GMoxPrinter {
public:
    struct Options {
        bool mIncludePlugs = true;
        bool mIncludeRotations = true;
        bool mIncludeSaltLanes = true;
        bool mIncludeModelSummary = true;
        bool mIncludeGroups = true;
    };

    static void Print(const GMoxPlan &plan);
    static void Print(const GMoxPlan &plan, const Options &options);

    static std::string ToString(const GMoxPlan &plan);
    static std::string ToJsonLikeString(const GMoxPlan &plan);
};

#endif /* GMoxPrinter_hpp */
