import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

file_name = "./DataAverage/280cm_average_data.xlsx"

df = pd.read_excel(file_name)
angles = df["Angle"].values
distances = df["Distance / cm"].values

valid_indices = distances > 0
angles = angles[valid_indices]
distances = distances[valid_indices]

theta = np.deg2rad(angles)

fig, ax = plt.subplots(subplot_kw={'projection': 'polar'}, figsize=(8, 8))

cmap = plt.cm.YlOrRd
vmin = 0
vmax = max(distances)
norm = plt.Normalize(vmin=vmin, vmax=vmax)
colors = cmap(norm(distances))

for i in range(len(theta)):
    ax.bar(
        theta[i],
        distances[i],
        width=np.deg2rad(1),
        color=colors[i],
        edgecolor="none",
        alpha=1.0
    )

sm = plt.cm.ScalarMappable(cmap=cmap, norm=norm)
sm.set_array([])

ax.set_title("280cm", va="bottom", fontsize=14)
ax.set_thetamin(45)
ax.set_thetamax(135)
ax.set_theta_zero_location("E")

plt.savefig("./Photos/angle-distance/280cm.png", dpi=1200)
plt.show()