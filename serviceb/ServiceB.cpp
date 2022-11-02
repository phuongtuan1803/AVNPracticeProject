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

}

void ServiceB::start();


bool ServiceB::requestEmployeeInfoSync(const int id, EmployeeInfo& employeeInfo){

}