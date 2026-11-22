#include "ffta.h"

// Target [0x080B336C, 0x080B351C): 432 bytes, 180 instructions.

typedef struct TransferRecord TransferRecord;

typedef struct {
    s32 x:16;
    s32 y:16;
    s32 z:16;
} Point080B336C;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    u8 unknown_0A[2];
    s16 y;
} Unit080B336C;

typedef struct {
    u8 unknown_00[0x44];
    void *sprite;
} Entry080B336C;

typedef struct {
    u8 unknown_00[0x80];
    void *party;
} Owner080B336C;

typedef struct {
    u8 unknown_0000[0x141C];
    Owner080B336C *owner;
    Unit080B336C *unit;
    u8 unknown_1424[0xC4];
    Entry080B336C *entries[13];
    u16 values[13];
    u16 count;
    u8 unknown_1538[0x18];
    u8 *graphics;
    void *menu;
    void *object;
    u16 tile;
    u8 unknown_155E[2];
    u8 transfer[4];
} State080B336C;

extern s32 func_080A8430(const Point080B336C *a, const Point080B336C *b);
extern const void *func_080A83EC(s16 x0, s16 y0, s16 x1, s16 y1);
extern void *func_08099C30(void *party);
extern void *func_08021B1C(void *owner);
extern s32 func_08021C90(void *owner, u32 alternate, s32 step);
extern void *func_08021B9C(void *menu);
extern void func_08021C84(void *object, u16 first, u16 second);
extern void *func_08022840(u32 size);
extern s32 func_08005318(const void *data, u8 *output, u16 start, u16 count);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern u32 func_08099CDC(void *party, Entry080B336C **entries);
extern u16 func_08021DE0(const void *object);

void func_080B336C(State080B336C *state)
{
    Point080B336C origin;
    Point080B336C target;
    const void *frames[4];
    s32 start;
    void *owner;
    s32 tile;
    s32 i;

    origin.x = 0;
    origin.y = 0;
    origin.z = 0;
    target = origin;
    target.x = 0x20;
    start = func_080A8430(&origin, &target);

    owner = func_08099C30(state->owner->party);
    state->menu = func_08021B1C(owner);
    tile = func_08021C90(owner, 1, 0x10);
    state->tile = tile;
    state->object = func_08021B9C(state->menu);
    func_08021C84(state->object, tile, 0x10);

    frames[2] = func_080A83EC(state->unit->x, state->unit->y + 0x30,
                              state->unit->x, state->unit->y);
    frames[0] = func_080A83EC(state->unit->x, state->unit->y - 0x30,
                              state->unit->x, state->unit->y);
    frames[3] = func_080A83EC(state->unit->x - 0x30, state->unit->y,
                              state->unit->x, state->unit->y);
    frames[1] = func_080A83EC(state->unit->x + 0x30, state->unit->y,
                              state->unit->x, state->unit->y);

    state->graphics = func_08022840(0x200);
    for (i = 0; i < 4; i++)
        func_08005318(frames[i], state->graphics + i * 0x80, start, 1);
    func_08000ADC((TransferRecord *)state->transfer, state->graphics,
                  (u8 *)0x06010000 + (state->tile << 5), 0x80);

    state->count = func_08099CDC(state->owner->party, state->entries);
    for (i = 0; i < state->count; i++)
        state->values[i] = func_08021DE0(state->entries[i]->sprite);
}
