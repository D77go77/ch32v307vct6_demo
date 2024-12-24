################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../myApp/sensor/Fusion/FusionAhrs.c \
../myApp/sensor/Fusion/FusionCompass.c \
../myApp/sensor/Fusion/FusionOffset.c \
../myApp/sensor/Fusion/filter.c \
../myApp/sensor/Fusion/wp_math.c 

OBJS += \
./myApp/sensor/Fusion/FusionAhrs.o \
./myApp/sensor/Fusion/FusionCompass.o \
./myApp/sensor/Fusion/FusionOffset.o \
./myApp/sensor/Fusion/filter.o \
./myApp/sensor/Fusion/wp_math.o 

C_DEPS += \
./myApp/sensor/Fusion/FusionAhrs.d \
./myApp/sensor/Fusion/FusionCompass.d \
./myApp/sensor/Fusion/FusionOffset.d \
./myApp/sensor/Fusion/filter.d \
./myApp/sensor/Fusion/wp_math.d 


# Each subdirectory must supply rules for building sources it contributes
myApp/sensor/Fusion/%.o: ../myApp/sensor/Fusion/%.c
	@	@	riscv-none-embed-gcc -march=rv32imafcxw -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myDriver" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myDriver\Adc" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myApp" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myApp\sensor" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myApp\sensor\Fusion" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myDriver\Mpu6050" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myDriver\LCD" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myDriver\Gpio" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myDriver\Key" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myDriver\Oled" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myDriver\System" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\Debug" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\myApp\scheduler" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\Core" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\User" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\007_adc_dma_NoRTOS\CH32V307VCT6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

