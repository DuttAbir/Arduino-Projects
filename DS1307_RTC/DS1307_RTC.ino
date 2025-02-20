#include <Wire.h>   //essential for I2C communication.

//abbreviated names of the days of the week and months.
const char* dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void setup() {
  Wire.begin();
  Serial.begin(9600);
  rtc_write(0, 28, 23, 4, 20, 2, 25);   // Set initial time (seconds, minutes, hours, day, date, month, year)
  delay(1000);
}

void loop() {
  delay(1000);
  Serial.println("-----------------------");

  Serial.print("Time - ");
  Serial.print(rtc_read(0x02));
  Serial.print(" : ");
  Serial.print(rtc_read(0x01));
  Serial.print(" : ");
  Serial.println(rtc_read(0x00));

  uint8_t day = rtc_read(0x03); // Day of the week (1-7, Sunday=1)
  uint8_t date = rtc_read(0x04); // Date
  uint8_t month = rtc_read(0x05); // Month
  uint8_t year = rtc_read(0x06); // Year

  Serial.print("Date - ");
  Serial.print(dayNames[day - 1]); // Day of the week name
  Serial.print(", ");
  Serial.print(date);
  Serial.print("-");
  Serial.print(monthNames[month - 1]); // Month name
  Serial.print("-");
  Serial.print(20);
  Serial.println(year);

  Serial.println("-----------------------");
}

//decimal value to its BCD equivalent, RTCs store time and date in BCD format
char decimal_to_BCD (unsigned char val){
  return ((val / 10) << 4) + (val % 10);
}

void rtc_write(char _second, char _minute, char _hour, char _day, char _date, char _month, char _year){
  Wire.beginTransmission(0x68);   //Start write transaction to i2c address
  Wire.write(0x00);   // Start at seconds register

  Wire.write(decimal_to_BCD(_second));
  Wire.write(decimal_to_BCD(_minute));
  Wire.write(decimal_to_BCD(_hour));
  Wire.write(decimal_to_BCD(_day));
  Wire.write(decimal_to_BCD(_date));
  Wire.write(decimal_to_BCD(_month));
  Wire.write(decimal_to_BCD(_year));

  Wire.endTransmission();   //end transaction 
}

uint8_t rtc_read(uint8_t addr){
  Wire.beginTransmission(0x68);  // Start write transaction to set address
  Wire.write(addr);   //sends the register address to read from.
  Wire.endTransmission();

  Wire.requestFrom(0x68, 1);    //requests 1 byte of data from the RTC.
  
  uint8_t data = 0;
  if (Wire.available()) {
    data = Wire.read();
    data = ((data >> 4) * 10) + (data & 0x0F); // BCD to Decimal
  }
  return data;
}
