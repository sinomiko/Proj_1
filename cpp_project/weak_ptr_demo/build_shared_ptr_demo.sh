#########################################################################
# File Name: build.sh
# Author: Miko Song
# mail: mikosong@gmail.com
# Created Time: Sun 23 Oct 2016 07:21:11 PM PDT
#########################################################################
#!/bin/bash
g++  -o shared_ptr_demo -g -Wall -std=c++11 shared_ptr_demo.cpp

ulimit -c unlimited

./shared_ptr_demo 

gdb ./shared_ptr_demo core.* 
