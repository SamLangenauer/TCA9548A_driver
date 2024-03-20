/**********************************************
 * File: TCA9548A_driver.h
 *     Version: 0.1 | Date: 03/20/2024
 * 
 * Description: 
 *  Arduino Library for TCA9548A I2C MUX.
 * 
 *  This library provides functions to switch
 *  between different I2C channels.
 * 
 * Author: samlang2003@gmail.com
**********************************************/


#ifndef TCA9548A_DRIVER_H
#define TCA9548A_DRIVER_H

/*required libraries*/
#include <Arduino.h>
#include <Wire.h>

/*definitions*/
#define TCA9548A_DEFAULT_ADDRESS 0x70   // Default I2C Address
/*channel definitions*/
#define TCA9548A_CHANNEL_0 0x01
#define TCA9548A_CHANNEL_1 0x02
#define TCA9548A_CHANNEL_2 0x04
#define TCA9548A_CHANNEL_3 0x08
#define TCA9548A_CHANNEL_4 0x10
#define TCA9548A_CHANNEL_5 0x20
#define TCA9548A_CHANNEL_6 0x40
#define TCA9548A_CHANNEL_7 0x80
#define TCA9548A_SELECT_CHANNELS 0xFF
#define TCA9548A_DESELECT_CHANNELS 0x00
/*error codes*/
#define TCA9548A_REGISTER_READ_ERROR 255

/*TCA9548A class definition*/
class TCA9548A
{
    public:
        TCA9548A(uint8_t addr = TCA9548A_DEFAULT_ADDRESS);

        void begin(TwoWire &wire_input = Wire);         // Enable I2C Bus
        void TCA9548A_open_channel(uint8_t channel);    // Open specific channel
        void TCA9548A_close_channel(uint8_t channel);   // Close specific channel
        void TCA9548A_open_all();                       // Open all channels
        void TCA9548A_close_all();                      // Close all channels
        void TCA9548A_write_register(uint8_t value);    // Write to internal register
        uint8_t TCA9548A_read_register();               // Reads from internal register
    
    private:
        TwoWire *TCA9548A_wire;             // Pointer to I2C Bus
        uint8_t curr_addr;                  // Current I2C Address of TCA9548A
        uint8_t curr_channels;              // Bitmask of Current active channels
        void TCA9548A_write(uint8_t data);  // Write to TCA9548A (change channels)
};

#endif