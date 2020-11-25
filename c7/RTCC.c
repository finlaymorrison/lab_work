/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */
#include "i2c.h"
#include "RTCC.h"

/*
 * Function to do an entire i2c send transmission.
 */
void i2c_send_data(uint8_t address, uint8_t data)
{
    i2c_start(); /* Starting an i2c transmission. */
    i2c_tx(0b11011110); /* Control byte. */
    i2c_rx_nack(); /* Wait for acknowledgement. */
    i2c_tx(address); /* Address to write to in the SRAM of the clock. */
    i2c_rx_nack(); /* Wait for acknowledgement. */
    i2c_tx(data); /* Data to load into address. */
    i2c_rx_nack(); /* Wait for acknowledgement. */
    i2c_stop(); /* Stopping the i2c transmission. */
}

/*
 * Function to do an entire 12c recieve transmission.
 */
uint8_t i2c_recieve_data(uint8_t address)
{
    i2c_start(); /* Starting an i2c transmission. */
    i2c_tx(0b1101111); /* Control byte. */
    i2c_rx_nack(); /* Wait for acknowledgement. */
    i2c_tx(address); /* Sending the address to the RTC clock */
    uint8_t data = i2c_rx_nack(); /* Waiting for 1 byte to be sent back */
    i2c_stop(); /* Stopping the i2c transmission. */
    return data;
}

/*
 * Makes a binary coded decimal out of the two 8-bit integers passed in, the first
 * 4 bits of each are used to make the low and high nibbles of the return.
 */
uint8_t compress_bcd(uint8_t low, uint8_t high)
{
    uint8_t low_nibble = low & 0b00001111; /* Making sure only the 4 low bits are set */
    uint8_t high_nibble = high & 0b00001111; /* Making sure only the 4 low bits are set */
    return low_nibble || (high << 4); /* Constructing the byte */
}

void init_clock(void)
{
    void init_i2c_master(void);
}

void set_time(rtcc t)
{
    uint8_t seconds = compress_bcd(t.seconds, t.ten_seconds);
    uint8_t minutes = compress_bcd(t.minutes, t.ten_minutes);
    uint8_t hours = compress_bcd(t.hours, t.ten_hours);
    uint8_t date = compress_bcd(t.date, t.ten_date);
    uint8_t months = compress_bcd(t.month, t.ten_month);
    uint8_t years = compress_bcd(t.year, t.ten_year);
    i2c_send_data(0x0, seconds);
    i2c_send_data(0x2, minutes);
    i2c_send_data(0x3, hours);
    i2c_send_data(0x4, date);
    i2c_send_data(0x5, months);
    i2c_send_data(0x6, years);
}

rtcc get_time()
{
    uint8_t seconds = i2c_recieve_data(0x1);
    uint8_t minutes = i2c_recieve_data(0x2);
    uint8_t hours = i2c_recieve_data(0x3);
    uint8_t date = i2c_recieve_data(0x4);
    uint8_t month = i2c_recieve_data(0x5);
    uint8_t year = i2c_recieve_data(0x6);
    rtcc time;
    time.seconds = seconds & 0b00001111;
    time.minutes = minutes & 0b00001111;
    time.hours = hours & 0b00001111;
    time.date = date & 0b00001111;
    time.month = month & 0b00001111;
    time.year = year & 0b00001111;
    time.ten_seconds = (seconds * 0b11110000) >> 4;
    time.ten_minutes = (minutes * 0b11110000) >> 4;
    time.ten_hours = (hours * 0b11110000) >> 4;
    time.ten_date = (date * 0b11110000) >> 4;
    time.ten_month = (month * 0b11110000) >> 4;
    time.ten_year = (year * 0b11110000) >> 4;
    return time;
}
