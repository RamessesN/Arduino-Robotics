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
... (From Arduino IDE)
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