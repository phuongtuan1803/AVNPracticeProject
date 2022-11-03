#ifndef PROVIDER_H_
#define PROVIDER_H_

#include <memory>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
 #include <unistd.h>
#include <sys/types.h>

#include "../../../common/avnDefs.h"

class Shmem
{
private:
	Shmem();

public:
    virtual ~Shmem();
    static std::shared_ptr<Shmem> getInstance();

public:
    bool getEmployeeInfo(EmployeeInfo& emplinfo);
    bool setEmployeeInfo(const EmployeeInfo& emplinfo);

    bool getEmployeeScoreList(EmployeeScoreList& employeeList);
    bool setEmployeeScoreList(const EmployeeScoreList& employeeList);
private:
	void* getShmemPtr();
    int open();
private:
	SHMEM_DATA_T* m_ptr;
    pthread_mutex_t shm_mutex;

};

#endif //PROVIDER_H_
