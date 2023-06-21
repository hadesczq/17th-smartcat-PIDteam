################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/lvgl/src/widgets/lv_arc.c \
../CODE/lvgl/src/widgets/lv_bar.c \
../CODE/lvgl/src/widgets/lv_btn.c \
../CODE/lvgl/src/widgets/lv_btnmatrix.c \
../CODE/lvgl/src/widgets/lv_canvas.c \
../CODE/lvgl/src/widgets/lv_checkbox.c \
../CODE/lvgl/src/widgets/lv_dropdown.c \
../CODE/lvgl/src/widgets/lv_img.c \
../CODE/lvgl/src/widgets/lv_label.c \
../CODE/lvgl/src/widgets/lv_line.c \
../CODE/lvgl/src/widgets/lv_objx_templ.c \
../CODE/lvgl/src/widgets/lv_roller.c \
../CODE/lvgl/src/widgets/lv_slider.c \
../CODE/lvgl/src/widgets/lv_switch.c \
../CODE/lvgl/src/widgets/lv_table.c \
../CODE/lvgl/src/widgets/lv_textarea.c 

OBJS += \
./CODE/lvgl/src/widgets/lv_arc.o \
./CODE/lvgl/src/widgets/lv_bar.o \
./CODE/lvgl/src/widgets/lv_btn.o \
./CODE/lvgl/src/widgets/lv_btnmatrix.o \
./CODE/lvgl/src/widgets/lv_canvas.o \
./CODE/lvgl/src/widgets/lv_checkbox.o \
./CODE/lvgl/src/widgets/lv_dropdown.o \
./CODE/lvgl/src/widgets/lv_img.o \
./CODE/lvgl/src/widgets/lv_label.o \
./CODE/lvgl/src/widgets/lv_line.o \
./CODE/lvgl/src/widgets/lv_objx_templ.o \
./CODE/lvgl/src/widgets/lv_roller.o \
./CODE/lvgl/src/widgets/lv_slider.o \
./CODE/lvgl/src/widgets/lv_switch.o \
./CODE/lvgl/src/widgets/lv_table.o \
./CODE/lvgl/src/widgets/lv_textarea.o 

COMPILED_SRCS += \
./CODE/lvgl/src/widgets/lv_arc.src \
./CODE/lvgl/src/widgets/lv_bar.src \
./CODE/lvgl/src/widgets/lv_btn.src \
./CODE/lvgl/src/widgets/lv_btnmatrix.src \
./CODE/lvgl/src/widgets/lv_canvas.src \
./CODE/lvgl/src/widgets/lv_checkbox.src \
./CODE/lvgl/src/widgets/lv_dropdown.src \
./CODE/lvgl/src/widgets/lv_img.src \
./CODE/lvgl/src/widgets/lv_label.src \
./CODE/lvgl/src/widgets/lv_line.src \
./CODE/lvgl/src/widgets/lv_objx_templ.src \
./CODE/lvgl/src/widgets/lv_roller.src \
./CODE/lvgl/src/widgets/lv_slider.src \
./CODE/lvgl/src/widgets/lv_switch.src \
./CODE/lvgl/src/widgets/lv_table.src \
./CODE/lvgl/src/widgets/lv_textarea.src 

C_DEPS += \
./CODE/lvgl/src/widgets/lv_arc.d \
./CODE/lvgl/src/widgets/lv_bar.d \
./CODE/lvgl/src/widgets/lv_btn.d \
./CODE/lvgl/src/widgets/lv_btnmatrix.d \
./CODE/lvgl/src/widgets/lv_canvas.d \
./CODE/lvgl/src/widgets/lv_checkbox.d \
./CODE/lvgl/src/widgets/lv_dropdown.d \
./CODE/lvgl/src/widgets/lv_img.d \
./CODE/lvgl/src/widgets/lv_label.d \
./CODE/lvgl/src/widgets/lv_line.d \
./CODE/lvgl/src/widgets/lv_objx_templ.d \
./CODE/lvgl/src/widgets/lv_roller.d \
./CODE/lvgl/src/widgets/lv_slider.d \
./CODE/lvgl/src/widgets/lv_switch.d \
./CODE/lvgl/src/widgets/lv_table.d \
./CODE/lvgl/src/widgets/lv_textarea.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/lvgl/src/widgets/%.src: ../CODE/lvgl/src/widgets/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/lvgl/src/widgets/%.o: ./CODE/lvgl/src/widgets/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


