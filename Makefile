COMPILER= cc
CXXFLAGS= -g -o

all: emulator/emulator assembler/assembler

emulator/emulator: emulator/emulator.c instructions/instructions.c emulator/vm.c
	${COMPILER} ${CXXFLAGS} $@ $^

assembler/assembler: assembler/assembler.c instructions/instructions.c emulator/vm.c
	${COMPILER} ${CXXFLAGS} $@ $^

disassembler/disassembler: disassembler/disassembler.c instructions/instructions.c emulator/vm.c
	${COMPILER} ${CXXFLAGS} $@ $^

clean:
	rm emulator/emulator assembler/assembler disassembler/disassembler