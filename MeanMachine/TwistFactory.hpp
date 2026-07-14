//
//  TwistFactory.hpp
//  MeanMachine
//

#ifndef TwistFactory_hpp
#define TwistFactory_hpp

class TwistExpander;

class TwistFactory {
public:
    static TwistExpander                   *Get(int pIndex);
};

#endif /* TwistFactory_hpp */
