## Assignment-1

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Question-2
### Running Code
    
- Open linux terminal in the current directory and run
   ```sh
    make run="q2" 
   ```
- After that you will be able to see the desired output on terminal itself
- Run `make clean` in linux terminal to clean up the directory

### Compilation Process
- Compile the `b.asm` file containing `B()` function to the `b.o` object file
- Then compile `main.c, a.c, c.c` and `b.o` into one single executable `q2`
- Run that q2 by `./q2`
- See `MAKEFILE` for commands

### How Program works
1. First `main()` function is called from `main.c`
2. `main()` function calls another function `A()` present in `a.c` file with the help of `extern` keyword definition
3. `A()` function prints `"Inside A"` calls another function `B()` present in `b.asm` file written in assembly language  with the help of `extern` keyword definition with 64-bit integer as an argument
4. In `B()` we first declare a `num` integer variable in `.bss` section and then define `text1 = "Inside B"` and `text2="\n"` in `.data` section, we also declare `extern C` at top to define C
5. Then we move the integer value of the argument passed from `rdi` to `[num]` using `mov` command
6. Then using `syscall` first print `text1` and then `num` which get interpreted as `8-byte ASCII string` automatically (as integer is stored in binary form which the compiler interprets as some text or character array in ASCII) and then finally print `text2`
7. Before executing `ret` we modify the stack in a way to prevent `B()` from returning to `A()`
7. We `pop` the `return address` which is stored at the top of the stack and then keep it in any register which is not currently in use, say, `rcx` using `pop rcx` and then `push` the new return address i.e. address of `C()` using `push C` so that it doesn't return to `A()` and passes control to `C()`
8. Finally when `B()` gives control to `C()` and we first print `"Inside C"` and then `exit(0)` to prevent `segmentation fault` or any other `error`

<br/>
