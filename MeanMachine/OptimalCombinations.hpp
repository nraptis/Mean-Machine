//
//  OptimalCombinations.hpp
//  MeanMachine
//

#ifndef OptimalCombinations_hpp
#define OptimalCombinations_hpp

#include <cstddef>
#include <string>

class OptimalCombinations {
public:
    struct Job {
        int                                     mWidth = 0;
        std::size_t                             mNeededCount = 0U;
        std::size_t                             mCandidateLimit = 0U;
        const char                              *mFileName = nullptr;
        const char                              *mArrayName = nullptr;
    };
    
    static bool                                 BuildProjectRoot(std::string *pErrorMessage);
    static bool                                 BuildProjectRoot(const Job *pJobs,
                                                                 std::size_t pJobCount,
                                                                 std::string *pErrorMessage);
};

#endif /* OptimalCombinations_hpp */
