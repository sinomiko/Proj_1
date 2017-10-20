#!/usr/bin/python
#coding=utf-8
#格式化字符串
import  string
width=input("please enter width:")
price_width=10
item_width=width-price_width
header_format='%-*s%*s'
format='%-*s%*.2f'

print string.capwords("there are all goods ")
print '='*width

print header_format%(item_width,'item',price_width,'price')

print  '-'*width

print  format % (item_width,'apple',price_width,0.4)
print  format % (item_width,'pears',price_width,1.82)
print  format % (item_width,'dried apricots(16 oz.)',price_width,8)
print  format % (item_width,'apple',price_width,198)
print '='*width