CC=gcc -Wall
run="hi"

# make run="hi"
exec: test_syscall.c
	$(CC) test_syscall.c -o test_syscall
	./test_syscall

# ./test_syscall $(run)

clean:
	rm -rf test_syscall