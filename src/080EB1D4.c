#include "ffta.h"

/* 0x080EB1D4: 570 target bytes, including branch-skipped literal pools. */
typedef struct {
    u16 step;
    u8 unknown_02[2];
    void *resource;
    u8 unknown_08[14];
    u16 mode;
} Command080EB1D4;

typedef struct {
    u16 timer;
    u8 mode;
    void *scheduler;
    void *motion;
    u32 motion_output[2];
    void *first_child;
    void *second_child;
    void *resource;
    void *initial_child;
    void *final_child;
    void *record_child;
    void *transition;
} State080EB1D4;

extern const u8 data_08398DE8[];
extern const u8 data_08398E48[];
extern const u8 data_08398E18[];
extern const u8 data_088F4E9C[];
extern const u8 data_0894D69C[];
extern const u8 data_08949074[];
extern s32 func_080EAFC8(void *, void *, void *);
extern void *func_08005B6C(s32 (*)(void *, void *, void *), u16, void *, void *);
extern s32 func_08005BB0(void *);
extern void func_08005B58(void *);
extern void func_080D38B4(void);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D6134(void *);
extern void func_080D7220(const void *, s32, s32, s32, s32, s32);
extern u8 func_080D8858(void *, s32);
extern void *func_080DFD68(s32, s32, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DFED8(void *);
extern void *func_080E03F8(void *, const void *, u16, u16, s32, void *);
extern void *func_080E05DC(void *);
extern void func_080EDB80(void *);
extern void *func_080EDB98(void *, s32, void *);
extern void *func_080EDBDC(void *);

s32 func_080EB1D4(void *task, Command080EB1D4 *script, State080EB1D4 *state)
{
    u32 descriptor[7];

    switch (script->step) {
    case 0:
        state->mode = script->mode;
        state->resource = script->resource;
        if (state->mode == 0)
            state->initial_child = func_080E03F8(state->resource,
                data_08398DE8, 4, 4, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (state->mode) {
            state->initial_child = func_080E05DC(state->initial_child);
            if (state->initial_child == 0)
                script->step = 0x105;
        } else {
            state->transition = func_080DFD68(1, 30, task);
            script->step++;
        }
        break;
    case 0x101:
        state->initial_child = func_080E05DC(state->initial_child);
        if (state->initial_child == 0) {
            state->transition = func_080DFED8(state->transition);
            if (state->transition == 0) {
                state->scheduler = func_08005B6C(func_080EAFC8, 100,
                    descriptor, task);
                state->record_child = func_080DFD8C(data_08398E48, 3, 4, 0, task);
                state->timer = 64;
                script->step++;
            }
        }
        break;
    case 0x102:
        if (--state->timer == 0) {
            state->motion = func_080D6098(0, 0, 0, 0, 2,
                state->motion_output, data_08398E18, task);
            state->timer = 30;
            script->step++;
        }
        break;
    case 0x103:
        if (state->scheduler && func_08005BB0(state->scheduler)) {
            func_08005B58(state->scheduler);
            state->scheduler = 0;
        }
        if (--state->timer == 0) {
            func_080D7220(data_088F4E9C, 0, 2, 120, 80, 0);
            state->first_child = func_080D3E9C(data_0894D69C, task);
            state->second_child = func_080D4704(data_08949074, task);
            state->timer = 131;
            script->step++;
        }
        break;
    case 0x104:
        if (state->timer) {
            if (--state->timer != 0)
                break;
            state->transition = func_080DFD68(0, 30, task);
            func_080EDB80(state->resource);
        }
        state->motion = func_080D6134(state->motion);
        if (state->motion)
            break;
        state->first_child = func_080D3F08(state->first_child);
        if (state->first_child)
            break;
        state->second_child = func_080D4774(state->second_child);
        if (state->second_child)
            break;
        state->transition = func_080DFED8(state->transition);
        if (state->transition)
            break;
        if (func_080D8858(state->resource, 0))
            script->step++;
        else
            script->step = 2;
        break;
    case 0x105:
        state->final_child = func_080EDB98(state->resource, 3, task);
        script->step++;
        break;
    case 0x106:
        state->final_child = func_080EDBDC(state->final_child);
        if (state->final_child == 0)
            script->step = 2;
        break;
    }
    return 0;
}
