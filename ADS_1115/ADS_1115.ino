#include <Wire.h>   //needed for i2c communication

#define ADS_1115_ADRESS 0x48    //i2c address of ADS_1115

#define CONFIG_REG 0x01   //configuration register address
#define CONVERT_REG 0x00    //conversion  register address

void setup() {
  Serial.begin(9600);   //initializes serial communication
  Wire.begin();   //initializes i2c communication
}

void loop() {
  //configure ADS1115 configuration register
  uint8_t config_H = 0b11000011;    //OS[15]:begin singel conversion, MUX[14:12]:ANI0, PGA[11:9]:+-2048V, MODE[8]:single-shot  
  uint8_t config_L = 0b10000011;    //datarate[7:5]:128SPS, COMP_MODE[4]:traditional, COM_POL[3]:low, COMP_LAT[2]:no latch, COMP_QUE[1:0]:disable

  write_to_ADS(CONFIG_REG, config_H, config_L);   //write the configuration to configuration register
  delay(10);
  int16_t adcVal =  read_ADS();   //read conversion
  float voltage = (float(adcVal) * 4.096) / 32767.0   //convert digital data to analog voltage;
  Serial.print(adcVal);
  Serial.print(" : ");
  Serial.println(voltage);
  delay(500);
}

//configure the ADS1115
void write_to_ADS(uint8_t reg, uint8_t value_H, uint8_t value_L){
  Wire.beginTransmission(ADS_1115_ADRESS);    //begin communication with the ADS1115
  Wire.write(reg);    //point to configuration register
  Wire.write(value_H);    //write MSB
  Wire.write(value_L);    //write LSB
  Wire.endTransmission();
}

//read conversion
int16_t read_ADS(){
  Wire.beginTransmission(ADS_1115_ADRESS);
  Wire.write(CONVERT_REG);    //point to conversion register
  Wire.endTransmission();

  Wire.requestFrom(ADS_1115_ADRESS, 2);   //request to read 2-bytes from the ADS1115
  int16_t value = Wire.read() << 8 | Wire.read();   //combine 2-bytes
  return value; 
}