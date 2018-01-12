/*
This sketch demonstrates how to send data from a Device
to a Host in a Gazell network.

When Button A on the Device is pressed and released,
the green led on the host will toggle.
*/

#include <RFduinoGZLL.h>

device_t role = DEVICE0;

int red_led = 2;
int green_led = 3;
int blue_led = 4;
double initialIntensity = .75;
double intensity = .75;
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
  RFduinoGZLL.txPowerLevel = 0;
  RFduinoGZLL.begin(role);
  RFduinoGZLL.sendToHost(1);
}

void rgb(){
  analogWrite(red_led, red*intensity);
  analogWrite(green_led, green*intensity);
  analogWrite(blue_led, blue*intensity);
}

void rgbKill(){
  for(intensity; intensity>0; intensity-=.01){
    rgb();
    delay(100);
  }
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, LOW);
}

void loop()
{
  if(millis()-timer > 3000)
    rgbKill();

}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  intensity = initialIntensity;
  rgb();
  timer = millis();
//  delay(2000);
  RFduinoGZLL.sendToHost(NULL);
}
