################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/application/hart1/u54_1.c 

OBJS += \
./src/application/hart1/u54_1.o 

C_DEPS += \
./src/application/hart1/u54_1.d 


# Each subdirectory must supply rules for building sources it contributes
src/application/hart1/%.o: ../src/application/hart1/%.c src/application/hart1/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv64gc -mabi=lp64d -mcmodel=medany -msmall-data-limit=8 -mstrict-align -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DNDEBUG -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/application" -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/platform" -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/boards/icicle-kit-es" -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/boards/icicle-kit-es/platform_config" -std=gnu11 -Wstrict-prototypes -Wbad-function-cast -Wa,-adhlns="$@.lst" --specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


