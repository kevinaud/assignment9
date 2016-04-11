#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_COUNT 200
#define BUF_SIZE 100

/**
 * Project Specific Functions
 */
void CreateBinaryTextFile(char*);
int getIntFromBinaryFile(FILE*);

char* getFilename(int, char**);
int childGetCount(int, char*);
int getCountForDir(char*, char*, int);
int isInDir(char*, char*);
char* addToPath(char*, char*);
int getCountForFile(char*, int);
int getSubdirs(char*, char***);
void expandSubdirArray(char***, int);

#endif
