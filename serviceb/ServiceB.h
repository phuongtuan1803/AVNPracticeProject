#ifndef SERVICEB_H
#define SERVICEB_H

#include "../common/avnDefs.h"
#include "../common/database.h"
#include "../common/ipc/shm/shmem.h"
#include "../common/ipc/mq/mq_b.h"
#include <iostream>
class ServiceB 
{

protected:

    ServiceB(ServiceB const&) = delete;
    ServiceB& operator=(ServiceB const&) = delete;
    static std::shared_ptr<ServiceB> m_instance;
public:
    ServiceB();
    static std::shared_ptr<ServiceB> getInstance();
    void start();
};
#endif // SERVICEB_H
