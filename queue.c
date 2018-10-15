#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Based off of Geeks for Geeks Queue Implementation with Queue Statistics added and modified to work with arrays of char pointers

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
struct Queue* createQueue(int capacity)
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
void enqueue(struct Queue* queue, char* item)
{
	if(isFull(queue))
	{
		printf("queue is full, cannot add item");
		return;
	}
	else
	{
		queue->rear = (queue->rear + 1) % queue->capacity;
		queue->array[queue->rear] = item;
		queue->size++;
		queue->enqueueCount++;
		printf("%s added to queue \n", item);
		printf("queue size is %d \n", queue->size);
	}
	
}

// function to remove item from front of queue, changes size, front and increments dequeue count
char* dequeue(struct Queue* queue)
{
	if(isEmpty(queue))
	{
		return "queue is empty";
	}
	else
	{
		char* item = queue->array[queue->front];
		queue->front = (queue->front + 1) % queue->capacity;
		queue->size = queue->size--;
		queue->dequeueCount++;
		return item;
	}
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

int main()
{
	struct Queue* queue = createQueue(10);

	enqueue(queue, "hello");
	printf("Enqueue count: %d \n", getEnqueueCount(queue));
	enqueue(queue, "testing sucks");
	printf("Enqueue count: %d \n", getEnqueueCount(queue));
	enqueue(queue, "maybe testing isnt so bad after all");
	printf("Enqueue count: %d \n", getEnqueueCount(queue));
	printf("String at rear of the queue is: %s \n", getRear(queue));
	printf("Dequeue count: %d \n", getDequeueCount(queue));
	printf("%s dequeued from queue\n", dequeue(queue));
	printf("Dequeue count: %d \n", getDequeueCount(queue));

	return 0;
}
	
