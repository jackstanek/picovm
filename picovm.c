#include <stdio.h>

#include "picovm.h"

unsigned long fsize(char *file)
{
	FILE *f = fopen(file, "r");
	unsigned long len = (unsigned long) ftell(f);
	fclose(f);
	return len;
}
