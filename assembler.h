#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include "vm.h"

int main(int argc, char *argv[]);
void assembleFile(FILE * asmFile, FILE * binFile);

void includeFile(const char * fileToken, FILE * binFile);

uint8_t getOpCode(const char * instructionToken);
int parseOperandToken(char * operandToken);
void writeBinForASMLine(char * asmLine, FILE * binFile);
void writeBinOperands(operandsType operandsType, const char * asmLine, FILE * binFile);

#endif