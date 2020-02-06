#include <stdio.h>
#include <time.h>
#include "interpreter.h"
#include "instructions.h"

int main(int argc, char *argv[]) {
    // op code: 8, rA: 24, rB: 12, rC: 9 
    uint32_t testInstruction = 0b00001000000110000000110000001001;
    char * fileName = argv[1];
    FILE * file = fopen(fileName, "rb");
    if (file == NULL) {
        return EXIT_FAILURE;
    }
    
    int programBegin = 0;
    int programEnd = programBegin;
    while (fread(memory + programEnd, sizeof(memory[0]), 1, file)) {
        printf("%d\n", memory[programEnd]);
        programEnd++;
    }
    memory[programEnd] = UINT32_MAX;

    for (int i = programBegin; i < programEnd; i++) {
        printf("%d\n", memory[i]);
        executeInstruction(memory[i]);
    }
}