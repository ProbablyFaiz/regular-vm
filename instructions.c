#include "instructions.h"
#include <string.h>

void (*instructions[])(instruction_t *) = {nop, add, sub, and, orr, xor, not, lsh, ash, tcu, tcs, set, mov, ldw, stw, ldb, stb};
operandsType instructionTypes[] = {opOnly, oprArBrC, oprArBrC, oprArBrC, oprArBrC, oprArBrC, oprArB, oprArBrC, oprArBrC, oprArBrC, oprArBrC, oprAimm, oprArB, oprArB, oprArB, oprArB, oprArB};

uint8_t getOpCode(const char * instructionToken) {
    if (strcmp(instructionToken,"nop") == 0)
		return 0;
	else if (strcmp(instructionToken,"add") == 0)
		return 1;
	else if (strcmp(instructionToken,"sub") == 0)
		return 2;
	else if (strcmp(instructionToken,"and") == 0)
		return 3;
	else if (strcmp(instructionToken,"orr") == 0)
		return 4;
	else if (strcmp(instructionToken,"xor") == 0)
		return 5;
	else if (strcmp(instructionToken,"not") == 0)
		return 6;
	else if (strcmp(instructionToken,"lsh") == 0)
		return 7;
	else if (strcmp(instructionToken,"ash") == 0)
		return 8;
	else if (strcmp(instructionToken,"tcu") == 0)
		return 9;
	else if (strcmp(instructionToken,"tcs") == 0)
		return 10;
	else if (strcmp(instructionToken,"set") == 0)
		return 11;
	else if (strcmp(instructionToken,"mov") == 0)
		return 12;
	else if (strcmp(instructionToken,"ldw") == 0)
		return 13;
	else if (strcmp(instructionToken,"stw") == 0)
		return 14;
	else if (strcmp(instructionToken,"ldb") == 0)
		return 15;
	else if (strcmp(instructionToken,"stb") == 0)
		return 16;
    return -1;
}

void executeInstruction(uint32_t * rawInstruction) {
    instruction_t * instruction = (instruction_t *)(rawInstruction);
    (*instructions[instruction->opOnly.opCode])(instruction);
}

void nop(instruction_t * operands) {
    // Well, that was easy.
}

void add(instruction_t * operands) {
    registers[operands->oprArBrC.rC] = registers[operands->oprArBrC.rA] + registers[operands->oprArBrC.rB];
}

void sub(instruction_t * operands) {
    registers[operands->oprArBrC.rC] = registers[operands->oprArBrC.rA] - registers[operands->oprArBrC.rB];
}

void and(instruction_t * operands) {
    registers[operands->oprArBrC.rC] = registers[operands->oprArBrC.rA] & registers[operands->oprArBrC.rB];
}

void orr(instruction_t * operands) {
    registers[operands->oprArBrC.rC] = registers[operands->oprArBrC.rA] | registers[operands->oprArBrC.rB];
}

void xor(instruction_t * operands) {
    registers[operands->oprArBrC.rC] = registers[operands->oprArBrC.rA] ^ registers[operands->oprArBrC.rB];
}

void not(instruction_t * operands) {
    registers[operands->oprArB.rA] = ~ registers[operands->oprArB.rB];
}

void lsh(instruction_t * operands) {
    int32_t shift = (int32_t) (registers[operands->oprArBrC.rC]);
    if (shift >= 0) {
	    registers[operands->oprArBrC.rA] = registers[operands->oprArBrC.rB] << shift;
    } 
    else {
	    registers[operands->oprArBrC.rA] = registers[operands->oprArBrC.rB] >> -shift;
    }
}

void ash(instruction_t * operands) {
    int32_t shift = (int32_t) (registers[operands->oprArBrC.rC]);
    if (shift >= 0) {
	    registers[operands->oprArBrC.rA] = (int32_t) (registers[operands->oprArBrC.rB]) << shift;
    } 
    else {
	    registers[operands->oprArBrC.rA] = (int32_t) (registers[operands->oprArBrC.rB]) >> -shift;
    }
}

void tcu(instruction_t * operands) {
    uint32_t rB = registers[operands->oprArBrC.rB];
    uint32_t rC = registers[operands->oprArBrC.rC];
    if (rB > rC)
        registers[operands->oprArBrC.rA] = 1;
    if (rB < rC)
        registers[operands->oprArBrC.rA] = -1;
    else
        registers[operands->oprArBrC.rA] = 0;
}

void tcs(instruction_t * operands) {
    int32_t rB = (int32_t) registers[operands->oprArBrC.rB];
    int32_t rC = (int32_t) registers[operands->oprArBrC.rC];
    if (rB > rC)
        registers[operands->oprArBrC.rA] = 1;
    if (rB < rC)
        registers[operands->oprArBrC.rA] = -1;
    else
        registers[operands->oprArBrC.rA] = 0;
 }

void set(instruction_t * operands) {
    registers[operands->oprAimm.rA] = operands->oprAimm.imm; 
}

void mov(instruction_t * operands) {
    registers[operands->oprArB.rA] = registers[operands->oprArB.rB];
}

void ldw(instruction_t * operands) {
    registers[operands->oprArB.rA] =
        memory[registers[operands->oprArB.rB] + 0] << 0 |
        memory[registers[operands->oprArB.rB] + 1] << 8 |
        memory[registers[operands->oprArB.rB] + 2] << 16 |
        memory[registers[operands->oprArB.rB] + 3] << 24;
}

void stw(instruction_t * operands) {
    memory[registers[operands->oprArB.rA] + 0] = registers[operands->oprArB.rB] >> 0 & 0xff;
         memory[registers[operands->oprArB.rA] + 1] = registers[operands->oprArB.rB] >> 8 & 0xff;
         memory[registers[operands->oprArB.rA] + 2] = registers[operands->oprArB.rB] >> 16 & 0xff;
         memory[registers[operands->oprArB.rA] + 3] = registers[operands->oprArB.rB] >> 24 & 0xff;
}

void ldb(instruction_t * operands) {
    registers[operands->oprArB.rA] &= memory[registers[operands->oprArB.rB]] & 0xff;
}

void stb(instruction_t * operands) {
    memory[registers[operands->oprArB.rA]] = registers[operands->oprArB.rB] & 0xff;
}