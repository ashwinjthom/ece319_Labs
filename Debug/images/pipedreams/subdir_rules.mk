################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
images/pipedreams/%.o: ../images/pipedreams/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/Users/shampoo/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"images/pipedreams/$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/shampoo/Documents/UTAustin/Coursework/Sp26/319H/MSPM0_ValvanoWare/ECE319K_Lab9H_SW/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


