#include <iostream>
#include "../common/avnDefs.h"
#include "../common/ipc/shm/shmem.h"
#include "mq_b.h"
#include "database.h"
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    Database::getInstance()->loadDatabase("../rc/database.json");
    EmployeeScoreList employeeScoreList = Database::getInstance()->requestEmployeeScoreList();
    Shmem::getInstance()->setEmployeeScoreList(employeeScoreList);
    MessageQueueB::getInstance()->start_receive();
    while(1){};
    return 0;
}
