# -*- coding:utf-8 -*-
from __future__ import print_function
import pprint
import argparse
import re
import sys
import os
import time
import threading
import re

#无缓冲输出，适合Jenkins
buf_arg = 0
if sys.version_info[0] == 3:
    os.environ['PYTHONUNBUFFERED'] = '1'
    buf_arg = 1
sys.stdout = os.fdopen(sys.stdout.fileno(), 'a+', buf_arg)
sys.stderr = os.fdopen(sys.stderr.fileno(), 'a+', buf_arg)

Safeprint = lambda x: sys.stdout.write("%s\n" % x)

global readyForTask
readyForTask = False


def TimeCmp(lPara, rPara):
    return int(time.strftime("%H%M", lPara)) - int(time.strftime("%H%M", rPara))


def Task(index,padding):
    global readyForTask
    while readyForTask == False:
        readyForTask = True
        Safeprint("thread " + str(index)+ " is running ============================================ \n")
        time.sleep(10)
        sys.exit(0)
        Safeprint("thread " + str(index)+ " is over ============================================ \n")
    Safeprint("thread " + str(index)+ " is exiting ============================================ \n")
    time.sleep(20)
    Safeprint("thread " + str(index)+ " is exited ============================================ \n")

if __name__ == '__main__':

    threads = []
    for index in range(1,5,1):
        threadTask = threading.Thread(target=Task, args=(index, 1))
        threads.append(threadTask)
    for threadTask in threads:
        threadTask.start()
    for threadTask in threads:
        threadTask.join()

    print ("task done " + time.strftime("%H:%M:%S", time.localtime()))
