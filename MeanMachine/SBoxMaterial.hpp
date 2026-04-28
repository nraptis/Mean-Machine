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
#include "ByteMap.hpp"
#include "ByteString.hpp"

class SBoxMaterial {
public:

    SBoxMaterial();

    void                                        AddPasser(const ByteString &pString);
    
    bool                                        WriteOutPassers();
    
    std::vector<ByteString>                     mListPassers;

    std::string                                 mOutputDirectoryPassers;
    
    std::string                                 mOutputFilePrefix;
    std::string                                 mOutputFileExtension;
    
    std::uint32_t                               mOutputFileDigitCount;
    std::uint32_t                               mStringsPerOutputFilePassers;
    
    std::uint32_t                               mFileIndexPassers;
    
    
private:
    bool                                        WriteOutPasser(std::vector<ByteString> &mList);
    
};

#endif /* SBoxMaterial_hpp */
