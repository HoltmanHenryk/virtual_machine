#ifndef VMASM_H
#define VMASM_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef int32_t i32;
typedef int32_t WORD;

#define UNUSED(x) (void)(x)

typedef struct {
    i32 arg_a;
    i32 arg_b;
    i32 arg_c;
    i32 arg_d;
    i32 arg_e;
    i32 arg_f;
    i32 arg_g;
    i32 arg_h;
} VMASMObject;

char *__vmasm_internal_globalstrirng = NULL;

WORD __vmasm_internal_setstring(const char *str) {

    if(__vmasm_internal_globalstrirng != NULL) {
        free(__vmasm_internal_globalstrirng);
        __vmasm_internal_globalstrirng = NULL;
    }

    if (str == NULL) {
        return 0;
    }

    __vmasm_internal_globalstrirng = strdup(str);

    if(__vmasm_internal_globalstrirng == NULL) {
        return 1;
    }

    return 0;
}

const char *vmasm_get_globalstring() {
    return (const char *)__vmasm_internal_globalstrirng;
}


#endif /* VMASM_H */
