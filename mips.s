.text
main:
move $fp, $sp
addiu $sp, $sp, -44
sw $s0, 4($sp)
sw $s1, 8($sp)
sw $s2, 12($sp)
sw $s3, 16($sp)
sw $s4, 20($sp)
sw $s5, 24($sp)
sw $s6, 28($sp)
sw $s7, 32($sp)
sw $fp, 36($sp)
sw $ra, 40($sp)
addi $sp, $sp, -4
addi $t0, $0, 2
sw $t0, -48($fp)
addi $t0, $0, 999
add $v0, $0, $t0
j mainend
addiu $sp, $sp, 4
mainend:
addiu $sp, $sp, 4
lw $s0, 4($sp)
lw $s1, 8($sp)
lw $s2, 12($sp)
lw $s3, 16($sp)
lw $s4, 20($sp)
lw $s5, 24($sp)
lw $s6, 28($sp)
lw $s7, 32($sp)
lw $fp, 36($sp)
lw $ra, 40($sp)
move $sp, $fp
jr $ra
.global main
