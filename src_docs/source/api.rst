.. _rest-api:

REST API
########

All the API's use a key called ``ID`` which is the unique device id (chip id). This is used as an API key when sending requests to the device. 

GET: /api/config
================

Retrive the current configuation of the device via an HTTP GET command. Payload is in JSON format.

* ``temp-format`` can be either ``C`` or ``F``
* ``gravity-format`` is always ``G`` (plato is not yet supported)

Other parameters are the same as in the configuration guide.

.. code-block:: json

   {
      "mdns": "gravmon",
      "id": "ee1bfc",
      "ota-url": "http://192.168.1.50:80/firmware/gravmon/",
      "temp-format": "C",
      "brewfather-push": "http://log.brewfather.net/stream?id=Qwerty",
      "http-push": "http://192.168.1.50:9090/api/v1/Qwerty/telemetry",
      "http-push-h1": "header: value",                           
      "http-push-h2": "header: value",                           
      "http-push2": "http://192.168.1.50/ispindel",
      "http-push2-h1": "header: value",                           
      "http-push2-h2": "header: value",                           
      "influxdb2-push": "http://192.168.1.50:8086",
      "influxdb2-org": "org",
      "influxdb2-bucket": "bucket_id",
      "influxdb2-auth": "token",
      "mqtt-push": "192.168.1.50",
      "mqtt-port": 1883,
      "mqtt-user": "user",
      "mqtt-pass": "pass",
      "sleep-interval": 30,
      "voltage-factor": 1.59,
      "gravity-formula": "0.0*tilt^3+0.0*tilt^2+0.0017978*tilt+0.9436",
      "gravity-format": "G",
      "temp-adjustment-value": 0,
      "gravity-temp-adjustment": false,
      "gyro-temp": true,
      "gyro-calibration-data": {
         "ax": -330,
         "ay": -2249,
         "az": 1170,
         "gx": 99,
         "gy": -6,
         "gz": 4
      },
      "angle": 90.93,
      "gravity": 1.105,
      "battery": 0.04
   }


GET: /api/device
================

Retrive the current device settings via an HTTP GET command. Payload is in JSON format.

.. code-block:: json

   {
      "app-name": "GravityMon",
      "app-ver": "0.0.0",
      "id": "ee1bfc",
      "mdns": "gravmon"
   }


GET: /api/status
================

Retrive the current device status via an HTTP GET command. Payload is in JSON format.

* ``temp-format`` can be either ``C`` or ``F``

Other parameters are the same as in the configuration guide.

.. code-block:: json

   {
      "id": "ee1bfc",
      "angle": 89.86,
      "gravity": 1.1052,
      "gravity-tempcorr": 1.1031,
      "temp-c": 0,
      "temp-f": 32,
      "battery": 0,
      "temp-format": "C",
      "sleep-mode": false,
      "rssi": -56
   }


GET: /api/config/formula
========================

Retrive the data used for formula calculation data via an HTTP GET command. Payload is in JSON format.

* ``a1``-``a4`` are the angles/tilt readings (up to 5 are currently supported)
* ``g1``-``g4`` are the corresponding gravity reaadings in SG or Plato depending on the device-format.

.. code-block:: json

   { 
      "id": "ee1bfc",   
      "a1": 22.4,       
      "a2": 54.4, 
      "a3": 58, 
      "a4": 0, 
      "a5": 0, 
      "g1": 1.000,      
      "g2": 1.053, 
      "g3": 1.062, 
      "g4": 1, 
      "g5": 1,
      "gravity-format": "G", 
      "gravity-formula": "0.0*tilt^3+0.0*tilt^2+0.0017978*tilt+0.9436"
   }


POST: /api/config/device
========================

Used to update device settings via an HTTP POST command. Payload is in JSON format.

* ``temp-format`` can be either ``C`` (Celcius) or ``F`` (Farenheight)

.. code-block:: json

   { 
      "id": "ee1bfc",            
      "mdns": "gravmon",         
      "temp-format": "C",        
      "sleep-interval": 30       
   }


POST: /api/config/push
======================

Used to update push settings via an HTTP POST command. Payload is in JSON format.

.. code-block:: json

   { 
      "id": "ee1bfc",                                 
      "http-push": "http://192.168.1.50/ispindel", 
      "http-push2": "", 
      "http-push-h1": "",                           
      "http-push-h2": "",                           
      "http-push2-h1": "",                           
      "http-push2-h2": "",                           
      "brewfather-push": "",
      "influxdb2-push": "http://192.168.1.50:8086",
      "influxdb2-org": "Qwerty",
      "influxdb2-bucket": "Qwerty",
      "influxdb2-auth": "Qwerty" 
      "mqtt-push": "192.168.1.50",
      "mqtt-port": 1883,
      "mqtt-user": "Qwerty",
      "mqtt-pass": "Qwerty",
   }  


POST: /api/config/gravity
=========================

Used to update gravity settings via an HTTP POST command. Payload is in JSON format.

* ``gravity-formula`` keywords ``temp`` and ``tilt`` are supported.
* ``gravity-format`` can be either ``G`` (SG) or ``P`` (PLATO)

.. note::
  ``gravity-temp-adjustment`` is defined as "on" or "off" when posting since this is the output values 
  from a checkbox, when reading data it's sent as boolean (true,false).

.. code-block:: json

   { 
      "id": "ee1bfc",                                                   
      "gravity-formula": "0.0*tilt^3+0.0*tilt^2+0.0017978*tilt+0.9436",
      "gravity-format": "P",
      "gravity-temp-adjustment": "off"                                  
   }


POST: /api/config/hardware
==========================

Used to update hardware settings via an HTTP POST command. Payload is in JSON format.

.. note::
  ``gyro-temp`` is defined as "on" or "off" when posting since this is the output values from a checkbox, when
  reading data it's sent as boolean (true,false).

.. code-block:: json

   { 
      "id": "ee1bfc",                                   
      "voltage-factor": 1.59, 
      "temp-adjustment": 0, 
      "gyro-temp": "off",
      "ota-url": "http://192.168.1.50/firmware/gravmon/" 
   }


POST: /api/config/formula
=========================

Used to update formula calculation data via an HTTP POST command. Payload is in JSON format.

* ``a1``-``a4`` are the angles/tilt readings (up to 5 are currently supported)
* ``g1``-``g4`` are the corresponding gravity reaadings (in SG)

.. code-block:: json

   { 
      "id": "ee1bfc",   
      "a1": 22.4,       
      "a2": 54.4, 
      "a3": 58, 
      "a4": 0, 
      "a5": 0, 
      "g1": 1.000,      
      "g2": 1.053, 
      "g3": 1.062, 
      "g4": 1, 
      "g5": 1 
   }


Calling the API's from Python
=============================

Here is some example code for how to access the API's from a python script. Keys should always be 
present or the API call will fail.

.. code-block:: python

   import requests
   import json

   host = "192.168.1.1"           # IP adress (or name) of the device to send these settings to
   id = "ee1bfc"                  # Device ID (shown in serial console during startup or in UI)

   def set_config( url, json ):
      headers = { "ContentType": "application/json" }
      print( url )
      resp = requests.post( url, headers=headers, data=json )
      if resp.status_code != 200 :
         print ( "Failed "  )
      else :
         print ( "Success "  )

   url = "http://" + host + "/api/config/device"
   json = { "id": id, 
            "mdns": "gravmon",             # Name of the device
            "temp-format": "C",            # Temperature format C or F
            "sleep-interval": 30           # Sleep interval in seconds
         }
   set_config( url, json )

   url = "http://" + host + "/api/config/push"
   json = { "id": id, 
            "http-push": "http://192.168.1.1/ispindel",  
            "http-push2": "",                           
            "http-push-h1": "",                           
            "http-push-h2": "",                           
            "http-push2-h1": "",                           
            "http-push2-h2": "",                           
            "brewfather-push": "",                      
            "influxdb2-push": "",                       
            "influxdb2-org": "",
            "influxdb2-bucket": "",
            "influxdb2-auth": "",
            "mqtt-push": "192.168.1.50",
            "mqtt-port": 1883,
            "mqtt-user": "Qwerty",
            "mqtt-pass": "Qwerty"
            }  
   set_config( url, json )

   url = "http://" + host + "/api/config/gravity"
   json = { "id": id, 
            "gravity-formula": "",                  
            "gravity-format": "P",
            "gravity-temp-adjustment": "off"        # Adjust gravity (on/off)
            }
   set_config( url, json )

   url = "http://" + host + "/api/config/hardware"
   json = { "id": id, 
            "voltage-factor": 1.59,                 # Default value for voltage calculation
            "temp-adjustment": 0,                   # If temp sensor needs to be corrected
            "gyro-temp": "on",                      # Use the temp sensor in the gyro instead (on/off)
            "ota-url": ""                           # if the device should seach for a new update when active
         }
   set_config( url, json )

   url = "http://" + host + "/api/formula"
   json = { "id": id, 
            "a1": 22.4, 
            "a2": 54.4, 
            "a3": 58, 
            "a4": 0, 
            "a5": 0, 
            "g1": 1.000, 
            "g2": 1.053, 
            "g3": 1.062, 
            "g4": 1, 
            "g5": 1 
            }
   set_config( url, json )