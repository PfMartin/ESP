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

with open('%s_temperature.csv' %today, 'r') as file:
  data = csv.reader(file, delimiter=',')
  for row in data:
    if len(row[1]) == 25:
      x.append(row[1][-14:-10])
    elif len(row[1]) == 26:
      x.append(row[1][-15:-10])

    y.append(float(row[0]))

plt.figure(figsize=(10,9))

plt.plot(x, y)
plt.title('%s\nTemperature over time outside of the Basislager' %today)
plt.xlabel('Time of day')
plt.xticks(rotation=90)
plt.ylabel('Temperature in degree Celsius')

plt.show()