################################################################################
# MRS Version: 1.9.2
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../myDriver/System/systick.c 

OBJS += \
./myDriver/System/systick.o 

C_DEPS += \
./myDriver/System/systick.d 


# Each subdirectory must supply rules for building sources it contributes
myDriver/System/%.o: ../myDriver/System/%.c
	@	@	riscv-none-embed-gcc -march=rv32imafcxw -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myDriver" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myApp\ui" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myDriver\Tim" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myDriver\Adc" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myApp" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myDriver\LCD" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myDriver\Gpio" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myDriver\Key" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myDriver\System" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\Debug" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\myApp\scheduler" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\Core" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\User" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\011_adc_Waveform_NoRTOS\CH32V307VCT6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
