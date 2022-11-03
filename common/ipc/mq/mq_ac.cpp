#include "mq_ac.h"
#include "../../database.h"
#include "../../AppController.h"
std::shared_ptr<MessageQueue> MessageQueue::getInstance()
{
    std::cout << "MessageQueue::getInstance" << std::endl;
    static std::shared_ptr<MessageQueue> instance (new MessageQueue());
    return instance;
}

MessageQueue::MessageQueue()
{
    // m_ptr = nullptr;
}

MessageQueue::~MessageQueue()
{
}

void MessageQueue::open(){
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
    if ((qd_a = mq_open (APPA_QUEUE_NAME, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        std::cout << "Server: mq_open (app A)" << std::endl;
    } 
    if ((qd_b = mq_open (SERB_QUEUE_NAME, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        std::cout << "Server: mq_open (server b)" << std::endl;
    } 
    if ((qd_c = mq_open (APPC_QUEUE_NAME, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        std::cout << "Server: mq_open (app c)" << std::endl;
    }
    std::cout << "MessageQueue::open(): qd_a: " << qd_a << ". qd_b: " << qd_b << ". qd_c: " << qd_c << std::endl;
}

// Only send/receive from Service B
void MessageQueue::appa_start(){
    open();

    auto f_receive = [this]() {
        char temp_buf [10];
        while (1) {            
            if (mq_receive (qd_a, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
                perror ("appa_start(): Server: mq_receive");
                continue;
            }

            printf ("appa_start(): Server: message received.\n");

            MQ_DATA_T rec_msg;
            memcpy(&rec_msg,in_buffer,sizeof(MQ_DATA_T));
            std::cout << "appa_start(): received signal: " << int(in_buffer[0]) << std::endl;
            std::cout << "appa_start(): received signal: " << int(in_buffer[1]) << std::endl;
            std::cout << "appa_start(): received signal: " << int(in_buffer[2]) << std::endl;
            std::cout << "appa_start(): received signal: " << int(in_buffer[3]) << std::endl;
            std::cout << "appa_start(): received signal: " << int(in_buffer[4]) << std::endl;
            std::cout << "appa_start(): received signal: " << int(in_buffer[5]) << std::endl;
            std::cout << "appa_start(): received signal: " << int(in_buffer[6]) << std::endl;
            std::cout << "appa_start(): Received message: rec_msg->message: " << int(rec_msg.message) <<std::endl;
            if(rec_msg.message == MQ_ONEMPLOYEEINFOCHANGED){
                std::cout << "appa_start(): Received: MQ_ONEMPLOYEEINFOCHANGED" <<std::endl;
                EmployeeInfo tmp;
                // memcpy(&tmp,&rec_msg.buffer,sizeof(EmployeeInfo));
                // EmployeeInfo *e = static_cast<EmployeeInfo *>(static_cast<void*>(tmp));
                EmployeeInfo *e = static_cast<EmployeeInfo *>(static_cast<void*>(rec_msg.buffer));
                memcpy(&tmp,e,sizeof(EmployeeInfo));
                std::cout << "appa_start(): " << (e->id) <<std::endl;
                std::cout << "appa_start(): " << (e->name) <<std::endl;
                std::cout << "appa_start(): " << (e->asm_score) <<std::endl;
                onEmployeeInfoChanged(*e); // App A will overide this function
            }
        }
    };

    auto f_send = [this]() {
        char temp_buf [10];
        while (1) {            
            // condition to send requestEmployeeInfo
            std::unique_lock<std::mutex> lck(m);
            cv.wait(lck);
            std::cout << "appa_start(): Received message: rec_msg->message: " << int(message.message) <<std::endl;
            memset(out_buffer,0,MSG_BUFFER_SIZE);
            memcpy(out_buffer,&message,sizeof(MQ_DATA_T));
            std::cout << "appa_start(): send signal: " << int(out_buffer[0]) << std::endl;
            std::cout << "appa_start(): send signal: " << int(out_buffer[1]) << std::endl;
            if (mq_send (qd_b, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
                perror ("appa_start(): Server: Not able to send message to client");
                continue;
            }
            std::cout << "appa_start(): Server: sent message to client" <<std::endl;
        }
    };
    std::thread th1(f_receive);
    std::thread th2(f_send);
    th1.detach();
    th2.detach();
}

//     // only call from App C
// bool MessageQueue::requestUpdateEmployeeInfo(EmployeeInfo& emplinfo) // from AppC to ServiceB 
// {
//     message.message = MQ_REQUESTUPDATEEMPLOYEEINFO;
//     memcpy(message.buffer,&emplinfo,sizeof(EmployeeInfo));
//     cv.notify_one();
// }
    // only call from App A
bool MessageQueue::onEmployeeInfoChanged(const EmployeeInfo& emplinfo) // from ServiceB to AppA
{
    AppController::getInstance().onEmployeeInfoChanged(emplinfo);
}
// only call from App A
EmployeeInfo MessageQueue::requestEmployeeInfo(const int id){
    message.message = MQ_REQUESTEMPLOYEEINFO;
    message.buffer[0] = id;
    // memcpy(&(message.buffer),&id,sizeof(int));
    cv.notify_one();
}