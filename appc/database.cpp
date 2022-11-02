#include "database.h"

bool Database::loadDatabase(const std::string database_file){
    qDebug() << "Read file: " << QString::fromStdString(database_file) ;
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

QList<EmployeeScore> Database::requestEmployeeScoreList(){
    if(m_employeeList.size() == 0){
        return QList<EmployeeScore>();
    }
    QList<EmployeeScore> retval;
    for(auto& e : m_employeeList){
        EmployeeScore es;
        es.id = e.id;
        strncpy(es.name , std::string(e.name).c_str(), MAX_NAME_CHAR);
        es.score = (e.asm_score + e.cpp_score + e.js_score + e.opengl_score + e.qml_score)/ 5;
        retval.append(es);
    }
    return retval;
}
