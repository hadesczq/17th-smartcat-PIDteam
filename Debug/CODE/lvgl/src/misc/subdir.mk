################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/lvgl/src/misc/lv_anim.c \
../CODE/lvgl/src/misc/lv_anim_timeline.c \
../CODE/lvgl/src/misc/lv_area.c \
../CODE/lvgl/src/misc/lv_async.c \
../CODE/lvgl/src/misc/lv_bidi.c \
../CODE/lvgl/src/misc/lv_color.c \
../CODE/lvgl/src/misc/lv_fs.c \
../CODE/lvgl/src/misc/lv_gc.c \
../CODE/lvgl/src/misc/lv_ll.c \
../CODE/lvgl/src/misc/lv_log.c \
../CODE/lvgl/src/misc/lv_lru.c \
../CODE/lvgl/src/misc/lv_math.c \
../CODE/lvgl/src/misc/lv_mem.c \
../CODE/lvgl/src/misc/lv_printf.c \
../CODE/lvgl/src/misc/lv_style.c \
../CODE/lvgl/src/misc/lv_style_gen.c \
../CODE/lvgl/src/misc/lv_templ.c \
../CODE/lvgl/src/misc/lv_timer.c \
../CODE/lvgl/src/misc/lv_tlsf.c \
../CODE/lvgl/src/misc/lv_txt.c \
../CODE/lvgl/src/misc/lv_txt_ap.c \
../CODE/lvgl/src/misc/lv_utils.c 

OBJS += \
./CODE/lvgl/src/misc/lv_anim.o \
./CODE/lvgl/src/misc/lv_anim_timeline.o \
./CODE/lvgl/src/misc/lv_area.o \
./CODE/lvgl/src/misc/lv_async.o \
./CODE/lvgl/src/misc/lv_bidi.o \
./CODE/lvgl/src/misc/lv_color.o \
./CODE/lvgl/src/misc/lv_fs.o \
./CODE/lvgl/src/misc/lv_gc.o \
./CODE/lvgl/src/misc/lv_ll.o \
./CODE/lvgl/src/misc/lv_log.o \
./CODE/lvgl/src/misc/lv_lru.o \
./CODE/lvgl/src/misc/lv_math.o \
./CODE/lvgl/src/misc/lv_mem.o \
./CODE/lvgl/src/misc/lv_printf.o \
./CODE/lvgl/src/misc/lv_style.o \
./CODE/lvgl/src/misc/lv_style_gen.o \
./CODE/lvgl/src/misc/lv_templ.o \
./CODE/lvgl/src/misc/lv_timer.o \
./CODE/lvgl/src/misc/lv_tlsf.o \
./CODE/lvgl/src/misc/lv_txt.o \
./CODE/lvgl/src/misc/lv_txt_ap.o \
./CODE/lvgl/src/misc/lv_utils.o 

COMPILED_SRCS += \
./CODE/lvgl/src/misc/lv_anim.src \
./CODE/lvgl/src/misc/lv_anim_timeline.src \
./CODE/lvgl/src/misc/lv_area.src \
./CODE/lvgl/src/misc/lv_async.src \
./CODE/lvgl/src/misc/lv_bidi.src \
./CODE/lvgl/src/misc/lv_color.src \
./CODE/lvgl/src/misc/lv_fs.src \
./CODE/lvgl/src/misc/lv_gc.src \
./CODE/lvgl/src/misc/lv_ll.src \
./CODE/lvgl/src/misc/lv_log.src \
./CODE/lvgl/src/misc/lv_lru.src \
./CODE/lvgl/src/misc/lv_math.src \
./CODE/lvgl/src/misc/lv_mem.src \
./CODE/lvgl/src/misc/lv_printf.src \
./CODE/lvgl/src/misc/lv_style.src \
./CODE/lvgl/src/misc/lv_style_gen.src \
./CODE/lvgl/src/misc/lv_templ.src \
./CODE/lvgl/src/misc/lv_timer.src \
./CODE/lvgl/src/misc/lv_tlsf.src \
./CODE/lvgl/src/misc/lv_txt.src \
./CODE/lvgl/src/misc/lv_txt_ap.src \
./CODE/lvgl/src/misc/lv_utils.src 

C_DEPS += \
./CODE/lvgl/src/misc/lv_anim.d \
./CODE/lvgl/src/misc/lv_anim_timeline.d \
./CODE/lvgl/src/misc/lv_area.d \
./CODE/lvgl/src/misc/lv_async.d \
./CODE/lvgl/src/misc/lv_bidi.d \
./CODE/lvgl/src/misc/lv_color.d \
./CODE/lvgl/src/misc/lv_fs.d \
./CODE/lvgl/src/misc/lv_gc.d \
./CODE/lvgl/src/misc/lv_ll.d \
./CODE/lvgl/src/misc/lv_log.d \
./CODE/lvgl/src/misc/lv_lru.d \
./CODE/lvgl/src/misc/lv_math.d \
./CODE/lvgl/src/misc/lv_mem.d \
./CODE/lvgl/src/misc/lv_printf.d \
./CODE/lvgl/src/misc/lv_style.d \
./CODE/lvgl/src/misc/lv_style_gen.d \
./CODE/lvgl/src/misc/lv_templ.d \
./CODE/lvgl/src/misc/lv_timer.d \
./CODE/lvgl/src/misc/lv_tlsf.d \
./CODE/lvgl/src/misc/lv_txt.d \
./CODE/lvgl/src/misc/lv_txt_ap.d \
./CODE/lvgl/src/misc/lv_utils.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/lvgl/src/misc/%.src: ../CODE/lvgl/src/misc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/lvgl/src/misc/%.o: ./CODE/lvgl/src/misc/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


