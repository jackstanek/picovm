#include <stdio.h>

#include "picovm.h"
#include "cpu.h"
#include "mem.h"

void usage()
{
	printf("picovm -- a miniscule virtual machine\n");
	printf("USAGE: picovm [FILE]\n");
}

int main(int argc, char *argv[])
{
	if (argc == 2) {
		cpu_t *cpu = init_cpu(argv[1]);
		if (cpu) {
			printf("Loaded cpu successfully\n");
		}
		run(cpu);

		cpu_del(cpu);
	} else if (argc < 2) {
		ERROR("Not enough arguments");
		usage();
	} else{
		ERROR("Too many arguments");
		usage();
	}

	return 0;
}
