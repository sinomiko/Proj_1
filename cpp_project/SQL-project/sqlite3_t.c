/*************************************************************************
	> File Name: sqlite3_t.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 27 Dec 2016 04:48:11 AM PST
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
 
 int myfunc(void *p, int argc, char **argv, char **argvv)
 {
         int i;
         *(int *)p = 0;
         for(i =0; i < argc; i++)
         {
                 printf("%s = %s \n", argvv[i], argv[i] ? argv[i] :"NULL");
         }
         putchar('\n');
         return 0;
 }
 
 int main(int argc, char *argv[])
 {
         sqlite3 *db;
         char *err =0;
         int ret =0;
         int empty =1;
 
         ret = sqlite3_open("student",&db);
         if(ret !=SQLITE_OK)
         {
                 fputs("\n",stderr);
                 exit(1);
         }
         ret = sqlite3_exec(db, "select * from user;", myfunc, &empty, &err);
 
         if(ret != SQLITE_OK)
         {
                 fputs(err,stderr);
                 fputs("\n",stderr);
                 sqlite3_close(db);
                 exit(1);
         }
 
         if(empty)
         {
                 fputs("table student is empty\n", stderr);
                 exit(1);
         }
 
         sqlite3_close(db);
 
         return 0;
 }
