#########################################################################
# File Name: string.sh
# Author: Miko Song
# mail: mikosong2013@gmail.com
# Created Time: Thu 16 Mar 2017 06:13:18 PM PDT
#########################################################################
#!/bin/bash
your_name='qinjx'
str="Hello, I know your are \"$your_name\"! \n"


your_name="qinjx"
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"
echo $greeting $greeting_1

string="abcd"
echo ${#string} 

string="alibaba is a great company"
echo ${string:1:4} 

string="alibaba is a great company"
echo `expr index "$string" is`

#out:
#Press ENTER or type command to continue
#hello, qinjx ! hello, qinjx !
#4
#liba
#3

funWithParam(){
    echo "The value of the first parameter is $1 !"
    echo "The value of the second parameter is $2 !"
    echo "The value of the tenth parameter is $10 !"
    echo "The value of the tenth parameter is ${10} !"
    echo "The value of the eleventh parameter is ${11} !"
    echo "The amount of the parameters is $# !"  # 参数个数
    echo "The string of the parameters is $* !"  # 传递给函数的所有参数
}
funWithParam 1 2 3 4 5 6 7 8 9 34 73

#The value of the first parameter is 1 !
#The value of the second parameter is 2 !
#The value of the tenth parameter is 10 !
#The value of the tenth parameter is 34 !
#The value of the eleventh parameter is 73 !
#The amount of the parameters is 11 !
#The string of the parameters is 1 2 3 4 5 6 7 8 9 34 73 !
# $# 传递给函数的参数个数。
# $*  显示所有传递给函数的参数。
# $@  与$*相同，但是略有区别，请查看Shell特殊变量。
# $?  函数的返回值。
