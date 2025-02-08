const int sensor = 2;
const int button = 3;
const int led = 13;

int sensor_val = 0;
int button_val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor, INPUT);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_val = digitalRead(sensor);
  button_val = digitalRead(button);

  if(sensor_val == HIGH){
    digitalWrite(led,HIGH);
  }
  if(button_val == LOW){
    digitalWrite(led,LOW);
  }

}
