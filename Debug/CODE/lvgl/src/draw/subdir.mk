################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/lvgl/src/draw/lv_draw.c \
../CODE/lvgl/src/draw/lv_draw_arc.c \
../CODE/lvgl/src/draw/lv_draw_img.c \
../CODE/lvgl/src/draw/lv_draw_label.c \
../CODE/lvgl/src/draw/lv_draw_line.c \
../CODE/lvgl/src/draw/lv_draw_mask.c \
../CODE/lvgl/src/draw/lv_draw_rect.c \
../CODE/lvgl/src/draw/lv_draw_triangle.c \
../CODE/lvgl/src/draw/lv_img_buf.c \
../CODE/lvgl/src/draw/lv_img_cache.c \
../CODE/lvgl/src/draw/lv_img_decoder.c 

OBJS += \
./CODE/lvgl/src/draw/lv_draw.o \
./CODE/lvgl/src/draw/lv_draw_arc.o \
./CODE/lvgl/src/draw/lv_draw_img.o \
./CODE/lvgl/src/draw/lv_draw_label.o \
./CODE/lvgl/src/draw/lv_draw_line.o \
./CODE/lvgl/src/draw/lv_draw_mask.o \
./CODE/lvgl/src/draw/lv_draw_rect.o \
./CODE/lvgl/src/draw/lv_draw_triangle.o \
./CODE/lvgl/src/draw/lv_img_buf.o \
./CODE/lvgl/src/draw/lv_img_cache.o \
./CODE/lvgl/src/draw/lv_img_decoder.o 

COMPILED_SRCS += \
./CODE/lvgl/src/draw/lv_draw.src \
./CODE/lvgl/src/draw/lv_draw_arc.src \
./CODE/lvgl/src/draw/lv_draw_img.src \
./CODE/lvgl/src/draw/lv_draw_label.src \
./CODE/lvgl/src/draw/lv_draw_line.src \
./CODE/lvgl/src/draw/lv_draw_mask.src \
./CODE/lvgl/src/draw/lv_draw_rect.src \
./CODE/lvgl/src/draw/lv_draw_triangle.src \
./CODE/lvgl/src/draw/lv_img_buf.src \
./CODE/lvgl/src/draw/lv_img_cache.src \
./CODE/lvgl/src/draw/lv_img_decoder.src 

C_DEPS += \
./CODE/lvgl/src/draw/lv_draw.d \
./CODE/lvgl/src/draw/lv_draw_arc.d \
./CODE/lvgl/src/draw/lv_draw_img.d \
./CODE/lvgl/src/draw/lv_draw_label.d \
./CODE/lvgl/src/draw/lv_draw_line.d \
./CODE/lvgl/src/draw/lv_draw_mask.d \
./CODE/lvgl/src/draw/lv_draw_rect.d \
./CODE/lvgl/src/draw/lv_draw_triangle.d \
./CODE/lvgl/src/draw/lv_img_buf.d \
./CODE/lvgl/src/draw/lv_img_cache.d \
./CODE/lvgl/src/draw/lv_img_decoder.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/lvgl/src/draw/%.src: ../CODE/lvgl/src/draw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/lvgl/src/draw/%.o: ./CODE/lvgl/src/draw/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


