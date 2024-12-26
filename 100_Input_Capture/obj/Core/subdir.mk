################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/01_my_document/desktop/01_contest_about/06_jlc_version/05_ch32/EVT/EXAM/SRC/Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/core_riscv.o: D:/01_my_document/desktop/01_contest_about/06_jlc_version/05_ch32/EVT/EXAM/SRC/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\EVT\EXAM\SRC\Debug" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\EVT\EXAM\SRC\Core" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\EVT\EXAM\TIM\Input_Capture\User" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

