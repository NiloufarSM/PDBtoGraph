################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Amino.cpp \
../src/Atom.cpp \
../src/Chain.cpp \
../src/Graph.cpp \
../src/Main.cpp \
../src/Model.cpp \
../src/PDB.cpp \
../src/Parser.cpp 

OBJS += \
./src/Amino.o \
./src/Atom.o \
./src/Chain.o \
./src/Graph.o \
./src/Main.o \
./src/Model.o \
./src/PDB.o \
./src/Parser.o 

CPP_DEPS += \
./src/Amino.d \
./src/Atom.d \
./src/Chain.d \
./src/Graph.d \
./src/Main.d \
./src/Model.d \
./src/PDB.d \
./src/Parser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


