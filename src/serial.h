#ifndef SERIAL_H
#define SERIAL_H

typedef enum {
    BAUD_RATE_57600,
    BAUD_RATE_38400,
    BAUD_RATE_19200,
    BAUD_RATE_9600,
    BAUD_RATE_4800
} baud_rate;

char serial_get_char(
    volatile unsigned char *pin,
    unsigned char num,
    baud_rate rate
);

void serial_put_char(
    volatile unsigned char *port,
    unsigned char num,
    baud_rate rate,
    char byte
);

void serial_put_string(
    volatile unsigned char *port,
    unsigned char num,
    baud_rate rate,
    const char *str
);

#endif // SERIAL_H
