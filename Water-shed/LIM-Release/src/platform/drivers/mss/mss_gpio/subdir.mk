################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/platform/drivers/mss/mss_gpio/mss_gpio.c 

OBJS += \
./src/platform/drivers/mss/mss_gpio/mss_gpio.o 

C_DEPS += \
./src/platform/drivers/mss/mss_gpio/mss_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
src/platform/drivers/mss/mss_gpio/%.o: ../src/platform/drivers/mss/mss_gpio/%.c src/platform/drivers/mss/mss_gpio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv64gc -mabi=lp64d -mcmodel=medany -msmall-data-limit=8 -mstrict-align -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DMSCC_STDIO_THRU_CORE_UART_APB -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/application" -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/platform" -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/boards/icicle-kit-es" -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/boards/icicle-kit-es/platform_config" -std=gnu11 -Wstrict-prototypes -Wbad-function-cast -Wa,-adhlns="$@.lst" --specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


