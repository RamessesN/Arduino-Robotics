import numpy as np
import mlx.core as mx
import matplotlib.pyplot as plt

def graphGenerate():
    altitude = [
        0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0
    ]

    sensor_stanley = [
        33, 37, 42, 48, 59, 65, 294, 560, 765, 895
    ]

    sensor_yilin = [
        34, 38, 43, 49, 54, 70, 275, 465, 680, 800
    ]

    sensor_chloe = [
        33, 38, 42, 48, 58, 86, 315, 510, 648, 846
    ]

    sensor_average = [
        (s + y + c) / 3 for s, y, c in zip(sensor_stanley, sensor_yilin, sensor_chloe)
    ]

    sensorValue = mx.array(sensor_average)
    altitudeValue = mx.array(altitude)

    poly_degree = 5
    poly_coeffs = np.polyfit(altitudeValue, sensorValue, poly_degree)
    poly_func = np.poly1d(poly_coeffs)

    altitude_dense = mx.linspace(0, 5, 600)
    sensor_dense = poly_func(altitude_dense)

    plt.figure(figsize=(10, 6))
    plt.plot(altitudeValue, sensorValue, 'ro', label='Original Data')
    plt.plot(altitude_dense, sensor_dense, 'b-', label=f"Fitting Curve (Degree-{poly_degree})")

    plt.xlim(left=0.4)

    plt.xlabel("Altitude / cm")
    plt.ylabel("Sensor Value")
    plt.title('Altitude - Sensor Value')
    plt.grid(True)
    plt.legend()

    plt.savefig("./Photos/lab4_graph.png", dpi = 1200)
    plt.show()

if __name__ == '__main__':
    graphGenerate()