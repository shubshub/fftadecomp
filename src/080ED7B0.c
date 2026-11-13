#include "ffta.h"
/* Target: 0x080ED7B0..0x080ED9FE, 590 bytes. */
typedef struct { u16 step; u16 unknown_02; void *object; u8 unknown_08[14]; u16 mode; } Command;
typedef struct { u16 timer; u8 mode; u8 unknown_03; void *first; void *second; void *display; void *effect; u8 unknown_14[0x140]; void *object; void *transition; void *operation; void *fade; } State;
/* Scheduler descriptors are copied as seven words by the scheduler. */
typedef struct { u32 unknown_00; void *context; u32 unknown_08; u32 unknown_0c; u32 unknown_10; u32 unknown_14; u32 unknown_18; } Descriptor;
extern u8 data_08399288[], data_088F4D7C[], data_0894904C[], data_0894D69C[], data_0894D720[];
extern void func_080ED4E8(void), func_080ED044(void);
extern void *func_080E03F8(void *,void *,int,int,int,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080DFD68(int,int,void *);
extern void *func_080DFED8(void *);
extern void func_080D7220(void *,int,int,int,int,int);
extern void *func_080D4704(void *,void *);
extern void func_080D47A0(void *,int);
extern void *func_080D3E9C(void *,void *);
extern void *func_08005B6C(void (*)(void),int,Descriptor *,void *);
extern void *func_080D3F08(void *);
extern int func_08005BB0(void *);
extern void func_08005B58(void *), func_080D4768(void *), func_080EDB80(void *);
extern u8 func_080D8858(void *,int);
extern void *func_080EDB98(void *,int,void *), *func_080EDBDC(void *);
int func_080ED7B0(void *owner, Command *command, State *state)
{
    Descriptor descriptor;
    switch (command->step) {
    case 0:
        state->mode = command->mode;
        state->object = command->object;
        if (!state->mode)
            state->transition = func_080E03F8(state->object,data_08399288,4,4,0,owner);
        break;
    case 1: func_080D38B4(); break;
    case 0x100:
        if (state->mode) {
            state->transition = func_080E05DC(state->transition);
            if (!state->transition) command->step = 0x105;
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
        func_080D7220(data_088F4D7C,0,2,120,0,0);
        state->display = func_080D4704(data_0894904C,owner);
        func_080D47A0(state->display,1);
        state->effect = func_080D3E9C(data_0894D69C,owner);
        descriptor.context = state->unknown_14;
        state->first = func_08005B6C(func_080ED4E8,484,&descriptor,owner);
        state->second = func_08005B6C(func_080ED044,188,&descriptor,owner);
        command->step++;
        break;
    case 0x102:
        state->effect = func_080D3F08(state->effect);
        if (func_08005BB0(state->first)) {
            state->effect = func_080D3E9C(data_0894D720,owner);
            state->timer = 30;
            command->step++;
        }
        break;
    case 0x103:
        if (--state->timer == 0) {
            func_08005B58(state->first); state->first = 0;
            func_08005B58(state->second); state->second = 0;
            func_080D4768(state->display);
            state->fade = func_080DFD68(0,30,owner);
            func_080EDB80(state->object);
            command->step++;
        }
        break;
    case 0x104:
        state->effect = func_080D3F08(state->effect);
        if (state->effect) break;
        state->fade = func_080DFED8(state->fade);
        if (state->fade) break;
        if (func_080D8858(state->object,0)) command->step++;
        else command->step = 2;
        break;
    case 0x105:
        state->operation = func_080EDB98(state->object,7,owner);
        command->step++;
        break;
    case 0x106:
        state->operation = func_080EDBDC(state->operation);
        if (!state->operation) command->step = 2;
        break;
    }
    return 0;
}
