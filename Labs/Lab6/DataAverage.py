import pandas as pd

file_paths = [
    "./DataProcessing/400cm/400cm_data_01.xlsx",
    "./DataProcessing/400cm/400cm_data_02.xlsx",
    "./DataProcessing/400cm/400cm_data_03.xlsx"
]

data_frames = [pd.read_excel(file) for file in file_paths]

combined_data = pd.concat(data_frames)
average_data = combined_data.groupby(combined_data.index).mean()

average_data = average_data.round(2)

output_file = "./DataAverage/400cm_average_data.xlsx"
average_data.to_excel(output_file, index=False)