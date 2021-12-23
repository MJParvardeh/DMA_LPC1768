

#include "lpc17xx.h"

#define ADC_GPDMA    1


#define PACurrent 0
#define MODIndex 1
#define Reserved 2
#define OutputCurrent 3
#define ForwardPower 4
#define ReversePower 5
#define InterVoltage 7
#define PAVoltage    6

void ADCinit();

int16_t ReadADC(uint16_t ch);
