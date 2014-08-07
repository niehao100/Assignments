0
lui $a0,0x4000  #0 0
polling1:
lw $t0,0x20($a0)    #读取串口状态1 4
lw $t1,0x1c($a0)    #读取串口接收数据2 8
andi $t0,$t0,0b1000 #掩码接收状态3 c
beq $zero,$t0,polling1   #继续轮询，如果没有收到完整数据4 10
polling2:
lw $t0,0x20($a0)    #读取串口状态5 14
lw $t2,0x1c($a0)    #读取串口接收数据6 18
andi $t0,$t0,0b1000 #掩码接收状态7 1c
beq $zero,$t0,polling2   #继续轮询，如果没有收到完整数据8 20
addi $a1,$t1,0  #9 24
addi $a2,$t2,0  #10 28
#至此两个操作数分别存在$a1和$a2中，启动定时器
sw $zero,8($a0) #关闭定时器，TCON写入0  11 2c
nor $t0,$zero,$zero #12 30
addi $t1,$zero,10000    #定时的周期数13 34
subu $t1,$t0,$t1    #t0中为TH应该设定的值,t1中为TL=0xffffffff14 38
sw $t1,0($a0)   #写入TH15 3c
sw $t0,4($a0)   #写入TL16 40
addi $t0,$zero,3    #17 44
sw $t0,8($a0)   #启动定时器，TCON写入3 18 48
#至此定时器开始工作，每隔固定周期将通过八段数码管输出a1和a2中的数
addi $t1,$a1,0  #19 4c
addi $t2,$a2,0  #20 50
begin:
slt $t0,$t1,$t2 #21 54
bne $t0,$zero,continue  #22 58
addi $t3,$t2,0  #23 5c
addi $t2,$t1,0  #24 60
addi $t1,$t3,0  #25 64
continue:
beq $t1,$t2,end #26 68
beq $t1,$zero,end   #27 6c
sub $t2,$t2,$t1 #28 70
j begin #29 74
end:
addi $v0,$t2,0  #30 78
#辗转相除法得到最大公约数v0
sw $v0,0xc($a0) #31 7c
sw $v0,0x18($a0)    #32 80
j polling1  #33 84
