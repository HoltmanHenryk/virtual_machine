# Simple loop example
mov 0, $1
mov 10, $2
start:
inc $1
cmp $1, $2
jne .start
halt
