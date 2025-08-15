## Natalie Huante
## Student ID: 2374481
## huante@chapman.edu
## CPSC 380-01
## Assignment 5: Thread Synchronization

## Source Files
    - buffer.h
    - prodcon.c

## Errors / Deviations


## Notes 
    - You may notice that the output of the program sometimes appears as if the consumer consumes an item before the producer produces it. 
        However, this is because the print statement are called outside of the critical section, so the threads then might print ahead of the other. 
        By nature of the program, however, the consumer can't consume that item before the producer produces it and the checksum also allow us to see this. 

## References
    - https://www.appsloveworld.com/c/100/24/sleep-warning-implicit-declaration-of-function-sleep
    - https://www.cse.cuhk.edu.hk/~ericlo/teaching/os/lab/9-PThread/Pass.html
    - https://www.geeksforgeeks.org/multithreading-in-c/
    - https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-pthread-mutex-init-initialize-mutex-object
    - https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
    - https://www.wikihow.com/Delay-in-C#:~:text=Use%20sleep()%20The%20function,the%20time%20in%20milliseconds%20specified.&text=Include%20the%20following%20line%20in,%23include%20%3CTIME.
    - https://www.geeksforgeeks.org/use-posix-semaphores-c/
    - https://stackoverflow.com/questions/50346142/identifier-uint8-t-is-undefined-visual-studio-2017
    - https://learn.zybooks.com/zybook/CHAPMANCPSC380SpringerFall2023/chapter/6/section/6?content_resource_id=79808046
    - https://docs.google.com/document/d/1_YwR38EH9HFkkDr_WrrL47hvru772PeXMglJu4_lbjo/edit#heading=h.m5m5v3qcs51e

## Build Instructions
    gcc prodcon.c -o prodcon.out -lpthread
    ./prodcon.out <delay> <# of producer threads> <# of consumer threads>

## Sample Output
    nhuante@LAPTOP-OULST2B7:~/CPSC_380/Assignment5$ ./prodcon.out 5 5 2
        consumer consumed item 4387
        producer produced item 4387
        producer produced item 3379
        producer produced item 3657
        consumer consumed item 3657
        producer produced item 3949
        producer produced item 4269
        consumer consumed item 3379
        producer produced item 6932
        producer produced item 8626
        producer produced item 7433
        consumer consumed item 3949
        consumer consumed item 4269
        producer produced item 7895
        producer produced item 7684
        producer produced item 11406
        producer produced item 11959
        producer produced item 11832
        consumer consumed item 6932
    nhuante@LAPTOP-OULST2B7:~/CPSC_380/Assignment5$