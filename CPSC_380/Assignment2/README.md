## Natalie Huante
## Student ID: 2374481
## huante@chapman.edu
## CPSC 380-01
## Assignment 2: Simple Shell Interface

## Source Files
- sshell.c

## Errors / Deviations
- Note: when you run with the "&" argument appended to your command, the formatting might be disrupted. 
    The "osh>" will appear before the previous command's output. Typing in your next command as normal should 
    fix the formatting again.
- During one of my tests, the "exit" command did not work until the third time I typed it in. After this one 
    time, I have yet to be able to replicate it. I say this in case you happen to encounter the same issue. 
    However, I don't see why this error should occur again. 

## References
- https://stackoverflow.com/questions/35860794/how-to-print-argv-arguments-from-main-function-in-c 
- https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/ 
- https://www.quora.com/What-is-scanf-n#:~:text=Short%20answer%3A,and%20put%20them%20in%20x. 
- https://www.tutorialspoint.com/cprogramming/c_strings.htm 
- https://stackoverflow.com/questions/3213827/how-to-iterate-over-a-string-in-c 
- https://www.geeksforgeeks.org/get-a-substring-in-c/ 
- https://dev-notes.eu/2019/07/Passing-Strings-in-C/
- https://www.geeksforgeeks.org/size_t-data-type-c-language/

## Build Instructions
gcc sshell.c -o sshell.out
./sshell.out

## Sample Output
osh>pwd
/home/nhuante/CPSC_380
osh>ping www.google.com
ping: www.google.com: Temporary failure in name resolution
osh>ls
process.c                             shm-posix-consumer.out                sshell.c     unix_pipe.c
process.out                           shm-posix-producer.c                  sshell.out   unix_pipe.c:Zone.Identifier
shm-posix-consumer.c                  shm-posix-producer.c:Zone.Identifier  sshell2.c    unix_pipe.out
shm-posix-consumer.c:Zone.Identifier  shm-posix-producer.out                sshell2.out
osh>exit
Exiting...