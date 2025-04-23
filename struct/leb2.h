#ifndef LEB2_H
#define LEB2_H

#define MAX_SEMESTER_CODE 4 //  `{years}-{term}`
#define SEMESTER_FORMAT "%d-%d" //  `{years}-{term}`
#define MAX_CLASS_CODE 10 // `{subjectID}{id}` Ex MTH101
#define CLASS_FORMAT "%s%d" // `{subjectID}{id}` Ex MTH101

typedef string SemesterCode;
typedef string ClassCode;

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"
#include "../datatype/date-type.h"

#include "../common/status.h"
#include "../common/log.h"
#include "../common/request.h"

#include "file.h"

typedef struct LEB2{
    Semester* semesters; // semester code
} LEB2;

typedef struct Semester{
    Class* classes;
    // struct Semester* next;
    // struct Semester* back;
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

Dashboard* createDashboard(const string description);
Syllabus* createSyllabus(const string description);
Assignment* createAssignment(const string head, const string description, DateTime assignDate, DateTime dueDate);
AssignmentActivity* createAssignmentActivity(const Assignment* assignments);
LearningActivity* createLearningActivity(const string name, const string description, const string imageUrl);
Attendance* createAttendance(const string name, const string description, const string imageUrl);
ScoreBook* createScoreBook(const string name, const string description, const string imageUrl);
LearnIt* createLearnIt(const string name, const string description, const string imageUrl);
Survey* createSurvey(const string name, const string description, const string imageUrl);
Members* createMembers(const string name, const string description, const string imageUrl);
Class* createClass(Dashboard* dashboard, Syllabus* syllabus, AssignmentActivity* assignmentActivity,
                   LearningActivity* learningActivity, Attendance* attendance, ScoreBook* scoreBook,
                   LearnIt* learnIt, Survey* survey, File* files, Members* members);
Semester* createSemester(const Class* classdata);
LEB2* createLEB2(const Semester* semesters);

// Forward declarations
void freeDashboard(Dashboard* dashboard);
void freeSyllabus(Syllabus* syllabus);
void freeAssignment(Assignment* assignment);
void freeAssignmentActivity(AssignmentActivity* activity, int freeAssignments);
void freeLearningActivity(LearningActivity* activity);
void freeAttendance(Attendance* attendance);
void freeScoreBook(ScoreBook* scoreBook);
void freeLearnIt(LearnIt* learnIt);
void freeSurvey(Survey* survey);
void freeMembers(Members* members);
void freeClass(Class* class, int freeComponents);
void freeSemester(Semester* semester, int freeClasses);
void freeLEB2(LEB2* leb2, int freeSemesters);

#endif // LEB2_H