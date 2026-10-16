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

void setup() {

  lcd.begin();
  lcd.backlight();

  Keyboard.begin();
  Mouse.begin();

  // Reset the mouse arrow to the most far right-top position
  for (int i = 0; i < 20; i++) {
    Mouse.move(-100, -100, 0);
    delay(1);
  }
}

void loop() {

  // Exemple
  movement(70, 70);
  Mouse.click();

  movement(210, 150);
  Mouse.click();

  movement(300, 180);
  Mouse.click();

  delay(10000);
  
}


void movement(int x, int y) {

  // Reset XY position
  for (int i = 0; i < 20; i++) {
    Mouse.move(-100, -100, 0);
    delay(10);
  }

  // Move X position
  while (x != 0) {
    int step = constrain(x, -increment, increment);
    Mouse.move(step, 0, 0);
    delay(movementDelay);
    x -= step;
  }

  // Move Y position
  while (y != 0) {
    int step = constrain(y, -increment, increment);
    Mouse.move(0, step, 0);
    delay(movementDelay);
    y -= step;
  }
}

/*
======================================================================
                    KEYBOARD.H - COMMAND REFERENCE
======================================================================

// INITIALIZATION
Keyboard.begin();                  // Initializes keyboard emulation.
Keyboard.end();                    // Stops keyboard emulation.

// TYPING TEXT
Keyboard.print("Hello");           // Types text without adding a new line.
Keyboard.println("Hello");         // Types text followed by a new line.
Keyboard.write('A');               // Sends a single character or keycode.

// PRESSING AND RELEASING KEYS
Keyboard.press('a');               // Presses and holds the A key.
Keyboard.release('a');             // Releases the A key.
Keyboard.releaseAll();             // Releases all currently pressed keys.

// SPECIAL KEYS
Keyboard.press(KEY_RETURN);        // Presses Enter.
Keyboard.press(KEY_BACKSPACE);     // Presses Backspace.
Keyboard.press(KEY_TAB);           // Presses Tab.
Keyboard.press(KEY_ESC);           // Presses Escape.
Keyboard.press(KEY_DELETE);        // Presses Delete.
Keyboard.press(KEY_INSERT);        // Presses Insert.
Keyboard.press(KEY_HOME);          // Presses Home.
Keyboard.press(KEY_END);           // Presses End.
Keyboard.press(KEY_PAGE_UP);       // Presses Page Up.
Keyboard.press(KEY_PAGE_DOWN);     // Presses Page Down.

// ARROW KEYS
Keyboard.press(KEY_UP_ARROW);      // Presses the Up arrow.
Keyboard.press(KEY_DOWN_ARROW);    // Presses the Down arrow.
Keyboard.press(KEY_LEFT_ARROW);    // Presses the Left arrow.
Keyboard.press(KEY_RIGHT_ARROW);   // Presses the Right arrow.

// MODIFIER KEYS
Keyboard.press(KEY_LEFT_CTRL);     // Holds the left Ctrl key.
Keyboard.press(KEY_LEFT_SHIFT);    // Holds the left Shift key.
Keyboard.press(KEY_LEFT_ALT);      // Holds the left Alt key.
Keyboard.press(KEY_LEFT_GUI);      // Holds the left Windows/Command key.

Keyboard.press(KEY_RIGHT_CTRL);    // Holds the right Ctrl key.
Keyboard.press(KEY_RIGHT_SHIFT);   // Holds the right Shift key.
Keyboard.press(KEY_RIGHT_ALT);     // Holds the right Alt key.
Keyboard.press(KEY_RIGHT_GUI);     // Holds the right Windows/Command key.

// FUNCTION KEYS
Keyboard.press(KEY_F1);            // Presses F1.
Keyboard.press(KEY_F2);            // Presses F2.
Keyboard.press(KEY_F5);            // Presses F5.
Keyboard.press(KEY_F12);           // Presses F12.

// KEY COMBINATIONS
Keyboard.press(KEY_LEFT_CTRL);     // Holds Ctrl.
Keyboard.press('c');               // Presses C (Ctrl+C).
Keyboard.releaseAll();             // Releases both keys.

Keyboard.press(KEY_LEFT_CTRL);     // Holds Ctrl.
Keyboard.press('v');               // Presses V (Ctrl+V).
Keyboard.releaseAll();             // Releases both keys.

// COMMON EXAMPLES
Keyboard.print("00");              // Types "00".
Keyboard.print(g);                 // Types the value of variable g.
Keyboard.print(".WMF");            // Types the file extension ".WMF".
Keyboard.write(KEY_RETURN);        // Sends a complete Enter keystroke.
Keyboard.write(KEY_TAB);           // Sends a complete Tab keystroke.


======================================================================
                      MOUSE.H - COMMAND REFERENCE
======================================================================

// INITIALIZATION
Mouse.begin();                     // Initializes mouse emulation.
Mouse.end();                       // Stops mouse emulation.

// CURSOR MOVEMENT
Mouse.move(10, 0, 0);              // Moves the cursor 10 units right.
Mouse.move(-10, 0, 0);             // Moves the cursor 10 units left.
Mouse.move(0, 10, 0);              // Moves the cursor 10 units down.
Mouse.move(0, -10, 0);             // Moves the cursor 10 units up.
Mouse.move(10, 10, 0);             // Moves diagonally right and down.
Mouse.move(0, 0, 1);               // Scrolls the mouse wheel up.
Mouse.move(0, 0, -1);              // Scrolls the mouse wheel down.

// MOUSE CLICKS
Mouse.click();                     // Performs a left mouse click.
Mouse.click(MOUSE_LEFT);           // Performs a left mouse click.
Mouse.click(MOUSE_RIGHT);          // Performs a right mouse click.
Mouse.click(MOUSE_MIDDLE);         // Performs a middle mouse click.

// PRESSING AND RELEASING BUTTONS
Mouse.press(MOUSE_LEFT);           // Presses and holds the left button.
Mouse.release(MOUSE_LEFT);         // Releases the left button.
Mouse.press(MOUSE_RIGHT);          // Presses and holds the right button.
Mouse.release(MOUSE_RIGHT);        // Releases the right button.
Mouse.release();                   // Releases all mouse buttons.

// BUTTON STATUS
Mouse.isPressed(MOUSE_LEFT);       // Returns true if the left button is held.
Mouse.isPressed(MOUSE_RIGHT);      // Returns true if the right button is held.
Mouse.isPressed(MOUSE_MIDDLE);     // Returns true if the middle button is held.

// DRAG AND DROP EXAMPLE
Mouse.press(MOUSE_LEFT);           // Holds the left mouse button.
Mouse.move(50, 0, 0);              // Drags the cursor 50 units right.
Mouse.release(MOUSE_LEFT);         // Releases the button to finish dragging.

// DOUBLE-CLICK EXAMPLE
Mouse.click(MOUSE_LEFT);           // Performs the first left click.
delay(100);                        // Waits 100 milliseconds.
Mouse.click(MOUSE_LEFT);           // Performs the second left click.


======================================================================
                           IMPORTANT NOTES
======================================================================

1. Keyboard.press() holds a key until Keyboard.release() or
   Keyboard.releaseAll() is called.

2. Keyboard.write() sends a key press followed by its release.

3. Mouse.move(x, y, wheel) uses relative movements, not absolute
   screen coordinates.

4. Mouse.move() normally supports values from -128 to 127 per axis.

5. Keyboard and Mouse emulation require a compatible USB HID board,
   such as Arduino Leonardo, Micro, or Pro Micro (ATmega32U4).

6. Keyboard and Mouse commands may interfere with normal computer
   operation if executed continuously inside loop().

======================================================================
*/
