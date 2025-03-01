/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut CS(D10);
SPI ser_port(D11, D12, D13);
char switch_word;

int main(){
    ser_port.format(8, 0);
    ser_port.frequency(1000000);

    CS = 1;
     
    while(1){
        switch_word = 0xAA;
        CS = 0;
        ser_port.write(switch_word);
        CS = 1;
        thread_sleep_for(500);
        switch_word = 0x55;
        CS = 0;
        ser_port.write(switch_word);
        CS=1;
        thread_sleep_for(500);
    }
}