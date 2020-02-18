#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stdlib.h>

#define VM_MEMORY_SIZE 16384
#define VM_REGISTERS_SIZE 32
#define VM_PC 0
#define VM_TMP1 29
#define VM_TMP2 30
#define VM_SPTR 31

uint32_t memory[VM_MEMORY_SIZE];
uint32_t registers[VM_REGISTERS_SIZE];

void dumpRegisters();

#endif