#include "../leb2.h"

#include <stdio.h>
#include <stdlib.h>

// Dashboard allocation
error allocateDashboard(Dashboard** dashboard) {
    if (*dashboard != NULL) {
        return "Dashboard pointer must be NULL";
    }
    
    *dashboard = (Dashboard*)malloc(sizeof(Dashboard));
    if (*dashboard == NULL) {
        return "Memory allocation failed";
    }
    
    (*dashboard)->description = NULL;
    
    return NULL;
}

// Syllabus allocation
error allocateSyllabus(Syllabus** syllabus) {
    if (*syllabus != NULL) {
        return "Syllabus pointer must be NULL";
    }
    
    *syllabus = (Syllabus*)malloc(sizeof(Syllabus));
    if (*syllabus == NULL) {
        return "Memory allocation failed";
    }
    
    (*syllabus)->description = NULL;
    
    return NULL;
}

// AssignmentList allocation
error allocateAssignmentList(AssignmentList** node) {
    if (*node != NULL) {
        return "AssignmentList node pointer must be NULL";
    }
    
    *node = (AssignmentList*)malloc(sizeof(AssignmentList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// LearningActivityList allocation
error allocateLearningActivityList(LearningActivityList** node) {
    if (*node != NULL) {
        return "LearningActivityList node pointer must be NULL";
    }
    
    *node = (LearningActivityList*)malloc(sizeof(LearningActivityList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// AttendanceList allocation
error allocateAttendanceList(AttendanceList** node) {
    if (*node != NULL) {
        return "AttendanceList node pointer must be NULL";
    }
    
    *node = (AttendanceList*)malloc(sizeof(AttendanceList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// ScoreBookList allocation
error allocateScoreBookList(ScoreBookList** node) {
    if (*node != NULL) {
        return "ScoreBookList node pointer must be NULL";
    }
    
    *node = (ScoreBookList*)malloc(sizeof(ScoreBookList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// LearnItList allocation
error allocateLearnItList(LearnItList** node) {
    if (*node != NULL) {
        return "LearnItList node pointer must be NULL";
    }
    
    *node = (LearnItList*)malloc(sizeof(LearnItList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Survey allocation
error allocateSurvey(Survey** survey) {
    if (*survey != NULL) {
        return "Survey pointer must be NULL";
    }
    
    *survey = (Survey*)malloc(sizeof(Survey));
    if (*survey == NULL) {
        return "Memory allocation failed";
    }
    
    return NULL;
}

// MemberList allocation
error allocateMemberList(MemberList** node) {
    if (*node != NULL) {
        return "MemberList node pointer must be NULL";
    }
    
    *node = (MemberList*)malloc(sizeof(MemberList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// FileList allocation
error allocateFileList(FileList** node) {
    if (*node != NULL) {
        return "FileList node pointer must be NULL";
    }
    
    *node = (FileList*)malloc(sizeof(FileList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Class allocation
error allocateClass(Class** class) {
    if (*class != NULL) {
        return "Class pointer must be NULL";
    }
    
    *class = (Class*)malloc(sizeof(Class));
    if (*class == NULL) {
        return "Memory allocation failed";
    }
    
    (*class)->classId = NULL;
    (*class)->dashboard = NULL;
    (*class)->syllabus = NULL;
    (*class)->assignmentList = NULL;
    (*class)->learningActivityList = NULL;
    (*class)->attendanceList = NULL;
    (*class)->scoreBookList = NULL;
    (*class)->learnItList = NULL;
    (*class)->fileList = NULL;
    (*class)->survey = NULL;
    (*class)->memberList = NULL;
    
    return NULL;
}

// ClassList allocation
error allocateClassList(ClassList** node) {
    if (*node != NULL) {
        return "ClassList node pointer must be NULL";
    }
    
    *node = (ClassList*)malloc(sizeof(ClassList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Semester allocation
error allocateSemester(Semester** semester) {
    if (*semester != NULL) {
        return "Semester pointer must be NULL";
    }
    
    *semester = (Semester*)malloc(sizeof(Semester));
    if (*semester == NULL) {
        return "Memory allocation failed";
    }
    
    (*semester)->year = 0;
    (*semester)->term = 0;
    (*semester)->classList = NULL;
    
    return NULL;
}

// SemesterList allocation
error allocateSemesterList(SemesterList** node) {
    if (*node != NULL) {
        return "SemesterList node pointer must be NULL";
    }
    
    *node = (SemesterList*)malloc(sizeof(SemesterList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// LEB2 allocation
error allocateLEB2(LEB2** leb2) {
    if (*leb2 != NULL) {
        return "LEB2 pointer must be NULL";
    }
    
    *leb2 = (LEB2*)malloc(sizeof(LEB2));
    if (*leb2 == NULL) {
        return "Memory allocation failed";
    }
    
    (*leb2)->semesterList = NULL;
    
    return NULL;
}

// Create Assignment
error createAssignment(Assignment* assignment, const string head, const string description, 
                     DateTime assignDate, DateTime dueDate) {
    if (assignment == NULL) {
        return "Assignment pointer is required";
    }
    
    error err;
    
    err = allocateString(&(assignment->head), head);
    if (err != NULL) {
        return err;
    }
    
    err = allocateString(&(assignment->description), description);
    if (err != NULL) {
        FreeString(&(assignment->head));
        return err;
    }
    
    assignment->assignDate = assignDate;
    assignment->dueDate = dueDate;
    
    return NULL;
}

error createAssignmentListNode(AssignmentList** node, Assignment assignment) {
    if (node == NULL) {
        return "AssignmentList node pointer is required";
    }
    
    *node = (AssignmentList*)malloc(sizeof(AssignmentList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->assignment = assignment;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Create Dashboard
error createDashboard(Dashboard* dashboard, const string description) {
    if (dashboard == NULL) {
        return "Dashboard pointer is required";
    }
    
    error err = allocateString(&dashboard->description, description);
    if (err != NULL) {
        return err;
    }
    
    return NULL;
}

// Create Syllabus
error createSyllabus(Syllabus* syllabus, const string description) {
    if (syllabus == NULL) {
        return "Syllabus pointer is required";
    }
    
    error err = allocateString(&syllabus->description, description);
    if (err != NULL) {
        return err;
    }
    
    return NULL;
}

// Create LearningActivity
error createLearningActivity(LearningActivity* activity, const string head, 
                           const string description, const string url, File* file) {
    if (activity == NULL) {
        return "LearningActivity pointer is required";
    }
    
    error err;
    
    err = allocateString(&(activity->head), head);
    if (err != NULL) {
        return err;
    }
    
    err = allocateString(&(activity->description), description);
    if (err != NULL) {
        FreeString(&(activity->head));
        return err;
    }
    
    err = allocateString(&(activity->url), url);
    if (err != NULL) {
        FreeString(&(activity->head));
        FreeString(&(activity->description));
        return err;
    }
    
    activity->file = file;
    
    return NULL;
}

// Create LearningActivityList node
error createLearningActivityListNode(LearningActivityList** node, LearningActivity activity) {
    if (*node != NULL) {
        return "LearningActivityList node pointer must be NULL";
    }
    
    *node = (LearningActivityList*)malloc(sizeof(LearningActivityList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->learningActivity = activity;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Create Attendance
error createAttendance(Attendance* attendance, code code, DateTime date) {
    if (attendance == NULL) {
        return "Attendance pointer is required";
    }
    
    attendance->joined = code;
    attendance->date = date;
    
    return NULL;
}

// Create AttendanceList node
error createAttendanceListNode(AttendanceList** node, Attendance attendance) {
    if (*node != NULL) {
        return "AttendanceList node pointer must be NULL";
    }
    
    *node = (AttendanceList*)malloc(sizeof(AttendanceList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->attendance = attendance;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Create ScoreBook
error createScoreBook(ScoreBook* scoreBook, const string head, const string description, float score) {
    if (scoreBook == NULL) {
        return "ScoreBook pointer is required";
    }
    
    error err;
    
    err = allocateString(&(scoreBook->head), head);
    if (err != NULL) {
        return err;
    }
    
    err = allocateString(&(scoreBook->description), description);
    if (err != NULL) {
        FreeString(&(scoreBook->head));
        return err;
    }
    
    scoreBook->score = score;
    
    return NULL;
}

// Create ScoreBookList node
error createScoreBookListNode(ScoreBookList** node, ScoreBook scoreBook) {
    if (*node != NULL) {
        return "ScoreBookList node pointer must be NULL";
    }
    
    *node = (ScoreBookList*)malloc(sizeof(ScoreBookList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->scoreBook = scoreBook;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Create LearnIt
error createLearnIt(LearnIt* learnIt, const string name, const string description, const string url) {
    if (learnIt == NULL) {
        return "LearnIt pointer is required";
    }
    
    error err;
    
    err = allocateString(&(learnIt->name), name);
    if (err != NULL) {
        return err;
    }
    
    err = allocateString(&(learnIt->description), description);
    if (err != NULL) {
        FreeString(&(learnIt->name));
        return err;
    }
    
    err = allocateString(&(learnIt->url), url);
    if (err != NULL) {
        FreeString(&(learnIt->name));
        FreeString(&(learnIt->description));
        return err;
    }
    
    return NULL;
}

// Create LearnItList node
error createLearnItListNode(LearnItList** node, LearnIt learnIt) {
    if (*node != NULL) {
        return "LearnItList node pointer must be NULL";
    }
    
    *node = (LearnItList*)malloc(sizeof(LearnItList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->learnIt = learnIt;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Create Survey
error createSurvey(Survey* survey) {
    if (survey == NULL) {
        return "Survey pointer is required";
    }
    
    // Currently empty as per specification
    return NULL;
}

// Create Member
error createMember(Member* member, const string studentId, const string name) {
    if (member == NULL) {
        return "Member pointer is required";
    }
    
    error err;
    
    err = allocateString(&(member->studentId), studentId);
    if (err != NULL) {
        return err;
    }
    
    err = allocateString(&(member->name), name);
    if (err != NULL) {
        FreeString(&(member->studentId));
        return err;
    }
    
    return NULL;
}

// Create MemberList node
error createMemberListNode(MemberList** node, Member member) {
    if (*node != NULL) {
        return "MemberList node pointer must be NULL";
    }
    
    *node = (MemberList*)malloc(sizeof(MemberList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->member = member;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Create FileList node
error createFileListNode(FileList** node, File file) {
    if (*node != NULL) {
        return "FileList node pointer must be NULL";
    }
    
    *node = (FileList*)malloc(sizeof(FileList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->file = file;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Create Class
error createClass(Class* class, const string classId, Dashboard* dashboard, 
                Syllabus* syllabus, AssignmentList* assignmentList, 
                LearningActivityList* learningActivityList, AttendanceList* attendanceList, 
                ScoreBookList* scoreBookList, LearnItList* learnItList, 
                FileList* fileList, Survey* survey, MemberList* memberList) {
    if (class == NULL) {
        return "Class pointer is required";
    }
    
    error err = allocateString(&(class->classId), classId);
    if (err != NULL) {
        return err;
    }
    
    class->dashboard = dashboard;
    class->syllabus = syllabus;
    class->assignmentList = assignmentList;
    class->learningActivityList = learningActivityList;
    class->attendanceList = attendanceList;
    class->scoreBookList = scoreBookList;
    class->learnItList = learnItList;
    class->fileList = fileList;
    class->survey = survey;
    class->memberList = memberList;
    
    return NULL;
}

// Create ClassList node
error createClassListNode(ClassList** node, Class class) {
    if (*node != NULL) {
        return "ClassList node pointer must be NULL";
    }
    
    *node = (ClassList*)malloc(sizeof(ClassList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->class = class;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Create Semester
error createSemester(Semester* semester, const uint8 year, const uint8 term, ClassList* classList) {
    if (semester == NULL) {
        return "Semester pointer is required";
    }
    
    semester->year = year;
    semester->term = term;
    semester->classList = classList;
    
    return NULL;
}

// Create SemesterList node
error createSemesterListNode(SemesterList** node, Semester semester) {
    if (*node != NULL) {
        return "SemesterList node pointer must be NULL";
    }
    
    *node = (SemesterList*)malloc(sizeof(SemesterList));
    if (*node == NULL) {
        return "Memory allocation failed";
    }
    
    (*node)->semester = semester;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    
    return NULL;
}

// Create LEB2
error createLEB2(LEB2* leb2, SemesterList* semesterList) {
    if (leb2 == NULL) {
        return "LEB2 pointer is required";
    }
    
    leb2->semesterList = semesterList;
    
    return NULL;
}

// Add node to AssignmentList
error addAssignmentToList(AssignmentList** head, Assignment assignment) {
    if (head == NULL) {
        return "AssignmentList head pointer is required";
    }
    
    AssignmentList* new_node = NULL;
    error err = createAssignmentListNode(&new_node, assignment);
    if (err != NULL) {
        return err;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return NULL;
    }
    
    AssignmentList* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    
    return NULL;
}

// Add node to LearningActivityList
error addLearningActivityToList(LearningActivityList** head, LearningActivity activity) {
    if (head == NULL) {
        return "LearningActivityList head pointer is required";
    }
    
    LearningActivityList* new_node = NULL;
    error err = createLearningActivityListNode(&new_node, activity);
    if (err != NULL) {
        return err;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return NULL;
    }
    
    LearningActivityList* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    
    return NULL;
}

// Add node to AttendanceList
error addAttendanceToList(AttendanceList** head, Attendance attendance) {
    if (head == NULL) {
        return "AttendanceList head pointer is required";
    }
    
    AttendanceList* new_node = NULL;
    error err = createAttendanceListNode(&new_node, attendance);
    if (err != NULL) {
        return err;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return NULL;
    }
    
    AttendanceList* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    
    return NULL;
}

// Add node to ScoreBookList
error addScoreBookToList(ScoreBookList** head, ScoreBook scoreBook) {
    if (head == NULL) {
        return "ScoreBookList head pointer is required";
    }
    
    ScoreBookList* new_node = NULL;
    error err = createScoreBookListNode(&new_node, scoreBook);
    if (err != NULL) {
        return err;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return NULL;
    }
    
    ScoreBookList* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    
    return NULL;
}

// Add node to LearnItList
error addLearnItToList(LearnItList** head, LearnIt learnIt) {
    if (head == NULL) {
        return "LearnItList head pointer is required";
    }
    
    LearnItList* new_node = NULL;
    error err = createLearnItListNode(&new_node, learnIt);
    if (err != NULL) {
        return err;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return NULL;
    }
    
    LearnItList* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    
    return NULL;
}

// Add node to MemberList
error addMemberToList(MemberList** head, Member member) {
    if (head == NULL) {
        return "MemberList head pointer is required";
    }
    
    MemberList* new_node = NULL;
    error err = createMemberListNode(&new_node, member);
    if (err != NULL) {
        return err;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return NULL;
    }
    
    MemberList* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    
    return NULL;
}

// Add node to FileList
error addFileToList(FileList** head, File file) {
    if (head == NULL) {
        return "FileList head pointer is required";
    }
    
    FileList* new_node = NULL;
    error err = createFileListNode(&new_node, file);
    if (err != NULL) {
        return err;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return NULL;
    }
    
    FileList* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    
    return NULL;
}

// Add node to ClassList
error addClassToList(ClassList** head, Class class) {
    if (head == NULL) {
        return "ClassList head pointer is required";
    }
    
    ClassList* new_node = NULL;
    error err = createClassListNode(&new_node, class);
    if (err != NULL) {
        return err;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return NULL;
    }
    
    ClassList* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    
    return NULL;
}

// Add node to SemesterList
error addSemesterToList(SemesterList** head, Semester semester) {
    if (head == NULL) {
        return "SemesterList head pointer is required";
    }
    
    SemesterList* new_node = NULL;
    error err = createSemesterListNode(&new_node, semester);
    if (err != NULL) {
        return err;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return NULL;
    }
    
    SemesterList* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    
    return NULL;
}

// 3. FREE FUNCTIONS

// Free Dashboard
void FreeDashboard(Dashboard* dashboard) {
    if (dashboard == NULL) return;
    
    FreeString(&dashboard->description);
    free(dashboard);
}

// Free Syllabus
void FreeSyllabus(Syllabus* syllabus) {
    if (syllabus == NULL) return;
    
    FreeString(&syllabus->description);
    free(syllabus);
}

// Free Survey
void FreeSurvey(Survey* survey) {
    if (survey == NULL) return;
    
    free(survey);
}

// Free Assignment contents
void FreeAssignmentContents(Assignment* assignment) {
    if (assignment == NULL) return;
    
    FreeString(&assignment->head);
    FreeString(&assignment->description);
}

void FreeAssignment(Assignment* assignment) {
    if (assignment == NULL) return;
    
    FreeAssignmentContents(assignment);
    free(assignment);
}

// Free AssignmentList
void FreeAssignmentList(AssignmentList* head) {
    if (head == NULL) return;
    
    // Free all nodes after head
    AssignmentList* current = head->next;
    while (current != NULL) {
        AssignmentList* next = current->next;
        FreeAssignmentContents(&current->assignment);
        free(current);
        current = next;
    }
    
    // Free all nodes before head
    current = head->prev;
    while (current != NULL) {
        AssignmentList* prev = current->prev;
        FreeAssignmentContents(&current->assignment);
        free(current);
        current = prev;
    }
    
    // Free the head node itself
    FreeAssignmentContents(&head->assignment);
    free(head);
}

// Free LearningActivity contents
void FreeLearningActivityContents(LearningActivity* activity) {
    if (activity == NULL) return;
    
    FreeString(&activity->head);
    FreeString(&activity->description);
    FreeString(&activity->url);
    FreeFile(activity->file);
    // Not freeing file as it may be referenced elsewhere
}

void FreeLearningActivity(LearningActivity* activity) {
    if (activity == NULL) return;
    
    FreeLearningActivityContents(activity);
    free(activity);
}

// Free LearningActivityList
void FreeLearningActivityList(LearningActivityList* head) {
    if (head == NULL) return;
    
    // Free all nodes after head
    LearningActivityList* current = head->next;
    while (current != NULL) {
        LearningActivityList* next = current->next;
        FreeLearningActivityContents(&current->learningActivity);
        free(current);
        current = next;
    }
    
    // Free all nodes before head
    current = head->prev;
    while (current != NULL) {
        LearningActivityList* prev = current->prev;
        FreeLearningActivityContents(&current->learningActivity);
        free(current);
        current = prev;
    }
    
    // Free the head node itself
    FreeLearningActivityContents(&head->learningActivity);
    free(head);
}

void FreeAttendanceContent(Attendance* attendance) {
    if (attendance == NULL) return;

    DateTime setDate = {0};
    code setCode = 0;
    attendance->date = setDate;
    attendance->joined = setCode;
}

// Free AttendanceList
void FreeAttendanceList(AttendanceList* head) {
    if (head == NULL) return;
    
    // Free all nodes after head
    AttendanceList* current = head->next;
    while (current != NULL) {
        AttendanceList* next = current->next;
        FreeAttendanceContent(&current->attendance);
        free(current);
        current = next;
    }
    
    // Free all nodes before head
    current = head->prev;
    while (current != NULL) {
        AttendanceList* prev = current->prev;
        FreeAttendanceContent(&current->attendance);
        free(current);
        current = prev;
    }
    
    // Free the head node itself
    FreeAttendanceContent(&head->attendance);
    free(head);
}

// Free ScoreBook contents
void FreeScoreBookContents(ScoreBook* scoreBook) {
    if (scoreBook == NULL) return;
    
    FreeString(&scoreBook->head);
    FreeString(&scoreBook->description);
    scoreBook->score = -1.0;
}

void FreeScoreBook(ScoreBook* scoreBook) {
    if (scoreBook == NULL) return;

    FreeScoreBookContents(scoreBook);
    free(scoreBook);
}

// Free ScoreBookList
void FreeScoreBookList(ScoreBookList* head) {
    if (head == NULL) return;
    
    // Free all nodes after head
    ScoreBookList* current = head->next;
    while (current != NULL) {
        ScoreBookList* next = current->next;
        FreeScoreBookContents(&current->scoreBook);
        free(current);
        current = next;
    }
    
    // Free all nodes before head
    current = head->prev;
    while (current != NULL) {
        ScoreBookList* prev = current->prev;
        FreeScoreBookContents(&current->scoreBook);
        free(current);
        current = prev;
    }
    
    // Free the head node itself
    FreeScoreBookContents(&head->scoreBook);
    free(head);
}

// Free LearnIt contents
void FreeLearnItContents(LearnIt* learnIt) {
    if (learnIt == NULL) return;
    
    FreeString(&learnIt->name);
    FreeString(&learnIt->description);
    FreeString(&learnIt->url);
}

void FreeLearnIt(LearnIt* learnIt) {
    if (learnIt == NULL) return;

    FreeLearnItContents(learnIt);
    free(learnIt);
}

// Free LearnItList
void FreeLearnItList(LearnItList* head) {
    if (head == NULL) return;
    
    // Free all nodes after head
    LearnItList* current = head->next;
    while (current != NULL) {
        LearnItList* next = current->next;
        FreeLearnItContents(&current->learnIt);
        free(current);
        current = next;
    }
    
    // Free all nodes before head
    current = head->prev;
    while (current != NULL) {
        LearnItList* prev = current->prev;
        FreeLearnItContents(&current->learnIt);
        free(current);
        current = prev;
    }
    
    // Free the head node itself
    FreeLearnItContents(&head->learnIt);
    free(head);
}

// Free Member contents
void FreeMemberContents(Member* member) {
    if (member == NULL) return;
    
    FreeString(&member->studentId);
    FreeString(&member->name);
}

void FreeMember(Member* member) {
    if (member == NULL) return;
    
    FreeMemberContents(member);
    free(member);
}

// Free MemberList
void FreeMemberList(MemberList* head) {
    if (head == NULL) return;
    
    // Free all nodes after head
    MemberList* current = head->next;
    while (current != NULL) {
        MemberList* next = current->next;
        FreeMemberContents(&current->member);
        free(current);
        current = next;
    }
    
    // Free all nodes before head
    current = head->prev;
    while (current != NULL) {
        MemberList* prev = current->prev;
        FreeMemberContents(&current->member);
        free(current);
        current = prev;
    }
    
    // Free the head node itself
    FreeMemberContents(&head->member);
    free(head);
}

// Free FileList
void FreeFileList(FileList* head) {
    if (head == NULL) return;
    
    // Free all nodes after head
    FileList* current = head->next;
    while (current != NULL) {
        FileList* next = current->next;
        FreeFileContent(&current->file);
        free(current);
        current = next;
    }
    
    // Free all nodes before head
    current = head->prev;
    while (current != NULL) {
        FileList* prev = current->prev;
        FreeFileContent(&current->file);
        free(current);
        current = prev;
    }
    
    // Free the head node itself
    FreeFileContent(&head->file);
    free(head);
}

// Free Class contents
void FreeClassContents(Class* class) {
    if (class == NULL) return;
    
    FreeString(&class->classId);
    FreeDashboard(class->dashboard);
    FreeSyllabus(class->syllabus);
    FreeAssignmentList(class->assignmentList);
    FreeLearningActivityList(class->learningActivityList);
    FreeAttendanceList(class->attendanceList);
    FreeScoreBookList(class->scoreBookList);
    FreeLearnItList(class->learnItList);
    FreeFileList(class->fileList);
    FreeSurvey(class->survey);
    FreeMemberList(class->memberList);
}

// Free Class
void FreeClass(Class* class) {
    if (class == NULL) return;
    
    FreeClassContents(class);
    free(class);
}

// Free ClassList
void FreeClassList(ClassList* head) {
    if (head == NULL) return;
    
    // Free all nodes after head
    ClassList* current = head->next;
    while (current != NULL) {
        ClassList* next = current->next;
        FreeClassContents(&current->class);
        free(current);
        current = next;
    }
    
    // Free all nodes before head
    current = head->prev;
    while (current != NULL) {
        ClassList* prev = current->prev;
        FreeClassContents(&current->class);
        free(current);
        current = prev;
    }
    
    // Free the head node itself
    FreeClassContents(&head->class);
    free(head);
}

// Free Semester contents
void FreeSemesterContents(Semester* semester) {
    if (semester == NULL) return;
    
    FreeClassList(semester->classList);
}

void FreeSemester(Semester* semester) {
    if (semester == NULL) return;
    
    FreeSemesterContents(semester);
    free(semester);
}

// Free SemesterList
void FreeSemesterList(SemesterList* head) {
    if (head == NULL) return;
    
    // Free all nodes after head
    SemesterList* current = head->next;
    while (current != NULL) {
        SemesterList* next = current->next;
        FreeSemesterContents(&current->semester);
        free(current);
        current = next;
    }
    
    // Free all nodes before head
    current = head->prev;
    while (current != NULL) {
        SemesterList* prev = current->prev;
        FreeSemesterContents(&current->semester);
        free(current);
        current = prev;
    }
    
    // Free the head node itself
    FreeSemesterContents(&head->semester);
    free(head);
}

void FreeLEB2Contents(LEB2* leb2) {
    if (leb2 == NULL) return;
    
    FreeSemesterList(leb2->semesterList);
}

// Free LEB2
void FreeLEB2(LEB2* leb2) {
    if (leb2 == NULL) return;
    
    FreeLEB2Contents(leb2);
    free(leb2);
}