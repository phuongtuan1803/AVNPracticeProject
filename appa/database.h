#ifndef DATABASE_H
#define DATABASE_H

#include <json/value.h>
#include <fstream>
#include <string>
class Database
{
public:
    Database();

    bool loadDatabase(const std::string database_file){
        std::ifstream people_file(database_file, std::ifstream::binary);
        people_file >> people;
    };
};

#endif // DATABASE_H
