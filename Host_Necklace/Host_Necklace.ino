#include <RFduinoGZLL.h>

device_t role = HOST;

bool isConnected = false;
int red_led = 2;
int green_led = 3;
int blue_led = 4;
double setIntensity = .45;
double intensity = 0.0;
int red = 127;
int green = 255;
int blue = 212;
int timer = millis();

void setup()
{
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  // start the GZLL stack
  Serial.begin(9600);
  RFduinoGZLL.txPowerLevel = 0;
  RFduinoGZLL.begin(role);
  RFduinoGZLL.sendToDevice(DEVICE0, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (isConnected) {
    increaseIntensity();
  } else {
    decreaseIntensity();
  }
  if (millis() - timer > 3000) {
    isConnected = false;
  }
  writeLED();
  RFduinoGZLL.sendToDevice(DEVICE0, 1);
  delay(50);
}

void increaseIntensity(){
  intensity += .01;
  if(intensity>setIntensity){
    intensity=setIntensity;
  }
}

void decreaseIntensity(){
  intensity -= .01;
  if(intensity<0){
    intensity=0;
  }
}

void writeLED(){
  analogWrite(red_led, red * intensity);
  analogWrite(blue_led, blue * intensity);
  analogWrite(green_led, green * intensity);
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  isConnected = true;
  timer = millis();
}
