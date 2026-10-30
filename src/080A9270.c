#include "ffta.h"

typedef struct State080A9270 State080A9270;

typedef struct {
    u8 unknown_00[8];
    void *field_08;
} Object08099C30;

extern State080A9270 data_0200F9E8;
extern u32 func_08022868(void);
extern void *func_08096D7C(void);
extern void *func_08099C30(const Object08099C30 *object);
extern void func_080A8AFC(State080A9270 *state, u32 value, void *object);

/* 080A9270..080A9298: 40 bytes, including the data_0200F9E8 literal. */
void func_080A9270(void)
{
    State080A9270 *state = &data_0200F9E8;
    u32 value = func_08022868();
    void *object = func_08099C30(func_08096D7C());

    func_080A8AFC(state, value, object);
}
