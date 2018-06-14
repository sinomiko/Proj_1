# -*- coding:utf-8 -*-
import openpyxl
import pprint
import argparse
import re
import sys
import os
import yaml
import time

#无缓冲输出，适合Jenkins
buf_arg = 0
if sys.version_info[0] == 3:
    os.environ['PYTHONUNBUFFERED'] = '1'
    buf_arg = 1
sys.stdout = os.fdopen(sys.stdout.fileno(), 'a+', buf_arg)
sys.stderr = os.fdopen(sys.stderr.fileno(), 'a+', buf_arg)


def TimeCmp(lPara, rPara):
    return int(time.strftime("%H%M", lPara)) - int(time.strftime("%H%M", rPara))

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='MC Stock Grabber')
    parser.add_argument('-v', '--version', dest='version', action='store_true')
    parser.add_argument('--dir', dest='dir', default='.')
    parser.add_argument('--init-retry', dest='init_retry', default=5)
    parser.add_argument('--mouse', dest='mouse', default='test_mouse.yml')
    parser.add_argument('--xlsx', dest='xlsx', default='.\stocklist.xlsx')
    parser.add_argument('--execute-time', dest='execute_time', default='00:00:00')
    parser.add_argument('--show-logs', dest='show_logs', action='store_true')
    args = parser.parse_args()
    stock_grabber_list =[]
    stock_grabber_list.append(('601288', 100, 7.25))
    index =''
    d = {'a': 1, 'c': 3, 'b': 2, 'd': 4}
    item = ''
    for i, j in enumerate(d.values()):
        print i,j
        if len(stock_grabber_list)>0:
            print len(stock_grabber_list)
            item = stock_grabber_list[0]
        if index == '':
            index = i
            print 'index :', index
            print 'stock_grabber_list: ', stock_grabber_list
            stock_grabber_list.remove(item)
            print 'stock_grabber_list: ',stock_grabber_list
