# CH32V307VCT6 示例项目

本仓库包含多个基于 CH32V307VCT6 微控制器的示例项目和演示代码。每个文件夹分别展示了该微控制器的特定功能和硬件特性。

## 仓库结构

- **001_led_NoRTOS**: 无RTOS的LED控制示例。
- **002_gpio_NoRTOS**: 无RTOS的GPIO示例，可控制LED和蜂鸣器。
- **003_key_NoRTOS**: 无RTOS的按键输入处理示例。
- **004_oled_iic_sw_NoRTOS**: 使用软件I2C控制OLED显示屏的示例（无RTOS）。
- **005_lcd_spi_hw_NoRTOS**: 使用硬件SPI控制LCD显示屏的示例（无RTOS）。
- **006_mpu6050_ahrs_NoRTOS**: 处理MPU6050传感器数据并实现姿态解算系统（AHRS）的示例（无RTOS）。
- **007_adc_dma_NoRTOS**: 使用DMA进行ADC数据采集的示例（无RTOS）。

## 功能介绍

1. **LED 控制**:
   - 演示如何通过简单的GPIO配置实现LED闪烁和控制。

2. **GPIO 应用**:
   - 展示如何通过GPIO控制外设，例如LED和蜂鸣器。

3. **按键输入处理**:
   - 说明如何处理按键输入并实现按键去抖动功能。

4. **OLED I2C 控制**:
   - 提供使用软件I2C控制OLED显示屏的示例代码。

5. **LCD SPI 控制**:
   - 演示如何通过硬件SPI高效通信并控制LCD显示屏。

6. **MPU6050 姿态解算系统**:
   - 示例代码展示如何读取MPU6050数据并实现姿态解算算法（AHRS）。

7. **ADC + DMA**:
   - 说明如何配置DMA高效采集ADC数据。

## 快速开始

### 依赖要求

- CH32V307VCT6 开发板
- CH32V307 工具链（例如 GCC for RISC-V 或 WCH 官方工具链/IDE）
- 调试器（例如 J-Link 或 WCH-Link）

### 安装步骤

1. 克隆本仓库：
   ```bash
   git clone https://github.com/D77go77/ch32v307vct6_demo.git
