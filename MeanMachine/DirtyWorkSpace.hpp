//
//  DirtyWorkSpace.hpp
//  MeanMachine
//
//  Created by icarus black on 6/30/26.
//

#ifndef DirtyWorkSpace_hpp
#define DirtyWorkSpace_hpp

class TwistExpander;
class TwistWorkSpace;

class DirtyWorkSpace {
public:
    static void                             Scramble(TwistWorkSpace *pWorkSpace,
                                                     TwistExpander *pExpander);
};

#endif /* DirtyWorkSpace_hpp */
