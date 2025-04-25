#ifndef CALENDAR_H 
#define CALENDAR_H

#include "../datatype/date-type.h"
#include "../datatype/int-type.h"   
#include "../datatype/string-type.h"

#include "../common/status.h"
#include "../common/log.h"

typedef struct Task Task;
typedef struct TaskList TaskList;
typedef struct Calendar Calendar;

// Creation functions
Task createTask(const string title, const string location, DateTime setBegin, DateTime setEnd, DateTime dueDate);
TaskList* createTaskList(Task task, TaskList* next, TaskList* prev);
Calendar* createCalendar(Date date, TaskList* taskList);

// Deallocation functions
void freeTask(Task* task);
void freeTaskList(TaskList* head);
void freeCalendar(Calendar* calendar);

typedef struct Task {
    string title;     // task title
    string location;  // task location
    DateTime setBegin;
    DateTime setEnd;  // task set date and time
    DateTime dueDate; // task due date (optional to extend setEnd)
} Task;

typedef struct TaskList {
    Task task;              // task
    struct TaskList* next;   // next task
    struct TaskList* prev;   // previous task
} TaskList;

typedef struct Calendar {
    Date date;               // date
    TaskList* taskList;      // list of tasks
} Calendar;

#endif // CALENDAR_H