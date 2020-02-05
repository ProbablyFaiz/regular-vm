#include "instructions.h"
#include "interpreter.h"

void nop(opPayload operands) {
    // Well, that was easy.
}

void add(opPayload operands) {
    registers[operands.oprArBrC.rC] = registers[operands.oprArBrC.rA] + registers[operands.oprArBrC.rB];
}

void sub(opPayload operands) {
    registers[operands.oprArBrC.rC] = registers[operands.oprArBrC.rA] - registers[operands.oprArBrC.rB];
}

void and(opPayload operands) {
    registers[operands.oprArBrC.rC] = registers[operands.oprArBrC.rA] & registers[operands.oprArBrC.rB];
}

void orr(opPayload operands) {
    registers[operands.oprArBrC.rC] = registers[operands.oprArBrC.rA] | registers[operands.oprArBrC.rB];
}

void xor(opPayload operands) {
    registers[operands.oprArBrC.rC] = registers[operands.oprArBrC.rA] ^ registers[operands.oprArBrC.rB];
}

void not(opPayload operands) {
    registers[operands.oprArB.rA] = ~ registers[operands.oprArB.rB];
}

void lsh(opPayload operands) {
    int32_t shift = (int32_t) (registers[operands.oprArBrC.rC]);
    if (shift >= 0) {
	    registers[operands.oprArBrC.rA] = registers[operands.oprArBrC.rB] << shift;
    } 
    else {
	    registers[operands.oprArBrC.rA] = registers[operands.oprArBrC.rB] >> -shift;
    }
}

void ash(opPayload operands) {
    int32_t shift = (int32_t) (registers[operands.oprArBrC.rC]);
    if (shift >= 0) {
	    registers[operands.oprArBrC.rA] = (int32_t) (registers[operands.oprArBrC.rB]) << shift;
    } 
    else {
	    registers[operands.oprArBrC.rA] = (int32_t) (registers[operands.oprArBrC.rB]) >> -shift;
    }
}

void tcu(opPayload operands) {
    uint32_t rB = registers[operands.oprArBrC.rB];
    uint32_t rC = registers[operands.oprArBrC.rC];
    if (rB > rC)
        registers[operands.oprArBrC.rA] = 1;
    if (rB < rC)
        registers[operands.oprArBrC.rA] = -1;
    else
        registers[operands.oprArBrC.rA] = 0;
}

void tcs(opPayload operands) {
    int32_t rB = (int32_t) registers[operands.oprArBrC.rB];
    int32_t rC = (int32_t) registers[operands.oprArBrC.rC];
    if (rB > rC)
        registers[operands.oprArBrC.rA] = 1;
    if (rB < rC)
        registers[operands.oprArBrC.rA] = -1;
    else
        registers[operands.oprArBrC.rA] = 0;
 }

void set(opPayload operands) {
    registers[operands.oprAimm.rA] = operands.oprAimm.imm; 
}

void mov(opPayload operands) {
    registers[operands.oprArB.rA] = registers[operands.oprArB.rB];
}

void ldw(opPayload operands) {
    registers[operands.oprArB.rA] =
        memory[registers[operands.oprArB.rB] + 0] << 0 |
        memory[registers[operands.oprArB.rB] + 1] << 8 |
        memory[registers[operands.oprArB.rB] + 2] << 16 |
        memory[registers[operands.oprArB.rB] + 3] << 24;
}

void stw(opPayload operands) {
    memory[registers[operands.oprArB.rA] + 0] = registers[operands.oprArB.rB] >> 0 & 0xff;
         memory[registers[operands.oprArB.rA] + 1] = registers[operands.oprArB.rB] >> 8 & 0xff;
         memory[registers[operands.oprArB.rA] + 2] = registers[operands.oprArB.rB] >> 16 & 0xff;
         memory[registers[operands.oprArB.rA] + 3] = registers[operands.oprArB.rB] >> 24 & 0xff;
}

void ldb(opPayload operands) {
    registers[operands.oprArB.rA] &= memory[registers[operands.oprArB.rB]] & 0xff;
}

void stb(opPayload operands) {
    memory[registers[operands.oprArB.rA]] = registers[operands.oprArB.rB] & 0xff;
}