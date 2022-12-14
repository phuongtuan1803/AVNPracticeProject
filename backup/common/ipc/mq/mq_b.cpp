#include "mq_b.h"
#include "../../database.h"
std::shared_ptr<MessageQueue> MessageQueue::getInstance()
{
    std::cout << "MessageQueue::getInstance" << std::endl;
    static std::shared_ptr<MessageQueue> instance(new MessageQueue());
    return instance;
}

MessageQueue::MessageQueue()
{
    // m_ptr = nullptr;
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
    if ((qd_a = mq_open(APPA_QUEUE_NAME, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
    {
        std::cout << "Server: mq_open (app A)" << std::endl;
    }
    if ((qd_b = mq_open(SERB_QUEUE_NAME, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
    {
        std::cout << "Server: mq_open (server b)" << std::endl;
    }
    if ((qd_c = mq_open(APPC_QUEUE_NAME, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
    {
        std::cout << "Server: mq_open (app c)" << std::endl;
    }
    std::cout << "MessageQueue::open(): qd_a: " << qd_a << ". qd_b: " << qd_b << ". qd_c: " << qd_c << std::endl;
}

// Receive from App C and  send to App A
void MessageQueue::serviceb_start()
{
    open();

    auto f = [this]()
    {
        char temp_buf[10];
        while (1)
        {
            printf("serviceb_start(): Server: begin check.\n");
            if (mq_receive(qd_b, in_buffer, MSG_BUFFER_SIZE, NULL) == -1)
            {
                perror("serviceb_start(): Server: mq_receive");
                continue;
            }
            MQ_DATA_T rec_msg;
            memcpy(&rec_msg, in_buffer, sizeof(MQ_DATA_T));
            std::cout << "serviceb_start(): Received message: rec_msg->message: " << int(rec_msg.message) << std::endl;
            if (rec_msg.message == MQ_REQUESTUPDATEEMPLOYEEINFO)
            {
                rec_msg.message = MQ_ONEMPLOYEEINFOCHANGED; // fw message to App A onEmployeeInfoChanged

                std::cout << "serviceb_start(): Begin sent: MQ_ONEMPLOYEEINFOCHANGED" << std::endl;

                memset(out_buffer, 0, MSG_BUFFER_SIZE);
                memcpy(out_buffer, &rec_msg, sizeof(MQ_DATA_T));
                if (mq_send(qd_a, out_buffer, strlen(out_buffer) + 1, 0) == -1)
                {
                    perror("serviceb_start(): Server: Not able to send message to client");
                    continue;
                }
            }
            else if (rec_msg.message == MQ_REQUESTEMPLOYEEINFO)
            {
                int id;
                id = rec_msg.buffer[0];

                // Prepare data
                EmployeeInfo emplinfo = Database::getInstance()->requestEmployeeInfo(id);
                // Prepare message
                message.message = MQ_ONEMPLOYEEINFOCHANGED;
                memcpy(message.buffer, &emplinfo, sizeof(EmployeeInfo));
                EmployeeInfo *e = static_cast<EmployeeInfo *>(static_cast<void*>(message.buffer));
                std::cout << "serviceb_start(): ====> name: " << e->name <<std::endl;
                // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "serviceb_start(): Begin sent: MQ_ONEMPLOYEEINFOCHANGED" << std::endl;
                // memset(out_buffer,0,MAX_MSG_SIZE);
                memcpy(out_buffer, &message, MSG_BUFFER_SIZE - 1);
                if (mq_send(qd_a, out_buffer, MAX_MSG_SIZE, NULL) == -1)
                {
                    perror("serviceb_start(): Server: Not able to send message to client");
                    continue;
                }
            }
            {
                // Not support message
            }
        }
    };

    std::thread th(f);
    th.join();
}

//     // only call from App C
// bool MessageQueue::requestUpdateEmployeeInfo(EmployeeInfo& emplinfo) // from AppC to ServiceB
// {
//     message.message = MQ_REQUESTUPDATEEMPLOYEEINFO;
//     memcpy(message.buffer,&emplinfo,sizeof(EmployeeInfo));
//     cv.notify_one();
// }
//     // only call from App A
// bool MessageQueue::onEmployeeInfoChanged(const EmployeeInfo& emplinfo) // from ServiceB to AppA
// {
//     EmployeeInfoModel::getInstance().onEmployeeInfoChanged(emplinfo);
// }
// // only call from App A
// EmployeeInfo MessageQueue::requestEmployeeInfo(const int id){
//     message.message = MQ_REQUESTEMPLOYEEINFO;
//     message.buffer[0] = id;
//     // memcpy(&(message.buffer),&id,sizeof(int));
//     cv.notify_one();
// }