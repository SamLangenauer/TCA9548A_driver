/**********************************************
 * File: TCA9548A_example.ino
 *     Version: 0.1 | Date: 03/20/2024
 * 
 * Description: 
 *  Example code using the TCA9548A Library.
 * 
 *  This library provides examples of the 
 *  functions to switch between different 
 *  I2C channels.
 * 
 * Author: samlang2003@gmail.com
**********************************************/

#include <Arduino.h>
#include <Wire.h>
#include "TCA9548A_driver.h"

void i2cScan(void);

// Create TCA9548A object
TCA9548A tca9548a;

void setup()
{
    Serial.begin(9600);

    /*initialize i2c communication*/
    tca9548a.begin();
}

void loop()
{
    /*open channel 0 for testing*/
    tca9548a.TCA9548A_open_channel(0);

    /*delay to ensure command is processed (can delete)*/
    delay(100);

    /*check whether channel is open*/
    uint8_t register_status = tca9548a.TCA9548A_read_register();
    if(register_status & TCA9548A_CHANNEL_0)
    {
        serial.println("Channel 0 Open, Scanning for devices.");

        /*i2c scan to check for communication through channel 0*/
        i2cScan();

        tca9548a.TCA9548A_close_channel(0);
    }
    else
    {
        Serial.println("Error opening channel 0");
    }

    /*avoid spamming function*/
    delay(2500);
}

void i2cScan()
{
    uint8_t error, address;
    uint8_t num_devices;

    Serial.println("Scanning...");
    num_devices = 0;
    for(address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission;

        if(!error)
        {
            Serial.println("I2C Device found at address 0x");
            Serial.print(address, HEX);
            num_devices++;
        }
        else if(error == 4)
        {
            Serial.println("Unknown error at address 0x");
            Serial.print(address, HEX);
        }
    }

    if(!num_devices)
    {
        Serial.println("No I2C devices found\n");
    }
    else
    {
        Serial.println("Scan Complete!");
    }
}