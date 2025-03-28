#include <Arduino.h>
#include "datatypes.h"

    

        PIDController::PIDController() : Kp(1.0), Ki(0.0), Kd(0.0), integral(0.0), previous_error(0.0),
                          last_time(micros())
        {
        }

        PIDController::PIDController(const float Kp, const float Ki, const float Kd) : Kp(Kp), Ki(Ki), Kd(Kd), integral(0.0),
                                                                        previous_error(0.0),
                                                                        last_time(micros())
        {
        }

        void PIDController::setParameters(const float Kp, const float Ki, const float Kd)
        {
            this->Kp = Kp;
            this->Ki = Ki;
            this->Kd = Kd;
        }

        void PIDController::reset()
        {
            integral = 0.0;
            previous_error = 0.0;
            last_time = micros();
        }

        float PIDController::calculate(const float error)
        {
            const auto current_time = micros();
            const unsigned long time_diff = current_time - last_time;
            last_time = current_time;

            integral += error * time_diff;
            const double derivative = (error - previous_error) / time_diff;
            previous_error = error;

            return static_cast<float>(error * Kp + Ki * integral + Kd * derivative);
        }
