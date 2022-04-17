#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Set Oled Screen Constants
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//Set Oled Screen Variables
Adafruit_SSD1306 oled1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 oled2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Set Stepper Motor Constants
const int stepsPerRevolution = 200;

//Set Stepper Motor Variables
Stepper leftMotor(stepsPerRevolution, 8, 9, 10, 11);
Stepper rightMotor(stepsPerRevolution, 4, 5, 6, 7);

void setup() {
  //Set baude rate
  Serial.begin(9600);
  
  //Check if oled on
  if (!oled1.begin(SSD1306_SWITCHCAPVCC, 0x3C) && !oled2.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  //Set Stepper Motor Speeds
  leftMotor.setSpeed(60);
  rightMotor.setSpeed(60);

  //Clear Oled displays
  oled1.clearDisplay();
  oled2.clearDisplay();
  oled1.setCursor(0, 0);
  oled2.setCursor(0, 0);

}

void loop() {
  if (Serial.available() > 0){
    String incomingString = Serial.readString();
    if (incomingString == 'Forward'){
      leftMotor.setSpeed(60);
      rightMotor.setSpeed(60);
      leftMotor.step(stepsPerRevolution);
      rightMotor.step(stepsPerRevolution);
    }
    if (incomingString == 'Backward'){
      leftMotor.setSpeed(60);
      rightMotor.setSpeed(60);
      leftMotor.step(-stepsPerRevolution);
      rightMotor.step(-stepsPerRevolution);
    }
    if (incomingString == 'Left'){
      leftMotor.setSpeed(60);
      rightMotor.setSpeed(60);
      leftMotor.step(-stepsPerRevolution);
      rightMotor.step(stepsPerRevolution);
    }
    if (incomingString == 'Right'){
      leftMotor.setSpeed(60);
      rightMotor.setSpeed(60);
      leftMotor.step(stepsPerRevolution);
      rightMotor.step(-stepsPerRevolution);
    }
    if (incomingString == 'Stop'){
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);      
    }
  }

  //Draw Eyes
  oled1.clearDisplay();
  oled1.drawCircle(20, 35, 20, WHITE);
  oled1.display();
  oled2.clearDisplay();
  oled2.drawCircle(20, 35, 20, WHITE);
  oled2.display();
  delay(200);
}
