################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/lvgl/src/draw/sw/lv_draw_sw.c \
../CODE/lvgl/src/draw/sw/lv_draw_sw_arc.c \
../CODE/lvgl/src/draw/sw/lv_draw_sw_blend.c \
../CODE/lvgl/src/draw/sw/lv_draw_sw_dither.c \
../CODE/lvgl/src/draw/sw/lv_draw_sw_gradient.c \
../CODE/lvgl/src/draw/sw/lv_draw_sw_img.c \
../CODE/lvgl/src/draw/sw/lv_draw_sw_letter.c \
../CODE/lvgl/src/draw/sw/lv_draw_sw_line.c \
../CODE/lvgl/src/draw/sw/lv_draw_sw_polygon.c \
../CODE/lvgl/src/draw/sw/lv_draw_sw_rect.c 

OBJS += \
./CODE/lvgl/src/draw/sw/lv_draw_sw.o \
./CODE/lvgl/src/draw/sw/lv_draw_sw_arc.o \
./CODE/lvgl/src/draw/sw/lv_draw_sw_blend.o \
./CODE/lvgl/src/draw/sw/lv_draw_sw_dither.o \
./CODE/lvgl/src/draw/sw/lv_draw_sw_gradient.o \
./CODE/lvgl/src/draw/sw/lv_draw_sw_img.o \
./CODE/lvgl/src/draw/sw/lv_draw_sw_letter.o \
./CODE/lvgl/src/draw/sw/lv_draw_sw_line.o \
./CODE/lvgl/src/draw/sw/lv_draw_sw_polygon.o \
./CODE/lvgl/src/draw/sw/lv_draw_sw_rect.o 

COMPILED_SRCS += \
./CODE/lvgl/src/draw/sw/lv_draw_sw.src \
./CODE/lvgl/src/draw/sw/lv_draw_sw_arc.src \
./CODE/lvgl/src/draw/sw/lv_draw_sw_blend.src \
./CODE/lvgl/src/draw/sw/lv_draw_sw_dither.src \
./CODE/lvgl/src/draw/sw/lv_draw_sw_gradient.src \
./CODE/lvgl/src/draw/sw/lv_draw_sw_img.src \
./CODE/lvgl/src/draw/sw/lv_draw_sw_letter.src \
./CODE/lvgl/src/draw/sw/lv_draw_sw_line.src \
./CODE/lvgl/src/draw/sw/lv_draw_sw_polygon.src \
./CODE/lvgl/src/draw/sw/lv_draw_sw_rect.src 

C_DEPS += \
./CODE/lvgl/src/draw/sw/lv_draw_sw.d \
./CODE/lvgl/src/draw/sw/lv_draw_sw_arc.d \
./CODE/lvgl/src/draw/sw/lv_draw_sw_blend.d \
./CODE/lvgl/src/draw/sw/lv_draw_sw_dither.d \
./CODE/lvgl/src/draw/sw/lv_draw_sw_gradient.d \
./CODE/lvgl/src/draw/sw/lv_draw_sw_img.d \
./CODE/lvgl/src/draw/sw/lv_draw_sw_letter.d \
./CODE/lvgl/src/draw/sw/lv_draw_sw_line.d \
./CODE/lvgl/src/draw/sw/lv_draw_sw_polygon.d \
./CODE/lvgl/src/draw/sw/lv_draw_sw_rect.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/lvgl/src/draw/sw/%.src: ../CODE/lvgl/src/draw/sw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/lvgl/src/draw/sw/%.o: ./CODE/lvgl/src/draw/sw/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


