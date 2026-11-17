#include "ffta.h"

// Target 0x0811D4A0..0x0811D5FC, 348 bytes:
// f0b588b0041c0e1c151c318880277f00b94234d0b94204dc00290dd001292bd097e0
// (first 34 of the 348 bytes)

typedef struct {
    u16 state;
    u16 unknown_2;
    void *object;
    void *actor;
} Event;

typedef struct {
    u16 timer;
    s16 x;
    s16 y;
    u16 unknown_6;
    void *task;
    void *effect;
    void *object;
    void *actor;
    void *animation;
} State;

typedef struct {
    u8 unknown_0[4];
    void *object;
    u8 unknown_8[20];
} Descriptor;

extern u8 data_083A6DC4[];
extern u8 data_03003940[];

void func_080DBDC8(void *object, s16 *x, s16 *y);
void *func_080D7A70(const void *entries, u8 mode, void *parent);
void func_0814186C(const void *source, void *destination, u32 control);
void func_080D35D8(void);
void *func_080D7ABC(void *task);
void *func_08005B6C(void *callback, int size, void *descriptor, void *parent);
int func_0811D218(void *owner, Event *event, State *state);
void *func_080E051C(void *task);
void *func_080E5694(void *owner);
void func_080DBEB4(void *object, int mode);
void func_080DD720(void *object, int mode);
void func_080DE10C(void *object, int value);
void *func_080DD350(void *object);
void func_0809A570(void *object, u32 clear, u32 set);
void func_0809A530(void *object, u32 value);
void func_080DE150(void *object, int a, int b);

int func_0811D4A0(void *owner, Event *event, State *state)
{

    switch (event->state) {
    case 0: {
        u16 color;
        u16 *source;
        state->object = event->object;
        state->actor = event->actor;
        func_080DBDC8(state->object, &state->x, &state->y);
        state->animation = func_080D7A70(data_083A6DC4, 8, owner);
        source = &color;
        *source = 0x7FFF;
        func_0814186C(source, data_03003940, 0x01000010);
        break;
    }
    case 1:
        func_080D35D8();
        break;
    case 0x100: {
        Descriptor descriptor;
        state->animation = func_080D7ABC(state->animation);
        if (state->animation) {
            break;
        }
        descriptor.object = state->object;
        state->task = func_08005B6C(func_0811D218, 0x40, &descriptor, owner);
        state->timer = 10;
        event->state++;
        break;
    }
    case 0x101:
        state->task = func_080E051C(state->task);
        if (state->task) {
            break;
        }
        if (state->timer == 0 || --state->timer == 0) {
            state->effect = func_080E5694(owner);
            state->timer = 0x14;
            event->state++;
        }
        break;
    case 0x102:
        if (state->timer != 0 && --state->timer == 0) {
            void *actor;
            func_080DBEB4(state->object, 0);
            func_080DBEB4(state->actor, 1);
            func_080DD720(state->actor, 2);
            func_080DE10C(state->actor, 0x3c);
            actor = func_080DD350(state->actor);
            func_0809A570(actor, 0, 0x100);
            func_0809A530(actor, 2);
        }
        state->effect = func_080E051C(state->effect);
        if (state->effect) {
            break;
        }
        state->timer = 0x28;
        event->state++;
        break;
    case 0x103:
        if (--state->timer == 0) {
            func_080DE150(state->actor, 0, 0);
            event->state = 2;
        }
        break;
    }
    return 0;
}
