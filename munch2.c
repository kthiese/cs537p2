// Alec Scheele
// Kathryn Thiese

// ascheele abscheele
// thiese thiese

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include "queue.h"
#include "args.h"
//#define qsize 10
//#define BUF 160

void *lowertoupper(void *ptr){
	struct args *arg = (struct args*) ptr;
	//char* string = (char *)malloc(sizeof(char)*BUF);
	//string = DequeueString(arg->queue1);
	char* string = DequeueString(arg->queue1);
        while (string != NULL){
		for (int i = 0; string[i] != '\0'; i++){
                	if (islower(string[i])){
                        	string[i] = toupper(string[i]);
                	}
        	}
		EnqueueString(arg->queue2, string);
		//string = (char*)malloc(sizeof(char)*BUF);
		string = DequeueString(arg->queue1);
	}
	EnqueueString(arg->queue2, string);
	pthread_exit(NULL);
	return 0;

}
