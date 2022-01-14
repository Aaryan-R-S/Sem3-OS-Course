default: clone_example pthread_example

pthread_example: pthread_example.c
	${CC} -o $@ $< -lpthread

.PHONY: default clean

clean:
	${RM} clone_example pthread_example

