CC=gcc -Wall
run=P

exec: $(run)

# make run="P"
P: p.c
	$(CC) p.c -o P
	./P
	rm -rf P

# make run="C"
C: c.c
	$(CC) c.c -o C
	./C
	rm -rf C