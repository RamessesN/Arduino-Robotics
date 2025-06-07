import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

x1 = np.linspace(-100, 100, 500)
y1 = x1

x2 = np.linspace(-4.15, 0, 500)
y2 = -x2

x3 = np.linspace(-4.15, 0, 500)
y3 = x3 + 4.15

x4 = np.linspace(0, 4.15, 500)
y4 = -x4 + 4.15

x5 = np.linspace(4.15, 8.3, 500)
y5 = -x5 + 8.3

x7 = np.linspace(-8.3, -4.15, 500)
y7 = x7 + 8.3

ax.plot(x1, y1, color='blue')
ax.plot(x2, y2, color='blue', linestyle='--')
ax.plot(x3, y3, color='green', linestyle='--')
ax.plot(x4, y4, color='green', linestyle='--')
ax.plot(x5, y5, color='red', linestyle='--')
ax.plot(x7, y7, color='red', linestyle = '--')

ax.spines['left'].set_position('zero')
ax.spines['bottom'].set_position('zero')
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.yaxis.set_ticks_position('left')

ax.text(8.5, 0.2, 'Distance', fontsize=12, ha='left', va='bottom')
ax.text(0.2, 5.5, 'Voltage / V', fontsize=12, ha='left', va='top')
ax.text(6, 5, '=> Linear Line', fontsize=12, ha='left', va='top')

plt.xlim(-10, 10)
plt.ylim(-6, 6)

plt.grid(True)
plt.title('Voltage - Distance')

plt.savefig("./graphGene/Figure_2.3.png", dpi=300)

plt.show()