#include <iostream>
#include "database.h"

using namespace std;

int main()
{
    Database::getInstance().loadDatabase("../rc/database.json");
    
    cout << "Hello World!" << endl;
    return 0;
}
