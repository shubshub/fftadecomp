#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 previous_quantity;
} InventoryRecord08027800;

typedef struct {
    u8 unknown_00;
    u8 rows;
    u8 unknown_02;
    u8 visible_count;
    u16 count;
} Menu08027800;

typedef struct {
    u8 unknown_00[0x80];
    Menu08027800 menu;
    u8 unknown_88[0x0c];
    u32 *entries;
    u8 *flags;
    u8 unknown_9c[4];
    u8 *allocation;
} State08027800;

typedef struct {
    u8 unknown_00[0x2a];
    u16 equipment[5];
} Unit08027800;

typedef struct {
    u8 unknown_00[0x18];
    Unit08027800 *unit;
} Selection08027800;

extern Selection08027800 *data_0200F438;
extern const u8 data_083A9CA4[];
extern const u8 data_0839144E[];
extern void *func_08005B28(u32 byte_count);
extern void func_08005318(const void *source, void *destination, u32 size, u32 mode);
extern InventoryRecord08027800 *func_080CB210(u32 identifier, s32 *count);
extern u8 func_080CB1F4(u16 identifier);
extern u8 func_080CB450(Unit08027800 *unit, u16 identifier);
extern u8 func_080CB48C(Unit08027800 *unit, u16 identifier, u8 slot);

/* Complete [0x08027800, 0x08027918): 280 bytes. */
void func_08027800(State08027800 *state)
{
    u8 slot = 0;
    Menu08027800 *menu = &state->menu;
    InventoryRecord08027800 *record;
    u8 *tiles;
    s32 count;
    s32 written;
    s32 i;

    tiles = func_08005B28(0xc0);
    state->allocation = tiles;
    tiles += 0x80;
    func_08005318(data_083A9CA4, tiles, 0x20, 1);
    for (i = 0; i < 5; i++) {
        if (data_0200F438->unit->equipment[i] == 0) {
            slot = i;
            break;
        }
    }
    record = func_080CB210(0, &count);
    for (written = 0, i = 0; i < count; i++, record++) {
        if (func_080CB1F4(record->identifier) && record->quantity != 0 &&
            func_080CB450(data_0200F438->unit, record->identifier)) {
            state->entries[written] = record->identifier;
            if (record->quantity == record->previous_quantity ||
                func_080CB48C(data_0200F438->unit, record->identifier, slot))
                state->flags[written] = 0;
            written++;
        }
    }
    menu->count = written;
    if (menu->count <= 5) {
        menu->visible_count = menu->count;
        menu->rows = data_0839144E[menu->count - 1];
    }
}
