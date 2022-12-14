#ifndef AVNDATABASE_H
#define AVNDATABASE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"
#include "avnDefs.h"
#include <QDebug>
using json = nlohmann::json;

class Database
{
protected:

    Database(){
        m_employeeList.clear();
    };
public:
    Database(Database &other) = delete;
    void operator=(const Database &) = delete;

    static Database& getInstance()
    {
        static Database singleton_;
        return singleton_;
    };

public:
    std::vector<EmployeeInfo> m_employeeList;
    
    bool loadDatabase(const std::string database_file);
    
    EmployeeInfo requestEmployeeInfo(const int id);
    EmployeeInfo requestEmployeeInfoAtIndex(const int index);
    QList<EmployeeScore> requestEmployeeScoreList();
    void requestUpdateEmployeeInfo(int id, int asm_score, int cpp_score, int js_score, int opengl_score, int qml_score);

};
// Database* Database::singleton_= nullptr;
#endif // DATABASE_H
