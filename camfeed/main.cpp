#include "camfeed.hpp"
#include <iostream>
#include "shared/system/sysevents.hpp"
#include <sharedstorage/sharedstrings.hpp>
#include <csignal>
#include <cxxopts/cxxopts.hpp>

using namespace std;
SysEvents *sys = nullptr;


void signalHandler( int signum ) {
    
    cout << "Interrupt signal (" << signum << ") received.\n";

    sys->raiseSignalSysShutdown();

    exit(signum);  
}

bool validateOptions(int argc, char **argv)
{
    cxxopts::Options options("Fuse", "Sensor fusion and follower");
    options.add_options()
        ("d,debug", "Enable debugging.")
        ("c,conf", "Config YAML file name.", cxxopts::value<std::string>())
    ;
    auto result = options.parse(argc, argv);

    if(result.count("conf") == 0){
        cout << "Please provide configuration file path." << endl;
        options.show_positional_help();
        return false;
    }
    
    string conf_path;

    try{bool readConfig();
        conf_path = result["conf"].as<std::string>();
        SharedStrings::get()->setVal("config-file", conf_path);
    }catch(const std::exception& e)
    {
        cout << "Invalid configuration path provided, expected string." << endl;
        return false;
    }

    return true;
}

int main(int argc, char **argv)
{
    signal(SIGINT, signalHandler);  

    Gst::init(argc, argv);

    if(!validateOptions(argc,argv)){
        cout << "Unable to validate options. Exiting." << endl;
        return -1;
    }
    BadBotLogger::initLogging();

    sys = SysEvents::getInstance();
    Fuse fuse;
    return fuse.main(argc, argv);
}