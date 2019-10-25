import paho.mqtt.client as mqtt
import time

def on_message(client, userdata, message):
    print("Message received ", str(message.payload.decode("utf-8")))
    print("Message topic: ", message.topic)
    print("Message qos: ", message.qos)
    print("Message retain flag: ", message.retain)

brokerAddress = "10.120.128.52" #Raspberry Pi in idn network
topic = "DPS310"
client = mqtt.Client("S1")
client.on_message = on_message #attach function to callback
client.connect(brokerAddress)
client.loop_start() #start the loop
client.subscribe(topic)

time.sleep(4)

client.loop_stop()



