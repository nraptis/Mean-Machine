//
//  SnapShotter.hpp
//  MeanMachine
//
//  Created by icarus black on 6/28/26.
//

#ifndef SnapShotter_hpp
#define SnapShotter_hpp

#include "TwistWorkSpace.hpp"
#include <string>

class SnapShotter {
public:
    
    static void SnapStart_KDFA(TwistWorkSpace *pWorkSpace);
    static void SnapUpdate_KDFA(TwistWorkSpace *pWorkSpace, std::string pName);
    
    
    
};

#endif /* SnapShotter_hpp */
