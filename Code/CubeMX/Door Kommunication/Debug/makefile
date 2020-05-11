################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_HOST/Target/subdir.mk
-include USB_HOST/App/subdir.mk
-include Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Door\ Kommunication.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Door\ Kommunication.list \

OBJCOPY_BIN += \
Door\ Kommunication.bin \


# All Target
all: Door\ Kommunication.elf secondary-outputs

# Tool invocations
Door\ Kommunication.elf: $(OBJS) $(USER_OBJS) C:\Users\Sebbe\OneDrive\Dokument\STM32\workspace\ii1302-hardware\Code\CubeMX\Door\ Kommunication\STM32L476VGTX_FLASH.ld
	arm-none-eabi-gcc -o "Door Kommunication.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Sebbe\OneDrive\Dokument\STM32\workspace\ii1302-hardware\Code\CubeMX\Door Kommunication\STM32L476VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Door Kommunication.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Door\ Kommunication.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Door Kommunication.list"
	@echo 'Finished building: $@'
	@echo ' '

Door\ Kommunication.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Door Kommunication.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
