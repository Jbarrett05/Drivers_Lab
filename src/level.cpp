#include <stdio.h>
#include <string.h>
#include <pico/stdlib.h>
#include "../libraries/LIS3DH.h"

int main(){
    stdio_init_all();

    LIS3DH accel = LIS3DH();
    accel.init();

    //display readings from LIS3DH chip
    printf("Hello, LIS3DH! Reading raw data from registers...\n");
    while(1){
        accel.update();

        printf("X acceleration: %.3fg\n", accel.x);
        printf("Y acceleration: %.3fg\n", accel.y);
        printf("Z acceleration: %.3fg\n", accel.z);

        sleep_ms(500);

        // Clear terminal 
        printf("\e[1;1H\e[2J");
    }
    

    return 0;
}