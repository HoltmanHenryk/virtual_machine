toggle_verbose 0
jmp .start

func_print:

    ld $arg_a, $arg_c
    strlen_r $arg_c, $arg_d
    mov write_syscall, $arg_a
    mov stdout, $arg_b
    syscall
    line_br
    ret


fizzbuzz:
    mov @fb, $arg_a
    call .func_print
    jmp .loop_midway

fizz:
    mov @f, $arg_a
    call .func_print
    jmp .loop_midway

buzz:
    mov @b, $arg_a
    call .func_print
    jmp .loop_midway


start:
    mov 100, $0
    mov 1, $1
    mov 0, $10
    mov 3, $3
    mov 5, $5
    mov 15, $15

    loop_start:

        
        ld $1, $6
        mod $6, $15
        cmp $6, $10
        je .fizzbuzz

        ld $1, $6
        mod $6, $3
        cmp $6, $10
        je .fizz

        ld $1, $6
        mod $6, $5
        cmp $6, $10
        je .buzz


        print_int $1
        line_br

        loop_midway:
	inc $1
	dec $0
        cmp $0, $10
        jne .loop_start

halt


.data
    fb: "FizzBuzz"
    f: "Fizz"
    b: "Buzz"
