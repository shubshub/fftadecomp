#include "ffta.h"

// Complete target: [0x0802AD54, 0x0802B048), 756 bytes, 272 instructions.

typedef struct {
    u8 unknown_00[0x26];
    u8 busy;
} Window0802AD54;

typedef struct {
    Window0802AD54 window;
    u8 unknown_28[0x794 - 0x28];
    u16 tile;
    u8 layout;
    u8 phase;
    u8 category;
    u8 entry;
    u8 selection;
    u8 id;
    u8 framed;
} State0802AD54;

extern u8 data_030008B0[];
extern u8 data_03000990[];
extern const u8 data_083916C0[][4];
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_0801174C(void *window, u8 id, u8 selection, void *first,
                          void *second, s32 x, s32 y, u32 width, u32 height,
                          u32 tile);
extern void *func_080C83CC(u8 category);
extern void func_080132B8(void *object, u8 alternate);
extern void func_0801339C(u16 value);
extern u32 func_080C8570(u8 first, u8 second, u8 field);
extern void func_08013108(u8 first, u8 second, u8 enabled, u32 tile);
extern void func_08013364(void);
extern void func_08011B30(u8 kind, u16 entry);
extern u16 func_08011860(void);
extern void func_08011C60(void);

void func_0802AD54(State0802AD54 *state)
{
    Window0802AD54 *window = &state->window;
    u8 first;
    u8 second;

    switch (state->phase) {
    case 0:
        break;
    case 1:
        if (state->framed) {
            if (state->layout <= 1)
                func_0802A2C0(0, 0, 30, 9);
            else
                func_0802A2C0(0, 12, 30, 9);
        }
        func_0801174C(state, state->id, state->selection, data_030008B0,
                      data_03000990, (s8)data_083916C0[state->layout][0],
                      (s8)data_083916C0[state->layout][1],
                      data_083916C0[state->layout][2],
                      data_083916C0[state->layout][3], state->tile);
        func_080132B8(func_080C83CC(state->category),
                      state->layout % 2 == 0);
        func_0801339C(3);
        state->phase = 3;
        break;
    case 2:
        if (state->framed)
            func_0802A2C0(0, 0, 30, 9);
        func_0801174C(state, state->id, state->selection, data_030008B0,
                      data_03000990, (s8)data_083916C0[state->layout][0],
                      (s8)data_083916C0[state->layout][1],
                      data_083916C0[state->layout][2],
                      data_083916C0[state->layout][3], state->tile);
        first = func_080C8570(state->entry, state->entry, 9);
        second = func_080C8570(state->entry, state->entry, 10);
        func_08013108(first, second, state->layout % 2 == 0, 0x4800);
        func_0801339C(3);
        state->phase = 3;
        break;
    case 4:
        if (state->framed)
            func_0802A2C0(0, 0, 30, 9);
        func_08013364();
        func_08011B30(state->id, state->selection);
        state->phase = 3;
        break;
    case 3:
        if (window->busy) {
            state->phase = 5;
            break;
        }
        if (func_08011860() == 1) {
            if (state->framed)
                func_0802A2C0(0, 0, 0, 0);
            state->phase = 0;
        }
        break;
    case 5:
        func_08011860();
        break;
    case 6:
        func_08013364();
        state->phase = 7;
        break;
    case 7:
        if (func_08011860() == 1) {
            state->phase = 0;
            if (state->framed)
                func_0802A2C0(0, 0, 0, 0);
        }
        break;
    }
    func_08011C60();
}
