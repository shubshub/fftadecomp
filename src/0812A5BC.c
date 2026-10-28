#include "ffta.h"

/* Target: complete [0x0812A5BC, 0x0812A816), 602 bytes, 230 instructions.
 * These local views describe observed offsets, not complete object extents. */
typedef struct {
    u16 phase;
} Task0812A5BC;

typedef struct {
    u8 unknown_00[6];
    u16 variant;
    u8 unknown_08[0x30a];
    u8 text[18];
    u8 position;
    u8 index;
    u8 length;
    u8 unknown_327;
    u8 alternate;
    u8 unknown_329[3];
    void *window;
    u8 stage;
} State0812A5BC;

extern u8 data_02001F1C[];
extern u8 g_state_020021A0[];
extern const void *const g_table_085516D0[];
extern const void *const g_table_08565F14[];
extern const u8 data_083A8284[];
extern u8 data_030008B0[];
extern u8 data_03000990[];

extern u8 func_0812B570(const u8 *);
extern void func_08018C24(void *, const void *);
extern void func_0814186C(const void *, void *, u32);
extern u32 func_081444B8(const void *);
extern void func_0812B59C(u8 *);
extern u8 func_0812A818(const u8 *, const u8 *);
extern void func_0812A878(State0812A5BC *, void *);
extern void func_0812AE8C(State0812A5BC *);
extern void func_0801174C(void *, u32, u32, void *, void *, u32, u32,
                          u32, u32, u32);
extern void func_0801339C(u16);
extern u16 func_08011860(void);
extern s8 func_08013380(void);
extern void func_08141570(u32, u32);
extern void func_0813BC30(void);
extern void func_08141540(u32);

void func_0812A5BC(Task0812A5BC *task, State0812A5BC *state)
{
    switch (state->stage) {
    case 0:
        state->alternate = 0;
        if (state->variant != 0) {
            if (func_0812B570(state->text)) {
                func_08018C24(data_02001F1C, g_table_085516D0[2]);
                func_0814186C(data_02001F1C, state->text, 10);
                state->length = func_081444B8(state->text) >> 1;
                func_0812B59C(state->text);
                state->position = 0;
                state->index = 0;
                func_0812AE8C(state);
            } else {
                if (func_0812A818(state->text, data_083A8284))
                    state->alternate = 1;
                else
                    func_0812A878(state, data_02001F1C);
            }
        } else {
            if (func_0812B570(state->text)) {
                func_08018C24(g_state_020021A0, g_table_08565F14[0]);
                func_0814186C(g_state_020021A0, state->text, 10);
                state->length = func_081444B8(state->text) >> 1;
                func_0812B59C(state->text);
                state->position = 0;
                state->index = 0;
                func_0812AE8C(state);
            } else {
                func_0812A878(state, g_state_020021A0);
            }
        }
        if (state->alternate) {
            func_0801174C(state->window, 1, 0x2c, data_030008B0,
                          data_03000990, 5, 5, 0x13, 4, 0x3a0);
            func_0801339C(2);
        } else {
            func_0801174C(state->window, 1, 8, data_030008B0,
                          data_03000990, 5, 5, 0x13, 4, 0x3a0);
            func_0801339C(2);
        }
        state->stage = 1;
        break;
    case 1:
        if (func_08011860()) {
            if (func_08013380()) {
                task->phase = 0x104;
            } else {
                if (state->alternate) {
                    func_08141570(1, 0x88);
                    func_0813BC30();
                    state->stage = 2;
                } else {
                    task->phase = 0x107;
                }
            }
        }
        break;
    case 2:
        func_0801174C(state->window, 1, 0x2e, data_030008B0,
                      data_03000990, 4, 5, 0x15, 4, 0x3a0);
        func_0801339C(2);
        state->stage = 3;
        break;
    case 3:
        if (func_08011860()) {
            func_08141540(100);
            task->phase = 0x104;
        }
        break;
    }
}
