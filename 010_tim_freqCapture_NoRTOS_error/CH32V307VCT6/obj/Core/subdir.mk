################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imafcxw -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myDriver" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myApp\ui" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myDriver\Tim" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myDriver\RTC" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myDriver\Adc" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myApp" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myDriver\LCD" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myDriver\Gpio" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myDriver\Key" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myDriver\System" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\Debug" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\myApp\scheduler" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\Core" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\User" -I"C:\window_apps\desktop\GithubDesktop\ch32v307vct6_demo\010_tim_freqCapture_NoRTOS_error\CH32V307VCT6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

