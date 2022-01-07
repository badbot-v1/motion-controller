#include "drivelineinterface.hpp"  
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>
#include "shared/system/sysevents.hpp"

DrivelineInterface::DrivelineInterface(std::string loggerName)
:SensorBase(loggerName)
{

}

DrivelineInterface::~DrivelineInterface()
{

}

bool DrivelineInterface::init(std::string sectionName)
{
    _log->info("Initialization started.");
    
    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));

    
    _telemetry_frame_height = config[sectionName]["telemetryFrameHeight"].as<int>();
    for(unsigned int i=0;i<_telemetry_frame_height; i++)
    {
        _driveline_history_left.push_back(0);
        _driveline_history_right.push_back(0);
    }

    _enabled = config[sectionName]["enabled"].as<bool>();
    _extra_trace_enabld = config[sectionName]["extraTraceEnabled"].as<bool>();

    _log->info(
        "Telemetry Frame Height (must match lidar frame height): [{}]", 
        config[sectionName]["telemetryFrameHeight"].as<int>()
    );

    if(_enabled)
    {
        _log->info("Tx Enabled at init: [{}]", _enabled);
    }else{
        _log->warn("Tx Enabled at init: [{}]", _enabled);
    }
    _log->info("Extra trace enabled?: [{}]", _extra_trace_enabld);

    //will also start the job thread
    SensorBase::init(sectionName);

    _log->info("Initialization finished.");
    return true;

}

void DrivelineInterface::drawTelemetry(Mat &frame)
{
    if(frame.rows < _telemetry_frame_height)
    {
        _log->warn("Expecting [{}] rows for telemetry frame, got only [{}]", _telemetry_frame_height, frame.rows);
        return;
    }
    deque<unsigned char> driveline_history_left(_driveline_history_left);
    deque<unsigned char> driveline_history_right(_driveline_history_right);

    int loop_limit = driveline_history_left.size() < _telemetry_frame_height ? driveline_history_left.size() : _telemetry_frame_height;

    //https://stackoverflow.com/questions/7899108/opencv-get-pixel-channel-value-from-mat-image
    uint8_t* pixelPtr = (uint8_t*)frame.data;
    int cn = frame.channels();
    Scalar_<uint8_t> bgrPixel;

    //draw histor onto frame
    #pragma omp parallel for
    for(int i=0;i<loop_limit;i++)
    {
        uint8_t val = driveline_history_left[i];
        // if(val+100 <=  255){
        //     val+=100;
        // }
         // G
        pixelPtr[i*frame.cols*cn + 5*cn + 1] = val;
        pixelPtr[i*frame.cols*cn + 6*cn + 1] = val;
        pixelPtr[i*frame.cols*cn + 7*cn + 1] = val;
        pixelPtr[i*frame.cols*cn + 8*cn + 1] = val;
        pixelPtr[i*frame.cols*cn + 9*cn + 1] = val;
        

        val = driveline_history_right[i];
        // if(val+100 <=  255){
        //     val+=100;
        // }
        //R
        pixelPtr[i*frame.cols*cn + 11*cn + 2] = val;
        pixelPtr[i*frame.cols*cn + 12*cn + 2] = val;
        pixelPtr[i*frame.cols*cn + 13*cn + 2] = val;
        pixelPtr[i*frame.cols*cn + 14*cn + 2] = val;
        pixelPtr[i*frame.cols*cn + 15*cn + 2] = val;
    }

    //finally in text write the latest values
    char str[255] = {0};
    sprintf(str, "L [%d] - R [%d]",
        _driveline_history_left.at(_driveline_history_left.size()-1), 
        driveline_history_right.at(driveline_history_right.size()-1)
    );

    drawText(str, 20, _telemetry_frame_height - 30, frame);
}

void DrivelineInterface::setEnabled(bool enabled)
{
    _enabled = enabled;
}

void DrivelineInterface::thread_proc()
{
    _log->debug("ThreadProc - entered.");

    doRx();

    _log->debug("ThreadProc - exiting.");
}

void DrivelineInterface::doRx()
{
    _log->warn("Child does not provide implementation for RX. Exiting.");
}

void DrivelineInterface::onCleanup()
{
    
}

//https://stackoverflow.com/questions/14047802/how-to-check-amount-of-data-available-for-a-socket-in-c-and-linux
int DrivelineInterface::isDataAvailableForRead(int socket)
{
    int count;
    ioctl(socket, FIONREAD, &count);

    return count;
}

void DrivelineInterface::cleanup()
{
    //let children cleanup
    onCleanup();    
}