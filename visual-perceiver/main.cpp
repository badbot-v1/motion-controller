#include "vpm.hpp"
#include "shared/system/sysevents.hpp"

#include <gstreamermm.h>
#include <iostream>
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
    cxxopts::Options options("Visual Perceiver", "Video control and analytics");
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
    try
    {
        signal(SIGINT, signalHandler);  

        Gst::init(argc, argv);

        if(!validateOptions(argc,argv)){
            cout << "Unable to validate options. Exiting." << endl;
            return -1;
        }
        BadBotLogger::initLogging("logging","vpm.log");

        sys = SysEvents::getInstance();
        VisualPerceptionModule vpm;
        return vpm.main(argc, argv);        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }catch(...)
    {
        std::cerr << "General failure on startup." << endl;
    }
    
    return -1000;
}