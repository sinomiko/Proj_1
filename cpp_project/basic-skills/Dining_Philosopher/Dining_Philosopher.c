/*
 ============================================================================
 Name        : Dining_Philosopher.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "simp_sem.h"
#include "diners.h"

int main(void)
{

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	pthread_t thread_id[N];
	int phils[N];

	mutex = sem_create( 105, 0);
	sem_signal(mutex);

	int i = 0;
	for(i = 0; i < N; i++)
		if( (s[i] = sem_create( (105 + i)  , 0)) < 0 )
			return EXIT_FAILURE;

	for(i = 0; i < N; i++)
	{
		phils[i] = i;
		pthread_create(&thread_id[i], NULL, (void*)philosopher, &phils[i]);
	}

	for(i = 0; i < N; i++)
		pthread_join(thread_id[i], 0);

	return EXIT_SUCCESS;
}
