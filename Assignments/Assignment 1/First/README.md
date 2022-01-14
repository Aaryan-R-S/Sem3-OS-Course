## Assignment-1

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Question-1 (A)
### Running Code
    
- Open linux terminal in current directory and run
   ```sh
    make run="q1_a" 
   ```
- After that you will be able to see the desired output on terminal itself
- Run `make clean` in linux terminal to clean up the directory


### How Program works
1. Call `fork_n_run()` function which will fork the program into one child and one parent process using `fork()` system call
2. By checking the return value of `fork()` deduce whether it is child or parent process and then call the `read_csv()` and `compute_avg()` function for computing the averages of Section- A or B respectively
3. `get_buff_size_dynamic()` helps in dynamically allocating the size of buffer according to the size of csv file. `read_csv()` uses `open()` and `read()` system call to open and read the csv and store the data in a char buffer[] array of nearly 1000 size and then close the file opened using `close()` system call
4. `compute_avg()` uses `get_code()` functions to get a line by line data from the char buffer array and then perform the required operations to compute the averages  
5. Then use `waitpid()` to prevent parent process from terminating before child process. The child process must call the `exit()` system call once its execution ends
6. Finally write the outputs to the stdout using `write()` system call

### System Calls Used
1. `fork()`
    - creating a new process, which is called child process
    - no parameters/arguments
    - returns an integer value
        - negative means child process creation is unsuccessful
        - zero means its child process
        - positive value means its parent process (return value in this case is `pid` of child process) 
2. `waitpid()`
    - suspends execution of the current process until a child specified by pid argument has changed state (termination)
    - Arguments:
        - `pid` of child process
        - reference to an int variable to store status info
    - on success, returns the process ID of the child whose state has changed; on error, -1 is returned
3. `exit()`
    - terminates the process, flushes the buffer and closes the opened file
    - takes only integer args in the range 0 – 255 (otherwise perform modulo 256 operation)
    - status value returns to the parent process
        - 0 indicates success
        - any other value indicates error
4. `open()`
    - open the file for reading, writing or both
    - Parameters
        - `Path` : path to file which you want to use 
        - `FLAGS`
            - `O_RDONLY`: read only
            - `O_WRONLY`: write only
            - `O_RDWR`: read and write
            - `O_CREATE`: create file if it doesn’t exist
            - `O_EXCL`: prevent creation if it already exists
    - returns file descriptor `fd` used, `-1` upon failure
5. `close()`
    - close the file which is pointed by fd
    - Parameters
        - `fd` : file descrpitor
    - returns 0 on success, -1 on failure 
6. `read()`
    - from the file indicated by the file descriptor fd, it reads some bytes (count) of input into the memory area indicated by user (buffer)
    - read from stdin `fd = 0`
    - Parameters:
        - fd: file descriptor
        - buffer:char buffer array to read data from
        - count: length of buffer
    - returns length of bytes that were actually read, -1 on error, 0  on reaching end of file
7. `write()`
    - writes count bytes from buffer to the file or to stout/stderr
    - write to stdout `fd = 1`
    - Parameters:
        - fd: file descriptor
        - buffer:char buffer array to take and write data to 
        - count: length of buffer
    - returns length of bytes that were actually written, -1 on error, 0 on reaching  end of file


### Handling some `Error` or `Corner` cases
- `fork()` return value negative means child process creation is unsuccessful so report it to the user and exit
- `waitpid()` on error, -1 is returned so report it to the user
- `open()` returns -1 upon failure so report it to the user and return from the `read_csv()` function
- `close()` returns -1 upon failure so report it to the user and return from the `read_csv()` function
- `read()` returns -1 upon failure so report it to the user and return from the `read_csv()` function

<br/>

## Question-1 (B)
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q1_b" 
   ```
- After that you will be able to see the desired output on terminal itself
- Run `make clean` in linux terminal to clean up the directory


### How Program works
1. `read_csv()` uses `open()` and `read()` system call to open and read the csv and store the data in a char buffer[] array of nearly 1000 size and then close the file opened using `close()` system call
2. Call `pthread_n_run()` function which will create a thread within the process using `pthread_create()` system call
3. By checking the return value of `pthread_create()` deduce whether the thread was created or not and if created, then call the `compute_avg()` function for computing the averages of Section-A 
4. `get_buff_size_dynamic()` helps in dynamically allocating the size of buffer according to the size of csv file. `compute_avg()` uses `get_code()` functions to get a line by line data from the char buffer array and then perform the required operations to compute the averages  
5. Then use `pthread_join()` to join the thread created with main thread
6. Then do the same for Section-B students
6. Store the results obtained from the threads in `total_marks`[] and `students`[] array and then use this result to print the avg marks across the sections
7. Finally write the outputs to the stdout using `write()` system call

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

### System Calls Used
3. `exit()`
    - terminates the process, flushes the buffer and closes the opened file
    - takes only integer args in the range 0 – 255 (otherwise perform modulo 256 operation)
    - status value returns to the parent process
        - 0 indicates success
        - any other value indicates error
4. `open()`
    - open the file for reading, writing or both
    - Parameters
        - `Path` : path to file which you want to use 
        - `FLAGS`
            - `O_RDONLY`: read only
            - `O_WRONLY`: write only
            - `O_RDWR`: read and write
            - `O_CREATE`: create file if it doesn’t exist
            - `O_EXCL`: prevent creation if it already exists
    - returns file descriptor `fd` used, `-1` upon failure
5. `close()`
    - close the file which is pointed by fd
    - Parameters
        - `fd` : file descrpitor
    - returns 0 on success, -1 on failure 
6. `read()`
    - from the file indicated by the file descriptor fd, it reads some bytes (count) of input into the memory area indicated by user (buffer)
    - read from stdin `fd = 0`
    - Parameters:
        - fd: file descriptor
        - buffer:char buffer array to read data from
        - count: length of buffer
    - returns length of bytes that were actually read, -1 on error, 0  on reaching end of file
7. `write()`
    - writes count bytes from buffer to the file or to stout/stderr
    - write to stdout `fd = 1`
    - Parameters:
        - fd: file descriptor
        - buffer:char buffer array to take and write data to 
        - count: length of buffer
    - returns length of bytes that were actually written, -1 on error, 0 on reaching  end of file


### Handling some `Error` or `Corner` cases
- `pthread_create()` on error, any value other than 0 is returned so report it to the user and exit
- `pthread_join()` on error, any value other than 0 is returned so report it to the user
- `open()` returns -1 upon failure so report it to the user and return from the `read_csv()` function
- `close()` returns -1 upon failure so report it to the user and return from the `read_csv()` function
- `read()` returns -1 upon failure so report it to the user and return from the `read_csv()` function

<br/>