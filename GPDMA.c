
#include "GPDMA.h"


void GPDMASet_Transfer(ChannelConfig_s LPC_CH,uint8_t EnableMode)
{
	
  LPC_GPDMA->DMACConfig|=1;
	LPC_GPDMA->DMACIntErrClr=0xff; //clear all interupts
	LPC_GPDMA->DMACIntTCClear=0xff;//clear all interupts
	GPDMA_CHANNEL(LPC_CH.CHx)->DMACCSrcAddr=LPC_CH.SRCADD;
	GPDMA_CHANNEL(LPC_CH.CHx)->DMACCDestAddr=LPC_CH.DSTADD;
	GPDMA_CHANNEL(LPC_CH.CHx)->DMACCLLI=LPC_CH.LLIADD;
	GPDMA_CHANNEL(LPC_CH.CHx)->DMACCControl=LPC_CH.CHx_Control.CCXControlVAL;
	GPDMA_CHANNEL(LPC_CH.CHx)->DMACCConfig=LPC_CH.CHx_Config.CCXConfiqVAL;
	if(EnableMode==ENABLED)	
		GPDMA_CHANNEL(LPC_CH.CHx)->DMACCConfig|=EnableMode;
	else
		GPDMA_CHANNEL(LPC_CH.CHx)->DMACCConfig&=~(EnableMode);
	
//	while(((GPDMA_CHANNEL(LPC_CH.CHx)->DMACCConfig)&(17<<1))==1);
		
}






void GPDMA_UART0_TX_SEND(Channels_e Channel,uint8_t *Buf,uint16_t Size)
{
	
	ChannelConfig_s UART_TX_DMA;
	UART_TX_DMA.CHx=Channel;
	UART_TX_DMA.CHx_Config.CCXConfiqREG.TransferType=MTOP;
	UART_TX_DMA.CHx_Config.CCXConfiqREG.SrcPeripheral=0;//SRC is memory so it is not considered	
	UART_TX_DMA.CHx_Config.CCXConfiqREG.DestPeripheral=UART0TX;
	UART_TX_DMA.CHx_Config.CCXConfiqREG.IEM=0;
//	UART_TX_DMA.CHx_Config.CCXConfiqVAL=(((DISABLED)|(0<<1)|(UART0TX<<6)|(MTOP<<11)));
	UART_TX_DMA.CHx_Control.CCXControlREG.DBSize=B_1B;
	UART_TX_DMA.CHx_Control.CCXControlREG.DWidth=BYTE;
	UART_TX_DMA.CHx_Control.CCXControlREG.DI=NOTINCREMENTED;
	UART_TX_DMA.CHx_Control.CCXControlREG.SBSize=B_1B;
	UART_TX_DMA.CHx_Control.CCXControlREG.SI=INCREMENT;
	UART_TX_DMA.CHx_Control.CCXControlREG.SWidth=BYTE;
	UART_TX_DMA.CHx_Control.CCXControlREG.TransferSize=Size;
//	UART_TX_DMA.CHx_Control.CCXControlVAL=((Size)|(B_1B<<12)|(B_1B<<15)|(BYTE<<18)|(BYTE<<21)|(INCREMENT<<26)|(NOTINCREMENTED<<27)|(DISABLED<<31));
	UART_TX_DMA.DSTADD=(uint32_t )&(LPC_UART0->THR);
  UART_TX_DMA.SRCADD=(uint32_t )Buf;
	UART_TX_DMA.LLIADD=0;
	
	
	GPDMASet_Transfer(UART_TX_DMA,ENABLED);
	
}



void GPDMA_UART0_RX_Receive(Channels_e Channel,uint8_t *Buf,uint16_t Size)
{
	ChannelConfig_s UART_RX_DMA;
	UART_RX_DMA.CHx=Channel;
	UART_RX_DMA.CHx_Config.CCXConfiqREG.TransferType=PTOM;
	UART_RX_DMA.CHx_Config.CCXConfiqREG.SrcPeripheral=0;//SRC is memory so it is not considered	
	UART_RX_DMA.CHx_Config.CCXConfiqREG.DestPeripheral=UART0TX;
	UART_RX_DMA.CHx_Config.CCXConfiqREG.IEM=0;
//	UART_TX_DMA.CHx_Config.CCXConfiqVAL=(((DISABLED)|(0<<1)|(UART0TX<<6)|(MTOP<<11)));
	UART_RX_DMA.CHx_Control.CCXControlREG.DBSize=B_1B;
	UART_RX_DMA.CHx_Control.CCXControlREG.DWidth=BYTE;
	UART_RX_DMA.CHx_Control.CCXControlREG.DI=INCREMENT;
	UART_RX_DMA.CHx_Control.CCXControlREG.SBSize=B_8B;
	UART_RX_DMA.CHx_Control.CCXControlREG.SI=NOTINCREMENTED;
	UART_RX_DMA.CHx_Control.CCXControlREG.SWidth=BYTE;
	UART_RX_DMA.CHx_Control.CCXControlREG.TransferSize=Size;
//	UART_TX_DMA.CHx_Control.CCXControlVAL=((Size)|(B_1B<<12)|(B_1B<<15)|(BYTE<<18)|(BYTE<<21)|(INCREMENT<<26)|(NOTINCREMENTED<<27)|(DISABLED<<31));
	UART_RX_DMA.DSTADD=(uint32_t)Buf;
  UART_RX_DMA.SRCADD=(uint32_t)&(LPC_UART0->RBR);
	UART_RX_DMA.LLIADD=0;

	GPDMASet_Transfer(UART_RX_DMA,ENABLED);
	
}

/*
GPDMA_GET_ADC(uint8_t *Buf,uint16_t Size)
Size should be as follows:
enabled channels number *  
*/

void GPDMA_GET_ADC(Channels_e Channel,uint16_t *Buf,uint16_t Size)
{
	ChannelConfig_s ADC_DMA;
	ADC_DMA.CHx=Channel;
	ADC_DMA.CHx_Config.CCXConfiqREG.TransferType=PTOM;
	ADC_DMA.CHx_Config.CCXConfiqREG.SrcPeripheral=ADC;//SRC is memory so it is not considered	
	ADC_DMA.CHx_Config.CCXConfiqREG.DestPeripheral=0;
	ADC_DMA.CHx_Config.CCXConfiqREG.IEM=0;
//	UART_TX_DMA.CHx_Config.CCXConfiqVAL=(((DISABLED)|(0<<1)|(UART0TX<<6)|(MTOP<<11)));
	ADC_DMA.CHx_Control.CCXControlREG.DBSize=B_8B;
	ADC_DMA.CHx_Control.CCXControlREG.DWidth=HALFWORD;
	ADC_DMA.CHx_Control.CCXControlREG.DI=INCREMENT;
	ADC_DMA.CHx_Control.CCXControlREG.SBSize=B_8B;
	ADC_DMA.CHx_Control.CCXControlREG.SI=INCREMENT;
	ADC_DMA.CHx_Control.CCXControlREG.SWidth=HALFWORD;
	ADC_DMA.CHx_Control.CCXControlREG.TransferSize=Size;
//	UART_TX_DMA.CHx_Control.CCXControlVAL=((Size)|(B_1B<<12)|(B_1B<<15)|(BYTE<<18)|(BYTE<<21)|(INCREMENT<<26)|(NOTINCREMENTED<<27)|(DISABLED<<31));
	
	ADC_DMA.DSTADD=(uint32_t)Buf;
  ADC_DMA.SRCADD=(uint32_t)&(LPC_ADC->ADDR0);
	ADC_DMA.LLIADD=0;	
	
	GPDMASet_Transfer(ADC_DMA,ENABLED);
	LPC_ADC->ADCR |=(0xFC|9<<8|1<<16|1<<21);	
  while(((LPC_GPDMACH2->DMACCConfig)&(1<<17))==1);
	
}
 
