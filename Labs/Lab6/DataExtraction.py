import pandas as pd

data_text = """
Angle: 135°; Distance: 218.58 cm
Angle: 134°; Distance: 274.31 cm
Angle: 133°; Distance: 0.00 cm
Angle: 132°; Distance: 0.00 cm
Angle: 131°; Distance: 188.98 cm
Angle: 130°; Distance: 248.95 cm
Angle: 129°; Distance: 309.20 cm
Angle: 128°; Distance: 42.93 cm
Angle: 127°; Distance: 117.10 cm
Angle: 126°; Distance: 179.23 cm
Angle: 125°; Distance: 236.17 cm
Angle: 124°; Distance: 299.51 cm
Angle: 123°; Distance: 357.11 cm
Angle: 122°; Distance: 85.48 cm
Angle: 121°; Distance: 161.19 cm
Angle: 120°; Distance: 220.33 cm
Angle: 119°; Distance: 280.51 cm
Angle: 118°; Distance: 336.40 cm
Angle: 117°; Distance: 63.27 cm
Angle: 116°; Distance: 138.78 cm
Angle: 115°; Distance: 207.50 cm
Angle: 114°; Distance: 265.57 cm
Angle: 113°; Distance: 329.91 cm
Angle: 112°; Distance: 57.25 cm
Angle: 111°; Distance: 126.04 cm
Angle: 110°; Distance: 179.61 cm
Angle: 109°; Distance: 255.90 cm
Angle: 108°; Distance: 307.29 cm
Angle: 107°; Distance: 0.00 cm
Angle: 106°; Distance: 0.00 cm
Angle: 105°; Distance: 219.49 cm
Angle: 104°; Distance: 288.14 cm
Angle: 103°; Distance: 338.66 cm
Angle: 102°; Distance: 69.89 cm
Angle: 101°; Distance: 142.47 cm
Angle: 100°; Distance: 200.50 cm
Angle: 99°; Distance: 268.19 cm
Angle: 98°; Distance: 348.21 cm
Angle: 97°; Distance: 358.93 cm
Angle: 96°; Distance: 163.18 cm
Angle: 95°; Distance: 243.96 cm
Angle: 94°; Distance: 323.93 cm
Angle: 93°; Distance: 65.22 cm
Angle: 92°; Distance: 150.85 cm
Angle: 91°; Distance: 239.12 cm
Angle: 90°; Distance: 317.81 cm
Angle: 89°; Distance: 55.74 cm
Angle: 88°; Distance: 152.36 cm
Angle: 87°; Distance: 56.66 cm
Angle: 86°; Distance: 65.03 cm
Angle: 85°; Distance: 56.99 cm
Angle: 84°; Distance: 65.03 cm
Angle: 83°; Distance: 56.53 cm
Angle: 82°; Distance: 69.47 cm
Angle: 81°; Distance: 0.00 cm
Angle: 80°; Distance: 0.00 cm
Angle: 79°; Distance: 0.00 cm
Angle: 78°; Distance: 0.00 cm
Angle: 77°; Distance: 0.00 cm
Angle: 76°; Distance: 0.00 cm
Angle: 75°; Distance: 0.00 cm
Angle: 74°; Distance: 0.00 cm
Angle: 73°; Distance: 0.00 cm
Angle: 72°; Distance: 0.00 cm
Angle: 71°; Distance: 0.00 cm
Angle: 70°; Distance: 0.00 cm
Angle: 69°; Distance: 0.00 cm
Angle: 68°; Distance: 0.00 cm
Angle: 67°; Distance: 0.00 cm
Angle: 66°; Distance: 0.00 cm
Angle: 65°; Distance: 0.00 cm
Angle: 64°; Distance: 0.00 cm
Angle: 63°; Distance: 0.00 cm
Angle: 62°; Distance: 66.78 cm
Angle: 61°; Distance: 56.65 cm
Angle: 60°; Distance: 65.36 cm
Angle: 59°; Distance: 64.43 cm
Angle: 58°; Distance: 63.90 cm
Angle: 57°; Distance: 59.25 cm
Angle: 56°; Distance: 56.78 cm
Angle: 55°; Distance: 57.21 cm
Angle: 54°; Distance: 15.80 cm
Angle: 53°; Distance: 56.78 cm
Angle: 52°; Distance: 196.09 cm
Angle: 51°; Distance: 287.76 cm
Angle: 50°; Distance: 56.80 cm
Angle: 49°; Distance: 115.88 cm
Angle: 48°; Distance: 197.79 cm
Angle: 47°; Distance: 275.62 cm
Angle: 46°; Distance: 0.00 cm
Angle: 45°; Distance: 0.00 cm
"""

data_lines = data_text.strip().split("\n")
extracted_data = []

for line in data_lines:
    parts = line.split(";")
    angle_part = parts[0].strip()
    distance_part = parts[1].strip()

    angle = int(angle_part.split(":")[1].strip().replace("°", ""))
    distance = float(distance_part.split(":")[1].strip().replace("cm", "").strip())

    extracted_data.append({"Angle": angle, "Distance / cm": distance})

df = pd.DataFrame(extracted_data)

df.to_excel("./DataProcessing/360cm/360cm_data_03.xlsx", index=False)