mov 10, $10
sto_pc $0
inc $1
cmp $1, $10
jle $0
state_dump
halt
