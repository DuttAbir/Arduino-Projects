#include<IRremote.h>

const int recv_pin = 4;

IRrecv irrecv(recv_pin);
decode_results results;

const int red_pin = 8;
const int green_pin = 9;
const int yellow_pin = 10;
const int blue_pin = 11;


 
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results)){
    //Serial.println(results.value, HEX);
    
    switch(results.value){
      case 0x52E9: //Red_button_Hex = 0x52E9
        digitalWrite(red_pin, HIGH);
        digitalWrite(green_pin, LOW);
        digitalWrite(yellow_pin, LOW);
        digitalWrite(blue_pin, LOW);
        break;

        case 0x32E9: //Green_button_Hex = 0x32E9
        digitalWrite(red_pin, LOW);
        digitalWrite(green_pin, HIGH);
        digitalWrite(yellow_pin, LOW);
        digitalWrite(blue_pin, LOW);
        break;

        case 0x72E9: //Yellow_button_Hex = 0x72E9
        digitalWrite(red_pin, LOW);
        digitalWrite(green_pin, LOW);
        digitalWrite(yellow_pin, HIGH);
        digitalWrite(blue_pin, LOW);
        break;

        case 0x12E9: //blue_button_Hex = 0x12E9
        digitalWrite(red_pin, LOW);
        digitalWrite(green_pin, LOW);
        digitalWrite(yellow_pin, LOW);
        digitalWrite(blue_pin, HIGH);
        break;
    }
    
    irrecv.resume();
  }
}
