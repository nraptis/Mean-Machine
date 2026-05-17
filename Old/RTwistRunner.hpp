//
//  RTwistRunner.hpp
//  MeanMachine
//

#ifndef RTwistRunner_hpp
#define RTwistRunner_hpp

#include "GSeedProgram.hpp"
#include "GTwistSeeder.hpp"

#include <string>

class RTwistRunner {
public:
    static bool                         LoadSeedBatchFromJsonText(const std::string &pJsonText,
                                                                  GBatch *pBatch,
                                                                  std::string *pError = nullptr);
    static bool                         LoadSeedBatchFromJsonFile(const std::string &pPath,
                                                                  GBatch *pBatch,
                                                                  std::string *pError = nullptr);

    static bool                         ConfigureSeederFromJsonText(GTwistSeeder *pSeeder,
                                                                    const std::string &pJsonText,
                                                                    std::string *pError = nullptr);
    static bool                         ConfigureSeederFromJsonFile(GTwistSeeder *pSeeder,
                                                                    const std::string &pPath,
                                                                    std::string *pError = nullptr);

    static bool                         SaveSeedBatchJsonFile(const GBatch &pBatch,
                                                              const std::string &pPath,
                                                              std::string *pError = nullptr);
    static bool                         SaveSeederJsonFile(const GTwistSeeder &pSeeder,
                                                           const std::string &pPath,
                                                           std::string *pError = nullptr);

    static bool                         SaveSeedBatchCppFile(const GBatch &pBatch,
                                                             const std::string &pFunctionName,
                                                             const std::string &pPath,
                                                             std::string *pError = nullptr);
    static bool                         SaveSeederCppFile(const GTwistSeeder &pSeeder,
                                                          const std::string &pFunctionName,
                                                          const std::string &pPath,
                                                          std::string *pError = nullptr);

    static bool                         RunSeedBatch(const GBatch &pBatch,
                                                     TwistWorkSpace *pWorkspace,
                                                     std::uint8_t *pSource,
                                                     std::string *pError = nullptr);
};

#endif /* RTwistRunner_hpp */
