#include <SoftwareSerial.h>

#define CONSOLE Serial
#define CONSOLE_BAUD 115200

// HardwareSerial doesn't support inverse logic!
//#define KEYBOARD Serial1
// https://docs.arduino.cc/learn/built-in-libraries/software-serial
// pro micro (leonardo compatible) support 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI) for software RX.
#define KEYBOARD_RX_PIN 8
#define KEYBOARD_TX_PIN 7
#define KEYBOARD_INVERSE_LOGIC true
SoftwareSerial sun_type6_keyboard_serial(KEYBOARD_RX_PIN, KEYBOARD_TX_PIN, KEYBOARD_INVERSE_LOGIC);
#define KEYBOARD sun_type6_keyboard_serial
#define KEYBOARD_BAUD 1200

// #define MOUSE_RX_PIN 9
// RX only! don't write anything!
// #define MOUSE_TX_PIN MOUSE_RX_PIN
// #define MOUSE_INVERSE_LOGIC true
// SoftwareSerial sun_type6_mouse_serial(MOUSE_RX_PIN, MOUSE_TX_PIN, MOUSE_INVERSE_LOGIC);
// #define MOUSE sun_type6_mouse_serial
// #define MOUSE_BAUD 1200

enum SunCommand {
  SUN_RESET_COMMAND = 0x01,
  SUN_BELL_ON_COMMAND = 0x02,
  SUN_BELL_OFF_COMMAND = 0x03,
  SUN_CLICK_ON_COMMAND = 0x0a,
  SUN_CLICK_OFF_COMMAND = 0x0b,
  SUN_LED_COMMAND = 0x0e,
  SUN_LAYOUT_COMMAND = 0x0f,
};

enum SunLedMask {
  SUN_NUM = 0x01,
  SUN_COMPOSE = 0x02,
  SUN_SCR = 0x04,
  SUN_CAPS = 0x08,
};

enum SunResponse {
  SUN_RESPONSE_IDLE = 0x7f,
  SUN_RESPONSE_LAYOUT = 0xfe,
  SUN_RESPONSE_RESET = 0xff,
  SUN_RESPONSE_RESET_OK = 0x04,
  SUN_RESPONSE_RESET_FAIL = 0x7e,
  SUN_RESPONSE_RESET_FAIL2 = 0x01,
};

void setup() {
  CONSOLE.begin(CONSOLE_BAUD);
#ifdef KEYBOARD
  KEYBOARD.begin(KEYBOARD_BAUD);
#endif
#ifdef MOUSE
  MOUSE.begin(MOUSE_BAUD);
#endif
}

uint8_t led = 0;

void loop() {
#ifdef KEYBOARD
  while (KEYBOARD.available()) {
    uint8_t c = KEYBOARD.read();
    if (c == 0) continue;
    CONSOLE.print("kbd << ");
    CONSOLE.print(c, HEX);
    CONSOLE.println();
    switch (c) {
      case SUN_RESPONSE_RESET: CONSOLE.println("RESET"); break;
      case SUN_RESPONSE_IDLE: CONSOLE.println("IDLE"); break;
      case SUN_RESPONSE_LAYOUT: CONSOLE.println("LAYOUT"); break;
    }
  }
#endif
#ifdef MOUSE
  while (MOUSE.available()) {
    uint8_t c = MOUSE.read();
    if (c == 0) continue;
    CONSOLE.print("mouse << ");
    CONSOLE.print(c, HEX);
    CONSOLE.println();
  }
#endif
  if (CONSOLE.available()) {
    String s = CONSOLE.readStringUntil('\n');
    if (s == "ping") {
      CONSOLE.println("pong!");
    } else if (s == "reset") {
      CONSOLE.println("reset!");
      KEYBOARD.write(SUN_RESET_COMMAND);
    } else if (s == "bell on") {
      CONSOLE.println("bell on!");
      KEYBOARD.write(SUN_BELL_ON_COMMAND);
    } else if (s == "bell off") {
      CONSOLE.println("bell off!");
      KEYBOARD.write(SUN_BELL_OFF_COMMAND);
    } else if (s == "click on") {
      CONSOLE.println("click on");
      KEYBOARD.write(SUN_CLICK_ON_COMMAND);
    } else if (s == "click off") {
      CONSOLE.println("click off!");
      KEYBOARD.write(SUN_CLICK_OFF_COMMAND);
    } else if (s == "caps on") {
      CONSOLE.println("caps on!");
      led_on(SUN_CAPS);
    } else if (s == "caps off") {
      CONSOLE.println("caps off!");
      led_off(SUN_CAPS);
    } else if (s == "num on") {
      led_on(SUN_NUM);
    } else if (s == "num off") {
      CONSOLE.println("num off!");
      led_off(SUN_NUM);
    } else if (s == "scr on") {
      CONSOLE.println("scr on!");
      led_on(SUN_SCR);
    } else if (s == "scr off") {
      CONSOLE.println("scr off!");
      led_off(SUN_SCR);
    } else if (s == "compose on") {
      CONSOLE.println("compose on!");
      led_on(SUN_COMPOSE);
    } else if (s == "compose off") {
      CONSOLE.println("compose off!");
      led_off(SUN_COMPOSE);
    } else if (s == "layout") {
      CONSOLE.println("layout!");
      KEYBOARD.write(SUN_LAYOUT_COMMAND);
    } else {
      CONSOLE.println("unknown command!");
    }
  }
}

void led_on(uint8_t mask) {
  set_led(led | mask);
}

void led_off(uint8_t mask) {
  set_led(led & ~mask);
}

void set_led(uint8_t new_led) {
  CONSOLE.print(">> led: ");
  CONSOLE.print(led, HEX);
  CONSOLE.print("->");
  CONSOLE.print(new_led, HEX);
  CONSOLE.println();
  led = new_led;
  KEYBOARD.write(SUN_LED_COMMAND);
  KEYBOARD.write(led);
}