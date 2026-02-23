# store value 10 for comparasion
mov 10, $10
# store a "jump point" right before we increment
sto_pc $0
inc $1
# compare if our value is less then 10
cmp $1, $10
# jump to our stored point if is less or equal to 10
jle $0
state_dump
halt
