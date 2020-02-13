#include <stdio.h>
#include <time.h>
#include "interpreter.h"
#include "instructions.h"

int main(int argc, char *argv[]) {
    // tests();
    // return EXIT_SUCCESS;

    char * fileName = argv[1];
    FILE * file = fopen(fileName, "rb");
    if (file == NULL) {
        return EXIT_FAILURE;
    }
    return run(file);
}

void tests(void) {
    // op code: 8, rA: 24, rB: 12, rC: 9
    uint32_t littleEndianInstruction = 0b00011001000011000001100000001000;
    uint32_t littleEndian = 0b00000000000010000000110000001110;
    instruction_t instruction = *(instruction_t *)(&littleEndianInstruction);
    printf("%d\n%d\n%d\n%d\n", instruction.oprArBrC.opCode, instruction.oprArBrC.rA, instruction.oprArBrC.rB, instruction.oprArBrC.rC);
    instruction.opOnly.opCode = 17;
    printf("%d\n", instruction.oprArBrC.opCode);
}

int run(FILE * binaryFile) {
    int programBegin = 0;
    int programEnd = programBegin;
    while (fread(memory + programEnd, sizeof(memory[0]), 1, binaryFile)) {
        programEnd++;
    }
    memory[programEnd] = UINT32_MAX;

    for (int i = programBegin; i < programEnd; i++) {
        executeInstruction(memory + i);
    }
    return EXIT_SUCCESS;
}