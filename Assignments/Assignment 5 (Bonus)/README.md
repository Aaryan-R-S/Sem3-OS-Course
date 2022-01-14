## Bonus Assignment

- Extract the `2020004.zip` file.
- Now, you are ready to go!

### Running Code
    
- Open linux terminal in current directory of `q1` or `q3` and run
   ```sh
    make
   ```
- After that you will be able to see the desired output on terminal itself.

### Program Logic
---
 - Problem 1:
    - To solve the classical dining philosopher problem with five philosphers, initialize five `semaphores` (forks) and create five `thread` process (philosopher)
    - For each philospoher `1<=i<=5` do the following:
    ```
        loop:
            think
            take left fork or wait(fork[i])
            take right fork or wait(fork[(i+1)%5])
            eat
            put left fork or signal(fork[i])
            put right fork or signal(fork[(i+1)%5])
    ```
    - But it is not sufficient to prevent `deadlock` as there can be case where each philosopher takes his/her left fork. In this case, no one will be able to take his/her right fork, consequently, a `deadlock`.
    - So, we just modify the code a little bit for the 5th (last) philosopher to prevent the deadlock. 
    - For each philospoher except the last `1<=i<=4` do the following:
    ```
        loop:
            think
            take left fork or wait(fork[i])
            take right fork or wait(fork[(i+1)%5])
            eat
            put left fork or signal(fork[i])
            put right fork or signal(fork[(i+1)%5])
    ```
    - For the last philospoher `i=5` do the following:
    ```
        loop:
            think
            take right fork or wait(fork[(i+1)%5])
            take left fork or wait(fork[i])
            eat
            put right fork or signal(fork[(i+1)%5])
            put left fork or signal(fork[i])
    ```
    - In this case, there will be no deadlock as at any instant a maximum of four philosopher can have a fork simultaneously (one fork per philosopher). So, out of five forks atleast one fork is available at this point which enables the philosopher to eat and prevent a deadlock. 
---
- Problem 2:
    - Since in this case only single fork is required to eat, so there will be no deadlock on forks beacause we can assign each fork to a particular philosopher.
    - Moreover, philosophers also need have access to any one of the four sauce bowls. If i-th philosopher takes i-th fork first and then take any of the four sauce bowl available (if no sauce bowl is available then wait till some philospher puts back a sauce bowl) then there will be no deadlock.
---
- Problem 3:
    - Now, in this case to avoid the deadlock we do the following steps:
    - For each philospoher except the last `1<=i<=4` do the following:
    ```
        loop:
            think
            take left fork or wait(fork[i])
            take right fork or wait(fork[(i+1)%5])
            take any sauce bowl (if available) or wait (bowls)
            eat
            put the sauce bowl or signal(bowls)
            put left fork or signal(fork[i])
            put right fork or signal(fork[(i+1)%5])
    ```
    - For the last philospoher `i=5` do the following:
    ```
        loop:
            think
            take right fork or wait(fork[(i+1)%5])
            take left fork or wait(fork[i])
            take any sauce bowl (if available) or wait(bowls)
            eat
            put the sauce bowl or signal(bowls)
            put right fork or signal(fork[(i+1)%5])
            put left fork or signal(fork[i])
    ```
    - `bowls` is another semaphore initialized by value 4 to indicate the number of sauce bowls available
    - Apply another semaphore `lock` on the `bowls` so as to synchronize the print statement which prints the value of `bowls` using `sem_getvalue()`

### Synchronization primitives used
- `Semaphores`: Semaphore is a non-negative variable that is shared between threads or processes. It uses two atomic operations:
  - `wait` (decrements the semaphore and blocks the thread call if the semaphore accessed is less than 0) 
  - `signal` (increments the semaphore and unblocks a previously blocked thread call if the semaphore accessed is less than or equal to 0)

### Data structures used
- None
- Data Types:
    - `pthred_t`: data type used to uniquely identify a thread
    - `sem_t`: data type used to identify a semaphore

### Pthread library functions used
1. `pthread_create()`
    - used to create a new thread
    - Parameters:
        - `tid`: pointer to an int that stores the thread id of the thread created
        - `attr`: pointer to a structure that is used to define thread attributes (set as NULL)
        - `start_routine`: pointer to a subroutine that is executed by the thread
        - `arg`: pointer to void that contains the arguments to the function
    - returns 0 if success, any other return value indicates that an error occurred
2. `pthread_join()`
    - used to wait for the termination of a thread
    - Arguments:
        - `tid`: thread id of the thread for which the current thread waits
        - `thread_return`: pointer to the location where the exit status of the thread mentioned in tid is stored (set as NULL)
    - returns 0 if success, any other return value indicates that an error occurred

### Semaphore library functions used
1. `sem_init(sem_t *sem, int pshared, unsigned int value)`: initialize an unnamed semaphore with initial value equal to value at address pointed by sem; pshared argument indicates whether semaphore is shared between the threads of a process (zero) or between processes (non-zero); returns 0 on success and -1 on error.

2. `sem_wait(sem_t *sem)`: decrements or locks the semaphore pointed to by sem; if the semaphore has the value zero, then the call is blocked until either it becomes possible to perform the decrement (above zero), or a signal handler interrupts the call; returns 0 on success and -1 on error.

3. `sem_post(sem_t *sem)`: increments or unlocks the semaphore pointed to by sem; if the semaphore's value becomes greater than zero, then another process or thread blocked in a sem_wait() call will be woken up and given the lock; returns 0 on success and -1 on error.

4. `sem_getvalue(sem_t *restrict sem, int *restrict sval)`: places the current value of the semaphore pointed to sem into the integer pointed to by sval; returns 0 on success and -1 on error.

### References
- [Linux Man Pages](https://man7.org/index.html)

<br/>