################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/delay_us.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/spi.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/delay_us.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/spi.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/delay_us.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/spi.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/delay_us.o: ../Core/Src/delay_us.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/delay_us.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/gpio.o: ../Core/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/spi.o: ../Core/Src/spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_hal_msp.o: ../Core/Src/stm32f4xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_it.o: ../Core/Src/stm32f4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f4xx.o: ../Core/Src/system_stm32f4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/tim.o: ../Core/Src/tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/usart.o: ../Core/Src/usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../tmc/ramp -I../Drivers/CMSIS/Include -I../tmc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../tmc/ic/TMC2130 -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../tmc/hal -I../tmc/helpers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

