################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/lvgl/src/extra/widgets/calendar/lv_calendar.c \
../CODE/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
../CODE/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c 

OBJS += \
./CODE/lvgl/src/extra/widgets/calendar/lv_calendar.o \
./CODE/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.o \
./CODE/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.o 

COMPILED_SRCS += \
./CODE/lvgl/src/extra/widgets/calendar/lv_calendar.src \
./CODE/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.src \
./CODE/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.src 

C_DEPS += \
./CODE/lvgl/src/extra/widgets/calendar/lv_calendar.d \
./CODE/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.d \
./CODE/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/lvgl/src/extra/widgets/calendar/%.src: ../CODE/lvgl/src/extra/widgets/calendar/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/lvgl/src/extra/widgets/calendar/%.o: ./CODE/lvgl/src/extra/widgets/calendar/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


