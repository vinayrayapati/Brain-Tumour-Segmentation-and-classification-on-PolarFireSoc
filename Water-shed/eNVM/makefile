################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/platform/mpfs_hal/startup_gcc/subdir.mk
-include src/platform/mpfs_hal/common/nwc/subdir.mk
-include src/platform/mpfs_hal/common/subdir.mk
-include src/platform/hal/subdir.mk
-include src/platform/drivers/mss/mss_mmuart/subdir.mk
-include src/platform/drivers/mss/mss_gpio/subdir.mk
-include src/application/hart4/subdir.mk
-include src/application/hart3/subdir.mk
-include src/application/hart2/subdir.mk
-include src/application/hart1/subdir.mk
-include src/application/hart0/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Water-shed
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Water-shed.hex \

SECONDARY_LIST += \
Water-shed.lst \

SECONDARY_SIZE += \
Water-shed.siz \


# All Target
all:
	+@$(MAKE) --no-print-directory pre-build && $(MAKE) --no-print-directory main-build

# Main-build Target
main-build: Water-shed.elf secondary-outputs

# Tool invocations
Water-shed.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv64-unknown-elf-gcc -march=rv64gc -mabi=lp64d -mcmodel=medany -msmall-data-limit=8 -mstrict-align -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "/home/vinay/Desktop/softconsole_watershed/Water-shed/src/platform/platform_config_reference/linker/mpfs-envm-lma-scratchpad-vma.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"Water-shed.map" --specs=nano.specs --specs=nosys.specs -o "Water-shed.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Water-shed.hex: Water-shed.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv64-unknown-elf-objcopy -O ihex "Water-shed.elf"  "Water-shed.hex"
	@echo 'Finished building: $@'
	@echo ' '

Water-shed.lst: Water-shed.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv64-unknown-elf-objdump --source --all-headers --demangle --line-numbers --wide "Water-shed.elf" > "Water-shed.lst"
	@echo 'Finished building: $@'
	@echo ' '

Water-shed.siz: Water-shed.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv64-unknown-elf-size --format=sysv --totals --radix=16 "Water-shed.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Water-shed.elf
	-@echo ' '

pre-build:
	-@echo 'This step generates the configuration header files from the xml file which contains the hardware configurations of your Libero design. For this project the xml configurations are located at  ../src/boards/icicle-kit-es. You will need to have your board specific folder if you are working on another board'
	-/home/vinay/Desktop/soft_console/SoftConsole-v2022.2-RISC-V-747/python3/bin/python3 ../src/platform/soc_config_generator/mpfs_configuration_generator.py ../src/boards/icicle-kit-es/fpga_design/design_description/   ../src/boards/icicle-kit-es
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build pre-build

-include ../makefile.targets
