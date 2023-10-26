################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../COTS/2-HAL/4-CLCD/CLCD_progam.c 

OBJS += \
./COTS/2-HAL/4-CLCD/CLCD_progam.o 

C_DEPS += \
./COTS/2-HAL/4-CLCD/CLCD_progam.d 


# Each subdirectory must supply rules for building sources it contributes
COTS/2-HAL/4-CLCD/%.o: ../COTS/2-HAL/4-CLCD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


