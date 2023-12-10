#ifndef __sun_scancode_h__
#define __sun_scancode_h__

// based on sparc HIDboard specification v1 and suniverse.
// https://kentie.net/article/sunkbd/page2.htm
// https://codeberg.org/xelalexv/suniversal
// and verified using my sun type6 HIDboard(din8, korean layout).

#define  SUN_0x00           0x00
#define  SUN_STOP           0x01
#define  SUN_VOLUMN_DOWN    0x02
#define  SUN_AGAIN          0x03
#define  SUN_VOLUMN_UP      0x04
#define  SUN_F1             0x05
#define  SUN_F2             0x06
#define  SUN_F10            0x07
#define  SUN_F3             0x08
#define  SUN_F11            0x09
#define  SUN_F4             0x0a
#define  SUN_F12            0x0b
#define  SUN_F5             0x0c
#define  SUN_GRAPH          0x0d  // RIGHT_CTRL? HANGUL?
#define  SUN_F6             0x0e
#define  SUN_0x0f           0x0f
#define  SUN_F7             0x10
#define  SUN_F8             0x11
#define  SUN_F9             0x12
#define  SUN_LEFT_ALT       0x13
#define  SUN_UP_ARROW       0x14
#define  SUN_PAUSE          0x15  //  BREAK
#define  SUN_PRINT_SCREEN   0x16  //  SYS_RQ
#define  SUN_SCROLL_LOCK    0x17
#define  SUN_LEFT_ARROW     0x18
#define  SUN_PROPS          0x19
#define  SUN_UNDO           0x1a
#define  SUN_DOWN_ARROW     0x1b
#define  SUN_RIGHT_ARROW    0x1c
#define  SUN_ESC            0x1d
#define  SUN_1              0x1e  //  !
#define  SUN_2              0x1f  //  @
#define  SUN_3              0x20  //  #
#define  SUN_4              0x21  //  $
#define  SUN_5              0x22  //  %
#define  SUN_6              0x23  //  ^
#define  SUN_7              0x24  //  &
#define  SUN_8              0x25  //  *
#define  SUN_9              0x26  //  (
#define  SUN_0              0x27  //  )
#define  SUN_HYPHEN         0x28  //  _
#define  SUN_EQUAL          0x29  //  +
#define  SUN_BACKTICK       0x2a  //  ~
#define  SUN_BACKSPACE      0x2b
#define  SUN_INSERT         0x2c
#define  SUN_VOLUME_MUTE    0x2d
#define  SUN_KP_SLASH       0x2e
#define  SUN_KP_ASTERISK    0x2f
#define  SUN_POWER          0x30
#define  SUN_FRONT          0x31
#define  SUN_KP_PERIOD      0x32  //  DELETE
#define  SUN_COPY           0x33
#define  SUN_HOME           0x34
#define  SUN_TAB            0x35
#define  SUN_Q              0x36
#define  SUN_W              0x37
#define  SUN_E              0x38
#define  SUN_R              0x39
#define  SUN_T              0x3a
#define  SUN_Y              0x3b
#define  SUN_U              0x3c
#define  SUN_I              0x3d
#define  SUN_O              0x3e
#define  SUN_P              0x3f
#define  SUN_LEFT_BRACKET   0x40  //  {
#define  SUN_RIGHT_BRACKET  0x41  //  }
#define  SUN_DELETE         0x42
#define  SUN_COMPOSE        0x43  //  RIGHT_ALT? HANJA?
#define  SUN_KP_7           0x44  //  HOME
#define  SUN_KP_8           0x45  //  UP_ARROW
#define  SUN_KP_9           0x46  //  PAGE_UP
#define  SUN_KP_HYPHEN      0x47
#define  SUN_OPEN           0x48
#define  SUN_PASTE          0x49
#define  SUN_END            0x4a
#define  SUN_0              0x4b
#define  SUN_LEFT_CTRL      0x4c
#define  SUN_A              0x4d
#define  SUN_S              0x4e
#define  SUN_D              0x4f
#define  SUN_F              0x50
#define  SUN_H              0x51
#define  SUN_G              0x52
#define  SUN_J              0x53
#define  SUN_K              0x54
#define  SUN_L              0x55
#define  SUN_SEMICOLON      0x56  //  :
#define  SUN_QUOTE          0x57  //  "
#define  SUN_BACKSLASH      0x58  //  |
#define  SUN_ENTER          0x59
#define  SUN_KP_ENTER       0x5a
#define  SUN_KP_4           0x5b  //  LEFT_ARROW
#define  SUN_KP_5           0x5c
#define  SUN_KP_6           0x5d  //  RIGHT_ARROW
#define  SUN_KP_0           0x5e  //  INSERT
#define  SUN_FIND           0x5f
#define  SUN_PAGE_UP        0x60
#define  SUN_CUT            0x61
#define  SUN_NUM_LOCK       0x62
#define  SUN_LEFT_SHIFT     0x63
#define  SUN_Z              0x64
#define  SUN_X              0x65
#define  SUN_C              0x66
#define  SUN_V              0x67
#define  SUN_B              0x68
#define  SUN_N              0x69
#define  SUN_M              0x6a
#define  SUN_COMMA          0x6b  //  <
#define  SUN_PERIOD         0x6c  //  >
#define  SUN_SLASH          0x6d  //  ?
#define  SUN_RIGHT_SHIFT    0x6e
#define  SUN_0x6f           0x6f  //  LINE_FEED?
#define  SUN_KP_1           0x70  //  END
#define  SUN_KP_2           0x71  //  DOWN_ARROW
#define  SUN_KP_3           0x72  //  PAGE_DOWN
#define  SUN_0x73           0x73
#define  SUN_0x74           0x74
#define  SUN_0x75           0x75
#define  SUN_HELP           0x76
#define  SUN_CAPS_LOCK      0x77
#define  SUN_LEFT_META      0x78
#define  SUN_SPACE          0x79
#define  SUN_RIGHT_META     0x7a
#define  SUN_PAGE_DOWN      0x7b
#define  SUN_0x7c           0x7c
#define  SUN_KP_PLUS        0x7d
#define  SUN_0x7e           0x7e
#define  SUN_0x7f           0x7f

#endif
