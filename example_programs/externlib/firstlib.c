#include <stdio.h>
#include "../../VMASM.h"


WORD hello_from_lib(VMASMObject obj) {
    printf("Hello, from the first library: %d %d %d\n", obj.arg_a, obj.arg_b, obj.arg_c);
    return 0;
}

