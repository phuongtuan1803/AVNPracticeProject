#include "ServiceB.h"

std::shared_ptr<ServiceB> ServiceB::m_instance = nullptr;
std::shared_ptr<ServiceB> ServiceB::getInstance()
{
    if(m_instance == nullptr)
	{
		m_instance = std::make_shared<ServiceB>();
	}
	return m_instance;
}

ServiceB::ServiceB(){
    // Load database and save to shared mem
    Database::getInstance()->loadDatabase(std::string("../rc/database.json"));
    std::cout << "Database size: " << Database::getInstance()->m_employeeList.size() << std::endl;
    EmployeeScoreList employeeScoreList = Database::getInstance()->requestEmployeeScoreList();
    Shmem::getInstance()->setEmployeeScoreList(employeeScoreList);
}


void ServiceB::start()
{
    MessageQueue::getInstance()->serviceb_start();
}
