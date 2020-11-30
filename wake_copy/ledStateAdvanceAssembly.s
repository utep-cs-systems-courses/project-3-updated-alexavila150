    .arch msp430g2553
    .p2align 1,0
    .text
jt:
    .word case0
    .word case1
    .word case2

    .extern turn_green_dim
    .extern turn_green_bright
    .extern turn_green_middle
    .extern turn_green_on
    .extern led_state
    .extern turn_red_on


    .global ledStateAdvance
ledStateAdvance:
    sub #2, r1 ; allocate memory for count
    mov r12, 0(r1);

    cmp #3, &led_state
    jc default
    mov &led_state, r13; r13 = state
    add r13, r13; r13 * 2
    mov jt(r13), r0 ;

case0:
    call #turn_green_dim
    add #1, 0(r1);
    jmp default

case1:
    call #turn_green_middle
    add #1, 0(r1)
    jmp default

case2:
    mov 0(r1), r12
    call #turn_green_bright
    mov r12, 0(r1)
    jmp default

default:
    cmp #250, 0(r1)
    jnc endif2
    add #1, &led_state
    cmp #3, &led_state
    jnz endif
    mov #0, &led_state
endif:
    mov #0, 0(r1)
endif2:
    mov 0(r1), r12
    add #2, r1; deallocate memory
    pop r0
