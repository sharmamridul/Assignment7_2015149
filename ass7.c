#include <avr/io.h>
#include <util/delay.h>

 
#define LTHRES 500
#define RTHRES 500
 
// initializing adc
void adc_init()
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128, 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
 
// read adc value
uint16_t adc_read(uint8_t ch)
{
    // ANDing of selected channel with '7' will always keep the value of 'ch' between 0 and 7
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch;     // clears the bottom 3 bits before ORing
 
    // to start single conversion write '1' to ADSC
    ADCSRA |= (1<<ADSC);
 
    // (WAIT: for conversion completion), ADSC becomes '0' again
    // till then, run loop continuously
    while(ADCSRA & (1<<ADSC));
 
    return (ADC);
}

int main()
{
    uint16_t adc_result0, adc_result1;
    while(1)
    {
        adc_result0 = adc_read(0);      // read adc value at PA0
        adc_result1 = adc_read(1);      // read adc value at PA1
        if(adc_result0>LTHRES)
            {
                //LED Off
            }
        else
            {
                //LED On
            }    
        if(adc_result1>RTHRES)
            {
                //LED On 
            }
        else
            {
                //LED Off
            }
    }

}