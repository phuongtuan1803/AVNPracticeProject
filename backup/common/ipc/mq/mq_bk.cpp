#include "mq.h"
#include "../../database.h"
#include "../../EmployeeInfoModel.h"
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

// Only send to Service B
void MessageQueue::appc_start(){
    open();

    auto f = [this]() {
        char temp_buf [10];
        while (1) {            
            // condition to send requestUpdateEmployeeInfo
            std::unique_lock<std::mutex> lck(m);
            cv.wait(lck);
            std::cout << "appc_start(): Received message: rec_msg->message: " << int(message.message) <<std::endl;
            memset(out_buffer,0,MSG_BUFFER_SIZE);
            memcpy(out_buffer,&message,sizeof(MQ_DATA_T));
            std::cout << "appc_start(): send signal: " << int(out_buffer[0]) << std::endl;
            std::cout << "appc_start(): send signal: " << int(out_buffer[1]) << std::endl;
            if (mq_send (qd_b, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
                perror ("appc_start(): Server: Not able to send message to client");
                continue;
            }
            std::cout << "appc_start(): Server: sent message to client" <<std::endl;
        }
    };
    std::thread th(f);

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // std::cout << "appc_start(): send signal" <<std::endl;
    // EmployeeInfo empinfo;
    // empinfo.id = 1;
    // memcpy(empinfo.name,"Hello Tuan",MAX_NAME_CHAR);
    // empinfo.asm_score = 1;
    // empinfo.cpp_score = 1;
    // empinfo.js_score = 1;
    // empinfo.opengl_score = 1;
    // empinfo.qml_score = 1;
    // MessageQueue::getInstance()->requestUpdateEmployeeInfo(empinfo);

    // th.join();
}

// Receive from App C and  send to App A
void MessageQueue::serviceb_start(){
    open();

    auto f = [this]() {
        char temp_buf [10];
        while (1) {   
            printf ("serviceb_start(): Server: begin check.\n");         
            if (mq_receive (qd_b, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
                perror ("serviceb_start(): Server: mq_receive");
                continue;
            }
                std::cout << "serviceb_start(): received signal: " << int(in_buffer[0]) << std::endl;
                std::cout << "serviceb_start(): received signal: " << int(in_buffer[1]) << std::endl;
            MQ_DATA_T rec_msg;
            memcpy(&rec_msg,in_buffer,sizeof(MQ_DATA_T));
            std::cout << "serviceb_start(): Received message: rec_msg->message: " << int(rec_msg.message) <<std::endl;
            if(rec_msg.message == MQ_REQUESTUPDATEEMPLOYEEINFO){
                rec_msg.message = MQ_ONEMPLOYEEINFOCHANGED; // fw message to App A onEmployeeInfoChanged

                std::cout << "serviceb_start(): Begin sent: MQ_ONEMPLOYEEINFOCHANGED" <<std::endl;

                memset(out_buffer,0,MSG_BUFFER_SIZE);
                memcpy(out_buffer,&rec_msg,sizeof(MQ_DATA_T));
                std::cout << "serviceb_start(): send signal: " << int(out_buffer[0]) << std::endl;
                std::cout << "serviceb_start(): send signal: " << int(out_buffer[1]) << std::endl;
                if (mq_send (qd_a, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
                    perror ("serviceb_start(): Server: Not able to send message to client");
                    continue;
                }
            } else if(rec_msg.message == MQ_REQUESTEMPLOYEEINFO){
                int id;
                id = rec_msg.buffer[0];
                // memcpy(&id,rec_msg.buffer,sizeof(int));

                // Prepare data
                EmployeeInfo emplinfo = Database::getInstance()->requestEmployeeInfo(id);
                std::cout << "serviceb_start(): id: " << emplinfo.id <<std::endl;
                std::cout << "serviceb_start(): name: " << emplinfo.name <<std::endl;
                std::cout << "serviceb_start(): asm_score: " << emplinfo.asm_score <<std::endl;
                std::cout << "serviceb_start(): cpp_score: " << emplinfo.cpp_score <<std::endl;
                std::cout << "serviceb_start(): js_score: " << emplinfo.js_score <<std::endl;
                std::cout << "serviceb_start(): opengl_score: " << emplinfo.opengl_score <<std::endl;
                std::cout << "serviceb_start(): qml_score: " << emplinfo.qml_score <<std::endl;
                // EmployeeInfo *e = static_cast<EmployeeInfo *>(static_cast<void*>(emplinfo));
                char *bef = static_cast<char*>(static_cast<void*>(&emplinfo));
                std::cout << "send signal: " << int(bef[0]) << std::endl;
                std::cout << "send signal: " << int(bef[1]) << std::endl;
                std::cout << "send signal: " << int(bef[2]) << std::endl;
                std::cout << "send signal: " << int(bef[3]) << std::endl;
                std::cout << "send signal: " << int(bef[4]) << std::endl;
                std::cout << "send signal: " << int(bef[5]) << std::endl;

                // Prepare message
                message.message = MQ_ONEMPLOYEEINFOCHANGED;
                memcpy(message.buffer,&emplinfo,sizeof(EmployeeInfo));

                EmployeeInfo *e = static_cast<EmployeeInfo *>(static_cast<void*>(message.buffer));
                std::cout << "serviceb_start(): name: " << e->name <<std::endl;
                std::cout << "serviceb_start(): asm_score: " << e->asm_score <<std::endl;
                std::cout << "serviceb_start(): cpp_score: " << e->cpp_score <<std::endl;
                std::cout << "serviceb_start(): js_score: " << e->js_score <<std::endl;
                std::cout << "serviceb_start(): opengl_score: " << e->opengl_score <<std::endl;
                std::cout << "serviceb_start(): qml_score: " << e->qml_score <<std::endl;

                std::cout << "serviceb_start(): Begin sent: MQ_ONEMPLOYEEINFOCHANGED" <<std::endl;
                std::cout << "serviceb_start(): send signal: " << int(out_buffer[0]) << std::endl;

                // memset(out_buffer,0,MAX_MSG_SIZE);
                memcpy(out_buffer,&message,MSG_BUFFER_SIZE-1);
                std::cout << "serviceb_start(): send signal: " << int(out_buffer[0]) << std::endl;
                std::cout << "send signal: " << int(out_buffer[0]) << std::endl;
                std::cout << "send signal: " << int(out_buffer[1]) << std::endl;
                std::cout << "send signal: " << int(out_buffer[2]) << std::endl;
                std::cout << "send signal: " << int(out_buffer[3]) << std::endl;
                std::cout << "send signal: " << int(out_buffer[4]) << std::endl;
                std::cout << "send signal: " << int(out_buffer[5]) << std::endl;
                std::cout << "strlen (out_buffer) : " << int(strlen (out_buffer) ) << std::endl;
                if (mq_send (qd_a, out_buffer, MAX_MSG_SIZE, NULL) == -1) {
                    perror ("serviceb_start(): Server: Not able to send message to client");
                    continue;
                }
            } {
                // Not support message
            }
        }
    };
  
    std::thread th(f);
    th.join();
}

    // only call from App C
bool MessageQueue::requestUpdateEmployeeInfo(EmployeeInfo& emplinfo) // from AppC to ServiceB 
{
    message.message = MQ_REQUESTUPDATEEMPLOYEEINFO;
    memcpy(message.buffer,&emplinfo,sizeof(EmployeeInfo));
    cv.notify_one();
}
    // only call from App A
bool MessageQueue::onEmployeeInfoChanged(const EmployeeInfo& emplinfo) // from ServiceB to AppA
{
    EmployeeInfoModel::getInstance().onEmployeeInfoChanged(emplinfo);
}
// only call from App A
EmployeeInfo MessageQueue::requestEmployeeInfo(const int id){
    message.message = MQ_REQUESTEMPLOYEEINFO;
    message.buffer[0] = id;
    // memcpy(&(message.buffer),&id,sizeof(int));
    cv.notify_one();
}