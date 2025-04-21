#ifndef LEB2_H
#define LEB2_H

#define MAX_SEMESTER_CODE 4 //  `{years}-{term}`
#define SEMESTER_FORMAT "%d-%d" //  `{years}-{term}`
#define MAX_CLASS_CODE 10 // `{subjectID}{id}` Ex MTH101
#define CLASS_FORMAT "%s%d" // `{subjectID}{id}` Ex MTH101

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"
#include "../datatype/date-type.h"
#include "file.h"

typedef struct LEB2{
    Semester* semesters; // semester code
} LEB2;

typedef struct Semester{
    Class* classes;
} Semester;

typedef struct Class{
    Dashboard* dashboard;
    Syllabus* syllabus;
    AssignmentActivity* assignmentActivity;
    LearningActivity* learningActivity;
    Attendance* attendance;
    ScoreBook* scoreBook;
    LearnIt* learnIt;
    Survey* survey;
    File* files;
    Members* members;
} Class;

typedef struct Dashboard{
    // urlPath path;
    string description;
} Dashboard;

typedef struct Syllabus{
    string description;
} Syllabus;

typedef struct AssignmentActivity{
    Assignment* assignments; // list of assignments
} AssignmentActivity;

typedef struct Assignment {
    string head;
    string description;
    DateTime assignDate;
    DateTime dueDate;
} Assignment;

typedef struct LearningActivity{
    string name;
    string description;
    string imageUrl;
} LearningActivity;

typedef struct Attendance{
    string name;
    string description;
    string imageUrl;
} Attendance;

typedef struct ScoreBook{
    string name;
    string description;
    string imageUrl;
} ScoreBook;

typedef struct LearnIt{
    string name;
    string description;
    string imageUrl;
} LearnIt;

typedef struct Survey{
    string name;
    string description;
    string imageUrl;
} Survey;

typedef struct Members{
    string name;
    string description;
    string imageUrl;
} Members;

#endif // LEB2_H