CC=gcc
run=q1_a

exec: $(run)

# make run="q3_a"
q3_a: q3_a.c
	$(CC) q3_a.c -o q3_a.o
	chmod +x q3_a.o
	./q3_a.o

# make run="q3_b"
q3_b: q3_b.c
	$(CC) q3_b.c -o q3_b.o
	chmod +x q3_b.o
	./q3_b.o

# make run="q4"
q4: q4.c
	$(CC) q4.c -o q4.o
	chmod +x q4.o
	./q4.o

clean:
	rm -rf *o
