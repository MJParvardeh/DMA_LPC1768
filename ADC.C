

#include "ADC.h"

#ifdef ADC_GPDMA

void ADCinit()
{
	//ADC_Init(LPC_ADC, 200);	
	LPC_SC->PCONP |=1<<12 ;
	LPC_ADC->ADINTEN=0;
	LPC_SC->PCLKSEL0|=3<<24;
	//configure pin of ADC0 to ADC7
	//LPC_PINCON->PINSEL0&=~(3<<4);
//	LPC_PINCON->PINSEL0|=2<<4;//ADC7	
//	LPC_PINCON->PINSEL0|=2<<6;//ADC6
	LPC_PINCON->PINSEL1|=1<<14;//ADC0
	LPC_PINCON->PINSEL1|=1<<16;//ADC1
	LPC_PINCON->PINSEL1|=1<<18;//ADC2
	LPC_PINCON->PINSEL1|=1<<20;//ADC3
	LPC_PINCON->PINSEL3|=3<<28;//ADC4
	LPC_PINCON->PINSEL3|=3<<30;//ADC5
	//interupt on ch6 &ch7
  LPC_ADC->ADINTEN =0x0FC;
	
	///DMA setting
	
}


#else

void ADCinit()
{
	//ADC_Init(LPC_ADC, 200);	
	LPC_SC->PCONP |=1<<12 ;
	LPC_ADC->ADCR |=(9<<8|1<<21);
	LPC_ADC->ADINTEN=0;
	LPC_SC->PCLKSEL0|=3<<24;
	//configure pin of ADC0 to ADC7
	LPC_PINCON->PINSEL0&=~(3<<4);
	LPC_PINCON->PINSEL0|=2<<4;//ADC7
	
	LPC_PINCON->PINSEL0|=2<<6;//ADC6
	LPC_PINCON->PINSEL1|=1<<14;//ADC0
	LPC_PINCON->PINSEL1|=1<<16;//ADC1
	LPC_PINCON->PINSEL1|=1<<18;//ADC2
	LPC_PINCON->PINSEL1|=1<<20;//ADC3
	LPC_PINCON->PINSEL3|=3<<28;//ADC4
	LPC_PINCON->PINSEL3|=3<<30;//ADC5
	//interupt on ch6 &ch7
  //LPC_ADC->INTEN |=1<<6|1<<7;
	
	///DMA setting
	
}






#endif



int16_t ReadADC(uint16_t ch)
{
	uint16_t timeout;
	uint16_t ADC_VAL;
	uint8_t chrv;
	switch(ch)
	{
		case 0:
			
			chrv=1;
		
		break;
		case 1:
			chrv=1<<1;
		break;
		case 2:
			chrv=1<<2;
		break;
		case 3:
			chrv=1<<3;
		break;
		case 4:
			chrv=1<<4;
		break;
		case 5:
			chrv=1<<5;
		break;
		case 6:
			chrv=64;
		break;
		case 7:
			
			chrv=128;
		break;
		
		
	}

	//deselect other channels
		LPC_ADC->ADCR&=0xFFFFFF00;
	//deselect other channels
		LPC_ADC->ADCR|=chrv; 
		LPC_ADC->ADCR|=1<<24;//start now
	while(((LPC_ADC->ADGDR&0x80000000)==0)&&(timeout<2000))
	{
		timeout++;
	};
	 ADC_VAL=(LPC_ADC->ADGDR >> 4) & 0xfff; 
	LPC_ADC->ADCR&=~(1<<24);
	LPC_ADC->ADCR&=0xFFFFFF00;

return ADC_VAL;
	
}

