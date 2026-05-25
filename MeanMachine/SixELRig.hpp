//
//  SixELSixELRig.hpp
//  MeanMachine
//
//  Created by nicholas on 5/24/26.
//

#ifndef SixELSixELRig_hpp
#define SixELSixELRig_hpp


#include "FileIO.hpp"
#include "TwistExpander.hpp"
#include "TwistFunctional.hpp"
#include "TwistMemory.hpp"
#include "TwistMix64.hpp"
#include "TwistSnow.hpp"

class SixELRig {
    
public:
    
    SixELRig();
    ~SixELRig();
    
    void SetRoundCount(int pRoundCount);
    
    void                            Run(TwistExpander *pExpander,
                                        std::uint8_t *pPassword,
                                        int pPasswordLength);

    bool                            SaveByteStream(const std::string &pFolder = "") const;
    bool                            SaveByteStreamProjectRoot(const std::string &pFolder = "") const;

    bool                            SaveByteStreamLastAsciiPassword(const std::string &pFolder = "") const;
    bool                            SaveByteStreamProjectRootLastAsciiPassword(const std::string &pFolder = "") const;

    bool                            SaveByteStream(const std::string &pFolder,
                                                   const std::string &pBaseFile,
                                                   int pFileNumber) const;
    bool                            SaveByteStreamProjectRoot(const std::string &pFolder,
                                                              const std::string &pBaseFile,
                                                              int pFileNumber) const;
    
    
    TwistWorkSpace                   mWorkSpace;
    std::uint8_t                     mSource[S_BLOCK];
    
    
    std::uint8_t                    *mData;
    std::size_t                     mDataLength;
    std::size_t                      mRoundCount;
    std::string                     mLastPasswordTag;
    
    
};

#endif /* SixELSixELRig_hpp */
