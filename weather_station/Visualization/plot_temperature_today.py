import matplotlib.pyplot as plt
import numpy as np
import csv
import datetime

d = datetime.datetime.today()
today = str(d)[:10]

print('Date: ' + today)

x = []
y = []

with open('values.csv', 'r') as file:
  data = csv.reader(file, delimiter=',')
  for row in data:
    if row[1][:10] == today and row[0] != 'value':
      x.append(row[1][-15:-10])
      y.append(float(row[0]))

plt.figure(1)

plt.plot(x, y)
plt.title('%s\nOutside temperature Basis Lager' %today)
plt.xlabel('Time of day')
plt.xticks(rotation=90)
plt.ylabel('Temperature in degree Celsius')

mng = plt.get_current_fig_manager()
# For Linux system
mng.resize(*mng.window.maxsize())
# For Windows
# mng.window.state('zoomed')

plt.show()
