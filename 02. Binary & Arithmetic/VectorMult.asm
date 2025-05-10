#Adam Fenjiro
#afenjiro@mtu.edu
#Program 2

.data
n: .word 0
d: .word 0
vectors: .space 4000

.text

main:
    # Reading the input for N and D
    li $v0, 5
    syscall
    sw $v0, n
    blez $v0, terminate  # n <= 0, terminate

    li $v0, 5
    syscall
    sw $v0, d
    blez $v0, terminate  # d <= 0, terminate

    # Check if total size exceeds the limit
    li $t2, 1000
    lw $t0, n
    lw $t1, d
    mul $t3, $t0, $t1  # $t3 = n * d
    bgt $t3, $t2, terminate  # If the total size exceeds the limit

    # Reading the input for vectors
    mul $t3, $t3, 4  # n*d * 4
    li $t4, 0  # input_count

read_loop:
    bge $t4, $t3, vector_multiplication_loop  # while (input_count <= n*d)

    li $v0, 5
    syscall

    sw $v0, vectors($t4)  # Store in the vectors array
    addi $t4, $t4, 4

    b read_loop

# Part 3: Multiplying vectors
vector_multiplication_loop:
    # Read index 1
    li $v0, 5
    syscall
    move $t0, $v0

    # Check index 1 validity
    bltz $t0, terminate
    lw $t4, n
    bge $t0, $t4, terminate

    # Read index 2
    li $v0, 5
    syscall
    move $t1, $v0

    # Check index 2 validity
    bltz $t1, terminate
    bge $t1, $t4, terminate

    # Multiply elements and print
    li $t2, 0
    lw $t4, d
    mul $t3, $t0, $t4
    mul $t4, $t1, $t4

vector_multiplication_inner_loop:
    andi $t3, $t3, -4
    lw $t5, vectors($t3)  # Load element from vector 1
    andi $t4, $t4, -4
    lw $t6, vectors($t4)  # Load element from vector 2
    mult $t5, $t6
    mflo $a0  # Print result
    li $v0, 1
    syscall

	# Print a space
    li $v0, 11  
    addi $a0, $0, 32
    syscall

    addi $t2, $t2, 1
    addi $t3, $t3, 4
    addi $t4, $t4, 4
    blt $t2, $t0, vector_multiplication_inner_loop

    # Print a line feed
    li $v0, 11
    addi $a0, $0, 10
    syscall

    j vector_multiplication_loop

terminate:
    li $v0, 10
    syscall