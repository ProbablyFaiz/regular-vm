#include <stdio.h>
#include <time.h>
#include "emulator.h"
#include "../instructions/instructions.h"

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

int run(FILE * binaryFile) {
    printf("------- START -------\n");
    int instructionNumMemRegs = 1;
    int programBegin = 0;
    int programEnd = programBegin;
    while (fread(memory + programEnd * instructionNumMemRegs, sizeof(*memory) * instructionNumMemRegs, 1, binaryFile)) {
        programEnd++;
    }
    memory[programEnd] = UINT8_MAX;
    registers[VM_SPTR] = programEnd * instructionNumMemRegs + 1;

    // for (size_t i = 0; i < programEnd; i++) {
    //     printf("%d %d %d %d\n", memory[i * instructionNumMemRegs], memory[i * instructionNumMemRegs + 1], memory[i * instructionNumMemRegs + 2], memory[i * instructionNumMemRegs + 3]);
    // }
    for (registers[VM_PC] = programBegin; registers[VM_PC] < programEnd; registers[VM_PC]++) {
        // dumpRegisters();
        executeInstruction(memory + registers[VM_PC] * instructionNumMemRegs);
    }
    dumpRegisters();
    return EXIT_SUCCESS;
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