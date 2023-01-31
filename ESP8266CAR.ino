#include<ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int forward_left = 16, backward_left = 5, forward_right = 4, backward_right = 0;

const char* SSID = "pawan";
const char* PSWD = "pawan1234";

ESP8266WebServer server(80);

void handleRoot(){
  server.send(200,"text/html",sendhtml());
}
void move(){
  if(server.arg("dir") == "F")
  {
    forward();
  }
  if(server.arg("dir") == "B")
  {
    backward();
  }
  if(server.arg("dir") == "L")
  {
    left();
  }
  if(server.arg("dir") == "R")
  {
    right();
  }
  if(server.arg("dir") == "S")
  {
    stops();
  }
}
String sendhtml(){
  String html ="<!DOCTYPE html> <html> <body> <h1>Ready to Drive</h1></body> </html>";
  return html;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.softAP(SSID,PSWD);
  pinMode(forward_left, OUTPUT);
  pinMode(forward_right, OUTPUT);
  pinMode(backward_left, OUTPUT);
  pinMode(backward_right, OUTPUT);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Acess Point IP:");
  Serial.println(myIP);
  server.on("/",handleRoot);
  server.on("/move",move);
  server.begin();
  digitalWrite(forward_left,LOW);
  digitalWrite(forward_right,LOW);
  digitalWrite(backward_left,LOW);
  digitalWrite(backward_right,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void forward()
{
  digitalWrite(forward_left, HIGH);
  digitalWrite(forward_right, HIGH);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, LOW);
  Serial.println("forward");
} 
void backward()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, HIGH);
  digitalWrite(backward_right, HIGH);
  Serial.println("backward");
} 
void left()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, HIGH);
  digitalWrite(backward_left, HIGH);
  digitalWrite(backward_right, LOW);
  Serial.println("left");
} 
void right()
{
  digitalWrite(forward_left, HIGH);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, HIGH);
  Serial.println("right");
} 
void stops()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, LOW);
  Serial.println("stop");
}
