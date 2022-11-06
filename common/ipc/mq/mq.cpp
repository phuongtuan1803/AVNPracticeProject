#include "mq.h"

std::shared_ptr<MessageQueue> MessageQueue::getInstance(const std::string mq_name)
{
    std::cout << "MessageQueue::getInstance" << std::endl;
    static std::shared_ptr<MessageQueue> instance(new MessageQueue(mq_name));
    return instance;
}

MessageQueue::MessageQueue(const std::string mq_name)
{
    this->mq_name = mq_name;
    open();
    start_receive();
}

MessageQueue::~MessageQueue()
{
}

void MessageQueue::open()
{
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
    if ((qd = mq_open(mq_name.c_str(), O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
    {
        std::cout << "Server: mq_open" << mq_name << std::endl;
    }
    std::cout << "MessageQueue::open(): qd: " << qd << std::endl;
}

void MessageQueue::send()
{
    memset(out_buffer, 0, MSG_BUFFER_SIZE);
    memcpy(out_buffer, &send_message, sizeof(MQ_DATA_T));
    if (mq_send(qd, out_buffer, strlen(out_buffer) + 1, 0) == -1)
    {
        perror("serviceb_start(): Server: Not able to send message to client");
        return;
    }
}

void MessageQueue::start_receive()
{
    auto f = [this]()
    {
        while (1)
        {
            printf("start_receive(): Server: begin check.\n");
            if (mq_receive(qd, in_buffer, MSG_BUFFER_SIZE, NULL) == -1)
            {
                perror("start_receive(): Server: mq_receive");
                continue;
            }
            memcpy(&receive_message, in_buffer, sizeof(MQ_DATA_T));
            std::cout << "start_receive(): Received message: rec_msg->message: " << int(receive_message.message) << std::endl;
            
            check_receive_message();
        }
    };

    std::thread th(f);
    th.detach();
}
