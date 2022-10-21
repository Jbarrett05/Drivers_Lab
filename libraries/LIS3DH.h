//header class for accelerometer driver
#ifndef LIS3DH_H
#define LIS3DH_H

#include <stdint.h>

class LIS3DH{
    public:
    //Class members representing the 3 accel values in units of g (Earth's Gravitation Accel)
    float x;
    float y;
    float z;

    //Class constructor
    LIS3DH();

    //Initializes the accelerometer, returning true on success or false on failure.
    bool init();

    //Set a register on the LIS3DH to the given value.
    void set_reg(uint8_t reg, uint8_t val);

    //Reads and returns the byte at address reg on the accelerometer.
    uint8_t read_reg(uint8_t reg);

    //Updates the class members x, y, and z with the current acceleration values.
    void update();

    //// Convert with respect to the value being cceleration reading 
    void lis3dh_calc_value(uint16_t raw_value, float *final_value, bool isAccel);

};

#endif