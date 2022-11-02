#include "mq.h"

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

// void MessageQueue::server_open(){
//     // mqd_t qd_server, qd_client;   // queue descriptors
//     // long token_number = 1; // next token to be given to client

//     struct mq_attr attr;

//     attr.mq_flags = 0;
//     attr.mq_maxmsg = MAX_MESSAGES;
//     attr.mq_msgsize = MAX_MSG_SIZE;
//     attr.mq_curmsgs = 0;
//     if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
//         std::cout << "Server: mq_open (server)" << std::endl;
//     } else{
//         perror ("Server: mq_receive when open");
//     }
// }

// void MessageQueue::server_start(){
//     token_number = 1;
//     auto f = [this]() {
//         while (1) {
//             // get the oldest message with highest priority
            
//             if (mq_receive (qd_server, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
//                 perror ("Server: mq_receive");
//                 continue;
//             }

//             printf ("Server: message received.\n");

//             // send reply message to client

//             if ((qd_client = mq_open (in_buffer, O_WRONLY)) == 1) {
//                 perror ("Server: Not able to open client queue");
//                 continue;
//             }

//             sprintf (out_buffer, "%ld", token_number);

//             if (mq_send (qd_client, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
//                 perror ("Server: Not able to send message to client");
//                 continue;
//             }

//             printf ("Server: response sent to client.\n");
//             token_number++;
//         }
//     };
  
//     // This thread is launched by using 
//     // lamda expression as callable
//     std::thread th(f);
//     th.join();
// }

// void MessageQueue::client_open(){
//     // create the client queue for receiving messages from server
//     sprintf (client_queue_name, "/client-%d", getpid ());

//     struct mq_attr attr;

//     attr.mq_flags = 0;
//     attr.mq_maxmsg = MAX_MESSAGES;
//     attr.mq_msgsize = MAX_MSG_SIZE;
//     attr.mq_curmsgs = 0;

//     if ((qd_client = mq_open (client_queue_name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
//         perror ("Client: mq_open (client)");
//         exit (1);
//     }

//     if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) {
//         perror ("Client: mq_open (server)");
//         exit (1);
//     }
// }

// void MessageQueue::client_start(){
//     token_number = 1;
//     auto f = [this]() {
//         char temp_buf [10];
//         while (1) {            
//             while (fgets (temp_buf, 2, stdin)) {

//                 // send message to server
//                 if (mq_send (qd_server, client_queue_name, strlen (client_queue_name) + 1, 0) == -1) {
//                     perror ("Client: Not able to send message to server");
//                     continue;
//                 }

//                 // receive response from server

//                 if (mq_receive (qd_client, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
//                     perror ("Client: mq_receive");
//                     exit (1);
//                 }
//                 // display token received from server
//                 printf ("Client: Token received from server: %s\n\n", in_buffer);
//             }
//         }
//     };
  
//     // This thread is launched by using 
//     // lamda expression as callable
//     std::thread th(f);
//     th.join();
// }

// void MessageQueue::client_close(){
//     if (mq_close (qd_client) == -1) {
//         perror ("Client: mq_close");
//         exit (1);
//     }

//     if (mq_unlink (client_queue_name) == -1) {
//         perror ("Client: mq_unlink");
//         exit (1);
//     }
//     printf ("Client: Close\n");
// }

// Only receive from Service B
void MessageQueue::appa_start(){
    open();

    auto f = [this]() {
        char temp_buf [10];
        while (1) {            
            if (mq_receive (qd_a, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
                perror ("Server: mq_receive");
                continue;
            }

            printf ("Server: message received.\n");

            MQ_DATA_T rec_msg;
            memcpy(&rec_msg,in_buffer,sizeof(MAX_MSG_SIZE));
            std::cout << "received signal: " << int(in_buffer[0]) << std::endl;
            std::cout << "received signal: " << int(in_buffer[1]) << std::endl;
            std::cout << "Received message: rec_msg->message: " << int(rec_msg.message) <<std::endl;
            if(rec_msg.message == MQ_ONEMPLOYEEINFOCHANGED){
                std::cout << "Received: MQ_ONEMPLOYEEINFOCHANGED" <<std::endl;
                EmployeeInfo tmp;
                memcpy(&tmp,&rec_msg,sizeof(EmployeeInfo));
                onEmployeeInfoChanged(tmp); // App A will overide this function
            }
        }
    };
  
    std::thread th(f);
    th.join();
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
            std::cout << "Received message: rec_msg->message: " << int(message.message) <<std::endl;
            memset(out_buffer,0,MSG_BUFFER_SIZE);
            memcpy(out_buffer,&message,sizeof(MQ_DATA_T));
            std::cout << "send signal: " << int(out_buffer[0]) << std::endl;
            std::cout << "send signal: " << int(out_buffer[1]) << std::endl;
            if (mq_send (qd_b, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
                perror ("Server: Not able to send message to client");
                continue;
            }
            std::cout << "Server: sent message to client" <<std::endl;
        }
    };
    std::thread th(f);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "send signal" <<std::endl;
    EmployeeInfo empinfo;
    empinfo.id = 1;
    memcpy(empinfo.name,"Hello Tuan",MAX_NAME_CHAR);
    empinfo.asm_score = 1;
    empinfo.cpp_score = 1;
    empinfo.js_score = 1;
    empinfo.opengl_score = 1;
    empinfo.qml_score = 1;
    MessageQueue::getInstance()->requestUpdateEmployeeInfo(empinfo);

    th.join();
}

// Receive from App C and  send to App A
void MessageQueue::serviceb_start(){
    open();

    auto f = [this]() {
        char temp_buf [10];
        while (1) {   
            printf ("Server: begin check.\n");         
            if (mq_receive (qd_b, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
                perror ("Server: mq_receive");
                continue;
            }
                std::cout << "received signal: " << int(in_buffer[0]) << std::endl;
                std::cout << "received signal: " << int(in_buffer[1]) << std::endl;
            MQ_DATA_T rec_msg;
            memcpy(&rec_msg,in_buffer,sizeof(MAX_MSG_SIZE));
            std::cout << "Received message: rec_msg->message: " << int(rec_msg.message) <<std::endl;
            if(rec_msg.message == MQ_REQUESTUPDATEEMPLOYEEINFO){
                rec_msg.message = MQ_ONEMPLOYEEINFOCHANGED; // fw message to App A onEmployeeInfoChanged

                std::cout << "Begin sent: MQ_ONEMPLOYEEINFOCHANGED" <<std::endl;

                memset(out_buffer,0,MSG_BUFFER_SIZE);
                memcpy(out_buffer,&rec_msg,sizeof(MQ_DATA_T));
                std::cout << "send signal: " << int(out_buffer[0]) << std::endl;
                std::cout << "send signal: " << int(out_buffer[1]) << std::endl;
                if (mq_send (qd_a, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
                    perror ("Server: Not able to send message to client");
                    continue;
                }
            } else {
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
}