//
//  main.m
//  MeanMachine
//
//  Created by John Snow on 4/20/26.
//

#import <Cocoa/Cocoa.h>
#include <string.h>

extern int MeanMachineRunExporter(void);
extern int MeanMachineBuildTestExpander(void);
extern int MeanMachineRegenerateFoldControls(void);

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        if ((argc > 1) &&
            ((strcmp(argv[1], "--export-control-values") == 0) ||
             (strcmp(argv[1], "--export-lane-splits") == 0))) {
            return MeanMachineRunExporter();
        }
        if ((argc > 1) &&
            (strcmp(argv[1], "--build-test-expander") == 0)) {
            return MeanMachineBuildTestExpander();
        }
        if ((argc > 1) &&
            (strcmp(argv[1], "--regenerate-fold-controls") == 0)) {
            return MeanMachineRegenerateFoldControls();
        }
    }
    return NSApplicationMain(argc, argv);
}
