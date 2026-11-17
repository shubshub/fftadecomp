#include "ffta.h"

// Target: [0x0801D818, 0x0801D880), 104 bytes, 45 instructions.
// 70b58eb0154c02a900200871002280200001c880081c8021490001814181012505704270
// 011c60890885a08948852089c883a169e26923698026b60198190090019502a8fdf7ccff
// 05482418a18d05480840a0850eb070bc01bc004768810002d8fdfffffdff0000

typedef struct {
    u8 active;
    u8 mode;
    u8 unknown_02[2];
    u8 unknown_04;
    u8 unknown_05;
    u16 unknown_06;
    u16 unknown_08;
    u16 unknown_0A;
    u8 unknown_0C[0x12];
    u16 unknown_1E;
    u8 unknown_20[8];
    u16 x;
    u16 y;
    u16 flags;
    u8 unknown_2E[2];
} View0801D818;

typedef struct {
    u8 unknown_00[8];
    u16 unknown_08;
    u16 x;
    u16 y;
    u8 unknown_0E[2];
    u8 *buffer;
    u8 unknown_14[4];
    void *first;
    void *second;
} Map0801D818;

typedef struct {
    View0801D818 view;
    u8 unknown_030[0x1f8];
    Map0801D818 map;
} State0801D818;

extern State0801D818 g_state_02007F40;
extern void func_0801B7F8(View0801D818 *state, void *first, void *second,
                          void *buffer, void *secondary_buffer, u32 enabled);

void func_0801D818(void)
{
    Map0801D818 *map = &g_state_02007F40.map;
    View0801D818 view;

    view.unknown_04 = 0;
    view.unknown_06 = 0x800;
    view.unknown_08 = 0x100;
    view.unknown_0A = 0x100;
    view.active = 1;
    view.mode = 0;
    view.x = map->x;
    view.y = map->y;
    view.unknown_1E = map->unknown_08;
    func_0801B7F8(&view, map->first, map->second, map->buffer,
                  map->buffer + 0x2000, 1);
    g_state_02007F40.view.flags &= ~2;
}
