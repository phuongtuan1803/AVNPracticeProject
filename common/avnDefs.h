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

/** Shared Memory */
struct SHMEM_DATA_T{
    EmployeeScoreList SHMEM_EmployeeScoreList;
    EmployeeInfo SHMEM_EmployeeInfo;
};

/* Message Queue */
// #define SERVER_QUEUE_NAME   "/server"
#define APPA_QUEUE_NAME   "/appa"
#define SERB_QUEUE_NAME   "/serverb"
#define APPC_QUEUE_NAME   "/appc"
#define QUEUE_PERMISSIONS 0777
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

#define MQ_REQUESTUPDATEEMPLOYEEINFO    0
#define MQ_ONEMPLOYEEINFOCHANGED        1

struct MQ_DATA_T{
    char message;
    char buffer[MSG_BUFFER_SIZE-1];
};
#endif // AVNDEFS_H
