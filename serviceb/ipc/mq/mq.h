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
    // only call from App C
    bool requestUpdateEmployeeInfo(EmployeeInfo& emplinfo); // from AppC to ServiceB 

    // only overide from App A
    virtual bool onEmployeeInfoChanged(const EmployeeInfo& emplinfo); // from ServiceB to AppA
    // void server_open();
    // void server_start();

    // void client_open();
    // void client_start();
    // void client_close();

    void open();
    void appa_start();
    void serviceb_start();
    void appc_start();
private:
	// MessageQueue_DATA_T* m_ptr;
    char in_buffer [MSG_BUFFER_SIZE];
    char out_buffer [MSG_BUFFER_SIZE];
    MQ_DATA_T message;
    // mqd_t qd_server, qd_client;   // queue descriptors
    // char client_queue_name [64];
    // long token_number;

    mqd_t qd_a, qd_b, qd_c; // queue descriptors

    std::condition_variable cv;
    std::mutex m;

};

#endif //MESSAGEQUEUE_H_
