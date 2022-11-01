#ifndef AVNDATABASE_H
#define AVNDATABASE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "nlohmann/json.hpp"
#include "avnDefs.h"

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
        // if(singleton_==nullptr){
        //     singleton_ = new Database();
        // }
        return singleton_;
    };

public:
    std::vector<EmployeeInfo> m_employeeList;
    
    bool loadDatabase(const std::string database_file){
        std::cout << "Read file: " << database_file ;
        std::ifstream f(database_file);
        if(!f.is_open()){
            return false;
        }
        json j = json::parse(f);
        m_employeeList.clear();

        for (auto& element : j) {
            EmployeeInfo empl;
            strncpy(empl.name , std::string(element.at("name")).c_str(), MAX_NAME_CHAR);
            empl.id = element.at("id");
            empl.asm_score = element.at("asm_score");
            empl.cpp_score = element.at("cpp_score");
            empl.js_score = element.at("js_score");
            empl.opengl_score = element.at("opengl_score");
            empl.qml_score = element.at("qml_score");

            m_employeeList.push_back(empl);
        }
        return true;
    };
    
    EmployeeInfo requestEmployeeInfo(const int id){
        if(m_employeeList.size() == 0){
            return EmployeeInfo();
        }
        for(auto& e : m_employeeList){
            if(e.id == id){
                return e;
            }
        }
        return EmployeeInfo();
    }

    std::vector<EmployeeScore> requestEmployeeScoreList(){
        if(m_employeeList.size() == 0){
            return std::vector<EmployeeScore>();
        }
        std::vector<EmployeeScore> retval;
        for(auto& e : m_employeeList){
            EmployeeScore es;
            es.id = e.id;
            strncpy(es.name , std::string(e.name).c_str(), MAX_NAME_CHAR);
            es.score = (e.asm_score + e.cpp_score + e.js_score + e.opengl_score + e.qml_score)/ 5;
            retval.push_back(es);
        }
        return retval;
    }
};
// Database* Database::singleton_= nullptr;
#endif // DATABASE_H
