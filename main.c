
#include <stdint.h>
#include "GPIO_LPC17xx.h"
#include "Driver_USART.h"
#include "GPDMA.h"
#include "ADC.h"

extern ARM_DRIVER_USART Driver_USART0;

void myUSART_callback(uint32_t event)
{
  uint32_t mask;
  mask = ARM_USART_EVENT_RECEIVE_COMPLETE  |
         ARM_USART_EVENT_TRANSFER_COMPLETE |
         ARM_USART_EVENT_SEND_COMPLETE     |
         ARM_USART_EVENT_TX_COMPLETE       ;
  if (event & mask) {
    /* Success: Wakeup Thread */
//    osSignalSet(tid_myUART_Thread, 0x01);
	
  }

}

void uart0init()
{
	 static ARM_DRIVER_USART * USARTdrv = &Driver_USART0;
    ARM_DRIVER_VERSION     version;
    ARM_USART_CAPABILITIES drv_capabilities;
    char                   cmd;
 
  #ifdef DEBUG
    version = USARTdrv->GetVersion();
    if (version.api < 0x200)   /* requires at minimum API version 2.00 or higher */
    {                          /* error handling */
        return;
    }
    drv_capabilities = USARTdrv->GetCapabilities();
    if (drv_capabilities.event_tx_complete == 0)
    {                          /* error handling */
        return;
    }
  #endif
 
    /*Initialize the USART driver */
    USARTdrv->Initialize(myUSART_callback);
    /*Power up the USART peripheral */
    USARTdrv->PowerControl(ARM_POWER_FULL);
    /*Configure the USART to 4800 Bits/sec */
    USARTdrv->Control(ARM_USART_MODE_ASYNCHRONOUS |
                      ARM_USART_DATA_BITS_8 |
                      ARM_USART_PARITY_NONE |
                      ARM_USART_STOP_BITS_1 |
                      ARM_USART_FLOW_CONTROL_NONE, 115200);
     
    /* Enable Receiver and Transmitter lines */
    USARTdrv->Control (ARM_USART_CONTROL_TX, 1);
    USARTdrv->Control (ARM_USART_CONTROL_RX, 1);
	
}


 
uint32_t i;
uint8_t buf[14]="Send with DMA";
uint8_t buf1[14]="Recv with DMA";
uint16_t ADCBUF[40];
uint8_t TXBUF[40];
 uint32_t CCControl=((13)|(0<<12)|(0<<15)|(0<<18)|(0<<21)|(1<<26)|(0<<27)|(1<<31));
 uint32_t CCConfig =((0)|(0<<1)|(0<<6)|(8<<6)|(1<<11)) ;
/*void DMA_IRQHandler()
{
	 LPC_GPDMA->DMACIntErrClr=3;
	 LPC_GPDMA->DMACIntTCClear=3;
}*/
int main()
{
	GPIO_SetDir(1,26,1);
	uart0init();
	ADCinit();
	
	
	
	while(1)
	{
	  int i=0;
	  GPIO_PinWrite(1,26,1);
		for( i=0; i<2000000;i++);
		GPIO_PinWrite(1,26,0);
		for( i=0; i<2000000;i++);

		/* 
		//snippet for testing receive and transmit a buffer using a DMA functions
		//connect Uart0_TX to Uart0_Rx externally
		
		GPDMA_UART0_TX_SEND(CH1,TXBUF,12);
		GPDMA_UART0_TX_Receive(CH0,buf1,13);
		
		 */
		//snippet for Reading ADC samples from DMA and sending to UART0_TX with DMA
		GPDMA_GET_ADC(CH2,ADCBUF,6);		

		for( i=0; i<6;i++)
		{
			TXBUF[2*i]=ADCBUF[i]%256;
			TXBUF[2*i+1]=ADCBUF[i]/256;
		}
		 
		GPDMA_UART0_TX_SEND(CH1,TXBUF,12);

		 		 
		 
	}


}





