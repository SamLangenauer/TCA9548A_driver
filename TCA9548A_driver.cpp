/**********************************************
 * File: TCA9548A_driver.cpp
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
#include "TCA9548A_driver.h"

// Initialize I2C Address
TCA9548A::TCA9548A(uint8_t addr) : curr_addr(addr), curr_channels(0) {}

// Initializes the I2C Bus with Wire interface
void TCA9548A::begin(TwoWire &wire_input)
{
    this->TCA9548A_wire = &wire_input;
    this->TCA9548A_wire->begin();
}

// Opens a specific channel
void TCA9548A::TCA9548A_open_channel(uint8_t channel)
{
    uint8_t channel_buffer = 1 << channel;
    this->curr_channels |= channel_buffer;
    TCA9548A_write(this->curr_channels);
}

// Opens all channels
void TCA9548A::TCA9548A_open_all()
{
    this->curr_channels = TCA9548A_SELECT_CHANNELS;
    TCA9548A_write(this->curr_channels);
}

// Closes a specific channel
void TCA9548A::TCA9548A_close_channel(uint8_t channel)
{
    uint8_t channel_buffer = 1 << channel;
    this->curr_channels &= ~channel_buffer;
    TCA9548A_write(this->curr_channels);
}

// Closes all channels
void TCA9548A::TCA9548A_close_all()
{
    this->curr_channels = TCA9548A_DESELECT_CHANNELS;
    TCA9548A_write(this->curr_channels);
}

// Writes to the internal register, select multiple specific channels
void TCA9548A::TCA9548A_write_register(uint8_t value)
{
    this->curr_channels = value;
    TCA9548A_write(this->curr_channels);
}

// Writes 8 bits to TCA9548A, changing currently active channels
void TCA9548A::TCA9548A_write(uint8_t data)
{
    this->TCA9548A_wire->beginTransmission(this->curr_addr);
    this->TCA9548A_wire->write(data);
    this->TCA9548A_wire->endTransmission(true);
}

// Reads current state of internal register (channel usage information)
uint8_t TCA9548A::TCA9548A_read_register()
{
    this->TCA9548A_wire->requestFrom(this->curr_addr, 1, true);
    
    if(!(this->TCA9548A_wire->available())) // Check if data can be read
    {
        return TCA9548A_REGISTER_READ_ERROR; // Return if nothing available
    }

    uint8_t buffr = this->TCA9548A_wire->read();    // Read state from TCA9548A
    return buffr;
}