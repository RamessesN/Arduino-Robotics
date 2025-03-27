import numpy as np
import mlx.core as mx
import matplotlib.pyplot as plt

speed =  [
    31, 31, 31, 31, 31, 33, 34, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
    47, 47, 48, 49, 50, 50, 51, 51, 52, 53, 53, 54, 54, 55, 55, 54, 54, 54
]
pot_lin = [
    450, 462, 474, 490, 508, 531, 559, 580, 602, 614, 630, 646, 665, 684, 698,
    715, 724, 736, 750, 762, 775, 785, 797, 806, 816, 825, 836, 844, 853, 861,
    870, 875, 876, 861, 863, 870
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

plt.xlabel("Speed / (rad / s)")
plt.ylabel(r"POT-LIN / $\Omega$")
plt.title('Speed - POT-LIN (1/4 PWM)')
plt.grid(True)
plt.legend()

plt.savefig("./Photos/Chart/124_MOTOR_CLOCKWISE.png", dpi=1200)

plt.show()