################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_arc.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_bg.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_composite.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_img.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_label.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_line.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_mask.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_polygon.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_rect.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.c \
../CODE/lvgl/src/draw/sdl/lv_draw_sdl_utils.c 

OBJS += \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_arc.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_bg.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_composite.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_img.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_label.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_line.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_mask.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_polygon.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_rect.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.o \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_utils.o 

COMPILED_SRCS += \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_arc.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_bg.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_composite.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_img.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_label.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_line.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_mask.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_polygon.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_rect.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.src \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_utils.src 

C_DEPS += \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_arc.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_bg.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_composite.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_img.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_label.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_line.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_mask.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_polygon.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_rect.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.d \
./CODE/lvgl/src/draw/sdl/lv_draw_sdl_utils.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/lvgl/src/draw/sdl/%.src: ../CODE/lvgl/src/draw/sdl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/lvgl/src/draw/sdl/%.o: ./CODE/lvgl/src/draw/sdl/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


