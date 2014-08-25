#ifndef _CPU_H
#define _CPU_H

struct cpu;
typedef struct cpu cpu_t;

cpu_t *init_cpu(char *ex_file);
int load_cpu(char *ex_file, cpu_t *cpu);
void cpu_del(cpu_t *cpu);

int run(cpu_t *cpu);

#endif
