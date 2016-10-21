#!/usr/bin/python
#coding:utf-8
import  copy
a=[1,2,3,4,['a','b','c']]
# 浅拷贝
c=a
# 浅拷贝，内层地址空间相同
b=copy.copy(a)
print  b
# 深拷贝
d=copy.deepcopy(a)
print  d
print  id(a[4])
print  id(c[4])
print  id(b[4])
print  id(d[4])