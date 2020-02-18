#include "assembler.h"
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    char* asmFileName = argv[1];
	FILE * asmFile = fopen(asmFileName, "r");
	// printf("Error reading file: %s\n", strerror(errno));

    char* binaryFileName = argv[2];
	FILE * binaryFile = fopen(binaryFileName,"wb");

    assembleFile(asmFile, binaryFile);

    fclose(asmFile);
	fclose(binaryFile);
    return EXIT_SUCCESS;
}

void assembleFile(FILE * asmFile, FILE * binFile) {
    char asmLine[64];

    while (fgets(asmLine, sizeof(asmLine), asmFile)) {
        asmLine[strcspn(asmLine, "\n")] = '\0'; // Remove \n character from end of line
        if (strcmp(asmLine, "") == 0 || asmLine[0] == '%') // Line is empty or commented out.
            continue;
		writeBinForASMLine(asmLine, binFile);
    }
}

int parseOperandToken(char * operandToken) {
    if(operandToken[0] == 'r')
		operandToken++;
    return atoi(operandToken);
}

void writeBinForASMLine(char * asmLine, FILE * binFile) {
	char * token = strtok(asmLine, " ");
	if (strcmp(asmLine, "inc") == 0) {
		// assembleFile(asmLine, binFile);
		return;
	}

	uint8_t opCode = getOpCode(token);
	operandsType operandsType = instructionTypes[opCode];
	fputc(opCode, binFile);
	writeBinOperands(operandsType, asmLine, binFile);
}

void writeBinOperands(operandsType operandsType, const char * asmLine, FILE * binFile) {
	char padding[3] = {}; // Maximum of 3 bytes of padding necessary.

	if (operandsType == opOnly) {
		fwrite(&padding, 1, 3, binFile); // Write 3 bytes of zeroes
		return;
	}
	// All remaining operand types have rA, so we can assign it now.
	char * token = strtok(NULL, " ");
	fputc(parseOperandToken(token), binFile);

	if (operandsType == oprA) {
		fwrite(&padding, 1, 2, binFile);
		return;
	}

	if (operandsType == oprAimm) {
		token = strtok(NULL, " ");
		int imm = parseOperandToken(token);
		fwrite(&imm, 2, 1, binFile); // imm is 16 bits, or 2 bytes long
		return;
	}
	// All remaining operand types have rB, so we can assign it now.
	token = strtok(NULL, " ");
	fputc(parseOperandToken(token), binFile);
	
	if (operandsType == oprArB) {
		fwrite(&padding, 1, 1, binFile);
		return;
	}

	// Only remaining operand types have either an 8 bit imm or an 8 bit rC, so we can assign it now.
	token = strtok(NULL, " ");
	fputc(parseOperandToken(token), binFile);
}