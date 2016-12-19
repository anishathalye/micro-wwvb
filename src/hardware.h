#ifndef HARDWARE_H
#define HARDWARE_H

#include "serial.h"
#include <avr/io.h>

#define GPS_BAUD_RATE BAUD_RATE_4800
#define GPS_PORT PORTA
#define GPS_PORT_DDR DDRA
#define GPS_PORT_NUM PA2
#define GPS_PIN PINA
#define GPS_PIN_DDR DDRA
#define GPS_PIN_NUM PB3

#define LED_G_PORT PORTA
#define LED_G_PORT_DDR DDRA
#define LED_G_PORT_NUM PA1
#define LED_B_PORT PORTA
#define LED_B_PORT_DDR DDRA
#define LED_B_PORT_NUM PA7

#endif // HARDWARE_H
