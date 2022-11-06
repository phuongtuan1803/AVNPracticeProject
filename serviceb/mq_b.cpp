#include "mq_b.h"
#include "database.h"
std::shared_ptr<MessageQueueB> MessageQueueB::getInstance()
{

    std::cout << "MessageQueueB::getInstance" << std::endl;
    static std::shared_ptr<MessageQueueB> instance(new MessageQueueB());
    return instance;
}

MessageQueueB::MessageQueueB() : MessageQueue(SERB_QUEUE_NAME)
{
}

MessageQueueB::~MessageQueueB()
{
}

void MessageQueueB::check_receive_message()
{
    send_message.message = MQ_INVALID;
    if (receive_message.message == MQ_REQUESTUPDATEEMPLOYEEINFO)
    {
        requestUpdateEmployeeInfo();
        
    }
    else if (receive_message.message == MQ_REQUESTEMPLOYEEINFO)
    {
        requestEmployeeInfo();
        
    }
    else {
        // Not support message
    }
}

// received from App C
void MessageQueueB::requestUpdateEmployeeInfo(){
    EmployeeInfo emplinfo;
    memcpy(&emplinfo,receive_message.buffer, sizeof(EmployeeInfo));
    Database::getInstance()->requestUpdateEmployeeInfo(emplinfo);
    onEmployeeInfoChanged(emplinfo);
}

// received from App A
void MessageQueueB::requestEmployeeInfo()
{
    int id = receive_message.buffer[0];
    // Prepare data
    EmployeeInfo emplinfo = Database::getInstance()->requestEmployeeInfo(id);
    onEmployeeInfoChanged(emplinfo);
}

// send to App A
void MessageQueueB::onEmployeeInfoChanged(const EmployeeInfo &emplinfo){
    // Prepare message
    send_message.message = MQ_ONEMPLOYEEINFOCHANGED;
    memcpy(send_message.buffer, &emplinfo, sizeof(EmployeeInfo));
    this->send();
}
