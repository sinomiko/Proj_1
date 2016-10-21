#!/usr/bin/python
#coding=utf-8

from  __future__ import  division
a=(1,0)
print  type(a)
print  id(a)

str_a="abc"*3
print str_a

b=[1,2]
print type(b)
b[1]=3
b.append('miko')
b.remove(1)
b.reverse()
b.pop(0)
print  b


c={1:"jack",2:"lucy"}

for k,v in c.items():
    print k,v
else:
    print "ending"#正常结束


for i in range(1,10):
    if i==2:
        pass
    elif i==4:
        continue
    elif i==7:
       # exit()
        pass
    print i

def fun1(x,y="miko"):
    global  str_a;
    str_a="i do"
    print  x,y
    print  str_a


#if __name__ == '__main__':
fun1(1)
print  str_a

l=range(1,5)
def f2(x,y):
    return x*y

print reduce(f2,l)

f2=lambda x,y:x*y
print reduce(f2,l)

def add(x,y):
    return  x+y

def sub(x,y):
    return x-y

def mul(x,y):
    return  x*y

def div(x,y):
    return x/y
# 利用字典实现switch
operator={"+":add,"-":sub,"*":mul,"/":div}
# print operator["+"](3,2)
def f(x,o,y):
    print  operator.get(o)(x,y)

f(3,"+",2)

help(divmod)

#
#  sum,min,max ,len,divmod,pow,round
# callable(),isinstance(),cmp(),range(),xrange()

print  callable(f)

print type(operator)==type({})

a=xrange(10)
print  a

#类型转化
#  type(),int(),long(),float(),complex()
# str(),list(),tuple(),hex(),oct(),chr(),ord()

#string函数
# str.capitalize()  #首字母大写
# str.replace()
# str.split()

s="hello world"
print  s.capitalize()
print  s.replace('o','a',1)
# 序列处理函数
# filter(),zip(),map(),reduce()
def f(x):
    if x>5:
        return  True

l=range(10)
print  filter(f,l)

name=["abc1","abc2","abc3"]
age=[1,2,3]
tel=["133","138","183"]
print zip(name,age,tel)

print map(None,name,age,tel)

test=[2,1]
print zip(name,age,tel,test)
print map(None,name,age,tel,test)
# map不足补None，zip按最少的合并
def mf(x,y):
    return  x*y
test.insert(2,0)
print map(mf,age,test)
# 求和
def rf(x,y):
    return  x+y
print  reduce(rf,range(101))
print reduce(lambda x,y:x+y,range(101))
print  filter(lambda x:x%2==0,range(101))