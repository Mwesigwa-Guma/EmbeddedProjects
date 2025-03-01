/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define ENABLE 0x80
#define COMMAND_MODE 0x00
#define DATA_MODE 0x04

DigitalOut CS(D10);
SPI ser_port(D11, D12, D13);

void clr_lcd(void);
void init_lcd(void);
void print_lcd(const char *string);
void shift_out(int data);
void write_cmd(int cmd);
void write_data(char c);
void write_4bit(int data);

int main(){
    CS = 1;
    init_lcd();
    clr_lcd();

    print_lcd("  Hello world!");
    write_cmd(0xc0);
    wait_us(40);
    print_lcd("     Testing");

    while(1){
        thread_sleep_for(100);
    }
}

void init_lcd(void){
    thread_sleep_for(40);
    shift_out(0x30);
    wait_us(37);
    write_cmd(0x20);
    wait_us(37);
    write_cmd(0x20);
    wait_us(0x37);
    write_cmd(0x0C);
    wait_us(37);
    write_cmd(0x01);
    wait_us(1520);
    write_cmd(0x06);
    wait_us(37);
    write_cmd(0x28);
    wait_us(37);
}

void write_4bit(int data, int mode){
    int hi_n;
    int lo_n;

    hi_n = (data & 0xF0);
    lo_n = ((data << 4) & 0xF0);

    shift_out(hi_n | ENABLE | mode);
    wait_us(1);
    shift_out(hi_n & ~ENABLE);
    shift_out(lo_n | ENABLE | mode);
    wait_us(1);
    shift_out(lo_n & ~ENABLE);
}

void shift_out(int data){
    CS = 0;
    ser_port.write(data);
    CS = 1;
}

void write_cmd(int cmd){
    write_4bit(cmd, COMMAND_MODE);
}

void write_data(char c){
    write_4bit(c, DATA_MODE);
}

void clr_lcd(void){
    write_cmd(0x01);
    wait_us(1520);
}

void print_lcd(const char *string){
    while(*string){
        write_data(*string++);
        wait_us(40);
    }
}
