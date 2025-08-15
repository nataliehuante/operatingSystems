#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(int argc, char* argv[]) {
    // argv[1] input file, argv[2] output file


    // 1. OPEN THE INPUT FILE
    const char *inputFileName = argv[1];
    int inFlags = O_RDONLY; // open for read-only
    mode_t inMode = 0; // set to '0' since we are not creating a file
    int inFileCall;

    inFileCall = syscall(SYS_open, inputFileName, inFlags, inMode);

    // if file could not be opened
    if (inFileCall == -1) {
      syscall(SYS_write, 1, strerror(errno), strlen(strerror(errno)));
      syscall(SYS_write, 1, " , Unable to open the input file\n", 34);
      return 1;
    }


    // 2. OPEN THE OUTPUT FILE
    const char *outputFileName = argv[2];// file name
    int outFlags = O_WRONLY; // open for read-only
    mode_t outMode = 0; // set to '0' since we are not creating a file
    int outFileCall;
    
    outFileCall = syscall(SYS_open, outputFileName, outFlags, outMode);

    // if file could not be opened, create it
    if (outFileCall == -1) {
      outFlags = O_CREAT; 
      outMode = 0644; // read the write for the owner, read for others
      outFileCall = syscall(SYS_open, outputFileName, outFlags, outMode);
      if (outFileCall == -1) {
        syscall(SYS_write, 1, strerror(errno), strlen(strerror(errno)));
        syscall(SYS_write, 1, " , Unable to open the output file\n", 35);
        return 1;
      }
    }


    // 3. READ THE INPUT FILE && 4. WRITE TO THE OUTPUT FILE
    char buffer[1024];
    ssize_t bytesRead;
    ssize_t bytesWritten;

    // while the number of bytes read > 0 a.k.a there is something to be read
      // write to the output file
    while ( (bytesRead = syscall(SYS_read, inFileCall, buffer, sizeof(buffer))) > 0) {
      bytesWritten = syscall(SYS_write, outFileCall, buffer, bytesRead);
    }

    // if bytes read but not written
    if (bytesWritten == -1) {
      syscall(SYS_write, 1, strerror(errno), strlen(strerror(errno)));
      syscall(SYS_write, 1, " , Unable to write to the output file\n", 39);
      return 1;
    }


    // 5. CLOSE INPUT AND OUTPUT FILES
    syscall(SYS_close, inFileCall);
    syscall(SYS_close, outFileCall);

    // 6. DISPLAY SUCCESS TO THE CONSOLE
    const char *message = "execution complete\n";
    syscall(SYS_write, 1, message, strlen(message));
    
    return 0;
}