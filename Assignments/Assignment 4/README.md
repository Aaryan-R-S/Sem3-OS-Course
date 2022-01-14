# Assignment-4

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Testing System Call    
- Open linux terminal in the current directory and split it into two terminals.
- Then on first terminal run:
   ```sh
    make run="P"
   ```
- And on second terminal run:
   ```sh
    make run="C"
   ```
- After that you will be able to see the desired output on terminal itself.

## Apply Diff/Patch file to Kernel
- There are two patch/diff files in the Q2 directory
  - `mySmallPatch.patch` contains all the changes in `.c` , `.h` and `.tbl` files only after the `make` command
  - `myPatch.patch` contains all the changes in  kernel source code after the `make` command
- To apply patch file, run
  ```sh
   git apply mySmallPatch.patch
   OR
   git apply myPatch.patch
  ```

## Data Structures Used
- `struct custom_queue`: Present in `sys.c`, it is a custom struct type object. It is used to implement the queue. It consists of following fields: `bool` is_initial, `char*` my_q, `long` start_head,	`long` end_head and `struct mutex` q_lock.
  
## Synchronization Primitives Used
- `Mutex`: Mutex exclusion lock (mutex) blocks another thread that is also trying to lock the same mutex until the owner thread unlocks the mutex. Following are some important functions related to it:
  - `mutex_init`: Initialize a mutex.
  - `mutex_lock`: Lock a mutex.
  - `mutex_unlock`: Unlock a mutex.


## Source Files Modified
- `arch>x86>entry>syscalls>syscall_64.tbl`: Added `writer()` and `reader()` system call at 451st and 452nd indices respectively.
- `kernel>sys.c`: Added the definition of the two system calls along with helper functions like `initial_queue`, `queue_my_queue` and `dequeue_my_queue` with a struct `custom_queue`.

## Logic Explanation
- First, create two system calls `writer()` and `reader()` in `sys.c`. Also add the entries of these two new system calls in `syscall_64.tbl`.
- Define new struct `struct custom_queue` to implement the queue. It consists of following fields: `bool` is_initial (stores whether the strtuct is initialized or not), `char*` my_q (original queue), `long` start_head (writer head),	`long` end_head (reader head) and `struct mutex` q_lock (mutex lock for synchronization).
- Declare a struct custom_queue `my_queue`. Create a function `initial_my_queue` which help in intializing myqueue struct with default values and using functions like `kmalloc()`.
- `writer()` sysytem call accept the 8-byte blocks from the user (after initializing `my_queue` if not initialized) and then queue these bytes to the queue with the help of `queue_my_queue()` function.
- `queue_my_queue()` locks the struct's mutex first, then write data to the queue and then update the `writer head` variable. It also handles the case where queue becomes full then set the writer head to 0. After writing to the queue, unlock the struct's mutex.
- `reader()` system call sends the 8-byte blocks from the queue (after initializing `my_queue` if not initialized) to the char* present in the argument with the help of `dequeue_my_queue()` function.
- `dequeue_my_queue()` locks the struct's mutex first, then reads data from the queue and then update the `reader head` variable. It also handles the case where queue is empty then return -1, and if `reader head` reaches to upper limit then set the it to 0. After reading from the queue, it copies the queued data to `char*` argument and unlock the struct's mutex.
-  Program `P` reads random 8-bytes of the device `/dev/urandom` using `open()` and `read()` system calls and passes it to the kernel via `writer()` system call using a `char[]` argument for queueing it.
-  Program `C` call `reader()` system call and prints the dequeued value using `char[]` argument passed. Also checks if queue is empty then report it.

## References:
- [Man pages](https://man7.org/)
- [Bootlin Docs](https://bootlin.com/docs/)