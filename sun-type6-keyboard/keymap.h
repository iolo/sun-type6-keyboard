#ifndef __keymap_h__
#define __keymap_h__

struct KeymapEntry {
  char* name;
  uint8_t normal;
  uint8_t shift;
  uint8_t num_lock;
  KeymapEntry(char* name, uint8_t normal = 0, uint8_t shift = 0, uint8_t num_lock = 0)
    : name(name), normal(normal), shift(shift), num_lock(num_lock) {}
};

extern const KeymapEntry SUN_TO_USB_KEYMAP[0x80];

#endif
