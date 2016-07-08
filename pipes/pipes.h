#ifndef PIPES_H
#define PIPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../tokenize/makeArgs.h"
#include "../process/process.h"
#include "../redirect/redirect.h"

int containsPipe(char *s);
char ** parsePrePipe(char *s, int * preCount, int * inFD);
char ** parsePostPipe(char *s, int * postCount, int * outFD);
char ** parseMidPipe(char *s, int * midCount);
void pipeIt(char ** prePipe, char ** postPipe, int inFD, int outFd);
void pipeItTwice(char ** prePipe, char ** midPipe, char ** postPipe,  int inFD, int outFD);

#endif 
