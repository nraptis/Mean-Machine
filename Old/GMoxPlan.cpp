#include "GMoxPlan.hpp"

GMoxStatement::GMoxStatement(GMoxStatementKind kind, GMoxType target) {
    mKind = kind;
    mTarget = target;
}

GMoxStatementGroup::GMoxStatementGroup(GMoxGroupKind kind) {
    mKind = kind;
}

GMoxPassPlan::~GMoxPassPlan() {
    for (GMoxStatementGroup *group : mGroups) {
        delete group;
    }
    mGroups.clear();

    for (GMoxStatement *statement : mStatements) {
        delete statement;
    }
    mStatements.clear();
}

GMoxPlan::~GMoxPlan() {
    for (GMoxPassPlan *pass : mPasses) {
        delete pass;
    }
    mPasses.clear();
}
