#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 index;
} Unit080CB65C;

typedef struct {
    u8 unknown_00[8];
    u16 first_slot : 4;
    u16 first_resource : 8;
    u16 second_slot : 4;
    u8 second_resource;
    u8 unknown_0B[3];
} __attribute__((packed)) PaletteEntry080CB65C;

typedef void (*BufferCopier080CB65C)(void *destination, const void *source,
                                    u32 size);

extern const PaletteEntry080CB65C g_table_085273D8[];
extern BufferCopier080CB65C data_0836D4BC[];
extern u8 data_03003A60[];
extern u8 func_080C817C(void *unit);
extern const u8 *func_080CBB7C(u8 index);
extern u32 func_080C92F0(void *unit, u32 selector);

/* 080CB65C..080CB714 copies a 32-byte palette into the slot in IWRAM. */
u8 func_080CB65C(Unit080CB65C *unit, u8 selector)
{
    if (func_080C817C(unit)) {
        const PaletteEntry080CB65C *entry = &g_table_085273D8[unit->index];

        if (selector == 1) {
            if (entry->first_resource != 0) {
                data_0836D4BC[0](data_03003A60 +
                                 (entry->first_slot << 5),
                                 func_080CBB7C(entry->first_resource - 1), 32);
            }
            return entry->first_slot;
        } else {
            if (entry->second_resource != 0) {
                data_0836D4BC[0](data_03003A60 +
                                 (entry->second_slot << 5),
                                 func_080CBB7C(entry->second_resource - 1), 32);
            }
            return entry->second_slot;
        }
    } else {
        u32 field = 7;

        if (selector == 1)
            field = 6;
        return func_080C92F0(unit, field);
    }
}
