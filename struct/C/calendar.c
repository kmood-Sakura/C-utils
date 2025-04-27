#include "../calendar.h"

#include <stdio.h>
#include <stdlib.h>

error allocateCalendarList(CalendarList** calendarList) {
    if (calendarList == NULL) {
        return "Calendar list pointer is required"; // Invalid calendar list pointer
    }
    if (*calendarList != NULL) {
        return NULL; // Invalid calendarList pointer
    }
    
    *calendarList = (CalendarList*)malloc(sizeof(CalendarList));
    if (calendarList == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    (*calendarList)->next = NULL; // Initialize next
    (*calendarList)->prev = NULL; // Initialize prev

    return NULL; // Success
}

error allocateCalendar(Calendar** calendar) {
    if (calendar == NULL) {
        return "Calendar pointer is required"; // Invalid calendar pointer
    }
    if (*calendar != NULL) {
        return NULL; // Invalid calendar pointer
    }
    
    (*calendar) = (Calendar*)malloc(sizeof(Calendar));
    if (calendar == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    (*calendar)->taskList = NULL; // Initialize tasks

    return NULL; // Success
}

error allocateTaskList(TaskList** taskList) {
    if (*taskList != NULL) {
        return NULL; // Invalid taskList pointer
    }
    
    (*taskList) = (TaskList*)malloc(sizeof(TaskList));
    if (taskList == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    (*taskList)->next = NULL; // Initialize next
    (*taskList)->prev = NULL; // Initialize prev
    
    return NULL; // Success
}

error allocateTask(Task** task) {
    if (task == NULL) {
        return "Task pointer is required"; // Invalid task pointer
    }
    if (*task != NULL) {
        return NULL; // Invalid task pointer
    }
    
    *task = (Task*)malloc(sizeof(Task));
    if (task == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    (*task)->title = NULL; // Initialize title
    (*task)->location = NULL; // Initialize location

    return NULL; // Success
}

error createCalendar(Calendar* calendar, Date date, TaskList* tasklist) {
    if (calendar == NULL) {
        return "Calendar pointer is required"; // Invalid calendar pointer
    }
    if (tasklist == NULL) {
        return "Task list is required"; // Invalid task list pointer
    }

    calendar->date = date; // Copy date
    calendar->taskList = tasklist; // Copy task list

    return NULL; // Success
}

error createCalendarListNode(CalendarList** calendarList, Calendar calendar) {
    if (*calendarList != NULL) {
        return "Calendar list node pointer must be NULL"; // Invalid calendar list node pointer
    }
    
    *calendarList = (CalendarList*)malloc(sizeof(CalendarList));
    if (*calendarList == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    
    (*calendarList)->calendar = calendar; // Copy calendar
    (*calendarList)->next = NULL; // Initialize next
    (*calendarList)->prev = NULL; // Initialize prev
    
    return NULL; // Success
}

error addCalendarToList(CalendarList** head, Calendar calendar) {
    if (head == NULL) {
        return "Calendar list head pointer is required"; // Invalid calendar list head pointer
    }
    
    CalendarList* newNode = NULL;
    error err = createCalendarListNode(&newNode, calendar); // Create a new calendar list node
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    
    if (*head == NULL) {
        *head = newNode; // If the list is empty, set the new node as the head
    } else {
        CalendarList* current = *head;
        while (current->next != NULL) {
            current = current->next; // Traverse to the end of the list
        }
        current->next = newNode; // Add the new node at the end of the list
        newNode->prev = current; // Set the previous pointer of the new node
    }
    
    return NULL; // Success
}

error createTask(Task* task, string title, string location, DateTime setBegin, DateTime setEnd, DateTime dueDate) {
    if (task == NULL) {
        return "Task pointer is required"; // Invalid task pointer
    }
    if (title == NULL || location == NULL) {
        return "Title and location are required"; // Invalid parameters
    }
    
    task->title = title; // Copy title
    task->location = location; // Copy location
    task->setBegin = setBegin; // Copy setBegin
    task->setEnd = setEnd; // Copy setEnd
    task->dueDate = dueDate; // Copy dueDate
    
    return NULL; // Success
}

error createTaskListNode(TaskList** taskList, Task task) {
    if (*taskList != NULL) {
        return "Task list node pointer must be NULL"; // Invalid task list node pointer
    }
    
    *taskList = (TaskList*)malloc(sizeof(TaskList));
    if (*taskList == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    
    (*taskList)->task = task; // Copy task
    (*taskList)->next = NULL; // Initialize next
    (*taskList)->prev = NULL; // Initialize prev
    
    return NULL; // Success
}

error addTaskToTaskList(TaskList** head, Task task) {
    if (head == NULL) {
        return "Task list head pointer is required"; // Invalid task list head pointer
    }
    
    TaskList* newNode = NULL;
    error err = createTaskListNode(&newNode, task); // Create a new task list node
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    
    if (*head == NULL) {
        *head = newNode; // If the list is empty, set the new node as the head
    } else {
        TaskList* current = *head;
        while (current->next != NULL) {
            current = current->next; // Traverse to the end of the list
        }
        current->next = newNode; // Add the new node at the end of the list
        newNode->prev = current; // Set the previous pointer of the new node
    }
    
    return NULL; // Success
}

void FreeTaskContent(Task* task) {
    if (task == NULL) return;
    if (task->title != NULL) {
        FreeString(&task->title); // Free title string
    }
    if (task->location != NULL) {
        FreeString(&task->location); // Free location string
    }
}

void FreeTask(Task* task) {
    if (task == NULL) return; // Invalid task pointer
    FreeTaskContent(task); // Free task content
    free(task); // Free task structure
}

// Function to free the memory allocated for a TaskList
void FreeTaskList(TaskList* head) {
    if (head == NULL)return; // Nothing to free

    TaskList* current = head->next;
    while( current != NULL) {
        TaskList* next = current->next;
        FreeTaskContent(&current->task); // Free the task in the node
        free(current); // Free the node
        current = next; // Move to the next node
    }

    current = head->prev;
    while(current != NULL) {
        TaskList* next = current->prev;
        FreeTaskContent(&current->task); // Free the task in the node
        free(current); // Free the node
        current = next; // Move to the next node
    }

    FreeTaskContent(&head->task); // Free the task in the head node
    free(head); // Free the head node
}

void FreeCalendarContent(Calendar* calendar) {
    if (calendar == NULL) return; // Invalid calendar pointer

    FreeTaskList(calendar->taskList); // Free task list
    calendar->taskList = NULL; // Reset task list pointer
    Date set = {0};
    calendar->date = set; // Reset date
}

// Function to free the memory allocated for a Calendar
void FreeCalendar(Calendar* calendar) {
    if (calendar == NULL) return; // Invalid calendar pointer

    FreeCalendarContent(calendar); // Free calendar content
    free(calendar); // Free calendar structure
}

void FreeCalendarList(CalendarList* calendarList) {
    if (calendarList == NULL) return;

    CalendarList* current = calendarList->next;
    while (current != NULL) {
        CalendarList* next = current->next;
        FreeCalendarContent(&current->calendar); // Free the calendar in the node
        free(current); // Free the node
        current = next; // Move to the next node
    }

    current = calendarList->prev;
    while (current != NULL) {
        CalendarList* next = current->prev;
        FreeCalendarContent(&current->calendar); // Free the calendar in the node
        free(current); // Free the node
        current = next; // Move to the next node
    }

    FreeCalendarContent(&calendarList->calendar); // Free the calendar in the head node
    free(calendarList); // Free the head node
}