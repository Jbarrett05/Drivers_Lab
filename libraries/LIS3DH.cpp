//file for accelerometer driver

#include "LIS3DH.h"

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "boards/adafruit_feather_rp2040.h"
#include "hardware/i2c.h"
#include "LIS3DH.h"

/* Example code to talk to a LIS3DH Mini GPS module.

   This example reads data from all 3 axes of the accelerometer and uses an auxillary ADC to output temperature values.

   Connections on ADAFRUIT FEATHER RP2040 board, other boards may vary.

   GPIO FEATHER_I2C_SDA_PIN (On Pico this is 2 (physical pin 4)) -> SDA on LIS3DH board
   GPIO FEATHER_I2C_SCL_PIN (On Pico this is 3 (physical pin 5)) -> SCL on LIS3DH board
   3.3v (physical pin 36) -> VIN on LIS3DH board
   GND (physical pin 38)  -> GND on LIS3DH board
*/

#define FEATHER_I2C_SDA_PIN 2
#define FEATHER_I2C_SCL_PIN 3


const int ADDRESS = 0x18;
const uint8_t CTRL_REG_1 = 0x20;
const uint8_t CTRL_REG_4 = 0x23;
const uint8_t TEMP_CFG_REG = 0xC0;

LIS3DH::LIS3DH(){
    x = 0;
    y = 0;
    z = 0;

    // This example will use I2C0 on the default SDA and SCL pins
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(FEATHER_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(FEATHER_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(FEATHER_I2C_SDA_PIN);
    gpio_pull_up(FEATHER_I2C_SCL_PIN);

    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(FEATHER_I2C_SDA_PIN, FEATHER_I2C_SCL_PIN, GPIO_FUNC_I2C));
}

//Initializes the accelerometer, returning true on success or false on failure.
bool LIS3DH::init(void){

    LIS3DH();

    uint8_t buf[2];

    // Turn normal mode and 1.344kHz data rate on
    set_reg(CTRL_REG_1,0x97);
    // buf[0] = CTRL_REG_1;
    // buf[1] = 0x97;
    // if(i2c_write_blocking(i2c1, ADDRESS, buf, 2, false) == 2){
    //     return false;
    // }

    // Turn auxillary ADC on
    set_reg(TEMP_CFG_REG,0xC0);
    // buf[0] = TEMP_CFG_REG;
    // buf[1] = 0xC0;
    // if(i2c_write_blocking(i2c1, ADDRESS, buf, 2, false) == 2){
    //     return false;
    // }

    return true;
}

//Set a register on the LIS3DH to the given value.
void LIS3DH::set_reg(uint8_t reg, uint8_t val){
    uint8_t buf[2] = {reg,val};
    i2c_write_blocking(i2c1, ADDRESS, buf, 2, false);
}


//Reads and returns the byte at address reg on the accelerometer.
uint8_t LIS3DH::read_reg(uint8_t reg){
    // Read 1 byte of data and store in a 8 bit data structure
    uint8_t result;
    // uint8_t msb;

    i2c_write_blocking(i2c1, ADDRESS, &reg, 1, true);
    i2c_read_blocking(i2c1, ADDRESS, &result, 1, false);
    return result;

    // reg |= 0x01;
    // i2c_write_blocking(i2c1, ADDRESS, &reg, 1, true);
    // i2c_read_blocking(i2c1, ADDRESS, &msb, 1, false);

}

//Updates the class members x, y, and z with the current acceleration values.
void LIS3DH::update(void){
    //get the x value from reg addr
    uint8_t x_l = read_reg(0x28);
    uint8_t x_h = read_reg(0x29);
    uint16_t x_raw = (x_h << 8) | x_l;

    //get the y value from reg addr
    uint8_t y_l = read_reg(0x2A);
    uint8_t y_h = read_reg(0x2B);
    uint16_t y_raw = (y_h << 8) | y_l;

    //get the z value from reg addr
    uint8_t z_l = read_reg(0x2C);
    uint8_t z_h = read_reg(0x2D);
    uint16_t z_raw = (z_h << 8) | z_l;

    //convert to scaling of gravity
    x = (float) ((int16_t) x_raw) / 64;
    y = (float) ((int16_t) x_raw) / 64;
    z = (float) ((int16_t) x_raw) / 64;
}

