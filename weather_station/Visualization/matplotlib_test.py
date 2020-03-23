import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(1, 100, 100)
y = np.random.randint(0, 10, 100) 

print(type(y))

plt.plot(x, y)
plt.show()