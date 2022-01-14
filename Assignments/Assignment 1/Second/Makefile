CC=gcc -no-pie
run=q2

exec: $(run)

# make run="q2"
q2: main.c a.c b.asm c.c
	nasm -f elf64 -o b.o b.asm
	$(CC) main.c a.c b.o c.c -o q2
	./q2

# objdump -S --disassemble q2 > q2.dump

clean:
	rm -rf *s
	rm -rf *o
	rm -rf q2
	rm -rf *dump