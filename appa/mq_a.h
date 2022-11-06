#ifndef MESSAGEQUEUE_B_H_
#define MESSAGEQUEUE_B_H_

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

#include "../common/avnDefs.h"
#include "../common/ipc/mq/mq.h"

class MessageQueueA : public MessageQueue
{
private:
    MessageQueueA();

public:
    virtual ~MessageQueueA();
    static std::shared_ptr<MessageQueueA> getInstance();

public:
    virtual void check_receive_message();

    // received from Service B
    void onEmployeeInfoChanged();

    // send to Service B
    void requestEmployeeInfo(char id);
};

#endif //MESSAGEQUEUE_B_H_
