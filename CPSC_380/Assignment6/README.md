## Natalie Huante
## Student ID: 2374481
## huante@chapman.edu
## CPSC 380-01
## Assignment 6 : Virtual Address Manager

## Source Files
    - vmmgr.c

## Errors / Deviations
    - 

## Notes 
    - Use of AI: I want to acknowledge that I did use Chat GPT in some parts of my process to complete this project. I used this for help with debugging error codes and looking at what typically causes such an error. I also consulted AI when trying to figure out how to mask the bits I needed to for the address. I, at first used an array, but wanted to find a way to do so without an array. Ultimately, I kept the array with the binary representation as a way to check my work, but was able to figure out how to shift the bits and keep the result as a decimal int value. 

## References
    - https://www.ibm.com/docs/en/i/7.1?topic=functions-fopen-open-files
    - https://www.geeksforgeeks.org/return-statement-vs-exit-in-main-in-cpp/
    - https://www.geeksforgeeks.org/error-handling-during-file-operations-in-c-c/
    - https://www.geeksforgeeks.org/error-handling-during-file-operations-in-c-c/
    - https://www.geeksforgeeks.org/typedef-in-c/
    - http://www.mrx.net/c/readfunctions.html
    - https://www.geeksforgeeks.org/why-to-use-fgets-over-scanf-in-c/
    - https://discuss.codechef.com/t/fscanf-going-in-infinite-while-loop-as-eof-is-not-getting-encountered/61046/2
    - https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm
    - https://stackoverflow.com/questions/11543341/reading-strings-integers-etc-from-files-using-fscanf
    - https://www.scaler.com/topics/decimal-to-binary-in-c/
    - https://www.binaryconvert.com/result_signed_int.html?decimal=051051049053051
    - https://www.tutorjoes.in/c_programming_tutorial/convert_binary_to_decimal_using_one_dimensional_array_in_c
    - https://www.geeksforgeeks.org/program-decimal-binary-conversion/
    - https://www.geeksforgeeks.org/c-binary-to-decimal/
    - https://stackoverflow.com/questions/8133074/error-unknown-type-name-bool
    - https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm
    - https://cplusplus.com/forum/beginner/122557/
    - https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
    - https://www.geeksforgeeks.org/fread-function-in-c/
    - https://hexed.it/
    - https://calculator.name/baseconvert/decimal/hexadecimal/12107


## Build Instructions
    gcc vmmgr.c -o vmmgr.out
    ./vmmgr.out <input file>

    // you must also have the BACKING_STORE.bin file in your local directory in addition to the input file

## Sample Output

given the following as an input file: 
1
256
32768
32769
128
65534
33153
25

the output is as follows:
nhuante@LAPTOP-OULST2B7:~/CPSC_380/Assignment6$ ./vmmgr.o test_addresses.txt
------ 1 ------
virtual address: 1    [ 0000 0000 0000 0000 0000 0000 0000 0001 ]
page number: 0    [ 0000 0000 ]
page offset: 1    [ 0000 0001 ]
frame number: 0
translated physical address: 1
signed byte stored: 0

------ 2 ------
virtual address: 256    [ 0000 0000 0000 0000 0000 0001 0000 0000 ]
page number: 1    [ 0000 0001 ]
page offset: 0    [ 0000 0000 ]
frame number: 1
translated physical address: 256
signed byte stored: 0

------ 3 ------
virtual address: 32768    [ 0000 0000 0000 0000 1000 0000 0000 0000 ]
page number: 128    [ 1000 0000 ]
page offset: 0    [ 0000 0000 ]
frame number: 128
translated physical address: 32768
signed byte stored: 0

------ 4 ------
virtual address: 32769    [ 0000 0000 0000 0000 1000 0000 0000 0001 ]
page number: 128    [ 1000 0000 ]
page offset: 1    [ 0000 0001 ]
frame number: 128
translated physical address: 32769
signed byte stored: 0

------ 5 ------
virtual address: 128    [ 0000 0000 0000 0000 0000 0000 1000 0000 ]
page number: 0    [ 0000 0000 ]
page offset: 128    [ 1000 0000 ]
frame number: 0
translated physical address: 128
signed byte stored: 0

------ 6 ------
virtual address: 65534    [ 0000 0000 0000 0000 1111 1111 1111 1110 ]
page number: 255    [ 1111 1111 ]
page offset: 254    [ 1111 1110 ]
frame number: 255
translated physical address: 65534
signed byte stored: 63

------ 7 ------
virtual address: 33153    [ 0000 0000 0000 0000 1000 0001 1000 0001 ]
page number: 129    [ 1000 0001 ]
page offset: 129    [ 1000 0001 ]
frame number: 129
translated physical address: 33153
signed byte stored: 0

------ 8 ------
virtual address: 25    [ 0000 0000 0000 0000 0000 0000 0001 1001 ]
page number: 0    [ 0000 0000 ]
page offset: 25    [ 0001 1001 ]
frame number: 0
translated physical address: 25
signed byte stored: 0

------ Overall Stats ------
Page-fault rate: 0.625000
TLB-hit rate: 0.375000

nhuante@LAPTOP-OULST2B7:~/CPSC_380/Assignment6$
    