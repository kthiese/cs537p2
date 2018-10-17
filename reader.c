#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"
#include "args.h"
#define qsize 10
#define BUF 160

void *readStrings(void *ptr){
	char* string = (char*)malloc(sizeof(char)*BUF);
	struct args *arg = (struct args*) ptr;
	char c;
	int i=0;
	do {
		c = fgetc(stdin);
		if (i == BUF) {
			fprintf(stderr, "String was longer than buffer.\n");
			i = 0;
			memset(string, 0, BUF);
			do {
				c = fgetc(stdin);
			}while (c != '\n' && c != EOF);	
		}
		else if (c == '\n'){
			i = 0;
			EnqueueString(arg->queue1, string);
			string = (char *) malloc(sizeof(char)*BUF);
		}
		else if (c != EOF){
			string[i] = c;
			i++;
		}
	}while (c != EOF);
}
