################################################################################
# MRS Version: 1.9.2
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\myDriver" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\myDriver\LCD" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\myDriver\Gpio" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\myDriver\Key" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\myDriver\Oled" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\myDriver\System" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\Debug" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\myApp\scheduler" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\Core" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\User" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\005_t_NoRTOS\CH32V307VCT6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
