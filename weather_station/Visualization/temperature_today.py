import matplotlib.pyplot as plt
import numpy as np
import csv
import datetime

d = datetime.datetime.today()
today = str(d)[:10]

print('Date: ' + today)

x = []
y = []

with open('%s_temperature.csv' %today, 'r') as file:
  data = csv.reader(file, delimiter=',')
  for row in data:
    if len(row[1]) == 18:
      x.append(row[1][-7:-3])
    elif len(row[1]) == 19:
      x.append(row[1][-8:-3])

    y.append(float(row[0]))

plt.plot(x, y, marker = 'x')
plt.title('Temperature over time outside of the Basislager')
plt.xlabel('Time of day')
plt.ylabel('Temperature in degree Celsius')

plt.show()