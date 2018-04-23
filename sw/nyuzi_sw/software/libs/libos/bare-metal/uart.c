//
// Copyright 2011-2015 Jeff Bush
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "registers.h"
#include "uart.h"

void init_uart( void )
{
	// enable interrupt and reset the fifos
	// since it is a write only register, it is sufficient to do a write 
	// reserved bits are protected by hardware
	REGISTERS[REG_UART_CTRL] = UART_CTRL_ENABLE_INTR | UART_CTRL_RST_TX_FIFO | UART_CTRL_RST_RX_FIFO;
}

void write_uart(char ch)
{
    while ((REGISTERS[REG_UART_STATUS] & UART_TX_FIFO_FULL) == 1) // not ready, as long as there is no place in fifo
        ;	// Wait for space

    REGISTERS[REG_UART_TX] = ch;
}

unsigned char read_uart(void)
{
    while ((REGISTERS[REG_UART_STATUS] & UART_RX_READY) == 0)
        ;	// Wait for characters to be available

    return REGISTERS[REG_UART_RX];
}

