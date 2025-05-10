#Adam Fenjiro
#afenjiro@mtu.edu
#Program 3 - Inventory

# .data section for inventory linked list
.data
delimiter: .asciiz ", qty "
newline: .asciiz "\n"

### START DATA ###
first:       .word node2
            .word 1995
            .word 3
            .asciiz "French Press Coffee Maker"
node2:       .word node3
            .word 1150
            .word 26
            .asciiz "illy Ground Coffee Espresso"
node3:       .word node4
            .word 2606
            .word 0
            .asciiz "Hollander Dutched Chocolate Sauce"
node4:       .word node5
            .word 1597
            .word 6
            .asciiz "Attsky 53mm Espresso Tamper"
node5:       .word node6
            .word 1898
            .word 0
            .asciiz "Starbucks Medium Roast Whole Bean Coffee"
node6:       .word -1
            .word 14905
            .word 1
            .asciiz "Nespresso Essenza Mini Espresso Machine"
### END DATA ###

# .text section for the main program
.text
.globl main

main:

    # Read mini price and store in $t0
    li $v0, 5
    syscall
    move $t0, $v0

    # Read max price and store in $t1
    li $v0, 5
    syscall
    move $t1, $v0

    # Load address first node
    la $t2, first

loop:
    # Check if end of list reached
    lw $t3, 0($t2)
    bne $t3, -1, continue
    j exit

continue:
    # Load price and quantity
    lw $t4, 4($t2)
    lw $t5, 8($t2)

    # Check price and quantity
    blt $t4, $t0, next_node  # if (price < minimum) then skip
    bgt $t4, $t1, next_node  # if (price > maximum) then skip
    blez $t5, next_node  # if (quantity <= 0) then skip

    # Print product information
    la $a0, 12($t2)
    li $v0, 4
    syscall
    
    # Print a coma
    li $v0, 11  
    addi $a0, $0, 44
    syscall

	# Print a space
    li $v0, 11  
    addi $a0, $0, 32
    syscall

    # Print dollar sign
    li $v0, 11  
    addi $a0, $0, 36
    syscall

	# Print price in dollars
    div $t6, $t4, 100
    mflo $a0              
    li $v0, 1
    syscall

    # Print decimal point
    li $v0, 11        
    addi $a0, $0, 46
    syscall

	# Print cents
    mfhi $a0              
    li $v0, 1
    syscall

	# Print delimiter
    li $v0, 4       
    la $a0, delimiter
    syscall

	# Print quantity
    move $a0, $t5    
    li $v0, 1
    syscall

	# Print newline
    li $v0, 4       
    la $a0, newline
    syscall

next_node:
    # Move to next node
    move $t2, $t3
    j loop

exit:
    # Exit program
    li $v0, 10
    syscall
