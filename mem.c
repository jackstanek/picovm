#include <stdlib.h>

#include "picovm.h"
#include "mem.h"

struct mem {
	byte *addrs;
	byte size;
};

mem_t *init_mem(size_t size)
{
	mem_t *mem = malloc(sizeof(mem_t) * size);
	if (mem) {
		mem->size = size;
		mem->addrs = malloc(sizeof(byte) * size);
		for (size_t i = 0; i < size; i++) {
			mem->addrs[i] = 0x0;
		}
		return mem;
	} else {
		ERROR("Could not initialize memory manager");
		return NULL;
	}
}

int set_addr(mem_t *mem, byte addr, byte con)
{
	if (!mem) {
		ERROR("Memory manager is null");
		return 0;
	}

	mem->addrs[addr] = con;
	return 1;
}

byte get_addr(mem_t *mem, byte addr)
{
	if (mem && mem->addrs) {
		return mem->addrs[addr];
	} else {
		return 0x00;
	}
}

void mem_del(mem_t *mem)
{
	free(mem->addrs);
	free(mem);
}
