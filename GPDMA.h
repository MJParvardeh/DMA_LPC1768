
#include <stdint.h>
#include "LPC17xx.h"
#ifndef  _GPDMA_H_
#define  _GPDMA_H_


/*
Base Addresses

*/


// GPDMA register structure

#define GPDMA_CHANNEL(n)  ((LPC_GPDMACH_TypeDef *) ((0x50004100) + (n * 0x20)))
#define LPC17xx_GPDMA     ((GPDMA_REG         *) LPC_GPDMA_BASE)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
DMA Connections
The connection of the GPDMA to the supported peripheral devices depends on the DMA
functions implemented in those peripherals. Table 544(user manual) shows the DMA Request numbers
used by the supported peripherals. UART and timer DMA requests on channels 8 through
15 are chosen via the DMAREQSEL register, see Section 31.5.15(user manual).
*/

#define     SSP0TX         0
#define     SSP0RX         1
#define     SSP1TX         2
#define     SSP1RX         3
#define     ADC            4
#define     I2SCHANNEL0    5
#define     I2SCHANNEL1    6
#define     DAC            7
#define     UART0TX        8
#define     MAT0_0         8
#define     UART0RX        9
#define     MAT0_1         9
#define     UART1TX        10
#define     MAT1_0         10
#define     UART1RX        11
#define     MAT1_1         11
#define     UART2TX        12
#define     MAT2_0         12
#define     UART2RX        13
#define     MAT2_1         13
#define     UART3TX        14
#define     MAT3_0         14
#define     UART3RX        15
#define     MAT3_1         15

//////////////////////////////////////////////////////////////////////////////////////////////////

/*
DMA Transfer type
Table 566(user manual) lists the bit values of the transfer type bits identified in Table 565.
Transfer type bits:
*/
#define     MTOM            0
#define     MTOP            1
#define     PTOM            2
#define     PTOP            3
/////////////////////////////////////////////////////////////////////////////////////////////////


/*
SBSize
Source burst size. Indicates the number of transfers that make up a source burst. This value must be
set to the burst size of the source peripheral, or if the source is memory, to the memory boundary
size. The burst size is the amount of data that is transferred when the DMACBREQ signal goes
active in the source peripheral.

DBSize
Destination burst size. Indicates the number of transfers that make up a destination burst transfer
request. This value must be set to the burst size of the destination peripheral or, if the destination is
memory, to the memory boundary size. The burst size is the amount of data that is transferred when
the DMACBREQ signal goes active in the destination peripheral.

*/

#define     B_1B            0
#define     B_4B            1
#define     B_8B            2
#define     B_16B           3
#define     B_32B           4
#define     B_64B           5
#define     B_128B          6
#define     B_256B          7

/////////////////////////////////////////////////////////////////////////////////////////////////



/*
Width
Source transfer width. Transfers wider than the AHB master bus width are illegal. The source and
destination widths can be different from each other. The hardware automatically packs and unpacks
the data as required.


Destination transfer width. Transfers wider than the AHB master bus width are not supported. The
source and destination widths can be different from each other. The hardware automatically packs
and unpacks the data as required.
*/
#define     BYTE          0
#define     HALFWORD      1
#define     WORD          2
/////////////////////////////////////////////////////////////////////////////////////////////////



/*
Source increment
Destination increment
Terminal count interrupt enable bit.
Halt: The contents of the channel FIFO are drained.
Active:
0 = there is no data in the FIFO of the channel.
1 = the channel FIFO has data.
*/
#define     INCREMENT             1
#define     NOTINCREMENTED        0
#define     ENABLED               1
#define     DISABLED              0
#define     HALTED                1
#define     NOTHALTED             1
/////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum 
{
	CH0=0,CH1,CH2,
	CH3,CH4,CH5,
	CH6,CH7
}Channels_e;

typedef union 
{
	struct 
	{
		uint32_t CE             :1;
		uint32_t SrcPeripheral  :5;
		uint32_t DestPeripheral :5;
		uint32_t TransferType  	:3;
		uint32_t IEM            :1;
		uint32_t Lock           :1;
		const uint32_t Active   :1;
		uint32_t Halt           :1;
		uint32_t Reserved       :13;
	}CCXConfiqREG;
	
	uint32_t CCXConfiqVAL;		
}GPDMA_CCxConfig_u;


typedef union 
{
	struct 
	{
		uint32_t TransferSize   :12;
		uint32_t SBSize  				:3;
		uint32_t DBSize 				:3;
		uint32_t SWidth  				:3;
		uint32_t DWidth         :3;
		uint32_t Reserved       :2;
		uint32_t SI   					:1;
		uint32_t DI             :1;
		uint32_t Prot1          :1;
		uint32_t Prot2          :1;
		uint32_t Prot3          :1;
		uint32_t I              :1;	
	}CCXControlREG;
	
	uint32_t CCXControlVAL;	
}GPDMA_CCxControl_u;

typedef struct 
{
	Channels_e CHx;
	GPDMA_CCxControl_u CHx_Control;
	GPDMA_CCxConfig_u  CHx_Config;
	uint32_t SRCADD;
	uint32_t DSTADD;
	uint32_t LLIADD;

}ChannelConfig_s;




void GPDMASet_Transfer(ChannelConfig_s LPC_CH,uint8_t EnableMode);
void GPDMA_UART0_TX_SEND(uint8_t *Buf,uint16_t Size);
void GPDMA_UART0_RX_Receive(uint8_t *Buf,uint16_t Size);
void GPDMA_GET_ADC(uint16_t *Buf,uint16_t Size);


#endif
