#ifndef CALENDAR_H 
#define CALENDAR_H

#include "../datatype/date-type.h"
#include "../datatype/int-type.h"   
#include "../datatype/string-type.h"

typedef struct Task Task;
typedef struct TaskList TaskList;
typedef struct Calendar Calendar;
typedef struct CalendarList CalendarList;

error allocateCalendarList(CalendarList** calendarList);
error allocateCalendar(Calendar** calendar);
error allocateTaskList(TaskList** taskList);
error allocateTask(Task** task);

error createCalendar(Calendar* calendar, Date date, TaskList* tasklist);
error createCalendarListNode(CalendarList** calendarList, Calendar calendar);
error addCalendarToList(CalendarList** head, Calendar calendar);

error createTask(Task* task, string title, string location, DateTime setBegin, DateTime setEnd, DateTime dueDate);
error createTaskListNode(TaskList** taskList, Task task);
error addTaskToTaskList(TaskList** head, Task task);

void FreeTaskContent(Task* task);
void FreeTaskList(TaskList* head);
void FreeCalendarContent(Calendar* calendar);
void FreeCalendarList(CalendarList* calendarList);

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

typedef struct CalendarList {
    Calendar calendar; // calendar
    struct CalendarList* next; // next calendar
    struct CalendarList* prev; // previous calendar
} CalendarList;

#endif // CALENDAR_H