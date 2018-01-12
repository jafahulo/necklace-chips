/*
  This sketch demonstrates how to send data from a Device
  to a Host in a Gazell network.

  The host and upto 3 devices should have the RGB shield
  attached.  When Button A on a Device is pressed, the
  associated led on the Host will toggle.  Device1 is
  associated with the Red led, Device2 with the Green led
  and Device3 with the Blue led.

  The Green led on the Device will blink to indicate
  that an acknowledgement from the Host was received.
*/

#include <RFduinoGZLL.h>

device_t role = HOST;

int red_led = 2;
int green_led = 3;
int blue_led = 4;
double initialIntensity = 0.75;
double intensity = 0.0;
int red = 127;
int green = 255;
int blue = 212;
bool isConnected = false;
int timer;

void setup()
{
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  // start the GZLL stack
  Serial.begin(9600);
  RFduinoGZLL.begin(role);
  RFduinoGZLL.sendToDevice(DEVICE0, NULL);
  timer = millis();
}

void loop()
{
  if (millis() - timer > 3000) {
    isConnected = false;
    rgbKill();
    //  } else if(isConnected){
    //    rgb();
  }
  Serial.println(intensity);
}

void rgb() {
  Serial.println("rgb start");
  for (intensity; intensity < initialIntensity; intensity += 0.05) {
    analogWrite(red_led, red * intensity);
    analogWrite(green_led, green * intensity);
    analogWrite(blue_led, blue * intensity);
    delay(100);
  }
  Serial.println("rgb end");
}

void rgbKill() {
  if (intensity!=0) {
    Serial.println("rgbKill start");
    for (intensity; intensity >= 0.0; intensity -= .01) {
      Serial.println(intensity);
      analogWrite(red_led, red * intensity);
      analogWrite(green_led, green * intensity);
      analogWrite(blue_led, blue * intensity);
      delay(100);
    }
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, LOW);
    digitalWrite(blue_led, LOW);
    intensity = 0.0;
    Serial.println("rgbKill end");
  } else {
    Serial.println("rgbKill failed");
  }
}
void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  if (!isConnected) {
    isConnected = true;
    rgb();
  }
  timer = millis();
  RFduinoGZLL.sendToDevice(device, NULL);
}
