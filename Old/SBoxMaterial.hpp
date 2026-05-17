//
//  SBoxMaterial.hpp
//  Superfox
//
//  Created by Sonic The Hedge Whore on 4/10/26.
//

#ifndef SBoxMaterial_hpp
#define SBoxMaterial_hpp

#include <map>
#include <stdio.h>
#include <string>
#include <vector>

class SBoxMaterial {
public:

    SBoxMaterial();
    
    void                                        AddPasser(const std::vector<std::uint8_t> &pBox);
    
    bool                                        WriteOutPassers();
    
    std::vector<std::vector<std::uint8_t>>                     mListPassers;

    std::string                                 mOutputDirectoryPassers;
    
    std::string                                 mOutputFilePrefix;
    std::string                                 mOutputFileExtension;
    
    std::uint32_t                               mOutputFileDigitCount;
    std::uint32_t                               mStringsPerOutputFilePassers;
    
    std::uint32_t                               mFileIndexPassers;
    
    
private:
    bool                                        WriteOutPasser(std::vector<std::vector<std::uint8_t>> &mList);
    
};

#endif /* SBoxMaterial_hpp */
