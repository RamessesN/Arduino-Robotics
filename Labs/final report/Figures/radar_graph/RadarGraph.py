import numpy as np
import matplotlib.pyplot as plt

labels = ['Report', 'Experiment', 'Code', '3D Modeling']
num_vars = len(labels)
values = [40, 50, 40, 90]

angles = np.linspace(0, 2 * np.pi, num_vars, endpoint=False).tolist()
angles += angles[:1]

values += values[:1]

fig, ax = plt.subplots(figsize=(6, 6), subplot_kw=dict(polar=True))
ax.plot(angles, values, color='red', linewidth=2)
ax.fill(angles, values, color='red', alpha=0.25)

ax.set_thetagrids(np.degrees(angles[:-1]), labels)

ax.set_title("Haohao QI", fontsize=16, fontweight='bold')
ax.set_ylim(0, 100)

plt.savefig("./contribution_haohao.png", dpi=300)

plt.show()