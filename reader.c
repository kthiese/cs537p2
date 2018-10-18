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

extern const int BUF;

void *readStrings(void *ptr){
	char* string = (char*)malloc(sizeof(char)*BUF);
	struct args *arg = (struct args*) ptr;
	char c;
	int i=0;
	do {
		c = getchar();
		if (c == EOF){
			break;
		}
		if (i == BUF) {
			fprintf(stderr, "String was longer than buffer.\n");
			fflush(stderr);
			i = 0;
			string = (char*)malloc(sizeof(char)*BUF);
			do {
				c = getchar();
			}while (c != '\n' && c != EOF);	
		}
		else if (c == '\n'){
			i = 0;
			EnqueueString(arg->queue1, string);
			
			string = (char*)malloc(sizeof(char)*BUF);
		}
		else if (c != EOF){
			string[i] = c;
			i++;
		}
	}while (c != EOF);
	
	//free string
	//free(string);

	EnqueueString(arg->queue1, NULL);

	pthread_exit(NULL);

	return 0;
}
