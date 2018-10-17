#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "queue.h"
#include "args.h"
#define qsize 10

void *writeStrings(void *ptr){
	struct args *arg = (struct args*) ptr;
	char* string = DequeueString(arg->queue1);
	while (string != NULL) {
		fprintf(stdout, "%s\n", string);
		string = DequeueString(arg->queue1);
	}

	return 0;
}
