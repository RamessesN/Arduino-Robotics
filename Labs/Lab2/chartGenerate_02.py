import numpy as np
import mlx.core as mx
import matplotlib.pyplot as plt

speed =  [
    136, 136, 134, 135, 135, 135, 137, 144, 153, 155, 160, 163, 166, 169, 174,
    176, 179, 182, 183, 184, 185, 187, 188, 190, 191, 193, 194, 196, 197, 196,
    196, 198, 198, 200, 200, 202, 202, 203, 202, 205, 206, 206, 209, 208, 209,
    211, 216, 216, 214, 213, 216, 214, 216
]
pot_lin = [
    527, 527, 524, 525, 525, 524, 532, 564, 597, 611, 629, 635, 641, 651, 669,
    671, 691, 699, 693, 707, 715, 723, 720, 735, 743, 748, 748, 751, 767, 760,
    770, 778, 787, 782, 801, 802, 805, 808, 813, 822, 816, 825, 823, 844, 847,
    851, 862, 866, 868, 865, 863, 861, 856
]

speed = mx.array(speed)
pot_lin = mx.array(pot_lin)

poly_degree = 6
poly_coeffs = np.polyfit(speed, pot_lin, poly_degree)
poly_func = np.poly1d(poly_coeffs)

speed_dense = mx.linspace(speed.min(), speed.max(), 300)
pot_lin_dense = poly_func(speed_dense)

plt.figure(figsize=(10, 6))
plt.plot(speed, pot_lin, 'ro', label='Original Data')
plt.plot(speed_dense, pot_lin_dense, 'b-', label=f"Fitting Curve (Degree-{poly_degree})")

plt.xlabel("Speed")
plt.ylabel(r"POT-LIN / $\Omega$")
plt.title('Speed - POT-LIN (4/4 PWM)')
plt.grid(True)
plt.legend()

plt.savefig("./Photos/Chart/424_MOTOR_CLOCKWISE.png", dpi=1200)

plt.show()