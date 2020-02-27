/*
 * GPIO.h
 *
 *  Created on: Feb 17, 2020
 *      Author: ali zewail
 */

#ifndef GPIO_H_
#define GPIO_H_


typedef enum {MODE_IN = 0x00, MODE_OUT = 0xff, MODE_AF = 0x3} gpio_mode_t;
typedef enum {PORTA, PORTB, PORTC,PORTD,PORTE,PORTF} gpio_port_CTL_t;
typedef enum
{
    PORTA_AHB = 0x40058000, PORTA_APB = 0x40004000

    , PORTB_AHB = 0x40059000, PORTB_APB = 0x40005000

    , PORTC_AHB = 0x4005A000, PORTC_APB = 0x40006000

    , PORTD_AHB = 0x4005B000, PORTD_APB = 0x40007000

    , PORTE_AHB = 0x4005C000, PORTE_APB = 0x40024000

    , PORTF_APB = 0x40025000, PORTF_AHB = 0x4005D000}gpio_port_t;

typedef enum {APB=0,AHB=1} gpio_bus_t;
typedef enum {Drive_2mA=0x500, Drive_4mA=0x504, Drive_8mA=0x508, Drive_8mA_Selw=0x508} gpio_drive_t;
typedef enum {Pad_PU=0x510,Pad_PD=0x514,PAD_NPU_NPD,PAD_OD=0x50C} gpio_pad_t;


//Functions prototype

void GPIOBusSet(gpio_port_CTL_t port,gpio_bus_t bus);
gpio_bus_t GPIOBusGet(gpio_port_CTL_t port);


void GPIOClockSet(gpio_port_CTL_t port);
void GPIOClockRst(gpio_port_CTL_t port);
uint8 GPIOClockGet(gpio_port_CTL_t port);

void GPIODirModeSet(gpio_port_t port, uint8 pins, gpio_mode_t Mode);
uint8 GPIODirGet(gpio_port_t port, uint8 pins);
uint8 GPIOModeGet(gpio_port_t port , uint8 pins);

void GPIOPadSet(gpio_port_t port, uint8 pins, gpio_drive_t str, gpio_pad_t pad);

uint8 GPIOPadDrive2_mAGet(gpio_port_t port, uint8 pins);
uint8 GPIOPadDrive4_mAGet(gpio_port_t port, uint8 pins);
uint8 GPIOPadDrive8_mAGet(gpio_port_t port, uint8 pins);

uint8 GPIOPadOpenDrainGet(gpio_port_t port, uint8 pins);
uint8 GPIOPadPullUpGet(gpio_port_t port, uint8 pins);
uint8 GPIOPadPullDownGet(gpio_port_t port, uint8 pins);

uint8 GPIORead(gpio_port_t port, uint8 pins);
void GPIOWrite(gpio_port_t port, uint8 pins, uint8 data);



#endif /* GPIO_H_ */
