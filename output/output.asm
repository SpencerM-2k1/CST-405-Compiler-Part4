.text
.globl main
main:
	li $t0, 15 #ASSIGN INT VALUE
	sw $t0, i80
	lw $t0, i80 #STORE INT
	nop
	sw $t0, main_0.localInt_var
	l.s $f0, float_const_0 #ASSIGN FLOAT VALUE
	nop
	s.s $f0, f8
	l.s $f0, f8 #STORE FLOAT
	nop
	s.s $f0, main_0.localFloat_var
	li $t0, 20 #ASSIGN INT VALUE
	sw $t0, i81
	lw $t0, i81 #STORE INT
	nop
	sw $t0, main_0.globalInt_var
	li $t0, 67 #ASSIGN CHAR VALUE
	la $t1, c9
	sb $t0, 0($t1)
	lb $t0, c9 #STORE CHAR
	nop
	la $t1, main_0.globalChar_var
	sb $t0, 0($t1)
	lw $t0, main_0.globalInt_var #LOAD INT
	nop
	sw $t0, i82
	lw $t0, i82 #LOAD INT
	nop
	sw $t0, printInt_1.value_var
	jal printInt_func #FUNCTION CALL
	nop
	lb $t0, main_0.globalChar_var #LOAD CHAR
	nop
	la $t1, c10
	sb $t0, 0($t1)
	lb $t0, c10 #LOAD CHAR
	nop
	la $t1, printChar_2.value_var
	sb $t0, 0($t1)
	jal printChar_func #FUNCTION CALL
	nop
	l.s $f0, main_0.globalFloat_var #LOAD FLOAT
	nop
	s.s $f0, f9
	l.s $f0, f9 #LOAD FLOAT
	nop
	s.s $f0, printFloat_3.value_var
	jal printFloat_func #FUNCTION CALL
	nop
	lw $t0, main_0.localInt_var #LOAD INT
	nop
	sw $t0, i83
	li $t0, 2 #ASSIGN INT VALUE
	sw $t0, i84
	lw $t0, i83 #MULTIPLY INT
	nop
	lw $t1, i84
	nop
	mul $t0, $t0, $t1
	sw $t0, i85
	li $t0, 3 #ASSIGN INT VALUE
	sw $t0, i86
	lw $t0, i85 #ADD INT
	nop
	lw $t1, i86
	nop
	add $t0, $t0, $t1
	sw $t0, i87
	li $t0, 5 #ASSIGN INT VALUE
	sw $t0, i88
	li $t0, 2 #ASSIGN INT VALUE
	sw $t0, i89
	lw $t0, i88 #SUBTRACT INT
	nop
	lw $t1, i89
	nop
	sub $t0, $t0, $t1
	sw $t0, i90
	lw $t0, i87 #DIVIDE INT
	nop
	lw $t1, i90
	nop
	div $t0, $t1
	mflo $t0
	sw $t0, i91
	lw $t0, main_0.globalInt_var #LOAD INT
	nop
	sw $t0, i92
	lw $t0, i91 #ADD INT
	nop
	lw $t1, i92
	nop
	add $t0, $t0, $t1
	sw $t0, i93
	lw $t0, i93 #STORE INT
	nop
	sw $t0, main_0.result_var
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i94
	li $t0, 10 #ASSIGN INT VALUE
	sw $t0, i95
	lw $t0, i94 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i95
	nop
	sgt $t2, $t0, $t1
	sw $t2, i96
	lw $t0, i96 #IF FALSE
	nop
	beq $t0, $zero, L11
	nop
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i97
	li $t0, 2 #ASSIGN INT VALUE
	sw $t0, i98
	lw $t0, i97 #MULTIPLY INT
	nop
	lw $t1, i98
	nop
	mul $t0, $t0, $t1
	sw $t0, i99
	lw $t0, i99 #STORE INT
	nop
	sw $t0, main_0.temp_var
	lw $t0, main_0.temp_var #LOAD INT
	nop
	sw $t0, i100
	lw $t0, i100 #LOAD INT
	nop
	sw $t0, displayResult_5.result_var
	jal displayResult_func #FUNCTION CALL
	nop
	j L12 #GOTO
	nop
L11:
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i101
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i102
	lw $t0, i101 #SUBTRACT INT
	nop
	lw $t1, i102
	nop
	sub $t0, $t0, $t1
	sw $t0, i103
	lw $t0, i103 #STORE INT
	nop
	sw $t0, main_0.temp_var
	lw $t0, main_0.temp_var #LOAD INT
	nop
	sw $t0, i104
	li $t0, 3 #ASSIGN INT VALUE
	sw $t0, i105
	lw $t0, i104 #ADD INT
	nop
	lw $t1, i105
	nop
	add $t0, $t0, $t1
	sw $t0, i106
	lw $t0, i106 #LOAD INT
	nop
	sw $t0, displayResult_5.result_var
	jal displayResult_func #FUNCTION CALL
	nop
L12:
	li $t0, 0 #ASSIGN INT VALUE
	sw $t0, i107
	lw $t0, i107 #STORE INT
	nop
	sw $t0, main_0.i_var
L13:
	lw $t0, main_0.i_var #LOAD INT
	nop
	sw $t0, i108
	li $t0, 10 #ASSIGN INT VALUE
	sw $t0, i109
	lw $t0, i108 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i109
	nop
	slt $t2, $t0, $t1
	sw $t2, i110
	lw $t0, i110 #IF FALSE
	nop
	beq $t0, $zero, L14
	nop
	lw $t0, main_0.i_var #LOAD INT
	nop
	sw $t0, i111
	lw $t0, main_0.i_var #LOAD INT
	nop
	sw $t0, i112
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i113
	lw $t0, i112 #ADD INT
	nop
	lw $t1, i113
	nop
	add $t0, $t0, $t1
	sw $t0, i114
	lw $t0, i114 #LOAD INT
	nop
	sw $t0, multiply_6.y_var
	lw $t0, i111 #LOAD INT
	nop
	sw $t0, multiply_6.x_var
	jal multiply_func #FUNCTION CALL
	nop
	lw $t0, returnInt #STORE INT
	nop
	sw $t0, main_0.result_var
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i115
	li $t0, 20 #ASSIGN INT VALUE
	sw $t0, i116
	lw $t0, i115 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i116
	nop
	sgt $t2, $t0, $t1
	sw $t2, i117
	lw $t0, i117 #IF FALSE
	nop
	beq $t0, $zero, L15
	nop
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i118
	lw $t0, i118 #STORE INT
	nop
	sw $t0, main_0.globalInt_var
	j L14 #GOTO
	nop
	j L16 #GOTO
	nop
L15:
	lw $t0, main_0.globalInt_var #LOAD INT
	nop
	sw $t0, i119
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i120
	lw $t0, i119 #ADD INT
	nop
	lw $t1, i120
	nop
	add $t0, $t0, $t1
	sw $t0, i121
	lw $t0, i121 #STORE INT
	nop
	sw $t0, main_0.globalInt_var
L16:
	lw $t0, main_0.i_var #LOAD INT
	nop
	sw $t0, i122
	lw $t0, i122 #LOAD INT
	nop
	sw $t0, printInt_1.value_var
	jal printInt_func #FUNCTION CALL
	nop
	lw $t0, main_0.i_var #LOAD INT
	nop
	sw $t0, i123
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i124
	lw $t0, i123 #ADD INT
	nop
	lw $t1, i124
	nop
	add $t0, $t0, $t1
	sw $t0, i125
	lw $t0, i125 #STORE INT
	nop
	sw $t0, main_0.i_var
	j L13 #GOTO
	nop
L14:
	li $t0, 5 #ASSIGN INT VALUE
	sw $t0, i126
	lw $t0, i126 #LOAD INT
	nop
	sw $t0, factorial_7.n_var
	jal factorial_func #FUNCTION CALL
	nop
	lw $t0, returnInt #STORE INT
	nop
	sw $t0, main_0.result_var
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i127
	lw $t0, i127 #LOAD INT
	nop
	sw $t0, printInt_1.value_var
	jal printInt_func #FUNCTION CALL
	nop
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i128
	lw $t0, i128 #LOAD INT
	nop
	sw $t0, isPrime_8.n_var
	jal isPrime_func #FUNCTION CALL
	nop
	lw $t0, returnInt #IF FALSE
	nop
	beq $t0, $zero, L17
	nop
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i129
	lw $t0, i129 #LOAD INT
	nop
	sw $t0, displayResult_5.result_var
	jal displayResult_func #FUNCTION CALL
	nop
	j L18 #GOTO
	nop
L17:
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i130
	li $t0, 10 #ASSIGN INT VALUE
	sw $t0, i131
	lw $t0, i130 #SUBTRACT INT
	nop
	lw $t1, i131
	nop
	sub $t0, $t0, $t1
	sw $t0, i132
	lw $t0, i132 #LOAD INT
	nop
	sw $t0, displayResult_5.result_var
	jal displayResult_func #FUNCTION CALL
	nop
L18:
	li $t0, 5 #ASSIGN INT VALUE
	sw $t0, i133
	li $t0, 4 #ASSIGN INT VALUE
	sw $t0, i134
	lw $t0, i133 #MULTIPLY INT
	nop
	lw $t1, i134
	nop
	mul $t0, $t0, $t1
	sw $t0, i135
	lw $t0, i135 #STORE INT
	nop
	sw $t0, main_0.temp_var
	lw $t0, main_0.temp_var #LOAD INT
	nop
	sw $t0, i136
	li $t0, 10 #ASSIGN INT VALUE
	sw $t0, i137
	lw $t0, i136 #ADD INT
	nop
	lw $t1, i137
	nop
	add $t0, $t0, $t1
	sw $t0, i138
	lw $t0, i138 #STORE INT
	nop
	sw $t0, main_0.result_var
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i139
	lw $t0, i139 #LOAD INT
	nop
	sw $t0, printInt_1.value_var
	jal printInt_func #FUNCTION CALL
	nop
	lw $t0, main_0.localInt_var #LOAD INT
	nop
	sw $t0, i140
	li $t0, 20 #ASSIGN INT VALUE
	sw $t0, i141
	lw $t0, i141 #LOAD INT
	nop
	sw $t0, computeSum_4.b_var
	lw $t0, i140 #LOAD INT
	nop
	sw $t0, computeSum_4.a_var
	jal computeSum_func #FUNCTION CALL
	nop
	lw $t0, returnInt #STORE INT
	nop
	sw $t0, main_0.result_var
	lw $t0, main_0.result_var #LOAD INT
	nop
	sw $t0, i142
	lw $t0, i142 #LOAD INT
	nop
	sw $t0, displayResult_5.result_var
	jal displayResult_func #FUNCTION CALL
	nop
	li $v0, 10 #EXIT
	syscall
printInt_func:
	addi $sp, $sp, -4 #FUNCTION START
	sw $ra, 0($sp)
	lw $t0, printInt_1.value_var #LOAD INT
	nop
	sw $t0, i0
	lw $t0, i0 #WRITE INT
	nop
	move $a0, $t0
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
printChar_func:
	addi $sp, $sp, -4 #FUNCTION START
	sw $ra, 0($sp)
	lb $t0, printChar_2.value_var #LOAD CHAR
	nop
	la $t1, c0
	sb $t0, 0($t1)
	la $t1, c0 #WRITE CHAR
	lb $t0, 0($t1)
	nop
	move $a0, $t0
	li $v0, 11
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
printFloat_func:
	addi $sp, $sp, -4 #FUNCTION START
	sw $ra, 0($sp)
	l.s $f0, printFloat_3.value_var #LOAD FLOAT
	nop
	s.s $f0, f0
	l.s $f0, f0 #WRITE FLOAT
	nop
	mov.s $f12, $f0
	li $v0, 2
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
computeSum_func:
	addi $sp, $sp, -4 #FUNCTION START
	sw $ra, 0($sp)
	lw $t0, computeSum_4.a_var #LOAD INT
	nop
	sw $t0, i1
	lw $t0, computeSum_4.b_var #LOAD INT
	nop
	sw $t0, i2
	lw $t0, i1 #ADD INT
	nop
	lw $t1, i2
	nop
	add $t0, $t0, $t1
	sw $t0, i3
	lw $t0, i3 #STORE INT
	nop
	sw $t0, computeSum_4.sum_var
	lw $t0, computeSum_4.sum_var #LOAD INT
	nop
	sw $t0, i4
	li $t0, 5 #ASSIGN INT VALUE
	sw $t0, i5
	lw $t0, i4 #ADD INT
	nop
	lw $t1, i5
	nop
	add $t0, $t0, $t1
	sw $t0, i6
	lw $t0, i6 #STORE INT
	nop
	sw $t0, computeSum_4.temp_var
	lw $t0, computeSum_4.temp_var #LOAD INT
	nop
	sw $t0, i7
	li $t0, 2 #ASSIGN INT VALUE
	sw $t0, i8
	lw $t0, i7 #MULTIPLY INT
	nop
	lw $t1, i8
	nop
	mul $t0, $t0, $t1
	sw $t0, i9
	lw $t0, i9 #STORE INT
	nop
	sw $t0, computeSum_4.doubleSum_var
	l.s $f0, main_0.globalFloat_var #LOAD FLOAT
	nop
	s.s $f0, f1
	lw $t0, computeSum_4.sum_var #LOAD INT
	nop
	sw $t0, i10
	lw $t0, i10 #CONVERT INT TO FLOAT
	nop
	mtc1 $t0, $f0
	cvt.s.w $f0, $f0
	s.s $f0, f2
	l.s $f0, f1 #ADD FLOAT
	nop
	l.s $f1, f2
	nop
	add.s $f0, $f0, $f1
	s.s $f0, f3
	l.s $f0, f3 #STORE FLOAT
	nop
	s.s $f0, main_0.globalFloat_var
	lw $t0, computeSum_4.doubleSum_var #LOAD INT
	nop
	sw $t0, i11
	li $t0, 50 #ASSIGN INT VALUE
	sw $t0, i12
	lw $t0, i11 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i12
	nop
	sgt $t2, $t0, $t1
	sw $t2, i13
	lw $t0, i13 #IF FALSE
	nop
	beq $t0, $zero, L0
	nop
	lw $t0, main_0.globalInt_var #LOAD INT
	nop
	sw $t0, i14
	li $t0, 10 #ASSIGN INT VALUE
	sw $t0, i15
	lw $t0, i14 #ADD INT
	nop
	lw $t1, i15
	nop
	add $t0, $t0, $t1
	sw $t0, i16
	lw $t0, i16 #STORE INT
	nop
	sw $t0, main_0.globalInt_var
	li $t0, 72 #ASSIGN CHAR VALUE
	la $t1, c1
	sb $t0, 0($t1)
	lb $t0, c1 #LOAD CHAR
	nop
	la $t1, printChar_2.value_var
	sb $t0, 0($t1)
	jal printChar_func #FUNCTION CALL
	nop
	j L1 #GOTO
	nop
L0:
	lw $t0, main_0.globalInt_var #LOAD INT
	nop
	sw $t0, i17
	li $t0, 5 #ASSIGN INT VALUE
	sw $t0, i18
	lw $t0, i17 #SUBTRACT INT
	nop
	lw $t1, i18
	nop
	sub $t0, $t0, $t1
	sw $t0, i19
	lw $t0, i19 #STORE INT
	nop
	sw $t0, main_0.globalInt_var
	li $t0, 76 #ASSIGN CHAR VALUE
	la $t1, c2
	sb $t0, 0($t1)
	lb $t0, c2 #LOAD CHAR
	nop
	la $t1, printChar_2.value_var
	sb $t0, 0($t1)
	jal printChar_func #FUNCTION CALL
	nop
L1:
	lw $t0, computeSum_4.doubleSum_var #LOAD INT
	nop
	sw $t0, i20
	lw $t0, i20 #LOAD INT
	nop
	sw $t0, printInt_1.value_var
	jal printInt_func #FUNCTION CALL
	nop
	lw $t0, computeSum_4.doubleSum_var #LOAD INT
	nop
	sw $t0, i21
	lw $t0, i21 #STORE INT
	nop
	sw $t0, returnInt
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
displayResult_func:
	addi $sp, $sp, -4 #FUNCTION START
	sw $ra, 0($sp)
	lw $t0, displayResult_5.result_var #LOAD INT
	nop
	sw $t0, i22
	lw $t0, i22 #STORE INT
	nop
	sw $t0, displayResult_5.localCopy_var
	lw $t0, displayResult_5.localCopy_var #LOAD INT
	nop
	sw $t0, i23
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i24
	lw $t0, i23 #ADD INT
	nop
	lw $t1, i24
	nop
	add $t0, $t0, $t1
	sw $t0, i25
	lw $t0, i25 #STORE INT
	nop
	sw $t0, displayResult_5.localCopy_var
	lw $t0, displayResult_5.localCopy_var #LOAD INT
	nop
	sw $t0, i26
	li $t0, 2 #ASSIGN INT VALUE
	sw $t0, i27
	li $t0, 0 #ASSIGN INT VALUE
	sw $t0, i29
	lw $t0, i28 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i29
	nop
	seq $t2, $t0, $t1
	sw $t2, i30
	lw $t0, i30 #IF FALSE
	nop
	beq $t0, $zero, L2
	nop
	li $t0, 69 #ASSIGN CHAR VALUE
	la $t1, c3
	sb $t0, 0($t1)
	lb $t0, c3 #STORE CHAR
	nop
	la $t1, main_0.globalChar_var
	sb $t0, 0($t1)
	j L3 #GOTO
	nop
L2:
	li $t0, 79 #ASSIGN CHAR VALUE
	la $t1, c4
	sb $t0, 0($t1)
	lb $t0, c4 #STORE CHAR
	nop
	la $t1, main_0.globalChar_var
	sb $t0, 0($t1)
L3:
	lb $t0, main_0.globalChar_var #LOAD CHAR
	nop
	la $t1, c5
	sb $t0, 0($t1)
	lb $t0, c5 #LOAD CHAR
	nop
	la $t1, printChar_2.value_var
	sb $t0, 0($t1)
	jal printChar_func #FUNCTION CALL
	nop
	lw $t0, displayResult_5.localCopy_var #LOAD INT
	nop
	sw $t0, i31
	lw $t0, i31 #STORE INT
	nop
	sw $t0, main_0.globalInt_var
	lw $t0, displayResult_5.localCopy_var #LOAD INT
	nop
	sw $t0, i32
	li $t0, 3 #ASSIGN INT VALUE
	sw $t0, i33
	lw $t0, i32 #MULTIPLY INT
	nop
	lw $t1, i33
	nop
	mul $t0, $t0, $t1
	sw $t0, i34
	lw $t0, i34 #STORE INT
	nop
	sw $t0, displayResult_5.localCopy_var
	lw $t0, displayResult_5.localCopy_var #LOAD INT
	nop
	sw $t0, i35
	lw $t0, i35 #LOAD INT
	nop
	sw $t0, printInt_1.value_var
	jal printInt_func #FUNCTION CALL
	nop
	li $t0, 45 #ASSIGN CHAR VALUE
	la $t1, c6
	sb $t0, 0($t1)
	la $t1, c6 #WRITE CHAR
	lb $t0, 0($t1)
	nop
	move $a0, $t0
	li $v0, 11
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
multiply_func:
	addi $sp, $sp, -4 #FUNCTION START
	sw $ra, 0($sp)
	lw $t0, multiply_6.x_var #LOAD INT
	nop
	sw $t0, i36
	lw $t0, multiply_6.y_var #LOAD INT
	nop
	sw $t0, i37
	lw $t0, i36 #MULTIPLY INT
	nop
	lw $t1, i37
	nop
	mul $t0, $t0, $t1
	sw $t0, i38
	lw $t0, i38 #STORE INT
	nop
	sw $t0, multiply_6.product_var
	lw $t0, multiply_6.x_var #LOAD INT
	nop
	sw $t0, i39
	lw $t0, multiply_6.x_var #LOAD INT
	nop
	sw $t0, i40
	lw $t0, i39 #MULTIPLY INT
	nop
	lw $t1, i40
	nop
	mul $t0, $t0, $t1
	sw $t0, i41
	lw $t0, i41 #STORE INT
	nop
	sw $t0, multiply_6.square_var
	lw $t0, multiply_6.product_var #LOAD INT
	nop
	sw $t0, i42
	lw $t0, multiply_6.square_var #LOAD INT
	nop
	sw $t0, i43
	lw $t0, i42 #ADD INT
	nop
	lw $t1, i43
	nop
	add $t0, $t0, $t1
	sw $t0, i44
	lw $t0, i44 #STORE INT
	nop
	sw $t0, multiply_6.tempResult_var
	lw $t0, multiply_6.tempResult_var #LOAD INT
	nop
	sw $t0, i45
	li $t0, 50 #ASSIGN INT VALUE
	sw $t0, i46
	lw $t0, i45 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i46
	nop
	sgt $t2, $t0, $t1
	sw $t2, i47
	lw $t0, i47 #IF FALSE
	nop
	beq $t0, $zero, L4
	nop
	l.s $f0, main_0.globalFloat_var #LOAD FLOAT
	nop
	s.s $f0, f4
	l.s $f0, float_const_1 #ASSIGN FLOAT VALUE
	nop
	s.s $f0, f5
	l.s $f0, f4 #DIVIDE FLOAT
	nop
	l.s $f1, f5
	nop
	div.s $f0, $f0, $f1
	s.s $f0, f6
	l.s $f0, f6 #STORE FLOAT
	nop
	s.s $f0, main_0.globalFloat_var
	l.s $f0, main_0.globalFloat_var #LOAD FLOAT
	nop
	s.s $f0, f7
	l.s $f0, f7 #LOAD FLOAT
	nop
	s.s $f0, printFloat_3.value_var
	jal printFloat_func #FUNCTION CALL
	nop
L4:
	lw $t0, multiply_6.tempResult_var #LOAD INT
	nop
	sw $t0, i48
	lw $t0, i48 #LOAD INT
	nop
	sw $t0, printInt_1.value_var
	jal printInt_func #FUNCTION CALL
	nop
	lw $t0, multiply_6.tempResult_var #LOAD INT
	nop
	sw $t0, i49
	lw $t0, i49 #STORE INT
	nop
	sw $t0, returnInt
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
factorial_func:
	addi $sp, $sp, -4 #FUNCTION START
	sw $ra, 0($sp)
	lw $t0, factorial_7.n_var #LOAD INT
	nop
	sw $t0, i50
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i51
	lw $t0, i50 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i51
	nop
	sle $t2, $t0, $t1
	sw $t2, i52
	lw $t0, i52 #IF FALSE
	nop
	beq $t0, $zero, L5
	nop
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i53
	lw $t0, i53 #LOAD INT
	nop
	sw $t0, printInt_1.value_var
	jal printInt_func #FUNCTION CALL
	nop
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i54
	lw $t0, i54 #STORE INT
	nop
	sw $t0, returnInt
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
	j L6 #GOTO
	nop
L5:
	lw $t0, factorial_7.n_var #LOAD INT
	nop
	sw $t0, i55
	lw $t0, factorial_7.n_var #LOAD INT
	nop
	sw $t0, i56
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i57
	lw $t0, i56 #SUBTRACT INT
	nop
	lw $t1, i57
	nop
	sub $t0, $t0, $t1
	sw $t0, i58
	lw $t0, i58 #LOAD INT
	nop
	sw $t0, factorial_7.n_var
	jal factorial_func #FUNCTION CALL
	nop
	lw $t0, i55 #MULTIPLY INT
	nop
	lw $t1, returnInt
	nop
	mul $t0, $t0, $t1
	sw $t0, i59
	lw $t0, i59 #STORE INT
	nop
	sw $t0, factorial_7.result_var
	lw $t0, factorial_7.result_var #LOAD INT
	nop
	sw $t0, i60
	lw $t0, i60 #LOAD INT
	nop
	sw $t0, printInt_1.value_var
	jal printInt_func #FUNCTION CALL
	nop
	lw $t0, factorial_7.result_var #LOAD INT
	nop
	sw $t0, i61
	lw $t0, i61 #STORE INT
	nop
	sw $t0, returnInt
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
L6:
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
isPrime_func:
	addi $sp, $sp, -4 #FUNCTION START
	sw $ra, 0($sp)
	lw $t0, isPrime_8.n_var #LOAD INT
	nop
	sw $t0, i62
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i63
	lw $t0, i62 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i63
	nop
	sle $t2, $t0, $t1
	sw $t2, i64
	lw $t0, i64 #IF FALSE
	nop
	beq $t0, $zero, L7
	nop
	li $t0, 0 #ASSIGN INT VALUE
	sw $t0, i65
	lw $t0, i65 #STORE INT
	nop
	sw $t0, returnInt
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
L7:
	li $t0, 2 #ASSIGN INT VALUE
	sw $t0, i66
	lw $t0, i66 #STORE INT
	nop
	sw $t0, isPrime_8.i_var
L8:
	lw $t0, isPrime_8.i_var #LOAD INT
	nop
	sw $t0, i67
	lw $t0, isPrime_8.n_var #LOAD INT
	nop
	sw $t0, i68
	lw $t0, i67 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i68
	nop
	slt $t2, $t0, $t1
	sw $t2, i69
	lw $t0, i69 #IF FALSE
	nop
	beq $t0, $zero, L9
	nop
	lw $t0, isPrime_8.n_var #LOAD INT
	nop
	sw $t0, i70
	lw $t0, isPrime_8.i_var #LOAD INT
	nop
	sw $t0, i71
	li $t0, 0 #ASSIGN INT VALUE
	sw $t0, i73
	lw $t0, i72 #LOAD INT FOR RELATIONAL OP
	nop
	lw $t1, i73
	nop
	seq $t2, $t0, $t1
	sw $t2, i74
	lw $t0, i74 #IF FALSE
	nop
	beq $t0, $zero, L10
	nop
	li $t0, 78 #ASSIGN CHAR VALUE
	la $t1, c7
	sb $t0, 0($t1)
	lb $t0, c7 #LOAD CHAR
	nop
	la $t1, printChar_2.value_var
	sb $t0, 0($t1)
	jal printChar_func #FUNCTION CALL
	nop
	li $t0, 0 #ASSIGN INT VALUE
	sw $t0, i75
	lw $t0, i75 #STORE INT
	nop
	sw $t0, returnInt
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
L10:
	lw $t0, isPrime_8.i_var #LOAD INT
	nop
	sw $t0, i76
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i77
	lw $t0, i76 #ADD INT
	nop
	lw $t1, i77
	nop
	add $t0, $t0, $t1
	sw $t0, i78
	lw $t0, i78 #STORE INT
	nop
	sw $t0, isPrime_8.i_var
	j L8 #GOTO
	nop
L9:
	li $t0, 80 #ASSIGN CHAR VALUE
	la $t1, c8
	sb $t0, 0($t1)
	lb $t0, c8 #LOAD CHAR
	nop
	la $t1, printChar_2.value_var
	sb $t0, 0($t1)
	jal printChar_func #FUNCTION CALL
	nop
	li $t0, 1 #ASSIGN INT VALUE
	sw $t0, i79
	lw $t0, i79 #STORE INT
	nop
	sw $t0, returnInt
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop
	lw $ra, 0($sp) #RETURN
	nop
	addi $sp, $sp, 4
	jr $ra
	nop

.data
   newline: .asciiz "\n"
   returnInt: .word 0
   returnFloat: .float 0.0
   returnChar: .byte 0
	computeSum_4.temp_var: .word 0
	computeSum_4.sum_var: .word 0
	computeSum_4.doubleSum_var: .word 0
	computeSum_4.a_var: .word 0
	computeSum_4.b_var: .word 0
	multiply_6.tempResult_var: .word 0
	multiply_6.square_var: .word 0
	multiply_6.x_var: .word 0
	multiply_6.y_var: .word 0
	multiply_6.product_var: .word 0
	printFloat_3.value_var: .float 0.0
	displayResult_5.localCopy_var: .word 0
	displayResult_5.result_var: .word 0
	main_0.i_var: .word 0
	main_0.multiply_func: .word 0
	main_0.factorial_func: .word 0
	main_0.temp_var: .word 0

	main_0.globalInt_var: .word 0
	main_0.result_var: .word 0

	main_0.localFloat_var: .float 0.0
	main_0.globalFloat_var: .float 0.0

	main_0.globalChar_var: .byte 'U'
	main_0.localInt_var: .word 0

	main_0.isPrime_func: .word 0
	main_0.computeSum_func: .word 0
	main_0.boolFlag_var: .word 0
	isPrime_8.i_var: .word 0
	isPrime_8.n_var: .word 0
	printInt_1.value_var: .word 0
	printChar_2.value_var: .byte 'U'
	factorial_7.n_var: .word 0
	factorial_7.result_var: .word 0
	i0: .word 0
	i1: .word 0
	i2: .word 0
	i3: .word 0
	i4: .word 0
	i5: .word 0
	i6: .word 0
	i7: .word 0
	i8: .word 0
	i9: .word 0
	i10: .word 0
	i11: .word 0
	i12: .word 0
	i13: .word 0
	i14: .word 0
	i15: .word 0
	i16: .word 0
	i17: .word 0
	i18: .word 0
	i19: .word 0
	i20: .word 0
	i21: .word 0
	i22: .word 0
	i23: .word 0
	i24: .word 0
	i25: .word 0
	i26: .word 0
	i27: .word 0
	i28: .word 0
	i29: .word 0
	i30: .word 0
	i31: .word 0
	i32: .word 0
	i33: .word 0
	i34: .word 0
	i35: .word 0
	i36: .word 0
	i37: .word 0
	i38: .word 0
	i39: .word 0
	i40: .word 0
	i41: .word 0
	i42: .word 0
	i43: .word 0
	i44: .word 0
	i45: .word 0
	i46: .word 0
	i47: .word 0
	i48: .word 0
	i49: .word 0
	i50: .word 0
	i51: .word 0
	i52: .word 0
	i53: .word 0
	i54: .word 0
	i55: .word 0
	i56: .word 0
	i57: .word 0
	i58: .word 0
	i59: .word 0
	i60: .word 0
	i61: .word 0
	i62: .word 0
	i63: .word 0
	i64: .word 0
	i65: .word 0
	i66: .word 0
	i67: .word 0
	i68: .word 0
	i69: .word 0
	i70: .word 0
	i71: .word 0
	i72: .word 0
	i73: .word 0
	i74: .word 0
	i75: .word 0
	i76: .word 0
	i77: .word 0
	i78: .word 0
	i79: .word 0
	i80: .word 0
	i81: .word 0
	i82: .word 0
	i83: .word 0
	i84: .word 0
	i85: .word 0
	i86: .word 0
	i87: .word 0
	i88: .word 0
	i89: .word 0
	i90: .word 0
	i91: .word 0
	i92: .word 0
	i93: .word 0
	i94: .word 0
	i95: .word 0
	i96: .word 0
	i97: .word 0
	i98: .word 0
	i99: .word 0
	i100: .word 0
	i101: .word 0
	i102: .word 0
	i103: .word 0
	i104: .word 0
	i105: .word 0
	i106: .word 0
	i107: .word 0
	i108: .word 0
	i109: .word 0
	i110: .word 0
	i111: .word 0
	i112: .word 0
	i113: .word 0
	i114: .word 0
	i115: .word 0
	i116: .word 0
	i117: .word 0
	i118: .word 0
	i119: .word 0
	i120: .word 0
	i121: .word 0
	i122: .word 0
	i123: .word 0
	i124: .word 0
	i125: .word 0
	i126: .word 0
	i127: .word 0
	i128: .word 0
	i129: .word 0
	i130: .word 0
	i131: .word 0
	i132: .word 0
	i133: .word 0
	i134: .word 0
	i135: .word 0
	i136: .word 0
	i137: .word 0
	i138: .word 0
	i139: .word 0
	i140: .word 0
	i141: .word 0
	i142: .word 0
	f0: .float 0.0
	f1: .float 0.0
	f2: .float 0.0
	f3: .float 0.0
	f4: .float 0.0
	f5: .float 0.0
	f6: .float 0.0
	f7: .float 0.0
	f8: .float 0.0
	f9: .float 0.0
	c0: .byte 0
	c1: .byte 0
	c2: .byte 0
	c3: .byte 0
	c4: .byte 0
	c5: .byte 0
	c6: .byte 0
	c7: .byte 0
	c8: .byte 0
	c9: .byte 0
	c10: .byte 0
	float_const_0: .float 3.700000
	float_const_1: .float 2.000000
