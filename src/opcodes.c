#include "opcodes.h"

#include <stdio.h>

void no_op(VM *vm) {
    printf("NO_OP\n");
    vm->program_counter++;
}

void halt(VM *vm) {
    printf("######################\n");
    printf("HALTED\n");
    printf("######################\n");
    vm->halted = true;
}

void state_dump(VM *vm) {

    printf("STATE_DUMP: \n");

    printf("PROGRAM MEMORY:\n");

    for (u32 i = 0; i < vm->program_size; ++i) {
        printf(" %d ", vm->program[i]);
    }

    printf("\n");

    printf("##############################\n");

    printf("REGISTERS:\n");

    for (u32 i = 0; i < REG_COUNT; ++i) {
        printf("        register[%d] = %d\n", i, vm->registers[i]);
    }

    printf("##############################\n");

    printf("MACHINE INFO:\n");

    printf("        program_couter = %d\n", vm->program_counter);
    printf("        program_size   = %d\n", vm->program_size);

    vm->program_counter++;
}

void mov(VM *vm) {

    printf("MOV: \n");
    vm->program_counter++;
    u32 tmp = vm->program[vm->program_counter];
    printf("    tmp = %d\n", vm->program[vm->program_counter]);
    vm->program_counter++;
    vm->registers[vm->program[vm->program_counter]] = tmp;
    printf("    reg%d = %d\n", vm->program[vm->program_counter], tmp);
    vm->program_counter++;
}

void ld(VM *vm) {

    printf("LD: \n");
    vm->program_counter++;
    u32 reg_num = vm->program[vm->program_counter];
    printf("    reg_num = %d\n", reg_num);
    u32 value = vm->registers[reg_num];
    printf("    value = %d\n", value);
    vm->program_counter++;
    u32 reg_target = vm->program[vm->program_counter];
    printf("    reg_target = %d\n", reg_target);
    vm->registers[reg_target] = value;
    vm->program_counter++;
}
