#ifndef AVNDEFS_H
#define AVNDEFS_H

#define MAX_NAME_CHAR   100
#define MAX_EMP_LIST   100
#pragma pack(push, 1)
struct EmployeeScore{
    int id;
    char name[MAX_NAME_CHAR];
    int score;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct EmployeeScoreList{
    EmployeeScore l[MAX_EMP_LIST];
};
#pragma pack(pop)
#pragma pack(push, 1)
struct EmployeeInfo{
    int id;
    char name[MAX_NAME_CHAR];
    int asm_score;
    int cpp_score;
    int js_score;
    int opengl_score;
    int qml_score;
};
#pragma pack(pop)

/** Shared Memory */
#pragma pack(push, 1)
struct SHMEM_DATA_T{
    EmployeeScoreList SHMEM_EmployeeScoreList;
    EmployeeInfo SHMEM_EmployeeInfo;
};
#pragma pack(pop)
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
#define MQ_REQUESTEMPLOYEEINFO          2
#pragma pack(push, 1)
struct MQ_DATA_T{
    char message;
    char buffer[MAX_MSG_SIZE-1];
};
#pragma pack(pop)
#endif // AVNDEFS_H
