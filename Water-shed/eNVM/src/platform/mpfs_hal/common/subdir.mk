################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/platform/mpfs_hal/common/mss_axiswitch.c \
../src/platform/mpfs_hal/common/mss_clint.c \
../src/platform/mpfs_hal/common/mss_h2f.c \
../src/platform/mpfs_hal/common/mss_irq_handler_stubs.c \
../src/platform/mpfs_hal/common/mss_l2_cache.c \
../src/platform/mpfs_hal/common/mss_mpu.c \
../src/platform/mpfs_hal/common/mss_mtrap.c \
../src/platform/mpfs_hal/common/mss_peripherals.c \
../src/platform/mpfs_hal/common/mss_plic.c \
../src/platform/mpfs_hal/common/mss_pmp.c \
../src/platform/mpfs_hal/common/mss_util.c 

OBJS += \
./src/platform/mpfs_hal/common/mss_axiswitch.o \
./src/platform/mpfs_hal/common/mss_clint.o \
./src/platform/mpfs_hal/common/mss_h2f.o \
./src/platform/mpfs_hal/common/mss_irq_handler_stubs.o \
./src/platform/mpfs_hal/common/mss_l2_cache.o \
./src/platform/mpfs_hal/common/mss_mpu.o \
./src/platform/mpfs_hal/common/mss_mtrap.o \
./src/platform/mpfs_hal/common/mss_peripherals.o \
./src/platform/mpfs_hal/common/mss_plic.o \
./src/platform/mpfs_hal/common/mss_pmp.o \
./src/platform/mpfs_hal/common/mss_util.o 

C_DEPS += \
./src/platform/mpfs_hal/common/mss_axiswitch.d \
./src/platform/mpfs_hal/common/mss_clint.d \
./src/platform/mpfs_hal/common/mss_h2f.d \
./src/platform/mpfs_hal/common/mss_irq_handler_stubs.d \
./src/platform/mpfs_hal/common/mss_l2_cache.d \
./src/platform/mpfs_hal/common/mss_mpu.d \
./src/platform/mpfs_hal/common/mss_mtrap.d \
./src/platform/mpfs_hal/common/mss_peripherals.d \
./src/platform/mpfs_hal/common/mss_plic.d \
./src/platform/mpfs_hal/common/mss_pmp.d \
./src/platform/mpfs_hal/common/mss_util.d 


# Each subdirectory must supply rules for building sources it contributes
src/platform/mpfs_hal/common/%.o: ../src/platform/mpfs_hal/common/%.c src/platform/mpfs_hal/common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv64gc -mabi=lp64d -mcmodel=medany -msmall-data-limit=8 -mstrict-align -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DNDEBUG -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/application" -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/platform" -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/boards/icicle-kit-es" -I"/home/vinay/Desktop/softconsole_watershed/Water-shed/src/boards/icicle-kit-es/platform_config" -std=gnu11 -Wstrict-prototypes -Wbad-function-cast -Wa,-adhlns="$@.lst" --specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


