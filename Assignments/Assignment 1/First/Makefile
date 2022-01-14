CC=gcc
run=q1_a

exec: $(run)

# make run="q1_a"
q1_a: q1_a.c
	$(CC) q1_a.c -S q1_a.s
	$(CC) q1_a.c -c q1_a.o
	$(CC) q1_a.c -o q1_a
	./q1_a

# make run="q1_b"
q1_b: q1_b.c
	$(CC) q1_b.c -S q1_b.s
	$(CC) q1_b.c -c q1_b.o
	$(CC) -pthread q1_b.c -o q1_b
	./q1_b

clean:
	rm -rf *s
	rm -rf *o
	rm -rf q1_a
	rm -rf q1_b