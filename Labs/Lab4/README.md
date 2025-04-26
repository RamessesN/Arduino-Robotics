<div align="center">
  <h1>Lab4 - Line Tracking</h1>
</div>

## 1. ADC 值随 IR 距离变化时的 "value - distance" 曲线

### 实验过程: 
1. 检测 IR 距离白纸每 0.5cm 其 ADC 值的变化，从 0.5 ~ 5cm 共 10 组数据。
2. 实验结果如下:
> From Stanley
>> [ 33, 37, 42, 48, 59, 65, 294, 560, 765, 895 ]
> 
> From Yilin
>> [ 34, 38, 43, 49, 54, 70, 275, 465, 680, 800 ]
> 
> From Chloe
>> [ 33, 38, 42, 48, 58, 86, 315, 510, 648, 846 ]

3. 绘制图像如下:
<p align="center">
  <img src="./Photos/lab4_graph.png" alt="lab4_graph" height="200">
</p>

## 2. IR 检测到不同形式 line 的 7 种状态
### 实验过程: 
1. 检测 IR 在 7 种情况下得到的不同结果。
2. 实验结果如下:
<p align="center">
  ***000***
  <br>
  <img src="./Photos/actual/000.jpg" alt="000" height="180">
  <img src="./Photos/data/000.png" alt="000" height="180">
  <br>
  ***001***
  <br>
  <img src="./Photos/actual/001.jpg" alt="001" height="180">
  <img src="./Photos/data/001.png" alt="001" height="180">
  <br>
  ***010***
  <br>
  <img src="./Photos/actual/010.jpg" alt="010" height="180">
  <img src="./Photos/data/010.png" alt="010" height="180">
  <br>
  ***011***
  <br>
  <img src="./Photos/actual/011.jpg" alt="011" height="180">
  <img src="./Photos/data/011.png" alt="011" height="180">
  <br>
  ***100***
  <br>
  <img src="./Photos/actual/100.jpg" alt="100" height="180">
  <img src="./Photos/data/100.png" alt="100" height="180">
  <br>
  ***110***
  <br>
  <img src="./Photos/actual/110.jpg" alt="110" height="180">
  <img src="./Photos/data/110.png" alt="110" height="180">
  <br>
  ***111***
  <br>
  <img src="./Photos/actual/111.jpg" alt="111" height="180">
  <img src="./Photos/data/111.png" alt="111" height="180">
  <br>
</p>