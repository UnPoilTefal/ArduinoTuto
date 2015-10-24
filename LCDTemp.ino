// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int temperatureValue = 0;
long previousMillis = 0;        // will store last time LED was updated
int potPin = 0;
int redLight = 13;
int blueLight = 10;
int greenLight = 9;
int ledState = 0;
int buzzer = 7;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(redLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(blueLight, OUTPUT);
}

void loop() {

  getTemperature();

  printTemperature();

  if (ledState > 6) {
    ledState = 0;
  }
  switch (ledState) {
    default:
    case 0:
      noLightOn();
      break;

    case 1:
      greenLightOn();
      break;

    case 2:
      blueLightOn();
      break;

    case 3:
      redLightOn();
      break;

    case 4:
      greenLightOn();
      delay(500);
      blueLightOn();
      delay(500);
      redLightOn();
      delay(500);
      noLightOn();
      break;
    case 5:
      Serial.println("buzzer!!!");
      buzzerAlert();
      ledState = 0;
      break;
  }

  // when characters arrive over the serial port...
  if (Serial.available()) {
    lcd.print("                ");
    lcd.setCursor(0, 1);

    while (Serial.available()) {
      // display each character to the LCD
      char serialRead = Serial.read();
      String serialString;
      serialString += serialRead;
      lcd.write(serialRead);

      ledState = serialString.toInt();

    }
    Serial.println(temperatureValue);

  }

}

void getTemperature()
{
  unsigned long interval = 1000;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    int val;
    val = analogRead(potPin);
    temperatureValue = (125 * val) >> 8 ; // Temperature calculation formula
  }
}

void printTemperature()
{
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // print from 0 to 9:
  lcd.print("Temp : ");
  lcd.print(temperatureValue);
  lcd.print("\337C");
}

void noLightOn()
{
  digitalWrite(greenLight, LOW);
  digitalWrite(redLight, LOW);
  digitalWrite(blueLight, LOW);
}
void greenLightOn()
{
  digitalWrite(greenLight, HIGH);
  digitalWrite(redLight, LOW);
  digitalWrite(blueLight, LOW);
}
void blueLightOn()
{
  digitalWrite(greenLight, LOW);
  digitalWrite(redLight, LOW);
  digitalWrite(blueLight, HIGH);
}
void redLightOn()
{
  digitalWrite(greenLight, LOW);
  digitalWrite(redLight, HIGH);
  digitalWrite(blueLight, LOW);
}

void buzzerAlert()
{
  unsigned char i;//define i
  for (i = 0; i < 5; i++) // Output a frequency of sound
  {
    digitalWrite(buzzer, HIGH); //sound
    delay(1);//delay 1ms
    digitalWrite(buzzer, LOW); //mute
    delay(1);//delay 1ms
  }
  for (i = 0; i < 100; i++) // Output the other frequency of sound
  {
    digitalWrite(buzzer, HIGH); //sound
    delay(2);//delay 2ms
    digitalWrite(buzzer, LOW); //mute
    delay(2);//delay 2ms
  }

}

