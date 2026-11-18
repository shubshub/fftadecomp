#include "ffta.h"

typedef struct {
    u8 unknown_00[0x150];
    void *resource;
} Sprite08A396F8;

/* Installed at 0x03006B44. Slot 0x08394030 is used by 0809A0F4 and 080A0FF0. */
void *func_08A396F8(void *object, void *resource)
{
    Sprite08A396F8 *sprite = object;
    void *previous = sprite->resource;

    sprite->resource = resource;
    return previous;
}
