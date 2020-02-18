#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdlib.h>
#include <stdio.h>
#include "../emulator/vm.h"

int main();
void tests(void);
int run(FILE * binaryFile);

#endif