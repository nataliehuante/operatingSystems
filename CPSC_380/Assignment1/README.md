## Natalie Huante
## Student ID: 2374481
## huante@chapman.edu
## CPSC 380-01
## Assignment 1: Simple File Copy

## Source Files
- syscpy.c

## Errors / Deviations
- n/a

## References
- https://www.scaler.com/topics/c/command-line-arguments-in-c/
- https://www.scaler.com/topics/c/c-string-declaration/
- https://jameshfisher.com/2018/02/19/how-to-syscall-in-c/
- https://jameshfisher.com/2018/02/19/how-to-syscall-in-c/
- https://ubuntu.com/tutorials/command-line-for-beginners#4-creating-folders-and-files
- https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
- https://www.quora.com/Why-are-the-system-call-sys_read-and-the-file-descriptor-stdin-used-together-as-they-are-put-in-eax-and-ebx-registers-in-assembly-x86-1 

## Build Instructions
gcc syscpy.c -o syscpy.out
./syscpy.out <inputFileName> <outputFileName>

## Sample Output
When the file copy program executes correctly, it will either advise the user of an error that occurred and why. 
For example, one might see "Bad file descriptor , Unable to write to the output file".
Otherwise, the program will output "execution complete" to the console, signifying a succesfull file copy.