#Adam Fenjiro
#afenjiro@mtu.edu
#CS1142
#Program 1 - Powers


.text
main:
    # Read an integer from the user
    li      $v0, 5
    syscall
    move    $t0, $v0

    # Check if N is equal to 0, less than 0, or equal to 1
    beq     $t0, $zero, terminate   # If N = 0, terminate
    bltz    $t0, terminate           # If N < 0, terminate
    beq     $t0, 1, terminate      # If N = 1, terminate

    # Initialize loop variable to 2 (powers start from 2)
    li      $t1, 2

powers_loop:
    li      $t2, 1
    li      $t3, 0

    powers_inner_loop:
        bgt     $t2, 1000, next_base
        move    $a0, $t2
        li      $v0, 1
        syscall
        li      $v0, 11
        li      $a0, 32          # ASCII code 32 is a space
        syscall

        # Calculate the next power: power = $t1^$t3
        mul     $t2, $t2, $t1
        addi    $t3, $t3, 1
        j       powers_inner_loop

    next_base:
    li      $v0, 11
    li      $a0, 10          # ASCII code 10 is a newline
    syscall

    addi    $t1, $t1, 1
    ble     $t1, $t0, powers_loop

terminate:
    li      $v0, 10          # syscall 10 terminates program execution
    syscall