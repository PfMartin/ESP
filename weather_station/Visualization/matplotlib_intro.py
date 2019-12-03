import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2, 200) #Range from 0 to 2 and 200 ticks
y = np.random.randint(11, size=200) #Random array with values from 0 to 10 and 200 
    
plt.plot(x, y, label = 'linear')

plt.xlabel('t - time')
plt.ylabel('T - temperature')

plt.title('Temperature over time')

plt.legend()

plt.show()
