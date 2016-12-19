#ifndef GPS_H
#define GPS_H

// written for SiRF GPS running the NMEA protocol

#include "serial.h"

void gps_init(volatile unsigned char *port, unsigned char num, baud_rate rate);

// returns negative number on error, in which case, out parameters aren't
// defined
int gps_get_time(
    volatile unsigned char *port,
    unsigned char port_num,
    volatile unsigned char *pin,
    unsigned char pin_num,
    baud_rate rate,
    int *year,
    int *month,
    int *day,
    int *hour,
    int *minute,
    int *second
);

#endif // GPS_H
