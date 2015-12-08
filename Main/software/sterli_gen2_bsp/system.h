/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'niosGe' in SOPC Builder design 'mi_nios'
 * SOPC Builder design path: ../../mi_nios.sopcinfo
 *
 * Generated: Wed Oct 28 22:07:41 PDT 2015
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x01001820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 80000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x19
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x00800020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 80000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 1
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_DIVISION_ERROR_EXCEPTION
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x19
#define ALT_CPU_NAME "niosGe"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x01001000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x01001820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 80000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x19
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x00800020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 1
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_DIVISION_ERROR_EXCEPTION
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x19
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x01001000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SPI
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __BEMICRO_MAX10_SERIAL_FLASH_CONTROLLER


/*
 * LED configuration
 *
 */

#define ALT_MODULE_CLASS_LED altera_avalon_pio
#define LED_BASE 0x1002040
#define LED_BIT_CLEARING_EDGE_REGISTER 0
#define LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_CAPTURE 0
#define LED_DATA_WIDTH 8
#define LED_DO_TEST_BENCH_WIRING 0
#define LED_DRIVEN_SIM_VALUE 0
#define LED_EDGE_TYPE "NONE"
#define LED_FREQ 50000000
#define LED_HAS_IN 0
#define LED_HAS_OUT 1
#define LED_HAS_TRI 0
#define LED_IRQ -1
#define LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_IRQ_TYPE "NONE"
#define LED_NAME "/dev/LED"
#define LED_RESET_VALUE 0
#define LED_SPAN 16
#define LED_TYPE "altera_avalon_pio"


/*
 * SW configuration
 *
 */

#define ALT_MODULE_CLASS_SW altera_avalon_pio
#define SW_BASE 0x1002050
#define SW_BIT_CLEARING_EDGE_REGISTER 0
#define SW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SW_CAPTURE 0
#define SW_DATA_WIDTH 4
#define SW_DO_TEST_BENCH_WIRING 0
#define SW_DRIVEN_SIM_VALUE 0
#define SW_EDGE_TYPE "NONE"
#define SW_FREQ 50000000
#define SW_HAS_IN 1
#define SW_HAS_OUT 0
#define SW_HAS_TRI 0
#define SW_IRQ -1
#define SW_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SW_IRQ_TYPE "NONE"
#define SW_NAME "/dev/SW"
#define SW_RESET_VALUE 0
#define SW_SPAN 16
#define SW_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "MAX 10"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag"
#define ALT_STDERR_BASE 0x1002108
#define ALT_STDERR_DEV jtag
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag"
#define ALT_STDIN_BASE 0x1002108
#define ALT_STDIN_DEV jtag
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag"
#define ALT_STDOUT_BASE 0x1002108
#define ALT_STDOUT_DEV jtag
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "mi_nios"


/*
 * bl_n configuration
 *
 */

#define ALT_MODULE_CLASS_bl_n altera_avalon_pio
#define BL_N_BASE 0x10020f0
#define BL_N_BIT_CLEARING_EDGE_REGISTER 0
#define BL_N_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BL_N_CAPTURE 0
#define BL_N_DATA_WIDTH 1
#define BL_N_DO_TEST_BENCH_WIRING 0
#define BL_N_DRIVEN_SIM_VALUE 0
#define BL_N_EDGE_TYPE "NONE"
#define BL_N_FREQ 80000000
#define BL_N_HAS_IN 0
#define BL_N_HAS_OUT 1
#define BL_N_HAS_TRI 0
#define BL_N_IRQ -1
#define BL_N_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BL_N_IRQ_TYPE "NONE"
#define BL_N_NAME "/dev/bl_n"
#define BL_N_RESET_VALUE 0
#define BL_N_SPAN 16
#define BL_N_TYPE "altera_avalon_pio"


/*
 * bl_p configuration
 *
 */

#define ALT_MODULE_CLASS_bl_p altera_avalon_pio
#define BL_P_BASE 0x10020e0
#define BL_P_BIT_CLEARING_EDGE_REGISTER 0
#define BL_P_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BL_P_CAPTURE 0
#define BL_P_DATA_WIDTH 1
#define BL_P_DO_TEST_BENCH_WIRING 0
#define BL_P_DRIVEN_SIM_VALUE 0
#define BL_P_EDGE_TYPE "NONE"
#define BL_P_FREQ 80000000
#define BL_P_HAS_IN 0
#define BL_P_HAS_OUT 1
#define BL_P_HAS_TRI 0
#define BL_P_IRQ -1
#define BL_P_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BL_P_IRQ_TYPE "NONE"
#define BL_P_NAME "/dev/bl_p"
#define BL_P_RESET_VALUE 0
#define BL_P_SPAN 16
#define BL_P_TYPE "altera_avalon_pio"


/*
 * flash configuration
 *
 */

#define ALT_MODULE_CLASS_flash BeMicro_Max10_serial_flash_controller
#define FLASH_BASE 0x1001000
#define FLASH_IRQ 3
#define FLASH_IRQ_INTERRUPT_CONTROLLER_ID 0
#define FLASH_NAME "/dev/flash"
#define FLASH_REGISTER_OFFSET 1024
#define FLASH_SPAN 2048
#define FLASH_TYPE "BeMicro_Max10_serial_flash_controller"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag configuration
 *
 */

#define ALT_MODULE_CLASS_jtag altera_avalon_jtag_uart
#define JTAG_BASE 0x1002108
#define JTAG_IRQ 1
#define JTAG_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_NAME "/dev/jtag"
#define JTAG_READ_DEPTH 64
#define JTAG_READ_THRESHOLD 8
#define JTAG_SPAN 8
#define JTAG_TYPE "altera_avalon_jtag_uart"
#define JTAG_WRITE_DEPTH 64
#define JTAG_WRITE_THRESHOLD 8


/*
 * lcd32_data configuration
 *
 */

#define ALT_MODULE_CLASS_lcd32_data altera_avalon_pio
#define LCD32_DATA_BASE 0x10020c0
#define LCD32_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define LCD32_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD32_DATA_CAPTURE 0
#define LCD32_DATA_DATA_WIDTH 16
#define LCD32_DATA_DO_TEST_BENCH_WIRING 0
#define LCD32_DATA_DRIVEN_SIM_VALUE 0
#define LCD32_DATA_EDGE_TYPE "NONE"
#define LCD32_DATA_FREQ 80000000
#define LCD32_DATA_HAS_IN 0
#define LCD32_DATA_HAS_OUT 0
#define LCD32_DATA_HAS_TRI 1
#define LCD32_DATA_IRQ -1
#define LCD32_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD32_DATA_IRQ_TYPE "NONE"
#define LCD32_DATA_NAME "/dev/lcd32_data"
#define LCD32_DATA_RESET_VALUE 0
#define LCD32_DATA_SPAN 16
#define LCD32_DATA_TYPE "altera_avalon_pio"


/*
 * lcd_cs configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_cs altera_avalon_pio
#define LCD_CS_BASE 0x1002060
#define LCD_CS_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_CS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_CS_CAPTURE 0
#define LCD_CS_DATA_WIDTH 1
#define LCD_CS_DO_TEST_BENCH_WIRING 0
#define LCD_CS_DRIVEN_SIM_VALUE 0
#define LCD_CS_EDGE_TYPE "NONE"
#define LCD_CS_FREQ 80000000
#define LCD_CS_HAS_IN 0
#define LCD_CS_HAS_OUT 1
#define LCD_CS_HAS_TRI 0
#define LCD_CS_IRQ -1
#define LCD_CS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_CS_IRQ_TYPE "NONE"
#define LCD_CS_NAME "/dev/lcd_cs"
#define LCD_CS_RESET_VALUE 0
#define LCD_CS_SPAN 16
#define LCD_CS_TYPE "altera_avalon_pio"


/*
 * lcd_rd configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_rd altera_avalon_pio
#define LCD_RD_BASE 0x10020d0
#define LCD_RD_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_RD_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_RD_CAPTURE 0
#define LCD_RD_DATA_WIDTH 1
#define LCD_RD_DO_TEST_BENCH_WIRING 0
#define LCD_RD_DRIVEN_SIM_VALUE 0
#define LCD_RD_EDGE_TYPE "NONE"
#define LCD_RD_FREQ 80000000
#define LCD_RD_HAS_IN 0
#define LCD_RD_HAS_OUT 1
#define LCD_RD_HAS_TRI 0
#define LCD_RD_IRQ -1
#define LCD_RD_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_RD_IRQ_TYPE "NONE"
#define LCD_RD_NAME "/dev/lcd_rd"
#define LCD_RD_RESET_VALUE 0
#define LCD_RD_SPAN 16
#define LCD_RD_TYPE "altera_avalon_pio"


/*
 * lcd_rs configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_rs altera_avalon_pio
#define LCD_RS_BASE 0x1002080
#define LCD_RS_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_RS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_RS_CAPTURE 0
#define LCD_RS_DATA_WIDTH 1
#define LCD_RS_DO_TEST_BENCH_WIRING 0
#define LCD_RS_DRIVEN_SIM_VALUE 0
#define LCD_RS_EDGE_TYPE "NONE"
#define LCD_RS_FREQ 80000000
#define LCD_RS_HAS_IN 0
#define LCD_RS_HAS_OUT 1
#define LCD_RS_HAS_TRI 0
#define LCD_RS_IRQ -1
#define LCD_RS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_RS_IRQ_TYPE "NONE"
#define LCD_RS_NAME "/dev/lcd_rs"
#define LCD_RS_RESET_VALUE 0
#define LCD_RS_SPAN 16
#define LCD_RS_TYPE "altera_avalon_pio"


/*
 * lcd_wr configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_wr altera_avalon_pio
#define LCD_WR_BASE 0x10020b0
#define LCD_WR_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_WR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_WR_CAPTURE 0
#define LCD_WR_DATA_WIDTH 1
#define LCD_WR_DO_TEST_BENCH_WIRING 0
#define LCD_WR_DRIVEN_SIM_VALUE 0
#define LCD_WR_EDGE_TYPE "NONE"
#define LCD_WR_FREQ 80000000
#define LCD_WR_HAS_IN 0
#define LCD_WR_HAS_OUT 1
#define LCD_WR_HAS_TRI 0
#define LCD_WR_IRQ -1
#define LCD_WR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_WR_IRQ_TYPE "NONE"
#define LCD_WR_NAME "/dev/lcd_wr"
#define LCD_WR_RESET_VALUE 0
#define LCD_WR_SPAN 16
#define LCD_WR_TYPE "altera_avalon_pio"


/*
 * reset configuration
 *
 */

#define ALT_MODULE_CLASS_reset altera_avalon_pio
#define RESET_BASE 0x10020a0
#define RESET_BIT_CLEARING_EDGE_REGISTER 0
#define RESET_BIT_MODIFYING_OUTPUT_REGISTER 0
#define RESET_CAPTURE 0
#define RESET_DATA_WIDTH 1
#define RESET_DO_TEST_BENCH_WIRING 0
#define RESET_DRIVEN_SIM_VALUE 0
#define RESET_EDGE_TYPE "NONE"
#define RESET_FREQ 80000000
#define RESET_HAS_IN 0
#define RESET_HAS_OUT 1
#define RESET_HAS_TRI 0
#define RESET_IRQ -1
#define RESET_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RESET_IRQ_TYPE "NONE"
#define RESET_NAME "/dev/reset"
#define RESET_RESET_VALUE 0
#define RESET_SPAN 16
#define RESET_TYPE "altera_avalon_pio"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x800000
#define SDRAM_CAS_LATENCY 2
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x16
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 8
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 12
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 8388608
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.4
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 15.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 15.0
#define SDRAM_T_WR 14.0


/*
 * spi_touch configuration
 *
 */

#define ALT_MODULE_CLASS_spi_touch altera_avalon_spi
#define SPI_TOUCH_BASE 0x1002020
#define SPI_TOUCH_CLOCKMULT 1
#define SPI_TOUCH_CLOCKPHASE 0
#define SPI_TOUCH_CLOCKPOLARITY 0
#define SPI_TOUCH_CLOCKUNITS "Hz"
#define SPI_TOUCH_DATABITS 8
#define SPI_TOUCH_DATAWIDTH 16
#define SPI_TOUCH_DELAYMULT "1.0E-9"
#define SPI_TOUCH_DELAYUNITS "ns"
#define SPI_TOUCH_EXTRADELAY 0
#define SPI_TOUCH_INSERT_SYNC 0
#define SPI_TOUCH_IRQ 0
#define SPI_TOUCH_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SPI_TOUCH_ISMASTER 1
#define SPI_TOUCH_LSBFIRST 0
#define SPI_TOUCH_NAME "/dev/spi_touch"
#define SPI_TOUCH_NUMSLAVES 1
#define SPI_TOUCH_PREFIX "spi_"
#define SPI_TOUCH_SPAN 32
#define SPI_TOUCH_SYNC_REG_DEPTH 2
#define SPI_TOUCH_TARGETCLOCK 1000000u
#define SPI_TOUCH_TARGETSSDELAY "0.0"
#define SPI_TOUCH_TYPE "altera_avalon_spi"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x1002100
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1446094586
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x1002000
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 50000000
#define TIMER_IRQ 2
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 49999
#define TIMER_MULT 0.001
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "ms"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 1000
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"


/*
 * touch_cs configuration
 *
 */

#define ALT_MODULE_CLASS_touch_cs altera_avalon_pio
#define TOUCH_CS_BASE 0x1002070
#define TOUCH_CS_BIT_CLEARING_EDGE_REGISTER 0
#define TOUCH_CS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TOUCH_CS_CAPTURE 0
#define TOUCH_CS_DATA_WIDTH 1
#define TOUCH_CS_DO_TEST_BENCH_WIRING 0
#define TOUCH_CS_DRIVEN_SIM_VALUE 0
#define TOUCH_CS_EDGE_TYPE "NONE"
#define TOUCH_CS_FREQ 80000000
#define TOUCH_CS_HAS_IN 0
#define TOUCH_CS_HAS_OUT 1
#define TOUCH_CS_HAS_TRI 0
#define TOUCH_CS_IRQ -1
#define TOUCH_CS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TOUCH_CS_IRQ_TYPE "NONE"
#define TOUCH_CS_NAME "/dev/touch_cs"
#define TOUCH_CS_RESET_VALUE 0
#define TOUCH_CS_SPAN 16
#define TOUCH_CS_TYPE "altera_avalon_pio"


/*
 * touch_irq configuration
 *
 */

#define ALT_MODULE_CLASS_touch_irq altera_avalon_pio
#define TOUCH_IRQ_BASE 0x1002090
#define TOUCH_IRQ_BIT_CLEARING_EDGE_REGISTER 0
#define TOUCH_IRQ_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TOUCH_IRQ_CAPTURE 0
#define TOUCH_IRQ_DATA_WIDTH 1
#define TOUCH_IRQ_DO_TEST_BENCH_WIRING 0
#define TOUCH_IRQ_DRIVEN_SIM_VALUE 0
#define TOUCH_IRQ_EDGE_TYPE "NONE"
#define TOUCH_IRQ_FREQ 80000000
#define TOUCH_IRQ_HAS_IN 1
#define TOUCH_IRQ_HAS_OUT 0
#define TOUCH_IRQ_HAS_TRI 0
#define TOUCH_IRQ_IRQ -1
#define TOUCH_IRQ_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TOUCH_IRQ_IRQ_TYPE "NONE"
#define TOUCH_IRQ_NAME "/dev/touch_irq"
#define TOUCH_IRQ_RESET_VALUE 0
#define TOUCH_IRQ_SPAN 16
#define TOUCH_IRQ_TYPE "altera_avalon_pio"


/*
 * ucosii configuration
 *
 */

#define OS_ARG_CHK_EN 1
#define OS_CPU_HOOKS_EN 1
#define OS_DEBUG_EN 1
#define OS_EVENT_NAME_SIZE 32
#define OS_FLAGS_NBITS 16
#define OS_FLAG_ACCEPT_EN 1
#define OS_FLAG_DEL_EN 1
#define OS_FLAG_EN 1
#define OS_FLAG_NAME_SIZE 32
#define OS_FLAG_QUERY_EN 1
#define OS_FLAG_WAIT_CLR_EN 1
#define OS_LOWEST_PRIO 20
#define OS_MAX_EVENTS 60
#define OS_MAX_FLAGS 20
#define OS_MAX_MEM_PART 60
#define OS_MAX_QS 20
#define OS_MAX_TASKS 10
#define OS_MBOX_ACCEPT_EN 1
#define OS_MBOX_DEL_EN 1
#define OS_MBOX_EN 1
#define OS_MBOX_POST_EN 1
#define OS_MBOX_POST_OPT_EN 1
#define OS_MBOX_QUERY_EN 1
#define OS_MEM_EN 1
#define OS_MEM_NAME_SIZE 32
#define OS_MEM_QUERY_EN 1
#define OS_MUTEX_ACCEPT_EN 1
#define OS_MUTEX_DEL_EN 1
#define OS_MUTEX_EN 1
#define OS_MUTEX_QUERY_EN 1
#define OS_Q_ACCEPT_EN 1
#define OS_Q_DEL_EN 1
#define OS_Q_EN 1
#define OS_Q_FLUSH_EN 1
#define OS_Q_POST_EN 1
#define OS_Q_POST_FRONT_EN 1
#define OS_Q_POST_OPT_EN 1
#define OS_Q_QUERY_EN 1
#define OS_SCHED_LOCK_EN 1
#define OS_SEM_ACCEPT_EN 1
#define OS_SEM_DEL_EN 1
#define OS_SEM_EN 1
#define OS_SEM_QUERY_EN 1
#define OS_SEM_SET_EN 1
#define OS_TASK_CHANGE_PRIO_EN 1
#define OS_TASK_CREATE_EN 1
#define OS_TASK_CREATE_EXT_EN 1
#define OS_TASK_DEL_EN 1
#define OS_TASK_IDLE_STK_SIZE 512
#define OS_TASK_NAME_SIZE 32
#define OS_TASK_PROFILE_EN 1
#define OS_TASK_QUERY_EN 1
#define OS_TASK_STAT_EN 1
#define OS_TASK_STAT_STK_CHK_EN 1
#define OS_TASK_STAT_STK_SIZE 512
#define OS_TASK_SUSPEND_EN 1
#define OS_TASK_SW_HOOK_EN 1
#define OS_TASK_TMR_PRIO 0
#define OS_TASK_TMR_STK_SIZE 512
#define OS_THREAD_SAFE_NEWLIB 1
#define OS_TICKS_PER_SEC TIMER_TICKS_PER_SEC
#define OS_TICK_STEP_EN 1
#define OS_TIME_DLY_HMSM_EN 1
#define OS_TIME_DLY_RESUME_EN 1
#define OS_TIME_GET_SET_EN 1
#define OS_TIME_TICK_HOOK_EN 1
#define OS_TMR_CFG_MAX 16
#define OS_TMR_CFG_NAME_SIZE 16
#define OS_TMR_CFG_TICKS_PER_SEC 10
#define OS_TMR_CFG_WHEEL_SIZE 2
#define OS_TMR_EN 0

#endif /* __SYSTEM_H_ */
