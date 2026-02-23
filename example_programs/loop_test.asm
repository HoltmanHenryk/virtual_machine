# --- JUMP INSTRUCTIONS EXAMPLES---
mov 10, $1          # reg 1 = 10 (limit)
mov 0, $2           # reg 2 = 0  (counter)

# test 1: JMP e JNE (increment loop)
start_loop:
inc $2
cmp $2, $1
jne .start_loop    # should jump 10 times until $2 is equals 10

# falls through the blocks

# test 2: JE 
cmp $2, $1
je .test_ge         # should jump, as 10 == 10
halt                # if you halted here, JE failed

# test 3: JGE and JLE 
test_ge:
mov 20, $3
cmp $3, $1          # compares 20 with 10 (20 > 10)
jge .test_le        # should jump, as 20 >= 10
halt                # if you halted here, JGE failed

test_le:
mov 5, $4
cmp $4, $1          # compares 5 with 10 (5 < 10)
jle .test_jmp       # should jump, as 5 <= 10
halt                # if you halted here, JLE failed

test_jmp:
jmp .end_success    # no condition checks, just straight jump
halt                # if you halted here, JMP failed


end_success:
state_dump          # expected: reg1 = 10, reg2 =  10, reg3 = 20, reg4 = 5, program_counter = 40, program_size = 42, condition_flag = -1
halt
