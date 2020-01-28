#https://techtutorialsx.com/2017/04/23/python-subscribing-to-mqtt-topic/

import paho.mqtt.client as mqttClient
import time

def on_connect(client, userdata, flags, rc):
    global connected
    if rc == 0:
        print("Connected to broker")
        connected = True
    else:
        print("Connection failed")

def on_message(client, userdata, message):
    print("Message received: " + message.payload)

connected = False

broker = "192.168.178.62"
port = 1883
#user = ""
#password = ""
topic = "weather_stats"

client = mqttClient.Client("Python")
#client.username_pw_set(Martin, password=Jahnel01)
client.on_connect = on_connect #attach function to the callback
client.on_message = on_message #attach function to the callback

client.connect(broker, port=port)
client.loop_start()

while connected != True:
    time.sleep(0.1)

client.subscribe(topic)

try:
    while True:
        time.sleep(1)

except KeyboardInterrupt:
    print("exiting")
    client.disconnect()
    client.loop_stop()
