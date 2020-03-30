###################################################################################################
#                                                                                                 #
# @file meson.build                                                                               #
# @brief  Top level meson build                                                                   #
# @author Bram Vlerick <bram.vlerick@openpixelsystems.org>                                        #
# @version v1.0                                                                                   #
# @date 2020-03-30                                                                                #
#                                                                                                 #
###################################################################################################

project('spi-stub', 'c')

###################################################################################################

# Compiler arguments
c_args = [
	'-mcpu=cortex-m7',
	'-std=gnu11',
	'-g3',
	'-c',
	'-ffunction-sections',
	'-fdata-sections',
	'-fstack-usage',
	'-mthumb',
	'-mfpu=fpv5-d16',
	'-mfloat-abi=hard',
	'--specs=nano.specs',
	'-DUSE_HAL_DRIVER',
	'-DSTM32F767xx',
	'-Wall',
	'-Wextra']

c_args += get_option('buildtype') == 'release' ? '-DNDEBUG' : '-DDEBUG=1 -g -ggdb'

# Linker arguments
link_args = [
	'-mcpu=cortex-m7',
	'--specs=nosys.specs',
	'-Wl,-Map=spi_stub.map',
	'-Wl,--gc-sections',
	'-static',
	'-mfpu=fpv5-d16',
	'-mfloat-abi=hard',
	'-mthumb',
	'-fno-exceptions',
	'-fno-common',
	'-ffunction-sections',
	'-fdata-sections',
	'-Wl,--start-group',
	'-lc',
	'-lm',
	'-Wl,--end-group',
	'--specs=nano.specs',
	'-flto',
	'--specs=rdimon.specs',
	'-lrdimon']

###################################################################################################

# Include directories
inc_dirs = include_directories([
  './Inc',
  './Drivers/CMSIS/Include',
  './Drivers/CMSIS/Device/ST/STM32F7xx/Include',
  './Drivers/STM32F7xx_HAL_Driver/Inc/Legacy',
  './Drivers/STM32F7xx_HAL_Driver/Inc',
])

###################################################################################################

# Static Source files
driver_srcs = files([
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi_ex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.c',
  'Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usb.c',
  ])

###################################################################################################


# Startup files
startup_src = files(['./startup_stm32f767xx.S'])

###################################################################################################

# Linker files
linkfiles = files(['./STM32F767ZITx_FLASH.ld'])
foreach linkfile : linkfiles
  link_args += ['-T@0@/@1@'.format(meson.current_source_dir(), linkfile)]
endforeach

###################################################################################################

# Include src dir
subdir('Src')

# Build main executable
spi_stub = executable('spi-stub', [user_srcs, startup_src, driver_srcs],
			name_suffix: 'elf',
			c_args : c_args,
			link_args : link_args,
			include_directories : inc_dirs)

###################################################################################################

# Find extra programs/binaries
gdb      = '@0@'.format(find_program('gdb').path())
objcopy  = '@0@'.format(find_program('objcopy').path())
terminal = '@0@'.format(find_program('gnome-terminal',required:false).path())
openocd  = '@0@'.format(find_program('openocd', required:false).path())

# Generate BIN file
mainbin = custom_target(
  'spi-stub.elf.bin',
  output           : ['spi-stub.elf.bin'],
  build_by_default : true,
  command	   : [objcopy, '-O', 'binary', '-R', '.sram2', 'spi-stub.elf', 'spi-stub.elf.bin'],
  depends          : [spi_stub])

###################################################################################################

#**********************************************************************************************
# Find all header files
#**********************************************************************************************
tool_find = find_program('find')
c = run_command(tool_find, meson.source_root()+'/Inc',
                '-type', 'f', '-name', '*.h*', '-printf', '%p|')
headers = c.stdout().strip().split('|')

#**********************************************************************************************
# Remove false positives
#**********************************************************************************************
p_headers = []
foreach l : headers
  if l != ''
    p_headers += l
  endif
endforeach

# Extra run targets
run_target('gdb',
           command : ['sh', 'scripts/gdb.sh'])

run_target('openocd',
           command : ['sh', 'scripts/openocd.sh'])

run_target('debug',
	   command : ['sh', 'scripts/debug.sh'])

run_target('cscope', command : ['cscope', '-b', '-q', user_srcs, startup_src, driver_srcs])
run_target('ctags', command : ['ctags', '--exclude=*.js','--exclude=*.htm', '--exclude=*.html', '--exclude=*.css','-R', meson.source_root()])

#
