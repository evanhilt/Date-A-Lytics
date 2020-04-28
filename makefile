CC = gcc
CFLAGS = -o

app: main.c date.c data.c
	$(CC) $(CFLAGS) date-a-lytics main.c date.c data.c

clean:
	rm date-a-lytics   
