################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/fuzzy.c \
../CODE/ladrc.c \
../CODE/ws2812.c 

OBJS += \
./CODE/fuzzy.o \
./CODE/ladrc.o \
./CODE/ws2812.o 

COMPILED_SRCS += \
./CODE/fuzzy.src \
./CODE/ladrc.src \
./CODE/ws2812.src 

C_DEPS += \
./CODE/fuzzy.d \
./CODE/ladrc.d \
./CODE/ws2812.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/%.src: ../CODE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/%.o: ./CODE/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


