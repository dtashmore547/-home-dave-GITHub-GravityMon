/*
MIT License

Copyright (c) 2021-2023 Magnus

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>

#include <config.hpp>
#include <gyro.hpp>
#include <main.hpp>
#include <tempsensor.hpp>

OneWire myOneWire(PIN_DS);
DallasTemperature mySensors(&myOneWire);

TempSensor myTempSensor;

void TempSensor::setup() {
#if LOG_LEVEL == 6 && !defined(TSEN_DISABLE_LOGGING)
  Log.verbose(F("TSEN: Looking for temp sensors." CR));
#endif
  mySensors.begin();

  if (mySensors.getDS18Count()) {
    Log.notice(F("TSEN: Found %d temperature sensor(s). Using %d bit" CR),
               mySensors.getDS18Count(),
               myAdvancedConfig.getTempSensorResolution());
  } else {
    Log.warning(F("TSEN: No temp sensors found" CR));
  }

  // Set the temp sensor adjustment values
  _tempSensorAdjC = myConfig.getTempSensorAdjC();

#if LOG_LEVEL == 6 && !defined(TSEN_DISABLE_LOGGING)
  Log.verbose(F("TSEN: Adjustment values for temp sensor %F C." CR),
              _tempSensorAdjC);
#endif
}

void TempSensor::readSensor(bool useGyro) {
  if (useGyro) {
    // When using the gyro temperature only the first read value will be
    // accurate so we will use this for processing.
    _temperatureC = myGyro.getInitialSensorTempC();
    _hasSensor = true;
#if LOG_LEVEL == 6 && !defined(TSEN_DISABLE_LOGGING)
    Log.verbose(F("TSEN: Reciving temp value for gyro sensor %F C." CR),
                _temperatureC);
#endif
    return;
  }

  // If we dont have sensors just return 0
  if (!mySensors.getDS18Count()) {
#if !defined(TSEN_DISABLE_LOGGING)
    Log.notice(F("TSEN: No temperature sensors found. Skipping read." CR));
#endif
    _temperatureC = -273;
    return;
  }

  // Read the sensors
  mySensors.setResolution(myAdvancedConfig.getTempSensorResolution());
  mySensors.requestTemperatures();

  if (mySensors.getDS18Count() >= 1) {
    _temperatureC = mySensors.getTempCByIndex(0);
    _hasSensor = true;

#if LOG_LEVEL == 6 && !defined(TSEN_DISABLE_LOGGING)
    Log.verbose(F("TSEN: Reciving temp value for DS18B20 sensor %F C." CR),
                _temperatureC);
#endif
  }
}

// EOF
