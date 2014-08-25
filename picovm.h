#ifndef _PICOVM_H
#define _PICOVM_H

#include <stdio.h>
#include <math.h>

#define ERROR(msg) do { fprintf(stderr, "ERROR: %s\n", msg); } while (0)

#define NUMREGS 7

typedef unsigned char byte;

unsigned long fsize(char *file);

#define ADDRSPC (sizeof(byte) * pow(2, sizeof(byte) * 8))

#endif
