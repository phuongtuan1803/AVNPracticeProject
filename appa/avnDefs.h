#ifndef AVNDEFS_H
#define AVNDEFS_H

#define MAX_NAME_CHAR   100
struct EmployeeScore{
    int id;
    char name[MAX_NAME_CHAR];
    int score;
};

struct EmployeeInfo{
    int id;
    char name[MAX_NAME_CHAR];
    int asm_score;
    int cpp_score;
    int js_score;
    int opengl_score;
    int qml_score;
};

#endif // AVNDEFS_H
