#include "shared/filters/kalman1.hpp"

#define BIAS 0.0001f

Kalman1::Kalman1(float err_est_initial, float est_initial)
:KalmanBase("Kalman1", 10, 30),
_measurement_err(0.0f),
_measurement(0.0f)
{
    _err_est_prev = err_est_initial;
    _est_prev = est_initial;
}

float Kalman1::getEstimate(float err_measurement_curr, float measurement_curr)
{
    //calculate kalman gain ( where 0.00000001f is bias to prevent divide by zero errors)
    float kalman_gain = (_err_est_prev+BIAS) / (_err_est_prev + err_measurement_curr + BIAS);

    //calculate current estimate
    float estimate_curr = _est_prev + (kalman_gain * (measurement_curr - _est_prev));

    //calculate error in estimate
    _err_est_prev = (1 - kalman_gain) * (_err_est_prev + BIAS);

    _est_prev = estimate_curr;

    _log->trace(
        "G [{}] err_est_prev [{}] est [{}] err_measurement [{}] measurement [{}]",
        kalman_gain,
        _err_est_prev,
        _est_prev,
        err_measurement_curr,
        measurement_curr
    );

    return estimate_curr;
}

void Kalman1::reset(float err_est_initial, float est_initial)
{
    _err_est_prev = err_est_initial;
    _est_prev = est_initial;    
}

void Kalman1::setMeasurements(float error, float measurement)
{
    _measurement_err = error;
    _measurement = measurement;
}

bool Kalman1::computeEstimate()
{

    float estimate = getEstimate(_measurement_err, _measurement);
    auto now = std::chrono::steady_clock::now();

    if( (now - _time_last_estimate_signal) >= std::chrono::milliseconds(_ms_estimate_signal_interval))
    {
        _time_last_estimate_signal = now;
        //raise signal
        _signal_estimate(estimate);
    }

    return false; //do not exit thread
}

void Kalman1::connectToSignalEstimate(const slot_signal_estimate &slot)
{
    _signal_estimate.connect(slot);
}