//
//  CompareWorkSpace.hpp
//  MeanMachine
//

#ifndef CompareWorkSpace_hpp
#define CompareWorkSpace_hpp

#include <cstddef>
#include <cstdint>
#include <string>

class TwistExpander;
class TwistWorkSpace;

class CompareWorkSpace {
public:
    static bool                             Compare(TwistWorkSpace *pLeft,
                                                    TwistWorkSpace *pRight,
                                                    std::string *pErrorMessage = nullptr);

    static bool                             Compare(TwistWorkSpace *pLeft,
                                                    TwistExpander *pLeftExpander,
                                                    TwistWorkSpace *pRight,
                                                    TwistExpander *pRightExpander,
                                                    std::string *pErrorMessage = nullptr);

    static bool                             CompareBlocks(const std::uint8_t *pLeft,
                                                          const std::uint8_t *pRight,
                                                          std::size_t pBlockCount,
                                                          std::string *pErrorMessage = nullptr);
};

#endif /* CompareWorkSpace_hpp */
