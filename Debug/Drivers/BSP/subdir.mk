################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/stm32f429i_discovery.c \
../Drivers/BSP/stm32f429i_discovery_eeprom.c \
../Drivers/BSP/stm32f429i_discovery_gyroscope.c \
../Drivers/BSP/stm32f429i_discovery_io.c \
../Drivers/BSP/stm32f429i_discovery_lcd.c \
../Drivers/BSP/stm32f429i_discovery_sdram.c \
../Drivers/BSP/stm32f429i_discovery_ts.c 

OBJS += \
./Drivers/BSP/stm32f429i_discovery.o \
./Drivers/BSP/stm32f429i_discovery_eeprom.o \
./Drivers/BSP/stm32f429i_discovery_gyroscope.o \
./Drivers/BSP/stm32f429i_discovery_io.o \
./Drivers/BSP/stm32f429i_discovery_lcd.o \
./Drivers/BSP/stm32f429i_discovery_sdram.o \
./Drivers/BSP/stm32f429i_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/stm32f429i_discovery.d \
./Drivers/BSP/stm32f429i_discovery_eeprom.d \
./Drivers/BSP/stm32f429i_discovery_gyroscope.d \
./Drivers/BSP/stm32f429i_discovery_io.d \
./Drivers/BSP/stm32f429i_discovery_lcd.d \
./Drivers/BSP/stm32f429i_discovery_sdram.d \
./Drivers/BSP/stm32f429i_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/%.o Drivers/BSP/%.su: ../Drivers/BSP/%.c Drivers/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP -I../Drivers/Fonts -I../Drivers/Components -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP

clean-Drivers-2f-BSP:
	-$(RM) ./Drivers/BSP/stm32f429i_discovery.d ./Drivers/BSP/stm32f429i_discovery.o ./Drivers/BSP/stm32f429i_discovery.su ./Drivers/BSP/stm32f429i_discovery_eeprom.d ./Drivers/BSP/stm32f429i_discovery_eeprom.o ./Drivers/BSP/stm32f429i_discovery_eeprom.su ./Drivers/BSP/stm32f429i_discovery_gyroscope.d ./Drivers/BSP/stm32f429i_discovery_gyroscope.o ./Drivers/BSP/stm32f429i_discovery_gyroscope.su ./Drivers/BSP/stm32f429i_discovery_io.d ./Drivers/BSP/stm32f429i_discovery_io.o ./Drivers/BSP/stm32f429i_discovery_io.su ./Drivers/BSP/stm32f429i_discovery_lcd.d ./Drivers/BSP/stm32f429i_discovery_lcd.o ./Drivers/BSP/stm32f429i_discovery_lcd.su ./Drivers/BSP/stm32f429i_discovery_sdram.d ./Drivers/BSP/stm32f429i_discovery_sdram.o ./Drivers/BSP/stm32f429i_discovery_sdram.su ./Drivers/BSP/stm32f429i_discovery_ts.d ./Drivers/BSP/stm32f429i_discovery_ts.o ./Drivers/BSP/stm32f429i_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP

