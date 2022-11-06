#ifndef MESSAGEQUEUE_A_H_
#define MESSAGEQUEUE_A_H_

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

protected:
    MessageQueue(const std::string mq_name);
public:
    virtual ~MessageQueue();
    static std::shared_ptr<MessageQueue> getInstance(const std::string mq_name);
    // static std::shared_ptr<MessageQueue> getInstance(); // client should overload this fucntion

    void open();
    void start_receive();
    void send();
    virtual void check_receive_message(){};
protected:
    std::string mq_name;

    char in_buffer [MSG_BUFFER_SIZE];
    char out_buffer [MSG_BUFFER_SIZE];
    MQ_DATA_T send_message;
    MQ_DATA_T receive_message;
    mqd_t qd; // queue descriptors

    std::condition_variable cv;
    std::mutex m;
    
};

#endif //MESSAGEQUEUE_H_
