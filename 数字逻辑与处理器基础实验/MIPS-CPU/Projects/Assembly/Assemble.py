#!/usr/bin/python
# coding=utf-8
import re
import sys
import time

# 不知道为什么想到Transformers
delay = 0.05
if True:
    sys.stderr.write("Autobots")
    sys.stderr.flush()
    time.sleep(delay*8)
    for i in range(0,6):
        sys.stderr.write("\010 \010")
        sys.stderr.flush()
        time.sleep(delay)
    sys.stderr.write("\rM")
    sys.stderr.flush()
    time.sleep(delay)
    sys.stderr.write("I")
    sys.stderr.flush()
    time.sleep(delay)
    sys.stderr.write("P")
    sys.stderr.flush()
    time.sleep(delay)
    sys.stderr.write("S ")
    sys.stderr.flush()
    time.sleep(delay)
    sys.stderr.write("assemble!\n")
# 以下为正式的代码

def BinaryR(op,rs,rt,rd,shamt,funct):
    return bin(eval(op))[2:].zfill(6)[0:6]+bin(eval(rs))[2:].zfill(5)[0:5]+bin(eval(rt))[2:].zfill(5)[0:5]+bin(eval(rd))[2:].zfill(5)[0:5]+bin(eval(shamt))[2:].zfill(5)[0:5]+bin(eval(funct))[2:].zfill(6)[0:6]+'\n'
def BinaryI(op,rs,rt,imm):
    return bin(eval(op))[2:].zfill(6)[0:6]+bin(eval(rs))[2:].zfill(5)[0:5]+bin(eval(rt))[2:].zfill(5)[0:5]+bin(eval(imm))[2:].zfill(16)[0:16]+'\n'
def BinaryJ(op,target):
    return bin(eval(op))[2:].zfill(6)[0:6]+bin(eval(target))[2:].zfill(24)[0:24]+'00\n'

labels = {}         #键为标号名，值为instructions的索引
instructions = []   #经过预处理以后的顺序储存的指令文本
lines = sys.stdin.readlines()
addr0 = int(eval(lines[0])/4)
for line in lines[1:]:
    line = line.replace(':',': ').strip()
    if len(line)==0 or line[0]=='#' :
        continue
    if(line.find('#')<0):
        end = len(line)
    else:
        end = line.find('#')
    line = re.split(r'[ ,]',line[0:end].strip())
    line = [i\
            .replace('$zero','$0')\
            .replace('$at',  '$1')\
            .replace('$v0','$2')\
            .replace('$v1','$3')\
            .replace('$a0','$4')\
            .replace('$a1','$5')\
            .replace('$a2','$6')\
            .replace('$a3','$7')\
            .replace('$t0','$8')\
            .replace('$t1','$9')\
            .replace('$t2','$10')\
            .replace('$t3','$11')\
            .replace('$t4','$12')\
            .replace('$t5','$13')\
            .replace('$t6','$14')\
            .replace('$t7','$15')\
            .replace('$s0','$16')\
            .replace('$s1','$17')\
            .replace('$s2','$18')\
            .replace('$s3','$19')\
            .replace('$s4','$20')\
            .replace('$s5','$21')\
            .replace('$s6','$22')\
            .replace('$s7','$23')\
            .replace('$t8','$24')\
            .replace('$t9','$25')\
            .replace('$k0','$26')\
            .replace('$k1','$27')\
            .replace('$gp','$28')\
            .replace('$sp','$29')\
            .replace('$fp','$30')\
            .replace('$ra','$31')\
            for i in line if len(i)]
    if line[0][-1]==':':
        labels[line[0][0:-1]] = len(instructions)
        if len(line)==1:
            continue
        else:
            line = line[1:]
    instructions.append(line)

binary = ''
nu = 0
for i in instructions:
    nu += 1
    if i[0]=='lw' or i[0]=='sw':
        op = {'lw':'0x23','sw':'0x2b'}[i[0]]
        rs = i[2][i[2].find('(')+2:i[2].find(')')]
        rt = i[1][1:]
        offset = i[2][0:i[2].find('(')]
        binary += BinaryI(op,rs,rt,offset)
    elif i[0] in {'add','addu','sub','subu','and','or','xor','nor','slt','sll','srl','sra'}:
        op = '0'
        rd = i[1][1:]
        rs = i[2][1:]
        rt = i[3][1:]
        shamt = '0'
        if i[0] in {'sll','srl','sra'}:
            shamt = i[3]
            rt = i[2][1:]
            rs = '0'
        funct = {'sll':'0x0',\
                'srl':'0x2',\
                'sra':'0x3',\
                'add':'0x20',\
                'addu':'0x21',\
                'sub':'0x22',\
                'subu':'0x23',\
                'and':'0x24',\
                'or':'0x25',\
                'xor':'0x26',\
                'nor':'0x27',\
                'slt':'0x2a'\
                }[i[0]]
        binary += BinaryR(op,rs,rt,rd,shamt,funct)
    elif i[0]=='lui':
        op = '0xf'
        rt = i[1][1:]
        imm = i[2]
        binary += BinaryI(op,'0',rt,imm)
    elif i[0] in {'addi','addiu','slti','sltiu','andi'}:
        op = {'addi':'0x8','addiu':'0x9','slti':'0xa','sltiu':'0xb','andi':'0xc'}[i[0]]
        rs = i[2][1:]
        rt = i[1][1:]
        imm = eval(i[3])
        imm = str(imm>0 and imm or imm&0xffff)
        binary += BinaryI(op,rs,rt,imm)
    elif i[0] in {'beq','bne'}:
        op = {'beq':'4','bne':'5'}[i[0]]
        rs = i[1][1:]
        rt = i[2][1:]
        offset = labels[i[3]]-nu
        offset = str(offset>0 and offset or offset&0xffff)
        binary += BinaryI(op,rs,rt,offset)
    elif i[0] in {'bltz','blez','bgtz'}:
        op = {'bltz':'1','blez':'6','bgtz':'7'}[i[0]]
        rs = i[1][1:]
        offset = labels[i[2]]-nu
        offset = str(offset>0 and offset or offset&0xffff)
        binary += BinaryI(op,rs,'0',offset)
    elif i[0] in {'j','jal'}:
        op = {'j':'2','jal':'3'}[i[0]]
        target = str((labels[i[1]]+addr0)%0x1000000)
        binary += BinaryJ(op,target)
    elif i[0]=='jr':
        op = '0'
        rs = i[1][1:]
        binary += 3*(32*'0'+'\n')
        binary += BinaryR(op,rs,'0','0','0','8')
    elif i[0]=='jalr':
        op = '0'
        rs = i[1][1:]
        rd = i[2][1:]
        binary += 3*(32*'0'+'\n')
        binary += BinaryR(op,rs,'0',rd,'0','9')
    elif i[0]=='nop':
        binary += 32*'0'+'\n'
    else:
        for label,n in labels.items():
            if(n+1==nu):
                binary += label+': '
        binary += i[0]+' '+','.join(i[1:])+'\n'
print(addr0)
print(binary)


