#Alec Scheele
#Kathryn Thiese 

CC=gcc
CFLAGS=-Wall -Wextra
SCAN_BUILD_DIR = scan-build-out

prodcomm: main.o queue.o reader.o munch1.o munch2.o writer.o 
	$(CC) $(CFLAGS) *.o -o prodcomm -pthread

reader.o: reader.c
	$(CC) $(CFLAGS) -c reader.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

munch1.o: munch1.c
	$(CC) $(CFLAGS) -c munch1.c

munch2.o: munch2.c
	$(CC) $(CFLAGS) -c munch2.c

writer.o: writer.c
	$(CC) $(CFLAGS) -c writer.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean: 
	rm -f prodcomm *.o
	rm -rf $(SCAN_BUILD_DIR)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	chrome -new-window $(SCAN_BUILD_DIR)/*/index.html
