# Arduino-Based PC Automation Using Mouse and Keyboard Emulation

A **USB HID-based automation system** developed using an **Arduino Leonardo** to control computer mouse movements, clicks, and keyboard commands without requiring additional software on the target computer.

Originally developed in **2022** to automate laboratory procedures involving an **Atomic Absorption Spectrometry (AAS) instrument** controlled by a computer running **Windows XP**.

The goal was to automate software operations such as starting measurements, navigating menus, and saving analytical data. An initial Python-based solution worked on a modern laptop but could not be implemented successfully on the older computer.

As an alternative, the Arduino Leonardo was programmed to emulate a standard USB mouse and keyboard, allowing automation through predefined screen coordinates and keyboard commands.

The project provides a practical approach for automating **computers and repetitive software tasks**, without requiring extensive Python knowledge.

**Development:** 2022  
**Microcontroller:** Arduino Leonardo / Arduino Micro (ATmega32U4)  
**Programming:** Arduino C/C++  
**Communication:** USB HID (Mouse and Keyboard)  
**Original operating system:** Windows XP  
**Application:** PC automation and laboratory instrumentation

<br>

## Overview

The project consists of **two Arduino sketches**:

1. **Coordinate Finder:** identifies mouse cursor positions using an LCD and three pushbuttons.
2. **Mouse and Keyboard Automation:** reproduces programmed mouse movements and clicks, with support for adding keyboard commands.

The Arduino acts as a standard USB input device, making it possible to automate software interfaces without installing additional programs on the target computer.

This approach is particularly useful for older laboratory instruments and computers with limited software compatibility.

<br>

## Hardware

The coordinate-finding system uses an Arduino Leonardo or Micro, a 16×2 I²C LCD, and three pushbuttons.

| Component | Arduino Pin | Function |
|---|---|---|
| Pushbutton 1 | A1 | Increase X position |
| Pushbutton 2 | D4 | Increase Y position |
| Pushbutton 3 | A0 | Reset cursor position |
| LCD SDA | SDA | I²C communication |
| LCD SCL | SCL | I²C communication |
| LCD VCC | 5V | Power |
| LCD GND | GND | Ground |

The pushbuttons use `INPUT_PULLUP` and are connected between their respective pins and GND. The LCD uses I²C address `0x27`.

**Coordinate Finder hardware:**

<img width="936" height="931" alt="image" src="https://github.com/user-attachments/assets/1785a7c2-7bf9-43e8-a17e-9e531b620666" />

<br>
<br>

## 1. Finding Screen Coordinates

The first sketch allows the user to move the mouse cursor using three physical pushbuttons while displaying the corresponding X and Y values on the LCD.

- **Button 1:** moves the cursor to the right.
- **Button 2:** moves the cursor downward.
- **Button 3:** returns the cursor toward the upper-left corner and resets the displayed coordinates.

The user positions the cursor over a desired software button and records the displayed coordinates.

For example:

```text
X: 200
Y: 100
```

These values can then be used in the automation sketch.

Two parameters control the movement:

```cpp
int increment = 10;
int movementDelay = 100; // ms
```

The `increment` variable defines the movement step, while `movementDelay` controls the delay between movements.

For better visualization of the movement, increase the`movementDelay`. For application when the code is finished, decrease the `movementDelay` to 1.

**Important:** The `increment` value must be the same in both sketches when reproducing the coordinates identified with this method.

<br>

## 2. Mouse and Keyboard Automation

After identifying the required positions, the second sketch can be used as an example of how to reproduce mouse movements and execute programmed actions.

The main function is:

```cpp
movement(x, y);
```

For example:

```cpp
movement(200, 100);
Mouse.click();

movement(210, 150);
Mouse.click();

movement(300, 180);
Mouse.click();
```

Each call first moves the cursor toward the upper-left corner and then moves it to the specified position.

The movement is divided into smaller steps using `constrain()`:

```cpp
int step = constrain(x, -increment, increment);
Mouse.move(step, 0, 0);
x -= step;
```

This allows larger movements to be performed progressively.

### Keyboard Commands

The Arduino can also emulate keyboard operations using the `Keyboard.h` library.

Examples:

```cpp
Keyboard.print("Sample_001");
Keyboard.write(KEY_RETURN);
Keyboard.write(KEY_TAB);
```

Keyboard shortcuts can also be executed:

```cpp
Keyboard.press(KEY_LEFT_CTRL);
Keyboard.press('s');
Keyboard.releaseAll();
```

These commands can be incorporated into an automation sequence to enter filenames, navigate software interfaces, and perform other repetitive tasks.

The provided automation example demonstrates mouse movements and clicks; keyboard commands are available for users to add according to their applications.

<br>

## Demonstration

The original application involved automating operations on a Windows XP computer controlling an AAS instrument.

The Arduino was used to reproduce mouse and keyboard interactions that would otherwise require manual operation, providing an alternative to software-based automation.

**Video — Automated computer operation:**

*[video]*

<br>
<br>

## Arduino Codes

Two Arduino sketches are provided:

| File | Description |
|---|---|
| `Coordinate_Finder.ino` | Identifies cursor positions using an LCD and three pushbuttons |
| `Mouse_Keyboard_Automation.ino` | Demonstrates programmed mouse movements and clicks, with keyboard support |

### Required Libraries

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keyboard.h>
#include <Mouse.h>
```

A compatible `LiquidCrystal_I2C` library may need to be installed through the Arduino IDE.

**Note:** Native USB HID functionality requires a compatible board, such as the Arduino Leonardo or Micro.

<br>

## Getting Started

1. Connect the LCD and pushbuttons according to the pin table.
2. Upload `Coordinate_Finder.ino` to the Arduino.
3. Connect the Arduino to the target computer and identify the desired screen coordinates.
4. Take notes of the coordinates sequence.
5. Open `Mouse_Keyboard_Automation.ino` and enter the recorded coordinates.
6. Keep the same `increment` value in both sketches.
7. Add mouse clicks, keyboard commands, and delays as needed.
8. Upload the automation sketch and test the sequence.

### Important Considerations

The system uses **relative mouse movements**, rather than reading absolute screen coordinates.

Consequently, different screen resolutions, mouse sensitivity settings, pointer acceleration, or application window positions may affect cursor positioning.

For reliable operation, maintain consistent display and pointer settings and recalibrate when using a different computer.

Also, remember that instructions inside `loop()` execute repeatedly. For practical applications, a start button or other controlled trigger is recommended to prevent unintended mouse or keyboard actions.

<br>

## Applications

- Automation of computer software
- Laboratory instrumentation control
- Automated measurement initiation and data saving
- Repetitive mouse and keyboard operations
- Computer interaction triggered by external electronics
- Custom USB HID automation systems

<br>

## Skills Demonstrated

- Arduino C/C++ programming
- USB HID mouse and keyboard emulation
- Computer automation
- LCD interfacing
- Laboratory instrumentation integration

<br>

## Author

**Gilberto Coelho**

This project was designed and programmed by me in 2022 as a practical solution for automating laboratory instrumentation and interacting with a computer software.

The codes are shared as a starting point for developing custom Arduino-based computer automation applications.
