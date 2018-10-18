// ascheele abscheele
// thiese thiese	

	For Programming Assignment 2 we were assigned to create a program that uses multiple threads running in parallel to modify and output character strings that have been read in from standard input and are stored between threads in multiple queues.
	We began by implementing a Queue that holds char pointers and creating methods that called the dequeue and enqueue methods from our queue and changed all lower case letters to capital letters and replaced spaces in the string with astrixes.  Next we implemented monitors in our enqueue and dequeue methods using pthread_mutex_t and pthread_cond_t for the mutex and condition variables respectively.  Then we wrote our main method to create multiple queues and threads for each of our methods and added the pthread_exit method to our methods.
