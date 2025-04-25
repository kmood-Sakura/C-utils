#include "../leb2.h"

#include <stdio.h>
#include <stdlib.h>

// Create Assignment (no pointer in the structure)
Assignment createAssignment(const string head, const string description, DateTime assignDate, DateTime dueDate) {
    Assignment assignment;
    assignment.head = createString(head);
    assignment.description = createString(description);
    assignment.assignDate = assignDate;
    assignment.dueDate = dueDate;
    return assignment;
}

// Create AssignmentList node
AssignmentList* createAssignmentList(Assignment assignment, AssignmentList* next, AssignmentList* prev) {
    AssignmentList* newNode = (AssignmentList*)malloc(sizeof(AssignmentList));
    if (newNode != NULL) {
        newNode->assignment = assignment;
        newNode->next = next;
        newNode->prev = prev;
    }
    return newNode;
}

// Create AssignmentActivity
AssignmentActivity* createAssignmentActivity() {
    AssignmentActivity* activity = (AssignmentActivity*)malloc(sizeof(AssignmentActivity));
    if (activity != NULL) {
        activity->assignmentList = NULL; // Initialize with empty list
    }
    return activity;
}

// Create Dashboard
Dashboard* createDashboard(const string description) {
    Dashboard* dashboard = (Dashboard*)malloc(sizeof(Dashboard));
    if (dashboard != NULL) {
        dashboard->description = createString(description);
    }
    return dashboard;
}

// Create Syllabus
Syllabus* createSyllabus(const string description) {
    Syllabus* syllabus = (Syllabus*)malloc(sizeof(Syllabus));
    if (syllabus != NULL) {
        syllabus->description = createString(description);
    }
    return syllabus;
}

// Create LearningActivity
LearningActivity* createLearningActivity(const string name, const string description, const string imageUrl) {
    LearningActivity* activity = (LearningActivity*)malloc(sizeof(LearningActivity));
    if (activity != NULL) {
        activity->name = createString(name);
        activity->description = createString(description);
        activity->imageUrl = createString(imageUrl);
    }
    return activity;
}

// Create Attendance
Attendance* createAttendance(const string name, const string description, const string imageUrl) {
    Attendance* attendance = (Attendance*)malloc(sizeof(Attendance));
    if (attendance != NULL) {
        attendance->name = createString(name);
        attendance->description = createString(description);
        attendance->imageUrl = createString(imageUrl);
    }
    return attendance;
}

// Create ScoreBook
ScoreBook* createScoreBook(const string name, const string description, const string imageUrl) {
    ScoreBook* scoreBook = (ScoreBook*)malloc(sizeof(ScoreBook));
    if (scoreBook != NULL) {
        scoreBook->name = createString(name);
        scoreBook->description = createString(description);
        scoreBook->imageUrl = createString(imageUrl);
    }
    return scoreBook;
}

// Create LearnIt
LearnIt* createLearnIt(const string name, const string description, const string imageUrl) {
    LearnIt* learnIt = (LearnIt*)malloc(sizeof(LearnIt));
    if (learnIt != NULL) {
        learnIt->name = createString(name);
        learnIt->description = createString(description);
        learnIt->imageUrl = createString(imageUrl);
    }
    return learnIt;
}

// Create Survey
Survey* createSurvey(const string name, const string description, const string imageUrl) {
    Survey* survey = (Survey*)malloc(sizeof(Survey));
    if (survey != NULL) {
        survey->name = createString(name);
        survey->description = createString(description);
        survey->imageUrl = createString(imageUrl);
    }
    return survey;
}

// Create Members
Members* createMembers(const string name, const string description, const string imageUrl) {
    Members* members = (Members*)malloc(sizeof(Members));
    if (members != NULL) {
        members->name = createString(name);
        members->description = createString(description);
        members->imageUrl = createString(imageUrl);
    }
    return members;
}

// Create Class
Class createClass(const string classId, Dashboard* dashboard, Syllabus* syllabus,
                 AssignmentActivity* assignmentActivity, LearningActivity* learningActivity,
                 Attendance* attendance, ScoreBook* scoreBook, LearnIt* learnIt,
                 Survey* survey, File* files, Members* members) {
    Class class;
    class.classId = createString(classId);
    class.dashboard = dashboard;
    class.syllabus = syllabus;
    class.assignmentActivity = assignmentActivity;
    class.learningActivity = learningActivity;
    class.attendance = attendance;
    class.scoreBook = scoreBook;
    class.learnIt = learnIt;
    class.survey = survey;
    class.files = files;
    class.members = members;
    return class;
}

// Create ClassList node
ClassList* createClassList(Class class, ClassList* next, ClassList* prev) {
    ClassList* newNode = (ClassList*)malloc(sizeof(ClassList));
    if (newNode != NULL) {
        newNode->class = class;
        newNode->next = next;
        newNode->prev = prev;
    }
    return newNode;
}

// Create Semester
Semester createSemester(const string semesterId, ClassList* classList) {
    Semester semester;
    semester.semesterId = createString(semesterId);
    semester.classList = classList;
    return semester;
}

// Create SemesterList node
SemesterList* createSemesterList(Semester semester, SemesterList* next, SemesterList* prev) {
    SemesterList* newNode = (SemesterList*)malloc(sizeof(SemesterList));
    if (newNode != NULL) {
        newNode->semester = semester;
        newNode->next = next;
        newNode->prev = prev;
    }
    return newNode;
}

// Create LEB2
LEB2* createLEB2() {
    LEB2* leb2 = (LEB2*)malloc(sizeof(LEB2));
    if (leb2 != NULL) {
        leb2->semesterList = NULL; // Initialize with empty list
    }
    return leb2;
}

// Helper function to free strings in structures with name, description, imageUrl
void freeNameDescImage(string name, string description, string imageUrl) {
    free(name);
    free(description);
    free(imageUrl);
}

// Function to free the memory allocated for an Assignment
void freeAssignment(Assignment* assignment) {
    if (assignment != NULL) {
        free(assignment->head);
        free(assignment->description);
        // Note: DateTime is a value type, not a pointer, so no need to free it
    }
}

// Function to free the memory allocated for an AssignmentList
void freeAssignmentList(AssignmentList* head) {
    AssignmentList* current = head;
    while (current != NULL) {
        AssignmentList* next = current->next;
        freeAssignment(&current->assignment);
        free(current);
        current = next;
    }
}

// Function to free the memory allocated for AssignmentActivity
void freeAssignmentActivity(AssignmentActivity* activity) {
    if (activity != NULL) {
        freeAssignmentList(activity->assignmentList);
        free(activity);
    }
}

// Function to free the memory allocated for a Dashboard
void freeDashboard(Dashboard* dashboard) {
    if (dashboard != NULL) {
        free(dashboard->description);
        free(dashboard);
    }
}

// Function to free the memory allocated for a Syllabus
void freeSyllabus(Syllabus* syllabus) {
    if (syllabus != NULL) {
        free(syllabus->description);
        free(syllabus);
    }
}

// Function to free the memory allocated for a LearningActivity
void freeLearningActivity(LearningActivity* activity) {
    if (activity != NULL) {
        freeNameDescImage(activity->name, activity->description, activity->imageUrl);
        free(activity);
    }
}

// Function to free the memory allocated for Attendance
void freeAttendance(Attendance* attendance) {
    if (attendance != NULL) {
        freeNameDescImage(attendance->name, attendance->description, attendance->imageUrl);
        free(attendance);
    }
}

// Function to free the memory allocated for ScoreBook
void freeScoreBook(ScoreBook* scoreBook) {
    if (scoreBook != NULL) {
        freeNameDescImage(scoreBook->name, scoreBook->description, scoreBook->imageUrl);
        free(scoreBook);
    }
}

// Function to free the memory allocated for LearnIt
void freeLearnIt(LearnIt* learnIt) {
    if (learnIt != NULL) {
        freeNameDescImage(learnIt->name, learnIt->description, learnIt->imageUrl);
        free(learnIt);
    }
}

// Function to free the memory allocated for Survey
void freeSurvey(Survey* survey) {
    if (survey != NULL) {
        freeNameDescImage(survey->name, survey->description, survey->imageUrl);
        free(survey);
    }
}

// Function to free the memory allocated for Members
void freeMembers(Members* members) {
    if (members != NULL) {
        freeNameDescImage(members->name, members->description, members->imageUrl);
        free(members);
    }
}

// Function to free the memory allocated for a Class
void freeClass(Class* class) {
    if (class != NULL) {
        free(class->classId);
        freeDashboard(class->dashboard);
        freeSyllabus(class->syllabus);
        freeAssignmentActivity(class->assignmentActivity);
        freeLearningActivity(class->learningActivity);
        freeAttendance(class->attendance);
        freeScoreBook(class->scoreBook);
        freeLearnIt(class->learnIt);
        freeSurvey(class->survey);
        // Assuming there's a function to free File
        // freeFile(class->files);
        freeMembers(class->members);
    }
}

// Function to free the memory allocated for a ClassList
void freeClassList(ClassList* head) {
    ClassList* current = head;
    while (current != NULL) {
        ClassList* next = current->next;
        freeClass(&current->class);
        free(current);
        current = next;
    }
}

// Function to free the memory allocated for a Semester
void freeSemester(Semester* semester) {
    if (semester != NULL) {
        free(semester->semesterId);
        freeClassList(semester->classList);
    }
}

// Function to free the memory allocated for a SemesterList
void freeSemesterList(SemesterList* head) {
    SemesterList* current = head;
    while (current != NULL) {
        SemesterList* next = current->next;
        freeSemester(&current->semester);
        free(current);
        current = next;
    }
}

// Function to free the memory allocated for an LEB2
void freeLEB2(LEB2* leb2) {
    if (leb2 != NULL) {
        freeSemesterList(leb2->semesterList);
        free(leb2);
    }
}