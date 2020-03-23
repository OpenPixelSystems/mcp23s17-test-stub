file build/ops-spi-reader.elf
tar ext:3333
monitor halt
load build/ops-spi-reader.elf
monitor reset halt
mon arm semihosting enable
