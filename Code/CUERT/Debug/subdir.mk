################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DCmotor.c \
../gpio.c \
../lcd.c \
../main.c \
../pwm_timer0.c \
../stepmotor.c \
../timer1.c \
../uart.c 

OBJS += \
./DCmotor.o \
./gpio.o \
./lcd.o \
./main.o \
./pwm_timer0.o \
./stepmotor.o \
./timer1.o \
./uart.o 

C_DEPS += \
./DCmotor.d \
./gpio.d \
./lcd.d \
./main.d \
./pwm_timer0.d \
./stepmotor.d \
./timer1.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


