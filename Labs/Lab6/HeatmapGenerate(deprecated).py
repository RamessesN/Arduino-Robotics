import pandas as pd
import mlx.core as mx
import matplotlib.pyplot as plt

file_paths = [f"./DataAverage/{i}cm_average_data.xlsx" for i in range(0, 401, 40)]

distance_steps = mx.arange(0, 400, 40)
angle_steps = mx.arange(45, 136)
data_matrix = mx.zeros((len(distance_steps), len(angle_steps)))

for idx, file_path in enumerate(file_paths):
    df = pd.read_excel(file_path)
    for _, row in df.iterrows():
        angle = int(row["Angle"])
        distance = row["Distance / cm"]
        if 45 <= angle <= 135:
            angle_idx = angle - 45
            data_matrix[idx, angle_idx] = distance

angles = mx.degrees(angle_steps)
distances = distance_steps
theta, r = mx.meshgrid(angles, distances)

fig, ax = plt.subplots(subplot_kw={'projection': 'polar'}, figsize=(8, 8))
cmap = plt.cm.Oranges
heatmap = ax.pcolor(theta, r, data_matrix, cmap=cmap, shading='auto')

cbar = plt.colorbar(
    heatmap,
    ax=ax,
    orientation='vertical',
    pad=0.1,
    shrink=0.6
)
cbar.set_label("Distance / cm", fontsize=12)

ax.set_title("Heatmap of \"Angle - Distance\"", va="bottom", fontsize=14)
ax.set_thetamin(45)
ax.set_thetamax(135)
ax.set_rticks(distance_steps)
ax.set_rlabel_position(90)

plt.savefig("./Photos/heatmap.png", dpi=1200)
plt.show()