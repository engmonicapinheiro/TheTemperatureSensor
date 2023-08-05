stm32l0xx-headers := CMSIS/Device/ST/STM32L0xx/Include
stm32l0xx-sources := CMSIS/Device/ST/STM32L0xx/Source
cmmsis-headers := CMSIS/Include
headers := Inc
sources := Src
executable := main.elf
assembly := main.s
include-flags := -I ${stm32l0xx-headers} -I ${stm32l0xx-sources} -I ${cmmsis-headers} -I ${headers} -I ${sources}

CC=	arm-none-eabi-gcc
CFLAGS= -Wall -shared -Wextra -Werror -O2 -specs=nosys.specs

.PHONY: all
all: clean compile gen-asm

.PHONY: compile
compile: ${executable}

${executable}: $(sources)/main.c $(headers) $(stm32l0xx-headers) $(cmmsis-headers)
	${CC} ${CFLAGS} -c ${include-flags} $< -o $@

.PHONY: gen-asm
gen-asm: ${assembly}

${assembly}: ${sources}/main.c
	${CC} ${CFLAGS} -c ${include-flags} $< -S


.PHONY: clean
clean:
	rm -rf ${executable} ${assembly} ${graph.dot} ${graph.png}

# Vizualization of the Makefile dependencies
graph.dot := graph.dot
graph.png := graph.png

${graph.dot}: Makefile
	make -Bnd | make2graph > $@

${graph.png}: ${graph.dot}
	dot -Tpng -o $@ $<
