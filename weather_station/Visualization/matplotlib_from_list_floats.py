import matplotlib.pyplot as plt
import numpy as np
import random

n =  60 #number of data points
s = 0.2 #steps
y = []

#Create random numbers and store them in a text file
with open("random_floats.txt", "w") as file:
    print("Storing {0:.0f} random float numbers in the file random_number.txt".format(n/s)) #way to insert variable into string
    for i in np.arange(-20, n-20, s):
        file.write(str(random.uniform(-20, 100))+ "\n")

#Create a list with the numbers from the file
with open("random_floats.txt", "r") as file:
    print("Reading {0:.0f} datapoints".format(n/s))
    for line in file:
        y.append(float(line))

#Create the Plot
x = np.arange(0, n, s)

plt.plot(x, y, label="random data points")

plt.title("Temperature history")
plt.xlabel("Time in min")
plt.ylabel("Temperature in °C")
plt.legend()

plt.show()
