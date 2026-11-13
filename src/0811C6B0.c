#include "ffta.h"

// Target: complete [0x0811C6B0, 0x0811C85E), 430 bytes, 215 halfwords.
typedef struct {
    void *object;
    u8 angle;
    u8 unknown_05[3];
} Orbit0811C6B0;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Motion0811C6B0;

typedef struct {
    u16 timer;
    u8 unknown_02[6];
    Orbit0811C6B0 orbits[8];
    Motion0811C6B0 motion;
    void *object;
} State0811C6B0;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
} Command0811C6B0;

extern const u8 data_08507EE8[];

extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_0801121C(void *, s16);
extern void func_080E0608(Motion0811C6B0 *, s16, s16, s16);
extern void func_080E064C(Motion0811C6B0 *);
extern u8 func_080E0690(Motion0811C6B0 *);
extern void func_0811C644(Orbit0811C6B0 *, u8);
extern u16 func_0801BB0C(s16, s16, u16);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080DC224(void *, s16, s16, s16 *, s16 *);
extern void func_08003508(s16, u8);
extern void func_08003558(s16, u8);
extern u8 func_0801BDB0(void);
extern void func_08011428(void *);

int func_0811C6B0(void *owner, Command0811C6B0 *command, State0811C6B0 *state)
{
    s16 x;
    s16 y;

    switch (command->phase) {
    case 0:
        state->object = command->object;
        state->timer = 25;
        break;
    case 1:
        break;
    case 0x100:
        if (--state->timer == 0) {
            u8 i;
            u8 angle = 0;
            for (i = 0; i < 8; i++) {
                void *sprite = func_080D5CC0(data_08507EE8, 0, 120, 64, 0x3e0, 6, 0, 0);
                state->orbits[i].object = sprite;
                func_0801121C(sprite, -1);
                state->orbits[i].angle = angle;
                angle += 0x20;
            }
            func_080E0608(&state->motion, 0, 64, 44);
            command->phase++;
        }
        break;
    case 0x101:
        func_080E064C(&state->motion);
        func_0811C644(state->orbits, state->motion.current);
        if (func_080E0690(&state->motion)) {
            func_0801BB0C(56, 208, 40);
            command->phase++;
        }
        break;
    case 0x102:
        func_0811C644(state->orbits, state->motion.current);
        func_080DBDC8(state->object, &x, &y);
        func_080DC224(state->object, x, y, &x, &y);
        func_08003508(x, 3);
        func_08003558(y, 3);
        if (!func_0801BDB0()) {
            func_080E0608(&state->motion, 64, 0, 44);
            command->phase++;
        }
        break;
    case 0x103:
        func_080E064C(&state->motion);
        func_0811C644(state->orbits, state->motion.current);
        if (func_080E0690(&state->motion)) {
            u8 i;
            for (i = 0; i < 8; i++) {
                func_08011428(state->orbits[i].object);
                state->orbits[i].object = 0;
            }
            command->phase = 2;
        }
        break;
    }
    return 0;
}
