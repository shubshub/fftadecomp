#include "ffta.h"

/* Complete [0x080500B0, 0x080501CC): 284 bytes, 119 instructions. */
typedef struct {
    u8 unknown_00[0x14];
    u8 text[0];
} Source080500B0;

typedef struct {
    u8 unknown_00[8];
    void *destination;
    u16 *row;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[6];
    u16 tile;
} Menu080500B0;

typedef struct {
    Source080500B0 *source;
    u8 unknown_04[0x44];
    Menu080500B0 menu;
    u8 unknown_68[0x28];
    s8 *enabled;
} State080500B0;

typedef struct {
    void *current;
    u8 unknown_04[8];
    u16 id;
    u16 selection;
} Selection080500B0;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics080500B0;

extern Selection080500B0 g_state_020020D0;
extern const u16 g_table_08529EE4[];
extern Graphics080500B0 data_030008B0;
extern const u8 data_084C3798[];
extern const u8 *g_table_085567F0[];
extern u16 func_080502EC(State080500B0 *);
extern void func_08013A88(void *, u16);
extern u8 *func_08005B28(u32);
extern void func_08005B40(void *);
extern u16 func_08013E9C(u8 *, const u8 *, u8 *, u16, u32, u32);
extern void func_08018C24(u8 *, const u8 *);
extern void func_08015110(void *, void *, const u8 *, u32, u32);
extern void func_0804FDF4(State080500B0 *, u32, u32, u16);
extern void func_0804FFB8(Menu080500B0 *, u32, u32, u16, u32);
extern void *func_0804CA8C(void);
extern void func_08000BAC(void *, const u16 *, void *, u16, u16, u16, u16);

void func_080500B0(State080500B0 *state)
{
    Menu080500B0 *menu = &state->menu;
    u16 selection = func_080502EC(state);
    u8 *destination;
    u8 *buffer;
    u16 *row;
    void *map;

    g_state_020020D0.selection = selection;
    g_state_020020D0.current = 0;
    g_state_020020D0.id = g_table_08529EE4[selection - 1];
    destination = data_030008B0.tiles + menu->tile * 32;
    func_08013A88(destination, 28);
    buffer = func_08005B28(0x200);
    if (state->enabled[selection - 1]) {
        u8 *workspace = buffer + 0x100;
        func_08013E9C(buffer, data_084C3798, workspace, 9, 0, 0);
    } else {
        buffer[0] = 0x40;
        buffer[1] = 0x67;
        buffer[2] = 0;
        func_08018C24(buffer + 3, g_table_085567F0[38]);
    }
    func_08015110(state->source->text, destination, buffer, 0, 1);
    func_08005B40(buffer);
    func_0804FDF4(state, 6, 0, selection);
    func_0804FFB8(menu, 2, 1, selection, 0);
    row = menu->row;
    row[1] = 0xd0f8;
    row[2] = 0xd0f9;
    map = menu->destination;
    func_08000BAC(func_0804CA8C(), row, map, (u16)(menu->width - 6),
                  2, menu->width * 2, 64);
}
