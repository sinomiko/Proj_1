#########################################################################
# File Name: build.sh
# Author: Miko Song
# mail: mikosong@gmail.com
# Created Time: Sun 23 Oct 2016 07:21:11 PM PDT
#########################################################################
#!/bin/bash
g++  -o weakSharePtrDemo -g -Wall -std=c++11 weakSharePtrDemo.cpp

ulimit -c unlimited

./weakSharePtrDemo 

gdb ./weakSharePtrDemo core.* 
