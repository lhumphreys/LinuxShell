#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../path/pathUtils.h"

void forkIt(char ** argv);
void execWithPath(char ** argv);

#endif
