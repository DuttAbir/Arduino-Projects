#include "Servo.h"  //for servo control
#include "Wire.h"   //for i2c communication

#define EEPROM_I2C_ADDRESS 0x50   //i2c adress if all three adress pins grounded

int analogPin = 0;    //analog pin connects the potentiometer

int val = 0;    //to store analog data from potentiometer

int readVal = 0;    //to read the data from the EEPROM

int maxAddress = 1500;    //maximum adress to be used (EEPROM max is 32KB)

Servo myServo;    //create servo object

//function to write to the external EEPROM
//arduino wire library send one byte at a time over I2C, you need to break the 16-bit address into two 8-bit parts
void wrtiteEEPROM(int address, byte val, int i2c_address){
  Wire.beginTransmission(i2c_address);
  //bitwise right shift on the address integer by 8 bits, extracts the MSB of the 16-bit address.
  Wire.write((int)(address>>8));
  //bitwise AND operation between address and 0xFF, isolates the LSB of the 16-bit address
  Wire.write((int)(address & 0xFF));

  Wire.write(val);    //send the data byte to into the address

  Wire.endTransmission();
  delay(5);
}

//function to read from the external EEPROM
byte readEEPROM(int address, int i2c_address){
  byte rcvData = 0xFF;    //store the byte read from the EEPROM, initialized it to a known value

  Wire.beginTransmission(i2c_address);
  Wire.write((int)(address>>8));
  Wire.write((int)(address & 0xFF));

  Wire.endTransmission();

  Wire.requestFrom(i2c_address, 1);   //request EEPROM to read 1 byte of data. 

  rcvData = Wire.read();    //read data byte from the address
  return rcvData;
}

void setup() {
  Wire.begin();   //initialized i2c communication
  Serial.begin(9600);   //initialize serial communication

  myServo.attach(9);    //initialize servo on pin 9

  Serial.println("Start recording...");

  //loop upto the max adress to be used and record the servo angles for corresponding analog reading from the potentiometer 
  for (int address = 0 ; address <= maxAddress; address++) {
    val = map(analogRead(analogPin),0, 1023, 0, 180);   //map the analog reading to servo angle
    myServo.write(val);   //move the servo to particular single 
    delay(15);
    wrtiteEEPROM(address,val,EEPROM_I2C_ADDRESS);   //write the angle to the adress of the EEPROM

    Serial.print("ADDR = ");
    Serial.print(address);
    Serial.print("\t");
    Serial.println(val);
  }

  Serial.println("Recording Done");
  delay(5000);

  Serial.println("Begin Playback...");

  //oop upto the max adress used and read the servo angles
  for (int address = 0; address<=maxAddress; address++) {
    readVal = readEEPROM(address, EEPROM_I2C_ADDRESS);    //read the angle from the address
    myServo.write(readVal);
    delay(15);

    Serial.print("ADDR = ");
    Serial.print(address);
    Serial.print("\t");
    Serial.println(readVal);
  }

  Serial.println("Playback finished...");

}

void loop() {}
