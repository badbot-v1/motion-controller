#pragma once

#include <map>
#include <string>
#include <mutex>

using namespace std;

class SharedStrings
{

    public:
        static SharedStrings* get();
        std::string getVal(std::string key);
        void setVal(std::string key, std::string val);

    private:
        SharedStrings();

    private:
        static SharedStrings* _instance;
        mutex _mutexAccess;
        map<string,string> _map;
};