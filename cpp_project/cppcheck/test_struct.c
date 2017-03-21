/*************************************************************************
	> File Name: test_struct.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 21 Mar 2017 01:34:34 AM PDT
 ************************************************************************/

#include<stdio.h>
typedef struct Student
{
 int index;
 char name[10];
 int  score[0];
}Student;

int main()
{
  Student stu;
  printf("size stu: %d, sizeof Student: %d", sizeof(stu),sizeof(Student) );
  printf("size int: %d, sizeof char: %d", sizeof(int),sizeof(char) );

}
