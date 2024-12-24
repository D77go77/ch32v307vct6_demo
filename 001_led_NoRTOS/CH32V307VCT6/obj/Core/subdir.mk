################################################################################
# MRS Version: 1.9.2
# �Զ����ɵ��ļ�����Ҫ�༭��
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
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\001_led\CH32V307VCT6\Debug" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\001_led\CH32V307VCT6\Core" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\001_led\CH32V307VCT6\User" -I"D:\01_my_document\desktop\01_contest_about\06_jlc_version\05_ch32\Code\001_led\CH32V307VCT6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
