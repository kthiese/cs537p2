#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "queue.h"
#include "args.h"
#include "reader.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"


#define qsize 10

int main() {
	struct Queue* m1queue = CreateStringQueue(qsize);
	struct Queue* m2queue = CreateStringQueue(qsize);
	struct Queue* wqueue = CreateStringQueue(qsize);
	
	struct args arg1;
	arg1.queue1 = m1queue;

	struct args arg2;
	arg2.queue1 = m1queue;
	arg2.queue2 = m2queue;

	struct args arg3;
	arg3.queue1 = m2queue;
	arg3.queue2 = wqueue;

	struct args arg4;
	arg4.queue1 = wqueue;

//	readStrings((void*) &arg1);	
//	spacetostar((void*) &arg2);
//	lowertoupper((void*) &arg3);
//	writeStrings((void*) &arg4);
	pthread_t reader;
	pthread_t munch1;
	pthread_t munch2;
	pthread_t writer;
	
	pthread_create(&reader, NULL, readStrings,(void *) &arg1);
	pthread_create(&munch1, NULL, spacetostar, (void *) &arg2);
	pthread_create(&munch2, NULL, lowertoupper, (void *) &arg3);
	pthread_create(&writer, NULL, writeStrings, (void *) &arg4);
	
	pthread_join(reader, NULL);
	pthread_join(munch1, NULL);
	pthread_join(munch2, NULL);
	pthread_join(writer, NULL);

//	pthread_exit(reader);
//	pthread_exit(munch1);
//	pthread_exit(munch2);
//	pthread_exit(writer);
}
