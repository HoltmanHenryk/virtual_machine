#ifndef SPEC_H
#define SPEC_H

typedef enum {
    REG_0 = 0,
    REG_1,
    REG_2,
    REG_3,
    REG_4,
    REG_5,
    REG_6,
    REG_7,
    REG_COUNT,
} Registers;

typedef enum {
    NO_OP = 0,
    HALT,
    STATE_DUMP,
    MOV, /* move value to register -> mov 30, %reg                    */
    LD,  /* load value from register to register -> ld %reg_a, %reg_b */

} Opcodes;

#endif /* SPEC_H */
