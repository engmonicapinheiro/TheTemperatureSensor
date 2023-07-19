stm32l0xx-headers := CMSIS/Device/ST/STM32L0xx/Include
stm32l0xx-sources := CMSIS/Device/ST/STM32L0xx/Source
cmmsis-headers := CMSIS/Include
headers := Inc
sources := Src
executable := main.elf
assembly := main.s
include-flags := -I ${stm32l0xx-headers} -I ${stm32l0xx-sources} -I ${cmmsis-headers} -I ${headers} -I ${sources}

clean:
	make clean-on-macos

compile-on-macos:
	arm-none-eabi-gcc -c ${include-flags} --specs=nosys.specs ${sources}/main.c -o ${executable}

gen-asm-on-macos:
	arm-none-eabi-gcc -c ${include-flags} --specs=nosys.specs ${sources}/main.c -S

clean-on-macos:
	rm -rf ${executable} ${assembly}