struct Queue{
	int enqueueCount;
	int dequeueCount;
	int enqueueBlockCount;
	int dequeueBlockCount;

	int front;
	int rear;
	int size;
	int capacity;
	char** array;
};

struct Queue* CreateStringQueue(int capacity);
int isFull(struct Queue* queue);
int isEmpty(struct Queue* queue);
void EnqueueString(struct Queue* queue, char* item);
char* DequeueString(struct Queue* queue);
char* getFront(struct Queue* queue);
char* getRear(struct Queue* queue);
int getEnqueueCount(struct Queue* queue);
int getDequeueCount(struct Queue* queue);
int getEnqueueBlockCount(struct Queue* queue);
int getDequeueBlockCount(struct Queue* queue);
int PrintQueueStats(struct Queue* queue);

