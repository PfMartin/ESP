import paho.mqtt.client as mqtt
from time import sleep

#variables
host = "192.168.178.62"
counter = 0

#Setup
client = mqtt.Client("Pub1")
client.connect(host)

#Publishing
while counter < 10:
    client.publish("data", counter) #topic, data
    counter += 1
    sleep(0.5)

client.disconnect()
quit()


