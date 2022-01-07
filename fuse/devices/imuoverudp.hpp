#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/signals2.hpp>
#include <memory>
#include <chrono>

#include "sensorbase.hpp"
#include "shared/log/badbotlogger.hpp"

using namespace std;

struct __attribute__((packed)) TELEMETRY_IMU 
{
  float ax, ay, az;
  float yaw, pitch, roll;
  float temperature;
  float pressure;
  float altitude;
  long timestamp;
};

class ImuOverUdp : public SensorBase
{
	public:
        typedef boost::signals2::signal<void (std::shared_ptr<TELEMETRY_IMU>)> signalIMU;
        typedef signalIMU::slot_type slot_imu;

	protected:
		struct sockaddr_in _rx_addr;
		int _sockfd;

	private:
        signalIMU _signalIMU;

	protected:
		void thread_proc() override;
		virtual void cleanup() override;
		
	public:
		ImuOverUdp();
		~ImuOverUdp();
		
		bool init();
		void connecToSignalIMUData(const slot_imu &slot);
};