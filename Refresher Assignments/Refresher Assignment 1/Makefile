CC=gcc
run=q2

exec: $(run)

# make run="q1" src="del/h1.c" dest="del/h2.c"
# make run="q1" src="del/tt.pdf" dest="del/indel/tt_copy.pdf"
q1: q1.c
	$(CC) q1.c -o q1.o
	chmod +x q1.o
	./q1.o $(src) $(dest)

# make run="q2"
q2: q2.c
	$(CC) q2.c -o q2.o
	chmod +x q2.o
	./q2.o

# make run="q3"
q3: q3.c
	$(CC) q3.c -o q3.o
	chmod +x q3.o
	./q3.o

# make run="q4"
q4: q4.c
	$(CC) q4.c -o q4.o
	chmod +x q4.o
	./q4.o

# make run="q5"
q5: q5.c
	$(CC) q5.c -o q5.o
	chmod +x q5.o
	./q5.o

clean:
	rm -rf *o
