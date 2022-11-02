#ifndef SERVICEB_H
#define SERVICEB_H

// #include "../ipc/mp/BaseProxySync.h"

class ServiceB 
{

private:
    ServiceB();
    ServiceB(ServiceB const&) = delete;
    ServiceB& operator=(ServiceB const&) = delete;
    virtual ~ServiceB();


public:
    static std::shared_ptr<ServiceB> getInstance();
    void start();
    virtual bool requestEmployeeInfoSync(EmployeeInfo& employeeInfo);
};
#endif // SERVICEB_H
