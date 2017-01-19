/*************************************************************************
	> File Name: str_ptr.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Fri 17 Feb 2017 02:57:01 AM PST
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>                                         
#include<stdint.h>                                        
#include<string.h>                                        
#include <unistd.h>                                       
                                                          
typedef enum __bool { false = 0, true = 1, } bool;        
                                                          
void memory_copy(char ** ptr)                             
{                                                         
    *ptr = "world";                                       
    ptr = (char *)malloc(sizeof(char)*6);               
    memcpy(ptr,"world",strlen("world"));                
    printf("%s \n",*ptr);                                 
 }                                                         
 int main(int argc, char * argv)                           
 {                                                         
          char * str = "hello" ;                                
          memory_copy(&str);                                    
          printf("%s \n",str);                                  
    //                     //   int n;                                              
    //                      //   if((n=1)>0)                                         
    //                       //       printf("ok \n");                                
    //                        //   else                                                
    //                        //        printf("not ok \n");                            
                       return 1;                                             
}                                                         
