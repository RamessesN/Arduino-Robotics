import numpy as np
import mlx.core as mx
import matplotlib.pyplot as plt

R1 = 1000.0
Vref = 5.0

adc_values_01 = np.array([
    1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
    1023, 1023, 1023, 1023, 892, 880, 887, 788, 796, 716,
    723, 731, 717, 680, 678, 600, 656, 619, 560, 541, 508,
    480, 456, 437, 399, 432, 492, 524, 831, 1023
])

voltage_values = adc_values_01 / 1023.0 * Vref

resistance_values = R1 * ((Vref - voltage_values) / voltage_values)

x_values = mx.arange(stop=len(adc_values_01))

poly_degree = 6
poly_coeffs = np.polyfit(x_values, resistance_values, poly_degree)
poly_func = np.poly1d(poly_coeffs)

x_dense = mx.linspace(start=x_values.min(), stop=x_values.max(), num=300)
y_dense = poly_func(x_dense)

plt.figure(figsize=(8, 5))
plt.plot(x_values, resistance_values, 'ro', label="Original Data")
plt.plot(x_dense, y_dense, 'b-', label=f"Polynomial Fit (Degree {poly_degree})")

plt.xlabel("Light Intensity")
plt.ylabel("Resistance")
plt.title("LDR Sensor Resistance Readings")
plt.grid(True)
plt.legend()

plt.savefig("./Photos/Chart/VCC_LDR_01.png", dpi=1200)

plt.show()