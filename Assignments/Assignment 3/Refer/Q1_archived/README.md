# Assignment-3: Q1

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Testing System Call    
- Open linux terminal in the current directory and run
   ```sh
    make 
   ```
- After that you will be able to see the desired output on terminal itself for checking the `delay_sched_process()` system call
- Run `sudo dmesg` to see timestamps in the kernel log
- Run `make clean` in linux terminal to clean up the directory

## Apply Diff/Patch file to Kernel
- There are two patch/diff files in the Q2 directory
  - `myPatch.patch` contains all the changes in  kernel source code after the `make` command
- To apply patch file, run
  ```sh
   git apply myPatch.patch
  ```

## Kernel Data Structures Used
- `struct task_structure`: Present in `"sched.h"`. It is a task object. Every process in the system has this struct. It holds a lot of information like sched_classs, stack, flag, name, statistics, etc.
- `struct sched_entity`: Present in `"sched.h"`.It is a schedule-able object. Every task_struct has a sched_entity. It hold a lot of information like on_rq, exec_start, sum_exec_runtime, vruntime, prev_sum_exec_runtime, nr_migrations, etc.

## Source Files Modified
- `arch>x86>entry>syscalls>syscall_64.tbl`: Added `delay_sched_process()` system call at 450th index.
- `include>linux>syscalls.h`: Added a declaration of the system call to inform the kernel that the syscall definition exists.
- `kernel>sys.c`: Added a definition of the system call.
- `include>linux>sched.h`: Modified `struct sched_entity` to include three more fields namely, `pid_of_process` (stores the pid of process), `log_timestamp_flag` (flag to indicate that timestamp os to be printed or not) and `delay_ms` (delay, in milliseconds, between process selection and execution by the scheduler).
- `kernel>sched>core.c`: Set the default value of newly added fields of `sched_entity struct` as zero.
- `kernel>sched>fair.c`: If `delay_ms` field of the sched_entity is not zero then add the delay to the `vruntime` to delay the process execution after selection in `update_curr()` function. Also in `pick_next_entity()` function, print the timestamp in kernel log with the help of `ktime_get_real()` function.


## Logic Explanation
- First I added the three more fields namely, `pid_of_process` (stores the pid of process), `log_timestamp_flag` (flag to indicate that timestamp os to be printed or not) and `delay_ms` (delay, in milliseconds, between process selection and execution by the scheduler) to the `sched_entity struct` in `sched.h` so as to help in identifying the processes which needs to be delayed.
- In `core.c` set the default values of these new fields as zero.
- Then created a `system call` to take pid of process and delay in milliseconds in `sys.c`. Also modified the `syscall_64.tbl` and `syscalls.h` to inform the kernel about new syscall.
- Then searched for the process in the task list and set the `log_timestamp_flag` to indicate that timestamp has to be printed for this process.
- Also set the `delay_ms` and `pid_of_process` field which will be used in updating vruntime and printing the timestammp.
- In order to delay the process execution after selection, I modified the vruntime variable. This is done in `update_curr()` function in `fair.c` by adding delay in nanoseconds to the vruntime. This is done only when the `delay_ms` is not equal to zero.
- In `pick_next_entity()` function, print the timestamp in kernel log before scheduling the process, with the help of `ktime_get_real()` and `ktime_to_ns()` function present in the same file.
- Finally test the system call by creating two processes with the help of `fork()` system call in `test.c` in userspace.
- Set the `nice` value of both the process as seven.
- `Parent process` uses the system call to pass on delay as 10ms. While `child process` passes delay of 0ms.
- Observe the output on `stdout` and `kernel log` to infer that majority of times, parent process takes more time to get completely executed as compared to child process.

<br/>