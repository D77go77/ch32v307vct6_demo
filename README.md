
# CH32V307VCT6 示例项目合集

本仓库包含多个基于 CH32V307VCT6 微控制器的示例项目和演示代码。每个项目展示了不同的功能和硬件特性，旨在帮助开发者快速上手开发。

---

## 示例项目说明

### **1. 001_led_NoRTOS**
- **功能**: 
  - 控制 LED 的点亮与闪烁。
- **技术点**:
  - 初始化 GPIO，控制 LED。
  - 使用任务调度器管理任务。
  - 串口打印系统信息（时钟、芯片 ID 等）。

### **2. 002_gpio_NoRTOS**
- **功能**:
  - 控制 GPIO 引脚，驱动 LED 和蜂鸣器。
- **技术点**:
  - 初始化 GPIO 并控制外设。
  - 系统定时器（SYSTICK）中断的使用。
  - 使用简单的调度器运行 GPIO 控制任务。

### **3. 003_key_NoRTOS**
- **功能**:
  - 检测按键输入，触发相应的动作（如 LED 闪烁）。
- **技术点**:
  - GPIO 初始化。
  - 按键状态检测与去抖动逻辑。
  - 利用调度器处理按键任务。

### **4. 004_oled_iic_sw_NoRTOS**
- **功能**:
  - 使用软件 I2C 驱动 OLED 显示屏，实现文字和图形的显示。
- **技术点**:
  - 软件 I2C 通信协议的实现。
  - OLED 初始化与数据更新。
  - 调度器管理显示任务。

### **5. 005_lcd_spi_hw_NoRTOS**
- **功能**:
  - 通过硬件 SPI 初始化和驱动 LCD 显示屏。
- **技术点**:
  - SPI 硬件接口的使用。
  - LCD 显示内容更新逻辑。
  - 使用调度器管理显示任务。

### **6. 006_mpu6050_ahrs_NoRTOS**
- **功能**:
  - 读取 MPU6050 加速度计和陀螺仪数据。
  - 实现简单的姿态解算系统（AHRS）。
- **技术点**:
  - I2C 读取 MPU6050 数据（加速度、角速度）。
  - 姿态解算算法基础。
  - 输出结果到 LCD 或串口。

### **7. 007_adc_dma_NoRTOS**
- **功能**:
  - 使用 ADC 和 DMA 采集模拟信号数据。
- **技术点**:
  - 配置 ADC 和 DMA，确保高效数据传输。
  - 使用任务调度器处理采集数据。
  - 可通过串口输出采集到的数据。
  - 
### **8. 008_lcdsprintf_spi_hw_NoRTOS**
- **功能**:
  - lcd函数重构，使用sprintf字符串
- **技术点**:
  - 方便使用，行数显示。

---

## 项目目录结构

```
CH32V307VCT6_demo/
│
├── 001_led_NoRTOS/                  # LED 示例项目
├── 002_gpio_NoRTOS/                 # GPIO 示例项目
├── 003_key_NoRTOS/                  # 按键输入示例项目
├── 004_oled_iic_sw_NoRTOS/          # OLED 软件I2C 示例项目
├── 005_lcd_spi_hw_NoRTOS/           # LCD 硬件SPI 示例项目
├── 006_mpu6050_ahrs_NoRTOS/         # MPU6050 姿态解算示例项目
├── 007_adc_dma_NoRTOS/              # ADC + DMA 示例项目
├── 008_lcdsprintf_spi_hw/           # lcd 显示函数更新示例项目
├── LICENSE                          # 开源许可
└── README.md                        # 本说明文件
```

---

## 快速开始

### 环境要求
- CH32V307VCT6 开发板
- 工具链（如 GCC for RISC-V 或 WCH 官方工具链/IDE）
- 调试器（如 J-Link 或 WCH-Link）

### 编译与运行
1. 克隆仓库：
   ```bash
   git clone https://github.com/D77go77/ch32v307vct6_demo.git
   ```
2. 进入对应的项目目录（如 `001_led_NoRTOS` 或 `002_gpio_NoRTOS`）。
3. 使用工具链编译并烧录程序到开发板。

### 示例测试
根据每个示例项目的功能，运行后可测试以下功能：
- **LED 点亮与闪烁（001_led_NoRTOS）**
- **GPIO 控制 LED 和蜂鸣器（002_gpio_NoRTOS）**
- **按键输入检测（003_key_NoRTOS）**
- **OLED 图像/文字显示（004_oled_iic_sw_NoRTOS）**
- **LCD 快速内容更新（005_lcd_spi_hw_NoRTOS）**
- **MPU6050 数据读取与姿态解算（006_mpu6050_ahrs_NoRTOS）**
- **ADC 数据采集（007_adc_dma_NoRTOS）**

---

## 许可证

本仓库基于 [GPLv3 许可证](LICENSE) 发布。

## 贡献

欢迎 Fork 本仓库并提交 Pull Request，贡献新的示例代码或改进功能。

---

本项目旨在为 CH32V307VCT6 的开发者提供基础示例，后续将扩展更多功能演示。
```
