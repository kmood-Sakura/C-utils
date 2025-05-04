#ifndef LEB_2_H
#define LEB_2_H

#define MAX_SEMESTER_CODE 4 //  `{years}-{term}`
#define SEMESTER_FORMAT "%d-%d" //  `{years}-{term}`
#define MAX_CLASS_CODE 10 // `{subjectID}{id}` Ex MTH101
#define CLASS_FORMAT "%s%d" // `{subjectID}{id}` Ex MTH101

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"
#include "../datatype/date-type.h"
#include "../datatype/float-type.h"

#include "file.h"

typedef struct Assignment Assignment;
typedef struct AssignmentList AssignmentList;
typedef struct AssignmentActivity AssignmentActivity;
typedef struct Dashboard Dashboard;
typedef struct Syllabus Syllabus;
typedef struct LearningActivity LearningActivity;
typedef struct LearningActivityList LearningActivityList;
typedef struct Attendance Attendance;
typedef struct AttendanceList AttendanceList;
typedef struct ScoreBook ScoreBook;
typedef struct ScoreBookList ScoreBookList;
typedef struct LearnIt LearnIt;
typedef struct LearnItList LearnItList;
typedef struct Survey Survey;
typedef struct Member Member;
typedef struct MemberList MemberList;
typedef struct FileList FileList;
typedef struct Class Class;
typedef struct ClassList ClassList;
typedef struct Semester Semester;
typedef struct SemesterList SemesterList;
typedef struct LEB2 LEB2;


// allocate functions
error allocateDashboard(Dashboard** dashboard);
error allocateSyllabus(Syllabus** syllabus);
error allocateAssignmentList(AssignmentList** node);
error allocateLearningActivityList(LearningActivityList** node);
error allocateAttendanceList(AttendanceList** node);
error allocateScoreBookList(ScoreBookList** node);
error allocateLearnItList(LearnItList** node);
error allocateSurvey(Survey** survey);
error allocateMemberList(MemberList** node);
error allocateFileList(FileList** node);
error allocateClass(Class** class);
error allocateClassList(ClassList** node);
error allocateSemester(Semester** semester);
error allocateSemesterList(SemesterList** node);
error allocateLEB2(LEB2** leb2);

// create functions
error createAssignment(Assignment* assignment, const string head, const string description, 
                     DateTime assignDate, DateTime dueDate);
error createAssignmentListNode(AssignmentList** node, Assignment assignment);
error createDashboard(Dashboard* dashboard, const string description);
error createSyllabus(Syllabus* syllabus, const string description);
error createLearningActivity(LearningActivity* activity, const string head, 
                           const string description, const string url, File* file);
error createLearningActivityListNode(LearningActivityList** node, LearningActivity activity);
error createAttendance(Attendance* attendance, code code, DateTime date);
error createAttendanceListNode(AttendanceList** node, Attendance attendance);
error createScoreBook(ScoreBook* scoreBook, const string head, const string description, float score);
error createScoreBookListNode(ScoreBookList** node, ScoreBook scoreBook);
error createLearnIt(LearnIt* learnIt, const string name, const string description, const string url);
error createLearnItListNode(LearnItList** node, LearnIt learnIt);
error createSurvey(Survey* survey);
error createMember(Member* member, const string studentId, const string name);
error createMemberListNode(MemberList** node, Member member);
error createFileListNode(FileList** node, File file);
error createClass(Class* class,
                const string classId, Dashboard* dashboard, Syllabus* syllabus, AssignmentList* assignmentList,
                LearningActivityList* learningActivityList, AttendanceList* attendanceList, ScoreBookList* scoreBookList,
                LearnItList* learnItList, FileList* fileList, Survey* survey, MemberList* memberList);
error createClassListNode(ClassList** node, Class class);
error createSemester(Semester* semester, const uint8 year, const uint8 term, ClassList* classList);
error createSemesterListNode(SemesterList** node, Semester semester);
error createLEB2(LEB2* leb2, SemesterList* semesterList);

// append list functions
error addAssignmentToList(AssignmentList** head, Assignment assignment);
error addLearningActivityToList(LearningActivityList** head, LearningActivity activity);
error addAttendanceToList(AttendanceList** head, Attendance attendance);
error addScoreBookToList(ScoreBookList** head, ScoreBook scoreBook);
error addLearnItToList(LearnItList** head, LearnIt learnIt);
error addMemberToList(MemberList** head, Member member);
error addFileToList(FileList** head, File file);
error addClassToList(ClassList** head, Class class);
error addSemesterToList(SemesterList** head, Semester semester);

// free functions
void FreeDashboard(Dashboard* dashboard);
void FreeSyllabus(Syllabus* syllabus);
void FreeSurvey(Survey* survey);

void FreeAssignmentContents(Assignment* assignment);
void FreeAssignmentList(AssignmentList* head);
void FreeLearningActivityContents(LearningActivity* activity);

void FreeLearningActivityList(LearningActivityList* head);
void FreeAttendanceContent(Attendance* attendance);
void FreeAttendanceList(AttendanceList* head);

void FreeScoreBookContents(ScoreBook* scoreBook);
void FreeScoreBookList(ScoreBookList* head);

void FreeLearnItContents(LearnIt* learnIt);
void FreeLearnItList(LearnItList* head);

void FreeMemberContents(Member* member);
void FreeMember(Member* member);
void FreeMemberList(MemberList* head);

void FreeFileList(FileList* head);

void FreeClassContents(Class* class);
void FreeClass(Class* class);
void FreeClassList(ClassList* head);

void FreeSemesterContents(Semester* semester);
void FreeSemesterList(SemesterList* head);

void FreeLEB2Contents(LEB2* leb2);
void FreeLEB2(LEB2* leb2);

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

typedef struct Dashboard {
    string description;
} Dashboard;

typedef struct Syllabus {
    string description;
} Syllabus;

typedef struct LearningActivity {
    string head;
    string description;
    string url; // can be NULL
    File* file; // can be NULL
} LearningActivity;

typedef struct LearningActivityList {
    LearningActivity learningActivity; // learning activity
    struct LearningActivityList* next; // next learning activity
    struct LearningActivityList* prev; // previous learning activity
} LearningActivityList;

typedef struct Attendance {
    code joined; // attendance
    DateTime date; // date
} Attendance;

typedef struct AttendanceList {
    Attendance attendance; // attendance
    struct AttendanceList* next; // next attendance
    struct AttendanceList* prev; // previous attendance
} AttendanceList;

typedef struct ScoreBook {
    string head;
    string description;
    float32 score; // score //can be negative !!need to check
} ScoreBook;

typedef struct ScoreBookList {
    ScoreBook scoreBook; // score book
    struct ScoreBookList* next; // next score book
    struct ScoreBookList* prev; // previous score book
} ScoreBookList;

typedef struct LearnIt {
    string name;
    string description;
    string url;
} LearnIt;

typedef struct LearnItList {
    LearnIt learnIt; // learn it
    struct LearnItList* next; // next learn it
    struct LearnItList* prev; // previous learn it
} LearnItList;

typedef struct Survey {
    // nothing for now !!!!!!!
    // string name;
    // string description;
    // string imageUrl;
} Survey;

typedef struct Member {
    string studentId; // student ID
    string name;
} Member;

typedef struct MemberList {
    Member member; // member
    struct MemberList* next; // next member
    struct MemberList* prev; // previous member
} MemberList;

typedef struct FileList {
    File file; // file
    struct FileList* next; // next file
    struct FileList* prev; // previous file
} FileList;

typedef struct Class {
    string classId; // class code
    Dashboard* dashboard;
    Syllabus* syllabus;
    AssignmentList* assignmentList;
    LearningActivityList* learningActivityList;
    AttendanceList* attendanceList;
    ScoreBookList* scoreBookList;
    LearnItList* learnItList;
    FileList* fileList; // list of files
    Survey* survey;
    MemberList* memberList;
} Class;

typedef struct ClassList {
    Class class; // class
    struct ClassList* next; // next class
    struct ClassList* prev; // previous class
} ClassList;

typedef struct Semester {
    uint8 year; // year
    uint8 term; // term
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