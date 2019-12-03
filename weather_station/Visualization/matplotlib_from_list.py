import matplotlib.pyplot as plt
import numpy as np
import random

n = 10 #number of data points
y = []

#Create random numbers and store them in a text file
with open("random_integers.txt", "w") as file:
    print("Storing {0} random numbers in the file random_number.txt".format(n)) #way to insert variable into string
    for i in range(0, n):
        file.write(str(random.randint(0,10))+ "\n")

#Create a list with the numbers from the file
with open("random_integers.txt", "r") as file:
    print("Reading {0} datapoints".format(n))
    for line in file:
        y.append(int(line))

#Create the Plot
x = np.linspace(0, n*5, n)

plt.plot(x, y, label="random data points")

plt.title("Temperature history")
plt.xlabel("Time in min")
plt.ylabel("Temperature in °C")
plt.legend()

plt.show()
