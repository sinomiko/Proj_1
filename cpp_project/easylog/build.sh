#########################################################################
# File Name: build.sh
# Author: Miko Song
# mail: mikosong2013@gmail.com
# Created Time: Wed 03 May 2017 01:54:59 AM PDT
#########################################################################
#!/bin/bash
g++ -o build/easylogging++.o -c -std=c++11 src/easylogging++.cc
g++ -o build/prog.o  -c -std=c++11 src/prog.cc
g++ -o proc build/easylogging++.o  build/prog.o 
#g++ prog.cc -Wall -Wextra -O2 -march=native -std=c++11 "easylogging++.cc"
