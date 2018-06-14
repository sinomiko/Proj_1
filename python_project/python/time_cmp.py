#! /usr/bin/python
# coding=utf-8

import time
#from datetime import datetime
import argparse

def TimeCmp(lPara, rPara):
    return int(time.strftime("%H%M", lPara)) - int(time.strftime("%H%M", rPara))

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--execute-time', dest='execute_time', default='15:01:00')
    args = parser.parse_args()
    while 1:
        time.sleep(30)
        #strTimeNow = time.strftime("%H:%M:%S",time.localtime())
        if TimeCmp(time.localtime(), time.strptime(args.execute_time, "%H:%M:%S")) == 0:
            print("equal")
            break
        else:
            print("less")