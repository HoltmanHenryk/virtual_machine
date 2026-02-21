#include "opcodes.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

void vm_verbose(VM *vm, const char *format, ...) {

    if (!vm || !vm->verbose) {
        return;
    }

    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

void no_op(VM *vm) {
    vm_verbose(vm, "NO_OP\n");
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
    for (i32 i = 0; i < REG_COUNT; ++i) {
        printf("        register[%2d] = %2d\n", i, vm->registers[i]);
    }
    printf("##############################\n");
    printf("MACHINE INFO:\n");
    printf("        program_couter  = %d\n", vm->program_counter);
    printf("        program_size    = %d\n", vm->program_size);
    printf("        condition_flag  = %d\n", vm->cond_flag);
    printf("##############################\n");
    vm->program_counter++;
}

void program_dump(VM *vm) {
    printf("PROGRAM_DUMP:\n");

    const char *rawdump = "dumped-program.obj";

    FILE *file = fopen(rawdump, "wb");
    fwrite(vm->program, sizeof(i32), vm->program_size, file);
    fclose(file);

    printf("    Dumped loaded program bytecode to %s\n", rawdump);

    vm->program_counter++;
}

void mov(VM *vm) {

    vm_verbose(vm, "MOV: { ");
    vm->program_counter++;
    i32 tmp = vm->program[vm->program_counter];
    vm_verbose(vm, "%d -> ", vm->program[vm->program_counter]);
    vm->program_counter++;
    vm->registers[vm->program[vm->program_counter]] = tmp;
    vm_verbose(vm, "register[%d] }", vm->program[vm->program_counter]);
    vm->program_counter++;
    vm_verbose(vm, "\n");
}

void ld(VM *vm) {

    vm_verbose(vm, "LD: {");
    vm->program_counter++;
    i32 reg_num = vm->program[vm->program_counter];
    vm_verbose(vm, " register[%d] ", reg_num);
    i32 value = vm->registers[reg_num];
    vm_verbose(vm, "= %d -> ", value);
    vm->program_counter++;
    i32 reg_target = vm->program[vm->program_counter];
    vm_verbose(vm, "register[%d] }", reg_target);
    vm->registers[reg_target] = value;
    vm->program_counter++;
    vm_verbose(vm, "\n");
}

void inc(VM *vm) {
    vm_verbose(vm, "INC: {");
    vm->program_counter++;
    i32 reg_ind = vm->program[vm->program_counter];
    vm_verbose(vm, " register[%d] = %d", reg_ind, vm->registers[reg_ind]);
    vm->registers[reg_ind]++;
    vm_verbose(vm, " -> %d }", vm->registers[reg_ind]);
    vm->program_counter++;
    vm_verbose(vm, "\n");
}

void dec(VM *vm) {
    vm_verbose(vm, "DEC: {");
    vm->program_counter++;
    i32 reg_ind = vm->program[vm->program_counter];
    vm_verbose(vm, " register[%d] = %d", reg_ind, vm->registers[reg_ind]);
    vm->registers[reg_ind]--;
    vm_verbose(vm, " -> %d }", vm->registers[reg_ind]);
    vm->program_counter++;
    vm_verbose(vm, "\n");
}

void sto_pc(VM *vm) {
    vm_verbose(vm, "STO_PC: {");
    i32 pc = vm->program_counter;
    vm->program_counter++;
    i32 reg_ind = vm->program[vm->program_counter];
    vm->registers[reg_ind] = pc + 2; /* pos of the next operation after sto_pc argument */
    vm_verbose(vm, " register[%d] = %d }\n", reg_ind, pc + 2);
    vm->program_counter++;
}

void cmp(VM *vm) {
    vm_verbose(vm, "CMP: {");
    vm->program_counter++;

    i32 arg_a_reg_ind = vm->program[vm->program_counter];
    i32 arg_a_value = vm->registers[arg_a_reg_ind];

    vm->program_counter++;

    i32 arg_b_reg_ind = vm->program[vm->program_counter];
    i32 arg_b_value = vm->registers[arg_b_reg_ind];

    i32 res = arg_a_value - arg_b_value;

    if (res < 0) {
        vm->cond_flag = COND_NEGATIVE;
        vm_verbose(vm, " register[%d] < register[%d]; cond: NEGATIVE }\n", arg_a_reg_ind, arg_b_reg_ind);
        vm->program_counter++;
        return;
    }

    if (res == 0) {
        vm->cond_flag = COND_ZERO;
        vm_verbose(vm, " register[%d] == register[%d]; cond: ZERO }\n", arg_a_reg_ind, arg_b_reg_ind);
        vm->program_counter++;
        return;
    }

    if (res > 0) {
        vm->cond_flag = COND_POSITIVE;
        vm_verbose(vm, " register[%d] > register[%d]; cond: POSITIVE }\n", arg_a_reg_ind, arg_b_reg_ind);
        vm->program_counter++;
        return;
    }

    // crash();
}

void jmp(VM *vm) {
    vm_verbose(vm, "JMP: {");
    vm->program_counter++;
    i32 reg_ind = vm->program[vm->program_counter];
    i32 jmp_to = vm->registers[reg_ind];
    vm_verbose(vm, " program_couter -> %.2d }\n", jmp_to);
    vm->program_counter = jmp_to;
}

void je(VM *vm) {
    vm_verbose(vm, "JE: {");
    vm->program_counter++;
    i32 reg_ind = vm->program[vm->program_counter];
    i32 jump_to = vm->registers[reg_ind];

    if (vm->cond_flag == COND_ZERO) {
        vm_verbose(vm, " cond: == 0; JUMPING }\n");
        vm->program_counter = jump_to;
        return;

    } else {
        vm_verbose(vm, " cond != 0; NOT JUMPING }\n");
        vm->program_counter++;
        return;
    }
}

void jne(VM *vm) {
    vm_verbose(vm, "JNE: {");
    vm->program_counter++;
    i32 reg_ind = vm->program[vm->program_counter];
    i32 jump_to = vm->registers[reg_ind];

    if (vm->cond_flag == COND_NEGATIVE || vm->cond_flag == COND_POSITIVE) {
        vm_verbose(vm, " cond: != 0; JUMPING }\n");
        vm->program_counter = jump_to;
        return;

    } else {
        vm_verbose(vm, " cond: == 0; NOT JUMPING }\n");
        vm->program_counter++;
        return;
    }
}

void jge(VM *vm) {
    vm_verbose(vm, "JGE: {");
    vm->program_counter++;
    i32 reg_ind = vm->program[vm->program_counter];
    i32 jump_to = vm->registers[reg_ind];

    if (vm->cond_flag == COND_POSITIVE || vm->cond_flag == COND_ZERO) {
        vm_verbose(vm, " cond >= 0; JUMPING }\n");
        vm->program_counter = jump_to;
        return;

    } else {
        vm_verbose(vm, "cond < 0; NOT JUMPING }\n");
        vm->program_counter++;
        return;
    }
}

void jle(VM *vm) {
    vm_verbose(vm, "JLE: {");
    vm->program_counter++;
    i32 reg_ind = vm->program[vm->program_counter];
    i32 jump_to = vm->registers[reg_ind];

    if (vm->cond_flag == COND_NEGATIVE || vm->cond_flag == COND_ZERO) {
        vm_verbose(vm, " cond <= 0; JUMPING }\n");
        vm->program_counter = jump_to;
        return;

    } else {
        vm_verbose(vm, " cond > 0; NOT JUMPING }\n");
        vm->program_counter++;
        return;
    }
}

void mul(VM *vm) {
}
