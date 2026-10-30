#include "ffta.h"

typedef struct {
    u8 identifier;
    u8 flags;
    u16 count;
} MenuEntry0805DD64;

typedef struct {
    u8 unknown_00[4];
    u8 active[0];
} SlotFlags0805DD64;

typedef struct {
    u8 unknown_0000[0x11AA];
    u8 selected;
    u8 unknown_11AB[0x9D];
    MenuEntry0805DD64 *entries[130];
    SlotFlags0805DD64 *slot_flags;
} MenuState0805DD64;

typedef void (*BufferInitializer0805DD64)(void *destination, u32 size);

extern MenuState0805DD64 *data_0200F448;
extern BufferInitializer0805DD64 const g_callbacks_0836D4B8[];

/* Target [0x0805DD64, 0x0805DDC8), 100 complete bytes:
 * f0b51349134c2068134a8018006804300a680221e4f068fa0023a4460f4f104e
 * 0024fe2560460168c8190078c0188000891909180a68002a04d054805178281c
 * 084050700133012becddf0bc01bc0047b8d4360848f4000250140000aa110000
 * 48120000
 */
void func_0805DD64(void)
{
    s32 index;

    g_callbacks_0836D4B8[0](data_0200F448->slot_flags->active, 2);
    for (index = 0; index < 2; index++) {
        MenuEntry0805DD64 *entry =
            data_0200F448->entries[data_0200F448->selected + index];

        if (entry != 0) {
            entry->count = 0;
            entry->flags &= ~1;
        }
    }
}
