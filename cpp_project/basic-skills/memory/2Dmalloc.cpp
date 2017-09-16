#include<stdio.h>
#include<string.h>
#include <iostream>
#include <vector>
#include<string.h>
using namespace std;

char**  test2(void) {
	char** ptr = (char**)malloc(8 * sizeof(char*));
	ptr[0] = (char*)malloc(5 * sizeof(char));
	*ptr[0] = 'a';
	*(ptr[0] + 1) = 'b';

	*(*(ptr)+2) = 'c';
	ptr[0][3] = 'd';
	ptr[0][4] = '\0';
	*(ptr+1)= (char*)malloc(2 * sizeof(char));
	*ptr[1] = 'a';
	*(*(ptr+1)+1) = '\0';
	
	*(ptr+2) = (char*)malloc(2 * sizeof(char));
	*ptr[2] = 'w';
	*(ptr[2] + 1) = '\0';
	return ptr;
}

int main()
{

	char** ptr = test2();
	printf("rep ptr :%04x \n", ptr);
	printf("rep ptr :%04x \n", ptr[0]);
	printf("rep ptr :%04x \n", *ptr[0]);
	printf("rep ptr :%04x \n", *ptr[1]);
	printf("rep ptr :%c \n", ptr);
	printf("rep ptr :%c \n", ptr[0]);
	printf("rep ptr :%c \n", *ptr[0]);
	return 0;
}