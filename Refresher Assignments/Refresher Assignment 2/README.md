## Assignment-2 Solutions

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Question-1
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q1_a" 
   ```
- E.g.: 
   ```sh
    make run="q1_a"
    Matrix created...
    Matrix populated with random numbers... 
    9 8 7 3 6 2 10 
    2 9 7 1 
    8 9 8 6 9 10 
    5 6 10 
    2 8 2 8 4 10 7 
    4 8 
    Matrix displayed...  
   ```
---
- Again open linux terminal and run
   ```sh
    make run="q1_b"   
   ```
- Enter no of queries = `q` then enter `row number` form 1 to 6 and enter `no of columns you want` in that row
- Run `make clean` in linux terminal to delete all the .o files
- E.g.: 
   ```sh
    make run="q1_b"
    [Matrix created] 
    [Matrix populated with random numbers] 
    10 10 7 2 6 3 7 
    1 5 7 6 
    3 4 8 9 7 6 
    5 4 4 
    7 3 7 3 6 6 7 
    1 3 
    [Matrix displayed] 
    Enter the number of queries:
    1
    Enter the row number whose no of columns you want to change (1-6):
    1
    Enter the number of columns you want to have in the row 1 (currently 7 columns):
    1
    10 
    1 5 7 6 
    3 4 8 9 7 6 
    5 4 4 
    7 3 7 3 6 6 7 
    1 3 
    [Matrix displayed] 
   ```

### Code Explanation
1. Part-A
   1. Create a double `ptr` and using `malloc()` allocate 6 row spaces each of size int* to it. Then using `createMatrix()` at each 6 space allocate desired no of columns to it each of size `col_in_rows[i]*sizeof(int)`.
   2. Then using `populateMatrix()` fill up the rand number at each entry with the help of `rand()`.
   3. Finally call `displayMatrix()` to see the given matrix
2. Part-B
   1. Continuing with above steps take queries input and call the `changeMatrix()`.
   2. It will change the no of columns in desired row using `realloc()` if the inputs are valid.

<br/>

## Question-2
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q2_a"
   ```
- Then enter `no of students` and `fill details` for each student (roll and year of joining must be integer)
- Then enter `no of queries` and enter `p` for printing the list of students and `s` for searching a student (also enter `name` in case of searching a student)
- Run `make clean` in linux terminal to delete all the .o files
---
- Again open linux terminal and run
   ```sh
    make run="q2_b"
   ```
- Then enter `no of students` and `fill details` for each student (roll and year of joining must be integer)
- Then enter `no of queries` and enter `p` for printing the list of students and `s` for searching a student (also enter `name` in case of searching a student)
- Run `make clean` in linux terminal to delete all the .o files
---
- Again open linux terminal and run
   ```sh
    make run="q2_c1"
   ```
- Then enter `no of queries` and enter `p` for push operation (also enter `key`), `d` for pop operation and `s` for printing the stack top
- Run `make clean` in linux terminal to delete all the .o files
---
- Again open linux terminal and run
   ```sh
    make run="q2_c2"
   ```
- Then enter `no of queries` and enter `p` for enqueue operation (also enter `key`), `d` for dequeue operation and `s` for printing the queue
- Run `make clean` in linux terminal to delete all the .o files


### Code Explanation
1. Part-A
   1. Create a struct `Node` which will have Node *next, name, roll no, academic program and year of joining as its attributes.
   2. Initialize Node* `head` as NULL. Take queries as input and using `insertLL()` insert the record in singly linked list also updating head pointer.
   3. Using `printList()` print the entire linked list by traversing it and with the `searchLL()` search for a particular record it its exists or not in the given LL.
2. Part-B
   1. Continuing with above just modify the `Node` by adding one more attribute Node *`prev` which will store the pointer to previous node.
   2. Modify `insertLL()` also and update prev pointers for each node to obtain the doubly Linked list.
3. Part-C1
   1. Create a struct `Node` which will have Node *next and data as its attributes.
   2. Implement `printLL()` and `insertAtEndLL()` function same as that of part-A.
   3. Add `deleteFromEndLL()` func which will delete the last inserted node.
   4. `push()` will insert the node at the end of LL and `pop()` will remove the node from end of LL both using above implemented funcs.
   5. `printStackTop()` will print the last node of LL.
4. Part-C2
   1. Create a struct `Node` which will have Node *next and data as its attributes.
   2. Implement `printLL()` and `insertAtEndLL()` function same as that of part-A.
   3. Add `deleteFromStartLL()` func which will delete the head node and update head = head->next.
   4. `enqueue()` will insert the node at the end of LL and `dequeue()` will remove the node from start of LL both using above implemented funcs.
   5.  `printQueue()` will print the all nodes of LL.

<br/>

## Question-3
### Running Code
- Open linux terminal and run
   ```sh
    make run="q3"
   ```
- Then enter `no of queries` and enter operand `a` and operand `b`
- Then enter `0` for add, `1` for subtract, `2` for multplication, `3` for division and `4` for exponentiation operation
- Run `make clean` in linux terminal to delete all the .o files

### Code Explanation
1. First `add()`, `sub()`, `mul()`, `div()`, and `expo()` functions are implemented using simple arithmnetic operations. (Note - word 'expo' is used instead of 'exp' as it was generating error during compilation because of collision with inbuilt exp() function)
2. Using array of pointers of type  `void` all the functions can be accessed through `arr[i]` .
   ```cpp
    void (*arr[]) (int, int) = {add, sub, mul, div, expo};
   ```
3. For calling a particular function we first take opearands and i as input and then call `(*arr[i])(op1,op2)` and print the result.

<br/>

## Question-5
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q5"
   ```
- Then enter `no of elems in arrays = n` and `n array elements`
- Then enter `b` for bubble sort and `s` for selection sort to see the sorted Array using chosen sort method
- Run `make clean` in linux terminal to delete all the .o files
- E.g.: 
   ```sh
    make run="q5"
    5
    23
    -24
    35
    235
    12
    Enter 'b' for bubble sort and 's' for selection sort: s
    Sorted Array using selection sort:
    -24 12 23 35 235 
   ```

### Code Explanation
1. Implement the `bubleSort()` and `selectionSort()` to sort the array of size n.
2. Take the no of elems in array and array elements as input and then sort them using `bubleSort()` or `selectionSort()` as specified by the user.
3. Finally print the resulting sorted array.

