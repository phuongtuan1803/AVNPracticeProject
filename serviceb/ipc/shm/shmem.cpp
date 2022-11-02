#include "shmem.h"
#include <iostream>
#define SHMEM_KEY "provider"
#define SHMEM_SIZE       sizeof(SHMEM_DATA_T)

std::shared_ptr<Shmem> Shmem::getInstance()
{
    std::cout << "Shmem::getInstance" << std::endl;
    static std::shared_ptr<Shmem> instance (new Shmem());
    instance->open();
    return instance;
}

Shmem::Shmem()
{
    m_ptr = nullptr;
}

Shmem::~Shmem()
{
}

int Shmem::open(){
    /* create the shared memory object */
    int shm_fd = shm_open(SHMEM_KEY, O_CREAT | O_RDWR, 0666);
    
    /* configure the size of the shared memory object */
    ftruncate(shm_fd, SHMEM_SIZE);

    /* memory map the shared memory object */
    void* ptr = mmap(0, SHMEM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED){
        std::cout << "mmap failed: " << errno << std::endl;
    }
        
    m_ptr = reinterpret_cast<SHMEM_DATA_T*>(ptr);    
    return shm_fd;
}

bool Shmem::getEmployeeInfo(EmployeeInfo& emplinfo)
{
    if(m_ptr == nullptr)
    {
        return false;
    }
    pthread_mutex_lock(&shm_mutex);
    memcpy(&emplinfo, &m_ptr->t_EmployeeInfo, sizeof(emplinfo));
    pthread_mutex_unlock(&shm_mutex);

    return true;
}

bool Shmem::setEmployeeInfo(const EmployeeInfo& emplinfo)
{
    if(m_ptr == nullptr)
    {
        return false;
    }    
    pthread_mutex_lock(&shm_mutex);
    memcpy(&m_ptr->t_EmployeeInfo, &emplinfo, sizeof(emplinfo));
    pthread_mutex_unlock(&shm_mutex);

    return true;
}

bool Shmem::getEmployeeScoreList(EmployeeScoreList& employeeList)
{
    if(m_ptr == nullptr)
    {
        return false;
    }    
    pthread_mutex_lock(&shm_mutex);
    memcpy(&employeeList, &m_ptr->t_EmployeeScoreList, sizeof(employeeList));
    pthread_mutex_unlock(&shm_mutex);

    return true;
}

bool Shmem::setEmployeeScoreList(const EmployeeScoreList& employeeList)
{
    if(m_ptr == nullptr)
    {
        return false;
    }
    pthread_mutex_lock(&shm_mutex);
    memcpy(&m_ptr->t_EmployeeScoreList, &employeeList, sizeof(employeeList));
    pthread_mutex_unlock(&shm_mutex);
    return true;
}
