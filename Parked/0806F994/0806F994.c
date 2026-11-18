#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u16 *source;
    u8 unknown_10[12];
    u16 first_tile;
    u8 stride;
    u8 tag;
} TileTransfer;

typedef struct {
    u8 state;
    u8 phase;
    u8 ticks[3];
    u8 unknown_05;
    u16 selection;
    u8 unknown_08[0x12];
    u8 width;
    u8 height;
    u8 unknown_1c[0x18];
    TileTransfer transfer;
} SelectionState;

typedef struct {
    u8 unknown_00[8];
    u8 type;
    u8 unknown_09[23];
} ItemRecord;

typedef struct {
    u16 id;
    u16 kind;
    u8 sources[4];
} GrantedAbility;

typedef struct {
    u16 count;
    u16 unknown_02;
    GrantedAbility entries[3];
} GrantedAbilities;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics;

extern const ItemRecord g_table_0851D180[];
extern Graphics data_030008B0;
extern u8 func_080C8D14(u16 item, GrantedAbilities *out);
extern void func_080CB9E0(void *object, u32 value);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_080CBA14(u8 index);
extern void func_0802AB64(TileTransfer *, u16, u16, u8, u8, u16, u8);
extern void func_0806F5FC(TileTransfer *, u8, u8);

void func_0806F994(SelectionState *state)
{
    GrantedAbilities abilities;
    u16 buffer[128];
    u8 count;
    u8 width = state->width;
    u8 i;

    if (g_table_0851D180[state->selection].type == 0x1B) {
        count = 0;
    } else {
        count = func_080C8D14(state->selection, &abilities);
    }
    for (i = 0; i < count; i++) {
        if ((state->ticks[i] & 0x3F) == 0) {
            u8 frame = state->ticks[i] >> 6;
            u16 tile = state->transfer.first_tile + (width << 3) + (i << 3);
            u8 palette;

            func_080CB9E0(buffer, abilities.entries[i].sources[frame]);
            func_0814186C(buffer, data_030008B0.tiles + tile * 32, 0x80);
            palette = func_080CBA14(abilities.entries[i].sources[frame]);
            func_0802AB64(&state->transfer, width * 7 + 1 + (width << 2) * i,
                          tile, width, 4, palette, 0);
        }
        state->ticks[i]++;
        if ((state->ticks[i] >> 6) == abilities.entries[i].kind)
            state->ticks[i] = 0;
    }
    func_0806F5FC(&state->transfer, state->width, state->height);
}
