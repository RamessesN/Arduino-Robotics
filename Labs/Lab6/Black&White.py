import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

file_paths = [f"./DataRestoration/{i}cm_0&1_data.xlsx" for i in range(0, 401, 40)]

distance_steps = np.arange(0, 401, 40)
angle_steps = np.arange(45, 136)
data_matrix = np.zeros((len(distance_steps), len(angle_steps)))

for idx, file_path in enumerate(file_paths):
    df = pd.read_excel(file_path)
    for _, row in df.iterrows():
        angle = int(row["Angle"])
        distance = row["Distance / cm"]
        if 45 <= angle <= 135:
            angle_idx = angle - 45
            data_matrix[idx, angle_idx] = distance

binary_matrix = np.where(data_matrix > 0, 1, 0)

angles = np.deg2rad(angle_steps)
distances = distance_steps
theta, r = np.meshgrid(angles, distances)

fig, ax = plt.subplots(subplot_kw={'projection': 'polar'}, figsize=(8, 8))

cmap = plt.cm.binary

heatmap = ax.pcolormesh(theta, r, binary_matrix, cmap=cmap, shading='auto')

ax.set_title("Radar Graph")

ax.set_thetamin(45)
ax.set_thetamax(135)
ax.set_rticks(distance_steps)
ax.set_rlabel_position(90)

plt.savefig("./Photos/RadarGraph.png", dpi=1200)
plt.show()