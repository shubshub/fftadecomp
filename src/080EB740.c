#include "ffta.h"
#include "control_flags.h"
/* Target: 0x080EB740..0x080EBA9E, 862 bytes, 368 instructions. */
typedef struct { u16 step; u16 unknown_02; void *object; u8 unknown_08[14]; u16 mode; } Command;
/* The interpolator func_080075CC sets up; the two sit 0x2C bytes apart. */
typedef struct { s32 value; s32 unknown_04[10]; } Tween;
typedef struct {
    u16 timer;
    u8 mode;
    u8 unknown_03;
    void *task;
    void *effect;
    void *children[3];
    void *window;
    Tween width;
    Tween height;
    void *object;
    void *transition;
    void *operation;
    void *script;
    void *fade;
} State;
typedef u32 (*TaskCallback)(void *task, void *command, void *payload);
/* Scheduler descriptors are copied as seven words by the scheduler.  This
 * one is never written (no store to sp+0x08..sp+0x23, call at 0x080EB98A),
 * as in func_080EA4A0: func_08005954 sets the copy's phase, the only field
 * func_080EB514 reads. */
typedef struct { u32 unknown_00[7]; } Descriptor;
extern u8 data_08398EA0[], data_088F4EA8[], data_08398F0C[], data_08398FC4[], data_0894D720[];
extern u32 func_080EB514(void *, void *, void *);
extern void *func_080E03F8(void *,void *,int,int,int,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080DFD68(int,int,void *);
extern void *func_080DFED8(void *);
extern void func_080D7220(void *,int,int,int,int,int);
extern void func_080D4870(const void *, void **, int, void *);
extern void func_080D47A0(void *,int);
extern void *func_080DAB84(int, s16, s16, void *);
extern void func_080DABB4(void *);
extern void func_080075CC(Tween *, s16, u16, s16, u16);
extern void func_080DAC80(void *, s16, s16, u16, u16);
extern u16 func_080035D0(u8);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void func_080076A0(Tween *);
extern void func_080D9B98(void *);
extern u32 func_08007880(const Tween *);
extern void *func_08005B6C(TaskCallback, u16, void *, void *);
extern void *func_080D3E9C(void *,void *);
extern int func_08005BB0(void *);
extern void func_08005B58(void *);
extern void func_080D4938(void **, u16);
extern void func_080D9B38(void *);
extern u16 func_080035A8(u8);
extern void func_080EDB80(void *);
extern void *func_080D3F08(void *);
extern void func_080D9B58(void *);
extern u8 func_080D8858(void *,int);
extern void *func_080EDB98(void *,int,void *);
extern void *func_080EDBDC(void *);
int func_080EB740(void *owner, Command *command, State *state)
{
    Descriptor descriptor;
    u8 i;

    switch (command->step) {
    case 0:
        state->mode = command->mode;
        state->object = command->object;
        if (!state->mode)
            state->transition = func_080E03F8(state->object,data_08398EA0,5,4,0,owner);
        break;
    case 1: func_080D38B4(); break;
    case 0x100:
        if (state->mode) {
            state->transition = func_080E05DC(state->transition);
            if (!state->transition) command->step = 0x106;
        } else {
            state->fade = func_080DFD68(1,30,owner);
            command->step++;
        }
        break;
    case 0x101:
        state->transition = func_080E05DC(state->transition);
        if (state->transition) break;
        state->fade = func_080DFED8(state->fade);
        if (state->fade) break;
        func_080D7220(data_088F4EA8,0,2,0,0,0);
        func_080D4870(data_08398F0C,state->children,3,owner);
        for (i = 0; i < 3; i++)
            func_080D47A0(state->children[i],1);
        state->window = func_080DAB84(0,0,0,owner);
        func_080DABB4(state->window);
        func_080075CC(&state->width,0,0,120,89);
        func_080075CC(&state->height,0,0,80,89);
        func_080DAC80(state->window,120,80,state->width.value,state->height.value);
        g_control_flags_03000940.winin_lo = 0x3f;
        g_control_flags_03000940.winout_lo = 0x3f & ~func_080035D0(2);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xff;
        g_control_flags_03000940.display |= 0x2000;
        state->script = func_080DFD8C(data_08398FC4,1,4,0,owner);
        command->step++;
        break;
    case 0x102:
        func_080076A0(&state->width);
        func_080076A0(&state->height);
        func_080DAC80(state->window,120,80,state->width.value,state->height.value);
        func_080D9B98(state->window);
        if (func_08007880(&state->width) && func_08007880(&state->height)) {
            state->task = func_08005B6C(func_080EB514,0x4CC,&descriptor,owner);
            state->timer = 250;
            command->step++;
        }
        break;
    case 0x103:
        if (--state->timer == 0) {
            state->effect = func_080D3E9C(data_0894D720,owner);
            state->timer = 30;
            command->step++;
        }
        break;
    case 0x104:
        if (--state->timer == 0) {
            if (state->task && func_08005BB0(state->task)) {
                func_08005B58(state->task);
                state->task = 0;
            }
            func_080D4938(state->children,3);
            func_080D9B38(state->window);
            g_control_flags_03000940.display &= ~func_080035A8(2);
            g_control_flags_03000940.display &= ~0x2000;
            state->fade = func_080DFD68(0,30,owner);
            func_080EDB80(state->object);
            command->step++;
        }
        break;
    case 0x105:
        state->effect = func_080D3F08(state->effect);
        if (state->effect) break;
        state->fade = func_080DFED8(state->fade);
        if (state->fade) break;
        func_080D9B58(state->window);
        if (func_080D8858(state->object,0)) command->step++;
        else command->step = 2;
        break;
    case 0x106:
        state->operation = func_080EDB98(state->object,4,owner);
        command->step++;
        break;
    case 0x107:
        state->operation = func_080EDBDC(state->operation);
        if (!state->operation) command->step = 2;
        break;
    }
    return 0;
}
