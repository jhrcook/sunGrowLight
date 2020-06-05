/*
 * An example of the 'sunGrowLight' Library.
 * 
 * Joshua H. Cook
 * 2020-06-05
 */

#include <Time.h>
#include <RTClib.h>
#include "sunGrowLight.h"

#define OUR_latitude 42.3417
#define OUR_longtitude -71.1004
#define OUR_timezone -240                     // localtime with UTC difference in minutes

// initiate RTC module object
RTC_DS3231 rtc;

// IO pins
int relayOne = 10;
int buttonOne = 3;

sunGrowLight lightOne(relayOne, OUR_latitude, OUR_longtitude, OUR_timezone);

void setup() {
    Serial.begin(9600);
    Serial.print("Setting up... ");

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(buttonOne, INPUT_PULLUP);
    
    // begin RTC
    rtc.begin();

//    if (rtc.lostPower()) {
    if (false) {
        Serial.println("RTC lost power, lets set the time!");
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    Serial.print("safety pause... ");
    delay(500);
    Serial.println("done");
    
 }

 void loop() {
    // Retrieve the current time.
    DateTime now_dt = rtc.now();
    
    // Check the current time against the time limits
    lightOne.updateLights(now_dt.unixtime());
    
    // Check time every 15 sec, otherwise look for button presses
    int checkTimeDelay = 2000;
    unsigned long start_timer = millis();
    unsigned long end_timer = start_timer;
    while(end_timer >= start_timer && checkTimeDelay > (end_timer - start_timer)) {

        if (checkButtonForLight(buttonOne, &lightOne) == LOW ) {
            delay(500);
            Serial.println("Button pressed");
            printSunriseSunsetTimes(lightOne);
            break;
        }
        
        delay(50);
        end_timer = millis();
    }
    Serial.println("(end of cycle)");
 }


// Check if the `button` is pressed. If it is, toggle the
// lights `gl` override switch.
int checkButtonForLight(int button, sunGrowLight *gl) {
    int buttonState = digitalRead(button);
    if (buttonState == LOW) {
            DateTime now_dt = rtc.now();
            gl->overrideLights(now_dt.unixtime());
        }
    return buttonState;
}


// Print the sunrise and sunset times for the date provided.
void printSunriseSunsetTimes(sunGrowLight gl) {
    DateTime now_dt = rtc.now();
    time_t sunrise = gl.getSunriseDate(now_dt.unixtime());
    time_t sunset = gl.getSunsetDate(now_dt.unixtime());
    
    Serial.print("Today's sunrise and sunset: ");
    printDate(sunrise); Serial.print("; ");
    printDate(sunset);  Serial.println("");
}


void printDate(time_t current_date) {
    char buff[20];
    sprintf(
        buff, "%2d-%02d-%4d %02d:%02d:%02d",
        day(current_date), month(current_date), year(current_date), 
        hour(current_date), minute(current_date), second(current_date)
    );
    Serial.print(buff);
}
