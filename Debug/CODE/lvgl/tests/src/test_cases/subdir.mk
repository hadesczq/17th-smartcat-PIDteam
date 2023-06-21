################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/lvgl/tests/src/test_cases/_test_template.c \
../CODE/lvgl/tests/src/test_cases/test_arc.c \
../CODE/lvgl/tests/src/test_cases/test_bar.c \
../CODE/lvgl/tests/src/test_cases/test_checkbox.c \
../CODE/lvgl/tests/src/test_cases/test_config.c \
../CODE/lvgl/tests/src/test_cases/test_demo_stress.c \
../CODE/lvgl/tests/src/test_cases/test_demo_widgets.c \
../CODE/lvgl/tests/src/test_cases/test_dropdown.c \
../CODE/lvgl/tests/src/test_cases/test_event.c \
../CODE/lvgl/tests/src/test_cases/test_font_loader.c \
../CODE/lvgl/tests/src/test_cases/test_obj_tree.c \
../CODE/lvgl/tests/src/test_cases/test_snapshot.c \
../CODE/lvgl/tests/src/test_cases/test_style.c \
../CODE/lvgl/tests/src/test_cases/test_switch.c \
../CODE/lvgl/tests/src/test_cases/test_txt.c 

OBJS += \
./CODE/lvgl/tests/src/test_cases/_test_template.o \
./CODE/lvgl/tests/src/test_cases/test_arc.o \
./CODE/lvgl/tests/src/test_cases/test_bar.o \
./CODE/lvgl/tests/src/test_cases/test_checkbox.o \
./CODE/lvgl/tests/src/test_cases/test_config.o \
./CODE/lvgl/tests/src/test_cases/test_demo_stress.o \
./CODE/lvgl/tests/src/test_cases/test_demo_widgets.o \
./CODE/lvgl/tests/src/test_cases/test_dropdown.o \
./CODE/lvgl/tests/src/test_cases/test_event.o \
./CODE/lvgl/tests/src/test_cases/test_font_loader.o \
./CODE/lvgl/tests/src/test_cases/test_obj_tree.o \
./CODE/lvgl/tests/src/test_cases/test_snapshot.o \
./CODE/lvgl/tests/src/test_cases/test_style.o \
./CODE/lvgl/tests/src/test_cases/test_switch.o \
./CODE/lvgl/tests/src/test_cases/test_txt.o 

COMPILED_SRCS += \
./CODE/lvgl/tests/src/test_cases/_test_template.src \
./CODE/lvgl/tests/src/test_cases/test_arc.src \
./CODE/lvgl/tests/src/test_cases/test_bar.src \
./CODE/lvgl/tests/src/test_cases/test_checkbox.src \
./CODE/lvgl/tests/src/test_cases/test_config.src \
./CODE/lvgl/tests/src/test_cases/test_demo_stress.src \
./CODE/lvgl/tests/src/test_cases/test_demo_widgets.src \
./CODE/lvgl/tests/src/test_cases/test_dropdown.src \
./CODE/lvgl/tests/src/test_cases/test_event.src \
./CODE/lvgl/tests/src/test_cases/test_font_loader.src \
./CODE/lvgl/tests/src/test_cases/test_obj_tree.src \
./CODE/lvgl/tests/src/test_cases/test_snapshot.src \
./CODE/lvgl/tests/src/test_cases/test_style.src \
./CODE/lvgl/tests/src/test_cases/test_switch.src \
./CODE/lvgl/tests/src/test_cases/test_txt.src 

C_DEPS += \
./CODE/lvgl/tests/src/test_cases/_test_template.d \
./CODE/lvgl/tests/src/test_cases/test_arc.d \
./CODE/lvgl/tests/src/test_cases/test_bar.d \
./CODE/lvgl/tests/src/test_cases/test_checkbox.d \
./CODE/lvgl/tests/src/test_cases/test_config.d \
./CODE/lvgl/tests/src/test_cases/test_demo_stress.d \
./CODE/lvgl/tests/src/test_cases/test_demo_widgets.d \
./CODE/lvgl/tests/src/test_cases/test_dropdown.d \
./CODE/lvgl/tests/src/test_cases/test_event.d \
./CODE/lvgl/tests/src/test_cases/test_font_loader.d \
./CODE/lvgl/tests/src/test_cases/test_obj_tree.d \
./CODE/lvgl/tests/src/test_cases/test_snapshot.d \
./CODE/lvgl/tests/src/test_cases/test_style.d \
./CODE/lvgl/tests/src/test_cases/test_switch.d \
./CODE/lvgl/tests/src/test_cases/test_txt.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/lvgl/tests/src/test_cases/%.src: ../CODE/lvgl/tests/src/test_cases/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/lvgl/tests/src/test_cases/%.o: ./CODE/lvgl/tests/src/test_cases/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


