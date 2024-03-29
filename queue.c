// Alec Scheele
// Kathryn Thiese

// ascheele abscheele
// thiese thiese

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Queue Implementation for array of char pointers

// queue structure
struct Queue
{
	// Queue Statistics from Assignment page
	int enqueueCount;
	int dequeueCount;
	int enqueueBlockCount;
	int dequeueBlockCount;

	// Queue attributes
	int front;
	int rear;
	int size;
	int capacity;
	char** array;


	// Monitor lock
	pthread_mutex_t mutex;

	// Condition variables
	pthread_cond_t empty;
	pthread_cond_t fill;


};

// method to make a new queue, takes the capacity of the queue as an arguement
struct Queue* CreateStringQueue(int capacity)
{
	// allocate memory for array of char pointers
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));

	// initialize conditional vars and mutex
	pthread_mutex_init(&queue->mutex, NULL);
	pthread_cond_init(&queue->empty, NULL);
	pthread_cond_init(&queue->fill, NULL);

	// initialize queue stats to 0s
	queue->enqueueCount = 0;
	queue->dequeueCount = 0;
	queue->enqueueBlockCount = 0;
	queue->dequeueBlockCount = 0;

	// capacity is provided
	queue->capacity = capacity;

	// both the size and the location of the front start at 0 index in array
	queue->front = queue->size = 0;

	// rear is set to one less than the capacity
	queue->rear = capacity - 1;

	// create underlying array
	queue->array = (char**) malloc(queue->capacity * sizeof(char*));
	

	return queue;
}

// if size == capacity queue is full
int isFull(struct Queue* queue)
{
	return (queue->size == queue->capacity);
}

// if size == 0 queue is empty
int isEmpty(struct Queue* queue)
{
	return (queue->size == 0);
}

// function to add item to queue, increments enqueue count
void EnqueueString(struct Queue* queue, char* item)
{
	pthread_mutex_lock(&queue->mutex);

	if(isFull(queue))
	{
		
		queue->enqueueBlockCount++;
		pthread_cond_wait(&queue->empty, &queue->mutex);
	}

	
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size++;

	if(item != NULL)
	{
		queue->enqueueCount++;
	}
	
	pthread_cond_signal(&queue->fill);
	pthread_mutex_unlock(&queue->mutex);
	
}

// function to remove item from front of queue, changes size, front and increments dequeue count
char* DequeueString(struct Queue* queue)
{
	pthread_mutex_lock(&queue->mutex);

	if(isEmpty(queue))
	{
		queue->dequeueBlockCount++;
			
		pthread_cond_wait(&queue->fill, &queue->mutex);
	}
	
	char* item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;

	if(item != NULL)
	{
		queue->dequeueCount++;
	}

	pthread_cond_signal(&queue->empty);
	pthread_mutex_unlock(&queue->mutex);

	return item;
}

// get item at front of queue
char* getFront(struct Queue* queue)
{
	if(isEmpty(queue))
		return "queue is empty";
	else
	{
		return queue->array[queue->front];
	}
}

// get item at rear of queue
char* getRear(struct Queue* queue)
{
	if(isEmpty(queue))
		return "queue is empty";
	else
	{
		return queue->array[queue->rear];
	}
}

// return enqueueCount
int getEnqueueCount(struct Queue* queue)
{
	return queue->enqueueCount;
}

// return dequeueCount
int getDequeueCount(struct Queue* queue)
{
	return queue->dequeueCount;
}

// return enqueueBlockCount
int getEnqueueBlockCount(struct Queue* queue)
{
	return queue->enqueueBlockCount;
}

// return enqueueBlockCount
int getDequeueBlockCount(struct Queue* queue)
{
	return queue->dequeueBlockCount;
}

// print queue statistics
void PrintQueueStats(struct Queue* queue)
{
	fprintf(stdout, "Enqueue Count: %d \n", getEnqueueCount(queue));
	fprintf(stdout, "Dequeue Count: %d \n", getDequeueCount(queue));	
	fprintf(stdout, "Enqueue Block Count: %d \n", getEnqueueBlockCount(queue));
	fprintf(stdout, "Dequeue Block Count: %d \n", getDequeueBlockCount(queue));
	//printf("Queue Size: %d \n", queue->size);
}
