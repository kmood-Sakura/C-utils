#ifndef LEB2_H
#define LEB2_H

#define MAX_SEMESTER_CODE 4 //  `{years}-{term}`
#define SEMESTER_FORMAT "%d-%d" //  `{years}-{term}`
#define MAX_CLASS_CODE 10 // `{subjectID}{id}` Ex MTH101
#define CLASS_FORMAT "%s%d" // `{subjectID}{id}` Ex MTH101

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"
#include "../datatype/date-type.h"

#include "../common/status.h"
#include "../common/log.h"
#include "../common/request.h"

#include "file.h"

typedef struct Assignment Assignment;
typedef struct AssignmentList AssignmentList;
typedef struct AssignmentActivity AssignmentActivity;
typedef struct Dashboard Dashboard;
typedef struct Syllabus Syllabus;
typedef struct LearningActivity LearningActivity;
typedef struct Attendance Attendance;
typedef struct ScoreBook ScoreBook;
typedef struct LearnIt LearnIt;
typedef struct Survey Survey;
typedef struct Members Members;
typedef struct Class Class;
typedef struct ClassList ClassList;
typedef struct Semester Semester;
typedef struct SemesterList SemesterList;
typedef struct LEB2 LEB2;

Assignment createAssignment(const string head, const string description, DateTime assignDate, DateTime dueDate);
AssignmentList* createAssignmentList(Assignment assignment, AssignmentList* next, AssignmentList* prev);
AssignmentActivity* createAssignmentActivity();
Dashboard* createDashboard(const string description);
Syllabus* createSyllabus(const string description);
LearningActivity* createLearningActivity(const string name, const string description, const string imageUrl);
Attendance* createAttendance(const string name, const string description, const string imageUrl);
ScoreBook* createScoreBook(const string name, const string description, const string imageUrl);
LearnIt* createLearnIt(const string name, const string description, const string imageUrl);
Survey* createSurvey(const string name, const string description, const string imageUrl);
Members* createMembers(const string name, const string description, const string imageUrl);
Class createClass(const string classId, Dashboard* dashboard, Syllabus* syllabus,
                 AssignmentActivity* assignmentActivity, LearningActivity* learningActivity,
                 Attendance* attendance, ScoreBook* scoreBook, LearnIt* learnIt,
                 Survey* survey, File* files, Members* members);
ClassList* createClassList(Class class, ClassList* next, ClassList* prev);
Semester createSemester(const string semesterId, ClassList* classList);
SemesterList* createSemesterList(Semester semester, SemesterList* next, SemesterList* prev);
LEB2* createLEB2();

// Deallocation functions
void freeAssignment(Assignment* assignment);
void freeAssignmentList(AssignmentList* head);
void freeAssignmentActivity(AssignmentActivity* activity);
void freeDashboard(Dashboard* dashboard);
void freeSyllabus(Syllabus* syllabus);
void freeLearningActivity(LearningActivity* activity);
void freeAttendance(Attendance* attendance);
void freeScoreBook(ScoreBook* scoreBook);
void freeLearnIt(LearnIt* learnIt);
void freeSurvey(Survey* survey);
void freeMembers(Members* members);
void freeClass(Class* class);
void freeClassList(ClassList* head);
void freeSemester(Semester* semester);
void freeSemesterList(SemesterList* head);
void freeLEB2(LEB2* leb2);

typedef struct Assignment {
    string head;
    string description;
    DateTime assignDate;
    DateTime dueDate;
} Assignment;

typedef struct AssignmentList {
    Assignment assignment; // assignment
    struct AssignmentList* next; // next assignment
    struct AssignmentList* prev; // previous assignment
} AssignmentList;

typedef struct AssignmentActivity {
    AssignmentList* assignmentList; // list of assignments
} AssignmentActivity;

typedef struct Dashboard {
    string description;
} Dashboard;

typedef struct Syllabus {
    string description;
} Syllabus;

typedef struct LearningActivity {
    string name;
    string description;
    string imageUrl;
} LearningActivity;

typedef struct Attendance {
    string name;
    string description;
    string imageUrl;
} Attendance;

typedef struct ScoreBook {
    string name;
    string description;
    string imageUrl;
} ScoreBook;

typedef struct LearnIt {
    string name;
    string description;
    string imageUrl;
} LearnIt;

typedef struct Survey {
    string name;
    string description;
    string imageUrl;
} Survey;

typedef struct Members {
    string name;
    string description;
    string imageUrl;
} Members;

typedef struct Class {
    string classId; // class code
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

typedef struct ClassList {
    Class class; // class
    struct ClassList* next; // next class
    struct ClassList* prev; // previous class
} ClassList;

typedef struct Semester {
    string semesterId; // semester ID
    ClassList* classList; // list of classes
} Semester;

typedef struct SemesterList {
    Semester semester; // semester
    struct SemesterList* next; // next semester
    struct SemesterList* prev; // previous semester
} SemesterList;

typedef struct LEB2 {
    SemesterList* semesterList; // list of semesters
} LEB2;

#endif // LEB2_H