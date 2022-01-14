CC=gcc -Wall
run=r

exec: $(run)

# make run="r"
r: main.c
	$(CC) main.c -o q1
	./q1 1 0

# make run="t"
t: main.c
	$(CC) main.c -o q1
	./q1 0 1

# make run="all"
all: main.c
	$(CC) main.c -o q1
	./q1 0 0

clean:
	rm -rf q1