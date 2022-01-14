## Assignment-1 Solutions

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Question-1
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q1" src="srcFile" dest="destFile"   
   ```
- Run `make clean` in linux terminal to delete all the .o files
- E.g.: After creating a `del` directory create a `h1.c` file and run to see the output
   ```sh
    make run="q1" src="del/h1.c" dest="del/h2.c"   
   ```

### Code Explanation
1. Take command line arguments and open the src and dest files using `fopen()` in read binary and write binary modes respectively.
2. While `feof()` equals 0 read the data using `fread()` form src file and write it to dest file using `fwrite()`.
3. If operation is successful then print `Done copying` and return 0.
4. Else return 1 and close the files using `fclose()` and print the error.

<br/>

## Question-2
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q2"
   ```
- Then enter `num1` and `num2` to see the sum `num1` + `num2`
- Run `make clean` in linux terminal to delete all the .o files
- E.g.: 
   ```sh
    make run="q2"
    Enter num 1: 5242465462666225
    Enter num 2: 25637363630356036
    Sum num 1 + num 2 = 30879829093022261   
   ```

### Code Explanation
1. Take the inputs `num1` and `num2` and store then in char arrays of size 100 as input num can be as large as 2^256-1.
2. Then convert each num to binary using `setCharArr()` and store it in a 32 byte char array.
3. Add the both character array using `addCharArr()` in binary and store it in a_char array.
4. Finally convert the result using `interpretCharArr()` followed by storing it on char array of size 100 and print the sum.
5. `printAns() or printArr()`, `divArr()`, `calPow()`, `addArr()` are some helper functions used to print the char array, divide char array by 2, multiply char array by 2 and add char array and powOfa array respectively.

<br/>

## Question-3
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q3"
   ```
- Then enter `no of elems in arrays = n` and `n array elements` two times to see the swapped array
- Run `make clean` in linux terminal to delete all the .o files
- E.g.: 
   ```sh
    make run="q3"
    Vars before swap d=3 j=-23 
    Vars after swap d=-23 j=3 
    Enter no of elements in the arrays:
    3
    2      
    3
    0
    3
    2
    3
    Arrays after swapping
    3 2 3 
    2 3 0  
   ```

### Code Explanation
1. `swap()` swaps values of two variables using temp variable.
2. `swapArr()` swaps elements of two arrays using `swap()` as helper function.

<br/>

## Question-4
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q4"
   ```
- Then enter `string` to be reversed and press enter to see the reversed string
- Run `make clean` in linux terminal to delete all the .o files
- E.g.: 
   ```sh
    make run="q4"
    Enter the string:
    235eacd345-14
    String before reversing = 235eacd345-14
    String after reversing = 41-543dcae532
   ```

### Code Explanation
1. `swap()` swaps values at two pointers using temp variable.
2. `reverseStr()` reverses the string using `swap()` by swaping `str[i]` with `str[n-i-1]` where i goes from 0 to n/2-1.

## Question-5
### Running Code
    
- Open linux terminal and run
   ```sh
    make run="q5"
   ```
- Then enter `no of elems in arrays = n` and `n array elements` to see the sorted array
- Then `enter no of queries = q` and enter the `q` nums to perform `binary search` over them
- Run `make clean` in linux terminal to delete all the .o files
- E.g.: 
   ```sh
    make run="q5"
    Enter no of elements in the array:
    8 
    4294967290
    4294967295
    10400
    0
    234
    1
    1441
    13551325524
    Sorted array is as follows:
    0 1 234 1441 10400 4294967290 4294967295 13551325524 
    Enter no of queries:
    6
    0
    Found at index 0 
    4294967290
    Found at index 5 
    4294967291
    Element not found!
    4294967295
    Found at index 6 
    13551325524     
    Found at index 7 
    234
    Found at index 2 
   ```

### Code Explanation
1. First the array of unsigned integers taken as the input is sorted using `mergeSort()` and then it is printed.
2. After that for each queriy we perform binary search over the array for the given element using `binarySearch()` function.
3. If element is present in the array then its `index` is printed else we print `-1`.

