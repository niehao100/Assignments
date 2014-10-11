#!/usr/bin/python2.7
# coding=utf8
import sys
from itertools import combinations

#读入
while True:
    try:
        n = int(raw_input('请输入变量个数n:'))
        if n>10:
            print '变量个数不能大于10'
        elif n<1:
            print '变量个数不能小于1'
        else:
            break
    except ValueError:
        print '非法输入'

while True:
    try:
        m_set = set(input('请以Python数组形式输入最小项，例如[1,2,3]:'))
        if len(m_set)>2**n:
            print '最小项数目不能大于'+str(2**n)
        else:
            good = True
            for m in m_set:
                if m<0 or m>2**n:
                    print '输入超出范围'
                    good=False
                    break
            if good:
                break
    except ValueError:
        print '非法输入'
    except TypeError:
        print '非法输入'
    except SyntaxError:
        print '非法输入'
    except NameError:
        print '非法输入'

while True:
    try:
        d_set = set(input('请以Python数组形式输入无关项，例如[5,6]:'))
        if len(d_set)>2**n-len(m_set):
            print '最小项数目不能大于'+str(2**n-len(m_se))
        elif d_set & m_set:
            print '无关项不能与最小项重复'
        else:
            good = True
            for d in d_set:
                if d<0 or d>2**n:
                    print '输入超出范围'
                    good=False
                    break
            if good:
                break
    except ValueError:
        print '非法输入'
    except TypeError:
        print '非法输入'
    except SyntaxError:
        print '非法输入'
    except NameError:
        print '非法输入'

#预处理，把标号转为二进制表示
m_and_d_dict={}
m_list=[]
for m in m_set:
    m=bin(m)[2:]
    m='0'*(n-len(m))+m
    m_list.append(m)
    if m.count('1') in m_and_d_dict:
        m_and_d_dict[m.count('1')].append([m,0])
    else:
        m_and_d_dict[m.count('1')]=[[m,0]]
d_list=[]
for d in d_set:
    d=bin(d)[2:]
    d='0'*(n-len(d))+d
    d_list.append(d)
    if d.count('1') in m_and_d_dict:
        m_and_d_dict[d.count('1')].append([d,0])
    else:
        m_and_d_dict[d.count('1')]=[[d,0]]

#合并蕴含项
prime_implicants=set()
implicants={}
implicants[0]=m_and_d_dict
for column in range(0,n+1): #column是QM算法的列数，也是-的个数
    if column<n:
        implicants[column+1]={}
    for i in range(0,n-column+1):   #i是1的个数
        if not i in implicants[column]:
            continue
        for current in implicants[column][i]:   #current是1有i个的各个蕴含项
            if i!=n-column and i+1 in implicants[column]:   #1已经满了就只判断是否本原蕴含项
                for next in implicants[column][i+1]:    #next是可能匹配的蕴含项
                    match_count=0
                    unmatch_position=0
                    for k in range(0,n):
                        if current[0][k] == next[0][k]:
                            match_count+=1
                        else:
                            unmatch_position=k
                    if match_count == n-1:  #可以合并
                        current[1]=1  #标记为非本原蕴含项
                        next[1]=1
                        if not i in implicants[column+1]:
                            implicants[column+1][i]=[]
                        implicants[column+1][i].append([current[0][0:unmatch_position]+'-'+current[0][unmatch_position+1:],0])   #将合并以后的蕴含项加入下一列
        for j in implicants[column][i]: #寻找本原蕴含项
            if j[1]==0:
                j[1]=2  #标记为本原蕴含项
                prime_implicants|=set([j[0]])

#覆盖
cover={}
essential_prime_implicants={}
for prime_implicant in prime_implicants:
    cover[prime_implicant]=[]
    for m in m_list:
        do_cover=True
        for i in range(0,n):    #匹配是否覆盖
            if prime_implicant[i]=='-':
                continue
            if prime_implicant[i]!=m[i]:
                do_cover=False
                break
        if do_cover:
            if not m in essential_prime_implicants:
                essential_prime_implicants[m]=[]
            essential_prime_implicants[m].append(prime_implicant)
            cover[prime_implicant].append(m)

essential_prime_implicant=set()
for item in essential_prime_implicants.keys():
    if len(essential_prime_implicants[item])==1:
        essential_prime_implicant|=set(essential_prime_implicants[item])

covered=set()
for item in essential_prime_implicant:
    covered|=set(cover[item])

m_set=set(m_list)
selected=essential_prime_implicant
done=False
for n in range(0,len(prime_implicants)-len(essential_prime_implicant)+1):
    for items in combinations(prime_implicants-essential_prime_implicant,n):
        try_cover=covered.copy()
        for item in items:
            try_cover|=set(cover[item])

        if len(m_set)==len(try_cover):
            selected|=set(items)
            done=True
    if done:
        break
print >>sys.stderr, str(selected)[5:-2].replace("'",'').replace(' ','')