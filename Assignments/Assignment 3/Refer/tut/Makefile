all: sched loop inf_loop

sched: sched_library_functions.c
	gcc sched_library_functions.c -o sched

loop: test_loop.c
	gcc test_loop.c -o loop

inf_loop: inf_loop.c
	gcc inf_loop.c -o inf_loop

clean:
	rm -f sched loop inf_loop