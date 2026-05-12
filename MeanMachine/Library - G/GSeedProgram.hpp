//
//  GSeedProgram.hpp
//  MeanMachine
//

#ifndef GSeedProgram_hpp
#define GSeedProgram_hpp

#include "GExpr.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using GRuntimeScalar = std::uint64_t;

struct GStatement;
struct GLoop;

struct GTarget {
    GSymbol                                     mSymbol;
    std::shared_ptr<GExpr>                      mIndex;
    
    GTarget();
    
    static GTarget                              Symbol(const GSymbol &pSymbol);
    static GTarget                              Write(const GSymbol &pSymbol,
                                                      const GExpr &pIndex);
    
    void                                        Set(const GTarget &pOther);
    void                                        Invalidate();
    
    bool                                        IsInvalid() const;
    bool                                        HasIndex() const;
    bool                                        IsVar() const;
    bool                                        IsBuf() const;
    
    bool                                        HasSymbol(GSymbol pSymbol) const;
    bool                                        HasOper(GOperType pOper) const;
    
};

enum class GAssignType : std::uint8_t {
    kInvalid = 0,
    kSet = 1
};

enum class GStatementType : std::uint8_t {
    kAssign = 0,
    kRawLine = 1
};

struct GStatement {
    GStatementType                      mType;
    GTarget                             mTarget;
    GAssignType                         mAssignType;
    GExpr                               mExpression;
    std::string                         mRawLine;
    std::string                         mOutputPrefix;

    GStatement();

    static GStatement                   Assign(const GTarget &pTarget,
                                            const GExpr &pExpression);
    static GStatement                   RawLine(const std::string &pRawLine);
    static GStatement                   Comment(const std::string &pComment);
    static GStatement                   EmptyLine();

    void                                Set(const GStatement &pOther);
    void                                Invalidate();
    bool                                IsInvalid() const;
    bool                                IsRawLine() const;
    
    GSymbol                             GetAssignSymbol(int pIndex) const;
    bool                                HasAssignSymbol(int pIndex) const;
    
    GOperType                           GetAssignOper(int pIndex) const;
    bool                                HasAssignOper(int pIndex) const;
    
    GSymbol                             GetExprSymbol(int pIndex) const;
    bool                                HasExprSymbol(int pIndex) const;
    
    GOperType                           GetExprOper(int pIndex) const;
    bool                                HasExprOper(int pIndex) const;
    
    bool                                HasAssignSymbol(GSymbol pSymbol) const;
    bool                                HasAssignOper(GOperType pOper) const;
    
    bool                                HasExprSymbol(GSymbol pSymbol) const;
    bool                                HasExprOper(GOperType pOper) const;
    
    std::vector<std::string>            ToCPPStatements() const;
    std::string                         ToPretty() const;
    
};

struct GLoop {
    struct BodyDecoration {
        enum class Type : std::uint8_t {
            kComment = 0,
            kEmptyLine = 1
        };

        Type                                mType = Type::kComment;
        std::string                         mText;
        std::size_t                         mStatementIndex = 0U;
    };

    GSymbol                             mLoopVariable;
    std::string                         mLoopVariableName;
    int                                 mLoopBegin;
    std::string                         mLoopEndText;
    int                                 mLoopStep;
    std::vector<GStatement>             mInitializationStatements;
    std::vector<GStatement>             mBodyStatements;
    std::vector<BodyDecoration>         mBodyDecorations;
    
    GLoop();
    
    bool                                IsInvalid() const;

    void                                AddBodyComment(std::string);
    void                                AddBodyEmptyLine();
    void                                AddBody(GStatement *pStatement);
    void                                AddBody(GStatement pStatement);
    void                                AddBody(std::vector<GStatement> *pStatements);
    
    void                                AddInitialization(GStatement *pStatement);
    
};

enum class GWhileWorkItemType : std::uint8_t {
    kLoop = 0,
    kStatements = 1,
    kComment = 2,
    kEmptyLine = 3
};

struct GWhileWorkItem {
    GWhileWorkItemType                  mType;
    GLoop                               mLoop;
    std::vector<GStatement>             mStatements;
    std::string                         mComment;

    GWhileWorkItem();

    static GWhileWorkItem               Loop(const GLoop &pLoop);
    static GWhileWorkItem               Statements(std::vector<GStatement> *pStatements);
    static GWhileWorkItem               Comment(std::string pComment);
    static GWhileWorkItem               EmptyLine();

    bool                                IsLoop() const;
    bool                                IsStatements() const;
    bool                                IsComment() const;
    bool                                IsEmptyLine() const;
    bool                                IsInvalid() const;
};

struct GWhile {
    GSymbol                             mConditionSymbol;
    std::string                         mConditionVariableName;
    std::vector<GWhileWorkItem>         mWorkItems;

    GWhile();

    bool                                IsInvalid() const;
    void                                SetCondition(GSymbol pSymbol);
    void                                CommitLoop(GLoop *pLoop);
    void                                CommitStatements(std::vector<GStatement> *pStatements);
    void                                AddComment(std::string pComment);
    void                                AddEmptyLine();
};

enum class GBatchWorkItemType : std::uint8_t {
    kLoop = 0,
    kWhile = 1,
    kStatements = 2,
    kComment = 3,
    kEmptyLine = 4
};

struct GBatchWorkItem {
    GBatchWorkItemType                  mType;
    GLoop                               mLoop;
    GWhile                              mWhile;
    std::vector<GStatement>             mStatements;
    std::string                         mComment;

    GBatchWorkItem();

    static GBatchWorkItem               Loop(const GLoop &pLoop);
    static GBatchWorkItem               While(const GWhile &pWhile);
    static GBatchWorkItem               Statements(std::vector<GStatement> *pStatements);
    static GBatchWorkItem               Comment(std::string pComment);
    static GBatchWorkItem               EmptyLine();

    bool                                IsLoop() const;
    bool                                IsWhile() const;
    bool                                IsStatements() const;
    bool                                IsComment() const;
    bool                                IsEmptyLine() const;
    bool                                IsInvalid() const;
};

struct GBatch {
    std::string                         mName;
    std::vector<GLoop>                  mLoops;
    std::vector<GBatchWorkItem>         mWorkItems;

    GBatch();

    bool                                IsInvalid() const;
    void                                CommitLoop(GLoop *pLoop);
    void                                CommitWhile(GWhile *pWhile);
    void                                CommitStatements(std::vector<GStatement> *pStatements);
    void                                AddComment(std::string pComment);
    void                                AddEmptyLine();

    int                                 CountReads(TwistWorkSpaceSlot pSlot) const;
    int                                 CountWrites(TwistWorkSpaceSlot pSlot) const;
    int                                 CountLoopsReading(TwistWorkSpaceSlot pSlot) const;
    int                                 CountLoopsWriting(TwistWorkSpaceSlot pSlot) const;

    std::vector<std::string>            CollectVariableNames() const;
    std::vector<TwistWorkSpaceSlot>     CollectReferencedSlots() const;

    std::string                         ToPrettyString() const;
    std::string                         ToJson(std::string *pErrorMessage = nullptr) const;
    static bool                         FromJson(const std::string &pJsonText,
                                                 GBatch *pBatch,
                                                 std::string *pErrorMessage = nullptr);

    std::string                         BuildCpp(const std::string &pFunctionName = "GeneratedTwistSeed",
                                                 std::string *pErrorMessage = nullptr,
                                                 bool pEmitDeclarations = true) const;
    std::string                         BuildCppScopeBlock(std::string *pErrorMessage = nullptr,
                                                           bool pEmitDeclarations = true) const;

    bool                                Execute(TwistWorkSpace *pWorkspace,
                                                TwistExpander *pExpander,
                                                std::string *pErrorMessage = nullptr) const;
    bool                                ExecuteWithVariables(TwistWorkSpace *pWorkspace,
                                                             TwistExpander *pExpander,
                                                             std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                                             std::string *pErrorMessage = nullptr) const;
};

#endif /* GSeedProgram_hpp */
