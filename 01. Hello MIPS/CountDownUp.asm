#Adam Fenjiro
#afenjiro@mtu.edu
#CS1142
#Program 1 - CountDownUp

.text
main:
    # Read an integer from the user
    li      $v0, 5
    syscall
    move    $t0, $v0

    # Output numbers from input to 1
    move    $t1, $t0
    j       output_backward

output_backward:
    bgtz    $t1, continue_output_backward  # If loop variable > 0, jump to continue_output_backward
    j       newline          # If loop variable <= 0, jump to newline

continue_output_backward:
    move    $a0, $t1
    li      $v0, 1
    syscall
    li      $v0, 11
    li      $a0, 32
    syscall
    subi    $t1, $t1, 1
    j       output_backward

newline:
    # Output a newline before finishing the first part
    li      $v0, 11
    li      $a0, 10
    syscall

    # Output numbers from 1 to input
    li      $t1, 1           # Initialize loop variable to 1
    j       output_forward   # Jump to output_forward

output_forward:
    bgt     $t1, $t0, terminate   # If loop variable > input, jump to terminate
    move    $a0, $t1
    li      $v0, 1
    syscall
    li      $v0, 11
    li      $a0, 32
    syscall
    addi    $t1, $t1, 1
    j       output_forward

terminate:
    li      $v0, 10          # syscall 10 terminates program execution
    syscall
