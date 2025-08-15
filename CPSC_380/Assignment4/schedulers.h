#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

#include "taskLinkedList.h"

/*
    Includes the implementation of the scheduling algorithms used by our cpu simulation
*/

void schedule_fcfs();

void schedule_priority();

void schedule_rr();

void schedule_sjf();

void initializeSchedule();

#endif
