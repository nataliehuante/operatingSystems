#include "schedulers.h"
#include "cpu.h"


// schedules the first task in the list
void schedule_fcfs() {

    // continue scheduling until there are no more tasks to schedule
    while (!isEmpty()) {
        // run the first node for the entirety of the time it needs on the cpu
        run(head, head->burst);

        // remove the task from the list now that it's fully ran
        deleteTask(head->tid);
    }
}

// schedules the task with the highest priority
void schedule_priority() {
    // continue scheduling until there are no more tasks to schedule
    while(!isEmpty()) {
        // run the node with the highest priority
        struct task *temp = head;
        struct task *highest = head;
        int highestPriority = head->priority;

        while (temp != NULL) {
            // check if current task's priority is higher
            if (temp->priority < highestPriority) {
                highestPriority = temp->priority;
                highest = temp;
            }
            temp = temp->next;
        }

        // we found it, now run the highest priority task for its full cpu burst
        run(highest, highest->burst);
        deleteTask(highest->tid);
    }
}

// schedules tasks in a circular pattern with a max duration of 10 milliseconds per task
void schedule_rr() {
    struct task *temp = head;
    struct task *tempNext;

    // continue scheduling until there are no more tasks to schedule
    while (!isEmpty()) {
        int timeToRun = 10;

        // check if the current task needs the 10 ms or less
        if (temp->timeLeft < 10) {
            timeToRun = temp->timeLeft;
        }

        // run the current for the appropriate time 
        run(temp, timeToRun);

        // update the current task's remaining time needed on cpu
        int newTimeLeft = temp->timeLeft - timeToRun;
        // if the task is done, remove it
        if (newTimeLeft <= 0) {
            // before we delete our reference, remember the next task
            tempNext = temp->next;
            if (tempNext == NULL) {
                tempNext = head;
            }
            // delete the completed task
            deleteTask(temp->tid);
            // update our reference 
            temp = tempNext;
            continue;
        }
        else { // if the task is not done yet
            // update the time it has left and continue to the next task
            temp->timeLeft = newTimeLeft;
            tempNext = temp->next;
            if (tempNext == NULL) {
                tempNext = head;
            }
            temp = tempNext;
            continue;
        }
    }
}

// schedules the task with the next shortest cpu burst needed
void schedule_sjf() {
    // continue scheduling until there are no more tasks to schedule
    while(!isEmpty()) {
        // run the node with the shortest burst
        struct task *temp = head;
        struct task *shortest = head;
        int shortestBurst = head->burst;

        while (temp != NULL) {
            // check if the current task's burst is shorter
            if (temp->burst < shortestBurst) {
                shortest = temp;
                shortestBurst = temp->burst;
            }
            temp = temp->next;
        }

        // we found it, now run the shortest task for its full cpu burst
        run(shortest, shortest->burst);
        deleteTask(shortest->tid);
    }
}