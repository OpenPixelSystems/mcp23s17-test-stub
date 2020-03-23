# SPI Stub

## Intro

This repository contains a very simple SPI Slave program for the STM32F767ZI-Nucleo board. The program mimics the behavior of an MCP23S17 device. This can be useful when implementing support for this chip in different software stacks while not having the actual HW available.

## HW

As mentioned before it runs on an STM32F767ZI-Nucleo board. The SW configures the SPI_B Interface of the board. Located on Header CN7. Using PINS PB3,4,5 and PA4.

PB3 ------> SPI1_SCK
PB4 ------> SPI1_MISO
PB5 ------> SPI1_MOSI
PA4 ------> SPI1_NSS

## SW

The program currently just consists of a small main loop which waits for the SPI IRQ to trigger the SPI RX Complete Soft IRQ. When this sIRQ gets triggerd the program will read-out the SPI buffer and process the received message.
