#ifndef GMoxValidator_hpp
#define GMoxValidator_hpp

#include <cstddef>
#include <string>

#include "GMoxPlan.hpp"

class GMoxValidator {
public:
    static bool Validate(const GMoxPlan &plan, std::string *error);

private:
    static bool ValidateFormat(const GMoxFormat &format, std::string *error);
    static bool ValidatePass(const GMoxPassPlan &pass,
                             const GMoxFormat &format,
                             std::size_t passIndex,
                             std::string *error);
    static bool ValidatePlugs(const GMoxPassPlan &pass,
                              const GMoxFormat &format,
                              std::string *error);
    static bool ValidateRotations(const GMoxPassPlan &pass,
                                  std::string *error);
    static bool ValidateSaltLanes(const GMoxPassPlan &pass,
                                  const GMoxFormat &format,
                                  std::string *error);
};

#endif /* GMoxValidator_hpp */
