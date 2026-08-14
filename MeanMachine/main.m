//
//  main.m
//  MeanMachine
//
//  Created by John Snow on 4/20/26.
//

#import <Cocoa/Cocoa.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern int MeanMachineRunExporter(void);
extern int MeanMachineBuildTestExpander(void);
extern int MeanMachineBuildAllExpanders(void);
extern int MeanMachineBuildExpanderRange(int pStartIndex, int pCount);
extern int MeanMachineRegenerateKeyForkControl(uint64_t pExplorationCases);
extern int MeanMachineRegenerateKeyLaneControl(uint64_t pExplorationCases);
extern int MeanMachineRegenerateResidualKDFControl(uint64_t pExplorationCases);
extern int MeanMachineGenerateLoopRolePermutations(void);

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        if ((argc > 1) &&
            (strcmp(argv[1], "--export-control-values") == 0)) {
            return MeanMachineRunExporter();
        }
        if ((argc > 1) &&
            (strcmp(argv[1], "--build-test-expander") == 0)) {
            return MeanMachineBuildTestExpander();
        }
        if ((argc > 1) &&
            (strcmp(argv[1], "--build-all-expanders") == 0)) {
            return MeanMachineBuildAllExpanders();
        }
        if ((argc > 3) &&
            (strcmp(argv[1], "--build-expander-range") == 0)) {
            const int aStartIndex = (int)strtol(argv[2], NULL, 10);
            const int aCount = (int)strtol(argv[3], NULL, 10);
            return MeanMachineBuildExpanderRange(aStartIndex, aCount);
        }
        if ((argc > 1) &&
            (strcmp(argv[1], "--regenerate-key-fork-control") == 0)) {
            const uint64_t aExplorationCases =
                argc > 2
                    ? strtoull(argv[2], NULL, 10)
                    : 1000ULL;
            return MeanMachineRegenerateKeyForkControl(
                aExplorationCases == 0ULL ? 1ULL : aExplorationCases);
        }
        if ((argc > 1) &&
            (strcmp(argv[1], "--regenerate-key-lane-control") == 0)) {
            const uint64_t aExplorationCases =
                argc > 2
                    ? strtoull(argv[2], NULL, 10)
                    : 1000ULL;
            return MeanMachineRegenerateKeyLaneControl(
                aExplorationCases == 0ULL ? 1ULL : aExplorationCases);
        }
        if ((argc > 1) &&
            (strcmp(argv[1], "--regenerate-residual-kdf-control") == 0)) {
            const uint64_t aExplorationCases =
                argc > 2
                    ? strtoull(argv[2], NULL, 10)
                    : 1000ULL;
            return MeanMachineRegenerateResidualKDFControl(
                aExplorationCases == 0ULL ? 1ULL : aExplorationCases);
        }
        if ((argc > 1) &&
            (strcmp(argv[1], "--generate-loop-role-permutations") == 0)) {
            return MeanMachineGenerateLoopRolePermutations();
        }
    }
    return NSApplicationMain(argc, argv);
}
