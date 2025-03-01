/*Reads temp from DS1631 and displays on PC screen 

*/ 

 

#include "mbed.h" 

// LCD
#define ENABLE 0x08         //Will be ORed in to data value to strobe E bit 
#define COMMAND_MODE 0x00   //used to clear RS line to 0, for command transfer 
#define DATA_MODE 0x04      //used to set RS line to 1, for data transfer 
DigitalOut CS(D10); 
SPI ser_port(D11, D12, D13); // Initialise SPI, using default settings 

// LCD Function Prototypes 
void clr_lcd(void); 
void init_lcd(void); 
void print_lcd(const char *string); 
void shift_out(int data); 
void write_cmd(int cmd); 
void write_data(char c);  
void write_4bit(int data); 


// Temp sensor variables
I2C temp_sensor(I2C_SDA, I2C_SCL); //Configure I2C interface 
BufferedSerial pc(USBTX, USBRX, 9600);  
const int temp_addr = 0x90; //I2C address of temperature sensor DS1631 
char commands[] = {0x51, 0xAA}; 
char read_temp[2]; 
char LCD_result[9];            //holds result to be displayed on LCD.  
 

//----------- MAIN function ---------------// 
int main(){ 
  CS=1;
  init_lcd();  //initialise the LCD 
  clr_lcd();   //Clear the LCD 
  print_lcd("Temperature is"); 
  
  while(1){ 

  //Write 0x51 to 0x90 to start temperature conversion 
  temp_sensor.write(temp_addr, &commands[0], 1, false); 
  thread_sleep_for (500);    //wait for the conversion to complete 

  //Write 0xAA to 0x90 to read the last converted temperature 
  temp_sensor.write(temp_addr, &commands[1], 1, false); 

  //Read the temperature into the read_temp array 
  temp_sensor.read(temp_addr, read_temp, 2); 

  //Convert temperature to Celsius 
  float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256); 

  //Print temperature to the serial monitor 
  printf("Temp = %d.%d\r\n", int(temp), int((temp-int(temp))*10)); 

  //convert float value in temp to character string in LCD_result 
  //sprintf(LCD_result, "%f", temp);  
  sprintf(LCD_result, "%d.%d", int(temp), int((temp-int(temp))*10));  
  write_cmd(0xc0);             //set cursor to start of second line 
  wait_us(40); 
  for (char i=0;i<4;i++){      //write 4 characters from string to LCD 
    write_data(LCD_result[i]); 
    }  
  print_lcd(" degrees C");     //add units 
  } 
} 


//----------- LCD functions --------------// 
void init_lcd(void) {   //follow designated procedure in data sheet 
    thread_sleep_for (40); 
    shift_out(0x30);    //function set 8-bit 
    wait_us(37); 
    write_cmd(0x20);    //function set 
    wait_us(37); 
    write_cmd(0x20);    //function set 
    wait_us(37); 
    write_cmd(0x0C);    //display ON/OFF 
    wait_us(37); 
    write_cmd(0x01);    //display clear 
    wait_us(1520); 
    write_cmd(0x06);    //entry-mode set 
    wait_us(37); 
    write_cmd(0x28);    //function set 
    wait_us(37); 
} 

void write_4bit(int data, int mode) {  //mode is RS line, ie 0 for cmd, 1 for data 
    int hi_n; 
    int lo_n; 
    hi_n = (data & 0xF0);           //form the two 4-bit nibbles that will be sent 
    lo_n = ((data << 4) &0xF0); 
    shift_out(hi_n | ENABLE | mode); //send each word twice, strobing the Enable line 
    wait_us(1); 
    shift_out(hi_n & ~ENABLE); 
    shift_out(lo_n | ENABLE | mode); 
    wait_us(1); 
    shift_out(lo_n & ~ENABLE); 
} 

void shift_out(int data) {     //Invokes SPI 
    CS = 0; 
    ser_port.write(data);   
    CS = 1; 
} 

void write_cmd(int cmd) { 
    write_4bit(cmd, COMMAND_MODE);   
} 

void write_data(char c) { 
    write_4bit(c, DATA_MODE);    //1 for data mode 
} 

void clr_lcd(void) { 
    write_cmd(0x01);    //display clear 
    wait_us(1520); 
} 

void print_lcd(const char *string) { 
    while(*string){ 
        write_data(*string++); 
            wait_us(40); 
    } 
} 