#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stdlib.h>

uint32_t memory[1024];
uint32_t registers[32];

void dumpRegisters();

#endif