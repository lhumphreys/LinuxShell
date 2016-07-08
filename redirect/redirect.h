#ifndef REDIRECT_H
#define REDIRECT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../tokenize/makeArgs.h"
#include "../process/process.h"

int containsRedirect(char * s);
int containsInputRedirect(char * s);
int containsOutputRedirect(char * s);
int containsAppendRedirect(char * s);
void parseRedirects(char * s, int * inFD, int * outFD, int * argc, char *** argv);
void redirectIt(char ** argv, int inFD, int outFD);

#endif
