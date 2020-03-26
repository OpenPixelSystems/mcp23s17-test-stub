#include "mcp23s17.h"

static int CURRENT_MCP_BANK = MCP23S17_BANK_0;

static struct mcp23s17_regstate_t ioexp1 = {
	.iodira = 0xff,
	.iodirb = 0xff,
};

static struct mcp23s17_regstate_t ioexp2 = {
	.iodira = 0xff,
	.iodirb = 0xff,
};

char* MCP23S17_reg_to_string(int reg)
{
	switch (reg) {
		case MCP23S17_IODIRA:
			return MCP23S17_REG_TO_STRING(MCP23S17_IODIRA);
		case MCP23S17_IODIRB:
			return MCP23S17_REG_TO_STRING(MCP23S17_IODIRB);
		case MCP23S17_IPOLA:
			return MCP23S17_REG_TO_STRING(MCP23S17_IPOLA);
		case MCP23S17_IPOLB:
			return MCP23S17_REG_TO_STRING(MCP23S17_IPOLB);
		case MCP23S17_GPINTENA:
			return MCP23S17_REG_TO_STRING(MCP23S17_GPINTENA);
		case MCP23S17_GPINTENB:
			return MCP23S17_REG_TO_STRING(MCP23S17_GPINTENB);
		case MCP23S17_DEFVALA:
			return MCP23S17_REG_TO_STRING(MCP23S17_DEFVALA);
		case MCP23S17_DEFVALB:
			return MCP23S17_REG_TO_STRING(MCP23S17_DEFVALB);
		case MCP23S17_INTCONA:
			return MCP23S17_REG_TO_STRING(MCP23S17_INTCONA);
		case MCP23S17_INTCONB:
			return MCP23S17_REG_TO_STRING(MCP23S17_INTCONB);
		case MCP23S17_IOCON1:
			return MCP23S17_REG_TO_STRING(MCP23S17_IOCON1);
		case MCP23S17_IOCON2:
			return MCP23S17_REG_TO_STRING(MCP23S17_IOCON2);
		case MCP23S17_GPPUA:
			return MCP23S17_REG_TO_STRING(MCP23S17_GPPUA);
		case MCP23S17_GPPUB:
			return MCP23S17_REG_TO_STRING(MCP23S17_GPPUB);
		case MCP23S17_INTFA:
			return MCP23S17_REG_TO_STRING(MCP23S17_INTFA);
		case MCP23S17_INTFB:
			return MCP23S17_REG_TO_STRING(MCP23S17_INTFB);
		case MCP23S17_INTCAPA:
			return MCP23S17_REG_TO_STRING(MCP23S17_INTCAPA);
		case MCP23S17_INTCAPB:
			return MCP23S17_REG_TO_STRING(MCP23S17_INTCAPB);
		case MCP23S17_GPIOA:
			return MCP23S17_REG_TO_STRING(MCP23S17_GPIOA);
		case MCP23S17_GPIOB:
			return MCP23S17_REG_TO_STRING(MCP23S17_GPIOB);
		case MCP23S17_OLATA:
			return MCP23S17_REG_TO_STRING(MCP23S17_OLATA);
		case MCP23S17_OLATB:
			return MCP23S17_REG_TO_STRING(MCP23S17_OLATB);
		case MCP23S17_DUMMY:
			return MCP23S17_REG_TO_STRING(MCP23S17_DUMMY);
		default:
			return "NULL";
	}
	return "NULL";
}

uint8_t _read_register(struct mcp23s17_regstate_t *regs, uint8_t reg)
{
	if (CURRENT_MCP_BANK != MCP23S17_BANK_0) {
		/* Update register */
	}

	/* Start at first register */
	uint8_t *tmp_reg = &regs->iodira;
	return (uint8_t)*(tmp_reg + (reg * sizeof(uint8_t)));
}

uint8_t _write_reg(struct mcp23s17_regstate_t *regs, uint8_t reg, uint8_t val)
{
	if (CURRENT_MCP_BANK != MCP23S17_BANK_0) {
		/* Update register */
	}

	/* Start at first register and shift to correct register */
	uint8_t *tmp_reg = &regs->iodira;
	tmp_reg = (tmp_reg + (reg * sizeof(uint8_t)));

	*tmp_reg = val;
	return *tmp_reg;
}

int MCP23S17_process_packet(unsigned char *spi_tx_buffer, unsigned char *spi_rx_buffer)
{
	uint8_t addr = spi_rx_buffer[0];
	uint8_t reg = MCP23S17_convert_reg(CURRENT_MCP_BANK, spi_rx_buffer[1]);
	/* int reg = spi_rx_buffer[1]; */

	struct mcp23s17_regstate_t *curr = NULL;
	if (addr == 0x40 || addr == 0x041) {
		curr = &ioexp1;
	} else if (addr == 0x42 || addr == 0x043) {
		curr = &ioexp2;
	} else {
		printf("Invalid address!\n");
		return -1;
	}

	if (addr & 0x01) {
		printf("%x %x %x\n", spi_rx_buffer[0], spi_rx_buffer[1], spi_rx_buffer[2]);
		printf("Reading register %s of chip 0x%.2x to 0x%.2x\n",
				MCP23S17_reg_to_string(reg), addr, spi_rx_buffer[2]);
		if (reg != MCP23S17_DUMMY) {
			memcpy(spi_tx_buffer, spi_rx_buffer, 3);
			spi_tx_buffer[2] = _read_register(curr, reg);
		}
	} else {
		printf("Changing register %s of chip 0x%.2x to 0x%.2x\n",
				MCP23S17_reg_to_string(reg), addr, spi_rx_buffer[2]);
		_write_reg(curr, reg, spi_rx_buffer[2]);
	}

	return 0;
}
