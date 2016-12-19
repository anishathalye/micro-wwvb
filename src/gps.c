#include "gps.h"

#define NMEA_MAX_MSG_LENGTH 82 // including starting '$' and ending '\n'

static inline int is_digit(char c);
static inline int to_digit(char c);
static void gps_init_chunked(
    volatile unsigned char *port,
    unsigned char num,
    baud_rate rate,
    char left,
    char right
);

const char *msg_prefix = "$PSRF103,0";
const char *init_msg_mid = ",00,00,01*2";
const char *msg_suffix = "\r\n";

static void gps_init_chunked(
    volatile unsigned char *port,
    unsigned char num,
    baud_rate rate,
    char left,
    char right
) {
    serial_put_string(port, num, rate, msg_prefix);
    serial_put_char(port, num, rate, left);
    serial_put_string(port, num, rate, init_msg_mid);
    serial_put_char(port, num, rate, right);
    serial_put_string(port, num, rate, msg_suffix);
}

void gps_init(
    volatile unsigned char *port,
    unsigned char num,
    baud_rate rate
) {
    // rate control: disable everything
    //
    // done in this weird way to save data memory
    // sends messages like "$PSRF103,0x,00,00,01*2y\r\n" to set all rates to zero
    gps_init_chunked(port, num, rate, '0', '4');
    gps_init_chunked(port, num, rate, '1', '5');
    gps_init_chunked(port, num, rate, '2', '6');
    gps_init_chunked(port, num, rate, '3', '7');
    gps_init_chunked(port, num, rate, '4', '0');
    gps_init_chunked(port, num, rate, '5', '1');
    gps_init_chunked(port, num, rate, '6', '2');
    gps_init_chunked(port, num, rate, '8', 'C');
}

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
) {
    // send query to get ZDA
    // "$PSRF103,08,01,00,01*2D\r\n"
    serial_put_string(port, port_num, rate, msg_prefix);
    serial_put_string(port, port_num, rate, "8,01,00,01*2D\r\n");

    // TODO have some kind of timeout (maybe the caller should set that up, though)

    // wait for '$' character
    while (serial_get_char(pin, pin_num, rate) != '$') {
        // busy wait
    }

    // get rest of message
    static char nmea_buf[NMEA_MAX_MSG_LENGTH];
    int idx = 0;
    while (idx < NMEA_MAX_MSG_LENGTH) {
        char c = serial_get_char(pin, pin_num, rate);
        nmea_buf[idx] = c;
        idx++;
        if (c == '\n') {
            break;
        }
    }

    // quick sanity check
    // TODO maybe check the checksum?
    // format is "$GPZDA,hhmmss.sss,dd,mm,yyyy,xx,yy*CC"
    //
    // we just want UTC time, so we need it to be at least the length of
    // "GPZDA,hhmmss.sss,dd,mm,yyyy,,*CC\r\n"
    if (idx < 34) {
        return -1; // maybe we don't have the time yet or something else went wrong
    }
    if (nmea_buf[0] != 'G' ||
            nmea_buf[1] != 'P' ||
            nmea_buf[2] != 'Z' ||
            nmea_buf[3] != 'D' ||
            nmea_buf[4] != 'A') {
        return -1;
    }

    // parse
    if (!is_digit(nmea_buf[6]) || !is_digit(nmea_buf[7])) {
        return -1;
    }
    *hour = to_digit(nmea_buf[6]) * 10 + to_digit(nmea_buf[7]);
    if (!is_digit(nmea_buf[8]) || !is_digit(nmea_buf[9])) {
        return -1;
    }
    *minute = to_digit(nmea_buf[8]) * 10 + to_digit(nmea_buf[9]);
    if (!is_digit(nmea_buf[10]) || !is_digit(nmea_buf[11])) {
        return -1;
    }
    *second = to_digit(nmea_buf[10]) * 10 + to_digit(nmea_buf[11]);
    if (!is_digit(nmea_buf[17]) || !is_digit(nmea_buf[18])) {
        return -1;
    }
    *day = to_digit(nmea_buf[17]) * 10 + to_digit(nmea_buf[18]);
    if (!is_digit(nmea_buf[20]) || !is_digit(nmea_buf[21])) {
        return -1;
    }
    *month = to_digit(nmea_buf[20]) * 10 + to_digit(nmea_buf[21]);
    if (!is_digit(nmea_buf[23]) ||
            !is_digit(nmea_buf[24]) ||
            !is_digit(nmea_buf[25]) ||
            !is_digit(nmea_buf[26])) {
        return -1;
    }
    *year = to_digit(nmea_buf[23]) * 1000 + to_digit(nmea_buf[24]) * 100 +
        to_digit(nmea_buf[25]) * 10 + to_digit(nmea_buf[26]);

    return 0;
}

static inline int is_digit(char c) {
    return ('0' <= c && c <= '9');
}

static inline int to_digit(char c) {
    return c - '0';
}
