#!/usr/bin/env python3

import json
import paho.mqtt.client as mqtt
import time
import smbus
import Adafruit_DHT

# DHT11 Init Config
# Set sensor type : Options are DHT11,DHT22 or AM2302
sensor = Adafruit_DHT.DHT11
# Set GPIO sensor is connected to
gpio = 17
# --------------------------------

# BH1750 Init Config
# Read data from a BH1750 digital light sensor.
#
# For more information please visit :
# https://www.raspberrypi-spy.co.uk/?s=bh1750
#

# Define some constants from the datasheet

DEVICE = 0x23  # Default device I2C address

POWER_DOWN = 0x00  # No active state
POWER_ON = 0x01  # Power on
RESET = 0x07  # Reset data register value

# Start measurement at 4lx resolution. Time typically 16ms.
CONTINUOUS_LOW_RES_MODE = 0x13
# Start measurement at 1lx resolution. Time typically 120ms
CONTINUOUS_HIGH_RES_MODE_1 = 0x10
# Start measurement at 0.5lx resolution. Time typically 120ms
CONTINUOUS_HIGH_RES_MODE_2 = 0x11
# Start measurement at 1lx resolution. Time typically 120ms
# Device is automatically set to Power Down after measurement.
ONE_TIME_HIGH_RES_MODE_1 = 0x20
# Start measurement at 0.5lx resolution. Time typically 120ms
# Device is automatically set to Power Down after measurement.
ONE_TIME_HIGH_RES_MODE_2 = 0x21
# Start measurement at 1lx resolution. Time typically 120ms
# Device is automatically set to Power Down after measurement.
ONE_TIME_LOW_RES_MODE = 0x23

# bus = smbus.SMBus(0) # Rev 1 Pi uses 0
bus = smbus.SMBus(1)  # Rev 2 Pi uses 1

def convertToNumber(data):
    # Simple function to convert 2 bytes of data
    # into a decimal number. Optional parameter 'decimals'
    # will round to specified number of decimal places.
    result = (data[1] + (256 * data[0])) / 1.2
    return (result)

def readLight(addr=DEVICE):
    # Read data from I2C interface
    data = bus.read_i2c_block_data(addr, ONE_TIME_HIGH_RES_MODE_1)
    return convertToNumber(data)
# --------------------------------

# mqtt Init Config

clientId = "PI6Node-178"
serverIp = "192.168.123.8"
serverPort = 1883
client = mqtt.Client(client_id=clientId, clean_session=False)
client.connect(host=serverIp, port=serverPort)
client.loop_start()
# --------------------------------

# mqtt Send OnlineMessage
onlineNodeMessage = {"nodeId": clientId}
print(json.dumps(onlineNodeMessage))
client.publish("OnlineNode", json.dumps(onlineNodeMessage))
# --------------------------------

# mqtt Send UpdateMessage
updateNodeMessage = {"nodeId": clientId, "sensor": [
    {"sensorType": "dht11_t", "sensorId": clientId + ":1"},
    {"sensorType": "dht11_h", "sensorId": clientId + ":2"},
    {"sensorType": "light", "sensorId": clientId + ":3"}
], "controller": []}
print(json.dumps(updateNodeMessage))
client.publish("UpdateNode", json.dumps(updateNodeMessage))
# --------------------------------

# Message Driver
while True:
    # Use read_retry method. This will retry up to 15 times to
    # get a sensor reading (waiting 2 seconds between each retry).
    humidity, temperature = Adafruit_DHT.read_retry(sensor, gpio)
    # Reading the DHT11 is very sensitive to timings and occasionally
    # the Pi might fail to get a valid reading. So check if readings are valid.
    if humidity is not None and temperature is not None:
        print('Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature, humidity))
    else:
        print('Failed to get reading. Try again!')
        continue
    lightLevel = readLight(addr=DEVICE)
    print("Light Level : " + format(lightLevel, '.2f') + " lx")
    data = {"nodeId": clientId,
            "sensor": [
                {"sensorId": clientId + ":1", "sensorVal": temperature},
                {"sensorId": clientId + ":2", "sensorVal": humidity},
                {"sensorId": clientId + ":3", "sensorVal": lightLevel}
            ]}
    print(json.dumps(data))
    client.publish("SensorData", json.dumps(data))
    time.sleep(2.0)
