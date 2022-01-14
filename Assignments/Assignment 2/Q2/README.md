## Assignment-2

- Extract the `2020004.zip` file.
- Now, you are ready to go!

## Question-2
### Testing System Call
    
- Open linux terminal in the current directory and run
   ```sh
    make 
   ```
- After that you will be able to see the desired output on terminal itself for checking the `kernel_2d_memcpy()` system call
- Run `make clean` in linux terminal to clean up the directory

### Apply Diff/Patch file to Kernel
- There are two patch/diff files in the Q2 directory
  - `myPatch_small.patch` contains the changes done in `sys.c` and `syscall_64.tbl` file only
  - `myPatch.patch` contains all the changes in whole kernel source code after the `make` command
- To apply patch file, run
  ```sh
   git apply myPatch_small.patch
   OR
   git apply myPatch.patch
  ```

### Code Explanation
1. First add the entry of `kernel_2d_memcpy()` system call in the `syscall_64.tbl`, then give its defintion in `sys.c` file.
2. Declare a temporary float array to store the original array in kernel space. Allocate memory space to it using `kmalloc()`. 
3. Copy the array to this new array using `copy_from_user()` kernel function.
4. Then check whether these `src` and `dest` pointers are accessible by the kernel or not, as a security check (Note, these pointers can also be pointing to some kernel addresses). If not then return `-EFAULT`.
5. Using `copy_to_user()` kernel function copy the array elements from the temp arr to `dest` pointer arr. If `ret_val` > 0 it means unsuccessful copy so report it.
6. In case of error at any point just free the temp arr pointer and return `-EFAULT`. Return `0` if all goes well till the end and copy is `successful`.
7. After that create a test `c` file to run the system call using `syscall()` function. Pass the id of `syscall`, `pointer` to 2D floating point array, `pointer` to location where array is to be copied and total `size` of array in bytes to this function.
8. Finally observe the `output` on the terminal to verify the working of system call.

<br/>