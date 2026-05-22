main:	
	lui $23, 0xffff
	lui $16, 0x1001
	
	addi $17, $16, 81920
	addi $16, $16, 16384
	
	sw $16, 0($17)
	addi $16, $16, 512
	
	sw $16, 4($17)
	
	
	addi $8, $0, 0xff00
	sw $8, 8($17)
	
	lw $9, 0($17)
	sw $8, 0($9)
	
	addi $8, $0, 0x00ff
	sw $8, 12($17)
	
	lw $9, 4($17)
	sw $8, 0($9)

	
multplay:
	
	jal player1
	
	jal player2

	jal timer
	
	j multplay


fim:	addi $2, $0, 10
	syscall
	
	
player1:
	lw $10, 40($17)
	
	bne $10, $0, loopmov1
	
	lw $8, 0($23)
	
	beq $8, $0, voidm
	
	lw $9, 4($23)
	  
	addi $10, $0, 'a'
	beq $9, $10, movl1
	
	addi $10, $0, 'w'
	beq $9, $10, movu1
	
	addi $10, $0, 'd'
	beq $9, $10, movr1
	
	addi $10, $0, 's'
	beq $9, $10, movd1
	
	jr $31


loopmov1:
	
	addi $10, $10, -1
	sw $10, 40($17)
	beq $10, $0, voidm
	
	lw $9, 44($17)
	
	beq $9, 1, movl1
	beq $9, 2, movu1
	beq $9, 3, movr1
	beq $9, 4, movd1
	
	jr $31	
movl1:	

	lw $8, 0($17)
	
	lw $9, 8($17)
	
	addi $8, $8, -4
	sw $9, 0($8)
	
	sw $0, 4($8)
	
	sw $8, 0($17)
	
	lw $11, 40($17)
	
	bne $11, $0, skipl1
	addi $11, $0, 5
	
	sw $11, 40($17)
	
skipl1:	addi $10, $0, 1
	sw $10, 44($17)
	
	jr $31

movu1:	

	lw $8, 0($17)
	
	lw $9, 8($17)
	
	addi $8, $8, -512
	sw $9, 0($8)
	
	sw $0, 512($8)
	
	sw $8, 0($17)
	
	lw $11, 40($17)
	
	bne $11, $0, skipu1
	
	addi $11, $0, 5
	
	sw $11, 40($17)
	
skipu1:	addi $10, $0, 2
	sw $10, 44($17)
	
	jr $31
	

movr1:	

	lw $8, 0($17)
	
	lw $9, 8($17)
	
	addi $8, $8, 4
	sw $9, 0($8)
	
	sw $0, -4($8)
	
	sw $8, 0($17)
	
	lw $11, 40($17)
	
	bne $11, $0, skipr1
	
	addi $11, $0, 5
	
	sw $11, 40($17)
	
skipr1:	addi $10, $0, 3
	sw $10, 44($17)
	
	
	jr $31		
	
movd1:	

	lw $8, 0($17)
	
	lw $9, 8($17)
	
	addi $8, $8, 512
	sw $9, 0($8)
	
	sw $0, -512($8)
	
	sw $8, 0($17)
	
	lw $11, 40($17)
	
	bne $11, $0, skipd1
	
	addi $11, $0, 5
	
	sw $11, 40($17)
	
skipd1:	addi $10, $0, 4
	sw $10, 44($17)
	
	
	jr $31
			
player2:
	lw $10, 48($17)
	
	bne $10, $0, loopmov2

	lw $8, 0($23)
	
	beq $8, $0, voidm
	
	lw $9, 4($23)
	  
	addi $10, $0, 'j'
	beq $9, $10, movl2
	
	addi $10, $0, 'i'
	beq $9, $10, movu2
	
	addi $10, $0, 'l'
	beq $9, $10, movr2
	
	addi $10, $0, 'k'
	beq $9, $10, movd2
	
	jr $31
	
loopmov2:
	
	addi $10, $10, -1
	sw $10, 48($17)
	beq $10, $0, voidm
	
	lw $9, 52($17)
	
	beq $9, 1, movl2
	beq $9, 2, movu2
	beq $9, 3, movr2
	beq $9, 4, movd2
	
	jr $31
	
movl2:	

	lw $8, 4($17)
	
	lw $9, 12($17)
	
	addi $8, $8, -4
	sw $9, 0($8)
	
	sw $0, 4($8)
	
	sw $8, 4($17)
	
	lw $11, 48($17)
	
	bne $11, $0, skipl2
	
	addi $11, $0, 5
	
	sw $11, 48($17)
	
skipl2:	addi $10, $0, 1
	sw $10, 52($17)
	
	jr $31

movu2:	

	lw $8, 4($17)
	
	lw $9, 12($17)
	
	addi $8, $8, -512
	sw $9, 0($8)
	
	sw $0, 512($8)
	
	sw $8, 4($17)
	
	lw $11, 48($17)
	
	bne $11, $0, skipu2
	
	addi $11, $0, 5
	
	sw $11, 48($17)
	
skipu2:	addi $10, $0, 2
	sw $10, 52($17)
	
	jr $31
	

movr2:	

	lw $8, 4($17)
	
	lw $9, 12($17)
	
	addi $8, $8, 4
	sw $9, 0($8)
	
	sw $0, -4($8)
	
	sw $8, 4($17)
	
	lw $11, 48($17)
	
	bne $11, $0, skipr2
	
	addi $11, $0, 5
	
	sw $11, 48($17)
	
skipr2:	addi $10, $0, 3
	sw $10, 52($17)
	
	jr $31		
	
movd2:	

	lw $8, 4($17)
	
	lw $9, 12($17)
	
	addi $8, $8, 512
	sw $9, 0($8)
	
	sw $0, -512($8)
	
	sw $8, 4($17)
	
	lw $11, 48($17)
	
	bne $11, $0, skipd2
	
	addi $11, $0, 5
	
	sw $11, 48($17)
	
skipd2:	addi $10, $0, 4
	sw $10, 52($17)
	
	jr $31	
	
voidm: jr $31

timer:	
	add $4, $0, 500
	
tloop:	
	addi $4, $4, -1
	
	bne $4, $0, tloop
	
	jr $31