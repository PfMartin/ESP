import matplotlib.pyplot as plt
import numpy as np
import csv
import datetime

d = datetime.datetime.today()
today = str(d)[:10]

print('Date: ' + today)
print(len("2020-03-23 1:50:34.344598"))

x = []
y = []

with open('values.csv', 'r') as file:
  data = csv.reader(file, delimiter=',')
  for row in data:
    if row[1][:10] == today and row[0] != 'value':
      x.append(row[1][-15:-10])
      y.append(float(row[0]))

plt.figure(figsize=(10, 10))

plt.plot(x, y)
plt.title('%s\nTemperature over time outside of the Basislager' %today)
plt.xlabel('Time of day')
plt.xticks(rotation=90)
plt.ylabel('Temperature in degree Celsius')

plt.show()