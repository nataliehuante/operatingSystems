#include "taskLinkedList.h"

struct task *head;
struct task *current;
int currentTID;

// initialize the head and current nodes
void initializeList() {
    head = NULL; 
    current = NULL;
    currentTID = 1;
}


// add a task to the linked list
void addTask(char *name, int priority, int burst) {
    // allocates memory for the new task node
    struct task *newTask = (struct task*) malloc(sizeof(struct task));

    // if no memory allocated, don't continue
    if (newTask == NULL){
        printf("new task unable to allocate memory");
        return;
    }

    // increment task id number
    currentTID++;

    // initialize variables for new task node
    newTask->name = strdup(name);
    newTask->tid = currentTID;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->next = NULL;
    newTask->timeLeft = burst;

    // iterate through the current linked list and insert the new node at the end
    
    // if the list is empty, new node is head
    if (head == NULL) {
        head = newTask;
    }
    else { // if list is not empty
        // iterate until next of current node is NULL
        current = head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newTask;
        current = NULL;
    }

}

// print the linked list 
void printList() {
    current = head;
    while (current != NULL) {
        printf("Name: %s, Priority: %d, BurstL %d\n", current->name, current->priority, current->burst);
        current = current->next;
    }
    current = NULL;
}

// delete a task 
void deleteTask(int Tid) {
    struct task *temp = head;
    struct task *prev;

    // if the first task is the target node
    if ( (temp != NULL) && (temp->tid == Tid) ){
        // remove the head node
        head = temp->next;
        return;
    }

    // if not the first task, look for the task 
    while ( (temp != NULL) && (temp->tid != Tid) ) {
        prev = temp;
        temp = temp->next;
    }

    // if we iterate to the end of the list & target task is not present
    if (temp == NULL) {
        return;
    }

    // if we found the target task, we wille execute the below
    prev->next = temp->next;
    
}


// returns if the list is empty
bool isEmpty() {
    if (head == NULL) {
        return true;
    }
    return false;
}