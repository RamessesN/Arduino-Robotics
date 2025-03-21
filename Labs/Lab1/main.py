import numpy as np
import mlx.core as mx
import matplotlib.pyplot as plt

R_Fixed = 270.0
Vref = 5.0

adc_values_01 = np.array([
    1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
    892, 880, 887, 788, 796, 716, 723, 731, 717, 680, 678, 600, 656, 619, 560,
    541, 508, 480, 456, 437, 399, 395, 380, 365, 370, 368
])[::-1]

Vout = adc_values_01 / 1023.0 * Vref

R_LDR = R_Fixed * ((Vref - Vout) / Vout)

x_values = mx.arange(stop=len(adc_values_01))

poly_degree = 6
poly_coeffs_01 = np.polyfit(x_values, R_LDR, poly_degree)
poly_func_01 = np.poly1d(poly_coeffs_01)

x_dense = mx.linspace(start=x_values.min(), stop=x_values.max(), num=300)
y_dense = poly_func_01(x_dense)

plt.figure(figsize=(8, 5))
plt.plot(x_values, R_LDR, 'ro', label="LDR1 data")
plt.plot(x_dense, y_dense, 'b-', label=f"Fitting Curve (Degree-{poly_degree})")

plt.xlabel("Light Intensity / cd")
plt.ylabel(r"Resistance / $\Omega$")
plt.title("VCC_270_LDR")
plt.grid(True)
plt.legend()

plt.savefig("./Photos/Chart/VCC_270_LDR.png", dpi=1200)

plt.show()