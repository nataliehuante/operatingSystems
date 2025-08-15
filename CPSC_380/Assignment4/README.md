## Natalie Huante
## Student ID: 2374481
## huante@chapman.edu
## CPSC 380-01
## Assignment 4: CPU Scheduling

## Source Files
- task.h
- taskLinkedList.h
- taskLinkedList.c
- schedulers.h
- schedulers.c
- cpu.h
- cpu.c
- ssched.c

## Errors / Deviations

## Notes 
- When running the program, the scheduling algorithm options are as follows: fcfs , priority , sjf , rr

## References
- https://stackoverflow.com/questions/1403890/how-do-you-implement-a-class-in-c
- https://stackoverflow.com/questions/64189225/errors-multiple-definition-and-first-defined-here
- https://stackoverflow.com/questions/30821356/multiple-definition-first-defined-here-errors
- https://stackoverflow.com/questions/8133074/error-unknown-type-name-bool
- https://www.geeksforgeeks.org/bool-in-c/
- https://stackoverflow.com/questions/19765536compile-all-c-files-in-a-directory-using-gcc-compiler-in-cmd
- https://www.geeksforgeeks.org/arrow-operator-in-c-c-with-examples/
- https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
- https://www.geeksforgeeks.org/strdup-strdndup-functions-c/
- https://chat.openai.com (used for debugging the "multiple definition of `head'; /tmp/ccZB0tQS.o:(.bss+0x0): first defined here" error)

## Build Instructions
gcc *.c -o ssched.out
./ssched.out <scheduling algorithm> <task list text document>

## Sample Output
#### Given this text file
```
P1, 4, 15
P2, 1, 3
P3, 2, 1
P4, 2, 7
P5, 3, 4
P6, 3, 22
```

#### First Come First Serve
```
nhuante@LAPTOP-OULST2B7:~/CPSC_380/Assignment4$ ./ssched.out fcfs TaskList.txt
Running task = [P1] [4] [15] for 15 units.
Running task = [P2] [1] [3] for 3 units.
Running task = [P3] [2] [1] for 1 units.
Running task = [P4] [2] [7] for 7 units.
Running task = [P5] [3] [4] for 4 units.
Running task = [P6] [3] [22] for 22 units.
```

#### Priority
```
nhuante@LAPTOP-OULST2B7:~/CPSC_380/Assignment4$ ./ssched.out priority TaskList.txt
Running task = [P2] [1] [3] for 3 units.
Running task = [P3] [2] [1] for 1 units.
Running task = [P4] [2] [7] for 7 units.
Running task = [P5] [3] [4] for 4 units.
Running task = [P6] [3] [22] for 22 units.
Running task = [P1] [4] [15] for 15 units.
```

#### Round Robin
```
nhuante@LAPTOP-OULST2B7:~/CPSC_380/Assignment4$ ./ssched.out rr TaskList.txt
Running task = [P1] [4] [15] for 10 units.
Running task = [P2] [1] [3] for 3 units.
Running task = [P3] [2] [1] for 1 units.
Running task = [P4] [2] [7] for 7 units.
Running task = [P5] [3] [4] for 4 units.
Running task = [P6] [3] [22] for 10 units.
Running task = [P1] [4] [15] for 5 units.
Running task = [P6] [3] [22] for 10 units.
Running task = [P6] [3] [22] for 2 units.
```

#### Shortest Job First
```
nhuante@LAPTOP-OULST2B7:~/CPSC_380/Assignment4$ ./ssched.out sjf TaskList.txt
Running task = [P3] [2] [1] for 1 units.
Running task = [P2] [1] [3] for 3 units.
Running task = [P5] [3] [4] for 4 units.
Running task = [P4] [2] [7] for 7 units.
Running task = [P1] [4] [15] for 15 units.
Running task = [P6] [3] [22] for 22 units.
```