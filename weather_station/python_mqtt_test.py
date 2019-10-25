import paho.mqtt.client as mqtt
import time

broker_address = "10.120.128.52"
client = mqtt.Client("P1") #create new instance
client.connect(broker_address) #connect to broker
topic = "test"

counter = 0

def quit_program():
    print("Program has been terminted")
    quit()

try:
    while counter < 10:
        client.publish(topic, counter)
        counter += 1
        time.sleep(1)

    quit_program()

except KeyboardInterrupt:
    quit_program()
