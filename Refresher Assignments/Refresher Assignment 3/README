## Assignment-3 Solutions

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Question-1
### Running Code
    
- Open linux terminal and run
   ```sh
    chmod +x q1.sh
    ./q1.sh dd mm yyyy
   ```
- E.g.: 
   ```sh
    chmod +x q1.sh
    ./q1.sh 15 10 2021
   ```

### Code Explanation
1. First `validate` the number of command line `arguments` as 3.
2. Then validate the year (>=0001) and month (>=1 && <=12).
3. Then using `cal $2 $3 |egrep -v [a-z] |wc -w` check if the date is valid or not.
4. If date is valid then `print` the calender using `cal` command.
5. Else inform the user that this is an `invalid date`.

<br/>

## Question-2
### Running Code
    
- Open linux terminal and run
   ```sh
    chmod +x q2.sh
    ./q2.sh operation operand1 operand2 (or more operands)
   ```
- E.g.: 
   ```sh
    chmod +x q2.sh
    ./q2.sh add 4 5 34
   ```

### Code Explanation
1. First `validate` the number of command line `arguments` as greater than or equal to 3.
2. Then check which operation is to be performed using `if-else`.
3. After that `iterate` over operands and perform the desired operations. For example if operation is sub then subtract op2, op3,.... and so on repeatedly from op1 modifying its value.
4. Finally `print` the result.

<br/>


## Question-3
### Running Code
- Open linux terminal and run
   ```sh
    make run="q3_a"
   ```
- You will be able to see `ouput` of the given default sample `input`
- In order to change the input `open` the file and modify the values in `main()` function only 
- Run `make clean` in linux terminal to delete all the .o files
- E.g.:
    ```sh
    make run="q3_a"
    1 3 4 5 6 7 8 9 10 15 
    1 3 5 6 7 8 9 10 15 
    1 3 5 6 7 8 10 15 
    1 3 5 6 7 8 15 
    1 3 5 6 7 8 15 
    1 3 5 6 8 15 
    ```
---
- Again open linux terminal and run
   ```sh
    make run="q3_b"
   ```
- You will be able to see `ouput` of the given default sample `input`

- In order to change the input `open` the file and modify the values in `main()` function only 
- Run `make clean` in linux terminal to delete all the .o files
- E.g.:
    ```sh
    make run="q3_b"
    30 20 10 25 40 50 
    10 20 25 30 40 50 
    20 10 30 25 
    10 20 25 30 
    25 20 30 
    20 25 30 
    [empty line]
    [empty line]
    ```

### Code Explanation
1. Part-A
   1. Create a `struct Node` with data, Node* left and Node *right as its attributes.
   2. Implement trivial Node attributes setting funcs along with `inorder()` func to print inorder traversal of BST.
   3. `insertBST()` inserts the Node in the BST at whose root node is `Root` at the proper place.
   4. `deleteBST()` deletes the Node with particular key from the BST whose root node is `Root`.
2. Part-B
   1. Create a `struct Node` with height, data, Node* left and Node *right as its attributes.
   2. Implement trivial Node attributes setting funcs along with `inorder()` and `preorder()` func to print inorder and preorder traversal of height balnaced BST or AVL tree.
   3. Create `RR()` and `LL()` functions which performs rotations over the particular node in paricular configuration.
   4. Implement the `balance()` and `balanceDel()` funcs to balance left and right height of a particular node.
   5. `insertBST()` inserts the Node in the BST at whose root node is `Root` at the proper place.
   6. `deleteBST()` deletes the Node with particular key from the BST whose root node is `Root`.

<br/>

## Question-4
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q4"
   ```
- Then enter `no of elems in arrays = n` and `n array elements`
- Then enter `b` for bubble sort and `s` for selection sort to see the sorted Array using chosen sort method
- Run `make clean` in linux terminal to delete all the .o files
- E.g.: 
   ```sh
    make run="q4"
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

