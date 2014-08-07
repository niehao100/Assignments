0x80000004
#保护现场，sp默认从0x000003fc开始
addi $sp,$sp,-12
sw $t0,0($sp)
sw $t1,4($sp)
sw $t2,8($sp)
#中断到来时
lw $at,8($a0)
andi $at,$at,0xfff9
sw $at,8($a0)

#决定点亮哪一位，k1作为计数器
addi $k1,$k1,1
andi $k1,$k1,0b11
addi $t0,$zero,0x3
beq $t0,$k1,light1
addi $t0,$t0,-1
beq $t0,$k1,light2
addi $t0,$t0,-1
beq $t0,$k1,light3
addi $t1,$a2,0
addi $t2,$zero,0x700
j lighted
light3:
srl $t1,$a2,4
addi $t2,$zero,0xb00
j lighted
light2:
addi $t1,$a1,0
addi $t2,$zero,0xd00
j lighted
light1:
srl $t1,$a1,4
addi $t2,$zero,0xe00

lighted:
andi $t1,$t1,0xF
addi $t0,$zero,0xf   #软件译码t1
beq $t0,$t1,getf
addi $t0,$t0,-1
beq $t0,$t1,gete
addi $t0,$t0,-1
beq $t0,$t1,getd
addi $t0,$t0,-1
beq $t0,$t1,getc
addi $t0,$t0,-1
beq $t0,$t1,getb
addi $t0,$t0,-1
beq $t0,$t1,geta
addi $t0,$t0,-1
beq $t0,$t1,get9
addi $t0,$t0,-1
beq $t0,$t1,get8
addi $t0,$t0,-1
beq $t0,$t1,get7
addi $t0,$t0,-1
beq $t0,$t1,get6
addi $t0,$t0,-1
beq $t0,$t1,get5
addi $t0,$t0,-1
beq $t0,$t1,get4
addi $t0,$t0,-1
beq $t0,$t1,get3
addi $t0,$t0,-1
beq $t0,$t1,get2
addi $t0,$t0,-1
beq $t0,$t1,get1
addi $t0,$t2,0b11000000
j decoded
get1:
addi $t0,$t2,0b11111001
j decoded
get2:
addi $t0,$t2,0b10100100
j decoded
get3:
addi $t0,$t2,0b10110000
j decoded
get4:
addi $t0,$t2,0b10011001
j decoded
get5:
addi $t0,$t2,0b10010010
j decoded
get6:
addi $t0,$t2,0b10000010
j decoded
get7:
addi $t0,$t2,0b11111000
j decoded
get8:
addi $t0,$t2,0b10000000
j decoded
get9:
addi $t0,$t2,0b10010000
j decoded
geta:
addi $t0,$t2,0b10001000
j decoded
getb:
addi $t0,$t2,0b10000011
j decoded
getc:
addi $t0,$t2,0b11000110
j decoded
getd:
addi $t0,$t2,0b10100001
j decoded
gete:
addi $t0,$t2,0b10000110
j decoded
getf:
addi $t0,$t2,0b10001110
decoded:
sw $t0,0x14($a0)


addi $t0,$zero,2
or $at,$at,$t0
sw $at,8($a0)

lw $t0,0($sp)
lw $t1,4($sp)
lw $t2,8($sp)
addi $sp,$sp,12
addi $k0,$k0,-4
jr $k0
