#include <iostream>
#include "../common/avnDefs.h"
#include "database.h"
#include "ipc/shm/shmem.h"
#include "ServiceB.h"
#include <chrono>
#include <thread>
#include "ipc/mq/mq.h"

using namespace std;

void mq_test(){
        // Set database to shared memory
    EmployeeScoreList employeeScoreList = Database::getInstance()->requestEmployeeScoreList();
    MessageQueue::getInstance()->serviceb_start();
    
}


int main()
{
    // Load database
    Database::getInstance()->loadDatabase(std::string("../rc/database.json"));
    cout << "Database size: " << Database::getInstance()->m_employeeList.size() << endl;
    mq_test();
    // ServiceB::getInstance()->start();
    return 0;
}
