import mlx.core as mx
import matplotlib.pyplot as plt

fig, ax = plt.subplots(subplot_kw={'projection': 'polar'}, figsize=(8, 8))

theta_min = mx.degrees(45)
theta_max = mx.degrees(135)
theta = mx.linspace(theta_min, theta_max, 91)

radii = mx.arange(0, 41, 10)

ax.set_rticks(radii)
ax.set_rlabel_position(90)

ax.set_thetamin(45)
ax.set_thetamax(135)

ax.grid(True)
ax.set_title("Angle - Distance", va="bottom")

plt.savefig("./Photos/ang&dis_graph.png", dpi=1200)
plt.show()