#########################################################################
# File Name: run.sh
# Author: Miko Song
# mail: mikosong2013@gmail.com
# Created Time: Mon 13 Mar 2017 06:02:55 PM PDT
#########################################################################
#!/bin/bash
rm -rf main
gcc -o main main.c -pthread
if [ $? -eq 0 ]
then
    ./main
fi

