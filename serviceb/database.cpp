#include "database.h"

std::shared_ptr<Database> Database::getInstance()
{
    static std::shared_ptr<Database> instance (new Database());
    return instance;
}

Database::Database()
{
    m_employeeList.clear();
}

bool Database::loadDatabase(const std::string database_file){
    // qDebug() << "Read file: " << QString::fromStdString(database_file) ;
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

EmployeeInfo Database::requestEmployeeInfo(const int id){
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

EmployeeInfo Database::requestEmployeeInfoAtIndex(const int index){
    if(index < m_employeeList.size()){
        return m_employeeList.at(index);
    }
    return EmployeeInfo();
}

EmployeeScoreList Database::requestEmployeeScoreList(){
    
    EmployeeScoreList retval;
    memset(&retval,0, sizeof(retval));

    int i =0;
    for(auto& e : m_employeeList){
        EmployeeScore es;
        es.id = e.id;
        strncpy(es.name , std::string(e.name).c_str(), MAX_NAME_CHAR);
        es.score = (e.asm_score + e.cpp_score + e.js_score + e.opengl_score + e.qml_score)/ 5;
        retval.l[i] = es;
        i++;
    }
    return retval;
}

void Database::requestUpdateEmployeeInfo(int id, int asm_score, int cpp_score, int js_score, int opengl_score, int qml_score){
    if(m_employeeList.size() == 0){
        return;
    }
    for(auto& e : m_employeeList){
        if(e.id == id){
            e.asm_score = asm_score;
            e.cpp_score = cpp_score;
            e.js_score = js_score;
            e.opengl_score = opengl_score;
            e.qml_score = qml_score;
        }
    }
    // set to shm, but this is inf file
    json j_obj = json::array();

    for(auto& e : m_employeeList){
        json j;
        j["id"] = e.id;
        j["name"] = std::string(e.name);
        j["asm_score"] = e.asm_score;
        j["cpp_score"] = e.cpp_score;
        j["js_score"] = e.js_score;
        j["opengl_score"] = e.opengl_score;
        j["qml_score"] = e.qml_score;
        j_obj.push_back(j);
        // qDebug() << QString::fromStdString(j.dump());
    }
    // write to file
    std::ofstream o("../rc/database.json");
    o << std::setw(4) << j_obj << std::endl;
}
