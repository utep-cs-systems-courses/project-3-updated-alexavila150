    .arch msp430g2553
    .p2align 1,0

    .data
state:
    .word 0


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

    .global ledStateAdvance
ledStateAdvance:
    call turn_green_on
    cmp #3, &state
    jc default
    mov &state, r13; r13 = state
    add r13, r13; r13 * 2
    mov jt(r13), r0 ;

case0:
    call turn_green_dim
    add #1, r12;
    jmp default

case1:
    call turn_green_middle
    add #1, r12
    jmp default

case2:
    mov r12, r12
    call turn_green_bright
    mov r12, r12
    jmp default

default:
    cmp #250, r12
    jnc endif2
    add #1, &state
    cmp #3, &state
    jnz endif
    mov #0, &state
endif:
    mov #0, r12
endif2:
    mov r12, r12
    pop r0
