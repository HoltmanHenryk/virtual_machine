#include "opcodes.h"

#include <stdio.h>

void no_op(VM *vm) {
    printf("NO_OP\n");
    vm->program_counter++;
}

void halt(VM *vm) {
    printf("HALT:\n");
    printf("==== MACHINE HALTED ====\n");
    vm->halted = true;
}

void state_dump(VM *vm) {

    printf("STATE_DUMP: \n");
    printf("##############################\n");
    printf("REGISTERS:\n");
    for (u32 i = 0; i < REG_COUNT; ++i) {
        printf("        register[%.2d] = %.2d\n", i, vm->registers[i]);
    }
    printf("##############################\n");
    printf("MACHINE INFO:\n");
    printf("        program_couter = %d\n", vm->program_counter);
    printf("        program_size   = %d\n", vm->program_size);
    printf("##############################\n");
    vm->program_counter++;
}

void mov(VM *vm) {

    printf("MOV: { ");
    vm->program_counter++;
    u32 tmp = vm->program[vm->program_counter];
    printf("%d -> ", vm->program[vm->program_counter]);
    vm->program_counter++;
    vm->registers[vm->program[vm->program_counter]] = tmp;
    printf("register[%d] }", vm->program[vm->program_counter]);
    vm->program_counter++;
    printf("\n");
}

void ld(VM *vm) {

    printf("LD: {");
    vm->program_counter++;
    u32 reg_num = vm->program[vm->program_counter];
    printf(" register[%d] ", reg_num);
    u32 value = vm->registers[reg_num];
    printf("= %d -> ", value);
    vm->program_counter++;
    u32 reg_target = vm->program[vm->program_counter];
    printf("register[%d] }", reg_target);
    vm->registers[reg_target] = value;
    vm->program_counter++;
    printf("\n");
}

void inc(VM *vm) {
    printf("INC: {");
    vm->program_counter++;
    u32 reg_ind = vm->program[vm->program_counter];
    printf(" register[%d] = %d", reg_ind, vm->registers[reg_ind]);
    vm->registers[reg_ind]++;
    printf(" -> %d }", vm->registers[reg_ind]);
    vm->program_counter++;
    printf("\n");
}
