################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/OLED/oled.c 

OBJS += \
./HARDWARE/OLED/oled.o 

C_DEPS += \
./HARDWARE/OLED/oled.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/OLED/oled.o: ../HARDWARE/OLED/oled.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32G431xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../HARDWARE/OLED -I../APP/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HARDWARE/OLED/oled.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

