#include "STD_TYPES.h"
#include"RegMap.h"
#include"GPIO.h"

#define Timer_RCGC (*((volatile uint32*) 0x400FE604))
#define WTimer_RCGC (*((volatile uint32*) 0x400FE65C))
#define Timer0_CTL (*((volatile uint32*) 0x4003000C))
#define Timer0_CFG (*((volatile uint32*) 0x40030000))
#define Timer0_AMR (*((volatile uint32*) 0x40030004))
#define Timer0_AILR (*((volatile uint32*) 0x40030028))
#define Timer0_IMR (*((volatile uint32*) 0x40030018))
#define Timer0_ICR (*((volatile uint32*) 0x40030024))
#define Timer0_PR (*((volatile uint32*) 0x40030038))

#define EN0 (*((volatile uint32*) 0xE000E100))
#define PRI4 (*((volatile uint32*) 0xE000E410))


uint8 flag = 1;



int main(void)

{
    GPIOBusSet(PORTF, AHB);
    GPIOClockSet(PORTF);
    GPIODirModeSet(PORTF_AHB, 0b00001110, MODE_OUT);

    Timer_RCGC |= (1 << 0);
//disable TEN in CTL
    Timer0_CTL &= ~(1 << 0);

//(GPTMCFG) with a value of 0x0000.0000
    Timer0_CFG = 0x04;

//TnMR IN MR WITH 0X2
    Timer0_AMR |= (2 << 0);

    //Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
    Timer0_AMR |= (1 << 4);

    //prescaler
    Timer0_PR = 255;

//start value into the GPTM Timer n Interval Load Register (GPTMTnILR)
    Timer0_AILR = 0xFFFF;

    //status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    Timer0_ICR |= (1 << 0);

    //Set the appropriate bits in the GPTM Interrupt Mask Register(GPTMIMR).
    Timer0_IMR |= (1 << 0);

    //Set the TnEN bit in the GPTMCTL register to enable the timer and start counting
    Timer0_CTL |= (1 << 0);
    //Enable interrupt
    EN0 |= (1 << 19);

    /*//set priority
     PRI4 |= (3 << 29);
     */

    GPIOWrite(PORTF_AHB, 0b00001110, 0b00000010);

    while (1)
    {
    }
    return 0;
}

void Timer0ISR(void)
{
    volatile uint32 read;
    if (flag == 1)
    {
        GPIOWrite(PORTF_AHB, 0b00001110, 0b00000100);
        flag = 0;
    }
    else if (flag == 0)
    {
        GPIOWrite(PORTF_AHB, 0b00001110, 0b00001000);
        flag = 1;

    }
    Timer0_ICR = 0x1;
    read = Timer0_ICR;
}

