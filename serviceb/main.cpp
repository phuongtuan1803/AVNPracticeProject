#include <iostream>
#include "../common/avnDefs.h"
#include "database.h"
#include "ipc/shm/shmem.h"
#include "ServiceB.h"
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    // Load database
    Database::getInstance()->loadDatabase(std::string("../rc/database.json"));
    cout << "Database size: " << Database::getInstance()->m_employeeList.size() << endl;
    
    // Set database to shared memory
    EmployeeScoreList employeeScoreList = Database::getInstance()->requestEmployeeScoreList();
    Shmem::getInstance()->setEmployeeScoreList(employeeScoreList);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    cout << "Later -----------------------------" << endl;
    EmployeeScoreList employeeScoreList2;
    Shmem::getInstance()->getEmployeeScoreList(employeeScoreList2);
    for(int i = 0 ;i < MAX_EMP_LIST ; i++){
        if(employeeScoreList2.l[i].id == 0){
            break;
        }
        cout << std::string(employeeScoreList2.l[i].name) << endl;
    }

    // ServiceB::getInstance()->start();
    return 0;
}
