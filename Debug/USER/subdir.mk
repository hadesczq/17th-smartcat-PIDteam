################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USER/Cpu0_Main.c \
../USER/Cpu1_Main.c \
../USER/adc.c \
../USER/debug.c \
../USER/img_process.c \
../USER/isr.c \
../USER/mylvgl.c \
../USER/pid.c \
../USER/pidcom.c 

OBJS += \
./USER/Cpu0_Main.o \
./USER/Cpu1_Main.o \
./USER/adc.o \
./USER/debug.o \
./USER/img_process.o \
./USER/isr.o \
./USER/mylvgl.o \
./USER/pid.o \
./USER/pidcom.o 

COMPILED_SRCS += \
./USER/Cpu0_Main.src \
./USER/Cpu1_Main.src \
./USER/adc.src \
./USER/debug.src \
./USER/img_process.src \
./USER/isr.src \
./USER/mylvgl.src \
./USER/pid.src \
./USER/pidcom.src 

C_DEPS += \
./USER/Cpu0_Main.d \
./USER/Cpu1_Main.d \
./USER/adc.d \
./USER/debug.d \
./USER/img_process.d \
./USER/isr.d \
./USER/mylvgl.d \
./USER/pid.d \
./USER/pidcom.d 


# Each subdirectory must supply rules for building sources it contributes
USER/%.src: ../USER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

USER/%.o: ./USER/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


