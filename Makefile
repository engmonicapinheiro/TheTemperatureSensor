stm32l0xx-headers := CMSIS/Device/ST/STM32L0xx/Include
stm32l0xx-sources := CMSIS/Device/ST/STM32L0xx/Source
cmmsis-headers := CMSIS/Include
headers := Inc
sources := Src
executable := main.elf
assembly := main.s
include-flags := -I ${stm32l0xx-headers} -I ${stm32l0xx-sources} -I ${cmmsis-headers} -I ${headers} -I ${sources}

.PHONY: all
all:
	make clean; \
	make compile; \
	make gen-asm-on-macos;

.PHONY: clean-on-macos
clean:
	make clean-on-macos

.PHONY: compile
compile:
	if [ "$(shell uname)" = "Darwin" ]; then \
		make compile-on-macos; \
	elif [ "$(shell uname)" = "Windows" ]; then \
		make compile-on-windows; \
	else \
		echo "Unsupported OS"; \
	fi

.PHONY: compile-on-macos
compile-on-macos: ${executable}

${executable}: ${sources}/main.c
	arm-none-eabi-gcc -c ${include-flags} --specs=nosys.specs $< -o $@

.PHONY: gen-asm-on-macos
gen-asm-on-macos: ${assembly}

${assembly}: ${sources}/main.c
	arm-none-eabi-gcc -c ${include-flags} --specs=nosys.specs $< -S

.PHONY: clean-on-macos
clean-on-macos:
	rm -rf ${executable} ${assembly}