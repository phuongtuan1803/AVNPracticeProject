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

class MessageQueueB : public MessageQueue
{
private:
	MessageQueueB();

public:
    virtual ~MessageQueueB();
    static std::shared_ptr<MessageQueueB> getInstance();

public:
    virtual void check_receive_message();

    // received from App C
    void requestUpdateEmployeeInfo(); 
    // received from App A
    void requestEmployeeInfo();

    // send to App A
    void onEmployeeInfoChanged(const EmployeeInfo& emplinfo); 

};

#endif //MESSAGEQUEUE_B_H_
