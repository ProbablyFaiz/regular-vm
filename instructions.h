#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "vm.h"

#define VM_NUM_INSTRUCTIONS 17

typedef struct { uint8_t opCode; } opOnly_t;  // op
typedef struct { uint8_t opCode; uint8_t rA; } oprA_t;  // op rA
typedef struct { uint8_t opCode; uint8_t rA; int16_t imm; } oprAimm_t;  // op rA imm
typedef struct { uint8_t opCode; uint8_t rA; uint8_t rB; } oprArB_t;  // op rA rB 
typedef struct { uint8_t opCode; uint8_t rA; uint8_t rB; int8_t imm; } oprArBimm_t;  // op rA rB imm
typedef struct { uint8_t opCode; uint8_t rA; uint8_t rB; uint8_t rC; } oprArBrC_t; //op rA rB rC

typedef enum _payloadType { opOnly, oprA, oprAimm, oprArB, oprArBimm, oprArBrC } operandsType;

typedef union _instruction_t {
    opOnly_t opOnly;
    oprA_t oprA;
    oprAimm_t oprAimm;
    oprArB_t oprArB;
    oprArBimm_t oprArBimm;
    oprArBrC_t oprArBrC;
} instruction_t;

void nop(instruction_t * operands); //0x00 opOnly
void add(instruction_t * operands); //0x01 oprArBrC
void sub(instruction_t * operands); //0x02 oprArBrC
void and(instruction_t * operands); //0x03 oprArBrC
void orr(instruction_t * operands); //0x04 oprArBrC
void xor(instruction_t * operands); //0x05 oprArBrC
void not(instruction_t * operands); //0x06 oprArB
void lsh(instruction_t * operands); //0x07 oprArBrC
void ash(instruction_t * operands); //0x08 oprArBrC
void tcu(instruction_t * operands); //0x09 oprArBrC
void tcs(instruction_t * operands); //0x0A oprArBrC
void set(instruction_t * operands); //0x0B oprAimm
void mov(instruction_t * operands); //0x0C oprArB
void ldw(instruction_t * operands); //0x0D oprArB
void stw(instruction_t * operands); //0x0E oprArB
void ldb(instruction_t * operands); //0x0F oprArB
void stb(instruction_t * operands); //0x10 oprArB

extern void (*instructions[])(instruction_t *);
extern operandsType instructionTypes[];

uint8_t getOpCode(const char * instructionToken);
void executeInstruction(uint32_t * rawInstruction);

#endif