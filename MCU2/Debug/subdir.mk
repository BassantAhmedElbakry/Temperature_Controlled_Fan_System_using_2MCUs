################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LEDs.c \
../buzzer.c \
../dc.c \
../gpio.c \
../main.c \
../pwm.c \
../uart.c 

OBJS += \
./LEDs.o \
./buzzer.o \
./dc.o \
./gpio.o \
./main.o \
./pwm.o \
./uart.o 

C_DEPS += \
./LEDs.d \
./buzzer.d \
./dc.d \
./gpio.d \
./main.d \
./pwm.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


