#include "ffta.h"

/* 0x08017528..0x080175E0: 184 bytes, 87 instructions. */
typedef struct {
    u8 unknown_00[8];
    u16 *cursor;
    const void *content;
    u8 unknown_10[2];
    u8 remaining;
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 next_row;
    u16 second;
    u8 unknown_1a[2];
    u16 first;
    u8 pitch;
    u8 setting;
} TextRecord;

typedef void (*BufferInitializer)(void *, u32);
extern BufferInitializer g_callbacks_0836D4B8[];
extern u16 func_080161A0(u8 x, u8 y, u8 width);

void func_08017528(TextRecord *record, u16 *source, const void *content,
                   u8 x, u8 y, u8 width, u8 height, u8 pitch,
                   u16 first, u8 setting, u16 second)
{
    g_callbacks_0836D4B8[0](record, sizeof(*record));
    record->x = x;
    record->y = y;
    record->cursor = source + func_080161A0(x, y, pitch);
    record->content = content;
    record->width = width;
    record->height = height;
    record->first = first;
    record->pitch = pitch;
    record->setting = setting;
    record->second = second;
    record->next_row = height + 1;
    record->remaining = width;
}
