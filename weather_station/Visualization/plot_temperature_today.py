import matplotlib.pyplot as plt
import numpy as np
import csv
import datetime

d = datetime.datetime.today()
today = str(d)[:10]

print('Date: ' + today)

x = []
y = []

# Store date from file in the lists for x and y
with open('values.csv', 'r') as file:
  data = csv.reader(file, delimiter=',')
  for row in data:
    if row[1][:10] == today and row[0] != 'value':
      x.append(row[1][-15:-10])
      y.append(float(row[0]))

fig = plt.figure()

# Configuring the axes
ax = fig.add_subplot(1, 1, 1)

y_major_ticks = np.arange(-20, 40, 1)
y_minor_ticks = np.arange(-20, 40, 0.2)

ax.set_yticks(y_major_ticks)
ax.set_yticks(y_minor_ticks, minor=True)

# Configuring the plot
plt.plot(x, y)
plt.title('%s\nOutside temperature Basis Lager' %today)
plt.grid(which='major', axis='y', c='black', linewidth='0.2')
plt.xlabel('Time of the day')
plt.xticks(rotation=90)
plt.setp(ax.get_xticklabels()[::2], visible=False)
plt.ylabel('Temperature in degree Celsius')

# Adjust the window size
mng = plt.get_current_fig_manager()
# For Linux system
mng.resize(*mng.window.maxsize())
# For Windows
# mng.window.state('zoomed')


plt.show()
