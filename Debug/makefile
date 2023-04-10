################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_HOST/Target/subdir.mk
-include USB_HOST/App/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/Fonts/subdir.mk
-include Drivers/Components/wm8994/subdir.mk
-include Drivers/Components/ts3510/subdir.mk
-include Drivers/Components/stmpe811/subdir.mk
-include Drivers/Components/stmpe1600/subdir.mk
-include Drivers/Components/st7789h2/subdir.mk
-include Drivers/Components/st7735/subdir.mk
-include Drivers/Components/s5k5cag/subdir.mk
-include Drivers/Components/ov5640/subdir.mk
-include Drivers/Components/ov2640/subdir.mk
-include Drivers/Components/otm8009a/subdir.mk
-include Drivers/Components/nt35510/subdir.mk
-include Drivers/Components/mfxstm32l152/subdir.mk
-include Drivers/Components/lsm303dlhc/subdir.mk
-include Drivers/Components/lsm303agr/subdir.mk
-include Drivers/Components/ls016b8uy/subdir.mk
-include Drivers/Components/lis3dsh/subdir.mk
-include Drivers/Components/lis302dl/subdir.mk
-include Drivers/Components/l3gd20/subdir.mk
-include Drivers/Components/ili9341/subdir.mk
-include Drivers/Components/ili9325/subdir.mk
-include Drivers/Components/i3g4250d/subdir.mk
-include Drivers/Components/ft6x06/subdir.mk
-include Drivers/Components/exc7200/subdir.mk
-include Drivers/Components/cs43l22/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/subdir.mk
-include Drivers/BSP/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
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


BUILD_ARTIFACT_NAME := BSP_LIB
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
BSP_LIB.elf \

MAP_FILES += \
BSP_LIB.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BSP_LIB.list \


# All Target
all: main-build

# Main-build Target
main-build: BSP_LIB.elf secondary-outputs

# Tool invocations
BSP_LIB.elf BSP_LIB.map: $(OBJS) $(USER_OBJS) D:\PROJECTS\BOSCH\STM_WORKSPACE\BSP_LIB\STM32F429ZITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "BSP_LIB.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\PROJECTS\BOSCH\STM_WORKSPACE\BSP_LIB\STM32F429ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BSP_LIB.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BSP_LIB.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BSP_LIB.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) BSP_LIB.elf BSP_LIB.list BSP_LIB.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
