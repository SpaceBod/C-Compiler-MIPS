f:
PUSH0:
addiu $sp, $sp, -44
sw $ra, 40($sp)
nop
sw $fp, 36($sp)
nop
sw $s0, 4($sp)
nop
sw $s1, 8($sp)
nop
sw $s2, 12($sp)
nop
sw $s3, 16($sp)
nop
sw $s4, 20($sp)
nop
sw $s5, 24($sp)
nop
sw $s6, 28($sp)
nop
sw $s7, 32($sp)
nop
move $fp, $sp
body2:
li $v0, 42
addiu $sp, $sp, 0
move $fp, $sp
b POP1
nop
addiu $sp, $sp, 0
move $fp, $sp
POP1:
mtc1 $v0, $f0
lw $s0, 4($sp)
nop
lw $s1, 8($sp)
nop
lw $s2, 12($sp)
nop
lw $s3, 16($sp)
nop
lw $s4, 20($sp)
nop
lw $s5, 24($sp)
nop
lw $s6, 28($sp)
nop
lw $s7, 32($sp)
nop
lw $ra, 40($sp)
nop
lw $fp, 36($sp)
nop
move $sp, $fp
jr $ra
nop
.global f
