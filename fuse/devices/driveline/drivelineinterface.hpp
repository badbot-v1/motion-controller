#pragma once

#include <deque>
#include <sys/ioctl.h>
#include <mtlog/badbotlogger.hpp>
#include <opencv2/core.hpp>
#include "shared/drawing/drawingbase.hpp"
#include "fuse/devices/sensorbase.hpp"

using namespace std;
using namespace cv;

#pragma pack(push, 1)
struct IMUData
{
	float ax, ay, az;
	float yaw, pitch, roll;  
	float temperature;
	float pressure;
	float altitude;
	int32_t timestamp;
};
#pragma pack(pop)

class DrivelineInterface  : public SensorBase, public DrawingBase
{
	protected:
		deque<unsigned char> _driveline_history_left;
		deque<unsigned char> _driveline_history_right;
		bool _enabled = false;
		bool _extra_trace_enabld = false;
		unsigned int _telemetry_frame_height = 512;

	public:
		virtual bool txCmd(std::string source, unsigned char vLeft, unsigned char vRight) = 0;
		void drawTelemetry(Mat &frame);
		void setEnabled(bool enabled);

	protected:
		DrivelineInterface(std::string loggerName);
		~DrivelineInterface();
		bool init(std::string sectionName);
		virtual void doRx();
		/**
		 * Checks to see if there is data available to be read
		 * and returns the number of bytes available
		 **/
		int isDataAvailableForRead(int socket);
		/*
			Children should implement this and free up any resources
		*/
		virtual void onCleanup();

	private:
		void thread_proc() override;
		void cleanup() override;
		
};