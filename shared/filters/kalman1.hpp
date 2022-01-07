#pragma once

#include "shared/filters/kalmanbase.hpp"
#include "shared/log/badbotlogger.hpp"
#include <boost/signals2.hpp>
class Kalman1 : public KalmanBase
{
    public:
        typedef boost::signals2::signal<void (const float estimate)> signal_estimate;
        typedef signal_estimate::slot_type slot_signal_estimate;

    private:
        float _err_est_prev, _est_prev;
        atomic<float> _measurement_err, _measurement;
        signal_estimate _signal_estimate;
    
    protected:
        /**
         * Called by base class thread
         * 
         */
        virtual bool computeEstimate() override;
    
    public:
        Kalman1(float err_est_initial, float est_initial);
        float getEstimate(float err_measurement_curr, float measurement_curr);
        void reset(float err_est_initial, float est_initial);

        void setMeasurements(float error, float measurement);
        void connectToSignalEstimate(const slot_signal_estimate &slot);
};