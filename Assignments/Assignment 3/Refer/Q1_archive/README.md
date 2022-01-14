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
- `struct sched_entity`: 

## Source Files Modified

## Logic Explanation

<br/>