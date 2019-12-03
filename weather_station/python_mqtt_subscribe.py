import paho.mqtt.client as mqtt

client = mqtt.Client("Sub1")
host = "192.168.178.62"

client.connect(host)

#Subscribing and printing message
client.subscribe("data")

