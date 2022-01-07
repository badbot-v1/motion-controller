#pragma once

#include <mtlog/badbotlogger.hpp>
#include <sharedstorage/sharedstrings.hpp>
#include <atomic>
#include <thread>
#include <boost/signals2.hpp>

using namespace std;
using namespace boost;


class ControllerBase : protected BadBotLogger
{
    public:
        typedef boost::signals2::signal<void (std::string source, unsigned char vLeft, unsigned char vRight)> signalDrivelineCmd;
        typedef signalDrivelineCmd::slot_type slot_signalDrivelineCmd;

    protected:
        //how many frames to keep the motor on once drive command is issued
        atomic<int> _driveline_on_counter; //decremented with every read frame
        
        //read from config
        //how much person can deviate before we take corrective action
        int _DEADZONE_MIN;
        int _DEADZONE_MAX;

        //how many ms to repeat the last action
        int _MS_TO_REPEAT_LAST_CMD;
        int _CMD_CALCULATION_FREQUENCY;
        int _MAX_NO_UPDATE_DURATION;

        std::thread _thread_cmd_generator;
        bool _keep_running = true;
                
        //flagged by the orchestrator
        //if true signals will be raised an calcualtions will be done
        bool _active_controller = false;

        signalDrivelineCmd _signalDrivelineCmd;

        //safety feature, how long since we last got a sensor update?
        //if we do not get updated in _MAX_NO_UPDATE_DURATION we stop issuing commands
        std::chrono::time_point<std::chrono::system_clock> _last_updated_inputs_at;

    protected:

        bool init(std::string ymlNodeName);
        /**
         * Utility function that takes returns true if
         *  current time - _last_updated_inputs_at < _MAX_NO_UPDATE_DURATION
         * or false otherwise
         */
        bool isInputStillValid();

        /**
         * updates the member field _last_updated_inputs_at with current system clock timepoint
         */
        void updateLastInputRxTime();

    public:
        ControllerBase(std::string name);
        bool cleanup();
        virtual void calculateNextFrame() = 0;
        void connectToSignalDrivelineCmd(const slot_signalDrivelineCmd &slot);
        virtual void setActive(bool state);
        void raiseDrivelineSignal(std::string source, unsigned char vLeft, unsigned char vRight);
};