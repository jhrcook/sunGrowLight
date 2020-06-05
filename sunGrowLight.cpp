/*
    GrowLight.h - Library for controlling a LED grow light
    Created by Joshua H. Cook (2019/02/16)
*/

#include "Arduino.h"
#include "sunGrowLight.h"
#include "sunMoon.h"
#include "Time.h"


sunGrowLight::sunGrowLight(int control_pin, double latitude, double longitude, int timezone) {
    controlPin = control_pin;
    pinMode(controlPin, OUTPUT);
    posLatitude = latitude;
    posLongitude = longitude;
    posTimezone = timezone;
    sm.init(posTimezone, posLatitude, posLongitude);
    
    lightStatus = false;
    switchLightsOnOff(lightStatus);
    
    overrideStatus = false;
}

// update the lights given the current time
void sunGrowLight::updateLights(time_t current_time) {
    
    time_t sunrise = sm.sunRise(current_time);
    time_t sunset = sm.sunSet(current_time);
    
    if (!overrideStatus) {
        if (sunrise <= current_time && current_time < sunset && !lightStatus) {
            switchLightsOnOff(true);
        } else if ((current_time < sunrise | sunset <= current_time) && lightStatus) {
            switchLightsOnOff(false);
        }
    }
}

// turn the lights on or off
void sunGrowLight::switchLightsOnOff(bool state) {
    if (state) {
        digitalWrite(controlPin, LOW);   // turn lights ON
        lightStatus = state;
    } else {
        digitalWrite(controlPin, HIGH);  // turn lights OFF
        lightStatus = state;
    }
}

// switch to override status
void sunGrowLight::overrideLights(time_t current_time) {
    overrideStatus = !overrideStatus;
    Serial.print("override status: ");
    Serial.println(overrideStatus);
    if (overrideStatus) {
        switchLightsOnOff(!lightStatus);
    } else {
        updateLights(current_time);
    }
}

// request the current state of the lights
bool sunGrowLight::getLightStatus() {
    return lightStatus;
}

// request the current state of the override
bool sunGrowLight::getOverrideStatus() {
    return overrideStatus;
}


time_t sunGrowLight::getSunriseDate(time_t current_time) {
    return sm.sunRise(current_time);
}


time_t sunGrowLight::getSunsetDate(time_t current_time) {
    return sm.sunSet(current_time);
}
