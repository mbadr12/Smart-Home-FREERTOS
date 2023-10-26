################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../COTS/FreeRTOS_SourceFiles/croutine.c \
../COTS/FreeRTOS_SourceFiles/heap_1.c \
../COTS/FreeRTOS_SourceFiles/list.c \
../COTS/FreeRTOS_SourceFiles/port.c \
../COTS/FreeRTOS_SourceFiles/queue.c \
../COTS/FreeRTOS_SourceFiles/tasks.c \
../COTS/FreeRTOS_SourceFiles/timers.c 

OBJS += \
./COTS/FreeRTOS_SourceFiles/croutine.o \
./COTS/FreeRTOS_SourceFiles/heap_1.o \
./COTS/FreeRTOS_SourceFiles/list.o \
./COTS/FreeRTOS_SourceFiles/port.o \
./COTS/FreeRTOS_SourceFiles/queue.o \
./COTS/FreeRTOS_SourceFiles/tasks.o \
./COTS/FreeRTOS_SourceFiles/timers.o 

C_DEPS += \
./COTS/FreeRTOS_SourceFiles/croutine.d \
./COTS/FreeRTOS_SourceFiles/heap_1.d \
./COTS/FreeRTOS_SourceFiles/list.d \
./COTS/FreeRTOS_SourceFiles/port.d \
./COTS/FreeRTOS_SourceFiles/queue.d \
./COTS/FreeRTOS_SourceFiles/tasks.d \
./COTS/FreeRTOS_SourceFiles/timers.d 


# Each subdirectory must supply rules for building sources it contributes
COTS/FreeRTOS_SourceFiles/%.o: ../COTS/FreeRTOS_SourceFiles/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


