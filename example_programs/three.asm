toggle_verbose 0

mov 0, $0
mov 3, $3
mov -1, $10

mov @prompt, $arg_c
strlen @prompt, $arg_d
call .print_syscall
rdint $1

cmp $1, $0
jge .gte_zero
jmp .else

halt


gte_zero:
    ld $1, $5
    sub $5, $3

    mov @minus, $arg_c
    strlen @minus, $arg_d
    call .print_syscall
    print_int $5
    mov @isthree, $arg_c
    strlen @isthree, $arg_d
    call .print_syscall
    line_br
    halt

else:
    ld $1, $5
    mul $5, $10
    add $5, $3
    
    mov @plus, $arg_c
    strlen @plus, $arg_d
    call .print_syscall
    print_int $5
    mov @isthree, $arg_c
    strlen @isthree, $arg_d
    call .print_syscall
    line_br
    halt


print_syscall:
    mov write_syscall, $arg_a
    mov stdout, $arg_b
    syscall
    ret


.data
    prompt: "Type a number: "
    isthree: " is 3!"
    minus: "Your number minus "
    plus: "Your number plus "
    
