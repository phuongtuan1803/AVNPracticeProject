#ifndef AVNDEFS_H
#define AVNDEFS_H

#define MAX_NAME_CHAR   100
#define MAX_EMP_LIST   100
struct EmployeeScore{
    int id;
    char name[MAX_NAME_CHAR];
    int score;
};

struct EmployeeScoreList{
    EmployeeScore l[MAX_EMP_LIST];
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

struct SHMEM_DATA_T{
    EmployeeScoreList SHMEM_EmployeeScoreList;
    EmployeeInfo SHMEM_EmployeeInfo;
};
#endif // AVNDEFS_H
