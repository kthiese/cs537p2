#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Queue Implementation for array of char pointers

// Monitor lock
pthread_mutex_t mutex;

// Condition variables
pthread_cond_t empty;
pthread_cond_t fill;

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

};

// method to make a new queue, takes the capacity of the queue as an arguement
struct Queue* CreateStringQueue(int capacity)
{
	// allocate memory for array of char pointers
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));

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
	pthread_mutex_lock(&mutex);

	if(isFull(queue))
	{
		queue->enqueueBlockCount++;
		pthread_cond_wait(&empty, &mutex);
	}

	
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size++;
	queue->enqueueCount++;
	printf("%s added to queue \n", item);
	printf("queue size is %d \n", queue->size);
	
	pthread_cond_signal(&fill);
	pthread_mutex_unlock(&mutex);
	
}

// function to remove item from front of queue, changes size, front and increments dequeue count
char* DequeueString(struct Queue* queue)
{
	pthread_mutex_lock(&mutex);

	if(isEmpty(queue))
	{
		queue->dequeueBlockCount++;
		pthread_cond_wait(&fill, &mutex);
	}
	

	char* item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;
	queue->dequeueCount++;

	pthread_cond_signal(&empty);
	pthread_mutex_unlock(&mutex);

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
	printf("Enqueue Count: %d \n", getEnqueueCount(queue));
	printf("Dequeue Count: %d \n", getDequeueCount(queue));	
	printf("Enqueue Block Count: %d \n", getEnqueueBlockCount(queue));
	printf("Dequeue Block Count: %d \n", getDequeueBlockCount(queue));
}

int main()
{
	struct Queue* queue = CreateStringQueue(2);

	EnqueueString(queue, "hello");
	PrintQueueStats(queue);
	EnqueueString(queue, "testing sucks");
	PrintQueueStats(queue);
	EnqueueString(queue, "maybe testing isnt so bad after all");
	PrintQueueStats(queue);
	PrintQueueStats(queue);
	PrintQueueStats(queue);
	printf("%s dequeued from queue\n", DequeueString(queue));
	printf("%s dequeued from queue\n", DequeueString(queue));
	printf("%s dequeued from queue\n", DequeueString(queue));
	printf("%s dequeued from queue\n", DequeueString(queue));
	PrintQueueStats(queue);

	return 0;
}
	
