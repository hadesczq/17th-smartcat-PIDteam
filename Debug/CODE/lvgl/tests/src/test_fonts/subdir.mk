################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/lvgl/tests/src/test_fonts/font_1.c \
../CODE/lvgl/tests/src/test_fonts/font_2.c \
../CODE/lvgl/tests/src/test_fonts/font_3.c 

OBJS += \
./CODE/lvgl/tests/src/test_fonts/font_1.o \
./CODE/lvgl/tests/src/test_fonts/font_2.o \
./CODE/lvgl/tests/src/test_fonts/font_3.o 

COMPILED_SRCS += \
./CODE/lvgl/tests/src/test_fonts/font_1.src \
./CODE/lvgl/tests/src/test_fonts/font_2.src \
./CODE/lvgl/tests/src/test_fonts/font_3.src 

C_DEPS += \
./CODE/lvgl/tests/src/test_fonts/font_1.d \
./CODE/lvgl/tests/src/test_fonts/font_2.d \
./CODE/lvgl/tests/src/test_fonts/font_3.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/lvgl/tests/src/test_fonts/%.src: ../CODE/lvgl/tests/src/test_fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/lvgl/tests/src/test_fonts/%.o: ./CODE/lvgl/tests/src/test_fonts/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


