## Assignment-2

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Question-1
### Running Code
    
- Open linux terminal in the current directory and run
   ```sh
    make 
   ```
- After that you will be able to see the desired output on terminal itself
- For stopping any process just do `Ctrl+C` or open another terminal and enter the following command 
  ```sh
    kill -TERM (pid)
  ```
- Run `make clean` in linux terminal to clean up the directory

### Code Explanation
1. Run `main.c` and using `fork()` system call create three new processes namely, `S1`, `SR` and `ST` from the main `parent` process.
2. Within `S1` process, using `sigaction()` system call link the `signal_handler_S1()` function with `SIGTERM` signal and `pause()` the `S1` process to receive the signal. For `sigaction()` pass a `my_action` struct also with appropriate flags as shown in code so as to receive the queued data from `SR` and `ST`.
3. `signal_handler_S1` will handle the `SIGTERM` signal and print the queued data recieved from `SR` (a random number, int) and `ST` (timestamp in UTC, string).
4. For `SR` and `ST` processes just execute `sr` and `st` executable using `execl()` command. Also pass the `pid` of `S1` process to these executables as arguments.
5. Within SR and ST processes register handler functions `signal_handler_SR()` and `signal_handler_ST()` respectively, for the both `SIGALRM` and `SIGTERM` signals using `sigaction()` and `signal()` system calls respectively.
6. Set a timer of `2 seconds` using `setitimer()` in both the processes and call the handler functions (`signal_handler_SR()` and `signal_handler_ST()`) by sending `SIGALRM` signal to themselves. These funcs will queue the data (random num in case of SR and timestamp in UTC in case of ST) and send the `SIGTERM` signal to the S1 process.
7. Catch the queued data in `signal_handler_S1()` and print it. Do the same for `ST` process in `signal_handler_ST()` by printing `timestamp` received from ST itself.
8. Within `SR`, random number is obtained by `getRandNum()` which uses inline assembly instruction `RDRAND` and passes it to the `S1` process via `sigqueue()` system call and `union sigval` data structure.
9. Within `ST`, timestamp UTC is obtained by `getTimeStamp()` which uses inline assembly instruction `RDTSC` (divide the CPU counter obtained by procesor's frequency and add the offset and covert it to the string using `asctime()` function) and passes it to the `S1` process via `shared memory` method of process inter-communication.
10. Avoid the processes `S1`, `SR`, `ST` and `main` from getting exited by using `pause()`, `sleep()` and `while()` loop.

<br/>