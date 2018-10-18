#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include "queue.h"
#include "args.h"
#define BUF 160
#define qsize 10

void *spacetostar(void *ptr){
	struct args *arg = (struct args*) ptr;
       	char* string = (char*)malloc(sizeof(char)*BUF);
	string =  DequeueString(arg->queue1);
	while(string != NULL) {
		for (int i = 0; string[i] != '\0'; i++){
                	if (string[i] == ' '){
                        	string[i] = '*';
                	}
        	}
		EnqueueString(arg->queue2, string);
		string = (char*)malloc(sizeof(char)*BUF);
		string = DequeueString(arg->queue1);

	}
	EnqueueString(arg->queue2, string);
	pthread_exit(NULL);

	return 0;

}
