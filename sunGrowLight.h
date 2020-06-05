/*
    GrowLight.h - Library for controlling a LED grow light
    Created by Joshua H. Cook (2019/02/16)
*/

#ifndef sunGrowLight_h
#define sunGrowLight_h

#include "Arduino.h"
#include "sunMoon.h"
#include "Time.h"

class sunGrowLight {
    private:
        int controlPin;
        double posLatitude;
        double posLongitude;
        int posTimezone;
        sunMoon sm;
        bool lightStatus;
        bool overrideStatus;
        void switchLightsOnOff(bool state);
    
    public:
        sunGrowLight(int control_pin, double latitude, double longitude, int timezone);
        void updateLights(time_t current_time);
        void overrideLights(time_t current_time);
        bool getLightStatus();
        bool getOverrideStatus();
        time_t getSunriseDate(time_t current_time);
        time_t getSunsetDate(time_t current_time);
};

#endif
