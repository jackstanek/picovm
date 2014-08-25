#ifndef _MEM_H
#define _MEM_H

#include "picovm.h"

struct mem;
typedef struct mem mem_t;

mem_t *init_mem();
int set_addr(mem_t *mem, byte addr, byte con);
byte get_addr(mem_t *mem, byte addr);
void mem_del(mem_t *mem);

#endif
