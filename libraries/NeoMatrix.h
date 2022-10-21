//header class for NeoMatrix driver
#ifndef NeoMatrix_H
#define NeoMatrix_H

#include <stdint.h>

class NeoMatrix{
    private:
        //size of NeoMatrix
        uint8_t width;
        uint8_t height;

        //array represent pixels on NeoMatrix
        uint32_t *pixels;

    public:
        //Class constructor. Used to instantiate an object.
        NeoMatrix(uint8_t width, uint8_t height);

        //Initialize the object, returning true on success or false on failure.
        bool init(void);
        
        //Set the pixel at row row and column col (zero indexed) to color.
        void set_pixel(uint8_t row, uint8_t col, uint32_t color);
        
        //Set all elements of the pixel buffer to 0x00.
        void clear_pixels(void);
        
        //Write the pixel buffer to the NeoMatrix.
        void write(void);
};

#endif