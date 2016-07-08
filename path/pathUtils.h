#ifndef PATHUTILS_H
#define PATHUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/myUtils.h"
#include "../linkedlist/linkedList.h"
#include "../linkedlist/genericData.h"
#include "path.h"

LinkedList * PATH;

void parsePath(char * str);

void appendPath(char * str);

void replacePath(char * str);

void cleanPath();

#endif 
