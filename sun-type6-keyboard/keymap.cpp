#include <Keyboard.h>

#include "keymap.h"
#include "sun_scancode.h"

// sun scan code(0x00 ~ 0x7f) to KeymapEntry
const KeymapEntry SUN_TO_USB_KEYMAP[0x80] = {
  KeymapEntry("0x00"),                                        //  0x00
  KeymapEntry("STOP"),                                        //  0x01
  KeymapEntry("VOLUME_DOWN"),                                 //  0x02
  KeymapEntry("AGAIN"),                                       //  0x03
  KeymapEntry("VOLUME_UP"),                                   //  0x04
  KeymapEntry("F1", KEY_F1),                                  //  0x05
  KeymapEntry("F2", KEY_F2),                                  //  0x06
  KeymapEntry("F10", KEY_F10),                                //  0x07
  KeymapEntry("F3", KEY_F3),                                  //  0x08
  KeymapEntry("F11", KEY_F11),                                //  0x09
  KeymapEntry("F4", KEY_F4),                                  //  0x0A
  KeymapEntry("F12", KEY_F12),                                //  0x0B
  KeymapEntry("F5", KEY_F5),                                  //  0x0C
  KeymapEntry("GRAPH", KEY_RIGHT_CTRL),                       //  0x0D HANGUL?
  KeymapEntry("F6", KEY_F6),                                  //  0x0E
  KeymapEntry("0x0f"),                                        //  0x0F
  KeymapEntry("F7", KEY_F7),                                  //  0x10
  KeymapEntry("F8", KEY_F8),                                  //  0x11
  KeymapEntry("F9", KEY_F9),                                  //  0x12
  KeymapEntry("LEFT_ALT", KEY_LEFT_ALT),                      //  0x13
  KeymapEntry("UP_ARROW", KEY_UP_ARROW),                      //  0x14
  KeymapEntry("PAUSE", KEY_PAUSE),                            //  0x15
  KeymapEntry("PRINT_SCREEN", KEY_PRINT_SCREEN),              //  0x16
  KeymapEntry("SCROLL_LOCK", KEY_SCROLL_LOCK),                //  0x17
  KeymapEntry("LEFT_ARROW", KEY_LEFT_ARROW),                  //  0x18
  KeymapEntry("PROPS"),                                       //  0x19
  KeymapEntry("UNDO"),                                        //  0x1A
  KeymapEntry("DOWN_ARROW", KEY_DOWN_ARROW),                  //  0x1B
  KeymapEntry("RIGHT_ARROW", KEY_RIGHT_ARROW),                //  0x1C
  KeymapEntry("ESC", KEY_ESC),                                //  0x1D
  KeymapEntry("1!", '1', '!'),                                //  0x1E
  KeymapEntry("2@", '2', '@'),                                //  0x1F
  KeymapEntry("3#", '3', '#'),                                //  0x20
  KeymapEntry("4$", '4', '$'),                                //  0x21
  KeymapEntry("5%", '5', '%'),                                //  0x22
  KeymapEntry("6^", '6', '^'),                                //  0x23
  KeymapEntry("7&", '7', '&'),                                //  0x24
  KeymapEntry("8*", '8', '*'),                                //  0x25
  KeymapEntry("9(", '9', '9'),                                //  0x26
  KeymapEntry("0)", '0', '0'),                                //  0x27
  KeymapEntry("-_", '-', '_'),                                //  0x28
  KeymapEntry("=+", '=', '+'),                                //  0x29
  KeymapEntry("`~", '`', '~'),                                //  0x2A
  KeymapEntry("BACKSPACE", KEY_BACKSPACE),                    //  0x2B
  KeymapEntry("INSERT", KEY_INSERT),                          //  0x2C
  KeymapEntry("VOLUME_MUTE"),                                 //  0x2D
  KeymapEntry("KP/", KEY_KP_SLASH),                           //  0x2E
  KeymapEntry("KP*", KEY_KP_ASTERISK),                        //  0x2F
  KeymapEntry("POWER"),                                       //  0x30
  KeymapEntry("FRONT"),                                       //  0x31
  KeymapEntry("KP./DELETE", KEY_KP_DOT),                      //  0x32
  KeymapEntry("COPY"),                                        //  0x33
  KeymapEntry("HOME", KEY_HOME),                              //  0x34
  KeymapEntry("TAB", KEY_TAB),                                //  0x35
  KeymapEntry("Q", 'q', 'Q'),                                 //  0x36
  KeymapEntry("W", 'w', 'W'),                                 //  0x37
  KeymapEntry("E", 'e', 'E'),                                 //  0x38
  KeymapEntry("R", 'r', 'R'),                                 //  0x39
  KeymapEntry("T", 't', 'T'),                                 //  0x3A
  KeymapEntry("Y", 'y', 'Y'),                                 //  0x3B
  KeymapEntry("U", 'u', 'U'),                                 //  0x3C
  KeymapEntry("I", 'i', 'I'),                                 //  0x3D
  KeymapEntry("O", 'o', 'O'),                                 //  0x3E
  KeymapEntry("P", 'p', 'P'),                                 //  0x3F
  KeymapEntry("[{", '[', '{'),                                //  0x40
  KeymapEntry("]}", ']', '}'),                                //  0x41
  KeymapEntry("DELETE", KEY_DELETE),                          //  0x42
  KeymapEntry("COMPOSE", KEY_RIGHT_ALT),                      //  0x43 HANJA?
  KeymapEntry("KP7/HOME", KEY_KP_7),                          //  0x44
  KeymapEntry("KP8/UP_ARROW", KEY_KP_8),                      //  0x45
  KeymapEntry("KP9/PAGE_UP", KEY_KP_9),                       //  0x46
  KeymapEntry("KP-", KEY_KP_MINUS),                           //  0x47
  KeymapEntry("OPEN"),                                        //  0x48
  KeymapEntry("PASTE"),                                       //  0x49
  KeymapEntry("END", KEY_END),                                //  0x4A
  KeymapEntry("0", '0'),                                      //  0x4B
  KeymapEntry("LEFT_CTRL", KEY_LEFT_CTRL),                    //  0x4C
  KeymapEntry("A", 'a', 'A'),                                 //  0x4D
  KeymapEntry("S", 's', 'S'),                                 //  0x4E
  KeymapEntry("D", 'd', 'D'),                                 //  0x4F
  KeymapEntry("F", 'f', 'F'),                                 //  0x50
  KeymapEntry("G", 'g', 'G'),                                 //  0x51
  KeymapEntry("H", 'h', 'H'),                                 //  0x52
  KeymapEntry("J", 'j', 'J'),                                 //  0x53
  KeymapEntry("K", 'k', 'K'),                                 //  0x54
  KeymapEntry("L", 'l', 'L'),                                 //  0x55
  KeymapEntry(";:", ';', ':'),                                //  0x56
  KeymapEntry("'\"", '\'', '\"'),                             //  0x57
  KeymapEntry("\\|", '\\', '|'),                              //  0x58
  KeymapEntry("ENTER", KEY_RETURN),                           //  0x59
  KeymapEntry("KP_ENTER", KEY_KP_ENTER),                      //  0x5A
  KeymapEntry("KP4/LEFT_ARROW", KEY_KP_4, KEY_LEFT_ARROW),    //  0x5B
  KeymapEntry("KP5", KEY_KP_5),                               //  0x5C
  KeymapEntry("KP6/RIGHT_ARROW", KEY_KP_6, KEY_RIGHT_ARROW),  //  0x5D
  KeymapEntry("KP0/INSERT", KEY_KP_0, KEY_INSERT),            //  0x5E
  KeymapEntry("FIND"),                                        //  0x5F
  KeymapEntry("PAGE_UP", KEY_PAGE_UP),                        //  0x60
  KeymapEntry("CUT"),                                         //  0x61
  KeymapEntry("NUM_LOCK", KEY_NUM_LOCK),                      //  0x62
  KeymapEntry("LEFT_SHIFT", KEY_LEFT_SHIFT),                  //  0x63
  KeymapEntry("Z", 'z', 'Z'),                                 //  0x64
  KeymapEntry("X", 'x', 'X'),                                 //  0x65
  KeymapEntry("C", 'c', 'C'),                                 //  0x66
  KeymapEntry("V", 'v', 'V'),                                 //  0x67
  KeymapEntry("B", 'b', 'B'),                                 //  0x68
  KeymapEntry("N", 'n', 'N'),                                 //  0x69
  KeymapEntry("M", 'm', 'M'),                                 //  0x6A
  KeymapEntry(",<", ',', '<'),                                //  0x6B
  KeymapEntry(".>", '.', '>'),                                //  0x6C
  KeymapEntry("/?", '/', '?'),                                //  0x6D
  KeymapEntry("RIGHT_SHIFT", KEY_RIGHT_SHIFT),                //  0x6E
  KeymapEntry("0x6f"),                                        //  0x6F
  KeymapEntry("KP1/END", KEY_KP_1, KEY_END),                  //  0x70
  KeymapEntry("KP2/DOWN_ARROW", KEY_KP_2, KEY_DOWN_ARROW),    //  0x71
  KeymapEntry("KP3/PAGE_DOWN", KEY_KP_3, KEY_PAGE_DOWN),      //  0x72
  KeymapEntry("0x73"),                                        //  0x73
  KeymapEntry("0x74"),                                        //  0x74
  KeymapEntry("0x75"),                                        //  0x75
  KeymapEntry("HELP"),                                        //  0x76
  KeymapEntry("CAPS_LOCK", KEY_CAPS_LOCK),                    //  0x77
  KeymapEntry("LEFT_META", KEY_LEFT_GUI),                     //  0x78
  KeymapEntry("SPACE", ' '),                                  //  0x79
  KeymapEntry("RIGHT_META", KEY_RIGHT_GUI),                   //  0x7A
  KeymapEntry("PAGE_DOWN", KEY_PAGE_DOWN),                    //  0x7B
  KeymapEntry("0x7c"),                                        //  0x7C
  KeymapEntry("KP+", KEY_KP_PLUS),                            //  0x7D
  KeymapEntry("0x7e"),                                        //  0x7E
  KeymapEntry("0x7f"),                                        //  0x7F
};
