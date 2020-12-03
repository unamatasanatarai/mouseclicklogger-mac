#include "mouselogger.h"

int main(int argc, const char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "ERROR: You must specify the full path to the logs folder.\n");
        exit(1);
    }

    sprintf(logDirectory, "%s", argv[1]);

    CGEventMask eventMask = (CGEventMaskBit(kCGEventLeftMouseDown) | CGEventMaskBit(kCGEventRightMouseDown) | CGEventMaskBit(kCGEventOtherMouseDown) | CGEventMaskBit(kCGEventScrollWheel));
    CFMachPortRef eventTap = CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, CGEventCallback, NULL
    );

    if(!eventTap) {
        fprintf(stderr, "ERROR: Unable to create event tap.\n");
        exit(1);
    }

    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);

    createNewFile();

    CFRunLoopRun();

    return 0;
}

bool hasDayChanged() {
    now = time(NULL);
    tm  = localtime(&now);
    return tm->tm_mday != theday;
}

CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    if (hasDayChanged()) {
        createNewFile();
    }

    fprintf(logfile, "%s\n", recognizeMouseButton(type));
    fflush(logfile);

    return event;
}

const char *recognizeMouseButton(CGEventType type){
    if (type == kCGEventLeftMouseDown){
        return "L";
    }
    if (type == kCGEventRightMouseDown){
        return "R";
    }
    if (type == kCGEventScrollWheel){
        return "W";
    }
    return "O";
}

void createNewFile() {
    now = time(NULL);
    tm  = localtime(&now);
    theday = tm->tm_mday;
    sprintf(logFileLocation, "%s/m%04d%02d%02d.log", logDirectory, tm->tm_year+1900, tm->tm_mon+1, theday);
    logfile = fopen(logFileLocation, "a");

    if (!logfile) {
        fprintf(stderr, "ERROR: Unable to access click log file. Please make sure you have the correct permissions.\n");
        exit(1);
    }
}
