#ifndef __HEADER_H
#define __HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <libgen.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

void prompt(char *CWD, char *HOME, char *a);
void cd(char *CWD, char *HOME, char *input);
void echo(char *CWD, char *HOME, char *input);
void ls(char *CWD, char *HOME, char *input, char **args, int n);
void pinfo(char *CWD, char *HOME, char *input);
void run(char *CWD, char *HOME, char *instr);
void discover(char *CWD, char *HOME, char *input, char **args, int n);

#endif