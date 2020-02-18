#include "vm.h"
#include <stdio.h>

void dumpRegisters() {
    
    for (size_t i = 0; i < VM_REGISTERS_SIZE; i++) {
        printf("Register %lu: %u", i, registers[i]);
        if ((i + 1) % 4)
            printf("\t");
        else
            printf("\n");
    }
    printf("\n");
}