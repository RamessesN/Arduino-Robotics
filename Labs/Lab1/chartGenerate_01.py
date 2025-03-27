import numpy as np
import mlx.core as mx
import matplotlib.pyplot as plt

R_Fixed = 1000.0
Vref = 5.0

adc_values_01 = np.array([
    172, 178, 181, 184, 277, 591, 585, 559, 550, 552, 757, 762, 768, 853,
    853, 845, 846, 902, 897, 892, 885, 909, 911, 913, 914, 915, 913, 913,
    916, 922, 956, 972, 982, 989, 1005, 1007, 1023, 1023, 1023, 1023
])

Vout = adc_values_01 / 1023.0 * Vref

R_LDR = R_Fixed * ((Vref - Vout) / Vout)

x_values = mx.arange(stop=len(adc_values_01))

poly_degree = 6
poly_coeffs_01 = np.polyfit(x_values, R_LDR, poly_degree)
poly_func_01 = np.poly1d(poly_coeffs_01)

x_dense = mx.linspace(start=x_values.min(), stop=x_values.max(), num=300)
y_dense = poly_func_01(x_dense)

plt.figure(figsize=(8, 5))
plt.plot(x_values, R_LDR, 'ro', label="LDR2 data")
plt.plot(x_dense, y_dense, 'b-', label=f"Fitting Curve (Degree-{poly_degree})")
plt.plot(x_values, adc_values_01, 'go', label="ADC data")

plt.xlabel("Light Intensity / cd")
plt.ylabel(r"Resistance / $\Omega$")
plt.title("VCC_LDR_02")
plt.grid(True)
plt.legend()

plt.savefig("./Photos/Chart/VCC_LDR_02.png", dpi=1200)

plt.show()