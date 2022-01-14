# Assignment-3: Q2

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Running the Programs

### For FIFO
- Open a linux terminal in the `2020004->Q2->FIFO` directory.
- Split the terminal into two terminals and run the following command `make run="P1"` on the first terminal and `make run="P2"` on the second terminal. [`Note:` Ensure that program `P1` runs first i.e. before `P2` for successful compilation!]
- After that you will be able to see the desired output on terminals itself.
- Run `make clean` in linux terminal to clean up the directory.

### For Message Queue
- Open a linux terminal in the `2020004->Q2->Message Queue` directory.
- Split the terminal into two terminals and run the following command `make run="P1"` on the first terminal and `make run="P2"` on the second terminal. [`Note:` Ensure that program `P1` runs first i.e. before `P2` for successful compilation!]
- After that you will be able to see the desired output on terminals itself.
- Run `make clean` in linux terminal to clean up the directory.

### For Socket
- Open a linux terminal in the `2020004->Q2->Socket` directory. 
- Split the terminal into two terminals and run the following command `make run="P1"` on the first terminal and `make run="P2"` on the second terminal. [`Note:` Ensure that program `P1` runs first i.e. before `P2` for successful compilation!]
- After that you will be able to see the desired output on terminals itself.
- Run `make clean` in linux terminal to clean up the directory.

## Data Structures Used

### FIFOs
They are used for IPC. These are `pipes` which have names (`named pipe`) and are represented in the filesystem by special files (FIFO). The advantage of using named pipe is that processes do not need to belong to the same hierarchy. FIFOs can be opened by multiple processes for `reading or writing`. They may persist after process termination. A FIFO can be opened for read and write in the both `blocking` and `nonblocking` mode in Linux. They accept data in form of `data stream`.

### Message Passing Queues 
They are also used for IPC like FIFOs. They are `kernel managed queues` that stores labeled messages in form of `data packets` (not the data stream). They allow processes to exchange data in the form of messages.
Messages can be retrieve from the oldest to newest and `filter by label`. They can also be assigned a `priority value` with lowest value of priority reaching first.

### Unix Domain Sockets
They are also used for IPC like above two data structures. Linux provides domain sockets for _`Stream`_ and _`Datagram`_. Socket creates an endpoint for communication. Although these sockets are `local` to the same system, the underlying implementation is abstracted by the `Socket API`, then they can be used as any other socket of the corresponding type. It is a `client-server model` of communication.

## Code Logic Explanation
### Basic Idea 
- There are two programs `P1` and `P2`. 
- The first program `P1` generate an array of 50 random strings (of characters) of fixed length using `generate_n_rand_str()` function (with the help of `rand()`) and store them in a `struct myStruct* myData` pointer variable. `myStruct` is custom `struct` to store both the random string and its corresponding index.
- `P1` then sends a group of five consecutive elements of the array of strings to `P2` along with the ID’s (or index) of the strings using FIFO/MessageQueue/Socket data structure via `send_t_rand_str()` function. Each data structure's IPC procedure is discussed below in this `README`.
- The second program `P2` accepts the received strings (via `receive_t_rand_str()` function), and send back the highest ID received back to `P1` (via `send_last_rand_str()` function) to acknowledge the strings received using same FIFO/MessageQueue/Socket data structure as used by `P1`. Program `P1` has `receive_last_rand_str()` function for receiving acknowledgement. The program `P2` simply prints the ID’s and the strings on the console.
- On receiving the acknowledged packet, `P1` sends the next five strings, with the string elements starting from the successor of the acknowledged ID. These above steps repeats unitl all the 50 random strings (alongwith respective indices) are successfully received by `P2`.

### Using FIFO
- `int mkfifo(const char *pathname, mode_t mode)`: makes a FIFO special file with name `pathname`; `mode` specifies the FIFO's permissions.
- `int mknod(const char *pathname, mode_t mode, dev_t dev)`: creates a filesystem node (named pipe) named pathname, with attributes specified by `mode` and `dev`.
- `int open(const char *pathname, int flags)`: opens the file specified by `pathname` with specified flags
- `int close(int fd)`: closes a file descriptor.
- `mode_t umask(mode_t mask)`: sets the calling process's file mode creation mask to mask; umask is used by `open()`;

### Using Message Passsing Queue
- `int msgget(key_t key, int msgflg)`: returns the System V message queue identifier associated with the value of the key argument.
- `int msgctl(int msqid, int cmd, struct msqid_ds *buf)`: performs the control operation specified by cmd on the System V message queue with identifier msqid
- `int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg)`: send messages to a message queue
- `ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)`: receive messages from a message queue

### Using Unix Socket Domain
- `int socket(int domain, int type, int protocol)`: creates an endpoint for communication and returns a file descriptor that refers to that endpoint.
- `int unlink(const char *pathname)`: deletes a name from the file system.
- `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`: assigns the address specified by addr to the socket referred to by the file descriptor sockfd.  addrlen specifies the size, in bytes, of the address structure pointed to by addr.
- `int listen(int sockfd, int backlog)`: make socket referred as passive to accept incoming connection requests.
- `int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen)`: take the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket.
- `ssize_t send(int sockfd, const void *buf, size_t len, int flags);`: transmit a message to another socket.
- `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`: connects the socket referred to by the file descriptor sockfd to the address specified by addr.
- `ssize_t recv(int sockfd, void *buf, size_t len, int flags)`: receive from a socket.


## References:
- [Man pages](https://man7.org/)
- [Die Net](https://linux.die.net/man/)

