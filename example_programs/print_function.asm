toggle_verbose 0

mov @msg, $arg_a
call .func_print
line_br

mov @msg2, $arg_a
call .func_print
line_br

mov @msg3, $arg_a
call .func_print
line_br

halt


func_print:



    ld $arg_a $arg_c

    strlen_r $arg_c, $arg_d
    
    mov write_syscall, $arg_a
    mov stdout, $arg_b

    syscall
    ret



.data
    msg: "This is the message i want to print"

    msg2: "This is another message i want to print"

    msg3: "Another one just for good measure"
