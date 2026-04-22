################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Clock.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/inc/Clock.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DAC5.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/inc/DAC5.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/inc/LaunchPad.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SPI.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/inc/SPI.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ST7735_SDC.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/SDCFilecpp/ST7735_SDC.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SlidePot.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/inc/SlidePot.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TExaS.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/inc/TExaS.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Timer.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/inc/Timer.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UART.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/inc/UART.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UARTbusywait.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/inc/UARTbusywait.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

diskio.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/SDCFilecpp/diskio.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ff.o: /Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/SDCFilecpp/ff.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


