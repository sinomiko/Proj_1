#########################################################################
# File Name: build.sh
# Author: Miko Song
# mail: mikosong@gmail.com
# Created Time: Sun 23 Oct 2016 07:21:11 PM PDT
#########################################################################
#!/bin/bash
g++  -o weak_ptr_demo -g -Wall -std=c++11 weak_ptr_demo.cpp

ulimit -c unlimited

./weak_ptr_demo 

gdb ./weak_ptr_demo core.* 
