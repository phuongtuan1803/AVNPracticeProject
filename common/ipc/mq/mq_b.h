#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include <iostream>
#include <memory>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
 #include <unistd.h>
#include <sys/types.h>
#include <mqueue.h>
#include <thread>
#include <condition_variable>

#include "../../../common/avnDefs.h"

class MessageQueue
{
private:
	MessageQueue();

public:
    virtual ~MessageQueue();
    static std::shared_ptr<MessageQueue> getInstance();

public:
    // // only call from App C
    // bool requestUpdateEmployeeInfo(EmployeeInfo& emplinfo); // from AppC to ServiceB 
    // EmployeeInfo requestEmployeeInfo(const int id);

    // // only overide from App A
    // virtual bool onEmployeeInfoChanged(const EmployeeInfo& emplinfo); // from ServiceB to AppA

    void open();
    void appa_start();
    void serviceb_start();
    void appc_start();
private:
    char in_buffer [MSG_BUFFER_SIZE];
    char out_buffer [MSG_BUFFER_SIZE];
    MQ_DATA_T message;

    mqd_t qd_a, qd_b, qd_c; // queue descriptors

    std::condition_variable cv;
    std::mutex m;

};

#endif //MESSAGEQUEUE_H_
