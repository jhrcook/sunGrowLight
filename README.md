# sunGrowLight

[![jhc github](https://img.shields.io/badge/GitHub-jhrcook-181717.svg?style=flat&logo=github)](https://github.com/jhrcook)
[![jhc twitter](https://img.shields.io/badge/Twitter-@JoshDoesA-00aced.svg?style=flat&logo=twitter)](https://twitter.com/JoshDoesa)
[![jhc website](https://img.shields.io/badge/Website-Joshua_Cook-5087B2.svg?style=flat&logo=telegram)](https://joshuacook.netlify.com)

An Arduino library for controlling a plant grow light with real sunrise and sunset times.

This library uses the ['sunMoon'](https://github.com/sfrwmaker/sunMoon) Arduino library to calculating the sunrise and sunset times.

## Basics

There is a simple example of a single `sunGrowLight` object in the "examples" directory.
Below are the basics for using the library.

A `sunGrowLight` object is instantiated with the relay pin it controls and the latitude, longitude, and timezone.
The timezone is the numbers of minutes offset from UTC.
This `sunGrowLight` object is placed at Joshua Tree National Park in California.

```cpp
int relayPin = 10;
sunGrowLight growLight(relayPin, 33.881866, -115.900650, 420);
```

In the project I used this library for, I used an Real Time Clock module Adafruit's 'RTClib' library to keep track of the time.

```cpp
#include <RTClib.h>
RTC_DS3231 rtc;
```

Finally, the status of the light can be checked using the `updateLights(time_t current_time)` method and passing the current time from the RTC.

```cpp
DateTime now_dt = rtc.now();
growLight(now_dt.unixtime());
```

The override can be toggled on and off using the `overrideLights(time_t current_time)` method.

```cpp
DateTime now_dt = rtc.now();
overrideLights(now_dt.unixtime());
```

### Helper functions

I included some helper functions to get information from the `sunGrowLight` object.

```cpp
# Returns the status of the lights.
bool getLightStatus();

# Returns the override status.
bool getOverrideStatus();

# Get the sunrise and sunset times for the current day.
time_t getSunriseDate(time_t current_time);
time_t getSunsetDate(time_t current_time);
```
