#include "serial.h"
#include <util/delay.h>

#if (F_CPU != 20000000)
// because of precomputed constants
#error "CPU frequency must be 20 MHz"
#endif

#define READ_PIN(pin, num) (!!(*pin & (1 << num)))
#define SET_PORT(port, num) (*port |= (1 << num))
#define CLEAR_PORT(port, num) (*port &= ~ (1 << num))
#define TEST_BIT(byte, num) (byte & (1 << num))
#define DELAY_OFFSET 0.2 // to compensate for calling the function and stuff
#define BAUD_DELAY(rate) (1e6 / rate - DELAY_OFFSET)
#define BAUD_DELAY_HALF(rate) (5e5 / rate - DELAY_OFFSET)

void bit_delay(baud_rate rate);
void half_bit_delay(baud_rate rate);

char serial_get_char(
    volatile unsigned char *pin,
    unsigned char num,
    baud_rate rate
) {
    char byte = 0;

    // wait for start bit
    while (READ_PIN(pin, num)) {
        // busy wait
    }

    bit_delay(rate); // skip start bit
    half_bit_delay(rate); // wiat for middle of first bit

    // unrolled loop to read 8 bits of data
    byte |= READ_PIN(pin, num) << 0;
    bit_delay(rate);
    byte |= READ_PIN(pin, num) << 1;
    bit_delay(rate);
    byte |= READ_PIN(pin, num) << 2;
    bit_delay(rate);
    byte |= READ_PIN(pin, num) << 3;
    bit_delay(rate);
    byte |= READ_PIN(pin, num) << 4;
    bit_delay(rate);
    byte |= READ_PIN(pin, num) << 5;
    bit_delay(rate);
    byte |= READ_PIN(pin, num) << 6;
    bit_delay(rate);
    byte |= READ_PIN(pin, num) << 7;

    half_bit_delay(rate); // wait for end of last bit
    bit_delay(rate); // wait for end of stop bit

    return byte;
}

void serial_put_char(
    volatile unsigned char *port,
    unsigned char num,
    baud_rate rate,
    char byte
) {
    // start bit
    CLEAR_PORT(port, num);
    bit_delay(rate);

    // unrolled loop to write 8 bits of data
    if (TEST_BIT(byte, 0)) {
        SET_PORT(port, num);
    } else {
        CLEAR_PORT(port, num);
    }
    bit_delay(rate);
    if (TEST_BIT(byte, 1)) {
        SET_PORT(port, num);
    } else {
        CLEAR_PORT(port, num);
    }
    bit_delay(rate);
    if (TEST_BIT(byte, 2)) {
        SET_PORT(port, num);
    } else {
        CLEAR_PORT(port, num);
    }
    bit_delay(rate);
    if (TEST_BIT(byte, 3)) {
        SET_PORT(port, num);
    } else {
        CLEAR_PORT(port, num);
    }
    bit_delay(rate);
    if (TEST_BIT(byte, 4)) {
        SET_PORT(port, num);
    } else {
        CLEAR_PORT(port, num);
    }
    bit_delay(rate);
    if (TEST_BIT(byte, 5)) {
        SET_PORT(port, num);
    } else {
        CLEAR_PORT(port, num);
    }
    bit_delay(rate);
    if (TEST_BIT(byte, 6)) {
        SET_PORT(port, num);
    } else {
        CLEAR_PORT(port, num);
    }
    bit_delay(rate);
    if (TEST_BIT(byte, 7)) {
        SET_PORT(port, num);
    } else {
        CLEAR_PORT(port, num);
    }
    bit_delay(rate);

    // stop bit
    SET_PORT(port, num);
    bit_delay(rate);

    // wait a little bit longer
    bit_delay(rate);
}

void serial_put_string(
    volatile unsigned char *port,
    unsigned char num,
    baud_rate rate,
    const char *str
) {
    for (; *str; str++) {
        serial_put_char(port, num, rate, *str);
    }
}

void bit_delay(baud_rate rate) {
    switch (rate) {
        case BAUD_RATE_57600:
            _delay_us(BAUD_DELAY(57600));
            break;
        case BAUD_RATE_38400:
            _delay_us(BAUD_DELAY(38400));
            break;
        case BAUD_RATE_19200:
            _delay_us(BAUD_DELAY(19200));
            break;
        case BAUD_RATE_9600:
            _delay_us(BAUD_DELAY(9600));
            break;
        case BAUD_RATE_4800:
            _delay_us(BAUD_DELAY(4800));
            break;
    }
}

void half_bit_delay(baud_rate rate) {
    switch (rate) {
        case BAUD_RATE_57600:
            _delay_us(BAUD_DELAY_HALF(57600));
            break;
        case BAUD_RATE_38400:
            _delay_us(BAUD_DELAY_HALF(38400));
            break;
        case BAUD_RATE_19200:
            _delay_us(BAUD_DELAY_HALF(19200));
            break;
        case BAUD_RATE_9600:
            _delay_us(BAUD_DELAY_HALF(9600));
            break;
        case BAUD_RATE_4800:
            _delay_us(BAUD_DELAY_HALF(4800));
            break;
    }
}
