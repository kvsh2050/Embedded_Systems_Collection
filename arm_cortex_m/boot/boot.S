    .section .vectors
    .align 2
vector_table:
        .word 0xabcd  //stack top 
        .word reset_handler + 1
        .zero 400

    .section .text 
    .align 2
    .type reset_handler, %function 
reset_handler:
        mov r1, #10
        mov r2, #20
        add r3 , r1, r2
        b start
        b .