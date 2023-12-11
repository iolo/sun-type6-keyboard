#include <SoftwareSerial.h>
#include <Keyboard.h>

#include "sun_scancode.h"
#include "keymap.h"

#define HID_KEYBOARD Keyboard

#define CONSOLE Serial
#define CONSOLE_BAUD 115200

#ifdef CONSOLE
#define LOG(...) CONSOLE.print(__VA_ARGS__)
#define LOGLN(...) CONSOLE.println(__VA_ARGS__)
#else
#define LOG(...)
#define LOGLN(...)
#endif

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

// option1. use HardwareSerial with inverter
// https://codeberg.org/xelalexv/suniversal
// #define MOUSE Serial1
// #define MOUSE_BAUD 1200
// #define MOUSE_CONFIG SERIAL_8N2

// option2. another SoftwareSerial --> fail!!!
// SoftwareSerial can listen a port at once!
// https://docs.arduino.cc/tutorials/communication/TwoPortReceive
// #define MOUSE_RX_PIN 9
// // RX only! don't write anything!
// #define MOUSE_TX_PIN MOUSE_RX_PIN
// #define MOUSE_INVERSE_LOGIC true
// SoftwareSerial sun_type6_mouse_serial(MOUSE_RX_PIN, MOUSE_TX_PIN, MOUSE_INVERSE_LOGIC);
// #define MOUSE sun_type6_mouse_serial
// #define MOUSE_BAUD 1200

// option3. attachInterrupt() with serial processing?
// https://www.arduino.cc/reference/ko/language/functions/external-interrupts/attachinterrupt/
// Micro, Leonardo, other 32u4-based: 0, 1, 2, 3, 7
//#define MOUSE_ISR_PIN 2

#define SUN_COMMAND_RESET 0x01
#define SUN_COMMAND_BELL_ON 0x02
#define SUN_COMMAND_BELL_OFF 0x03
#define SUN_COMMAND_CLICK_ON 0x0a
#define SUN_COMMAND_CLICK_OFF 0x0b
#define SUN_COMMAND_LED 0x0e
#define SUN_COMMAND_LAYOUT 0x0f

#define SUN_LED_NUM_LOCK_MASK 0x01
#define SUN_LED_COMPOSE_MASK 0x02
#define SUN_LED_SCROLL_LOCK_MASK 0x04
#define SUN_LED_CAPS_LOCK_MASK 0x08

#define SUN_RESPONSE_IDLE 0x7f
#define SUN_RESPONSE_LAYOUT 0xfe
#define SUN_RESPONSE_RESET 0xff

#define SUN_RESPONSE_RESET_OK 0x04
#define SUN_RESPONSE_RESET_FAIL 0x7e
#define SUN_RESPONSE_RESET_FAIL2 0x01

#define SUN_PRESS_CODE_MASK 0x7f
#define SUN_RELEASE_CODE_MASK 0x80

uint8_t led = 0;

bool shift_mode = false;
bool ctrl_mode = false;
bool alt_mode = false;
bool meta_mode = false;

void setup() {
  init_console();
  init_keyboard();
  init_mouse();
  init_hid_keyboard();
}

void loop() {
  process_console();
  process_keyboard();
  process_mouse();
}

//
//
//

void init_console() {
#ifdef CONSOLE
  CONSOLE.begin(CONSOLE_BAUD);
  while (!CONSOLE) { delay(100); }
#endif
}

void process_console() {
#ifdef CONSOLE
  if (CONSOLE.available()) {
    String s = CONSOLE.readStringUntil('\n');
    if (s == "ping") {
      LOGLN("pong!");
    } else if (s == "reset") {
      LOGLN("reset!");
      send_command(SUN_COMMAND_RESET);
    } else if (s == "bell on") {
      LOGLN("bell on!");
      send_command(SUN_COMMAND_BELL_ON);
    } else if (s == "bell off") {
      LOGLN("bell off!");
      send_command(SUN_COMMAND_BELL_OFF);
    } else if (s == "click on") {
      LOGLN("click on");
      send_command(SUN_COMMAND_CLICK_ON);
    } else if (s == "click off") {
      LOGLN("click off!");
      send_command(SUN_COMMAND_CLICK_OFF);
    } else if (s == "caps on") {
      LOGLN("caps on!");
      led_on(SUN_LED_CAPS_LOCK_MASK);
    } else if (s == "caps off") {
      LOGLN("caps off!");
      led_off(SUN_LED_CAPS_LOCK_MASK);
    } else if (s == "num on") {
      led_on(SUN_LED_NUM_LOCK_MASK);
    } else if (s == "num off") {
      LOGLN("num off!");
      led_off(SUN_LED_NUM_LOCK_MASK);
    } else if (s == "scr on") {
      LOGLN("scr on!");
      led_on(SUN_LED_SCROLL_LOCK_MASK);
    } else if (s == "scr off") {
      LOGLN("scr off!");
      led_off(SUN_LED_SCROLL_LOCK_MASK);
    } else if (s == "compose on") {
      LOGLN("compose on!");
      led_on(SUN_LED_COMPOSE_MASK);
    } else if (s == "compose off") {
      LOGLN("compose off!");
      led_off(SUN_LED_COMPOSE_MASK);
    } else if (s == "layout") {
      LOGLN("layout!");
      send_command(SUN_COMMAND_LAYOUT);
    } else {
      LOGLN("unknown command!");
    }
  }
#endif
}

//
//
//

void init_keyboard() {
#ifdef KEYBOARD
  KEYBOARD.begin(KEYBOARD_BAUD);
#endif
  led_marquee();
  led_marquee();
  led_marquee();
  send_led_command(SUN_LED_NUM_LOCK_MASK);
}

void process_keyboard() {
#ifdef KEYBOARD
  // https://docs.arduino.cc/tutorials/communication/TwoPortReceive
  KEYBOARD.listen();
  while (KEYBOARD.available()) {
    KEYBOARD.listen();
    uint8_t c = KEYBOARD.read();
    if (c == 0) break;
    LOG("kbd << ");
    LOG(c, HEX);
    switch (c) {
      case SUN_RESPONSE_RESET:
        LOG("(RESET)");
        led_marquee();
        led_marquee();
        led_marquee();
        break;
      case SUN_RESPONSE_IDLE:
        LOG("(IDLE)");
        break;
      case SUN_RESPONSE_LAYOUT:
        LOG("(LAYOUT)");
        break;
      case SUN_POWER:
        send_command(SUN_COMMAND_RESET);
        break;
      default:
        uint8_t scan_code = c & SUN_PRESS_CODE_MASK;
        bool pressed = (c & SUN_RELEASE_CODE_MASK) == 0;
        // toggle keys
        switch (c) {
          case SUN_NUM_LOCK:
            led_toggle(SUN_LED_NUM_LOCK_MASK);
            break;
          case SUN_CAPS_LOCK:
            led_toggle(SUN_LED_CAPS_LOCK_MASK);
            break;
          case SUN_SCROLL_LOCK:
            led_toggle(SUN_LED_SCROLL_LOCK_MASK);
            break;
          case SUN_COMPOSE:
            led_toggle(SUN_LED_COMPOSE_MASK);
            break;
        }
        // mode keys
        switch (scan_code) {
          case SUN_LEFT_SHIFT:
          case SUN_RIGHT_SHIFT:
            shift_mode = pressed;
            break;
          //case SUN_RIGHT_CTRL:
          //case SUN_GRAPH
          case SUN_LEFT_CTRL:
            ctrl_mode = pressed;
            break;
          //case SUN_RIGHT_ALT:
          //case SUN_COMPOSE:
          case SUN_LEFT_ALT:
            alt_mode = pressed;
            break;
          case SUN_LEFT_META:
          case SUN_RIGHT_META:
            meta_mode = pressed;
            break;
        }
        // translate to hid key press/release...
        KeymapEntry entry = SUN_TO_USB_KEYMAP[scan_code];
        uint8_t key = entry.normal;
        LOG(c, HEX);
        LOG(pressed ? " press " : " release ");
        LOG(entry.name);
        LOG(" -> ");
        LOG(key, HEX);
        if (shift_mode && entry.shift) {
          key = entry.shift;
          LOG(" -> shift -> ");
          LOG(key, HEX);
          LOG(" -> ");
        }
        if (is_led_on(SUN_LED_NUM_LOCK_MASK) && entry.num_lock) {
          key = entry.num_lock;
          LOG(" -> num_lock -> ");
          LOG(key, HEX);
          LOG(" -> ");
        }
        // arduino keyboard library doesn't use original scan code but performs unexpected translation!
        // TODO: special cases!
        if (pressed) {
          hid_key_press(key);
        } else {
          hid_key_release(key);
        }
        break;
    }
    LOGLN();
  }
#endif
}

void send_command(uint8_t command) {
#ifdef KEYBOARD
  KEYBOARD.write(command);
#else
  LOG("*send_command:");
  LOG(command, HEX);
  LOGLN();
#endif
}

bool is_led_on(uint8_t mask) {
  return led & mask;
}

void led_toggle(uint8_t mask) {
  if (is_led_on(mask)) {
    led_off(mask);
  } else {
    led_on(mask);
  }
}

void led_on(uint8_t mask) {
  send_led_command(led | mask);
}

void led_off(uint8_t mask) {
  send_led_command(led & ~mask);
}

void send_led_command(uint8_t arg) {
  LOG("kbd >> led: ");
  LOG(led, BIN);
  LOG("->");
  LOG(arg, BIN);
  LOGLN();
  led = arg;
  send_command(SUN_COMMAND_LED);
#ifdef KEYBOARD
  KEYBOARD.write(led);
#else
  LOG(">> led=");
  LOG(led, HEX);
  LOGLN();
#endif
}

void led_marquee() {
  uint8_t led_orig = led;
  send_led_command(0);
  delay(20);
  led_on(SUN_LED_NUM_LOCK_MASK);
  delay(20);
  led_off(SUN_LED_NUM_LOCK_MASK);
  led_on(SUN_LED_CAPS_LOCK_MASK);
  delay(20);
  led_off(SUN_LED_CAPS_LOCK_MASK);
  led_on(SUN_LED_SCROLL_LOCK_MASK);
  delay(20);
  led_off(SUN_LED_SCROLL_LOCK_MASK);
  led_on(SUN_LED_COMPOSE_MASK);
  delay(20);
  led_off(SUN_LED_COMPOSE_MASK);
  led_on(SUN_LED_SCROLL_LOCK_MASK);
  delay(20);
  led_off(SUN_LED_SCROLL_LOCK_MASK);
  led_on(SUN_LED_CAPS_LOCK_MASK);
  delay(20);
  led_off(SUN_LED_CAPS_LOCK_MASK);
  led_on(SUN_LED_NUM_LOCK_MASK);
  delay(20);
  led_off(SUN_LED_NUM_LOCK_MASK);
  delay(20);
  send_led_command(led_orig);
}

//
//
//

void init_mouse() {
#ifdef MOUSE
#ifdef MOUSE_CONFIG  // hardware serial
  MOUSE.begin(MOUSE_BAUD, MOUSE_CONFIG);
#else  // software serial
  MOUSE.begin(MOUSE_BAUD);
#endif
#endif
#ifdef MOUSE_ISR_PIN
  pinMode(MOUSE_ISR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MOUSE_ISR_PIN), mouse_isr, CHANGE);
#endif
}

volatile uint8_t mouse_buf[100];
volatile int mouse_buf_head = 0;
volatile int mouse_buf_tail = 0;

void process_mouse() {
#ifdef MOUSE
  // https://docs.arduino.cc/tutorials/communication/TwoPortReceive
  MOUSE.listen();
  while (MOUSE.available()) {
    MOUSE.listen();
    uint8_t c = MOUSE.read();
    if (c == 0) continue;
    LOG("mouse << ");
    LOG(c, HEX);
    LOGLN();
  }
#endif
#ifdef MOUSE_ISR_PIN
  if (mouse_buf_head != mouse_buf_tail) {
    LOG("mouse_isr << ");
    while (mouse_buf_head != mouse_buf_tail) {
      LOG(mouse_buf[mouse_buf_head]);
      LOG(" ");
      if (++mouse_buf_head > sizeof(mouse_buf)) {
        mouse_buf_head = 0;
      }
    }
    LOGLN();
  }
#endif
}

void mouse_isr() {
#ifdef MOUSE_ISR_PIN
  uint8_t state = digitalRead(MOUSE_ISR_PIN);
  mouse_buf[mouse_buf_tail] = state;
  if (++mouse_buf_tail > sizeof(mouse_buf)) {
    mouse_buf_tail = 0;
  }
#endif
}

//
// HID keyboard
//

void init_hid_keyboard() {
#ifdef HID_KEYBOARD
  HID_KEYBOARD.begin();
#endif
}

void hid_key_press(uint8_t key) {
  if (key == 0) return;
#ifdef HID_KEYBOARD
  HID_KEYBOARD.press(key);
#endif
  LOG("hid key press ");
  LOG(key, HEX);
  LOGLN();
}

void hid_key_release(uint8_t key) {
  if (key == 0) return;
#ifdef HID_KEYBOARD
  HID_KEYBOARD.release(key);
#endif
  LOG("hid key release ");
  LOG(key, HEX);
  LOGLN();
}
