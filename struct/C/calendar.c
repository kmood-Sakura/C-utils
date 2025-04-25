#include "../calendar.h"

#include <stdio.h>
#include <stdlib.h>

// Create Task
Task createTask(const string title, const string location, DateTime setBegin, DateTime setEnd, DateTime dueDate) {
    Task task;
    task.title = createString(title);
    task.location = createString(location);
    task.setBegin = setBegin;
    task.setEnd = setEnd;
    task.dueDate = dueDate;
    return task;
}

// Create TaskList node
TaskList* createTaskList(Task task, TaskList* next, TaskList* prev) {
    TaskList* newNode = (TaskList*)malloc(sizeof(TaskList));
    if (newNode != NULL) {
        newNode->task = task;
        newNode->next = next;
        newNode->prev = prev;
    }
    return newNode;
}

// Create Calendar
Calendar* createCalendar(Date date, TaskList* taskList) {
    Calendar* calendar = (Calendar*)malloc(sizeof(Calendar));
    if (calendar != NULL) {
        calendar->date = date;
        calendar->taskList = taskList;
    }
    return calendar;
}

void freeTask(Task* task) {
    if (task != NULL) {
        free(task->title);     // Free title string
        free(task->location);  // Free location string
        // Note: DateTime is a value type, not a pointer, so no need to free it
    }
}

// Function to free the memory allocated for a TaskList
void freeTaskList(TaskList* head) {
    TaskList* current = head;
    while (current != NULL) {
        TaskList* next = current->next;
        freeTask(&current->task); // Free the task in the list
        free(current);
        current = next;
    }
}

// Function to free the memory allocated for a Calendar
void freeCalendar(Calendar* calendar) {
    if (calendar != NULL) {
        freeTaskList(calendar->taskList);
        free(calendar);
    }
}