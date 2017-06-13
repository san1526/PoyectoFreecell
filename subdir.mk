################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Card.cpp \
../Classifier.cpp \
../FrameProcessor.cpp \
../GameSolver.cpp \
../Gameinstance.cpp \
../main.cpp 

OBJS += \
./Card.o \
./Classifier.o \
./FrameProcessor.o \
./GameSolver.o \
./Gameinstance.o \
./main.o 

CPP_DEPS += \
./Card.d \
./Classifier.d \
./FrameProcessor.d \
./GameSolver.d \
./Gameinstance.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


