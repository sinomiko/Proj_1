#!/usr/bin/python
#coding:utf-8
import  re
regx=r"\d{3,4}-?\d{8}"
reg=re.compile(regx,re.I)
print reg
print  reg.findall("010-123456789")

x=reg.match("010-123456789")

print x.group()
print  reg.search("010-123456789")

print  reg.finditer("010-123456789")
print  re.sub(r"c..t","python","csvt caat cvvt ccc")


print  re.subn(r"c..t","python","csvt caat cvvt ccc")


s="123*345-567+"
print  re.split(r"[\+\-\*]",s)

print dir(re)

tel=r"""
\d{3,4}
-?
\d{8}
"""

# re.X正则表达式去掉换行符
# re.M字符串不考虑回车换行
print  re.findall(tel,"010-12345678",re.X)
email=r"\w{3}@\w+(\.com|\.cn)"
print  re.findall(email,'zzz@cctv.com')

r1=r'herf src=(.+) yes'
s="hhsfsdf  herf src=cctv yes sfdfs \n sdfsd herf src=sina yes"
print  re.findall(r1,s)
# 百度贴吧图片爬取
# reg=r'src="(.*?\.jpg)" width'