#include <ESP8266WiFi.h>
#include "C:\Users\dutta\OneDrive\Documents\Arduino\Arduino-Projects\info.h"

const char *SSID = ssid();
const char *PASSWORD = password();

int ledPin = 2;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Server Strated");

  Serial.print("server URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print("/");

  server.begin();

}

void loop() {
  WiFiClient client = server.available();
  while (!client) {
    return;
  }
  Serial.println("New Client");
  while (!client.available()) {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int value = LOW;
  if (request.indexOf("/LED=on") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=off") != -1) {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

  client.println("HTTP/1.1/ 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Led pin is now : ");

  if (value == HIGH) {
    client.print("ON");
  }
  else{
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("Click <a href=\"/LED=on\">here</a> to turn the LED on<br>");
  client.println("Click <a href=\"/LED=off\">here</a> to turn the LED off<br>");
  client.println("</html>");
  
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
