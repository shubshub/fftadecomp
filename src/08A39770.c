#include "ffta.h"

typedef struct {
    u8 unknown_00[0x16];
    u8 value;
} Object08A39770;

/* Installed at 0x03006BBC and called through ROM slot 0x08394040. */
void func_08A39770(void *object, s32 value)
{
    Object08A39770 *entry = object;
    entry->value = (u8)value;
}
