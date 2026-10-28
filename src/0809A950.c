#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 first;
    u8 unknown_1A[2];
    u16 second;
    u8 unknown_1E[0xB2];
    s16 counters[3];
    u16 unknown_D6;
    u8 buffer_D8[16];
    u8 buffer_E8[8];
    u8 unknown_F0[0x18];
} ResetRecord;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer g_callbacks_0836D4B8[];
extern s32 func_080C7EA4(const void *object, u32 selector);

/* 0809A950..0809A9A8: 88 bytes. */
void func_0809A950(ResetRecord *record, s32 count)
{
    s32 index;

    for (index = 0; index < count; index++, record++) {
        record->first = func_080C7EA4(record, 0x14);
        record->second = func_080C7EA4(record, 0x16);
        record->counters[0] = 0;
        record->counters[2] = 0;
        g_callbacks_0836D4B8[0](record->buffer_E8, sizeof(record->buffer_E8));
        g_callbacks_0836D4B8[0](record->buffer_D8, sizeof(record->buffer_D8));
    }
}
