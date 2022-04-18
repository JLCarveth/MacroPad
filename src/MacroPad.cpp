#include <Keyboard.h>

/**
   @file MacroPad.ino
   @author John L. Carveth <jlcarveth@gmail.com>
   @brief A small macro keypad running on an Arduino Pro Micro
   @version 0.1
   @date 2022-01-13

   @copyright Copyright (c) 2022

*/

// Button Definitions
#define BUTTON_KEY1 KEY_F13
#define BUTTON_KEY2 KEY_F14
#define BUTTON_KEY3 KEY_F15
#define BUTTON_KEY4 KEY_F16
#define BUTTON_KEY5 KEY_F17
#define BUTTON_KEY6 KEY_F18
#define BUTTON_KEY7 KEY_F19
#define BUTTON_KEY8 KEY_F22
#define BUTTON_KEY9 KEY_F23

// Pin Definitions
#define BUTTON_PIN1 0
#define BUTTON_PIN2 2
#define BUTTON_PIN3 3
#define BUTTON_PIN4 4
#define BUTTON_PIN5 5
#define BUTTON_PIN6 6
#define BUTTON_PIN7 7
#define BUTTON_PIN8 8
#define BUTTON_PIN9 9

int vDelay = 100;
void macroCommand(boolean state, uint8_t key);

class Button {
  public:
    const uint8_t key;
    const uint8_t pin;

    Button(uint8_t k, uint8_t p) : key(k), pin(p) {}

    void press(boolean state) {
      if (state == pressed || (millis() - lastPressed <= debounceTime)) {
        return;
      }

      lastPressed = millis();

      macroCommand(state, key);

      pressed = state;
    }

    void update() {
      press(!digitalRead(pin));
    }

  private:
    const unsigned long debounceTime = 100;
    unsigned long lastPressed = 0;
    boolean pressed = 0;
};

Button buttons [] = {
  {(uint8_t) BUTTON_KEY1, BUTTON_PIN1},
  {(uint8_t) BUTTON_KEY2, BUTTON_PIN2},
  {(uint8_t) BUTTON_KEY3, BUTTON_PIN3},
  {(uint8_t) BUTTON_KEY4, BUTTON_PIN4},
  {(uint8_t) BUTTON_KEY5, BUTTON_PIN5},
  {(uint8_t) BUTTON_KEY6, BUTTON_PIN6},
  {(uint8_t) BUTTON_KEY7, BUTTON_PIN7},
  {(uint8_t) BUTTON_KEY8, BUTTON_PIN8},
  {(uint8_t) BUTTON_KEY9, BUTTON_PIN9},
};

const uint8_t NumButtons = sizeof(buttons) / sizeof(Button);

void setup() {
  Serial.begin(38400);

  for (int i = 0; i < NumButtons; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < NumButtons; i++) {
    buttons[i].update();
  }
}

void macroCommand(boolean state, uint8_t key) {
  if (state) {
    //Keyboard.press(KEY_LEFT_CTRL);
    //Keyboard.press(KEY_LEFT_SHIFT);
    //Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(key);
  } else Keyboard.releaseAll();
}
