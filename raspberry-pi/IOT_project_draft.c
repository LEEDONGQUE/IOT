#include <stdio.h>
#include <wiringPi.h>

#define SPI_CH 0
#define ADC_CH1 1 //Gas
#define ADC_CH2 2 //Flame
#define ADC_CH3 3 // temperature
#define ADC_CS 29
#define SPI_SPEED 500000
#define BUZZ_PIN 7



int readADC(int adcChannel) {
    unsigned char buf[3];
    int value;

    buf[0] = 0x06 | ((adcChannel & 0x04) >> 2);
    buf[1] = ((adcChannel & 0x03) << 6);
    buf[2] = 0x00;
    digitalWrite(ADC_CS, 0);
    wiringPiSPIDataRW(SPI_CH, buf, 3);
    buf[1] = 0x0F & buf[1];
    value = (buf[1] << 8) | buf[2];
    digitalWrite(ADC_CS, 1);

    return value;
}
int main(void) {
    int first_value, second_value , third_value;
    if (wiringPiSetup() == -1) return 1;
    if (wiringPiSPISetup(SPI_CH, SPI_SPEED) == -1) return 1;

    first_value = readADC(ADC_CH1) & 0x3F;
    second_value = readADC(ADC_CH2) & 0x3F;
    third_value = readADC(ADC_CH3) &0x3F;

    while (1) {
        printf("Gas : %d\n", first_value);
        printf("Flame : %d\n", second_value);
        printf("Temperature : %d\n", third_value);
        if()
        //pinMode(BUZZ_PIN, OUTPUT);
    }
  

        

       
        
      return 0;
}
