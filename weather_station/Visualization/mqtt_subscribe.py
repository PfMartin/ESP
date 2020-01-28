#https://techtutorialsx.com/2017/04/23/python-subscribing-to-mqtt-topic/

import paho.mqtt.client as mqtt
import time

def on_connect(client, userdata, flags, rc):
    global connected
    if rc == 0:
        print("Connected to broker")
        connected = True
    else:
        print("Connection failed")

def on_message(client, userdata, msg):
    print("Message received: " + msg.payload.decode("utf-8"))
    print("Message topic: " + msg.topic)
    print("Message qos: " + msg.qos)
    print("Message retain flag=" + msg.retain)

broker = "192.168.178.62"
port = 1883
topic = "weather_stats"

print("Creating new instance")
client = mqtt.Client("P1")
client.on_message = on_message #attach function to the callback
client.on_connect = on_connect #attach function to the callback

print("Connecting to broker")
client.connect(broker, port=port)
client.loop_start()

client.subscribe(topic, qos=0)
time.sleep(2)
client.publish(topic, "Message")
time.sleep(4)

print("Exiting")
client.loop_stop()

