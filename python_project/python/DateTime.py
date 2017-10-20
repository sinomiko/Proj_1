#!/usr/bin/python
#coding=utf-8
# 要求输入年月日，然后给出相日期应的月份名称：
months=["January","February","March","April","May","June","July","Auguest","September","October","November","December"]
endings=["st","nd","rd"]+17*["th"]+["st","nd","rd"]+7*["th"]+["st"]
year=raw_input("year:")
month=raw_input("month:")
day=raw_input("day:")

year_number=int(year)
month_number=int(month)
day_numer=int(day)

month_name=months[month_number-1]
day_name=day+endings[day_numer-1]

print month_name+' '+day_name+' '+str(year_number)