    .arch msp430g2553
    .p2align 1,0
    .text
jt:				; Jump table
    .word case0
    .word case1
    .word case2

    .extern turn_green_dim	; Import Methods to turn lights if they are call multiple times
    .extern turn_green_bright
    .extern turn_green_middle
    .extern turn_green_on
    .extern led_state
    .extern turn_red_on


    .global ledStateAdvance
ledStateAdvance:
    sub #2, r1 			; Allocate memory for count
    mov r12, 0(r1) 		; 0(r1) = count

    cmp #3, &led_state		; if(led_state <= 3)
    jc default			; goto default
    mov &led_state, r13		; r13 = state
    add r13, r13		; r13 * 2
    mov jt(r13), r0 		; switch(state)

case0:
    call #turn_green_dim	; turn_green_dim()
    add #1, 0(r1)		; count++
    jmp default			; break

case1:
    call #turn_green_middle	; turn_green_middle()
    add #1, 0(r1)		; count++
    jmp default			; break

case2:
    mov 0(r1), r12		; 1st parameter = count
    call #turn_green_bright	; turn_green_bright(count)
    mov r12, 0(r1)		; count = returning value
    jmp default			; break

default:
    cmp #250, 0(r1)		; if(count < 250)
    jl endif2			; goto endif2
    add #1, &led_state		; led_state++
    cmp #3, &led_state		; if(led_state != 3)
    jnz endif			; goto endif
    mov #0, &led_state		; led_state = 0
endif:
    mov #0, 0(r1)		; 0(r1) = 0
endif2:
    mov 0(r1), r12		; return count
    add #2, r1			; Deallocate Memory
    pop r0			; finish method
