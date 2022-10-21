#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "NeoMatrix.h"
#include "generated/NeoMatrix.pio.h"

#define IS_RGBW false
#define NUM_PIXELS 150

#define WS2812_PIN 7
#define PWD_PIN 10


//Class constructor. Used to instantiate an object.
NeoMatrix::NeoMatrix(uint8_t width, uint8_t height){
    //create an array to represent NeoMatrix
    this->width = width;
    this->height = height;
    uint8_t array_size = width * height;
    pixels = new uint32_t{array_size};
}


//Initialize the object, returning true on success or false on failure.
bool NeoMatrix::init(void){
    //set PWD pin to active-low to turn on
    gpio_init(PWD_PIN);
    gpio_set_dir(PWD_PIN, GPIO_OUT);

    //todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    return true;
}
    
//Set the pixel at row row and column col (zero indexed) to color.
void NeoMatrix::set_pixel(uint8_t row, uint8_t col, uint32_t color){
    uint8_t temp = (1*row) + col;
    pixels[temp] = color;
}
    
//Set all elements of the pixel buffer to 0x00.
void NeoMatrix::clear_pixels(void){
    pixels = {0x00};
}
    
//Write the pixel buffer to the NeoMatrix.
void NeoMatrix::write(void){
    //for-loop thru the array to set colors given within pixel
    for(uint32_t i = 0; i < width * height; i++){
        pio_sm_put_blocking(pio0, 0, pixels[i] << 8u);
    }
    
}