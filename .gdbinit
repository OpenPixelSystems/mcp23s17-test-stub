file build-cortex/spi-stub.elf
tar ext:3333
monitor halt
load build-cortex/spi-stub.elf
monitor reset halt
mon arm semihosting enable
