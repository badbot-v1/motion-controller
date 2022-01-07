#include "sharedstrings.hpp"

SharedStrings* SharedStrings::_instance = nullptr;

SharedStrings::SharedStrings()
{
    
}

std::string SharedStrings::getVal(std::string key)
{
    lock_guard<mutex> guard(_mutexAccess);
    
    auto iter = _map.find(key);
    
    if(iter != _map.end())
    {
        return iter->second;
    }

    return "";
}

void SharedStrings::setVal(std::string key, std::string val)
{
    lock_guard<mutex> guard(_mutexAccess);
    
    _map.emplace(key, val);
}

SharedStrings* SharedStrings::get()
{
    if(nullptr == _instance){
        _instance = new SharedStrings();
    }

    return _instance;
}