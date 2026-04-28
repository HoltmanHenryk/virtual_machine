#include <stdio.h>
#include "../../VMASM.h"

WORD hello_another_lib(void) {
    printf("Hello, %s, this is from a second library!\n", vmasm_get_globalstring());
    return 0;
}
