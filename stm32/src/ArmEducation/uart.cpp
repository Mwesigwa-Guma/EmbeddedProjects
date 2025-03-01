/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

BufferedSerial pc(USBTX, USBRX, 9600);
int cycle = 0;

int main(){
    while(true){
        printf("Hello world. This is loop %i\n\r", cycle);
        thread_sleep_for(500);
        cycle++;
    }
}