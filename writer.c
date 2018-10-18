#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "queue.h"
#include "args.h"
#define qsize 10

void *writeStrings(void *ptr){
	struct args *arg = (struct args*) ptr;
	int i = 0;
	char* string = DequeueString(arg->queue1);
	while (string != NULL) {
		i++;
		fprintf(stdout, "%s\n", string);
		string = DequeueString(arg->queue1);
	}
	fprintf(stdout, "Strings processed: %i\n", i);
	pthread_exit(NULL);
	
	return 0;
}
