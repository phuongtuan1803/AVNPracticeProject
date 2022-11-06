#include "mq_a.h"
#include "EmployeeInfoModel.h""
std::shared_ptr<MessageQueueA> MessageQueueA::getInstance()
{

    std::cout << "MessageQueueA::getInstance" << std::endl;
    static std::shared_ptr<MessageQueueA> instance(new MessageQueueA());
    return instance;
}

MessageQueueA::MessageQueueA() : MessageQueue(SERB_QUEUE_NAME)
{
}

MessageQueueA::~MessageQueueA()
{
}

void MessageQueueA::check_receive_message()
{
    send_message.message = MQ_INVALID;
    if (receive_message.message == MQ_ONEMPLOYEEINFOCHANGED)
    {
        onEmployeeInfoChanged();
    }
    else {
        // Not support message
    }
    if(send_message.message != MQ_INVALID){
        this->send();
    }
}

// received from App C
void MessageQueueA::onEmployeeInfoChanged(){
    EmployeeInfo emplinfo;
    memcpy(&emplinfo,receive_message.buffer, sizeof(EmployeeInfo));
    EmployeeInfoModel::getInstance().onEmployeeInfoChanged(emplinfo);
}

// send to App A
void MessageQueueA::requestEmployeeInfo(char id){
    // Prepare message
    send_message.message = MQ_REQUESTEMPLOYEEINFO;
    send_message.buffer[0] = id;
    this->send();
}

