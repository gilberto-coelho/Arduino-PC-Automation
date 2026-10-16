#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keyboard.h>
#include <Mouse.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*====================================================================================*/
int increment = 10; // It should be between 1 and 100
int movementDelay = 100; // ms
/*====================================================================================*/

int x = 0;
int y = 0;

#define Button1 A1
#define Button2 4
#define Button3 A0

void setup() {

  lcd.begin();
  lcd.backlight();

  Keyboard.begin();
  Mouse.begin();

  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);

  // Reset the mouse arrow to the most far right-top position
  for (int i = 0; i < 20; i++) {
    Mouse.move(-100, -100, 0);
    delay(1);
  }
}

void loop() {

  lcd.setCursor(0, 0); lcd.print("X: "); lcd.print(x);
  lcd.setCursor(0, 1); lcd.print("Y: "); lcd.print(y);

  // Move X position
  if (digitalRead(Button1) == LOW) {
    x = x + increment;
    Mouse.move(increment, 0, 0);
    delay(movementDelay);
  }

  // Move Y position
  if (digitalRead(Button2) == LOW) {
    y = y + increment;
    Mouse.move(0, increment, 0);
    delay(movementDelay);
  }

  // Reset XY position
  if (digitalRead(Button3) == LOW) {
    x = 0;
    y = 0;
    lcd.clear();
    for (int i = 0; i < 20; i++) {
      Mouse.move(-100, -100, 0);
      delay(1);
    }
  }
}
