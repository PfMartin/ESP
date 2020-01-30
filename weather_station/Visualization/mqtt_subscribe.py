#https://techtutorialsx.com/2017/04/23/python-subscribing-to-mqtt-topic/

import paho.mqtt.client as mqtt
import time
from datetime import datetime

def on_connect(client, userdata, flags, rc):
    global connected
    if rc == 0:
        print("Connected to broker")
        connected = True
    else:
        print("Connection failed")

def on_message(client, userdata, msg):
    print("Message received: " + msg.payload.decode("utf-8") + " (" + str(datetime.now()) + ")")
    #print("Message topic: " + msg.topic)
    #print("Message qos: " + msg.qos)
    #print("Message retain flag=" + msg.retain)
    with open("values.csv", "a") as file:
        file.write(msg.payload.decode("utf-8") + "," + str(datetime.now()) + "\n")

broker = "192.168.178.62"
port = 1883
topic = "weather_stats"

print("Creating new instance")
client = mqtt.Client("P1")
client.on_message = on_message
client.on_connect = on_connect

print("Connecting to broker")
client.connect(broker, port=port)

client.loop_start()

client.subscribe(topic, qos = 0)
time.sleep(1)
client.publish(topic, "value")
time.sleep(1)

try:
 print("Waiting for messages")
 while True:
  time.sleep(0.1)

except KeyboardInterrupt:
 print("Exiting")
 client.loop_stop()
 client.disconnect()
