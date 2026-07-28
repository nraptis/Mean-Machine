//
//  main.m
//  MeanMachine
//
//  Created by John Snow on 4/20/26.
//

#import <Cocoa/Cocoa.h>
#include <string.h>

extern int MeanMachineRunExporter(void);

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        if ((argc > 1) &&
            ((strcmp(argv[1], "--export-control-values") == 0) ||
             (strcmp(argv[1], "--export-lane-splits") == 0))) {
            return MeanMachineRunExporter();
        }
    }
    return NSApplicationMain(argc, argv);
}
