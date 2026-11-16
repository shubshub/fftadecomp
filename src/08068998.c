#include "ffta.h"

/* Complete [0x08068998, 0x08068ADE): 326 bytes, 150 instructions, including
 * a three-word literal pool at 0x08068A80.
 *
 * Animated ability icons in a menu window.  On the first tick it collects the
 * abilities granted by the owner's item, draws each ability's current frame
 * (picked by indices[]) as an icon in the window's tile run and refreshes the
 * window; afterwards it advances every icon's frame each 64 ticks, wrapping at
 * the entry's kind (its number of sources). */

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
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 count;
    u8 unknown_16[6];
    u16 tile;
    u8 unknown_1E;
    u8 palette;
} TileRun08068998;

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
    TileRun08068998 run;
} MenuState08068998;

typedef struct {
    u16 id;
} Item08068998;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
    u16 timer;
    u8 indices[3];
    u8 count;
    u8 unknown_10[0x18];
    MenuState08068998 menu;
    u8 unknown_74[0x28];
    GrantedAbilities abilities;
    Item08068998 *item;
    u16 *tiles;
} Context08068998;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState08068998;

extern u8 data_02003CB0[];
extern TileState08068998 data_030008B0;
extern u8 func_080C8D14(u16 item, GrantedAbilities *out);
extern void func_080CB9E0(void *object, u32 value);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_080CBA14(u8 index);
extern void func_0802AB64(TileRun08068998 *, u16, u16, u8, u8, u16, u8);
extern void func_0802AC14(MenuState08068998 *, u16 *, u8, u8, u8);

void func_08068998(Context08068998 *context)
{
    s32 index;

    if (context->flags & 8)
        return;

    if (context->timer == 0) {
        TileRun08068998 *run = &context->menu.run;
        MenuState08068998 *menu = &context->menu;
        s32 width = menu->width;

        context->timer++;
        context->count = func_080C8D14(context->item->id, &context->abilities);
        for (index = 0; index < context->count; index++) {
            u16 tile = 0x251 + index * 8;
            u8 frame = context->indices[index];
            u8 palette;

            if (context->abilities.entries[index].sources[frame] == 0xFF) {
                context->count = 0;
                break;
            }
            func_080CB9E0(data_02003CB0, context->abilities.entries[index].sources[frame]);
            func_0814186C(data_02003CB0, data_030008B0.tiles + tile * 32, 0x80);
            palette = func_080CBA14(context->abilities.entries[index].sources[frame]);
            func_0802AB64(run, width * 7 + 1 + index * 4 * width, tile, width, 4,
                          palette, 0);
        }
        if (context->count)
            func_0802AC14(menu, context->tiles, menu->x, menu->y, menu->height);
    } else {
        context->timer++;
        if (context->timer > 63) {
            context->timer = 0;
            for (index = 0; index < context->count; index++) {
                context->indices[index]++;
                if (context->indices[index] >= context->abilities.entries[index].kind)
                    context->indices[index] = 0;
            }
        }
    }
}
