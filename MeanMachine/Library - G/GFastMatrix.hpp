//
//  GFastMatrix.hpp
//  MeanMachine
//

#ifndef GFastMatrix_hpp
#define GFastMatrix_hpp

#include "GSeedProgram.hpp"
#include "TwistFastMatrix.hpp"

#include <cstdint>
#include <string>
#include <vector>

enum class GFastMatrixType : std::uint8_t {
    kA = 0,
    kB = 1
};

using GFastMatrixOp = TwistFastMatrixOp;


struct GFastMatrixDualDiffuseOperationChannel {
    std::vector<TwistFastMatrixOp>      mSlowList;
    std::vector<TwistFastMatrixOp>      mMediumList;
    std::vector<TwistFastMatrixOp>      mFastList;
    
    TwistFastMatrixUnrollScheme         mUnrollSchemeA = TwistFastMatrixUnrollScheme::kA;
    TwistFastMatrixUnrollScheme         mUnrollSchemeB = TwistFastMatrixUnrollScheme::kC;
    
};

struct GFastMatrixDualDiffuseOperationPack {
    GFastMatrixDualDiffuseOperationChannel  mChannelA_1;
    GFastMatrixDualDiffuseOperationChannel  mChannelA_2;
    GFastMatrixDualDiffuseOperationChannel  mChannelA_3;
    GFastMatrixDualDiffuseOperationChannel  mChannelA_4;
    
    GFastMatrixDualDiffuseOperationChannel  mChannelB_1;
    GFastMatrixDualDiffuseOperationChannel  mChannelB_2;
    GFastMatrixDualDiffuseOperationChannel  mChannelB_3;
    GFastMatrixDualDiffuseOperationChannel  mChannelB_4;
    
};

class GFastMatrix {
public:
    struct ArgRead {
        GSymbol                            mOperationByte;
        GSymbol                            mOperationSource;
        GSymbol                            mOperationSourceIndex;
        std::uint32_t                      mOperationSourceOffset = 0U;
    };

    struct Step {
        GFastMatrixOp                      mOp = GFastMatrixOp::kInv;
        std::uint8_t                       mArg1 = 0U;
        std::uint8_t                       mArg2 = 0U;
        GSymbol                            mArg1Symbol;
        GSymbol                            mArg2Symbol;

        bool                               mHasArg1Read = false;
        bool                               mHasArg2Read = false;

        ArgRead                            mArg1Read;
        ArgRead                            mArg2Read;
    };

    explicit GFastMatrix(GFastMatrixType pType = GFastMatrixType::kA);

    void                                    SetType(GFastMatrixType pType);
    GFastMatrixType                         GetType() const;
    void                                    Clear();

    static TwistFastMatrixUnrollScheme      GetRandomUnrollScheme();

    static std::vector<TwistFastMatrixOp>   GetRandomOpsFromList(const std::vector<TwistFastMatrixOp> &pSourceList,
                                                                  int pCount,
                                                                  std::vector<TwistFastMatrixOp> &pIgnoreList);

    static std::vector<TwistFastMatrixOp>   GetRandomOpsFast(int pCount,
                                                             std::vector<TwistFastMatrixOp> &pIgnoreList);

    static std::vector<TwistFastMatrixOp>   GetRandomOpsMedium(int pCount,
                                                               std::vector<TwistFastMatrixOp> &pIgnoreList);

    static std::vector<TwistFastMatrixOp>   GetRandomOpsSlow(int pCount,
                                                             std::vector<TwistFastMatrixOp> &pIgnoreList);

    GFastMatrix                            &Perform(GFastMatrixOp pOp);

    GFastMatrix                            &Perform(GFastMatrixOp pOp,
                                                    GSymbol pArg1Symbol);

    GFastMatrix                            &Perform(GFastMatrixOp pOp,
                                                    GSymbol pArg1Symbol,
                                                    GSymbol pArg2Symbol);

    GFastMatrix                            &Perform(GFastMatrixOp pOp,
                                                    GSymbol pOperationByteA,
                                                    GSymbol pOperationSourceA,
                                                    GSymbol pOperationSourceIndexA,
                                                    std::uint32_t pOperationSourceOffsetA);

    GFastMatrix                            &Perform(GFastMatrixOp pOp,
                                                    GSymbol pOperationByteA,
                                                    GSymbol pOperationSourceA,
                                                    GSymbol pOperationSourceIndexA,
                                                    std::uint32_t pOperationSourceOffsetA,
                                                    GSymbol pOperationByteB,
                                                    GSymbol pOperationSourceB,
                                                    GSymbol pOperationSourceIndexB,
                                                    std::uint32_t pOperationSourceOffsetB);

    GFastMatrix                            &Perform(GFastMatrixOp pOp,
                                                    std::uint8_t pArg1,
                                                    std::uint8_t pArg2);

    bool                                    BakeLoad(GSymbol pSource,
                                                     GSymbol pLoopIndex,
                                                     std::vector<GStatement> *pStatements,
                                                     std::string *pErrorMessage) const;

    bool                                    BakePerform(std::vector<GStatement> *pStatements,
                                                        std::string *pErrorMessage) const;

    bool                                    BakePerform(std::vector<GStatement> *pStatements,
                                                        GSymbol pDomainWordArgA,
                                                        GSymbol pDomainWordArgB,
                                                        GSymbol pDomainWordArgC,
                                                        GSymbol pDomainWordArgD,
                                                        std::string *pErrorMessage) const;

    bool                                    BakeUnroll(GSymbol pDest,
                                                       GSymbol pLoopIndex,
                                                       TwistFastMatrixUnrollScheme pUnrollScheme,
                                                       GSymbol pUnrollWord,
                                                       std::vector<GStatement> *pStatements,
                                                       std::string *pErrorMessage) const;
    
    static void                             GetDualDiffuseOps(GFastMatrixDualDiffuseOperationPack *pResult);
    

private:
    static GStatement                       BuildOperationReadStatement(const ArgRead &pRead,
                                                                       GSymbol pDomainWord);

    static GSymbol                          DomainWordForOperationOffset(std::uint32_t pOperationSourceOffset,
                                                                         GSymbol pDomainWordArgA,
                                                                         GSymbol pDomainWordArgB,
                                                                         GSymbol pDomainWordArgC,
                                                                         GSymbol pDomainWordArgD);

    static TwistFastMatrixOp                GetRandomOpFromList(const std::vector<TwistFastMatrixOp> &pList,
                                                                TwistFastMatrixOp pFallback);

    static std::vector<TwistFastMatrixOp>   GetRandomOpsFromListInternal(const std::vector<TwistFastMatrixOp> &pSource,
                                                                         int pCount,
                                                                         const std::vector<TwistFastMatrixOp> &pIgnoreList);

    
    static std::string                      MatrixObjectName(GFastMatrixType pType);

    static void                             SetError(std::string *pErrorMessage,
                                                     const std::string &pMessage);
    
    
    

private:
    GFastMatrixType                         mType = GFastMatrixType::kA;
    std::vector<Step>                       mSteps;
};

#endif /* GFastMatrix_hpp */
