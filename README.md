
# CH32V307VCT6 示例项目合集

本仓库包含多个基于 CH32V307VCT6 微控制器的示例项目，旨在帮助开发者熟悉该芯片的功能和开发流程。

## 目录

- [001_led_NoRTOS](./001_led_NoRTOS/CH32V307VCT6): LED 闪烁示例，演示如何使用 GPIO 控制 LED。
- [002_gpio_NoRTOS](./002_gpio_NoRTOS/CH32V307VCT6): GPIO 输入输出示例，展示如何配置和读取 GPIO 状态。
- [003_key_NoRTOS](./003_key_NoRTOS/CH32V307VCT6): 按键输入示例，演示如何检测按键按下和释放事件。
- [004_oled_iic_sw_NoRTOS](./004_oled_iic_sw_NoRTOS/CH32V307VCT6): 使用软件 I2C 驱动 OLED 显示屏的示例。
- [005_lcd_spi_hw_NoRTOS](./005_lcd_spi_hw_NoRTOS/CH32V307VCT6): 使用硬件 SPI 接口驱动 LCD 显示屏的示例。
- [006_mpu6050_ahrs_NoRTOS](./006_mpu6050_ahrs_NoRTOS/CH32V307VCT6): 使用 MPU6050 传感器进行姿态解算的示例。
- [007_adc_dma_NoRTOS](./007_adc_dma_NoRTOS/CH32V307VCT6): 使用 ADC 和 DMA 进行模拟信号采集的示例。
- [008_lcdsprintf_spi_hw_NoRTOS](./008_lcdsprintf_spi_hw_NoRTOS/CH32V307VCT6): 使用 sprintf 函数格式化字符串并通过 SPI 显示在 LCD 上的示例。
- [009_rtc_ui_NoRTOS](./009_rtc_ui_NoRTOS/CH32V307VCT6): 实时时钟（RTC）和用户界面示例，展示如何设置和读取时间。
- [010_tim_freqCapture_NoRTOS_error](./010_tim_freqCapture_NoRTOS_error/CH32V307VCT6): 频率捕获示例，演示如何使用定时器捕获输入信号的频率。
- [011_adc_Waveform_NoRTOS](./011_adc_Waveform_NoRTOS/CH32V307VCT6): 使用 ADC 采集波形并进行显示的示例。

## 快速开始

1. **环境准备**:
   - 确保已安装 [MounRiver Studio](https://mounriver.com/) 开发环境。
   - 获取并安装 CH32V307VCT6 的相关驱动和库文件。

2. **克隆仓库**:
   ```bash
   git clone https://github.com/D77go77/ch32v307vct6_demo.git
   ```

3. **打开项目**:
   - 在 MounRiver Studio 中，选择“文件”->“打开项目”，导航到克隆的仓库目录，选择相应的示例项目文件夹。

4. **编译和下载**:
   - 在 MounRiver Studio 中，点击“构建”按钮进行编译。
   - 确保开发板已连接至电脑，点击“下载”按钮将程序烧录到开发板。

5. **运行和调试**:
   - 在开发板上运行程序，使用串口调试助手或其他工具观察输出结果。

## 资源

- [CH32V307 官方资料](https://github.com/openwch/ch32v307): 包含 SDK、HDK、数据手册等开发资料。
- [CH32V307 数据手册](https://github.com/openwch/ch32v307/blob/main/README_zh.md): 提供芯片的详细规格和功能描述。
- [MounRiver Studio 官方网站](https://mounriver.com/): 提供开发环境的下载和使用指南。

## 许可证

本项目基于 GPL-3.0 许可证进行分发。有关详细信息，请参阅 [LICENSE](./LICENSE) 文件。
