#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "vm.h"

typedef struct { } opOnly_t;  // op
typedef struct { uint8_t rA; } oprA_t;  // op rA
typedef struct { uint8_t rA; int16_t imm; } oprAimm_t;  // op rA imm
typedef struct { uint8_t rA; uint8_t rB; } oprArB_t;  // op rA rB 
typedef struct { uint8_t rA; uint8_t rB; int8_t imm; } oprArBimm_t;  // op rA rB imm
typedef struct { uint8_t rA; uint8_t rB; uint8_t rC; } oprArBrC_t; //op rA rB rC

typedef enum _payloadType { opOnly, oprA, oprAimm, oprArB, oprArBimm, oprArBrC } payloadType;

typedef union _opPayload {
    opOnly_t opOnly;
    oprA_t oprA;
    oprAimm_t oprAimm;
    oprArB_t oprArB;
    oprArBimm_t oprArBimm;
    oprArBrC_t oprArBrC;
} opPayload;

typedef struct _instruction {
    uint8_t opCode;
    opPayload payload;
} instruction_t;

instruction_t parseInstruction(uint32_t instruction);

void nop(opPayload operands); //0x00 opOnly
void add(opPayload operands); //0x01 oprArBrC
void sub(opPayload operands); //0x02 oprArBrC
void and(opPayload operands); //0x03 oprArBrC
void orr(opPayload operands); //0x04 oprArBrC
void xor(opPayload operands); //0x05 oprArBrC
void not(opPayload operands); //0x06 oprArB
void lsh(opPayload operands); //0x07 oprArBrC
void ash(opPayload operands); //0x08 oprArBrC
void tcu(opPayload operands); //0x09 oprArBrC
void tcs(opPayload operands); //0x0A oprArBrC
void set(opPayload operands); //0x0B oprAimm
void mov(opPayload operands); //0x0C oprArB
void ldw(opPayload operands); //0x0D oprArB
void stw(opPayload operands); //0x0E oprArB
void ldb(opPayload operands); //0x0F oprArB
void stb(opPayload operands); //0x10 oprArB

extern void (*instructions[])(opPayload);
extern payloadType instructionTypes[];

void executeInstruction(uint32_t rawInstruction);

#endif