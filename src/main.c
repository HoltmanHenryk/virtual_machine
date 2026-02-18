#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "spec.h"

#define MAX_PROGRAM_SIZE 32767

typedef uint32_t u32;

typedef struct {

    u32 program_counter;
    u32 program[MAX_PROGRAM_SIZE];
    u32 program_size;
    u32 registers[REG_COUNT];
} VM;

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
}

int main(void) {

    //   const char *program_path = "program.vmbin";

    VM vm = {0};

    printf("program loaded: \n"
           "    mov 30, %%5 \n"
           "    STATE_DUMP\n"
           "    ld %%5, %%7\n"
           "\n");

    printf("program_counter = %d\n", vm.program_counter);

    /* move 30 in to register 5 */
    /* r5 = 30; */
    vm.program[0] = MOV;
    vm.program[1] = 30;
    vm.program[2] = 5;

    vm.program[3] = STATE_DUMP;

    /* load the value of register 5 in to register 7 */
    /* r7 = r5; */
    vm.program[4] = LD;
    vm.program[5] = 5;
    vm.program[6] = 7;

    vm.program[7] = STATE_DUMP;

    vm.program_size = 8;

    for (u32 i = 0; i < vm.program_size; ++i) {

        printf("program[%d] = %d\n", i, vm.program[i]);
    }

    printf("==== VM INIT ===\n");

    bool loop = true;

    while (loop) {

        printf("debug: program_counter = %d\n", vm.program_counter);

        switch (vm.program[vm.program_counter]) {

        case STATE_DUMP: {
            state_dump(&vm);
            vm.program_counter++;

        } break;

        case MOV: {
            printf("MOV: \n");
            vm.program_counter++;
            u32 tmp = vm.program[vm.program_counter];
            printf("    tmp = %d\n", vm.program[vm.program_counter]);
            vm.program_counter++;
            vm.registers[vm.program[vm.program_counter]] = tmp;
            printf("    reg%d = %d\n", vm.program[vm.program_counter], tmp);
            vm.program_counter++;
        } break;

        case LD: {
            printf("LD: \n");
            vm.program_counter++;
            u32 reg_num = vm.program[vm.program_counter];
            printf("    reg_num = %d\n", reg_num);
            u32 value = vm.registers[reg_num];
            printf("    value = %d\n", value);
            vm.program_counter++;
            u32 reg_target = vm.program[vm.program_counter];
            printf("    reg_target = %d\n", reg_target);
            vm.registers[reg_target] = value;
            vm.program_counter++;

        } break;

        default: {
            printf("default\n");
            loop = false;
            break;
        }
        }
    }

    return 0;
}
