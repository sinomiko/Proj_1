# -*- coding:utf-8 -*-
import openpyxl
import pprint
import argparse
import re
import sys
import os
import yaml
import time
import re

def test_args_kwargs(arg1, arg2, arg3):
    print("arg1:", arg1)
    print("arg2:", arg2)
    print("arg3:", arg3)
def testRegx(s):
    #re_words=re.compile(r".*信用客户融资融券规模盯市记录不存在.*")
    re_words=re.compile(u".*请稍后.*".encode('utf-8'))
    #re_words=re.compile(r".*请稍后.*")
    match =  re_words.search(s,0)
    print(u".*请稍后.*".encode('utf-8'))
    print(repr(u".*请稍后.*".encode('utf-8')))
    print(type(u".*请稍后.*".encode('utf-8')))

    print("==============")

    print(ur".*请稍后.*".encode('utf-8'))
    print(repr(ur".*请稍后.*".encode('utf-8')))
    print(type(ur".*请稍后.*".encode('utf-8')))
    if match:
    # 使用Match获得分组信息
        print match.group()
        print("match")
#不带编码
# >>> repr("请稍后")
# "'\\xc7\\xeb\\xc9\\xd4\\xba\\xf3'"

#Unicode
# >>> repr(u"请稍后")
# "u'\\u8bf7\\u7a0d\\u540e'"

#Unicode转utf8
# >>> repr(u"请稍后".encode('utf8'))
# "'\\xe8\\xaf\\xb7\\xe7\\xa8\\x8d\\xe5\\x90\\x8e'

#不带编码先用gbk编码，再转utf8
# >>> repr("请稍后".decode('gbk').encode('utf-8'))
# "'\\xe8\\xaf\\xb7\\xe7\\xa8\\x8d\\xe5\\x90\\x8e'"

#
def testArgs(args):
    print args
if __name__ == '__main__':
    args = ("two", 3, 5)
    test_args_kwargs(*args)
    kwargs = {"arg3": 3, "arg2": "two", "arg1": 5}
    print("\n")
    test_args_kwargs(**kwargs)
    print("====\n")
    #testRegx("-420411020[-150906084]vip系统尚未同步2018-06-27 01:00:21    委托已提交,证券系统返回的原因: -420411020[-990290006]信用客户融资融券规模盯市记录不存在")
    testRegx("2018-06-28 00:00:38    请稍后")

    #for i in kwargs.keys():
    #        jerry={}
    #    print i
    #    jerry[i] = kwargs[i]
    #    print jerry
    #testArgs(kwargs)
    print ("grabber task done " + time.strftime("%H:%M:%S", time.localtime()))
    print("请稍后".decode('utf-8'))
    #s = '濮旀墭宸叉彁浜�,璇佸埜绯荤粺杩斿洖鐨勫師鍥�:'
    #print s.decode('utf-8')
    #print s
