#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

void nop(opPayload operands);
void add(opPayload operands);
void sub(opPayload operands);
void and(opPayload operands);
void orr(opPayload operands);
void xor(opPayload operands);
void not(opPayload operands);
void lsh(opPayload operands);
void ash(opPayload operands);
void tcu(opPayload operands);
void tcs(opPayload operands);
void set(opPayload operands);
void mov(opPayload operands);
void ldw(opPayload operands);
void stw(opPayload operands);
void ldb(opPayload operands);
void stb(opPayload operands);

typedef struct { } opOnly;  // op
typedef struct { uint8_t rA; } oprA;  // op rA
typedef struct { uint8_t rA; int16_t imm; } oprAimm;  // op rA imm
typedef struct { uint8_t rA; uint8_t rB; } oprArB;  // op rA rB 
typedef struct { uint8_t rA; uint8_t rB; int8_t imm; } oprArBimm;  // op rA rB imm
typedef struct { uint8_t rA; uint8_t rB; uint8_t rC; } oprArBrC; //op rA rB rC

typedef union opPayload {
    opOnly opOnly;
    oprA opRA;
    oprAimm oprAimm;
    oprArB oprArB;
    oprArBimm oprArBimm;
    oprArBrC oprArBrC;
} opPayload;

void (*instructions[])(opPayload) = {nop, add, sub, and, orr, xor, not, lsh, ash, tcu, tcs, set, mov, ldw, stw, ldb, stb};

#endif