#ifndef TASKLINKEDLIST_H
#define TASKLINKEDLIST_H

#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// declare the head and current nodes of the list
extern struct task *head;
extern struct task *current;
extern int currentTID;

void initializeList();

// add a task to the linked list
void addTask(char *name, int priority, int burst);

// print the linked list 
void printList();

// delete a task 
void deleteTask(int Tid);

// check if the linked list is empty
bool isEmpty();

#endif
