#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "picovm.h"
#include "opcode.h"
#include "cpu.h"
#include "mem.h"

struct cpu {
	byte *inst;		/* instruction queue */
	byte *ip;		/* instruction pointer */
	byte acc;		/* accumulator */
	byte reg[NUMREGS];	/* registers */
	int isize;		/* instruction size */
	mem_t *mem;		/* memory manager */
};

cpu_t *init_cpu(char *ex_file)
{
	cpu_t *cpup = malloc(sizeof(cpu_t));
	if (!cpup) {
		ERROR("Could not allocate a new processor; not enough memory?");
		return NULL;
	}

	if (load_cpu(ex_file, cpup) > 0) {
		return cpup;
	} else {
		cpu_del(cpup);
		return NULL;
	}
}

int load_cpu(char *ex_file, cpu_t *cpu)
{
	/* get file size */
	FILE *efp = fopen(ex_file, "rb");
	if (efp) {
		fseek(efp, 0, SEEK_END);
		cpu->isize = ftell(efp);
		rewind(efp);
	} else {
		ERROR("Could not open executable file");
		return -1;
	}

	/* initialize registers, queue, and mem */
	cpu->acc = 0x00;
	for (int i = 0; i < NUMREGS; i++) {
		cpu->reg[i] = 0x00;
	}

	cpu->inst = malloc(cpu->isize);
	if (!cpu->inst) {
		ERROR("Could not allocate instruction queue");
		return -1;
	}

	size_t br = fread(cpu->inst, sizeof(byte), cpu->isize, efp);
	if (br != cpu->isize) {
		ERROR("Failed to load instructions from file");
		return -1;
	}
	cpu->ip = cpu->inst;

	cpu->mem = init_mem();
	if (!cpu->mem) {
		ERROR("Failed to initialize virtual memory");
		return -1;
	}
	return 1;
}

void cpu_del(cpu_t *cpu)
{
	free(cpu->inst);
	mem_del(cpu->mem);
	free(cpu);
}

int op(cpu_t *cpu)
{
	if (!cpu) {
		ERROR("The cpu is null! WTF is happening!?");
		return 0;
	} else {
		if (cpu->ip - cpu->inst < cpu->isize) {
			byte buf[4];
			memcpy(buf, cpu->ip, 4);
			byte op = buf[0];
			byte *reg = cpu->reg;

			switch (op) {
			case NOP:
				break;
			case ADD:
				reg[buf[3]] =  reg[buf[1]] + reg[buf[2]];
				break;
			case SUB:
				reg[buf[3]] =  reg[buf[1]] - reg[buf[2]];
				break;
			case MUL:
				reg[buf[3]] =  reg[buf[1]] * reg[buf[2]];
				break;
			case DIV:
				reg[buf[3]] =  reg[buf[1]] / reg[buf[2]];
				break;
			case MOV:
				reg[buf[2]] = reg[buf[1]];
				break;
			case LOD:
				reg[buf[2]] = get_addr(cpu->mem, buf[2]);
				break;
			case STO:
				set_addr(cpu->mem, reg[buf[1]], reg[buf[2]]);
				break;
			case SET:
			        reg[buf[1]] = buf[2];
				break;
			case PRI:
				printf("Contents of register %x: %x\n", buf[1], reg[buf[1]]);
				break;
			case ERR:
				fprintf(stderr, "DBG: Contents of register %x: %x\n", buf[1], reg[buf[1]]);
				break;
			}

			cpu->ip += 4;
			return 1;
		} else {
			return 0;
		}
	}
}

int run(cpu_t *cpu)
{
	int rv = 0;
	do {
		rv = op(cpu);
	} while (rv != 0);
	return 0;
}
