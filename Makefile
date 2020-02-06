COMPILER= cc
CXXFLAGS= -g -o

all: interpreter assembler disassembler

interpreter: interpreter.c instructions.c
	${COMPILER} ${CXXFLAGS} interpreter interpreter.c instructions.c

assembler: assembler.c instructions.c
	${COMPILER} ${CXXFLAGS} assembler assembler.c instructions.c

disassembler: disassembler.c instructions.c
	${COMPILER} ${CXXFLAGS} disassembler disassembler.c instructions.c

clean:
	rm -rf interpreter assembler disassembler