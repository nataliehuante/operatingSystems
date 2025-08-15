/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedulers.h"

#define SIZE 100

int main(int argc, char *argv[])
{
   FILE *in; // in stream
   char *temp; // temp holder for line read
   char task[SIZE]; // stores the line read

   char *name;
   int   priority;
   int   burst;

   // if the user did not include the correct arguments
   if (argc != 3) {
      printf("Usage: %s <sched> <taskList> \n", argv[0]);
      return -1;
   }

   // initialize the scheduler
   initializeList();
   
   // open the task list file
   in = fopen(argv[2],"r");
   
   // read the task list file
   while (fgets(task,SIZE,in) != NULL) { 
      /* ARGUMENTS  
         task: array in which the line read will be stored
         SIZE: tha max num of chars that will be read
         in: the file stream from which to read from
      */

      // reads in, formats, and stores the arguments of each task
      temp = strdup(task);
      name = strsep(&temp,",");
      priority = atoi(strsep(&temp,","));
      burst = atoi(strsep(&temp,","));

      // create the task and add the task to the scheduler's list of tasks
      addTask(name,priority,burst);

      // free the memory used for temp
      free(temp);
   }

   // close the file stream 
   fclose(in);

   // invoke the scheduler
   if (strncmp(argv[1], "fcfs", 4) == 0) {
      schedule_fcfs();
   } else if (strncmp(argv[1], "priority", 8) == 0) {
      schedule_priority();
   } else if (strncmp(argv[1], "rr", 2) == 0) {
      schedule_rr();
   } else if (strncmp(argv[1], "sjf", 3) == 0) {
      schedule_sjf();
   } else {
      printf("Error: scheduler '%s' not supported \n", argv[1]);
      return -1;
   }

   return 0;
}
