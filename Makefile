CC=gcc

all: kson.o iterate_json.o
	$(CC) kson.o iterate_test.o -o iterate_json

kson.o:
	$(CC) -c kson.c -o kson.o

iterate_json.o:
	$(CC) -c kson.c iterate_test.c

clean:
	rm -rf *.o iterate_json