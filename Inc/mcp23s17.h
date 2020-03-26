/**
 * @file mcp23s17_stub.h
 * @brief  MCP23S17 Header implementation
 * @author Bram Vlerick <bram.vlerick@openpixelsystems.org>
 * @version v0.1
 * @date 2020-03-23
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MCP23S17_IODIRA 	0x00
#define MCP23S17_IODIRB 	0x01
#define MCP23S17_IPOLA 		0x02
#define MCP23S17_IPOLB 		0x03
#define MCP23S17_GPINTENA 	0x04
#define MCP23S17_GPINTENB 	0x05
#define MCP23S17_DEFVALA 	0x06
#define MCP23S17_DEFVALB 	0x07
#define MCP23S17_INTCONA 	0x08
#define MCP23S17_INTCONB 	0x09
#define MCP23S17_IOCON1 	0x0A
#define MCP23S17_IOCON2 	0x0B
#define MCP23S17_GPPUA 		0x0C
#define MCP23S17_GPPUB 		0x0D
#define MCP23S17_INTFA 		0x0E
#define MCP23S17_INTFB 		0x0F
#define MCP23S17_INTCAPA 	0x10
#define MCP23S17_INTCAPB 	0x11
#define MCP23S17_GPIOA 		0x12
#define MCP23S17_GPIOB 		0x13
#define MCP23S17_OLATA 		0x14
#define MCP23S17_OLATB 		0x15

#define MCP23S17_DUMMY		0xff

#define MCP23S17_NR_REGS	0x16
#define MCP23S17_BANK_0 	0x0
#define MCP23S17_BANK_1		0x1

#define MCP23S17_ADDRESS_MASK 	~(0x4e) // | 0 | 1 | 0 | 0 | A2 | A1 | A0 | R/W |

#define MCP23S17_REG_TO_STRING(a) #a

struct mcp23s17_regstate_t {
	uint8_t iodira;
	uint8_t iodirb;
	uint8_t ipola;
	uint8_t ipolb;
	uint8_t gpintena;
	uint8_t gpintenb;
	uint8_t defvala;
	uint8_t defvalb;
	uint8_t intcona;
	uint8_t intconb;
	uint8_t iocon1;
	uint8_t iocon2;
	uint8_t gppua;
	uint8_t gppub;
	uint8_t intfa;
	uint8_t intfb;
	uint8_t intcapa;
	uint8_t intcapb;
	uint8_t gpioa;
	uint8_t gpiob;
	uint8_t olata;
	uint8_t olatb;
};


static inline int MCP23S17_convert_reg(uint8_t bank, uint8_t reg)
{
	if (bank == MCP23S17_BANK_1) {
		return (reg % 2 ? (reg / 2 + (1 << 4)): reg / 2);
	}
	return reg;
}

char* MCP23S17_reg_to_string(int reg);
int MCP23S17_process_packet(unsigned char *spi_tx_buffer, unsigned char *spi_rx_buffer);
