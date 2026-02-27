# you can leave comments with a hash 
mov 10, $10
loop_start:
# you can adress registers with both '%' and '$'
inc $1
cmp $1, $10
jle .loop_start
state_dump
halt
